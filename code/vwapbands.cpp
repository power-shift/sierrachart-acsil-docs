#include "sierrachart.h"


//SCDLLName("VwapBands")



SCSFExport scsf_VwapBands(SCStudyGraphRef sc)
{
    if (sc.SetDefaults)
    {        
        sc.GraphName = "VwapBands";
        sc.StudyDescription = "<a href=""http://www.sierrachart.com/supportboard/showthread.php?t=21384"">Need help with VWAP bands, etc</a>.";
        sc.GraphRegion = 0;
        sc.ScaleRangeType = SCALE_SAMEASREGION; //So it doesn't squish the chart
        
        sc.StudyDescription = "VwapBands";
        
        /*Optional:
        Have "sc.FreeDLL = 0" when you are finished developing your function. This makes calling your function faster. However, if you need
        to make changes to the code after applying it to a chart, you will need to restart SierraChart (SC) to release the DLL.
        Alternatively, if you want to make changes and then test it have "sc.FreeDLL = 1" so you do not have to repeatedly restart SC. */
        sc.FreeDLL = 0;

        sc.AutoLoop = 1;
        
        sc.Subgraph[0].Name = "Vwap";
        sc.Subgraph[0].PrimaryColor = RGB(0, 0, 255); 
        sc.Subgraph[0].LineWidth = 2;
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;
        sc.Subgraph[0].LineStyle = LINESTYLE_SOLID;
        
        sc.Subgraph[1].Name = "Vwsd1 Upper";
        sc.Subgraph[1].PrimaryColor = RGB(0, 0, 255); 
        sc.Subgraph[1].LineWidth = 1;
        sc.Subgraph[1].DrawStyle = DRAWSTYLE_LINE;
        sc.Subgraph[1].LineStyle = LINESTYLE_DASH;
        
        sc.Subgraph[2].Name = "Vwsd1 Lower";
        sc.Subgraph[2].PrimaryColor = RGB(0, 0, 255); 
        sc.Subgraph[2].LineWidth = 1;
        sc.Subgraph[2].DrawStyle = DRAWSTYLE_LINE;
        sc.Subgraph[2].LineStyle = LINESTYLE_DASH;
        
        sc.Subgraph[3].Name = "Vwsd2 Upper";
        sc.Subgraph[3].PrimaryColor = RGB(0, 0, 255); 
        sc.Subgraph[3].LineWidth = 1;
        sc.Subgraph[3].DrawStyle = DRAWSTYLE_LINE;
        sc.Subgraph[3].LineStyle = LINESTYLE_DASH;
        
        sc.Subgraph[4].Name = "Vwsd2 Lower";
        sc.Subgraph[4].PrimaryColor = RGB(0, 0, 255); 
        sc.Subgraph[4].LineWidth = 1;
        sc.Subgraph[4].DrawStyle = DRAWSTYLE_LINE;
        sc.Subgraph[4].LineStyle = LINESTYLE_DASH;
        
        sc.Subgraph[5].Name = "Vwsd3 Upper";
        sc.Subgraph[5].PrimaryColor = RGB(0, 0, 255); 
        sc.Subgraph[5].LineWidth = 1;
        sc.Subgraph[5].DrawStyle = DRAWSTYLE_LINE;
        sc.Subgraph[5].LineStyle = LINESTYLE_DASH;
        
        sc.Subgraph[6].Name = "Vwsd3 Lower";
        sc.Subgraph[6].PrimaryColor = RGB(0, 0, 255); 
        sc.Subgraph[6].LineWidth = 1;
        sc.Subgraph[6].DrawStyle = DRAWSTYLE_LINE;
        sc.Subgraph[6].LineStyle = LINESTYLE_DASH;
        
        
        sc.Input[0].Name  = "Input Data";
        sc.Input[0].SetInputDataIndex(SC_LAST);
        
        sc.Input[1].Name = "Display Historically";
        sc.Input[1].SetYesNo(1);
        
        sc.Input[2].Name = "Use Chart Settings Start Time instead of 0:00";
        sc.Input[2].SetYesNo(0);
        

        return;
    }

    long InputDataIndex = sc.Input[0].GetInputDataIndex();
    int DisplayHistorically = sc.Input[1].GetYesNo(); // Display historically (Yes/No)
    int Ucssti0 = sc.Input[2].GetYesNo(); // Use Chart Settings Start Time instead of 0:00 (Yes/No)
    
    
    int Tsst, Cbd; // Trading session start time / Current bar date
    SCDateTime Cbdt, Pbdt, Tssdt; // Current bar date/time / Previous bar date/time / Trading session start date/time

    bool Ntsb; // New trading session bar
    
    int& Ntsbi = sc.PersistVars->i1; // New trading session bar index
    
    SCFloatArrayRef InputData = sc.Subgraph[0].Arrays[0]; // InputData
    SCFloatArrayRef Vol = sc.Subgraph[0].Arrays[1]; // Volume of bar
    SCFloatArrayRef Rsidtv = sc.Subgraph[0].Arrays[2]; // Running sum of (InputData) * (Volume)
    SCFloatArrayRef Rsv = sc.Subgraph[0].Arrays[3]; // Running sum of Volume
    SCFloatArrayRef Vwap = sc.Subgraph[0].Arrays[4]; // Volume weighted average price
    SCFloatArrayRef Rssd = sc.Subgraph[0].Arrays[5]; // Running sum of (squared deviations of InputData from Vwap) * (Volume)
    SCFloatArrayRef Vwsd = sc.Subgraph[0].Arrays[6]; // Volume weighted standard deviation

    
    Cbd = sc.BaseDateTimeIn[sc.Index].GetDate();
    
    // If "Use Chart Settings Start Time instead of 0:00" is "Yes", then if using the evening session times, then use evening session
    // start time otherwise use day session start time
    // If "Use Chart Settings Start Time instead of 0:00" is "No" then use 0:00 as start time
    Tsst = Ucssti0 ? (sc.UseSecondStartEndTimes ? sc.StartTime2 : sc.StartTime1) : 0;
    
    Tssdt = COMBINE_DATE_TIME(Cbd, Tsst);
    
    Cbdt = sc.BaseDateTimeIn[sc.Index];
    
    if (sc.Index > 0)
    { Pbdt = sc.BaseDateTimeIn[sc.Index - 1]; }
    else
    { Pbdt = 0; }
    
    
    Ntsb = (Cbdt >= Tssdt && Pbdt < Tssdt) ? true : false;

    
    InputData[sc.Index] = sc.BaseDataIn[InputDataIndex][sc.Index];
    Vol[sc.Index] = sc.BaseDataIn[SC_VOLUME][sc.Index];
    
    if (Ntsb)
    {
        Rsidtv[sc.Index] = InputData[sc.Index] * Vol[sc.Index];
        Rsv[sc.Index] = Vol[sc.Index];
        Vwap[sc.Index] = Rsv[sc.Index] > 0 ? (Rsidtv[sc.Index] / Rsv[sc.Index]) : 0;
        Rssd[sc.Index] = (InputData[sc.Index] - Vwap[sc.Index]) * (InputData[sc.Index] - Vwap[sc.Index]) * Vol[sc.Index];
        Vwsd[sc.Index] = Rsv[sc.Index] > 0 ? sqrt(Rssd[sc.Index] / Rsv[sc.Index]) : 0;    
        

        sc.Subgraph[0][sc.Index] = Vwap[sc.Index];
        sc.Subgraph[1][sc.Index] = Vwap[sc.Index] + 1 * Vwsd[sc.Index];
        sc.Subgraph[2][sc.Index] = Vwap[sc.Index] - 1 * Vwsd[sc.Index];
        sc.Subgraph[3][sc.Index] = Vwap[sc.Index] + 2 * Vwsd[sc.Index];
        sc.Subgraph[4][sc.Index] = Vwap[sc.Index] - 2 * Vwsd[sc.Index];
        sc.Subgraph[5][sc.Index] = Vwap[sc.Index] + 3 * Vwsd[sc.Index];
        sc.Subgraph[6][sc.Index] = Vwap[sc.Index] - 3 * Vwsd[sc.Index];
        
        
        if (!DisplayHistorically && sc.Index > 0)
        {
            int Ptslbi = sc.Index - 1; // Previous trading session last bar index
            
            for (int a = Ptslbi - 1; a >= Ntsbi; --a)
            {
                sc.Subgraph[0][a] = Vwap[Ptslbi];
                sc.Subgraph[1][a] = Vwap[Ptslbi] + 1 * Vwsd[Ptslbi];
                sc.Subgraph[2][a] = Vwap[Ptslbi] - 1 * Vwsd[Ptslbi];
                sc.Subgraph[3][a] = Vwap[Ptslbi] + 2 * Vwsd[Ptslbi];
                sc.Subgraph[4][a] = Vwap[Ptslbi] - 2 * Vwsd[Ptslbi];
                sc.Subgraph[5][a] = Vwap[Ptslbi] + 3 * Vwsd[Ptslbi];
                sc.Subgraph[6][a] = Vwap[Ptslbi] - 3 * Vwsd[Ptslbi];
            }
        }
        
        Ntsbi = sc.Index;
    }
    else
    {
        Rsidtv[sc.Index] = InputData[sc.Index] * Vol[sc.Index] + Rsidtv[sc.Index - 1];
        Rsv[sc.Index] = Vol[sc.Index] + Rsv[sc.Index - 1];
        Vwap[sc.Index] = Rsv[sc.Index] > 0 ? (Rsidtv[sc.Index] / Rsv[sc.Index]) : 0;
        Rssd[sc.Index] = (InputData[sc.Index] - Vwap[sc.Index]) * (InputData[sc.Index] - Vwap[sc.Index]) * Vol[sc.Index] + Rssd[sc.Index - 1];
        Vwsd[sc.Index] = Rsv[sc.Index] > 0 ? sqrt(Rssd[sc.Index] / Rsv[sc.Index]) : 0;    
        
        
        sc.Subgraph[0][sc.Index] = Vwap[sc.Index];
        sc.Subgraph[1][sc.Index] = Vwap[sc.Index] + 1 * Vwsd[sc.Index];
        sc.Subgraph[2][sc.Index] = Vwap[sc.Index] - 1 * Vwsd[sc.Index];
        sc.Subgraph[3][sc.Index] = Vwap[sc.Index] + 2 * Vwsd[sc.Index];
        sc.Subgraph[4][sc.Index] = Vwap[sc.Index] - 2 * Vwsd[sc.Index];
        sc.Subgraph[5][sc.Index] = Vwap[sc.Index] + 3 * Vwsd[sc.Index];
        sc.Subgraph[6][sc.Index] = Vwap[sc.Index] - 3 * Vwsd[sc.Index];
        
        
        if (!DisplayHistorically && sc.Index == sc.ArraySize - 1)
        {
            int Ctslbi = sc.Index; // Current trading session last bar index
        
            for (int a = Ctslbi - 1; a >= Ntsbi; --a)
            {
                sc.Subgraph[0][a] = Vwap[Ctslbi];
                sc.Subgraph[1][a] = Vwap[Ctslbi] + 1 * Vwsd[Ctslbi];
                sc.Subgraph[2][a] = Vwap[Ctslbi] - 1 * Vwsd[Ctslbi];
                sc.Subgraph[3][a] = Vwap[Ctslbi] + 2 * Vwsd[Ctslbi];
                sc.Subgraph[4][a] = Vwap[Ctslbi] - 2 * Vwsd[Ctslbi];
                sc.Subgraph[5][a] = Vwap[Ctslbi] + 3 * Vwsd[Ctslbi];
                sc.Subgraph[6][a] = Vwap[Ctslbi] - 3 * Vwsd[Ctslbi];
            }
        }
    }
} 