//
// Kase Bars
//
// written by aslan
//
// 20101215 - initial version for SC
// 20110111 - fixed OHLC averages
//
#include "sierrachart.h"

//SCDLLName("KaseBar")



// macros for bar creation/updates, handles tick or bar inputs
#define ADD_BAR()											\
	sc.AddElements(1);										\
	o++;													\
	sc.DateTimeOut[o] = sc.BaseDateTimeIn[i];				\
	Open[o] = iOpen[i];										\
	High[o] = iHigh[i];										\
	Low[o] = iLow[i];										\
	Close[o] = iClose[i];									\
	Volume[o] = iVolume[i];									\
	Ticks[o] = iTicks[i];									\
	sc.CalculateOHLCAverages(o);							\
	BidVol[o] = iBidVol[i];									\
	AskVol[o] = iAskVol[i];									\
	UpTickVol[o] = iUpTickVol[i];							\
	DownTickVol[o] = iDownTickVol[i];						\
	BidTrades[o] = iBidTrades[i];							\
	AskTrades[o] = iAskTrades[i]

#define UPDATE_BAR()										\
	if (iHigh[i] > High[o]) High[o] = iHigh[i];				\
	if (iLow[i] < Low[o]) Low[o] = iLow[i];					\
	Close[o] = iClose[i];									\
	Volume[o] += iVolume[i];								\
	Ticks[o] += iTicks[i];									\
	sc.CalculateOHLCAverages(o);							\
	BidVol[o] += iBidVol[i];								\
	AskVol[o] += iAskVol[i];								\
	UpTickVol[o] += iUpTickVol[i];							\
	DownTickVol[o] += iDownTickVol[i];						\
	BidTrades[o] += iBidTrades[i];							\
	AskTrades[o] += iAskTrades[i]


SCSFExport scsf_KaseBar(SCStudyGraphRef sc)
{
	// input refs
	SCInputRef targetRangeTicks = sc.Input[0];

	// input bar refs
	SCFloatArrayRef iOpen        = sc.BaseDataIn[0];
	SCFloatArrayRef iHigh        = sc.BaseDataIn[1];
	SCFloatArrayRef iLow         = sc.BaseDataIn[2];
	SCFloatArrayRef iClose       = sc.BaseDataIn[3];
	SCFloatArrayRef iVolume      = sc.BaseDataIn[4];
	SCFloatArrayRef iTicks       = sc.BaseDataIn[5];
	SCFloatArrayRef iBidVol      = sc.BaseDataIn[9];
	SCFloatArrayRef iAskVol      = sc.BaseDataIn[10];
	SCFloatArrayRef iUpTickVol   = sc.BaseDataIn[11];
	SCFloatArrayRef iDownTickVol = sc.BaseDataIn[12];
	SCFloatArrayRef iBidTrades   = sc.BaseDataIn[13];
	SCFloatArrayRef iAskTrades   = sc.BaseDataIn[14];

	// ouput bar refs
	SCSubgraphRef Open        = sc.Subgraph[0];
	SCSubgraphRef High        = sc.Subgraph[1];
	SCSubgraphRef Low         = sc.Subgraph[2];
	SCSubgraphRef Close       = sc.Subgraph[3];
	SCSubgraphRef Volume      = sc.Subgraph[4];
	SCSubgraphRef Ticks       = sc.Subgraph[5];
	SCSubgraphRef OHLCAvg     = sc.Subgraph[6];
	SCSubgraphRef HLCAvg      = sc.Subgraph[7];
	SCSubgraphRef HLAvg       = sc.Subgraph[8];
	SCSubgraphRef BidVol      = sc.Subgraph[9];
	SCSubgraphRef AskVol      = sc.Subgraph[10];
	SCSubgraphRef UpTickVol   = sc.Subgraph[11];
	SCSubgraphRef DownTickVol = sc.Subgraph[12];
	SCSubgraphRef BidTrades   = sc.Subgraph[13];
	SCSubgraphRef AskTrades   = sc.Subgraph[14];

	// Set configuration variables
	if (sc.SetDefaults)
	{
		// Set the defaults
		sc.GraphName = "Kase";
		sc.StudyDescription = "Kase bars custom chart. <a href=""http://www.sierrachart.com/supportboard/showthread.php?t=29726"">Discussion subtopic (Kase bars custom chart)</a>";
		
		sc.IsCustomChart = 1;
		sc.DisplayAsMainPriceGraph = 1;
		sc.GraphRegion = 0;
		sc.StandardChartHeader = 1;
		sc.DrawZeros = 0;
		sc.GraphDrawType = GDT_OHLCBAR;
		sc.AutoLoop = 0;
		sc.FreeDLL = 0;

		sc.ValueFormat = sc.BaseGraphValueFormat;

		// Inputs		
		targetRangeTicks.Name = "Target range (ticks):";
		targetRangeTicks.SetInt(4);

		// Subgraphs
		Open.Name = "Open";
		Open.DrawStyle = DRAWSTYLE_LINE;
		High.Name = "High";
		High.DrawStyle = DRAWSTYLE_LINE;
		Low.Name = "Low";
		Low.DrawStyle = DRAWSTYLE_LINE;
		Close.Name = "Close";
		Close.DrawStyle = DRAWSTYLE_LINE;

		Volume.Name = "Volume";
		Volume.DrawStyle = DRAWSTYLE_IGNORE;
		Ticks.Name = "# of Trades";
		Ticks.DrawStyle = DRAWSTYLE_IGNORE;

		OHLCAvg.Name = "OHLC Avg";
		OHLCAvg.DrawStyle = DRAWSTYLE_IGNORE;
		HLCAvg.Name = "HLC Avg";
		HLCAvg.DrawStyle = DRAWSTYLE_IGNORE;
		HLAvg.Name = "HL Avg";
		HLAvg.DrawStyle = DRAWSTYLE_IGNORE;

		BidVol.Name = "Bid Vol";
		BidVol.DrawStyle = DRAWSTYLE_IGNORE;
		AskVol.Name = "Ask Vol";
		AskVol.DrawStyle = DRAWSTYLE_IGNORE;

		UpTickVol.Name = "Up Tick Vol";
		UpTickVol.DrawStyle = DRAWSTYLE_IGNORE;
		DownTickVol.Name = "Down Tick Vol";
		DownTickVol.DrawStyle = DRAWSTYLE_IGNORE;

		BidTrades.Name = "Bid Trades";
		BidTrades.DrawStyle = DRAWSTYLE_IGNORE;
		AskTrades.Name = "Ask Trades";
		AskTrades.DrawStyle = DRAWSTYLE_IGNORE;

		return;
	}

	try
	{
		long i = 0;		// input  index - underlying tick/bar chart
		long o = 0;		// output index - kase chart

		// refs to persistent vars
		float& targetRange = sc.PersistVars->f1;  // target bar size in price terms
		int&   lastIndex   = sc.PersistVars->i1;  // lastIndex processed
		int&   firstBar    = sc.PersistVars->i2;  // keep track of when we have first bar of session

		if (sc.UpdateStartIndex == 0)
		{
			// clear existing chart data
			sc.ResizeArrays(0);

			// init state i.e. persist vars
			targetRange = sc.RoundToTickSize(targetRangeTicks.GetInt() * sc.TickSize, sc.TickSize);
			firstBar = true;
			lastIndex = -1;

			sc.ValueFormat = sc.BaseGraphValueFormat;
			sc.GraphName.Format("Kase %i", targetRangeTicks.GetInt());
		}


		// do data processing
		o = sc.OutArraySize - 1;

		for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
		{
			if (i == lastIndex) continue;  // block handling the same tick multiple times (manual looping)

			// starting new bar at session boundary makes sure you have the same bars
			// reguardless of the first date that is loaded in the chart
			// Note: using date change instead of session boundary for now
			if (i == 0 || (sc.BaseDateTimeIn[i-1].GetDate() != sc.BaseDateTimeIn[i].GetDate()))
			{
				// create new bar
				ADD_BAR();
				firstBar = true;
			}
			else 
			{
				// calc true range using new tick to see if bar will exceed target range
				float prevClose = firstBar ? Open[o] : Close[o-1];
				float hi = max(max(High[o], iHigh[i]), prevClose);
				float lo = min(min(Low[o],  iLow[i]),  prevClose);
				float trueRange = hi - lo;
				
				if (sc.FormattedEvaluate(trueRange, sc.ValueFormat, GREATER_OPERATOR, targetRange, sc.ValueFormat))
				{
					ADD_BAR();
					firstBar = false;
				}
				else
				{
					UPDATE_BAR();
				}
			}
			lastIndex = i;
		}
	}
	catch (char *ErrMsg){
		sc.AddMessageToLog(ErrMsg, 1);
	}
}
