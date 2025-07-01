 // Author: jsyd
#include "sierrachart.h"

//SCDLLName("ZigZagHLLines") 

SCSFExport scsf_ZigZagHLLines(SCStudyGraphRef sc)
{
	SCSubgraphRef ZigZag = sc.Subgraph[1];
	SCSubgraphRef TextLabels = sc.Subgraph[2];
	SCSubgraphRef UpLength = sc.Subgraph[3];
	SCSubgraphRef DnLength = sc.Subgraph[4];
	SCSubgraphRef uL = sc.Subgraph[5];
	SCSubgraphRef dL = sc.Subgraph[6];
	SCSubgraphRef test = sc.Subgraph[7];

	SCInputRef VersionUpdate = sc.Input[0];
	SCInputRef InputDataHigh = sc.Input[1];
	SCInputRef InputDataLow = sc.Input[2];
	SCInputRef CalculationMode = sc.Input[3];
	SCInputRef RevPercent = sc.Input[4];
	SCInputRef RevAmount = sc.Input[5];
	SCInputRef NumberBarsForReversal = sc.Input[6];
	SCInputRef ShowRevPrice = sc.Input[7];
	SCInputRef ShowLabels = sc.Input[8];
	SCInputRef LabelsOffset = sc.Input[9];
	SCInputRef LWidth = sc.Input[10];


	if(sc.SetDefaults)
	{
		sc.GraphName="Zig Zag High/Low Trendlines";
		sc.StudyDescription="Draw horizontal trend lines at each high/low. End each line when it is tested again.";

		//Manual looping

		ZigZag.Name = "Zig Zag Line";
		ZigZag.DrawStyle = DRAWSTYLE_LINE;
		ZigZag.LineStyle = LINESTYLE_DOT;
		ZigZag.PrimaryColor = RGB(255,0,255);
		ZigZag.LineWidth = 3;
		ZigZag.DrawZeros = false;

		TextLabels.Name = "Text Labels";
		TextLabels.SecondaryColorUsed = 1;
		TextLabels.PrimaryColor = RGB(0,255,0);
		TextLabels.SecondaryColor = RGB(255,0,0);
		TextLabels.LineWidth = 10;
		TextLabels.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
		
		UpLength.Name = "Up Length";
		UpLength.DrawStyle = DRAWSTYLE_IGNORE;
		
		DnLength.Name = "Down Length";
		DnLength.DrawStyle = DRAWSTYLE_IGNORE;

		uL.Name = "High Line Color";
		uL.PrimaryColor = RGB(255, 0, 0);
		uL.DrawStyle = DRAWSTYLE_IGNORE;

		dL.Name = "Low Line Color";
		dL.PrimaryColor = RGB(0, 255, 0);
		dL.DrawStyle = DRAWSTYLE_IGNORE;
		
		test.Name = "test";
		test.DrawStyle = DRAWSTYLE_IGNORE;

		sc.Subgraph[10].Name = "High Trendline";
		sc.Subgraph[10].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[10].LineWidth = 2;

		sc.Subgraph[11].Name = "High Trendline";
		sc.Subgraph[11].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[11].LineWidth = 2;

		sc.Subgraph[12].Name = "High Trendline";
		sc.Subgraph[12].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[12].LineWidth = 2;

		sc.Subgraph[13].Name = "High Trendline";
		sc.Subgraph[13].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[13].LineWidth = 2;

		sc.Subgraph[14].Name = "High Trendline";
		sc.Subgraph[14].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[14].LineWidth = 2;

		sc.Subgraph[15].Name = "High Trendline";
		sc.Subgraph[15].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[15].LineWidth = 2;

		sc.Subgraph[16].Name = "High Trendline";
		sc.Subgraph[16].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[16].LineWidth = 2;

		sc.Subgraph[17].Name = "High Trendline";
		sc.Subgraph[17].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[17].LineWidth = 2;

		sc.Subgraph[18].Name = "High Trendline";
		sc.Subgraph[18].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[18].LineWidth = 2;

		sc.Subgraph[19].Name = "High Trendline";
		sc.Subgraph[19].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[19].LineWidth = 2;

		sc.Subgraph[20].Name = "High Trendline";
		sc.Subgraph[20].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[20].LineWidth = 2;

		sc.Subgraph[21].Name = "High Trendline";
		sc.Subgraph[21].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[21].LineWidth = 2;

		sc.Subgraph[22].Name = "High Trendline";
		sc.Subgraph[22].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[22].LineWidth = 2;

		sc.Subgraph[23].Name = "High Trendline";
		sc.Subgraph[23].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[23].LineWidth = 2;

		sc.Subgraph[24].Name = "High Trendline";
		sc.Subgraph[24].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[24].LineWidth = 2;

		sc.Subgraph[25].Name = "Low Trendline";
		sc.Subgraph[25].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[25].LineWidth = 2;

		sc.Subgraph[26].Name = "Low Trendline";
		sc.Subgraph[26].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[26].LineWidth = 2;

		sc.Subgraph[27].Name = "Low Trendline";
		sc.Subgraph[27].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[27].LineWidth = 2;

		sc.Subgraph[28].Name = "Low Trendline";
		sc.Subgraph[28].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[28].LineWidth = 2;

		sc.Subgraph[29].Name = "Low Trendline";
		sc.Subgraph[29].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[29].LineWidth = 2;

		sc.Subgraph[30].Name = "Low Trendline";
		sc.Subgraph[30].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[30].LineWidth = 2;

		sc.Subgraph[31].Name = "Low Trendline";
		sc.Subgraph[31].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[31].LineWidth = 2;

		sc.Subgraph[32].Name = "Low Trendline";
		sc.Subgraph[32].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[32].LineWidth = 2;

		sc.Subgraph[33].Name = "Low Trendline";
		sc.Subgraph[33].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[33].LineWidth = 2;

		sc.Subgraph[34].Name = "Low Trendline";
		sc.Subgraph[34].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[34].LineWidth = 2;

		sc.Subgraph[35].Name = "Low Trendline";
		sc.Subgraph[35].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[35].LineWidth = 2;

		sc.Subgraph[36].Name = "Low Trendline";
		sc.Subgraph[36].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[36].LineWidth = 2;

		sc.Subgraph[37].Name = "Low Trendline";
		sc.Subgraph[37].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[37].LineWidth = 2;

		sc.Subgraph[38].Name = "Low Trendline";
		sc.Subgraph[38].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[38].LineWidth = 2;

		sc.Subgraph[39].Name = "Low Trendline";
		sc.Subgraph[39].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[39].LineWidth = 2;
		
		// Inputs

		InputDataHigh.Name = "Input Data for High";
		InputDataHigh.SetInputDataIndex(SC_HIGH);

		InputDataLow.Name = "Input Data for Low";
		InputDataLow.SetInputDataIndex(SC_LOW);

		CalculationMode.Name = "Calculation Mode (1,2,3)";
		CalculationMode.SetInt(1);
		CalculationMode.SetIntLimits(1, 3);

		RevPercent.Name = "Reversal % for Calculation Mode 1";
		RevPercent.SetFloat(.15f);

		RevAmount.Name = "Reversal Amount for Calculation Mode 2,3";
		RevAmount.SetFloat(0.01f);

		NumberBarsForReversal.Name = "Number of Bars Required for Reversal (Calculation mode 2)";
		NumberBarsForReversal.SetInt(5);

		ShowRevPrice.Name = "Display Reversal Price and Length of Zig Zag Line";
		ShowRevPrice.SetYesNo(0);

		ShowLabels.Name = "Display HH,HL,LL,LH Labels";
		ShowLabels.SetYesNo(0);

		LabelsOffset.Name = "Text Labels Percentage Offset";
		LabelsOffset.SetFloat(5.0f);

		LWidth.Name = "Trendline Thickness (1-10)";
		LWidth.SetInt(2);
		LWidth.SetIntLimits(1, 10);
		
		VersionUpdate.Name = "Version";
		VersionUpdate.SetInt(3);
		VersionUpdate.SetIntLimits(3,3);
		
		sc.ValueFormat = 5;
		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		sc.GraphRegion=0;
		sc.ScaleRangeType=SCALE_SAMEASREGION;

		return;
	}
	
	int& lastUpIndex = sc.PersistVars->i1;
	int& lastDnIndex = sc.PersistVars->i2;
	
	for (int Index = sc.UpdateStartIndex; Index <= sc.ArraySize - 1; Index++)
	{
		switch (CalculationMode.GetInt())
		{
		case 1:
			sc.ZigZag(
				sc.BaseData[InputDataHigh.GetInputDataIndex()],
				sc.BaseData[InputDataLow.GetInputDataIndex()],
				ZigZag,
				Index,
				RevPercent.GetFloat() * 0.01f
				);
			break;
		case 2:
			sc.ZigZag2(
				sc.BaseData[InputDataHigh.GetInputDataIndex()],
				sc.BaseData[InputDataLow.GetInputDataIndex()],
				ZigZag,
				Index,
				NumberBarsForReversal.GetInt(),
				RevAmount.GetFloat()
				);
			break;
		case 3:
			sc.ZigZag(
				sc.BaseData[InputDataHigh.GetInputDataIndex()],
				sc.BaseData[InputDataLow.GetInputDataIndex()],
				ZigZag,
				Index,
				0.0f,
				RevAmount.GetFloat()
				);
			break;
		}
	}

	const int UniqueID = 11062009;
	int Index = sc.UpdateStartIndex;
	int EndIndex = 0;
	int LastIndex = sc.PersistVars->i1;

	SCFloatArrayRef Values = ZigZag.Data;
	SCFloatArrayRef Peaks = ZigZag.Arrays[0];

	int StartIndex = 0;
	if (sc.UpdateStartIndex == 0)
	{
		StartIndex = sc.ArraySize - 1;
		LastIndex = 0;
	}
	else
		StartIndex = sc.UpdateStartIndex;

	for (int i = StartIndex; i >= 0; i--)
	{
		if (Peaks[i] != 0.0f)
		{
			EndIndex = i;
			break;
		}
	}

	if (LastIndex > sc.UpdateStartIndex)
		LastIndex = 0;

	if (EndIndex == LastIndex)
		return;

	for (int i = LastIndex; i <= EndIndex; i++)
	{
		if (Peaks[i] == 0.0f) //not a peak, nothing to be drawn
			continue;

		SCString BarLabelText;
		SCString LengthStr;
		SCString ReversalPrice;
		int VerticalTextAlignment = Peaks[i] == 1.0 ? DT_BOTTOM : DT_TOP;
		double Length = 0.0;
		for (int i1 = i - 1; i1 >= 0; i1--)
		{
			if (Peaks[i1] == -Peaks[i])
			{
				Length = Values[i] - Values[i1];
				LengthStr = sc.FormatGraphValue(Length, sc.ValueFormat);
				ReversalPrice = sc.FormatGraphValue(Values[i], sc.ValueFormat);
				
				if (ShowRevPrice.GetYesNo() && !ShowLabels.GetYesNo())
				{
					BarLabelText.Format("%s (%s)", ReversalPrice.GetChars(), LengthStr.GetChars());
					break;
				}
			}

			if (Peaks[i1] == Peaks[i])
			{
				if (ShowLabels.GetYesNo())
				{
					
					if (Peaks[i1] == 1.0f)//High
					{
						if (Values[i1] > Values[i]) //LowerHigh
						{
							if (ShowRevPrice.GetYesNo())
								BarLabelText.Format("LH %s (%s)", ReversalPrice.GetChars(), LengthStr.GetChars());
							else
								BarLabelText = "LH";
						}
						else //HigherHigh
						{
							if (ShowRevPrice.GetYesNo())
								BarLabelText.Format("HH %s (%s)", ReversalPrice.GetChars(), LengthStr.GetChars());
							else
								BarLabelText = "HH";
						}
					}
					else //Low
					{
						if (Values[i1] < Values[i]) //HigherLow
						{
							if (ShowRevPrice.GetYesNo())
								BarLabelText.Format("HL %s (%s)", ReversalPrice.GetChars(), LengthStr.GetChars());
							else
								BarLabelText = "HL";
						}
						else //LowerLow
						{
							if (ShowRevPrice.GetYesNo())
								BarLabelText.Format("LL %s (%s)", ReversalPrice.GetChars(), LengthStr.GetChars());
							else
								BarLabelText = "LL";
						}
					}
				}

				break;
			}
		}

		s_UseTool Tool; 
		Tool.Clear();
		Tool.ChartNumber = sc.ChartNumber;
		Tool.DrawingType = DRAWING_TEXT;
		Tool.ReverseTextColor = 0;
		Tool.BeginDateTime = sc.BaseDateTimeIn[i];
		
		float Offset;

		if(Peaks[i] == 1.0f)
			Offset = LabelsOffset.GetFloat()*0.01f*(sc.High[i]-sc.Low[i]);
		else
			Offset = -LabelsOffset.GetFloat()*0.01f*(sc.High[i]-sc.Low[i]);
		
		Tool.BeginValue = Values[i] + Offset;

		if (Peaks[i] == 1.0f)
			Tool.Color =  TextLabels.PrimaryColor;
		else
			Tool.Color = TextLabels.SecondaryColor;

		if (Peaks[i] == 1.0f) 
		{
			if(lastUpIndex > lastDnIndex) {
				UpLength[lastUpIndex] = 0;
			}
			UpLength[i] = (float)Length;
			uL[i] = (float)Length;
			lastUpIndex = i;
		} else {
			if(lastDnIndex > lastUpIndex) {
				DnLength[lastDnIndex] = 0;
			}
			DnLength[i] = (float)Length;
			dL[i] = (float)Length;
			lastDnIndex = i;
		}	
		

		Tool.FontSize = TextLabels.LineWidth;
		Tool.FontBold = FALSE;

		Tool.Text = BarLabelText;
		if (i == EndIndex)
		{
			Tool.AddMethod = UTAM_ADD_OR_ADJUST;
			Tool.LineNumber = UniqueID + 1;
		}
		else
		{
			Tool.AddMethod = UTAM_ADD_ALWAYS;
			Tool.LineNumber = UniqueID;
		}

		Tool.TextAlignment	= DT_CENTER | VerticalTextAlignment;

		if (ShowLabels.GetYesNo() || ShowRevPrice.GetYesNo())
		{
			sc.UseTool(Tool);
		}
	}
	int u = 0;
	for (u = sc.UpdateStartIndex; u < sc.ArraySize; u++)
	{
		if(sc.GetBarHasClosedStatus(u) == BHCS_BAR_HAS_CLOSED)
		{
			test[u] = (float)u;
			/******* HIGH LINES *******/
			// remove duplicate lines
/*
			for(int y = 10;y <= 24;y++) {
				for(int z = 10;z <= 24;z++) {
					if((sc.Subgraph[y][u-1] == sc.Subgraph[z][u-1]) && (z != y) && (sc.Subgraph[z][u-1] > 0)) {
						sc.Subgraph[z][u] = 0;
						sc.Subgraph[z].Arrays[0][u] = u;
						sc.Subgraph[z][u-1] = 0;
						sc.Subgraph[z].Arrays[0][u-1] = u;
					} 
				}
			}
*/
			// pre plot all lines
			for(int y = 10;y <= 24;y++) {
				sc.Subgraph[y].DataColor[u] = uL.PrimaryColor;
				sc.Subgraph[y].LineWidth = LWidth.GetInt();
				sc.Subgraph[y][u] = sc.Subgraph[y][u-1];
				sc.Subgraph[y].Arrays[0][u] = sc.Subgraph[y].Arrays[0][u-1];
			}
			// Plot new highs
			int hnewZero = 0;
			if(uL[u] > 0) 
			{
				// remove duplicate lines
				float hlastLine = 0;
				for(int y = 10;y <= 24;y++) {
					if(sc.Subgraph[y][u-1] == hlastLine) {
						sc.Subgraph[y][u] = 0;
						sc.Subgraph[y].Arrays[0][u] = (float)u;
						sc.Subgraph[y][u-1] = 0;
						sc.Subgraph[y].Arrays[0][u-1] = (float)u;
					} 
					if(sc.Subgraph[y][u-1] > 0) {
						hlastLine = sc.Subgraph[y][u-1];
					}
				}
				// Check to see if we have used all subgraphs - if so, clear the oldest
				int hfoundZero = 0;
				int maxHCnt = 0;
				int maxHSub = 0;
				for(int y = 10;y <= 24;y++) {
					if(sc.Subgraph[y][u-1] == 0) {
						hfoundZero = 1;
						break;
					} else if((u-sc.Subgraph[y].Arrays[0][u-1]) > maxHCnt) {
						maxHCnt = u - (int)sc.Subgraph[y].Arrays[0][u-1];
						maxHSub = y;
					}
				}
				int hZCnt = 0;
				if((hfoundZero == 0) && (hZCnt == 0))
				{
					sc.Subgraph[maxHSub][u-1] = 0;
					sc.Subgraph[maxHSub].Arrays[0][u-1] = (float)u;
					hZCnt = 1;
				}
				// See if we have a new high to plot
				int hLinePlotted = 0;
				for(int y = 10;y <= 24;y++)
				{
					if(sc.BaseDataIn[SC_HIGH][u] > sc.Subgraph[y][u-1]) 
					{
						if(hLinePlotted == 0) {
							sc.Subgraph[y][u] = sc.BaseDataIn[SC_HIGH][u];
							sc.Subgraph[y].Arrays[0][u] = (float)u;
							hLinePlotted = 1;
						} else {
							// avoid duplicates
							sc.Subgraph[y][u] = 0;
							sc.Subgraph[y].Arrays[0][u] = (float)u;
						}
					}
				}
			}
		
			/******* LOW LINES *******/
			// remove duplicate lines
/*
			for(int y = 25;y <= 39;y++) {
				for(int z = 25;z <= 39;z++) {
					if((sc.Subgraph[y][u-1] == sc.Subgraph[z][u-1]) && (z != y) && (sc.Subgraph[z][u-1] > 0)) {
						sc.Subgraph[z][u] = 0;
						sc.Subgraph[z].Arrays[0][u] = u;
						sc.Subgraph[z][u-1] = 0;
						sc.Subgraph[z].Arrays[0][u-1] = u;
					} 
				}
			}
*/
			// pre plot all lines
			for(int y = 25;y <= 39;y++) {
				sc.Subgraph[y].DataColor[u] = dL.PrimaryColor;
				sc.Subgraph[y].LineWidth = LWidth.GetInt();
				sc.Subgraph[y][u] = sc.Subgraph[y][u-1];
				sc.Subgraph[y].Arrays[0][u] = sc.Subgraph[y].Arrays[0][u-1];
			}
			// Plot new lows
			if(dL[u] < 0) 
			{
				// Check to see if we have used all subgraphs - if so, clear the oldest
				int lfoundZero = 0;
				int maxLCnt = 0;
				int maxLSub = 0;
				for(int y = 25;y <= 39;y++) {
					if(sc.Subgraph[y][u-1] == 0) {
						lfoundZero = 1;
						break;
					} else if((u-sc.Subgraph[y].Arrays[0][u-1]) > maxLCnt) {
						maxLCnt = u - (int)sc.Subgraph[y].Arrays[0][u-1];
						maxLSub = y;
					}
				}
				int lZCnt = 0;
				if((lfoundZero == 0) && (lZCnt == 0))
				{
					sc.Subgraph[maxLSub][u-1] = 0;
					sc.Subgraph[maxLSub].Arrays[0][u-1] = (float)u;
					lZCnt = 1;
				}
				// See if we have a new low to plot
				int lLinePlotted = 0;
				for(int y = 25;y <= 39;y++)
				{
					if((sc.BaseDataIn[SC_LOW][u] < sc.Subgraph[y][u-1]) || (sc.Subgraph[y][u-1] == 0)) 
					{
						if(lLinePlotted == 0) {
							sc.Subgraph[y][u] = sc.BaseDataIn[SC_LOW][u];
							sc.Subgraph[y].Arrays[0][u] = (float)u;
							lLinePlotted = 1;
						} else {
							// avoid duplicates
							sc.Subgraph[y][u] = 0;
							sc.Subgraph[y].Arrays[0][u] = (float)u;
						}
					}
				}
			}
		}
	}
	sc.PersistVars->i1 = EndIndex - 1;
}