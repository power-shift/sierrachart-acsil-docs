// The top of every source code file must include this line
#include "sierrachart.h"




//This is an empty study function.  Auto looping is enabled. 
SCSFExport scsf_DYVolumeBreakdown(SCStudyGraphRef sc)
{
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "DY Volume Breakdown";
		


		sc.FreeDLL = 0;

		sc.GraphName = "Volume Breakdown";
		sc.StudyDescription = "AVol Summation - BVol Summation";
		sc.GraphRegion = 1;
		sc.ValueFormat = 2;
		
		sc.Subgraph[0].Name = "Vol B";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[0].LineWidth = 4; 
		sc.Subgraph[0].PrimaryColor = RGB(0,166,0);
		sc.Subgraph[0].SecondaryColor = RGB(183,0,0);
		sc.Subgraph[0].SecondaryColorUsed = 1;	
		
		sc.Input[0].Name = "Period";
		sc.Input[0].SetInt(14);
		
		sc.AutoLoop = 1;
		
		return;
	}
	
	int period = sc.Input[0].GetInt();
	
	sc.Subgraph[1][sc.Index] = (sc.BaseData[SC_ASKVOL][sc.Index] - sc.BaseData[SC_BIDVOL][sc.Index]);

	sc.TriangularMovingAverage(sc.Subgraph[1], sc.Subgraph[0], period);
	
	if (sc.Subgraph[0][sc.Index] > 0) {sc.Subgraph[0].DataColor[sc.Index] = sc.Subgraph[0].PrimaryColor;}
	else {sc.Subgraph[0].DataColor[sc.Index] = sc.Subgraph[0].SecondaryColor;}


}
