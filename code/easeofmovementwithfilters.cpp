// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Ease Of Movement With Filters") 

//Custom study starts here.
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
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Ease Of Movement With Filters (EMV). A volume based oscillator developed by Richard Arms. Above the zero line shows positive movement. Below the zero line shows negative movement. Small volumes and a large high-low price range will produce higher EMV values since it took lower volume to move price more. Large volumes and a small high-low price range will produce lower EMV values since it took higher volumes to move the price a smaller amount. Once the price breaks out, the EMV line will start moving again. When price is significantly moving, the EMV line should be moving in the same direction and away from the zero line. This indicator should be used with other indicators to confirm final price movement.<p>This EMV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final EMV line.<p>Observations. Log and Square Root volume filtering have an interesting side effect of shrinking the EMV value on low volume moves. This is useful for identifying dead zones during the trading day.";
		
		//sc.GraphRegion = 1; //in this case, not main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
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
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = 2;
		
		return;
		}
	
	// Section 2 - Do data processing here

	//Handle the zero line.
	ZeroLine[sc.Index] = 0.0;
	
	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = 1;
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
