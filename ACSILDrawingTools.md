# Using Drawing Tools From an Advanced Custom Study

* [Introduction](#introduction)
* [Using Tools with sc.UseTool()](#usingtools)
  + [Preventing More Than One Chart Drawing Per Chart Bar or More Drawings than Intended](#preventingmorethanonechartdrawingperchartbar)
  + [Return Value](#returnvalue)
  + [Code Example](#codeexample)
  + [Adjusting Existing Chart Drawings](#adjustingchartdrawings)
* [Drawing Tools and s\_UseTool Member Descriptions](#usetoolmembers)
  + [s\_UseTool::DrawingType](#susetooldrawingtype)
  + [s\_UseTool::AddMethod](#susetooladdmethod)
  + [s\_UseTool::ChartNumber](#susetoolchartnumber)
  + [s\_UseTool::LineNumber](#susetoollinenumber)
  + [s\_UseTool::BeginDateTime](#susetoolbegindatetime)
  + [s\_UseTool::EndDateTime](#susetoolenddatetime)
  + [s\_UseTool::ThirdDateTime](#susetoolthirddatetime)
  + [s\_UseTool::BeginIndex](#susetoolbeginindex)
  + [s\_UseTool::EndIndex](#susetoolendindex)
  + [s\_UseTool::ThirdIndex](#susetoolthirdindex)
  + [s\_UseTool::UseRelativeVerticalValues / s\_UseTool::UseRelativeValue](#susetooluserelativeverticalvalues)
  + [s\_UseTool::BeginValue](#susetoolbeginvalue)
  + [s\_UseTool::EndValue](#susetoolendvalue)
  + [s\_UseTool::ThirdValue](#susetoolthirdvalue)
  + [s\_UseTool::Region](#susetoolregion)
  + [s\_UseTool::Color](#susetoolcolor)
  + [s\_UseTool::SecondaryColor](#susetoolsecondarycolor)
  + [s\_UseTool::TransparencyLevel](#susetooltransparencylevel)
  + [s\_UseTool::SquareEdge](#susetoolsquareedge)
  + [s\_UseTool::LineWidth](#susetoollinewidth)
  + [s\_UseTool::LineStyle](#susetoollinestyle)
  + [s\_UseTool::Text](#susetooltext)
  + [s\_UseTool::DisplayHorizontalLineValue](#susetooldisplayhorizontallinevalue)
  + [s\_UseTool::FontSize](#susetoolfontsize)
  + [s\_UseTool::FontBackColor](#susetoolfontbackcolor)
  + [s\_UseTool::FontFace](#susetoolfontface)
  + [s\_UseTool::FontBold](#susetoolfontbold)
  + [s\_UseTool::FontItalic](#susetoolfontitalic)
  + [s\_UseTool::TextAlignment](#susetooltextalignment)
  + [s\_UseTool::ReverseTextColor](#susetoolreversetextcolor)
  + [s\_UseTool::MarkerType](#susetoolmarkertype)
  + [s\_UseTool::MarkerSize](#susetoolmarkersize)
  + [s\_UseTool::UseBarSpacingForMarkerSize](#susetoolusebarspacingformarkersize)
  + [s\_UseTool::ShowVolume](#susetoolshowvolume)
  + [s\_UseTool::ShowAskBidDiffVolume](#susetoolshowaskbiddiffvolume)
  + [s\_UseTool::ShowPriceDifference](#susetoolshowpricedifference)
  + [s\_UseTool::ShowTickDifference](#susetoolshowtickdifference)
  + [s\_UseTool::ShowCurrencyValue](#susetoolshowcurrencyvalue)
  + [s\_UseTool::ShowPercentChange](#susetoolshowpercentchange)
  + [s\_UseTool::ShowTimeDifference](#susetoolshowtimedifference)
  + [s\_UseTool::ShowNumberOfBars](#susetoolshownumberofbars)
  + [s\_UseTool::ShowAngle](#susetoolshowangle)
  + [s\_UseTool::ShowEndPointPrice](#susetoolshowendpointprice)
  + [s\_UseTool::ShowEndPointDateTime](#susetoolshowendpointdatetime)
  + [s\_UseTool::ShowEndPointDate](#susetoolshowendpointdate)
  + [s\_UseTool::ShowEndPointTime](#susetoolshowendpointtime)
  + [s\_UseTool::MultiLineLabel](#susetoolmultilinelabel)
  + [s\_UseTool::ShowPercent](#susetoolshowpercent)
  + [s\_UseTool::ShowPrice](#susetoolshowprice)
  + [s\_UseTool::RoundToTickSize](#susetoolroundtoticksize)
  + [s\_UseTool::ExtendLeft](#susetoolextendleft)
  + [s\_UseTool::ExtendRight](#susetoolextendright)
  + [s\_UseTool::TimeExpVerticals](#susetooltimeexpverticals)
  + [s\_UseTool::TimeExpTopLabel1](#susetooltimeexptoplabel1)
  + [s\_UseTool::TimeExpBottomLabel1](#susetooltimeexpbottomlabel1)
  + [s\_UseTool::TimeExpBasedOnTime](#susetooltimeexpbasedontime)
  + [s\_UseTool::TransparentLabelBackground](#susetooltransparentlabelbackground)
  + [s\_UseTool::FixedSizeArrowHead](#susetoolfixedsizearrowhead)
  + [s\_UseTool::RetracementLevels[]](#s_UseTool_RetracementLevels)
  + [s\_UseTool::LevelColor[]](#s_UseTool_LevelColor)
  + [s\_UseTool::LevelWidth[]](#s_UseTool_LevelWidth)
  + [s\_UseTool::LevelStyle[]](#s_UseTool_LevelStyle)
  + [s\_UseTool::AddAsUserDrawnDrawing](#susetooladdasuserdrawndrawing)
  + [s\_UseTool::DrawUnderneathMainGraph](#susetooldrawunderneathmaingraph)
  + [s\_UseTool::UseToolConfigNum](#susetoolusetoolconfignum)
  + [s\_UseTool::FlatEdge](#susetoolflatedge)
  + [s\_UseTool::DrawWithinRegion](#susetooldrawwithinregion)
  + [s\_UseTool::CenterPriceLabels](#centerpricelabels)
  + [s\_UseTool::NoVerticalOutline](#susetoolnoverticaloutline)
  + [s\_UseTool::AllowSaveToChartbook](#susetoolallowsavetochartbook)
  + [s\_UseTool::ShowBeginMark](#susetoolshowbeginmark)
  + [s\_UseTool::ShowEndMark](#susetoolshowendmark)
  + [s\_UseTool::AssociatedStudyID](#susetoolassociatedstudyid)
  + [s\_UseTool::HideDrawing](#susetoolhidedrawing)
  + [s\_UseTool::LockDrawing](#susetoollockdrawing)
  + [s\_UseTool::DrawOutlineOnly](#susetooldrawoutlineonly)
  + [s\_UseTool::NumCycles](#susetoolnumcycles)
  + [s\_UseTool::ExtendMultiplier](#susetoolextendmultiplier)
  + [s\_UseTool::DrawMidline](#susetooldrawmidline)
  + [s\_UseTool::AllowCopyToOtherCharts](#susetoolallowcopytoothercharts)
* [sc.ChartDrawingExists()](#scchartdrawingexists)
* [sc.UserDrawnChartDrawingExists()](#scuserdrawnchartdrawingexists)
* [sc.GetUserDrawnChartDrawing()](#scgetuserdrawnchartdrawing)
* [sc.GetLineNumberOfSelectedUserDrawnDrawing()](#scgetlinenumberofselecteduserdrawndrawing)
* [sc.GetUserDrawnDrawingByLineNumber()](#scgetuserdrawndrawingbylinenumber)
* [sc.GetACSDrawingByLineNumber()](#scgetacsdrawingbylinenumber)
* [sc.GetACSDrawingByIndex()](#scgetacsdrawingbyindex)
* [sc.GetACSDrawingsCount()](#scgetacsdrawingscount)
* [sc.DeleteACSChartDrawing()](#scdeleteacschartdrawing)
* [sc.DeleteUserDrawnACSDrawing()](#scdeleteuserdrawnacsdrawing)
* [RGB Color Values](#rgb)
* [Drawing Chart Drawings On Top of or Underneath Main Graph and Studies](#drawingchartdrawingsontopoforunderneath)
* [Adding Chart Drawings to Other Charts from an ACSIL Study Function](#addingchartdrawingstootherchartsfromacsilstudy)
* [Drawing Lines with a Specific Angle Using ACSIL](#drawinglineswithspecificangleusingacsil)

---

## Introduction

[Link](#introduction) - [Top](#top)

This page documents programmatically adding Chart Drawings and interacting with user drawn Chart Drawings through the [Advanced Custom Study Interface and Language](AdvancedCustomStudyInterfaceAndLanguage.md).

For information about Drawing Tools, refer to [Chart Drawing Tools](Tools.md).

## Using Tools with sc.UseTool()

[Link](#usingtools) - [Top](#top)

**Type:** ACSIL Function

Declaration: int **UseTool**(s\_UseTool& **UseTool**);

This page documents programmatically adding the same type of Chart Drawings to a chart from Advanced Custom Studies, that are normally drawn by a user using the [Chart Drawing Tools](Tools.md). Therefore, Advanced Custom Studies can independently add the same types of Chart Drawings to a chart programmatically.

Refer to the Sierra Chart [Advanced Custom Study Interface and Language](AdvancedCustomStudyInterfaceAndLanguage.md) (ACSIL) page for more information about the Advanced Custom Study Interface and Language.

To use the built-in Sierra Chart Drawing Tools from an Advanced Custom Study, you will use the **sc.UseTool()** function.

When calling this function, a Chart Drawing is added to an internal list in a chart. The **sc.UseTool()** function supports many different drawing types. This is a very powerful feature. You can place various types of Chart Drawing objects on a chart or place Text anywhere on a chart, and dynamically move those objects. You can control the foreground and background colors and font size of Text.

The **sc.UseTool()** function uses the **s\_UseTool** structure to specify the various parameters for the tool. You need to define an instance of the **s\_UseTool** structure in your function. **sc.UseTool()** takes a reference to the **s\_UseTool** instance you defined in the study function.

Set the relevant members of the **s\_UseTool** structure, call the **sc.UseTool()** function and pass an instance of **s\_UseTool** to that function. The **DrawingType** member of the **s\_UseTool** structure specifies which drawing tool to use.

Before setting the members of **s\_UseTool**, always be sure to use the **Clear()** function of the **s\_UseTool** structure to initialize the structure. This is especially important if you are using the same instance of the structure to multiple calls of **sc.UseTool()**. Refer to the code example below.

The [s\_UseTool Member Descriptions](#usetoolmembers) section documents the members of the s\_UseTool structure for all of the imported drawing tools.

For actual code examples, refer to the **scsf\_UseToolExample\*** study functions located in the **/ACS\_Source/studies.cpp**  file in the folder where Sierra Chart is installed to on your system.

For another example to place text on a chart, refer to the **scsf\_CountDownTimer** in the /ACS\_Source/studies2.cpp file.

This paragraph applies when **s\_UseTool::AddAsUserDrawnDrawing** is not set which is almost always the case. Chart Drawings added with **sc.UseTool()**, are automatically *deleted* from the chart when the study is removed from the chart, or when the study is fully recalculated, unless you have set **s\_UseTool::AddAsUserDrawnDrawing** to 1 (TRUE). Therefore, when **s\_UseTool::AddAsUserDrawnDrawing** is set to 0, there is no need to delete Chart Drawings manually by using **sc.DeleteACSChartDrawing()**.

Expressly deleting a chart drawing with [sc.DeleteACSChartDrawing()](#scdeleteacschartdrawing) is only needed for more specialized purposes.

On a recalculation of a study that has added non-user drawn Chart Drawings through ACSIL will have those Chart Drawings automatically deleted.

Chart drawings added by an ACSIL function are never saved to a Chartbook. They exist only in temporary memory.

### Preventing More Than One Chart Drawing Per Chart Bar or More Drawings than Intended

[Link](#preventingmorethanonechartdrawingperchartbar) - [Top](#top)

When adding Chart Drawings with **sc.UseTool()** it is important not to add more than one Chart Drawing per chart bar or more than intended unless that is the intention. During a full recalculation of the study, if one Chart Drawing is added per chart bar, there will not be a problem in this case.

However, during normal chart updating [sc.Index](ACSIL_Members_Variables_And_Arrays.md#scindex) is set to the index of the last bar in the chart from the prior chart update. Therefore, it is important not to add another Chart Drawing to the bar at that index if that is not the intention. Even if it is the intention to add more than one Chart Drawing per bar index, you need to be careful that you do not add more Chart Drawings per chart bar index than intended.

When updating the existing Chart Drawing at a particular bar index or at sc.Index, set [s\_UseTool::AddMethod](#addmethod) to **UTAM\_ADD\_OR\_ADJUST** and specify the same [s\_UseTool::LineNumber](#linenumber) returned by the **sc.UseTool** function when the Chart Drawing was originally added. You will need to hold this LineNumber in a [Persistent Variable](ACSIL_Members_Functions.md#scgetpersistentint).

If you do not set [s\_UseTool::AddMethod](#addmethod) to **UTAM\_ADD\_OR\_ADJUST** and specify the same [s\_UseTool::LineNumber](#linenumber) originally returned for a Chart Drawing that you are updating and do not want to add again, then there will be a large number of Chart Drawings added to the chart and this will have a *serious negative performance and memory impact*. Make sure you are not creating this problem in your code!

### Return Value

[Link](#returnvalue) - [Top](#top)

**sc.UseTool()** returns 1 on success, 0 on failure.

### Code Example

[Link](#codeexample) - [Top](#top)

```cpp

// Marker example
s_UseTool Tool;
int UniqueLineNumber = 74191;//any random number.

Tool.Clear(); // Reset tool structure.  Good practice but unnecessary in this case.
Tool.ChartNumber = sc.ChartNumber;

Tool.DrawingType = DRAWING_MARKER;
Tool.LineNumber =  UniqueLineNumber +1;

BarIndex = max(0, sc.ArraySize - 35);

Tool.BeginDateTime = sc.BaseDateTimeIn[BarIndex];
Tool.BeginValue = sc.High[BarIndex];

Tool.Color = RGB(0,200,200);
Tool.AddMethod = UTAM_ADD_OR_ADJUST;

Tool.MarkerType = MARKER_X;
Tool.MarkerSize = 8;

Tool.LineWidth = 5;

sc.UseTool(Tool);
        
```

### Adjusting Existing Chart Drawings

[Link](#adjustingchartdrawings) - [Top](#top)

When a Chart Drawing is added to the chart through the use of the **sc.UseTool**  function, it can later be adjusted/modified. The method by which a chart drawing can be adjusted is by calling the **sc.UseTool** with [s\_UseTool::AddMethod](#addmethod) set to **UTAM\_ADD\_OR\_ADJUST**, which is the default.

When adjusting a drawing, set the **s\_UseTool::LineNumber** member to the same number that was previously set after the **sc.UseTool**  function returned when the Chart Drawing was originally added. The **LineNumber** that was automatically set can be remembered into a [persistent variable](ACSIL_Members_Functions.md#scgetpersistentint).

If more than one drawing uses the same LineNumber, only the first found drawing will be adjusted when adjusting a Chart Drawing, for performance reasons. Therefore, it is not considered best practice to use the same **LineNumber**  for different Chart Drawings added by the **sc.UseTool** function.

Set the other members of the s\_UseTool structure that you want to modify. The structure members that you do not want to change need to be left unset. For more information, refer to [AddMethod](#addmethod).

It is possible to modify a Chart Drawing that was added as a *user drawn* drawing. A drawing is considered a user drawn drawing if it was added with **sc.UseTool** and the **s\_UseTool::AddAsUserDrawnDrawing**  variable is set to 1.

When modifying a user drawn drawing, it is necessary to set **s\_UseTool::AddAsUserDrawnDrawing**  to modify it.

**sc.UseTool**  returns 1 upon a successful adjustment/modification of an existing chart drawing.

## Drawing Tools and s\_UseTool Member Descriptions

[Link](#usetoolmembers) - [Top](#top)

#### s\_UseTool::DrawingType

[Link](#susetooldrawingtype) - [Top](#top)

**Type:** DrawingTypeEnum

This member needs to be set to one of the following drawing types, unless you are adjusting an existing drawing:

* **DRAWING\_LINE**: Draws a Line on the chart.
* **DRAWING\_RAY**: Draws a Ray on the chart.
* **DRAWING\_EXTENDED\_LINE**: Draws an Extended Line (extends in both directions) on the chart.
* **DRAWING\_RECTANGLEHIGHLIGHT**: Draws a rectangle highlight drawing.
* **DRAWING\_RECTANGLE\_EXT\_HIGHLIGHT**: Draws a rectangle highlight drawing that extends either right or left.
* **DRAWING\_ELLIPSEHIGHLIGHT**: Draws an ellipse highlight drawing.
* **DRAWING\_TRIANGLE**: Draws a triangle drawing.
* **DRAWING\_TEXT**: This tool draws text anywhere on the chart and in any chart region. You can use both absolute and relative positioning. You can specify various font properties. A very good example of how to use this tool and what you can do can be found in the **scsf\_WoodiesPanel** function in the **/ACS\_Source/studies7.cpp** file. This is in the folder where Sierra Chart is installed to on your computer.
* **DRAWING\_STATIONARY\_TEXT**: This tool draws text on the chart using realtive positions.
* **DRAWING\_RETRACEMENT**: This tool draws a 2-point Retracement drawing on the chart.
* **DRAWING\_EXPANSION**: This tool draws a 2-point Expansion drawing on the chart.
* **DRAWING\_PRICE\_PROJECTION**: This tool draws a 3-point Projection drawing on the chart.
* **DRAWING\_CALCULATOR**: This tool draws a Chart Calculator line on the chart.
* **DRAWING\_HORIZONTALLINE**: This tool draws a Horizontal Line drawing on the chart. This horizontal line extends from the left side of the chart window to the right side of the chart window.
* **DRAWING\_HORIZONTAL\_RAY**: Draws a Horizontal Ray on the chart. This horizontal line extends from s\_UseTool::BeginDateTime to the right side of the chart window.
* **DRAWING\_HORIZONTAL\_LINE\_NON\_EXTENDED**: This tool draws a Horizontal Line on the chart which does not extend. It begins at s\_UseTool::BeginDateTime and ends at s\_UseTool::EndDateTime.
* **DRAWING\_VERTICALLINE**: This tool draws a Vertical line drawing on the chart.
* **DRAWING\_ARROW**: This tool draws an Arrow drawing on the chart.
* **DRAWING\_PITCHFORK**: This tool draws a Pitchfork drawing on the chart.
* **DRAWING\_PITCHFORK\_SCHIFF**: This tool draws a Schiff Pitchfork drawing on the chart.
* **DRAWING\_PITCHFORK\_MODIFIED\_SCHIFF**: This tool draws a Modified Schiff Pitchfork drawing on the chart.
* **DRAWING\_TIME\_EXPANSION**: This tool draws a 2-point Time Expansion drawing on the chart.
* **DRAWING\_TIME\_PROJECTION**: This tool draws a 3-point Time Projection drawing on the chart.
* **DRAWING\_PARALLEL\_LINES**: This tool draws a Parallel Lines drawing on the chart.
* **DRAWING\_PARALLEL\_RAYS**: This tool draws a Parallel Rays drawing on the chart.
* **DRAWING\_LINEAR\_REGRESSION**: This tool draws a Linear Regression drawing on the chart.
* **DRAWING\_RAFF\_REGRESSION\_CHANNEL**: This tool draws a Raff Regression Channel drawing on the chart.
* **DRAWING\_MARKER**: This tool draws a Marker drawing on the chart. For a Marker drawing, it is necessary to set the **s\_UseTool::MarkerType**  to specify the actual type of marker.
* **DRAWING\_FAN\_FIBONACCI**: This tool draws a Fibonacci Fan drawing on the chart.
* **DRAWING\_REWARD\_RISK**: This tool draws a Reward Risk drawing on the chart.
* **DRAWING\_SWING\_MARKER**: This tool draws a Swing Marker drawing on the chart.
* **DRAWING\_DATE\_MARKER**: This tool draws a Date Marker drawing on the chart.
* **DRAWING\_REWARD\_RISK** : This tool draws a Reward Risk drawing on the chart. For an example function which demonstrates its use, refer to the scsf\_UseToolExampleRewardRisk() function in the /ACS\_Source/Studies.cpp file. The Reward/Risk drawing is a rather complex drawing to add due to the number of options. The example lays out all of the options and documents what they do. The example should be used to understand how to add a DRAWING\_REWARD\_RISK drawing.

#### s\_UseTool::AddMethod

[Link](#susetooladdmethod) - [Top](#top)

**Type:** Integer

Specifies whether the Chart Drawing for the drawing tool is always added to the drawing list, not allowed to be added, or whether instead it will update an existing Chart Drawing.

It is important to understand, a Chart Drawing can be added to one of the following lists in a chart: Advanced Custom Study Drawing List, Advanced Custom Study Fast Drawing List (for drawings which are specified to use bar indexes rather than bar date-times), User Drawn Chart Drawing List.

When a drawing is added to one of these lists, and there is a check ahead of time and to see if it already exist to see if the existing drawing should be updated or if the new drawing should just be ignored based upon the **AdMethod** , that check takes time based upon the size of the corresponding drawing list.

No check takes place to see if a Chart Drawing exists in an existing list, when the [s\_UseTool::LineNumber](#linenumber) is unset and has its default value of -1 in which case it will be automatically set since it is known that this will be a new Chart Drawing.

**AddMethod** by default is set to **UTAM\_ADD\_OR\_ADJUST**.

Possible values for AddMethod:

* **UTAM\_ADD\_ALWAYS**: The Chart Drawing will be added to the chart even if another Chart Drawing with the same **LineNumber** already exists. There is no check if the Chart Drawing already exists if it is a non-user drawn Chart Drawing. Therefore, the insertion is very fast.
    
     
  However, it is not possible to add more than one user drawn drawing ( when s\_UseTool::AddAsUserDrawnDrawing = 1) with the same **LineNumber**. This will fail and 0 will be returned from the **sc.UseTool** function. In this case, there is a check if the Chart Drawing already exists.
* **UTAM\_ADD\_ONLY\_IF\_NEW**: The Chart Drawing will only be added if no other Chart Drawing already on the chart has the same **LineNumber**, if **LineNumber** is set.
    
     
  If **LineNumber**  is not set, then the Chart Drawing will always be added.
* **UTAM\_ADD\_OR\_ADJUST**: If the Chart Drawing already exists on the chart as identified by the **LineNumber** member, then that existing Chart Drawing will be adjusted. Otherwise, a new Chart Drawing will be added.
    
     
  If [LineNumber](#linenumber) is not set, then a new Chart Drawing will be added. Upon return from the **sc.UseTool** function, **LineNumber** will be set to the automatically assigned number.
    
     
  If the drawing is adjusted, then only the s\_UseTool structure members specified will be updated in the existing Chart Drawing, the others will be left as is.
    
    
  If the **DrawingType** member is a different type than specified previously for the same **LineNumber**, then the Chart Drawing type will change to the new specified **DrawingType**.

#### s\_UseTool::ChartNumber

[Link](#susetoolchartnumber) - [Top](#top)

**Type:** Integer

This member is ignored if **s\_UseTool::AddAsUserDrawnDrawing**  is 0, which is the default.

When [s\_UseTool::AddAsUserDrawnDrawing](#susetooladdasuserdrawndrawing) is set to 1 or a nonzero value, then **ChartNumber** specifies the chart number that the drawing will be drawn on. Use 0 to put the drawing on the same chart that the study is applied to.

There are special considerations when setting **s\_UseTool::AddAsUserDrawnDrawing** to 1. Be sure to read the documentation for [s\_UseTool::AddAsUserDrawnDrawing](#susetooladdasuserdrawndrawing).

The **ChartNumber** of a chart is the number of the chart and this is displayed after the "**#**" sign on the top line of the chart. Each chart has a unique number identifying itself within its Chartbook.

If the **ChartNumber** specified is not in the Chartbook or that chart is in the process of loading chart data (not downloading historical data), then the Chart Drawing will not be added by the **sc.UseTool** function.

#### s\_UseTool::LineNumber

[Link](#susetoollinenumber) - [Top](#top)

**Type:** Integer

The **LineNumber** is a unique integer identifier used to identify the Chart Drawing added with the **sc.UseTool** function. This **LineNumber** is used to later identify the Chart Drawing.

This **LineNumber** is needed when performing modifications to the Chart Drawing. Or deleting the Chart Drawing if needed in special cases.

*Setting the **LineNumber** should only be done when modifying or deleting an existing Chart Drawing*. Otherwise, leave it unset and let it be automatically assigned. It is considered proper practice to let the LineNumber be automatically assigned.

If a **LineNumber** is not specified, it will be automatically assigned as a positive number, or usually negative in the case of user drawn drawing, by ACSIL after calling the **sc.UseTool** function. You will be able to get the value by accessing the **LineNumber** member variable, after calling the **sc.UseTool** function.

The default value for **LineNumber** is -1 which is a flag to the sc.UseTool function to automatically assign the LineNumber. So a -1 is acceptable and is the default if **LineNumber** is not set.

The **LineNumber** for ACSIL added drawings will not conflict with user drawn chart drawings when **s\_UseTool::AddAsUserDrawnDrawing** is set to 0.

It is not considered acceptable practice to use the same **LineNumber**  for different Chart Drawings added by the  **sc.UseTool** function.

In the case of a user drawn drawing (**s\_UseTool::AddAsUserDrawnDrawing**=1) and when **s\_UseTool::AddMethod == UTAM\_ADD\_ALWAYS**, using the same LineNumber for a drawing will result in **sc.UseTool** returning 0 and the drawing will not be added.

In the case of a user drawn drawing (**s\_UseTool::AddAsUserDrawnDrawing**=1), adding a new Chart Drawing, and specifying a negative line number other than -1, will result in **sc.UseTool** returning 0 and the drawing will not be added.

After calling the **sc.UseTool** function and if it returns a nonzero number, the **LineNumber** if it was not set, will be set. You can then check what the **LineNumber** is and set it into a [Persistent Variable](ACSIL_Members_Functions.md#scgetpersistentint) if needed for future use.

When calling the **sc.UseTool** function and the [AddMethod](#addmethod) is set to **UTAM\_ADD\_OR\_ADJUST**, the Chart Drawing with the specified **LineNumber** will be [adjusted](#adjustingchartdrawings) instead.

In the case when LineNumber is automatically set when **s\_UseTool::AddAsUserDrawnDrawing** is set to 1 or a nonzero number, the automatically assigned LineNumber may be a negative number or it may be a positive number. When adding Chart Drawings during the calling of the study function, it will continuously decrement to a more negative number, or decrement to a less positive number, depending whether it is negative or positive, without any skips of numbers. Therefore, when adding a range of drawings you can remember the beginning LineNumber and the ending LineNumber to later be able to reference that range of drawings for modification or deletion. Remember these values in a [Persistent Variable](ACSIL_Members_Functions.md#scgetpersistentint).

#### s\_UseTool::BeginDateTime

[Link](#susetoolbegindatetime) - [Top](#top)

**Type:** [SCDateTime](SCDateTime.md)

The Date and Time at which the chart drawing begins.

This member is not used with the Horizontal line tool.

To use a value relative to the left side of the chart for BeginDateTime rather than an absolute Date Time value, specify an integer value from 1 to 150. Where 1 represents the left side of the chart window and where 150 represents the right side of the chart window, not including the Values Scale on the right side of the chart.

**Drawing Text After the End of the Chart Bars:** It is possible to draw text after the end of the chart bars. This only applies in the case of when the **Tool** member of s\_UseTool is **DRAWING\_TEXT**. To do this use an integer value of -1, -2, -3 or lower. A value of -1 will display the text in the fill space after the very last bar in the chart, and a value of -2 or lower will display the text in the fill space even when the chart is scrolled back towards the left. When drawing text in the fill space on the right side of the chart, by default the text is one bar spacing beyond the last bar. To increase the spacing use a value less than -2 such as -3. -3 will draw the text in the fill space and it will be offset from the last bar by 2 bar spacings.

**Drawing Chart Drawings In The Fill Space (Forward Projection Area):** If you want the beginning point of your chart drawing to be in the fill space or forward projection area on the right side of the chart after the last loaded bar in the chart, then use code similar to the example below. This only applies to non-text drawings. This *does not* work with Text drawings.

```cpp

s_UseTool UseTool;

UseTool.Clear();

// BeginDateTime is at the second column in the forward projection area

UseTool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize + 1];
            
```

For maximum performance, use the [BeginIndex](#beginindex) member instead of **BeginDateTime**.

#### s\_UseTool::EndDateTime

[Link](#susetoolenddatetime) - [Top](#top)

**Type:** [SCDateTime](SCDateTime.md)

The Date and Time at which the chart drawing ends. In the case of an extending chart drawing, this is the date and time which the drawing extends from.

This is not used with the Horizontal Line, Vertical Line, or Text tools.

**EndDateTime** should not be the same as **BeginDateTime**  because it is required that a drawing spans at least more than one bar unless it is just a Line which is vertical.

To use a value relative to the left side of the chart for EndDateTime rather than an absolute Date Time value, specify an integer value from 1 to 150. Where 1 represents the left side of the chart window and where 150 represents the right side of the chart window, not including the Values Scale on the right side of the chart.

**Drawing Chart Drawings In The Fill Space (Forward Projection Area):** If you want the ending point of your chart drawing to be in the fill space or forward projection area on the right side of the chart after the last loaded bar in the chart, then use code similar to the example below. This only applies to non-text drawings. This *does not* work with Text drawings.

```cpp

s_UseTool UseTool;

UseTool.Clear();

UseTool.EndDateTime = sc.BaseDateTimeIn[sc.ArraySize + 4];
            
```

For maximum performance, use the [EndIndex](#endindex) member instead of **EndDateTime**.

#### s\_UseTool::ThirdDateTime

[Link](#susetoolthirddatetime) - [Top](#top)

**Type:** [SCDateTime](SCDateTime.md)

For drawings with three points, ThirdDateTime specifies the Date and Time of the third point. Valid for **DRAWING\_PRICE\_PROJECTION**, **DRAWING\_PITCHFORK**, **DRAWING\_PITCHFORK\_SCHIFF**, **DRAWING\_PITCHFORK\_MODIFIED\_SCHIFF**, **DRAWING\_TRIANGLE**, **DRAWING\_TIME\_PROJECTION**, **DRAWING\_PARALLEL\_LINES**, and **DRAWING\_PARALLEL\_RAYS**. Specified in same manner as **EndDateTime**.

#### s\_UseTool::BeginIndex

[Link](#susetoolbeginindex) - [Top](#top)

**Type:** Integer

Drawings may be specified with a bar Index instead of a Date-Time to specify the horizontal position.

Using the **BeginIndex** member instead of [BeginDateTime](#begindatetime) will be *dramatically more efficient*, and allows for bars with the same timestamp to be distinguished. The efficiency benefit is only when the drawing is not a [user drawn](#susetooladdasuserdrawndrawing) drawing.

**BeginIndex** is used to specify the first point of a drawing.

When using **BeginIndex** to modify a drawing, whether [user drawn](#susetooladdasuserdrawndrawing) or an Advanced Custom Study added drawing, make sure to clear s\_UseTool::BeginDateTime by calling the Clear() function on that SCDateTime variable, in case it has a set Date-Time value. Example: UseTool.BeginDateTime.Clear().

```cpp

s_UseTool Tool;
Tool.BeginIndex = sc.Index;
            
```

#### s\_UseTool::EndIndex

[Link](#susetoolendindex) - [Top](#top)

**Type:** Integer

Drawings may be specified with a bar Index instead of a Date-Time to specify the horizontal position.

Using the **EndIndex** member instead of [EndDateTime](#enddatetime) will be *dramatically more efficient*, and allows for bars with the same timestamp to be distinguished. The efficiency benefit is only when the drawing is not a [user drawn](#susetooladdasuserdrawndrawing) drawing.

**EndIndex** is used to specify the second point of a drawing.

**EndIndex** should not be the same as **BeginIndex**  because it is required that a drawing spans at least more than one bar unless it is just a Line which is vertical.

When using **EndIndex** to modify a drawing, whether [user drawn](#susetooladdasuserdrawndrawing) or an Advanced Custom Study added drawing, make sure to clear s\_UseTool::EndDateTime by calling the Clear() function on that SCDateTime variable, in case it has a set Date-Time value. Example: UseTool.EndDateTime.Clear().

#### s\_UseTool::ThirdIndex

[Link](#susetoolthirdindex) - [Top](#top)

**Type:** Integer

When using bar indexes to define drawing points, **ThirdIndex** specifies the bar index of the third point for drawings that used three points. Valid for **DRAWING\_PRICE\_PROJECTION**, **DRAWING\_PITCHFORK**, **DRAWING\_PITCHFORK\_SCHIFF**, **DRAWING\_PITCHFORK\_MODIFIED\_SCHIFF**, **DRAWING\_TRIANGLE**, **DRAWING\_TIME\_PROJECTION**, **DRAWING\_PARALLEL\_LINES**, and **DRAWING\_PARALLEL\_RAYS**.

When using **ThirdIndex** to modify a drawing, make sure to clear s\_UseTool::ThirdDateTime by calling the Clear() function on that SCDateTime variable, in case it has a set Date-Time value. Example: UseTool.ThirdDateTime.Clear().

#### s\_UseTool::UseRelativeVerticalValues / s\_UseTool::UseRelativeValue

[Link](#susetooluserelativeverticalvalues) - [Top](#top)

**Type:** Integer

Set **UseRelativeVerticalValues**  to 1 or any nonzero value, to use **BeginValue** and **EndValue** as relative vertical scale values to the Chart Region instead of as absolute scale values.

Refer to the [BeginValue](#beginvalue) and [EndValue](#endvalue) documentation for more details.

It is supported to use **BeginValue** and **EndValue** as relative vertical scale values to the Chart Region by setting **UseRelativeVerticalValues** to 1 and still use [BeginDateTime](#begindatetime) and [EndDateTime](#enddatetime) as absolute references to specific Date-Times.

UseRelativeVerticalValues does not apply to any of the \*DateTime or \*Index members.

When using **UseRelativeVerticalValues**, it is necessary for there to be a scale established for the particular Chart Region this study is set to display in through the [sc.GraphRegion](ACSIL_Members_Variables_And_Arrays.md#scgraphregion) setting. Otherwise, the Chart Drawing will not display or display properly. This scale can be established by another study or price graph in the Chart Region, or if there is no other study it must be established by the study using **UseRelativeVerticalValues**  by filling in values into a visible [sc.Subgraph](ACSIL_Members_scSubgraph.md) or by using a [user-defined scale](ACSIL_Members_Variables_And_Arrays.md#scscalerangetype).

#### s\_UseTool::BeginValue

[Link](#susetoolbeginvalue) - [Top](#top)

**Type:** Float

The vertical axis chart value for the beginning point of the Chart Drawing. This value needs to be based on the values of the main price graph or the first study graph in the Chart Region (specified with the **Region** member) where the Chart Drawing will be located.

This is not used with the Vertical line tool.

If **UseRelativeVerticalValues** is set to 1 or a nonzero value, then **BeginValue** is a value relative to the Chart Region itself completely independent of the scale used for the graphs in the Chart Region. It is a percentage. Where 1 = 1%. The entire height of the Chart Region is 100%. 0 = The bottom of the Chart Region. 100 = The top of the Chart Region. These values apply to the Chart Region and not the entire height of the chart window unless there is only a single Chart Region displayed.

The horizontal axis equivalent to **UseRelativeVerticalValues** is by setting the [BeginDateTime](#begindatetime) member to a integer value between 1 to 150.

#### s\_UseTool::EndValue

[Link](#endvalue) - [Top](#top)

**Type:** Float

The vertical axis chart value for the ending point of the Chart Drawing. This is not needed for the Text tool. This value needs to be based on the values of the main price graph or the first study graph in the Chart Region (specified with the **Region** member) where the Chart Drawing will be located.

This is not used with the Horizontal or Vertical line tools.

If **UseRelativeVerticalValues** is set to 1 or a nonzero value, then **EndValue**  is a value relative to the Chart Region itself completely independent of the scale used for the graphs in the Chart Region. It is a percentage. Where 1 = 1%. The entire height of the Chart Region is 100%. 0 = The bottom of the Chart Region. 100 = The top of the Chart Region. These values apply to the Chart Region and not the entire height of the chart window unless there is only a single Chart Region displayed.

The horizontal axis equivalent to **UseRelativeVerticalValues** is by setting the [EndDateTime](#enddatetime) member to a integer value between 1 to 150.

#### s\_UseTool::ThirdValue

[Link](#susetoolthirdvalue) - [Top](#top)

**Type:** Float

For drawings with three points, the **ThirdValue** member specifies the vertical scale value of the third point.

Valid for **DRAWING\_PRICE\_PROJECTION**, **DRAWING\_PITCHFORK**, **DRAWING\_PITCHFORK\_SCHIFF**, **DRAWING\_PITCHFORK\_MODIFIED\_SCHIFF**, **DRAWING\_TIME\_PROJECTION**, **DRAWING\_PARALLEL\_LINES**, and **DRAWING\_PARALLEL\_RAYS**.

Specified in same manner as **EndValue**.

#### s\_UseTool::Region

[Link](#susetoolregion) - [Top](#top)

**Type:** integer

This is the region on the chart where the Chart Drawing appears. This number is 0 based and must be 0 to 12.

Region 0 represents Chart Region 1. This is where the Main Price Graph is located. Regions 1 to 11 correspond to chart regions 2 to 12. This is where the study graphs below the Main Price Graph are located.

#### s\_UseTool::Color

[Link](#susetoolcolor) - [Top](#top)

**Type:** unsigned integer (COLORREF)

The Chart Drawing color in [RGB format](#rgb). The default value of this is RGB(0, 0, 0) which is equal to black. This variable must be set, otherwise you will not see the Chart Drawing on a black background.

For the Rectangle, Ellipse, and Triangle Chart Drawings ( **DRAWING\_RECTANGLEHIGHLIGHT, DRAWING\_RECTANGLE\_EXT\_HIGHLIGHT, DRAWING\_ELLIPSEHIGHLIGHT, DRAWING\_TRIANGLE**), this member specifies the outline color of the Chart Drawing. In order to see the outline, it is necessary to set the LineWidth to 1 or greater. Otherwise, the outline will not be visible.

#### s\_UseTool::SecondaryColor

[Link](#susetoolsecondarycolor) - [Top](#top)

**Type:** unsigned integer (COLORREF)

The fill color in [RGB format](#rgb). This applies to the following Chart Drawing types: **DRAWING\_RECTANGLEHIGHLIGHT, DRAWING\_RECTANGLE\_EXT\_HIGHLIGHT, DRAWING\_ELLIPSEHIGHLIGHT, DRAWING\_TRIANGLE**.

#### s\_UseTool::TransparencyLevel

[Link](#susetooltransparencylevel) - [Top](#top)

**Type:** Integer

**TransparencyLevel** sets the amount of transparency for the interior fill area for the following Chart Drawing types: **DRAWING\_RECTANGLEHIGHLIGHT, DRAWING\_RECTANGLE\_EXT\_HIGHLIGHT, DRAWING\_ELLIPSEHIGHLIGHT, DRAWING\_TRIANGLE**.

0 means that the interior fill is completely solid and has no transparency. 100 means that the interior fill is completely transparent and not even visible.

#### s\_UseTool::SquareEdge

[Link](#susetoolsquareedge) - [Top](#top)

**Type:** Integer

Set this to 1 to use square edges for the ends of a Line or Ray.

#### s\_UseTool::LineWidth

[Link](#susetoollinewidth) - [Top](#top)

**Type:** Integer

The line width of the Chart Drawing in pixels. The default is 1. However, you should always set this value so the code is clear.

For the Rectangle, Triangle, and Ellipse Chart Drawing types (**DRAWING\_RECTANGLEHIGHLIGHT, DRAWING\_RECTANGLE\_EXT\_HIGHLIGHT, DRAWING\_ELLIPSEHIGHLIGHT, DRAWING\_TRIANGLE**), in order to see the outline it is necessary to set the LineWidth to 1 or greater. Otherwise, the outline will not be visible.

#### s\_UseTool::LineStyle

[Link](#susetoollinestyle) - [Top](#top)

**Type:** Integer

The line style for the chart drawing. This is an enumeration of type **SubgraphLineStyles**.

Available line styles are: **LINESTYLE\_SOLID**, **LINESTYLE\_DASH**, **LINESTYLE\_DOT**, **LINESTYLE\_DASHDOT**, **LINESTYLE\_DASHDOTDOT**, **LINESTYLE\_ALTERNATE**.

#### s\_UseTool::Text

[Link](#susetooltext) - [Top](#top)

**Type:** [SCString](ACSILProgrammingConcepts.md#workingwithstrings)

The text to draw onto the chart. This applies to the DRAWING\_TEXT tool. This member can also be used with the DRAWING\_HORIZONTALLINE tool. In this case, this is the text that displays below the horizontal line.

For multiline text, each line needs to be terminated with a "\n" character.

If the Text member contains "\n" characters for multiline text, you also need to set **MultiLineLabel = 1** .

This string also has full support for [UTF-8](https://en.wikipedia.org/wiki/UTF-8). Therefore, all of the 1,000,000+ code points are supported. ASCII characters need to be encoded using 8-bit characters.

#### s\_UseTool::DisplayHorizontalLineValue

[Link](#susetooldisplayhorizontallinevalue) - [Top](#top)

**Type:** Integer

This member only applies to the DRAWING\_HORIZONTALLINE, DRAWING\_HORIZONTAL\_LINE\_NON\_EXTENDED, DRAWING\_HORIZONTAL\_RAY drawing tools. Set this to 1 to display the value of the horizontal line with the horizontal line. Set this to 0 to not display the value of the horizontal line.

#### s\_UseTool::FontSize

[Link](#susetoolfontsize) - [Top](#top)

**Type:** Integer

The Font Size of the text. This applies to the DRAWING\_TEXT tool.

#### s\_UseTool::FontBackColor

[Link](#susetoolfontbackcolor) - [Top](#top)

**Type:** unsigned integer (COLORREF)

The color for the text background in [RGB format](#rgb). This applies to the DRAWING\_TEXT tool.

#### s\_UseTool::FontFace

[Link](#susetoolfontface) - [Top](#top)

**Type:** [SCString](ACSILProgrammingConcepts.md#workingwithstrings)

The Font Face name. Such as Arial. This can be left unset to use the Font Face specified in **Global Settings >> Tool Settings >> Text**. This applies to the DRAWING\_TEXT tool.

#### s\_UseTool::FontBold

[Link](#susetoolfontbold) - [Top](#top)

**Type:** Integer

Set this to 1 to make the font Bold. Set it to 0, to not. The default is 0. This applies to the DRAWING\_TEXT tool.

#### s\_UseTool::FontItalic

[Link](#susetoolfontitalic) - [Top](#top)

**Type:** Integer

Set this to 1 to make the font Italic. Set it to 0, to not. The default is 0. This applies to the DRAWING\_TEXT tool.

#### s\_UseTool::TextAlignment

[Link](#susetooltextalignment) - [Top](#top)

**Type:** Integer

This member can be optionally set to one or more of the following flags separated by the C++ OR (**|**) operator: **DT\_TOP, DT\_VCENTER, DT\_BOTTOM, DT\_CENTER, DT\_LEFT, DT\_RIGHT**. The default is **DT\_TOP** and **DT\_LEFT**. These alignment flags apply to the **DRAWING\_TEXT** tool *only* and not any other tools.

This member can also be set to apply text alignment to the Text drawn on a DRAWING\_HORIZONTALLINE drawing. In this case this can be set to **DT\_LEFT** or **DT\_RIGHT**. By default text is aligned to the left.

This member can also be a set to apply the text alignment to the Text drawn on a DRAWING\_RECTANGLEHIGHLIGHT or DRAWING\_RECTANGLE\_EXT\_HIGHLIGHT drawing. In this case, this can be set to **DT\_LEFT** or **DT\_RIGHT**. By default the text is aligned to the left.

#### s\_UseTool::ReverseTextColor

[Link](#susetoolreversetextcolor) - [Top](#top)

**Type:** Integer

Set this to 1, to reverse the color of the text when using the DRAWING\_TEXT drawing type. The text will be drawn with the chart background color and the area around the text will be drawn with the specified color ([Color](#color) member).

The default value is 0, meaning a reversed color is not used.

This applies to the DRAWING\_TEXT drawing type.

#### s\_UseTool::MarkerType

[Link](#susetoolmarkertype) - [Top](#top)

**Type:** Integer

When using **DRAWING\_MARKER**, this member is used to set the marker type to be drawn. The following constant values can be used:

* **MARKER\_POINT**: Draws a point.
* **MARKER\_DASH**: Draws a dash.
* **MARKER\_SQUARE**: Draws a square.
* **MARKER\_STAR**: Draws a star.
* **MARKER\_PLUS**: Draws a "+".
* **MARKER\_X**: Draws an "X".
* **MARKER\_ARROWUP**: Draws an up arrow.
* **MARKER\_ARROWDOWN**: Draws a down arrow.
* **MARKER\_ARROWRIGHT**: Draws a right arrow.
* **MARKER\_ARROWLEFT**: Draws a left arrow.
* **MARKER\_TRIANGLEUP**: Draws a up triangle.
* **MARKER\_TRIANGLEDOWN**: Draws a down triangle.
* **MARKER\_TRIANGLERIGHT**: Draws a right triangle.
* **MARKER\_TRIANGLELEFT**: Draws a left triangle.
* **MARKER\_DIAMOND**: Draws a diamond.

#### s\_UseTool::MarkerSize

[Link](#susetoolmarkersize) - [Top](#top)

**Type:** Integer

When using **DRAWING\_MARKER**, this member is used to set the size of the marker be drawn, and should be greater than zero. This value is ignored if **UseBarSpacingForMarkerSize** is set.

#### s\_UseTool::UseBarSpacingForMarkerSize

[Link](#susetoolusebarspacingformarkersize) - [Top](#top)

**Type:** Integer

When using **DRAWING\_MARKER**, this member can be set to 1 to specify that the size of the marker drawn is set based on the bar spacing. When set, the marker size will scale with the bar spacing as it is changed.

#### s\_UseTool::ShowVolume

[Link](#susetoolshowvolume) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the total volume between the start and end points is displayed in the drawing result text.

#### s\_UseTool::ShowAskBidDiffVolume

[Link](#susetoolshowaskbiddiffvolume) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the total Ask Volume minus the total Bid Volume between the start and end points is displayed in the drawing result text.

#### s\_UseTool::ShowPriceDifference

[Link](#susetoolshowpricedifference) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the price difference of the start and end points is displayed in the drawing result text.

#### s\_UseTool::ShowTickDifference

[Link](#susetoolshowtickdifference) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the price difference of the Begin and End points, measured in ticks, is displayed in the drawing result text. The Tick Size must be properly set for the chart.

#### s\_UseTool::ShowCurrencyValue

[Link](#susetoolshowcurrencyvalue) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the price difference of the Begin and End points, measured in currency value, is displayed in the drawing result text. The Tick Size and Currency Value per Tick must be properly set for the chart.

#### s\_UseTool::ShowPercentChange

[Link](#susetoolshowpercentchange) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the price difference of the start and end points, measured as a percentage change, is displayed in the drawing result text.

#### s\_UseTool::ShowTimeDifference

[Link](#susetoolshowtimedifference) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the time difference of the start and end points is displayed in the drawing result text.

#### s\_UseTool::ShowNumberOfBars

[Link](#susetoolshownumberofbars) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the time duration of the start and end points, measured in number of bars, is displayed in the drawing result text.

#### s\_UseTool::ShowAngle

[Link](#susetoolshowangle) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the angle of the calculator line is displayed in the drawing result text.

#### s\_UseTool::ShowEndPointPrice

[Link](#susetoolshowendpointprice) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the price value of the drawing endpoint is displayed in the drawing result text.

#### s\_UseTool::ShowEndPointDateTime

[Link](#susetoolshowendpointdatetime) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the date and time of the drawing endpoint is displayed in the drawing result text.

#### s\_UseTool::ShowEndPointDate

[Link](#susetoolshowendpointdate) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the date of the drawing endpoint is displayed in the drawing result text.

#### s\_UseTool::ShowEndPointTime

[Link](#susetoolshowendpointtime) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that the time of the drawing endpoint is displayed in the drawing result text.

#### s\_UseTool::MultiLineLabel

[Link](#susetoolmultilinelabel) - [Top](#top)

**Type:** Integer

When using **DRAWING\_CALCULATOR**, this member can be set to 1 to specify that result text should be split into multiple lines, one line for each result type. When not set, the result text is all contained on a singe line.

When using **DRAWING\_TEXT** and the **s\_UseTool::Text** member contains new line characters ("\n"), then MultiLineLabel needs to be set to 1 to cause the text to be displayed on multiple lines.

#### s\_UseTool::ShowPercent

[Link](#susetoolshowpercent) - [Top](#top)

**Type:** Integer

When using **DRAWING\_RETRACEMENT**, **DRAWING\_EXPANSION**, or **DRAWING\_PRICE\_PROJECTION**, this member can be set to 1 to specify that the level percentage be displayed in the drawing level text label.

#### s\_UseTool::ShowPrice

[Link](#susetoolshowprice) - [Top](#top)

**Type:** Integer

When using **DRAWING\_RETRACEMENT**, **DRAWING\_EXPANSION**, or **DRAWING\_PRICE\_PROJECTION** this member can be set to 1 to specify that the level price value be displayed on the drawing as a text label.

When using **DRAWING\_RECTANGLEHIGHLIGHT** or **DRAWING\_RECTANGLE\_EXT\_HIGHLIGHT** this member can be set to 1 to specify that the price values be displayed as text labels on the rectangle drawings. In this case the alignment is controlled with [TextAlignment](#textalignment).

#### s\_UseTool::RoundToTickSize

[Link](#susetoolroundtoticksize) - [Top](#top)

**Type:** Integer

When using **DRAWING\_RETRACEMENT**, **DRAWING\_EXPANSION**, or **DRAWING\_PRICE\_PROJECTION**, this member can be set to 1 to specify that the level price values should be rounded to the nearest TickSize.

#### s\_UseTool::ExtendLeft

[Link](#susetoolextendleft) - [Top](#top)

**Type:** Integer

When using **DRAWING\_RETRACEMENT**, **DRAWING\_EXPANSION**, or **DRAWING\_PRICE\_PROJECTION**, this member can be set to 1 to specify that the level lines will extend to the left.

#### s\_UseTool::ExtendRight

[Link](#susetoolextendright) - [Top](#top)

**Type:** Integer

When using **DRAWING\_RETRACEMENT**, **DRAWING\_EXPANSION**, **DRAWING\_PRICE\_PROJECTION**, **DRAWING\_LINEAR\_REGRESSION**, or **DRAWING\_RAFF\_REGRESSION\_CHANNEL** this member can be set to 1 to specify that the lines will extend to the right.

#### s\_UseTool::TimeExpVerticals

[Link](#susetooltimeexpverticals) - [Top](#top)

**Type:** Integer

When using **DRAWING\_TIME\_EXPANSION** or **DRAWING\_TIME\_PROJECTION**, this member can be set to specify the type of vertical time lines to draw. The possible constant values are:

* **TIME\_EXP\_EXTENDED**: The vertical time lines extend from the top to bottom of the chart region.
* **TIME\_EXP\_STANDARD**: For DRAWING\_TIME\_EXPANSION, the vertical time lines extend from the drawing begining price value to the drawing ending price value. For DRAWING\_TIME\_PROJECTION, the begin and end are drawing points 2 & 3.
* **TIME\_EXP\_COMPRESSED**: The vertical time lines are compressed around the horizontal time line.

#### s\_UseTool::TimeExpTopLabel1

[Link](#susetooltimeexptoplabel1) - [Top](#top)

**Type:** Integer

When using **DRAWING\_TIME\_EXPANSION** or **DRAWING\_TIME\_PROJECTION**, this member can be set to specify the contents of the first top text label, which is placed above the corresponding vertical time line. The possible constant values are:

* **TIME\_EXP\_LABEL\_NONE**: No value specified.
* **TIME\_EXP\_LABEL\_PERCENT**: Time specified as percentage.
* **TIME\_EXP\_LABEL\_BARS**: Time specified in number of bars.
* **TIME\_EXP\_LABEL\_PERCENTBARS**: Percentage (Number of Bars).
* **TIME\_EXP\_LABEL\_BARSPERCENT**: Number of Bars (Percentage).
* **TIME\_EXP\_LABEL\_DATE**: Date for vertical.
* **TIME\_EXP\_LABEL\_TIME**: Time for vertical.
* **TIME\_EXP\_LABEL\_DATETIME**: Date-Time for Vertical

#### s\_UseTool::TimeExpTopLabel2

[Link](#susetooltimeexptoplabel2) - [Top](#top)

**Type:** Integer

When using **DRAWING\_TIME\_EXPANSION** or **DRAWING\_TIME\_PROJECTION**, this member can be set to specify the contents of the second top text label, which is placed above the corresponding vertical time line. The possible values are specified above.

#### s\_UseTool::TimeExpBottomLabel1

[Link](#susetooltimeexpbottomlabel1) - [Top](#top)

**Type:** Integer

When using **DRAWING\_TIME\_EXPANSION** or **DRAWING\_TIME\_PROJECTION**, this member can be set to specify the contents of the first bottom text label, which is placed below the corresponding vertical time line. The possible values are specified above.

#### s\_UseTool::TimeExpBottomLabel2

[Link](#susetooltimeexpbottomlabel2) - [Top](#top)

**Type:** Integer

When using **DRAWING\_TIME\_EXPANSION** or **DRAWING\_TIME\_PROJECTION**, this member can be set to specify the contents of the second bottom text label, which is placed below the corresponding vertical time line. The possible values are specified above.

#### s\_UseTool::TimeExpBasedOnTime

[Link](#susetooltimeexpbasedontime) - [Top](#top)

**Type:** Integer

When using **DRAWING\_TIME\_EXPANSION** or **DRAWING\_TIME\_PROJECTION**, this member can be set to 1 to specify that the tool should use DateTimes instead of bar counts to calculate the time spans. This setting is really only relevant if the tool is being applied to a non-time based chart.

#### s\_UseTool::TransparentLabelBackground

[Link](#susetooltransparentlabelbackground) - [Top](#top)

**Type:** Integer

For tools that use text labels and also the Text tools, this member can be set to 1 to specify that the labels/text should use a transparent background for the labels/text. Otherwise an opaque background is used.

However, in the case when the background color is not specified when using one of the Text tools, the background will be transparent.

#### s\_UseTool::FixedSizeArrowHead

[Link](#susetoolfixedsizearrowhead) - [Top](#top)

**Type:** Integer

When using **DRAWING\_ARROW**, setting this member to 1 specifies that the **ArrowHeadSize** member specifies a fixed size. Otherwise, the **ArrowHeadSize** member specifies an arrowhead/body ratio.

#### s\_UseTool::RetracementLevels[]

[Link](#susetoolretracementlevels) - [Top](#top)

**Type:** float[32]

This array of float values specifies the levels for the drawing tools, specified with the s\_UseTool::DrawingType variable, that require levels.

These drawing tools/types include **DRAWING\_RETRACEMENT**, **DRAWING\_EXPANSION**, **DRAWING\_PRICE\_PROJECTION**, **DRAWING\_TIME\_EXPANSION**, **DRAWING\_TIME\_PROJECTION**, **DRAWING\_PITCHFORK**, **DRAWING\_PITCHFORK\_SCHIFF**, **DRAWING\_PITCHFORK\_MODIFIED\_SCHIFF**, **DRAWING\_PARALLEL\_LINES**, **DRAWING\_PARALLEL\_RAYS**, **DRAWING\_LINEAR\_REGRESSION**, and **DRAWING\_RAFF\_REGRESSION\_CHANNEL**.

Each drawing tool has built in levels that define the basic tool. For example, **DRAWING\_RETRACEMENT** has the initial angled line, and **DRAWING\_PARALLEL\_LINES** has the two base lines. The color, width, and style of these built-in levels are controlled with **Color**, **LineWidth**, and **LineStyle**.

For the other levels, the color width, and style are controlled with **LevelColor**, **LevelWidth**, and **LevelStyle**. All levels are specified as a floating point percentage (Example: **0.618**) except for **DRAWING\_LINEAR\_REGRESSION**, which specifies number of standard deviations (Example: **2.0**).

Using a value of **FLT\_MAX** at a particular index in the **RetracementLevels[]** array means that level will not be drawn. Subsequently setting that level to any other value will restore the level to that particular value.

#### s\_UseTool::LevelColor[]

[Link](#susetoollevelcolor) - [Top](#top)

**Type:** COLORREF[32]

This array specifies the colors for the corresponding tool levels set with **RetracementLevels[]**.

#### s\_UseTool::LevelWidth[]

[Link](#susetoollevelwidth) - [Top](#top)

**Type:** int[32]

This array specifies the line widths for the corresponding tool levels set with **RetracementLevels[]**. The width needs to be greater than or equal to 1.

#### s\_UseTool::LevelStyle[]

[Link](#susetoollevelstyle) - [Top](#top)

**Type:** int[32]

This array specifies the line styles for the corresponding tool levels set with **RetracementLevels[]**. Available line styles are: **LINESTYLE\_SOLID**, **LINESTYLE\_DASH**, **LINESTYLE\_DOT**, **LINESTYLE\_DASHDOT**, and **LINESTYLE\_DASHDOTDOT**.

#### s\_UseTool::AddAsUserDrawnDrawing

[Link](#susetooladdasuserdrawndrawing) - [Top](#top)

**Type:** Integer

This member specifies that a drawing is to be added as a user drawn drawing, which allows the user to interact with the ACSIL added drawing on the chart as if it had been added by the user with one of the drawing tools on the **Tools** menu.

Set this to 1 (TRUE) to make the drawing a user drawn drawing type. When a drawing is *added* with the **AddAsUserDrawnDrawing** member set to 1, this member *must*  always be set to 1 when the drawing is  *updated/modified* .

When working with ACSIL user drawn drawings, the **sc.UserDrawnChartDrawingExists()** and **sc.GetUserDrawnDrawingByLineNumber()** functions can be used to find and retrieve the drawing.

When you have added a chart drawing by setting  **AddAsUserDrawnDrawing** to 1, then you must expressly delete the drawing by calling [sc.DeleteUserDrawnACSDrawing()](#scdeleteuserdrawnacsdrawing).

A chart drawing added with **AddAsUserDrawnDrawing** set to 1 is not saved to a Chartbook like an actual user drawn drawing would be. Unless [s\_UseTool::AllowSaveToChartbook](#susetoolallowsavetochartbook) is set to 1.

#### s\_UseTool::DrawUnderneathMainGraph

[Link](#susetooldrawunderneathmaingraph) - [Top](#top)

**Type:** Integer

When **DrawUnderneathMainGraph** is set to 1 (TRUE), then the Chart Drawing will be drawn underneath the main price graph and studies, independent of how the **Chart >> Chart Settings >> Chart Drawings >> Draw Non-Highlight Chart Drawings Underneath Main Graph and Studies** or **Chart >> Chart Settings >> Chart Drawings >> Draw Highlight Drawings Underneath Main Graph and Studies** options are set.

When **DrawUnderneathMainGraph** is set to 0 (FALSE), then the chart drawing will be drawn above the main price graph and studies, independent of how the **Chart >> Chart Settings >> Chart Drawings >> Draw Non-Highlight Chart Drawings Underneath Main Graph and Studies** or **Chart >> Chart Settings >> Chart Drawings >> Draw Highlight Drawings Underneath Main Graph and Studies** options are set.

When **DrawUnderneathMainGraph** is not set, then the chart drawing will be drawn based on the values of **Chart >> Chart Settings >> Chart Drawings >> Draw Non-Highlight Chart Drawings Underneath Main Graph and Studies** and **Chart >> Chart Settings >> Chart Drawings >> Draw Highlight Drawings Underneath Main Graph and Studies** options are set.

The default for **DrawUnderneathMainGraph** is not set.

#### s\_UseTool::UseToolConfigNum

[Link](#susetoolusetoolconfignum) - [Top](#top)

**Type:** Integer

This can be set to 1 through 24 (Or whatever the maximum number of Chart Drawing Tool configurations currently supported in Sierra Chart is). This specifies the particular tool configuration defined for the Chart Drawing Tool specified, to automatically be applied to the Chart Drawing being added.

For additional information, refer to [Using Multiple Drawing Tool Configurations](Tools.md#usingmultipledrawingtoolconfigurations).

#### s\_UseTool::FlatEdge

[Link](#susetoolflatedge) - [Top](#top)

**Type:** Integer

Set this to 1 to use flat edges for the ends of a Line or Ray. This flag is mutually exclusive with the SquareEdge option.

#### s\_UseTool::DrawWithinRegion

[Link](#susetooldrawwithinregion) - [Top](#top)

**Type:** Integer

Set this to 1 for Vertical Line drawings to cause them to be drawn with the specified Chart Region only instead of across all Chart Regions.

#### s\_UseTool::CenterPriceLabels

[Link](#susetoolcenterpricelabels) - [Top](#top)

**Type:** Integer

Set this to 1 for rectangle highlights to cause the price labels to be centered on the top/bottom price levels.

#### s\_UseTool::NoVerticalOutline

[Link](#susetoolnoverticaloutline) - [Top](#top)

**Type:** Integer

Set this to 1 for rectangle highlight drawings to cause the vertical outline to not be drawn. The result is a rectangle highlight with only top and bottom outline lines similar to a double extending rectangle highlight drawing.

#### s\_UseTool::AllowSaveToChartbook

[Link](#susetoolallowsavetochartbook) - [Top](#top)

**Type:** Integer

Set this to 1 to allow a drawing added as a [User Drawn Drawing](#susetooladdasuserdrawndrawing) to be saved to the Chartbook which contains the chart which contains the custom study which added the Chart Drawing, when the Chartbook is saved.

Set this to 0 to prevent saving of the Chart Drawing to the Chartbook.

#### s\_UseTool::ShowBeginMark

[Link](#susetoolshowbeginmark) - [Top](#top)

**Type:** Integer

Set this to 1 to show a square mark at the beginning of a Line or other types of Chart Drawings which support marks at the anchor points. This is equivalent to the **Options >> Mark** setting in the [Drawing Tool Configuration/Properties](Tools.md#drawingtoolconfiguration) window.

#### s\_UseTool::ShowEndMark

[Link](#susetoolshowendmark) - [Top](#top)

**Type:** Integer

Set this to 1 to show a square mark at the ending of a Line or other types of Chart Drawings which support marks at the anchor points. This is equivalent to the **Options >> Mark** setting in the [Drawing Tool Configuration/Properties](Tools.md#drawingtoolconfiguration) window.

#### s\_UseTool::AssociatedStudyID

[Link](#susetoolassociatedstudyid) - [Top](#top)

**Type:** Integer

**AssociatedStudyID** is set to a nonzero number when the Chart Drawing is associated with a **Volume by Price**  study which was drawn on the chart using the [Draw Volume Profile](StudiesReference.md#drawvolumeprofile) tool.

**AssociatedStudyID** specifies the unique ID for the study the Chart Drawing is associated with. This is equivalent to the ACSIL member variable [sc.StudyGraphInstanceID](ACSIL_Members_Variables_And_Arrays.md#scstudygraphinstanceid) for the study.

#### s\_UseTool::HideDrawing

[Link](#susetoolhidedrawing) - [Top](#top)

**Type:** Integer

When this is set to 1, it hides the Chart Drawing. Set this to 0 to make a hidden Chart Drawing visible.

#### s\_UseTool::LockDrawing

[Link](#susetoollockdrawing) - [Top](#top)

**Type:** Integer

This member needs to be set to 1 to lock the chart drawing and prevent it from being modified through the chart user interface.

Set this to 0 or do not set it, to keep the drawing unlocked. It only makes sense to use this variable, for a user drawn drawing because only those types of drawings can be modified through the chart user interface.

#### s\_UseTool::DrawOutlineOnly

[Link](#susetooldrawoutlineonly) - [Top](#top)

**Type:** Integer

This member only applies to the following drawing types: DRAWING\_TRIANGLE, DRAWING\_MARKER, DRAWING\_RECTANGLEHIGHLIGHT, DRAWING\_ELLIPSEHIGHLIGHT, DRAWING\_RECTANGLE\_EXT\_HIGHLIGHT.

When this is set to 1, it means the outline of the drawing will only be drawn. When this is set to 0 or is unset, then the interior of the drawing will also be drawn.

#### s\_UseTool::NumCycles

[Link](#susetoolnumcycles) - [Top](#top)

**Type:** Integer

#### s\_UseTool::ExtendMultiplier

[Link](#susetoolextendmultiplier) - [Top](#top)

**Type:** Float

#### s\_UseTool::DrawMidline

[Link](#susetooldrawmidline) - [Top](#top)

**Type:** Integer

This member variable only applies to Chart Drawings which use a Midline option.

When this is set to 1, the Midline is drawn.

When this is set to 0 the Midline is not drawn.

#### s\_UseTool::AllowCopyToOtherCharts

[Link](#susetoolallowcopytoothercharts) - [Top](#top)

**Type:** Integer

When this is set to 1, it allows the Chart Drawing to be copied to other charts through the [Copy Chart Drawings](CopyingChartDrawingsFromOtherChartsAutomatically.md) functionality.

When this is set to 0 or is unset, then the drawing cannot be copied to another chart. This is the default.

This only applies to user drawn drawings. This is when [s\_UseTool::AddAsUserDrawnDrawing](#susetooladdasuserdrawndrawing) is set to 1.

---

### sc.ChartDrawingExists()

[Link](#scchartdrawingexists) - [Top](#top)

ACSIL Function

Declaration: int **ChartDrawingExists**(int **ChartNumber**, int **LineNumber**);

**sc.ChartDrawingExists()** is used to determine if a Chart Drawing with the specified **LineNumber** exists within the specified chart (**ChartNumber**).

This function ignores user drawn Chart Drawings, it only checks Chart Drawings added by ACSIL.

This function returns the number of matching drawings found. Refer to the **scsf\_UseToolExample()** function in the /ACS\_Source/studies.cpp file for example code on how to work with this function.

```cpp

if (sc.ChartDrawingExists(sc.ChartNumber, 5))
{
    // A line with a LineNumber of 5 exists on the same chart that this study is on
}
        
```

### sc.UserDrawnChartDrawingExists()

[Link](#scuserdrawnchartdrawingexists) - [Top](#top)

ACSIL Function

Declaration: int **UserDrawnChartDrawingExists**(int **ChartNumber**, int **LineNumber**);

**sc.UserDrawnChartDrawingExists()** function is used to determine if a user drawn Chart Drawing with the specified **LineNumber** exists within the specified chart (**ChartNumber**).

An ACSIL Chart Drawing is considered user drawn if it was added with the **s\_UseTool::AddAsUserDrawnDrawing** member set to 1.

Non-user drawn ACSIL Chart Drawings are not searched with this function.

It returns the number of matching drawings found.

Refer to the **scsf\_UseToolExample()** function in the /ACS\_Source/studies.cpp file for example code on how to work with this function.

```cpp

if (sc.UserDrawnChartDrawingExists(sc.ChartNumber, 5))
{
    // An ACSIL added user drawing with a LineNumber of 5 exists on the same chart that this study is on
}
        
```

### sc.GetUserDrawnChartDrawing()

[Link](#scgetuserdrawnchartdrawing) - [Top](#top)

ACSIL Function

int **GetUserDrawnChartDrawing**(int **ChartNumber**, DrawingTypeEnum **DrawingType**, s\_UseTool& **ChartDrawing**, int **DrawingIndex**);

**sc.GetUserDrawnChartDrawing()** is used to get a Chart Drawing drawn by a drawing Tool on the specified chart.

Only user drawn drawings can be retrieved, not Chart Drawings added by an ACSIL study, unless the Chart Drawing was specified as being **s\_UseTool::AddAsUserDrawnDrawing** when adding it with sc.UseTool().

This function returns 1 on success, and 0 on error. A error includes an invalid DrawingType specified or a drawing not found on the chart.

Refer to the **scsf\_GetChartDrawingExample** function in the /ACS\_Source/studies.cpp file for example code on how to work with this function.

#### Parameters

* **ChartNumber**: This number corresponds to the number after the number "#" sign on the top line of the chart. Using a zero (0) will specify the chart the ACSIL study is applied to.
* **DrawingType**: The chart drawing type that you want to get. This parameter can be any of the following.
  + DRAWING\_LINE
  + DRAWING\_RAY
  + DRAWING\_HORIZONTALLINE
  + DRAWING\_VERTICALLINE
  + DRAWING\_ARROW
  + DRAWING\_TEXT
  + DRAWING\_CALCULATOR
  + DRAWING\_RETRACEMENT
  + DRAWING\_PRICE\_PROJECTION
  + DRAWING\_RECTANGLEHIGHLIGHT
  + DRAWING\_ELLIPSEHIGHLIGHT
  + DRAWING\_TRIANGLE
  + DRAWING\_FAN\_GANN
  + DRAWING\_PITCHFORK
  + DRAWING\_CYCLE
  + DRAWING\_TIME\_EXPANSION
  + DRAWING\_GANNGRID
  + DRAWING\_ENTRYEXIT\_CONNECTLINE
  + DRAWING\_RECTANGLE\_EXT\_HIGHLIGHT
  + DRAWING\_FAN\_FIBONACCI
  + DRAWING\_PARALLEL\_LINES
  + DRAWING\_PARALLEL\_RAYS
  + DRAWING\_LINEAR\_REGRESSION
  + DRAWING\_RAFF\_REGRESSION\_CHANNEL
  + DRAWING\_EXTENDED\_LINE
  + DRAWING\_PITCHFORK\_SCHIFF
  + DRAWING\_PITCHFORK\_MODIFIED\_SCHIFF
  + DRAWING\_EXPANSION
  + DRAWING\_VOLUME\_PROFILE
  + DRAWING\_STATIONARY\_TEXT
  + DRAWING\_TIME\_PROJECTION
  + DRAWING\_MARKER
  + DRAWING\_HORIZONTAL\_RAY
  + DRAWING\_HORIZONTAL\_LINE\_NON\_EXTENDED
  + DRAWING\_UNKNOWN. Use this constant to get any type of drawing. When the function returns and **DrawingType** was set to **DRAWING\_UNKNOWN**, the **ChartDrawing::DrawingType** parameter member will indicate the type of drawing that has been found.
* **ChartDrawing**: A reference to a **s\_UseTool** structure. This is where the Chart Drawing information will be copied to. For the descriptions of the **s\_UseTool** structure, refer to [Drawing Tools and s\_UseTool Member Descriptions](#usetoolmembers).
    
    
  User drawn Chart Drawings have a negative **LineNumber**. This is how you can distinguish Chart Drawings drawn by a user and also drawings flagged as user drawn which were added by the ACSIL.
* **DrawingIndex**:
    
    
  An index to specify which instance of the matching chart drawing you want. This is a 0-based index in the order that chart drawings were added to the chart. For example, if **DrawingIndex** is 0, the function will return the first instance that matches the drawing type. If **DrawingIndex** is 1, the function will return the second instance that matches the drawing type.
    
    
  Also you can give a negative index to specify drawings from the last drawing that was added to the chart. For example, if **DrawingIndex** is -1, the function will return the last drawing matching the drawing type that was added to the chart.
    
    
  Be aware that when a Chart Drawing is modified, it is put at the end of the list. So in this case if you modify a Chart Drawing, it is going to be put at the end of the list, and be the one that is considered last added.
    
    
  This index only counts the Chart Drawings on the chart that match the given **DrawingType**.
    
    
  For example, if **DrawingType** is **DRAWING\_RAY** and **DrawingIndex** is 1, then the function will return the second Ray on the chart. If **DrawingType** is **DRAWING\_TEXT** and **DrawingIndex** is 1, then the function will return the second Text drawing on the chart.
    
    
  If **DrawingType** is **DRAWING\_TEXT** and **DrawingIndex** is -1, then the function will return the last Text drawing on the chart. If **DrawingType** is **DRAWING\_UNKNOWN**, then DrawingIndex considers all Chart Drawings on the chart.

#### Example:

```cpp

// Gets the last drawn text on the chart and adds a message to the Sierra Chart message log, if the text exists.
s_UseTool ChartDrawing;
if (sc.GetUserDrawnChartDrawing(0, DRAWING_TEXT, &ChartDrawing, -1))
{
    sc.AddMessageToLog("Text was added on current chart!", 0);
    sc.AddMessageToLog(ChartDrawing.Text, 1);
}
            
```

### sc.GetLineNumberOfSelectedUserDrawnDrawing()

[Link](#scgetlinenumberofselecteduserdrawndrawing) - [Top](#top)

ACSIL Function

int **GetLineNumberOfSelectedUserDrawnDrawing**();

The **sc.GetLineNumberOfSelectedUserDrawnDrawing()** returns the [Line Number](#linenumber) of the selected User Drawn drawing. If more than one drawing is selected, the first found drawing is returned.

### sc.GetUserDrawnDrawingByLineNumber()

[Link](#scgetuserdrawndrawingbylinenumber) - [Top](#top)

ACSIL Function

int **GetUserDrawnDrawingByLineNumber**(int **ChartNumber**, int **LineNumber**, s\_UseTool& **ChartDrawing**);

The  **sc.GetUserDrawnDrawingByLineNumber()** function is used to get a user drawn Chart Drawing on the chart. This also includes Chart Drawings added by ACSIL which are flagged as user drawn when setting **s\_UseTool::AddAsUserDrawnDrawing** = 1 when the drawing is added with **sc.UseTool**.

This function cannot get Chart Drawings which are added by ACSIL when **s\_UseTool::AddAsUserDrawnDrawing** = 0. To get non-user drawn Chart Drawings added by ACSIL, use the function [sc.GetACSDrawingByLineNumber()](#scgetacsdrawingbylinenumber).

This function returns 1 on success, and 0 on failure. A failure means the Chart Drawing was not found on the specified chart.

Refer to the **scsf\_GetChartDrawingExample** function in the **/ACS\_Source/studies.cpp** file for example code on how to work with this function.

When a user drawn Chart Drawing is being moved or adjusted by the user, the **sc.GetUserDrawnDrawingByLineNumber()** call will fail to find the Chart Drawing even though **sc.UserDrawnChartDrawingExists()** indicates that it exists.

Therefore, a study should always use **sc.UserDrawnChartDrawingExists()** to detect if the user drawn Chart Drawing exists, and then use **sc.GetUserDrawnDrawingByLineNumber()** to get the Chart Drawing, and understand that a failure means that the Chart Drawing is being modified.

When a Chart Drawing you are getting is not visible in the current view of the chart, then **s\_UseTool::BeginIndex, s\_UseTool::EndIndex, s\_UseTool::ThirdIndex** will all equal -1.

#### Parameters

* **ChartNumber**: This number corresponds to the number after the number "#" sign on the top line of the chart you want to get the drawing from. Using a zero (0) will specify the chart the custom study is applied to. Usually set this parameter to 0 or **sc.ChartNumber**.
* **LineNumber**: This number corresponds to the **s\_UseTool::LineNumber** of the ACSIL added user drawn Chart Drawing or the LineNumber retrieved when using the [sc.GetUserDrawnChartDrawing()](#scgetuserdrawnchartdrawing) function to get an actual user drawn drawing.
    
    
  This parameter should not be 0 or -1.
* **ChartDrawing**: A reference to a **s\_UseTool** structure. This is where the Chart Drawing information will be copied to. For the descriptions of the **s\_UseTool** structure, refer to [Drawing Tools and s\_UseTool Member Descriptions](#usetoolmembers).
    
    
  Note that when chart drawings are returned through this function, the **DrawingType** member is set to indicate the type of drawing retrieved.

### sc.GetACSDrawingByLineNumber()

[Link](#scgetacsdrawingbylinenumber) - [Top](#top)

ACSIL Function

int **GetACSDrawingByLineNumber**(int **ChartNumber**, int **LineNumber**, s\_UseTool& **ChartDrawing**);

The  **sc.GetACSDrawingByLineNumber()** function is used to get an ACSIL added Chart Drawing on the chart added with the **sc.UseTool** function.

This function does not get user drawn Chart Drawings which are specified with s\_UseTool::AddAsUserDrawnDrawing = 1. You need to use the [sc.GetUserDrawnDrawingByLineNumber()](#scgetuserdrawndrawingbylinenumber) function instead.

This function returns 1 on success, and 0 on failure. A failure means the Chart Drawing was not found on the specified chart.

When a Chart Drawing you are getting is not visible in the current view of the chart, then **s\_UseTool::BeginIndex, s\_UseTool::EndIndex, s\_UseTool::ThirdIndex** will all equal -1 unless the drawing specified its horizontal positioning using these \*Index values when it was added.

#### Parameters

* **ChartNumber**: This number corresponds to the number after the number "#" sign on the top line of the chart. Using a zero (0) will specify the chart the custom study is applied to. Usually set this parameter to 0.
* **LineNumber**: This number corresponds to the **s\_UseTool::LineNumber** of the ACSIL added Chart Drawing.
    
    
  This parameter should not be 0 or -1. Otherwise, a match will not be found.
* **ChartDrawing**: A reference to a **s\_UseTool** structure. This is where the Chart Drawing information will be copied to. For the descriptions of the **s\_UseTool** structure, refer to [Drawing Tools and s\_UseTool Member Descriptions](#usetoolmembers).
    
    
  Note that when chart drawings are returned through this function, the **DrawingType** member is set to indicate the type of drawing retrieved.

### sc.GetACSDrawingByIndex()

[Link](#scgetacsdrawingbyindex) - [Top](#top)

ACSIL Function

int **GetACSDrawingByIndex**(int **ChartNumber**, int **Index**, s\_UseTool& **ChartDrawing**, int **ExcludeOtherStudyInstances**);

The  **sc.GetACSDrawingByIndex()** function is used to get an ACSIL added Chart Drawing on the chart added with the **sc.UseTool** function. The drawing is looked up by its index number rather than by the s\_UseTool::LineNumber.

This function returns 1 on success, and 0 on failure. A failure means the Chart Drawing was not found on the specified chart.

When a Chart Drawing you are getting is not visible in the current view of the chart, then **s\_UseTool::BeginIndex, s\_UseTool::EndIndex, s\_UseTool::ThirdIndex** will all equal -1 unless the drawing specified its horizontal positioning using these \*Index values when it was added.

#### Parameters

* **ChartNumber**: This number corresponds to the number after the number "#" sign on the top line of the chart. Using a zero (0) will specify the chart the custom study is applied to. Usually set this parameter to 0.
* **Index**: This zero-based index number is used to get a Chart Drawing according to its index in the internal list that ACSIL added Chart Drawings are added to.
    
    
  The first Chart Drawing has an index of 0, the second Chart Drawing is 1 and so on.
    
    
  Negative indexes are not supported.
* **ChartDrawing**: A reference to a **s\_UseTool** structure. This is where the Chart Drawing information will be copied to. For the descriptions of the **s\_UseTool** structure, refer to [Drawing Tools and s\_UseTool Member Descriptions](#usetoolmembers).
    
    
  Note that when chart drawings are returned through this function, the **DrawingType** member is set to indicate the type of drawing retrieved.
* **ExcludeOtherStudyInstances**: When this is set to a nonzero value, then Chart Drawings added by other study instances are excluded. When this is set to 0, then Chart Drawings on the chart added by other study instances will be included when getting an Advanced Custom Study drawing by its index.

### sc.GetACSDrawingsCount()

[Link](#scgetacsdrawingscount) - [Top](#top)

**Type**: ACSIL Function

int **GetACSDrawingsCount**(int **ChartNumber**, int **ExcludeOtherStudyInstances**);

The **sc.GetACSDrawingsCount** function returns the total number of ACSIL added Chart Drawings on the specified chart, specified by the **ChartNumber** parameter. This does not count user drawn ChartDrawings.

#### Parameters

* **ChartNumber**: [**Type**: Integer] The number of the chart that contains the drawing or drawings. The *default and recommended value is 0*, which means the chart the ACSIL study instance is applied to. This number corresponds to the number after the number "#" sign on the top line of the chart.
* **ExcludeOtherStudyInstances:**: When this parameter is set to 1, then Chart Drawings from other study instances on the chart is excluded in the drawing count. When this is set to 0, all Chart Drawings added by all custom studies are counted.

### sc.DeleteACSChartDrawing()

[Link](#scdeleteacschartdrawing) - [Top](#top)

ACSIL Function

Declaration: int **DeleteACSChartDrawing**(int **ChartNumber**, int **Tool**, int **LineNumber**);

The **sc.DeleteACSChartDrawing()** function deletes Chart Drawings that have been added by ACSIL studies using the [sc.UseTool()](#usingtools) function.

This function cannot be used to delete *user drawn* Chart Drawings. User drawn Chart Drawings are manually drawn by a user or ACSIL added Chart Drawings that have the **s\_UseTool::AddAsUserDrawnDrawing = 1** flag set. For deleting user drawn drawings, use [sc.DeleteUserDrawnACSDrawing()](#scdeleteuserdrawnacsdrawing).

When a study is removed from the chart, or when it is fully recalculated, and it has Chart Drawings added with sc.UseTool(), these Chart Drawings are automatically deleted from the chart. Therefore, there is no need to use **sc.DeleteACSChartDrawing()**.

This function should only be used for more specialized purposes like when you need to delete a Chart Drawing for some other reason.

For an example which uses this function, refer to the **scsf\_DeleteACSChartDrawingExample**  function in the **/ACS\_Source/studies.cpp** file in the Sierra Chart installation folder.

#### Parameters

* **ChartNumber**: [**Type**: Integer] The number of the chart that contains the drawing or drawings to delete. The *default and recommended value is 0*, which means the chart the ACSIL study instance is applied to. This number corresponds to the number after the number "#" sign on the top line of the chart.
* **Tool**: [**Type:** Integer] The **Tool** parameter can be **TOOL\_DELETE\_ALL** or **TOOL\_DELETE\_CHARTDRAWING**.
    
    
  If Tool is set to **TOOL\_DELETE\_ALL**, then all non user drawn Chart Drawings on the specified **ChartNumber** will be deleted. The **LineNumber** parameter in this case is ignored and should be 0.
    
    
  If Tool is set to **TOOL\_DELETE\_CHARTDRAWING**, then all non user drawn Chart Drawings with the specified **LineNumber** will be deleted from the chart specified by the **ChartNumber** parameter.
* **LineNumber**: [**Type:** Integer] The LineNumber of the Chart Drawings to delete. The LineNumber is the same **LineNumber** that was specified when adding the Chart Drawing with **sc.UseTool()**. In the case where LineNumber was not set when calling **sc.UseTool()**, then it will be automatically set. In this case remember it into a [persistent integer](ACSIL_Members_Functions.md#scgetpersistentint) and then it can be specified in this function call.
    
    
  This parameter only applies to **TOOL\_DELETE\_CHARTDRAWING**.
    
    
  Multiple Chart Drawings can be deleted if they use the same **LineNumber**. All chart drawings with the same **LineNumber** will be deleted from the chart.

#### Return Value

For **TOOL\_DELETE\_ALL**, 1 on success, 0 on failure.

For **TOOL\_DELETE\_CHARTDRAWING**, the number of Chart Drawings deleted.

### sc.DeleteUserDrawnACSDrawing()

[Link](#scdeleteuserdrawnacsdrawing) - [Top](#top)

ACSIL Function

Declaration: int **DeleteUserDrawnACSDrawing**(int **ChartNumber**, int **LineNumber**);

The **sc.DeleteUserDrawnACSDrawing()** function deletes Chart Drawings that have been added by ACSIL studies using **sc.UseTool()** and have specified **s\_UseTool::AddAsUserDrawnDrawing = 1**.

Chart Drawings manually drawn by a user can also be deleted with this function if the **LineNumber**  for the drawing is known. This can be determined with the [sc.GetUserDrawnChartDrawing](#scgetuserdrawnchartdrawing) function.

When Chart Drawings have been added **sc.UseTool()** and have specified **s\_UseTool::AddAsUserDrawnDrawing = 1**, it is necessary to remove these drawings with **sc.DeleteUserDrawnACSDrawing()** in the study function when **sc.LastCallToFunction** is TRUE. Otherwise, they will remain on the chart.

When **sc.DeleteUserDrawnACSDrawing()** successfully removes a user drawn Chart Drawing, the internal storage container will no longer contain this Chart Drawing. Therefore, the index position of Chart Drawings after this deleted Chart Drawing in the container, changes. Therefore, the index specified to functions like [sc.GetACSDrawingByIndex()](#scgetacsdrawingbyindex) may be affected by this.

#### Parameters

* **ChartNumber**: [**Type**: Integer] The number of the chart that contains the Chart Drawing. The default value is 0, this means the chart the ACSIL study is applied to. This number corresponds to the number after the number "#" sign on the top line of the chart.
* **LineNumber**: [**Type:** Integer] The  **LineNumber** of the Chart Drawing to delete. The  **LineNumber** of the Chart Drawing must be known.
    
    
  Since user drawn chart drawings each need to have a unique **LineNumber**, when the first user drawn drawing encountered has a matching **LineNumber**, it is deleted and no other drawings will be checked.
    
    
  The  **LineNumber** is the same  **LineNumber** that you specified when adding the chart drawing with the [sc.UseTool](#usingtools)function, or was automatically set and remembered.
    
    
  This can also be a  **LineNumber** from an actual user drawn Chart Drawing retrieved with the [sc.GetUserDrawnChartDrawing](#scgetuserdrawnchartdrawing) function.

#### Return Value

The number of user drawn Chart Drawings deleted.

## RGB Color Values

[Link](#rgb) - [Top](#top)

Colors are stored as 32-bit unsigned integer values. It is easiest to use the RGB function. It takes red, green, and blue integer values as parameters, and returns a color value. For more information, you may want to refer to the [RGB color model](https://en.wikipedia.org/wiki/RGB_color_model) Wikipedia article.

Here are some color examples:

* Red: **RGB(255,0,0)**
* Green: **RGB(0,255,0)**
* Blue: **RGB(0,0,255)**
* Magenta: **RGB(255,0,255)**
* White: **RGB(255,255,255)**
* Black: **RGB(0,0,0)**
* Dark Blue: **RGB(0,0,127)**
* Orange: **RGB(255,127,0)**

```cpp

sc.Subgraph[0].PrimaryColor = RGB(255, 0, 0); // Set the primary color for the first subgraph to red
s_UseTool Tool;
Tool.Color = RGB(0, 0, 255); // Set Tool color to Blue
    
```

## Drawing Chart Drawings On Top of or Underneath Main Graph and Studies

[Link](#drawingchartdrawingsontopoforunderneath) - [Top](#top)

The Chart Drawings added by the **sc.UseTool** function can be set to be displayed on top of or underneath the Main Price Graph and Studies in the chart. This can be done by using the [DrawUnderneathMainGraph](#drawunderneathmaingraph) member of the [s\_UseTool](#usetoolmembers) structure.

Also, there are 2 settings for this as well in **Chart >> Chart Settings >> Chart Drawings**.

They are **Draw Non-Highlight Chart Drawings Under Main Graph and Studies** and  **Draw Highlight Drawings Under Main Graph and Studies**.

## Adding Chart Drawings to Other Charts from an ACSIL Study Function

[Link](#addingchartdrawingstootherchartsfromacsilstudy) - [Top](#top)

It is supported when using the [sc.UseTool()](#usingtools) function, to add Chart Drawings to a chart other than the chart the study function making the function call is applied to.

This can be done by setting the [s\_UseTool::ChartNumber](#chartnumber) member to the chart number that you want to add a drawing to.

It is also necessary to set [s\_UseTool::AddAsUserDrawnDrawing](#susetooladdasuserdrawndrawing) to 1.

## Drawing Lines With a Specific Angle Using ACSIL

[Link](#drawinglineswithspecificangleusingacsil) - [Top](#top)

This section explains how to use ACSIL to draw lines at a specific angle. For introductory information about using drawing tools from ACSIL, refer to the [Introduction](#introduction) section on this page.

The **s\_UseTool** structure supports specifying the beginning and ending anchor points of the line using these members:

* [BeginDateTime](#begindatetime)
* [EndDateTime](#enddatetime)
* [BeginIndex](#beginindex)
* [EndIndex](#endindex)
* [Begin Value](#beginvalue)
* [End Value](#endvalue)

You need to make sure the combination of these values results in a line with a specific angle that you require. For example a 45 degree line will have a slope of 1. This means one unit of price over one unit of time. One unit of time is always one bar in the chart. The [Drawing a Line with a Specific Angle or Slope](Tools.md#angle) section has complete information on this subject.

To have a better idea of all of this, it is recommended to manually draw [Lines](Tools.md#lineray) at 45 degrees to get an idea of what values to use.

---

\*Last modified Monday, 24th March, 2025.
