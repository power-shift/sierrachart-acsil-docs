#include "sierrachart.h"
#include "RobBooker.h"


#define REFS \
	SCSubgraphRef graph_long		= sc.Subgraph[0]; \
	SCSubgraphRef graph_short		= sc.Subgraph[1]; \
	SCSubgraphRef graph_macd		= sc.Subgraph[2]; \
	SCSubgraphRef graph_stoch		= sc.Subgraph[3]; \
	int& initialized				= sc.PersistVars->i1; \
	SCInputRef inp_macd_input		= sc.Input[0]; \
	SCInputRef inp_macd_fast_ma		= sc.Input[1]; \
	SCInputRef inp_macd_slow_ma		= sc.Input[2]; \
	SCInputRef inp_macd_len			= sc.Input[3]; \
	SCInputRef inp_macd_movavg		= sc.Input[4]; \
	SCInputRef inp_stoch_fastk		= sc.Input[5]; \
	SCInputRef inp_stoch_fastd		= sc.Input[6]; \
	SCInputRef inp_stoch_slowd		= sc.Input[7]; \
	SCInputRef inp_stoch_movavg		= sc.Input[8]; \
	SCInputRef inp_stoch_upper		= sc.Input[9]; \
	SCInputRef inp_stoch_lower		= sc.Input[10]; \
	SCInputRef inp_offset			= sc.Input[11]; \
	SCInputRef inp_alert_id			= sc.Input[12]; \


namespace reversal_arrows
{
;


void process(SCStudyInterfaceRef sc)
{
	REFS;

	if (sc.SetDefaults)
	{
		sc.GraphName = "Reversal Arrows";
		sc.StudyDescription = "";
		sc.AutoLoop = 1;  // true
		sc.GraphRegion = 0;
		sc.FreeDLL = FREE_DLL;

		// MACD
		inp_macd_input.Name = "MACD Input Data";
		inp_macd_input.SetInputDataIndex(SC_LAST);

		inp_macd_fast_ma.Name ="MACD Fast Moving Average Length";
		inp_macd_fast_ma.SetInt(12);  
		inp_macd_fast_ma.SetIntLimits(1,MAX_STUDY_LENGTH);

		inp_macd_slow_ma.Name = "MACD Slow Moving Average Length";
		inp_macd_slow_ma.SetInt(26);  
		inp_macd_slow_ma.SetIntLimits(1,MAX_STUDY_LENGTH);

		inp_macd_len.Name = "MACD Moving Average Length";
		inp_macd_len.SetInt(9);   
		inp_macd_len.SetIntLimits(1,MAX_STUDY_LENGTH);

		inp_macd_movavg.Name = "MACD Moving Average Type";
		inp_macd_movavg.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);

		// Stochastic
		inp_stoch_fastk.Name = "Stochastic Fast %K Length";
		inp_stoch_fastk.SetInt(70);
		inp_stoch_fastk.SetIntLimits(1,MAX_STUDY_LENGTH);

		inp_stoch_fastd.Name = "Stochastic Fast %D Length (Slow %K)";
		inp_stoch_fastd.SetInt(10);
		inp_stoch_fastd.SetIntLimits(1,MAX_STUDY_LENGTH);

		inp_stoch_slowd.Name = "Stochastic Slow %D Length";
		inp_stoch_slowd.SetInt(10);
		inp_stoch_slowd.SetIntLimits(1,MAX_STUDY_LENGTH);

		inp_stoch_upper.Name = "Stochastic Upper Line Value";
		inp_stoch_upper.SetFloat(70);

		inp_stoch_lower.Name = "Stochastic Lower Line Value";
		inp_stoch_lower.SetFloat(30);

		inp_stoch_movavg.Name = "Stochastic Moving Average Type";
		inp_stoch_movavg.SetMovAvgType(MOVAVGTYPE_SIMPLE);

		// other
		inp_offset.Name = "Arrow Offset";
		inp_offset.SetInt(5);

		inp_alert_id.Name = "Alert ID";
		inp_alert_id.SetAlertSoundNumber(0);

		// graphs
		graph_long.Name = "Long";
		graph_long.DrawStyle = DRAWSTYLE_ARROWUP;
		graph_long.PrimaryColor = COLOR_GREEN;
		graph_long.LineWidth = 2;
		graph_long.DrawZeros = false;

		graph_short.Name = "Short";
		graph_short.DrawStyle = DRAWSTYLE_ARROWDOWN;
		graph_short.PrimaryColor = COLOR_RED;
		graph_short.LineWidth = 2;
		graph_short.DrawZeros = false;

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

	if (sc.Index == 0)
	{
		;
	}

	sc.MACD(sc.BaseData[inp_macd_input.GetInputDataIndex()], graph_macd, inp_macd_fast_ma.GetInt(), inp_macd_slow_ma.GetInt(), inp_macd_len.GetInt(), inp_macd_movavg.GetMovAvgType());
	sc.Stochastic(sc.BaseDataIn, graph_stoch, inp_stoch_fastk.GetInt(), inp_stoch_fastd.GetInt(), inp_stoch_slowd.GetInt(), inp_stoch_movavg.GetMovAvgType());

	if(sc.Index > 0 && sc.GetBarHasClosedStatus() == BHCS_BAR_HAS_CLOSED)
	{
		float MACD = graph_macd[sc.Index];
		float MACD1 = graph_macd[sc.Index - 1];
		float Stoch = graph_stoch[sc.Index];

		if(MACD1 > 0 && MACD < 0 && Stoch > inp_stoch_upper.GetFloat())
		{
			graph_short[sc.Index] = sc.BaseData[SC_HIGH][sc.Index] + inp_offset.GetInt() * sc.TickSize;
			sc.SetAlert(inp_alert_id.GetAlertSoundNumber());
		}

		if(MACD1 < 0 && MACD > 0 && Stoch < inp_stoch_lower.GetFloat())
		{
			graph_long[sc.Index] = sc.BaseData[SC_LOW][sc.Index] - inp_offset.GetInt() * sc.TickSize;
			sc.SetAlert(inp_alert_id.GetAlertSoundNumber());
		}
	}
}




}

