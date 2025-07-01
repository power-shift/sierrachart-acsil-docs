// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("On Balance Volume Price Movement With Filters") 

//Custom study starts here.
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
		sc.GraphName = "On Balance Volume Price Movement With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
	
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume Price Movement With Filters (OBVPM). An original indicator by Brett Johnson made in 2014. The intent is to help identify weak price movements from stronger ones by using volume with a scaling multiplier of bar height and bar close to close distance to create a balance function. Think of it as price distance pushed by volume. This graph should be plotted on the main price graph with an independent scale. If you have tick by tick data, use the \"By Tick\" version for much better accuracy. OBVPM is not locked to the price graph and will float and stretch, so the lines being above or below each other is totally relative. What is important is comparing the size of the price move with the size of the OBVPM move. Individual OBVPM bar values by themselves hold no meaning. The pattern is what's important.<p>The \"Set OBVPM Smoothing?\" option will enable a moving average filter to the output line. EMA5 is recommended to help keep the noise down and prevent false signals.<p>This version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. To learn the movement characteristics of each, it is recommended to put them all on one chart for equal comparison.<p>Observations. Log scale will tend to follow price closely. While it's useful to verify price movement, it's more useful to have the relative volume push distance. Take note of current peak and dip heights relative to previous ones. Larger price moves with smaller OBVPM moves indicate price weakness in that direction. In Straight mode, some sharp price reversals will show up as rounded reversals in the OBVPM line.";
		
		sc.GraphRegion = 0; //main price graph
		
		sc.ScaleRangeType = SCALE_INDEPENDENT; //independent scaling from price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
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
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = 2;
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = 1;
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
