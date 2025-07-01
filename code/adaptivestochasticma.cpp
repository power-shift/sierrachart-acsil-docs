// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Adaptive Stochastic Moving Average With Filters") 

//Custom study starts here.
SCSFExport scsf_AdaptiveStochasticMAWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_ASTO = sc.Subgraph[0];
	SCInputRef In_ASTOPeriod = sc.Input[0];
	SCInputRef In_ASTOScaleFactorChange = sc.Input[1];
	SCInputRef In_STOSetSmoothing = sc.Input[2];
	SCInputRef In_STOSmoothingPeriod = sc.Input[3];
	SCInputRef In_STOSmoothingMAType = sc.Input[4];
	SCSubgraphRef STO = sc.Subgraph[1];
	SCSubgraphRef STOSmoothed = sc.Subgraph[2];
	//SCFloatArrayRef FloatArray = Graph_ASTO.Arrays[0];

	//remember local variables are not persistent.
	float ScalingFactor;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Adaptive Stochastic Moving Average With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive Stochastic Moving Average With Filters. This was an academic experiment to compare Adaptive RSI with Adaptive Stochastic. It really doesn't show much since Stochastic tends to follow price movements closely. ASTO acts more like an EMA5-10 most of the time.<p>What did come of this experiment is the \"Scale Factor Change\" option. Since Stochastic spends most of its time away from the 50 line, dropping the Scale Factor to 20% (default) of normal finally made this average behave in an adaptive way.<p>The \"Set STO Smoothing?\" option enables cleaning up some of the STO noise after the calculation. It is recommended to smooth STO out with an EMA 3-7.<p>To visualize what the scaling factor is doing, a separate Stochastic graph can be added with the selected smoothing values. When Stochastic is close to 50, the ASTO line will go flat and move less. Further away from 50 will increase the line movement.";
		
		sc.GraphRegion = 0; //main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graph
		Graph_ASTO.Name = "ASTO"; //drawn graphs must have a name.
		Graph_ASTO.PrimaryColor = RGB(255, 255, 0);
		Graph_ASTO.DrawStyle = DRAWSTYLE_LINE;
		Graph_ASTO.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_ASTO.LineWidth = 2;
		Graph_ASTO.DrawZeros = 0;
		
		//User Inputs
		
		In_ASTOPeriod.Name = "ASTO Period";
		In_ASTOPeriod.SetInt(20);
		In_ASTOPeriod.SetIntLimits(3, 300);
		In_ASTOPeriod.SetDescription("Number of bars for the period. Useful values are 30 and higher.");

		In_ASTOScaleFactorChange.Name = "ASTO Scale Factor Change";
		In_ASTOScaleFactorChange.SetFloat(0.2);
		In_ASTOScaleFactorChange.SetFloatLimits(0.05, 1.0);
		In_ASTOScaleFactorChange.SetDescription("Percent of Scale Factor to change Adaptive calculation. Range 0.05 to 1.0. Recommend 0.2 or smaller.");
		
		In_STOSetSmoothing.Name = "Set STO Smoothing?";
		In_STOSetSmoothing.SetYesNo(1);
		In_STOSetSmoothing.SetDescription("Enables extended STO smoothing options.");
		
		In_STOSmoothingPeriod.Name = "STO Smoothing Period";
		In_STOSmoothingPeriod.SetInt(5);
		In_STOSmoothingPeriod.SetIntLimits(2, 50);
		In_STOSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_STOSmoothingMAType.Name = "STO Smoothing Moving Average Type";
		In_STOSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_STOSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = sc.BaseGraphValueFormat;
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run
	if (sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_ASTOPeriod.GetInt() - 1;
		//return;
		}

	//Not enough data yet. Pre-load existing data into array for later calculations.
	if( sc.Index < In_ASTOPeriod.GetInt() ) {
		Graph_ASTO[sc.Index] = sc.BaseDataIn[SC_LAST][sc.Index];
		return;
		}
	
	//Do the ASTO calculations.

	sc.Stochastic(sc.BaseDataIn, STO, In_ASTOPeriod.GetInt(), 0, 0, MOVAVGTYPE_EXPONENTIAL );
	
	if( In_STOSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(STO, STOSmoothed, In_STOSmoothingMAType.GetMovAvgType(), In_STOSmoothingPeriod.GetInt() );
		ScalingFactor = ((STOSmoothed[sc.Index] / 100.0) - 0.5) * 2.0 * In_ASTOScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		//Note that a MA may overshoot the range a little. For this it doesn't matter.
		}
	else {
		ScalingFactor = ((STO[sc.Index] / 100.0) - 0.5) * 2.0 * In_ASTOScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		}
	
	if(ScalingFactor < 0.0) {ScalingFactor *= -1.0;} //range must be positive for the next calculation
	
	//EMA type calculation.
	Graph_ASTO[sc.Index] = ((sc.BaseDataIn[SC_LAST][sc.Index] - Graph_ASTO[sc.Index-1]) * ScalingFactor) + Graph_ASTO[sc.Index-1];
}
