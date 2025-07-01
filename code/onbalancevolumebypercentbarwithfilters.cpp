// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("On Balance Volume By Percent Bar With Filters") 

//Custom study starts here.
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
		sc.GraphName = "On Balance Volume By Percent Bar With Filters";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "On Balance Volume By Percent Bar With Filters. Traditional OBV is calculated by comparing the previuos bar with the current. This creates an offset problem. When watching a live graph, the current price and current volume happen together, not offset by 1. This OBV version fixes that and adds a percent scale. The scale splits the bar based on where close is within the high to low range. A close in the middle does nothing. A close below middle subtracts more from the balance than it adds. A close above middle adds more to the balance than it subtracts. Note that true OBV requires tick by tick data, so if you have it, use it. This algorithm estimates OBV from data by the bar. Like all algorithms of this type, it is not 100% accurate and subject to manipulation by large institutions.<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.<p>Observations. The various volume filters are very effective and will walk right through the volume spike bar hardly noticing it. The volume filters also tend to minimize errant graph changes.<p>When using one of the volume filters, it is necessary to have the first OBV instance running in \"Straight\" mode. Add the second OBV instance to the same graph with \"Independent Scaling\". This is important because the filtered bars tend to drift in value with smaller volume bars. While this drift will show the OBV bias direction, it will not do it to scale and may cause false signals. The \"Straight\" instance will be used to verify actual distance moved. Note that Log tends to drift the most (sometimes offering an early indicator), followed by Square Root and then MA Clip. To learn the movement characteristics of each, put them all on one chart for equal comparison.<p>Take note when all OBV lines pivot in the same direction. This tends to indicate a change with strength.";
		
		//sc.GraphRegion = 1; //in this case, not main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
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
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = 2;
		
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
		sc.DataStartIndex = 0;
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
