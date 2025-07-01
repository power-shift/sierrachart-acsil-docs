// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Adaptive ERI Moving Average With Filters") 

//Custom study starts here.
SCSFExport scsf_AdaptiveERIWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_AERI = sc.Subgraph[0];
	SCInputRef In_InputData = sc.Input[1];
	SCInputRef In_PriceSetSmoothing = sc.Input[2];
	SCInputRef In_PriceSmoothingPeriod = sc.Input[3];
	SCInputRef In_PriceSmoothingMAType = sc.Input[4];
	SCInputRef In_ERIPeriod = sc.Input[5];
	SCInputRef In_FastPeriodLimit = sc.Input[6];
	SCInputRef In_SlowPeriodLimit = sc.Input[7];
	SCInputRef In_AERIScaleFactorChange = sc.Input[8];
	SCInputRef In_ERINormalSmoothingPeriod = sc.Input[9];
	SCInputRef In_ERINormalSmoothingMAType = sc.Input[10];
	SCInputRef In_ERISetExtraSmoothing = sc.Input[11];
	SCInputRef In_ERIExtraSmoothingPeriod = sc.Input[12];
	SCInputRef In_ERIExtraSmoothingMAType = sc.Input[13];
	SCSubgraphRef Price = sc.Subgraph[1];
	SCSubgraphRef ERI = sc.Subgraph[2];
	SCSubgraphRef ERISmoothed = sc.Subgraph[3];
	SCSubgraphRef ERIFinal = sc.Subgraph[4];
	//SCFloatArrayRef FloatArray = Graph_AERI.Arrays[0];
	
	//remember local variables are not persistent.
	int i, Period;
	float Change, SumTotal, Temp;
	float FastPeriod, SlowPeriod, ScalingFactor;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Adaptive ERI Moving Average With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive ERI Moving Average With Filters. Perry Kaufman came up with ERI which measures the ratio of the direct distance divided by the total distance traveled of the period. He uses it as the Scaling Factor in an EMA equation to create an Adaptive Moving Average (AMA). Since the Scaling Factor didn't slow down enough, he squared it to produce smaller numbers. The fast and slow limits he uses don't do much, so they are usually left out of other AMA's. This version includes an option to change the ERI period directly.<p>The \"Set Price Smoothing?\" option enables cleaning up the price before calculations. If price is really noisy (too noisy for a volatility equation), recommended settings are EMA 3-10. Otherwise leave price smoothing off. The \"Normal Output Smoothing Period\" option enables cleaning up some of the ERI noise before AERI is calculated. It is recommended to smooth ERI out with an EMA 3-7. This allows for less volatility and more consistent movements. The \"Set Extra Output Smoothing?\" allows for double smoothing for cleaner results.<p>The \"AERI Scale Factor Change\" option allows the output line to be sped up or slowed down by modifying the EMA Scale Factor variable in the final adaptive calculation. It is recommended to change the main period variable first and then modify this one for fine tuning. A value of 1.0 (100%) will leave the rate unchanged. A value of 2.0 (200%) will double the rate. A value of 0.5 (50%) will cut the rate in half.<p>To use traditional AERI without any enhancements, turn off all extra options.<p>To visualize what the Scaling Factor is doing, a separate ERI graph can be added with the selected smoothing values. When ERI is close to 0, the AERI line will go flat and move less. Further away from 0 will increase the line movement.";
		
		sc.GraphRegion = 0; //main price graph
		
		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graph
		Graph_AERI.Name = "AERI"; //drawn graphs must have a name.
		Graph_AERI.PrimaryColor = RGB(255, 0, 0);
		Graph_AERI.DrawStyle = DRAWSTYLE_LINE;
		Graph_AERI.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_AERI.LineWidth = 2;
		Graph_AERI.DrawZeros = 0;
		
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
		In_ERIPeriod.SetIntLimits(3, 100);
		In_ERIPeriod.SetDescription("Number of bars for the period. Usually 10-20.");
		
		In_FastPeriodLimit.Name = "Fast Period Limit";
		In_FastPeriodLimit.SetInt(2);
		In_FastPeriodLimit.SetIntLimits(3, 1000);
		In_FastPeriodLimit.SetDescription("Number of bars for the period. Usually 2-10.");
		
		In_SlowPeriodLimit.Name = "Slow Period Limit";
		In_SlowPeriodLimit.SetInt(30);
		In_SlowPeriodLimit.SetIntLimits(3, 1000);
		In_SlowPeriodLimit.SetDescription("Number of bars for the period. Usually 30 or higher.");
		
		In_AERIScaleFactorChange.Name = "AERI Scale Factor Change";
		In_AERIScaleFactorChange.SetFloat(1.0);
		In_AERIScaleFactorChange.SetFloatLimits(0.1, 2.0);
		In_AERIScaleFactorChange.SetDescription("Percent of Scale Factor to change Adaptive calculation. Range 0.1 to 2.0.");
		
		In_ERINormalSmoothingPeriod.Name = "Normal Output Smoothing Period";
		In_ERINormalSmoothingPeriod.SetInt(5);
		In_ERINormalSmoothingPeriod.SetIntLimits(2, 50);
		In_ERINormalSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-20.");
		
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
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = sc.BaseGraphValueFormat;
		
		return;
		}
	
	// Section 2 - Do data processing here

	Period = In_ERIPeriod.GetInt(); //easier to read.
	
	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period + In_ERINormalSmoothingPeriod.GetInt() + (In_ERISetExtraSmoothing.GetYesNo() ? In_ERIExtraSmoothingPeriod.GetInt() : 0.0 );
		//Make sure fast is smaller than slow.
		if(In_FastPeriodLimit.GetInt() > In_SlowPeriodLimit.GetInt() ) {
			//swap the values around
			i = In_FastPeriodLimit.GetInt();
			In_FastPeriodLimit.SetInt( In_SlowPeriodLimit.GetInt() );
			In_SlowPeriodLimit.SetInt(i);
			}
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
	
	//Do the AERI calculations.

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
	
	ERI[sc.Index] = Change / SumTotal;
	
	//Handle smoothing.
	sc.MovingAverage(ERI, ERISmoothed, In_ERINormalSmoothingMAType.GetMovAvgType(), In_ERINormalSmoothingPeriod.GetInt() );
	
	//Handle extra smoothing.
	if( In_ERISetExtraSmoothing.GetYesNo() ) {
		sc.MovingAverage(ERISmoothed, ERIFinal, In_ERIExtraSmoothingMAType.GetMovAvgType(), In_ERIExtraSmoothingPeriod.GetInt() );
		}
	else {
		ERIFinal[sc.Index] = ERISmoothed[sc.Index];
		}
	
	//set the period limits
	FastPeriod = 2.0 / ((float)In_FastPeriodLimit.GetInt() + 1.0);
	SlowPeriod = 2.0 / ((float)In_SlowPeriodLimit.GetInt() + 1.0);
	//multiply it out
	ScalingFactor = ((ERIFinal[sc.Index] * (FastPeriod - SlowPeriod)) + SlowPeriod ) * In_AERIScaleFactorChange.GetFloat();
	//square it and handle scaling factor manual adjust
	ScalingFactor = (ScalingFactor * ScalingFactor ) * In_AERIScaleFactorChange.GetFloat();
	
	if(ScalingFactor < 0.0) {ScalingFactor *= -1.0;} //range must be positive for the next calculation
	
	//EMA type calculation.
	Graph_AERI[sc.Index] = ((Price[sc.Index] - Graph_AERI[sc.Index-1]) * ScalingFactor) + Graph_AERI[sc.Index-1];
}
