// Swing High/Lows
//
// By Scottorama March 29, 2009

#include "sierrachart.h"
#include "sccolors.h"

//SCDLLInit("MySwings");

// Description: Swing High/Low 


SCSFExport scsf_MySwings(SCStudyGraphRef sc)
{

    if (sc.SetDefaults)
    {
        // Set the configuration and defaults

        sc.GraphName = "My Swing High/Lows";

        sc.StudyDescription = "Creates Swing High/Low indications by Scottorama. <a href=""http://www.sierrachart.com/supportboard/showthread.php?t=20755"">Discussion subtopic (Swing High/Low Code)</a>";

        sc.Subgraph[0].Name = "Swing Highs";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_ARROWDOWN;
		sc.Subgraph[0].PrimaryColor = RGB(255, 0, 0);
		sc.Subgraph[0].LineWidth = 2;

        sc.Subgraph[1].Name = "Swing Lows";
        sc.Subgraph[1].DrawStyle = DRAWSTYLE_ARROWUP;
		sc.Subgraph[1].PrimaryColor = RGB(0, 255, 0);
		sc.Subgraph[1].LineWidth = 2;

        sc.Input[0].Name = "High/Lows Before";
        sc.Input[0].SetInt(2);
        sc.Input[0].SetIntLimits(1, INT_MAX);

        sc.Input[1].Name = "High/Lows After";
        sc.Input[1].SetInt(2);
        sc.Input[1].SetIntLimits(1, INT_MAX);

        sc.Input[2].Name = "Offset from bars (ticks)";
        sc.Input[2].SetInt(1);
        sc.Input[2].SetIntLimits(0, INT_MAX);

        sc.Input[3].Name = "Allow adjacent equal bars";
        sc.Input[3].SetYesNo(0);

		// during development set this flag to 1, so the dll can be modified. When development is done set it to 0 to speed up the function calling.
		sc.FreeDLL = 0;
        sc.DrawZeros = 0;
		sc.AutoLoop = 1;  // true

		// Default to Main Graph
		sc.GraphRegion = 0;

        return;
    }

    // Do data processing

    // Get inputs
    int Before = sc.Input[0].GetInt();
    int After = sc.Input[1].GetInt();
	int iOffset = sc.Input[2].GetInt();
	int iYesNo = sc.Input[3].GetYesNo();
	
	// Check starting at current bar - Before Bars - After Bars
	// So, Current - 2 - 2 is used for 2 before and 2 after the bar in question
	int iStartBar = sc.Index - Before - After - 1;
	int iTheBar = sc.Index - After - 1;
	int iLastBar = sc.Index - 1;
	
	bool bSwingHigh = true;
	bool bSwingLow = true;
	
	bool bSwingHighDip = false;
	bool bSwingLowDip = false;
	
	// Make sure we have enough bars!
	if (iStartBar < 0) return;

	// Check Before
	for (int i = iTheBar-1; i >= iStartBar; i--) {
		// Check for High or Low Swing
		if (iYesNo) {
			if (sc.BaseDataIn[SC_HIGH][i] > sc.BaseDataIn[SC_HIGH][iTheBar]) bSwingHigh = false;
			if (sc.BaseDataIn[SC_LOW][i] < sc.BaseDataIn[SC_LOW][iTheBar]) bSwingLow = false;
			
			if (bSwingHigh && sc.BaseDataIn[SC_HIGH][i] < sc.BaseDataIn[SC_HIGH][iTheBar] && !bSwingHighDip) bSwingHighDip = true;
			if (bSwingHigh && sc.BaseDataIn[SC_HIGH][i] == sc.BaseDataIn[SC_HIGH][iTheBar] && bSwingHighDip) bSwingHigh = false;
			
			if (bSwingLow && sc.BaseDataIn[SC_LOW][i] > sc.BaseDataIn[SC_LOW][iTheBar] && !bSwingLowDip) bSwingLowDip = true;
			if (bSwingLow && sc.BaseDataIn[SC_LOW][i] == sc.BaseDataIn[SC_LOW][iTheBar] && bSwingLowDip) bSwingLow = false;
			
		} else {
			if (sc.BaseDataIn[SC_HIGH][i] >= sc.BaseDataIn[SC_HIGH][iTheBar]) bSwingHigh = false;
			if (sc.BaseDataIn[SC_LOW][i] <= sc.BaseDataIn[SC_LOW][iTheBar]) bSwingLow = false;
		}
	}
	
	bSwingHighDip = false;
	bSwingLowDip = false;
	
	// Check After
	for (int i = (iTheBar + 1); i <= iLastBar; i++) {
		// Check for High or Low Swing
		if (iYesNo) {
			if (sc.BaseDataIn[SC_HIGH][i] > sc.BaseDataIn[SC_HIGH][iTheBar]) bSwingHigh = false;
			if (sc.BaseDataIn[SC_LOW][i] < sc.BaseDataIn[SC_LOW][iTheBar]) bSwingLow = false;

			if (bSwingHigh && sc.BaseDataIn[SC_HIGH][i] < sc.BaseDataIn[SC_HIGH][iTheBar] && !bSwingHighDip) bSwingHighDip = true;
			if (bSwingHigh && sc.BaseDataIn[SC_HIGH][i] == sc.BaseDataIn[SC_HIGH][iTheBar] && bSwingHighDip) bSwingHigh = false;

			if (bSwingLow && sc.BaseDataIn[SC_LOW][i] > sc.BaseDataIn[SC_LOW][iTheBar] && !bSwingLowDip) bSwingLowDip = true;
			if (bSwingLow && sc.BaseDataIn[SC_LOW][i] == sc.BaseDataIn[SC_LOW][iTheBar] && bSwingLowDip) bSwingLow = false;
			
		} else {
			if (sc.BaseDataIn[SC_HIGH][i] >= sc.BaseDataIn[SC_HIGH][iTheBar]) bSwingHigh = false;
			if (sc.BaseDataIn[SC_LOW][i] <= sc.BaseDataIn[SC_LOW][iTheBar]) bSwingLow = false;
		}
	}
	
	if (bSwingHigh) {
		sc.Subgraph[0][iTheBar] = sc.BaseDataIn[SC_HIGH][iTheBar] + iOffset*sc.TickSize;
		sc.Subgraph[0].DataColor[iTheBar] = sc.Subgraph[0].PrimaryColor;
	}

	if (bSwingLow) {
		sc.Subgraph[1][iTheBar] = sc.BaseDataIn[SC_LOW][iTheBar] - iOffset*sc.TickSize;
		sc.Subgraph[1].DataColor[iTheBar] = sc.Subgraph[1].PrimaryColor;
	}

}