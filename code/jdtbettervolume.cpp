/*
jdt BetterVolume
Better Volume from emini-watch.com
Author: jsyd
Date: 10/04/2010
 ****** Thanks to Scottorama at Sierra Charts ******
*/


#include "sierrachart.h"
//SCDLLInit("jdt Better Volume(jdtBetterVolume.dll)");
/***********************************************************************/
SCSFExport scsf_jdtBetterVolume(SCStudyGraphRef sc)
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
	
	SCInputRef lookBackInput = sc.Input[0];
	SCInputRef volMaTypeInput = sc.Input[1];
	SCInputRef volMAPeriodInput = sc.Input[2];
	SCInputRef volCliUpInput = sc.Input[3];
	SCInputRef volCliDnInput = sc.Input[4];
	SCInputRef hVolChurnInput = sc.Input[5];
	SCInputRef hVolChurnCliInput = sc.Input[6];
	SCInputRef lVolInput = sc.Input[7];
	SCInputRef alert1Input = sc.Input[8];
	SCInputRef alert2Input = sc.Input[9];
	SCInputRef alert3Input = sc.Input[10];
	SCInputRef alert4Input = sc.Input[11];
	SCInputRef alert5Input = sc.Input[12];
	SCInputRef colorBarsInput = sc.Input[13];
	
	if(sc.SetDefaults)
	{
		sc.GraphName="jdt BetterVolume";
		sc.StudyDescription="<a href=""http://www.sierrachart.com/supportboard/showpost.php?p=166484&postcount=24"">Better Volume - Histogram or ColorBars. new better volume indicator - ColorBars!</a>";
		
		
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
		volCliUpColorSubgraph.PrimaryColor = RGB(128, 0, 0);
		
		volCliDnColorSubgraph.Name = "Volume Climax Down Color";
		volCliDnColorSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		volCliDnColorSubgraph.PrimaryColor = RGB(255, 255, 255);
		
		hVolChurnColorSubgraph.Name = "High Volume Churn Color";
		hVolChurnColorSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		hVolChurnColorSubgraph.PrimaryColor = RGB(0, 0, 255);
		
		hVolChurnCliColorSubgraph.Name = "High Volume Churn + Climax Color";
		hVolChurnCliColorSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		hVolChurnCliColorSubgraph.PrimaryColor = RGB(255, 0, 255);
		
		lVolColorSubgraph.Name = "Low Volume Color";
		lVolColorSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		lVolColorSubgraph.PrimaryColor = RGB(255, 255, 0);
		
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
		barSubgraph.PrimaryColor = RGB(0, 255, 0);
		
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

		sc.DrawZeros = false;
        sc.AutoLoop = 1;
		sc.FreeDLL = 0;
		sc.GraphRegion = 2;

		return;
	}

	int cur = sc.Index;
	int upBar;
	float Value1, Value2, Value3, Range;
	
	SCFloatArrayRef RangeArray = volumeSubgraph.Arrays[0];
	SCFloatArrayRef Value2Array = volumeSubgraph.Arrays[1];
	SCFloatArrayRef Value3Array = volumeSubgraph.Arrays[2];
	
	if(!colorBarsInput.BooleanValue) {
		volumeSubgraph[cur] = sc.BaseDataIn[SC_VOLUME][cur];
		volumeSubgraph.DataColor[sc.Index] = volumeSubgraph.PrimaryColor;
		sc.MovingAverage(sc.BaseDataIn[SC_VOLUME], volumeMASubgraph, volMaTypeInput.GetMovAvgType() , cur, volMAPeriodInput.GetInt());
	}
		
	if(sc.GetBarHasClosedStatus() == BHCS_BAR_HAS_CLOSED) {
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
		Value2 = Value1*Range;
		Value2Array[cur] = Value2;
		if (Range != 0.0) {
			Value3 = Value1/Range;
		} else {
			Value3 = 0.0;
		}
		Value3Array[cur] = Value3;
		
	// Now to the good stuff
	
		if (Value2 == sc.GetHighest(Value2Array, lookBackInput.GetInt()) && (upBar == 1) && (volCliUpInput.BooleanValue)) { //Volume CLimax Up
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
	
		if (Value2 == sc.GetHighest(Value2Array, lookBackInput.GetInt()) && (upBar == -1) && (volCliDnInput.BooleanValue)) { //Volume CLimax Down
			
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
	
		if (Value1 == sc.GetLowest(volumeSubgraph, lookBackInput.GetInt()) && (lVolInput.BooleanValue)) { //Low Volume Climax
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
}