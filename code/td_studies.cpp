#include "sierrachart.h"
//SCDLLName("Tom DeMark Studies")

SCSFExport scsf_TDMovingAverages (SCStudyGraphRef sc)
{
	SCSubgraphRef HiAvg  = sc.Subgraph[0];
	SCSubgraphRef LoAvg  = sc.Subgraph[1];

	int& HiDays = sc.PersistVars->i1;
	int& LoDays = sc.PersistVars->i2;

	if (sc.SetDefaults)
	{
		sc.GraphName = "TD Moving Averages";
		sc.GraphRegion = 0;
		sc.DrawZeros = 0;
		sc.FreeDLL =0;
		sc.AutoLoop = 1;
		HiAvg.Name = "Upper Moving Average";
		HiAvg.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		HiAvg.LineWidth = 2;
		HiAvg.PrimaryColor = RGB(192,0,0);
		LoAvg.Name = "Lower Moving Average";
		LoAvg.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		LoAvg.LineWidth = 2;		
		LoAvg.PrimaryColor = RGB(0,128,0);
		return;
	}

	if (sc.Index < 12) return;

	if(sc.High[sc.Index] < sc.GetLowest(sc.High, sc.Index - 1, 12))
	{
		HiDays = 4;
		LoDays = 0;
	}
	else HiDays--;
	if(sc.Low[sc.Index] > sc.GetHighest(sc.Low, sc.Index - 1, 12))
	{
		LoDays = 4;
		HiDays = 0;
	}
	else LoDays--;

	if(HiDays > 0) sc.MovingAverage(sc.High, HiAvg, MOVAVGTYPE_SIMPLE, sc.Index, 5);
		else HiAvg[sc.Index] = 0;
	if(LoDays > 0) sc.MovingAverage(sc.Low, LoAvg, MOVAVGTYPE_SIMPLE, sc.Index, 5);
		else LoAvg[sc.Index] = 0;

	if(HiDays > 0 && sc.Close[sc.Index - 1] > HiAvg[sc.Index - 1] && sc.Open[sc.Index] > HiAvg[sc.Index]) HiDays = 0;
	if(LoDays > 0 && sc.Close[sc.Index - 1] < LoAvg[sc.Index - 1] && sc.Open[sc.Index] < LoAvg[sc.Index]) LoDays = 0;
}
