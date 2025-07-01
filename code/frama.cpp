#include "sierrachart.h"


SCSFExport scsf_FRAMA (SCStudyGraphRef sc)
{
	SCFloatArrayRef High = sc.BaseData[SC_HIGH];
	SCFloatArrayRef Low = sc.BaseData[SC_LOW];
	SCFloatArrayRef AvgPrice = sc.BaseData[SC_HL];

	if (sc.SetDefaults)
	{
		sc.GraphName = "FRAMA";
		sc.GraphRegion = 0;
		sc.FreeDLL = 0;

		sc.AutoLoop = 0;

		sc.Subgraph[0].Name = "FRAMA";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[0].LineWidth = 2;
		sc.Subgraph[0].PrimaryColor = RGB(192,0,0);
		
		sc.Input[0].Name = "Length";
		sc.Input[0].SetInt(16);
		sc.Input[0].SetIntLimits(2, 1000);
		return;
	}

	float n1, n2, n3, dimen, alpha;
	int n = sc.Input[0].GetInt();
	if (n % 2 != 0) n++; //force n to even number

	for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		if (i < n) sc.Subgraph[0][i] = AvgPrice[i];
		else
		{
			n1 = (sc.GetHighest(High, i, n/2) - sc.GetLowest(Low, i, n/2)) / (n/2);
			n2 = (sc.GetHighest(High, i - n/2, n/2) - sc.GetLowest(Low, i - n/2, n/2)) / (n/2);
			n3 = (sc.GetHighest(High, i, n) - sc.GetLowest(Low, i, n)) / n;
			dimen = (logf(n1 + n2) - logf(n3)) / logf(2);
			alpha = exp(-4.6 * (dimen - 1));

			if (alpha < 0.01)
				alpha = 0.01f;

			if (alpha > 1)
				alpha = 1;

			sc.Subgraph[0][i] = alpha * AvgPrice[i] + (1 - alpha) * sc.Subgraph[0][i - 1];
		}
	}
}
