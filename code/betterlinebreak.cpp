//
// BetterLineBreak Custom Chart
//
// written by aslan
//
// 20110218 - initial version for SC
//
#include "sierrachart.h"

//SCDLLName("BetterLineBreak")

// macros - used to collect common code without passing lots of parameters
#define BLB_ADD_BAR()											\
	/* pre-add bar work - clean up previous bar */				\
	/* adjust open to show LineBreak instead of real open */	\
	if (showRealOpen.GetYesNo() == 0)							\
	{															\
		float temp = Open[o];									\
		Open[o] = LineBreakOpen[o];								\
		LineBreakOpen[o] = temp;								\
	}															\
	/* real add bar work */										\
	sc.AddElements(1);											\
	o++;														\
	sc.DateTimeOut[o] = sc.BaseDateTimeIn[i];					\
	if (secPerBar != 0)											\
		sc.DateTimeOut[o].SetTime(sc.DateTimeOut[o].GetTime()-(sc.DateTimeOut[o].GetTime()%secPerBar));  \
	Open[o] = iOpen[i];											\
	High[o] = iHigh[i];											\
	Low[o] = iLow[i];											\
	Close[o] = iClose[i];										\
	Volume[o] = iVolume[i];										\
	Ticks[o] = iTicks[i];										\
	sc.CalculateOHLCAverages(o);								\
	BidVol[o] = iBidVol[i];										\
	AskVol[o] = iAskVol[i];										\
	UpTickVol[o] = iUpTickVol[i];								\
	DownTickVol[o] = iDownTickVol[i];							\
	BidTrades[o] = iBidTrades[i];								\
	AskTrades[o] = iAskTrades[i];								\
	LineBreakOpen[o] = iOpen[i];								\
	if (secPerBar != 0)											\
		barEndTime = quoteTime + (secPerBar - (quoteTime % secPerBar));	\
	barComplete = false;										\
	barTicks = (int)iTicks[i];  /* start tracking new bar */	\
	barVolume = (int)iVolume[i]


#define BLB_UPDATE_BAR()										\
	if (iHigh[i] > High[o]) High[o] = iHigh[i];					\
	if (iLow[i] < Low[o])   Low[o]  = iLow[i];					\
	Close[o] = iClose[i];										\
	Volume[o] += (iVolume[i] - lbVolume);						\
	Ticks[o] += (iTicks[i] - lbTicks);							\
	sc.CalculateOHLCAverages(o);								\
	BidVol[o] += (iBidVol[i] - lbBidVol);						\
	AskVol[o] += (iAskVol[i] - lbAskVol);						\
	UpTickVol[o] += (iUpTickVol[i] - lbUpTickVol);				\
	DownTickVol[o] += (iDownTickVol[i] - lbDownTickVol);		\
	BidTrades[o] += (iBidTrades[i] - lbBidTrades);				\
	AskTrades[o] += (iAskTrades[i] - lbAskTrades);				\
	barTicks += (int)(iTicks[i] - lbTicks);						\
	barVolume += (int)(iVolume[i] - lbVolume)


#define BLB_CHECK_TREND_CHANGE()								\
	if ((trend ==  1 && Close[o] > Close[o-1]) ||				\
		(trend == -1 && Close[o] < Close[o-1]))					\
	{															\
		/* continue trend with new bar, inc to max value  */	\
		numBars = min(numBars+1, numLines.GetInt());			\
	}															\
	else														\
	{															\
		/* switch/set trend */									\
		if (trend != 0)											\
		{														\
			LineBreakOpen[o] = Open[o-1];						\
			trend = -trend;										\
		}														\
		else trend = Close[o] > Open[o] ? 1 : -1;				\
		numBars = 1;											\
	}


// new lb bar when new close in trend direction or reverse beyond line break threshold
#define BLB_NEW_LB_BAR																\
((trend ==  1 && (Close[o] > Close[o-1] || Close[o] < lbOpen[o-numBars])) ||		\
 (trend == -1 && (Close[o] < Close[o-1] || Close[o] > lbOpen[o-numBars])) ||		\
 (trend ==  0 && Close[o] != Open[o]))


#define BLB_ADD_LINEBREAK_LINE(start, end, value)				\
	tool.Clear();												\
	tool.DrawingType = DRAWING_LINE;								\
	tool.Region = sc.GraphRegion;								\
	tool.Color = lblColor.GetColor();							\
	tool.LineWidth = 2;											\
	tool.LineStyle = LINESTYLE_DASH;							\
	tool.LineNumber = 444555666;								\
	tool.BeginDateTime = sc.DateTimeOut[start];					\
	tool.EndDateTime = sc.DateTimeOut[end];						\
	tool.BeginValue = value;									\
	tool.EndValue = value;										\
	sc.UseTool(tool)


//
// Better Line Break
//
SCSFExport scsf_BetterLineBreak(SCStudyGraphRef sc)
{
	// input refs
	SCInputRef numLines     = sc.Input[0];
	SCInputRef numMin       = sc.Input[1];
	SCInputRef numSec       = sc.Input[2];
	SCInputRef numTicks     = sc.Input[3];
	SCInputRef numVolume    = sc.Input[4];
	SCInputRef showRealOpen = sc.Input[5];
	SCInputRef lblColor     = sc.Input[6];

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
	SCSubgraphRef Open          = sc.Subgraph[0];
	SCSubgraphRef High          = sc.Subgraph[1];
	SCSubgraphRef Low           = sc.Subgraph[2];
	SCSubgraphRef Close         = sc.Subgraph[3];
	SCSubgraphRef Volume        = sc.Subgraph[4];
	SCSubgraphRef Ticks         = sc.Subgraph[5];
	SCSubgraphRef OHLCAvg       = sc.Subgraph[6];
	SCSubgraphRef HLCAvg        = sc.Subgraph[7];
	SCSubgraphRef HLAvg         = sc.Subgraph[8];
	SCSubgraphRef BidVol        = sc.Subgraph[9];
	SCSubgraphRef AskVol        = sc.Subgraph[10];
	SCSubgraphRef UpTickVol     = sc.Subgraph[11];
	SCSubgraphRef DownTickVol   = sc.Subgraph[12];
	SCSubgraphRef BidTrades     = sc.Subgraph[13];
	SCSubgraphRef AskTrades     = sc.Subgraph[14];
	SCSubgraphRef LineBreakOpen = sc.Subgraph[15];  // Line Break Open or True Open based on input value


	// Set configuration variables
	if (sc.SetDefaults)
	{
		// Set the defaults
		sc.GraphName = "BetterLineBreak";
		sc.StudyDescription = "BetterLineBreak custom chart. <a href=""http://www.sierrachart.com/supportboard/showthread.php?p=177816""> Discussion subtopic (BetterLineBreak Custom Chart)</a>.";
		
		sc.IsCustomChart = 1;
		sc.DisplayAsMainPriceGraph = 1;
		sc.GraphRegion = 0;
		sc.StandardChartHeader = 1;
		sc.DrawZeros = 0;
		sc.GraphDrawType = GDT_CANDLESTICK;
		sc.AutoLoop = 0;
		sc.FreeDLL = 0;

		sc.ValueFormat = sc.BaseGraphValueFormat;

		// Inputs		
		numLines.Name = "Num Line Break:";
		numLines.SetInt(3);
		numLines.SetIntLimits(0, INT_MAX);

		numMin.Name = "Min:";
		numMin.SetInt(0);
		numMin.SetIntLimits(0, INT_MAX);

		numSec.Name = "Sec:";
		numSec.SetInt(0);
		numSec.SetIntLimits(0, INT_MAX);

		numTicks.Name = "Ticks:";
		numTicks.SetInt(0);
		numTicks.SetIntLimits(0, INT_MAX);

		numVolume.Name = "Volume:";
		numVolume.SetInt(0);
		numVolume.SetIntLimits(0, INT_MAX);

		showRealOpen.Name = "Show real Open (vs Line Break Open):";
		showRealOpen.SetYesNo(1);

		lblColor.Name = "Line Break Line Color:";
		lblColor.SetColor(COLOR_WHITE);
		
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

		LineBreakOpen.Name = "Line Break/True Open";
		LineBreakOpen.DrawStyle = DRAWSTYLE_IGNORE;

		return;
	}

	try
	{
		long i = 0;		// input  index - underlying chart
		long o = 0;		// output index - renko chart
		s_UseTool tool;

		// refs to persistent vars
		int& lastIndex       = sc.PersistVars->i1;   // lastIndex processed
		int& barComplete     = sc.PersistVars->i2;   // barComplete
		int& numBars         = sc.PersistVars->i3;   // num bars in current trend
		int& trend           = sc.PersistVars->i4;   // -1 = down, +1 = up, 0 = first bar
		int& secPerBar       = sc.PersistVars->i5;   // num secs / bar
		int& ticksPerBar     = sc.PersistVars->i6;   // num ticks / bar
		int& volumePerBar    = sc.PersistVars->i7;   // volume / bar
		int& barEndTime      = sc.PersistVars->i8;   // end time boundary of current sub bar
		int& barTicks        = sc.PersistVars->i9;   // num ticks for current sub bar
		int& barVolume       = sc.PersistVars->i10;  // volume for current sub bar

		// track last value of current input bar (need for live updates to non-tick data)
		float& lbVolume      = sc.PersistVars->f1;   // last bar volume
		float& lbTicks       = sc.PersistVars->f2;   // last bar ticks
		float& lbBidVol      = sc.PersistVars->f3;   // last bar bid vlume
		float& lbAskVol      = sc.PersistVars->f4;   // last bar ask volume
		float& lbUpTickVol   = sc.PersistVars->f5;   // last bar up tick volume
		float& lbDownTickVol = sc.PersistVars->f6;   // last bar down tick volume
		float& lbBidTrades   = sc.PersistVars->f7;   // last bar bid trades
		float& lbAskTrades   = sc.PersistVars->f8;   // last bar ask trades

		// select which open array should be used for checking a line break
		SCSubgraphRef lbOpen = showRealOpen.GetYesNo() ? LineBreakOpen : Open;

		if (sc.UpdateStartIndex == 0)
		{
			// clear existing chart data
			sc.ResizeArrays(0);

			// init state i.e. persist vars
			lastIndex = -1;
			barComplete = false;
			numBars = 0;
			trend = 0;
			barEndTime = 0;

			secPerBar = numMin.GetInt()*60 + numSec.GetInt();
			ticksPerBar = numTicks.GetInt();
			volumePerBar = numVolume.GetInt();

			if (secPerBar == 0 && ticksPerBar == 0 && volumePerBar == 0)
			{
				// if the inputs are not set, use the underlying chart values
				ticksPerBar = sc.NumberOfTradesPerBar;
				volumePerBar = sc.VolumePerBar;
				if (ticksPerBar == 0 && volumePerBar == 0)
					secPerBar = sc.SecondsPerBar;  // only set if not tick/volume, sc limitation
			}

			sc.ValueFormat = sc.BaseGraphValueFormat;

			// set graph name along with underlying type
			sc.GraphName.Format("%i BetterLineBreak", numLines.GetInt());
			SCString barType;
			if (secPerBar != 0)
			{
				int min = secPerBar / 60;
				int sec = secPerBar % 60;
				if (min != 0 && sec != 0)
					sc.GraphName += barType.Format(" %i:%02i Min:Sec", min, sec);
				else if (min != 0)
					sc.GraphName += barType.Format(" %i Min", min);
				else
					sc.GraphName += barType.Format(" %i Sec", sec);
			}
			if (ticksPerBar != 0)
				sc.GraphName += barType.Format(" %i Ticks", ticksPerBar);
			if (volumePerBar != 0)
				sc.GraphName += barType.Format(" %i Vol", volumePerBar);

			LineBreakOpen.Name = showRealOpen.GetYesNo() ? "Line Break Open" : "True Open";
		}

		// do data processing
		o = sc.OutArraySize - 1;


		for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
		{
			if (i != lastIndex)
			{
				// new input bar, reset last bar values
				lbVolume = 0; lbTicks = 0; lbBidVol = 0; lbAskVol = 0;
				lbUpTickVol = 0; lbDownTickVol = 0; lbBidTrades = 0; lbAskTrades = 0;
			}
			else
			{
				if (iTicks[i] == lbTicks) continue;  // block handling the same tick multiple times
			}

			int quoteTime = sc.BaseDateTimeIn[i].GetTime();

			// starting new bar at session boundary makes sure you have the same bars
			// reguardless of the first date that is loaded in the chart
			// Note: using date change instead of session boundary
			if (i == 0 || (sc.BaseDateTimeIn[i-1].GetDate() != sc.BaseDateTimeIn[i].GetDate()))
			{
				// create new bar
				BLB_ADD_BAR();
				barEndTime = 0;  // start at begining of day
				numBars = 0;
				trend = 0;
			}
			else 
			{
				if (barComplete)
				{
					// this tick creates a new bar
					BLB_ADD_BAR();
					BLB_ADD_LINEBREAK_LINE(o-numBars, o, lbOpen[o-numBars]);
				}
				else
				{
					// check if this tick starts a new bar - only time bars can do this
					bool newTimeBar = secPerBar != 0 && quoteTime >= barEndTime;
					if (newTimeBar && BLB_NEW_LB_BAR)
					{
						BLB_CHECK_TREND_CHANGE();
						BLB_ADD_BAR();
						BLB_ADD_LINEBREAK_LINE(o-numBars, o, lbOpen[o-numBars]);
					}
					else
					{
						BLB_UPDATE_BAR();
						if (newTimeBar)  // did not start new lb bar, but need to update bar end time stamp
							barEndTime = quoteTime + (secPerBar - (quoteTime % secPerBar));
					}
				}
			}

			// check if bar is complete - tick and volume bars can trigger after update
			if ((ticksPerBar != 0 && barTicks >= ticksPerBar) || 
				(volumePerBar != 0 && barVolume >= volumePerBar))
			{
				// restart underlying bar tracking, then check if new line break bar
				barTicks = 0;
				barVolume = 0;
				if (BLB_NEW_LB_BAR)
				{
					barComplete = true;
					BLB_CHECK_TREND_CHANGE();
				}
			}

			// finally update last bar info
			lastIndex = i;
			lbVolume = iVolume[i]; lbTicks = iTicks[i]; lbBidVol = iBidVol[i]; lbAskVol = iAskVol[i];
			lbUpTickVol = iUpTickVol[i]; lbDownTickVol = iDownTickVol[i]; lbBidTrades = iBidTrades[i]; lbAskTrades = iAskTrades[i];
		}
	}
	catch (char *ErrMsg){
		sc.AddMessageToLog(ErrMsg, 1);
	}
}

// remove macro defs
#undef BLB_ADD_BAR
#undef BLB_UPDATE_BAR
#undef BLB_ADD_LINEBREAK_LINE
#undef BLB_NEW_LB_BAR
#undef BLB_CHECK_TREND_CHANGE
