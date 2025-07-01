// The top of every source code file must include this line
#include "sierrachart.h"


/*==========================================================================*/
//
// Clock
//
/*==========================================================================*/

SCSFExport scsf_Clock(SCStudyInterfaceRef sc)
{
    // Enums
    enum e_FontWeight {
        FONT_WEIGHT_NORMAL,
        FONT_WEIGHT_BOLD
    };
    enum e_TimeMode {
        SYSTEM_TIME,
        BAR_TIME
    };
    enum e_Timezone {
        CHICAGO,
        NEWYORK,
        LONDON
    };

    // Inputs
    SCInputRef HorizontalPosition    = sc.Input[0];
    SCInputRef VerticalPosition        = sc.Input[1];
    SCInputRef FontSize                = sc.Input[2];
    SCInputRef FontColor            = sc.Input[3];
    SCInputRef FontWeight            = sc.Input[4];
    SCInputRef BkgdColor            = sc.Input[5];
    SCInputRef TimeMode                = sc.Input[6];
    SCInputRef TimeZone                = sc.Input[7];
    SCInputRef ShowTimeZoneLabel    = sc.Input[8];

    // Defaults
    if (sc.SetDefaults)
    {
        sc.GraphName = "Clock";
        sc.StudyDescription = "Displays a chart label for Chicago, New York or London timezones.";

        // Inputs

        HorizontalPosition.Name = "Horizontal Position";
        HorizontalPosition.SetInt(1);
        HorizontalPosition.SetIntLimits(1, 100);

        VerticalPosition.Name = "Vertical Position";
        VerticalPosition.SetInt(4);
        VerticalPosition.SetIntLimits(1, 100);

        FontSize.Name = "Font Size";
        FontSize.SetInt(16);

        FontColor.Name = "Font Color";
        FontColor.SetColor(255,255,255);

        FontWeight.Name = "Font Weight";
        FontWeight.SetCustomInputStrings("Normal;Bold");
        FontWeight.SetCustomInputIndex(1);

        BkgdColor.Name = "Background Color";
        BkgdColor.SetColor(0,0,0);

        TimeMode.Name = "Time Mode";
        TimeMode.SetCustomInputStrings("Current System Time;Latest Time From Current Bar");
        TimeMode.SetCustomInputIndex(0);

        TimeZone.Name = "Time Zone";
        TimeZone.SetCustomInputStrings("Chicago;New York;London");
        TimeZone.SetCustomInputIndex(0);

        ShowTimeZoneLabel.Name = "Show Time Zone Label";
        ShowTimeZoneLabel.SetYesNo(true);

        // Set Graph Region
        sc.GraphRegion = 0;

        // Auto Looping
        sc.AutoLoop = 0;

        // Set To True For Development Only
        sc.FreeDLL = false;

        // Must return
        return;
    }

    //
    // Init
    //

    SCString Text, Label;
    s_UseTool Tool;
    SCDateTime Time;

    int LineNumber;
    int Hour, Minute, Second;

    //
    // Get Time
    //

    switch (TimeMode.GetIndex())
    {
        case SYSTEM_TIME:
            Time = sc.CurrentSystemDateTime;
            sc.UpdateAlways = true;
            LineNumber = 74730000;
            break;

        case BAR_TIME:
            Time = sc.LatestDateTimeForLastBar;
            sc.UpdateAlways = false;
            LineNumber = 74730010;
            break;
    }

    switch (TimeZone.GetIndex())
    {
        case CHICAGO:
            Time = sc.ConvertToSCTimeZone(Time, TIMEZONE_CHICAGO);
            Label = "Chicago ";
            LineNumber += 1;
            break;

        case NEWYORK:
            Time = sc.ConvertToSCTimeZone(Time, TIMEZONE_NEW_YORK);
            Label = "New York ";
            LineNumber += 2;
            break;

        case LONDON:
            Time = sc.ConvertToSCTimeZone(Time, TIMEZONE_LONDON);
            Label = "London ";
            LineNumber += 3;
            break;
    }

    Time.GetTimeHMS(Hour, Minute, Second);
    Text.Format("%02d:%02d:%02d", Hour, Minute, Second);

    if (ShowTimeZoneLabel.GetYesNo())
        Text = Label+Text;

    //
    // Print Clock
    //

    Tool.Clear();
    Tool.DrawingType = DRAWING_TEXT;
    Tool.AddMethod = UTAM_ADD_OR_ADJUST;

    Tool.Region = 0;
    Tool.ChartNumber = 0;
    Tool.LineNumber =  LineNumber;

    Tool.BeginDateTime = HorizontalPosition.GetInt();
    Tool.BeginValue = 100-(VerticalPosition.GetInt()-1);
    Tool.UseRelativeVerticalValues = true;

    Tool.Text = Text;
    Tool.Color = FontColor.GetColor();
    Tool.FontBackColor = BkgdColor.GetColor();
    Tool.FontSize = FontSize.GetInt();

    if (FontWeight.GetIndex() == FONT_WEIGHT_BOLD)
        Tool.FontBold = true;

    sc.UseTool(Tool);

} 