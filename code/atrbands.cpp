// The top of every source code file must include this line
#include "sierrachart.h"


//*****************************************************************************
// 06/22/13. ATRBands Version 1.0. In response to Sierra support forum question
// http://www.sierrachart.com/SupportBoard.php?ThreadID=1763
// Compiled with MSVS 2010 Pro with SC v990 headers.
// Tested with SC v990
// Support Forum user: StevieD
//******************************************************************************


SCSFExport scsf_ATRBands(SCStudyGraphRef sc)
{
	// Section 1 - Set the configuration variables
	
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults
		
		sc.GraphName = "ATRBands";
		
		sc.StudyDescription = "ATRBands from Active Trader Magazine, July 2013";
		
		sc.AutoLoop = 1;  // true
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		sc.GraphRegion = 0;
		sc.ValueFormat = VALUEFORMAT_INHERITED;
		
		sc.Input[0].Name = "ATR/MA Length";
		sc.Input[0].SetInt(21);  
		sc.Input[0].SetIntLimits(1, 500); 
		sc.Input[0].SetDescription("MA Length.<br>\
									Displays as the Mid-Band and used to calculate ATR value."); 
		
		sc.Input[1].Name = "ATR/MA Type";
		sc.Input[1].SetMovAvgType(MOVAVGTYPE_SIMPLE);
		sc.Input[1].SetDescription("MA Type.<br>\
								   Displays as the Mid-Band and used to calculate ATR value."); 

		sc.Input[2].Name = "Bands Multiplier ... 1 = 100%";
		sc.Input[2].SetFloat(1.5f);
		sc.Input[2].SetFloatLimits(0.1f, 10.0f);
		sc.Input[2].SetDescription("Upper Band = MA + (ATR * MULTIPLIER)<br>\
								   Lower Band = MA - (ATR * MULTIPLIER<br>\
								   Band calculations are rounded to nearest tick size.<br>\
								   Accepts values 0.1 (10%) to 10.0 (1000%)<br>\
								   ATR Value is available in the chart/tool windows only."); 

		sc.Subgraph[0].Name = "ATR/MA";
		sc.Subgraph[0].PrimaryColor = COLOR_RED; 
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;	
		sc.Subgraph[0].LineWidth = 2;

		// Named but ignored. For tool value window only.
		// This study draws on the main price graph, not a region.
		// Unless ATR value is similar to price scale, chart will distort, as it should.
		sc.Subgraph[1].Name = "ATR Value";
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_IGNORE;	
		
		sc.Subgraph[2].Name = "Upper Band";
		sc.Subgraph[2].PrimaryColor = COLOR_MEDIUMPURPLE; 
		sc.Subgraph[2].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[2].LineStyle = LINESTYLE_DASH; 
		sc.Subgraph[2].LineWidth = 2;

		sc.Subgraph[3].Name = "Lower Band";
		sc.Subgraph[3].PrimaryColor = COLOR_MEDIUMPURPLE; 
		sc.Subgraph[3].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[3].LineStyle = LINESTYLE_DASH; 
		sc.Subgraph[3].LineWidth = 2;

		return;
	}
	
	
	// Section 2 - Do data processing

	sc.MovingAverage(sc.BaseDataIn[SC_LAST],sc.Subgraph[0],sc.Input[1].GetMovAvgType(),sc.Input[0].GetInt());
	
	sc.ATR(sc.BaseDataIn, sc.Subgraph[1], sc.Input[0].GetInt(), sc.Input[1].GetMovAvgType());
	
	//upper band
	sc.Subgraph[2][sc.Index] = sc.RoundToTickSize(sc.Subgraph[0][sc.Index] + (sc.Subgraph[1][sc.Index] * sc.Input[2].GetFloat()), sc.TickSize);
	//lower band
	sc.Subgraph[3][sc.Index] = sc.RoundToTickSize(sc.Subgraph[0][sc.Index] - (sc.Subgraph[1][sc.Index] * sc.Input[2].GetFloat()), sc.TickSize);
	
	
}


