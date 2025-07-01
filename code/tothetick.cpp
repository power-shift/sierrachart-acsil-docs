#include "sierrachart.h"
#include <string>


/*----------------------------------------------------------------------*/
int RequestData(SCStudyGraphRef sc, SCString Symbol)
{
	SCString UrlFileData;

	int& RequestState = sc.PersistVars->i8;

	if (RequestState == HTTP_REQUEST_NOT_SENT)
	{
		const char* p_Username = NULL;
		
		p_Username =sc.UserName.GetChars();

		if (sc.UserName.CompareNoCase("TransActUser")== 0)
			p_Username =sc.ExternalServiceUsername.GetChars();

#ifdef _DEBUG 
		p_Username = "Joel%20R%20Wyse";
#endif

		UrlFileData.Format("http://www.tothetick.com/checkaccess.php?type=sierra&symbol=%s&id=%s", Symbol.GetChars(), p_Username);


		if (!sc.MakeHTTPRequest(UrlFileData))
		{
			sc.AddMessageToLog( "Error Making HTTP Request.", true);
			RequestState = HTTP_REQUEST_ERROR;
		}
		else
			RequestState = HTTP_REQUEST_MADE;

		return 0;
	}

	if (RequestState == HTTP_REQUEST_MADE && sc.HTTPResponse != "")
	{
		RequestState = HTTP_REQUEST_RECEIVED;
		return 1;
	}
	else if(RequestState == HTTP_REQUEST_MADE && sc.HTTPResponse == "")
	{
		return 0;
	}

	if (RequestState != HTTP_REQUEST_RECEIVED)
		return 0;

	return 1;
}

/*----------------------------------------------------------------------*/

void ClearRequest(SCStudyGraphRef sc)
{
	int& RequestState = sc.PersistVars->i8;
	SCDateTime& RequestDateTime = sc.PersistVars->scdt2;

	RequestState = HTTP_REQUEST_NOT_SENT;
	RequestDateTime = sc.CurrentSystemDateTime;
}

/*----------------------------------------------------------------------*/

void GetItemArrayFromString(const SCString& Line, float* DataArray, int ArraySize)
{
	char FieldsDelimitter = '\t';

	int find_delim = Line.IndexOf(FieldsDelimitter);
	unsigned int pos = 0;

	int CurrentItem = 0;

	while (find_delim > 0 && CurrentItem < ArraySize)
	{
		SCString NextStr = Line.GetSubString(find_delim - pos, pos);

		pos = find_delim + 1;
		find_delim = Line.IndexOf(FieldsDelimitter,find_delim + 1);

		DataArray[CurrentItem] = (float)atof(NextStr);
		CurrentItem++;
	}
}

/*----------------------------------------------------------------------*/

/* http://www.tothetick.com/checkaccess.php?type=sierra&symbol=ES&id=Joel%20R%20Wyse

symbol is either ES, TF, CL or 6E
id is the sierra chart account name
If the account name has an active subscription, it will return levels.  Otherwise return "NA"

Levels returned are the lower end of the zones.  To get the upper end of the rectangle, take lower end plus ticks,  6 for ES, 10 for TF, 15 for CL, 15 for 6E.

*/
SCSFExport scsf_ToTheTickStudy(SCStudyGraphRef sc)
{
	const int ZonesCount = 12;

	SCSubgraphRef AroonOscillator = sc.Subgraph[ZonesCount*2];
	SCSubgraphRef UpArrow = sc.Subgraph[ZonesCount*2+1];
	SCSubgraphRef DownArrow = sc.Subgraph[ZonesCount*2+2];

	SCInputRef ZonesWidth = sc.Input[0];
	SCInputRef UpdateTime = sc.Input[1];
	SCInputRef DaysBack = sc.Input[2];
	SCInputRef WithinZoneTolerance = sc.Input[3];

	if (sc.SetDefaults)
	{
		sc.GraphName = "To the Tick";

		sc.GraphRegion = 0;
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.ValueFormat = VALUEFORMAT_INHERITED;
		sc.AutoLoop = 0; //Not using automatic looping.
		sc.FreeDLL = 0;
		sc.DrawStudyUnderneathMainPriceGraph = true;

		for (int i = 0; i < 2 * ZonesCount; i+=2)
		{
			int CurrentZone = i / 2 + 1;

			SCString SubgraphName;
			SubgraphName.Format("Zone %d Top", CurrentZone);
			sc.Subgraph[i].Name = SubgraphName;
			sc.Subgraph[i].DrawStyle = DRAWSTYLE_FILLRECTTOP;
			sc.Subgraph[i].PrimaryColor = RGB(92, 164, 224); // Light blue
			sc.Subgraph[i].DrawZeros = 0;
			sc.Subgraph[i].DisplayNameValueInWindowsFlags =  SNV_DISPLAY_IN_WINDOWS;

			SubgraphName.Format("Zone %d Bottom", CurrentZone);
			sc.Subgraph[i + 1].Name = SubgraphName;
			sc.Subgraph[i + 1].DrawStyle = DRAWSTYLE_FILLRECTBOTTOM;
			sc.Subgraph[i + 1].PrimaryColor = RGB(92, 164, 224); // Light blue
			sc.Subgraph[i + 1].DrawZeros = 0;
			sc.Subgraph[i + 1].DisplayNameValueInWindowsFlags =  SNV_DISPLAY_IN_WINDOWS;
		}

		UpArrow.Name = "Up Arrow";
		UpArrow.DrawStyle = DRAWSTYLE_ARROWUP;
		UpArrow.PrimaryColor = RGB(0, 255, 0);
		UpArrow.DrawZeros = 0;
		UpArrow.LineWidth = 3;

		DownArrow.Name = "Down Arrow";
		DownArrow.DrawStyle = DRAWSTYLE_ARROWDOWN;
		DownArrow.PrimaryColor = RGB(255, 0, 0);
		DownArrow.DrawZeros = 0;
		DownArrow.LineWidth = 3;

		ZonesWidth.Name = "Zones Width in Ticks";
		ZonesWidth.SetInt(4);
		
		UpdateTime.Name = "Zones Update Time (US Central Time)";
		UpdateTime.SetTime(HMS_TIME(8,5,0));  // 8:05
		
		DaysBack.Name = "Days Back (set 0 to show for all bars in the chart)";
		DaysBack.SetInt(5);

		WithinZoneTolerance.Name = "Within Zone Tolerance in Ticks";
		WithinZoneTolerance.SetInt(3);
		
		return;
	}

	SCString ShortSymbolName = sc.Symbol.GetSubString(2);

	SCDateTime RemoteFileUpdateTime = sc.ConvertToSCTimeZone(COMBINE_DATE_TIME(sc.CurrentSystemDateTime.GetDate(), UpdateTime.GetTime()), TIMEZONE_CHICAGO);
	
	int& RequestState = sc.PersistVars->i8;
	int PriorRequestState = RequestState;
	SCDateTime& RequestDateTime = sc.PersistVars->scdt2;

	//Aroon oscillator processing
	for (int Index = sc.UpdateStartIndex ; Index < sc.ArraySize; Index++)
	{
		sc.AroonIndicator(sc.BaseData[SC_HIGH],sc.BaseData[SC_LOW],AroonOscillator, Index,14);
	}

	//if (sc.UpdateStartIndex == 0 && RequestState == HTTP_REQUEST_MADE)
		//ClearRequest(sc);  // This is to solve a condition when Apply is used from the Chart Studies window, and the initial state of the RequestState is remembered
	//else 
		if (RequestDateTime == 0.0
		|| sc.UpdateStartIndex == 0
		|| (sc.CurrentSystemDateTime.GetTime() > RemoteFileUpdateTime.GetTime() && RequestDateTime.GetDate() != sc.CurrentSystemDateTime.GetDate())
		)
		ClearRequest(sc);

	if (!RequestData(sc, ShortSymbolName))
		return;

	SCString& Response = sc.HTTPResponse;


	bool RequestStateChanged = PriorRequestState != RequestState;

	if (Response.GetSubString(2).Compare("Z1") == 0)	
	{
		if(RequestStateChanged)
			sc.AddMessageToLog("Received valid data.", 0);

	}
	else if (Response.GetSubString(2).Compare("NA") == 0)	
	{
		if(RequestStateChanged)
			sc.AddMessageToLog( "Error: User is not authorized for current symbol or current symbol is not available.",1);

		return;
	}
	else
	{
		if(RequestStateChanged)
			sc.AddMessageToLog("Unknown server error.", 1);

		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// Parsing Data
	//////////////////////////////////////////////////////////////////////////



	char LinesDelimitter = '\n';
	char FieldsDelimitter = '\t';
	SCString NextLine;
	
	int find_delim = Response.IndexOf(LinesDelimitter);
	unsigned int pos = 0;

	int Index = sc.ArraySize - 1;
	SCDateTime LastChartDateTime = sc.BaseDateTimeIn[Index];
	while (find_delim > 0)
	{
		NextLine = Response.GetSubString(find_delim - pos, pos);
		pos = find_delim + 1;
		find_delim = Response.IndexOf(LinesDelimitter,find_delim + 1);

		if (NextLine.GetSubString(2).Compare("Z1") == 0)
			continue; // skip headers line

		NextLine = NextLine.GetSubString(NextLine.GetLength() - 1); // remove '\r' character
		int find_last = NextLine.LastIndexOf(FieldsDelimitter, NextLine.GetLength() - 1);
		if (find_last < 0)
			continue;

		SCString CurrentDateTimeStr = NextLine.GetSubString(NextLine.GetLength() - find_last - 1, find_last + 1);

		SCDateTime CurrentDateTime = sc.DateStringToSCDateTime(CurrentDateTimeStr);

		if (CurrentDateTime == 0.0)
			continue;

		SCDateTime DateTimeOfLastNotUpdatedIndex = sc.BaseDateTimeIn[Index];
		float CurrentZonesData[ZonesCount] = {0.0f};

		// check if we are not too many days back
		if (DaysBack.GetInt() > 0)
		{
			if (CurrentDateTime.GetDate() + DaysBack.GetInt() <= LastChartDateTime.GetDate())
				return;
		}

		GetItemArrayFromString(NextLine, CurrentZonesData, ZonesCount);

		while(true)
		{
			if(Index < 0)
				break;

			UpArrow[Index] = 0;
			DownArrow[Index] = 0;


			SCDateTime IndexDateTime = sc.BaseDateTimeIn[Index];

			if (IndexDateTime.GetDate() != CurrentDateTime.GetDate())
			{
				if(IndexDateTime.GetDate() < CurrentDateTime.GetDate())
					break;

				Index--;
				continue;
			}

			for (int i = 0; i < 2 * ZonesCount; i+=2)
			{
				sc.Subgraph[i][Index] = CurrentZonesData[i / 2] + ZonesWidth.GetInt()*sc.TickSize;
				sc.Subgraph[i + 1][Index] = CurrentZonesData[i / 2];

				float HalfTick = 0.5f * sc.TickSize;

				float UpperZoneValue = sc.Subgraph[i][Index] + (sc.TickSize*WithinZoneTolerance.GetInt()) + HalfTick;
				float LowerZoneValue =  sc.Subgraph[i+1][Index] - (sc.TickSize*WithinZoneTolerance.GetInt()) - HalfTick;


				if (sc.Close[Index] <= UpperZoneValue && sc.Close[Index] >= LowerZoneValue)
				{
					float Oscillator = AroonOscillator[Index] - AroonOscillator.Arrays[0][Index];
					if(Oscillator <= -99.5)
					{
						UpArrow[Index] = sc.Low[Index];
						
					}
					else if(Oscillator >= 99.5)
					{
						DownArrow[Index] = sc.High[Index];

					}
				}
			}



			Index--;
		}
	}


}