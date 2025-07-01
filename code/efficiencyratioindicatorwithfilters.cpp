// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Efficiency Ratio Indicator With Filters") 

//Custom study starts here.
SCSFExport scsf_EfficiencyRatioIndicatorWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_ERI = sc.Subgraph[0];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_PriceSetSmoothing = sc.Input[1];
	SCInputRef In_PriceSmoothingPeriod = sc.Input[2];
	SCInputRef In_PriceSmoothingMAType = sc.Input[3];
	SCInputRef In_ERIPeriod = sc.Input[4];
	SCInputRef In_ERINormalSmoothingPeriod = sc.Input[5];
	SCInputRef In_ERINormalSmoothingMAType = sc.Input[6];
	SCInputRef In_ERISetExtraSmoothing = sc.Input[7];
	SCInputRef In_ERIExtraSmoothingPeriod = sc.Input[8];
	SCInputRef In_ERIExtraSmoothingMAType = sc.Input[9];
	SCInputRef In_ERIOutputMultiplier = sc.Input[10];
	SCSubgraphRef Price = sc.Subgraph[1];
	SCSubgraphRef ERI = sc.Subgraph[2];
	SCSubgraphRef ERISmoothed = sc.Subgraph[3];
	//SCFloatArrayRef FloatArray = Graph_ERI.Arrays[0];
	
	//remember local variables are not persistent.
	int i, Period;
	float Change, SumTotal, Temp;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Efficiency Ratio Indicator With Filters";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Efficiency Ratio Indicator With Filters by Perry Kaufman. This indicator measures volatility relative to previous samples. In short, it measures the direct distance between 2 points and divides it by the sum of the difference between each of those points. The normal indicator range is 0.0 to 1.0 (essentially 0% to 100%). Values closer to 1.0 are moving with a higher efficiency than those closer to 0.0.<p>This version includes extra smoothing options to help clean up the output line.<p>This algorithm forms the core of the generic adaptive moving average line.";
		
		//sc.GraphRegion = 1; //in this case, not main price graph. Let it auto-choose.

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graph
		Graph_ERI.Name = "ERI"; //drawn graphs must have a name.
		Graph_ERI.PrimaryColor = RGB(255, 0, 0);
		Graph_ERI.DrawStyle = DRAWSTYLE_LINE;
		Graph_ERI.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_ERI.LineWidth = 1;
		Graph_ERI.DrawZeros = 1;
		
		//User Inputs
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData.SetDescription("Usually \"Last\" for Close.");
		
		In_PriceSetSmoothing.Name = "Set Price Smoothing?";
		In_PriceSetSmoothing.SetYesNo(0);
		In_PriceSetSmoothing.SetDescription("Enables extended price smoothing options.");
		
		In_PriceSmoothingPeriod.Name = "Price Smoothing Period";
		In_PriceSmoothingPeriod.SetInt(3);
		In_PriceSmoothingPeriod.SetIntLimits(2, 50);
		In_PriceSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-5.");
		
		In_PriceSmoothingMAType.Name = "Price Smoothing Moving Average Type";
		In_PriceSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_PriceSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_ERIPeriod.Name = "ERI Period";
		In_ERIPeriod.SetInt(15);
		In_ERIPeriod.SetIntLimits(2, 100);
		In_ERIPeriod.SetDescription("Number of bars for the period. Usually 10-20.");
		
		In_ERINormalSmoothingPeriod.Name = "Normal Output Smoothing Period";
		In_ERINormalSmoothingPeriod.SetInt(5);
		In_ERINormalSmoothingPeriod.SetIntLimits(2, 50);
		In_ERINormalSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_ERINormalSmoothingMAType.Name = "Normal Output Smoothing Moving Average Type";
		In_ERINormalSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_ERINormalSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");

		In_ERISetExtraSmoothing.Name = "Set Extra Output Smoothing?";
		In_ERISetExtraSmoothing.SetYesNo(1);
		In_ERISetExtraSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_ERIExtraSmoothingPeriod.Name = "Extra Output Smoothing Period";
		In_ERIExtraSmoothingPeriod.SetInt(5);
		In_ERIExtraSmoothingPeriod.SetIntLimits(2, 50);
		In_ERIExtraSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_ERIExtraSmoothingMAType.Name = "Extra Output Smoothing Moving Average Type";
		In_ERIExtraSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_ERIExtraSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_ERIOutputMultiplier.Name = "Output Multiplier";
		In_ERIOutputMultiplier.SetFloat(1.0);
		In_ERIOutputMultiplier.SetFloatLimits(0.1, 1000.0);
		In_ERIOutputMultiplier.SetDescription("Increase the number's size for human readability. Since the range is 0.0-1.0, select 100.0 to make this naturally fit on a 100 range chart.");
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Graph start at 0 and goes to 1.0.
		sc.ScaleRangeType = SCALE_ZEROBASED;
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = 3;
		
		return;
		}
	
	// Section 2 - Do data processing here

	Period = In_ERIPeriod.GetInt(); //easier to read.
	
	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period + In_ERINormalSmoothingPeriod.GetInt() + (In_ERISetExtraSmoothing.GetYesNo() ? In_ERIExtraSmoothingPeriod.GetInt() : 0.0 );
		}
	
	//Handle price smoothing.
	if( In_PriceSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Price, In_PriceSmoothingMAType.GetMovAvgType(), In_PriceSmoothingPeriod.GetInt() );
		}
	else {
		Price[sc.Index] = sc.BaseDataIn[In_InputData.GetInputDataIndex()][sc.Index];
		}
	
	//not enough data yet for the calculation.
	if(sc.Index < Period) {return;}
	
	//do the ERI calculations
	
	//direct distance
	Change = Price[sc.Index] - Price[sc.Index - Period];
	if(Change < 0.0) {Change *= -1.0;} //number must be positive
	
	//indirect distance: add up the sums
	SumTotal = 0.0;
	for(i=sc.Index-Period; i < sc.Index; i++) {
		Temp = Price[i+1] - Price[i];
		if(Temp < 0.0) {Temp *= -1.0;} //number must be positive
		SumTotal += Temp;
		}
	
	ERI[sc.Index] = (Change / SumTotal) * In_ERIOutputMultiplier.GetFloat();
	
	//Handle smoothing.
	sc.MovingAverage(ERI, ERISmoothed, In_ERINormalSmoothingMAType.GetMovAvgType(), In_ERINormalSmoothingPeriod.GetInt() );
	
	//Handle extra smoothing.
	if( In_ERISetExtraSmoothing.GetYesNo() ) {
		sc.MovingAverage(ERISmoothed, Graph_ERI, In_ERIExtraSmoothingMAType.GetMovAvgType(), In_ERIExtraSmoothingPeriod.GetInt() );
		}
	else {
		Graph_ERI[sc.Index] = ERISmoothed[sc.Index];
		}
}
