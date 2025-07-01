// The top of every source code file must include this line
#include "sierrachart.h"


//This is the basic framework of a study function.
SCSFExport scsf_EngulfingBar_Vline(SCStudyGraphRef sc)
{
	SCSubgraphRef V_line = sc.Subgraph[0];
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "EngulfingBar_Vline";

		sc.FreeDLL = 0;

		sc.AutoLoop = 1;  //Auto looping is enabled. 

		V_line.Name = "Vertical Line";
		V_line.DrawStyle = DRAWSTYLE_LINE;
		V_line.LineWidth = 1;
		V_line.PrimaryColor = RGB (0, 255, 0);		

		return;
	}	

	// Section 2 - Do data processing here

	int& Index = sc.PersistVars->i1;
	int& LineNumber = sc.PersistVars->i2;	// Index for finding New Bar.	
	s_UseTool Vline;

	if(Index != sc.Index)
	{
		if(sc.Low[sc.Index-1] < sc.Low[sc.Index-2] && sc.High[sc.Index -1] > sc.High[sc.Index-2])
		{
			Vline.Clear();
			Vline.ChartNumber = sc.ChartNumber;
			Vline.Region = 0;
			Vline.DrawingType = DRAWING_VERTICALLINE;
			Vline.LineNumber = 10000 + LineNumber;
			Vline.AddMethod = UTAM_ADD_OR_ADJUST;
			Vline.Color= V_line.PrimaryColor;
			Vline.LineWidth= V_line.LineWidth;	
			Vline.LineStyle = V_line.LineStyle;		            
			Vline.UseRelativeVerticalValues=0;
			Vline.BeginIndex = sc.Index-1; 		               
			sc.UseTool(Vline);
			LineNumber++;		 
		}	  
	}	
	Index = sc.Index;
}
