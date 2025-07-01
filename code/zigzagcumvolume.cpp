 // Author: jsyd
#include "sierrachart.h"

//SCDLLName("ZigZagCumVolume") 

SCSFExport scsf_ZigZagCumVolume(SCStudyGraphRef sc)
{
	SCSubgraphRef ZigZag = sc.Subgraph[0];
	SCSubgraphRef UpLength = sc.Subgraph[2];
	SCSubgraphRef DnLength = sc.Subgraph[3];
	SCSubgraphRef Volume = sc.Subgraph[4];
	SCSubgraphRef Ratio = sc.Subgraph[5];
	SCSubgraphRef textColor = sc.Subgraph[6];
	SCSubgraphRef tH = sc.Subgraph[7];
	SCSubgraphRef tL = sc.Subgraph[8];
	SCSubgraphRef pV = sc.Subgraph[9];
	SCSubgraphRef test = sc.Subgraph[10];

	SCInputRef VersionUpdate = sc.Input[0];
	SCInputRef InputDataHigh = sc.Input[1];
	SCInputRef InputDataLow = sc.Input[2];
	SCInputRef CalculationMode = sc.Input[3];
	SCInputRef RevPercent = sc.Input[4];
	SCInputRef RevAmount = sc.Input[5];
	SCInputRef NumberBarsForReversal = sc.Input[6];
	SCInputRef UseBidAsk = sc.Input[7];
	SCInputRef CalcRatio = sc.Input[8];
	SCInputRef MFactor = sc.Input[9];
	SCInputRef showText = sc.Input[10];
	SCInputRef textOffset = sc.Input[11];


	if(sc.SetDefaults)
	{
		sc.GraphName="Zig Zag Cumulative Volume";
		sc.StudyDescription="Chart cumulative volume from each Zig Zag direction change. You can choose volume type. Also includes, optionally, average volume labels for each move and volume/price ratio bars.";

		//Manual looping

		sc.GraphRegion = 0;

		ZigZag.Name = "Zig Zag Line";
		ZigZag.DrawStyle = DRAWSTYLE_DONOTDRAW;
		
		UpLength.Name = "Up Length";
		UpLength.DrawStyle = DRAWSTYLE_IGNORE;
		
		DnLength.Name = "Down Length";
		DnLength.DrawStyle = DRAWSTYLE_IGNORE;
		
		Volume.Name = "Volume Bars";
		Volume.DrawStyle = DRAWSTYLE_BAR;
		Volume.PrimaryColor = RGB(255, 255, 255);
		Volume.SecondaryColor = RGB(202, 68, 95);
		Volume.SecondaryColorUsed = 1;
		Volume.LineWidth = 4;
		
		Ratio.Name = "Volume/Price Ratio";
		Ratio.DrawStyle = DRAWSTYLE_BAR;
		Ratio.PrimaryColor = RGB(0, 128, 255);
		Ratio.SecondaryColor = RGB(255, 255, 0);
		Ratio.SecondaryColorUsed = 1;
		Ratio.LineWidth = 1;
		
		textColor.Name = "Text Color";
		textColor.DrawStyle = DRAWSTYLE_IGNORE;
		textColor.PrimaryColor = RGB(255, 255, 255);
		textColor.SecondaryColor = RGB(202, 68, 95);
		textColor.SecondaryColorUsed = 1;
		
		tH.Name = "Debug-High Index";
		tH.DrawStyle = DRAWSTYLE_IGNORE;
		
		tL.Name = "Debug-Low Index";
		tL.DrawStyle = DRAWSTYLE_IGNORE;
		
		pV.Name = "Debug-Direction";
		pV.DrawStyle = DRAWSTYLE_IGNORE;
		
		test.Name = "Test";
		test.DrawStyle = DRAWSTYLE_IGNORE;
		
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

		UseBidAsk.Name = "Volume (1=BA,2=UT/DT,3=BATrades,4=B/ADiffH,5=B/ADiffL,6=BvsA,7=total)";
		UseBidAsk.SetInt(7);
		UseBidAsk.SetIntLimits(1, 7);

		CalcRatio.Name = "Show Volume/Price Ratio";
		CalcRatio.SetYesNo(false);

		MFactor.Name = "Mutliplication Factor for Ratio Display";
		MFactor.SetInt(1);

		showText.Name = "Show Avg Volume Labels";
		showText.SetYesNo(false);

		textOffset.Name = "Label Offset";
		textOffset.SetFloat(2000);
		
		VersionUpdate.Name = "Version";
		VersionUpdate.SetInt(9);
		VersionUpdate.SetIntLimits(9,9);
		
		sc.ValueFormat = 0;
		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		sc.GraphRegion=1;

		return;
	}
	
	int& lastUpIndex = sc.PersistVars->i1;
	int& lastDnIndex = sc.PersistVars->i2;
	int& upIndex = sc.PersistVars->i3;
	int& dnIndex = sc.PersistVars->i4;
	int& lastDir = sc.PersistVars->i5;
	int& toolInc = sc.PersistVars->i6;
	
	const int toolID = 12890431;

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

		SCString LengthStr;
		SCString ReversalPrice;
		double Length = 0.0;
		for (int i1 = i - 1; i1 >= 0; i1--)
		{
			if (Peaks[i1] == -Peaks[i])
			{
				Length = Values[i] - Values[i1];
			}
		}
		if (Peaks[i] == 1.0f) 
		{
			if(lastUpIndex > lastDnIndex) {
//				UpLength[lastUpIndex] = 0;
			}
			UpLength[i] = (float)Length;
			lastUpIndex = i;
		} else {
			if(lastDnIndex > lastUpIndex) {
//				DnLength[lastDnIndex] = 0;
			}
			DnLength[i] = (float)Length;
			lastDnIndex = i;
		}
	}
	
	int u = 0;
	int barCnt = 0;
	for (u = 0; u < sc.ArraySize; u++)
	{	
		barCnt++;
		test[u] = toolID;
//		if(showText.BooleanValue) {
			s_UseTool Tool1;
			Tool1.Clear();
			Tool1.ChartNumber = sc.ChartNumber;
			Tool1.Tool = TOOL_TEXT;
			Tool1.Region = sc.GraphRegion;
			SCString StrATR;
			Tool1.FontSize = 8;
			Tool1.FontBold = true;
			Tool1.TextAlignment	= DT_CENTER|DT_TOP;
			Tool1.AddMethod = UTAM_ADD_ALWAYS;
//		}
		
		float tmpVol = 0;
		float tmpUVol = 0;
		float tmpDVol = 0;
		float tempLow = 0;
		float tempHigh = 0;
		float uVar = 0;
		float rHigh = 0;
		float rLow = 0;
		// Get Volume
		
		if(UseBidAsk.GetInt() == 1) {
			tmpUVol = sc.BaseDataIn[SC_ASKVOL][u];
			tmpDVol = sc.BaseDataIn[SC_BIDVOL][u];
		} else if(UseBidAsk.GetInt() == 2) {
			tmpUVol = sc.BaseDataIn[SC_UPVOL][u];
			tmpDVol = sc.BaseDataIn[SC_DOWNVOL][u];
		} else if(UseBidAsk.GetInt() == 3) {
			tmpUVol = sc.BaseDataIn[SC_ASKNT][u];
			tmpDVol = sc.BaseDataIn[SC_BIDNT][u];
		} else {
			if(UseBidAsk.GetInt() == 4) {
				tmpUVol = sc.BaseDataIn[15][u];
				tmpDVol = sc.BaseDataIn[15][u];
			} else if(UseBidAsk.GetInt() == 5) {
				tmpUVol = sc.BaseDataIn[16][u];
				tmpDVol = sc.BaseDataIn[16][u];
			} else if(UseBidAsk.GetInt() == 6) {
				tmpUVol = (sc.BaseDataIn[SC_ASKVOL][u] - sc.BaseDataIn[SC_BIDVOL][u]);
				tmpDVol = (sc.BaseDataIn[SC_ASKVOL][u] - sc.BaseDataIn[SC_BIDVOL][u]);
			} else {
				tmpUVol = sc.BaseDataIn[SC_VOLUME][u];
				tmpDVol = sc.BaseDataIn[SC_VOLUME][u];
			}
		}

		if(pV[u-1] == 1) {
			Volume.DataColor[u] = Volume.PrimaryColor;
			Volume[u] = tmpUVol + Volume[u-1];
		} else if(pV[u-1] == -1) {
			Volume.DataColor[u] = Volume.SecondaryColor;
			Volume[u] = tmpDVol + Volume[u-1];
		}

		pV[u] = pV[u-1];

		if(tH[u] == 0) {
			tH[u] = tH[u-1];
		}
		if(tL[u] == 0) {
			tL[u] = tL[u-1];
		}
		
		if(ZigZag[u] != 0) {
			if(ZigZag[u] > ZigZag[u-1]) {
				if(pV[u] == -1) {
					Volume.DataColor[u] = Volume.PrimaryColor;
					Volume[u] = tmpUVol;
					if(toolInc == 0) {
						Tool1.Color = textColor.SecondaryColor;
						Tool1.BeginDateTime = sc.BaseDateTimeIn[u-1];
						Tool1.LineNumber = toolID+toolInc;
						StrATR.Format("%.0f",(Volume[u-1]/barCnt));
						Tool1.Text = StrATR;
						if(UseBidAsk.GetInt() == 6) {
							Tool1.BeginValue = Volume[u-1]-textOffset.GetFloat();
						} else {
							Tool1.BeginValue = Volume[u-1]+textOffset.GetFloat();
						}
						if(showText.BooleanValue) {
							sc.UseTool(Tool1);
						}
					}
					toolInc = 1;
					barCnt = 0;
				} else if(pV[u] == 1) {
					tL[u] = (float)(u+1);
				}
				pV[u] = 1; 
			} else if(ZigZag[u] < ZigZag[u-1]) {
				if(pV[u] == 1) {
					Volume.DataColor[u] = Volume.SecondaryColor;
					Volume[u] = tmpDVol;
					if(toolInc == 1) {
						Tool1.Color = textColor.PrimaryColor;
						Tool1.BeginDateTime = sc.BaseDateTimeIn[u-1];
						Tool1.LineNumber = toolID+toolInc;
						StrATR.Format("%.0f",(Volume[u-1]/barCnt));
						Tool1.Text = StrATR;
						Tool1.BeginValue = Volume[u-1]+textOffset.GetFloat();
						if(showText.BooleanValue) {
							sc.UseTool(Tool1);
						}
					}
					toolInc = 0;
					barCnt = 0;
				} else if(pV[u] == -1) {
					tH[u] = (float)(u+1);
				}
				pV[u] = -1; 
			}
		}

		if(sc.GetBarHasClosedStatus(u) == BHCS_BAR_HAS_CLOSED) {
			if(CalcRatio.BooleanValue) {
				if(tL[u] > tH[u]) {
					Ratio.DataColor[u] = Ratio.PrimaryColor;
					if(tL[u] == u) {
						rHigh = sc.BaseDataIn[SC_HIGH][(int)tH[u]];
						rLow = sc.BaseDataIn[SC_LOW][u];
					} else {
						rHigh = sc.BaseDataIn[SC_HIGH][u];
						rLow = sc.BaseDataIn[SC_LOW][(int)tL[u]];
					}
				} else {
					Ratio.DataColor[u] = Ratio.SecondaryColor;		
					if(tH[u] == u) {
						rHigh = sc.BaseDataIn[SC_HIGH][u];
						rLow = sc.BaseDataIn[SC_LOW][(int)tL[u]];
					} else {
						rHigh = sc.BaseDataIn[SC_HIGH][(int)tH[u]];
						rLow = sc.BaseDataIn[SC_LOW][u];
					}
				}
				float rLength = (rHigh - rLow);
				float lenTicks = rLength/sc.TickSize;
				if(lenTicks != 0) {
					Ratio[u] = ((Volume[u]/lenTicks) * MFactor.GetInt());
				}
			}
		}
	}
	sc.PersistVars->i1 = EndIndex - 1;
}