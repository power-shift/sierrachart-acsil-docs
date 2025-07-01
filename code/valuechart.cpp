
#include "sierrachart.h"
//created by David Stendahl //
// adapted for Sierra Chart by tcast //

SCSFExport scsf_ValueChart(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "Value Chart";
		sc.GraphDrawType = GDT_OHLCBAR;
		sc.AutoLoop = 1;

		sc.Subgraph[0].PrimaryColor = RGB(0,255,0);
		sc.Subgraph[1].PrimaryColor = RGB(0,255,0);
		sc.Subgraph[2].PrimaryColor = RGB(0,255,0);
		sc.Subgraph[3].PrimaryColor = RGB(0,255,0);

		sc.Subgraph[0].Name = "Open";
		sc.Subgraph[1].Name = "High";
		sc.Subgraph[2].Name = "Low";
		sc.Subgraph[3].Name = "Close";
		
		sc.Input[0].Name = "Period";
		sc.Input[0].SetInt(5);
		sc.Input[0].SetIntLimits(1, 10000);
		sc.FreeDLL=0;
		return;
	}
int i = sc.Index;
	int period = sc.Input[0].GetInt();
	sc.Subgraph[4][i] = (sc.BaseData[SC_HIGH][i] + sc.BaseData[SC_LOW][i])/2;
	sc.SimpleMovAvg(sc.Subgraph[4],sc.Subgraph[5],i,period);

	float VarAs = sc.Subgraph[5][i];
	sc.ATR(sc.BaseData,sc.Subgraph[6],sc.Subgraph[7],i,5,MOVAVGTYPE_SIMPLE);
	float Volatiliteit = sc.Subgraph[7][i]/period;
	sc.Subgraph[1][i] = (sc.BaseData[SC_HIGH][i] - VarAs)/Volatiliteit;
	sc.Subgraph[2][i] = (sc.BaseData[SC_LOW][i] - VarAs)/Volatiliteit;
	sc.Subgraph[3][i] = (sc.BaseData[SC_LAST][i] - VarAs)/Volatiliteit;

}
