// The top of every source code file must include this line
#include "sierrachart.h"



SCSFExport scsf_BidAskArrow2(SCStudyInterfaceRef sc)
{


	if (sc.SetDefaults)
	{


		sc.UpdateAlways = 1;
		sc.GraphName = "Bid Ask Arrow 2";
		sc.StudyDescription = "This study draws an arrow in the fill space and changes color depending on the bid or ask price.  Make sure the chart Tick Size setting is correct.";
		sc.DrawZeros = 0;
		sc.GraphRegion = 0;
		sc.AutoLoop = 0;

		sc.FreeDLL = 0;



		return;
	}
	
	// Do data processing
	float TICK;
	TICK=sc.TickSize;
	s_UseTool All_Tool;
	float CurrentPrice;
	float BidPrice;
	float AskPrice;
	int Color=0;  //1=red 2=green 3=white
	
	BidPrice = sc.SymbolData->BidDOM[0].Price;
	AskPrice = sc.SymbolData->AskDOM[0].Price;
	//CurrentPrice=sc.BaseData[SC_LAST][sc.Index];
	CurrentPrice=sc.SymbolData->LastTradePrice;
	
	if (CurrentPrice == BidPrice) Color = 1;
	
	else  Color= 2;
	
	if (BidPrice == AskPrice) Color = 3;

		
		//Last price traded arrow      //1=red 2=green 3=white  
		All_Tool.Clear();
		All_Tool.ChartNumber = sc.ChartNumber;
		All_Tool.DrawingType = DRAWING_TEXT;
		All_Tool.LineNumber = 2589;
		All_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
		All_Tool.FontSize=18;
		All_Tool.FontBold=1;
		All_Tool.TextAlignment=DT_VCENTER|DT_CENTER;
	
		All_Tool.BeginDateTime = -1;
		All_Tool.BeginValue = CurrentPrice;
		
		if (Color == 1 )   
			All_Tool.Color = RGB(255,0,0);    //white
			
		else if (Color == 2 )  
			All_Tool.Color = RGB(0,255,0); 
		  
		else 
			All_Tool.Color = RGB(255,255,255); 
		
		
		All_Tool.Text.Format("<---        ");
		sc.UseTool(All_Tool);
		

}