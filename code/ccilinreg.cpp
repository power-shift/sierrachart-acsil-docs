#include "sierrachart.h"

//SCDLLName("CCILinReg") 

SCFloatArrayRef CCI_S(SCStudyGraphRef sc, SCFloatArrayRef In, SCFloatArrayRef CCIOut, int Index, int Length, float Multiplier)
{
	if (Length < 1)
		return CCIOut;
	
	SCFloatArrayRef SMAOut = sc.Subgraph[Index];
	sc.LinearRegressionIndicator(In, SMAOut, Index, Length);
	//SimpleMovAvg_S(In, SMAOut, Index, Length);
	
    float Num0 = 0;
	for (int j = Index; j > Index - Length && j >= 0; j--)
		Num0 += fabs(SMAOut[Index] - In[j]);
	
	Num0 /= Length;
	
	CCIOut[Index] = (In[Index] - SMAOut[Index]) / (Num0 * Multiplier);
	
	return CCIOut;
}

/*==========================================================================*/
SCSFExport scsf_CCILinReg(SCStudyInterfaceRef sc)
{
	SCSubgraphRef CCI = sc.Subgraph[0];
	
	SCSubgraphRef L1 = sc.Subgraph[1];
	SCSubgraphRef L2 = sc.Subgraph[2];
	SCSubgraphRef L3 = sc.Subgraph[3];
	SCSubgraphRef L4 = sc.Subgraph[4];
	SCSubgraphRef L5 = sc.Subgraph[5];	
	
	SCInputRef InputData = sc.Input[0];
	SCInputRef Multiplier = sc.Input[1];	
	SCInputRef period = sc.Input[2];	
	
	SCInputRef Line1 = sc.Input[3];
	SCInputRef Line2 = sc.Input[4];
	SCInputRef Line3 = sc.Input[5];
	SCInputRef Line4 = sc.Input[6];
	SCInputRef Line5 = sc.Input[7];	
	
	if (sc.SetDefaults)
	{
		sc.GraphName = "CCI - Linear Regression";
						
		sc.AutoLoop = true;
		sc.FreeDLL = 0;
		sc.DrawZeros	= 1;
				
		CCI.Name = "CCI - Linear Regression";
		CCI.LineWidth = 1;
		CCI.DrawStyle = DRAWSTYLE_LINE;
		CCI.PrimaryColor = RGB(0,0,0);
				
		L1.Name = "Line 1";
		L1.LineWidth = 1;
		L1.DrawStyle = DRAWSTYLE_LINE;
		L1.PrimaryColor = RGB(64,0,0);
		
		L2.Name = "Line 2";
		L2.LineWidth = 1;
		L2.DrawStyle = DRAWSTYLE_LINE;
		L2.PrimaryColor = RGB(255,0,0);
				
		L3.Name = "Line 3";
		L3.LineWidth = 1;
		L3.DrawStyle = DRAWSTYLE_LINE;
		L3.PrimaryColor = RGB(0,0,0);
				
		L4.Name = "Line 4";
		L4.LineWidth = 1;
		L4.DrawStyle = DRAWSTYLE_LINE;
		L4.PrimaryColor = RGB(255,0,0);
				
		L5.Name = "Line 5";
		L5.LineWidth = 1;
		L5.DrawStyle = DRAWSTYLE_LINE;
		L5.PrimaryColor = RGB(64,0,0);
		
		period.Name = "CCI Period";
		period.SetInt(14);
		period.SetIntLimits(1, 9999);
	
		Line1.Name = "Line 1";
		Line1.SetInt(200);
		
		Line2.Name = "Line 2";
		Line2.SetInt(100);
		
		Line3.Name = "Line 3";
		Line3.SetInt(0);
		
		Line4.Name = "Line 4";
		Line4.SetInt(-100);
		
		Line5.Name = "Line 5";
		Line5.SetInt(-200);
		
		InputData.Name = "Input Data";
		InputData.SetInputDataIndex(SC_LAST);
		
		Multiplier.Name = "Multiplier";
		Multiplier.SetFloat(0.015f);
		Multiplier.SetFloatLimits(0, 1);
	
		return;
	}
	// Do data processing
	sc.DataStartIndex = period.GetInt();
	if (sc.Index > period.GetInt())
	
	{
	
	CCI_S(sc, sc.BaseData[InputData.GetInputDataIndex()], CCI, sc.Index, period.GetInt(), Multiplier.GetFloat());
	
	L1[sc.Index] = Line1.GetInt();
	L2[sc.Index] = Line2.GetInt();
	L3[sc.Index] = Line3.GetInt();
	L4[sc.Index] = Line4.GetInt();
	L5[sc.Index] = Line5.GetInt();
		
	}
}
