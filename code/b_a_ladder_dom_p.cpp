// The top of every source code file must include this line
#include "sierrachart.h"



//This is an empty study function.  Auto looping is enabled. 
SCSFExport scsf_B_A_Ladder_Function(SCStudyGraphRef sc)


{
	//SCSubgraphRef Average = sc.Subgraph[0];
	SCSubgraphRef Selling = sc.Subgraph[1];
	SCSubgraphRef Buying = sc.Subgraph[2];
	SCSubgraphRef BelowThresholdColors= sc.Subgraph[3];
	
	SCSubgraphRef SellingColors = sc.Subgraph[4];
	SCSubgraphRef BuyingColors = sc.Subgraph[5];
	
	SCInputRef DeltaStudy = sc.Input[0];
	SCInputRef Lookback = sc.Input[1];
	SCInputRef LookbackShort = sc.Input[2];
	SCInputRef Divergence = sc.Input[3];
	SCInputRef DivergenceAlert = sc.Input[4];
	SCInputRef Threshold = sc.Input[6];
	SCInputRef Offset = sc.Input[7];
	
	SCInputRef InFillSpace = sc.Input[5];
	SCInputRef ShowLongterm = sc.Input[8];
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "Delta Ladder";
		sc.GraphRegion = 0;
		//sc.DrawZeros = 0;


		sc.FreeDLL = 0;
		sc.StudyDescription = "This study works with the Sierra Chart cumulative delta bars study or the CD chartbook.  Bottom numbers are buying pressure.  Top numbers are selling pressure.  Make sure your TICK size is correct.  Numbers change color at the 4000 mark.  Point the study to the cumulative delta candle stick chart.";
		
		sc.AutoLoop = 0;  // true
		//sc.MaintainVolumeAtPriceData = 1;  // true
		sc.UpdateAlways = 1;
		sc.CalculationPrecedence = LOW_PREC_LEVEL;
		sc.AlertOnlyOncePerBar=1;
			
		DeltaStudy.Name = "Delta Study";
		DeltaStudy.SetStudyID(0);	

		Lookback.Name = "Long Term Length";
		Lookback.SetInt(10);
		
		LookbackShort.Name = "Short Term Length";
		LookbackShort.SetInt(3);
		
		//Divergence.Name="Divergence Alert Length.";
		//Divergence.SetInt(10);
		
		//DivergenceAlert.Name="Divergece Alert Number";
		//DivergenceAlert.SetInt(26);
		
		Threshold.Name="Threshold";
		Threshold.SetInt(3999);
		
		Offset.Name="Offset in ticks";
		Offset.SetInt(3);
		
		Selling.Name = "Short Term Selling";
		Selling.DrawStyle=DRAWSTYLE_IGNORE;

		Buying.Name = "Short Term Buying";
		Buying.DrawStyle=DRAWSTYLE_IGNORE;
		
		BuyingColors.Name = "Buying Colors";
		BuyingColors.DrawStyle =DRAWSTYLE_IGNORE;
		BuyingColors.SecondaryColorUsed=1;
		BuyingColors.PrimaryColor = RGB(100,223,100);
		BuyingColors.SecondaryColor = RGB(0,255,0);
		
		SellingColors.Name = "Selling Colors";
		SellingColors.DrawStyle =DRAWSTYLE_IGNORE;
		SellingColors.SecondaryColorUsed=1;
		SellingColors.PrimaryColor = RGB(223,100,100);
		SellingColors.SecondaryColor = RGB(255,0,0);
		
		BelowThresholdColors.Name = "Below Threshold Colors";
		BelowThresholdColors.DrawStyle =DRAWSTYLE_IGNORE;
		BelowThresholdColors.PrimaryColor = RGB(255,255,255);
		
		InFillSpace.Name = "Display Ladder in Fill Space";
		InFillSpace.SetYesNo(0);
		
		ShowLongterm.Name = "Show long term numbers";
		ShowLongterm.SetYesNo(1);
	
		//DeltaStudy.Name = "Delta Study";
		//DeltaStudy.SetSubgraphIndex(0);

	
		//sc.Subgraph[0].Name = "Name";
		//sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;
		
		//sc.Input[0].Name = "Float Input";
		//sc.Input[0].SetFloat(0.0f);
		
		//float& OldPrice = sc.PersistVars->f1;  //static variable
		//OldPrice=sc.BaseData[SC_LAST][sc.Index];
		
		return;
	}
	if (Offset.GetInt() > 10)  Offset.SetInt(1);
	
	SCFloatArray DeltaLastArray;
	sc.GetStudyArrayUsingID(DeltaStudy.GetStudyID(),3,DeltaLastArray);
	SCFloatArray DeltaHighArray;
	sc.GetStudyArrayUsingID(DeltaStudy.GetStudyID(),1,DeltaHighArray);
	SCFloatArray DeltaLowArray;
	sc.GetStudyArrayUsingID(DeltaStudy.GetStudyID(),2,DeltaLowArray);


	// Section 2 - Do data processing here
	s_UseTool Last_Tool;
	s_UseTool Buy_Tool;
	s_UseTool Sell_Tool;
	s_UseTool High_Tool;
	s_UseTool Low_Tool;
	s_UseTool ShortTermBuy_Tool;
	
	float TICK;
	float CurrentPrice;
	TICK=sc.TickSize;
	float BuyingPressureShortTerm;
	float SellingPressureShortTerm;
	float LowPrice;
	float HighPrice;
	//float DeltaLow;
	//float DeltaHigh;
	//float HighestPrice;
	//float LowestPrice;
	
	//float& OldPrice = sc.PersistVars->f1;  //satic variable
	CurrentPrice=sc.BaseData[SC_LAST][sc.Index];
	LowPrice=sc.BaseData[SC_LOW][sc.Index];
	HighPrice=sc.BaseData[SC_HIGH][sc.Index];
	float DeltaLastValue = DeltaLastArray[sc.Index];
	float DeltaLow = DeltaLowArray[sc.Index];
	float DeltaHigh = DeltaHighArray[sc.Index];
	float DeltaHighShortTerm;
	float DeltaLowShortTerm;
	float DeltaLowValue = DeltaLowArray[sc.Index];
	float DeltaHighValue = DeltaHighArray[sc.Index];
	
	DeltaHighValue=sc.GetHighest(DeltaHighArray, Lookback.GetInt());
	DeltaLowValue=sc.GetLowest(DeltaLowArray,Lookback.GetInt());
	DeltaHighShortTerm = sc.GetHighest(DeltaHighArray, LookbackShort.GetInt());
	DeltaLowShortTerm = sc.GetLowest(DeltaLowArray, LookbackShort.GetInt());

		//Last delta value
		//Last_Tool.Clear();
		//Last_Tool.ChartNumber = sc.ChartNumber;
		//Last_Tool.Tool = TOOL_TEXT;
		//Last_Tool.LineNumber = 2525;
		//Last_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
	
		//Last_Tool.BeginDateTime = -1;
		//Last_Tool.BeginValue = CurrentPrice+TICK;
	
		//Last_Tool.Color = RGB(255,255,255);  //white

		//Last_Tool.Text.Format("%5.0f",DeltaLastValue);
	
		//sc.UseTool(Last_Tool);
		
		BuyingPressureShortTerm = DeltaLastValue - DeltaLowShortTerm;
		SellingPressureShortTerm = DeltaHighShortTerm - DeltaLastValue;
		
	// short term selling
	High_Tool.Clear();
	High_Tool.ChartNumber = sc.ChartNumber;
	High_Tool.DrawingType = DRAWING_TEXT;
	High_Tool.LineNumber = 2535;
	High_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
	
	if (InFillSpace.GetYesNo() == 1)   {
		High_Tool.BeginDateTime = -1;
		High_Tool.TextAlignment=DT_VCENTER|DT_CENTER;   }
	else   {
		High_Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize - 1];
		High_Tool.TextAlignment=DT_VCENTER|DT_LEFT;  } 
		
	High_Tool.BeginValue = HighPrice+(TICK*Offset.GetInt());
	
	High_Tool.Color = BelowThresholdColors.PrimaryColor;
	if (SellingPressureShortTerm > Threshold.GetInt() ) {
		High_Tool.Color = SellingColors.PrimaryColor;
	}
	High_Tool.Text.Format("%5.0f",SellingPressureShortTerm);
	Selling[sc.Index]=SellingPressureShortTerm;
	sc.UseTool(High_Tool);
	
	
	// short term buying
	ShortTermBuy_Tool.Clear();
	ShortTermBuy_Tool.ChartNumber = sc.ChartNumber;
	ShortTermBuy_Tool.DrawingType = DRAWING_TEXT;
	ShortTermBuy_Tool.LineNumber = 2537;
	ShortTermBuy_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
	
	//ShortTermBuy_Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize - 1];
	if (InFillSpace.GetYesNo() == 1)  {
		ShortTermBuy_Tool.BeginDateTime = -1;
		ShortTermBuy_Tool.TextAlignment=DT_VCENTER|DT_CENTER;   }
	else   {
		ShortTermBuy_Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize - 1];
		ShortTermBuy_Tool.TextAlignment=DT_VCENTER|DT_RIGHT;   }
	
	ShortTermBuy_Tool.BeginValue = LowPrice-(TICK*Offset.GetInt());
	//ShortTermBuy_Tool.TextAlignment=DT_LEFT;

	//Buy_Tool.BeginValue = LowPrice-TICK-TICK-TICK-TICK;
	
	ShortTermBuy_Tool.Color = BelowThresholdColors.PrimaryColor;
	if (BuyingPressureShortTerm > Threshold.GetInt() ) {
		ShortTermBuy_Tool.Color = BuyingColors.PrimaryColor;
	}	
	ShortTermBuy_Tool.Text.Format("%5.0f",BuyingPressureShortTerm);
	Buying[sc.Index]=BuyingPressureShortTerm;
	sc.UseTool(ShortTermBuy_Tool);
	
	
	if (ShowLongterm.GetYesNo() == 1) {
	
		//Start of lookback marker
		// else were float DeltaLowValue = DeltaLowArray[sc.Index];
		float LookBackLow;
		Low_Tool.Clear();
		Low_Tool.TextAlignment=DT_VCENTER|DT_CENTER;
		LookBackLow=sc.BaseData[SC_HIGH][sc.Index-Lookback.GetInt()-1];
		Low_Tool.ChartNumber = sc.ChartNumber;
		Low_Tool.DrawingType = DRAWING_TEXT;
		Low_Tool.LineNumber = 2545;
		Low_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
		
		Low_Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize - Lookback.GetInt()];
		Low_Tool.BeginValue = LookBackLow - (TICK + TICK*Offset.GetInt());
		
		Low_Tool.Color = RGB(255,127,0);  
		Low_Tool.Text = "Start";

		sc.UseTool(Low_Tool);

		float BuyingPressure;
		float SellingPressure;
		BuyingPressure=DeltaLastValue - DeltaLowValue;
		SellingPressure=DeltaHighValue - DeltaLastValue;
			
		
		//buying pressure
		Buy_Tool.Clear();
		Buy_Tool.ChartNumber = sc.ChartNumber;
		Buy_Tool.DrawingType = DRAWING_TEXT;
		Buy_Tool.LineNumber = 2555;
		Buy_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
		
		//Buy_Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize - 1];
		if (InFillSpace.GetYesNo() == 1)  {
			Buy_Tool.BeginDateTime = -1;
			Buy_Tool.TextAlignment=DT_VCENTER|DT_CENTER;   }
		else   {
			Buy_Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize - 1];
			Buy_Tool.TextAlignment=DT_VCENTER|DT_RIGHT;   }
		
		Buy_Tool.BeginValue = LowPrice-(TICK+TICK+TICK*Offset.GetInt()); // * Offset.GetInt());
		//Buy_Tool.TextAlignment=DT_LEFT;
		
		Buy_Tool.Color = BelowThresholdColors.PrimaryColor;
		if (BuyingPressure > Threshold.GetInt() ) {
			Buy_Tool.Color = BuyingColors.SecondaryColor;
		}	
		Buy_Tool.Text.Format("%5.0f",BuyingPressure);
		
		sc.UseTool(Buy_Tool);
		
		// selling pressure
		Sell_Tool.Clear();
		
		if (InFillSpace.GetYesNo() == 1)
		
			Sell_Tool.TextAlignment=DT_VCENTER|DT_CENTER;
		else	
			Sell_Tool.TextAlignment=DT_VCENTER|DT_LEFT;
		
		Sell_Tool.ChartNumber = sc.ChartNumber;
		Sell_Tool.DrawingType = DRAWING_TEXT;
		Sell_Tool.LineNumber = 2565;
		Sell_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
		
		//Sell_Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize - 1];
		if (InFillSpace.GetYesNo() == 1)   {
			Sell_Tool.BeginDateTime = -1;
			Sell_Tool.TextAlignment=DT_VCENTER|DT_CENTER;  }
		else   { 
			Sell_Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize - 1];
			Sell_Tool.TextAlignment=DT_VCENTER|DT_LEFT;  }
			
		Sell_Tool.BeginValue = HighPrice+(TICK+TICK+TICK * Offset.GetInt());
		
		Sell_Tool.Color = BelowThresholdColors.PrimaryColor;
		if (SellingPressure > Threshold.GetInt() ) {
			Sell_Tool.Color = SellingColors.SecondaryColor;
		}
		Sell_Tool.Text.Format("%5.0f",SellingPressure);
		
		sc.UseTool(Sell_Tool);
	
	}
	
	
	//Divergence alert
	/*HighestPrice=sc.GetHighest(sc.BaseData[SC_HIGH], Divergence.GetInt());
	LowestPrice=sc.GetLowest(sc.BaseData[SC_LOW], Divergence.GetInt());
	if (DeltaHigh < DeltaHighValue && HighPrice >= HighestPrice) 
	{     
		 sc.SetAlert(DivergenceAlert.GetInt());
		 }
	if (DeltaLow > DeltaLowValue && LowPrice <= LowestPrice) 
		{ 
		sc.SetAlert(DivergenceAlert.GetInt());
		}
     */	
	/*
	if (CurrentPrice > OldPrice) //only ask is updated
	{
	//ask data
	//Bid_Tool.Clear();
		Ask_Tool.ChartNumber = sc.ChartNumber;
		Ask_Tool.Tool = TOOL_TEXT;
		Ask_Tool.LineNumber = 2535;
		Ask_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
	
		Ask_Tool.BeginDateTime = -3;
		Ask_Tool.BeginValue = CurrentPrice+TICK;
	
		Ask_Tool.Color = RGB(0,0,255);  // Blue
		//Ask_Tool.Text = "Start";
		Ask_Tool.Text.Format("%5.2f",CurrentPrice);
	
		sc.UseTool(Ask_Tool);
	}
	
	if (CurrentPrice == OldPrice)   //both ask and bid are updated
	{
			//bid data
		//Ask_Tool.Clear();
		Bid_Tool.ChartNumber = sc.ChartNumber;
		Bid_Tool.Tool = TOOL_TEXT;
		Bid_Tool.LineNumber = 2525;
		Bid_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
	
		Bid_Tool.BeginDateTime = -1;
		Bid_Tool.BeginValue = CurrentPrice+TICK;
	
		Bid_Tool.Color = RGB(255,0,0);  // Red
		//Bid_Tool.Text = "Minus 1";
		Bid_Tool.Text.Format("%5.2f",CurrentPrice);
	
		sc.UseTool(Bid_Tool);
		
			//ask data
		//Bid_Tool.Clear();
		Ask_Tool.ChartNumber = sc.ChartNumber;
		Ask_Tool.Tool = TOOL_TEXT;
		Ask_Tool.LineNumber = 2535;
		Ask_Tool.AddMethod = UTAM_ADD_OR_ADJUST;
	
		Ask_Tool.BeginDateTime = -3;
		Ask_Tool.BeginValue = CurrentPrice+TICK;
	
		Ask_Tool.Color = RGB(0,0,255);  // Blue
		//Ask_Tool.Text = "Minus 2";
		Ask_Tool.Text.Format("%5.2f",CurrentPrice);
	
		sc.UseTool(Ask_Tool);
	
	}   */
	
	//sc.Subgraph[0][sc.Index]=sc.BaseData[SC_LOW][sc.Index];
	//OldPrice=sc.BaseData[SC_LAST][sc.Index];  //save the last price in static variable
}













