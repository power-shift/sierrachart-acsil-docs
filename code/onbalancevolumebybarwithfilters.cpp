// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("On Balance Volume By Bar With Filters") 

//Custom study starts here.
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
		sc.GraphName = "On Balance Volume By Bar With Filters";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume By Bar With Filters. Traditional OBV is calculated by comparing the previuos bar with the current. This creates an offset problem. When watching a live graph, the current price and current volume happen together, not offset by 1. This OBV version fixes that. An up bar increases the balance. A down bar decreases the balance. A bar with an open equal to close does nothing. Note that true OBV requires tick by tick data, so if you have it, use it. This algorithm estimates OBV from data by the bar. Like all algorithms of this type, it is not 100% accurate and subject to manipulation by large institutions.<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.<p>Observations. The various volume filters are very effective and will walk right through the volume spike bar hardly noticing it. The volume filters also tend to minimize errant graph changes.<p>When using one of the volume filters, it is necessary to have the first OBV instance running in \"Straight\" mode. Add the second OBV instance to the same graph with \"Independent Scaling\". This is important because the filtered bars tend to drift in value with smaller volume bars. While this drift will show the OBV bias direction, it will not do it to scale and may cause false signals. The \"Straight\" instance will be used to verify actual distance moved. Note that Log tends to drift the most (sometimes offering an early indicator), followed by Square Root and then MA Clip. To learn the movement characteristics of each, put them all on one chart for equal comparison.<p>Take note when all OBV lines pivot in the same direction. This tends to indicate a change with strength.";
		
		//sc.GraphRegion = 1; //in this case, not main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
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
		In_MAClipSmoothingPeriod.SetInt(5);
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
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Initial setting for decimal places. Will be changed on first run.
		sc.ValueFormat = 0;
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = 0;
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = 2;
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
