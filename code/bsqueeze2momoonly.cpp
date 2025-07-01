#include "sierrachart.h"

//SCDLLName("BSqueeze2MomoOnly") 
/*==========================================================================*/
SCSFExport scsf_BSqueeze2MomoOnly(SCStudyInterfaceRef sc)
{
	SCSubgraphRef BollingerSqueezeSubgraph = sc.Subgraph[0];
	
	SCInputRef InputMomentumLength = sc.Input[0];

	if (sc.SetDefaults)
	{
		sc.GraphName="Bollinger Squeeze 2 Momo only";
		
		// Subgraphs
		BollingerSqueezeSubgraph.Name = "Momentum Avg";
		BollingerSqueezeSubgraph.DrawStyle = DRAWSTYLE_BAR;
		BollingerSqueezeSubgraph.PrimaryColor = RGB(0,255,0);
		BollingerSqueezeSubgraph.SecondaryColor = RGB(255,0,0);
		BollingerSqueezeSubgraph.SecondaryColorUsed = true;

		// Data Inputs
		InputMomentumLength.Name = "Momentum Length";
		InputMomentumLength.SetInt(20);
		InputMomentumLength.SetIntLimits(1, MAX_STUDY_LENGTH);

		sc.AutoLoop = 1;
		sc.GraphRegion = 1;
		sc.ValueFormat = 3;
		sc.FreeDLL = 0;

		return;
	}

	int MomentumLength = InputMomentumLength.GetInt();

	if ((sc.Index < MomentumLength))
		return;

	// Calculate BollingerSqueeze: EMA(Base[LAST][Index] - Base[LAST][Index - MomentumLength]). Use Arrays[0] for first calculation.
	BollingerSqueezeSubgraph.Arrays[0][sc.Index] = 
		sc.Close[sc.Index] - sc.Close[sc.Index - MomentumLength];
	sc.ExponentialMovAvg(BollingerSqueezeSubgraph.Arrays[0], BollingerSqueezeSubgraph, MomentumLength);
	
	if ((BollingerSqueezeSubgraph[sc.Index] > 0) && 
		(BollingerSqueezeSubgraph[sc.Index] >= BollingerSqueezeSubgraph[sc.Index-1]))
		BollingerSqueezeSubgraph.DataColor[sc.Index] = BollingerSqueezeSubgraph.PrimaryColor;
	else if ((BollingerSqueezeSubgraph[sc.Index] > 0) && 
		(BollingerSqueezeSubgraph[sc.Index] < BollingerSqueezeSubgraph[sc.Index-1]))
	{
		BollingerSqueezeSubgraph.DataColor[sc.Index] = 
			RGB(GetRValue(BollingerSqueezeSubgraph.PrimaryColor)/2, 
			GetGValue(BollingerSqueezeSubgraph.PrimaryColor)/2, 
			GetBValue(BollingerSqueezeSubgraph.PrimaryColor)/2);
	}
	else if ((BollingerSqueezeSubgraph[sc.Index] < 0) && 
		(BollingerSqueezeSubgraph[sc.Index] <= BollingerSqueezeSubgraph[sc.Index-1])) 
		BollingerSqueezeSubgraph.DataColor[sc.Index] = BollingerSqueezeSubgraph.SecondaryColor;
	else if ((BollingerSqueezeSubgraph[sc.Index] < 0) && 
		(BollingerSqueezeSubgraph[sc.Index] > BollingerSqueezeSubgraph[sc.Index-1]))
	{
		BollingerSqueezeSubgraph.DataColor[sc.Index] = 
			RGB(GetRValue(BollingerSqueezeSubgraph.SecondaryColor)/2, 
			GetGValue(BollingerSqueezeSubgraph.SecondaryColor)/2, 
			GetBValue(BollingerSqueezeSubgraph.SecondaryColor)/2);
	}

}
