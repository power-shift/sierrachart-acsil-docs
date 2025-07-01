//
// BetterRenko
//
// written by aslan
//
// 20101215 - initial version for SC
// 20110111 - fixed OHLC averages, removed showWicks to allow other bar types
//
#include "sierrachart.h"

//SCDLLName("BetterRenko")



inline void br_MoveLimits(SCStudyGraphRef sc, float high, float low, float brickSize, int revMult, float& renkoHigh, float& renkoLow)
{
	if (sc.FormattedEvaluate(high, sc.ValueFormat, GREATER_EQUAL_OPERATOR, renkoHigh, sc.ValueFormat))
	{
		do
		{
			renkoHigh += brickSize;
			renkoLow  = renkoHigh - ((revMult+1) * brickSize);
		} while (sc.FormattedEvaluate(high, sc.ValueFormat, GREATER_OPERATOR, renkoHigh, sc.ValueFormat));  // stops if price in range, including edge
	}
	else
	{
		do
		{
			renkoLow -= brickSize;
			renkoHigh = renkoLow + ((revMult+1) * brickSize);
		} while (sc.FormattedEvaluate(low, sc.ValueFormat, LESS_OPERATOR, renkoLow, sc.ValueFormat));
	}
}

inline void br_CheckBarComplete(SCStudyGraphRef sc, float high, float low, float brickSize, int revMult, float& renkoHigh, float& renkoLow, int& barComplete)
{
	if (sc.FormattedEvaluate(high, sc.ValueFormat, EQUAL_OPERATOR, renkoHigh, sc.ValueFormat) || 
		sc.FormattedEvaluate(low,  sc.ValueFormat, EQUAL_OPERATOR, renkoLow,  sc.ValueFormat))
	{
		barComplete = true;
		br_MoveLimits(sc, high, low, brickSize, revMult, renkoHigh, renkoLow);  // will move limits once since equal
	}
	else barComplete = false;
}

inline bool br_RangeExceeded(SCStudyGraphRef sc, float high, float low, float& renkoHigh, float& renkoLow)
{
	return 	sc.FormattedEvaluate(high, sc.ValueFormat, GREATER_OPERATOR, renkoHigh, sc.ValueFormat) || 
			sc.FormattedEvaluate(low,  sc.ValueFormat, LESS_OPERATOR,    renkoLow,  sc.ValueFormat);
}


// macros for bar creation/updates, handles tick or bar inputs
#define UPDATE_OPENS()										\
	/* set renkoOpen based on brick size and price action */\
	if (Close[o] > Open[o])									\
		RenkoOpen[o] = max(Close[o] - brickSize, Low[o]);	\
	else													\
		RenkoOpen[o] = min(Close[o] + brickSize, High[o]);	\
															\
	/* adjust open to show RenkoOpen instead of real open */\
	if (showRealOpen.GetYesNo() == 0)						\
	{														\
		float temp = Open[o];								\
		Open[o] = RenkoOpen[o];								\
		RenkoOpen[o] = temp;								\
	}														\

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
	AskTrades[o] = iAskTrades[i];							\
	RenkoOpen[o] = iOpen[i]

#define UPDATE_BAR()										\
	if (iHigh[i] > High[o]) High[o] = iHigh[i];				\
	if (iLow[i] < Low[o])   Low[o]  = iLow[i];				\
	Close[o] = iClose[i];									\
	Volume[o] += iVolume[i];								\
	Ticks[o] += iTicks[i];									\
	sc.CalculateOHLCAverages(o);							\
	BidVol[o] += iBidVol[i];								\
	AskVol[o] += iAskVol[i];								\
	UpTickVol[o] += iUpTickVol[i];							\
	DownTickVol[o] += iDownTickVol[i];						\
	BidTrades[o] += iBidTrades[i];							\
	AskTrades[o] += iAskTrades[i];							\
	RenkoOpen[o] = iClose[i]


SCSFExport scsf_BetterRenko(SCStudyGraphRef sc)
{
	// input refs
	SCInputRef brickSizeTicks    = sc.Input[0];
	SCInputRef alignToBrickSize  = sc.Input[1];
	SCInputRef showRealOpen      = sc.Input[2];
	SCInputRef reverseMultiplier = sc.Input[3];

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
	SCSubgraphRef RenkoOpen   = sc.Subgraph[15];  // Renko Open or True Open based on input value


	// Set configuration variables
	if (sc.SetDefaults)
	{
		// Set the defaults
		sc.GraphName = "BetterRenko";
		sc.StudyDescription = "BetterRenko custom chart. <a href=""http://www.sierrachart.com/supportboard/showthread.php?t=29758"">Discussion subtopic (BetterRenko Custom Chart)</a>";
		
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
		brickSizeTicks.Name = "Brick size (ticks):";
		brickSizeTicks.SetInt(4);
		alignToBrickSize.Name = "Align to brick size:";
		alignToBrickSize.SetYesNo(1);
		showRealOpen.Name = "Show real Open (vs Renko Open):";
		showRealOpen.SetYesNo(0);
		reverseMultiplier.Name = "Reverse multiplier (number of bricks):";
		reverseMultiplier.SetInt(2);
		reverseMultiplier.SetIntLimits(1, 20);

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

		RenkoOpen.Name = "Renko/True Open";
		RenkoOpen.DrawStyle = DRAWSTYLE_IGNORE;

		return;
	}

	try
	{
		long i = 0;		// input  index - underlying chart
		long o = 0;		// output index - renko chart
		float cum = 0;  // calc cumulative delta

		// refs to persistent vars
		float& brickSize   = sc.PersistVars->f1;  // brickSize in terms of price
		float& renkoHigh   = sc.PersistVars->f2;  // renkoHigh
		float& renkoLow    = sc.PersistVars->f3;  // renkoLow
		int&   lastIndex   = sc.PersistVars->i1;  // lastIndex processed
		int&   barComplete = sc.PersistVars->i2;  // barComplete

		if (sc.UpdateStartIndex == 0)
		{
			// clear existing chart data
			sc.ResizeArrays(0);

			// init state i.e. persist vars
			brickSize = sc.RoundToTickSize(brickSizeTicks.GetInt() * sc.TickSize, sc.TickSize);
			lastIndex = -1;
			barComplete = false;

			sc.ValueFormat = sc.BaseGraphValueFormat;
			sc.GraphName.Format("BetterRenko %i", brickSizeTicks.GetInt());

			RenkoOpen.Name = showRealOpen.GetYesNo() ? "True Open" : "Renko Open";
		}

		// do data processing
		o = sc.OutArraySize - 1;


		for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
		{
			if (i == lastIndex) continue;  // block handling the same tick multiple times

			// starting new bar at session boundary makes sure you have the same bars
			// reguardless of the first date that is loaded in the chart
			// Note: using date change instead of session boundary
			if (i == 0 || (sc.BaseDateTimeIn[i-1].GetDate() != sc.BaseDateTimeIn[i].GetDate()))
			{
				// create new bar
				if (i != 0) {
					UPDATE_OPENS();
				}
				ADD_BAR();
				float mod = !alignToBrickSize.GetYesNo() ? brickSize : sc.RoundToTickSize(fmod(Close[o], brickSize), sc.TickSize);
				float mid = sc.FormattedEvaluate(mod, sc.ValueFormat, EQUAL_OPERATOR, brickSize, sc.ValueFormat) ? Close[o] : Close[o] - mod;
				renkoHigh = mid + brickSize;
				renkoLow  = mid - brickSize;
				barComplete = false;
			}
			else 
			{
				if (barComplete)
				{
					// this tick creates a new bar
					UPDATE_OPENS();
					ADD_BAR();
					if (br_RangeExceeded(sc, High[o], Low[o], renkoHigh, renkoLow))
						br_MoveLimits(sc, High[o], Low[o], brickSize, reverseMultiplier.GetInt(), renkoHigh, renkoLow);
				}
				else
				{
					if (br_RangeExceeded(sc, iHigh[i], iLow[i], renkoHigh, renkoLow))
					{
						UPDATE_OPENS();
						ADD_BAR();
						br_MoveLimits(sc, High[o], Low[o], brickSize, reverseMultiplier.GetInt(), renkoHigh, renkoLow);
					}
					else
					{
						UPDATE_BAR();
					}
				}
				br_CheckBarComplete(sc, High[o], Low[o], brickSize, reverseMultiplier.GetInt(), renkoHigh, renkoLow, barComplete);
			}
			lastIndex = i;
		}
	}
	catch (char *ErrMsg){
		sc.AddMessageToLog(ErrMsg, 1);
	}
}
