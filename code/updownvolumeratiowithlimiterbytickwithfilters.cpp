// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Up/Down Volume Ratio With Limiter By Tick With Filters") 

//Custom study starts here.
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
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Up/Down Volume Ratio With Limiter By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.<p>This indicator uses the traditional Up/Down Volume Ratio but adds a limiter to reduce the value on low volume. This helps reduce the large ranges on low volume that can blow out the scale. With the limiter in place, this is not a ratio with a 100% scale. It is very similar to Up/Down Volume Difference but much slower to calculate because of searching for the Highes Value average. The Highest Value average takes the selected number of highest values for a time period and averages them to a high value line. Anything above the line is ignored. Anything below the line gets the output ratio scaled proportionally by the limiter. Despite the higher number of calculations per bar, this helps identify which of the big peaks/dips are real or not. This indicator solves the problem of the ratio line jumping on each new bar with little data. This also makes it easier to use with automated trading systems.<p>This indicator version has a second smoothing option. The ratio data is very choppy and extremely noisy. The second moving average can be of any type and will help clean up the line. Smoothing with a larger number isn't as effective as double smoothing with a number half that size.<p>This indicator version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average.";
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//sc.GraphRegion = 1; //in this case, not main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
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
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Set printed output value format. Number is the index of the selected format.
		sc.ValueFormat = 3;  // 3 decimal places
		
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
	if(In_InputData.GetIndex() == 0) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
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
