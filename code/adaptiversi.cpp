// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Adaptive RSI Moving Average With Filters") 

//Custom study starts here.
SCSFExport scsf_AdaptiveRSIWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_ARSI = sc.Subgraph[0];
	SCInputRef In_ARSIPeriod = sc.Input[0];
	SCInputRef In_RSICalcMAType = sc.Input[1];
	SCInputRef In_InputData = sc.Input[2];
	SCInputRef In_PriceSetSmoothing = sc.Input[3];
	SCInputRef In_PriceSmoothingPeriod = sc.Input[4];
	SCInputRef In_PriceSmoothingMAType = sc.Input[5];
	SCInputRef In_ARSIScaleFactorChange = sc.Input[6];
	SCInputRef In_RSISetSmoothing = sc.Input[7];
	SCInputRef In_RSISmoothingPeriod = sc.Input[8];
	SCInputRef In_RSISmoothingMAType = sc.Input[9];
	SCSubgraphRef Price = sc.Subgraph[1];
	SCSubgraphRef RSI = sc.Subgraph[2];
	SCSubgraphRef RSISmoothed = sc.Subgraph[3];
	//SCFloatArrayRef FloatArray = Graph_ARSI.Arrays[0];

	//remember local variables are not persistent.
	float ScalingFactor;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Adaptive RSI Moving Average With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive RSI Moving Average With Filters. Traditional Adaptive RSI (ARSI) uses straight price and then RSI as the scaling factor without smoothing. The \"Set Price Smoothing?\" option enables cleaning up the price before calculations. If price is really noisy, recommended settings are EMA 3-10. Otherwise leave price smoothing off. The \"Set RSI Smoothing?\" option enables cleaning up some of the RSI noise before ARSI is calculated. It is recommended to smooth RSI out with an EMA 3-7. This allows for less volatility and more consistent movements.<p>The \"Scale Factor Change\" option allows the output line to be sped up or slowed down by modifying the EMA Scale Factor variable in the final adaptive calculation. It is recommended to change the main period variable first and then modify this one for fine tuning. A value of 1.0 (100%) will leave the rate unchanged. A value of 2.0 (200%) will double the rate. A value of 0.5 (50%) will cut the rate in half.<p>To use traditional ARSI without any enhancements, turn off all extra options.<p>Observations: When there's a strong reversal, ARSI will go flat and then bend to follow the price. On weaker events, ARSI will go flat while price bounces around above or below and then returns to the ARSI line. Check indicators and wave counts to verify final motion.<p>To visualize what the scaling factor is doing, a separate RSI graph can be added with the selected smoothing values. When RSI is close to 50, the ARSI line will go flat and move less. Further away from 50 will increase the line movement.";
		
		sc.GraphRegion = 0; //main price graph
		
		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graph
		Graph_ARSI.Name = "ARSI"; //drawn graphs must have a name.
		Graph_ARSI.PrimaryColor = RGB(0, 0, 255);
		Graph_ARSI.DrawStyle = DRAWSTYLE_LINE;
		Graph_ARSI.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_ARSI.LineWidth = 2;
		Graph_ARSI.DrawZeros = 0;
		
		//User Inputs
		
		In_ARSIPeriod.Name = "ARSI Period";
		In_ARSIPeriod.SetInt(35);
		In_ARSIPeriod.SetIntLimits(3, 300);
		In_ARSIPeriod.SetDescription("Number of bars for the period. Useful values are 25 and higher.");
		
		In_RSICalcMAType.Name = "RSI Calculation Moving Average Type";
		In_RSICalcMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_RSICalcMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData.SetDescription("Usually \"Last\" for bar close when viewing stock prices. One of the averages can be used for forex and other less time synchronized data.");

		In_PriceSetSmoothing.Name = "Set Price Smoothing?";
		In_PriceSetSmoothing.SetYesNo(0);
		In_PriceSetSmoothing.SetDescription("Enables extended price smoothing options.");
		
		In_PriceSmoothingPeriod.Name = "Price Smoothing Period";
		In_PriceSmoothingPeriod.SetInt(3);
		In_PriceSmoothingPeriod.SetIntLimits(2, 50);
		In_PriceSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_PriceSmoothingMAType.Name = "Price Smoothing Moving Average Type";
		In_PriceSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_PriceSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");

		In_ARSIScaleFactorChange.Name = "ARSI Scale Factor Change";
		In_ARSIScaleFactorChange.SetFloat(1.0);
		In_ARSIScaleFactorChange.SetFloatLimits(0.1, 2.0);
		In_ARSIScaleFactorChange.SetDescription("Percent of Scale Factor to change Adaptive calculation. Range 0.1 to 2.0.");
		
		In_RSISetSmoothing.Name = "Set RSI Smoothing?";
		In_RSISetSmoothing.SetYesNo(1);
		In_RSISetSmoothing.SetDescription("Enables extended RSI smoothing options.");
		
		In_RSISmoothingPeriod.Name = "RSI Smoothing Period";
		In_RSISmoothingPeriod.SetInt(5);
		In_RSISmoothingPeriod.SetIntLimits(2, 50);
		In_RSISmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_RSISmoothingMAType.Name = "RSI Smoothing Moving Average Type";
		In_RSISmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_RSISmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
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
		sc.DataStartIndex = In_ARSIPeriod.GetInt() - 1;
		//return;
		}

	//Handle price smoothing.
	if( In_PriceSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Price, In_PriceSmoothingMAType.GetMovAvgType(), In_PriceSmoothingPeriod.GetInt() );
		}
	else {
		Price[sc.Index] = sc.BaseDataIn[In_InputData.GetInputDataIndex()][sc.Index];
		}
		
	//Not enough data yet. Pre-load existing data into array for later calculations.
	if( sc.Index < In_ARSIPeriod.GetInt() ) {
		Graph_ARSI[sc.Index] = Price[sc.Index];
		return;
		}
	
	//Do the ARSI calculations.

	sc.RSI(Price, RSI, In_RSICalcMAType.GetMovAvgType(), In_ARSIPeriod.GetInt() );
	
	if( In_RSISetSmoothing.GetYesNo() ) {
		sc.MovingAverage(RSI, RSISmoothed, In_RSISmoothingMAType.GetMovAvgType(), In_RSISmoothingPeriod.GetInt() );
		ScalingFactor = ((RSISmoothed[sc.Index] / 100.0) - 0.5) * 2.0 * In_ARSIScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		//Note that a MA may overshoot the range a little. For this it doesn't matter.
		}
	else {
		ScalingFactor = ((RSI[sc.Index] / 100.0) - 0.5) * 2.0 * In_ARSIScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		}
	
	if(ScalingFactor < 0.0) {ScalingFactor *= -1.0;} //range must be positive for the next calculation
	
	//EMA type calculation.
	Graph_ARSI[sc.Index] = ((Price[sc.Index] - Graph_ARSI[sc.Index-1]) * ScalingFactor) + Graph_ARSI[sc.Index-1];
}
