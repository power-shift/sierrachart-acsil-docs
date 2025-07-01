//Bricks (3 Line Break)
//
//Author: Jsyd
//Date: 01/11/2009
// 
//

#include "sierrachart.h"
//SCDLLInit("Bricks");



SCSFExport scsf_Bricks(SCStudyGraphRef sc)
{
	SCSubgraphRef upBarSubgraph = sc.Subgraph[0];
	SCSubgraphRef dnBarSubgraph = sc.Subgraph[1];
	SCSubgraphRef trendSubgraph = sc.Subgraph[2];
	
	// Inputs
	SCInputRef breakBarsInput = sc.Input[0];
	
    if ( sc.SetDefaults)
    {
        // Set the configuration and defaults

         sc.GraphName = "Bricks";

         sc.StudyDescription = "Displays Brick (Three Line Break) bars behind primary price bars. BricksTrend is the 3LB in trend form with entry signals. The bars change trend color when the trend changes AND crosses beyond x number (1 - 5) of ranges formed by the 3LB. Updated on (01-02-2011). <a href=""http://www.sierrachart.com/supportboard/showthread.php?t=17828"">Discussion subtopic (three line break)</a>";

         upBarSubgraph.Name = "UpBar";
         upBarSubgraph.DrawStyle = DRAWSTYLE_FILLRECTTOP;
		 upBarSubgraph.PrimaryColor = RGB(179, 255, 179);

         dnBarSubgraph.Name = "DownBar";
         dnBarSubgraph.DrawStyle = DRAWSTYLE_FILLRECTBOTTOM;
		 dnBarSubgraph.PrimaryColor = RGB(255, 179, 179);

         trendSubgraph.Name = "Trend";
         trendSubgraph.DrawStyle = DRAWSTYLE_IGNORE;

         breakBarsInput.Name = "Number of bars to break";
         breakBarsInput.SetInt(3);
         breakBarsInput.SetIntLimits(1, 1000);

		// during development set this flag to 1, so the dll can be modified. When development is done set it to 0 to speed up the function calling.
		 sc.FreeDLL = 0;
         sc.DrawZeros = 0;  // true
		 sc.AutoLoop = 1;  // true
		 sc.GraphRegion = 0;
        return;
    }
//	Init Vars

	int& start = sc.PersistVars->i1;
	int& Trend =  sc.PersistVars->i2;
	
	float& fHigh =  sc.PersistVars->f1;
	float& fLow =  sc.PersistVars->f2;
	
    int bInt =  breakBarsInput.GetInt();
	int cur =  sc.Index;
	int c = 0;
	
	float last =  sc.BaseDataIn[SC_LAST][cur];
	
	if(sc.GetBarHasClosedStatus() == BHCS_BAR_HAS_CLOSED)
	{
//	UpTrend setting a new range - just draw a new range bar
		if((last > fHigh) && (Trend > 0))
		{
				Trend = 1;
			//	Set new hgh and low to draw trend range area
				fLow = fHigh;
				fHigh = last;	
			//	Save new range begin index	
				start = cur;
		}
	//	Possible trend reversal - DownTrend -> UpTrend
		if((last > fHigh) && (Trend < 1))
		{
		//	Iterate thru number of bars to compare as specifed by user
			for (int x=cur-bInt;x<=cur;x++) 
			{
			//	Make sure we are higher that all bars, both up and down
				if((last > sc.BaseDataIn[SC_OPEN][x]) && (last > sc.BaseDataIn[SC_LAST][x]))
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
			//	Save new range begin index
				 sc.PersistVars->i1 = cur;
			}
		}
	//	DownTrend setting a new range - just draw a new range bar
		if((last < fLow) && (Trend < 1))
		{
				Trend = 0;
			//	Set new hgh and low to draw trend range area
				fHigh = fLow;
				fLow = last;
			//	Save new range begin index		
				 start = cur;
		}
	//	Possible trend reversal - UpTrend -> DownTrend
		if((last < fLow) && (Trend > 0))
		{
		//	Iterate thru number of bars to compare as specifed by user
			for (int x = cur - bInt; x <= cur; x++) 
			{		
			//	Make sure we are lower that all bars, both up and down
				if((last < sc.BaseDataIn[SC_OPEN][x]) && (last < sc.BaseDataIn[SC_LAST][x]))
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
			//	Save new range begin index		
				 start = cur;
			}
		}
	//	Draw new range rectangle	
		for (int i=start;i<=cur;i++) {
	//		 upBarSubgraph[i] = fHigh;
	//		 dnBarSubgraph[i] = fLow;
			if (Trend == 1) {
				 upBarSubgraph.DataColor[i] =  upBarSubgraph.PrimaryColor;
				 dnBarSubgraph.DataColor[i] =  upBarSubgraph.PrimaryColor;
				 trendSubgraph[i] = 1;
			} else if (Trend == 0) {
				 upBarSubgraph.DataColor[i] =  dnBarSubgraph.PrimaryColor;
				 dnBarSubgraph.DataColor[i] =  dnBarSubgraph.PrimaryColor;
				 trendSubgraph[i] = 0;
			}
		}
		upBarSubgraph[cur]= fHigh;
		dnBarSubgraph[cur]= fLow;
	}
}