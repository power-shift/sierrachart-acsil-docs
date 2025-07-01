// Larger Timeframe/multiples background H/L bars
//
// By Scottorama October 6, 2008
//
// Updated October 31 to handle Tick and Volume multiples.
//

#include "sierrachart.h"
//SCDLLInit("BackgroundBars");


SCSFExport scsf_BackgroundBars(SCStudyGraphRef sc)
{

    if (sc.SetDefaults)
    {
        // Set the configuration and defaults

        sc.GraphName = "BackgroundBars";

        sc.StudyDescription = "Creates Bars for use behind Prices. For time-based bars, bars are in seconds, for tick or volume bars, they are simply multiples of the current bars. Note: Overlay SAME chart to see current chart's bars on top of these bars. <a href=""http://www.sierrachart.com/supportboard/showthread.php?t=17828"">Discussion subtopic</a>.";

        sc.Subgraph[0].Name = "TimeBarsTop";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_FILLRECTTOP;
		sc.Subgraph[0].PrimaryColor = RGB(0, 50, 0);

        sc.Subgraph[1].Name = "TimeBarsBottom";
        sc.Subgraph[1].DrawStyle = DRAWSTYLE_FILLRECTBOTTOM;
		sc.Subgraph[1].PrimaryColor = RGB(50, 0, 0);

        sc.Subgraph[2].Name = "Open->Close Line";
        sc.Subgraph[2].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[2].PrimaryColor = RGB(150,150, 150);

        sc.Input[0].Name = "Length (seconds / #tick bars / #volume bars)";
        sc.Input[0].SetInt(600);
        sc.Input[0].SetIntLimits(1, INT_MAX);

		// during development set this flag to 1, so the dll can be modified. When development is done set it to 0 to speed up the function calling.
		sc.FreeDLL = 0;
        sc.DrawZeros = 0;  // true
		sc.AutoLoop = 1;  // true
		sc.PersistVars->i1 = 0; // Start at first Index

        return;
    }

    // Do data processing

    // Get inputs
    int InLength = sc.Input[0].GetInt();

    // Get last time and create a bar zone
	int CurrentTime = sc.BaseDateTimeIn.TimeAt(sc.Index);  // Current Time in seconds
	if (sc.AreTimeSpecificBars()) {	
		if ((CurrentTime % InLength) == 0) {
			// New Zone
			sc.PersistVars->i1 = sc.Index;
		}
	}
	
	// Just grab chunks of InLength*BaseInterval duration
	if (sc.AreNumberOfTradesBars() || sc.AreVolumeBars())
	{
		if ((sc.Index % InLength) == 0) {
			// New Zone
			sc.PersistVars->i1 = sc.Index;
		}
	}

	// Calculate H/L of previous bars in the zone
	//GetOHLCOfTimePeriod(sc.BaseDateTimeIn[sc.PersistVars->i1], sc.BaseDateTimeIn[sc.Index], &sc.Subgraph[2][sc.Index], &sc.Subgraph[0][sc.Index], &sc.Subgraph[1][sc.Index], &sc.Subgraph[3][sc.Index], &dontcare);
	float fHigh = 0.0;
	float fLow = 1000000000.0;
	float fOpen = 0.0;
	float fClose = 0.0;
	
	for (int i = sc.PersistVars->i1; i <= sc.Index; i++) {
		if (sc.BaseDataIn[SC_HIGH][i] > fHigh) { fHigh = sc.BaseDataIn[SC_HIGH][i]; }
		if (sc.BaseDataIn[SC_LOW][i] < fLow) { fLow = sc.BaseDataIn[SC_LOW][i]; }
	}
	fOpen = sc.BaseDataIn[SC_OPEN][sc.PersistVars->i1];
	fClose = sc.BaseDataIn[SC_LAST][sc.Index];
	
	for (int i = sc.PersistVars->i1; i <= sc.Index; i++) {
		sc.Subgraph[0][i] = fHigh;
		sc.Subgraph[1][i] = fLow;
		if (fClose > fOpen) {
			sc.Subgraph[0].DataColor[i] = sc.Subgraph[0].PrimaryColor;
			sc.Subgraph[1].DataColor[i] = sc.Subgraph[0].PrimaryColor;
		} else {
			sc.Subgraph[0].DataColor[i] = sc.Subgraph[1].PrimaryColor;
			sc.Subgraph[1].DataColor[i] = sc.Subgraph[1].PrimaryColor;
		}
	}

	if (sc.PersistVars->i1 == sc.Index) {
		sc.Subgraph[2][sc.Index] = fOpen;
		sc.Subgraph[2][sc.Index - 1] = sc.BaseDataIn[SC_LAST][sc.Index - 1];
	}
}