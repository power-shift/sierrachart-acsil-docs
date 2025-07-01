// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Bollinger Band Ribbon") 

//Custom study starts here.
SCSFExport scsf_BollingerBandRibbon(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_BB5Low = sc.Subgraph[0];
	SCSubgraphRef Graph_BB5Mid = sc.Subgraph[1];
	SCSubgraphRef Graph_BB5Top = sc.Subgraph[2];
	SCSubgraphRef Graph_BB4Low = sc.Subgraph[3];
	SCSubgraphRef Graph_BB4Mid = sc.Subgraph[4];
	SCSubgraphRef Graph_BB4Top = sc.Subgraph[5];
	SCSubgraphRef Graph_BB3Low = sc.Subgraph[6];
	SCSubgraphRef Graph_BB3Mid = sc.Subgraph[7];
	SCSubgraphRef Graph_BB3Top = sc.Subgraph[8];
	SCSubgraphRef Graph_BB2Low = sc.Subgraph[9];
	SCSubgraphRef Graph_BB2Mid = sc.Subgraph[10];
	SCSubgraphRef Graph_BB2Top = sc.Subgraph[11];
	SCSubgraphRef Graph_BB1Low = sc.Subgraph[12];
	SCSubgraphRef Graph_BB1Mid = sc.Subgraph[13];
	SCSubgraphRef Graph_BB1Top = sc.Subgraph[14];
	SCSubgraphRef Graph_PrimaryLine = sc.Subgraph[15];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_SetPrimaryLine = sc.Input[1];
	SCInputRef In_PrimaryLinePeriod = sc.Input[2];
	SCInputRef In_PrimaryLineMAType = sc.Input[3];
	SCInputRef In_StandardDeviation = sc.Input[4];
	SCInputRef In_BBRibbonMAType = sc.Input[5];
	SCInputRef In_BBRibbon1Period = sc.Input[6];
	SCInputRef In_BBRibbon2Period = sc.Input[7];
	SCInputRef In_BBRibbon3Period = sc.Input[8];
	SCInputRef In_BBRibbon4Period = sc.Input[9];
	SCInputRef In_BBRibbon5Period = sc.Input[10];

	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Bollinger Band Ribbon";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Bollinger Band Ribbon: Taking The Moving Average Ribbon To A New Extreme. Bollinger Bands take a moving average and add high and low lines at 2.0 standard deviations away (configurable) to help show movement ranges. A Bollinger Band Ribbon is a moving average ribbon with these high and low lines for each individual line. A moving average ribbon is a set of moving average lines of differing values following a single source. That source is usually price but non-oscillating indicators can also have a ribbon attached to them. It is recommended to give the ribbon a lot of screen height to see the movement... even more than a straight moving average ribbon. Institutional traders do use Bollinger Bands as seen by price lines bending, pausing, and reversing at the standard levels and with their high and low lines. The Primary Line is usually a small EMA number to closely track the source. If it's not needed, it can be set to another moving average number and type or set to disabled. The ribbon lines are usually Simple Moving Averages since that is what the big institutions use. Both moving average types can be changed.<p>The colors chosen are based on light frequency from slow to fast (think of a prism or rainbow). This method makes remembering the values much easier. Industry standard values are red=200, orange=100, yellow=50, green=35, and cyan=20. These can all be changed in the configuration menu.<p>This simple study offers the convenience of setting up 5 Bollinger Bands quickly in one place and making sure they are all scaled properly together on the same graph. It also simplifies the setup for automation.<p>At first glance this can be very confusing to look at, but it is easy to understand and use once explained. It's all about watching the data line.<ul><li>If the data line is rising, identify which color top band it is touching the most. That is the channel the data line is in. Flip that over for a falling data line.<li>If the data line has a strong movement then goes flat, take note of which mid line it is sitting on or resting under. If the data line gets stuck between a mid line and outer band, the move may be over or about to reverse.<li>If the data line has gone flat, identify which color mid line it is crossing the most. Then look high and low for the outer bands of the same color. That will be the channel the data line is in. Watch for an eventual break out.<li>When rising or falling, the data line may cross a mid line and touch a top line that is also riding on the next level up mid line. That means the data line is fully in the channel of the first mid line but could break out to the top line of the second mid line.<li>During any real movement, the data line will mostly be in one channel, be popping into the next channel every now and then, and be constrained to the upper or lower section of the next channel up. If the move fails to hit the outer band of that highest level channel, the move may not be over yet.<li>Wave counters take note of the previous two points. The corrective waves will be the ones crossing outer bands and the next level mid lines. If the continuation movement doesn't return to the previous movement, the correction may be larger than expected or the overall movement may be over.<li>The 200 period bands are usually the long term channel for the data line. The data line will usually bounce back if it crosses its outer band lines (they may stretch a little). If the data line keeps going, look for a new long term trend direction to start.<li>In summary, Bollinger Bands are all about dynamic support and resistance lines and measuring movement. If a line on one level gets crossed, look for the action to be defined on the next level up (the bands will start expanding). If volatility starts to decrease, look for the action to be defined on the next level down (the bands will start contracting).</ul><p>As an exercise to help you see the messy bands easier, pick a color and focus on it very hard. Try to block out all other colors except the one you're focusing on. While still focusing on that color, let your vision go soft. Without moving your eyes off the first color, look for the other lines of the same color in your peripheral vision. With a little practice, this will become easy.";
		
		//sc.GraphRegion = 0; //main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graphs
		
		Graph_PrimaryLine.Name = "Primary Line"; //drawn graphs must have a name.
		Graph_PrimaryLine.PrimaryColor = RGB(255, 255, 255);
		Graph_PrimaryLine.DrawStyle = DRAWSTYLE_LINE;
		Graph_PrimaryLine.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_PrimaryLine.LineWidth = 2;
		Graph_PrimaryLine.DrawZeros = 1;
		
		
		Graph_BB1Top.Name = "BB1 Top"; //drawn graphs must have a name.
		Graph_BB1Top.PrimaryColor = RGB(0, 255, 255);
		Graph_BB1Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB1Top.LineWidth = 1;
		Graph_BB1Top.DrawZeros = 1;
		
		Graph_BB1Mid.Name = "BB1 Mid"; //drawn graphs must have a name.
		Graph_BB1Mid.PrimaryColor = RGB(0, 255, 255);
		Graph_BB1Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB1Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB1Mid.LineWidth = 2;
		Graph_BB1Mid.DrawZeros = 1;
		
		Graph_BB1Low.Name = "BB1 Low"; //drawn graphs must have a name.
		Graph_BB1Low.PrimaryColor = RGB(0, 255, 255);
		Graph_BB1Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB1Low.LineWidth = 1;
		Graph_BB1Low.DrawZeros = 1;
		
		
		Graph_BB2Top.Name = "BB2 Top"; //drawn graphs must have a name.
		Graph_BB2Top.PrimaryColor = RGB(0, 255, 0);
		Graph_BB2Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB2Top.LineWidth = 1;
		Graph_BB2Top.DrawZeros = 1;
		
		Graph_BB2Mid.Name = "BB2 Mid"; //drawn graphs must have a name.
		Graph_BB2Mid.PrimaryColor = RGB(0, 255, 0);
		Graph_BB2Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB2Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB2Mid.LineWidth = 2;
		Graph_BB2Mid.DrawZeros = 1;
		
		Graph_BB2Low.Name = "BB2 Low"; //drawn graphs must have a name.
		Graph_BB2Low.PrimaryColor = RGB(0, 255, 0);
		Graph_BB2Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB2Low.LineWidth = 1;
		Graph_BB2Low.DrawZeros = 1;


		Graph_BB3Top.Name = "BB3 Top"; //drawn graphs must have a name.
		Graph_BB3Top.PrimaryColor = RGB(255, 255, 0);
		Graph_BB3Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB3Top.LineWidth = 1;
		Graph_BB3Top.DrawZeros = 1;
		
		Graph_BB3Mid.Name = "BB3 Mid"; //drawn graphs must have a name.
		Graph_BB3Mid.PrimaryColor = RGB(255, 255, 0);
		Graph_BB3Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB3Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB3Mid.LineWidth = 2;
		Graph_BB3Mid.DrawZeros = 1;
		
		Graph_BB3Low.Name = "BB3 Low"; //drawn graphs must have a name.
		Graph_BB3Low.PrimaryColor = RGB(255, 255, 0);
		Graph_BB3Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB3Low.LineWidth = 1;
		Graph_BB3Low.DrawZeros = 1;
		

		Graph_BB4Top.Name = "BB4 Top"; //drawn graphs must have a name.
		Graph_BB4Top.PrimaryColor = RGB(255, 128, 0);
		Graph_BB4Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB4Top.LineWidth = 1;
		Graph_BB4Top.DrawZeros = 1;
		
		Graph_BB4Mid.Name = "BB4 Mid"; //drawn graphs must have a name.
		Graph_BB4Mid.PrimaryColor = RGB(255, 128, 0);
		Graph_BB4Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB4Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB4Mid.LineWidth = 2;
		Graph_BB4Mid.DrawZeros = 1;
		
		Graph_BB4Low.Name = "BB4 Low"; //drawn graphs must have a name.
		Graph_BB4Low.PrimaryColor = RGB(255, 128, 0);
		Graph_BB4Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB4Low.LineWidth = 1;
		Graph_BB4Low.DrawZeros = 1;
		
		
		Graph_BB5Top.Name = "BB5 Top"; //drawn graphs must have a name.
		Graph_BB5Top.PrimaryColor = RGB(255, 0, 0);
		Graph_BB5Top.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB5Top.LineWidth = 1;
		Graph_BB5Top.DrawZeros = 1;
		
		Graph_BB5Mid.Name = "BB5 Mid"; //drawn graphs must have a name.
		Graph_BB5Mid.PrimaryColor = RGB(255, 0, 0);
		Graph_BB5Mid.DrawStyle = DRAWSTYLE_LINE;
		Graph_BB5Mid.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_BB5Mid.LineWidth = 2;
		Graph_BB5Mid.DrawZeros = 1;
		
		Graph_BB5Low.Name = "BB5 Low"; //drawn graphs must have a name.
		Graph_BB5Low.PrimaryColor = RGB(255, 0, 0);
		Graph_BB5Low.DrawStyle = DRAWSTYLE_POINT;
		Graph_BB5Low.LineWidth = 1;
		Graph_BB5Low.DrawZeros = 1;
		
		//User Inputs	
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData.SetDescription("Usually \"Last\" for Close.");
		
		In_SetPrimaryLine.Name = "Enable Primary Line?";
		In_SetPrimaryLine.SetYesNo(1);
		In_SetPrimaryLine.SetDescription("Enables the Primary Line.");
		
		In_PrimaryLinePeriod.Name = "Primary Line Smoothing Period";
		In_PrimaryLinePeriod.SetInt(3);
		In_PrimaryLinePeriod.SetIntLimits(2, 1000);
		In_PrimaryLinePeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_PrimaryLineMAType.Name = "Primary Line Moving Average Type";
		In_PrimaryLineMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_PrimaryLineMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_StandardDeviation.Name = "Standard Deviation";
		In_StandardDeviation.SetFloat(2.0);
		In_StandardDeviation.SetFloatLimits(0.1, 10.0);
		In_StandardDeviation.SetDescription("Bollinger Bands Standard Deviation setting. Usually 2.0.");
		
		In_BBRibbonMAType.Name = "Moving Average Type";
		In_BBRibbonMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_BBRibbonMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_BBRibbon1Period.Name = "MA Line 1 Period";
		In_BBRibbon1Period.SetInt(20);
		In_BBRibbon1Period.SetIntLimits(2, 1000);
		In_BBRibbon1Period.SetDescription("Number of bars for the period. Usually 20.");
		
		In_BBRibbon2Period.Name = "MA Line 2 Period";
		In_BBRibbon2Period.SetInt(35);
		In_BBRibbon2Period.SetIntLimits(2, 1000);
		In_BBRibbon2Period.SetDescription("Number of bars for the period. Usually 35.");
		
		In_BBRibbon3Period.Name = "MA Line 3 Period";
		In_BBRibbon3Period.SetInt(50);
		In_BBRibbon3Period.SetIntLimits(2, 1000);
		In_BBRibbon3Period.SetDescription("Number of bars for the period. Usually 50.");
		
		In_BBRibbon4Period.Name = "MA Line 4 Period";
		In_BBRibbon4Period.SetInt(100);
		In_BBRibbon4Period.SetIntLimits(2, 1000);
		In_BBRibbon4Period.SetDescription("Number of bars for the period. Usually 100.");
		
		In_BBRibbon5Period.Name = "MA Line 5 Period";
		In_BBRibbon5Period.SetInt(200);
		In_BBRibbon5Period.SetIntLimits(2, 1000);
		In_BBRibbon5Period.SetDescription("Number of bars for the period. Usually 200.");
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Setting for decimal places.
		sc.ValueFormat = VALUEFORMAT_INHERITED;
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	if(sc.Index == 0) {
		//Turn off Graph_PrimaryLine if disabled.
		if(In_SetPrimaryLine.GetYesNo()) {Graph_PrimaryLine.DrawStyle = DRAWSTYLE_LINE;}
		else {Graph_PrimaryLine.DrawStyle = DRAWSTYLE_IGNORE;}
		}
	
	if(In_SetPrimaryLine.GetYesNo()) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_PrimaryLine, In_PrimaryLineMAType.GetMovAvgType(), In_PrimaryLinePeriod.GetInt() );
		}
	
	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB1Mid, In_BBRibbon1Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB1Top[sc.Index] = Graph_BB1Mid.Arrays[0][sc.Index];
	Graph_BB1Low[sc.Index] = Graph_BB1Mid.Arrays[1][sc.Index];

	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB2Mid, In_BBRibbon2Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB2Top[sc.Index] = Graph_BB2Mid.Arrays[0][sc.Index];
	Graph_BB2Low[sc.Index] = Graph_BB2Mid.Arrays[1][sc.Index];
	
	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB3Mid, In_BBRibbon3Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB3Top[sc.Index] = Graph_BB3Mid.Arrays[0][sc.Index];
	Graph_BB3Low[sc.Index] = Graph_BB3Mid.Arrays[1][sc.Index];
	
	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB4Mid, In_BBRibbon4Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB4Top[sc.Index] = Graph_BB4Mid.Arrays[0][sc.Index];
	Graph_BB4Low[sc.Index] = Graph_BB4Mid.Arrays[1][sc.Index];
	
	sc.BollingerBands(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_BB5Mid, In_BBRibbon5Period.GetInt(), In_StandardDeviation.GetFloat(),In_BBRibbonMAType.GetMovAvgType());
	Graph_BB5Top[sc.Index] = Graph_BB5Mid.Arrays[0][sc.Index];
	Graph_BB5Low[sc.Index] = Graph_BB5Mid.Arrays[1][sc.Index];
}
