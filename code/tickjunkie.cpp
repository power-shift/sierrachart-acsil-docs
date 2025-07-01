#include "sierrachart.h"

//SCDLLName("TickJunkie") 
 

////////////////////////////////////////////////////////////////////
SCSFExport scsf_RockwellTrend(SCStudyGraphRef sc)
{
	const int MACD_INPUT_DATA_TYPE = 0;
	const int MACD_FAST = 3;
	const int MACD_SLOW = 4;
	const int MACD_MA = 5;
	const int MACD_MA_TYPE = 6;
	
    if (sc.SetDefaults)
    {
        sc.GraphName = "Rockwell Trend Paintbar";
        sc.StudyDescription = "Three Candle Colors Based on MACD & MACD Diff by tickjunkie <a href=""http://www.sierrachart.com/supportboard/showthread.php?t=18921"">Discussion subtopic: Three Candle Colors Based on MACD & MACD Diff)</a>";
        sc.GraphRegion = 0;
        
        sc.Subgraph[0].Name = "Uptrend";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_COLORBAR;
        sc.Subgraph[0].PrimaryColor = RGB(0,196,0);  
        
		sc.Subgraph[1].Name = "Downtrend";
        sc.Subgraph[1].DrawStyle = DRAWSTYLE_COLORBAR;
        sc.Subgraph[1].PrimaryColor = RGB(206,0,0);  
		
		sc.Subgraph[2].Name = "Chop";
        sc.Subgraph[2].DrawStyle = DRAWSTYLE_COLORBAR;
        sc.Subgraph[2].PrimaryColor = RGB(0,0,0);  
 
 
 		sc.Input[0].Name = "MACD Input Data";
		sc.Input[0].SetInputDataIndex(SC_LAST);  

		sc.Input[MACD_FAST].Name ="Fast Moving Average Length";
		sc.Input[MACD_FAST].SetInt(12);  
		sc.Input[MACD_FAST].SetIntLimits(1, 10000);

		sc.Input[MACD_SLOW].Name = "Slow Moving Average Length";
		sc.Input[MACD_SLOW].SetInt(26);  
		sc.Input[MACD_SLOW].SetIntLimits(1,1000);

		sc.Input[MACD_MA].Name = "MACD Moving Average Length(Trigger)";
		sc.Input[MACD_MA].SetInt(9);   
		sc.Input[MACD_MA].SetIntLimits(1,1000);

		sc.Input[MACD_MA_TYPE].Name = "Moving Average Type";
		sc.Input[MACD_MA_TYPE].SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		
		
		sc.AutoLoop = 1;
        sc.FreeDLL = 0;
				
        return;
    }
		
	SCFloatArrayRef baseData = sc.BaseDataIn[(int)sc.Input[MACD_INPUT_DATA_TYPE].GetInputDataIndex()];

	sc.MACD(baseData, sc.Subgraph[3], sc.Index, sc.Input[MACD_FAST].GetInt(), sc.Input[MACD_SLOW].GetInt(), sc.Input[MACD_MA].GetInt(), sc.Input[MACD_MA_TYPE].GetInt());
	//sc.MACD(sc.BaseData[SC_LAST], sc.Subgraph[3], sc.Index, 12, 26, 9, MOVAVGTYPE_EXPONENTIAL);
	
	//Access the individual values
	float MACD = sc.Subgraph[3][sc.Index];
	float MACDMA = sc.Subgraph[3].Arrays[2][sc.Index];
	float MACDDiff = sc.Subgraph[3].Arrays[3][sc.Index];
	
	sc.Subgraph[0][sc.Index] = 0;
	sc.Subgraph[1][sc.Index] = 0;
	sc.Subgraph[2][sc.Index] = 0;
	
	if ((MACD > 0.0f) && (MACDDiff > 0.0f)){
		sc.Subgraph[0][sc.Index] = 1;
		sc.Subgraph[0].DataColor[sc.Index] = sc.Subgraph[0].PrimaryColor;
	}
	else if ((MACD < 0.0f) && (MACDDiff < 0.0f)){
		sc.Subgraph[1][sc.Index] = 1;
		sc.Subgraph[1].DataColor[sc.Index] = sc.Subgraph[1].PrimaryColor;
	}
	else{
		sc.Subgraph[2][sc.Index] = 1;
		sc.Subgraph[2].DataColor[sc.Index] = sc.Subgraph[2].PrimaryColor;	
	}

	
}