//jdt Trend Collection
//
//Author: Jsyd
//Date: 01/17/2009
// 
//

#include "sierrachart.h"

SCSFExport scsf_jdtTrendCatcher3(SCStudyGraphRef sc)
{
	SCSubgraphRef vcSubgraph = sc.Subgraph[2];
	SCSubgraphRef sellSubgraph = sc.Subgraph[17];
	SCSubgraphRef buySubgraph = sc.Subgraph[18];
	SCSubgraphRef brSubgraph = sc.Subgraph[19];
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "jdtTrendCatcher3";

		sc.StudyDescription = "Trend Reversal Indicator. This indicator uses a combination of Three Line Break, John Carter's Value Chart, Heikin-Ashi, and Three Bar Reversal. Entry arrows are dispayed when the TLB and HA are in agreement. The dots are overbought/oversold indications using the VC calculations. The 3BR is indicated by outlining the candles in yellow(sell) or white(buy).\
							  Discussion subtopic (macd bollinger custom study):\
							  https://www.sierrachart.com/supportboard/showthread.php?p=115354#post115354";

		sc.Subgraph[0].Name = "UpBar";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[0].PrimaryColor = RGB(0, 255, 0);

		sc.Subgraph[1].Name = "DownBar";
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[1].PrimaryColor = RGB(255, 0, 0);

		vcSubgraph.Name = "ValueChart +/- 8 point";
		vcSubgraph.DrawStyle = DRAWSTYLE_POINT;
		vcSubgraph.SecondaryColorUsed = 1;
		vcSubgraph.PrimaryColor = RGB(255, 0, 0);
		vcSubgraph.SecondaryColor = RGB(0, 255, 0);
		vcSubgraph.LineWidth = 4;

		sellSubgraph.Name = "Sell Entry Arrow";
		sellSubgraph.DrawStyle = DRAWSTYLE_ARROWDOWN;
		sellSubgraph.PrimaryColor = RGB(255, 0, 0);
		sellSubgraph.LineWidth = 2;

		buySubgraph.Name = "Buy Entry Arrow";
		buySubgraph.DrawStyle = DRAWSTYLE_ARROWUP;
		buySubgraph.PrimaryColor = RGB(0, 255, 0);
		buySubgraph.LineWidth = 2;

		brSubgraph.Name = "3BR Color";
		brSubgraph.DrawStyle = DRAWSTYLE_COLORBARHOLLOW;
		brSubgraph.SecondaryColorUsed = 1;
		brSubgraph.LineWidth = 1;
		brSubgraph.PrimaryColor = RGB(255,255,255);
		brSubgraph.SecondaryColor = RGB(255,255,0);

		sc.Input[0].Name = "3LB - Number of bars to break";
		sc.Input[0].SetInt(3);
		sc.Input[0].SetIntLimits(1, 10);

		sc.Input[1].Name = "3LB - Number of ranges to break";
		sc.Input[1].SetInt(3);
		sc.Input[1].SetIntLimits(1, 5);

		sc.Input[2].Name = "Entry Point Hide - Volatility Period(bars)";
		sc.Input[2].SetInt(10);
		sc.Input[2].SetIntLimits(1, 1000);

		sc.Input[3].Name = "Entry Point Hide - Volatility Range(price)";
		sc.Input[3].SetFloat(40);
		sc.Input[3].SetFloatLimits(.0001f, 1000);

		sc.Input[4].Name = "Never hide Volatility Entry Points";
		sc.Input[4].ValueType=YESNO_VALUE;
		sc.Input[4].SetYesNo(0);

		sc.Input[5].Name = "Value Chart Trigger Value (+/-)";
		sc.Input[5].SetInt(8);
		sc.Input[5].SetIntLimits(1, 16);

		sc.Input[6].Name = "Value Chart Period";
		sc.Input[6].SetInt(5);
		sc.Input[6].SetIntLimits(1, 100);

		sc.Input[9].Name = "Entry Point Displacement";
		sc.Input[9].SetFloat(3);
		sc.Input[9].SetFloatLimits(.0001f, 100);

		sc.Input[10].Name = "Value Chart Displacement";
		sc.Input[10].SetFloat(2);
		sc.Input[10].SetFloatLimits(.0001f, 100);

		// during development set this flag to 1, so the dll can be modified. When development is done set it to 0 to speed up the function calling.
		sc.FreeDLL = 0;
		sc.DrawZeros = 0;  // true
		sc.AutoLoop = 1;  // true
		sc.GraphRegion = 0;
		return;
	}
	//	Init Vars
	int rInt = sc.Input[1].GetInt();
	//	float highArr [rInt];
	//	float lowArr [rInt];
	float& fHigh = sc.PersistVars->f1;
	float& fLow = sc.PersistVars->f2;
	float& rLow0 = sc.PersistVars->f3;
	float& rLow1 = sc.PersistVars->f4;
	float& rLow2 = sc.PersistVars->f5;
	float& rLow3 = sc.PersistVars->f6;
	float& rLow4 = sc.PersistVars->f7;
	float& rHigh0 = sc.PersistVars->f8;
	float& rHigh1 = sc.PersistVars->f9;
	float& rHigh2 = sc.PersistVars->f10;
	float& rHigh3 = sc.PersistVars->f11;
	float& rHigh4 = sc.PersistVars->f12;
	int& rTrend = sc.PersistVars->i1;
	int& Trend = sc.PersistVars->i2;
	int& haFlow0 = sc.PersistVars->i3;
	int& haFlow1 = sc.PersistVars->i4;
	int& rTrend0 = sc.PersistVars->i5;
	int& rTrend1 = sc.PersistVars->i6;
	int bInt = sc.Input[0].GetInt();
	int cur = sc.Index;
	int c = 0;
	int lastTrend = rTrend;
	float last = sc.BaseDataIn[SC_LAST][cur];

	sc.Subgraph[0][cur]=sc.BaseDataIn[SC_LAST][cur];
	//	sc.Subgraph[1][cur]=sc.BaseDataIn[SC_LAST][cur];

	//	UpTrend setting a new range - just draw a new range bar
	if((last > fHigh) && (Trend > 0))
	{
		Trend = 1;
		//	Set new hgh and low to draw trend range area
		fLow = fHigh;
		fHigh = last;
		//	Update our range values
		rHigh4 = rHigh3;
		rHigh3 = rHigh2;
		rHigh2 = rHigh1;
		rHigh1 = rHigh0;
		rHigh0 = fLow;
		//	Save new range begin index	
		sc.PersistVars->i1 = cur;
	}
	//	Possible trend reversal - DownTrend -> UpTrend
	if((last > fHigh) && (Trend < 1))
	{
		//	Iterate thru number of bars to compare as specifed by user
		for (int x = cur - bInt; x < cur; x++) 
		{
			//	Make sure we are higher that all bars, both up and down
			if((last >  sc.BaseDataIn[SC_OPEN][x]) && (last >  sc.BaseDataIn[SC_LAST][x]))
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
			//	Update our range values
			rLow4 = rLow3;
			rHigh3 = rLow2;
			rLow2 = rLow1;
			rLow1 = rLow0;
			rLow0 = fHigh;
		}
	}
	//	DownTrend setting a new range - just draw a new range bar
	if((last < fLow) && (Trend < 1))
	{
		Trend = 0;
		//	Set new hgh and low to draw trend range area
		fHigh = fLow;
		fLow = last;
		//	Update our range values
		rLow4 = rLow3;
		rHigh3 = rLow2;
		rLow2 = rLow1;
		rLow1 = rLow0;
		rLow0 = fHigh;
	}
	//	Possible trend reversal - UpTrend -> DownTrend
	if((last < fLow) && (Trend > 0))
	{
		//	Iterate thru number of bars to compare as specifed by user
		for (int x = cur - bInt; x < cur; x++) 
		{		
			//	Make sure we are lower that all bars, both up and down
			if((last <  sc.BaseDataIn[SC_OPEN][x]) && (last <  sc.BaseDataIn[SC_LAST][x]))
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
			//	Update our range values
			rLow4 = rLow3;
			rHigh3 = rLow2;
			rLow2 = rLow1;
			rLow1 = rLow0;
			rLow0 = fHigh;
		}
	}
	//	Color the bar
	float highArr [] = {rLow0,rLow1,rLow2,rLow3,rLow4}; 
	float lowArr [] = {rHigh0,rHigh1,rHigh2,rHigh3,rHigh4};
	int NoChg = 0;
	int rTrendArr [] = {rTrend0, rTrend1};
	rTrend1 = rTrend0;
	for (int r=0; r < rInt ; r++ )
	{
		if(Trend == 1)
		{
			if(fHigh < highArr[r]) {
				NoChg = 1;
				break;
			}	
		} 
		else if(Trend == 0)
		{
			if(fLow > lowArr[r]) {
				NoChg = 1;
				break;
			}	
		}
	}
	if(NoChg == 0) {
		rTrend = Trend;
	} else {
		rTrend = lastTrend;
	}
	rTrend0 = rTrend;
	if (rTrend == 1) {
		sc.Subgraph[0].DataColor[cur] = sc.Subgraph[0].PrimaryColor;
	} else if (rTrend == 0) {
		sc.Subgraph[0].DataColor[cur] = sc.Subgraph[1].PrimaryColor;
	}
	/*====================================================================================
	John Carter's Value Chart
	====================================================================================*/	

	int period = sc.Input[6].GetInt();
	sc.Subgraph[4][cur-1] = (sc.BaseData[SC_HIGH][cur-1] + sc.BaseData[SC_LOW][cur-1])/2;
	sc.SimpleMovAvg(sc.Subgraph[4],sc.Subgraph[5],cur-1,period);
	float PreVarAs = sc.Subgraph[5][cur-1];
	sc.ATR(sc.BaseData,sc.Subgraph[6],sc.Subgraph[7],cur-1,period,MOVAVGTYPE_SIMPLE);
	float PreVolatiliteit = sc.Subgraph[7][cur-1]/period;
	int vcPreHigh = (sc.BaseData[SC_HIGH][cur-1] - PreVarAs)/PreVolatiliteit;
	int vcPreLow = (sc.BaseData[SC_LOW][cur-1] - PreVarAs)/PreVolatiliteit;

	sc.Subgraph[8][cur] = (sc.BaseData[SC_HIGH][cur] + sc.BaseData[SC_LOW][cur])/2;
	sc.SimpleMovAvg(sc.Subgraph[8],sc.Subgraph[9],cur,period);
	float VarAs = sc.Subgraph[9][cur];
	sc.ATR(sc.BaseData,sc.Subgraph[10],sc.Subgraph[11],cur,period,MOVAVGTYPE_SIMPLE);
	float Volatiliteit = sc.Subgraph[11][cur]/period;
	int vcHigh = (sc.BaseData[SC_HIGH][cur] - VarAs)/Volatiliteit;
	int vcLow = (sc.BaseData[SC_LOW][cur] - VarAs)/Volatiliteit;
	//	sc.Subgraph[3][i] = (sc.BaseData[SC_LAST][cur] - VarAs)/Volatiliteit;

	if((vcPreHigh >= sc.Input[5].GetInt()) && (vcHigh < sc.Input[5].GetInt())) {
		vcSubgraph.DataColor[cur-1] = vcSubgraph.PrimaryColor;
		vcSubgraph[cur-1] = sc.BaseDataIn[SC_HIGH][cur-1] + sc.Input[10].GetFloat();
	} else if((vcPreLow <= -sc.Input[5].GetInt()) && (vcLow > -sc.Input[5].GetInt())) {
		vcSubgraph.DataColor[cur-1] = vcSubgraph.SecondaryColor;
		vcSubgraph[cur-1] = sc.BaseDataIn[SC_LOW][cur-1] - sc.Input[10].GetFloat();
	}
	/*============================================================================
	Heiken-ashi


	Formula Used:
	Heikin Ashi close: haClose = ( O + H + L + C ) / 4
	Heikin Ashi open: haOpen = ( yesterday's haOpen + yesterday's haClose ) / 2
	Heikin Ashi high: haHigh = the higher of H, and today's haOpen
	Heikin Ashi low: haLow = the lower of L, and today's haOpen
	----------------------------------------------------------------------------*/
	float Open = sc.BaseDataIn[SC_OPEN][cur];
	float High = sc.BaseDataIn[SC_HIGH][cur];
	float Low = sc.BaseDataIn[SC_LOW][cur];
	float Close = sc.BaseDataIn[SC_LAST][cur];

	sc.Subgraph[12][cur] = sc.BaseDataIn[SC_LAST][cur];
	if (cur == 0)
		sc.Subgraph[13][cur] = Open;
	else
	{
		sc.Subgraph[13][cur] = (sc.Subgraph[13][cur - 1] + sc.Subgraph[12][cur - 1]) / 2.0f;
	}

	sc.Subgraph[14][cur] = max(High, sc.Subgraph[13][cur]);
	sc.Subgraph[15][cur] = min(Low, sc.Subgraph[13][cur]);
	haFlow1 = haFlow0;
	if(sc.Subgraph[12][cur] > sc.Subgraph[13][cur])
	{
		haFlow0 = 1;
	}
	else if(sc.Subgraph[12][cur] < sc.Subgraph[13][cur])
	{
		haFlow0 = 0;
	}
	int haFlowArr [] = {haFlow0,haFlow1};

	if((sc.GetHighest(sc.BaseDataIn[SC_HIGH], cur, sc.Input[2].GetInt()) - sc.GetLowest(sc.BaseDataIn[SC_LOW], cur, sc.Input[2].GetInt()) > sc.Input[3].GetFloat()) || sc.Input[4].BooleanValue)
	{
		if(rTrendArr[0] != rTrendArr[1]) {
			if((rTrend == 1) && (haFlowArr[1] == 1))
			{
				buySubgraph.DataColor[cur] = buySubgraph.PrimaryColor;
				buySubgraph[cur] = sc.BaseDataIn[SC_LOW][cur] - sc.Input[9].GetFloat();
			}
			else if((rTrend == 0) && (haFlowArr[1] == 0))
			{
				sellSubgraph.DataColor[cur] = sellSubgraph.PrimaryColor;
				sellSubgraph[cur] = sc.BaseDataIn[SC_HIGH][cur] + sc.Input[9].GetFloat();
			}
		}
	}

	/*====================================================================================
	3 Bar Reversal		
	====================================================================================*/
	SCFloatArrayRef brHigh  = sc.BaseDataIn[SC_HIGH];
	SCFloatArrayRef brLow   = sc.BaseDataIn[SC_LOW];
	SCFloatArrayRef brOpen = sc.BaseDataIn[SC_OPEN];
	SCFloatArrayRef brLast  = sc.BaseDataIn[SC_LAST];
	SCFloatArrayRef brAvg  = sc.BaseDataIn[SC_OHLC];                   
	SCFloatArrayRef brOut  = brSubgraph.Data;

	if ((brLast[cur] > brHigh[cur - 1] || brHigh[cur] > brHigh[cur - 1]) && brLow[cur - 1] > brLow[cur - 2] && brLow[cur - 2] < brLow[cur - 3] )
	{
		brOut[cur] = brAvg[cur];
		brSubgraph.DataColor[cur] = brSubgraph.PrimaryColor;
	}
	else if ((brLast[cur] > brHigh[cur - 1] || brHigh[cur] > brHigh[cur - 1]) && brLow[cur - 1] > brLow[cur - 2] && brLow[cur - 2] == brLow[cur - 3] && brLow[cur - 3] < brLow[cur - 4] )
	{
		brOut[cur] = brAvg[cur];
		brSubgraph.DataColor[cur] = brSubgraph.PrimaryColor;
	}
	else if ((brLast[cur] < brLow[cur - 1] || brLow[cur] < brLow[cur - 1]) && brHigh[cur - 1] < brHigh[cur - 2] && brHigh[cur - 2] > brHigh[cur - 3] )
	{
		brOut[cur] = brAvg[cur];
		brSubgraph.DataColor[cur] = brSubgraph.SecondaryColor;
	}
	else if ((brLast[cur] < brLow[cur - 1] || brLow[cur] < brLow[cur - 1]) && brHigh[cur - 1] < brHigh[cur - 2] && brHigh[cur - 2] == brHigh[cur - 3] && brHigh[cur - 3] > brHigh[cur - 4] )
	{
		brOut[cur] = brAvg[cur];
		brSubgraph.DataColor[cur] = brSubgraph.SecondaryColor;
	}
	else
	{
		brOut[cur] = 0;
	}
}

/*======================================================================================*/
SCSFExport scsf_jdtMDBBHA(SCStudyGraphRef sc)
{
	// Define Subgraphs for easy recognition
	SCSubgraphRef macd1Subgraph = sc.Subgraph[0];
	SCInputRef macd1InputInData = sc.Input[0];
	SCInputRef macd1InputFastLength = sc.Input[1];
	SCInputRef macd1InputSlowLength = sc.Input[2];
	SCInputRef macd1InputTriggerLength = sc.Input[3];
	SCInputRef macd1InputMAType = sc.Input[4];
	SCSubgraphRef macd2Subgraph = sc.Subgraph[1];
	SCSubgraphRef bbHighSubgraph = sc.Subgraph[2];
	SCSubgraphRef bbMiddleSubgraph = sc.Subgraph[3];
	SCSubgraphRef bbLowSubgraph = sc.Subgraph[4];
	SCInputRef bbInputLength = sc.Input[5];
	SCInputRef bbInputStandDev = sc.Input[6];

	// Section 1 - Set the configuration variables
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "jdt MACD/Bollinger Bands/Heiken-ashi";

		sc.StudyDescription = "jdt Strength and Direction Indicator based on the MACD, Bollinger Bands, and Heiken-Ashi studies. This study supplies multiple entry/exit confirmations.";

		macd1Subgraph.Name = "MACD Line";
		macd1Subgraph.DrawStyle = DRAWSTYLE_LINE;
		macd1Subgraph.LineWidth = 1;
		macd1Subgraph.PrimaryColor = RGB(255, 255, 0);

		macd2Subgraph.Name="MACD Points";
		macd2Subgraph.DrawStyle = DRAWSTYLE_POINT;
		macd2Subgraph.LineWidth = 3;
		macd2Subgraph.SecondaryColorUsed = 1;
		macd2Subgraph.PrimaryColor = RGB(0, 255, 0);
		macd2Subgraph.SecondaryColor = RGB(255, 0, 0);

		bbHighSubgraph.Name = "Bollinger Bands Upper Line";
		bbHighSubgraph.DrawStyle = DRAWSTYLE_LINE;
		bbHighSubgraph.LineWidth = 1;
		bbHighSubgraph.PrimaryColor = RGB(255, 255, 255);

		bbLowSubgraph.Name = "Bollinger Bands Lower Line";
		bbLowSubgraph.DrawStyle = DRAWSTYLE_LINE;
		bbLowSubgraph.LineWidth = 1;
		bbLowSubgraph.PrimaryColor = RGB(255, 255, 255);

		macd1InputInData.Name = "MACD Input Data";
		macd1InputInData.SetInputDataIndex(SC_LAST);

		macd1InputFastLength.Name = "MACD Fast MA Length";
		macd1InputFastLength.SetInt(10);
		macd1InputFastLength.SetIntLimits(1, 1000);

		macd1InputSlowLength.Name = "MACD Slow MA Length";
		macd1InputSlowLength.SetInt(21);
		macd1InputSlowLength.SetIntLimits(1, 1000);

		macd1InputTriggerLength.Name = "MACD MA LENGTH TRIGGER";
		macd1InputTriggerLength.SetFloat(16);
		macd1InputTriggerLength.SetFloatLimits(.5f, 100);

		macd1InputMAType.Name = "MACD Moving average type";
		macd1InputMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);

		bbInputLength.Name = "BBands Length";
		bbInputLength.SetInt(10);
		bbInputLength.SetIntLimits(1, 1000);

		bbInputStandDev.Name = "BBands Standard Deviation";
		bbInputStandDev.SetFloat(1);
		bbInputStandDev.SetFloatLimits(.1f, 100);

		/*Optional: Uncomment the following line when you are finished developing your function.
		This makes calling your function faster.
		However, if you need to make modifications after applying it to a chart, you will
		need to restart SierraChart to release the DLL. */
		//sc.FreeDLL = 0;
		sc.AutoLoop = 1;  // true
		sc.GraphRegion = 1;

		return;
	}
	// Setup Variables
	int i = sc.Index;
	float Open = sc.BaseDataIn[SC_OPEN][i];
	float High = sc.BaseDataIn[SC_HIGH][i];
	float Low = sc.BaseDataIn[SC_LOW][i];
	float Close = sc.BaseDataIn[SC_LAST][i];
	/*============================================================================
	Heiken-ashi

	Formula Used:
	Heikin Ashi close: haClose = ( O + H + L + C ) / 4
	Heikin Ashi open: haOpen = ( yesterday's haOpen + yesterday's haClose ) / 2
	Heikin Ashi high: haHigh = the higher of H, and today's haOpen
	Heikin Ashi low: haLow = the lower of L, and today's haOpen
	============================================================================*/



	if (i == sc.ArraySize - 1)
	{
		sc.Subgraph[12][i] = sc.BaseDataIn[SC_LAST][i];
	}
	else
	{
		sc.Subgraph[12][i] = (Open + High + Low + Close) / 4.0f;
	}
	if (i == 0)
	{
		sc.Subgraph[13][i] = Open;
	}
	else
	{
		sc.Subgraph[13][i] = (sc.Subgraph[13][i - 1] + sc.Subgraph[12][i - 1]) / 2.0f;
	}

	if(sc.Subgraph[12][i] > sc.Subgraph[13][i])
	{
		macd2Subgraph.DataColor[i] = macd2Subgraph.PrimaryColor;
	}
	else if(sc.Subgraph[12][i] < sc.Subgraph[13][i])
	{
		macd2Subgraph.DataColor[i] = macd2Subgraph.SecondaryColor;
	}

	/*===============================================================================
	MACD
	===============================================================================*/
	int len1 = macd1InputFastLength.GetInt();
	int len2 = macd1InputSlowLength.GetInt();
	int len3 = macd1InputTriggerLength.GetFloat();
	int ma_type	= macd1InputMAType.GetInt();
	int data_type_indx = (int)macd1InputInData.GetInputDataIndex();

	SCFloatArrayRef in = sc.BaseDataIn[data_type_indx];
	sc.MACD(in, macd1Subgraph, i, len1, len2, len3, ma_type);
	macd2Subgraph[i] = macd1Subgraph[i];
	//	sc.MACD(in, macd2Subgraph, i, len1, len2, len3, ma_type);
	sc.Subgraph[14][i] = macd1Subgraph[i]; //MACD
	sc.Subgraph[15][i] = macd1Subgraph.Arrays[2][i]; // MACD_MA
	sc.Subgraph[16][i] = macd1Subgraph.Arrays[3][i]; // MACD_Diff

	/*==============================================================================
	Bollinger Bands
	===============================================================================*/
	//	sc.BollingerBands(sc.Subgraph[14], bbHighSubgraph, i, bbInputLength.GetInt(), bbInputStandDev.GetInt(),ma_type);
	//	sc.BollingerBands(sc.Subgraph[16], bbLowSubgraph, i, bbInputLength.GetInt(), bbInputStandDev.GetInt(),ma_type);
	sc.BollingerBands(sc.Subgraph[14], bbMiddleSubgraph, i, bbInputLength.GetInt(), bbInputStandDev.GetFloat(), ma_type);
	//Access the individual lines
	float Average = bbMiddleSubgraph[i];
	float UpperBand = bbMiddleSubgraph.Arrays[0][i];
	float LowerBand = bbMiddleSubgraph.Arrays[1][i];
	//	UpperBand = (UpperBand + Average) / 2;
	//	LowerBand = (LowerBand + Average) / 2;
	//Copy to Visible Subgraphs
	bbHighSubgraph[i] = UpperBand;
	bbLowSubgraph[i] = LowerBand; 
}
SCSFExport scsf_jdtTrailingStop(SCStudyGraphRef sc)
{	 
	if(sc.SetDefaults)
	{
		sc.GraphName="jdt Trailing Stop (Kiwi)";
		sc.Subgraph[0].Name="TSUp";
		sc.Subgraph[0].DrawStyle=DRAWSTYLE_IGNORE;
		sc.Subgraph[1].Name="TSDn";
		sc.Subgraph[1].DrawStyle=DRAWSTYLE_IGNORE;

		sc.DrawZeros = 0;  // false
		sc.AutoLoop = 0;

		sc.Input[2].Name="ATR Length";
		sc.Input[2].SetFloat(9.0);
		sc.Input[3].Name="ATR Factor";
		sc.Input[3].SetFloat(2.5);

		sc.Input[4].Name="Hold if stops extending";
		sc.Input[4].ValueType=YESNO_VALUE;

		sc.Input[5].Name="Show SL Price Value (Default is offset)";
		sc.Input[5].ValueType=YESNO_VALUE; 

		sc.GraphRegion = 0;

		return;
	}

	int 	pos;
	bool	ratchet;
	float 	N,ATRFactor,Ave;
	float  	b,b2,b3,c1,c2,c3,c4,w1=0,w2=0;

	sc.DataStartIndex=10;

	N=sc.Input[2].FloatValue;
	ATRFactor=sc.Input[3].FloatValue;

	SCFloatArrayRef direction = sc.Subgraph[3];
	SCFloatArrayRef hiclose = sc.Subgraph[4];
	SCFloatArrayRef loclose = sc.Subgraph[5];

	SCFloatArrayRef e1 = sc.Subgraph[6];
	SCFloatArrayRef e2 = sc.Subgraph[7];
	SCFloatArrayRef e3 = sc.Subgraph[8];
	SCFloatArrayRef e4 = sc.Subgraph[9];
	SCFloatArrayRef e5 = sc.Subgraph[10];
	SCFloatArrayRef e6 = sc.Subgraph[11];

	if (sc.UpdateStartIndex < 1)
	{
		direction[sc.UpdateStartIndex] = 1;
		loclose[sc.UpdateStartIndex] = sc.BaseData[SC_LAST][sc.UpdateStartIndex]; 
		hiclose[sc.UpdateStartIndex] = loclose[sc.UpdateStartIndex];

		e1[sc.UpdateStartIndex]=sc.BaseData[SC_HIGH][sc.UpdateStartIndex]-sc.BaseData[SC_LOW][sc.UpdateStartIndex]; 
		e2[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex]; 
		e3[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex]; 
		e4[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex]; 
		e5[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex]; 
		e6[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex];
	}

	b=0.5;					// 0.5
	b2=(b*b);				// 0.25
	b3=(b2*b);				// 0.125

	c1=-b3;					// - 0.125
	c2=(3*(b2+b3));			// 0.45
	c3=(-3*(2*b2+b+b3)); 
	c4=(1+3*b+b3+3*b2);
	w1 = 2/(N+1);  
	w2 = 1-w1;

	for (pos=max(sc.UpdateStartIndex, 1); pos < sc.ArraySize; pos++)
	{
		float temp = max(sc.BaseData[SC_HIGH][pos]-sc.BaseData[SC_LOW][pos], sc.BaseData[SC_HIGH][pos]-sc.BaseData[SC_LAST][pos-1]);
		float P   = max(temp,sc.BaseData[SC_LAST][pos-1]-sc.BaseData[SC_LOW][pos]);

		e1[pos] = w1*P + w2*e1[pos - 1];
		e2[pos] = w1*e1[pos] + w2*e2[pos - 1];
		e3[pos] = w1*e2[pos] + w2*e3[pos - 1];
		e4[pos] = w1*e3[pos] + w2*e4[pos - 1];
		e5[pos] = w1*e4[pos] + w2*e5[pos - 1];
		e6[pos] = w1*e5[pos] + w2*e6[pos - 1];

		Ave = c1*e6[pos] + c2*e5[pos] + c3*e4[pos] + c4*e3[pos];

		ratchet=1;
		if((direction[pos-1]==1 && sc.BaseData[SC_LAST][pos]<sc.Subgraph[0].Data[pos-1]) 
			|| 
			(direction[pos-1]==-1 && sc.BaseData[SC_LAST][pos]>sc.Subgraph[1].Data[pos-1]))
		{
			if(direction[pos-1]==1)
			{
				direction[pos] = -1; //reverse short
				hiclose[pos] = sc.BaseData[SC_LAST][pos];
				loclose[pos] = 0;
			} 
			else
			{
				direction[pos] = 1; //reverse long
				loclose[pos] = sc.BaseData[SC_LAST][pos];
				hiclose[pos] = 0;
			}
		} 
		else
		{
			if(direction[pos-1]==1)
			{
				if(sc.BaseData[SC_LAST][pos]>loclose[pos-1])
				{
					loclose[pos] = sc.BaseData[SC_LAST][pos];
					hiclose[pos] = hiclose[pos-1];
				}
				else
				{
					ratchet=0;
					loclose[pos] = loclose[pos-1];
					hiclose[pos] = hiclose[pos-1];
				}
			} 
			else
			{
				if(sc.BaseData[SC_LAST][pos]<hiclose[pos-1])
				{
					loclose[pos] = loclose[pos-1];
					hiclose[pos] = sc.BaseData[SC_LAST][pos];
				}
				else
				{
					ratchet=0;
					loclose[pos] = loclose[pos-1];
					hiclose[pos] = hiclose[pos-1];
				}
			};

			direction[pos] = direction[pos-1]; // no change
		};
		if(!sc.Input[4].BooleanValue || ratchet)
		{
			if(direction[pos]==1) 
			{
				sc.Subgraph[0].Data[pos] = (loclose[pos]-(Ave*ATRFactor)); 
				sc.Subgraph[1].Data[pos] = (hiclose[pos]+(Ave*ATRFactor))+sc.BaseData[SC_LAST][pos];
			} 
			else
			{
				sc.Subgraph[1].Data[pos] = (hiclose[pos]+(Ave*ATRFactor)); 
				sc.Subgraph[0].Data[pos] = (loclose[pos]-(Ave*ATRFactor))+sc.BaseData[SC_LAST][pos];
			}
		} else
		{
			sc.Subgraph[0].Data[pos] = sc.Subgraph[0].Data[pos-1];
			sc.Subgraph[1].Data[pos] = sc.Subgraph[1].Data[pos-1];
		}

		s_UseTool Tool;
		if(sc.Input[5].BooleanValue)
		{
			Tool.Clear(); // reset tool structure for our next use
			Tool.ChartNumber = sc.ChartNumber;
			Tool.DrawingType = DRAWING_TEXT;
			Tool.LineNumber = 11;
			// Update BarIndex to 40 bars from the end
			int BarIndex = sc.ArraySize - 20;
			BarIndex = max(BarIndex,0);
			Tool.BeginDateTime = sc.BaseDateTimeIn[BarIndex];
			float High,Low,BeginValue;
			sc.GetMainGraphVisibleHighAndLow(High,Low);
			BeginValue = High - ((High - Low) * (5*0.01f));
			Tool.BeginValue = BeginValue;
			Tool.Color = RGB(0,255,0);  // Green
			Tool.TextAlignment = DT_TOP;
			Tool.Text.Format("Buy SL: %.3f",sc.Subgraph[0].Data[pos]);
			Tool.AddMethod = UTAM_ADD_OR_ADJUST;
			sc.UseTool(Tool);

			s_UseTool Tool2;
			Tool2.Clear(); // reset Tool2 structure for our next use
			Tool2.ChartNumber = sc.ChartNumber;
			Tool2.DrawingType = DRAWING_TEXT;
			Tool2.LineNumber = 12;
			// Update BarIndex to 40 bars from the end
			BarIndex = sc.ArraySize - 20;
			BarIndex = max(BarIndex,0);
			Tool2.BeginDateTime = sc.BaseDateTimeIn[BarIndex];
			sc.GetMainGraphVisibleHighAndLow(High,Low);
			BeginValue = High - ((High - Low) * (1*0.01f));
			Tool2.BeginValue = BeginValue;
			Tool2.Color = RGB(255,0,0);  // Red
			Tool2.TextAlignment = DT_TOP;
			Tool2.Text.Format("Sell SL: %.3f",sc.Subgraph[1].Data[pos]);
			Tool2.AddMethod = UTAM_ADD_OR_ADJUST;
			sc.UseTool(Tool2);
		}
		else
		{
			float textVal;
			if((sc.Subgraph[0].Data[pos]-sc.BaseData[SC_LAST][pos]) < 0.000)
			{
				textVal = (sc.Subgraph[0].Data[pos]-sc.BaseData[SC_LAST][pos])*-1;
			}
			else
			{
				textVal = sc.Subgraph[0].Data[pos]-sc.BaseData[SC_LAST][pos];
			}
			Tool.Clear(); // reset tool structure for our next use
			Tool.ChartNumber = sc.ChartNumber;
			Tool.DrawingType = DRAWING_TEXT;
			Tool.LineNumber = 11;
			// Update BarIndex to 40 bars from the end
			int BarIndex = sc.ArraySize - 20;
			BarIndex = max(BarIndex,0);
			Tool.BeginDateTime = sc.BaseDateTimeIn[BarIndex];
			float High,Low,BeginValue;
			sc.GetMainGraphVisibleHighAndLow(High,Low);
			BeginValue = High - ((High - Low) * (1*0.01f));
			Tool.BeginValue = BeginValue;
			Tool.Color = RGB(255,255,0);  // Yellow
			Tool.TextAlignment = DT_TOP;
			Tool.Text.Format("StopLoss: %.3f",textVal);
			Tool.AddMethod = UTAM_ADD_OR_ADJUST;
			sc.UseTool(Tool);
		}
	}

}