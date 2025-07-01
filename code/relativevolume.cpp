#include "sierrachart.h"

int RVCalc(SCDateTimeArrayRef DateTimeIn, SCBaseDataRef DataIn, c_ArrayWrapper<s_SCSubgraph_260> SgOut, int position, int lookback);

SCSFExport scsf_RelativeVolume(SCStudyGraphRef sc) 
{ 
    if (sc.SetDefaults) 
    { 
        sc.GraphName = "Relative Volume";
        sc.ValueFormat = 0;
        sc.Subgraph[0].Name = "Volume";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_BAR;
        sc.Subgraph[0].LineWidth = 2;
        sc.Subgraph[0].PrimaryColor = RGB(0,134,77);
        sc.Subgraph[0].SecondaryColor = RGB(192,0,0);
        sc.Subgraph[0].SecondaryColorUsed = 1;
        sc.Subgraph[0].AutoColoring = AUTOCOLOR_POSNEG;
        sc.Subgraph[1].Name = "Zero Line";
        sc.Subgraph[1].DrawStyle = DRAWSTYLE_LINE;
        sc.Subgraph[1].LineWidth = 1;
        sc.Subgraph[1].PrimaryColor = RGB(0,0,0);
        sc.Input[0].Name = "Lookback (>=5)";
        sc.Input[0].SetInt(5);
        sc.Input[0].SetIntLimits(5,10000);
        sc.DrawZeros = 0;
        sc.FreeDLL = 0;
        return; 
    } 

    int position, lookback = sc.Input[0].GetInt();

    if (sc.Index != 0)
    {
        position = sc.Index - 1;
       while (++position < sc.ArraySize) RVCalc(sc.BaseDateTimeIn, sc.BaseData, sc.Subgraph, position, lookback);
    }
    else
    {
        position = sc.ArraySize;
        while (--position > 0)
        {
            if (RVCalc(sc.BaseDateTimeIn, sc.BaseData, sc.Subgraph, position, lookback) == 1)
            {
                if (position == sc.ArraySize - 1) sc.AddMessageToLog("ERROR: Insufficient Bars Loaded to Run Study.",1);
                break;
            }
        }   
    }
    return;
}

int RVCalc(SCDateTimeArrayRef DateTimeIn, SCBaseDataRef DataIn, c_ArrayWrapper<s_SCSubgraph_260> SgOut, int position, int lookback)
{
    double cumvol = 0;
    int counter = 0, offset = position;
    while (--offset >= 0 && counter < lookback)
    {
        if (DateTimeIn.TimeAt(position)*1  == DateTimeIn.TimeAt(offset)*1)
        {
            counter++;
            cumvol += DataIn[SC_VOLUME][offset];
        }
    }
    if (counter == lookback)
    {
        SgOut[0][position] = (100 * DataIn[SC_VOLUME][position] / (cumvol / lookback)) - 100;
        SgOut[1][position] = 0;
        return(0);
    }
    return(1);
}
