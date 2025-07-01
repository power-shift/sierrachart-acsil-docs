#include "sierrachart.h"

//SCDLLName("Volatility2") 

SCSFExport scsf_VolatilityTrend(SCStudyInterfaceRef sc)
{
	SCSubgraphRef VolatilityTrend = sc.Subgraph[0];
	SCSubgraphRef TrueRange = sc.Subgraph[1];
	SCSubgraphRef AverageTrueRange = sc.Subgraph[2];
	SCSubgraphRef Direction = sc.Subgraph[3];
	SCSubgraphRef DynamicPeriodLength = sc.Subgraph[4];
	SCSubgraphRef VolTrendUp = sc.Subgraph[5];
	SCSubgraphRef VolTrenDown = sc.Subgraph[6];

	SCInputRef ATRLength = sc.Input[0];
	SCInputRef ATRType = sc.Input[1];
	SCInputRef ATRMultiplier = sc.Input[2];
	SCInputRef MaxDynamicPeriod= sc.Input[3];
	SCInputRef DynamicPeriodDataInput = sc.Input[4];
	SCInputRef VolatilityTrendUp = sc.Input[5];
	SCInputRef VolatilityTrendDown = sc.Input[6];

	// Configuration
  	if (sc.SetDefaults)
 	{   
 		sc.GraphName = "Volatility Trend Indicator"; 
 		sc.StudyDescription = "Volatility Trend Indicator";
		sc.GraphRegion = 0;    // Zero based chart region number
		
		// During development set this flag to 1, so the DLL can be modified. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;

		sc.DrawZeros = 0;
		
		ATRLength.Name = "Average True Range Length";
		ATRLength.SetInt(21);
		ATRLength.SetIntLimits(1, MAX_STUDY_LENGTH);
		
		ATRType.Name = "ATR Moving Average Type";
		ATRType.SetMovAvgType(MOVAVGTYPE_WEIGHTED);

		ATRMultiplier.Name = "ATR Multiplier";
		ATRMultiplier.SetFloat(3);
		
		MaxDynamicPeriod.Name = "Max. Dynamic Period for Trend Calculation";
		MaxDynamicPeriod.SetInt(50);
		MaxDynamicPeriod.SetIntLimits(1, MAX_STUDY_LENGTH);

		DynamicPeriodDataInput.Name = "Dynamic Period Input Data";
		DynamicPeriodDataInput.SetInputDataIndex(SC_LAST);
		
		VolatilityTrendUp.Name="Above VolatilityTrend";
		VolatilityTrendUp.SetFloat(0.01f);
		
		VolatilityTrendDown.Name="Below VolatilityTrend";
		VolatilityTrendDown.SetFloat(0.01f);

		VolatilityTrend.Name = "Volatility Trend";
		VolatilityTrend.DrawStyle = DRAWSTYLE_LINE;
		VolatilityTrend.PrimaryColor = RGB(0, 128, 0); // green
		VolatilityTrend.SecondaryColor = RGB(128, 0, 0); // red
		VolatilityTrend.SecondaryColorUsed = 1;
		
		VolTrendUp.Name="above VolatilityTrend";
		VolTrendUp.DrawStyle=DRAWSTYLE_LINE;
		VolTrenDown.Name="below VolatilityTrend";
		VolTrenDown.DrawStyle=DRAWSTYLE_LINE;
		

		DynamicPeriodLength.Name = "Dynamic Period Length";
		DynamicPeriodLength.DrawStyle = DRAWSTYLE_IGNORE;
		
		sc.AutoLoop = 1;

 		return;
 	}   

	COLORREF UpTrendColor = VolatilityTrend.PrimaryColor;
	COLORREF DownTrendColor = VolatilityTrend.SecondaryColor;

	sc.DataStartIndex = ATRLength.GetInt()-1;

	// Data processing

	if (sc.Index < 1)
		return;

	sc.ATR(sc.BaseDataIn, TrueRange, AverageTrueRange,  ATRLength.GetInt(), ATRType.GetMovAvgType());

	if (sc.BaseDataIn[DynamicPeriodDataInput.GetInputDataIndex()][sc.Index] > VolatilityTrend[sc.Index-1])
        Direction[sc.Index] = 1; // uptrend
	else
		Direction[sc.Index] = -1; // downtrend

	int Period = (int)(DynamicPeriodLength[sc.Index-1]+0.5f);

	if (Direction[sc.Index] != Direction[sc.Index-1]) // Different trend than previous
		Period = 0; 

	if (Period < MaxDynamicPeriod.GetInt())
		Period++;
    
    DynamicPeriodLength[sc.Index] = (float)Period;		

	if (Direction[sc.Index] == 1) // uptrend
	{
		VolatilityTrend[sc.Index] = sc.GetHighest(sc.BaseDataIn[DynamicPeriodDataInput.GetInputDataIndex()], Period) - 
															ATRMultiplier.GetFloat() * AverageTrueRange[sc.Index];
		VolatilityTrend.DataColor[sc.Index] = UpTrendColor;
	}
	else // downtrend
	{
		VolatilityTrend[sc.Index] = sc.GetLowest(sc.BaseDataIn[DynamicPeriodDataInput.GetInputDataIndex()],  Period) + 
															ATRMultiplier.GetFloat() * AverageTrueRange[sc.Index];    									
		VolatilityTrend.DataColor[sc.Index] = DownTrendColor;
	}
					VolTrendUp[sc.Index]=VolatilityTrend[sc.Index]+VolatilityTrendUp.GetFloat();	
				VolTrenDown[sc.Index]=VolatilityTrend[sc.Index]-VolatilityTrendDown.GetFloat();
	
}