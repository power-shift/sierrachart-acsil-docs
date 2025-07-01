// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("On Balance Volume By Tick With Filters") 

//Custom study starts here.
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
		sc.GraphName = "On Balance Volume By Tick With Filters";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.<p>This OBV version adds a moving average ribbon to help quantify the moves. Reading the ribbon is the same as if the ribbon was attached to a price line. If the ribbon is enabled, it is recommended to give it a lot of screen height to see the movement. Adding it to a second chart may be a better option. Institutional traders do use moving average lines as seen by the OBV line bending, pausing, and reversing at the standard levels. The colors chosen are based on light frequency from slow to fast (think of a prism or rainbow). This method makes remembering the values much easier. Standard values are red=200, orange=100, yellow=50, green=35, and cyan=20. These can all be changed in the configuration menu.<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.<p>Observations. The various volume filters are very effective and will walk right through the volume spike bar hardly noticing it. The volume filters also tend to minimize errant graph changes.<p>When using one of the volume filters, it is necessary to have the first OBV instance running in \"Straight\" mode. Add the second OBV instance to the same graph with \"Independent Scaling\". This is important because the filtered bars tend to drift in value with smaller volume bars. While this drift will show the OBV bias direction, it will not do it to scale and may cause false signals. The \"Straight\" instance will be used to verify actual distance moved. Note that Log tends to drift the most (sometimes offering an early indicator), followed by Square Root and then MA Clip. To learn the movement characteristics of each, put them all on one chart for equal comparison.<p>Take note when all OBV lines pivot in the same direction. This tends to indicate a change with strength.";
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		//sc.GraphRegion = 1; //in this case, not main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
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
	if(In_InputData.GetIndex() == 0) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
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
