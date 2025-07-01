#include "sierrachart.h"

//SCDLLInit("VEMAMACD")



SCSFExport scsf_VEMAMACD(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "VEMA-MACD";
		sc.StudyDescription = "Volume Weighted EMA MACD Histogram by jaklspackal <a href=""http://www.sierrachart.com/supportboard/showthread.php?p=137161#post137161"">Discussion subtopic (New Indicator - Volume Weighted EMA MACD)</a>";
		sc.FreeDLL = 0;

		sc.AutoLoop = 1;  // true

		//sc.GraphRegion = 0;

		// Set the name of the first subgraph
		sc.Subgraph[0].Name = "Short VWEMA:sub1";
		sc.Subgraph[1].Name = "Short VWEMA:sub2";
		sc.Subgraph[2].Name = "Short VWEMA";
		sc.Subgraph[3].Name = "Long VWEMA:sub1";
		sc.Subgraph[4].Name = "Long VWEMA:sub2";
		sc.Subgraph[5].Name = "Long VWEMA";
		sc.Subgraph[6].Name = "VEMA-MACD";
		sc.Subgraph[7].Name = "VEMA-MACD Signal";
		sc.Subgraph[8].Name = "VEMA-MACD Hist";
		sc.Subgraph[9].Name = "Volume x Last";
		//sc.Subgraph[0].PrimaryColor = RGB(0,255,0);
		//sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE ;
		//sc.Subgraph[0].LineWidth = 2 ;		
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[2].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[3].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[4].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[5].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[6].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[7].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[8].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[9].DrawStyle = DRAWSTYLE_IGNORE;
		
		sc.Input[0].Name = "1-Short Period";		
		sc.Input[0].SetFloat(12);             // default value
		sc.Input[1].Name = "2-Long Period";		
		sc.Input[1].SetFloat(26);             // default value
		sc.Input[2].Name = "1-Smoothing Period";		
		sc.Input[2].SetFloat(9);             // default value
		
		return;
	}

	// Do data processing
	sc.Subgraph[9][sc.Index] = sc.BaseDataIn[SC_VOLUME][sc.Index] * sc.BaseDataIn[SC_LAST][sc.Index];
	
	// calculate short VWEMA:sub1
	sc.ExponentialMovAvg(sc.Subgraph[9], sc.Subgraph[0], sc.Index, sc.Input[0].GetInt());
	// calculate short VWEMA:sub2
	sc.ExponentialMovAvg(sc.BaseDataIn[SC_VOLUME], sc.Subgraph[1], sc.Index, sc.Input[0].GetInt());
	// calculate short VWEMA
	sc.Subgraph[2][sc.Index] = sc.Subgraph[0][sc.Index] / sc.Subgraph[1][sc.Index];
	
	// calculate long VWEMA:sub1
	sc.ExponentialMovAvg(sc.Subgraph[9], sc.Subgraph[3], sc.Index, sc.Input[1].GetInt());
	// calculate long VWEMA:sub2
	sc.ExponentialMovAvg(sc.BaseDataIn[SC_VOLUME], sc.Subgraph[4], sc.Index, sc.Input[1].GetInt());
	// calculate long VWEMA
	sc.Subgraph[5][sc.Index] = sc.Subgraph[3][sc.Index] / sc.Subgraph[4][sc.Index];
	
	//VMACD
	sc.Subgraph[6][sc.Index] = sc.Subgraph[2][sc.Index] - sc.Subgraph[5][sc.Index];
	
	//VWMACD Signal Line
	sc.ExponentialMovAvg(sc.Subgraph[6], sc.Subgraph[7], sc.Index, sc.Input[2].GetInt());
	
	//VWMACD Histogram
	sc.Subgraph[8][sc.Index] = sc.Subgraph[6][sc.Index] - sc.Subgraph[7][sc.Index];

}	
