// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Scale Study to 100 Graph By Zero Line") 

//Custom study starts here.
SCSFExport scsf_ScaleTo100ByZeroLine(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	//Keep graphs and associated inputs on the same index number.
	SCSubgraphRef Graph_Line1 = sc.Subgraph[0];
	SCSubgraphRef Graph_Line2 = sc.Subgraph[1];
	SCSubgraphRef Graph_Line3 = sc.Subgraph[2];
	SCSubgraphRef Graph_Line4 = sc.Subgraph[3];
	SCSubgraphRef Graph_Line5 = sc.Subgraph[4];
	SCInputRef In_InputData1 = sc.Input[0];
	SCInputRef In_InputData2 = sc.Input[1];
	SCInputRef In_InputData3 = sc.Input[2];
	SCInputRef In_InputData4 = sc.Input[3];
	SCInputRef In_InputData5 = sc.Input[4];
	
	SCInputRef In_InputCount = sc.Input[5];
	
	int i, iStart, iStop, iLine, LineCount, iData;
	float Low, High;
	long double Multiplier; //going from small MACD to a large 100 scale chart requires a lot of precision.
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Scale Study to 100 Graph By Zero Line";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Scale Study to 100 Graph By Zero Line. This is a simple translator that will convert an oscillator graph with values above and below 0.0 to a 100 scale graph with 50 being the new middle line (from the previous 0.0 line). This is used to combine multiple studies on one chart and have a fixed middle point instead of several floating middle points that are hard to read.<ul><li>To use this, first add one of the horizontal line studies as the base of the new chart region. I prefer \"Lines 5\" but at a minimum set a single line to 50.0 to be the middle of the range. Go into the Scale option, select User Defined, set Top = 100.0 and Bottom = 0.0.<li>Add your source study to the same chart region as the horizontal line(s) and configure your settings with all of the lines set to hidden. It is recommended to put the source study under the horizontal line study in the \"Studies To Graph\" list for clarity.<li>Add this Scale study to the same chart region. It is recommended to put the Scale study under the source study in the \"Studies To Graph\" list for clarity.<li>Use the drop down box for \"Based On\" and select the source study you just added. The \"Input Data\" lines might come up with the wrong value or go blank in the configuration box. Select each \"Input Data\" line and assign it a new input value from the bottom drop down box. If the source study has multiple output lines, set every one that should be visible. Note: All of the 5 lines must have a value. It doesn't matter which value the unused lines will get.<li>Remember that the first line to be drawn on the chart will be below all the other lines. Line 1 will be below Line 2. Line 2 will be below Line 3. Make sure to account for this in your desired order from the input box.<li>Set \"Number Of Lines To Draw\" to the number of lines you want to see on the chart. If your study only has 1 line, then leave the value at 1. If drawing all 3 lines from MACD, select 3. The remaining lines will be skipped over and not drawn.<li>On the Subgraphs tab, select your line(s) and assign the preferred color and line style. The rest of the lines will automatically be set to Ignore once the Scale study loads.<li>If adding other studies on top of this one that are already 100 scale (like Stochastic or RSI), set any horizontal lines they have to hidden to avoid those lines being drawn on top of previous graph lines.<li>To see the unchanged values of the original study, open the Tools Values Window and put the mouse cursor in Crosshair mode.";
		
		//sc.GraphRegion = 1; //not main price graph, use auto select

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graphs
		
		Graph_Line1.Name = "Line 1"; //drawn graphs must have a name.
		Graph_Line1.PrimaryColor = RGB(0, 255, 255);
		Graph_Line1.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line1.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line1.LineWidth = 1;
		Graph_Line1.DrawZeros = 1;
		
		Graph_Line2.Name = "Line 2"; //drawn graphs must have a name.
		Graph_Line2.PrimaryColor = RGB(0, 255, 0);
		Graph_Line2.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line2.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line2.LineWidth = 1;
		Graph_Line2.DrawZeros = 1;
		
		Graph_Line3.Name = "Line 3"; //drawn graphs must have a name.
		Graph_Line3.PrimaryColor = RGB(255, 255, 0);
		Graph_Line3.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line3.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line3.LineWidth = 1;
		Graph_Line3.DrawZeros = 1;
		
		Graph_Line4.Name = "Line 4"; //drawn graphs must have a name.
		Graph_Line4.PrimaryColor = RGB(255, 128, 0);
		Graph_Line4.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line4.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line4.LineWidth = 1;
		Graph_Line4.DrawZeros = 1;
		
		Graph_Line5.Name = "Line 5"; //drawn graphs must have a name.
		Graph_Line5.PrimaryColor = RGB(255, 0, 0);
		Graph_Line5.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line5.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line5.LineWidth = 1;
		Graph_Line5.DrawZeros = 1;
		
		//User Inputs	
		
		In_InputCount.Name = "Number Of Lines To Draw";
		In_InputCount.SetInt(1);
		In_InputCount.SetIntLimits(1, 5);
		In_InputCount.SetDescription("Number of lines to draw from the Input Data count.");
		
		In_InputData1.Name = "Input Data 1";
		In_InputData1.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData1.SetDescription("The input for line 1 to draw.");
		
		In_InputData2.Name = "Input Data 2";
		In_InputData2.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData2.SetDescription("The input for line 2 to draw.");
		
		In_InputData3.Name = "Input Data 3";
		In_InputData3.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData3.SetDescription("The input for line 3 to draw.");
		
		In_InputData4.Name = "Input Data 4";
		In_InputData4.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData4.SetDescription("The input for line 4 to draw.");
		
		In_InputData5.Name = "Input Data 5";
		In_InputData5.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputData5.SetDescription("The input for line 5 to draw.");
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Setting for decimal places.
		sc.ValueFormat = VALUEFORMAT_INHERITED;
		
		//Redraw needed for scrolling the chart.
		sc.UpdateAlways = 1;
		
		//Set output range.
		sc.ScaleRangeType = SCALE_USERDEFINED;
		sc.ScaleRangeTop = 100.0;
		sc.ScaleRangeBottom = 0.0;
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	LineCount = In_InputCount.GetInt();
	iStart = sc.IndexOfFirstVisibleBar;
	iStop = sc.IndexOfLastVisibleBar;
	
	//if first run...
	if (sc.Index == 0) {
		//turn off unused lines
		for(i=0; i < 5; i++) {
			if(i >= LineCount) {
				sc.Subgraph[i].DrawStyle = DRAWSTYLE_IGNORE;
				sc.Subgraph[i].DisplayNameValueInWindowsFlags = 0;
				}
			}
		}
	
	//find the lowest and highest numbers of all the lines.
	iData = sc.Input[0].GetInputDataIndex();
	Low = sc.BaseDataIn[iData][iStart];
	High = sc.BaseDataIn[iData][iStart];
	for (iLine=0; iLine < LineCount; iLine++) {
		iData = sc.Input[iLine].GetInputDataIndex();
		//find the lowest and highest numbers.
		for(i=iStart; i <= iStop; i++) {
			if(Low > sc.BaseDataIn[iData][i]) {Low = sc.BaseDataIn[iData][i];}
			if(High < sc.BaseDataIn[iData][i]) {High = sc.BaseDataIn[iData][i];}
			}
		}
	//select the largest numbers. need greatest distance away from 0.
	if(Low < 0.0) {Low *= -1.0;} //keep it positive
	if(Low > High) {High = Low;}
	//create the multiplier
	Multiplier = 100.0 / (2.0 * (long double)High);
	
	//loop through active lines and scale them.
	for (iLine=0; iLine < LineCount; iLine++) {
		iData = sc.Input[iLine].GetInputDataIndex();
		//scale the range
		for(i=iStart; i <= iStop; i++) {
			sc.Subgraph[iLine][i] = ((long double)sc.BaseDataIn[iData][i] * Multiplier) + 50.0;
			}
		}
}
