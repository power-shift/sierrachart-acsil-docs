// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Moving Average Ribbon") 

//Custom study starts here.
SCSFExport scsf_MovingAverageRibbon(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_MA5 = sc.Subgraph[0];
	SCSubgraphRef Graph_MA4 = sc.Subgraph[1];
	SCSubgraphRef Graph_MA3 = sc.Subgraph[2];
	SCSubgraphRef Graph_MA2 = sc.Subgraph[3];
	SCSubgraphRef Graph_MA1 = sc.Subgraph[4];
	SCSubgraphRef Graph_MA0 = sc.Subgraph[5];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_SetMARibbon0 = sc.Input[1];
	SCInputRef In_MARibbon0Period = sc.Input[2];
	SCInputRef In_MARibbon0MAType = sc.Input[3];
	SCInputRef In_MARibbonMAType = sc.Input[4];
	SCInputRef In_MARibbon1Period = sc.Input[5];
	SCInputRef In_MARibbon2Period = sc.Input[6];
	SCInputRef In_MARibbon3Period = sc.Input[7];
	SCInputRef In_MARibbon4Period = sc.Input[8];
	SCInputRef In_MARibbon5Period = sc.Input[9];

	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Moving Average Ribbon";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Moving Average Ribbon. A moving average ribbon is a set of moving average lines of differing values following a single source. That source is usually price but non-oscillating indicators can also have a ribbon attached to them. It is recommended to give the ribbon a lot of screen height to see the movement. Institutional traders do use moving average lines as seen by price lines bending, pausing, and reversing at the standard levels. The Primary Line is usually a small EMA number to closely track the source. If it's not needed, it can be set to another moving average number and type or set to disable. The ribbon lines are usually Simple Moving Averages since that is what the big institutions use. Both moving average types can be changed.<p>The colors chosen are based on light frequency from slow to fast (think of a prism or rainbow). This method makes remembering the values much easier. Industry standard values are red=200, orange=100, yellow=50, green=35, and cyan=20. These can all be changed in the configuration menu.<p>This simple study offers the convenience of setting up 6 MA lines quickly in one place and making sure they are all scaled properly together on the same graph. It also simplifies the setup for automation.";
		
		//sc.GraphRegion = 0; //main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graphs

		Graph_MA0.Name = "Primary Line"; //drawn graphs must have a name.
		Graph_MA0.PrimaryColor = RGB(255, 255, 255);
		Graph_MA0.DrawStyle = DRAWSTYLE_LINE;
		Graph_MA0.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_MA0.LineWidth = 2;
		Graph_MA0.DrawZeros = 1;
		
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
		In_InputData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData.SetDescription("Usually \"Last\" for Close.");
		
		In_SetMARibbon0.Name = "Enable Primary Line?";
		In_SetMARibbon0.SetYesNo(1);
		In_SetMARibbon0.SetDescription("Enables the Primary Line.");
		
		In_MARibbon0Period.Name = "Primary Line Smoothing Period";
		In_MARibbon0Period.SetInt(3);
		In_MARibbon0Period.SetIntLimits(2, 1000);
		In_MARibbon0Period.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_MARibbon0MAType.Name = "Primary Line Moving Average Type";
		In_MARibbon0MAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MARibbon0MAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_MARibbonMAType.Name = "MA Ribbon Moving Average Type";
		In_MARibbonMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_MARibbonMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_MARibbon1Period.Name = "MA Line 1 Period";
		In_MARibbon1Period.SetInt(20);
		In_MARibbon1Period.SetIntLimits(2, 1000);
		In_MARibbon1Period.SetDescription("Number of bars for the period. Usually 20.");
		
		In_MARibbon2Period.Name = "MA Line 2 Period";
		In_MARibbon2Period.SetInt(35);
		In_MARibbon2Period.SetIntLimits(2, 1000);
		In_MARibbon2Period.SetDescription("Number of bars for the period. Usually 35.");
		
		In_MARibbon3Period.Name = "MA Line 3 Period";
		In_MARibbon3Period.SetInt(50);
		In_MARibbon3Period.SetIntLimits(2, 1000);
		In_MARibbon3Period.SetDescription("Number of bars for the period. Usually 50.");
		
		In_MARibbon4Period.Name = "MA Line 4 Period";
		In_MARibbon4Period.SetInt(100);
		In_MARibbon4Period.SetIntLimits(2, 1000);
		In_MARibbon4Period.SetDescription("Number of bars for the period. Usually 100.");
		
		In_MARibbon5Period.Name = "MA Line 5 Period";
		In_MARibbon5Period.SetInt(200);
		In_MARibbon5Period.SetIntLimits(2, 1000);
		In_MARibbon5Period.SetDescription("Number of bars for the period. Usually 200.");
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Setting for decimal places.
		sc.ValueFormat = VALUEFORMAT_INHERITED;
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	if(sc.Index == 0) {
		//Turn off MA0 if disabled.
		if(In_SetMARibbon0.GetYesNo()) {Graph_MA0.DrawStyle = DRAWSTYLE_LINE;}
		else {Graph_MA0.DrawStyle = DRAWSTYLE_IGNORE;}
		}

	if(In_SetMARibbon0.GetYesNo()) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA0, In_MARibbon0MAType.GetMovAvgType(), In_MARibbon0Period.GetInt() );
		}

	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA1, In_MARibbonMAType.GetMovAvgType(), In_MARibbon1Period.GetInt() );
	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA2, In_MARibbonMAType.GetMovAvgType(), In_MARibbon2Period.GetInt() );
	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA3, In_MARibbonMAType.GetMovAvgType(), In_MARibbon3Period.GetInt() );
	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA4, In_MARibbonMAType.GetMovAvgType(), In_MARibbon4Period.GetInt() );
	sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Graph_MA5, In_MARibbonMAType.GetMovAvgType(), In_MARibbon5Period.GetInt() );
}
