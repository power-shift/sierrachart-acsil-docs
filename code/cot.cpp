#include "sierrachart.h"
#include "scstudyfunctions.h"
SCDLLName("COT report study") 
/*
V1 PUBLISHED 2019/02/10
V2 CHANGES   2019/02/11
	- added new instruments to list, getting codes from the list using first 6 chars



*/

/*============================================================================*/
int TradingLevelsStudy_RequestValuesFromServer
(SCStudyInterfaceRef sc
	, const SCString& BaseWebsiteURL
	, int& r_RequestState
);
/*============================================================================*/
void TradingLevelsStudy_ResetStateForNextRequest
(SCStudyInterfaceRef sc
	, int& r_RequestState
	, SCDateTime& r_RequestDateTime
	, std::vector<SCString>* p_ValuesLineForDates
	, std::vector<std::vector<char*>>* p_PointersToValuesForDates
);

/*============================================================================*/
SCSFExport scsf_TradingLevelsStudy(SCStudyInterfaceRef sc)
{


	SCInputRef InstOp = sc.Input[0];
	SCInputRef Instrument = sc.Input[1];
	SCInputRef InstMeasure = sc.Input[2];
	SCInputRef StartDate = sc.Input[3];
	SCInputRef QuandlAPIKey = sc.Input[4];
	SCInputRef Logging = sc.Input[8];



	if (sc.SetDefaults)
	{
		sc.GraphName = "COT report study";

		sc.GraphRegion = 1;
		sc.ScaleRangeType = SCALE_AUTO;
		sc.ValueFormat = 1;
		sc.AutoLoop = 0;
		sc.FreeDLL = 0;//1 testing , 0 published
		sc.StudyDescription = " COT report study. This study will access COT data from the Quandle.com database and display it in subgraphs. In order to access the Quandle database a Quandle APIKey is needed which is available from your Quandle Account Settings. Quandle basic subscription is free and its restricted to 50 queries per day. There are two ways of choosing an COT Instrument code: 1. Select an instrument from the dropdown list, these are the most commonly used futures instruments. 2. Enter an instrument code manually. The above drop down list must be set to \"Select instrument\". Next select the Intrument Measure code. A start date can also be input or else the maximum lookback period will be downloaded for the chosen instrument. IMPORTANT! AFTER A  SELECTION IS MADE PRESS THE \"Apply\" BUTTON TWICE. In case you dont see any data, select Detailed Logging to Yes and look in the Message Log for the potential cause.";



		InstOp.Name = "Instrument preset code list, after selecting press APPLY twice";
		InstOp.SetCustomInputStrings("Select instrument;13874A - S&P;124603 - Dow;209742 - Nasdaq;239742 - Russell;1170E1 - S&P VIX;067651 - Oil;111659 - RBOB;022651 - HO;023651 - Nat Gas;025601 - Ethanol;088691 - Gold;084691 - Silver;085692 - Copper;075651 - Paladium;076651 - Platinum;002602 - Corn;001602 - Wheat;005602 - Soybeans;026603 - Soybean Meal;007601 - Soybean Oil;073732 - Cocoa;083731 - Coffee;040701 - OJ;080732 - Sugar;058643 - Lumber;033661 - Cotton;057642 - Live Cattle;061641 - Feeder Cattle;054642 - Lean Hogs;232741 - Australian Dollar;096742 - British Pound;090741 - Canadian Dollar;098662 - Dollar Index;099741 - Euro;097741 - Japanese Yen;095741 - Mexican Peso;112741 - New Zealand Dollar;102741 - Brazilian Real;089741 - Russian Ruble;044601 - T-Notes;020601 - T-Bonds; ");
		InstOp.SetCustomInputIndex(0);
		InstOp.SetDescription(" A selection of the most common futures instruments. This is provided for easy of use.  If you wish to see other COT reports please enter Instrument code bellow. Instrument codes can be found on the Qunadle website");

		Instrument.Name = "Instrument manual code entry, above list must be set to Select instrument ";
		Instrument.SetString("");
		Instrument.SetDescription("Instrument code - manual entry. This is a 6 digit numerical code or in some cases the 6th digit is a letter");

		InstMeasure.Name = "Instrument Measure";
		InstMeasure.SetCustomInputStrings("_F_ALL;_F_ALL_NT;_F_ALL_OI;_F_CHG;_FO_ALL;_FO_ALL_NT;_FO_ALL_OI;_FO_CHG");
		InstMeasure.SetCustomInputIndex(0);
		InstMeasure.SetDescription("Instrument measure refers to the type of COT report. Detail can be found on the Quandle website.");

		QuandlAPIKey.Name = "Quandle APIKey";
		QuandlAPIKey.SetString("");
		QuandlAPIKey.SetDescription("Eneter your Quandle APIKey here available from your Quandle account page");

		StartDate.Name = ("Start date yyyy-mm-dd . Leave Blank for maximum lookback COT data");
		StartDate.SetString("");
		StartDate.SetDescription("start date");

		Logging.Name = "Detailed Logging to message log";
		Logging.SetYesNo(0);


		//create subgraphs
		for (int Index = 0; Index < SC_SUBGRAPHS_AVAILABLE; Index++)
		{
			SCString SubgraphName;
			SubgraphName.Format("Level %d", Index + 1);
			sc.Subgraph[Index].Name = SubgraphName;
			sc.Subgraph[Index].DrawStyle = DRAWSTYLE_HIDDEN;
			sc.Subgraph[Index].LineWidth = 2;
			sc.Subgraph[Index].PrimaryColor = RGB(0, 0, 0);
			sc.Subgraph[Index].DrawZeros = 0;  // false
			sc.Subgraph[Index].LineLabel = 0;
			sc.Subgraph[Index].DisplayNameValueInWindowsFlags = 0;

		}

		sc.Subgraph[0].Name = "Producers";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_STAIR_STEP;
		sc.Subgraph[0].PrimaryColor = RGB(255, 0, 0); //red
		sc.Subgraph[0].LineLabel = LL_DISPLAY_VALUE | LL_VALUE_ALIGN_CENTER | LL_VALUE_ALIGN_VALUES_SCALE;
		sc.Subgraph[0].DisplayNameValueInWindowsFlags = SNV_DISPLAY_IN_DATA_LINE;

		sc.Subgraph[1].Name = "Swap Dealers";
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_STAIR_STEP;
		sc.Subgraph[1].PrimaryColor = RGB(0, 128, 0);  //green
		sc.Subgraph[1].LineLabel = LL_DISPLAY_VALUE | LL_VALUE_ALIGN_CENTER | LL_VALUE_ALIGN_VALUES_SCALE;
		sc.Subgraph[1].DisplayNameValueInWindowsFlags = SNV_DISPLAY_IN_DATA_LINE;

		sc.Subgraph[2].Name = "Managed Money";
		sc.Subgraph[2].DrawStyle = DRAWSTYLE_STAIR_STEP;
		sc.Subgraph[2].PrimaryColor = RGB(0, 0, 255); //blue
		sc.Subgraph[2].LineLabel = LL_DISPLAY_VALUE | LL_VALUE_ALIGN_CENTER | LL_VALUE_ALIGN_VALUES_SCALE;
		sc.Subgraph[2].DisplayNameValueInWindowsFlags = SNV_DISPLAY_IN_DATA_LINE;

		sc.Subgraph[3].Name = "Other";
		sc.Subgraph[3].DrawStyle = DRAWSTYLE_STAIR_STEP;
		sc.Subgraph[3].PrimaryColor = RGB(200, 200, 0);  //yellow
		sc.Subgraph[3].LineLabel = LL_DISPLAY_VALUE | LL_VALUE_ALIGN_CENTER | LL_VALUE_ALIGN_VALUES_SCALE;
		sc.Subgraph[3].DisplayNameValueInWindowsFlags = SNV_DISPLAY_IN_DATA_LINE;

		return;
	}

	/*
	if(sc.IsUserAllowedForSCDLLName == false)
	{
		if(sc.UpdateStartIndex == 0)
		{
			sc.AddMessageToLog("You are not allowed to use this study",1);
		}
		return;
	}
	*/
	//==================Input menu programming
	SCString RequestURL = "";
	//SCString RequestURL_last =  "g";
	SCString APIKey = QuandlAPIKey.GetString();
	SCString Inst = Instrument.GetString();
	SCString SDate = StartDate.GetString();
	SCString Buffer; //used for alertmessages

	int& r_RequestState = sc.GetPersistentInt(1);
	int& r_ClearAtMidnight = sc.GetPersistentInt(2);
	int& r_AwaitingNextRequestForLevels = sc.GetPersistentInt(3);
	SCDateTime& r_RequestDateTime = sc.GetPersistentSCDateTime(2);
	int& AllowRequestLevelsFromServer = sc.GetPersistentInt(4);
	int& FullRecalculate = sc.GetPersistentInt(5);
	int& ReportType = sc.GetPersistentInt(6);
	SCDateTime CurrentDateTimeInRequestTimeZone;
	SCString& RequestURL_last = sc.GetPersistentSCString(1);
	SCString InstrumentCode = "";
	SCString InstrumentMeasure = "";

	if (InstMeasure.GetIndex() == 0)  InstrumentMeasure = "_F_ALL";
	if (InstMeasure.GetIndex() == 1)  InstrumentMeasure = "_F_ALL_NT";
	if (InstMeasure.GetIndex() == 2)  InstrumentMeasure = "_F_ALL_OI";
	if (InstMeasure.GetIndex() == 3)  InstrumentMeasure = "_F_CHG";
	if (InstMeasure.GetIndex() == 4)  InstrumentMeasure = "_FO_ALL";
	if (InstMeasure.GetIndex() == 5)  InstrumentMeasure = "_FO_ALL_NT";
	if (InstMeasure.GetIndex() == 6)  InstrumentMeasure = "_FO_ALL_OI";
	if (InstMeasure.GetIndex() == 7)  InstrumentMeasure = "_FO_CHG";
	/////////// URL ////////////////	

	if (APIKey != "")
	{

		if (InstOp.GetIndex() != 0)//SELECTION MADE
		{ //GetSubString(5, 0)
			RequestURL.Format("https://www.quandl.com/api/v3/datasets/CFTC/%s%s.csv?api_key=%s&start_date=%s", InstOp.GetSelectedCustomString().GetSubString(6, 0).GetChars(), InstrumentMeasure.GetChars(), APIKey.GetChars(), SDate.GetChars());
			sc.GraphName.Format("COT - %s", InstOp.GetSelectedCustomString().GetSubString(20, 9).GetChars());
			if (!Inst.IsEmpty()) sc.AddMessageToLog("######## If using manual code then the preset list must be set to \"Select Instrument\"", 1);
		}
		else if (InstOp.GetIndex() == 0) //NO SELECTION MADE
		{
			if (!Inst.IsEmpty())
			{
				RequestURL.Format("https://www.quandl.com/api/v3/datasets/CFTC/%s%s.csv?api_key=%s&start_date=%s", Inst.GetChars(), InstrumentMeasure.GetChars(), APIKey.GetChars(), SDate.GetChars());
				sc.GraphName.Format("COT - %s", Inst.GetChars());
				if (Logging.GetYesNo()) sc.AddMessageToLog("######## Quandl URL based on Instrument code and date if provided", 1);
			}
			else if (Inst.IsEmpty())
			{
				sc.AddMessageToLog("######## Select instrument from list or input intrument code manualy", 1);
			}
		}
	}
	else if (APIKey.IsEmpty())
	{
		sc.AddMessageToLog("######## Quandle APIKey needed", 1);
	}




	if (RequestURL != "")
	{
		Buffer.Format("######## Current  URL is %s", RequestURL.GetChars()); if (Logging.GetYesNo()) sc.AddMessageToLog(Buffer, 1);
		Buffer.Format("######## Previous URL is %s", RequestURL_last.GetChars()); if (Logging.GetYesNo()) sc.AddMessageToLog(Buffer, 1);

		if (!RequestURL_last.CompareNoCase(RequestURL))
		{
			if (Logging.GetYesNo()) sc.AddMessageToLog("######## URL not changed since last request.", 1);
			AllowRequestLevelsFromServer = false;
		}
		if (RequestURL_last.CompareNoCase(RequestURL))
		{
			if (Logging.GetYesNo()) sc.AddMessageToLog("######## URL has changed, initializing HTTP request.", 1);
			AllowRequestLevelsFromServer = true;
		}
	}



	//set vectors to persistent pointer
	std::vector<SCString>* p_ValuesLineForDates = (std::vector<SCString>*)sc.GetPersistentPointer(1);
	std::vector<std::vector<char*>>* p_PointersToValuesForDates = (std::vector<std::vector<char*>>*)sc.GetPersistentPointer(2);



	/*============================================================================*/


	if (sc.LastCallToFunction)                     // remove study = clear persistent pointers

	{
		if (p_ValuesLineForDates != NULL)
		{
			delete p_ValuesLineForDates;
			sc.SetPersistentPointer(1, NULL); //persistent 1 is dates
		}

		if (p_PointersToValuesForDates != NULL)
		{
			delete p_PointersToValuesForDates;
			sc.SetPersistentPointer(2, NULL); // persitent 2 is data for the dates 
		}

		return;
	}

	if (p_ValuesLineForDates == NULL)  							// if dates vector is empty then create new vector
	{
		p_ValuesLineForDates = new std::vector <SCString>;

		if (p_ValuesLineForDates != NULL)
			sc.SetPersistentPointer(1, p_ValuesLineForDates);	// if have dates then remember them!?
		else


			return;

	}

	if (p_PointersToValuesForDates == NULL)						// same as above for dates but this time for the values under dates
	{
		p_PointersToValuesForDates = new std::vector <std::vector < char*> >;

		if (p_PointersToValuesForDates != NULL)
			sc.SetPersistentPointer(2, p_PointersToValuesForDates);
		else


			return;

	}

	if (sc.IsFullRecalculation)
		FullRecalculate = true;



	// IF HTTPREQUEST NEEDED DO IT 
	if (AllowRequestLevelsFromServer || r_RequestState == HTTP_REQUEST_MADE)
	{
		RequestURL_last = RequestURL;
		//Request data on a full recalculation and also at the specified interval

		// This is to solve a condition when Apply is used from the Chart Studies window, and the initial state of the RequestState is remembered
		if (sc.UpdateStartIndex == 0 && r_RequestState == HTTP_REQUEST_MADE)
			TradingLevelsStudy_ResetStateForNextRequest(sc, r_RequestState, r_RequestDateTime, p_ValuesLineForDates, p_PointersToValuesForDates);

		else if (sc.UpdateStartIndex == 0 && r_RequestState == HTTP_REQUEST_RECEIVED)
			TradingLevelsStudy_ResetStateForNextRequest(sc, r_RequestState, r_RequestDateTime, p_ValuesLineForDates, p_PointersToValuesForDates);

		else if (r_RequestDateTime.IsUnset())// Request interval has elapsed
			TradingLevelsStudy_ResetStateForNextRequest(sc, r_RequestState, r_RequestDateTime, p_ValuesLineForDates, p_PointersToValuesForDates);

		if (TradingLevelsStudy_RequestValuesFromServer(sc, RequestURL, r_RequestState))
		{
			if (r_RequestState == HTTP_REQUEST_MADE)
				r_AwaitingNextRequestForLevels = false;
			if (Logging.GetYesNo()) sc.AddMessageToLog("######## HTTP REQUEST MADE, waiting for response.", true);
			return;//Return here since we need to wait for the response
		}
	}

	// CHECK IF HTTPREQUEST IS ERROR
	if (sc.HTTPRequestID != 0)
	{
		//sc.AddMessageToLog(sc.HTTPResponse, 1);
		std::string Bufferas = sc.HTTPResponse.GetChars();
		std::replace(Bufferas.begin(), Bufferas.end(), ';', '-'); // replace all 'x' to 'y'
		//sc.AddMessageToLog(Bufferas.c_str(), 1);
		sc.HTTPResponse = Bufferas.c_str();
		//sc.AddMessageToLog(sc.HTTPResponse, 1);

		r_RequestState = HTTP_REQUEST_RECEIVED;

		if (sc.HTTPResponse == ACSIL_HTTP_REQUEST_ERROR_TEXT
			|| sc.HTTPResponse == ACSIL_HTTP_EMPTY_RESPONSE_TEXT)
		{
			sc.AddMessageToLog("######## There was an error requesting data from the server.", true);
			return;
		}

		if (sc.UpdateStartIndex == 0 && sc.HTTPResponse == "NO_DATA")
			sc.AddMessageToLog("######## There is no data for the given parameters.", false);

		if (strstr(sc.HTTPResponse.GetChars(), "CLEAR_AT_MIDNIGHT") != NULL)
		{
			sc.AddMessageToLog("######## Received clear at midnight command.", false);
			r_ClearAtMidnight = true;
		}
	}
	// GO BACK UNTILL REQUEST RECEIVED?!?!
	if (r_RequestState != HTTP_REQUEST_RECEIVED)
		return;

	SCDateTime StartIndexDate = sc.BaseDateTimeIn[sc.UpdateStartIndex].GetDate();
	SCDateTime LastBarDate = sc.BaseDateTimeIn[sc.ArraySize - 1].GetDate();



	if (p_ValuesLineForDates->size() == 0)
	{
		sc.AddMessageToLog(sc.HTTPResponse, 1);
		std::string Bufferas = sc.HTTPResponse.GetChars();
		std::replace(Bufferas.begin(), Bufferas.end(), ';', '-'); // replace all 'x' to 'y'
		//sc.AddMessageToLog(Bufferas.c_str(), 1);
		sc.HTTPResponse = Bufferas.c_str();
		sc.AddMessageToLog(sc.HTTPResponse, 1);

		if (sc.HTTPResponse.CompareNoCase("Date", 4) == 0)  //Comodities Report type	
		{
			sc.HTTPResponse.ParseLines(*p_ValuesLineForDates);
			Buffer.Format("######## Received %d COT lines of data from server.", p_ValuesLineForDates->size());
			sc.AddMessageToLog(Buffer, 1);

			std::vector<char*> EmptyVector;

			for (int Index = 0; Index < (int)p_ValuesLineForDates->size(); Index++)
			{
				p_PointersToValuesForDates->push_back(EmptyVector);
				p_ValuesLineForDates->at(Index).Tokenize(",", p_PointersToValuesForDates->back());
			}
			AllowRequestLevelsFromServer = false;
			FullRecalculate = true;
		}
		else
		{
			Buffer.Format("######## Quandle request error: %s", sc.HTTPResponse.GetChars());
			sc.AddMessageToLog(Buffer, 1);
			AllowRequestLevelsFromServer = false;
		}
	}

	if (p_PointersToValuesForDates->empty())
	{
		AllowRequestLevelsFromServer = true;
		if (Logging.GetYesNo()) sc.AddMessageToLog("######## p_PointersToValuesForDates is empty, dont try input to subgraph, return to top instead.", 1);
		RequestURL = "";
		AllowRequestLevelsFromServer = true;

	}
	if (FullRecalculate)
	{
		if (Logging.GetYesNo()) sc.AddMessageToLog("########  Data loaded into vector, disallow further HTTP requests", 1);
		sc.UpdateStartIndex = 0;
	}



	if (!p_PointersToValuesForDates->empty() && FullRecalculate)
	{

		// Set Report type and name ast 4 subgraphs

		SCString RepTyp = p_PointersToValuesForDates->at(0)[2];
		if (RepTyp.CompareNoCase("Prod", 4) == 0)  //Comodities Report type
		{
			ReportType = 1;
			sc.Subgraph[0].Name = "Producer";
			sc.Subgraph[1].Name = "Swap Dealer";
			sc.Subgraph[2].Name = "Managed Money";
			sc.Subgraph[3].Name = "Other Reportable";
			if (Logging.GetYesNo()) sc.AddMessageToLog("######## This is a COMMODITIES COT report", 1);
		}
		else if (RepTyp.CompareNoCase("Deal", 4) == 0)  //Financial Report type
		{
			ReportType = 2;
			sc.Subgraph[0].Name = "Dealer";
			sc.Subgraph[1].Name = "Asset Manager";
			sc.Subgraph[2].Name = "Leveraged Funds";
			sc.Subgraph[3].Name = "Other Reportable";
			if (Logging.GetYesNo()) sc.AddMessageToLog("######## This is a FINANCIAL COT report", 1);
		}

		// NAME SUBGRAPHS 5,6,7......
		SCString NAME = ("########Loading Subgraph titles: ");
		for (int ItemIndex = 1; ItemIndex < (p_PointersToValuesForDates->at(0).size()); ItemIndex++)
		{
			NAME += p_PointersToValuesForDates->at(0)[ItemIndex];
			NAME += " - ";
			sc.Subgraph[ItemIndex + 3].Name = p_PointersToValuesForDates->at(0)[ItemIndex];
		}
		if (Logging.GetYesNo()) sc.AddMessageToLog(NAME, 1);
		sc.AddMessageToLog("######## Loading data to subgraphs", 1);



		//FILL SUBGRAPHS WITH DATA
		for (int BarIndex = sc.UpdateStartIndex; BarIndex < sc.ArraySize - 1; ++BarIndex)
		{
			SCDateTime IndexDate = sc.BaseDateTimeIn[BarIndex];

			for (unsigned int Index = 0; Index < p_PointersToValuesForDates->size(); Index++)
			{
				SCDateTime DataDate = sc.DateStringToSCDateTime(p_PointersToValuesForDates->at(Index)[0]); //Datedate is date from array
				SCDateTime DataDateLessOne = DataDate;
				DataDateLessOne.SubtractDays(1);

				if (IndexDate == DataDateLessOne)
				{

					if (ReportType == 1)//COMMODITIES PRODUCERS 2-3, SWAP 4-5, MM 7-8, OT 10-11
					{
						sc.Subgraph[0][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[2]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[3]);
						sc.Subgraph[1][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[4]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[5]);
						sc.Subgraph[2][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[7]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[8]);
						sc.Subgraph[3][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[10]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[11]);
					}
					else if (ReportType == 2)//FINANCIAL  DEALER 2-3, ASSETMANGR 5-6, Lev 8-9 , Other 11-12
					{
						sc.Subgraph[0][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[2]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[3]);
						sc.Subgraph[1][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[5]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[6]);
						sc.Subgraph[2][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[8]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[9]);
						sc.Subgraph[3][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[11]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[12]);
					}

					for (unsigned int ItemIndex = 1; ItemIndex < (p_PointersToValuesForDates->at(Index).size()); ItemIndex++)
					{
						sc.Subgraph[ItemIndex + 3][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[ItemIndex]);
					}


				}
				else if (IndexDate == DataDate)
				{

					if (ReportType == 1)//COMMODITIES PRODUCERS 2-3, SWAP 4-5, MM 7-8, OT 10-11
					{
						sc.Subgraph[0][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[2]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[3]);
						sc.Subgraph[1][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[4]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[5]);
						sc.Subgraph[2][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[7]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[8]);
						sc.Subgraph[3][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[10]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[11]);
					}
					else if (ReportType == 2)//FINANCIAL  DEALER 2-3, ASSETMANGR 5-6, Lev 8-9 , Other 11-12
					{
						sc.Subgraph[0][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[2]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[3]);
						sc.Subgraph[1][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[5]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[6]);
						sc.Subgraph[2][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[8]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[9]);
						sc.Subgraph[3][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[11]) - (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[12]);
					}
					for (unsigned int ItemIndex = 1; ItemIndex < (p_PointersToValuesForDates->at(Index).size()); ItemIndex++)
					{
						sc.Subgraph[ItemIndex + 3][BarIndex] = (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[ItemIndex]);
					}
				}



			}

		}
		//PRINT DATA TO LOG FOR DEBUGGING
		if (Logging.GetYesNo())
		{
			sc.AddMessageToLog("######## Message log listing first 6 rows and 4 columns of data only", 1);
			for (unsigned int Index = 1; Index < 7; Index++)//p_PointersToValuesForDates->size(
			{
				SCString DataFor = p_PointersToValuesForDates->at(Index)[0];
				SCDateTime DataDate = sc.DateStringToSCDateTime(p_PointersToValuesForDates->at(Index)[0]); //Datedate is date from array
				SCString Buffer;
				Buffer.Format("Date %s - %f - %f - %f - %f", DataFor.GetChars(), (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[1]), (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[2]), (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[3]), (float)sc.StringToDouble(p_PointersToValuesForDates->at(Index)[4]));
				sc.AddMessageToLog(Buffer, 1);
			}
		}

		FullRecalculate = false;
	}


}
/*============================================================================*/
//Returns 1 if request has been made. Returns 0 if request has not been made.
int TradingLevelsStudy_RequestValuesFromServer
(SCStudyInterfaceRef sc
	, const SCString& BaseWebsiteURL
	, int& r_RequestState
)
{

	if (r_RequestState == HTTP_REQUEST_NOT_SENT)
	{


		if (!sc.MakeHTTPRequest(BaseWebsiteURL))
		{
			sc.AddMessageToLog("######## Error making HTTP Request.", true);
			r_RequestState = HTTP_REQUEST_ERROR;
		}
		else
		{
			r_RequestState = HTTP_REQUEST_MADE;
			SCString LogMessage("######## Requesting data from Quandl server: ");
			LogMessage += BaseWebsiteURL;
			sc.AddMessageToLog(LogMessage, true);
		}

		return 1;
	}

	return 0;
}

/*============================================================================*/
void TradingLevelsStudy_ResetStateForNextRequest
(SCStudyInterfaceRef sc
	, int& r_RequestState
	, SCDateTime& r_RequestDateTime
	, std::vector<SCString>* p_ValuesLineForDates
	, std::vector<std::vector<char*>>* p_PointersToValuesForDates
)
{
	p_ValuesLineForDates->clear();
	p_PointersToValuesForDates->clear();

	r_RequestState = HTTP_REQUEST_NOT_SENT;
	r_RequestDateTime = sc.CurrentSystemDateTime;
}
/*============================================================================*/
