#include "sierrachart.h"

//SCDLLName("Choppiness") 
/*==========================================================================*/
SCSFExport scsf_Choppiness(SCStudyInterfaceRef sc)
{
	SCSubgraphRef Choppy = sc.Subgraph[0];
	
	SCInputRef InputData = sc.Input[0];
	SCInputRef period = sc.Input[1];	
	
	if (sc.SetDefaults)
	{
		sc.GraphName = "Choppiness";
						
		sc.AutoLoop = true;
		sc.FreeDLL = 0;
				
		Choppy.Name = "Choppiness";
		Choppy.LineWidth = 1;
		
		period.Name = "Period";
		period.SetInt(14);
		period.SetIntLimits(1, MAX_STUDY_LENGTH);
		
		InputData.Name = "Input Data";
		InputData.SetInputDataIndex(SC_LAST);
			
		return;
	}
	// Do data processing
	//sc.DataStartIndex = period.GetInt();
	if (sc.Index > period.GetInt())
	
	{
	
	sc.Highest(sc.BaseDataIn[SC_HIGH], sc.Subgraph[10], period.GetInt());
	float Highest = sc.Subgraph[10][sc.Index];
	
	sc.Lowest(sc.BaseDataIn[SC_LOW], sc.Subgraph[11], period.GetInt());
	float Lowest = sc.Subgraph[11][sc.Index];
	
	sc.ATR(sc.BaseDataIn, sc.Subgraph[12], period.GetInt(), MOVAVGTYPE_SIMPLE);
	
	sc.Summation(sc.Subgraph[12], sc.Subgraph[13], period.GetInt());
	float Summation = sc.Subgraph[13][sc.Index];
	
	Choppy[sc.Index] = 100 * log10(Summation/(Highest-Lowest)) / log10((float)period.GetInt());	
		
	}
}
