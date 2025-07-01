/*
Better TRIN indcator from e-minwatch.com by Scottorama 11/12/08
*/


#include "sierrachart.h"

//SCDLLInit("BetterTRIN") 

SCSFExport scsf_BetterTRIN(SCStudyGraphRef sc)
{


	if (sc.SetDefaults)
	{


		sc.GraphName = "Better $TRIN indicator";

		sc.StudyDescription = "Better $TRIN indicator from e-miniwatch.com. Description: TRIN oscillator by Scottorama <a href=""http://www.sierrachart.com/supportboard/showthread.php?t=18428"">Discussion subtopic (Help with TRIN oscillator code)</a>";


		sc.FreeDLL = 0;


		sc.CalculationPrecedence = LOW_PREC_LEVEL;

		sc.Subgraph[0].Name = "Better $TRIN";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[1].PrimaryColor = RGB(0,255,0);

		sc.AutoLoop = 1;  // true

		return;
	}


	// Fill in data...

	sc.Subgraph[0][sc.Index] = (log(sc.BaseDataIn[SC_LAST][sc.Index])*-1.0)*100.0;

	//Done!
}
