/*
jdt Delta Divergence
Author: jsyd
Date: 11/13/2011
*/

#include "sierrachart.h"
#include <string>
//SCDLLInit("Delta Divergence");
/***********************************************************************/
SCSFExport scsf_DeltaDivergence(SCStudyGraphRef sc)
{
	SCSubgraphRef ddVolSubgraph = sc.Subgraph[0];
	SCSubgraphRef ddBuySubgraph = sc.Subgraph[1];
	SCSubgraphRef ddSellSubgraph = sc.Subgraph[2];
	SCSubgraphRef ma1Subgraph = sc.Subgraph[3];
	SCSubgraphRef ma2Subgraph = sc.Subgraph[4];
	
	SCInputRef version = sc.Input[0];
	SCInputRef useCumVolInput = sc.Input[1];
	SCInputRef volTypeInput = sc.Input[2];
	SCInputRef ddModeInput = sc.Input[3];
	SCInputRef useCSTInput = sc.Input[4];
	SCInputRef ddPeriodInput = sc.Input[5];
	SCInputRef ma1Input = sc.Input[6];
	SCInputRef ma2Input = sc.Input[7];
	SCInputRef maTypeInput = sc.Input[8];
	SCInputRef maInputDataInput = sc.Input[9];
	SCInputRef ddOffsetInput = sc.Input[10];
	SCInputRef maZoneInput = sc.Input[11];
	SCInputRef sigZoneInput = sc.Input[12];
	
	if(sc.SetDefaults)
	{
		sc.GraphName="Delta Divergence";
		sc.StudyDescription="Delta Divergence with option to only trade with trend";
		
		ddVolSubgraph.Name = "Delta Volume";
		ddVolSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		
		ddBuySubgraph.Name = "Delta Divergence Buy";
		ddBuySubgraph.DrawStyle = DRAWSTYLE_ARROWUP;
		ddBuySubgraph.PrimaryColor = RGB(0, 255, 0);
		ddBuySubgraph.LineWidth = 2;
		
		ddSellSubgraph.Name = "Delta Divergence Sell";
		ddSellSubgraph.DrawStyle = DRAWSTYLE_ARROWDOWN;
		ddSellSubgraph.PrimaryColor = RGB(255, 0, 0);
		ddSellSubgraph.LineWidth = 2;
		
		ma1Subgraph.Name = "ma1";
		ma1Subgraph.DrawStyle = DRAWSTYLE_LINE;
		ma1Subgraph.PrimaryColor = RGB(0, 128, 0);
		ma1Subgraph.SecondaryColor = RGB(0, 0, 0);
		ma1Subgraph.LineWidth = 1;
		
		ma2Subgraph.Name = "ma2";
		ma2Subgraph.DrawStyle = DRAWSTYLE_LINE;
		ma2Subgraph.PrimaryColor = RGB(128, 0, 0);
		ma2Subgraph.SecondaryColor = RGB(0, 0, 0);
		ma2Subgraph.LineWidth = 1;
		
		// Inputs

		useCumVolInput.Name = "Use Cummulative Volume";
		useCumVolInput.SetYesNo(true);

		volTypeInput.Name = "Volume Type - 1=Ask-Bid, 2=UpTickVol-DnTickVol";
        volTypeInput.SetInt(1);
        volTypeInput.SetIntLimits(1, 2);

		ddModeInput.Name = "Trend following mode";
		ddModeInput.SetYesNo(false);

		useCSTInput.Name = "Use Daily HH/LL (else define period)";
		useCSTInput.SetYesNo(true);
		
		ddPeriodInput.Name = "Lookback Period";
        ddPeriodInput.SetInt(13);
        ddPeriodInput.SetIntLimits(0, 1000);
		
		ma1Input.Name = "Fast MA Length";
		ma1Input.SetInt(20);
		ma1Input.SetIntLimits(1, 10000);
		
		ma2Input.Name = "Slow MA Length";
		ma2Input.SetInt(30);
		ma2Input.SetIntLimits(1, 10000);					

		maTypeInput.Name = "MA Type";
		maTypeInput.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		
		maInputDataInput.Name = "MA Input Data";
		maInputDataInput.SetInputDataIndex(SC_LAST);

		ddOffsetInput.Name = "Display Signal Offset";
        ddOffsetInput.SetFloat(.001);
        ddOffsetInput.SetFloatLimits(.00001f, 1000);

		maZoneInput.Name = "MA Trend Zone";
        maZoneInput.SetFloat(.0002);
        maZoneInput.SetFloatLimits(.00001f, 1000);

		sigZoneInput.Name = "Entry Signal Zone";
        sigZoneInput.SetFloat(.0005);
        sigZoneInput.SetFloatLimits(.00001f, 1000);	
		
		version.Name = "Version";
		version.SetInt(3);
		version.SetIntLimits(3,3);	

		sc.DrawZeros = false;
        sc.AutoLoop = 1;
		sc.FreeDLL = 0;
		sc.GraphRegion = 0;
		sc.ValueFormat = 6;
		sc.ScaleRangeType=SCALE_SAMEASREGION;

		return;
	}

	int cur = sc.Index;
/*======================================================================================
MA
========================================================================================*/
	sc.MovingAverage(sc.BaseDataIn[maInputDataInput.GetInputDataIndex()], ma1Subgraph, maTypeInput.GetMovAvgType() , cur, ma1Input.GetInt());
	sc.MovingAverage(sc.BaseDataIn[maInputDataInput.GetInputDataIndex()], ma2Subgraph, maTypeInput.GetMovAvgType() , cur, ma2Input.GetInt());

/*====================================================================================
Delta Divergence
====================================================================================*/
	if(sc.GetBarHasClosedStatus() == BHCS_BAR_HAS_CLOSED) {
		float ddHigh;
		float ddLow;
		float Open;
		float Close;
		int uVolType = SC_ASKVOL;
		int dVolType = SC_BIDVOL;
		if(volTypeInput.GetInt() == 2) {
			uVolType = SC_UPVOL;
			dVolType = SC_DOWNVOL;
		}
//		ddVolSubgraph[cur] = sc.BaseDataIn[SC_ASKVOL][cur] - sc.BaseDataIn[SC_BIDVOL][cur];
		if(useCSTInput.BooleanValue) {
			if(useCumVolInput.BooleanValue) {
				if(sc.SecondsSinceStartTime(sc.BaseDateTimeIn[cur]) < 30) {
					ddVolSubgraph[cur] = sc.BaseDataIn[uVolType][cur] - sc.BaseDataIn[dVolType][cur];
				} else {
					ddVolSubgraph[cur] = ddVolSubgraph[cur-1] + (sc.BaseDataIn[uVolType][cur] - sc.BaseDataIn[dVolType][cur]);
				}
			} else {
				ddVolSubgraph[cur] = sc.BaseDataIn[uVolType][cur] - sc.BaseDataIn[dVolType][cur];
			}
			sc.GetOHLCForDate(sc.BaseDateTimeIn[cur], Open, ddHigh, ddLow, Close);
		} else {
			if(useCumVolInput.BooleanValue) {
				for(int x=cur-ddPeriodInput.GetInt();x<=cur;x++) {
					if(x == cur-ddPeriodInput.GetInt()) {
						ddVolSubgraph[x] = sc.BaseDataIn[uVolType][x] - sc.BaseDataIn[dVolType][x];
					} else {
						ddVolSubgraph[x] = ddVolSubgraph[x-1] + (sc.BaseDataIn[uVolType][x] - sc.BaseDataIn[dVolType][x]);
					}
				}
			} else {
				ddVolSubgraph[cur] = sc.BaseDataIn[uVolType][cur] - sc.BaseDataIn[dVolType][cur];
			}		
			ddHigh = sc.GetHighest(sc.BaseData[SC_HIGH], ddPeriodInput.GetInt());
			ddLow = sc.GetLowest(sc.BaseData[SC_LOW], ddPeriodInput.GetInt());
		}
		if(ddModeInput.BooleanValue) {
			if((ddVolSubgraph[cur] > 0) && (sc.BaseData[SC_LOW][cur] <= ddLow) && (ma1Subgraph[cur] > (ma2Subgraph[cur]+maZoneInput.GetFloat())) && (sc.BaseDataIn[SC_LOW][cur] <= (ma2Subgraph[cur]+sigZoneInput.GetFloat()))) {
				ddBuySubgraph[cur] = sc.BaseDataIn[SC_LOW][cur] - ddOffsetInput.GetFloat();
			} else if((ddVolSubgraph[cur] < 0) && (sc.BaseData[SC_HIGH][cur] >= ddHigh) && (ma1Subgraph[cur] < (ma2Subgraph[cur]-maZoneInput.GetFloat())) && (sc.BaseDataIn[SC_HIGH][cur] >= (ma1Subgraph[cur]-sigZoneInput.GetFloat()))) {
				ddSellSubgraph[cur] = sc.BaseDataIn[SC_HIGH][cur] + ddOffsetInput.GetFloat();
			}
		} else {
			if((ddVolSubgraph[cur] > 0) && (sc.BaseData[SC_LOW][cur] <= ddLow)) {
				ddBuySubgraph[cur] = sc.BaseDataIn[SC_LOW][cur] - ddOffsetInput.GetFloat();
			} else if((ddVolSubgraph[cur] < 0) && (sc.BaseData[SC_HIGH][cur] >= ddHigh)) {
				ddSellSubgraph[cur] = sc.BaseDataIn[SC_HIGH][cur] + ddOffsetInput.GetFloat();
			}	
		}
	}
}