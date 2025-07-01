#include "sierrachart.h" 


// This line is required. Change the text within the quote marks to what you want to name 
// your group of custom studies. This function name can also be SCDLLInit instead of SCDLLName. 
// SCDLLName("InitialBalanceLevels") 




SCSFExport scsf_InitialBalanceLevels(SCStudyInterfaceRef sc)
{
	SCSubgraphRef ibhigh = sc.Subgraph[0];
	SCSubgraphRef iblow = sc.Subgraph[1];
	
	SCSubgraphRef ibhigh15 = sc.Subgraph[2];
	SCSubgraphRef iblow15 = sc.Subgraph[3];
	
	SCSubgraphRef ibhigh20 = sc.Subgraph[4];
	SCSubgraphRef iblow20 = sc.Subgraph[5];

	SCSubgraphRef ibhigh30 = sc.Subgraph[6];
	SCSubgraphRef iblow30 = sc.Subgraph[7];
	
	SCInputRef StartTime = sc.Input[0];
	SCInputRef EndTime = sc.Input[1];
	
	SCInputRef Multiplier1 = sc.Input[2];
	SCInputRef Multiplier2 = sc.Input[3];
	SCInputRef Multiplier3 = sc.Input[4];
	
	if (sc.SetDefaults)
	{
		sc.FreeDLL = 0;
		sc.GraphName			= "Initial Balance Levels";
		sc.StudyDescription			= "<a href=""http://www.sierrachart.com/supportboard/showthread.php?p=178043"">Discussion subtopic: Initial Balance Study (with x1.5, x2.0, x3.0)</a>";
		sc.DrawZeros			= 0;
		sc.GraphRegion			= 0;
		sc.AutoLoop				= 1;
		
		ibhigh.Name = "IBH";
		ibhigh.PrimaryColor = RGB(255, 0, 0);
		ibhigh.DrawStyle = DRAWSTYLE_DASH;
		ibhigh.DrawZeros = false;
		
		iblow.Name = "IBL";
		iblow.PrimaryColor = RGB(255, 0, 0);
		iblow.DrawStyle = DRAWSTYLE_DASH;
		iblow.DrawZeros = false;
		
		ibhigh15.Name = "IBHx1.5";
		ibhigh15.PrimaryColor = RGB(255, 255, 128);
		ibhigh15.DrawStyle = DRAWSTYLE_DASH;
		ibhigh15.DrawZeros = false;
		
		iblow15.Name = "IBLx1.5";
		iblow15.PrimaryColor = RGB(255, 255, 128);
		iblow15.DrawStyle = DRAWSTYLE_DASH;
		iblow15.DrawZeros = false;
		
		ibhigh20.Name = "IBHx2.0";
		ibhigh20.PrimaryColor = RGB(128, 255, 128);
		ibhigh20.DrawStyle = DRAWSTYLE_DASH;
		ibhigh20.DrawZeros = false;
		
		iblow20.Name = "IBLx2.0";
		iblow20.PrimaryColor = RGB(128, 255, 128);
		iblow20.DrawStyle = DRAWSTYLE_DASH;
		iblow20.DrawZeros = false;
		
		ibhigh30.Name = "IBHx3.0";
		ibhigh30.PrimaryColor = RGB(255, 128, 128);
		ibhigh30.DrawStyle = DRAWSTYLE_DASH;
		ibhigh30.DrawZeros = false;
		
		iblow30.Name = "IBLx3.0";
		iblow30.PrimaryColor = RGB(255, 128, 128);
		iblow30.DrawStyle = DRAWSTYLE_DASH;
		iblow30.DrawZeros = false;

		StartTime.Name = "Start Time";
		StartTime.SetTime(34200); //9:30

		EndTime.Name = "End Time";
		EndTime.SetTime(37800-1); //10:30 subtract a second

		Multiplier1.Name = "Multiplier1";
		Multiplier1.SetFloat(1.5f);
		
		Multiplier2.Name = "Multiplier2";
		Multiplier2.SetFloat(2.0f);
		
		Multiplier3.Name = "Multiplier3";
		Multiplier3.SetFloat(3.0f);
	
		return;
	}

	SCDateTime InStartTime = StartTime.GetDateTime();
	SCDateTime InEndTime = EndTime.GetDateTime();

	SCDateTime StartDateTime = 0;
	SCDateTime EndDateTime = 0;
	float Open = 0.0f, High = 0.0f, Low = 0.0f, Close = 0.0f, NextOpen = 0.0f;
	float Open1 = 0.0f, High1 = 0.0f, Low1 = 0.0f, Close1 = 0.0f, NextOpen1 = 0.0f;
	int	Index = 0;

	if(sc.Index <= 0)
		return;

	bool ShouldDecreaseEndTime = false;
	if (InStartTime.GetTime() <= InEndTime.GetTime())
	{
		ShouldDecreaseEndTime = (InStartTime.GetTime() > sc.StartTimeOfDay && InEndTime.GetTime() < sc.StartTimeOfDay) 
			||
			(InStartTime.GetTime() < sc.StartTimeOfDay && InEndTime.GetTime() > sc.StartTimeOfDay);
	}
	else
	{
		ShouldDecreaseEndTime= (InStartTime.GetTime() < sc.StartTimeOfDay && InEndTime.GetTime() < sc.StartTimeOfDay)
			||
			(InStartTime.GetTime() > sc.StartTimeOfDay && InEndTime.GetTime() > sc.StartTimeOfDay);
	}

	if (ShouldDecreaseEndTime)
	{
		InEndTime.SetTime(sc.StartTimeOfDay);
		if (InEndTime != 0.0)
			InEndTime -=SECONDS;
		else
			InEndTime.SetTime(SECONDS_PER_DAY - 1);
	}

	SCDateTime CurrentDateTime = sc.BaseDateTimeIn[sc.Index];
	SCDateTime StartDateTimeOfCurIndex = CurrentDateTime.GetDate();
	StartDateTimeOfCurIndex.SetTime(sc.StartTimeOfDay);
	if(sc.StartTimeOfDay > CurrentDateTime.GetTime())
		StartDateTimeOfCurIndex -= DAYS;

	if (sc.Index < sc.ArraySize - 2)
	{
		SCDateTime PrevDateTime = sc.BaseDateTimeIn[sc.Index - 1];
		SCDateTime StartDateTimeOfPrevIndex = PrevDateTime.GetDate();
		StartDateTimeOfPrevIndex.SetTime(sc.StartTimeOfDay);
		if(sc.StartTimeOfDay > PrevDateTime.GetTime())
			StartDateTimeOfPrevIndex -= DAYS;

		if (StartDateTimeOfPrevIndex == StartDateTimeOfCurIndex)
			return;

		Index = sc.Index - 1;
		StartDateTimeOfCurIndex = StartDateTimeOfPrevIndex;
		CurrentDateTime = PrevDateTime;
	}
	else
	{
		Index = sc.Index;
	}

	StartDateTime = EndDateTime = StartDateTimeOfCurIndex.GetDate();
	StartDateTime.SetTime(InStartTime.GetTime());
	EndDateTime.SetTime(InEndTime.GetTime());

	if (InStartTime.GetTime() > InEndTime.GetTime())
		EndDateTime += DAYS;

	if(InStartTime.GetTime() < StartDateTimeOfCurIndex.GetTime())
	{
		StartDateTime += DAYS;
		EndDateTime += DAYS;
	}

	sc.GetOHLCOfTimePeriod(StartDateTime, EndDateTime, Open, High, Low, Close, NextOpen);

	// set/reset all values for current day
	float m1 = Multiplier1.GetFloat();
	float m2 = Multiplier2.GetFloat();
	float m3 = Multiplier3.GetFloat();
	float tick = sc.TickSize;
	while(true)
	{
		if(Index < 0)
			break;

		SCDateTime IndexDateTime = sc.BaseDateTimeIn[Index];

		if(IndexDateTime < StartDateTimeOfCurIndex)
			break;

		bool ShouldDisplay = false;

		if (InStartTime.GetTime() < InEndTime.GetTime())
		{
			ShouldDisplay = (IndexDateTime.GetTime() <= InEndTime.GetTime() 
				&& IndexDateTime.GetTime() >= InStartTime.GetTime());
		}
		else
		{
			ShouldDisplay = (IndexDateTime.GetTime() <= InEndTime.GetTime() 
				|| IndexDateTime.GetTime() >= InStartTime.GetTime());
		}

		if (IndexDateTime > EndDateTime)
			ShouldDisplay = true;

		if(ShouldDisplay)
		{
			ibhigh[Index] = High;
			iblow[Index] = Low;
			
			ibhigh15[Index] = sc.RoundToTickSize((m1-1)*(High-Low)+High,tick);
			iblow15[Index] = sc.RoundToTickSize(-(m1-1)*(High-Low)+Low,tick);
			
			ibhigh20[Index] = sc.RoundToTickSize((m2-1)*(High-Low)+High,tick);
			iblow20[Index] = sc.RoundToTickSize(-(m2-1)*(High-Low)+Low,tick);
			
			ibhigh30[Index] = sc.RoundToTickSize((m3-1)*(High-Low)+High,tick);
			iblow30[Index] = sc.RoundToTickSize(-(m3-1)*(High-Low)+Low,tick);
		}
		else
		{
			ibhigh[Index] = 0.0f;
			iblow[Index] = 0.0f;
			
			ibhigh15[Index] = 0.0f;
			iblow15[Index] = 0.0f;
			
			ibhigh20[Index] = 0.0f;
			iblow20[Index] = 0.0f;
			
			ibhigh30[Index] = 0.0f;
			iblow30[Index] = 0.0f;
		}

		Index--;
	}
}