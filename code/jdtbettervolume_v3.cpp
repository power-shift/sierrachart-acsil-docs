/*
jdt BetterVolume
Better Volume from emini-watch.com
Author: jsyd
Date: 10/04/2010

Added John Carter Value Chart
Date: 11/06/2010

Added VC On/Off option
Added On Bar CLose option
Added Option to use Bid/Ask Volume or Total Volume
Date: 12/11/2010

Fixed low volume color paint
Refactored to eliminate some unnecessary code
Date: 01/29/2011

 ****** Thanks to Scottorama at Sierra Charts ******
*/

#include "sierrachart.h"

/***********************************************************************/
SCSFExport scsf_jdtBetterVolume_v3(SCStudyGraphRef sc)
{
	SCSubgraphRef volumeSubgraph = sc.Subgraph[0];
	SCSubgraphRef volumeMASubgraph = sc.Subgraph[1];
	SCSubgraphRef volCliUpColorSubgraph = sc.Subgraph[2];
	SCSubgraphRef volCliDnColorSubgraph = sc.Subgraph[3];
	SCSubgraphRef hVolChurnColorSubgraph = sc.Subgraph[4];
	SCSubgraphRef hVolChurnCliColorSubgraph = sc.Subgraph[5];
	SCSubgraphRef lVolColorSubgraph = sc.Subgraph[6];
	SCSubgraphRef volCliUpFlagSubgraph = sc.Subgraph[7];
	SCSubgraphRef volCliDnFlagSubgraph = sc.Subgraph[8];
	SCSubgraphRef hVolChurnFlagSubgraph = sc.Subgraph[9];
	SCSubgraphRef hVolChurnCliFlagSubgraph = sc.Subgraph[10];
	SCSubgraphRef lVolFlagSubgraph = sc.Subgraph[11];
	SCSubgraphRef barSubgraph = sc.Subgraph[12];
	SCSubgraphRef vcSubgraph = sc.Subgraph[13];
	SCSubgraphRef vcDataSubgraph = sc.Subgraph[14];
	
	SCInputRef lookBackInput = sc.Input[0];
	SCInputRef volMaTypeInput = sc.Input[1];
	SCInputRef volMAPeriodInput = sc.Input[2];
	SCInputRef onCloseInput = sc.Input[3];
	SCInputRef volCliUpInput = sc.Input[4];
	SCInputRef volCliDnInput = sc.Input[5];
	SCInputRef hVolChurnInput = sc.Input[6];
	SCInputRef hVolChurnCliInput = sc.Input[7];
	SCInputRef lVolInput = sc.Input[8];
	SCInputRef alert1Input = sc.Input[9];
	SCInputRef alert2Input = sc.Input[10];
	SCInputRef alert3Input = sc.Input[11];
	SCInputRef alert4Input = sc.Input[12];
	SCInputRef alert5Input = sc.Input[13];
	SCInputRef colorBarsInput = sc.Input[14];
	SCInputRef colorBarsNeutralInput = sc.Input[15];
	SCInputRef baVolInput = sc.Input[16];
	SCInputRef vcInput = sc.Input[17];
	SCInputRef vcPeriodInput = sc.Input[18];
	SCInputRef vcTriggerInput = sc.Input[19];
	SCInputRef vcOffsetInput = sc.Input[20];
	
	if(sc.SetDefaults)
	{
		sc.GraphName="jdt BetterVolume v3";
		sc.StudyDescription="Better Volume - Histogram or ColorBars, with, optional, ValueChart points plotted";
		
		
		volumeSubgraph.Name = "Volume Bars";
		volumeSubgraph.DrawStyle = DRAWSTYLE_BAR;
		volumeSubgraph.PrimaryColor = RGB(0, 255, 255);
		volumeSubgraph.LineWidth = 4;
		
		volumeMASubgraph.Name = "Volume MA";
		volumeMASubgraph.DrawStyle = DRAWSTYLE_LINE;
		volumeMASubgraph.PrimaryColor = RGB(255, 0, 0);
		volumeMASubgraph.LineWidth = 2;
		
		volCliUpColorSubgraph.Name = "Volume Climax Up Color";
		volCliUpColorSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		volCliUpColorSubgraph.PrimaryColor = RGB(128,0, 0);
		
		volCliDnColorSubgraph.Name = "Volume Climax Down Color";
		volCliDnColorSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		volCliDnColorSubgraph.PrimaryColor = RGB(255, 255, 255);
		
		hVolChurnColorSubgraph.Name = "High Volume Churn Color";
		hVolChurnColorSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		hVolChurnColorSubgraph.PrimaryColor = RGB(255, 128, 0);
		
		hVolChurnCliColorSubgraph.Name = "High Volume Churn + Climax Color";
		hVolChurnCliColorSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		hVolChurnCliColorSubgraph.PrimaryColor = RGB(255, 0, 255);
		
		lVolColorSubgraph.Name = "Low Volume Color";
		lVolColorSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		lVolColorSubgraph.PrimaryColor = RGB(192, 192, 192);
		
		volCliUpFlagSubgraph.Name = "Volume Climax Up Flag";
		volCliUpFlagSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		
		volCliDnFlagSubgraph.Name = "Volume Climax Down Flag";
		volCliDnFlagSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		
		hVolChurnFlagSubgraph.Name = "High Volume Churn Flag";
		hVolChurnFlagSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		
		hVolChurnCliFlagSubgraph.Name = "High Volume Churn + Climax Flag";
		hVolChurnCliFlagSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		
		lVolFlagSubgraph.Name = "Low Volume Flag";
		lVolFlagSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;

        barSubgraph.Name = "Bar";
        barSubgraph.DrawStyle = DRAWSTYLE_COLORBAR;
		barSubgraph.PrimaryColor = RGB(0, 255, 255);
		
		vcSubgraph.Name = "Value Chart";
		vcSubgraph.DrawStyle = DRAWSTYLE_POINT;
		vcSubgraph.PrimaryColor = RGB(0, 255, 0);
		vcSubgraph.SecondaryColor = RGB(255, 0, 0);
		vcSubgraph.SecondaryColorUsed = 1;
		vcSubgraph.LineWidth = 4;
		
		// Inputs

		lookBackInput.Name = "Look Back Bars";
		lookBackInput.SetInt(20);
		lookBackInput.SetIntLimits(1,1000);

		volMaTypeInput.Name = "Volume MA Type";
		volMaTypeInput.SetMovAvgType(MOVAVGTYPE_SIMPLE);

		volMAPeriodInput.Name = "Volume MA Period";
		volMAPeriodInput.SetInt(100);
		volMAPeriodInput.SetIntLimits(1,1000);

		volMaTypeInput.Name = "Volume MA Type";
		volMaTypeInput.SetMovAvgType(MOVAVGTYPE_SIMPLE);

		onCloseInput.Name = "Only Paint Signals on Bar Close";
		onCloseInput.SetYesNo(true);

		volCliUpInput.Name = "Show Volume Climax Up Bar";
		volCliUpInput.SetYesNo(true);

		volCliDnInput.Name = "Show Volume Climax Down Bar";
		volCliDnInput.SetYesNo(true);

		hVolChurnInput.Name = "Show High Volume Churn Bar";
		hVolChurnInput.SetYesNo(true);

		hVolChurnCliInput.Name = "Show High Volume Churn + Climax Bar";
		hVolChurnCliInput.SetYesNo(true);

		lVolInput.Name = "Show Low Volume Bar";
		lVolInput.SetYesNo(true);

		alert1Input.Name = "Volume Climax Up Alert (Zero for off)";
        alert1Input.SetInt(0);
        alert1Input.SetIntLimits(0, 50);

		alert2Input.Name = "Volume Climax Down Alert (Zero for off)";
        alert2Input.SetInt(0);
        alert2Input.SetIntLimits(0, 50);

		alert3Input.Name = "High Volume Churn Alert (Zero for off)";
        alert3Input.SetInt(0);
        alert3Input.SetIntLimits(0, 50);

		alert4Input.Name = "High Volume Churn + Climax Alert (Zero for off)";
        alert4Input.SetInt(0);
        alert4Input.SetIntLimits(0, 50);

		alert5Input.Name = "Low Volume Alert (Zero for off)";
        alert5Input.SetInt(0);
        alert5Input.SetIntLimits(0, 50);

		colorBarsInput.Name = "Color Bars (No = Volume Histogram)";
		colorBarsInput.SetYesNo(false);

		colorBarsNeutralInput.Name = "Make non-signal Color Bars netural color";
		colorBarsNeutralInput.SetYesNo(false);

		vcInput.Name = "Plot Value Chart Signals (Color Bar mode Only)";
		vcInput.SetYesNo(true);

		baVolInput.Name = "Use Bid/Ask Volume for Calc - Otherwise Total Volume";
		baVolInput.SetYesNo(true);

		vcPeriodInput.Name = "Value Chart Period";
        vcPeriodInput.SetInt(5);
        vcPeriodInput.SetIntLimits(0, 1000);

		vcTriggerInput.Name = "Value Chart Trigger";
        vcTriggerInput.SetInt(8);
        vcTriggerInput.SetIntLimits(0, 16);

		vcOffsetInput.Name = "Value Chart Points Offset";
        vcOffsetInput.SetFloat(.001);
        vcOffsetInput.SetFloatLimits(.00001f, 1000);	

		sc.DrawZeros = false;
        sc.AutoLoop = 1;
		sc.FreeDLL = 0;
		sc.GraphRegion = 2;

		return;
	}

	int cur = sc.Index;
	int upBar;
	float Value1, Value1Bid, Value1Ask, Value2, Value2Bid, Value2Ask, Value3, Range;
	
	SCFloatArrayRef RangeArray = volumeSubgraph.Arrays[0];
	SCFloatArrayRef Value2Array = volumeSubgraph.Arrays[1];
	SCFloatArrayRef Value2BidArray = volumeSubgraph.Arrays[2];
	SCFloatArrayRef Value2AskArray = volumeSubgraph.Arrays[3];
	SCFloatArrayRef Value3Array = volumeSubgraph.Arrays[4];
	
	if(!colorBarsInput.BooleanValue) {
		volumeSubgraph[cur] = sc.BaseDataIn[SC_VOLUME][cur];
		volumeSubgraph.DataColor[cur] = volumeSubgraph.PrimaryColor;
		sc.MovingAverage(sc.BaseDataIn[SC_VOLUME], volumeMASubgraph, volMaTypeInput.GetMovAvgType() , cur, volMAPeriodInput.GetInt());
	} else if(colorBarsNeutralInput.BooleanValue) {
		barSubgraph.DataColor[cur] = barSubgraph.PrimaryColor;
		barSubgraph[cur] = sc.BaseDataIn[SC_LAST][cur];
	}
		
	if((sc.GetBarHasClosedStatus() == BHCS_BAR_HAS_CLOSED) || (!onCloseInput.BooleanValue)) {
		if(sc.BaseDataIn[SC_OPEN][cur] < sc.BaseDataIn[SC_LAST][cur]) {
			upBar = 1;
		} else if(sc.BaseDataIn[SC_OPEN][cur] > sc.BaseDataIn[SC_LAST][cur]) {
			upBar = -1;
		} else {
			upBar = 0;
		}
		Range = sc.BaseDataIn[SC_HIGH][cur] - sc.BaseDataIn[SC_LOW][cur];
		RangeArray[cur] = Range;
		Value1 = sc.BaseDataIn[SC_VOLUME][cur];
		if(baVolInput.BooleanValue) {
			Value1Bid = sc.BaseDataIn[SC_BIDVOL][cur];
			Value1Ask = sc.BaseDataIn[SC_ASKVOL][cur];
		} else {
			Value1Bid = sc.BaseDataIn[SC_VOLUME][cur];
			Value1Ask = sc.BaseDataIn[SC_VOLUME][cur];
		}
		Value2 = Value1*Range;
		Value2Bid = Value1Bid*Range;
		Value2Ask = Value1Ask*Range;
		Value2Array[cur] = Value2;
		Value2BidArray[cur] = Value2Bid;
		Value2AskArray[cur] = Value2Ask;
		if (Range != 0.0) {
			Value3 = Value1/Range;
		} else {
			Value3 = 0.0;
		}
		Value3Array[cur] = Value3;
		
	// Now to the good stuff
		
		if (Value2Ask == sc.GetHighest(Value2AskArray, lookBackInput.GetInt()) && (upBar == 1) && (volCliUpInput.BooleanValue)) { //Volume CLimax Up
			if(colorBarsInput.BooleanValue) {
				barSubgraph.DataColor[cur] = volCliUpColorSubgraph.PrimaryColor;
				barSubgraph[cur] = sc.BaseDataIn[SC_LAST][cur];
			} else {
				volumeSubgraph.DataColor[cur] = volCliUpColorSubgraph.PrimaryColor;
			}
			volCliUpFlagSubgraph[cur] = 1;
			if(alert1Input.GetInt() > 0) {
				sc.SetAlert(alert1Input.GetInt(),cur);
			}
		}
	
		if (Value2Bid == sc.GetHighest(Value2BidArray, lookBackInput.GetInt()) && (upBar == -1) && (volCliDnInput.BooleanValue)) { //Volume CLimax Down
			
			if(colorBarsInput.BooleanValue) {
				barSubgraph.DataColor[cur] = volCliDnColorSubgraph.PrimaryColor;
				barSubgraph[cur] = sc.BaseDataIn[SC_LAST][cur];
			} else {
				volumeSubgraph.DataColor[cur] = volCliDnColorSubgraph.PrimaryColor;
			}
			volCliDnFlagSubgraph[cur] = 1;
			if(alert2Input.GetInt() > 0) {
				sc.SetAlert(alert2Input.GetInt(),cur);
			}
		}
	
		if (Value3 == sc.GetHighest(Value3Array, lookBackInput.GetInt()) && (hVolChurnInput.BooleanValue)) { //High Volume Churn
			if(colorBarsInput.BooleanValue) {
				barSubgraph.DataColor[cur] = hVolChurnColorSubgraph.PrimaryColor;
				barSubgraph[cur] = sc.BaseDataIn[SC_LAST][cur];
			} else {
				volumeSubgraph.DataColor[cur] = hVolChurnColorSubgraph.PrimaryColor;
			}
			hVolChurnFlagSubgraph[cur] = 1;
			if(alert3Input.GetInt() > 0) {
				sc.SetAlert(alert3Input.GetInt(),cur);
			}
		}
	
		if (Value2 == sc.GetHighest(Value2Array, lookBackInput.GetInt()) && Value3 == sc.GetHighest(Value3Array, lookBackInput.GetInt()) && (hVolChurnCliInput.BooleanValue)) { //High Volume Churn + Climax
			if(colorBarsInput.BooleanValue) {
				barSubgraph.DataColor[cur] = hVolChurnCliColorSubgraph.PrimaryColor;
				barSubgraph[cur] = sc.BaseDataIn[SC_LAST][cur];
			} else {
				volumeSubgraph.DataColor[cur] = hVolChurnCliColorSubgraph.PrimaryColor;
			}
			hVolChurnCliFlagSubgraph[cur] = 1;
			if(alert4Input.GetInt() > 0) {
				sc.SetAlert(alert4Input.GetInt(),cur);
			}
		}
	
		if (Value1 == sc.GetLowest(sc.BaseDataIn[SC_VOLUME], lookBackInput.GetInt()) && (lVolInput.BooleanValue)) { //Low Volume Climax
			if(colorBarsInput.BooleanValue) {
				barSubgraph.DataColor[cur] = lVolColorSubgraph.PrimaryColor;
				barSubgraph[cur] = sc.BaseDataIn[SC_LAST][cur];
			} else {
				volumeSubgraph.DataColor[cur] = lVolColorSubgraph.PrimaryColor;
			}
			lVolFlagSubgraph[cur] = 1;
			if(alert5Input.GetInt() > 0) {
				sc.SetAlert(alert5Input.GetInt(),cur);
			}
		}
	}

/*====================================================================================
John Carter's Value Chart
====================================================================================*/	
	
	if((colorBarsInput.BooleanValue) && (vcInput.BooleanValue)) {
		int period = vcPeriodInput.GetInt();
		vcDataSubgraph.Arrays[0][cur-1] = (sc.BaseData[SC_HIGH][cur-1] + sc.BaseData[SC_LOW][cur-1])/2;
		sc.SimpleMovAvg(vcDataSubgraph.Arrays[0],vcDataSubgraph.Arrays[1],cur-1,period);
		float PreVarAs = vcDataSubgraph.Arrays[1][cur-1];
		sc.ATR(sc.BaseData,vcDataSubgraph.Arrays[2],vcDataSubgraph.Arrays[3],cur-1,period,MOVAVGTYPE_SIMPLE);
		float PreVolatiliteit = vcDataSubgraph.Arrays[3][cur-1]/period;
		int vcPreHigh = (sc.BaseData[SC_HIGH][cur-1] - PreVarAs)/PreVolatiliteit;
		int vcPreLow = (sc.BaseData[SC_LOW][cur-1] - PreVarAs)/PreVolatiliteit;
		
		vcDataSubgraph.Arrays[4][cur] = (sc.BaseData[SC_HIGH][cur] + sc.BaseData[SC_LOW][cur])/2;
		sc.SimpleMovAvg(vcDataSubgraph.Arrays[4],vcDataSubgraph.Arrays[5],cur,period);
		float VarAs = vcDataSubgraph.Arrays[5][cur];
		sc.ATR(sc.BaseData,vcDataSubgraph.Arrays[6],vcDataSubgraph.Arrays[7],cur,period,MOVAVGTYPE_SIMPLE);
		float Volatiliteit = vcDataSubgraph.Arrays[7][cur]/period;
		int vcHigh = (sc.BaseData[SC_HIGH][cur] - VarAs)/Volatiliteit;
		int vcLow = (sc.BaseData[SC_LOW][cur] - VarAs)/Volatiliteit;

		if((vcPreHigh >= vcTriggerInput.GetInt()) && (vcHigh < vcTriggerInput.GetInt())) {
			vcSubgraph.DataColor[cur-1] = vcSubgraph.SecondaryColor;
			vcSubgraph[cur-1] = sc.BaseDataIn[SC_HIGH][cur-1] + vcOffsetInput.GetFloat();
		} else if((vcPreLow <= -vcTriggerInput.GetInt()) && (vcLow > -vcTriggerInput.GetInt())) {
			vcSubgraph.DataColor[cur-1] = vcSubgraph.PrimaryColor;
			vcSubgraph[cur-1] = sc.BaseDataIn[SC_LOW][cur-1] - vcOffsetInput.GetFloat();
		}
	}
}