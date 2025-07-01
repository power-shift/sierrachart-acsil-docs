// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Volume Bars Stacked By Tick") 

//Custom study starts here.
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
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Volume Bars Stacked By Tick. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.<p>This indicator shows a traditional volume bar split by buy and sell volumes as opposed to being a traditional entire buy or sell volume bar.<p>As of this programming, Sierra Chart doesn't have a stacked bar output feature. This is simulated using a trick from gnuplot by partly overwriting an existing bar. \"Total Volume\" should be the same color as \"Sell Volume\" (typically red). A red bar drawn on top of a red bar will look like the larger red bar. \"Buy Volume\" is then drawn on top again to show the usually green bar. Because of this, changing the bar colors may lead to unexpected consequences. For this reason, separate \"Buy Color\" and \"Sell Color\" entries have been made on the \"Settings And Inputs\" page. Change these two colors to your preferred settings and the rest of the bar colors will be automatically set. \"Volume MA\" still has its color on the \"Subgraphs\" page.<p>Observations. Institutions are known to manipulate bar open and close values to make the bar look like it was totally an up or down day. In reality, they may be buying or selling with or against the bar behind the scene. Having an accurate intraday volume count helps expose those patterns.<p>The three data bars are left independent in case someone wants to change them to line graphs to experiment.<p>A volume average line is included and can be disabled if desired. Normal values are 9 and 21 periods. SMA 9 is known to be a good activity indicator. When volume is above the line, a new movement is taking place. When volume then drops below the line, the movement is ending.";
		
		//sc.GraphRegion = 1; //in this case, not main price graph
		
		//Volume bar graphs start at 0.
		sc.ScaleRangeType = SCALE_ZEROBASED;
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = 0; //whole numbers
		
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
		In_InputData.SetCustomInputStrings("Up/Down Volume;Ask/Bid Volume;Up/Down Trades");
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
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
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
	if(In_InputData.GetIndex() == 0) {Up = SC_UPVOL; Down = SC_DOWNVOL;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_ASKVOL; Down = SC_BIDVOL;}
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
