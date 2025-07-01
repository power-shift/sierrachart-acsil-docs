
#include "sierrachart.h"
//DEVELOPED BY TCAST
//tcast@charter.net
//SCDLLInit("SierraTrend");


/***********************************************************************/
SCSFExport scsf_SierraTrend(SCStudyGraphRef sc)
{
    if(sc.SetDefaults)
    {
        sc.GraphName="SierraTREND";
        sc.StudyDescription="SierraTREND. TTM trend replica by tcast. ";

        sc.Subgraph[0].Name="sierraTREND BAR";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[0].LineWidth = 3;

		sc.Input[0].Name = "Length";
		sc.Input[0].SetInt(5);
		sc.Input[0].SetIntLimits(1, 1000);
		
		sc.FreeDLL = 0;
        sc.AutoLoop = 1;
        sc.GraphRegion = 0;
        return;
    }
    
int i = sc.Index;
int len = sc.Input[0].GetInt();
	const DWORD upColor = RGB(0, 0, 255);	
	const DWORD downColor = RGB(255, 0, 0);	

	sc.Subgraph[0][i]=sc.BaseDataIn[SC_LAST][i];

	if( sc.BaseData[SC_OPEN][i] >=sc.BaseData[SC_HIGH][i-len])
	{
		sc.Subgraph[0].DataColor[sc.Index] =upColor ;		
	}
	else if ( sc.BaseData[SC_OPEN][i] <=sc.BaseData[SC_LOW][i-len])
	{
		sc.Subgraph[0].DataColor[sc.Index] = downColor;		
	}
else 
	{
		sc.Subgraph[0].DataColor[sc.Index] = sc.Subgraph[0].DataColor[sc.Index-1];		
	}
	
	}

