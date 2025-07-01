#include "sierrachart.h"

float TkAccH[10000]={0};
float TkAccC[10000]={0};
float TkAccL[10000]={0};
float TkAccO[10000]={0};

SCSFExport scsf_CumulativeDeltaBars(SCStudyGraphRef sc)
{

	SCSubgraphRef Open = sc.Subgraph[0];
	SCSubgraphRef High = sc.Subgraph[1];
	SCSubgraphRef Low = sc.Subgraph[2];
	SCSubgraphRef Close = sc.Subgraph[3];

	//SCInputRef ResetAtSessionStart = sc.Input[2];
	SCInputRef ChartOverlayNumber = sc.Input[3];
	
	if (sc.SetDefaults)
	{
		sc.GraphName = "Cumulative NYSE $ticks Bars";

		sc.DrawZeros = 1;
		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		
		sc.UseGlobalChartColors = 0;
		sc.ValueFormat = 2;
		sc.GraphRegion = 0;
		sc.DrawZeros = 0;
		sc.ScaleRangeType = SCALE_INDEPENDENT;

		sc.GraphDrawType = GDT_CANDLESTICK;
		Open.Name = "Open";
		Open.PrimaryColor = RGB(0,255,0);
		High.Name = "High";
		High.PrimaryColor = RGB(0,128,0);
		Low.Name  = "Low";
		Low.PrimaryColor = RGB(255,0,0);
		Close.Name = "Close";
		Close.PrimaryColor = RGB(128,0,0);

		//ResetAtSessionStart.Name = "Reset at Start of Trading Day";
		//ResetAtSessionStart.SetYesNo(0);
		
		ChartOverlayNumber.Name = "Chart Number To Overlay";
		ChartOverlayNumber.SetChartNumber(1);

		return;
	}
	
	SCGraphData ChartOverlayArrays;
	sc.GetChartBaseData(-ChartOverlayNumber.GetChartNumber(), ChartOverlayArrays);
	
	if (ChartOverlayArrays[SC_OPEN].GetArraySize() == 0)
		return;
	
	for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		int i1 = sc.GetNearestMatchForDateTimeIndex(ChartOverlayNumber.GetChartNumber(), i);
		
		if (i==1) {
			TkAccH[i] = ChartOverlayArrays[1][i1]; //sc.High[i];
			TkAccC[i] = ChartOverlayArrays[3][i1]; //sc.Close[i];
			TkAccL[i] = ChartOverlayArrays[2][i1]; //sc.Low[i];
			TkAccO[i] = ChartOverlayArrays[0][i1]; //sc.Open[i];
		} else {
		
			int Time = sc.BaseDateTimeIn.TimeAt(i);
			int Hour, Minute, Second;
			TIME_TO_HMS(Time, Hour, Minute, Second);
			if( (Hour == 9 && Minute >= 30) || (Hour > 9 && Hour < 16) ){
				TkAccH[i] = TkAccH[i-1] + ChartOverlayArrays[1][i1]; //sc.High[i];
				TkAccC[i] = TkAccC[i-1] + ChartOverlayArrays[3][i1]; //sc.Close[i];
				TkAccL[i] = TkAccL[i-1] + ChartOverlayArrays[2][i1]; //sc.Low[i];
				TkAccO[i] = TkAccO[i-1] + ChartOverlayArrays[0][i1]; //sc.Open[i];
				
				Open[i]  = TkAccC[i-1] ;
				High[i]  = TkAccC[i-1]+(TkAccH[i]-TkAccH[i-1]);
				Low[i]   = TkAccC[i-1]+(TkAccL[i]-TkAccL[i-1]);
				Close[i] = TkAccC[i];
				if (Open[i] > High[i]) 
					Open[i] = High[i];
				if (Open[i] < Low[i])
					Open[i] = Low[i];	
			} else {
				TkAccH[i] = TkAccH[i-1];
				TkAccC[i] = TkAccC[i-1];
				TkAccL[i] = TkAccL[i-1];
				TkAccO[i] = TkAccO[i-1];
				Open[i]  = Close[i-1];
				High[i]  = Close[i-1];
				Low[i]   = Close[i-1];
				Close[i] = Close[i-1];
			}
		}
		
		//for (int SubgraphIndex = 0; SubgraphIndex < ChartOverlayArrays.GetArraySize(); SubgraphIndex++)
		//	sc.Subgraph[SubgraphIndex][DataIndex] = ChartOverlayArrays[SubgraphIndex][i1] * Multiplier.GetFloat();
		
		//sc.CalculateOHLCAverages(i);
	}
	
	//SCString ChartOverlayName = sc.GetStudyNameFromChart(ChartOverlayNumber.GetChartNumber(), 0);
	//sc.GraphName.Format("%s Overlay", ChartOverlayName.GetChars());
}