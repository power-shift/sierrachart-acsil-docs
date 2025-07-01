/*****************************************************
* Display daily targets on an intraday chart using   *
* ATR values from a daily chart. The daily chart #   *
* must be entered as an input and the daily chart    *
* must have the ATR study loaded as the 1st study.   *
* 					                                 *
* By Sock 2010  									 *
* windysock@gmail.com                                *
*****************************************************/
#include "sierrachart.h"
#define SOK_DEBUG 0    // SET TO 0 WHEN READY FOR PRODUCTION
//SCDLLName("DailyTargets") 

SCSFExport scsf_DailyTargets(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "Daily Targets";
		sc.GraphRegion = 0;
		sc.FreeDLL = SOK_DEBUG;
		sc.AutoLoop = 0;  
		sc.ValueFormat = 4;
		sc.CalculationPrecedence = LOW_PREC_LEVEL;
		sc.Subgraph[0].Name = "High Target";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[0].PrimaryColor = COLOR_TURQUOISE;
		sc.Subgraph[1].Name = "Low Target";
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[1].PrimaryColor = COLOR_PINK;
		sc.Subgraph[2].Name = "Text box colours";
		sc.Subgraph[2].LineWidth = 10;
		sc.Subgraph[2].PrimaryColor = COLOR_BLACK;
		sc.Subgraph[2].SecondaryColor = COLOR_YELLOW;
		sc.Subgraph[2].SecondaryColorUsed = true;
		sc.Subgraph[3].Name = "ATR";
		sc.Subgraph[3].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[4].Name = "Day High";
		sc.Subgraph[4].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[4].PrimaryColor = COLOR_BLUE;
		sc.Subgraph[5].Name = "Day Low";
		sc.Subgraph[5].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[5].PrimaryColor = COLOR_RED;
		sc.Subgraph[6].Name = "Session divider colour";
		sc.Subgraph[6].LineStyle = LINESTYLE_DOT;
		sc.Subgraph[6].LineWidth = 1;
		sc.Subgraph[6].PrimaryColor = COLOR_YELLOW;
		sc.Input[0].Name = "Daily chart # for ATR values";
		sc.Input[0].SetInt(1);
		sc.Input[1].Name = "Session start time";
		sc.Input[1].SetTime(HMS_TIME(22,0,0));
		sc.Input[2].Name = "Pip size";
		sc.Input[2].SetFloat(0.0001);
		return;
	}
	int i;
	int ChartNum = sc.Input[0].GetInt();
	int	StartTime = sc.Input[1].GetTime();
	float PipSize = sc.Input[2].GetFloat();
	int BarDate, BarTime, BarDoW;
	float Open, High, Low, Close, NextOpen;
	float ATR = 0.0f;
	SCFloatArray ATRArray;
	SCDateTime SessionStart, ATRDateTime;
	s_UseTool TextBox;
	s_UseTool VertLine;
	
	sc.GetStudyArrayFromChart(ChartNum, 1, 1, ATRArray);

	for (i = sc.UpdateStartIndex; i < sc.ArraySize; i++) 
	{
		BarDate = sc.BaseDateTimeIn[i].GetDate();
		BarTime = sc.BaseDateTimeIn[i].GetTime();
		BarDoW = sc.BaseDateTimeIn[i].GetDayOfWeek();
		if (BarDoW == MONDAY && BarTime < StartTime) {
			SessionStart.SetDateTime(BarDate-2, StartTime);
		}
		else if (BarDoW == SUNDAY || BarTime < StartTime) {
			SessionStart.SetDateTime(BarDate-1, StartTime);
		}
		else {
			SessionStart.SetDateTime(BarDate, StartTime);
		}
		if ((BarTime >= StartTime && StartTime != 0) || BarDoW == SUNDAY) {
			ATRDateTime.SetDateTime(BarDate+1, 0);
		}
		else {
			ATRDateTime.SetDateTime(BarDate, 0);
		}
		if (ATRDateTime.GetDayOfWeek() == MONDAY) { 
			ATRDateTime -= 3*DAYS;
		}
		else if (ATRDateTime.GetDayOfWeek() == SUNDAY) {
			ATRDateTime -= 2*DAYS;
		}
		else {
			ATRDateTime -= 1*DAYS;
		}
			
		ATR = ATRArray[sc.GetNearestMatchForSCDateTime(ChartNum, ATRDateTime)];
		sc.Subgraph[3][i] = ATR;
		sc.GetOHLCOfTimePeriod(SessionStart, sc.BaseDateTimeIn[i], Open, High, Low, Close, NextOpen);
		sc.Subgraph[4][i] = High;
		sc.Subgraph[5][i] = Low;
		sc.Subgraph[0][i] = Low+ATR;
		sc.Subgraph[1][i] = High-ATR;
		TextBox.Clear();
		TextBox.ChartNumber = sc.ChartNumber;
		TextBox.DrawingType = DRAWING_TEXT;
		TextBox.LineNumber = sc.ChartNumber+99;
		TextBox.BeginDateTime = sc.BaseDateTimeIn[sc.IndexOfFirstVisibleBar];
		TextBox.UseRelativeVerticalValues = true;
		TextBox.BeginValue = 8;
		TextBox.Region = sc.GraphRegion;
		TextBox.Color = sc.Subgraph[2].PrimaryColor;
		TextBox.FontBackColor = sc.Subgraph[2].SecondaryColor;
		TextBox.FontBold = true;
		TextBox.FontSize = sc.Subgraph[2].LineWidth;
		TextBox.ReverseTextColor = false;
		TextBox.Text.Format("%d, %d, %.f%%\n%d, %d,", 
							int(ATR/PipSize), int((High-Low)/PipSize), ((High-Low)/ATR)*100.0,
							int((sc.Subgraph[0][i]-sc.BaseDataIn[SC_LAST][i])/PipSize),
							int((sc.BaseDataIn[SC_LAST][i]-sc.Subgraph[1][i])/PipSize));
		TextBox.AddMethod = UTAM_ADD_OR_ADJUST;
		sc.UseTool(TextBox);
		
		if ((BarTime == StartTime && BarDoW != SUNDAY) || (BarDoW == SUNDAY && sc.BaseDateTimeIn[i-1].GetDayOfWeek() == FRIDAY)) {
			VertLine.Clear();
			VertLine.ChartNumber = sc.ChartNumber;
			VertLine.DrawingType = DRAWING_VERTICALLINE;
			VertLine.LineNumber = BarDate;
			VertLine.BeginDateTime = sc.BaseDateTimeIn[i];
			VertLine.Region = sc.GraphRegion;
			VertLine.Color = sc.Subgraph[6].PrimaryColor;
			VertLine.LineWidth = sc.Subgraph[6].LineWidth;
			VertLine.LineStyle = sc.Subgraph[6].LineStyle;
			VertLine.AddMethod = UTAM_ADD_OR_ADJUST;
			sc.UseTool(VertLine);
		}
	}
}
