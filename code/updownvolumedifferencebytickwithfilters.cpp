// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Up/Down Volume Difference By Tick With Filters") 

//Custom study starts here.
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
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Up/Down Volume Difference By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.<p>This indicator shows the difference between up and down volume on a graph. Generally speaking, the difference in positive territory shows strength, and the difference in negative territory shows weakness. This indicator is very similar to \"Up/Down Volume Ratio\" but handles 2 problems: (1) On low volume the ratio can go way out in the distance. Low volume with this indicator will show low distance. If the distance is too low, try the Volume Filter of Square Root or Log for large number signal compression.(2) With each new bar the ratio usually jumps very far out and pulls back as enough data to establish a solid ratio becomes available. With this indicator each difference bar starts small and builds up as the volume bar grows. This also makes it easier to use with automated trading systems.<p>This indicator version has a second smoothing option. The difference data is very choppy and extremely noisy. The second moving average can be of any type and will help clean up the line. Smoothing with a larger number isn't as effective as double smoothing with a number half that size.<p>This indicator version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average.";
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//sc.GraphRegion = 1; //in this case, not main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
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
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Initial setting for decimal places. Will be changed on first run.
		sc.ValueFormat = 0;
		
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
	if(In_InputData.GetIndex() == 0) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
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
