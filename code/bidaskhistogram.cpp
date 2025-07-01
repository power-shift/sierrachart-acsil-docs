
#include "sierrachart.h"


//SCDLLName("Bid Ask Difference Histogram") 


SCSFExport scsf_BidAskDifferenceHistogram(SCStudyGraphRef sc)
{
	// Section 1 - Set the configuration variables

	if (sc.SetDefaults)
	{
		// Set the configuration and defaults
		
		sc.GraphName = "Bid Ask Difference";
		
		sc.StudyDescription = "Bid Ask Difference Colored Histogram by danielyashaev. <a href=""http://www.sierrachart.com/supportboard/attachment.php?attachmentid=3527&d=1251709505"">Discussion subtopic  (Bid Ask Difference Colored Histogram)</a>";
		
		sc.FreeDLL = 0;

		sc.AutoLoop = 1;  // true
		
		sc.Subgraph[0].Name = "BAD Histo";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[0].PrimaryColor = RGB(0,255,0);
		sc.Subgraph[0].SecondaryColor = RGB(255,0,0);
		
		
		
		return;
	}
	
	
	// Section 2 - Do data processing here
	if (sc.BaseDataIn[SC_ASKVOL][sc.Index] > sc.BaseDataIn[SC_BIDVOL][sc.Index])
	{
	sc.Subgraph[0][sc.Index] = (sc.BaseDataIn[SC_ASKVOL][sc.Index] - sc.BaseDataIn[SC_BIDVOL][sc.Index]);
	sc.Subgraph[0].DataColor[sc.Index] = sc.Subgraph[0].PrimaryColor;
	}
	else 
	{
	sc.Subgraph[0][sc.Index] = (sc.BaseDataIn[SC_BIDVOL][sc.Index] - sc.BaseDataIn[SC_ASKVOL][sc.Index]);
	sc.Subgraph[0].DataColor[sc.Index] = sc.Subgraph[0].SecondaryColor;
	}
}
