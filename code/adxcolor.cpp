
#include "sierrachart.h"
//DEVELOPED BY TCAST
//tcast@charter.net
//SCDLLInit("ADX_COLOR");




/***********************************************************************/
SCSFExport scsf_ADXColor(SCStudyGraphRef sc)
{
    if(sc.SetDefaults)
    {
        sc.GraphName="ADX COLOR";
        sc.StudyDescription="ADX coloring based on +/- 30 (or whatever other) level by gregorfx.";

        sc.Subgraph[0].Name="ADX COLOR ";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[0].LineWidth = 3;

		sc.Input[0].Name = "DX Length";
		sc.Input[0].SetInt(14);
		sc.Input[0].SetIntLimits(1, 1000);
		
		
		sc.Input[1].Name = "DX MOVING AVG LENGTH";
		sc.Input[1].SetInt(14);
		sc.Input[1].SetIntLimits(1, 1000);
		
		sc.Input[2].Name = "ALERT LEVEL";
		sc.Input[2].SetInt(30);
		sc.Input[2].SetIntLimits(1, 1000);
		
		sc.FreeDLL = 0;
        sc.AutoLoop = 1;
        sc.GraphRegion = 0;
        return;
    }
int i = sc.Index;
int len = sc.Input[0].GetInt();
int len2 = sc.Input[1].GetInt();
int alrt = sc.Input[2].GetInt();
	const DWORD red = RGB(255, 0, 0);	
	const DWORD blue = RGB(0, 0, 255);	


	
	sc.ADX(sc.BaseDataIn, sc.Subgraph[0], sc.Index, len, len2);

	if( sc.Subgraph[0][i] >=alrt)
	{
		sc.Subgraph[0].DataColor[sc.Index] =red;		
	}
else 
	{
		sc.Subgraph[0].DataColor[sc.Index] = blue;		
	}
	
	}

