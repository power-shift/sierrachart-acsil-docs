
#include "sierrachart.h"


long T[24][60]={ 0 };int iT[24][60]={ 0 };
long TN[24][60]={ 0 };int iTN[24][60]={ 0 };
long MarketAvgVol=0; 
long MarketVolSum=0; int iMarketVolSum=0;
long NormVolume[10000]={0};
long NormVolSum=0; int iNormVolSum=0;
long NormAvgVol=0; 

/*==========================================================================*/
SCSFExport scsf_NormalizedVolume(SCStudyInterfaceRef sc)
{
	SCSubgraphRef UltraHighVolume = sc.Subgraph[0];
	SCSubgraphRef VeryHighVolume = sc.Subgraph[1];
	SCSubgraphRef HighVolume = sc.Subgraph[2];
	SCSubgraphRef LowVolume = sc.Subgraph[3];
	SCSubgraphRef VeryLowVolume = sc.Subgraph[4];
	
	SCSubgraphRef AvgVolumeMarketHours = sc.Subgraph[5];
	SCSubgraphRef AvgNormVolume = sc.Subgraph[6];
	
	SCSubgraphRef NormUpVol = sc.Subgraph[7];
	SCSubgraphRef NormDnVol = sc.Subgraph[8];
	SCSubgraphRef Volume  = sc.Subgraph[9];
	
	SCSubgraphRef BarAvgVolume = sc.Subgraph[10];
	SCSubgraphRef BarAvgNormVolume = sc.Subgraph[11];
	
	SCInputRef MarketOpenHour = sc.Input[1];
	SCInputRef MarketOpenMinute = sc.Input[2];
	SCInputRef MarketCloseHour = sc.Input[3];
	SCInputRef MarketCloseMinute = sc.Input[4];

	
	// Set configuration variables
	
	if (sc.SetDefaults)
	{
		// Set the defaults
		
		sc.GraphName = "Normalized Volume";
		sc.StudyDescription = "Normalized Volume calculates the median volume per hour of the day, and ...";
			
		sc.GraphRegion = 2;		
		
		// Subgraphs

		Volume.Name = "Regular Total Volume";
		Volume.DrawStyle = DRAWSTYLE_BAR;
		Volume.PrimaryColor = RGB(0, 0, 128);
		Volume.LineWidth = 1;
		
		BarAvgVolume.Name = "Bar Avg Regular Volume";
		BarAvgVolume.DrawStyle = DRAWSTYLE_STAIR;
		BarAvgVolume.PrimaryColor = RGB(0, 128, 255);
		BarAvgVolume.LineWidth = 2;
		
		BarAvgNormVolume.Name = "Bar Avg Normalized Volume";
		BarAvgNormVolume.DrawStyle = DRAWSTYLE_STAIR;
		BarAvgNormVolume.PrimaryColor = RGB(255, 128, 0);
		BarAvgNormVolume.LineWidth = 2;

		NormUpVol.Name = "Normalized UpBar Volume";
		NormUpVol.DrawStyle = DRAWSTYLE_BAR;
		NormUpVol.LineWidth = 6;
		NormUpVol.PrimaryColor = RGB(0, 255, 0);
		NormUpVol.SecondaryColor = RGB(0, 150, 0);
		NormUpVol.SecondaryColorUsed = 1;
		
		NormDnVol.Name = "Normalized DnBar Volume";
		NormDnVol.DrawStyle = DRAWSTYLE_BAR;
		NormDnVol.LineWidth = 6;
		NormDnVol.PrimaryColor = RGB(255, 0, 0);
		NormDnVol.SecondaryColor = RGB(150, 0, 0);
		NormDnVol.SecondaryColorUsed = 1;
		
		VeryLowVolume.Name = "VeryLowVolume";
		VeryLowVolume.DrawStyle = DRAWSTYLE_LINE;
		VeryLowVolume.PrimaryColor = RGB(255, 128, 128);
		VeryLowVolume.LineWidth = 10;
		
		LowVolume.Name = "LowVolume";
		LowVolume.DrawStyle = DRAWSTYLE_LINE;
		LowVolume.PrimaryColor = RGB(155, 227, 255);
		LowVolume.LineWidth = 10;
		
		HighVolume.Name = "HighVolume";
		HighVolume.DrawStyle = DRAWSTYLE_LINE;
		HighVolume.PrimaryColor = RGB(155, 227, 255);
		HighVolume.LineWidth = 10;
		
		VeryHighVolume.Name = "VeryHighVolume";
		VeryHighVolume.DrawStyle = DRAWSTYLE_FILLTOP;
		VeryHighVolume.PrimaryColor = RGB(220, 180, 255);
		
		UltraHighVolume.Name = "UltraHighVolume";
		UltraHighVolume.DrawStyle = DRAWSTYLE_LINE;
		UltraHighVolume.PrimaryColor = RGB(255, 128, 128);
		UltraHighVolume.LineWidth = 10;
		
		AvgVolumeMarketHours.Name = "AvgVolumeMarketHours";
		AvgVolumeMarketHours.DrawStyle = DRAWSTYLE_LINE;
		AvgVolumeMarketHours.PrimaryColor = RGB(255, 0, 0);
		AvgVolumeMarketHours.LineWidth = 2;
		
		AvgNormVolume.Name = "Avg Normalized Volume";
		AvgNormVolume.DrawStyle = DRAWSTYLE_LINE;
		AvgNormVolume.PrimaryColor = RGB(0, 0, 160);
		AvgNormVolume.LineWidth = 2;
		
		MarketOpenHour.Name = "MarketOpenHour";
		MarketOpenHour.SetInt(9);
		MarketOpenMinute.Name = "MarketOpenMinute";
		MarketOpenMinute.SetInt(30);
		MarketCloseHour.Name = "MarketCloseHour";
		MarketCloseHour.SetInt(16);
		MarketCloseMinute.Name = "MarketCloseMinute";
		MarketCloseMinute.SetInt(0);
		
		sc.AutoLoop = 1;
		
		return;
	}
	
	Volume[sc.Index] = sc.Volume[sc.Index];
	
	if(sc.GetBarHasClosedStatus(sc.Index)==BHCS_BAR_HAS_CLOSED){

		int Time = sc.BaseDateTimeIn.TimeAt(sc.Index);
		int Hour, Minute, Second;
		TIME_TO_HMS(Time, Hour, Minute, Second);
		if (Volume[sc.Index]>0){
			T[Hour][Minute]=T[Hour][Minute]+Volume[sc.Index];iT[Hour][Minute]++;BarAvgVolume[sc.Index]=T[Hour][Minute]/iT[Hour][Minute];
			if(Hour >= 9 && Hour < 16){
				if((Hour == 9 && Minute > 29) || Hour > 9){
					MarketVolSum=MarketVolSum+Volume[sc.Index];iMarketVolSum++;MarketAvgVol=MarketVolSum/iMarketVolSum;
				}
			}
		}
		AvgVolumeMarketHours[sc.Index]=MarketAvgVol;
		
		NormVolume[sc.Index]=Volume[sc.Index]*(MarketAvgVol/BarAvgVolume[sc.Index]);
		if(NormVolume[sc.Index] > 0){
			NormVolSum=NormVolSum+NormVolume[sc.Index]; iNormVolSum++;
			NormAvgVol=NormVolSum/iNormVolSum;
			AvgNormVolume[sc.Index]=NormAvgVol;
			if(sc.Close[sc.Index] >= sc.Close[sc.Index-1]){
				// UpBar
				NormUpVol[sc.Index]=NormVolume[sc.Index];
				if (NormVolume[sc.Index] < NormVolume[sc.Index-1]) { 
					NormUpVol.DataColor[sc.Index] = NormUpVol.SecondaryColor;
				} else {
					NormUpVol.DataColor[sc.Index] = NormUpVol.PrimaryColor;
				}
				if (NormUpVol[sc.Index] > (3*NormAvgVol)) NormUpVol[sc.Index]=3*NormAvgVol;
				NormDnVol[sc.Index]=0;
			} else {
				// DnBar
				NormDnVol[sc.Index]=NormVolume[sc.Index];
				if (NormVolume[sc.Index] < NormVolume[sc.Index-1]) { 
					NormDnVol.DataColor[sc.Index] = NormDnVol.SecondaryColor;
				} else {
					NormDnVol.DataColor[sc.Index] = NormDnVol.PrimaryColor;
				}
				if (NormDnVol[sc.Index] > (3*NormAvgVol)) NormDnVol[sc.Index]=3*NormAvgVol;
				NormUpVol[sc.Index]=0;
			}
			
			if (NormVolume[sc.Index]>0){
				TN[Hour][Minute]=TN[Hour][Minute]+NormVolume[sc.Index];iTN[Hour][Minute]++;BarAvgNormVolume[sc.Index]=TN[Hour][Minute]/iTN[Hour][Minute];
			}
		}
		UltraHighVolume[sc.Index]=(2*NormAvgVol)*0.90;
		VeryHighVolume[sc.Index]=(2*NormAvgVol)*0.90;
		HighVolume[sc.Index]=(2*NormAvgVol)*0.55;
		LowVolume[sc.Index]=(2*NormAvgVol)*0.45;
		VeryLowVolume[sc.Index]=(2*NormAvgVol)*0.15;
	}
}

