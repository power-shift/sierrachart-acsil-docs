#include <string>
#include "sierrachart.h"
#include "RobBooker.h"

#define EMPTY_VALUE 0

#define REFS \
	SCSubgraphRef graph_sell		= sc.Subgraph[0]; \
	SCSubgraphRef graph_sellAlt		= sc.Subgraph[1]; \
	SCSubgraphRef graph_sellAlt1	= sc.Subgraph[2]; \
	SCSubgraphRef graph_buy			= sc.Subgraph[3]; \
	SCSubgraphRef graph_buyAlt		= sc.Subgraph[4]; \
	SCSubgraphRef graph_buyAlt1		= sc.Subgraph[5]; \
	SCSubgraphRef graph_rsi			= sc.Subgraph[6]; \
	SCSubgraphRef graph_momentum	= sc.Subgraph[7]; \
	SCInputRef inp_candles_back		= sc.Input[0]; \
	SCInputRef inp_rsi_input		= sc.Input[1]; \
	SCInputRef inp_rsi_movavg		= sc.Input[2]; \
	SCInputRef inp_rsi_length		= sc.Input[3]; \
	SCInputRef inp_momentum_input	= sc.Input[4]; \
	SCInputRef inp_momentum_length	= sc.Input[5]; \
	SCInputRef inp_alert_id			= sc.Input[6]; \
	int& initialized				= sc.PersistVars->i1; \
	double &LastKDS					= sc.PersistVars->d1; \
	double &LastKDSA				= sc.PersistVars->d2; \
	double &LastKDSA2				= sc.PersistVars->d3; \
	double &LastKDB					= sc.PersistVars->d4; \
	double &LastKDBA				= sc.PersistVars->d5; \
	double &LastKDBA2				= sc.PersistVars->d6; \



namespace knoxville_divergence
{
;

void LineDraw(SCStudyInterfaceRef sc, int Start, int Finish, std::string BuySell, bool UseAlt, bool UseAlt2)
{
	REFS;

	double Slope;

	if(BuySell == "Buy")
	{
		Slope = (sc.BaseDataIn[SC_LOW][Start] - sc.BaseDataIn[SC_LOW][Finish]) / double(Start - Finish);
		double StartBuy = sc.BaseDataIn[SC_LOW][Start];

		for(int y = 0; y <= (Finish - Start); y++)
		{
			StartBuy += Slope;
			if(!UseAlt && !UseAlt2)	graph_buy    [Start+y] = (float)StartBuy;
			if( UseAlt)				graph_buyAlt [Start+y] = (float)StartBuy;
			if( UseAlt2)			graph_buyAlt1[Start+y] = (float)StartBuy;
		}
		for(int n = Start - 1; n > 0; n--)
		{
			if(!UseAlt && !UseAlt2 && graph_buy[n] == EMPTY_VALUE)	return;
			if( UseAlt && graph_buyAlt[n] == EMPTY_VALUE)			return;
			if( UseAlt2 && graph_buyAlt1[n] == EMPTY_VALUE)			return;

			if(!UseAlt && !UseAlt2)	graph_buy    [n] = EMPTY_VALUE;
			if( UseAlt)				graph_buyAlt [n] = EMPTY_VALUE;
			if( UseAlt2)			graph_buyAlt1[n] = EMPTY_VALUE;
		}
	}

	if(BuySell == "Sell")
	{
		Slope = (sc.BaseDataIn[SC_HIGH][Start] - sc.BaseDataIn[SC_HIGH][Finish]) / double(Start - Finish);
		double StartSell = sc.BaseDataIn[SC_HIGH][Start];

		for(int y = 0; y <= (Finish - Start); y++)
		{
			StartSell += Slope;
			if(!UseAlt && !UseAlt2)	graph_sell    [Start+y]	= (float)StartSell;
			if( UseAlt)				graph_sellAlt [Start+y]	= (float)StartSell;
			if( UseAlt2)			graph_sellAlt1[Start+y]	= (float)StartSell;
		}
		for(int n = Start - 1; n > 0; n--)
		{
			if(!UseAlt && !UseAlt2 && graph_sell[n] == EMPTY_VALUE)	return;
			if( UseAlt && graph_sellAlt[n] == EMPTY_VALUE)			return;
			if( UseAlt2 && graph_sellAlt1[n] == EMPTY_VALUE)		return;

			if(!UseAlt && !UseAlt2)	graph_sell    [n] = EMPTY_VALUE;
			if( UseAlt)				graph_sellAlt [n] = EMPTY_VALUE;
			if( UseAlt2)			graph_sellAlt1[n] = EMPTY_VALUE;
		}
	}
	return;
}

void RSISellCheck(SCStudyInterfaceRef sc)
{
	REFS;

	double RSIMain = graph_rsi[sc.Index];

	if(RSIMain < 50)
	{
		graph_sell[sc.Index] = 0;
		return;
	}

	for(int x = sc.Index; x >= sc.Index - 2; x--)
	{
		if(sc.BaseDataIn[SC_HIGH][x] > sc.BaseDataIn[SC_HIGH][sc.Index])
		{
			graph_sell[sc.Index] = 0;
			return;
		}
	}

	for(int y = sc.Index - 4; y >= (sc.Index - inp_candles_back.GetInt()); y--)
	{
		bool UseKDSAlt = false;
		bool UseKDSAlt1 = false;

		if(sc.BaseDateTimeIn[y].m_dt < LastKDS)
		{
			UseKDSAlt = true;
		}
		if(sc.BaseDateTimeIn[y].m_dt < LastKDSA)
		{
			UseKDSAlt  = false;
			UseKDSAlt1 = true;
		}
		if(sc.BaseDateTimeIn[y].m_dt < LastKDSA2)
		{
			UseKDSAlt1 = false;
		}

		if(y == (sc.Index - inp_candles_back.GetInt()))
		{
			graph_sell[sc.Index] = 0;
			return;
		}
		if(sc.BaseDataIn[SC_HIGH][y] > sc.BaseDataIn[SC_HIGH][sc.Index])
		{
			graph_sell[sc.Index] = 0;
			return;
		}

		int s = y;
		for(int z = y + 2; z >= y - 2; z--)
		{
			if(sc.BaseDataIn[SC_HIGH][z] > sc.BaseDataIn[SC_HIGH][y])
			{
				y--;
				break;
			}
		}

		if(s != y)
		{
			y++;
			continue;
		}

		bool OB = false;
		for(int k = sc.Index; k >= y; k--)
		{
			double RSIOB = graph_rsi[k];
			if(RSIOB > 70)
			{
				OB = true;
				break;
			}
		}

		if(OB == false)
			continue;

		double Mom1 = graph_momentum[sc.Index];
		double Mom2 = graph_momentum[y];

		if(Mom1 > Mom2)
			continue;

		LastKDS = sc.BaseDateTimeIn[sc.Index].m_dt;
		if(UseKDSAlt)
			LastKDSA = sc.BaseDateTimeIn[sc.Index].m_dt;
		if(UseKDSAlt1)
			LastKDSA2 = sc.BaseDateTimeIn[sc.Index].m_dt;

		LineDraw(sc, y, sc.Index, "Sell", UseKDSAlt, UseKDSAlt1);

		sc.SetAlert(inp_alert_id.GetAlertSoundNumber());

		return;
	}
}

void RSIBuyCheck(SCStudyInterfaceRef sc)
{
	REFS;

	double RSIMain = graph_rsi[sc.Index];

	if(RSIMain > 50)
	{
		graph_buy[sc.Index] = EMPTY_VALUE;
		return;
	}
	for(int x = sc.Index; x >= sc.Index - 2; x--)
	{
		if(sc.BaseDataIn[SC_LOW][x] < sc.BaseDataIn[SC_LOW][sc.Index])
		{
			graph_buy[sc.Index] = EMPTY_VALUE;
			return;
		}
	}

	for(int y = sc.Index - 4; y >= (sc.Index - inp_candles_back.GetInt()); y--)
	{
		bool UseKDBAlt = false;
		bool UseKDBAlt1 = false;

		if(sc.BaseDateTimeIn[y].m_dt < LastKDB)
		{
			UseKDBAlt = true;
		}
		if(sc.BaseDateTimeIn[y].m_dt < LastKDBA)
		{
			UseKDBAlt  = false;
			UseKDBAlt1 = true;
		}
		if(sc.BaseDateTimeIn[y].m_dt < LastKDBA2)
		{
			UseKDBAlt1 = false;
		}

		if(y == (sc.Index - inp_candles_back.GetInt()))
		{
			graph_buy[sc.Index] = EMPTY_VALUE;
			return;
		}

		if(sc.BaseDataIn[SC_LOW][y] < sc.BaseDataIn[SC_LOW][sc.Index])
		{
			graph_buy[sc.Index] = EMPTY_VALUE;
			return;
		}

		int s = y;
		for(int z = y + 2; z >= y - 2; z--)
		{
			if(sc.BaseDataIn[SC_LOW][z] < sc.BaseDataIn[SC_LOW][y])
			{
				y--;
				break;
			}
		}

		if(s != y)
		{
			y++;
			continue;
		}

		bool OB = false;
		for(int k = sc.Index; k >= y; k--)
		{
			double RSIOB = graph_rsi[k];
			if(RSIOB < 30)
			{
				OB = true;
				break;
			}
		}

		if(OB == false)
			continue;

		double Mom1 = graph_momentum[sc.Index];
		double Mom2 = graph_momentum[y];

		if(Mom1 < Mom2)
			continue;

		LastKDB = sc.BaseDateTimeIn[sc.Index].m_dt;
		if(UseKDBAlt)
			LastKDBA = sc.BaseDateTimeIn[sc.Index].m_dt;
		if(UseKDBAlt1)
			LastKDBA2 = sc.BaseDateTimeIn[sc.Index].m_dt;

		LineDraw(sc, y, sc.Index, "Buy", UseKDBAlt, UseKDBAlt1);

		sc.SetAlert(inp_alert_id.GetAlertSoundNumber());

		return;
	}
}

void process(SCStudyInterfaceRef sc)
{
	REFS;

	if (sc.SetDefaults)
	{
		sc.GraphName = "Knoxville Divergence";
		sc.StudyDescription = "";
		sc.AutoLoop = 1;  // true
		sc.GraphRegion = 0;
		sc.FreeDLL = FREE_DLL;

		//
		inp_candles_back.Name = "Candles Back";
		inp_candles_back.SetInt(30);  
		inp_candles_back.SetIntLimits(1,MAX_STUDY_LENGTH);

		// RSI
		inp_rsi_input.Name = "RSI Input Data";
		inp_rsi_input.SetInputDataIndex(SC_LAST);

		inp_rsi_length.Name ="RSI Length";
		inp_rsi_length.SetInt(21);  
		inp_rsi_length.SetIntLimits(1,MAX_STUDY_LENGTH);

		inp_rsi_movavg.Name = "RSI Moving Average Type";
		inp_rsi_movavg.SetMovAvgType(MOVAVGTYPE_SIMPLE);

		// momentum
		inp_momentum_input.Name = "Momentum Input Data";
		inp_momentum_input.SetInputDataIndex(SC_LAST);

		inp_momentum_length.Name ="Momentum Length";
		inp_momentum_length.SetInt(20);  
		inp_momentum_length.SetIntLimits(1,MAX_STUDY_LENGTH);

		// other

		inp_alert_id.Name = "Alert ID";
		inp_alert_id.SetAlertSoundNumber(0);

		// graphs
		//    sell
		graph_sell.Name = "Sell";
		graph_sell.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		graph_sell.LineStyle = LINESTYLE_SOLID;
		graph_sell.PrimaryColor = COLOR_RED;
		graph_sell.LineWidth = 2;
		graph_sell.DrawZeros = false;

		graph_sellAlt.Name = "Sell Alt";
		graph_sellAlt.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		graph_sellAlt.LineStyle = LINESTYLE_DOT;
		graph_sellAlt.PrimaryColor = COLOR_RED;
		graph_sellAlt.LineWidth = 2;
		graph_sellAlt.DrawZeros = false;

		graph_sellAlt1.Name = "Sell Alt 1";
		graph_sellAlt1.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		graph_sellAlt1.LineStyle = LINESTYLE_DASH;
		graph_sellAlt1.PrimaryColor = COLOR_RED;
		graph_sellAlt1.LineWidth = 2;
		graph_sellAlt1.DrawZeros = false;

		//    buy
		graph_buy.Name = "Buy";
		graph_buy.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		graph_buy.LineStyle = LINESTYLE_SOLID;
		graph_buy.PrimaryColor = COLOR_GREEN;
		graph_buy.LineWidth = 2;
		graph_buy.DrawZeros = false;

		graph_buyAlt.Name = "Buy Alt";
		graph_buyAlt.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		graph_buyAlt.LineStyle = LINESTYLE_DOT;
		graph_buyAlt.PrimaryColor = COLOR_GREEN;
		graph_buyAlt.LineWidth = 2;
		graph_buyAlt.DrawZeros = false;

		graph_buyAlt1.Name = "Buy Alt 1";
		graph_buyAlt1.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		graph_buyAlt1.LineStyle = LINESTYLE_DASH;
		graph_buyAlt1.PrimaryColor = COLOR_GREEN;
		graph_buyAlt1.LineWidth = 2;
		graph_buyAlt1.DrawZeros = false;

		return;
	}

	if (initialized == 0)
	{
		initialized = 1;
	}

	if (sc.LastCallToFunction)
	{
		return;
	}


	sc.RSI(sc.BaseDataIn[inp_rsi_input.GetInputDataIndex()], graph_rsi, inp_rsi_movavg.GetMovAvgType(), inp_rsi_length.GetInt());
	sc.Momentum(sc.BaseDataIn[inp_momentum_input.GetInputDataIndex()], graph_momentum, inp_momentum_length.GetInt());

	if(sc.Index > 0 && sc.GetBarHasClosedStatus() == BHCS_BAR_HAS_CLOSED)
	{
		if(inp_candles_back.GetInt() + 3 < sc.Index)
		{
			RSISellCheck(sc);
			RSIBuyCheck(sc);
		}
	}
}

}

