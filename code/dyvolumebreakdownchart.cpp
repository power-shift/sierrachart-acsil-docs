// The top of every source code file must include this line
#include "sierrachart.h"



//This is an empty study function.  Auto looping is enabled. 
SCSFExport scsf_DYVolumeBreakdownChart(SCStudyGraphRef sc)
{
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "Volume Breakdown Chart";
		
		sc.FreeDLL = 0;

		sc.AutoLoop = 1;
		sc.GraphDrawType = GDT_CANDLESTICK;
		sc.ValueFormat = 0;
		sc.DrawZeros = 1;
		sc.UpdateAlways = 1;
		
		sc.Subgraph[0].PrimaryColor = RGB(131,131,131);
		sc.Subgraph[0].Name = "Open";
		
		sc.Subgraph[1].PrimaryColor = RGB(0,166,0);
		sc.Subgraph[1].Name = "High";
		
		sc.Subgraph[2].PrimaryColor = RGB(131,131,131);
		sc.Subgraph[2].Name = "Low";
		
		sc.Subgraph[3].PrimaryColor = RGB(255,0,0);
		sc.Subgraph[3].Name = "Close";
		
		return;
	}

		
		sc.Subgraph[5][sc.Index] = (sc.BaseData[SC_ASKVOL][sc.Index] - sc.BaseData[SC_BIDVOL][sc.Index]);
		sc.CumulativeSummation(sc.Subgraph[5], sc.Subgraph[3], sc.Index);

		sc.Subgraph[0][sc.Index] = sc.Subgraph[3][sc.Index-1];
		sc.Subgraph[1][sc.Index] = sc.Subgraph[3][sc.Index-1] + sc.BaseDataIn[SC_ASKVOL][sc.Index];
		sc.Subgraph[2][sc.Index] = sc.Subgraph[3][sc.Index-1] - sc.BaseDataIn[SC_BIDVOL][sc.Index];
		sc.Subgraph[3][sc.Index] = sc.Subgraph[3][sc.Index];
	
}
