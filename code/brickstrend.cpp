//BricksTrend (3 Line Break Trend) 
//
//Author: Jsyd
//Date: 01/17/2009
// 
//

#include "sierrachart.h"
//SCDLLInit("BricksTrend");


SCSFExport scsf_BricksTrend(SCStudyGraphRef sc)
{

    if (sc.SetDefaults)
    {
        // Set the configuration and defaults

        sc.GraphName = "BricksTrend";

        sc.StudyDescription = "Displays Brick (Three Line Break) Trend. BricksTrend is the 3LB in trend form with entry signals. The bars change trend color when the trend changes AND crosses beyond x number (1 - 5) of ranges formed by the 3LB. Updated on (01-02-2011). <a href=""http://www.sierrachart.com/supportboard/showthread.php?t=17828"">Discussion subtopic (three line break)</a>";

        sc.Subgraph[0].Name = "UpBar";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[0].PrimaryColor = RGB(0, 255, 0);

        sc.Subgraph[1].Name = "DownBar";
        sc.Subgraph[1].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[1].PrimaryColor = RGB(255, 0, 0);

        sc.Subgraph[2].Name = "Trend";
        sc.Subgraph[2].DrawStyle = DRAWSTYLE_IGNORE;

        sc.Input[0].Name = "Number of bars to break";
        sc.Input[0].SetInt(3);
        sc.Input[0].SetIntLimits(1, 10);

        sc.Input[1].Name = "Number of ranges to break (entry signal)";
        sc.Input[1].SetInt(3);
        sc.Input[1].SetIntLimits(1, 5);

		// during development set this flag to 1, so the dll can be modified. When development is done set it to 0 to speed up the function calling.
		sc.FreeDLL = 0;
        sc.DrawZeros = 0;  // true
		sc.AutoLoop = 1;  // true
		sc.GraphRegion = 0;
        return;
    }
//	Init Vars
	int rInt = sc.Input[1].GetInt();
//	float highArr [rInt];
//	float lowArr [rInt];
	float& fHigh = sc.PersistVars->f1;
	float& fLow = sc.PersistVars->f2;
	float& rLow0 = sc.PersistVars->f3;
	float& rLow1 = sc.PersistVars->f4;
	float& rLow2 = sc.PersistVars->f5;
	float& rLow3 = sc.PersistVars->f6;
	float& rLow4 = sc.PersistVars->f7;
	float& rHigh0 = sc.PersistVars->f8;
	float& rHigh1 = sc.PersistVars->f9;
	float& rHigh2 = sc.PersistVars->f10;
	float& rHigh3 = sc.PersistVars->f11;
	float& rHigh4 = sc.PersistVars->f12;
	int& rTrend = sc.PersistVars->i1;
	int& Trend = sc.PersistVars->i2;
    int bInt = sc.Input[0].GetInt();
	int cur = sc.Index;
	int c = 0;
	int lastTrend = rTrend;
	float last = sc.BaseDataIn[SC_LAST][cur];

	if(sc.GetBarHasClosedStatus() == BHCS_BAR_HAS_CLOSED)
	{
	//	UpTrend setting a new range - just draw a new range bar
		if((last > fHigh) && (Trend > 0))
		{
				Trend = 1;
			//	Set new hgh and low to draw trend range area
				fLow = fHigh;
				fHigh = last;
			//	Update our range values
				rHigh4 = rHigh3;
				rHigh3 = rHigh2;
				rHigh2 = rHigh1;
				rHigh1 = rHigh0;
				rHigh0 = fLow;
			//	Save new range begin index	
				sc.PersistVars->i1 = cur;
		}
	//	Possible trend reversal - DownTrend -> UpTrend
		if((last > fHigh) && (Trend < 1))
		{
		//	Iterate thru number of bars to compare as specifed by user
			for (int x = cur - bInt; x < cur; x++) 
			{
			//	Make sure we are higher that all bars, both up and down
				if((last >  sc.BaseDataIn[SC_OPEN][x]) && (last >  sc.BaseDataIn[SC_LAST][x]))
				{
					c++;
				}
			}
		//	if price is higher than all previous bars in range reverse Trend  	
			if(c >= bInt)
			{
				Trend = 1;
			//	Set new hgh and low to draw trend range area	
				fLow = fHigh;
				fHigh = last;
			//	Update our range values
				rLow4 = rLow3;
				rHigh3 = rLow2;
				rLow2 = rLow1;
				rLow1 = rLow0;
				rLow0 = fHigh;
			}
		}
	//	DownTrend setting a new range - just draw a new range bar
		if((last < fLow) && (Trend < 1))
		{
				Trend = 0;
			//	Set new hgh and low to draw trend range area
				fHigh = fLow;
				fLow = last;
			//	Update our range values
				rLow4 = rLow3;
				rHigh3 = rLow2;
				rLow2 = rLow1;
				rLow1 = rLow0;
				rLow0 = fHigh;
		}
	//	Possible trend reversal - UpTrend -> DownTrend
		if((last < fLow) && (Trend > 0))
		{
		//	Iterate thru number of bars to compare as specifed by user
			for (int x = cur - bInt; x < cur; x++) 
			{		
			//	Make sure we are lower that all bars, both up and down
				if((last <  sc.BaseDataIn[SC_OPEN][x]) && (last <  sc.BaseDataIn[SC_LAST][x]))
				{
					c++;
				}
			}
		//	if price is lower than all previous bars in range reverse Trend 
			if(c >= bInt)
			{
				Trend = 0;
			//	Set new hgh and low to draw trend range area	
				fHigh = fLow;
				fLow = last;
			//	Update our range values
				rLow4 = rLow3;
				rHigh3 = rLow2;
				rLow2 = rLow1;
				rLow1 = rLow0;
				rLow0 = fHigh;
			}
		}
	//	Color the bar
		float highArr [] = {rLow0,rLow1,rLow2,rLow3,rLow4}; 
		float lowArr [] = {rHigh0,rHigh1,rHigh2,rHigh3,rHigh4};
		int NoChg = 0;
		for (int r=0; r < rInt ; r++ )
		{
			if(Trend == 1)
			{
				if(fHigh < highArr[r]) {
					NoChg = 1;
					break;
				}	
			} 
			else if(Trend == 0)
			{
				if(fLow > lowArr[r]) {
					NoChg = 1;
					break;
				}	
			}
		}
		if(NoChg == 0) {
			rTrend = Trend;
		} else {
			rTrend = lastTrend;
		}
	}
	if (rTrend == 1) {
		sc.Subgraph[0].DataColor[cur] = sc.Subgraph[0].PrimaryColor;
		sc.Subgraph[2][cur] = 1;
	} else if (rTrend == 0) {
		sc.Subgraph[0].DataColor[cur] = sc.Subgraph[1].PrimaryColor;
		sc.Subgraph[2][cur] = 0;
	}
	sc.Subgraph[0][cur]=sc.BaseDataIn[SC_LAST][cur];
}