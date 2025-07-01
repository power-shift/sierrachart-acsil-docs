// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Adaptive MFI Moving Average With Filters") 

//Custom study starts here.
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
		sc.GraphName = "Adaptive MFI Moving Average With Filters";

		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive MFI Moving Average With Filters. Adaptive MFI (AMFI) uses price as an input and then MFI as the scaling factor in an exponential moving average equation. It is very similar to Adaptive RSI (ARSI). Some people prefer the MFI indicator over the RSI indicator since it takes volume into account.<p> The proper MFI algorithm uses Typical Price (HLC Avg) as the input. There is an option to change this if desired. The \"Set Price Smoothing?\" option enables cleaning up the price before calculations. If price is really noisy, recommended settings are EMA 3-10. Otherwise leave price smoothing off. The \"Set MFI Smoothing?\" option enables cleaning up some of the MFI noise before AMFI is calculated. It is recommended to smooth MFI out with an EMA 3-7. This allows for less volatility and more consistent movements. <p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.<p>The \"Scale Factor Change\" option allows the output line to be sped up or slowed down by modifying the EMA Scale Factor variable in the final adaptive calculation. It is recommended to change the main period variable first and then modify this one for fine tuning. A value of 1.0 (100%) will leave the rate unchanged. A value of 2.0 (200%) will double the rate. A value of 0.5 (50%) will cut the rate in half.<p>To use straight AMFI without any enhancements, turn off all extra options.<p>Observations: When there's a strong reversal, AMFI will go flat and then bend to follow the price. It will do this more than ARSI given the same settings. AMFI will often go flat before the end of major price peaks/dips indicating that the move is almost over (something ARSI will not do). On weaker events, AMFI will go flat while price bounces around above or below and then returns to the AMFI line. Check indicators and wave counts to verify final motion.<p>To visualize what the scaling factor is doing, a separate MFI graph can be added with the selected smoothing values. When MFI is close to 50, the AMFI line will go flat and move less. Further away from 50 will increase the line movement.<p>First known public AMFI version by Brett Johnson, 2015.";
		
		sc.GraphRegion = 0; //main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
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
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = sc.BaseGraphValueFormat;
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	i = sc.Index; //easier to read traditional C/C++ index i in multiple arrays on one line.
	Period = In_AMFIPeriod.GetInt(); //easier to read.
	
	//if first run
	if (i == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = Period - 1;
		//return;
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
