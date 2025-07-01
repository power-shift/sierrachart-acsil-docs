#include "sierrachart.h"

/*==========================================================================*/

SCSFExport scsf_TriangularBollingerBands(SCStudyInterfaceRef sc)
{
	SCSubgraphRef BollingerUpperBand = sc.Subgraph[1];
	SCSubgraphRef BollingerLowerBand = sc.Subgraph[2];
	SCSubgraphRef BollingerMiddleBand = sc.Subgraph[3];
	
	SCSubgraphRef AtrTemp = sc.Subgraph[7];
	SCSubgraphRef StdTemp = sc.Subgraph[8];

	SCInputRef InputData = sc.Input[0];
	
	SCInputRef BollingerPeriod = sc.Input[3];
	SCInputRef BollingerStandardDeviations = sc.Input[4];
	
	if(sc.SetDefaults)
	{
		sc.GraphName = "Triangular Bollinger Bands";
		sc.StudyDescription = "Bollinger Bands based on a Triangular Moving Average";
		
		sc.GraphRegion = 0;		 
		sc.AutoLoop = true;
		sc.FreeDLL 		= 0;
		
		BollingerUpperBand.Name = "Bollinger Upper Band";
		BollingerUpperBand.DrawStyle = DRAWSTYLE_LINE;
		BollingerUpperBand.PrimaryColor = COLOR_BLACK;
		
		BollingerLowerBand.Name = "Bollnger Lower Band";
		BollingerLowerBand.DrawStyle = DRAWSTYLE_LINE;
		BollingerLowerBand.PrimaryColor = COLOR_BLACK;
		
		BollingerMiddleBand.Name = "Bollnger Middle Band";
		BollingerMiddleBand.DrawStyle = DRAWSTYLE_LINE;
		BollingerMiddleBand.PrimaryColor = COLOR_BLACK;
		
		InputData.Name = "Input Data";
		InputData.SetInputDataIndex(SC_LAST);
		
		BollingerPeriod.Name = "Bollinger Bands - Period";
		BollingerPeriod.SetInt(20);
		BollingerPeriod.SetIntLimits(1,1000);
		
		BollingerStandardDeviations.Name = "Bollinger Bands - Standard Deviations";
		BollingerStandardDeviations.SetFloat(2.0f);
		BollingerStandardDeviations.SetFloatLimits(.0001f,1000);
		
		return;
	}
	
	//Bollinger Standard Deviations
	sc.StdDeviation(sc.BaseDataIn[InputData.GetInputDataIndex()], StdTemp, BollingerPeriod.GetInt());
	
	//Band Calculations
	
	sc.TriangularMovingAverage(sc.BaseDataIn[InputData.GetInputDataIndex()], sc.Subgraph[10], BollingerPeriod.GetInt());

	//float TriangularMovingAverage = sc.Subgraph[10][sc.Index];
	
	BollingerMiddleBand[sc.Index] = sc.Subgraph[10][sc.Index];
		
	BollingerUpperBand[sc.Index] = BollingerMiddleBand[sc.Index] + (StdTemp[sc.Index]*BollingerStandardDeviations.GetFloat());
	BollingerLowerBand[sc.Index] = BollingerMiddleBand[sc.Index] - (StdTemp[sc.Index]*BollingerStandardDeviations.GetFloat());
}
