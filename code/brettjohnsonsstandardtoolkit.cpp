// The top of every source code file must include this line
#include "sierrachart.h"
/*****************************************************************************
	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
*****************************************************************************/

/* =============================================================================
A collection of studies and trading programs I've put together for chart
analysis, trading, and educational reference. These have been consolidated into
a single DLL for ease of management and distribution. Each study is documented.
Use the "Display Study Documentation" button for instructions.
============================================================================= */

// Name of the custom study.
SCDLLName("Brett Johnson's Standard Tool Kit")

/* =============================================================================
================================================================================
Reminder: use the "Display Study Documentation" button.
================================================================================
============================================================================= */

SCSFExport scsf_ReadMe(SCStudyGraphRef sc) {
	if (sc.SetDefaults) {
		sc.GraphName = "0: Use the \"Display Study Documentation\" button.";
		sc.StudyDescription = "A collection of studies and trading programs I've put together for chart analysis, trading, and educational reference. These have been consolidated into a single DLL for ease of management and distribution. Use the \"Display Study Documentation\" button for instructions on each.";
		}
	}
	
/* =============================================================================
================================================================================
AMA: Adaptive ERI Moving Average With Filters
================================================================================
============================================================================= */
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
		sc.GraphName = "AMA: Adaptive ERI Moving Average With Filters";
		
		sc.StudyVersion = 1.2;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 6; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive ERI Moving Average With Filters. Perry Kaufman came up with ERI which measures the ratio of the direct distance divided by the total distance traveled of the period. He uses it as the Scaling Factor in an EMA equation to create an Adaptive Moving Average (AMA). Since the Scaling Factor didn't slow down enough, he squared it to produce smaller numbers. The fast and slow limits he uses don't do much, so they are usually left out of other AMA's. This version includes an option to change the ERI period directly.\
<p>The \"Set Price Smoothing?\" option enables cleaning up the price before calculations. If price is really noisy (too noisy for a volatility equation), recommended settings are EMA 3-10. Otherwise leave price smoothing off. The \"Normal Output Smoothing Period\" option enables cleaning up some of the ERI noise before AERI is calculated. It is recommended to smooth ERI out with an EMA 3-7. This allows for less volatility and more consistent movements. The \"Set Extra Output Smoothing?\" allows for double smoothing for cleaner results.\
<p>The \"AERI Scale Factor Change\" option allows the output line to be sped up or slowed down by modifying the EMA Scale Factor variable in the final adaptive calculation. It is recommended to change the main period variable first and then modify this one for fine tuning. A value of 1.0 (100%) will leave the rate unchanged. A value of 2.0 (200%) will double the rate. A value of 0.5 (50%) will cut the rate in half.\
<p>To use traditional AERI without any enhancements, turn off all extra options.\
<p>To visualize what the Scaling Factor is doing, a separate ERI graph can be added with the selected smoothing values. When ERI is close to 0, the AERI line will go flat and move less. Further away from 0 will increase the line movement.";
		
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
		
		return;
		}
	
	// Section 2 - Do data processing here

	Period = In_ERIPeriod.GetInt(); //easier to read.
	
	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period + In_ERINormalSmoothingPeriod.GetInt() + (In_ERISetExtraSmoothing.GetYesNo() ? In_ERIExtraSmoothingPeriod.GetInt() : 0 );
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

/* =============================================================================
================================================================================
AMA: Adaptive IIO Moving Average With Filters
================================================================================
============================================================================= */
SCSFExport scsf_AdaptiveIIOWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_AIIO = sc.Subgraph[0];
	SCInputRef In_IIOPeriod = sc.Input[0];
	SCInputRef In_VolumeFilterType = sc.Input[1];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[2];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[3];
	SCInputRef In_IIOSetSmoothing = sc.Input[4];
	SCInputRef In_IIOSmoothingPeriod = sc.Input[5];
	SCInputRef In_IIOSmoothingMAType = sc.Input[6];
	SCInputRef In_AIIOScaleFactorChange = sc.Input[7];
	SCSubgraphRef II = sc.Subgraph[1];
	SCSubgraphRef IIO = sc.Subgraph[2];
	SCSubgraphRef IIOSmoothed = sc.Subgraph[3];
	SCSubgraphRef VolumeMA = sc.Subgraph[4];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[5];
	//SCFloatArrayRef FloatArray = Graph_AIIO.Arrays[0];

	//remember local variables are not persistent.
	int i, j, k, Period, IndexTemp;
	float RunningTotalII, RunningTotalVolume, ScalingFactor;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "AMA: Adaptive IIO Moving Average With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 6; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive IIO Moving Average With Filters. A price and volume based adaptive moving average from the Intraday Intensity Oscillator. Since IIO is semi-predictive, it is recommended to also run regular IIO in a sub chart for comparison.\
<p>This version includes extras to help clean up the graph and make it easier to integrate with automation. The \"Set IIO Smoothing?\" option enables cleaning up some of the IIO noise after the calculation. It is recommended to smooth IIO out with an EMA 3-7.\
<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.\
<p>The \"Scale Factor Change\" option allows the output line to be sped up or slowed down by modifying the EMA Scale Factor variable in the final adaptive calculation. It is recommended to change the main period variable first and then modify this one for fine tuning. A value of 1.0 (100%) will leave the rate unchanged. A value of 2.0 (200%) will double the rate. A value of 0.5 (50%) will cut the rate in half.\
<p>Observations. AIIO will often slow down and go flat when a movement is almost over. When there's a strong reversal, AIIO will go flat and then bend to follow the price. AIIO will often ignore most of a large price spike that's fake. AIIO will often go flat through noise that other adaptive moving averages will track.\
<p>First known public AIIO version by Brett Johnson, 2015.";
		
		//Output Graph
		Graph_AIIO.Name = "AIIO"; //drawn graphs must have a name.
		Graph_AIIO.PrimaryColor = RGB(0, 255, 0);
		Graph_AIIO.DrawStyle = DRAWSTYLE_LINE;
		Graph_AIIO.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_AIIO.LineWidth = 2;
		Graph_AIIO.DrawZeros = 0;
		
		//User Inputs
		
		In_IIOPeriod.Name = "IIO Period";
		In_IIOPeriod.SetInt(20);
		In_IIOPeriod.SetIntLimits(3, 300);
		In_IIOPeriod.SetDescription("Number of bars for the period. Useful values are 20 and higher.");
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");	
		
		In_IIOSetSmoothing.Name = "Set IIO Smoothing?";
		In_IIOSetSmoothing.SetYesNo(1);
		In_IIOSetSmoothing.SetDescription("Enables extended IIO smoothing options.");
		
		In_IIOSmoothingPeriod.Name = "IIO Smoothing Period";
		In_IIOSmoothingPeriod.SetInt(7);
		In_IIOSmoothingPeriod.SetIntLimits(2, 50);
		In_IIOSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_IIOSmoothingMAType.Name = "IIO Smoothing Moving Average Type";
		In_IIOSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_IIOSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_AIIOScaleFactorChange.Name = "AIIO Scale Factor Change";
		In_AIIOScaleFactorChange.SetFloat(1.0);
		In_AIIOScaleFactorChange.SetFloatLimits(0.1, 2.0);
		In_AIIOScaleFactorChange.SetDescription("Percent of Scale Factor to change Adaptive calculation. Range 0.1 to 2.0.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	i = sc.Index; //easier to read traditional C/C++ index i in multiple arrays on one line.
	Period = In_IIOPeriod.GetInt(); //easier to read.
	
	//if first run
	if (i == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period - 1 + (In_IIOSetSmoothing.GetYesNo() ? In_IIOSmoothingPeriod.GetInt() : 0 );
		}

	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[i] = (float)sc.Volume[i];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[i] = log( (float)sc.Volume[i] < 1.0 ? 1.0 : (float)sc.Volume[i] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[i] = sqrt( (float)sc.Volume[i] < 1.0 ? 1.0 : (float)sc.Volume[i] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.Volume[i] <= VolumeMA[i]) {VolumeFiltered[i] = (float)sc.Volume[i];} //handle normal volume
		else {VolumeFiltered[i] = (float)VolumeMA[i];} //handle clipped volume
		}

	//Generate Intraday Intensity values.
	//Handle divide by 0 problems.
	if( (VolumeFiltered[i] < 0.01) || (sc.High[i] == sc.Low[i]) ) {II[i] = 0.0;}
	//else calculate as normal.
	//Analysis: ScalingFactor * Volume. If close is in the middle, ScalingFactor=0.0.
	//If close is at the top, ScalingFactor=1.0. If close is at the bottom, ScalingFactor=-1.0.
	else {II[i] = (((2.0 * sc.Close[i]) - sc.High[i] - sc.Low[i]) / (sc.High[i] - sc.Low[i])) * VolumeFiltered[i];}
	
	//Not enough data yet for the IIO calculation.
	if( i < Period ) {return;}
	
	//do the inner loop
	for(j=i-Period+1; j<=i; j++) {
		RunningTotalII = 0.0;
		RunningTotalVolume = 0.0;
		IndexTemp = j - Period +1;
		if(IndexTemp < 0) {IndexTemp = 0;}
		for(k=IndexTemp; k<=j; k++) {
			RunningTotalII += II[k];
			//Safety: Under some very rare circumstances, a volume moving average number may be negative.
			//Filter those out so the indicator doesn't get trashed.
			if(VolumeFiltered[k] > 0.0) {RunningTotalVolume += VolumeFiltered[k];}
			}
		}
	
	//Handle divide by 0.
	//Analysis: ScaledVolume/TotalVolume for the period.
	if(RunningTotalVolume > 0.0) {IIO[i] = RunningTotalII / RunningTotalVolume;}
	else {IIO[i] = 0.0;};
	
	//Do the AIIO calculations.
	
	if( In_IIOSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(IIO, IIOSmoothed, In_IIOSmoothingMAType.GetMovAvgType(), In_IIOSmoothingPeriod.GetInt() );
		ScalingFactor = IIOSmoothed[i] * In_AIIOScaleFactorChange.GetFloat(); //range roughly -1.0 to 1.0
		//Note that a MA may overshoot the range a little. For this it doesn't matter.
		}
	else {
		ScalingFactor = IIO[i] * In_AIIOScaleFactorChange.GetFloat(); //range roughly -1.0 to 1.0
		}
	
	if(ScalingFactor < 0.0) {ScalingFactor *= -1.0;} //range must be positive for the next calculation
	
	//EMA type calculation.
	Graph_AIIO[i] = ((sc.Close[i] - Graph_AIIO[i-1]) * ScalingFactor) + Graph_AIIO[i-1];
}

/* =============================================================================
================================================================================
AMA: Adaptive IIO Moving Average By Tick With Filters
================================================================================
============================================================================= */
SCSFExport scsf_AdaptiveIIOByTickWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_AIIO = sc.Subgraph[0];
	SCInputRef In_IIOPeriod = sc.Input[0];
	SCInputRef In_InputData = sc.Input[1];
	SCInputRef In_VolumeFilterType = sc.Input[2];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[3];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[4];
	SCInputRef In_IIOSetSmoothing = sc.Input[5];
	SCInputRef In_IIOSmoothingPeriod = sc.Input[6];
	SCInputRef In_IIOSmoothingMAType = sc.Input[7];
	SCInputRef In_OutputMultiplier = sc.Input[8];
	SCInputRef In_AIIOScaleFactorChange = sc.Input[9];
	SCSubgraphRef II = sc.Subgraph[1];
	SCSubgraphRef IIO = sc.Subgraph[2];
	SCSubgraphRef IIOSmoothed = sc.Subgraph[3];
	SCSubgraphRef VolumeMA = sc.Subgraph[4];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[5];
	//SCFloatArrayRef FloatArray = Graph_AIIO.Arrays[0];

	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	int i, j, k, Period, IndexTemp;
	float RunningTotalII, RunningTotalVolume, ScalingFactor;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "AMA: Adaptive IIO Moving Average By Tick With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 6; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive IIO Moving Average By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>A price and volume based adaptive moving average from the Intraday Intensity Oscillator By Tick. Since IIO is semi-predictive, it is recommended to also run regular IIO By Tick in a sub chart for comparison.\
<p>This version includes extras to help clean up the graph and make it easier to integrate with automation. The \"Set IIO Smoothing?\" option enables cleaning up some of the IIO noise after the calculation. It is recommended to smooth IIO out with an EMA 3-7.\
<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.\
<p>The \"Scale Factor Change\" option allows the output line to be sped up or slowed down by modifying the EMA Scale Factor variable in the final adaptive calculation. It is recommended to change the main period variable first and then modify this one for fine tuning. A value of 1.0 (100%) will leave the rate unchanged. A value of 2.0 (200%) will double the rate. A value of 0.5 (50%) will cut the rate in half.\
<p>Observations. AIIO will often slow down and go flat when a movement is almost over. When there's a strong reversal, AIIO will go flat and then bend to follow the price. AIIO will often ignore most of a large price spike that's fake. AIIO will often go flat through noise that other adaptive moving averages will track.\
<p>Because of its use of real up/down tick data, this version tends to move much slower than its non-tick version. It may walk straight through lower volume fake price moves. If a faster adaptive moving average is also desired, run a second instance with a higher Scale Factor or Output Multiplier.\
<p>First known public AIIO version by Brett Johnson, 2015.";
		
		//Output Graph
		Graph_AIIO.Name = "AIIO"; //drawn graphs must have a name.
		Graph_AIIO.PrimaryColor = RGB(0, 255, 0);
		Graph_AIIO.DrawStyle = DRAWSTYLE_LINE;
		Graph_AIIO.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_AIIO.LineWidth = 2;
		Graph_AIIO.DrawZeros = 0;
		
		//User Inputs
		
		In_IIOPeriod.Name = "IIO Period";
		In_IIOPeriod.SetInt(20);
		In_IIOPeriod.SetIntLimits(3, 300);
		In_IIOPeriod.SetDescription("Number of bars for the period. Useful values are 20 and higher.");
		
		In_InputData.Name = "Input Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");	
		
		In_IIOSetSmoothing.Name = "Set IIO Smoothing?";
		In_IIOSetSmoothing.SetYesNo(1);
		In_IIOSetSmoothing.SetDescription("Enables extended IIO smoothing options.");
		
		In_IIOSmoothingPeriod.Name = "IIO Smoothing Period";
		In_IIOSmoothingPeriod.SetInt(7);
		In_IIOSmoothingPeriod.SetIntLimits(2, 50);
		In_IIOSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_IIOSmoothingMAType.Name = "IIO Smoothing Moving Average Type";
		In_IIOSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_IIOSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_OutputMultiplier.Name = "IIO Output Multiplier";
		In_OutputMultiplier.SetFloat(5.0);
		In_OutputMultiplier.SetFloatLimits(1.0, 50.0);
		In_OutputMultiplier.SetDescription("This By Tick version produces much smaller output. Multiply it to make it larger and more equal to the original version.");
		
		In_AIIOScaleFactorChange.Name = "AIIO Scale Factor Change";
		In_AIIOScaleFactorChange.SetFloat(1.0);
		In_AIIOScaleFactorChange.SetFloatLimits(0.1, 2.0);
		In_AIIOScaleFactorChange.SetDescription("Percent of Scale Factor to change Adaptive calculation. Range 0.1 to 2.0.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	i = sc.Index; //easier to read traditional C/C++ index i in multiple arrays on one line.
	Period = In_IIOPeriod.GetInt(); //easier to read.
	
	//if first run
	if (i == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period - 1 + (In_IIOSetSmoothing.GetYesNo() ? In_IIOSmoothingPeriod.GetInt() : 0 );
		}
	
	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}

	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[i] = (float)sc.BaseData[VolumeType][i];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[i] = log( (float)sc.BaseData[VolumeType][i] < 1.0 ? 1.0 : (float)sc.BaseData[VolumeType][i] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[i] = sqrt( (float)sc.BaseData[VolumeType][i] < 1.0 ? 1.0 : (float)sc.BaseData[VolumeType][i] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.BaseData[VolumeType][i] <= VolumeMA[i]) {
			//handle normal volume
			VolumeFiltered[i] = (float)sc.BaseData[VolumeType][i];
			}
		else { //handle clipped volume
			VolumeFiltered[i] = VolumeMA[i];
			}
		}

	/* Old Intraday Intensity Calculations: split the volume based on accumulation or distribution estimations. Keep this here for original comparison.
	//Generate Intraday Intensity values.
	//Handle divide by 0 problems.
	if( (VolumeFiltered[i] < 0.01) || (sc.High[i] == sc.Low[i]) ) {II[i] = 0.0;}
	//else calculate as normal.
	//Analysis: ScalingFactor * Volume. If close is in the middle, ScalingFactor=0.0.
	//If close is at the top, ScalingFactor=1.0. If close is at the bottom, ScalingFactor=-1.0.
	else {II[i] = (((2.0 * sc.Close[i]) - sc.High[i] - sc.Low[i]) / (sc.High[i] - sc.Low[i])) * VolumeFiltered[i];}
	*/
	//New Intraday Intensity Calculations: the difference between up and down volume.
	//For volume filtering: create the fraction and multiply it times VolumeFiltered. Fraction range is still 1.0 to -1.0.
	II[i] = (((float)sc.BaseData[Up][i] - (float)sc.BaseData[Down][i]) / (float)sc.BaseData[VolumeType][i]) * VolumeFiltered[i];
	
	//Not enough data yet for the IIO calculation.
	if( i < Period ) {return;}
	
	//do the inner loop
	for(j=i-Period+1; j<=i; j++) {
		RunningTotalII = 0.0;
		RunningTotalVolume = 0.0;
		IndexTemp = j - Period +1;
		if(IndexTemp < 0) {IndexTemp = 0;}
		for(k=IndexTemp; k<=j; k++) {
			RunningTotalII += II[k];
			//Safety: Under some very rare circumstances, a volume moving average number may be negative.
			//Filter those out so the indicator doesn't get trashed.
			if(VolumeFiltered[k] > 0.0) {RunningTotalVolume += VolumeFiltered[k];}
			}
		}
	
	//Handle divide by 0.
	//Analysis: ScaledVolume/TotalVolume for the period.
	if(RunningTotalVolume > 0.0) {IIO[i] = (RunningTotalII / RunningTotalVolume) * In_OutputMultiplier.GetFloat();}
	else {IIO[i] = 0.0;}
	
	//Do the AIIO calculations.
	
	if( In_IIOSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(IIO, IIOSmoothed, In_IIOSmoothingMAType.GetMovAvgType(), In_IIOSmoothingPeriod.GetInt() );
		ScalingFactor = IIOSmoothed[i] * In_AIIOScaleFactorChange.GetFloat(); //range roughly -1.0 to 1.0
		//Note that a MA may overshoot the range a little. For this it doesn't matter.
		}
	else {
		ScalingFactor = IIO[i] * In_AIIOScaleFactorChange.GetFloat(); //range roughly -1.0 to 1.0
		}
	
	if(ScalingFactor < 0.0) {ScalingFactor *= -1.0;} //range must be positive for the next calculation
	
	//EMA type calculation.
	Graph_AIIO[i] = ((sc.Close[i] - Graph_AIIO[i-1]) * ScalingFactor) + Graph_AIIO[i-1];
}

/* =============================================================================
================================================================================
AMA: Adaptive MFI Moving Average With Filters
================================================================================
============================================================================= */
SCSFExport scsf_AdaptiveMFIWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_AMFI = sc.Subgraph[0];
	SCInputRef In_AMFIPeriod = sc.Input[0];
	SCInputRef In_InputData = sc.Input[1];
	SCInputRef In_PriceSetSmoothing = sc.Input[2];
	SCInputRef In_PriceSmoothingPeriod = sc.Input[3];
	SCInputRef In_PriceSmoothingMAType = sc.Input[4];
	SCInputRef In_VolumeFilterType = sc.Input[5];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[6];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[7];
	SCInputRef In_AMFIScaleFactorChange = sc.Input[8];
	SCInputRef In_MFISetSmoothing = sc.Input[9];
	SCInputRef In_MFISmoothingPeriod = sc.Input[10];
	SCInputRef In_MFISmoothingMAType = sc.Input[11];
	SCSubgraphRef Price = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[3];
	SCSubgraphRef MFI = sc.Subgraph[4];
	SCSubgraphRef MFISmoothed = sc.Subgraph[5];
	//SCFloatArrayRef FloatArray = Graph_AMFI.Arrays[0];

	//remember local variables are not persistent.
	float ScalingFactor;
	int i, j, Period;
	float TypicalPrice, TypicalPricePrevious, MFPositive, MFNegative, MFTotal;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "AMA: Adaptive MFI Moving Average With Filters";

		sc.StudyVersion = 1.2;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 6; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive MFI Moving Average With Filters. Adaptive MFI (AMFI) uses price as an input and then MFI as the scaling factor in an exponential moving average equation. It is very similar to Adaptive RSI (ARSI). Some people prefer the MFI indicator over the RSI indicator since it takes volume into account.\
<p> The proper MFI algorithm uses Typical Price (HLC Avg) as the input. There is an option to change this if desired. The \"Set Price Smoothing?\" option enables cleaning up the price before calculations. If price is really noisy, recommended settings are EMA 3-10. Otherwise leave price smoothing off. The \"Set MFI Smoothing?\" option enables cleaning up some of the MFI noise before AMFI is calculated. It is recommended to smooth MFI out with an EMA 3-7. This allows for less volatility and more consistent movements.\
<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.\
<p>The \"Scale Factor Change\" option allows the output line to be sped up or slowed down by modifying the EMA Scale Factor variable in the final adaptive calculation. It is recommended to change the main period variable first and then modify this one for fine tuning. A value of 1.0 (100%) will leave the rate unchanged. A value of 2.0 (200%) will double the rate. A value of 0.5 (50%) will cut the rate in half.\
<p>To use straight AMFI without any enhancements, turn off all extra options.\
<p>Observations: When there's a strong reversal, AMFI will go flat and then bend to follow the price. It will do this more than ARSI given the same settings. AMFI will often go flat before the end of major price peaks/dips indicating that the move is almost over (something ARSI will not do). On weaker events, AMFI will go flat while price bounces around above or below and then returns to the AMFI line. Check indicators and wave counts to verify final motion.\
<p>To visualize what the scaling factor is doing, a separate MFI graph can be added with the selected smoothing values. When MFI is close to 50, the AMFI line will go flat and move less. Further away from 50 will increase the line movement.\
<p>First known public AMFI version by Brett Johnson, 2015.";
		
		//Output Graph
		Graph_AMFI.Name = "AMFI"; //drawn graphs must have a name.
		Graph_AMFI.PrimaryColor = RGB(0, 255, 0);
		Graph_AMFI.DrawStyle = DRAWSTYLE_LINE;
		Graph_AMFI.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_AMFI.LineWidth = 2;
		Graph_AMFI.DrawZeros = 0;
		
		//User Inputs
		
		In_AMFIPeriod.Name = "AMFI Period";
		In_AMFIPeriod.SetInt(35);
		In_AMFIPeriod.SetIntLimits(3, 300);
		In_AMFIPeriod.SetDescription("Number of bars for the period. Useful values are 25 and higher.");
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_HLC); //default to bar close.
		In_InputData.SetDescription("Usually \"HLC Avg\" for Typical Price.");

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
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");	
		
		In_AMFIScaleFactorChange.Name = "AMFI Scale Factor Change";
		In_AMFIScaleFactorChange.SetFloat(1.0);
		In_AMFIScaleFactorChange.SetFloatLimits(0.1, 2.0);
		In_AMFIScaleFactorChange.SetDescription("Percent of Scale Factor to change Adaptive calculation. Range 0.1 to 2.0.");
		
		In_MFISetSmoothing.Name = "Set MFI Smoothing?";
		In_MFISetSmoothing.SetYesNo(1);
		In_MFISetSmoothing.SetDescription("Enables extended MFI smoothing options.");
		
		In_MFISmoothingPeriod.Name = "MFI Smoothing Period";
		In_MFISmoothingPeriod.SetInt(5);
		In_MFISmoothingPeriod.SetIntLimits(2, 50);
		In_MFISmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_MFISmoothingMAType.Name = "MFI Smoothing Moving Average Type";
		In_MFISmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MFISmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
				
		return;
		}
	
	// Section 2 - Do data processing here
	
	i = sc.Index; //easier to read traditional C/C++ index i in multiple arrays on one line.
	Period = In_AMFIPeriod.GetInt(); //easier to read.
	
	//if first run
	if (i == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period - 1 + (In_PriceSetSmoothing.GetYesNo() ? In_PriceSmoothingPeriod.GetInt() : 0 ) + (In_MFISetSmoothing.GetYesNo() ? In_MFISmoothingPeriod.GetInt() : 0 );
		}

	//Handle price smoothing.
	if( In_PriceSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Price, In_PriceSmoothingMAType.GetMovAvgType(), In_PriceSmoothingPeriod.GetInt() );
		}
	else {
		Price[i] = sc.BaseDataIn[In_InputData.GetInputDataIndex()][i];
		}

	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[i] = (float)sc.Volume[i];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[i] = log( (float)sc.Volume[i] < 1.0 ? 1.0 : (float)sc.Volume[i] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[i] = sqrt( (float)sc.Volume[i] < 1.0 ? 1.0 : (float)sc.Volume[i] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.Volume[i] <= VolumeMA[i]) {VolumeFiltered[i] = (float)sc.Volume[i];} //handle normal volume
		else {VolumeFiltered[i] = (float)VolumeMA[i];} //handle clipped volume
		}

	//Not enough data yet. Pre-load existing data into array for later calculations.
	if( i < Period ) {
		Graph_AMFI[i] = Price[i];
		return;
		}
	
	//Do the MFI calculations.
	MFPositive = 0.0;
	MFNegative = 0.0;
	
	//set previous typical price.
	j = i - Period;
	if(j >= 0) {TypicalPricePrevious = Price[j];}
	else {TypicalPricePrevious = 0.0;}
	
	//do the inner loop
	j = i - Period +1;
	if(j < 0) {j = 0;}
	for(; j<=i; j++) {
		TypicalPrice = Price[j];
		if(TypicalPrice == TypicalPricePrevious) {continue;} //nothing to do
		//calculate money flows
		if(TypicalPrice > TypicalPricePrevious) {MFPositive += TypicalPrice * VolumeFiltered[j];}
		else {MFNegative += TypicalPrice * VolumeFiltered[j];}
		TypicalPricePrevious = TypicalPrice;
		}
	
	MFTotal = MFPositive + MFNegative;
	if(MFTotal > 0.0) {MFI[i] = 100.0 * (MFPositive / MFTotal);}
	else { //left with divide by 0 problem or bad negative number
		if(i>0) {MFI[i] = MFI[i-1];} //copy in previous value
		else {MFI[i] = 0.0;} //force it to 0
		}
	
	//Do the AMFI calculations.
	
	if( In_MFISetSmoothing.GetYesNo() ) {
		sc.MovingAverage(MFI, MFISmoothed, In_MFISmoothingMAType.GetMovAvgType(), In_MFISmoothingPeriod.GetInt() );
		ScalingFactor = ((MFISmoothed[i] / 100.0) - 0.5) * 2.0 * In_AMFIScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		//Note that a MA may overshoot the range a little. For this it doesn't matter.
		}
	else {
		ScalingFactor = ((MFI[i] / 100.0) - 0.5) * 2.0 * In_AMFIScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		}
	
	if(ScalingFactor < 0.0) {ScalingFactor *= -1.0;} //range must be positive for the next calculation
	
	//EMA type calculation.
	Graph_AMFI[i] = ((Price[i] - Graph_AMFI[i-1]) * ScalingFactor) + Graph_AMFI[i-1];
}

/* =============================================================================
================================================================================
AMA: Adaptive OBV RSI Moving Average By Tick With Filters
================================================================================
============================================================================= */
SCSFExport scsf_AdaptiveOBVRSIByTick(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_AOBVRSI = sc.Subgraph[0];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_VolumeFilterType = sc.Input[1];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[2];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[3];
	SCInputRef In_OBVSetSmoothing = sc.Input[4];
	SCInputRef In_OBVSmoothingPeriod = sc.Input[5];
	SCInputRef In_OBVSmoothingMAType = sc.Input[6];
	SCInputRef In_RSIPeriod = sc.Input[7];
	SCInputRef In_RSICalcMAType = sc.Input[8];
	SCInputRef In_RSISetSmoothing = sc.Input[9];
	SCInputRef In_RSISmoothingPeriod = sc.Input[10];
	SCInputRef In_RSISmoothingMAType = sc.Input[11];
	SCInputRef In_AOBVRSIScaleFactorChange = sc.Input[12];
	SCInputRef In_InputPriceData = sc.Input[13];
	SCSubgraphRef OBV = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	SCSubgraphRef OBVSmoothed = sc.Subgraph[3];
	SCSubgraphRef OBVRSI = sc.Subgraph[4];
	SCSubgraphRef OBVRSISmoothed = sc.Subgraph[5];
	//SCFloatArrayRef FloatArray = Graph_AOBVRSI.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	float Balance, VolumeScale, ScalingFactor;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "AMA: Adaptive OBV RSI Moving Average By Tick With Filters";
		
		sc.StudyVersion = 1.2;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 6; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive OBV RSI Moving Average By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>OBV acts similar for volume for what price does on the main chart. OBV is first calculated and then an RSI is taken of it. The RSI values are then put into an EMA formula to make an Adaptive Moving Average. When RSI goes weak (indicating volume movement has gone weak), the AMA line will slow down. For a more complete picture, it is recommended to use this indicator with Up/Down Volume Ratio or Difference, OBV By Tick using the MA Ribbon option, OBV By Tick MACD, and OBV By Tick RSI to help see the volume moves to identify the trend.\
<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.\
<p>This RSI version has recommended extra smoothing options to help take the noise out of the RSI line.\
<p>Observations. Volume tends to have longer runs than price. Setting the RSI period too small will just smash the indicator during these long runs. The AOBVRSI line tends to be slower than Adaptive IIO and Adaptive Volume Ratio (but a bit noisier at the RSI extremes) because RSI as a base tends to be a little more sluggish. That makes this indicator preferred when looking for slower AMA lines. Like the other tick based volume AMA's, this one tends to ignore weaker price movements.";
		
		//Output Graph
		Graph_AOBVRSI.Name = "AOBVRSI"; //drawn graphs must have a name.
		Graph_AOBVRSI.PrimaryColor = RGB(255, 0, 0);
		Graph_AOBVRSI.DrawStyle = DRAWSTYLE_LINE;
		Graph_AOBVRSI.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_AOBVRSI.LineWidth = 2;
		Graph_AOBVRSI.DrawZeros = 0;
		
		//User Inputs
		
		In_InputData.Name = "Input Volume Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");

		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_OBVSetSmoothing.Name = "Set OBV Smoothing?";
		In_OBVSetSmoothing.SetYesNo(1);
		In_OBVSetSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_OBVSmoothingPeriod.Name = "OBV Smoothing Period";
		In_OBVSmoothingPeriod.SetInt(7);
		In_OBVSmoothingPeriod.SetIntLimits(2, 50);
		In_OBVSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_OBVSmoothingMAType.Name = "OBV Smoothing Moving Average Type";
		In_OBVSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_OBVSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_RSIPeriod.Name = "RSI Period";
		In_RSIPeriod.SetInt(35);
		In_RSIPeriod.SetIntLimits(3, 100);
		In_RSIPeriod.SetDescription("Number of bars for the period. Useful values are 10 and higher.");
		
		In_RSICalcMAType.Name = "RSI Calculation Moving Average Type";
		In_RSICalcMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_RSICalcMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_RSISetSmoothing.Name = "Set RSI Smoothing?";
		In_RSISetSmoothing.SetYesNo(1);
		In_RSISetSmoothing.SetDescription("Enables extended RSI smoothing options.");
		
		In_RSISmoothingPeriod.Name = "RSI Smoothing Period";
		In_RSISmoothingPeriod.SetInt(7);
		In_RSISmoothingPeriod.SetIntLimits(2, 50);
		In_RSISmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_RSISmoothingMAType.Name = "RSI Smoothing Moving Average Type";
		In_RSISmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_RSISmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_AOBVRSIScaleFactorChange.Name = "AOBVRSI Scale Factor Change";
		In_AOBVRSIScaleFactorChange.SetFloat(0.6);
		In_AOBVRSIScaleFactorChange.SetFloatLimits(0.1, 2.0);
		In_AOBVRSIScaleFactorChange.SetDescription("Percent of Scale Factor to change Adaptive calculation. Range 0.1 to 2.0.");
		
		In_InputPriceData.Name = "Input Price Data";
		In_InputPriceData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputPriceData.SetDescription("Usually \"Last\" for Close.");
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = (In_OBVSetSmoothing.GetYesNo() ? In_OBVSmoothingPeriod.GetInt() : 0) + In_RSIPeriod.GetInt() + (In_RSISetSmoothing.GetYesNo() ? In_RSISmoothingPeriod.GetInt() : 0);
		//local variable
		Balance = 0.0;
		}
	
	//Reload Balance with previous value. Much easier to read this way.
	if(sc.Index >= 1) {Balance = OBV[sc.Index -1];}

	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}
	
	//Calculate On Balance Volume filter type.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		Balance += (float)sc.BaseData[Up][sc.Index];
		Balance -= (float)sc.BaseData[Down][sc.Index];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		Balance += log( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= log( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		Balance += sqrt( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= sqrt( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.BaseData[VolumeType][sc.Index] <= VolumeMA[sc.Index]) {
			Balance += (float)sc.BaseData[Up][sc.Index];
			Balance -= (float)sc.BaseData[Down][sc.Index];
			}
		//handle clipped volume
		else {
			VolumeScale = (float)VolumeMA[sc.Index] / (float)sc.BaseData[VolumeType][sc.Index];
			Balance += VolumeScale * (float)sc.BaseData[Up][sc.Index];
			Balance -= VolumeScale * (float)sc.BaseData[Down][sc.Index];
			}
		}
	OBV[sc.Index] = Balance;
	
	//Handle OBV smoothing.
	if( In_OBVSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBV, OBVSmoothed, In_OBVSmoothingMAType.GetMovAvgType(), In_OBVSmoothingPeriod.GetInt() );
		}
	else {
		OBVSmoothed[sc.Index] = OBV[sc.Index];
		}

	//Generate RSI.
	sc.RSI(OBVSmoothed, OBVRSI, In_RSICalcMAType.GetMovAvgType(), In_RSIPeriod.GetInt() );
	
	//Handle RSI smoothing.
	if( In_RSISetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBVRSI, OBVRSISmoothed, In_RSISmoothingMAType.GetMovAvgType(), In_RSISmoothingPeriod.GetInt() );
		ScalingFactor = ((OBVRSISmoothed[sc.Index] / 100.0) - 0.5) * 2.0 * In_AOBVRSIScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		//Note that a MA may overshoot the range a little. For this it doesn't matter.
		}
	else {
		ScalingFactor = ((OBVRSI[sc.Index] / 100.0) - 0.5) * 2.0 * In_AOBVRSIScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		}
	
	ScalingFactor = ScalingFactor * ScalingFactor; //Square it to slow down the overly fast parts. Also keeps it positive for the next calculation.
	
	//EMA type calculation.
	Graph_AOBVRSI[sc.Index] = ((sc.BaseDataIn[In_InputPriceData.GetInputDataIndex()][sc.Index] - Graph_AOBVRSI[sc.Index-1]) * ScalingFactor) + Graph_AOBVRSI[sc.Index-1];
}

/* =============================================================================
================================================================================
AMA: Adaptive RSI Moving Average With Filters
================================================================================
============================================================================= */
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
		sc.GraphName = "AMA: Adaptive RSI Moving Average With Filters";
		
		sc.StudyVersion = 1.2;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 6; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive RSI Moving Average With Filters. Traditional Adaptive RSI (ARSI) uses straight price and then RSI as the scaling factor without smoothing. The \"Set Price Smoothing?\" option enables cleaning up the price before calculations. If price is really noisy, recommended settings are EMA 3-10. Otherwise leave price smoothing off. The \"Set RSI Smoothing?\" option enables cleaning up some of the RSI noise before ARSI is calculated. It is recommended to smooth RSI out with an EMA 3-7. This allows for less volatility and more consistent movements.\
<p>The \"Scale Factor Change\" option allows the output line to be sped up or slowed down by modifying the EMA Scale Factor variable in the final adaptive calculation. It is recommended to change the main period variable first and then modify this one for fine tuning. A value of 1.0 (100%) will leave the rate unchanged. A value of 2.0 (200%) will double the rate. A value of 0.5 (50%) will cut the rate in half.\
<p>To use traditional ARSI without any enhancements, turn off all extra options.\
<p>Observations: When there's a strong reversal, ARSI will go flat and then bend to follow the price. On weaker events, ARSI will go flat while price bounces around above or below and then returns to the ARSI line. Check indicators and wave counts to verify final motion.\
<p>To visualize what the scaling factor is doing, a separate RSI graph can be added with the selected smoothing values. When RSI is close to 50, the ARSI line will go flat and move less. Further away from 50 will increase the line movement.";
		
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
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run
	if (sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_ARSIPeriod.GetInt() - 1 + (In_PriceSetSmoothing.GetYesNo() ? In_PriceSmoothingPeriod.GetInt() : 0) + (In_RSISetSmoothing.GetYesNo() ? In_RSISmoothingPeriod.GetInt() : 0);
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

/* =============================================================================
================================================================================
AMA: Adaptive Stochastic Moving Average With Filters
================================================================================
============================================================================= */
SCSFExport scsf_AdaptiveStochasticMAWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_ASTO = sc.Subgraph[0];
	SCInputRef In_ASTOPeriod = sc.Input[0];
	SCInputRef In_STOCalcMAType = sc.Input[1];
	SCInputRef In_InputData = sc.Input[2];
	SCInputRef In_ASTOScaleFactorChange = sc.Input[3];
	SCInputRef In_STOSetSmoothing = sc.Input[4];
	SCInputRef In_STOSmoothingPeriod = sc.Input[5];
	SCInputRef In_STOSmoothingMAType = sc.Input[6];
	SCSubgraphRef STO = sc.Subgraph[1];
	SCSubgraphRef STOSmoothed = sc.Subgraph[2];
	//SCFloatArrayRef FloatArray = Graph_ASTO.Arrays[0];

	//remember local variables are not persistent.
	float ScalingFactor;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "AMA: Adaptive Stochastic Moving Average With Filters";
		
		sc.StudyVersion = 1.2;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 6; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive Stochastic Moving Average With Filters. This was an academic experiment to compare Adaptive RSI with Adaptive Stochastic. It really doesn't show much since Stochastic tends to follow price movements closely. ASTO acts more like an EMA5-10 most of the time.\
<p>What did come of this experiment is the \"Scale Factor Change\" option. Since Stochastic spends most of its time away from the 50 line, dropping the Scale Factor to 20% (default) of normal finally made this average behave in an adaptive way.\
<p>The \"Set STO Smoothing?\" option enables cleaning up some of the STO noise after the calculation. It is recommended to smooth STO out with an EMA 3-7.\
<p>To visualize what the scaling factor is doing, a separate Stochastic graph can be added with the selected smoothing values. When Stochastic is close to 50, the ASTO line will go flat and move less. Further away from 50 will increase the line movement.\
<p>First known public ASTO version by Brett Johnson, 2015.";
		
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
		
		In_STOCalcMAType.Name = "STO Calculation Moving Average Type";
		In_STOCalcMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_STOCalcMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData.SetDescription("Usually \"Last\" for bar close when viewing stock prices. One of the averages can be used for forex and other less time synchronized data.");
		
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
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run
	if (sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_ASTOPeriod.GetInt() - 1 + (In_STOSetSmoothing.GetYesNo() ? In_STOSmoothingPeriod.GetInt() : 0);
		}

	//Not enough data yet. Pre-load existing data into array for later calculations.
	if( sc.Index < In_ASTOPeriod.GetInt() ) {
		Graph_ASTO[sc.Index] = sc.BaseDataIn[In_InputData.GetInputDataIndex()][sc.Index];
		return;
		}
	
	//Do the ASTO calculations.

	sc.Stochastic(sc.BaseDataIn, STO, In_ASTOPeriod.GetInt(), 0, 0, In_STOCalcMAType.GetMovAvgType() );
	
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
	Graph_ASTO[sc.Index] = ((sc.BaseDataIn[In_InputData.GetInputDataIndex()][sc.Index] - Graph_ASTO[sc.Index-1]) * ScalingFactor) + Graph_ASTO[sc.Index-1];
}

/* =============================================================================
================================================================================
AMA: Adaptive Volume Ratio Moving Average By Tick With Filters
================================================================================
============================================================================= */
SCSFExport scsf_AdaptiveVolumeRatioByTickWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_AVRatio = sc.Subgraph[0];
	SCInputRef In_NumberOfHighestValues = sc.Input[0];
	SCInputRef In_NumberOfBarsForHighs = sc.Input[1];
	SCInputRef In_LimiterStrength = sc.Input[2];
	SCInputRef In_InputVolumeData = sc.Input[3];
	SCInputRef In_VolumeFilterType = sc.Input[4];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[5];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[6];
	SCInputRef In_VRNormalSmoothingPeriod = sc.Input[7];
	SCInputRef In_VRNormalSmoothingMAType = sc.Input[8];
	SCInputRef In_VRSetExtraSmoothing = sc.Input[9];
	SCInputRef In_VRExtraSmoothingPeriod = sc.Input[10];
	SCInputRef In_VRExtraSmoothingMAType = sc.Input[11];
	SCInputRef In_InputPriceData = sc.Input[12];
	SCInputRef In_ScaleFactorChange = sc.Input[13];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	SCSubgraphRef ArrayOfHighs = sc.Subgraph[3];
	SCSubgraphRef VR = sc.Subgraph[4];
	SCSubgraphRef VRSmoothed = sc.Subgraph[5];
	SCSubgraphRef VRFinal = sc.Subgraph[6];
	//SCFloatArrayRef FloatArray = Graph_AVRatio.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	int i, NumberOfHighs, NumberOfBars, VIdx, HIdx, IndexLow;
	float VolumeScale, AverageHigh, RatioScale, ScalingFactor;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "AMA: Adaptive Volume Ratio Moving Average By Tick With Filters";
		
		sc.StudyVersion = 1.2;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 6; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive Volume Ratio Moving Average By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>This indicator turns the Up/Down Volume Ratio into an Adaptive Moving Average. It is generally faster than Adaptive IIO and Adaptive OBV RSI. It is pretty much guaranteed that you will have to tune the \"AVRatio Scale Factor Change\" number because of movement variances between different securities. The Scale Factor number will speed up or slow down the AMA line. To tune for fast mode, start the AMA line slightly slower and speed it up until it just follows the price line. This will show short term price movements that are weak and over shoots. To tune for slow mode, start the AMA line slightly fast and slow it down until most of the price movements are above or below the AMA line. The Up/Down Volume Ratio Limiter will slow down the AMA line on low volume and help identify weak and false moves. For a more complete picture, it is recommended to use this indicator with Up/Down Volume Ratio or Difference, OBV By Tick using the MA Ribbon option, OBV By Tick MACD, and OBV By Tick RSI to help see the volume moves to identify the trend.\
<p>The AMA engine uses the traditional Up/Down Volume Ratio but adds a limiter to reduce the value on low volume. This helps reduce the large ranges on low volume that can blow out the scale. With the limiter in place, this is not a ratio with a 100% scale. It is very similar to Up/Down Volume Difference but much slower to calculate because of searching for the Highes Value average. The Highest Value average takes the selected number of highest values for a time period and averages them to a high value line. Anything above the line is ignored. Anything below the line gets the output ratio scaled proportionally by the limiter. Despite the higher number of calculations per bar, this helps identify which of the big peaks/dips are real or not. This indicator solves the problem of the ratio line jumping on each new bar with little data. This also makes it easier to use with automated trading systems.\
<p>This indicator version has a second smoothing option. The ratio data is very choppy and extremely noisy. The second moving average can be of any type and will help clean up the line. Smoothing with a larger number isn't as effective as double smoothing with a number half that size.\
<p>This indicator version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average.";

		//Output Graph
		Graph_AVRatio.Name = "AVRatio"; //drawn graphs must have a name.
		Graph_AVRatio.PrimaryColor = RGB(255, 0, 255);
		Graph_AVRatio.DrawStyle = DRAWSTYLE_LINE;
		Graph_AVRatio.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_AVRatio.LineWidth = 2;
		Graph_AVRatio.DrawZeros = 0;
		
		//User Inputs
		
		In_NumberOfHighestValues.Name = "Number Of Highest Values To Keep";
		In_NumberOfHighestValues.SetInt(20);
		In_NumberOfHighestValues.SetIntLimits(10, 500);
		In_NumberOfHighestValues.SetDescription("The number of highest values to look for in a range of bars. Usually 10-50. Note: the higher the number the slower the calculation will be.");

		In_NumberOfBarsForHighs.Name = "Number Of Bars To Search For Highest Values";
		In_NumberOfBarsForHighs.SetInt(240);
		In_NumberOfBarsForHighs.SetIntLimits(10, 3000);
		In_NumberOfBarsForHighs.SetDescription("The range of bars to look for the highest values. Usually 240 - 1440 (a few hours to about one full trading day). Note: the higher the number the slower the calculation will be.");
		
		In_LimiterStrength.Name = "Limiter Strength";
		In_LimiterStrength.SetFloat(1.0);
		In_LimiterStrength.SetFloatLimits(0.1, 1.0);
		In_LimiterStrength.SetDescription("The strength the limiter will apply to low volume ranges ranges to make matching low ratio ranges. Range 0.1 to 1.0 for 10-100%. Usually 1.0 (100%)");
		
		In_InputVolumeData.Name = "Input Volume Data";
		In_InputVolumeData.SetCustomInputIndex(0);
		In_InputVolumeData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputVolumeData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");

		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");
		
		In_VRNormalSmoothingPeriod.Name = "Normal Output Smoothing Period";
		In_VRNormalSmoothingPeriod.SetInt(5);
		In_VRNormalSmoothingPeriod.SetIntLimits(2, 50);
		In_VRNormalSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-20.");
		
		In_VRNormalSmoothingMAType.Name = "Normal Output Smoothing Moving Average Type";
		In_VRNormalSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_VRNormalSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_VRSetExtraSmoothing.Name = "Set Extra Output Smoothing?";
		In_VRSetExtraSmoothing.SetYesNo(1);
		In_VRSetExtraSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_VRExtraSmoothingPeriod.Name = "Extra Output Smoothing Period";
		In_VRExtraSmoothingPeriod.SetInt(5);
		In_VRExtraSmoothingPeriod.SetIntLimits(2, 50);
		In_VRExtraSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_VRExtraSmoothingMAType.Name = "Extra Output Smoothing Moving Average Type";
		In_VRExtraSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_VRExtraSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_InputPriceData.Name = "Input Price Data";
		In_InputPriceData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputPriceData.SetDescription("Usually \"Last\" for Close.");
		
		In_ScaleFactorChange.Name = "AVRatio Scale Factor Change";
		In_ScaleFactorChange.SetFloat(5.0);
		In_ScaleFactorChange.SetFloatLimits(0.001, 1000.0);
		In_ScaleFactorChange.SetDescription("Multiplier to change the Adaptive calculation. Range 0.001 to 1000.0. Given the variances between different securities, it is pretty much guaranteed that you will have to change this number to tune the AMA line.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	i = sc.Index; //easier to read long lines

	//if first run. Set persistent variables here.
	if(i == 0) {
		//Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_VRNormalSmoothingPeriod.GetInt() + (In_VRSetExtraSmoothing.GetYesNo() ? In_VRExtraSmoothingPeriod.GetInt() : 0.0 );
		//Make sure the count of highs is less than or equal to the range.
		if(In_NumberOfHighestValues.GetInt() > In_NumberOfBarsForHighs.GetInt() ) {
			//swap the values around
			HIdx = In_NumberOfBarsForHighs.GetInt();
			In_NumberOfBarsForHighs.SetInt( In_NumberOfHighestValues.GetInt() );
			In_NumberOfHighestValues.SetInt(HIdx);
			}
		}

	//Select Input Data Type
	if(In_InputVolumeData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputVolumeData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}
	
	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[i] = (float)sc.BaseData[VolumeType][i];
		VolumeScale = 1.0;
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[i] = log( (float)sc.BaseData[VolumeType][i] < 1.0 ? 1.0 : (float)sc.BaseData[VolumeType][i] );
		VolumeScale = VolumeFiltered[i] / (float)sc.BaseData[VolumeType][i];
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[i] = sqrt( (float)sc.BaseData[VolumeType][i] < 1.0 ? 1.0 : (float)sc.BaseData[VolumeType][i] );
		VolumeScale = VolumeFiltered[i] / (float)sc.BaseData[VolumeType][i];
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.BaseData[VolumeType][i] <= VolumeMA[i]) {
			//handle normal volume
			VolumeFiltered[i] = (float)sc.BaseData[VolumeType][i];
			VolumeScale = 1.0;
			}
		else { //handle clipped volume
			VolumeFiltered[i] = VolumeMA[i];
			VolumeScale = VolumeFiltered[i] / (float)sc.BaseData[VolumeType][i];
			}
		}
	
	//We need to shrink the smaller volume number's output to avoid them blowing the output range.
	//A moving average doesn't work as well here because it takes into account ALL numbers.
	//A better method is to take the selected highest numbers in the range and average them (ignoring the lowest numbers).
	//Enter...
	
	//The Sloppy High Values Bucket Algorithm: Faster than continuously sorting an array.
	//Start: Fill highs array and search for the low.
	//If (CURRENT > Low), then Low = CURRENT. Search for new low in highs array.
	//If (CURRENT < Low), then skip to next value.
	//Load and check ranges.
	NumberOfHighs = In_NumberOfHighestValues.GetInt();
	if(NumberOfHighs > i) {NumberOfHighs = i +1;}
	NumberOfBars = In_NumberOfBarsForHighs.GetInt();
	if(NumberOfBars > i) {NumberOfBars = i +1;}
	//Initial fill of array.
	VIdx = i - NumberOfBars +1;
	IndexLow = 0;
	for(HIdx=0; HIdx < NumberOfHighs; HIdx++, VIdx++) {
		ArrayOfHighs[HIdx] = VolumeFiltered[VIdx];
		if(ArrayOfHighs[IndexLow] > ArrayOfHighs[HIdx]) {IndexLow = HIdx;}
		}
	//Search the rest of the main array.
	for(; VIdx <= i; VIdx++) {
		if(VolumeFiltered[VIdx] > ArrayOfHighs[IndexLow]) {
			//Overwrite the low value
			ArrayOfHighs[IndexLow] = VolumeFiltered[VIdx];
			//Search for the new low index
			for(IndexLow=0, HIdx=1; HIdx < NumberOfHighs; HIdx++) {if(ArrayOfHighs[IndexLow] > ArrayOfHighs[HIdx]) {IndexLow = HIdx;}}
			}
		}
	//Calculate the average high.
	AverageHigh = 0.0;
	for(HIdx=0; HIdx < NumberOfHighs; HIdx++) {AverageHigh += ArrayOfHighs[HIdx];}
	AverageHigh /= NumberOfHighs;
	
	//Calculate RatioScale to scale down volume ratio output number.
	//Higher numbers get passed.
	//Normal numbers won't be affected much.
	//Very low numbers get squashed to help prevent blowing the output range.
	//The limiter strength is a percentage of the RatioScale to use.
	if((VolumeFiltered[i] < AverageHigh) && (AverageHigh > 0.0) ) {
		RatioScale =  1.0 - ((1.0 - (VolumeFiltered[i] / AverageHigh)) * In_LimiterStrength.GetFloat() );
		}
	else {RatioScale = 1.0;}
	
	//Calculate volume ratio.
	if(VolumeFiltered[i] > 0) {
		VR[i] = (((float)(sc.BaseData[Up][i] - sc.BaseData[Down][i]) * VolumeScale) / VolumeFiltered[i]) * RatioScale;
		}
	else {VR[i] = 0.0;}
	
	//Handle smoothing.
	sc.MovingAverage(VR, VRSmoothed, In_VRNormalSmoothingMAType.GetMovAvgType(), In_VRNormalSmoothingPeriod.GetInt() );
	
	//Handle extra smoothing.
	if( In_VRSetExtraSmoothing.GetYesNo() ) {
		sc.MovingAverage(VRSmoothed, VRFinal, In_VRExtraSmoothingMAType.GetMovAvgType(), In_VRExtraSmoothingPeriod.GetInt() );
		}
	else {
		VRFinal[i] = VRSmoothed[i];
		}
	
	//Do the AMA calculation.
	
	ScalingFactor = VRFinal[i] * In_ScaleFactorChange.GetFloat(); //range roughly -1.0 to 1.0
	if(ScalingFactor < 0.0) {ScalingFactor *= -1.0;} //range must be positive for the next calculation
	
	//EMA type calculation.
	Graph_AVRatio[i] = ((sc.BaseDataIn[In_InputPriceData.GetInputDataIndex()][i] - Graph_AVRatio[i-1]) * ScalingFactor) + Graph_AVRatio[i-1];
}

/* =============================================================================
================================================================================
Tool: Bollinger Band Ribbon
================================================================================
============================================================================= */
SCSFExport scsf_BollingerBandRibbon(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_BB5Low = sc.Subgraph[0];
	SCSubgraphRef Graph_BB5Mid = sc.Subgraph[1];
	SCSubgraphRef Graph_BB5Top = sc.Subgraph[2];
	SCSubgraphRef Graph_BB4Low = sc.Subgraph[3];
	SCSubgraphRef Graph_BB4Mid = sc.Subgraph[4];
	SCSubgraphRef Graph_BB4Top = sc.Subgraph[5];
	SCSubgraphRef Graph_BB3Low = sc.Subgraph[6];
	SCSubgraphRef Graph_BB3Mid = sc.Subgraph[7];
	SCSubgraphRef Graph_BB3Top = sc.Subgraph[8];
	SCSubgraphRef Graph_BB2Low = sc.Subgraph[9];
	SCSubgraphRef Graph_BB2Mid = sc.Subgraph[10];
	SCSubgraphRef Graph_BB2Top = sc.Subgraph[11];
	SCSubgraphRef Graph_BB1Low = sc.Subgraph[12];
	SCSubgraphRef Graph_BB1Mid = sc.Subgraph[13];
	SCSubgraphRef Graph_BB1Top = sc.Subgraph[14];
	SCSubgraphRef Graph_PrimaryLine = sc.Subgraph[15];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_SetPrimaryLine = sc.Input[1];
	SCInputRef In_PrimaryLinePeriod = sc.Input[2];
	SCInputRef In_PrimaryLineMAType = sc.Input[3];
	SCInputRef In_StandardDeviation = sc.Input[4];
	SCInputRef In_BBRibbonMAType = sc.Input[5];
	SCInputRef In_BBRibbon1Period = sc.Input[6];
	SCInputRef In_BBRibbon2Period = sc.Input[7];
	SCInputRef In_BBRibbon3Period = sc.Input[8];
	SCInputRef In_BBRibbon4Period = sc.Input[9];
	SCInputRef In_BBRibbon5Period = sc.Input[10];

	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Tool: Bollinger Band Ribbon";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 0; //any graph
		sc.ValueFormat = VALUEFORMAT_INHERITED; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Bollinger Band Ribbon: Taking The Moving Average Ribbon To A New Extreme. Bollinger Bands take a moving average and add high and low lines at 2.0 standard deviations away (configurable) to help show movement ranges. A Bollinger Band Ribbon is a moving average ribbon with these high and low lines for each individual line. A moving average ribbon is a set of moving average lines of differing values following a single source. That source is usually price but non-oscillating indicators can also have a ribbon attached to them. It is recommended to give the ribbon a lot of screen height to see the movement... even more than a straight moving average ribbon. Institutional traders do use Bollinger Bands as seen by price lines bending, pausing, and reversing at the standard levels and with their high and low lines. The Primary Line is usually a small EMA number to closely track the source. If it's not needed, it can be set to another moving average number and type or set to disabled. The ribbon lines are usually Simple Moving Averages since that is what the big institutions use. Both moving average types can be changed.\
<p>The colors chosen are based on light frequency from slow to fast (think of a prism or rainbow). This method makes remembering the values much easier. Industry standard values are red=200, orange=100, yellow=50, green=35, and cyan=20. These can all be changed in the configuration menu.\
<p>This simple study offers the convenience of setting up 5 Bollinger Bands quickly in one place and making sure they are all scaled properly together on the same graph. It also simplifies the setup for automation.\
<p>At first glance this can be very confusing to look at, but it is easy to understand and use once explained. It's all about watching the data line.\
<ul><li>If the data line is rising, identify which color top band it is touching the most. That is the channel the data line is in. Flip that over for a falling data line.\
<li>If the data line has a strong movement then goes flat, take note of which mid line it is sitting on or resting under. If the data line gets stuck between a mid line and outer band, the move may be over or about to reverse.\
<li>If the data line has gone flat, identify which color mid line it is crossing the most. Then look high and low for the outer bands of the same color. That will be the channel the data line is in. Watch for an eventual break out.\
<li>When rising or falling, the data line may cross a mid line and touch a top line that is also riding on the next level up mid line. That means the data line is fully in the channel of the first mid line but could break out to the top line of the second mid line.\
<li>During any real movement, the data line will mostly be in one channel, be popping into the next channel every now and then, and be constrained to the upper or lower section of the next channel up. If the move fails to hit the outer band of that highest level channel, the move may not be over yet.\
<li>Wave counters take note of the previous two points. The corrective waves will be the ones crossing outer bands and the next level mid lines. If the continuation movement doesn't return to the previous movement, the correction may be larger than expected or the overall movement may be over.\
<li>The 200 period bands are usually the long term channel for the data line. The data line will usually bounce back if it crosses its outer band lines (they may stretch a little). If the data line keeps going, look for a new long term trend direction to start.\
<li>In summary, Bollinger Bands are all about dynamic support and resistance lines and measuring movement. If a line on one level gets crossed, look for the action to be defined on the next level up (the bands will start expanding). If volatility starts to decrease, look for the action to be defined on the next level down (the bands will start contracting).</ul>\
<p>As an exercise to help you see the messy bands easier, pick a color and focus on it very hard. Try to block out all other colors except the one you're focusing on. While still focusing on that color, let your vision go soft. Without moving your eyes off the first color, look for the other lines of the same color in your peripheral vision. With a little practice, this will become easy.";
		
		//Output Graphs
		
		Graph_PrimaryLine.Name = "Primary Line"; //drawn graphs must have a name.
		Graph_PrimaryLine.PrimaryColor = RGB(255, 255, 255);
		Graph_PrimaryLine.DrawStyle = DRAWSTYLE_LINE;
		Graph_PrimaryLine.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_PrimaryLine.LineWidth = 2;
		Graph_PrimaryLine.DrawZeros = 1;
		
		
		Graph_BB1Top.Name = "BB1 Top"; //drawn graphs must have a name.
		Graph_BB1Top.PrimaryColor = RGB(0, 255, 255);
		Graph_BB1Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB1Top.LineWidth = 1;
		Graph_BB1Top.DrawZeros = 1;
		
		Graph_BB1Mid.Name = "BB1 Mid"; //drawn graphs must have a name.
		Graph_BB1Mid.PrimaryColor = RGB(0, 255, 255);
		Graph_BB1Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB1Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB1Mid.LineWidth = 2;
		Graph_BB1Mid.DrawZeros = 1;
		
		Graph_BB1Low.Name = "BB1 Low"; //drawn graphs must have a name.
		Graph_BB1Low.PrimaryColor = RGB(0, 255, 255);
		Graph_BB1Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB1Low.LineWidth = 1;
		Graph_BB1Low.DrawZeros = 1;
		
		
		Graph_BB2Top.Name = "BB2 Top"; //drawn graphs must have a name.
		Graph_BB2Top.PrimaryColor = RGB(0, 255, 0);
		Graph_BB2Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB2Top.LineWidth = 1;
		Graph_BB2Top.DrawZeros = 1;
		
		Graph_BB2Mid.Name = "BB2 Mid"; //drawn graphs must have a name.
		Graph_BB2Mid.PrimaryColor = RGB(0, 255, 0);
		Graph_BB2Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB2Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB2Mid.LineWidth = 2;
		Graph_BB2Mid.DrawZeros = 1;
		
		Graph_BB2Low.Name = "BB2 Low"; //drawn graphs must have a name.
		Graph_BB2Low.PrimaryColor = RGB(0, 255, 0);
		Graph_BB2Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB2Low.LineWidth = 1;
		Graph_BB2Low.DrawZeros = 1;


		Graph_BB3Top.Name = "BB3 Top"; //drawn graphs must have a name.
		Graph_BB3Top.PrimaryColor = RGB(255, 255, 0);
		Graph_BB3Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB3Top.LineWidth = 1;
		Graph_BB3Top.DrawZeros = 1;
		
		Graph_BB3Mid.Name = "BB3 Mid"; //drawn graphs must have a name.
		Graph_BB3Mid.PrimaryColor = RGB(255, 255, 0);
		Graph_BB3Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB3Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB3Mid.LineWidth = 2;
		Graph_BB3Mid.DrawZeros = 1;
		
		Graph_BB3Low.Name = "BB3 Low"; //drawn graphs must have a name.
		Graph_BB3Low.PrimaryColor = RGB(255, 255, 0);
		Graph_BB3Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB3Low.LineWidth = 1;
		Graph_BB3Low.DrawZeros = 1;
		

		Graph_BB4Top.Name = "BB4 Top"; //drawn graphs must have a name.
		Graph_BB4Top.PrimaryColor = RGB(255, 128, 0);
		Graph_BB4Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB4Top.LineWidth = 1;
		Graph_BB4Top.DrawZeros = 1;
		
		Graph_BB4Mid.Name = "BB4 Mid"; //drawn graphs must have a name.
		Graph_BB4Mid.PrimaryColor = RGB(255, 128, 0);
		Graph_BB4Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB4Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB4Mid.LineWidth = 2;
		Graph_BB4Mid.DrawZeros = 1;
		
		Graph_BB4Low.Name = "BB4 Low"; //drawn graphs must have a name.
		Graph_BB4Low.PrimaryColor = RGB(255, 128, 0);
		Graph_BB4Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB4Low.LineWidth = 1;
		Graph_BB4Low.DrawZeros = 1;
		
		
		Graph_BB5Top.Name = "BB5 Top"; //drawn graphs must have a name.
		Graph_BB5Top.PrimaryColor = RGB(255, 0, 0);
		Graph_BB5Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB5Top.LineWidth = 1;
		Graph_BB5Top.DrawZeros = 1;
		
		Graph_BB5Mid.Name = "BB5 Mid"; //drawn graphs must have a name.
		Graph_BB5Mid.PrimaryColor = RGB(255, 0, 0);
		Graph_BB5Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB5Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB5Mid.LineWidth = 2;
		Graph_BB5Mid.DrawZeros = 1;
		
		Graph_BB5Low.Name = "BB5 Low"; //drawn graphs must have a name.
		Graph_BB5Low.PrimaryColor = RGB(255, 0, 0);
		Graph_BB5Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB5Low.LineWidth = 1;
		Graph_BB5Low.DrawZeros = 1;
		
		//User Inputs	
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData.SetDescription("Usually \"Last\" for Close.");
		
		In_SetPrimaryLine.Name = "Enable Primary Line?";
		In_SetPrimaryLine.SetYesNo(1);
		In_SetPrimaryLine.SetDescription("Enables the Primary Line.");
		
		In_PrimaryLinePeriod.Name = "Primary Line Smoothing Period";
		In_PrimaryLinePeriod.SetInt(3);
		In_PrimaryLinePeriod.SetIntLimits(2, 1000);
		In_PrimaryLinePeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_PrimaryLineMAType.Name = "Primary Line Moving Average Type";
		In_PrimaryLineMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_PrimaryLineMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_StandardDeviation.Name = "Standard Deviation";
		In_StandardDeviation.SetFloat(2.0);
		In_StandardDeviation.SetFloatLimits(0.1, 10.0);
		In_StandardDeviation.SetDescription("Bollinger Bands Standard Deviation setting. Usually 2.0.");
		
		In_BBRibbonMAType.Name = "Moving Average Type";
		In_BBRibbonMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_BBRibbonMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_BBRibbon1Period.Name = "MA Line 1 Period";
		In_BBRibbon1Period.SetInt(20);
		In_BBRibbon1Period.SetIntLimits(2, 1000);
		In_BBRibbon1Period.SetDescription("Number of bars for the period. Usually 20.");
		
		In_BBRibbon2Period.Name = "MA Line 2 Period";
		In_BBRibbon2Period.SetInt(35);
		In_BBRibbon2Period.SetIntLimits(2, 1000);
		In_BBRibbon2Period.SetDescription("Number of bars for the period. Usually 35.");
		
		In_BBRibbon3Period.Name = "MA Line 3 Period";
		In_BBRibbon3Period.SetInt(50);
		In_BBRibbon3Period.SetIntLimits(2, 1000);
		In_BBRibbon3Period.SetDescription("Number of bars for the period. Usually 50.");
		
		In_BBRibbon4Period.Name = "MA Line 4 Period";
		In_BBRibbon4Period.SetInt(100);
		In_BBRibbon4Period.SetIntLimits(2, 1000);
		In_BBRibbon4Period.SetDescription("Number of bars for the period. Usually 100.");
		
		In_BBRibbon5Period.Name = "MA Line 5 Period";
		In_BBRibbon5Period.SetInt(200);
		In_BBRibbon5Period.SetIntLimits(2, 1000);
		In_BBRibbon5Period.SetDescription("Number of bars for the period. Usually 200.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	if(sc.Index == 0) {
		//Turn off Graph_PrimaryLine if disabled.
		if(In_SetPrimaryLine.GetYesNo()) {Graph_PrimaryLine.DrawStyle = DRAWSTYLE_LINE;}
		else {Graph_PrimaryLine.DrawStyle = DRAWSTYLE_IGNORE;}
		}
	
	if(In_SetPrimaryLine.GetYesNo()) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_PrimaryLine, In_PrimaryLineMAType.GetMovAvgType(), In_PrimaryLinePeriod.GetInt() );
		}
	
	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB1Mid, In_BBRibbon1Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB1Top[sc.Index] = Graph_BB1Mid.Arrays[0][sc.Index];
	Graph_BB1Low[sc.Index] = Graph_BB1Mid.Arrays[1][sc.Index];

	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB2Mid, In_BBRibbon2Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB2Top[sc.Index] = Graph_BB2Mid.Arrays[0][sc.Index];
	Graph_BB2Low[sc.Index] = Graph_BB2Mid.Arrays[1][sc.Index];
	
	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB3Mid, In_BBRibbon3Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB3Top[sc.Index] = Graph_BB3Mid.Arrays[0][sc.Index];
	Graph_BB3Low[sc.Index] = Graph_BB3Mid.Arrays[1][sc.Index];
	
	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB4Mid, In_BBRibbon4Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB4Top[sc.Index] = Graph_BB4Mid.Arrays[0][sc.Index];
	Graph_BB4Low[sc.Index] = Graph_BB4Mid.Arrays[1][sc.Index];
	
	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB5Mid, In_BBRibbon5Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB5Top[sc.Index] = Graph_BB5Mid.Arrays[0][sc.Index];
	Graph_BB5Low[sc.Index] = Graph_BB5Mid.Arrays[1][sc.Index];
}

/* =============================================================================
================================================================================
Ease Of Movement With Filters
================================================================================
============================================================================= */
SCSFExport scsf_EMVWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef ZeroLine = sc.Subgraph[0];
	SCSubgraphRef Graph_EMV = sc.Subgraph[1];
	SCInputRef In_VolumeFilterType = sc.Input[0];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[1];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[2];
	SCInputRef In_EMVSmoothingPeriod = sc.Input[3];
	SCInputRef In_EMVSmoothingMAType = sc.Input[4];
	SCInputRef In_OutputMultiplier = sc.Input[5];
	SCSubgraphRef EMV = sc.Subgraph[2];
	SCSubgraphRef VolumeMA = sc.Subgraph[3];
	//SCFloatArrayRef FloatArray = Graph_EMV.Arrays[0];
	
	//remember local variables are not persistent.
	float HighLowRange, VolumeFiltered;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Ease Of Movement With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //in this case, not main price graph
		sc.ValueFormat = VALUEFORMAT_INHERITED; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Ease Of Movement With Filters (EMV). A volume based oscillator developed by Richard Arms. Above the zero line shows positive movement. Below the zero line shows negative movement. Small volumes and a large high-low price range will produce higher EMV values since it took lower volume to move price more. Large volumes and a small high-low price range will produce lower EMV values since it took higher volumes to move the price a smaller amount. Once the price breaks out, the EMV line will start moving again. When price is significantly moving, the EMV line should be moving in the same direction and away from the zero line. This indicator should be used with other indicators to confirm final price movement.\
<p>This EMV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final EMV line.\
<p>Observations. Log and Square Root volume filtering have an interesting side effect of shrinking the EMV value on low volume moves. This is useful for identifying dead zones during the trading day.";
		
		//Output Graph
		Graph_EMV.Name = "EMV"; //drawn graphs must have a name.
		Graph_EMV.PrimaryColor = RGB(255, 0, 255);
		Graph_EMV.DrawStyle = DRAWSTYLE_LINE;
		Graph_EMV.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_EMV.LineWidth = 1;
		Graph_EMV.DrawZeros = 1;
		
		ZeroLine.Name="Zero";
		ZeroLine.DrawStyle = DRAWSTYLE_LINE;
		ZeroLine.LineStyle = LINESTYLE_DOT;
		ZeroLine.LineWidth = 1;
		ZeroLine.PrimaryColor = RGB(128, 128, 128);;
		ZeroLine.DisplayNameValueInWindowsFlags = 0;
		ZeroLine.DrawZeros = 1;
		
		//User Inputs
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_EMVSmoothingPeriod.Name = "EMV Smoothing Period";
		In_EMVSmoothingPeriod.SetInt(14);
		In_EMVSmoothingPeriod.SetIntLimits(2, 50);
		In_EMVSmoothingPeriod.SetDescription("Number of bars for the period. Usually 10-25.");
		
		In_EMVSmoothingMAType.Name = "EMV Smoothing Moving Average Type";
		In_EMVSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_EMVSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_OutputMultiplier.Name = "Output Multiplier";
		In_OutputMultiplier.SetFloat(1e8);
		In_OutputMultiplier.SetDescription("EMV numbers are typically very small. This does nothing more than to increase their value to something easier to read.");
		
		return;
		}
	
	// Section 2 - Do data processing here

	//Handle the zero line.
	ZeroLine[sc.Index] = 0.0;
	
	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex =  In_EMVSmoothingPeriod.GetInt() -1;
		//Set lower limit on the Output Multiplier. There doesn't need to be an upper limit.
		if(In_OutputMultiplier.GetFloat() < 1.0) {In_OutputMultiplier.SetFloat(1.0);}
		}
	
	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered = (float)sc.Volume[sc.Index];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered = log( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered = sqrt( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.Volume[sc.Index] <= VolumeMA[sc.Index]) {VolumeFiltered = (float)sc.Volume[sc.Index];} //handle normal volume
		else {VolumeFiltered = (float)VolumeMA[sc.Index];} //handle clipped volume
		}
	
	//not enough data yet.
	if(sc.Index < 1) {return;}
	
	//Do the EMV calculations.
	HighLowRange = sc.High[sc.Index] - sc.Low[sc.Index];
	if( (HighLowRange > 0.0) && (VolumeFiltered > 0.01) ) { //handle divide by 0 problems
		EMV[sc.Index] = ( ((sc.High[sc.Index] + sc.Low[sc.Index]) / 2.0) - ((sc.High[sc.Index-1] + sc.Low[sc.Index-1]) / 2.0) ) / (VolumeFiltered / HighLowRange) * In_OutputMultiplier.GetFloat();
		}
	else {
		//copy previous value to avoid skipping around and gaps in chart.
		EMV[sc.Index] = EMV[sc.Index-1];
		}
	
	//Handle smoothing.
	sc.MovingAverage(EMV, Graph_EMV, In_EMVSmoothingMAType.GetMovAvgType(), In_EMVSmoothingPeriod.GetInt() );
}

/* =============================================================================
================================================================================
Efficiency Ratio Indicator With Filters
================================================================================
============================================================================= */
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
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //in this case, not main price graph. Let it auto-choose.
		sc.ValueFormat = 4; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_ZEROBASED; //Graph start at 0 and goes to 1.0.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Efficiency Ratio Indicator With Filters by Perry Kaufman. This indicator measures volatility relative to previous samples. In short, it measures the direct distance between 2 points and divides it by the sum of the difference between each of those points. The normal indicator range is 0.0 to 1.0 (essentially 0% to 100%). Values closer to 1.0 are moving with a higher efficiency than those closer to 0.0.\
<p>This version includes extra smoothing options to help clean up the output line.\
<p>This algorithm forms the core of the generic adaptive moving average line.";
		
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
		
		return;
		}
	
	// Section 2 - Do data processing here

	Period = In_ERIPeriod.GetInt(); //easier to read.
	
	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period + In_ERINormalSmoothingPeriod.GetInt() + (In_ERISetExtraSmoothing.GetYesNo() ? In_ERIExtraSmoothingPeriod.GetInt() : 0.0 ) + (In_PriceSetSmoothing.GetYesNo() ? In_PriceSmoothingPeriod.GetInt() : 0.0 );
		}
		
	//Handle price smoothing.
	if( In_PriceSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Price, In_PriceSmoothingMAType.GetMovAvgType(), In_PriceSmoothingPeriod.GetInt() );
		}
	else {
		Price[sc.Index] = sc.BaseDataIn[In_InputData.GetInputDataIndex()][sc.Index];
		}
	
	//Not enough data yet for the calculation.
	if(sc.Index < Period) {return;}
	
	//Do the ERI calculations
	
	//Direct distance
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

/* =============================================================================
================================================================================
Intraday Intensity Oscillator By Tick With Filters
================================================================================
============================================================================= */
SCSFExport scsf_IntradayIntensityOscillatorByTickWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef ZeroLine = sc.Subgraph[0];
	SCSubgraphRef Graph_IIO = sc.Subgraph[1];
	SCInputRef In_IIOPeriod = sc.Input[0];
	SCInputRef In_InputData = sc.Input[1];
	SCInputRef In_VolumeFilterType = sc.Input[2];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[3];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[4];
	SCInputRef In_IIOSetSmoothing = sc.Input[5];
	SCInputRef In_IIOSmoothingPeriod = sc.Input[6];
	SCInputRef In_IIOSmoothingMAType = sc.Input[7];
	SCInputRef In_OutputMultiplier = sc.Input[8];
	SCSubgraphRef II = sc.Subgraph[2];
	SCSubgraphRef IIO = sc.Subgraph[3];
	SCSubgraphRef VolumeMA = sc.Subgraph[4];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[5];
	//SCFloatArrayRef FloatArray = Graph_IIO.Arrays[0];

	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	int i, j, k, Period, IndexTemp;
	float RunningTotalII, RunningTotalVolume;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Intraday Intensity Oscillator By Tick With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 3; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Intraday Intensity Oscillator By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>A price and volume based indicator that attempts to estimate accumulation and distribution of institutional traders. Normal ranges are +/-0.3. Spikes can go higher. Filtering can changes these values some. This \"By Tick\" version uses the difference between up and down volume instead of the price scaling factor in the original. This version is more accurate.\
<p>This version includes extras to help clean up the graph and make it easier to integrate with automation. The \"Set IIO Smoothing?\" option enables cleaning up some of the IIO noise after the calculation. It is recommended to smooth IIO out with an EMA 3-7.\
<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.\
<p>To use traditional IIO, turn off all smoothing and filtering options.";

		//Output Graph
		Graph_IIO.Name = "IIO"; //drawn graphs must have a name.
		Graph_IIO.PrimaryColor = RGB(0, 255, 0);
		Graph_IIO.DrawStyle = DRAWSTYLE_LINE;
		Graph_IIO.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_IIO.LineWidth = 2;
		Graph_IIO.DrawZeros = 1;
		
		ZeroLine.Name="Zero";
		ZeroLine.DrawStyle = DRAWSTYLE_LINE;
		ZeroLine.LineStyle = LINESTYLE_DOT;
		ZeroLine.LineWidth = 1;
		ZeroLine.PrimaryColor = RGB(128, 128, 128);;
		ZeroLine.DisplayNameValueInWindowsFlags = 0;
		ZeroLine.DrawZeros = 1;
		
		//User Inputs
		
		In_IIOPeriod.Name = "IIO Period";
		In_IIOPeriod.SetInt(20);
		In_IIOPeriod.SetIntLimits(3, 300);
		In_IIOPeriod.SetDescription("Number of bars for the period. Useful values are 20 and higher.");
		
		In_InputData.Name = "Input Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");	
		
		In_IIOSetSmoothing.Name = "Set IIO Smoothing?";
		In_IIOSetSmoothing.SetYesNo(1);
		In_IIOSetSmoothing.SetDescription("Enables extended IIO smoothing options.");
		
		In_IIOSmoothingPeriod.Name = "IIO Smoothing Period";
		In_IIOSmoothingPeriod.SetInt(7);
		In_IIOSmoothingPeriod.SetIntLimits(2, 50);
		In_IIOSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_IIOSmoothingMAType.Name = "IIO Smoothing Moving Average Type";
		In_IIOSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_IIOSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_OutputMultiplier.Name = "IIO Output Multiplier";
		In_OutputMultiplier.SetFloat(5.0);
		In_OutputMultiplier.SetFloatLimits(1.0, 50.0);
		In_OutputMultiplier.SetDescription("This By Tick version produces much smaller output. Multiply it to make it larger and more equal to the original version.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	i = sc.Index; //easier to read traditional C/C++ index i in multiple arrays on one line.
	Period = In_IIOPeriod.GetInt(); //easier to read.
	
	//Handle the zero line.
	ZeroLine[i] = 0.0;
	
	//if first run
	if (i == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period - 1 - (In_IIOSetSmoothing.GetYesNo() ? In_IIOSmoothingPeriod.GetInt() : 0);
		}

	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}
		
	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[i] = (float)sc.BaseData[VolumeType][i];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[i] = log( (float)sc.BaseData[VolumeType][i] < 1.0 ? 1.0 : (float)sc.BaseData[VolumeType][i] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[i] = sqrt( (float)sc.BaseData[VolumeType][i] < 1.0 ? 1.0 : (float)sc.BaseData[VolumeType][i] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.BaseData[VolumeType][i] <= VolumeMA[i]) {
			//handle normal volume
			VolumeFiltered[i] = (float)sc.BaseData[VolumeType][i];
			}
		else { //handle clipped volume
			VolumeFiltered[i] = VolumeMA[i];
			}
		}

	/* Old Intraday Intensity Calculations: split the volume based on accumulation or distribution estimations. Keep this here for original comparison.
	//Generate Intraday Intensity values.
	//Handle divide by 0 problems.
	if( (VolumeFiltered[i] < 0.01) || (sc.High[i] == sc.Low[i]) ) {II[i] = 0.0;}
	//else calculate as normal.
	//Analysis: ScalingFactor * Volume. If close is in the middle, ScalingFactor=0.0.
	//If close is at the top, ScalingFactor=1.0. If close is at the bottom, ScalingFactor=-1.0.
	else {II[i] = (((2.0 * sc.Close[i]) - sc.High[i] - sc.Low[i]) / (sc.High[i] - sc.Low[i])) * VolumeFiltered[i];}
	*/
	//New Intraday Intensity Calculations: the difference between up and down volume.
	//For volume filtering: create the fraction and multiply it times VolumeFiltered. Fraction range is still 1.0 to -1.0.
	II[i] = (((float)sc.BaseData[Up][i] - (float)sc.BaseData[Down][i]) / (float)sc.BaseData[VolumeType][i]) * VolumeFiltered[i];
	
	//Not enough data yet for the IIO calculation.
	if( i < Period ) {return;}
	
	//do the inner loop
	for(j=i-Period+1; j<=i; j++) {
		RunningTotalII = 0.0;
		RunningTotalVolume = 0.0;
		IndexTemp = j - Period +1;
		if(IndexTemp < 0) {IndexTemp = 0;}
		for(k=IndexTemp; k<=j; k++) {
			RunningTotalII += II[k];
			//Safety: Under some very rare circumstances, a volume moving average number may be negative.
			//Filter those out so the indicator doesn't get trashed.
			if(VolumeFiltered[k] > 0.0) {RunningTotalVolume += VolumeFiltered[k];}
			}
		}
	
	//Handle divide by 0.
	//Analysis: ScaledVolume/TotalVolume for the period.
	if(RunningTotalVolume > 0.0) {IIO[i] = (RunningTotalII / RunningTotalVolume) * In_OutputMultiplier.GetFloat();}
	else {IIO[i] = 0.0;}
	
	if( In_IIOSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(IIO, Graph_IIO, In_IIOSmoothingMAType.GetMovAvgType(), In_IIOSmoothingPeriod.GetInt() );
		}
	else {
		Graph_IIO[i] = IIO[i];
		}
}

/* =============================================================================
================================================================================
Intraday Intensity Oscillator With Filters
================================================================================
============================================================================= */
SCSFExport scsf_IntradayIntensityOscillatorWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef ZeroLine = sc.Subgraph[0];
	SCSubgraphRef Graph_IIO = sc.Subgraph[1];
	SCInputRef In_IIOPeriod = sc.Input[0];
	SCInputRef In_VolumeFilterType = sc.Input[1];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[2];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[3];
	SCInputRef In_IIOSetSmoothing = sc.Input[4];
	SCInputRef In_IIOSmoothingPeriod = sc.Input[5];
	SCInputRef In_IIOSmoothingMAType = sc.Input[6];
	SCSubgraphRef II = sc.Subgraph[2];
	SCSubgraphRef IIO = sc.Subgraph[3];
	SCSubgraphRef VolumeMA = sc.Subgraph[4];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[5];
	//SCFloatArrayRef FloatArray = Graph_IIO.Arrays[0];

	//remember local variables are not persistent.
	int i, j, k, Period, IndexTemp;
	float RunningTotalII, RunningTotalVolume;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Intraday Intensity Oscillator With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 4; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Intraday Intensity Oscillator With Filters. A price and volume based indicator that attempts to estimate accumulation and distribution of institutional traders. Normal ranges are +/-0.3. Spikes can go higher. Filtering can changes these values some.\
<p>If you have tick by tick volume up/down data, use the \"By Tick\" version.\
<p>This version includes extras to help clean up the graph and make it easier to integrate with automation. The \"Set IIO Smoothing?\" option enables cleaning up some of the IIO noise after the calculation. It is recommended to smooth IIO out with an EMA 3-7.\
<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.\
<p>To use traditional IIO, turn off all smoothing and filtering options.";
		
		//Output Graph
		Graph_IIO.Name = "IIO"; //drawn graphs must have a name.
		Graph_IIO.PrimaryColor = RGB(0, 255, 0);
		Graph_IIO.DrawStyle = DRAWSTYLE_LINE;
		Graph_IIO.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_IIO.LineWidth = 2;
		Graph_IIO.DrawZeros = 1;
		
		ZeroLine.Name="Zero";
		ZeroLine.DrawStyle = DRAWSTYLE_LINE;
		ZeroLine.LineStyle = LINESTYLE_DOT;
		ZeroLine.LineWidth = 1;
		ZeroLine.PrimaryColor = RGB(128, 128, 128);;
		ZeroLine.DisplayNameValueInWindowsFlags = 0;
		ZeroLine.DrawZeros = 1;
		
		//User Inputs
		
		In_IIOPeriod.Name = "IIO Period";
		In_IIOPeriod.SetInt(20);
		In_IIOPeriod.SetIntLimits(3, 300);
		In_IIOPeriod.SetDescription("Number of bars for the period. Useful values are 20 and higher.");
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");	
		
		In_IIOSetSmoothing.Name = "Set IIO Smoothing?";
		In_IIOSetSmoothing.SetYesNo(1);
		In_IIOSetSmoothing.SetDescription("Enables extended IIO smoothing options.");
		
		In_IIOSmoothingPeriod.Name = "IIO Smoothing Period";
		In_IIOSmoothingPeriod.SetInt(7);
		In_IIOSmoothingPeriod.SetIntLimits(2, 50);
		In_IIOSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_IIOSmoothingMAType.Name = "IIO Smoothing Moving Average Type";
		In_IIOSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_IIOSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	i = sc.Index; //easier to read traditional C/C++ index i in multiple arrays on one line.
	Period = In_IIOPeriod.GetInt(); //easier to read.
	
	//Handle the zero line.
	ZeroLine[i] = 0.0;
	
	//if first run
	if (i == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period - 1 + (In_IIOSetSmoothing.GetYesNo() ? In_IIOSmoothingPeriod.GetInt() : 0.0);
		}

	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[i] = (float)sc.Volume[i];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[i] = log( (float)sc.Volume[i] < 1.0 ? 1.0 : (float)sc.Volume[i] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[i] = sqrt( (float)sc.Volume[i] < 1.0 ? 1.0 : (float)sc.Volume[i] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.Volume[i] <= VolumeMA[i]) {VolumeFiltered[i] = (float)sc.Volume[i];} //handle normal volume
		else {VolumeFiltered[i] = VolumeMA[i];} //handle clipped volume
		}

	//Generate Intraday Intensity values.
	//Handle divide by 0 problems.
	if( (VolumeFiltered[i] < 0.01) || (sc.High[i] == sc.Low[i]) ) {II[i] = 0.0;}
	//else calculate as normal.
	//Analysis: ScalingFactor * Volume. If close is in the middle, ScalingFactor=0.0.
	//If close is at the top, ScalingFactor=1.0. If close is at the bottom, ScalingFactor=-1.0.
	else {II[i] = (((2.0 * sc.Close[i]) - sc.High[i] - sc.Low[i]) / (sc.High[i] - sc.Low[i])) * VolumeFiltered[i];}
	
	//Not enough data yet for the IIO calculation.
	if( i < Period ) {return;}
	
	//do the inner loop
	for(j=i-Period+1; j<=i; j++) {
		RunningTotalII = 0.0;
		RunningTotalVolume = 0.0;
		IndexTemp = j - Period +1;
		if(IndexTemp < 0) {IndexTemp = 0;}
		for(k=IndexTemp; k<=j; k++) {
			RunningTotalII += II[k];
			//Safety: Under some very rare circumstances, a volume moving average number may be negative.
			//Filter those out so the indicator doesn't get trashed.
			if(VolumeFiltered[k] > 0.0) {RunningTotalVolume += VolumeFiltered[k];}
			}
		}
	
	//Handle divide by 0.
	//Analysis: ScaledVolume/TotalVolume for the period.
	if(RunningTotalVolume > 0.0) {IIO[i] = RunningTotalII / RunningTotalVolume;}
	else {IIO[i] = 0.0;}
	
	if( In_IIOSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(IIO, Graph_IIO, In_IIOSmoothingMAType.GetMovAvgType(), In_IIOSmoothingPeriod.GetInt() );
		}
	else {
		Graph_IIO[i] = IIO[i];
		}	
}

/* =============================================================================
================================================================================
Klinger Volume Oscillator With Filters
================================================================================
============================================================================= */
SCSFExport scsf_KVOWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef ZeroLine = sc.Subgraph[0];
	SCSubgraphRef Graph_Histogram = sc.Subgraph[1];
	SCSubgraphRef Graph_KVOTrigger = sc.Subgraph[2];
	SCSubgraphRef Graph_KVO = sc.Subgraph[3]; //last graph is drawn on top.
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_PriceSetSmoothing = sc.Input[1];
	SCInputRef In_PriceSmoothingPeriod = sc.Input[2];
	SCInputRef In_PriceSmoothingMAType = sc.Input[3];
	SCInputRef In_VolumeFilterType = sc.Input[4];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[5];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[6];
	SCInputRef In_KVOFastSmoothingPeriod = sc.Input[7];
	SCInputRef In_KVOSlowSmoothingPeriod = sc.Input[8];
	SCInputRef In_KVOFastSlowSmoothingMAType = sc.Input[9];
	SCInputRef In_KVOSetExtraSmoothing = sc.Input[10];
	SCInputRef In_KVOExtraSmoothingPeriod = sc.Input[11];
	SCInputRef In_KVOExtraSmoothingMAType = sc.Input[12];
	SCInputRef In_KVOTriggerSmoothingPeriod = sc.Input[13];
	SCInputRef In_KVOTriggerSmoothingMAType = sc.Input[14];
	SCInputRef In_OutputMultiplier = sc.Input[15];
	SCSubgraphRef Price = sc.Subgraph[4];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[5];
	SCSubgraphRef VolumeMA = sc.Subgraph[6];
	SCSubgraphRef VolumeForce = sc.Subgraph[7];
	SCSubgraphRef KVOFast = sc.Subgraph[8];
	SCSubgraphRef KVOSlow = sc.Subgraph[9];
	SCSubgraphRef KVO = sc.Subgraph[10];
	SCSubgraphRef KVOSmoothed = sc.Subgraph[11];
	SCSubgraphRef HighLow = sc.Subgraph[12];
	//SCFloatArrayRef FloatArray = Graph_KVO.Arrays[0];
	
	//remember local variables are not persistent.
	int itemp;
	float ScalingFactor;
	
	//persistent variables.
	int &Trend = sc.PersistVars->i1;
	int &TrendPrevious = sc.PersistVars->i2;
	float &HighLowSum = sc.PersistVars->f1;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Klinger Volume Oscillator With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 2; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Klinger Volume Oscillator With Filters (KVO). A price and volume based oscillator developed by Stephen J. Klinger to handle both short term and long term time frame analysis of money flowing into and out of a security. It's output is very similar to MACD and can be traded in the same way. It is somewhat unique as its algorithm keeps track of current direction and accounts for it in the calculations. Klinger defined volume as a force behind price movement and accumulation/distribution as the overall volume change from period to period. He labeled it Volume Force. A positive Volume Force is more accumulation than distribution, a negative volume force is more distribution than accumulation. As a trend starts to end, the Volume Force should noticeably reduce before the price reversal. Klinger has some guidelines for his oscillator. The most reliable signals from KVO are in the direction of the current price trend so don't trade against the trend. KVO divergence from current price action is a trend weakening signal (similar to MACD divergence). Klinger uses a separate 89 period EMA for price to determine the current price trend. An up trend is price above EMA89, and a down trend is price below EMA89. In an up trend, if KVO tops then down crosses the trigger line, that's a signal that the trend is near completion (invert that for a down trend). Klinger recommends other indicators like Stochastic, RSI, and MACD to help confirm movement into over bought/sold conditions.\
<p>Brett Johnson's Programming Rant: Most people are totally clueless about how to properly implement this indicator. Initially I thought I found a web page that properly explained it, but continued searching over the next couple hours proved me very wrong. I've found several variations that are incorrect. I've found some web pages with 3 different versions written in 3 different stock chart languages. I've found a couple web pages showing the proper algorithm in math form (well, mostly), but then they screw up the code several lines down. Nobody seems to pay attention. Some people seem to give up and implement a simplified version. If you're trying to program this indicator yourself and are stuck, check my source code. It's open and excessively documented. There's no reason for a simple algorithm to be this screwed up on so many other platforms and web pages.\
<p>This KVO version has multiple smoothing options to handle an extremely noisy indicator.\
<p>This KVO version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.\
<p>To use KVO in its original form, turn off all extra options and use the default values.\
<p>Observations. To say that this is a noisy indicator is an understatement. Turn on MA Clip 3 and all the filters to their default values (or higher) to greatly clean this up. In addition to the recommended indicators, also add trend lines as a price shouldn't be traded until it breaks the trend line. Always remember, just because KVO moves doesn't mean that price will move with it. This indicator doesn't do very well with ranging data. To be fair, that's true of many indicators. This indicator was originally developed in the mid 1990's for daily bars that almost always had volume. Low time scale intraday bars (like 1 minute) with 0 volume will make the KVO line very noisy. Zoom out time wise until all the bars have enough volume for a clean signal.";
		
		//Output Graph
		
		Graph_KVO.Name = "KVO"; //drawn graphs must have a name.
		Graph_KVO.PrimaryColor = RGB(0, 0, 255);
		Graph_KVO.DrawStyle = DRAWSTYLE_LINE;
		Graph_KVO.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_KVO.LineWidth = 1;
		Graph_KVO.DrawZeros = 1;
		
		Graph_KVOTrigger.Name = "KVOTrigger"; //drawn graphs must have a name.
		Graph_KVOTrigger.PrimaryColor = RGB(255, 0, 0);
		Graph_KVOTrigger.DrawStyle = DRAWSTYLE_LINE;
		Graph_KVOTrigger.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_KVOTrigger.LineWidth = 1;
		Graph_KVOTrigger.DrawZeros = 1;
		
		Graph_Histogram.Name = "KVOHistogram"; //drawn graphs must have a name.
		Graph_Histogram.PrimaryColor = RGB(64, 64, 64);
		Graph_Histogram.DrawStyle = DRAWSTYLE_BAR;
		Graph_Histogram.LineStyle = LINESTYLE_SOLID;
		Graph_Histogram.LineWidth = 2;
		Graph_Histogram.DrawZeros = 1;
		
		ZeroLine.Name="Zero";
		ZeroLine.DrawStyle = DRAWSTYLE_LINE;
		ZeroLine.LineStyle = LINESTYLE_DOT;
		ZeroLine.LineWidth = 1;
		ZeroLine.PrimaryColor = RGB(128, 128, 128);;
		ZeroLine.DisplayNameValueInWindowsFlags = 0;
		ZeroLine.DrawZeros = 1;
		
		//User Inputs
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_HLC); //default to bar close.
		In_InputData.SetDescription("Usually \"HLC Avg\" for Typical Price.");

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
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_KVOFastSmoothingPeriod.Name = "KVO Fast Period";
		In_KVOFastSmoothingPeriod.SetInt(34);
		In_KVOFastSmoothingPeriod.SetIntLimits(2, 300);
		In_KVOFastSmoothingPeriod.SetDescription("Number of bars for the period. Usually over 20.");
		
		In_KVOSlowSmoothingPeriod.Name = "KVO Slow Period";
		In_KVOSlowSmoothingPeriod.SetInt(55);
		In_KVOSlowSmoothingPeriod.SetIntLimits(3, 300);
		In_KVOSlowSmoothingPeriod.SetDescription("Number of bars for the period. Usually over 40.");
		
		In_KVOFastSlowSmoothingMAType.Name = "KVO Moving Average Type";
		In_KVOFastSlowSmoothingMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_KVOFastSlowSmoothingMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_KVOSetExtraSmoothing.Name = "Set Extra KVO Smoothing?";
		In_KVOSetExtraSmoothing.SetYesNo(0);
		In_KVOSetExtraSmoothing.SetDescription("The KVO line is noisy. Enables extended KVO smoothing options.");
		
		In_KVOExtraSmoothingPeriod.Name = "Extra KVO Smoothing Period";
		In_KVOExtraSmoothingPeriod.SetInt(5);
		In_KVOExtraSmoothingPeriod.SetIntLimits(2, 50);
		In_KVOExtraSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_KVOExtraSmoothingMAType.Name = "Extra KVO Smoothing Moving Average Type";
		In_KVOExtraSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_KVOExtraSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_KVOTriggerSmoothingPeriod.Name = "KVO Trigger Period";
		In_KVOTriggerSmoothingPeriod.SetInt(13);
		In_KVOTriggerSmoothingPeriod.SetIntLimits(3, 300);
		In_KVOTriggerSmoothingPeriod.SetDescription("Number of bars for the period. Usually 9-15.");
		
		In_KVOTriggerSmoothingMAType.Name = "KVO Trigger Moving Average Type";
		In_KVOTriggerSmoothingMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_KVOTriggerSmoothingMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_OutputMultiplier.Name = "Output Multiplier";
		In_OutputMultiplier.SetFloat(100.0);
		In_OutputMultiplier.SetFloatLimits(1.0e-6, 100.0);
		In_OutputMultiplier.SetDescription("Range 1.0e-6 to 100.0. The Output Multiplier of 100.0 is part of the original formula. It does nothing more than to increase the output values to something more human readable. On larger time frame bars (like daily) the numbers will be excessively large. It would be better to shrink those numbers to something more manageable.");
		
		return;
		}
	
	// Section 2 - Do data processing here

	//Handle the zero line.
	ZeroLine[sc.Index] = 0.0;
	
	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		//Make sure smoothing periods are in the right order.
		if(In_KVOFastSmoothingPeriod.GetInt() > In_KVOSlowSmoothingPeriod.GetInt()) {
			itemp = In_KVOSlowSmoothingPeriod.GetInt();
			In_KVOSlowSmoothingPeriod.SetInt( In_KVOFastSmoothingPeriod.GetInt() );
			In_KVOFastSmoothingPeriod.SetInt( itemp );
			}
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_KVOSlowSmoothingPeriod.GetInt() + In_KVOTriggerSmoothingPeriod.GetInt() + (In_PriceSetSmoothing.GetYesNo() ? In_PriceSmoothingPeriod.GetInt() : 0 ) + (In_KVOSetExtraSmoothing.GetYesNo() ? In_KVOExtraSmoothingPeriod.GetInt() : 0 );
		// Initialize persistent variables.
		Trend = 0; //Initializing Trend to 0 will block early garbage in the later VolumeForce calculation.
		TrendPrevious = 0; //Initializing TrendPrevious to 0 will block early garbage in the later VolumeForce calculation.
		HighLowSum = 0.0;
		}
	
	//Handle price smoothing.
	if( In_PriceSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Price, In_PriceSmoothingMAType.GetMovAvgType(), In_PriceSmoothingPeriod.GetInt() );
		}
	else {
		Price[sc.Index] = sc.BaseDataIn[In_InputData.GetInputDataIndex()][sc.Index];
		}
	
	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[sc.Index] = (float)sc.Volume[sc.Index];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[sc.Index] = log( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[sc.Index] = sqrt( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.Volume[sc.Index] <= VolumeMA[sc.Index]) {VolumeFiltered[sc.Index] = (float)sc.Volume[sc.Index];} //handle normal volume
		else {VolumeFiltered[sc.Index] = (float)VolumeMA[sc.Index];} //handle clipped volume
		}
	
	//Do the KVO calculations.
	
	//Typical Price handled by In_InputData and Price[] already. Using "High+Low+Close" without the "divide by 3" can create false movements.
	//Variable names cleaned up for clarity and understanding:
	//DM[] or Daily Measurement = HighLow[]
	//CM or Cumulative Measurement = HighLowSum
	//ScalingFactor = that part of the VolumeForce equation where a lot of people screw up. Watch the parenthesis everyone. Order of operation is very important here. The absolute value of ScalingFactor is designed to be above 1.0 most of the time. The longer the run, the higher ScalingFactor gets to 2.0.
	//The WRONG Scaling Factor: abs(2.0 * (HighLow[sc.Index]/HighLowSum) -1.0); The range on this one is mostly 0.0 to 1.0. A value of 0.0 in a running average will whiplash the MA line. 0 vales are generally useless to everyone.
	//The right Scaling Factor: abs(2.0 * ((HighLow[sc.Index]/HighLowSum) -1.0)); The range on this one is mostly 1.0 to 2.0. This means the values are passed through ranging from untouched to doubled. The whiplash potential is much less and the signal will be cleaner.
	
	//Load HighLow array.
	HighLow[sc.Index] = sc.High[sc.Index] - sc.Low[sc.Index];
	
	//not enough data yet to finish the calculation.
	if(sc.Index < 1) {return;}
	
	//Determine if the current trend direction.
	if(Price[sc.Index] == Price[sc.Index-1]) {Trend = TrendPrevious;} //no trend, leave it unchanged
	else if(Price[sc.Index] > Price[sc.Index-1]) {Trend = 1;} //up trend
	else {Trend = -1;} //down trend
	
	//Handle price summation.
	if(Trend == TrendPrevious) {HighLowSum += HighLow[sc.Index];} //continue trending
	else { //trend reversal
		HighLowSum = HighLow[sc.Index-1] + HighLow[sc.Index]; //initialize with the previous and current values
		TrendPrevious = Trend; //register trend change
		}
	
	/*
	Scaling Factor divide by 0 problems. These should be rare but can happen on low volume securities. This is poorly addressed in all the documentation, so it needs to be analyzed in depth.
	Under normal circumstances, HighLowSum is initialized with 2 bars of HighLow[] and should keep increasing with each additional bar until reversal. The HighLow[i]/HighLowSum number is a fraction that should always be getting smaller until the next reversal because of the constantly increasing denominator.
	Real world data shows the Scaling Factor range to mostly be between 1.0 and 2.0 with the number approaching 2.0 the longer it goes without a reversal.
	If HighLowSum is 0.0, then there was probably a recent reversal reset on junk data.
	To find out what the Scaling Factor would be in general after a reversal, set up a test with boring data, in this case 1.0 for the 2 previous HighLow[] bars:
	ScalingFactor = abs(2.0 * ((1.0/(1.0+1.0)) - 1.0)) = 1.0
	We already know the range is mostly 1.0-2.0 and generally starts out low. The value of 1.0 is a good choice for "pass through and don't mess with it".
	To find out what the Scaling Factor would be with a whiplash reset, set up another test with 1.0 and 0.1:
	ScalingFactor = abs(2.0 * ((0.1/(1.0+0.1)) - 1.0)) = 1.8
	This starts out very high in the range. A near full boost starting out on garbage amplifying a bad signal is a bad idea.
	To find out what the Scaling Factor would be with the previous whiplashed flipped around, set up another test with 0.1 and 1.0:
	ScalingFactor = abs(2.0 * ((1.0/(0.1+1.0)) - 1.0)) = 0.18
	This damps the output and would bring the final equation value down close to 0.0. Unnecessary zeros in a moving average cause whiplash. This isn't a very good choice either.
	If we take the middle of the last 2 extremes, we get 0.8. This isn't far from 1.0 in the boring example. In general, it looks like setting Scaling Factor to 1.0 on bad data and just letting it pass through would probably be the most logical choice.
	Keep in mind there's always the possibility volume will be 0, thus zeroing out the equation and handling the problem by itself.
	*/
	
	//Calculate a proper Scaling Factor
	if(HighLowSum == 0.0) {ScalingFactor = 1.0;} //handle any divide by 0 problems
	else {
		ScalingFactor = 2.0 * ((HighLow[sc.Index]/HighLowSum) -1.0);
		if(ScalingFactor < 0.0) {ScalingFactor *= -1.0;} //ScalingFactor must be positive.		
		}
		
	//Do the VolumeForce Calculation
	VolumeForce[sc.Index] = VolumeFiltered[sc.Index] * ScalingFactor * (float)Trend * In_OutputMultiplier.GetFloat();
	
	//Fast moving average.
	sc.MovingAverage(VolumeForce, KVOFast, In_KVOFastSlowSmoothingMAType.GetMovAvgType(), In_KVOFastSmoothingPeriod.GetInt() );
	//Slow moving average.
	sc.MovingAverage(VolumeForce, KVOSlow, In_KVOFastSlowSmoothingMAType.GetMovAvgType(), In_KVOSlowSmoothingPeriod.GetInt() );
	
	//Generate the KVO value.
	KVO[sc.Index] = KVOFast[sc.Index] - KVOSlow[sc.Index];
	
	//Handle KVO extra smoothing.
	if( In_KVOSetExtraSmoothing.GetYesNo() ) {
		sc.MovingAverage(KVO, KVOSmoothed, In_KVOExtraSmoothingMAType.GetMovAvgType(), In_KVOExtraSmoothingPeriod.GetInt() );
		Graph_KVO[sc.Index] = KVOSmoothed[sc.Index];
		}
	else {
		Graph_KVO[sc.Index] = KVO[sc.Index];
		}
		
	//KVO Trigger line.
	sc.MovingAverage(Graph_KVO, Graph_KVOTrigger, In_KVOTriggerSmoothingMAType.GetMovAvgType(), In_KVOTriggerSmoothingPeriod.GetInt() );
	
	//KVO Histogram.
	Graph_Histogram[sc.Index] = Graph_KVO[sc.Index] - Graph_KVOTrigger[sc.Index];
}

/* =============================================================================
================================================================================
Tool: Lines 5
================================================================================
============================================================================= */
SCSFExport scsf_Lines5(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_Line1 = sc.Subgraph[0];
	SCSubgraphRef Graph_Line2 = sc.Subgraph[1];
	SCSubgraphRef Graph_Line3 = sc.Subgraph[2];
	SCSubgraphRef Graph_Line4 = sc.Subgraph[3];
	SCSubgraphRef Graph_Line5 = sc.Subgraph[4];
	SCInputRef In_Line1Level = sc.Input[0];
	SCInputRef In_Line2Level = sc.Input[1];
	SCInputRef In_Line3Level = sc.Input[2];
	SCInputRef In_Line4Level = sc.Input[3];
	SCInputRef In_Line5Level = sc.Input[4];

	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Tool: Lines 5";
		
		sc.StudyVersion = 1.2;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = VALUEFORMAT_INHERITED; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Lines 5. Draws 5 horizontal lines across a subgraph. This is mainly useful when multiple indicators will be on one subgraph. This will create a fixed scale and a place holder for the subgraph. This also allows for graphs stacked on top of each other to be seen easier if those graphs have lines which could then be turned off to avoid overlapping. Be sure to change the graph scale of any indicators added on top.";
		
		//Output Graphs
		
		Graph_Line1.Name = "Line 1"; //drawn graphs must have a name.
		Graph_Line1.PrimaryColor = RGB(128, 128, 128);
		Graph_Line1.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line1.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line1.LineWidth = 1;
		Graph_Line1.DrawZeros = 1;
		Graph_Line1.DisplayNameValueInWindowsFlags = 0;
		
		Graph_Line2.Name = "Line 2"; //drawn graphs must have a name.
		Graph_Line2.PrimaryColor = RGB(128, 128, 128);
		Graph_Line2.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line2.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line2.LineWidth = 1;
		Graph_Line2.DrawZeros = 1;
		Graph_Line2.DisplayNameValueInWindowsFlags = 0;
		
		Graph_Line3.Name = "Line 3"; //drawn graphs must have a name.
		Graph_Line3.PrimaryColor = RGB(192, 192, 192);
		Graph_Line3.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line3.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line3.LineWidth = 1;
		Graph_Line3.DrawZeros = 1;
		Graph_Line3.DisplayNameValueInWindowsFlags = 0;
		
		Graph_Line4.Name = "Line 4"; //drawn graphs must have a name.
		Graph_Line4.PrimaryColor = RGB(128, 128, 128);
		Graph_Line4.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line4.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line4.LineWidth = 1;
		Graph_Line4.DrawZeros = 1;
		Graph_Line4.DisplayNameValueInWindowsFlags = 0;
		
		Graph_Line5.Name = "Line 5"; //drawn graphs must have a name.
		Graph_Line5.PrimaryColor = RGB(128, 128, 128);
		Graph_Line5.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line5.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line5.LineWidth = 1;
		Graph_Line5.DrawZeros = 1;
		Graph_Line5.DisplayNameValueInWindowsFlags = 0;
		
		//User Inputs
		
		In_Line1Level.Name = "Line 1 Level";
		In_Line1Level.SetFloat(100);
		In_Line1Level.SetDescription("The value number of the line.");
		
		In_Line2Level.Name = "Line 2 Level";
		In_Line2Level.SetFloat(70);
		In_Line2Level.SetDescription("The value number of the line.");
		
		In_Line3Level.Name = "Line 3 Level";
		In_Line3Level.SetFloat(50);
		In_Line3Level.SetDescription("The value number of the line.");
		
		In_Line4Level.Name = "Line 4 Level";
		In_Line4Level.SetFloat(30);
		In_Line4Level.SetDescription("The value number of the line.");
		
		In_Line5Level.Name = "Line 5 Level";
		In_Line5Level.SetFloat(0);
		In_Line5Level.SetDescription("The value number of the line.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	Graph_Line1[sc.Index] = In_Line1Level.GetFloat();
	Graph_Line2[sc.Index] = In_Line2Level.GetFloat();
	Graph_Line3[sc.Index] = In_Line3Level.GetFloat();
	Graph_Line4[sc.Index] = In_Line4Level.GetFloat();
	Graph_Line5[sc.Index] = In_Line5Level.GetFloat();
}

/* =============================================================================
================================================================================
Money Flow Index With Filters
================================================================================
============================================================================= */
SCSFExport scsf_MoneyFlowIndexWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_MFI = sc.Subgraph[0];
	SCInputRef In_MFIPeriod = sc.Input[0];
	SCInputRef In_InputData = sc.Input[1];
	SCInputRef In_PriceSetSmoothing = sc.Input[2];
	SCInputRef In_PriceSmoothingPeriod = sc.Input[3];
	SCInputRef In_PriceSmoothingMAType = sc.Input[4];
	SCInputRef In_VolumeFilterType = sc.Input[5];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[6];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[7];
	SCInputRef In_MFISetSmoothing = sc.Input[8];
	SCInputRef In_MFISmoothingPeriod = sc.Input[9];
	SCInputRef In_MFISmoothingMAType = sc.Input[10];
	SCSubgraphRef Price = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[3];
	SCSubgraphRef MFI = sc.Subgraph[4];
	//SCFloatArrayRef FloatArray = Graph_MFI.Arrays[0];

	//remember local variables are not persistent.
	int i, j, Period;
	float TypicalPrice, TypicalPricePrevious, MFPositive, MFNegative, MFTotal;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Money Flow Index With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 1; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Money Flow Index With Filters. This version includes a number of extras to help clean up the graph and make it easier to integrate with automation. The \"Set Price Smoothing?\" option enables cleaning up the price before calculations. If price is really noisy, recommended settings are EMA 3-10. Otherwise leave price smoothing off. The \"Set MFI Smoothing?\" option enables cleaning up some of the MFI noise after the calculation. It is recommended to smooth MFI out with an EMA 3-7.\
<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.\
<p>To use traditional MFI, turn off all smoothing and filtering options.";

		//Output Graph
		Graph_MFI.Name = "MFI"; //drawn graphs must have a name.
		Graph_MFI.PrimaryColor = RGB(0, 255, 0);
		Graph_MFI.DrawStyle = DRAWSTYLE_LINE;
		Graph_MFI.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MFI.LineWidth = 2;
		Graph_MFI.DrawZeros = 1;
		
		//User Inputs
		
		In_MFIPeriod.Name = "MFI Period";
		In_MFIPeriod.SetInt(14);
		In_MFIPeriod.SetIntLimits(3, 300);
		In_MFIPeriod.SetDescription("Number of bars for the period. Useful values are 7 and higher.");
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_HLC); //default to bar close.
		In_InputData.SetDescription("Usually \"HLC Avg\" for Typical Price.");

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
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");	
		
		In_MFISetSmoothing.Name = "Set MFI Smoothing?";
		In_MFISetSmoothing.SetYesNo(1);
		In_MFISetSmoothing.SetDescription("Enables extended MFI smoothing options.");
		
		In_MFISmoothingPeriod.Name = "MFI Smoothing Period";
		In_MFISmoothingPeriod.SetInt(5);
		In_MFISmoothingPeriod.SetIntLimits(2, 50);
		In_MFISmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_MFISmoothingMAType.Name = "MFI Smoothing Moving Average Type";
		In_MFISmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MFISmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");

		return;
		}
	
	// Section 2 - Do data processing here
	
	i = sc.Index; //easier to read traditional C/C++ index i in multiple arrays on one line.
	Period = In_MFIPeriod.GetInt(); //easier to read.
	
	//if first run
	if (i == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period - 1 + (In_PriceSetSmoothing.GetYesNo() ? In_PriceSmoothingPeriod.GetInt() : 0 ) + (In_MFISetSmoothing.GetYesNo() ? In_MFISmoothingPeriod.GetInt() : 0 );
		}

	//Handle price smoothing.
	if( In_PriceSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Price, In_PriceSmoothingMAType.GetMovAvgType(), In_PriceSmoothingPeriod.GetInt() );
		}
	else {
		Price[i] = sc.BaseDataIn[In_InputData.GetInputDataIndex()][i];
		}

	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[i] = (float)sc.Volume[i];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[i] = log( (float)sc.Volume[i] < 1.0 ? 1.0 : (float)sc.Volume[i] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[i] = sqrt( (float)sc.Volume[i] < 1.0 ? 1.0 : (float)sc.Volume[i] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.Volume[i] <= VolumeMA[i]) {VolumeFiltered[i] = (float)sc.Volume[i];} //handle normal volume
		else {VolumeFiltered[i] = (float)VolumeMA[i];} //handle clipped volume
		}

	//Not enough data yet for the MFI calculation.
	if( i < Period ) {return;}
	
	//Do the MFI calculations.
	MFPositive = 0.0;
	MFNegative = 0.0;
	
	//set previous typical price.
	j = i - Period;
	if(j >= 0) {TypicalPricePrevious = Price[j];}
	else {TypicalPricePrevious = 0.0;}
	
	//do the inner loop
	j = i - Period +1;
	if(j < 0) {j = 0;}
	for(; j<=i; j++) {
		TypicalPrice = Price[j];
		if(TypicalPrice == TypicalPricePrevious) {continue;} //nothing to do
		//calculate money flows
		if(TypicalPrice > TypicalPricePrevious) {MFPositive += TypicalPrice * VolumeFiltered[j];}
		else {MFNegative += TypicalPrice * VolumeFiltered[j];}
		TypicalPricePrevious = TypicalPrice;
		}
	
	MFTotal = MFPositive + MFNegative;
	if(MFTotal > 0.0) {MFI[i] = 100.0 * (MFPositive / MFTotal);}
	else { //left with divide by 0 problem or bad negative number
		if(i>0) {MFI[i] = MFI[i-1];} //copy in previous value
		else {MFI[i] = 0.0;} //force it to 0
		}
	
	if( In_MFISetSmoothing.GetYesNo() ) {
		sc.MovingAverage(MFI, Graph_MFI, In_MFISmoothingMAType.GetMovAvgType(), In_MFISmoothingPeriod.GetInt() );
		}
	else {
		Graph_MFI[i] = MFI[i];
		}	
}

/* =============================================================================
================================================================================
Tool: Moving Average Ribbon
================================================================================
============================================================================= */
SCSFExport scsf_MovingAverageRibbon(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_MA5 = sc.Subgraph[0];
	SCSubgraphRef Graph_MA4 = sc.Subgraph[1];
	SCSubgraphRef Graph_MA3 = sc.Subgraph[2];
	SCSubgraphRef Graph_MA2 = sc.Subgraph[3];
	SCSubgraphRef Graph_MA1 = sc.Subgraph[4];
	SCSubgraphRef Graph_MA0 = sc.Subgraph[5];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_SetMARibbon0 = sc.Input[1];
	SCInputRef In_MARibbon0Period = sc.Input[2];
	SCInputRef In_MARibbon0MAType = sc.Input[3];
	SCInputRef In_MARibbonMAType = sc.Input[4];
	SCInputRef In_MARibbon1Period = sc.Input[5];
	SCInputRef In_MARibbon2Period = sc.Input[6];
	SCInputRef In_MARibbon3Period = sc.Input[7];
	SCInputRef In_MARibbon4Period = sc.Input[8];
	SCInputRef In_MARibbon5Period = sc.Input[9];

	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Tool: Moving Average Ribbon";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = VALUEFORMAT_INHERITED; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Moving Average Ribbon. A moving average ribbon is a set of moving average lines of differing values following a single source. That source is usually price but non-oscillating indicators can also have a ribbon attached to them. It is recommended to give the ribbon a lot of screen height to see the movement. Institutional traders do use moving average lines as seen by price lines bending, pausing, and reversing at the standard levels. The Primary Line is usually a small EMA number to closely track the source. If it's not needed, it can be set to another moving average number and type or set to disable. The ribbon lines are usually Simple Moving Averages since that is what the big institutions use. Both moving average types can be changed.<p>The colors chosen are based on light frequency from slow to fast (think of a prism or rainbow). This method makes remembering the values much easier. Industry standard values are red=200, orange=100, yellow=50, green=35, and cyan=20. These can all be changed in the configuration menu.<p>This simple study offers the convenience of setting up 6 MA lines quickly in one place and making sure they are all scaled properly together on the same graph. It also simplifies the setup for automation.";
		
		//sc.GraphRegion = 0; //main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graphs

		Graph_MA0.Name = "Primary Line"; //drawn graphs must have a name.
		Graph_MA0.PrimaryColor = RGB(255, 255, 255);
		Graph_MA0.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA0.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA0.LineWidth = 2;
		Graph_MA0.DrawZeros = 1;
		
		Graph_MA1.Name = "MA1"; //drawn graphs must have a name.
		Graph_MA1.PrimaryColor = RGB(0, 255, 255);
		Graph_MA1.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA1.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA1.LineWidth = 2;
		Graph_MA1.DrawZeros = 1;
		
		Graph_MA2.Name = "MA2"; //drawn graphs must have a name.
		Graph_MA2.PrimaryColor = RGB(0, 255, 0);
		Graph_MA2.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA2.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA2.LineWidth = 2;
		Graph_MA2.DrawZeros = 1;
		
		Graph_MA3.Name = "MA3"; //drawn graphs must have a name.
		Graph_MA3.PrimaryColor = RGB(255, 255, 0);
		Graph_MA3.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA3.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA3.LineWidth = 2;
		Graph_MA3.DrawZeros = 1;
		
		Graph_MA4.Name = "MA4"; //drawn graphs must have a name.
		Graph_MA4.PrimaryColor = RGB(255, 128, 0);
		Graph_MA4.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA4.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA4.LineWidth = 2;
		Graph_MA4.DrawZeros = 1;
		
		Graph_MA5.Name = "MA5"; //drawn graphs must have a name.
		Graph_MA5.PrimaryColor = RGB(255, 0, 0);
		Graph_MA5.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA5.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA5.LineWidth = 2;
		Graph_MA5.DrawZeros = 1;
		
		//User Inputs	
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData.SetDescription("Usually \"Last\" for Close.");
		
		In_SetMARibbon0.Name = "Enable Primary Line?";
		In_SetMARibbon0.SetYesNo(1);
		In_SetMARibbon0.SetDescription("Enables the Primary Line.");
		
		In_MARibbon0Period.Name = "Primary Line Smoothing Period";
		In_MARibbon0Period.SetInt(3);
		In_MARibbon0Period.SetIntLimits(2, 1000);
		In_MARibbon0Period.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_MARibbon0MAType.Name = "Primary Line Moving Average Type";
		In_MARibbon0MAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MARibbon0MAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_MARibbonMAType.Name = "MA Ribbon Moving Average Type";
		In_MARibbonMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_MARibbonMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_MARibbon1Period.Name = "MA Line 1 Period";
		In_MARibbon1Period.SetInt(20);
		In_MARibbon1Period.SetIntLimits(2, 1000);
		In_MARibbon1Period.SetDescription("Number of bars for the period. Usually 20.");
		
		In_MARibbon2Period.Name = "MA Line 2 Period";
		In_MARibbon2Period.SetInt(35);
		In_MARibbon2Period.SetIntLimits(2, 1000);
		In_MARibbon2Period.SetDescription("Number of bars for the period. Usually 35.");
		
		In_MARibbon3Period.Name = "MA Line 3 Period";
		In_MARibbon3Period.SetInt(50);
		In_MARibbon3Period.SetIntLimits(2, 1000);
		In_MARibbon3Period.SetDescription("Number of bars for the period. Usually 50.");
		
		In_MARibbon4Period.Name = "MA Line 4 Period";
		In_MARibbon4Period.SetInt(100);
		In_MARibbon4Period.SetIntLimits(2, 1000);
		In_MARibbon4Period.SetDescription("Number of bars for the period. Usually 100.");
		
		In_MARibbon5Period.Name = "MA Line 5 Period";
		In_MARibbon5Period.SetInt(200);
		In_MARibbon5Period.SetIntLimits(2, 1000);
		In_MARibbon5Period.SetDescription("Number of bars for the period. Usually 200.");

		return;
		}
	
	// Section 2 - Do data processing here
	
	if(sc.Index == 0) {
		//Turn off MA0 if disabled.
		if(In_SetMARibbon0.GetYesNo()) {Graph_MA0.DrawStyle = DRAWSTYLE_LINE;}
		else {Graph_MA0.DrawStyle = DRAWSTYLE_IGNORE;}
		}

	if(In_SetMARibbon0.GetYesNo()) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA0, In_MARibbon0MAType.GetMovAvgType(), In_MARibbon0Period.GetInt() );
		}

	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA1, In_MARibbonMAType.GetMovAvgType(), In_MARibbon1Period.GetInt() );
	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA2, In_MARibbonMAType.GetMovAvgType(), In_MARibbon2Period.GetInt() );
	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA3, In_MARibbonMAType.GetMovAvgType(), In_MARibbon3Period.GetInt() );
	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA4, In_MARibbonMAType.GetMovAvgType(), In_MARibbon4Period.GetInt() );
	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA5, In_MARibbonMAType.GetMovAvgType(), In_MARibbon5Period.GetInt() );
}

/* =============================================================================
================================================================================
OBV: On Balance Volume By Bar With Filters
================================================================================
============================================================================= */
SCSFExport scsf_OBVByBarWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_OBV = sc.Subgraph[0];
	SCInputRef In_VolumeFilterType = sc.Input[0];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[1];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[2];
	SCInputRef In_OBVSetSmoothing = sc.Input[3];
	SCInputRef In_OBVSmoothingPeriod = sc.Input[4];
	SCInputRef In_OBVSmoothingMAType = sc.Input[5];
	SCSubgraphRef OBV = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	//SCFloatArrayRef FloatArray = Graph_OBV.Arrays[0];
	
	//remember local variables are not persistent.
	float Balance;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "OBV: On Balance Volume By Bar With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 2; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume By Bar With Filters. Traditional OBV is calculated by comparing the previous bar with the current. This creates an offset problem. When watching a live graph, the current price and current volume happen together, not offset by 1. This OBV version fixes that. An up bar increases the balance. A down bar decreases the balance. A bar with an open equal to close does nothing. Note that true OBV requires tick by tick data, so if you have it, use it. This algorithm estimates OBV from data by the bar. Like all algorithms of this type, it is not 100% accurate and subject to manipulation by large institutions.\
<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.\
<p>Observations. The various volume filters are very effective and will walk right through the volume spike bar hardly noticing it. The volume filters also tend to minimize errant graph changes.\
<p>When using one of the volume filters, it is necessary to have the first OBV instance running in \"Straight\" mode. Add the second OBV instance to the same graph with \"Independent Scaling\". This is important because the filtered bars tend to drift in value with smaller volume bars. While this drift will show the OBV bias direction, it will not do it to scale and may cause false signals. The \"Straight\" instance will be used to verify actual distance moved. Note that Log tends to drift the most (sometimes offering an early indicator), followed by Square Root and then MA Clip. To learn the movement characteristics of each, put them all on one chart for equal comparison.<p>Take note when all OBV lines pivot in the same direction. This tends to indicate a change with strength.";
		
		//Output Graph
		Graph_OBV.Name = "OBVBar"; //drawn graphs must have a name.
		Graph_OBV.PrimaryColor = RGB(255, 0, 255);
		Graph_OBV.DrawStyle = DRAWSTYLE_LINE;
		Graph_OBV.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_OBV.LineWidth = 2;
		Graph_OBV.DrawZeros = 1;
		
		//User Inputs
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_OBVSetSmoothing.Name = "Set OBV Smoothing?";
		In_OBVSetSmoothing.SetYesNo(1);
		In_OBVSetSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_OBVSmoothingPeriod.Name = "OBV Smoothing Period";
		In_OBVSmoothingPeriod.SetInt(7);
		In_OBVSmoothingPeriod.SetIntLimits(2, 50);
		In_OBVSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_OBVSmoothingMAType.Name = "OBV Smoothing Moving Average Type";
		In_OBVSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_OBVSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = (In_OBVSetSmoothing.GetYesNo() ? In_OBVSmoothingPeriod.GetInt() : 0 );
		//local variable
		Balance = 0.0;
		}
	
	//Reload Balance with previous value. Much easier to read this way.
	if(sc.Index >= 1) {Balance = OBV[sc.Index -1];}

	//Calculate On Balance Volume type.
	//Note: if(sc.Open[sc.Index] == sc.Close[sc.Index]) then there is nothing to do.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		if(sc.Open[sc.Index] < sc.Close[sc.Index]) {Balance += (float)sc.Volume[sc.Index];} //up bar
		else if(sc.Open[sc.Index] > sc.Close[sc.Index]) {Balance -= (float)sc.Volume[sc.Index];} //down bar
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		if(sc.Open[sc.Index] < sc.Close[sc.Index]) {Balance += log( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );} //up bar
		else if(sc.Open[sc.Index] > sc.Close[sc.Index]) {Balance -= log( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );} //down bar
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		if(sc.Open[sc.Index] < sc.Close[sc.Index]) {Balance += sqrt( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );} //up bar
		else if(sc.Open[sc.Index] > sc.Close[sc.Index]) {Balance -= sqrt( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );} //down bar
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.Volume[sc.Index] <= VolumeMA[sc.Index]) {
			if(sc.Open[sc.Index] < sc.Close[sc.Index]) {Balance += (float)sc.Volume[sc.Index];} //up bar
			else if(sc.Open[sc.Index] > sc.Close[sc.Index]) {Balance -= (float)sc.Volume[sc.Index];} //down bar
			}
		//handle clipped volume
		else {
			if(sc.Open[sc.Index] < sc.Close[sc.Index]) {Balance += (float)VolumeMA[sc.Index];} //up bar
			else if(sc.Open[sc.Index] > sc.Close[sc.Index]) {Balance -= (float)VolumeMA[sc.Index];} //down bar
			}
		}
	OBV[sc.Index] = Balance;
	
	//Handle smoothing.
	if( In_OBVSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBV, Graph_OBV, In_OBVSmoothingMAType.GetMovAvgType(), In_OBVSmoothingPeriod.GetInt() );
		}
	else {
		Graph_OBV[sc.Index] = OBV[sc.Index];
		}
}

/* =============================================================================
================================================================================
OBV: On Balance Volume By Percent Bar With Filters
================================================================================
============================================================================= */
SCSFExport scsf_OBVByPercentBarWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_OBV = sc.Subgraph[0];
	SCInputRef In_VolumeFilterType = sc.Input[0];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[1];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[2];
	SCInputRef In_OBVSetSmoothing = sc.Input[3];
	SCInputRef In_OBVSmoothingPeriod = sc.Input[4];
	SCInputRef In_OBVSmoothingMAType = sc.Input[5];
	SCSubgraphRef OBV = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	//SCFloatArrayRef FloatArray = Graph_OBV.Arrays[0];
	
	//remember local variables are not persistent.
	int i;
	float Balance, VolumeScale, VolumeUp, VolumeDown;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "OBV: On Balance Volume By Percent Bar With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 2; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume By Percent Bar With Filters. Traditional OBV is calculated by comparing the previuos bar with the current. This creates an offset problem. When watching a live graph, the current price and current volume happen together, not offset by 1. This OBV version fixes that and adds a percent scale. The scale splits the bar based on where close is within the high to low range. A close in the middle does nothing. A close below middle subtracts more from the balance than it adds. A close above middle adds more to the balance than it subtracts. Note that true OBV requires tick by tick data, so if you have it, use it. This algorithm estimates OBV from data by the bar. Like all algorithms of this type, it is not 100% accurate and subject to manipulation by large institutions.\
<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.\
<p>Observations. The various volume filters are very effective and will walk right through the volume spike bar hardly noticing it. The volume filters also tend to minimize errant graph changes.\
<p>When using one of the volume filters, it is necessary to have the first OBV instance running in \"Straight\" mode. Add the second OBV instance to the same graph with \"Independent Scaling\". This is important because the filtered bars tend to drift in value with smaller volume bars. While this drift will show the OBV bias direction, it will not do it to scale and may cause false signals. The \"Straight\" instance will be used to verify actual distance moved. Note that Log tends to drift the most (sometimes offering an early indicator), followed by Square Root and then MA Clip. To learn the movement characteristics of each, put them all on one chart for equal comparison.\
<p>Take note when all OBV lines pivot in the same direction. This tends to indicate a change with strength.";

		//Output Graph
		Graph_OBV.Name = "OBVPctBar"; //drawn graphs must have a name.
		Graph_OBV.PrimaryColor = RGB(255, 0, 255);
		Graph_OBV.DrawStyle = DRAWSTYLE_LINE;
		Graph_OBV.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_OBV.LineWidth = 2;
		Graph_OBV.DrawZeros = 1;
		
		//User Inputs
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_OBVSetSmoothing.Name = "Set OBV Smoothing?";
		In_OBVSetSmoothing.SetYesNo(1);
		In_OBVSetSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_OBVSmoothingPeriod.Name = "OBV Smoothing Period";
		In_OBVSmoothingPeriod.SetInt(7);
		In_OBVSmoothingPeriod.SetIntLimits(2, 50);
		In_OBVSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_OBVSmoothingMAType.Name = "OBV Smoothing Moving Average Type";
		In_OBVSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_OBVSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	//initialize local variables.
	i = sc.Index; //easier to read traditional C/C++ index i in multiple arrays on one line.
	VolumeUp = 0.0;
	VolumeDown = 0.0;
	
	//if first run. Set persistent variables here.
	if(i == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = (In_OBVSetSmoothing.GetYesNo() ? In_OBVSmoothingPeriod.GetInt() : 0 );
		//local variable
		Balance = 0.0;
		//Safety: Handle a very rare case where there is volume on the first bar but the bar is flat.
		//This can also help filter out bad data.
		if( (sc.High[i] == sc.Low[i]) && (sc.Volume[i] != 0) ) {
			//split volume in half with no previous data to go on.
			VolumeUp = (float)sc.Volume[i] / 2.0;
			VolumeDown = (float)sc.Volume[i] - VolumeUp;
			}
		}
	
	if(i >= 1) {
		//Reload Balance with previous value. Much easier to read this way.
		Balance = OBV[i-1];
		//Safety: Handle a very rare case where price jumps but the bar is flat.
		//Split volume based on previous movement.
		//This can also help filter out bad data.
		if( (sc.High[i] == sc.Low[i]) && (sc.Volume[i] != 0) ) {
			//if previous==current, split volume in half
			if(sc.Close[i-1] == sc.Close[i]) {
				VolumeUp = (float)sc.Volume[i] / 2.0;
				VolumeDown = (float)sc.Volume[i] - VolumeUp;
				}
			//up bar
			else if(sc.Close[i-1] < sc.Close[i]) {
				VolumeUp = (float)sc.Volume[i];
				VolumeDown = 0.0;
				}
			//down bar
			else {
				VolumeUp = 0.0;
				VolumeDown = (float)sc.Volume[i];
				}
			} //end if flat bar
		} //end if(sc.Index>=1)
	
	//Do the normal percent split calculations.
	if((sc.High[i] != sc.Low[i]) && sc.Volume[i] != 0) {
		VolumeUp = (float)sc.Volume[i] * ((sc.Close[i] - sc.Low[i]) / (sc.High[i] - sc.Low[i]));
		VolumeDown = (float)sc.Volume[i] - VolumeUp;
		}
	
	//Nothing to calculate if volume is 0.
	if(sc.Volume[i] == 0) {
		VolumeUp = 0.0;
		VolumeDown = 0.0;
		}
	
	
	//Calculate On Balance Volume filter type.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		Balance += VolumeUp;
		Balance -= VolumeDown;
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		Balance += log( VolumeUp < 1.0 ? 1.0 : VolumeUp );
		Balance -= log( VolumeDown < 1.0 ? 1.0 : VolumeDown );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		Balance += sqrt( VolumeUp < 1.0 ? 1.0 : VolumeUp );
		Balance -= sqrt( VolumeDown < 1.0 ? 1.0 : VolumeDown );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.Volume[i] <= VolumeMA[i]) {
			Balance += VolumeUp;
			Balance -= VolumeDown;
			}
		//handle clipped volume
		else {
			VolumeScale = (float)VolumeMA[i] / (float)sc.Volume[i];
			Balance += VolumeScale * VolumeUp;
			Balance -= VolumeScale * VolumeDown;
			}
		}
	OBV[i] = Balance;
	
	//Handle smoothing.
	if( In_OBVSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBV, Graph_OBV, In_OBVSmoothingMAType.GetMovAvgType(), In_OBVSmoothingPeriod.GetInt() );
		}
	else {
		Graph_OBV[i] = OBV[i];
		}
}

/* =============================================================================
================================================================================
OBV: On Balance Volume By Tick MACD With Filters
================================================================================
============================================================================= */
SCSFExport scsf_OBVByTickMACDWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_Zero = sc.Subgraph[0];
	SCSubgraphRef Graph_OBVMACDHist = sc.Subgraph[1];
	SCSubgraphRef Graph_OBVMACDSignal = sc.Subgraph[2];
	SCSubgraphRef Graph_OBVMACD = sc.Subgraph[3];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_VolumeFilterType = sc.Input[1];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[2];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[3];
	SCInputRef In_OBVSetSmoothing = sc.Input[4];
	SCInputRef In_OBVSmoothingPeriod = sc.Input[5];
	SCInputRef In_OBVSmoothingMAType = sc.Input[6];
	SCInputRef In_MACDFastPeriod = sc.Input[7];
	SCInputRef In_MACDSlowPeriod = sc.Input[8];
	SCInputRef In_MACDMAType = sc.Input[9];
	SCInputRef In_MACDSignalPeriod = sc.Input[10];
	SCInputRef In_MACDSignalMAType = sc.Input[11];
	SCSubgraphRef OBV = sc.Subgraph[4];
	SCSubgraphRef VolumeMA = sc.Subgraph[5];
	SCSubgraphRef OBVSmoothed = sc.Subgraph[6];
	SCSubgraphRef MACDFast = sc.Subgraph[7];
	SCSubgraphRef MACDSlow = sc.Subgraph[8];
	//SCFloatArrayRef FloatArray = Graph_OBVMACD.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	float Balance, VolumeScale;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "OBV: On Balance Volume By Tick MACD With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 4; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume By Tick MACD With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>OBV acts similar for volume for what price does on the main chart. OBV is first calculated and then a MACD is taken of it. Using MACD as a measurement of volume movement gives clues to when volume has moved too far and will stop or reverse. Reading OBV MACD is very similar to reading price MACD. Volume movements affect price, and when volume stops, so does price. For a more complete picture, it is recommended to combine this indicator with OBV By Tick using the MA Ribbon option, OBV By Tick RSI, Intraday Intensity Oscillator By Tick, and Up/Down Volume Difference By Tick. Accurate volume measurement by tick is crucial to seeing what the market is doing under the hood.\
<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.\
<p>Observations. The various volume filters are very effective and will walk right through the volume spike bar hardly noticing it. The volume filters also tend to minimize errant graph changes.\
<p>Setting the MACD periods too small will just give a lot of false crossover signals. My personal preferences are 15,80,10 to capture the overall movement.";
		
		//Output Graph
		Graph_OBVMACD.Name = "OBVtickMACD"; //drawn graphs must have a name.
		Graph_OBVMACD.PrimaryColor = RGB(0, 0, 255);
		Graph_OBVMACD.DrawStyle = DRAWSTYLE_LINE;
		Graph_OBVMACD.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_OBVMACD.LineWidth = 1;
		Graph_OBVMACD.DrawZeros = 1;
		
		Graph_OBVMACDSignal.Name = "OBVtickMACDSignal"; //drawn graphs must have a name.
		Graph_OBVMACDSignal.PrimaryColor = RGB(255, 0, 0);
		Graph_OBVMACDSignal.DrawStyle = DRAWSTYLE_LINE;
		Graph_OBVMACDSignal.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_OBVMACDSignal.LineWidth = 1;
		Graph_OBVMACDSignal.DrawZeros = 1;
		
		Graph_OBVMACDHist.Name = "OBVtickMACDHist"; //drawn graphs must have a name.
		Graph_OBVMACDHist.PrimaryColor = RGB(0, 255, 0);
		Graph_OBVMACDHist.DrawStyle = DRAWSTYLE_BAR;
		Graph_OBVMACDHist.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_OBVMACDHist.LineWidth = 2;
		Graph_OBVMACDHist.DrawZeros = 1;
		
		Graph_Zero.Name = "Zero"; //drawn graphs must have a name.
		Graph_Zero.PrimaryColor = RGB(0, 255, 0);
		Graph_Zero.DrawStyle = DRAWSTYLE_LINE;
		Graph_Zero.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Zero.LineWidth = 1;
		Graph_Zero.DrawZeros = 1;
		
		//User Inputs
		
		In_InputData.Name = "Input Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");

		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_OBVSetSmoothing.Name = "Set OBV Smoothing?";
		In_OBVSetSmoothing.SetYesNo(1);
		In_OBVSetSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_OBVSmoothingPeriod.Name = "OBV Smoothing Period";
		In_OBVSmoothingPeriod.SetInt(7);
		In_OBVSmoothingPeriod.SetIntLimits(2, 50);
		In_OBVSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_OBVSmoothingMAType.Name = "OBV Smoothing Moving Average Type";
		In_OBVSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_OBVSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_MACDFastPeriod.Name = "MACD Fast Period";
		In_MACDFastPeriod.SetInt(12);
		In_MACDFastPeriod.SetIntLimits(3, 100);
		In_MACDFastPeriod.SetDescription("Number of bars for the period. Useful values are 10 and higher.");
		
		In_MACDSlowPeriod.Name = "MACD Slow Period";
		In_MACDSlowPeriod.SetInt(26);
		In_MACDSlowPeriod.SetIntLimits(3, 100);
		In_MACDSlowPeriod.SetDescription("Number of bars for the period. Useful values are 26 and higher.");
		
		In_MACDMAType.Name = "MACD Moving Average Type";
		In_MACDMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_MACDMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_MACDSignalPeriod.Name = "MACD Signal Line Period";
		In_MACDSignalPeriod.SetInt(9);
		In_MACDSignalPeriod.SetIntLimits(3, 100);
		In_MACDSignalPeriod.SetDescription("Number of bars for the period. Useful values are 9 and higher.");
		
		In_MACDSignalMAType.Name = "MACD Signal Line Moving Average Type";
		In_MACDSignalMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_MACDSignalMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		//Make sure fast is smaller than slow.
		if(In_MACDFastPeriod.GetInt() > In_MACDSlowPeriod.GetInt() ) {
			Up = In_MACDSlowPeriod.GetInt();
			In_MACDSlowPeriod.SetInt(In_MACDFastPeriod.GetInt() );
			In_MACDFastPeriod.SetInt(Up);
			}
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = (In_OBVSetSmoothing.GetYesNo() ? In_OBVSmoothingPeriod.GetInt() : 0) + In_MACDSlowPeriod.GetInt() + In_MACDSignalPeriod.GetInt();
		//local variable
		Balance = 0.0;
		}
	
	//Reload Balance with previous value. Much easier to read this way.
	if(sc.Index >= 1) {Balance = OBV[sc.Index -1];}

	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}
	
	//Calculate On Balance Volume filter type.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		Balance += (float)sc.BaseData[Up][sc.Index];
		Balance -= (float)sc.BaseData[Down][sc.Index];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		Balance += log( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= log( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		Balance += sqrt( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= sqrt( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.BaseData[VolumeType][sc.Index] <= VolumeMA[sc.Index]) {
			Balance += (float)sc.BaseData[Up][sc.Index];
			Balance -= (float)sc.BaseData[Down][sc.Index];
			}
		//handle clipped volume
		else {
			VolumeScale = (float)VolumeMA[sc.Index] / (float)sc.BaseData[VolumeType][sc.Index];
			Balance += VolumeScale * (float)sc.BaseData[Up][sc.Index];
			Balance -= VolumeScale * (float)sc.BaseData[Down][sc.Index];
			}
		}
	OBV[sc.Index] = Balance;
	
	//Handle smoothing.
	if( In_OBVSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBV, OBVSmoothed, In_OBVSmoothingMAType.GetMovAvgType(), In_OBVSmoothingPeriod.GetInt() );
		}
	else {
		OBVSmoothed[sc.Index] = OBV[sc.Index];
		}
	
	//Generate OBV MACD
	Graph_Zero[sc.Index] = 0.0;
	sc.MovingAverage(OBVSmoothed, MACDFast, In_MACDMAType.GetMovAvgType(), In_MACDFastPeriod.GetInt() );
	sc.MovingAverage(OBVSmoothed, MACDSlow, In_MACDMAType.GetMovAvgType(), In_MACDSlowPeriod.GetInt() );
	Graph_OBVMACD[sc.Index] = MACDFast[sc.Index] - MACDSlow[sc.Index];
	sc.MovingAverage(Graph_OBVMACD, Graph_OBVMACDSignal, In_MACDSignalMAType.GetMovAvgType(), In_MACDSignalPeriod.GetInt() );
	Graph_OBVMACDHist[sc.Index] = Graph_OBVMACD[sc.Index] - Graph_OBVMACDSignal[sc.Index];
}

/* =============================================================================
================================================================================
OBV: On Balance Volume By Tick RSI With Filters
================================================================================
============================================================================= */
SCSFExport scsf_OBVByTickRSIWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_OBVRSI = sc.Subgraph[0];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_VolumeFilterType = sc.Input[1];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[2];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[3];
	SCInputRef In_OBVSetSmoothing = sc.Input[4];
	SCInputRef In_OBVSmoothingPeriod = sc.Input[5];
	SCInputRef In_OBVSmoothingMAType = sc.Input[6];
	SCInputRef In_RSIPeriod = sc.Input[7];
	SCInputRef In_RSICalcMAType = sc.Input[8];
	SCInputRef In_RSISetSmoothing = sc.Input[9];
	SCInputRef In_RSISmoothingPeriod = sc.Input[10];
	SCInputRef In_RSISmoothingMAType = sc.Input[11];
	SCSubgraphRef OBV = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	SCSubgraphRef OBVSmoothed = sc.Subgraph[3];
	SCSubgraphRef OBVRSI = sc.Subgraph[4];
	//SCFloatArrayRef FloatArray = Graph_OBVRSI.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	float Balance, VolumeScale;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "OBV: On Balance Volume By Tick RSI With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 0; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume By Tick RSI With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>OBV acts similar for volume for what price does on the main chart. OBV is first calculated and then an RSI is taken of it. Using RSI as a measurement of volume movement gives clues to when volume has moved too far and will stop or reverse. Reading OBV RSI is very similar to reading price RSI. Volume movements affect price, and when volume stops, so does price. For a more complete picture, it is recommended to combine this indicator with OBV By Tick using the MA Ribbon option, OBV By Tick MACD, Intraday Intensity Oscillator By Tick, and Up/Down Volume Difference By Tick. Accurate volume measurement by tick is crucial to seeing what the market is doing under the hood.\
<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.\
<p>This RSI version has recommended extra smoothing options to help take the noise out of the RSI line.\
<p>Observations. The various volume filters are very effective and will walk right through the volume spike bar hardly noticing it. The volume filters also tend to minimize errant graph changes.\
<p>Volume tends to have longer runs than price. Setting the RSI period too small will just smash the indicator during these long runs.";
		
		//Output Graph
		Graph_OBVRSI.Name = "OBVtickRSI"; //drawn graphs must have a name.
		Graph_OBVRSI.PrimaryColor = RGB(255, 0, 0);
		Graph_OBVRSI.DrawStyle = DRAWSTYLE_LINE;
		Graph_OBVRSI.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_OBVRSI.LineWidth = 1;
		Graph_OBVRSI.DrawZeros = 1;
		
		//User Inputs
		
		In_InputData.Name = "Input Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");

		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_OBVSetSmoothing.Name = "Set OBV Smoothing?";
		In_OBVSetSmoothing.SetYesNo(1);
		In_OBVSetSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_OBVSmoothingPeriod.Name = "OBV Smoothing Period";
		In_OBVSmoothingPeriod.SetInt(7);
		In_OBVSmoothingPeriod.SetIntLimits(2, 50);
		In_OBVSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_OBVSmoothingMAType.Name = "OBV Smoothing Moving Average Type";
		In_OBVSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_OBVSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_RSIPeriod.Name = "RSI Period";
		In_RSIPeriod.SetInt(15);
		In_RSIPeriod.SetIntLimits(3, 100);
		In_RSIPeriod.SetDescription("Number of bars for the period. Useful values are 10 and higher.");
		
		In_RSICalcMAType.Name = "RSI Calculation Moving Average Type";
		In_RSICalcMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_RSICalcMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_RSISetSmoothing.Name = "Set RSI Smoothing?";
		In_RSISetSmoothing.SetYesNo(1);
		In_RSISetSmoothing.SetDescription("Enables extended RSI smoothing options.");
		
		In_RSISmoothingPeriod.Name = "RSI Smoothing Period";
		In_RSISmoothingPeriod.SetInt(7);
		In_RSISmoothingPeriod.SetIntLimits(2, 50);
		In_RSISmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_RSISmoothingMAType.Name = "RSI Smoothing Moving Average Type";
		In_RSISmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_RSISmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = (In_OBVSetSmoothing.GetYesNo() ? In_OBVSmoothingPeriod.GetInt() : 0) + In_RSIPeriod.GetInt() + (In_RSISetSmoothing.GetYesNo() ? In_RSISmoothingPeriod.GetInt() : 0);
		//local variable
		Balance = 0.0;
		}
	
	//Reload Balance with previous value. Much easier to read this way.
	if(sc.Index >= 1) {Balance = OBV[sc.Index -1];}

	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}
	
	//Calculate On Balance Volume filter type.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		Balance += (float)sc.BaseData[Up][sc.Index];
		Balance -= (float)sc.BaseData[Down][sc.Index];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		Balance += log( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= log( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		Balance += sqrt( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= sqrt( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.BaseData[VolumeType][sc.Index] <= VolumeMA[sc.Index]) {
			Balance += (float)sc.BaseData[Up][sc.Index];
			Balance -= (float)sc.BaseData[Down][sc.Index];
			}
		//handle clipped volume
		else {
			VolumeScale = (float)VolumeMA[sc.Index] / (float)sc.BaseData[VolumeType][sc.Index];
			Balance += VolumeScale * (float)sc.BaseData[Up][sc.Index];
			Balance -= VolumeScale * (float)sc.BaseData[Down][sc.Index];
			}
		}
	OBV[sc.Index] = Balance;
	
	//Handle smoothing.
	if( In_OBVSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBV, OBVSmoothed, In_OBVSmoothingMAType.GetMovAvgType(), In_OBVSmoothingPeriod.GetInt() );
		}
	else {
		OBVSmoothed[sc.Index] = OBV[sc.Index];
		}

	//generate RSI.
	sc.RSI(OBVSmoothed, OBVRSI, In_RSICalcMAType.GetMovAvgType(), In_RSIPeriod.GetInt() );
	
	//handle final smoothing.
	if( In_RSISetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBVRSI, Graph_OBVRSI, In_RSISmoothingMAType.GetMovAvgType(), In_RSISmoothingPeriod.GetInt() );
		}
	else {
		Graph_OBVRSI[sc.Index] = OBVRSI[sc.Index];
		}
}

/* =============================================================================
================================================================================
OBV: On Balance Volume By Tick With Filters
================================================================================
============================================================================= */
SCSFExport scsf_OBVByTickWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_MA5 = sc.Subgraph[0];
	SCSubgraphRef Graph_MA4 = sc.Subgraph[1];
	SCSubgraphRef Graph_MA3 = sc.Subgraph[2];
	SCSubgraphRef Graph_MA2 = sc.Subgraph[3];
	SCSubgraphRef Graph_MA1 = sc.Subgraph[4];
	SCSubgraphRef Graph_OBV = sc.Subgraph[5];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_VolumeFilterType = sc.Input[1];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[2];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[3];
	SCInputRef In_OBVSetSmoothing = sc.Input[4];
	SCInputRef In_OBVSmoothingPeriod = sc.Input[5];
	SCInputRef In_OBVSmoothingMAType = sc.Input[6];
	SCInputRef In_SetMARibbon = sc.Input[7];
	SCInputRef In_MARibbonMAType = sc.Input[8];
	SCInputRef In_MARibbon1Period = sc.Input[9];
	SCInputRef In_MARibbon2Period = sc.Input[10];
	SCInputRef In_MARibbon3Period = sc.Input[11];
	SCInputRef In_MARibbon4Period = sc.Input[12];
	SCInputRef In_MARibbon5Period = sc.Input[13];
	SCSubgraphRef OBV = sc.Subgraph[6];
	SCSubgraphRef VolumeMA = sc.Subgraph[7];
	//SCFloatArrayRef FloatArray = Graph_OBV.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	float Balance, VolumeScale;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "OBV: On Balance Volume By Tick With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 2; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>This OBV version adds a moving average ribbon to help quantify the moves. Reading the ribbon is the same as if the ribbon was attached to a price line. If the ribbon is enabled, it is recommended to give it a lot of screen height to see the movement. Adding it to a second chart may be a better option. Institutional traders do use moving average lines as seen by the OBV line bending, pausing, and reversing at the standard levels. The colors chosen are based on light frequency from slow to fast (think of a prism or rainbow). This method makes remembering the values much easier. Standard values are red=200, orange=100, yellow=50, green=35, and cyan=20. These can all be changed in the configuration menu.\
<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.\
<p>Observations. The various volume filters are very effective and will walk right through the volume spike bar hardly noticing it. The volume filters also tend to minimize errant graph changes.\
<p>When using one of the volume filters, it is necessary to have the first OBV instance running in \"Straight\" mode. Add the second OBV instance to the same graph with \"Independent Scaling\". This is important because the filtered bars tend to drift in value with smaller volume bars. While this drift will show the OBV bias direction, it will not do it to scale and may cause false signals. The \"Straight\" instance will be used to verify actual distance moved. Note that Log tends to drift the most (sometimes offering an early indicator), followed by Square Root and then MA Clip. To learn the movement characteristics of each, put them all on one chart for equal comparison.\
<p>Take note when all OBV lines pivot in the same direction. This tends to indicate a change with strength.";

		//Output Graph
		Graph_OBV.Name = "OBVTick"; //drawn graphs must have a name.
		Graph_OBV.PrimaryColor = RGB(255, 0, 255);
		Graph_OBV.DrawStyle = DRAWSTYLE_LINE;
		Graph_OBV.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_OBV.LineWidth = 2;
		Graph_OBV.DrawZeros = 1;
		
		Graph_MA1.Name = "MA1"; //drawn graphs must have a name.
		Graph_MA1.PrimaryColor = RGB(0, 255, 255);
		Graph_MA1.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA1.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA1.LineWidth = 2;
		Graph_MA1.DrawZeros = 1;
		
		Graph_MA2.Name = "MA2"; //drawn graphs must have a name.
		Graph_MA2.PrimaryColor = RGB(0, 255, 0);
		Graph_MA2.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA2.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA2.LineWidth = 2;
		Graph_MA2.DrawZeros = 1;
		
		Graph_MA3.Name = "MA3"; //drawn graphs must have a name.
		Graph_MA3.PrimaryColor = RGB(255, 255, 0);
		Graph_MA3.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA3.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA3.LineWidth = 2;
		Graph_MA3.DrawZeros = 1;
		
		Graph_MA4.Name = "MA4"; //drawn graphs must have a name.
		Graph_MA4.PrimaryColor = RGB(255, 128, 0);
		Graph_MA4.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA4.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA4.LineWidth = 2;
		Graph_MA4.DrawZeros = 1;
		
		Graph_MA5.Name = "MA5"; //drawn graphs must have a name.
		Graph_MA5.PrimaryColor = RGB(255, 0, 0);
		Graph_MA5.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA5.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA5.LineWidth = 2;
		Graph_MA5.DrawZeros = 1;
		
		//User Inputs
		
		In_InputData.Name = "Input Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");

		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_OBVSetSmoothing.Name = "Set OBV Smoothing?";
		In_OBVSetSmoothing.SetYesNo(1);
		In_OBVSetSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_OBVSmoothingPeriod.Name = "OBV Smoothing Period";
		In_OBVSmoothingPeriod.SetInt(7);
		In_OBVSmoothingPeriod.SetIntLimits(2, 50);
		In_OBVSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_OBVSmoothingMAType.Name = "OBV Smoothing Moving Average Type";
		In_OBVSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_OBVSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_SetMARibbon.Name = "Enable Moving Average Ribbon?";
		In_SetMARibbon.SetYesNo(1);
		In_SetMARibbon.SetDescription("Enables extended moving average ribbon option.");
		
		In_MARibbonMAType.Name = "MA Ribbon Moving Average Type";
		In_MARibbonMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_MARibbonMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_MARibbon1Period.Name = "MA Line 1 Period";
		In_MARibbon1Period.SetInt(20);
		In_MARibbon1Period.SetIntLimits(2, 500);
		In_MARibbon1Period.SetDescription("Number of bars for the period. Usually 20.");
		
		In_MARibbon2Period.Name = "MA Line 2 Period";
		In_MARibbon2Period.SetInt(35);
		In_MARibbon2Period.SetIntLimits(2, 500);
		In_MARibbon2Period.SetDescription("Number of bars for the period. Usually 35.");
		
		In_MARibbon3Period.Name = "MA Line 3 Period";
		In_MARibbon3Period.SetInt(50);
		In_MARibbon3Period.SetIntLimits(2, 500);
		In_MARibbon3Period.SetDescription("Number of bars for the period. Usually 50.");
		
		In_MARibbon4Period.Name = "MA Line 4 Period";
		In_MARibbon4Period.SetInt(100);
		In_MARibbon4Period.SetIntLimits(2, 500);
		In_MARibbon4Period.SetDescription("Number of bars for the period. Usually 100.");
		
		In_MARibbon5Period.Name = "MA Line 5 Period";
		In_MARibbon5Period.SetInt(200);
		In_MARibbon5Period.SetIntLimits(2, 500);
		In_MARibbon5Period.SetDescription("Number of bars for the period. Usually 200.");

		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = (In_OBVSetSmoothing.GetYesNo() ? In_OBVSmoothingPeriod.GetInt() : 0);
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		if(In_VolumeFilterType.GetIndex() == 0) {sc.ValueFormat = 0;}
		else {sc.ValueFormat = 2;}
		//local variable
		Balance = 0.0;
		//If disabled, the MA lines need to be turned off to keep from messing with the graph.
		if(In_SetMARibbon.GetYesNo()) {
			Graph_MA1.DrawStyle = DRAWSTYLE_LINE;
			Graph_MA2.DrawStyle = DRAWSTYLE_LINE;
			Graph_MA3.DrawStyle = DRAWSTYLE_LINE;
			Graph_MA4.DrawStyle = DRAWSTYLE_LINE;
			Graph_MA5.DrawStyle = DRAWSTYLE_LINE;
			}
		else {
			Graph_MA1.DrawStyle = DRAWSTYLE_IGNORE;
			Graph_MA2.DrawStyle = DRAWSTYLE_IGNORE;
			Graph_MA3.DrawStyle = DRAWSTYLE_IGNORE;
			Graph_MA4.DrawStyle = DRAWSTYLE_IGNORE;
			Graph_MA5.DrawStyle = DRAWSTYLE_IGNORE;
			}
		}
	
	//Reload Balance with previous value. Much easier to read this way.
	if(sc.Index >= 1) {Balance = OBV[sc.Index -1];}

	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}
	
	//Calculate On Balance Volume filter type.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		Balance += (float)sc.BaseData[Up][sc.Index];
		Balance -= (float)sc.BaseData[Down][sc.Index];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		Balance += log( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= log( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		Balance += sqrt( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= sqrt( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.BaseData[VolumeType][sc.Index] <= VolumeMA[sc.Index]) {
			Balance += (float)sc.BaseData[Up][sc.Index];
			Balance -= (float)sc.BaseData[Down][sc.Index];
			}
		//handle clipped volume
		else {
			VolumeScale = (float)VolumeMA[sc.Index] / (float)sc.BaseData[VolumeType][sc.Index];
			Balance += VolumeScale * (float)sc.BaseData[Up][sc.Index];
			Balance -= VolumeScale * (float)sc.BaseData[Down][sc.Index];
			}
		}
	OBV[sc.Index] = Balance;
	
	//Handle smoothing.
	if( In_OBVSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBV, Graph_OBV, In_OBVSmoothingMAType.GetMovAvgType(), In_OBVSmoothingPeriod.GetInt() );
		}
	else {
		Graph_OBV[sc.Index] = OBV[sc.Index];
		}

	if( In_SetMARibbon.GetYesNo() ) {
		sc.MovingAverage(Graph_OBV, Graph_MA1, In_MARibbonMAType.GetMovAvgType(), In_MARibbon1Period.GetInt() );
		sc.MovingAverage(Graph_OBV, Graph_MA2, In_MARibbonMAType.GetMovAvgType(), In_MARibbon2Period.GetInt() );
		sc.MovingAverage(Graph_OBV, Graph_MA3, In_MARibbonMAType.GetMovAvgType(), In_MARibbon3Period.GetInt() );
		sc.MovingAverage(Graph_OBV, Graph_MA4, In_MARibbonMAType.GetMovAvgType(), In_MARibbon4Period.GetInt() );
		sc.MovingAverage(Graph_OBV, Graph_MA5, In_MARibbonMAType.GetMovAvgType(), In_MARibbon5Period.GetInt() );
		}
}

/* =============================================================================
================================================================================
OBVPM: On Balance Volume Price Movement By Tick With Filters
================================================================================
============================================================================= */
SCSFExport scsf_OBVPMByTickWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_OBVPM = sc.Subgraph[0];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_VolumeFilterType = sc.Input[1];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[2];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[3];
	SCInputRef In_OBVPMSetSmoothing = sc.Input[4];
	SCInputRef In_OBVPMSmoothingPeriod = sc.Input[5];
	SCInputRef In_OBVPMSmoothingMAType = sc.Input[6];
	SCSubgraphRef OBVPM = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	//SCFloatArrayRef FloatArray = Graph_OBVPM.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	float Range, Balance, VolumeSum, VolumeScale;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "OBVPM: On Balance Volume Price Movement By Tick With Filters";
		
		sc.StudyVersion = 1.2;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 2; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume Price Movement By Tick With Filters (OBVPM). An original indicator by Brett Johnson made in 2014. The intent is to help identify weak price movements from stronger ones by using volume up-down difference with a scaling multiplier of bar height and bar close to close distance to create a balance function. Think of it as price distance pushed by volume. This graph should be plotted on the main price graph with an independent scale. OBVPM is not locked to the price graph and will float and stretch, so the lines being above or below each other is totally relative. What is important is comparing the size of the price move with the size of the OBVPM move. Individual OBVPM bar values by themselves hold no meaning. The pattern is what's important.\
<p>To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>The \"Set OBVPM Smoothing?\" option will enable a moving average filter to the output line. EMA5 is recommended to help keep the noise down and prevent false signals.\
<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.\
<p>Observations. Log scale will tend to follow price closely. While it's useful to verify price movement, it's more useful to have the relative volume push distance. Take note of current peak and dip heights relative to previous ones. Larger price moves with smaller OBVPM moves indicate price weakness in that direction. In Straight mode, some sharp price reversals will show up as rounded reversals in the OBVPM line.";

		//Output Graph
		Graph_OBVPM.Name = "OBVPMtick"; //drawn graphs must have a name.
		Graph_OBVPM.PrimaryColor = RGB(255, 255, 0);
		Graph_OBVPM.DrawStyle = DRAWSTYLE_LINE;
		Graph_OBVPM.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_OBVPM.LineWidth = 2;
		Graph_OBVPM.DrawZeros = 1;
		
		//User Inputs
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_InputData.Name = "Input Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_OBVPMSetSmoothing.Name = "Set OBVPM Smoothing?";
		In_OBVPMSetSmoothing.SetYesNo(1);
		In_OBVPMSetSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_OBVPMSmoothingPeriod.Name = "OBVPM Smoothing Period";
		In_OBVPMSmoothingPeriod.SetInt(5);
		In_OBVPMSmoothingPeriod.SetIntLimits(2, 50);
		In_OBVPMSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_OBVPMSmoothingMAType.Name = "OBVPM Smoothing Moving Average Type";
		In_OBVPMSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_OBVPMSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = (In_OBVPMSetSmoothing.GetYesNo() ? In_OBVPMSmoothingPeriod.GetInt() : 0 );
		//local variable
		Balance = 0.0;
		}
	
	//Reload Balance with previous value. Much easier to read this way.
	if(sc.Index >= 1) {Balance = OBVPM[sc.Index -1];}
	
	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}

	//Calculate bar range.
	//Note: if(Range == 0.0) then nothing happens.
	//up bar, positive
	if(sc.Close[sc.Index] >= sc.Open[sc.Index]) {Range = sc.High[sc.Index] - sc.Low[sc.Index];}
	//down bar, negative
	else {Range = sc.Low[sc.Index] - sc.High[sc.Index];}
	//add change between bars, positive or negative.
	Range += sc.Close[sc.Index] - sc.Close[sc.Index -1];
	
	//Calculat Volume.
	//VolumeSum is the up-down difference. Direction is determined by Range, so VolumeSum must be positive.
	VolumeSum = (float)sc.BaseData[Up][sc.Index] - (float)sc.BaseData[Down][sc.Index];
	if(VolumeSum < 0.0) {VolumeSum *= -1.0;} //keep the value positive
	//On Balance calculations.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		Balance += Range * VolumeSum;
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		Balance += Range * log( VolumeSum < 1.0 ? 1.0 : VolumeSum );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		Balance += Range * sqrt( VolumeSum < 1.0 ? 1.0 : VolumeSum );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.BaseData[VolumeType][sc.Index] <= VolumeMA[sc.Index]) {
			Balance += Range * VolumeSum;
			}
		//handle clipped volume
		else {
			VolumeScale = (float)VolumeMA[sc.Index] / (float)sc.BaseData[VolumeType][sc.Index];
			Balance += Range * VolumeScale * VolumeSum;
			}
		}
	OBVPM[sc.Index] = Balance;
	
	//Handle smoothing.
	if( In_OBVPMSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBVPM, Graph_OBVPM, In_OBVPMSmoothingMAType.GetMovAvgType(), In_OBVPMSmoothingPeriod.GetInt() );
		}
	else {
		Graph_OBVPM[sc.Index] = OBVPM[sc.Index];
		}
}

/* =============================================================================
================================================================================
OBVPM: On Balance Volume Price Movement With Filters
================================================================================
============================================================================= */
SCSFExport scsf_OBVPMWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_OBVPM = sc.Subgraph[0];
	SCInputRef In_VolumeFilterType = sc.Input[0];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[1];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[2];
	SCInputRef In_OBVPMSetSmoothing = sc.Input[3];
	SCInputRef In_OBVPMSmoothingPeriod = sc.Input[4];
	SCInputRef In_OBVPMSmoothingMAType = sc.Input[5];
	SCSubgraphRef OBVPM = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	//SCFloatArrayRef FloatArray = Graph_OBVPM.Arrays[0];
	
	//remember local variables are not persistent.
	float Range, Balance;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "OBVPM: On Balance Volume Price Movement With Filters";
		
		sc.StudyVersion = 1.2;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = 2; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
	
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume Price Movement With Filters (OBVPM). An original indicator by Brett Johnson made in 2014. The intent is to help identify weak price movements from stronger ones by using volume with a scaling multiplier of bar height and bar close to close distance to create a balance function. Think of it as price distance pushed by volume. This graph should be plotted on the main price graph with an independent scale. If you have tick by tick data, use the \"By Tick\" version for much better accuracy. OBVPM is not locked to the price graph and will float and stretch, so the lines being above or below each other is totally relative. What is important is comparing the size of the price move with the size of the OBVPM move. Individual OBVPM bar values by themselves hold no meaning. The pattern is what's important.\
<p>The \"Set OBVPM Smoothing?\" option will enable a moving average filter to the output line. EMA5 is recommended to help keep the noise down and prevent false signals.\
<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.\
<p>Observations. Log scale will tend to follow price closely. While it's useful to verify price movement, it's more useful to have the relative volume push distance. Take note of current peak and dip heights relative to previous ones. Larger price moves with smaller OBVPM moves indicate price weakness in that direction. In Straight mode, some sharp price reversals will show up as rounded reversals in the OBVPM line.";
		
		//Output Graph
		Graph_OBVPM.Name = "OBVPM"; //drawn graphs must have a name.
		Graph_OBVPM.PrimaryColor = RGB(255, 255, 0);
		Graph_OBVPM.DrawStyle = DRAWSTYLE_LINE;
		Graph_OBVPM.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_OBVPM.LineWidth = 2;
		Graph_OBVPM.DrawZeros = 1;
		
		//User Inputs
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_OBVPMSetSmoothing.Name = "Set OBVPM Smoothing?";
		In_OBVPMSetSmoothing.SetYesNo(1);
		In_OBVPMSetSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_OBVPMSmoothingPeriod.Name = "OBVPM Smoothing Period";
		In_OBVPMSmoothingPeriod.SetInt(5);
		In_OBVPMSmoothingPeriod.SetIntLimits(2, 50);
		In_OBVPMSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_OBVPMSmoothingMAType.Name = "OBVPM Smoothing Moving Average Type";
		In_OBVPMSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_OBVPMSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = (In_OBVPMSetSmoothing.GetYesNo() ? In_OBVPMSmoothingPeriod.GetInt() : 0 );
		//local variable
		Balance = 0.0;
		}
	
	//Reload Balance with previous value. Much easier to read this way.
	if(sc.Index >= 1) {Balance = OBVPM[sc.Index -1];}

	//Calculate bar range.
	//up bar, positive
	if(sc.Close[sc.Index] >= sc.Open[sc.Index]) {Range = sc.High[sc.Index] - sc.Low[sc.Index];}
	//down bar, negative
	else {Range = sc.Low[sc.Index] - sc.High[sc.Index];}
	//add change between bars, positive or negative.
	Range += sc.Close[sc.Index] - sc.Close[sc.Index -1];
	
	//Calculat Volume type.
	//Note: if(Range == 0.0) then nothing happens.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		Balance += Range * (float)sc.Volume[sc.Index];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		Balance += Range * log( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		Balance += Range * sqrt( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.Volume[sc.Index] <= VolumeMA[sc.Index]) {
			Balance += Range * (float)sc.Volume[sc.Index];
			}
		//handle clipped volume
		else {
			Balance += Range * (float)VolumeMA[sc.Index];
			}
		}
	OBVPM[sc.Index] = Balance;
	
	//Handle smoothing.
	if( In_OBVPMSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBVPM, Graph_OBVPM, In_OBVPMSmoothingMAType.GetMovAvgType(), In_OBVPMSmoothingPeriod.GetInt() );
		}
	else {
		Graph_OBVPM[sc.Index] = OBVPM[sc.Index];
		}
}

/* =============================================================================
================================================================================
Tool: Scale Study to 100 Graph By Zero Line
================================================================================
============================================================================= */
SCSFExport scsf_ScaleTo100ByZeroLine(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	//Keep graphs and associated inputs on the same index number.
	SCSubgraphRef Graph_Line1 = sc.Subgraph[0];
	SCSubgraphRef Graph_Line2 = sc.Subgraph[1];
	SCSubgraphRef Graph_Line3 = sc.Subgraph[2];
	SCSubgraphRef Graph_Line4 = sc.Subgraph[3];
	SCSubgraphRef Graph_Line5 = sc.Subgraph[4];
	SCInputRef In_InputData1 = sc.Input[0];
	SCInputRef In_InputData2 = sc.Input[1];
	SCInputRef In_InputData3 = sc.Input[2];
	SCInputRef In_InputData4 = sc.Input[3];
	SCInputRef In_InputData5 = sc.Input[4];
	
	SCInputRef In_InputCount = sc.Input[5];
	
	int i, iStart, iStop, iLine, LineCount, iData;
	float Low, High;
	long double Multiplier; //going from small MACD to a large 100 scale chart requires a lot of precision.
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Tool: Scale Study to 100 Graph By Zero Line";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = VALUEFORMAT_INHERITED; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_USERDEFINED; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		//Set output range.
		sc.ScaleRangeTop = 100.0;
		sc.ScaleRangeBottom = 0.0;
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Redraw needed for scrolling the chart.
		sc.UpdateAlways = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Scale Study to 100 Graph By Zero Line. This is a simple translator that will convert an oscillator graph with values above and below 0.0 to a 100 scale graph with 50 being the new middle line (from the previous 0.0 line). This is used to combine multiple studies on one chart and have a fixed middle point instead of several floating middle points that are hard to read.\
<ul><li>To use this, first add one of the horizontal line studies as the base of the new chart region. I prefer \"Lines 5\" but at a minimum set a single line to 50.0 to be the middle of the range. Go into the Scale option, select User Defined, set Top = 100.0 and Bottom = 0.0.\
<li>Add your source study to the same chart region as the horizontal line(s) and configure your settings with all of the lines set to hidden. It is recommended to put the source study under the horizontal line study in the \"Studies To Graph\" list for clarity.\
<li>Add this Scale study to the same chart region. It is recommended to put the Scale study under the source study in the \"Studies To Graph\" list for clarity.\
<li>Use the drop down box for \"Based On\" and select the source study you just added. The \"Input Data\" lines might come up with the wrong value or go blank in the configuration box. Select each \"Input Data\" line and assign it a new input value from the bottom drop down box. If the source study has multiple output lines, set every one that should be visible. Note: All of the 5 lines must have a value. It doesn't matter which value the unused lines will get.\
<li>Remember that the first line to be drawn on the chart will be below all the other lines. Line 1 will be below Line 2. Line 2 will be below Line 3. Make sure to account for this in your desired order from the input box.\
<li>Set \"Number Of Lines To Draw\" to the number of lines you want to see on the chart. If your study only has 1 line, then leave the value at 1. If drawing all 3 lines from MACD, select 3. The remaining lines will be skipped over and not drawn.\
<li>On the Subgraphs tab, select your line(s) and assign the preferred color and line style. The rest of the lines will automatically be set to Ignore once the Scale study loads.\
<li>If adding other studies on top of this one that are already 100 scale (like Stochastic or RSI), set any horizontal lines they have to hidden to avoid those lines being drawn on top of previous graph lines.\
<li>To see the unchanged values of the original study, open the Tools Values Window and put the mouse cursor in Crosshair mode.";

		//Output Graphs
		
		Graph_Line1.Name = "Line 1"; //drawn graphs must have a name.
		Graph_Line1.PrimaryColor = RGB(0, 255, 255);
		Graph_Line1.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line1.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line1.LineWidth = 1;
		Graph_Line1.DrawZeros = 1;
		
		Graph_Line2.Name = "Line 2"; //drawn graphs must have a name.
		Graph_Line2.PrimaryColor = RGB(0, 255, 0);
		Graph_Line2.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line2.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line2.LineWidth = 1;
		Graph_Line2.DrawZeros = 1;
		
		Graph_Line3.Name = "Line 3"; //drawn graphs must have a name.
		Graph_Line3.PrimaryColor = RGB(255, 255, 0);
		Graph_Line3.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line3.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line3.LineWidth = 1;
		Graph_Line3.DrawZeros = 1;
		
		Graph_Line4.Name = "Line 4"; //drawn graphs must have a name.
		Graph_Line4.PrimaryColor = RGB(255, 128, 0);
		Graph_Line4.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line4.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line4.LineWidth = 1;
		Graph_Line4.DrawZeros = 1;
		
		Graph_Line5.Name = "Line 5"; //drawn graphs must have a name.
		Graph_Line5.PrimaryColor = RGB(255, 0, 0);
		Graph_Line5.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line5.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line5.LineWidth = 1;
		Graph_Line5.DrawZeros = 1;
		
		//User Inputs	
		
		In_InputCount.Name = "Number Of Lines To Draw";
		In_InputCount.SetInt(1);
		In_InputCount.SetIntLimits(1, 5);
		In_InputCount.SetDescription("Number of lines to draw from the Input Data count.");
		
		In_InputData1.Name = "Input Data 1";
		In_InputData1.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData1.SetDescription("The input for line 1 to draw.");
		
		In_InputData2.Name = "Input Data 2";
		In_InputData2.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData2.SetDescription("The input for line 2 to draw.");
		
		In_InputData3.Name = "Input Data 3";
		In_InputData3.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData3.SetDescription("The input for line 3 to draw.");
		
		In_InputData4.Name = "Input Data 4";
		In_InputData4.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData4.SetDescription("The input for line 4 to draw.");
		
		In_InputData5.Name = "Input Data 5";
		In_InputData5.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData5.SetDescription("The input for line 5 to draw.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	LineCount = In_InputCount.GetInt();
	iStart = sc.IndexOfFirstVisibleBar;
	iStop = sc.IndexOfLastVisibleBar;
	
	//if first run...
	if (sc.Index == 0) {
		//turn off unused lines
		for(i=0; i < 5; i++) {
			if(i >= LineCount) {
				sc.Subgraph[i].DrawStyle = DRAWSTYLE_IGNORE;
				sc.Subgraph[i].DisplayNameValueInWindowsFlags = 0;
				}
			}
		}
	
	//find the lowest and highest numbers of all the lines.
	iData = sc.Input[0].GetInputDataIndex();
	Low = sc.BaseDataIn[iData][iStart];
	High = sc.BaseDataIn[iData][iStart];
	for (iLine=0; iLine < LineCount; iLine++) {
		iData = sc.Input[iLine].GetInputDataIndex();
		//find the lowest and highest numbers.
		for(i=iStart; i <= iStop; i++) {
			if(Low > sc.BaseDataIn[iData][i]) {Low = sc.BaseDataIn[iData][i];}
			if(High < sc.BaseDataIn[iData][i]) {High = sc.BaseDataIn[iData][i];}
			}
		}
	//select the largest numbers. need greatest distance away from 0.
	if(Low < 0.0) {Low *= -1.0;} //keep it positive
	if(Low > High) {High = Low;}
	//create the multiplier
	Multiplier = 100.0 / (2.0 * (long double)High);
	
	//loop through active lines and scale them.
	for (iLine=0; iLine < LineCount; iLine++) {
		iData = sc.Input[iLine].GetInputDataIndex();
		//scale the range
		for(i=iStart; i <= iStop; i++) {
			sc.Subgraph[iLine][i] = ((long double)sc.BaseDataIn[iData][i] * Multiplier) + 50.0;
			}
		}
}

/* =============================================================================
================================================================================
Trade Testing: Constant Entry For An Exit Management Program
================================================================================
============================================================================= */
SCSFExport scsf_TradeTesting_ConstantEntryForAnExitManagementProgram(SCStudyInterfaceRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_Slow = sc.Subgraph[0];
	SCSubgraphRef Graph_Fast = sc.Subgraph[1];
	SCSubgraphRef Graph_LongEntry = sc.Subgraph[2];
	SCSubgraphRef Graph_LongExit = sc.Subgraph[3];
	SCSubgraphRef Graph_ShortEntry = sc.Subgraph[4];
	SCSubgraphRef Graph_ShortExit = sc.Subgraph[5];

	SCInputRef In_Enabled = sc.Input[0];
	SCInputRef InFlag_ServerConnectionState = sc.Input[1];
	SCInputRef InFlag_IsAutoTradingEnabled = sc.Input[2];
	SCInputRef InFlag_IsChartTradeModeOn = sc.Input[3];
	SCInputRef InFlag_GlobalTradeSimulationIsOn = sc.Input[4];
	SCInputRef In_ExecuteOnce = sc.Input[5];
	SCInputRef In_Volume = sc.Input[6];
	SCInputRef In_SlowMA = sc.Input[7];
	SCInputRef In_FastMA = sc.Input[8];
	
	s_SCNewOrder NewOrder;
	s_SCPositionData PositionData;
	SCString LogText;
	
	int itmp, Direction, RC;
	
	if (sc.SetDefaults)
	{
		// Set the study configuration and defaults.

		//Long descriptive name.
		sc.GraphName = "Trade Testing: Constant Entry For An Exit Management Program";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1;  //Auto looping is enabled.
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = VALUEFORMAT_INHERITED; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Trading Settings. Start locked down.
		sc.CalculationPrecedence = VERY_LOW_PREC_LEVEL; //other dependent studies get calculated first.
		sc.MaintainTradeStatisticsAndTradesData = true; //needed for trading functions.
		sc.AllowOnlyOneTradePerBar = false;
		sc.AllowMultipleEntriesInSameDirection = true;
		sc.AllowEntryWithWorkingOrders = true;
		sc.SupportReversals = true;
		sc.AllowOppositeEntryWithOpposingPositionOrOrders = true;
		sc.SupportAttachedOrdersForTrading = false; //don't use attach orders from the chart Trading Window.
		sc.UseGUIAttachedOrderSetting = false; //don't use attach orders from the chart Trading Window.
		sc.CancelAllOrdersOnEntriesAndReversals = true; //start fresh going in.
		sc.CancelAllWorkingOrdersOnExit = true; //allows for exits with attached orders.
		
		sc.SendOrdersToTradeService = false;
		sc.UpdateAlways = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Trade Testing: Constant Entry For An Exit Management Program. This is a torture test for another program that manages exit trades. As soon as no active trade is detected, a new trade will be entered at the current market price. If the Fast MA is above the Slow MA, the trade will be entered long. If the Fast MA is below the Slow MA, the trade will be entered short. Trading will not start until there are enough bars to draw the Slow MA. Make sure the Flags show \"Yes\" before running the program in Replay Mode.\
<p>NEVER, EVER modify this program to perform real trades. It will cause you a trading disaster. It currently will only activate if in Simulation Mode. If nothing happens, check that you are in Simulation Mode.";
		
		//Output Graphs
		
		//To avoid confusion, going long is always up arrows, short is down. Entry is green. Exit is red.
		
		Graph_LongEntry.Name = "Long Entry";
		Graph_LongEntry.PrimaryColor = RGB(0, 255, 0);
		Graph_LongEntry.DrawStyle = DRAWSTYLE_ARROWUP;
		Graph_LongEntry.LineWidth = 4;
		Graph_LongEntry.DrawZeros = 0;
		Graph_LongEntry.DisplayNameValueInWindowsFlags = 0;
		
		Graph_LongExit.Name = "Long Exit";
		Graph_LongExit.PrimaryColor = RGB(255, 0, 0);
		Graph_LongExit.DrawStyle = DRAWSTYLE_ARROWUP;
		Graph_LongExit.LineWidth = 4;
		Graph_LongExit.DrawZeros = 0;
		Graph_LongExit.DisplayNameValueInWindowsFlags = 0;
		
		Graph_ShortEntry.Name = "Short Entry";
		Graph_ShortEntry.PrimaryColor = RGB(0, 255, 0);
		Graph_ShortEntry.DrawStyle = DRAWSTYLE_ARROWDOWN;
		Graph_ShortEntry.LineWidth = 4;
		Graph_ShortEntry.DrawZeros = 0;
		Graph_ShortEntry.DisplayNameValueInWindowsFlags = 0;
		
		Graph_ShortExit.Name = "Short Exit";
		Graph_ShortExit.PrimaryColor = RGB(255, 0, 0);
		Graph_ShortExit.DrawStyle = DRAWSTYLE_ARROWDOWN;
		Graph_ShortExit.LineWidth = 4;
		Graph_ShortExit.DrawZeros = 0;
		Graph_ShortExit.DisplayNameValueInWindowsFlags = 0;
		
		Graph_Slow.Name = "Slow"; //drawn graphs must have a name.
		Graph_Slow.PrimaryColor = RGB(255, 0, 0);
		Graph_Slow.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		Graph_Slow.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Slow.LineWidth = 2;
		Graph_Slow.DrawZeros = 0;
		
		Graph_Fast.Name = "Fast"; //drawn graphs must have a name.
		Graph_Fast.PrimaryColor = RGB(0, 0, 255);
		Graph_Fast.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		Graph_Fast.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Fast.LineWidth = 2;
		Graph_Fast.DrawZeros = 0;
		
		
		In_Enabled.Name = "Did you read the instructions?";
		In_Enabled.SetYesNo(0);
		In_Enabled.SetDescription("Enables trading operations.");
		
		InFlag_ServerConnectionState.Name = "FLAG: File >> Disconnect";
		InFlag_ServerConnectionState.SetYesNo(!sc.ServerConnectionState);
		InFlag_ServerConnectionState.SetDescription("Needs \"Yes\".<p>This is a flag value shown for convenience. Changing this value here does nothing. Go to the menu option to make the change. Note that some flags affect other flags. Close and reopen settings to see if the new value took.");
		
		InFlag_IsAutoTradingEnabled.Name = "FLAG: Trade >> Auto Trading Enabled";
		InFlag_IsAutoTradingEnabled.SetYesNo(sc.IsAutoTradingEnabled);
		InFlag_IsAutoTradingEnabled.SetDescription("Needs \"Yes\".<p>This is a flag value shown for convenience. Changing this value here does nothing. Go to the menu option to make the change. Note that some flags affect other flags. Close and reopen settings to see if the new value took.");
		
		InFlag_IsChartTradeModeOn.Name = "FLAG: Trade >> Chart Trade Mode On";
		InFlag_IsChartTradeModeOn.SetYesNo(sc.IsChartTradeModeOn);
		InFlag_IsChartTradeModeOn.SetDescription("Needs \"Yes\".<p>This is a flag value shown for convenience. Changing this value here does nothing. Go to the menu option to make the change. Note that some flags affect other flags. Close and reopen settings to see if the new value took.");
		
		
		InFlag_GlobalTradeSimulationIsOn.Name = "FLAG: Trade >> Trade Simulation Mode On";
		InFlag_GlobalTradeSimulationIsOn.SetYesNo(sc.GlobalTradeSimulationIsOn);
		InFlag_GlobalTradeSimulationIsOn.SetDescription("Sim mode needs to be on for testing. Otherwise this program will not run.<p>This is a flag value shown for convenience. Changing this value here does nothing. Go to the menu option to make the change. Close and reopen settings to see if the new value took.");
		
		In_ExecuteOnce.Name = "Execute only once?";
		In_ExecuteOnce.SetYesNo(0);
		In_ExecuteOnce.SetDescription("Execute only one trade then disable instead of looping and always executing a trade.");
		
		In_Volume.Name = "Trade Volume Size";
		In_Volume.SetInt(10);
		In_Volume.SetIntLimits(1, 1000000);
		In_Volume.SetDescription("Size of the trade volume.");
		
		In_SlowMA.Name = "Slow MA Period";
		In_SlowMA.SetInt(50);
		In_SlowMA.SetIntLimits(2, 1000);
		In_SlowMA.SetDescription("Number of bars for the period. Usually 50 or higher.");
		
		In_FastMA.Name = "Fast MA Period";
		In_FastMA.SetInt(10);
		In_FastMA.SetIntLimits(2, 1000);
		In_FastMA.SetDescription("Number of bars for the period. Usually less than 50.");
		
		///INVERT OPTION

		return;
	}
	
	//Set the flags.
	InFlag_ServerConnectionState.SetYesNo(!sc.ServerConnectionState);
	InFlag_IsAutoTradingEnabled.SetYesNo(sc.IsAutoTradingEnabled);
	InFlag_IsChartTradeModeOn.SetYesNo(sc.IsChartTradeModeOn);
	InFlag_GlobalTradeSimulationIsOn.SetYesNo(sc.GlobalTradeSimulationIsOn);
	
	//Force sim mode on for this program to work.
	//NEVER use this program for real trading.
	if(sc.GlobalTradeSimulationIsOn == 0) {In_Enabled.SetYesNo(0);}
	
	//Force other flags.
	if(sc.IsAutoTradingEnabled == 0) {In_Enabled.SetYesNo(0);}
	if(sc.IsChartTradeModeOn == 0) {In_Enabled.SetYesNo(0);}
	
	//Nothing to do if disabled.
	if(In_Enabled.GetYesNo() == 0) {return;}
	
	//If first run.
	if (sc.Index == 0) {
		//Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_SlowMA.GetInt() - 1;
		//Maximum position allowed.
		sc.MaximumPositionAllowed = In_Volume.GetInt();
		//Scaling must be outside of the sc.SetDefaults code block since they have a dependency upon an actual chart object existing.
		sc.SupportTradingScaleIn = 0;
		sc.SupportTradingScaleOut = 0;
		//Make sure fast<slow;
		if(In_FastMA.GetInt() > In_SlowMA.GetInt()) {
			itmp = In_FastMA.GetInt();
			In_FastMA.SetInt(In_SlowMA.GetInt());
			In_SlowMA.SetInt(itmp);
			}
		}
	
	// Calculate the moving average
	sc.SimpleMovAvg(sc.Close, Graph_Fast, In_FastMA.GetInt());
	sc.SimpleMovAvg(sc.Close, Graph_Slow, In_SlowMA.GetInt());
	
	//Not enough data yet.
	if( sc.Index < In_SlowMA.GetInt() ) {return;}
	
	//Reset conditions
	if(sc.DownloadingHistoricalData) {return;} //Cannot manage orders when downloading data.
	if(sc.IsFullRecalculation) {return;} //Cannot manage orders when recalculating.
	
	//Get current trade status.
	sc.GetTradePosition(PositionData);
	
	//Only enter a trade if one doesn't exist.
	if(PositionData.PositionQuantity != 0) {return;}
	
	//Get new trade direction.
	if(Graph_Fast[sc.Index] > Graph_Slow[sc.Index]) {Direction = 1;}
	else {Direction = -1;}
	
	//Create a new order.
	NewOrder.Reset();
	NewOrder.OrderQuantity = In_Volume.GetInt();
	NewOrder.OrderType = SCT_ORDERTYPE_MARKET;
	NewOrder.TimeInForce = SCT_TIF_GTC;
	if(Direction > 0) { //go long
		RC = sc.BuyEntry(NewOrder);
		if(RC>0) {Graph_LongEntry[sc.Index] = sc.Low[sc.Index];}
		LogText.Format("%s Long Entry: Trade Test Entry (RC=%d), Price Current: %f", PositionData.Symbol.GetChars(), RC, sc.Close[sc.Index]);
		}
	else { //go short
		RC = sc.SellEntry(NewOrder);
		if(RC>0) {Graph_ShortEntry[sc.Index] = sc.High[sc.Index];}
		LogText.Format("%s Short Entry: Trade Test Entry (RC=%d), Price Current: %f", PositionData.Symbol.GetChars(), RC, sc.Close[sc.Index]);
		}
	sc.AddMessageToLog(LogText, 0);
	
	if(In_ExecuteOnce.GetYesNo()) {In_Enabled.SetYesNo(0);}
	
	// ??? eventually set exit trade arrow ???
	
	return;
}

/* =============================================================================
================================================================================
Trade: Brett's Multi-Function Trailing Stop
================================================================================
============================================================================= */
/*
Brett Johnson's Multi-Function Trailing Stop
Copyright 2015 under GNU GPL v1. If you use this code in your own program, share it like I have.

This program provides a trailing stop based on a moving average. This helps prevent premature
exits caused by "bar whiskers" and some stop running. There is also:
 * A traditional trailing stop further away for safety.
 * An exit trend line useful for catching channel break outs.
 * A price target feature.
 * An exit based on the time of day (such as closing).
 * An exit based on the end of the trading week (avoiding weekend gaps). 
*/

//Global
#define DEBUGON 0 //enable or disable some of the debugging code
#define DEBUGLOG "DebugOrderList.log" //SC will put this log file in the Data dir.
enum TradeDirection {TD_None, TD_Long, TD_Short};
enum ResetCodes {RESET_ZERO, RESET_MANUAL, RESET_DOWNLOADINGDATA, RESET_FULLRECALCULATION, RESET_VOLUMECHANGE, RESET_REPLAY};

//Debug: Print out data type sizes to log file to see variable type size limitations.
void debug_DataTypeSizes() {
	//open output log
	FILE *FileOut;
	FileOut = fopen(DEBUGLOG, "a"); //"a" is append text. DEBUGLOG will be in the Data dir.
	if(!FileOut) {return;} //abort on error
	setvbuf(FileOut, NULL, _IOFBF, (1*1024)); //output buffering: 1k
	fprintf(FileOut, "\n==============================\n");
	fprintf(FileOut, "Data Type    Bytes\n");
    fprintf(FileOut, "---------    -----\n");
    fprintf(FileOut, "char           %d\n", sizeof(char));
    fprintf(FileOut, "int8_t         %d\n", sizeof(int8_t));
    fprintf(FileOut, "short          %d\n", sizeof(short));
    fprintf(FileOut, "int16_t        %d\n", sizeof(int16_t));
    fprintf(FileOut, "int            %d\n", sizeof(int));
    fprintf(FileOut, "int32_t        %d\n", sizeof(int32_t));
    fprintf(FileOut, "long           %d\n", sizeof(long));
    fprintf(FileOut, "long long      %d\n", sizeof(long long));
    fprintf(FileOut, "int64_t        %d\n", sizeof(int64_t));
    fprintf(FileOut, "float          %d\n", sizeof(float));
    fprintf(FileOut, "double         %d\n", sizeof(double));
    fprintf(FileOut, "long double    %d\n", sizeof(long double));
	fprintf(FileOut, "pointer        %d\n", sizeof(int *));
	fprintf(FileOut, "FILE           %d\n", sizeof(FILE));
    fprintf(FileOut, "time_t         %d\n", sizeof(time_t));
	fprintf(FileOut, "\n==============================\n");
	fclose(FileOut);
} //void debug_DataTypeSizes


//Convert week day number to String. Sunday=0
char *DayOfWeekToString(const int StatusCode, char *TempStr, const unsigned int StrSize) {
	switch(StatusCode) {
		case(SUNDAY): strncpy(TempStr, "Sunday", StrSize); break;
		case(MONDAY): strncpy(TempStr, "Monday", StrSize); break;
		case(TUESDAY): strncpy(TempStr, "Tuesday", StrSize); break;
		case(WEDNESDAY): strncpy(TempStr, "Wednesday", StrSize); break;
		case(THURSDAY): strncpy(TempStr, "Thursday", StrSize); break;
		case(FRIDAY): strncpy(TempStr, "Friday", StrSize); break;
		case(SATURDAY): strncpy(TempStr, "Saturday", StrSize); break;
		default: strncpy(TempStr, "[Error: Week Day Not Defined]", StrSize); break;
		} //end switch
return TempStr;
} //end char *DayOfWeekToString


//Debug: Convert reset number to String.
char *ResetToString(const int StatusCode, char *TempStr, const unsigned int StrSize) {
	switch(StatusCode) {
		case(RESET_ZERO): strncpy(TempStr, "RESET_ZERO", StrSize); break;
		case(RESET_MANUAL): strncpy(TempStr, "RESET_MANUAL", StrSize); break;
		case(RESET_DOWNLOADINGDATA): strncpy(TempStr, "RESET_DOWNLOADINGDATA", StrSize); break;
		case(RESET_FULLRECALCULATION): strncpy(TempStr, "RESET_FULLRECALCULATION", StrSize); break;
		case(RESET_VOLUMECHANGE): strncpy(TempStr, "RESET_VOLUMECHANGE", StrSize); break;
		case(RESET_REPLAY): strncpy(TempStr, "RESET_REPLAY", StrSize); break;
		default: strncpy(TempStr, "[Error: Reset Code Not Defined]", StrSize); break;
		} //end switch
return TempStr;
} //end char *ResetToString


//Debug: Convert Order Status Code to String
char *OSCToString(const int StatusCode, char *TempStr, const unsigned int StrSize) {
	switch(StatusCode) {
		//case(SCT_OSC_WORKING): strncpy(TempStr, "SCT_OSC_WORKING", StrSize); break; //mentioned in docs but undefined
		case(SCT_OSC_OPEN): strncpy(TempStr, "SCT_OSC_OPEN", StrSize); break;
		case(SCT_OSC_FILLED): strncpy(TempStr, "SCT_OSC_FILLED", StrSize); break;
		case(SCT_OSC_CANCELED): strncpy(TempStr, "SCT_OSC_CANCELED", StrSize); break;
		case(SCT_OSC_ERROR): strncpy(TempStr, "SCT_OSC_ERROR", StrSize); break;
		case(SCT_OSC_UNSPECIFIED): strncpy(TempStr, "SCT_OSC_UNSPECIFIED", StrSize); break;
		case(SCT_OSC_ORDERSENT): strncpy(TempStr, "SCT_OSC_ORDERSENT", StrSize); break;
		case(SCT_OSC_PENDINGOPEN): strncpy(TempStr, "SCT_OSC_PENDINGOPEN", StrSize); break;
		case(SCT_OSC_PENDING_CHILD_CLIENT): strncpy(TempStr, "SCT_OSC_PENDING_CHILD_CLIENT", StrSize); break;
		case(SCT_OSC_PENDING_CHILD_SERVER): strncpy(TempStr, "SCT_OSC_PENDING_CHILD_SERVER", StrSize); break;
		case(SCT_OSC_PENDINGMODIFY): strncpy(TempStr, "SCT_OSC_PENDINGMODIFY", StrSize); break;
		case(SCT_OSC_PENDINGCANCEL): strncpy(TempStr, "SCT_OSC_PENDINGCANCEL", StrSize); break;
		default: strncpy(TempStr, "[Error: SCT_OSC Not Defined]", StrSize); break;
		} //end switch
return TempStr;
} //end char *OSCToString


//Debug: Convert Order Error Code to String
char *SkippedToString(const int StatusCode, char *TempStr, const unsigned int StrSize) {
	switch(StatusCode) {
		case(SCT_SKIPPED_FULL_RECALC): strncpy(TempStr, "SCT_SKIPPED_FULL_RECALC", StrSize); break;
		case(SCT_SKIPPED_DOWNLOADING_HISTORICAL_DATA): strncpy(TempStr, "SCT_SKIPPED_DOWNLOADING_HISTORICAL_DATA", StrSize); break;
		case(SCT_SKIPPED_ONLY_ONE_TRADE_PER_BAR): strncpy(TempStr, "SCT_SKIPPED_ONLY_ONE_TRADE_PER_BAR", StrSize); break;
		case(SCT_SKIPPED_INVALID_INDEX_SPECIFIED): strncpy(TempStr, "SCT_SKIPPED_INVALID_INDEX_SPECIFIED", StrSize); break;
		case(SCT_SKIPPED_TOO_MANY_NEW_BARS_DURING_UPDATE): strncpy(TempStr, "SCT_SKIPPED_TOO_MANY_NEW_BARS_DURING_UPDATE", StrSize); break;
		default: strncpy(TempStr, "[Error: SCT_SKIPPED Not Defined]", StrSize); break;
		} //end switch
return TempStr;
} //end char *SkippedToString


//Debug: Convert Order Type Code to String
char *OrderTypeToString(const int StatusCode, char *TempStr, const unsigned int StrSize) {
	switch(StatusCode) {
		case(SCT_ORDERTYPE_MARKET): strncpy(TempStr, "SCT_ORDERTYPE_MARKET", StrSize); break;
		//case(SCT_MARKET): strncpy(TempStr, "SCT_MARKET", StrSize); break; //older enum no longer used
		case(SCT_ORDERTYPE_LIMIT): strncpy(TempStr, "SCT_ORDERTYPE_LIMIT", StrSize); break;
		case(SCT_ORDERTYPE_STOP): strncpy(TempStr, "SCT_ORDERTYPE_STOP", StrSize); break;
		case(SCT_ORDERTYPE_STOP_LIMIT): strncpy(TempStr, "SCT_ORDERTYPE_STOP_LIMIT", StrSize); break;
		case(SCT_ORDERTYPE_MARKET_IF_TOUCHED): strncpy(TempStr, "SCT_ORDERTYPE_MARKET_IF_TOUCHED", StrSize); break;
		case(SCT_ORDERTYPE_LIMIT_CHASE): strncpy(TempStr, "SCT_ORDERTYPE_LIMIT_CHASE", StrSize); break;
		case(SCT_ORDERTYPE_LIMIT_TOUCH_CHASE): strncpy(TempStr, "SCT_ORDERTYPE_LIMIT_TOUCH_CHASE", StrSize); break;
		case(SCT_ORDERTYPE_TRAILING_STOP): strncpy(TempStr, "SCT_ORDERTYPE_TRAILING_STOP", StrSize); break;
		case(SCT_ORDERTYPE_TRAILING_STOP_LIMIT): strncpy(TempStr, "SCT_ORDERTYPE_TRAILING_STOP_LIMIT", StrSize); break;
		case(SCT_ORDERTYPE_TRIGGERED_TRAILING_STOP_3_OFFSETS): strncpy(TempStr, "SCT_ORDERTYPE_TRIGGERED_TRAILING_STOP_3_OFFSETS", StrSize); break;
		case(SCT_ORDERTYPE_TRIGGERED_TRAILING_STOP_LIMIT_3_OFFSETS): strncpy(TempStr, "SCT_ORDERTYPE_TRIGGERED_TRAILING_STOP_LIMIT_3_OFFSETS", StrSize); break;
		case(SCT_ORDERTYPE_STEP_TRAILING_STOP): strncpy(TempStr, "SCT_ORDERTYPE_STEP_TRAILING_STOP", StrSize); break;
		case(SCT_ORDERTYPE_STEP_TRAILING_STOP_LIMIT): strncpy(TempStr, "SCT_ORDERTYPE_STEP_TRAILING_STOP_LIMIT", StrSize); break;
		case(SCT_ORDERTYPE_TRIGGERED_STEP_TRAILING_STOP): strncpy(TempStr, "SCT_ORDERTYPE_TRIGGERED_STEP_TRAILING_STOP", StrSize); break;
		case(SCT_ORDERTYPE_TRIGGERED_STEP_TRAILING_STOP_LIMIT): strncpy(TempStr, "SCT_ORDERTYPE_TRIGGERED_STEP_TRAILING_STOP_LIMIT", StrSize); break;
		case(SCT_ORDERTYPE_OCO_LIMIT_STOP): strncpy(TempStr, "SCT_ORDERTYPE_OCO_LIMIT_STOP", StrSize); break;
		case(SCT_ORDERTYPE_OCO_LIMIT_STOP_LIMIT): strncpy(TempStr, "SCT_ORDERTYPE_OCO_LIMIT_STOP_LIMIT", StrSize); break;
		case(SCT_ORDERTYPE_OCO_BUY_STOP_SELL_STOP): strncpy(TempStr, "SCT_ORDERTYPE_OCO_BUY_STOP_SELL_STOP", StrSize); break;
		case(SCT_ORDERTYPE_OCO_BUY_STOP_LIMIT_SELL_STOP_LIMIT): strncpy(TempStr, "SCT_ORDERTYPE_OCO_BUY_STOP_LIMIT_SELL_STOP_LIMIT", StrSize); break;
		case(SCT_ORDERTYPE_OCO_BUY_LIMIT_SELL_LIMIT): strncpy(TempStr, "SCT_ORDERTYPE_OCO_BUY_LIMIT_SELL_LIMIT", StrSize); break;
		default: strncpy(TempStr, "[Error: SCT_ORDERTYPE Not Defined]", StrSize); break;
		} //end switch
return TempStr;
} //end char *OrderTypeToString


//Debug: Convert Move To Break Even Action Type Code to String
char *MoveToBEToString(const int StatusCode, char *TempStr, const unsigned int StrSize) {
	switch(StatusCode) {
		case(MOVETO_BE_ACTION_TYPE_OFFSET_TRIGGERED): strncpy(TempStr, "MOVETO_BE_ACTION_TYPE_OFFSET_TRIGGERED", StrSize); break;
		case(MOVETO_BE_ACTION_TYPE_OCO_GROUP_TRIGGERED): strncpy(TempStr, "MOVETO_BE_ACTION_TYPE_OCO_GROUP_TRIGGERED", StrSize); break;
		case(MOVETO_BE_ACTION_TYPE_TRAIL_TO_BREAKEVEN): strncpy(TempStr, "MOVETO_BE_ACTION_TYPE_TRAIL_TO_BREAKEVEN", StrSize); break;
		case(MOVETO_BE_ACTION_TYPE_OFFSET_TRIGGERED_TRAIL_TO_BREAKEVEN): strncpy(TempStr, "MOVETO_BE_ACTION_TYPE_OFFSET_TRIGGERED_TRAIL_TO_BREAKEVEN", StrSize); break;
		default: strncpy(TempStr, "[Error: MOVETO_BE_ACTION_TYPE Not Defined]", StrSize); break;
		} //end switch
return TempStr;
} //end char *MoveToBEToString


//Debug: Convert Trading Error Code to String
char *TradingErrorToString(const int StatusCode, char *TempStr, const unsigned int StrSize) {
	switch(StatusCode) {
		case(SCTRADING_ORDER_ERROR): strncpy(TempStr, "SCTRADING_ORDER_ERROR", StrSize); break; //-1, BuyEntry, BuyExit, SellEntry, SellExit, GetOrderByID, GetOrderByIndex
		case(SCTRADING_NOT_OCO_ORDER_TYPE): strncpy(TempStr, "SCTRADING_NOT_OCO_ORDER_TYPE", StrSize); break; //-2
		default:
			if(StatusCode > 0) {strncpy(TempStr, "Order Size Accepted", StrSize);}
			else {strncpy(TempStr, "[Error: SCTRADING Not Defined]", StrSize);}
			break;
		} //end switch
return TempStr;
} //end char *TradingErrorToString


//Debug: Print out all orders in the system.
//This is used to see what information is available and what has been done.
int debug_PrintOrders(SCStudyInterfaceRef sc) {
	int i, ListSize, PrintCount;
	int Year, Month, Day, Hour, Minute, Second;
	char TimeStr[30+1], TempStr[100+1];
	SCDateTime TimeNow;
	s_SCPositionData PositionData;
	s_SCTradeOrder TradeOrder;
	s_ACSTrade ACSTrade;
	s_SCOrderFillData OrderFillData;
	
	//open output log
	FILE *FileOut;
	FileOut = fopen(DEBUGLOG, "a"); //"a" is append text. DEBUGLOG will be in the Data dir.
	if(!FileOut) {return -1;} //abort on error
	setvbuf(FileOut, NULL, _IOFBF, (10*1024)); //output buffering: 10k
	
	//initialize variables
	PrintCount = 0;
	TimeNow = sc.CurrentSystemDateTime;
	sprintf(TimeStr, "%04d-%02d-%02d %d:%02d.%02d", TimeNow.GetYear(), TimeNow.GetMonth(), TimeNow.GetDay(), TimeNow.GetHour(), TimeNow.GetMinute(), TimeNow.GetSecond() );
	
	//print separator
	fprintf(FileOut, "\n========== %s ====================\n", TimeStr);
	fprintf(FileOut, "Mode: %s\n", (sc.SendOrdersToTradeService==0?"Simulation":"Live Trading"));
	
	//s_SCPositionData: Get overall current trade status.
	sc.GetTradePosition(PositionData);
	PrintCount++;
	fprintf(FileOut, "\ns_SCPositionData: (%s)\n", (sc.SendOrdersToTradeService==0?"Simulation":"Live Trading"));
	fprintf(FileOut, "   Symbol: %s\n", PositionData.Symbol.GetChars());
	fprintf(FileOut, "   PositionQuantity: %d\n", PositionData.PositionQuantity);
	fprintf(FileOut, "   AveragePrice: %f\n", PositionData.AveragePrice);
	fprintf(FileOut, "   OpenProfitLoss: %f\n", PositionData.OpenProfitLoss);
	fprintf(FileOut, "   CumulativeProfitLoss: %f\n", PositionData.CumulativeProfitLoss);
	fprintf(FileOut, "   DailyProfitLoss: %f\n", PositionData.DailyProfitLoss);
	fprintf(FileOut, "   MaximumOpenPositionProfit: %f\n", PositionData.MaximumOpenPositionProfit);
	fprintf(FileOut, "   MaximumOpenPositionLoss: %f\n", PositionData.MaximumOpenPositionLoss);
	fprintf(FileOut, "   LastTradeProfitLoss: %f\n", PositionData.LastTradeProfitLoss);
	fprintf(FileOut, "   PositionQuantityWithAllWorkingOrders: %d\n", PositionData.PositionQuantityWithAllWorkingOrders);
	fprintf(FileOut, "   PositionQuantityWithExitWorkingOrders: %d\n", PositionData.PositionQuantityWithExitWorkingOrders);
	fprintf(FileOut, "   WorkingOrdersExist: %d\n", PositionData.WorkingOrdersExist);
	PositionData.LastFillDateTime.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);
	fprintf(FileOut, "   LastFillDateTime: %04d-%02d-%02d %02d:%02d.%02d\n",  Year, Month, Day, Hour, Minute, Second);
	PositionData.LastEntryDateTime.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);
	fprintf(FileOut, "   LastEntryDateTime: %04d-%02d-%02d %02d:%02d.%02d\n",  Year, Month, Day, Hour, Minute, Second);
	PositionData.LastExitDateTime.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);
	fprintf(FileOut, "   LastExitDateTime: %04d-%02d-%02d %02d:%02d.%02d\n",  Year, Month, Day, Hour, Minute, Second);
	
	//s_SCTradeOrder: Get individual trade orders.
	//Index 0 is newest entry.
	i=0;
	while(sc.GetOrderByIndex(i, TradeOrder) != SCTRADING_ORDER_ERROR) {
		PrintCount++;
		fprintf(FileOut, "\ns_SCTradeOrder: %d (%s)\n", i, (sc.SendOrdersToTradeService==0?"Simulation":"Live Trading"));
		fprintf(FileOut, "   Symbol: %s\n", TradeOrder.Symbol.GetChars());
		fprintf(FileOut, "   InternalOrderID: %d\n", TradeOrder.InternalOrderID);
		fprintf(FileOut, "   ParentInternalOrderID: %d (%s)\n", TradeOrder.ParentInternalOrderID, (TradeOrder.ParentInternalOrderID==0?"Parent":"Attached"));
		fprintf(FileOut, "   LinkID: %d\n", TradeOrder.LinkID); //if !=0 and attached order with >1 OCO Order Group, has split OrderQuantity.
		fprintf(FileOut, "   OrderType: %s\n", TradeOrder.OrderType.GetChars());
		fprintf(FileOut, "   OrderTypeAsInt: %d (%s)\n", TradeOrder.OrderTypeAsInt, OrderTypeToString(TradeOrder.OrderTypeAsInt, TempStr, 100));
		fprintf(FileOut, "   OrderQuantity: %d\n", TradeOrder.OrderQuantity);
		fprintf(FileOut, "   FilledQuantity: %d\n", TradeOrder.FilledQuantity);
		fprintf(FileOut, "   BuySell: %d (%s)\n", TradeOrder.BuySell, (TradeOrder.BuySell==BSE_BUY?"BSE_BUY":"BSE_SELL"));
		fprintf(FileOut, "   Price1: %f\n", TradeOrder.Price1);
		fprintf(FileOut, "   Price2: %f\n", TradeOrder.Price2);
		fprintf(FileOut, "   AvgFillPrice: %f\n", TradeOrder.AvgFillPrice);
		fprintf(FileOut, "   OrderStatusCode: %d (%s)\n", TradeOrder.OrderStatusCode, OSCToString(TradeOrder.OrderStatusCode, TempStr, 100));
		TradeOrder.LastActivityTime.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);
		fprintf(FileOut, "   LastActivityTime: %04d-%02d-%02d %02d:%02d.%02d\n",  Year, Month, Day, Hour, Minute, Second);
		TradeOrder.EntryDateTime.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);
		fprintf(FileOut, "   EntryDateTime: %04d-%02d-%02d %02d:%02d.%02d\n",  Year, Month, Day, Hour, Minute, Second);
		i++;
	} //end while TradeOrder
	
	//s_ACSTrade: Completed trades.
	//Last entry index is newest entry.
	ListSize = sc.GetTradeListSize();
	for(i=0; i<ListSize; i++) {
		PrintCount++;
		sc.GetTradeListEntry(i, ACSTrade);
		fprintf(FileOut, "\ns_ACSTrade: %d%s (%s)\n", i, (ACSTrade.CloseDateTime.GetYear()<1900?" (Open)":""), (sc.SendOrdersToTradeService==0?"Simulation":"Live Trading"));
		ACSTrade.OpenDateTime.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);
		fprintf(FileOut, "   OpenDateTime: %04d-%02d-%02d %02d:%02d.%02d\n",  Year, Month, Day, Hour, Minute, Second);
		ACSTrade.CloseDateTime.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);
		fprintf(FileOut, "   CloseDateTime: %04d-%02d-%02d %02d:%02d.%02d\n",  Year, Month, Day, Hour, Minute, Second); //CloseDateTime Year = 1899 = open trade.
		fprintf(FileOut, "   TradeType: %d (%s)\n", ACSTrade.TradeType, (ACSTrade.TradeType>0?"Long":"Short"));
		fprintf(FileOut, "   EntryQuantity: %d\n", ACSTrade.EntryQuantity);
		fprintf(FileOut, "   ExitQuantity: %d%s\n", ACSTrade.ExitQuantity, (ACSTrade.ExitQuantity<ACSTrade.MaxOpenQuantity?" (Open)":"")); //ExitQuantity < MaxOpenQuantity = Open
		fprintf(FileOut, "   MaxOpenQuantity: %d\n", ACSTrade.MaxOpenQuantity);
		fprintf(FileOut, "   AverageEntryPrice: %f\n", ACSTrade.AverageEntryPrice);
		fprintf(FileOut, "   AverageExitPrice: %f\n", ACSTrade.AverageExitPrice);
		fprintf(FileOut, "   OpenProfitLoss: %f\n", ACSTrade.OpenProfitLoss);
		fprintf(FileOut, "   ClosedProfitLoss: %f\n", ACSTrade.ClosedProfitLoss);
		fprintf(FileOut, "   MaximumOpenPositionProfit: %f\n", ACSTrade.MaximumOpenPositionProfit);
		fprintf(FileOut, "   MaximumOpenPositionLoss: %f\n", ACSTrade.MaximumOpenPositionLoss);
		fprintf(FileOut, "   MaximumRunup: %f\n", ACSTrade.MaximumRunup);
		fprintf(FileOut, "   MaximumDrawdown: %f\n", ACSTrade.MaximumDrawdown);
		fprintf(FileOut, "   Commission: %f\n", ACSTrade.Commission);	
	} // end for ACSTrade
	
	//s_SCOrderFillData: Order fill information. Completed individual order actions.
	//Last entry index is newest entry.
	ListSize = sc.GetOrderFillArraySize();
	for(i=0; i<ListSize; i++) {
		PrintCount++;
		sc.GetOrderFillEntry(i, OrderFillData);
		fprintf(FileOut, "\ns_SCOrderFillData: %d (%s)\n", i, (sc.SendOrdersToTradeService==0?"Simulation":"Live Trading"));
		fprintf(FileOut, "   Symbol: %s\n", OrderFillData.Symbol.GetChars());
		fprintf(FileOut, "   TradeAccount: %s\n", OrderFillData.TradeAccount.GetChars());
		fprintf(FileOut, "   InternalOrderID: %d\n", OrderFillData.InternalOrderID);
		fprintf(FileOut, "   BuySell: %d (%s)\n", OrderFillData.BuySell, (OrderFillData.BuySell==BSE_BUY?"BSE_BUY":"BSE_SELL"));
		fprintf(FileOut, "   Quantity: %d\n", OrderFillData.Quantity);
		fprintf(FileOut, "   AverageFillPrice: %f\n", OrderFillData.AverageFillPrice);
		OrderFillData.FillDateTime.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);
		fprintf(FileOut, "   FillDateTime: %04d-%02d-%02d %02d:%02d.%02d\n",  Year, Month, Day, Hour, Minute, Second);
	} //end for OrderFillData
	
	//finish out
	fprintf(FileOut, "\n========== %s ====================\n", TimeStr);
	fclose(FileOut); //close output log
	return PrintCount;
} //end int debug_PrintOrders


//Keep track of entry times into a position. If too many too fast, throw an alert.
//Time1, Time2, Time3 need to be initialized to 0 first in the main code.
//time(NULL) returns the number of seconds since the unix epoch.
//Since there is no roll over day math with time(NULL), it is very easy to use here.
char FlipFlopAlert(const unsigned int Seconds, int *Time1, int *Time2, int *Time3) {
	//Shift and add a new time.
	*Time3 = *Time2;
	*Time2 = *Time1;
	*Time1 = time(NULL); //time right now
	//Nothing to do if values aren't fully filled in.
	if( (*Time3 == 0) || (*Time2 == 0) ) {return 0;}
	//Calculate the alert.
	if( (*Time1 - *Time3) <= Seconds ) {return 1;} //alert triggered
	return 0; //not an alert
} //end char FlipFlopAlert


//Disable or enable blocking variables.
//What's the point in these variables if they don't allow simple order management?
void SetBlockingVariables(SCStudyInterfaceRef sc, const int Status) {
	if(Status > 0) { //safety on
		sc.AllowOnlyOneTradePerBar = true;
		sc.AllowMultipleEntriesInSameDirection = false;
		sc.AllowEntryWithWorkingOrders = false;
		sc.AllowOppositeEntryWithOpposingPositionOrOrders = false;
		sc.CancelAllOrdersOnEntriesAndReversals = true;
		}
	else { //safety off
		sc.AllowOnlyOneTradePerBar = false;
		sc.AllowMultipleEntriesInSameDirection = true;
		sc.AllowEntryWithWorkingOrders = true;
		sc.AllowOppositeEntryWithOpposingPositionOrOrders = true;
		sc.CancelAllOrdersOnEntriesAndReversals = false;
		}
} //end void SetBlockingVariables


//Test to see if an order is active. If so, cancel it and log a message.
//This is used to reset a persistent OrderID variable and not cause the message log to pop up if it doesn't exist.
//This is usually called in safety and clean up code to make sure there aren't any unwanted leftovers.
int CancelOrderAndLog(SCStudyInterfaceRef sc, const int OrderID, const char *Name) {
int RC;
char TempStr[100+1];
SCString LogText;
s_SCTradeOrder TradeOrder;
if(OrderID != 0) {
	if( sc.GetOrderByOrderID(OrderID, TradeOrder) ) {
		if(IsWorkingOrderStatus(TradeOrder.OrderStatusCode)) {
			RC = sc.CancelOrder(OrderID);
			LogText.Format("%s %s Cancel: %s (%s) (OrderID=%d RC=%d).", TradeOrder.Symbol.GetChars(), (TradeOrder.BuySell==BSE_BUY?"Buy":"Sell"), Name, OrderTypeToString(TradeOrder.OrderTypeAsInt, TempStr, 100), OrderID, RC);
			sc.AddMessageToLog(LogText, 0);
			}
		}
	}
return 0;
} //end int CancelOrderAndLog


//Used with the "Time Exit" feature to check and add a day if the intraday time has already passed.
//Returns a double in SCDateTime format.
SCDateTime HandleTimeExitSetup(SCStudyInterfaceRef sc, const int TimeInSeconds2) {
	SCDateTime DateTime1, DateTimeTemp; //double containing days.seconds
	if(TimeInSeconds2 <= 0) {return 0.0;} //nothing to do, disable.
	//Get the time now.
	DateTime1 = sc.CurrentSystemDateTime;
	//Build the full SC date/time variable for today.
	DateTimeTemp.SetDateTime(DateTime1.GetDate(), TimeInSeconds2);
	//Test if time right now is after or before.
	if(DateTime1.GetTime() > TimeInSeconds2) {return DateTimeTemp + (1.0 * DAYS);} //add one day
	else {return DateTimeTemp;} //no change
} //end double HandleTimeExitSetup


//Easier way to delete chart drawings with logging if DebugNumber>0.
//DebugNumber is just a chosen index number to see which delete got called in the main code. Set to 0 to disable.
//Usual call: LineNumber = DeleteChartDrawing(). That will reset any persistent LineNumber to 0.
char DeleteChartDrawing(SCStudyInterfaceRef sc, const int LineNumber, const int DebugNumber) {
	int RC;
	SCString LogText;
	if(LineNumber == 0) {return 0;} //nothing to do
	if(LineNumber > 0) {RC = sc.DeleteACSChartDrawing(sc.ChartNumber, TOOL_DELETE_CHARTDRAWING, LineNumber);}
	else {RC = sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, LineNumber);}
	if(DebugNumber > 0) {
		LogText.Format("INFO: %s chart drawing deleted Chart#=%d Line#=%d RC=%d Debug=%d", (LineNumber>0?"ACSIL":"User"), sc.ChartNumber, LineNumber, RC, DebugNumber);
		sc.AddMessageToLog(LogText, 0);
		}
	return 0;
} //end int DeleteChartDrawing








//Custom study starts here.
SCSFExport scsf_BrettsMultiFunctionTrailingStop(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_SafetyStop = sc.Subgraph[0];
	SCSubgraphRef Graph_MATrailingStop = sc.Subgraph[1];
	SCSubgraphRef Graph_MATSLeadingEdge = sc.Subgraph[2];
	SCSubgraphRef Graph_PriceMA = sc.Subgraph[3];
	SCSubgraphRef Graph_LongEntry = sc.Subgraph[4];
	SCSubgraphRef Graph_LongExit = sc.Subgraph[5];
	SCSubgraphRef Graph_ShortEntry = sc.Subgraph[6];
	SCSubgraphRef Graph_ShortExit = sc.Subgraph[7];

	SCInputRef In_Enabled = sc.Input[0];
	SCInputRef InFlag_ServerConnectionState = sc.Input[1];
	SCInputRef InFlag_IsAutoTradingEnabled = sc.Input[2];
	SCInputRef InFlag_IsChartTradeModeOn = sc.Input[3];
	SCInputRef InFlag_GlobalTradeSimulationIsOn = sc.Input[4];
	SCInputRef InFlag_SendOrdersToTradeService = sc.Input[5];
	SCInputRef InFlag_LiveTradingEnabled = sc.Input[6];
	SCInputRef InFlag_TradeDirection = sc.Input[7];
	SCInputRef InFlag_Volume = sc.Input[8];
	SCInputRef InFlag_ManagingATrade = sc.Input[9];
	SCInputRef In_SimulationMode = sc.Input[10];
	SCInputRef In_ClearChartOnTradeExit = sc.Input[11];
	SCInputRef In_PriceInputData = sc.Input[12];
	SCInputRef In_PriceInputBias = sc.Input[13];
	SCInputRef In_PriceMAPeriod = sc.Input[14];
	SCInputRef In_PriceMAMAType = sc.Input[15];
	SCInputRef In_CancelAllOtherOrders = sc.Input[16];
	SCInputRef In_MaximumPositionAllowed = sc.Input[17];
	SCInputRef In_TradeManagementStart = sc.Input[18];
	SCInputRef In_MATrailingStopValueType = sc.Input[19];
	SCInputRef In_MATrailingStop = sc.Input[20];
	SCInputRef In_SafetyStopValueType = sc.Input[21];
	SCInputRef In_SafetyStop = sc.Input[22];
	SCInputRef In_ExitTrendLineEnable = sc.Input[23];
	SCInputRef In_ExitTrendLineColor = sc.Input[24];
	SCInputRef In_ExitTrendLineWidth = sc.Input[25];
	SCInputRef In_PriceTargetValueType = sc.Input[26];
	SCInputRef In_PriceTarget = sc.Input[27];
	SCInputRef In_PriceTargetOrderType = sc.Input[28];
	SCInputRef In_PriceTargetLineColor = sc.Input[29];
	SCInputRef In_PriceTargetLineWidth = sc.Input[30];
	SCInputRef In_TimeExit = sc.Input[31];
	SCInputRef In_WeekendExitTime = sc.Input[32];
	SCInputRef In_WeekendExitDay = sc.Input[33];
	
	SCInputRef In_DebugPrintOrders = sc.Input[34];
	
	//remember local variables are not persistent.
	int i, IndexEnd, RC, ListSize, OrderType, SafetyStopOrderTrigger, PriceTargetOrderTrigger;
	int Hour, Minute, Second;
	float PriceCurrent, PriceTemp, SafetyStopPrice;
	char TempStr[100+1];
	
	//for debug
	#if DEBUGON > 0
	FILE *FileOut;
	SCDateTime TimeNow;
	char TimeStr[30+1];
	#endif
	
	int& pPriceInputData = sc.GetPersistentInt(0);
	int& pIndexLast = sc.GetPersistentInt(1);
	int& pResetIssued = sc.GetPersistentInt(2);
	int& pManagingATrade = sc.GetPersistentInt(3);
	int& pExitingATrade = sc.GetPersistentInt(4);
	int& pTradeStartBar = sc.GetPersistentInt(5);
	int& pTradeDirection = sc.GetPersistentInt(6);
	int& pVolumePrevious = sc.GetPersistentInt(7);
	int& pPriceTargetOrderID = sc.GetPersistentInt(8);
	int& pPriceTargetOrderType = sc.GetPersistentInt(9);
	int& pPriceTargetOrderTypePrevious = sc.GetPersistentInt(10);
	int& pPriceTargetValueTypePrevious = sc.GetPersistentInt(11);
	int& pPriceTargetLineNumber = sc.GetPersistentInt(12);
	int& pSafetyStopOrderID = sc.GetPersistentInt(13);
	int& pSafetyStopValueTypePrevious = sc.GetPersistentInt(14);
	int& pWeekendExitTimeSeconds = sc.GetPersistentInt(15);
	int& pWeekendExitDay = sc.GetPersistentInt(16);
	int& pExitTrendLineLineNumber = sc.GetPersistentInt(17);
	int& pExitTrendLineX1 = sc.GetPersistentInt(18);
	int& pExitTrendLineX2 = sc.GetPersistentInt(19);
	int& pTime1 = sc.GetPersistentInt(20);
	int& pTime2 = sc.GetPersistentInt(21);
	int& pTime3 = sc.GetPersistentInt(22);
	
	float& pMATrailingStopOffset = sc.GetPersistentFloat(0);
	float& pMATrailingStopPriceHold = sc.GetPersistentFloat(1);
	float& pSafetyStopOffset = sc.GetPersistentFloat(2);
	float& pSafetyStopPrevious = sc.GetPersistentFloat(3);
	float& pPriceTarget = sc.GetPersistentFloat(4);
	float& pPriceTargetPrevious = sc.GetPersistentFloat(5);
	float& pExitTrendLineY1 = sc.GetPersistentFloat(6);
	float& pExitTrendLineY2 = sc.GetPersistentFloat(7);
	float& pExitTrendLineSlope = sc.GetPersistentFloat(8);
	
	double& pPriceTargetHold = sc.GetPersistentDouble(0); //TradeOrder.Price1 is a double
	
	SCDateTime& pTimeExit = sc.GetPersistentSCDateTime(0);
	
	SCString LogText;
	s_SCNewOrder NewOrder;
	s_SCPositionData PositionData;
	s_SCTradeOrder TradeOrder;
	s_ACSTrade ACSTrade;
	s_SCOrderFillData OrderFillData;
	s_UseTool Tool;
	
	//also (4000 of each):
	//__int64& sc.GetPersistentInt64()
	//void*& sc.GetPersistentPointer()
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		#if DEBUGON > 0
		debug_DataTypeSizes(); //show variable size limitations
		#endif
		
		//Long descriptive name.
		sc.GraphName = "Trade: Brett's Multi-Function Trailing Stop";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;

		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.GraphRegion = 0; //main price graph
		sc.ValueFormat = VALUEFORMAT_INHERITED; //Setting for decimal places.
		sc.ScaleRangeType = SCALE_SAMEASREGION; //make sure the graphs line up with the bars.
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//Trading Settings. Start locked down.
		sc.CalculationPrecedence = VERY_LOW_PREC_LEVEL; //other dependent studies get calculated first.
		sc.MaintainTradeStatisticsAndTradesData = true; //needed for trading functions.
		sc.AllowOnlyOneTradePerBar = true; //throttle, but this is really only one "order" per bar.
		sc.AllowMultipleEntriesInSameDirection = false; //one trade managed at a time.
		sc.AllowEntryWithWorkingOrders = false; //one trade managed at a time.
		sc.SupportReversals = false; //don't close out more than you have in the order.
		sc.AllowOppositeEntryWithOpposingPositionOrOrders = false; //don't trade against yourself on the same chart.
		sc.SupportAttachedOrdersForTrading = false; //don't use attach orders from the chart Trading Window.
		sc.UseGUIAttachedOrderSetting = false; //don't use attach orders from the chart Trading Window.
		sc.CancelAllOrdersOnEntriesAndReversals = true; //start fresh going in.
		sc.CancelAllWorkingOrdersOnExit = true; //allows for exits with attached orders.
		
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Brett Johnson\'s Multi-Function Trailing Stop. Copyright 2015 under GNU GPL v1. If you use this code in your own program, share it like I have. This program provides a trailing stop based on a moving average. This helps prevent premature exits caused by \"bar whiskers\" and some stop running. There is also:<ul><li>A traditional trailing stop further away for safety.<li>An exit trend line useful for catching channel break outs.<li>A price target feature.<li>An exit based on the time of day (such as closing).<li>An exit based on the end of the trading week (avoiding weekend gaps).</ul>\
<p>Note For Lawyers: The goal of this trading program is to keep losses small and let winners run. While this code has been written as solid as possible with many extra safeties in the code, every possible scenario cannot be accounted for. It will also not protect from bad trades 100% of the time. It will not make a bad trading plan into a good one. It is not a magic black box with unlimited profits. There will be money lost. Hopefully losses will be limited and the gains will be far more. There is no warranty expressed nor implied. This trading program is open sourced. If you have questions about programming competency or how it works, source code can be easily checked. There is also extensive documentation in the \"Display Study Documentation\" button on how things work and the quirks of the program.\
<p>By using this program, you first agree to test it out in simulation mode. While the conceptual operation is quite simple, some of the actions will be unexpected. I wrote this program and some of the actions caught me off guard. When there is real money on the line, always test first.\
<p>Functionality and Observations\
<p>Sierra Chart must be up and running and connected to the trade service to manage trades. A connection loss to the trade server will mean that the watched orders will go unmanaged and may go horribly wrong. Always use the Safety Trailing Stop option as it will leave a protection Stop at the trade server that does not depend on Sierra Chart connectivity. Note that since the Safety Trailing Stop is on the trade server, it will execute much faster than Sierra Chart triggering an exit order. The Safety Trailing Stop is a traditional Trailing Stop managed by Sierra Chart (not this program) and will be triggered by any price action hitting it. Sierra Chart manages its Trailing Stop by periodically moving a fixed Stop on the trade server.\
<p>Make sure there is at least enough data for the \"Price MA Smoothing Period\" before trading.\
<p>This program is for managing a single order after it has been opened. Multiple trades going in will be treated as an overall single trade. This may not have the desired effect you were expecting.\
<p>On the chart, up arrows are used for long positions and down arrows are used for short positions. A green arrow shows order entry. A red arrow shows order exit.\
<p>The Message Log is used to record entry, exit, and notable changes. If there is an error, the Message Log will pop up with a description of the problem.\
<p>The Settings window has a bunch of Flag values at the top. The Flags are set from Sierra Chart\'s current internal settings. Changing them in the Settings window will do nothing. The point of the Flags is to report Sierra Chart settings in one convenient location and show if trade management will be enabled or not. Set \"MA Trailing Stop Offset\" to 0.0 (disabled) to check Flag values before trading. Some values may not change until the Settings window is closed and then reopened.\
<p>This program will wait in standby mode for an order to appear. After that, it will start managing it. Check the Flags in the Settings window to make sure detected trade values are correct. When the order closes for any reason, this program will go back into standby mode waiting for the next order.\
<p>The MA Trailing Stop is based on a distance from the Price MA line instead of price bars. If the bar price crosses the Price MA line, nothing will happen. This is to help keep noise from causing a premature exit. Note that the Price MA\'s smoothing period should not be set too high or it will cause significant lag during a high volume jump that will exit the trade late. At the same time, a less noisy price line will allow for tighter stops. If the Price MA line crosses the MA Trailing Stop line, then the MA Trailing Stop will be triggered. The same will happen if the Price MA line crosses the Exit Trend Line. All orders will be flattened and pending orders will be canceled. This leaves a clean chart for the next trade.\
<p>If there is an event that causes a graph reset, a redraw will be issued. The redrawn trailing stop lines will be close but not be exactly as they were before due to all the live data not being saved. The Safety Trailing Stop will jump a little at the end of the redraw because of rounding to the nearest tick and the variables realigning over the next few bars. It also is not possible to reset a Safety Trailing Stop with the same price distance information as before, so it might step backwards.\
<p>Warning: Changing the chart time period (like from 1m to 5m) will redraw the Price MA line using different bar data and could trigger an early stop out. If you need to see multiple time frames, duplicate your chart window before this program starts and leave this program running in it undisturbed.\
<p>Warning: if there are multiple open orders not generated by this program, behavior will be undefined. Early partial exit orders could screw up the Price Target feature. A partial Stop order could screw up the Safety Trailing Stop feature. In this case it would very likely create unwanted positions in an unwanted direction. Use the \"Cancel All Other Orders On Entry\" feature to stop this from happening. Note again that this program was designed to manage a single order at a time. Adding additional pending orders after order management has started may cause undefined behavior.\
<p>The Price Target horizontal line can be dragged and changed on the chart and this program will follow it. The Safety Trailing Stop is constantly moving and much more complicated to keep track of. This program cannot reliably track it. If you move it on the chart, it will be moved back during a reset. This may not be a desired behavior. If you need to change the Safety Trailing Stop, do it in the Settings window.\
<p>This program has a safety order limiter in place. If there are 3 new position entries and exits within 15 seconds, this program will disable itself. This helps prevent massive losses in commissions from multiple automated bad position entries that might never stop until someone manually pulls the plug. Be warned that the entered positions will no longer be managed. The automated entry program should also have a safety similar to this. Some might call this an Order Exit Circuit Breaker to prevent costly race conditions.\
<p>Replay Notes. The time exit features will not work in any Back Test or Replay Mode. This program uses sc.CurrentSystemDateTime to set the time exit variables. The sc.CurrentSystemDateTime variable always returns current time and not Replay time. There is no clean way to get around this limitation. When you are finished with Replay testing, double check the Settings window to make sure this program is set up for your normal operations. It is recommended to run Replays and Back Tests in a separate chart window to avoid conflicts with your normal trade settings.\
<p>The rest of the program functionality is described in the Input Descriptions blocks.";
		
		//Output Graphs
		
		//To avoid confusion, going long is always up arrows, short is down. Entry is green. Exit is red.
		
		Graph_LongEntry.Name = "Long Entry";
		Graph_LongEntry.PrimaryColor = RGB(0, 255, 0);
		Graph_LongEntry.DrawStyle = DRAWSTYLE_ARROWUP;
		Graph_LongEntry.LineWidth = 4;
		Graph_LongEntry.DrawZeros = 0;
		Graph_LongEntry.DisplayNameValueInWindowsFlags = 0;
		
		Graph_LongExit.Name = "Long Exit";
		Graph_LongExit.PrimaryColor = RGB(255, 0, 0);
		Graph_LongExit.DrawStyle = DRAWSTYLE_ARROWUP;
		Graph_LongExit.LineWidth = 4;
		Graph_LongExit.DrawZeros = 0;
		Graph_LongExit.DisplayNameValueInWindowsFlags = 0;
		
		Graph_ShortEntry.Name = "Short Entry";
		Graph_ShortEntry.PrimaryColor = RGB(0, 255, 0);
		Graph_ShortEntry.DrawStyle = DRAWSTYLE_ARROWDOWN;
		Graph_ShortEntry.LineWidth = 4;
		Graph_ShortEntry.DrawZeros = 0;
		Graph_ShortEntry.DisplayNameValueInWindowsFlags = 0;
		
		Graph_ShortExit.Name = "Short Exit";
		Graph_ShortExit.PrimaryColor = RGB(255, 0, 0);
		Graph_ShortExit.DrawStyle = DRAWSTYLE_ARROWDOWN;
		Graph_ShortExit.LineWidth = 4;
		Graph_ShortExit.DrawZeros = 0;
		Graph_ShortExit.DisplayNameValueInWindowsFlags = 0;
		
		Graph_PriceMA.Name = "Price MA"; //drawn graphs must have a name.
		Graph_PriceMA.PrimaryColor = RGB(255, 255, 255);
		Graph_PriceMA.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		Graph_PriceMA.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_PriceMA.LineWidth = 2;
		Graph_PriceMA.DrawZeros = 0;
		
		Graph_MATSLeadingEdge.Name = "MA Trailing Stop Leading Edge"; //drawn graphs must have a name.
		Graph_MATSLeadingEdge.PrimaryColor = RGB(255, 255, 0);
		Graph_MATSLeadingEdge.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		Graph_MATSLeadingEdge.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MATSLeadingEdge.LineWidth = 2;
		Graph_MATSLeadingEdge.DrawZeros = 0;
		
		Graph_MATrailingStop.Name = "MA Trailing Stop"; //drawn graphs must have a name.
		Graph_MATrailingStop.PrimaryColor = RGB(255, 0, 0);
		Graph_MATrailingStop.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		Graph_MATrailingStop.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MATrailingStop.LineWidth = 2;
		Graph_MATrailingStop.DrawZeros = 0;
		
		Graph_SafetyStop.Name = "Safety Stop"; //drawn graphs must have a name.
		Graph_SafetyStop.PrimaryColor = RGB(192, 0, 0);
		Graph_SafetyStop.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		Graph_SafetyStop.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_SafetyStop.LineWidth = 3;
		Graph_SafetyStop.DrawZeros = 0;
		
		
		//User Inputs
		
		In_Enabled.Name = "Did you read the instructions?";
		In_Enabled.SetYesNo(0);
		In_Enabled.SetDescription("Enables trading operations.");
		
		InFlag_ServerConnectionState.Name = "FLAG: File >> Connect To Data Feed";
		InFlag_ServerConnectionState.SetYesNo(sc.ServerConnectionState);
		InFlag_ServerConnectionState.SetDescription("Needs \"Yes\".<p>This is a flag value shown for convenience. Changing this value here does nothing. Go to the menu option to make the change. Note that some flags affect other flags. Close and reopen settings to see if the new value took.");
		
		InFlag_IsAutoTradingEnabled.Name = "FLAG: Trade >> Auto Trading Enabled";
		InFlag_IsAutoTradingEnabled.SetYesNo(sc.IsAutoTradingEnabled);
		InFlag_IsAutoTradingEnabled.SetDescription("Needs \"Yes\".<p>This is a flag value shown for convenience. Changing this value here does nothing. Go to the menu option to make the change. Note that some flags affect other flags. Close and reopen settings to see if the new value took.");
		
		InFlag_IsChartTradeModeOn.Name = "FLAG: Trade >> Chart Trade Mode On";
		InFlag_IsChartTradeModeOn.SetYesNo(sc.IsChartTradeModeOn);
		InFlag_IsChartTradeModeOn.SetDescription("Needs \"Yes\". This allows SC to control the Safety Trailing Stop.<p>This is a flag value shown for convenience. Changing this value here does nothing. Go to the menu option to make the change. Note that some flags affect other flags. Close and reopen settings to see if the new value took.");
		
		InFlag_GlobalTradeSimulationIsOn.Name = "FLAG: Trade >> Trade Simulation Mode On";
		InFlag_GlobalTradeSimulationIsOn.SetYesNo(sc.GlobalTradeSimulationIsOn);
		InFlag_GlobalTradeSimulationIsOn.SetDescription("Sim mode on for testing, off for live trades.<p>This is a flag value shown for convenience. Changing this value here does nothing. Go to the menu option to make the change. Note that some flags affect other flags. Close and reopen settings to see if the new value took.");
		
		InFlag_SendOrdersToTradeService.Name = "FLAG: Send Orders To Trade Service (Sim Mode)";
		InFlag_SendOrdersToTradeService.SetYesNo(sc.SendOrdersToTradeService);
		InFlag_SendOrdersToTradeService.SetDescription("Sim mode on for testing, off for live trades.<p>This is a flag value shown for convenience. Changing this value here does nothing. Go to the settings option below to make the change. Note that some flags affect other flags. Close and reopen settings to see if the new value took.");
		
		InFlag_LiveTradingEnabled.Name = "FLAG: Live Trading Enabled";
		InFlag_LiveTradingEnabled.SetColor(255, 0, 0);
		InFlag_LiveTradingEnabled.SetDescription("Shows if settings allow for live trading (green).<p>This is a flag value shown for convenience. Changing this value here does nothing. Close and reopen settings to see if the new value took.");
		
		InFlag_TradeDirection.Name = "FLAG: Detected Trade Direction";
		InFlag_TradeDirection.SetCustomInputIndex(TD_None);
		InFlag_TradeDirection.SetCustomInputStrings("None;Long;Short");
		InFlag_TradeDirection.SetDescription("Shows detected trade direction. Will show \"None\" if there isn't an active trade.<p>This is a flag value shown for convenience. Changing this value here does nothing. Close and reopen settings to see the new value.");
		
		InFlag_Volume.Name = "FLAG: Detected Volume";
		InFlag_Volume.SetInt(0);
		InFlag_Volume.SetDescription("Shows detected volume if an active trade is found.<p>This is a flag value shown for convenience. Changing this value here does nothing. Close and reopen settings to see the new value.");
		
		InFlag_ManagingATrade.Name = "FLAG: Actively Managing A Trade";
		InFlag_ManagingATrade.SetColor(255, 0, 0);
		InFlag_ManagingATrade.SetDescription("Shows if this program is managing a found trade (green).<p>This is a flag value shown for convenience. Changing this value here does nothing. Close and reopen settings to see if the new value took.");
		
		In_SimulationMode.Name = "Simulation Mode?";
		In_SimulationMode.SetYesNo(1);
		In_SimulationMode.SetDescription("Sets trading operations to be done in simulation mode.");
		
		In_ClearChartOnTradeExit.Name = "Clear Chart On Trade Exit?";
		In_ClearChartOnTradeExit.SetYesNo(0);
		In_ClearChartOnTradeExit.SetDescription("Removes trade items this program has drawn to the chart on position exit.");
		
		In_PriceInputData.Name = "Price Input Data";
		In_PriceInputData.SetInputDataIndex(SC_HLC);
		In_PriceInputData.SetDescription("Usually \"HLC Avg\" for Typical Price. This is less likely to cause a false exit than using Close.");
		
		In_PriceInputBias.Name = "Price Input Bias?";
		In_PriceInputBias.SetYesNo(1);
		In_PriceInputBias.SetDescription("Sets the Price MA line to Input Low on long orders and Input High on short orders. This shifts the Price MA line from center to the outer edge closest to the exit line. It will cause an exit sooner than if Price MA is in the middle of the bar with typical price (HLA Avg). Note that the High/Low jump on order entry may trigger an exit if it set too close.");
		
		In_PriceMAPeriod.Name = "Price MA Smoothing Period";
		In_PriceMAPeriod.SetInt(2);
		In_PriceMAPeriod.SetIntLimits(2, 1000);
		In_PriceMAPeriod.SetDescription("Number of bars for the period. Usually 2-10.");
		
		In_PriceMAMAType.Name = "Price MA Moving Average Type";
		In_PriceMAMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_PriceMAMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_CancelAllOtherOrders.Name = "Cancel All Other Orders On Entry";
		In_CancelAllOtherOrders.SetYesNo(1);
		In_CancelAllOtherOrders.SetDescription("When an order is found, this will cancel all other pending orders to clean up the chart and prevent conflicts that may cause unexpected behavior. This is mandatory for normal behavior.");
		
		In_MaximumPositionAllowed.Name = "Maximum Position Allowed";
		In_MaximumPositionAllowed.SetInt(10);
		In_MaximumPositionAllowed.SetIntLimits(1, 1000000);
		In_MaximumPositionAllowed.SetDescription("Safety setting. Maximum number of contracts/lots/shares allowed in the order. When an order is found, this will be set to the volume found. It can be reset for safety afterwards. This setting mainly prevents other programs from increasing the order size.");
		
		In_TradeManagementStart.Name = "Trade Management Start Point";
		In_TradeManagementStart.SetCustomInputIndex(0);
		In_TradeManagementStart.SetCustomInputStrings("Start Of Trade;Right Now");
		In_TradeManagementStart.SetDescription("\"Start Of Trade\" for when the trade was first executed. \"Right Now\" for starting the managing right now.");
		
		
		
		In_MATrailingStopValueType.Name = "MA Trailing Stop Value Type";
		In_MATrailingStopValueType.SetCustomInputIndex(0);
		In_MATrailingStopValueType.SetCustomInputStrings("Offset;Percent;Absolute");
		In_MATrailingStopValueType.SetDescription("\"Offset\" for an offset from the entry price. \"Percent\" (where 1.0 is 100%) for a percent difference from the entry price. \"Absolute\" for entering an exact price that will be converted to an Offset so a second run in the loop won't give a bad value.");
		
		In_MATrailingStop.Name = "MA Trailing Stop";
		In_MATrailingStop.SetFloat(0.0);
		In_MATrailingStop.SetFloatLimits(0.0, 1000000.0);
		In_MATrailingStop.SetDescription("Price distance from the Price MA line for the trailing stop. Set to 0.0 to disable this entire study but have the flags updated (as in, use 0.0 for setting up).");
		
		
		
		In_SafetyStopValueType.Name = "Safety Trailing Stop Value Type";
		In_SafetyStopValueType.SetCustomInputIndex(0);
		In_SafetyStopValueType.SetCustomInputStrings("Offset;Percent;Absolute");
		In_SafetyStopValueType.SetDescription("\"Offset\" for an offset from the entry price. \"Percent\" (where 1.0 is 100%) for a percent difference from the entry price. \"Absolute\" for entering an exact price that will be converted to an Offset so a second run in the loop won't give a bad value.");
		
		In_SafetyStop.Name = "Safety Trailing Stop";
		In_SafetyStop.SetFloat(0.0);
		In_SafetyStop.SetFloatLimits(0.0, 1000000.0);
		In_SafetyStop.SetDescription("Sets the Safety Trailing Stop price. This should be larger than the MA Trailing Stop to avoid getting stopped out early. Set to 0.0 to disable. Disabled is not recommended but will hide stops from the trading service. There will be no safety stop on the trade server if disconnected from trading service (EXTREMELY DANGEROUS).");
		
		
		
		In_ExitTrendLineEnable.Name = "Exit Trend Line Enable?";
		In_ExitTrendLineEnable.SetYesNo(1);
		In_ExitTrendLineEnable.SetDescription("Draws a trend line on the chart. When Price MA crosses it, an exit is triggered. Note that deleting the line from the chart will not cancel its effects. To disable the line after it is created, turn it off here.");
		
		In_ExitTrendLineColor.Name = "Exit Trend Line Color";
		In_ExitTrendLineColor.SetColor(0, 255, 255);
		In_ExitTrendLineColor.SetDescription("Draw the trend line in this color.");
		
		In_ExitTrendLineWidth.Name = "Exit Trend Line Width";
		In_ExitTrendLineWidth.SetInt(2);
		In_ExitTrendLineWidth.SetIntLimits(1, 10);
		In_ExitTrendLineWidth.SetDescription("Draw the trend line at this width.");
		
		
		In_PriceTargetValueType.Name = "Price Target Value Type";
		In_PriceTargetValueType.SetCustomInputIndex(0);
		In_PriceTargetValueType.SetCustomInputStrings("Offset;Percent;Absolute");
		In_PriceTargetValueType.SetDescription("\"Offset\" for an offset from the entry price. \"Percent\" (where 1.0 is 100%) for a percent difference from the entry price. \"Absolute\" for entering an exact price that will be converted to an Offset so a second run in the loop won't give a bad value.");
		
		In_PriceTarget.Name = "Price Target";
		In_PriceTarget.SetFloat(0.0);
		In_PriceTarget.SetFloatLimits(0.0, 1000000.0);
		In_PriceTarget.SetDescription("Sets an exit target price. 0.0 to disable. The MA Trailing Stop will take care of normal trade exits, probably better than a target price.");
		
		In_PriceTargetOrderType.Name = "Price Target Order Type";
		In_PriceTargetOrderType.SetCustomInputIndex(1);
		In_PriceTargetOrderType.SetCustomInputStrings("Market;Limit;Stealth");
		In_PriceTargetOrderType.SetDescription("\"Market\" for a Market If Touched order. \"Limit\" for a limit order. \"Stealth\" to keep the order hidden from the trade service and to have this program execute it as a market order once the price is hit. Note that a price target miss would be caught by the MA Trailing Stop.");
		
		In_PriceTargetLineColor.Name = "Price Target Stealth Line Color";
		In_PriceTargetLineColor.SetColor(0, 255, 0);
		In_PriceTargetLineColor.SetDescription("If this program controls the price target in Stealth mode, it will draw a line of this color at the target level.");
		
		In_PriceTargetLineWidth.Name = "Price Target Stealth Line Width";
		In_PriceTargetLineWidth.SetInt(2);
		In_PriceTargetLineWidth.SetIntLimits(1, 10);
		In_PriceTargetLineWidth.SetDescription("If this program controls the price target in Stealth mode, it will draw a line of this width at the target level.");
		
		
		In_TimeExit.Name = "Trading Exit Time";
		In_TimeExit.SetTime(0); //also SetTime(HMS_TIME(15, 55, 0))
		In_TimeExit.SetDescription("Time of day to automatically exit a trade using 24 hour time. \"0:00\" to disable. This is usually just before market close for stocks and before the rollover time for forex. If using the day close, always choose a few minutes before to give the order time to clear. If you use the exact closing time then the order will be submitted after the market has closed and will fail. Orders entered after the exit time will be set to exit the next day. That could be the weekend, so pay attention. Some markets like forex will be opened or closed on the weekend depending on your time zone. This program cannot determine holidays, so make accommodations accordingly. Do not go into the Settings Window or cause a full recalculation close to the exit time. That may cause the date to be recalculated for tomorrow and miss your exit.");
		
		
		In_WeekendExitTime.Name = "Weekend Exit Time";
		In_WeekendExitTime.SetTime(0); //also SetTime(HMS_TIME(15, 55, 0))
		In_WeekendExitTime.SetDescription("Time of day on the last trading day of the week to automatically exit a trade using 24 hour time. \"0:00\" to disable. This function is intended to exit a position at the end of a trading week to avoid any price gaps that may occur over the weekend. It can be used to exit a position earlier in the week, but make sure the time and day are reset for the next trade. Note that any order entry after the set time and day will cause an immediate exit which is why mid-week settings need to be reset. If using the day close, always choose a few minutes before to give the order time to clear. If you use the exact closing time then the order will be submitted after the market has closed and will fail. Some markets like forex will be opened or closed on the weekend depending on your time zone. Make sure the exit time and day are set for when the market is open. This program cannot determine holidays, so make accommodations accordingly. Do not go into the Settings Window or cause a full recalculation close to the exit time. That may cause the exit time to be missed.");
		
		In_WeekendExitDay.Name = "Weekend Exit Day";
		In_WeekendExitDay.SetCustomInputIndex(5);
		In_WeekendExitDay.SetCustomInputStrings("Sunday;Monday;Tuesday;Wednesday;Thursday;Friday;Saturday");
		In_WeekendExitDay.SetDescription("The last trading day of the week.");
		
		
		
		
		
		
		In_DebugPrintOrders.Name = "DEBUG: Print Orders";
		In_DebugPrintOrders.SetYesNo(0);
		In_DebugPrintOrders.SetDescription("Prints out the orders to the debug log in the Data dir. This is a one time operation and not needed for normal use.");
		
		//sc.UpdateAlways = 1; //controlled inside the program.
		//Set in: Global Settings >> General Settings >> Chart Update Interval.
		//Set in: Chart >> Chart Settings >> Advanced Settings >> Chart Update Interval In Milliseconds
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	//Last call to function (destructor). This must be at the top to make sure it gets executed.
	if(sc.LastCallToFunction) {
		//Remove Exit Trend Line if it was created.
		if(pExitTrendLineLineNumber != 0) {DeleteChartDrawing(sc, pExitTrendLineLineNumber, 0);}
		return;
		}
	
	//Nothing to do if disabled.
	if(In_Enabled.GetYesNo() == 0) {return;}
	
	//Reload variables.
	i = sc.Index;
	IndexEnd = sc.ArraySize - 1;
	
	//If first run.
	//Keep this high in the code so it gets executed.
	if (i == 0) {
		//Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_PriceMAPeriod.GetInt() - 1;
		//Price input data starting out.
		if(In_PriceInputBias.GetYesNo()) {
			if(pTradeDirection == TD_Long) {pPriceInputData = SC_LOW;}
			else if(pTradeDirection == TD_Short) {pPriceInputData = SC_HIGH;}
			else {pPriceInputData = In_PriceInputData.GetInputDataIndex();} //TD_None, user choice for now.
			}
		else {pPriceInputData = In_PriceInputData.GetInputDataIndex();}
		//Maximum position allowed. Taken care of elsewhere.
		//sc.MaximumPositionAllowed = In_MaximumPositionAllowed.GetInt();
		//Scaling must be outside of the sc.SetDefaults code block since they have a dependency upon an actual chart object existing.
		sc.SupportTradingScaleIn = 0;
		sc.SupportTradingScaleOut = 0;
		//DO NOT initialize persistent variables. If there's a reset, any previous data will be lost.
		//pResetIssued = 0; pManagingATrade = 0; pTradeStartBar = 0;
		//Set In_TimeExit and weekend exit to real dates for the time exit function.
		pTimeExit = HandleTimeExitSetup(sc, In_TimeExit.GetTime());
		pWeekendExitTimeSeconds = In_WeekendExitTime.GetTime();
		pWeekendExitDay = In_WeekendExitDay.GetIndex();
		//return;
		}
	
	//Price line smoothing.
	//Keep this high in the code so it gets executed.
	sc.MovingAverage(sc.BaseDataIn[pPriceInputData], Graph_PriceMA, In_PriceMAMAType.GetMovAvgType(), In_PriceMAPeriod.GetInt() );
	
	//Set input flags for Settings window.
	InFlag_ServerConnectionState.SetYesNo(sc.ServerConnectionState);
	InFlag_IsAutoTradingEnabled.SetYesNo(sc.IsAutoTradingEnabled);
	InFlag_IsChartTradeModeOn.SetYesNo(sc.IsChartTradeModeOn);
	InFlag_GlobalTradeSimulationIsOn.SetYesNo(sc.GlobalTradeSimulationIsOn);
	
	//Input Flag and Safety: Handle simulation mode.
	if(In_SimulationMode.GetYesNo()) {sc.SendOrdersToTradeService = false;}
	else {sc.SendOrdersToTradeService = !sc.GlobalTradeSimulationIsOn;}
	InFlag_SendOrdersToTradeService.SetYesNo(sc.SendOrdersToTradeService);
	
	//Set the Live Trading flag color if everything is working.
	if(	(In_Enabled.GetYesNo()) &&
		(sc.ServerConnectionState) &&
		(sc.IsAutoTradingEnabled) &&
		(sc.IsChartTradeModeOn) &&
		(sc.SendOrdersToTradeService) &&
		(In_MATrailingStop.GetFloat() > 0.0)
		)
		{InFlag_LiveTradingEnabled.SetColor(0, 255, 0);} //enabled green
	else {InFlag_LiveTradingEnabled.SetColor(255, 0, 0);} //disabled red
	
	//DEBUG: One time print of all the orders.
	if(In_DebugPrintOrders.GetYesNo()) {debug_PrintOrders(sc); In_DebugPrintOrders.SetYesNo(0);}
	
	/* //Replay is done disconnected. It is safe to leave commented out.
	//Input Flag: If data connection is disabled, disable study.
	if(sc.ServerConnectionState == 0) {In_Enabled.SetYesNo(0); return;}
	*/
	
	//Input Flag: If auto trading is disabled, disable study.
	if(sc.IsAutoTradingEnabled == 0) {In_Enabled.SetYesNo(0); return;}
	
	//Input Flag: If chart trading is disabled, disable study.
	if(sc.IsChartTradeModeOn == 0) {In_Enabled.SetYesNo(0); return;}
	
	//Disabled by MA TS Offset. Usually used to check flag values before trading is enabled.
	if(In_MATrailingStop.GetFloat() <= 0.0) {return;}
	
	//Not enough data yet.
	if( i < In_PriceMAPeriod.GetInt() ) {return;}
	
	//Nothing to do if not at the end. This seems to happen every bar.
	//Since there is more data waiting, returning to fetch it is very fast.
	if(i != IndexEnd) {return;}
	
	//Reset conditions
	if(sc.DownloadingHistoricalData) {pResetIssued = RESET_DOWNLOADINGDATA; return;} //Cannot manage orders when downloading data.
	if(sc.IsFullRecalculation) {pResetIssued = RESET_FULLRECALCULATION; return;} //Cannot manage orders when recalculating.
	
	/* //In Replay Mode only simulated trades are affected. Make sure trade error code blocks don't execute in Replay Mode.
	if(sc.ReplayStatus) {pResetIssued = RESET_REPLAY; return;} //Cannot manage orders during a replay.
	*/
	
	// *** Beyond this point is clear for active trading. ***
	// *** Beyond this point is clear for active trading. ***
	// *** Beyond this point is clear for active trading. ***
	
	//Get current trade status.
	sc.GetTradePosition(PositionData);
	
	//Set Settings flags. Return if TD_None and nothing to do.
	//This will keep watching for an eventual trade to be entered.
	InFlag_Volume.SetInt(PositionData.PositionQuantity);
	if( (PositionData.PositionQuantity == 0) || (pExitingATrade == 1) ) { //flat, no active trades
		//First run after the trade.
		if(pManagingATrade == 1) {
			//pManagingATrade = 0; //reset below
			//set the trade arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Reset dates.
			pTimeExit = 0.0;
			pWeekendExitTimeSeconds = 0.0;
			//Cancel a Price Target if it was created.
			pPriceTargetOrderID = CancelOrderAndLog(sc, pPriceTargetOrderID, "old Price Target after exit");
			pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
			//Cancel a Safety Trailing Stop if it was created.
			pSafetyStopOrderID = CancelOrderAndLog(sc, pSafetyStopOrderID, "old Safety Trailing Stop after exit");
			//Remove old Exit Trend Line if it was created.
			pExitTrendLineLineNumber = DeleteChartDrawing(sc, pExitTrendLineLineNumber, 0);
			//Reset tracking of previous order variables.
			pSafetyStopPrevious = In_SafetyStop.GetFloat();
			pSafetyStopValueTypePrevious = In_SafetyStopValueType.GetIndex();
			pPriceTarget = 0.0;
			pPriceTargetHold = 0.0;
			pPriceTargetPrevious = In_PriceTarget.GetFloat();
			pPriceTargetValueTypePrevious = In_PriceTargetValueType.GetIndex();
			pPriceTargetOrderTypePrevious = In_PriceTargetOrderType.GetIndex();
			//Clear the chart if enabled.
			if(In_ClearChartOnTradeExit.GetYesNo()) {
				for(i=0; i<sc.ArraySize; i++) {
					Graph_SafetyStop[i] = 0.0;
					Graph_MATrailingStop[i] = 0.0;
					Graph_MATSLeadingEdge[i] = 0.0;
					Graph_LongEntry[i] = 0.0;
					Graph_LongExit[i] = 0.0;
					Graph_ShortEntry[i] = 0.0;
					Graph_ShortExit[i] = 0.0;
					}
				i = sc.Index; //reset i back to normal
				}
			//log the exit
			LogText.Format("%s %s STOP: Trade Management Stopped: Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), sc.Close[i]);
			sc.AddMessageToLog(LogText, 0);
			#if DEBUGON > 0
			debug_PrintOrders(sc);
			#endif
			} //end first run after the trade
		pTradeDirection = TD_None;
		InFlag_TradeDirection.SetCustomInputIndex(TD_None);
		InFlag_ManagingATrade.SetColor(255, 0, 0); //disabled red
		pManagingATrade = 0;
		pTradeStartBar = 0;
		pVolumePrevious = 0; //Keep track of volume to detect changes.
		pIndexLast = sc.Index; //Keep track of last index to detect bar changes.
		pResetIssued = 0; //Reset the reset variable at the very end.
		pExitingATrade = 0; //Reset the flag so this only gets called once.
		sc.UpdateAlways = 0; //Go into standby mode. Needs to be reset to 0 if using the exit time features.
		return; //If no positions, nothing to manage.
		}
	//Trade finally entered...
	else if(PositionData.PositionQuantity > 0) {pTradeDirection = TD_Long;}
	else {pTradeDirection = TD_Short;}
	InFlag_TradeDirection.SetCustomInputIndex(pTradeDirection);
	InFlag_ManagingATrade.SetColor(0, 255, 0); //enabled green
	
	
	//Load up variables.
	PriceCurrent = sc.Close[i];
	SafetyStopOrderTrigger = 0;
	PriceTargetOrderTrigger = 0;
	
	
	
	//First run inside the trade.
	if(pManagingATrade == 0) {
		pManagingATrade = 1;
		//Test for rapid order entry and exit. If 3 in 15 seconds, disable this program for safety reasons.
		//This helps prevent massive losses in commissions from multiple automated bad position entries.
		//The automated position entry system should also have a safety like this.
		if( (sc.ReplayStatus == REPLAY_STOPPED) && FlipFlopAlert(15, &pTime1, &pTime2, &pTime3) ) {
			LogText.Format("%s %s EMERGENCY EXIT: 3 new orders in 15 seconds, circuit breaker tripped. Check your automated trade setup immediately. Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), PriceCurrent);
			sc.AddMessageToLog(LogText, 1);
			In_Enabled.SetYesNo(0);
			//trigger a full recalculation to clear off the graph? or leave it there to see the damage?
			sc.UpdateAlways = 0; //Go into standby mode.
			return;
			}
		//Log the start
		LogText.Format("%s %s START: Trade Management Started: Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), PriceCurrent);
		sc.AddMessageToLog(LogText, 0);
		//Set price input data.
		if(In_PriceInputBias.GetYesNo()) {
			if(pTradeDirection == TD_Long) {pPriceInputData = SC_LOW;}
			else {pPriceInputData = SC_HIGH;} //TD_Short
			}
		else {pPriceInputData = In_PriceInputData.GetInputDataIndex();}
		//Full trade management: cancel everything else that could cause problems.
		if(In_CancelAllOtherOrders.GetYesNo()) {
			RC = sc.CancelAllOrders();
			pPriceTargetOrderID = 0;
			pSafetyStopOrderID = 0;
			LogText.Format("%s %s Cancel: Remove all other orders on new management entry (RC=%d).", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC);
			sc.AddMessageToLog(LogText, 0);
			}
		//Keep track of volume for a change.
		pVolumePrevious = PositionData.PositionQuantity;
		//where to start monitoring the trade.
		if(In_TradeManagementStart.GetIndex() == 0) { // 0: start at beginning of order
			pTradeStartBar = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, PositionData.LastEntryDateTime);
			}
		else {pTradeStartBar = i;} //1: start right now
		//Max position has to be at least equal to the current position.
		if(PositionData.PositionQuantity > 0) {sc.MaximumPositionAllowed = PositionData.PositionQuantity;}
		else {sc.MaximumPositionAllowed = PositionData.PositionQuantity * -1.0;} //keep it positive
		In_MaximumPositionAllowed.SetInt(sc.MaximumPositionAllowed);
		//set the dates
		//Set In_TimeExit and weekend exit to real dates for the time exit function.
		pTimeExit = HandleTimeExitSetup(sc, In_TimeExit.GetTime());
		if(pTimeExit > 0.0) {
			LogText.Format("%s %s Info: Exit Time set to %d-%02d-%02d %d:%02d.%02d", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), pTimeExit.GetYear(), pTimeExit.GetMonth(), pTimeExit.GetDay(), pTimeExit.GetHour(), pTimeExit.GetMinute(), pTimeExit.GetSecond() );
			sc.AddMessageToLog(LogText, 0);
			}
		pWeekendExitTimeSeconds = In_WeekendExitTime.GetTime();
		pWeekendExitDay = In_WeekendExitDay.GetIndex();
		if(pWeekendExitTimeSeconds > 0.0) {
			TIME_TO_HMS(pWeekendExitTimeSeconds, Hour, Minute, Second);
			LogText.Format("%s %s Info: Weekend Exit Time set to %d:%02d.%02d D: %s", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), Hour, Minute, Second, DayOfWeekToString(pWeekendExitDay, TempStr, 100) );
			sc.AddMessageToLog(LogText, 0);
			}
		//Reset arrays to avoid an instant exit problem
		Graph_MATrailingStop[i] = 0.0;
		Graph_MATrailingStop[i-1] = 0.0;
		Graph_SafetyStop[i] = 0.0;
		Graph_SafetyStop[i-1] = 0.0;
		//Cancel an old Price Target if it was created.
		pPriceTargetOrderID = CancelOrderAndLog(sc, pPriceTargetOrderID, "old Price Target on new entry");
		pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
		//Cancel an old Safety Trailing Stop if it was created.
		pSafetyStopOrderID = CancelOrderAndLog(sc, pSafetyStopOrderID, "old Safety Trailing Stop on new entry");
		//Remove old Exit Trend Line if it was created.
		pExitTrendLineLineNumber = DeleteChartDrawing(sc, pExitTrendLineLineNumber, 0);
		//Issue a manual reset to handle new orders and offsets.
		//This allows for order code consolidation further down.
		pResetIssued = RESET_MANUAL;
		SafetyStopOrderTrigger = 1;
		PriceTargetOrderTrigger = 1;
		
		#if DEBUGON > 0
		debug_PrintOrders(sc);
		//set debug for end of this loop.
		In_DebugPrintOrders.SetYesNo(1);
		#endif
		} //end if(pManagingATrade == 0)
	
	//sc.UpdateAlways is only needed for time related features.
	//Turning it off here also allows for turning it on once to trigger a redraw.
	if( (pTimeExit > 0) || (pWeekendExitTimeSeconds > 0) ) {
		sc.UpdateAlways = 1;
		}
	else {sc.UpdateAlways = 0;}
	
	//Check for volume change. A reset will modify the orders.
	if(PositionData.PositionQuantity != pVolumePrevious) {
		pResetIssued = RESET_VOLUMECHANGE;
		SafetyStopOrderTrigger = 1;
		PriceTargetOrderTrigger = 1;
		//Max position has to be at least equal to the current position.
		if(PositionData.PositionQuantity > 0) {sc.MaximumPositionAllowed = PositionData.PositionQuantity;}
		else {sc.MaximumPositionAllowed = PositionData.PositionQuantity * -1.0;} //keep it positive
		In_MaximumPositionAllowed.SetInt(sc.MaximumPositionAllowed);
		}
	
	
	//Look for Price Target change. This would happen if the line was dragged on the graph.
	//Since SC already changed the order, we only need to keep track of the new price.
	//If the Price Target was cancelled, that will be taken care of in the reset code below.
	//pPriceTarget=0.0 for SC controlled orders.
	if( (pPriceTargetHold > 0.0) && (pPriceTarget <= 0.0) && (pPriceTargetOrderID > 0) && (In_PriceTarget.GetFloat() > 0.0) ) {
		if(sc.GetOrderByOrderID(pPriceTargetOrderID, TradeOrder)) {
			if(IsWorkingOrderStatus(TradeOrder.OrderStatusCode)) {
				if(TradeOrder.Price1 != pPriceTargetHold) {
					LogText.Format("%s %s Modify: Price Target changed on chart (%s) (OrderID=%d RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), OrderTypeToString(TradeOrder.OrderTypeAsInt, TempStr, 100), pPriceTargetOrderID, RC, TradeOrder.Price1, PriceCurrent);
					sc.AddMessageToLog(LogText, 0);
					//reset price. Convert pPriceTarget to relative price.
					if(In_PriceTargetValueType.GetIndex() == 0) { //Convert To Offset
						pPriceTarget = TradeOrder.Price1 - sc.Close[pTradeStartBar];
						}
					else if(In_PriceTargetValueType.GetIndex() == 0) { //Convert To Percent
						if(pTradeDirection == TD_Long) {pPriceTarget = (TradeOrder.Price1 / sc.Close[pTradeStartBar]) - 1.0;}
						else {pPriceTarget = 1.0 - (TradeOrder.Price1 / sc.Close[pTradeStartBar]);}
						}
					if(pPriceTarget < 0.0) {pPriceTarget *= -1.0;} //keep it positive
					In_PriceTarget.SetFloat(pPriceTarget); //set the relative value
					pPriceTargetPrevious = pPriceTarget; //set the relative value
					pPriceTargetHold = TradeOrder.Price1; //keep the actual value for order management
					pPriceTarget = 0.0; //reset to 0.0 for SC order management
					}
				}
			else { //Cancel a Price Target that was missed.
				pPriceTargetOrderID = CancelOrderAndLog(sc, pPriceTargetOrderID, "Price Target OrderID cancelled but not zero'd.");
				pPriceTarget = 0.0;
				pPriceTargetHold = 0.0;
				pPriceTargetPrevious = In_PriceTarget.GetFloat();
				pPriceTargetValueTypePrevious = In_PriceTargetValueType.GetIndex();
				pPriceTargetOrderTypePrevious = In_PriceTargetOrderType.GetIndex();
				PriceTargetOrderTrigger = 0;
				pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
				}
			}
		else { //Cancel a Price Target that was missed.
			pPriceTargetOrderID = CancelOrderAndLog(sc, pPriceTargetOrderID, "Price Target OrderID cancelled but not zero'd.");
			pPriceTarget = 0.0;
			pPriceTargetHold = 0.0;
			pPriceTargetPrevious = In_PriceTarget.GetFloat();
			pPriceTargetValueTypePrevious = In_PriceTargetValueType.GetIndex();
			pPriceTargetOrderTypePrevious = In_PriceTargetOrderType.GetIndex();
			PriceTargetOrderTrigger = 0;
			pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
			}
		}
	//Doing this with a Safety Trailing Stop is much harder and not practical since it is constantly moving.
	
	
	// *** Beyond this point is long/short management. ***
	// *** Beyond this point is long/short management. ***
	// *** Beyond this point is long/short management. ***
	
	
	#if DEBUGON > 0
	//reset debug
	if(pResetIssued > 0) {
	FileOut = fopen(DEBUGLOG, "a"); //"a" is append text. DEBUGLOG will be in the Data dir.
	TimeNow = sc.CurrentSystemDateTime;
	sprintf(TimeStr, "%04d-%02d-%02d %d:%02d.%02d", TimeNow.GetYear(), TimeNow.GetMonth(), TimeNow.GetDay(), TimeNow.GetHour(), TimeNow.GetMinute(), TimeNow.GetSecond() );
	fprintf(FileOut, "\nReset Issued: %s (R=%d, %s)\n", TimeStr, pResetIssued, ResetToString(pResetIssued, TempStr, 100) );
	fclose(FileOut);
	In_DebugPrintOrders.SetYesNo(1);
	}
	#endif

	
	
	if(pResetIssued > 0) {
		//handle graph redraws if there is a reset.
		sc.UpdateAlways = 1;
		//set i to start of trade
		i = pTradeStartBar;
		//set the trade arrow at pTradeStartBar
		if(pTradeDirection == TD_Long) {Graph_LongEntry[i] = sc.Low[i];}
		else {Graph_ShortEntry[i] = sc.High[i];}
		//Handle Price Target removal.
		if(In_PriceTarget.GetFloat() <= 0.0) {
			pPriceTargetOrderID = CancelOrderAndLog(sc, pPriceTargetOrderID, "Price Target removed after reset");
			pPriceTarget = 0.0;
			pPriceTargetHold = 0.0;
			pPriceTargetPrevious = In_PriceTarget.GetFloat();
			pPriceTargetValueTypePrevious = In_PriceTargetValueType.GetIndex();
			pPriceTargetOrderTypePrevious = In_PriceTargetOrderType.GetIndex();
			PriceTargetOrderTrigger = 0;
			pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
			}
		//Handle Safety Trailing Stop removal.
		//Look for changes for an order trigger.
		if( (In_SafetyStop.GetFloat() != pSafetyStopPrevious) ||
			(In_SafetyStopValueType.GetIndex() != pSafetyStopValueTypePrevious) )
			{SafetyStopOrderTrigger = 1;}
		if(In_SafetyStop.GetFloat() <= 0.0) {
			//reset everything
			pSafetyStopOrderID = CancelOrderAndLog(sc, pSafetyStopOrderID, "Safety Trailing Stop removed after reset");
			SafetyStopPrice = 0.0;
			pSafetyStopOffset = 0.0;
			pSafetyStopPrevious = In_SafetyStop.GetFloat();
			pSafetyStopValueTypePrevious = In_SafetyStopValueType.GetIndex();
			SafetyStopOrderTrigger = 0;
			}
		//Handle Safety Trailing Stop new distance.
		else if(SafetyStopOrderTrigger > 0) {
			SafetyStopPrice = In_SafetyStop.GetFloat();
			//Convert SafetyStopPrice into an absolute price.
			if(In_SafetyStopValueType.GetIndex() == 0) { //Offset
				pSafetyStopOffset = SafetyStopPrice;
				if(pTradeDirection == TD_Long) {SafetyStopPrice = sc.Close[pTradeStartBar] - pSafetyStopOffset;}
				else {SafetyStopPrice = sc.Close[pTradeStartBar] + pSafetyStopOffset;}
				}
			else if(In_SafetyStopValueType.GetIndex() == 1) { //Percent
				pSafetyStopOffset = sc.Close[pTradeStartBar] * SafetyStopPrice;
				if(pTradeDirection == TD_Long) {SafetyStopPrice = sc.Close[pTradeStartBar] - pSafetyStopOffset;}
				else {SafetyStopPrice = sc.Close[pTradeStartBar] + pSafetyStopOffset;}
				}
			else { //Absolute
				if(pTradeDirection == TD_Long) {pSafetyStopOffset = sc.Close[pTradeStartBar] - SafetyStopPrice;}
				else {pSafetyStopOffset = SafetyStopPrice - sc.Close[pTradeStartBar];}
				//Change Safety Trailing Stop type so a bad number won't get triggered next major loop.
				In_SafetyStopValueType.SetCustomInputIndex(0); //offset
				In_SafetyStop.SetFloat(pSafetyStopOffset);
				}
			//Make sure calculations didn't produce a negative price.
			if(SafetyStopPrice < 0.0) {SafetyStopPrice = -1.0;}
			//Make sure the safety stop is in bounds and won't immediately flatten the entire position.
			if( (pTradeDirection == TD_Long) && (SafetyStopPrice >= PriceCurrent) ) {SafetyStopPrice = -2.0;}
			if( (pTradeDirection == TD_Short) && (SafetyStopPrice <= PriceCurrent) ) {SafetyStopPrice = -3.0;}
			//Report SafetyStopPrice errors.
			if(SafetyStopPrice <= 0.0) {
				LogText.Format("%s %s Error: Modify Safety Trailing Stop out of bounds, disabling, RC=%f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), SafetyStopPrice, PriceCurrent);
				sc.AddMessageToLog(LogText, 1);
				//Cancel a Safety Trailing Stop if it was created.
				pSafetyStopOrderID = CancelOrderAndLog(sc, pSafetyStopOrderID, "new Safety Trailing Stop out of bounds");
				SafetyStopPrice = 0.0;
				pSafetyStopOffset = 0.0;
				pSafetyStopPrevious = In_SafetyStop.GetFloat();
				pSafetyStopValueTypePrevious = In_SafetyStopValueType.GetIndex();
				SafetyStopOrderTrigger = 0;
				}
			} //end Safety Trailing Stop new distance
		
		//Convert pMATrailingStopOffset into an offset.
		if(In_MATrailingStopValueType.GetIndex() == 0) { //Offset
			pMATrailingStopOffset = In_MATrailingStop.GetFloat();
			}
		else if(In_MATrailingStopValueType.GetIndex() == 1) { //Percent
			pMATrailingStopOffset = sc.Close[pTradeStartBar] * In_MATrailingStop.GetFloat();
			}
		else { //Absolute
			if(pTradeDirection == TD_Long) {pMATrailingStopOffset = sc.Close[pTradeStartBar] - In_MATrailingStop.GetFloat();}
			else {pMATrailingStopOffset = In_MATrailingStop.GetFloat() - sc.Close[pTradeStartBar];}
			if(pMATrailingStopOffset < 0.0) {pMATrailingStopOffset *= -1.0;} //keep it positive
			//Change MA Trailing Stop type so a bad number won't get triggered next major loop.
			In_MATrailingStopValueType.SetCustomInputIndex(0); //offset
			In_MATrailingStop.SetFloat(pMATrailingStopOffset);
			}
		
		} //end (pResetIssued > 0)
	
	
	//The for() loop will handle graph redraws.
	//Note that i might have been changed above. It will be reset at the end of this for().
	for(; i<=IndexEnd; i++) {
	
	//Do the price movement calculations and draw the graphs.
	//Long Order.
	if(pTradeDirection == TD_Long) {
		//first run
		if(Graph_MATrailingStop[i-1] == 0.0) {Graph_MATrailingStop[i-1] = Graph_PriceMA[i-1] - pMATrailingStopOffset;}
		//new uninitialized bar, catch it so it won't trigger problems
		if(pIndexLast != i) {Graph_MATrailingStop[i] = Graph_MATrailingStop[i-1]; pMATrailingStopPriceHold = Graph_PriceMA[i];}
		//safety, usually during redraws
		if(Graph_MATrailingStop[i] == 0.0) {Graph_MATrailingStop[i] = Graph_MATrailingStop[i-1]; pMATrailingStopPriceHold = Graph_PriceMA[i];}
		//regular run. Keep track of distance moved so the stop won't go in reverse on the current bar.
		if(pMATrailingStopPriceHold < Graph_PriceMA[i]) {pMATrailingStopPriceHold = Graph_PriceMA[i];} //find highest
		PriceTemp = pMATrailingStopPriceHold - pMATrailingStopOffset;
		//long trailing stop can only move up.
		if(PriceTemp > Graph_MATrailingStop[i-1]) {Graph_MATrailingStop[i] = PriceTemp;}
		//Handle the leading edge graph.
		Graph_MATSLeadingEdge[i] = Graph_MATrailingStop[i] + pMATrailingStopOffset;
		
		//Handle SafetyStopPrice redraw. Redraw doesn't span function calls so it doesn't need persistent variables set.
		if( (pResetIssued > 0) && (pSafetyStopOrderID > 0) ) {
			//first run
			if(Graph_SafetyStop[i-1] == 0.0) {Graph_SafetyStop[i-1] = sc.High[i-1] - pSafetyStopOffset;}
			//new uninitialized bar, catch it so it won't trigger problems
			if(pIndexLast != i) {Graph_SafetyStop[i] = Graph_SafetyStop[i-1];}
			//safety, usually during redraws
			if(Graph_SafetyStop[i] == 0.0) {Graph_SafetyStop[i] = Graph_SafetyStop[i-1];}
			//calculate distance
			PriceTemp = sc.High[i] - pSafetyStopOffset;
			//long trailing stop can only move up.
			if(PriceTemp > Graph_SafetyStop[i-1]) {Graph_SafetyStop[i] = PriceTemp;}
			} //end SafetyStopPrice redraw.
		} //end if(pTradeDirection == TD_Long)
	
	//Short Order.
	if(pTradeDirection == TD_Short) {
		//first run
		if(Graph_MATrailingStop[i-1] == 0.0) {Graph_MATrailingStop[i-1] = Graph_PriceMA[i-1] + pMATrailingStopOffset;}
		//new uninitialized bar, catch it so it won't trigger problems
		if(pIndexLast != i) {Graph_MATrailingStop[i] = Graph_MATrailingStop[i-1]; pMATrailingStopPriceHold = Graph_PriceMA[i];}
		//safety, usually during redraws
		if(Graph_MATrailingStop[i] == 0.0) {Graph_MATrailingStop[i] = Graph_MATrailingStop[i-1]; pMATrailingStopPriceHold = Graph_PriceMA[i];}
		//regular run. Keep track of distance moved so the stop won't go in reverse on the current bar.
		if(pMATrailingStopPriceHold > Graph_PriceMA[i]) {pMATrailingStopPriceHold = Graph_PriceMA[i];} //find lowest
		PriceTemp = pMATrailingStopPriceHold + pMATrailingStopOffset;
		//short trailing stop can only move down.
		if(PriceTemp < Graph_MATrailingStop[i-1]) {Graph_MATrailingStop[i] = PriceTemp;}
		//Handle the leading edge graph.
		Graph_MATSLeadingEdge[i] = Graph_MATrailingStop[i] - pMATrailingStopOffset;
		
		//Handle SafetyStopPrice redraw. Redraw doesn't span function calls so it doesn't need persistent variables set.
		if( (pResetIssued > 0) && (pSafetyStopOrderID > 0) ) {
			//first run
			if(Graph_SafetyStop[i-1] == 0.0) {Graph_SafetyStop[i-1] = sc.Low[i-1] + pSafetyStopOffset;}
			//new uninitialized bar, catch it so it won't trigger problems
			if(pIndexLast != i) {Graph_SafetyStop[i] = Graph_SafetyStop[i-1];}
			//safety, usually during redraws
			if(Graph_SafetyStop[i] == 0.0) {Graph_SafetyStop[i] = Graph_SafetyStop[i-1];}
			//calculate distance
			PriceTemp = sc.Low[i] + pSafetyStopOffset;
			//short trailing stop can only move down.
			if(PriceTemp < Graph_SafetyStop[i-1]) {Graph_SafetyStop[i] = PriceTemp;}
			} //end SafetyStopPrice redraw.
		} //end if(pTradeDirection == TD_Short)
	
	} //end for()
	//Since i might have been changed, make sure it is reset.
	i = sc.Index;
	
	
	
	
	
	//Modify price target and safety stop orders if there was a reset.
	if(pResetIssued > 0) {
		//Price Target. Cancellations are handled above.
		//Look for changes for an order trigger.
		if( (In_PriceTarget.GetFloat() != pPriceTargetPrevious) ||
			(In_PriceTargetValueType.GetIndex() != pPriceTargetValueTypePrevious) ||
			(In_PriceTargetOrderType.GetIndex() != pPriceTargetOrderTypePrevious) )
			{PriceTargetOrderTrigger = 1;}
		if( (In_PriceTarget.GetFloat() > 0.0) && (PriceTargetOrderTrigger > 0) ) {
			PriceTargetOrderTrigger = 0; //reset
			pPriceTarget = In_PriceTarget.GetFloat();
			//Convert pPriceTarget into an absolute price.
			if(In_PriceTargetValueType.GetIndex() == 0) { //Offset
				if(pTradeDirection == TD_Long) {pPriceTarget = sc.Close[pTradeStartBar] + pPriceTarget;}
				else {pPriceTarget = sc.Close[pTradeStartBar] - pPriceTarget;}
				}
			else if(In_PriceTargetValueType.GetIndex() == 1) { //Percent
				if(pTradeDirection == TD_Long) {pPriceTarget = sc.Close[pTradeStartBar] + (sc.Close[pTradeStartBar] * pPriceTarget);}
				else {pPriceTarget = sc.Close[pTradeStartBar] - (sc.Close[pTradeStartBar] * pPriceTarget);}
				}
			else { //Absolute
				//Change PriceTarget type so a bad number won't get triggered next major loop.
				In_PriceTargetValueType.SetCustomInputIndex(0); //offset
				if(pTradeDirection == TD_Long) {In_PriceTarget.SetFloat(pPriceTarget - sc.Close[pTradeStartBar]);}
				else {In_PriceTarget.SetFloat(sc.Close[pTradeStartBar] - pPriceTarget);}
				}
			//Make sure calculations didn't produce a negative price.
			if(pPriceTarget < 0.0) {pPriceTarget = -1.0;}
			//Make sure the price target is in bounds and won't immediately flatten the entire position.
			if( (pTradeDirection == TD_Long) && (pPriceTarget <= PriceCurrent) ) {pPriceTarget = -2.0;}
			if( (pTradeDirection == TD_Short) && (pPriceTarget >= PriceCurrent) ) {pPriceTarget = -3.0;}
			//Report PriceTarget errors.
			if(pPriceTarget <= 0.0) {
				LogText.Format("%s %s Error: Modify Price Target out of bounds, disabling, RC=%f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), pPriceTarget, PriceCurrent);
				sc.AddMessageToLog(LogText, 1);
				pPriceTarget = 0.0; //disable
				//Cancel a Price Target if it was created.
				pPriceTargetOrderID = CancelOrderAndLog(sc, pPriceTargetOrderID, "new Price Target out of bounds");
				pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
				}
			//Set price target order type.
			OrderType = -1; //stealth type, this program manages the order.
			if(In_PriceTargetOrderType.GetIndex() == 0) {OrderType = SCT_ORDERTYPE_MARKET_IF_TOUCHED;}
			else if(In_PriceTargetOrderType.GetIndex() == 1) {OrderType = SCT_ORDERTYPE_LIMIT;}
			//Handle Price Target changed to stealth mode.
			if(OrderType < 0) {
				pPriceTargetOrderID = CancelOrderAndLog(sc, pPriceTargetOrderID, "Price Target changed to stealth mode");
				PriceTargetOrderTrigger = 0;
				pPriceTargetHold = 0.0;
				pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
				}
			//Cancel a Price Target if the order type was changed. ModifyOrder cannot change the order type.
			//This won't do anything if it is the first order entry.
			if(pPriceTargetOrderType != OrderType) {
				pPriceTargetOrderID = CancelOrderAndLog(sc, pPriceTargetOrderID, "Price Target order type change");
				pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
				}
			//Modify price target order.
			if( (OrderType >= 0) && (pPriceTarget > 0.0) &&
			    (pPriceTargetOrderID > 0) &&
				(sc.GetOrderByOrderID(pPriceTargetOrderID, TradeOrder)) &&
				(IsWorkingOrderStatus(TradeOrder.OrderStatusCode)) ) {
				NewOrder.Reset();
				NewOrder.InternalOrderID = pPriceTargetOrderID;
				NewOrder.Price1 = pPriceTarget;
				if(pTradeDirection == TD_Long) {NewOrder.OrderQuantity = PositionData.PositionQuantity;}
				else {NewOrder.OrderQuantity = PositionData.PositionQuantity * -1.0;}
				RC = sc.ModifyOrder(NewOrder);
				if(RC > 0) {
					LogText.Format("%s %s Modify: Price Target after a reset (%s) (OrderID=%d RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), OrderTypeToString(TradeOrder.OrderTypeAsInt, TempStr, 100), pPriceTargetOrderID, RC, NewOrder.Price1, PriceCurrent);
					sc.AddMessageToLog(LogText, 0);
					}
				else {
					LogText.Format("%s %s Error: Modify failed for Price Target (%s) (OrderID=%d RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), OrderTypeToString(TradeOrder.OrderTypeAsInt, TempStr, 100), pPriceTargetOrderID, RC, NewOrder.Price1, PriceCurrent);
					sc.AddMessageToLog(LogText, 1);
					}
				sc.GetOrderByOrderID(pPriceTargetOrderID, TradeOrder);
				pPriceTargetHold = TradeOrder.Price1;
				pPriceTarget = 0.0; //reset so this program won't manage the SC order.
				} //end sc.ModifyOrder
			//Add missing price target order.
			else if( (OrderType >= 0) && (pPriceTarget > 0.0) ) { //SC managed order.
				NewOrder.Reset();
				NewOrder.OrderType = OrderType;
				pPriceTargetOrderType = NewOrder.OrderType; //remember this if the order type changes.
				NewOrder.TimeInForce = SCT_TIF_GTC; //or SCT_TIF_DAY. Use GTC so it won't be missed.
				NewOrder.Price1 = pPriceTarget;
				SetBlockingVariables(sc, 0); //disable block variables
				if(pTradeDirection == TD_Long) {
					NewOrder.OrderQuantity = PositionData.PositionQuantity;
					//RC = sc.BuyExit(NewOrder); //BuyExit to exit an existing long. Only one exit order at a time can exist.
					RC = sc.SellOrder(NewOrder); //disable security variables first
					}
				else { //short
					NewOrder.OrderQuantity = PositionData.PositionQuantity * -1.0; //keep it positive
					//RC = sc.SellExit(NewOrder); //SellExit to exit an existing short. Only one exit order at a time can exist.
					RC = sc.BuyOrder(NewOrder); //disable security variables first
					}
				SetBlockingVariables(sc, 1); //enable block variables
				if(RC > 0) { //report success
					pPriceTargetOrderID = NewOrder.InternalOrderID; //save OrderID
					LogText.Format("%s %s Order: Entered Price Target order (%s) (OrderID=%d RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), OrderTypeToString(NewOrder.OrderType, TempStr, 100), pPriceTargetOrderID, RC, NewOrder.Price1, PriceCurrent);
					sc.AddMessageToLog(LogText, 0);
					}
				else { //report an error
					pPriceTargetOrderID = 0; //nothing happened
					LogText.Format("%s %s Error: Failed to enter Price Target order (%s) (RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), OrderTypeToString(NewOrder.OrderType, TempStr, 100), RC, NewOrder.Price1, PriceCurrent);
					sc.AddMessageToLog(LogText, 1);
					}
				sc.GetOrderByOrderID(pPriceTargetOrderID, TradeOrder);
				pPriceTargetHold = TradeOrder.Price1;
				pPriceTarget = 0.0; //reset so this program won't manage the SC order.
				} //end if(OrderType >= 0)
			else if(OrderType < 0) {
				//Cancel a Price Target if it was created.
				//??? This didn't get executed during tests.
				pPriceTargetOrderID = CancelOrderAndLog(sc, pPriceTargetOrderID, "Price Target changed to stealth mode");
				PriceTargetOrderTrigger = 0;
				pPriceTargetHold = 0.0;
				pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
				}
			//Reset tracking of previous order variables.
			pPriceTargetPrevious = In_PriceTarget.GetFloat();
			pPriceTargetValueTypePrevious = In_PriceTargetValueType.GetIndex();
			pPriceTargetOrderTypePrevious = In_PriceTargetOrderType.GetIndex();
			} //end if( (In_PriceTarget.GetFloat() > 0.0) && (PriceTargetOrderTrigger > 0) )
		
		//Handle stealth price target line.
		if(pPriceTarget > 0.0) {
			Tool.Clear();
			Tool.AddAsUserDrawnDrawing = 0;
			Tool.ChartNumber = sc.ChartNumber;
			Tool.Region = sc.GraphRegion;
			Tool.DrawingType = DRAWING_HORIZONTALLINE;
			Tool.DisplayHorizontalLineValue = 1;
			Tool.BeginValue = pPriceTarget;
			Tool.Color = In_PriceTargetLineColor.GetColor();
			Tool.LineWidth = In_PriceTargetLineWidth.GetInt();
			Tool.AddMethod = UTAM_ADD_OR_ADJUST;
			if(pPriceTargetLineNumber > 0) {Tool.LineNumber = pPriceTargetLineNumber;}
			RC = sc.UseTool(Tool);
			pPriceTargetLineNumber = Tool.LineNumber;
			}
		else { //Safety: Cancel a stealth Price Target line that was missed.
			pPriceTargetLineNumber = DeleteChartDrawing(sc, pPriceTargetLineNumber, 0);
			}
		
		//Handle Safety Trailing Stop
		if( (SafetyStopPrice > 0.0) && (SafetyStopOrderTrigger > 0) ) {
			SafetyStopOrderTrigger = 0; //reset
			// SafetyStopPrice already converted above, DO NOT CHANGE THOSE VARIABLES!
			//Modify Safety Trailing Stop order.
			if( (SafetyStopPrice > 0.0) && (pSafetyStopOrderID > 0) &&
			    (sc.GetOrderByOrderID(pSafetyStopOrderID, TradeOrder)) &&
				(IsWorkingOrderStatus(TradeOrder.OrderStatusCode)) ) {
				NewOrder.Reset();
				NewOrder.InternalOrderID = pSafetyStopOrderID;
				if(pTradeDirection == TD_Long) {
					NewOrder.Price1 = sc.High[i] - pSafetyStopOffset;
					NewOrder.OrderQuantity = PositionData.PositionQuantity;
					}
				else {
					NewOrder.Price1 = sc.Low[i] + pSafetyStopOffset;
					NewOrder.OrderQuantity = PositionData.PositionQuantity * -1.0;
					}
				RC = sc.ModifyOrder(NewOrder);
				if(RC > 0) {
					LogText.Format("%s %s Modify: Safety Trailing Stop after a reset (%s) (OrderID=%d RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), OrderTypeToString(TradeOrder.OrderTypeAsInt, TempStr, 100), pSafetyStopOrderID, RC, NewOrder.Price1, PriceCurrent);
					sc.AddMessageToLog(LogText, 0);
					}
				else {
					LogText.Format("%s %s Error: Modify failed for Safety Trailing Stop (%s) (OrderID=%d RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), OrderTypeToString(TradeOrder.OrderTypeAsInt, TempStr, 100), pSafetyStopOrderID, RC, NewOrder.Price1, PriceCurrent);
					sc.AddMessageToLog(LogText, 1);
					}
				} //end sc.ModifyOrder
			//Add missing Safety Trailing Stop order.
			else if(SafetyStopPrice > 0.0) { //New SC managed order.
				NewOrder.Reset();
				NewOrder.OrderType = SCT_ORDERTYPE_TRAILING_STOP;
				NewOrder.TimeInForce = SCT_TIF_GTC; //or SCT_TIF_DAY. Use GTC so it won't be missed.
				SetBlockingVariables(sc, 0); //disable block variables
				if(pTradeDirection == TD_Long) {
					NewOrder.Price1 = sc.High[i] - pSafetyStopOffset;
					NewOrder.OrderQuantity = PositionData.PositionQuantity;
					//RC = sc.BuyExit(NewOrder); //BuyExit to exit an existing long. Only one exit order at a time can exist.
					RC = sc.SellOrder(NewOrder); //disable security variables first
					}
				else { //short
					NewOrder.Price1 = sc.Low[i] + pSafetyStopOffset;
					NewOrder.OrderQuantity = PositionData.PositionQuantity * -1.0; //keep it positive
					//RC = sc.SellExit(NewOrder); //SellExit to exit an existing short. Only one exit order at a time can exist.
					RC = sc.BuyOrder(NewOrder); //disable security variables first
					}
				SetBlockingVariables(sc, 1); //enable block variables
				if(RC > 0) { //report success
					pSafetyStopOrderID = NewOrder.InternalOrderID; //save OrderID
					LogText.Format("%s %s Order: Entered Safety Trailing Stop order (%s) (OrderID=%d RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), OrderTypeToString(NewOrder.OrderType, TempStr, 100), pSafetyStopOrderID, RC, NewOrder.Price1, PriceCurrent);
					sc.AddMessageToLog(LogText, 0);
					}
				else { //report an error
					pSafetyStopOrderID = 0; //nothing happened
					LogText.Format("%s %s Error: Failed to enter Safety Trailing Stop order (%s) (RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), OrderTypeToString(NewOrder.OrderType, TempStr, 100), RC, NewOrder.Price1, PriceCurrent);
					sc.AddMessageToLog(LogText, 1);
					}
				} //end if sc.Order
			//Reset tracking of previous order variables.
			pSafetyStopPrevious = In_SafetyStop.GetFloat();
			pSafetyStopValueTypePrevious = In_SafetyStopValueType.GetIndex();
			} //end (SafetyStopPrice > 0.0)
	
		//Handle Exit Trend Line creation.
		if(In_ExitTrendLineEnable.GetYesNo()) { //enabled
			//Safety: delete wrong line type if it exists.
			if(pExitTrendLineLineNumber > 0) {
				pExitTrendLineLineNumber = DeleteChartDrawing(sc, pExitTrendLineLineNumber, 0);
				}
			//Add the line.
			if(pExitTrendLineLineNumber == 0) {
				Tool.Clear();
				Tool.AddAsUserDrawnDrawing = 1;
				Tool.ChartNumber = sc.ChartNumber;
				Tool.Region = sc.GraphRegion;
				Tool.DrawingType = DRAWING_RAY;
				Tool.BeginIndex = pTradeStartBar;
				Tool.EndIndex = sc.ArraySize - 1;
				if(Tool.BeginIndex == Tool.EndIndex) {Tool.BeginIndex = Tool.BeginIndex - 1;}
				if(Tool.BeginIndex < 0) {Tool.BeginIndex = 0;}
				Tool.BeginValue = Graph_MATrailingStop[i];
				Tool.EndValue = Graph_MATrailingStop[i];
				Tool.Color = In_ExitTrendLineColor.GetColor();
				Tool.LineWidth = In_ExitTrendLineWidth.GetInt();
				Tool.AddMethod = UTAM_ADD_OR_ADJUST;
				//if(pExitTrendLineLineNumber < 0) {Tool.LineNumber = pExitTrendLineLineNumber;}
				RC = sc.UseTool(Tool);
				pExitTrendLineLineNumber = Tool.LineNumber;
				if(pExitTrendLineLineNumber < 0) {
					//save the values and calculate slope
					pExitTrendLineX1 = Tool.BeginIndex;
					pExitTrendLineX2 = Tool.EndIndex;
					pExitTrendLineY1 = Tool.BeginValue;
					pExitTrendLineY2 = Tool.EndValue;
					pExitTrendLineSlope = (pExitTrendLineY2 - pExitTrendLineY1) / (float)(pExitTrendLineX2 - pExitTrendLineX1);
					}
				LogText.Format("%s %s INFO: Exit Trend Line created (RC=%d) Chart#=%d Line#=%d I1=%d I2=%d V=%f Slope=%f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, Tool.ChartNumber, pExitTrendLineLineNumber, Tool.BeginIndex, Tool.EndIndex, Tool.BeginValue, pExitTrendLineSlope);
				sc.AddMessageToLog(LogText, 0);
				}
			}
		else { //disabled
			//Remove Exit Trend Line if it was created.
			pExitTrendLineLineNumber = DeleteChartDrawing(sc, pExitTrendLineLineNumber, 0);
			}
	
	} //end if pResetIssued
	
	
	//Draw Safety Trailing Stop line.
	if(pSafetyStopOrderID > 0.0) {
		if( sc.GetOrderByOrderID(pSafetyStopOrderID, TradeOrder) ) {
			if(IsWorkingOrderStatus(TradeOrder.OrderStatusCode)) {
				Graph_SafetyStop[i] = TradeOrder.Price1;
				}
			else { //Cancel a Safety Trailing Stop that was missed.
				pSafetyStopOrderID = CancelOrderAndLog(sc, pSafetyStopOrderID, "Safety Trailing Stop OrderID cancelled but not zero'd");
				SafetyStopPrice = 0.0;
				pSafetyStopOffset = 0.0;
				pSafetyStopPrevious = In_SafetyStop.GetFloat();
				pSafetyStopValueTypePrevious = In_SafetyStopValueType.GetIndex();
				SafetyStopOrderTrigger = 0;
				}
			}
		else { //Cancel a Safety Trailing Stop that was missed.
			pSafetyStopOrderID = CancelOrderAndLog(sc, pSafetyStopOrderID, "Safety Trailing Stop OrderID cancelled but not zero'd");
			SafetyStopPrice = 0.0;
			pSafetyStopOffset = 0.0;
			pSafetyStopPrevious = In_SafetyStop.GetFloat();
			pSafetyStopValueTypePrevious = In_SafetyStopValueType.GetIndex();
			SafetyStopOrderTrigger = 0;
			}
		} //end if Safety Trailing Stop line
	
	
	//Check if Exit Trend Line changed.
	if(pExitTrendLineLineNumber < 0) {
		if(sc.UserDrawnChartDrawingExists(sc.ChartNumber, pExitTrendLineLineNumber)) {
			RC = sc.GetUserDrawingByLineNumber(sc.ChartNumber, pExitTrendLineLineNumber, Tool, DRAWING_RAY, 0);
			if( (RC > 0) && ( // RC==0 means stuck in update
				(pExitTrendLineX1 != Tool.BeginIndex) ||
				(pExitTrendLineX2 != Tool.EndIndex) ||
				(pExitTrendLineY1 != Tool.BeginValue) ||
				(pExitTrendLineY2 != Tool.EndValue)
				) ) {
				//resave and recalculate slope
				pExitTrendLineX1 = Tool.BeginIndex;
				pExitTrendLineX2 = Tool.EndIndex;
				pExitTrendLineY1 = Tool.BeginValue;
				pExitTrendLineY2 = Tool.EndValue;
				pExitTrendLineSlope = (pExitTrendLineY2 - pExitTrendLineY1) / (float)(pExitTrendLineX2 - pExitTrendLineX1);
				#if DEBUGON > 0
				LogText.Format("%s %s INFO: Exit Trend Line modified RC=%d Line#=%d I1=%d I2=%d V1=%f V2=%f Slope=%f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, pExitTrendLineLineNumber, Tool.BeginIndex, Tool.EndIndex, Tool.BeginValue, Tool.EndValue, pExitTrendLineSlope);
				sc.AddMessageToLog(LogText, 0);
				#endif
				}
			}
		else { //Safety: get drawing failed, reset it.
			pExitTrendLineLineNumber = DeleteChartDrawing(sc, pExitTrendLineLineNumber, 0);
			}
		}
	
	
	// *** Beyond this point are order exits. ***
	// *** Beyond this point are order exits. ***
	// *** Beyond this point are order exits. ***
	
	
	//y=mx+b
	PriceTemp = (pExitTrendLineSlope * (float)(i - pExitTrendLineX1)) + pExitTrendLineY1;
	//Exit if Exit Trend Line hit.
	if( (pExitTrendLineLineNumber < 0) && (PriceTemp > 0.0) ) {
	if(	( (pTradeDirection == TD_Long) && (Graph_PriceMA[i] <= PriceTemp) ) ||
		( (pTradeDirection == TD_Short) && (Graph_PriceMA[i] >= PriceTemp) )
		) {
		//Close out everything. Keep it clean for the next iteration.
		RC = sc.FlattenAndCancelAllOrders();
		pPriceTargetOrderID = 0; pSafetyStopOrderID = 0;
		pExitingATrade = 1; sc.UpdateAlways = 1; //Make sure the reset code gets called next iteration.
		//Handle the close.
		if(sc.ReplayStatus != REPLAY_STOPPED) { // replay / back test in progress
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log action
			LogText.Format("%s %s Replay Exit: Exit Trend Line Hit (RC=%d): %f, Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, PriceTemp, PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		else if(RC > 0) {
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log success
			LogText.Format("%s %s Exit: Exit Trend Line Hit (RC=%d): %f, Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, PriceTemp, PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		//Handle an error.
		else {
			//Add error message to the Sierra Chart Message Log for interpretation.
 			//sc.AddMessageToLog(sc.GetTradingErrorTextMessage(RC), 0);
			LogText.Format("%s %s Error: Exit failed from Exit Trend Line Hit (RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, PriceTemp, PriceCurrent);
			sc.AddMessageToLog(LogText, 1);
			}
		#if DEBUGON > 0
		debug_PrintOrders(sc);
		#endif
		return;
		}
	} //end if Exit Trend Line hit.
	
	
	//Exit if MA Trailing Stop hit.
	if(	( (pTradeDirection == TD_Long) && (Graph_PriceMA[i] <= Graph_MATrailingStop[i]) ) ||
		( (pTradeDirection == TD_Short) && (Graph_PriceMA[i] >= Graph_MATrailingStop[i]) )
		) {
		//Close out everything. Keep it clean for the next iteration.
		RC = sc.FlattenAndCancelAllOrders();
		pPriceTargetOrderID = 0; pSafetyStopOrderID = 0;
		pExitingATrade = 1; sc.UpdateAlways = 1; //Make sure the reset code gets called next iteration.
		//Handle the close.
		if(sc.ReplayStatus != REPLAY_STOPPED) { // replay / back test in progress
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log success
			LogText.Format("%s %s Replay Exit: Multi-Function MA Trailing Stop Hit (RC=%d): %f, Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, Graph_MATrailingStop[i], PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		//Handle a successful close.
		else if(RC > 0) {
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log success
			LogText.Format("%s %s Exit: Multi-Function MA Trailing Stop Hit (RC=%d): %f, Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, Graph_MATrailingStop[i], PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		//Handle an error.
		else {
			//Add error message to the Sierra Chart Message Log for interpretation.
 			//sc.AddMessageToLog(sc.GetTradingErrorTextMessage(RC), 0);
			LogText.Format("%s %s Error: Exit failed from Multi-Function MA Trailing Stop Hit (RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, Graph_MATrailingStop[i], PriceCurrent);
			sc.AddMessageToLog(LogText, 1);
			}
		#if DEBUGON > 0
		debug_PrintOrders(sc);
		#endif
		return;
		} //end if MA Trailing Stop hit.

	
	//Exit if price target hit: stealth mode, managed by this program.
	if(pPriceTarget > 0.0) {
	if(	( (pTradeDirection == TD_Long) && (PriceCurrent >= pPriceTarget) ) ||
		( (pTradeDirection == TD_Short) && (PriceCurrent <= pPriceTarget) )
		) {
		//Close out everything. Keep it clean for the next iteration.
		RC = sc.FlattenAndCancelAllOrders();
		pPriceTargetOrderID = 0; pSafetyStopOrderID = 0;
		pExitingATrade = 1; sc.UpdateAlways = 1; //Make sure the reset code gets called next iteration.
		//Handle the close.
		if(sc.ReplayStatus != REPLAY_STOPPED) { // replay / back test in progress
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log success
			LogText.Format("%s %s Replay Exit: Stealth Price Target Hit (RC=%d): %f, Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, pPriceTarget, PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		//Handle a successful close.
		else if(RC > 0) {
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log success
			LogText.Format("%s %s Exit: Stealth Price Target Hit (RC=%d): %f, Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, pPriceTarget, PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		//Handle an error.
		else {
			//Add error message to the Sierra Chart Message Log for interpretation.
 			//sc.AddMessageToLog(sc.GetTradingErrorTextMessage(RC), 0);
			LogText.Format("%s %s Error: Exit failed from Stealth Price Target Hit (RC=%d): %f, Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), RC, pPriceTarget, PriceCurrent);
			sc.AddMessageToLog(LogText, 1);
			}
		#if DEBUGON > 0
		debug_PrintOrders(sc);
		#endif
		return;
		} //end if pPriceTarget hit.
	} //end if(pPriceTarget > 0.0)

	
	//Exit based on time of day.
	if( (pTimeExit > 0.0) && (sc.BaseDateTimeIn[sc.Index] >= pTimeExit) ) {
		//Close out everything. Keep it clean for the next iteration.
		RC = sc.FlattenAndCancelAllOrders();
		pPriceTargetOrderID = 0; pSafetyStopOrderID = 0;
		pExitingATrade = 1; sc.UpdateAlways = 1; //Make sure the reset code gets called next iteration.
		//Handle the close.
		if(sc.ReplayStatus != REPLAY_STOPPED) { // replay / back test in progress
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log success
			LogText.Format("%s %s Replay Exit: Exit Time Hit %d:%02d (RC=%d): Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), pTimeExit.GetHour(), pTimeExit.GetMinute(), RC, PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		//Handle a successful close.
		else if(RC > 0) {
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log success
			LogText.Format("%s %s Exit: Exit Time Hit %d:%02d (RC=%d): Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), pTimeExit.GetHour(), pTimeExit.GetMinute(), RC, PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		//Handle an error.
		else {
			//Add error message to the Sierra Chart Message Log for interpretation.
 			//sc.AddMessageToLog(sc.GetTradingErrorTextMessage(RC), 0);
			LogText.Format("%s %s Error: Exit failed from Exit Time Hit %d:%02d (RC=%d): Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), pTimeExit.GetHour(), pTimeExit.GetMinute(), RC, PriceCurrent);
			sc.AddMessageToLog(LogText, 1);
			}
		#if DEBUGON > 0
		debug_PrintOrders(sc);
		#endif
		return;
	} //end pTimeExit > 0.0
	
	
	//Exit based on weekend.
	if( (pWeekendExitTimeSeconds > 0.0) && (sc.BaseDateTimeIn[sc.Index].GetTime() >= pWeekendExitTimeSeconds ) &&
	    (sc.BaseDateTimeIn[sc.Index].GetDayOfWeek() == pWeekendExitDay) ) {
		//Close out everything. Keep it clean for the next iteration.
		RC = sc.FlattenAndCancelAllOrders();
		pPriceTargetOrderID = 0; pSafetyStopOrderID = 0;
		pExitingATrade = 1; sc.UpdateAlways = 1; //Make sure the reset code gets called next iteration.
		TIME_TO_HMS(pWeekendExitTimeSeconds, Hour, Minute, Second);
		//Handle the close.
		if(sc.ReplayStatus != REPLAY_STOPPED) { // replay / back test in progress
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log success
			LogText.Format("%s %s Replay Exit: Weekend Exit Time Hit %d:%02d.%02d D: %s (RC=%d): Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), Hour, Minute, Second, DayOfWeekToString(pWeekendExitDay, TempStr, 100), RC, PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		//Handle a successful close.
		else if(RC > 0) {
			//Draw the closing arrow
			if(pTradeDirection == TD_Long) {Graph_LongExit[i] = sc.Low[i];}
			else {Graph_ShortExit[i] = sc.High[i];}
			//Get the completed individual order action.
			sc.GetOrderFillEntry((sc.GetOrderFillArraySize() -1), OrderFillData); //Last entry index is newest entry.
			//Log success
			LogText.Format("%s %s Exit: Weekend Exit Time Hit %d:%02d.%02d D: %s (RC=%d): Price Current: %f, Slippage: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), Hour, Minute, Second, DayOfWeekToString(pWeekendExitDay, TempStr, 100), RC, PriceCurrent, (PriceCurrent - OrderFillData.AverageFillPrice));
			sc.AddMessageToLog(LogText, 0);
			}
		//Handle an error.
		else {
			//Add error message to the Sierra Chart Message Log for interpretation.
 			//sc.AddMessageToLog(sc.GetTradingErrorTextMessage(RC), 0);
			LogText.Format("%s %s Error: Exit failed from Weekend Exit Time Hit %d:%02d.%02d D: %s (RC=%d): Price Current: %f", PositionData.Symbol.GetChars(), (pTradeDirection==TD_Long?"Long":"Short"), Hour, Minute, Second, DayOfWeekToString(pWeekendExitDay, TempStr, 100), RC, PriceCurrent);
			sc.AddMessageToLog(LogText, 1);
			}
		#if DEBUGON > 0
		debug_PrintOrders(sc);
		#endif
		return;
	} //end pWeekendExitTimeSeconds > 0.0
	
	
	// *** Final settings before next loop. ***
	// *** Final settings before next loop. ***
	// *** Final settings before next loop. ***

	//Keep track of last index to detect bar changes.
	pIndexLast = sc.Index;
	
	//Keep track of volume for a change.
	pVolumePrevious = PositionData.PositionQuantity;
	
	//All reset functions done. Reset the reset variable.
	pResetIssued = 0; 
	
	#if DEBUGON > 0
	//DEBUG: One time print of all the orders.
	if(In_DebugPrintOrders.GetYesNo()) {debug_PrintOrders(sc); In_DebugPrintOrders.SetYesNo(0);}
	#endif
	
} //end

/* Replay Notes
sc.CurrentSystemDateTime always returns current system time and not the replay time. This breaks time based features in a replay.
sc.ReplayStatus will be REPLAY_STOPPED (not in a replay), REPLAY_RUNNING, or REPLAY_PAUSED.
sc.IsReplayRunning() returns true if running, false if not.
Replays only work on intraday charts, not historical charts. Bar Based Back Tests will work on historical charts.
Replays are done disconnected from the data/trade server.
*/

/* =============================================================================
================================================================================
Up/Down Volume Difference By Tick With Filters
================================================================================
============================================================================= */
SCSFExport scsf_UpDownVolumeDifferenceByTickWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef ZeroLine = sc.Subgraph[0]; //first graph is on the bottom.
	SCSubgraphRef Graph_Diff = sc.Subgraph[1];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_VolumeFilterType = sc.Input[1];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[2];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[3];
	SCInputRef In_DiffNormalSmoothingPeriod = sc.Input[4];
	SCInputRef In_DiffNormalSmoothingMAType = sc.Input[5];
	SCInputRef In_DiffSetExtraSmoothing = sc.Input[6];
	SCInputRef In_DiffExtraSmoothingPeriod = sc.Input[7];
	SCInputRef In_DiffExtraSmoothingMAType = sc.Input[8];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	SCSubgraphRef Diff = sc.Subgraph[3];
	SCSubgraphRef DiffSmoothed = sc.Subgraph[4];
	//SCFloatArrayRef FloatArray = Graph_Diff.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	float VolumeScale, Difference, Sign;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Up/Down Volume Difference By Tick With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 0; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Up/Down Volume Difference By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>This indicator shows the difference between up and down volume on a graph. Generally speaking, the difference in positive territory shows strength, and the difference in negative territory shows weakness. This indicator is very similar to \"Up/Down Volume Ratio\" but handles 2 problems: (1) On low volume the ratio can go way out in the distance. Low volume with this indicator will show low distance. If the distance is too low, try the Volume Filter of Square Root or Log for large number signal compression.(2) With each new bar the ratio usually jumps very far out and pulls back as enough data to establish a solid ratio becomes available. With this indicator each difference bar starts small and builds up as the volume bar grows. This also makes it easier to use with automated trading systems.\
<p>This indicator version has a second smoothing option. The difference data is very choppy and extremely noisy. The second moving average can be of any type and will help clean up the line. Smoothing with a larger number isn't as effective as double smoothing with a number half that size.\
<p>This indicator version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average.";

		//Output Graph
		Graph_Diff.Name = "Up/DnVolDiff"; //drawn graphs must have a name.
		Graph_Diff.PrimaryColor = RGB(255, 0, 255);
		Graph_Diff.DrawStyle = DRAWSTYLE_LINE;
		Graph_Diff.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Diff.LineWidth = 1;
		Graph_Diff.DrawZeros = 1;
		
		ZeroLine.Name="Zero";
		ZeroLine.DrawStyle = DRAWSTYLE_LINE;
		ZeroLine.LineStyle = LINESTYLE_DOT;
		ZeroLine.LineWidth = 1;
		ZeroLine.PrimaryColor = RGB(128, 128, 128);;
		ZeroLine.DisplayNameValueInWindowsFlags = 0;
		ZeroLine.DrawZeros = 1;
		
		//User Inputs
		
		In_InputData.Name = "Input Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");

		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");
		
		In_DiffNormalSmoothingPeriod.Name = "Normal Output Smoothing Period";
		In_DiffNormalSmoothingPeriod.SetInt(5);
		In_DiffNormalSmoothingPeriod.SetIntLimits(2, 50);
		In_DiffNormalSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-20.");
		
		In_DiffNormalSmoothingMAType.Name = "Normal Output Smoothing Moving Average Type";
		In_DiffNormalSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_DiffNormalSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");

		In_DiffSetExtraSmoothing.Name = "Set Extra Output Smoothing?";
		In_DiffSetExtraSmoothing.SetYesNo(1);
		In_DiffSetExtraSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_DiffExtraSmoothingPeriod.Name = "Extra Output Smoothing Period";
		In_DiffExtraSmoothingPeriod.SetInt(5);
		In_DiffExtraSmoothingPeriod.SetIntLimits(2, 50);
		In_DiffExtraSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_DiffExtraSmoothingMAType.Name = "Extra Output Smoothing Moving Average Type";
		In_DiffExtraSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_DiffExtraSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	//Handle the zero line.
	ZeroLine[sc.Index] = 0.0;

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_DiffNormalSmoothingPeriod.GetInt() + (In_DiffSetExtraSmoothing.GetYesNo() ? In_DiffExtraSmoothingPeriod.GetInt() : 0.0 );
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		if( (In_VolumeFilterType.GetIndex() == 0) || (In_VolumeFilterType.GetIndex() == 3) ) {sc.ValueFormat = 0;}
		else {sc.ValueFormat = 2;}
		}

	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}
	
	//Calculate volume difference.
	Difference = (float)sc.BaseData[Up][sc.Index] - (float)sc.BaseData[Down][sc.Index];
	//Value must be positive for log and sqrt, so save the sign in a separate variable.
	if(Difference < 0.0) {
		Difference *= -1.0;
		Sign = -1.0;
		}
	else {Sign = 1.0;}
	//Calculate filter type
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		Diff[sc.Index] = Difference * Sign;
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		Diff[sc.Index] = log( Difference < 1.0 ? 1.0 : Difference ) * Sign;
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		Diff[sc.Index] = sqrt( Difference < 1.0 ? 1.0 : Difference ) * Sign;
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.BaseData[VolumeType][sc.Index] <= VolumeMA[sc.Index]) {
			Diff[sc.Index] = Difference * Sign;
			}
		//handle clipped volume
		else {
			VolumeScale = (float)VolumeMA[sc.Index] / (float)sc.BaseData[VolumeType][sc.Index];
			Diff[sc.Index] = VolumeScale * Difference * Sign;
			}
		}
	
	//Handle smoothing.
	sc.MovingAverage(Diff, DiffSmoothed, In_DiffNormalSmoothingMAType.GetMovAvgType(), In_DiffNormalSmoothingPeriod.GetInt() );
	
	//Handle extra smoothing.
	if( In_DiffSetExtraSmoothing.GetYesNo() ) {
		sc.MovingAverage(DiffSmoothed, Graph_Diff, In_DiffExtraSmoothingMAType.GetMovAvgType(), In_DiffExtraSmoothingPeriod.GetInt() );
		}
	else {
		Graph_Diff[sc.Index] = DiffSmoothed[sc.Index];
		}
}

/* =============================================================================
================================================================================
Up/Down Volume Ratio With Limiter By Tick With Filters
================================================================================
============================================================================= */
SCSFExport scsf_UpDownVolumeRatioWithLimiterByTickWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef ZeroLine = sc.Subgraph[0]; //first graph is on the bottom.
	SCSubgraphRef Graph_VR = sc.Subgraph[1];
	SCInputRef In_NumberOfHighestValues = sc.Input[0];
	SCInputRef In_NumberOfBarsForHighs = sc.Input[1];
	SCInputRef In_LimiterStrength = sc.Input[2];
	SCInputRef In_InputData = sc.Input[3];
	SCInputRef In_VolumeFilterType = sc.Input[4];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[5];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[6];
	SCInputRef In_VRNormalSmoothingPeriod = sc.Input[7];
	SCInputRef In_VRNormalSmoothingMAType = sc.Input[8];
	SCInputRef In_VRSetExtraSmoothing = sc.Input[9];
	SCInputRef In_VRExtraSmoothingPeriod = sc.Input[10];
	SCInputRef In_VRExtraSmoothingMAType = sc.Input[11];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[2];
	SCSubgraphRef VolumeMA = sc.Subgraph[3];
	SCSubgraphRef ArrayOfHighs = sc.Subgraph[4];
	SCSubgraphRef VR = sc.Subgraph[5];
	SCSubgraphRef VRSmoothed = sc.Subgraph[6];
	//SCFloatArrayRef FloatArray = Graph_VR.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	int i, NumberOfHighs, NumberOfBars, VIdx, HIdx, IndexLow;
	float VolumeScale, AverageHigh, RatioScale;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Up/Down Volume Ratio With Limiter By Tick With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 3; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_INDEPENDENT; //separate graph
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Up/Down Volume Ratio With Limiter By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.<p>This indicator uses the traditional Up/Down Volume Ratio but adds a limiter to reduce the value on low volume. This helps reduce the large ranges on low volume that can blow out the scale. With the limiter in place, this is not a ratio with a 100% scale. It is very similar to Up/Down Volume Difference but much slower to calculate because of searching for the Highes Value average. The Highest Value average takes the selected number of highest values for a time period and averages them to a high value line. Anything above the line is ignored. Anything below the line gets the output ratio scaled proportionally by the limiter. Despite the higher number of calculations per bar, this helps identify which of the big peaks/dips are real or not. This indicator solves the problem of the ratio line jumping on each new bar with little data. This also makes it easier to use with automated trading systems.<p>This indicator version has a second smoothing option. The ratio data is very choppy and extremely noisy. The second moving average can be of any type and will help clean up the line. Smoothing with a larger number isn't as effective as double smoothing with a number half that size.<p>This indicator version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average.";

		//Output Graph
		Graph_VR.Name = "Up/DownVolRatio"; //drawn graphs must have a name.
		Graph_VR.PrimaryColor = RGB(255, 0, 255);
		Graph_VR.DrawStyle = DRAWSTYLE_LINE;
		Graph_VR.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_VR.LineWidth = 1;
		Graph_VR.DrawZeros = 1;
		
		ZeroLine.Name="Zero";
		ZeroLine.DrawStyle = DRAWSTYLE_LINE;
		ZeroLine.LineStyle = LINESTYLE_DOT;
		ZeroLine.LineWidth = 1;
		ZeroLine.PrimaryColor = RGB(128, 128, 128);;
		ZeroLine.DisplayNameValueInWindowsFlags = 0;
		ZeroLine.DrawZeros = 1;
		
		//User Inputs
		
		In_NumberOfHighestValues.Name = "Number Of Highest Values To Keep";
		In_NumberOfHighestValues.SetInt(20);
		In_NumberOfHighestValues.SetIntLimits(10, 500);
		In_NumberOfHighestValues.SetDescription("The number of highest values to look for in a range of bars. Usually 10-50. Note: the higher the number the slower the calculation will be.");

		In_NumberOfBarsForHighs.Name = "Number Of Bars To Search For Highest Values";
		In_NumberOfBarsForHighs.SetInt(240);
		In_NumberOfBarsForHighs.SetIntLimits(10, 3000);
		In_NumberOfBarsForHighs.SetDescription("The range of bars to look for the highest values. Usually 240 - 1440 (a few hours to about one full trading day). Note: the higher the number the slower the calculation will be.");
		
		In_LimiterStrength.Name = "Limiter Strength";
		In_LimiterStrength.SetFloat(0.9);
		In_LimiterStrength.SetFloatLimits(0.1, 1.0);
		In_LimiterStrength.SetDescription("The strength the limiter will apply to low volume ranges ranges to make matching low ratio ranges. Range 0.1 to 1.0 for 10-100%. Usually 0.9 (90%)");
		
		In_InputData.Name = "Input Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");

		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");
		
		In_VRNormalSmoothingPeriod.Name = "Normal Output Smoothing Period";
		In_VRNormalSmoothingPeriod.SetInt(7);
		In_VRNormalSmoothingPeriod.SetIntLimits(2, 50);
		In_VRNormalSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-20.");
		
		In_VRNormalSmoothingMAType.Name = "Normal Output Smoothing Moving Average Type";
		In_VRNormalSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_VRNormalSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_VRSetExtraSmoothing.Name = "Set Extra Output Smoothing?";
		In_VRSetExtraSmoothing.SetYesNo(1);
		In_VRSetExtraSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_VRExtraSmoothingPeriod.Name = "Extra Output Smoothing Period";
		In_VRExtraSmoothingPeriod.SetInt(7);
		In_VRExtraSmoothingPeriod.SetIntLimits(2, 50);
		In_VRExtraSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_VRExtraSmoothingMAType.Name = "Extra Output Smoothing Moving Average Type";
		In_VRExtraSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_VRExtraSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	i = sc.Index; //easier to read long lines
	
	//Handle the zero line.
	ZeroLine[i] = 0.0;

	//if first run. Set persistent variables here.
	if(i == 0) {
		//Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_VRNormalSmoothingPeriod.GetInt() + (In_VRSetExtraSmoothing.GetYesNo() ? In_VRExtraSmoothingPeriod.GetInt() : 0.0 );
		//Make sure the count of highs is less than or equal to the range.
		if(In_NumberOfHighestValues.GetInt() > In_NumberOfBarsForHighs.GetInt() ) {
			//swap the values around
			HIdx = In_NumberOfBarsForHighs.GetInt();
			In_NumberOfBarsForHighs.SetInt( In_NumberOfHighestValues.GetInt() );
			In_NumberOfHighestValues.SetInt(HIdx);
			}
		}

	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}
	
	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[i] = (float)sc.BaseData[VolumeType][i];
		VolumeScale = 1.0;
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[i] = log( (float)sc.BaseData[VolumeType][i] < 1.0 ? 1.0 : (float)sc.BaseData[VolumeType][i] );
		VolumeScale = VolumeFiltered[i] / (float)sc.BaseData[VolumeType][i];
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[i] = sqrt( (float)sc.BaseData[VolumeType][i] < 1.0 ? 1.0 : (float)sc.BaseData[VolumeType][i] );
		VolumeScale = VolumeFiltered[i] / (float)sc.BaseData[VolumeType][i];
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.BaseData[VolumeType][i] <= VolumeMA[i]) {
			//handle normal volume
			VolumeFiltered[i] = (float)sc.BaseData[VolumeType][i];
			VolumeScale = 1.0;
			}
		else { //handle clipped volume
			VolumeFiltered[i] = VolumeMA[i];
			VolumeScale = VolumeFiltered[i] / (float)sc.BaseData[VolumeType][i];
			}
		}
	
	//We need to shrink the smaller volume number's output to avoid them blowing the output range.
	//A moving average doesn't work as well here because it takes into account ALL numbers.
	//A better method is to take the selected highest numbers in the range and average them (ignoring the lowest numbers).
	//Enter...
	
	//The Sloppy High Values Bucket Algorithm: Faster than continuously sorting an array.
	//Start: Fill highs array and search for the low.
	//If (CURRENT > Low), then Low = CURRENT. Search for new low in highs array.
	//If (CURRENT < Low), then skip to next value.
	//Load and check ranges.
	NumberOfHighs = In_NumberOfHighestValues.GetInt();
	if(NumberOfHighs > i) {NumberOfHighs = i +1;}
	NumberOfBars = In_NumberOfBarsForHighs.GetInt();
	if(NumberOfBars > i) {NumberOfBars = i +1;}
	//Initial fill of array.
	VIdx = i - NumberOfBars +1;
	IndexLow = 0;
	for(HIdx=0; HIdx < NumberOfHighs; HIdx++, VIdx++) {
		ArrayOfHighs[HIdx] = VolumeFiltered[VIdx];
		if(ArrayOfHighs[IndexLow] > ArrayOfHighs[HIdx]) {IndexLow = HIdx;}
		}
	//Search the rest of the main array.
	for(; VIdx <= i; VIdx++) {
		if(VolumeFiltered[VIdx] > ArrayOfHighs[IndexLow]) {
			//Overwrite the low value
			ArrayOfHighs[IndexLow] = VolumeFiltered[VIdx];
			//Search for the new low index
			for(IndexLow=0, HIdx=1; HIdx < NumberOfHighs; HIdx++) {if(ArrayOfHighs[IndexLow] > ArrayOfHighs[HIdx]) {IndexLow = HIdx;}}
			}
		}
	//Calculate the average high.
	AverageHigh = 0.0;
	for(HIdx=0; HIdx < NumberOfHighs; HIdx++) {AverageHigh += ArrayOfHighs[HIdx];}
	AverageHigh /= (float)NumberOfHighs;
	
	//Calculate RatioScale to scale down volume ratio output number.
	//Higher numbers get passed.
	//Normal numbers won't be affected much.
	//Very low numbers get squashed to help prevent blowing the output range.
	//The limiter strength is a percentage of the RatioScale to use.
	if((VolumeFiltered[i] < AverageHigh) && (AverageHigh > 0.0) ) {
		RatioScale =  1.0 - ((1.0 - (VolumeFiltered[i] / AverageHigh)) * In_LimiterStrength.GetFloat() );
		}
	else {RatioScale = 1.0;}
	
	//Calculate volume ratio.
	if(VolumeFiltered[i] > 0) {
		VR[i] = ((((float)sc.BaseData[Up][i] - (float)sc.BaseData[Down][i]) * VolumeScale) / VolumeFiltered[i]) * 100.0 * RatioScale;
		}
	else {VR[i] = 0.0;}
	
	//Handle smoothing.
	sc.MovingAverage(VR, VRSmoothed, In_VRNormalSmoothingMAType.GetMovAvgType(), In_VRNormalSmoothingPeriod.GetInt() );
	
	//Handle extra smoothing.
	if( In_VRSetExtraSmoothing.GetYesNo() ) {
		sc.MovingAverage(VRSmoothed, Graph_VR, In_VRExtraSmoothingMAType.GetMovAvgType(), In_VRExtraSmoothingPeriod.GetInt() );
		}
	else {
		Graph_VR[i] = VRSmoothed[i];
		}
}

/* =============================================================================
================================================================================
Volume Bars Stacked By Tick
================================================================================
============================================================================= */
SCSFExport scsf_VolumeBarsStackedByTick(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_Total = sc.Subgraph[0];
	SCSubgraphRef Graph_Hold = sc.Subgraph[1];
	SCSubgraphRef Graph_Top = sc.Subgraph[2];
	SCSubgraphRef Graph_VolumeMA = sc.Subgraph[3];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_BuyColor = sc.Input[1];
	SCInputRef In_SellColor = sc.Input[2];
	SCInputRef In_SetSellOnTop = sc.Input[3];
	SCInputRef In_SetVolumeMA = sc.Input[4];
	SCInputRef In_VolumeMAPeriod = sc.Input[5];
	SCInputRef In_VolumeMAMAType = sc.Input[6];
	//SCFloatArrayRef FloatArray = Graph_OBV.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Volume Bars Stacked By Tick";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.AutoLoop = 1; //Auto looping is enabled.
		
		sc.CalculationPrecedence = STD_PREC_LEVEL; //STD_PREC_LEVEL (default), LOW_PREC_LEVEL, VERY_LOW_PREC_LEVEL
		
		//sc.GraphRegion = 1; //any graph
		sc.ValueFormat = 0; //Set output decimal places: 0-6. Also sc.BaseGraphValueFormat, VALUEFORMAT_INHERITED.
		sc.ScaleRangeType = SCALE_ZEROBASED; //separate graph starts at 0
		//options: SCALE_AUTO, SCALE_USERDEFINED, SCALE_INDEPENDENT, SCALE_SAMEASREGION, SCALE_CONSTRANGE, SCALE_CONSTRANGECENTER, SCALE_ZEROBASED
		
		sc.AlertOnlyOncePerBar = true; //Keep alerts from going crazy.
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Volume Bars Stacked By Tick. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.\
<p>This indicator shows a traditional volume bar split by buy and sell volumes as opposed to being a traditional entire buy or sell volume bar.\
<p>As of this programming, Sierra Chart doesn't have a stacked bar output feature. This is simulated using a trick from gnuplot by partly overwriting an existing bar. \"Total Volume\" should be the same color as \"Sell Volume\" (typically red). A red bar drawn on top of a red bar will look like the larger red bar. \"Buy Volume\" is then drawn on top again to show the usually green bar. Because of this, changing the bar colors may lead to unexpected consequences. For this reason, separate \"Buy Color\" and \"Sell Color\" entries have been made on the \"Settings And Inputs\" page. Change these two colors to your preferred settings and the rest of the bar colors will be automatically set. \"Volume MA\" still has its color on the \"Subgraphs\" page.<p>Observations. Institutions are known to manipulate bar open and close values to make the bar look like it was totally an up or down day. In reality, they may be buying or selling with or against the bar behind the scene. Having an accurate intraday volume count helps expose those patterns.\
<p>The three data bars are left independent in case someone wants to change them to line graphs to experiment.\
<p>A volume average line is included and can be disabled if desired. Normal values are 9 and 21 periods. SMA 9 is known to be a good activity indicator. When volume is above the line, a new movement is taking place. When volume then drops below the line, the movement is ending.";

		//Output Graph
		
		Graph_Total.Name = "Total Volume"; //drawn graphs must have a name.
		Graph_Total.PrimaryColor = RGB(255, 0, 0);
		Graph_Total.DrawStyle = DRAWSTYLE_BAR;
		Graph_Total.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Total.LineWidth = 2;
		Graph_Total.DrawZeros = 1;
		
		Graph_Hold.Name = "Sell Volume"; //drawn graphs must have a name.
		Graph_Hold.PrimaryColor = RGB(255, 0, 0);
		Graph_Hold.DrawStyle = DRAWSTYLE_BAR;
		Graph_Hold.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Hold.LineWidth = 2;
		Graph_Hold.DrawZeros = 1;
		
		Graph_Top.Name = "Buy Volume"; //drawn graphs must have a name.
		Graph_Top.PrimaryColor = RGB(0, 255, 0);
		Graph_Top.DrawStyle = DRAWSTYLE_BAR;
		Graph_Top.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Top.LineWidth = 2;
		Graph_Top.DrawZeros = 1;
		
		Graph_VolumeMA.Name = "Volume MA"; //drawn graphs must have a name.
		Graph_VolumeMA.PrimaryColor = RGB(255, 0, 255);
		Graph_VolumeMA.DrawStyle = DRAWSTYLE_LINE;
		Graph_VolumeMA.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_VolumeMA.LineWidth = 1;
		Graph_VolumeMA.DrawZeros = 1;
		
		//User Inputs
		
		In_InputData.Name = "Input Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Ask/Bid Volume;Up/Down Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");
		
		In_BuyColor.Name = "Buy Color";
		In_BuyColor.SetColor(0, 255, 0);
		In_BuyColor.SetDescription("The color of the Buy or up bars. With simulated bar stacking, it is safer to set the color on the Input Page.");
		
		In_SellColor.Name = "Sell Color";
		In_SellColor.SetColor(255, 0, 0);
		In_SellColor.SetDescription("The color of the Sell or down bars. With simulated bar stacking, it is safer to set the color on the Input Page.");
		
		In_SetSellOnTop.Name = "Set Sell On Top Of Buy?";
		In_SetSellOnTop.SetYesNo(1);
		In_SetSellOnTop.SetDescription("Stack sell on top of buy or \"No\" to flip it around.");
		
		In_SetVolumeMA.Name = "Set Volume Moving Average Line?";
		In_SetVolumeMA.SetYesNo(1);
		In_SetVolumeMA.SetDescription("Enables Volume MA Line.");
		
		In_VolumeMAPeriod.Name = "Volume MA Period";
		In_VolumeMAPeriod.SetInt(9);
		In_VolumeMAPeriod.SetIntLimits(2, 100);
		In_VolumeMAPeriod.SetDescription("Number of bars for the period. Usually 3-30. Values 9 and 21 are common.");
		
		In_VolumeMAMAType.Name = "Volume MA Moving Average Type";
		In_VolumeMAMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE); //or MOVAVGTYPE_EXPONENTIAL
		In_VolumeMAMAType.SetDescription("Usually SMA or EMA, but others can be experimented with.");
		
		return;
		}
	
	// Section 2 - Do data processing here

	//If first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = 0;
		//Turn the VolumeMA line off if disabled. Make sure it is on if re-enabled.
		if( In_SetVolumeMA.GetYesNo() ) {Graph_VolumeMA.DrawStyle = DRAWSTYLE_LINE;}
		else {Graph_VolumeMA.DrawStyle = DRAWSTYLE_IGNORE;}
		//Fix the bar namings and colors if the chart is in normal or swapped mode.
		//Manually setting names and colors makes sure it won't accidentally alternate.
		if(In_SetSellOnTop.GetYesNo() ) { //sell bar on top
			Graph_Total.PrimaryColor = In_SellColor.GetColor();
			Graph_Hold.Name = "Sell Volume";
			Graph_Hold.PrimaryColor = In_SellColor.GetColor();
			Graph_Top.Name = "Buy Volume";
			Graph_Top.PrimaryColor = In_BuyColor.GetColor();
			}
		else { //buy bar on top
			Graph_Total.PrimaryColor = In_BuyColor.GetColor();
			Graph_Hold.Name = "Buy Volume";
			Graph_Hold.PrimaryColor = In_BuyColor.GetColor();
			Graph_Top.Name = "Sell Volume";
			Graph_Top.PrimaryColor = In_SellColor.GetColor();
			}
		}
	
	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_ASKVOL; Down = SC_BIDVOL;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_UPVOL; Down = SC_DOWNVOL;}
	else {Up = SC_ASKNT; Down = SC_BIDNT;}
	
	//Calculate volume bar.
	Graph_Total[sc.Index] = sc.BaseData[Up][sc.Index] + sc.BaseData[Down][sc.Index];
	if(In_SetSellOnTop.GetYesNo() ) {
		//Buy layered on top of Sell. Sell appears to be stacked on top of Buy.
		Graph_Hold[sc.Index] = sc.BaseData[Down][sc.Index];
		Graph_Top[sc.Index] = sc.BaseData[Up][sc.Index];
		}
	else {
		//Sell layered on top of Buy. Buy appears to be stacked on top of Sell.
		Graph_Hold[sc.Index] = sc.BaseData[Up][sc.Index];
		Graph_Top[sc.Index] = sc.BaseData[Down][sc.Index];
		}
	
	//Handle VolumeMA line.
	if( In_SetVolumeMA.GetYesNo() ) {
		sc.MovingAverage(Graph_Total, Graph_VolumeMA, In_VolumeMAMAType.GetMovAvgType(), In_VolumeMAPeriod.GetInt() );
		}
}


