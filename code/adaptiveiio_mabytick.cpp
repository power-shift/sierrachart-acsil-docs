// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Adaptive IIO Moving Average By Tick With Filters") 

//Custom study starts here.
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
		sc.GraphName = "Adaptive IIO Moving Average By Tick With Filters";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive IIO Moving Average By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.<p>A price and volume based adaptive moving average from the Intraday Intensity Oscillator By Tick. Since IIO is semi-predictive, it is recommended to also run regular IIO By Tick in a sub chart for comparison.<p>This version includes extras to help clean up the graph and make it easier to integrate with automation. The \"Set IIO Smoothing?\" option enables cleaning up some of the IIO noise after the calculation. It is recommended to smooth IIO out with an EMA 3-7.<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.<p>The \"Scale Factor Change\" option allows the output line to be sped up or slowed down by modifying the EMA Scale Factor variable in the final adaptive calculation. It is recommended to change the main period variable first and then modify this one for fine tuning. A value of 1.0 (100%) will leave the rate unchanged. A value of 2.0 (200%) will double the rate. A value of 0.5 (50%) will cut the rate in half.<p>Observations. AIIO will often slow down and go flat when a movement is almost over. When there's a strong reversal, AIIO will go flat and then bend to follow the price. AIIO will often ignore most of a large price spike that's fake. AIIO will often go flat through noise that other adaptive moving averages will track.<p>Because of its use of real up/down tick data, this version tends to move much slower than its non-tick version. It may walk straight through lower volume fake price moves. If a faster adaptive moving average is also desired, run a second instance with a higher Scale Factor or Output Multiplier.<p>First known public AIIO version by Brett Johnson, 2015.";

		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		sc.GraphRegion = 0; //main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
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
		In_InputData.SetCustomInputStrings("Up/Down Volume;Ask/Bid Volume;Up/Down Trades");
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
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = 5;
		
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
	if(In_InputData.GetIndex() == 0) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
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
