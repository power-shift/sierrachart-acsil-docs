// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Lines 5") 

//Custom study starts here.
SCSFExport scsf_Lines5(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_Line1 = sc.Subgraph[0];
	SCSubgraphRef Graph_Line2 = sc.Subgraph[1];
	SCSubgraphRef Graph_Line3 = sc.Subgraph[2];
	SCSubgraphRef Graph_Line4 = sc.Subgraph[3];
	SCSubgraphRef Graph_Line5 = sc.Subgraph[4];
	SCInputRef In_Line1Level = sc.Input[0];
	SCInputRef In_Line2Level = sc.Input[1];
	SCInputRef In_Line3Level = sc.Input[2];
	SCInputRef In_Line4Level = sc.Input[3];
	SCInputRef In_Line5Level = sc.Input[4];

	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Lines 5";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Lines 5. Draws 5 horizontal lines across a subgraph. This is mainly useful when multiple indicators will be on one subgraph. This will create a fixed scale and a place holder for the subgraph. This also allows for graphs stacked on top of each other to be seen easier if those graphs have lines which could then be turned off to avoid overlapping. Be sure to change the graph scale of any indicators added on top.";
		
		//sc.GraphRegion = 1; //not main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graphs
		
		Graph_Line1.Name = "Line 1"; //drawn graphs must have a name.
		Graph_Line1.PrimaryColor = RGB(128, 128, 128);
		Graph_Line1.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line1.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line1.LineWidth = 1;
		Graph_Line1.DrawZeros = 1;
		Graph_Line1.DisplayNameValueInWindowsFlags = 0;
		
		Graph_Line2.Name = "Line 2"; //drawn graphs must have a name.
		Graph_Line2.PrimaryColor = RGB(128, 128, 128);
		Graph_Line2.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line2.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line2.LineWidth = 1;
		Graph_Line2.DrawZeros = 1;
		Graph_Line2.DisplayNameValueInWindowsFlags = 0;
		
		Graph_Line3.Name = "Line 3"; //drawn graphs must have a name.
		Graph_Line3.PrimaryColor = RGB(192, 192, 192);
		Graph_Line3.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line3.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line3.LineWidth = 1;
		Graph_Line3.DrawZeros = 1;
		Graph_Line3.DisplayNameValueInWindowsFlags = 0;
		
		Graph_Line4.Name = "Line 4"; //drawn graphs must have a name.
		Graph_Line4.PrimaryColor = RGB(128, 128, 128);
		Graph_Line4.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line4.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line4.LineWidth = 1;
		Graph_Line4.DrawZeros = 1;
		Graph_Line4.DisplayNameValueInWindowsFlags = 0;
		
		Graph_Line5.Name = "Line 5"; //drawn graphs must have a name.
		Graph_Line5.PrimaryColor = RGB(128, 128, 128);
		Graph_Line5.DrawStyle = DRAWSTYLE_LINE;
		Graph_Line5.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_Line5.LineWidth = 1;
		Graph_Line5.DrawZeros = 1;
		Graph_Line5.DisplayNameValueInWindowsFlags = 0;
		
		//User Inputs
		
		In_Line1Level.Name = "Line 1 Level";
		In_Line1Level.SetFloat(100);
		In_Line1Level.SetDescription("The value number of the line.");
		
		In_Line2Level.Name = "Line 2 Level";
		In_Line2Level.SetFloat(70);
		In_Line2Level.SetDescription("The value number of the line.");
		
		In_Line3Level.Name = "Line 3 Level";
		In_Line3Level.SetFloat(50);
		In_Line3Level.SetDescription("The value number of the line.");
		
		In_Line4Level.Name = "Line 4 Level";
		In_Line4Level.SetFloat(30);
		In_Line4Level.SetDescription("The value number of the line.");
		
		In_Line5Level.Name = "Line 5 Level";
		In_Line5Level.SetFloat(0);
		In_Line5Level.SetDescription("The value number of the line.");
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Setting for decimal places.
		sc.ValueFormat = VALUEFORMAT_INHERITED;
		
		return;
		}
	
	// Section 2 - Do data processing here
	
	Graph_Line1[sc.Index] = In_Line1Level.GetFloat();
	Graph_Line2[sc.Index] = In_Line2Level.GetFloat();
	Graph_Line3[sc.Index] = In_Line3Level.GetFloat();
	Graph_Line4[sc.Index] = In_Line4Level.GetFloat();
	Graph_Line5[sc.Index] = In_Line5Level.GetFloat();
}
