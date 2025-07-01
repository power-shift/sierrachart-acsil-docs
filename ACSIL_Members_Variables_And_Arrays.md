# ACSIL Interface Members - Variables and Arrays

## Related Documentation

* [ACSIL Interface Members - Introduction](ACSIL_Members.md)
* **ACSIL Interface Members - Variables and Arrays**
* [ACSIL Interface Members - sc.Input Array](ACSIL_Members_scInputs.md)
* [ACSIL Interface Members - sc.Subgraph Array](ACSIL_Members_scSubgraph.md)
* [ACSIL Interface Members - Functions](ACSIL_Members_Functions.md)
* [ACSIL Interface Members - Graphics Functions](ACSIL_Members_GraphicsFunctions.md).

---

## On This Page

* [sc.ACSVersion](#scacsversion)
* [sc.ActiveToolIndex](#scactivetoolindex)
* [sc.ActiveToolYPosition](#scactivetoolyposition)
* [sc.ActiveToolYValue](#scactivetoolyvalue)
* [sc.AlertConditionEnabled](#scalertconditionenabled)
* [sc.AlertConditionFlags](#scalertconditionflags)
* [sc.AlertOnlyOncePerBar](#scalertonlyonceperbar)
* [sc.AllocateAndNameRenkoChartBarArrays](#scallocateandnamerenkochartbararrays)
* [sc.ArraySize](#scarraysize)
* [sc.Ask](#scask)
* [sc.AskSize](#scasksize)
* [sc.AutoLoop](#scautoloop)
* [sc.AutoScalePaddingPercentage](#scautoscalepaddingpercentage)
* [sc.BaseDataEndDateTime[]](#scBaseDataEndDateTime)
* [sc.BaseDataIn[][] / sc.BaseData[][]](#scBaseDataIn)
* [sc.BaseDateTimeIn[]](#scBaseDateTimeIn)
* [sc.BasedOnGraphValueFormat](#scbasedongraphvalueformat)
* [sc.BaseGraphAutoScalePaddingPercentage](#scbasegraphautoscalepaddingpercentage)
* [sc.BaseGraphConstantRangeScaleMode](#scbasegraphconstantrangescalemode)
* [sc.BaseGraphGraphDrawType](#scbasegraphgraphdrawtype)
* [sc.BaseGraphHorizontalGridLineIncrement](#scbasegraphhorizontalgridlineincrement)
* [sc.BaseGraphScaleConstRange](#scbasegraphscaleconstrange)
* [sc.BaseGraphScaleIncrement](#scbasegraphscaleincrement)
* [sc.BaseGraphScaleValueOffset](#scbasegraphscalevalueoffset)
* [sc.BaseGraphScaleRangeBottom](#scbasegraphscalerangebottom)
* [sc.BaseGraphScaleRangeTop](#scbasegraphscalerangetop)
* [sc.BaseGraphScaleRangeType](#scbasegraphscalerangetype)
* [sc.BaseGraphValueFormat](#scbasegraphvalueformat)
* [sc.Bid](#scbid)
* [sc.BidSize](#scbidsize)
* [sc.BlockChartDrawingSelection](#scblockchartdrawingselection)
* [sc.CalculationPrecedence](#sccalculationprecedence)
* [sc.CancelAllOrdersOnEntries](#sccancelallordersonentries)
* [sc.CancelAllOrdersOnReversals](#sccancelallordersonreversals)
* [sc.CharacterEventCode](#sccharactereventcode)
* [sc.ChartBackgroundColor](#scchartbackgroundcolor)
* [sc.ChartBarSpacing](#scchartbarspacing)
* [sc.ChartbookName](#scchartbookname)
* [sc.ChartDataEndDate](#scchartdataenddate)
* [sc.ChartDataStartDate](#scchartdatastartdate)
* [sc.ChartDataType](#scchartdatatype)
* [sc.ChartNumber](#scchartnumber)
* [sc.ChartRegion1BottomCoordinate](#scchartregion1bottomcoordinate)
* [sc.ChartRegion1LeftCoordinate](#scchartregion1leftcoordinate)
* [sc.ChartRegion1RightCoordinate](#scchartregion1rightcoordinate)
* [sc.ChartRegion1TopCoordinate](#scchartregion1topcoordinate)
* [sc.ChartTextFont](#sccharttextfont)
* [sc.ChartTradeModeEnabled](#sccharttrademodeenabled)
* [sc.ChartTradingOrderPrice](#sccharttradingorderprice)
* [sc.ChartUpdateIntervalInMilliseconds](#scchartupdateintervalinmilliseconds)
* [sc.ChartWindowHandle](#scchartwindowhandle)
* [sc.ChartWindowIsActive](#scchartwindowisactive)
* [sc.ConnectToExternalServiceServer](#scconnecttoexternalserviceserver)
* [sc.ConstantRangeScaleModeTicksFromCenterOrEdge](#scconstantrangescalemodeticksfromcenteroredge)
* [sc.ContinuousFuturesContractLoading](#sccontinuousfuturescontractloading)
* [sc.ContinuousFuturesContractOption](#sccontinuousfuturescontractoption)
* [sc.ContractRolloverDate](#sccontractrolloverdate)
* [sc.CurrencyValuePerTick](#sccurrencyvaluepertick)
* [sc.CurrentSystemDateTime](#sccurrentsystemdatetime)
* [sc.CurrentDateTimeForReplay](#sccurrentdatetimeforreplay)
* [sc.CurrentSystemDateTimeMS](#sccurrentdatetimems)
* [sc.CurrentlySelectedDrawingTool](#sccurrentlyselecteddrawingtool)
* [sc.CurrentlySelectedDrawingToolState](#sccurrentlyselecteddrawingtoolstate)
* [sc.CustomAffiliateCode](#sccustomaffiliatecode)
* [sc.CustomChartTitleBarName](#sccustomcharttitlebarname)
* [sc.DailyHigh](#scdailyhigh)
* [sc.DailyLow](#scdailylow)
* [sc.DailyStatsResetTime](#scdailystatsresettime)
* [sc.DailyVolume](#scdailyvolume)
* [sc.DataFeedActivityCounter](#scdatafeedactivitycounter)
* [sc.DataFile](#scdatafile) (This can be used to change the symbol of the chart)
* [sc.DataFilesFolder](#scdatafilesfolder)
* [sc.DataStartIndex](#scdatastartindex)
* [sc.DateTimeOfLastFileRecord](#scdatetimeoflastfilerecord)
* [sc.DateTimeOut[]](#scDateTimeOut)
* [sc.DaysToLoadInChart](#scdaystoloadinchart)
* [sc.DeltaVolumePerBar](#scdeltavolumeperbar)
* [sc.DisconnectFromExternalServiceServer](#scdisconnectfromexternalserviceserver)
* [sc.DisplayAsMainPriceGraph](#scdisplayasmainpricegraph)
* [sc.DisplayStudyInputValues](#scdisplaystudyinputvalues)
* [sc.DisplayStudyName](#scdisplaystudyname)
* [sc.DLLNameUserServiceLevel](#scdllnameuserservicelevel)
* [sc.DocumentationImageURL](#scdocumentationimageurl)
* [sc.DoNotRedrawChartAfterStudyReturns](#scdonotredrawchartafterstudyreturns)
* [sc.DownloadingHistoricalData](#scdownloadinghistoricaldata)
* [sc.DrawACSDrawingsAboveOtherDrawings](#scdrawacsdrawingsaboveotherdrawings)
* [sc.DrawBaseGraphOverStudies](#scdrawbasegraphoverstudies)
* [sc.DrawStudyUnderneathMainPriceGraph](#scdrawstudyunderneathmainpricegraph)
* [sc.EarliestUpdateSubgraphDataArrayIndex](#scearliestupdatesubgraphdataarrayindex)
* [sc.EndTime1](#scendtime1)
* [sc.EndTime2](#scendtime2)
* [sc.FileRecordIndexOfLastDataRecordInChart()](#scfilerecordindexoflastdatarecordinchart)
* [sc.FilterChartVolumeGreaterThanEqualTo](#scfilterchartvolumegreaterthanequalto)
* [sc.FilterChartVolumeLessThanEqualTo](#scfilterchartvolumelessthanequalto)
* [sc.FilterChartVolumeTradeCompletely](#scfilterchartvolumetradecompletely)
* [sc.FlagFullRecalculate](#scflagfullrecalculate)
* [sc.FlagToReloadChartData](#scflagtoreloadchartdata)
* [sc.FreeDLL](#scfreedll)
* [sc.GlobalDisplayStudySubgraphsNameAndValue](#scglobaldisplaystudysubgraphsnameandvalue)
* [sc.GlobalTradeSimulationIsOn](#scglobaltradesimulationison)
* [sc.GraphDrawType](#scgraphdrawtype)
* [sc.GraphName](#scgraphname)
* [sc.GraphRegion](#scgraphregion)
* [sc.GraphShortName](#scgraphshortname)
* [sc.GraphUsesChartColors](#scgraphuseschartcolors)
* [sc.HideDLLAndFunctionNames](#schidedllandfunctionnames)
* [sc.HideStudy](#schidestudy)
* [sc.HistoricalHighPullbackVolumeAtPriceForBars](#schistoricalhighpullbackvolumeatpriceforbars)
* [sc.HistoricalLowPullbackVolumeAtPriceForBars](#schistoricallowpullbackvolumeatpriceforbars)
* [sc.HistoricalPriceMultiplier](#schistoricalpricemultiplier)
* [sc.HTTPBinaryResponse](#schttpbinaryresponse)
* [sc.HTTPRequestID](#schttprequestid)
* [sc.IncludeInSpreadsheet](#scincludeinspreadsheet)
* [sc.IncludeInStudySummary](#scincludeinstudysummary)
* [sc.CurrentIndex / sc.Index](#scindex) (Automatic Looping)
* [sc.IndexOfFirstVisibleBar](#scindexoffirstvisiblebar)
* [sc.IndexOfLastVisibleBar](#scindexoflastvisiblebar)
* [sc.IntradayDataStorageTimeUnit](#scintradaydatastoragetimeunit)
* [sc.IntradayChartRecordingState](#scintradaychartrecordingstate)
* [sc.IsAutoTradingEnabled](#scisautotradingenabled)
* [sc.IsAutoTradingOptionEnabledForChart](#scisautotradingoptionenabledforchart)
* [sc.IsChartbookBeingSaved](#scischartbookbeingsaved)
* [sc.IsChartTradeModeOn](#scischarttrademodeon)
* [sc.IsCustomChart](#sciscustomchart)
* [sc.IsFullRecalculation](#scisfullrecalculation)
* [sc.IsKeyPressed\_Alt](#sciskeypressedalt)
* [sc.IsKeyPressed\_Control](#sciskeypressedcontrol)
* [sc.IsKeyPressed\_Shift](#sciskeypressedshift)
* [sc.IsUserAllowedForSCDLLName](#scisuserallowedforscdllname)
* [sc.KeyboardKeyEventCode](#sckeyboardkeyeventcode)
* [sc.LastCallToFunction](#sclastcalltofunction)
* [sc.LastFullCalculationTimeInMicroseconds](#sclastfullcalculationtimeinmicroseconds)
* [sc.LastSize](#sclastsize)
* [sc.LastTradePrice](#sclasttradeprice)
* [sc.LatestDateTimeForLastBar](#sclatestdatetimeforlastbar)
* [sc.LoadChartDataByDateRange](#scloadchartdatabydaterange)
* [sc.MaintainAdditionalChartDataArrays](#scmaintainadditionalchartdataarrays)
* [sc.MaintainHistoricalMarketDepthData](#scmaintainhistoricalmarketdepthdata)
* [sc.MaintainReferenceToOtherChartsForPersistentVariables](#scmaintainreferencetootherchartsforpersistentvariables)
* [sc.MaintainTradeStatisticsAndTradesData](#scmaintaintradestatisticsandtradesdata)
* [sc.MaintainVolumeAtPriceData](#scmaintainvolumeatpricedata)
* [sc.NewBarAtSessionStart](#scnewbaratsessionstart)
* [sc.NumberOfArrays](#scnumberofarrays)
* [sc.NumberOfForwardColumns](#scnumberofforwardcolumns)
* [sc.NumberOfTradesPerBar](#scnumberoftradesperbar)
* [sc.NumFillSpaceBars](#scnumfillspacebars)
* [sc.OutArraySize](#scoutarraysize)
* [sc.p\_VolumeLevelAtPriceForBars](#scpvolumelevelatpriceforbars)
* [sc.PersistVars](#scpersistvars)
* [sc.PlaceACSChartShortcutMenuItemsAtTopOfMenu](#scplaceacschartshortcutmenuitemsattopofmenu)
* [sc.PointAndFigureBoxSizeInTicks](#scpointandfigureboxsizeinticks)
* [sc.PointAndFigureReversalSizeNumBoxes](#scpointandfigurereversalsizenumboxes)
* [sc.PointAndFigureXOGraphDrawTypeBoxSize](#scpointandfigurexographdrawtypeboxsize)
* [sc.PointerHorzWindowCoord](#scpointerhorzwindowcoord)
* [sc.PointerVertWindowCoord](#scpointervertwindowcoord)
* [sc.PreserveFillSpace](#scpreservefillspace)
* [sc.PreviousClose](#scpreviousclose)
* [sc.PriceChangesPerBar](#scpricechangesperbar)
* [sc.PriorSelectedCustomStudyControlBarButtonNumber](#scpriorselectedcustomstudycontrolbarbuttonnumber)
* [sc.ProcessIdentifier](#scprocessidentifier)
* [sc.ProtectStudy](#scprotectstudy)
* [sc.PullbackVolumeAtPrice](#scpullbackvolumeatprice)
* [sc.RangeBarType](#scrangebartype)
* [sc.RangeBarValue](#scrangebarvalue)
* [sc.RealTimePriceMultiplier](#screaltimepricemultiplier)
* [sc.ReceiveCharacterEvents](#screceivecharacterevents)
* [sc.ReceiveKeyboardKeyEvents](#screceivekeyboardkeyevents)
* [sc.ReceivePointerEvents](#screceivepointerevents)
* [sc.ReconnectToExternalServiceServer](#screconnecttoexternalserviceserver)
* [sc.RenkoNewBarWhenExceeded](#screnkonewbarwhenexceeded)
* [sc.RenkoReversalOpenOffsetInTicks](#screnkoreversalopenoffsetinticks)
* [sc.RenkoTicksPerBar](#screnkoticksperbar)
* [sc.RenkoTrendOpenOffsetInTicks](#screnkotrendopenoffsetinticks)
* [sc.ReplayStatus](#screplaystatus)
* [sc.ResetAlertOnNewBar](#scresetalertonnewbar)
* [sc.ResetAllScales](#scresetallscales)
* [sc.ReversalTicksPerBar](#screversalticksperbar)
* [sc.RightValuesScaleLeftCoordinate](#scrightvaluesscaleleftcoordinate)
* [sc.RightValuesScaleRightCoordinate](#scrightvaluesscalerightcoordinate)
* [sc.RoundTurnCommission](#scroundturncommission)
* [sc.SaveChartImageToFile](#scsavechartimagetofile)
* [sc.ScaleBorderColor](#scscalebordercolor)
* [sc.ScaleConstRange](#scscaleconstrange)
* [sc.ScaleIncrement](#scscaleincrement)
* [sc.ScaleRangeBottom](#scscalerangebottom)
* [sc.ScaleRangeTop](#scscalerangetop)
* [sc.ScaleRangeType](#scscalerangetype)
* [sc.ScaleType](#scscaletype)
* [sc.ScaleValueOffset](#scscalevalueoffset)
* [sc.SCDataFeedSymbol](#scscdatafeedsymbol)
* [sc.ScrollToDateTime](#scscrolltodatetime)
* [sc.SecondsPerBar](#scsecondsperbar)
* [sc.SelectedAlertSound](#scselectedalertsound)
* [sc.SelectedTradeAccount](#scselectedtradeaccount)
* [sc.ServerConnectionState](#scserverconnectionstate)
* [sc.ServiceCodeForSelectedDataTradingService](#scservicecodeforselecteddatatradingservice)
* [sc.SetDefaults](#scsetdefaults)
* [sc.StandardChartHeader](#scstandardchartheader)
* [sc.StartTime1](#scstarttime1)
* [sc.StartTime2](#scstarttime2)
* [sc.StartTimeOfDay](#scstarttimeofday)
* [sc.StorageBlock](#scstorageblock)
* [sc.StudyDescription](#scstudydescription)
* [sc.StudyGraphInstanceID](#scstudygraphinstanceid)
* [sc.StudyRegionBottomCoordinate](#scstudyregionbottomcoordinate)
* [sc.StudyRegionLeftCoordinate](#scstudyregionleftcoordinate)
* [sc.StudyRegionRightCoordinate](#scstudyregionrightcoordinate)
* [sc.StudyRegionTopCoordinate](#scstudyregiontopcoordinate)
* [sc.StudyVersion](#scstudyversion)
* [SC\_SUBGRAPHS\_AVAILABLE](#scsubgraphsavailable)
* [SupportAttachedOrdersForTrading](#scsupportattachedordersfortrading)
* [sc.SupportKeyboardModifierStates](#scsupportkeyboardmodifierstates)
* [sc.SupportTradingScaleIn](#scsupporttradingscalein)
* [sc.SupportTradingScaleOut](#scsupporttradingscaleout)
* [sc.Symbol](#scsymbol)
* [sc.SymbolData](#scsymboldata)
* [sc.TextInput](#sctextinput)
* [sc.TextInputName](#sctextinputname)
* [sc.TickSize](#scticksize)
* [sc.TimeScaleAdjustment](#sctimescaleadjustment)
* [sc.TradeAndCurrentQuoteSymbol](#sctradeandcurrentquotesymbol)
* [sc.TradeServiceAccountBalance](#sctradeserviceaccountbalance)
* [sc.TradeServiceAvailableFundsForNewPositions](#sctradeserviceavailablefundsfornewpositions)
* [sc.TradeWindowConfigFileName](#sctradewindowconfigfilename)
* [sc.TradeWindowOrderQuantity](#sctradewindoworderquantity)
* [sc.TradingIsLocked](#sctradingislocked)
* [sc.TransparencyLevel](#sctransparencylevel)
* [sc.UpdateAlways](#scupdatealways)
* [sc.UpdateStartIndex](#scupdatestartindex) (Manual Looping)
* [sc.UseGlobalChartColors](#scuseglobalchartcolors)
* [sc.UseGUIAttachedOrderSetting](#scuseguiattachedordersetting)
* [sc.UseHighResolutionWindowRelativeCoordinatesForChartDrawings](#scusehighresolutionwindowrelativecoordinatesforchartdrawings)
* [sc.UserName](#scusername)
* [sc.UseSecondStartEndTimes](#scusesecondstartendtimes)
* [sc.UsesMarketDepthData](#scusesmarketdepthdata)
* [sc.ValueFormat](#scvalueformat)
* [sc.ValueIncrementPerBar](#scvalueincrementperbar)
* [sc.VersionNumber](#scversionnumber)
* [sc.VolumeAtPriceForBars](#scvolumeatpriceforbars)
* [sc.VolumeAtPriceForStudy](#scvolumeatpriceforstudy)
* [sc.VolumeAtPriceMultiplier](#scvolumeatpricemultiplier)
* [sc.VolumePerBar](#scvolumeperbar)
* [sc.VolumeValueFormat](#scvolumevalueformat)

---

## Variables and Arrays

### sc.ACSVersion

[Link](#scacsversion) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.ACSVersion** variable is set to the version number in the SierraChart.h header file that the custom study was compiled with. This version number corresponds to a particular Sierra Chart version number.

For the study to function in Sierra Chart it requires a Sierra Chart version equal to this version or higher.

### sc.ActiveToolIndex

[Link](#scactivetoolindex) - [Top](#top)

**Type**: Read-only integer variable.

**sc.ActiveToolIndex** is the array index corresponding to the second index used with the arrays **sc.BaseData[][]** and **sc.Subgraph[][]**, that the current [Drawing Tool](Tools.md) is pointing to on the chart that the study function is applied to.

This variable will not be updated when the **Pointer** tool is selected or when the **Chart Values** tool is selected, and not active.

This variable is always guaranteed to be up-to-date when **sc.ReceivePointerEvents**  is set to a value which causes pointer events to be received by the study function, and the **Pointer**, **Chart Values** or **Hand** tool is selected, whether they are active or not.

When you use this variable it may be a good idea to set **sc.UpdateAlways** to 1, so that your study function is continuously called so it can be aware of the new tool position more often.

Alternatively you may want to use the [Advanced Custom Study Interaction With Menus, Control Bars, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) functionality.

**sc.ActiveToolIndex** can also be at an index value which is in the fill space on the right side of the chart after the last bar.

This index can be converted into a pixel coordinate with the [sc.BarIndexToXPixelCoordinate](ACSIL_Members_Functions.md#scbarindextoxpixelcoordinate) function.

#### Example

```cpp

 // Get the Open value of the bar that the tool is over
float OpenValueAtTool = sc.BaseData[SC_OPEN][sc.ActiveToolIndex];

//Get the Date-Time of the bar that the current tool is over.
SCDateTime BarDateTime = sc.BaseDateTimeIn[sc.ActiveToolIndex];
            
```

### sc.ActiveToolYPosition

[Link](#scactivetoolyposition) - [Top](#top)

**Type**: Read-only integer variable.

**sc.ActiveToolYPosition** is the Y-axis coordinate in pixels of the current drawing tool's position over the chart your study function is applied to. This variable will not be updated when the Pointer tool is selected or when the Chart Values tool is selected, however not active.

When you use this variable it may be a good idea to set **sc.UpdateAlways** to 1, so that your study function is continuously called so it can be aware of the new tool position more often.

### sc.ActiveToolYValue

[Link](#scactivetoolyvalue) - [Top](#top)

**Type**: Read-only float variable.

The sc.ActiveToolYValue variable is the Y-axis value in the chart region that the mouse pointer is at when using one of the chart tools including the Chart Values tool. This is not the pixel position. It is the actual chart region value derived from the displayed graphs.

#### Example

```cpp

float Value = sc.ActiveToolYValue;
            
```

### sc.AlertConditionEnabled

[Link](#scalertconditionenabled) - [Top](#top)

**Type**: Read/Write integer variable.

A value of 0 is used to disable the Alert Condition Formula for the study. A value of 1 is used to enable the Alert Condition Formula for the study.

### sc.AlertConditionFlags

[Link](#scalertconditionflags) - [Top](#top)

**Type**: Read-only integer variable.

**sc.AlertConditionFlags** will be a nonzero value when the Simple Alert Condition Formula on the the study is TRUE

#### Example

```cpp

int AlertState = sc.AlertConditionFlags;
            
```

### sc.AlertOnlyOncePerBar

[Link](#scalertonlyonceperbar) - [Top](#top)

**Type**: Read/Write integer variable.

**sc.AlertOnlyOncePerBar** can be set to 1 or 0 (TRUE/FALSE) to cause an Alert to be given only once per bar in the chart. This variable works with the [sc.SetAlert](ACSIL_Members_Functions.md#scsetalert)() function.

The **sc.AlertOnlyOncePerBar** variable can also be changed through the [Alert Options](StudyChartAlertsAndScanning.md#alertoptionsalertonlyonceperbar) on the Study Settings window.

### sc.AllocateAndNameRenkoChartBarArrays

[Link](#scallocateandnamerenkochartbararrays) - [Top](#top)

**Type**: Integer variable.

The **sc.AllocateAndNameRenkoChartBarArrays**  variable only applies when **sc.UsesCustomChartBarFunction**  is set to 1 and the study is creating custom chart bars.

When **sc.AllocateAndNameRenkoChartBarArrays**  is set to 1, then the [sc.BaseData[SC\_RENKO\_OPEN][]](#scBaseDataIn) and the [sc.BaseData[SC\_RENKO\_CLOSE][]](#scBaseDataIn) arrays have array elements added to them to match the standard arrays like sc.BaseData[SC\_OPEN][], so that the elements of them which correspond with chart bars can then be set.

These arrays will also be named "Renko Open" and "Renko Close" respectively.

### sc.ArraySize

[Link](#scarraysize) - [Top](#top)

**Type**: Read-only integer variable.

**sc.ArraySize** is set to the number of array elements (equivalent to chart bars), that are in the arrays of the chart the study instance is applied to.

**sc.ArraySize** applies to the **[sc.BaseDateTimeIn[]](#scBaseDateTimeIn)**, **[sc.BaseDataIn[][]](#scBaseDataIn)**, and **[sc.Subgraph[][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** arrays.

If you set **[sc.IsCustomChart](#sciscustomchart)** to 1 (TRUE), **sc.ArraySize** does not apply to the **[sc.Subgraph[][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** arrays. Refer to **[sc.OutArraySize](#scoutarraysize)**, for more information.

Setting **[sc.IsCustomChart](#sciscustomchart)** is uncommon, so in most cases this is not applicable.

#### Example

```cpp

// Copy all the Close elements from the BaseDataIn array
// to the Data array of the first Subgraph. 
// This example assumes that sc.AutoLoop = 0 (manual looping).

for (int BarIndex =  sc.UpdateStartIndex; BarIndex < sc.ArraySize; ++BarIndex)
{
    // SC_LAST is for the Close values in OHLC bars
    sc.Subgraph[0].Data[BarIndex] = sc.BaseDataIn[SC_LAST][BarIndex];
}
            
```

### sc.Ask

[Link](#scask) - [Top](#top)

**Type**: Read-only float variable.

**sc.Ask** is the current Ask price value for the symbol if Bid and Ask data is available for the symbol.

If the chart is not replaying, then this will only be set and up-to-date when Sierra Chart is connected to the data feed.

During a replay, this value is set. For additional information, refer to [Trade Simulation Accuracy and Bid/Ask Prices During Replays](TradeSimulation.md#tradesimulationbidaskprices).

### sc.AskSize

[Link](#scasksize) - [Top](#top)

**Type**: Read-only integer variable.

**sc.AskSize** is the current Ask size/quantity value for the symbol if Bid and Ask data is available for the symbol.

If the chart is not replaying, then this will only be set and up-to-date when Sierra Chart is connected to the data feed, and the market is open.

During a replay, this value will be set to 1.

### sc.AutoLoop

[Link](#scautoloop) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0 (FALSE)

When **sc.AutoLoop** is set to 1 (TRUE), then **sc.BaseData**  and **sc.Subgraph[].Data[]** array element looping is *automatically* performed.

Otherwise, array element looping is *manual* and you will need to create your own internal loop to iterate through these arrays.

It is preferred that you set **sc.AutoLoop** to 1 (TRUE) unless you do not require it. For a complete discussion on this, refer to [Automatic Looping/Iterating](ACS_ArraysAndLooping.md#automaticloopingiterating).

**sc.AutoLoop** must only be set within the **sc.SetDefaults**  code block at the top of the study function.

#### Example

```cpp

if (sc.SetDefaults)
{
    sc.AutoLoop = 1; // Enable auto-looping
} 
            
```

### sc.AutoScalePaddingPercentage

[Link](#scautoscalepaddingpercentage) - [Top](#top)

**Type**: Read/Write float variable.

Initial value: .02

sc.AutoScalePaddingPercentage is a percentage value within the range of -1 to 1 where positive values mean more vertical scale padding, and negative values mean inverse vertical scale padding.

A value of 0.4 means that padding takes up 40% of the chart, and the graph uses the rest of the 60%.

This is the value that gets changed when you use the [Interactive Scale Range](Scaling.md#interactivescalingexpandcompress) feature when you left click and drag the scale on the right side of the chart.

#### Example

```cpp

sc.AutoScalePaddingPercentage = 0.5f;
            
```

### sc.BaseDataEndDateTime[]

[Link](#scbasedataenddatetime) - [Top](#top)

**Type**: Read-only [SCDateTime](SCDateTime.md) Array.

The **sc.BaseDataEndDateTime[]** array contains the actual ending date time of a chart bar at the specified array index. The values in this array are only going to be most accurate when the [Intraday Data Storage Time Unit](DataSourceSettings.md#intradaydatastoragetimeunit) is set to **1 Tick** or **1 Second**.

For information about array indexing and array sizes, refer to [Array Indexing and Sizes](ACS_ArraysAndLooping.md#arrayindexing).

For this array to be maintained and filled in, it is necessary to set [sc.MaintainAdditionalChartDataArrays](#scmaintainadditionalchartdataarrays) to 1 in the [sc.SetDefaults](#scsetdefaults) code block.

The Date-Time at each element for a chart bar in this array, contains the last trade Date-Time within that chart bar. It is not necessarily at the last second or millisecond for the chart bar since trading does not necessarily end exactly at that time for a chart bar.

#### Example

```cpp

// Get the End DateTime at the current index.
SCDateTime BarEndDateTime = sc.BaseDataEndDateTime[sc.Index];
            
```

### sc.BaseDataIn[][] / sc.BaseData[][]

[Link](#scbasedatain) - [Top](#top)

**Type**: Read-only array of float arrays.

**sc.BaseDataIn[][] / sc.BaseData[][]** is an array of float arrays that contain the data for the main graph in the chart.

The first use of square brackets on this object will get the specified array of the main graph on the chart. For example: **sc.BaseDataIn[SC\_OPEN]** will get the array of opening prices for each bar on the chart. The second use of square brackets will get an element inside the array that you received with the first set of square brackets.

For example: **sc.BaseDataIn[SC\_OPEN][sc.Index]** will get the opening price for the bar at the array index your study function should do processing at when using Auto-Looping (the standard method of looping). The main graph is not necessarily the underlying data in the chart. For example, if you are using the **Point and Figure** study, then **sc.BaseData[][]** will contain the Point and Figure bar data.

For complete information about indexing and array sizes for the sc.BaseData[][] arrays, refer to the [Array Indexing and Sizes](ACS_ArraysAndLooping.md#arrayindexing) section.

**sc.BaseData[]** and **sc.BaseDataIn[]** are both the same. They just have different names referring to the same array of arrays.

**sc.BaseData[] / sc.BaseDataIn[]** is meant to be read only, but there is no compiler enforcement of that implemented to avoid potential issues with defining these arrays as constant. A custom study can modify both of these arrays. But it should never do so.

The following lists all of the supported **sc.BaseData[] / sc.BaseDataIn[]** arrays and the corresponding constants that can be used. The descriptions for each are provided. These arrays provide access to the main price graph. The direct referencing arrays are also given, such as **sc.Open[]**.

* **sc.BaseData[SC\_OPEN] or sc.Open[]:** The array of opening prices for each bar.
* **sc.BaseData[SC\_HIGH] or sc.High[]:** The array of high prices for each bar.
* **sc.BaseData[SC\_LOW] or sc.Low[]:** The array of low prices for each bar.
* **sc.BaseData[SC\_LAST] or sc.Close[]:** The array of closing/last prices for each bar.
* **sc.BaseData[SC\_VOLUME] or sc.Volume[]:** The array of trade volumes for each bar.
* **sc.BaseData[SC\_NUM\_TRADES] or sc.NumberOfTrades[]:** The array of the number of trades for each bar for Intraday charts.
* **sc.BaseData[SC\_OPEN\_INTEREST] or sc.OpenInterest[]:** The array of the open interest data for each bar for Historical Daily or higher timeframe charts. This is not valid for Intraday charts. It will return the number of trades for each bar for Intraday charts.
* **sc.BaseData[SC\_OHLC]or sc.OHLCAvg[]:** The array of the average prices of the open, high, low, and close prices for each bar.
* **sc.BaseData[SC\_HLC] or sc.HLCAvg[]:** The array of the average prices of the high, low, and close prices for each bar.
* **sc.BaseData[SC\_HL] or sc.HLAvg[]:** The array of the average prices of the high and low prices for each bar.
* **sc.BaseData[SC\_BIDVOL] or sc.BidVolume[]:** The array of Bid Volumes for each bar. This represents the volumes of the trades that occurred at the Bid price or lower. A trade that occurs between the Bid or Ask and is considered a downtick, will have the volume of that trade added to Bid Volume.
* **sc.BaseData[SC\_ASKVOL] or sc.AskVolume[]:** The array of Ask Volumes for each bar. This represents the volumes of the trades that occurred at the Ask price or higher. A trade that occurs between the Bid or Ask and is considered an uptick, will have the volume of the trade added to the Ask Volume.
* **sc.BaseData[SC\_UPVOL] or sc.UpTickVolume:** This array contains the total volume of trades for the bar where the trades occurred at a higher price than the trade before or the symbol traded at the same price as before and previously it traded higher.
    
  For this to work properly, the **Intraday Data Storage Time Unit** setting in **Global Settings >> Data/Trade Service Settings** needs to be **1 Tick**. If it is not, then when the chart is reloaded, the historical up volume can change compared to real-time updating. In the case of **Number of Trades, Volume, Range, Reversal, Renko, Delta Volume** chart bars, the data in this array may not be correct if **Chart >>Chart Settings >> Split Data Records** is enabled, unless there is 1 Tick data being used and the chart bars are based on **Number of Trades** or a **Range**.
    
  If you are using this array in your study function, you must set **sc.MaintainAdditionalChartDataArrays** to 1 in the sc.SetDefaults code block.
* **sc.BaseData[SC\_DOWNVOL] or sc.DownTickVolume:** This array contains the total volume of trades for the bar where the trades occurred at a lower price than the trade before or the symbol traded at the same price as before and previously it traded down.
    
  For this to work properly, the **Intraday Data Storage Time Unit** setting in **Global Settings >> Data/Trade Service Settings** needs to be **1 Tick**. If it is not, then when the chart is reloaded, the historical down volume can change compared to real-time updating. In the case of **Number of Trades, Volume, Range, Reversal, Renko, Delta Volume** chart bars, the data in this array may not be correct if **Chart >>Chart Settings >> Split Data Records** is enabled, unless there is 1 Tick data being used and the chart bars are based on **Number of Trades** or a **Range**.
    
  If you are using this array in your study function, you must set **sc.MaintainAdditionalChartDataArrays** to 1 in the sc.SetDefaults code block.
* **sc.BaseData[SC\_BIDNT] or sc.NumberOfBidTrades:** The array containing the total number of trades at the bid price or lower. For this to work properly, the **Intraday Data Storage Time Unit** setting in **Global Settings >> Data/Trade Service Settings**. needs to be **1 Tick**. This will also not work on historical data that does not have bid volume. In the case of Tick, Volume, and Range charts, the data in this array may not be correct if **Chart >>Chart Settings >> Split Data Records** is enabled, unless you are using tick data and the chart is based on Ticks or a Range.
    
  If you are using this array in your study function, you must set **sc.MaintainAdditionalChartDataArrays** to 1 in the sc.SetDefaults code block.
* **sc.BaseData[SC\_ASKNT] or sc.NumberOfAskTrades:** The array containing the total number of trades at the ask price or higher. For this to work properly, the **Intraday Data Storage Time Unit** setting in **Global Settings >> Data/Trade Service Settings** needs to be 1 Tick. This will also not work on historical data that does not have ask volume. In the case of Tick, Volume, and Range charts, the data in this array may not be correct if **Chart >>Chart Settings >> Split Data Records** is enabled, unless you are using tick data and the chart is based on Ticks or a Range.
    
  If you are using this array in your study function, you must set **sc.MaintainAdditionalChartDataArrays** to 1 in the sc.SetDefaults code block.
* **sc.BaseData[SC\_ASKBID\_DIFF\_HIGH]:** The array containing the maximum difference between the Ask volume and the Bid volume for the bar at the specified Index. This is calculated at every tick during the creation of the bar.
    
  For the data in this array to be most accurate, the **Intraday Data Storage Time Unit** setting in **Global Settings >> Data/Trade Service Settings** needs to be 1 Tick. The data in this array will not be available for historical data that does not have Ask Volume and Bid Volume.
    
  For the chart to maintain the data in this array, you need to set **sc.MaintainAdditionalChartDataArrays** to TRUE in the **sc.SetDefaults** code block in your study function.
* **sc.BaseData[SC\_ASKBID\_DIFF\_LOW]:** The array containing the minimum difference between the Ask volume and the Bid volume for the bar at the specified Index. This is calculated at every tick during the creation of the bar. For the data in this array to be most accurate, the **Intraday Data Storage Time Unit** setting in **Global Settings >> Data/Trade Service Settings** needs to be 1 Tick. The data in this array will not be available for historical data that does not have Ask volume and Bid Volume.
    
  For the chart to maintain the data in this array, you need to set **sc.MaintainAdditionalChartDataArrays** to TRUE in the **sc.SetDefaults** code block in your study function.
* **sc.BaseData[SC\_ASKBID\_NUM\_TRADES\_DIFF\_HIGH]:** The array containing the maximum difference between the number of trades at the Ask price or higher and the number of trades at the Bid price or lower, for the bar at the specified Index. This is calculated at every tick during the creation of the bar. For the data in this array to be accurate, the **Intraday Data Storage Time Unit** setting in **Global Settings >> Data/Trade Service Settings** must be 1 Tick. The data in this array will not be available for historical data that does not have Ask and Bid volume.
    
  If you are using this array in your study function, you must set **sc.MaintainAdditionalChartDataArrays** to 1 in the sc.SetDefaults code block.
* **sc.BaseData[SC\_ASKBID\_NUM\_TRADES\_DIFF\_LOW]:** The array containing the minimum difference between the number of trades at the Ask price or higher and the number of trades at the Bid price or lower, for the bar at the specified Index. This is calculated at every tick during the creation of the bar. For the data in this array to be accurate, the **Intraday Data Storage Time Unit** setting in **Global Settings >> Data/Trade Service Settings** must be 1 Tick. The data in this array will not be available for historical data that does not have Ask and Bid volume.
    
  If you are using this array in your study function, you must set **sc.MaintainAdditionalChartDataArrays** to 1 in the sc.SetDefaults code block.
* **sc.BaseData[SC\_UPDOWN\_VOL\_DIFF\_HIGH]**: The array containing the *maximum* difference between the total volume of trades for the bar where the trades occurred at a higher price than the trade before and the total volume of trades for the bar where the trades occurred at a lower price than the trade before. Also take note of the additional details explained in **sc.BaseData[SC\_UPVOL/SC\_DOWNVOL]**.
    
  If you are using this array in your study function, you must set **sc.MaintainAdditionalChartDataArrays** to 1 in the sc.SetDefaults code block.
* **sc.BaseData[SC\_UPDOWN\_VOL\_DIFF\_LOW]**: The array containing the *minimum* difference between the total volume of trades for the bar where the trades occurred at a higher price than the trade before and the total volume of trades for the bar where the trades occurred at a lower price than the trade before. Also take note of the additional details explained in **sc.BaseData[SC\_UPVOL/SC\_DOWNVOL]**.
    
  If you are using this array in your study function, you must set **sc.MaintainAdditionalChartDataArrays** to 1 in the sc.SetDefaults code block.
* **sc.BaseData[SC\_RENKO\_OPEN]:** In the case of a Renko chart set through **Chart >> Chart Settings**, this array provides the Renko Open price. This array is used to draw the Renko bar body.
* **sc.BaseData[SC\_RENKO\_CLOSE]:** In the case of a Renko chart set through **Chart >> Chart Settings**, this array provides the Renko Close price. This array is used to draw the Renko bar body.
* **sc.BaseData[SC\_BID\_PRICE]:** This array contains the bid prices at the time of the last trade for each bar. By default, the Bid and Ask prices are only recorded when there is a trade.
    
    
  When using this array in a study function, it is necessary to set [sc.MaintainAdditionalChartDataArrays](#scmaintainadditionalchartdataarrays) to 1 in the [sc.SetDefaults](#scsetdefaults) code block.
    
    
  For there to be Bid prices in this array, Sierra Chart must be set to a [Tick by tick Data Configuration](TickbyTickDataConfiguration.md), the Intraday data file for the chart must contain tick by tick data, and contain a Bid and Ask prices. This is not supported with all Data and Trading services.
* **sc.BaseData[SC\_ASK\_PRICE]:** This array contains the ask prices at the time of the last trade for each bar. By default, the Bid and Ask prices are only recorded when there is a trade.
    
    
  When using this array in a study function, it is necessary to set [sc.MaintainAdditionalChartDataArrays](#scmaintainadditionalchartdataarrays) to 1 in the [sc.SetDefaults](#scsetdefaults) code block.
    
    
  For there to be Ask prices in this array, Sierra Chart must be set to a [Tick by tick Data Configuration](TickbyTickDataConfiguration.md), the Intraday data file for the chart must contain tick by tick data, and contain a Bid and Ask prices. This is not supported with all Data and Trading services.
* **sc.BaseData[SC\_ASK\_BID\_VOL\_DIFF\_MOST\_RECENT\_CHANGE]:** This array contains a value indicating whether the **SC\_ASKBID\_DIFF\_HIGH** or the **SC\_ASKBID\_DIFF\_LOW** array was most recently changed.
    
    
  It will be set to 1 if the **SC\_ASKBID\_DIFF\_HIGH** array at the corresponding element was most recently changed. It will be set to -1 if the **SC\_ASKBID\_DIFF\_LOW** array at the corresponding element was most recently changed. When using this array in a study function, it is necessary to set [sc.MaintainAdditionalChartDataArrays](#scmaintainadditionalchartdataarrays) to 1 in the [sc.SetDefaults](#scsetdefaults) code block.
* **sc.BaseData[PF\_DIRECTION\_ARRAY]:** This array is only used with [Point and Figure chart bars](ChartSettings.md#timeperiodperbar). Otherwise, the array is empty.
    
    
  At a particular chart bar index it will have a value of 1 if the Point and Figure chart bar is an Up bar. At a particular chart bar index it will have a value of -1 if the Point and Figure chart bar is an Down bar.

The index value returned by [sc.Input[].GetInputDataIndex()](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputGetInputDataIndex), corresponds to the array index constants given above. You can use this Input to select any of these array index constants to use with sc.BaseData[].

**sc.BaseData** is short-hand for **sc.BaseDataIn**.

#### Example

```cpp

// Get the volume at the current index.
// This requires sc.AutoLoop = 1;
float Volume = sc.BaseData[SC_VOLUME][sc.Index];

// Copy the Last price from the current index to sc.Subgraph 0
sc.Subgraph[0][sc.Index]=sc.BaseData[SC_LAST][sc.Index];
            
```

### sc.BaseData References

[Link](#scbasedatareferences) - [Top](#top)

A useful technique to make it easier to work with a single array for main price graph is to use a reference to the array. A reference to one of these arrays would be declared as **SCFloatArrayRef**. **SCFloatArrayRef** is a reference to the type of the arrays that are used in **sc.BaseData[]**. Below is an example of using a reference to one of the arrays in the chart.

#### Example

```cpp

// Make a reference to the array of High prices called Highs
SCFloatArrayRef Highs = sc.BaseData[SC_HIGH];

// Get the high price at the current index
// This is the same as sc.BaseData[SC_HIGH][sc.Index]
float HighValue = Highs[sc.Index];
            
```

### sc.BaseDateTimeIn[]

[Link](#scbasedatetimein) - [Top](#top)

**Type**: Read-only **SCDateTime** array.

**sc.BaseDateTimeIn[]** is an array of the Date-Time for each bar in the chart. Each element of the array is a **[SCDateTime](SCDateTime.md)**.

The word **In** at the end of this array means input, which signifies that this array is input data for your study.

The Date-Time for a chart bar is the starting time of that bar. To get the ending Date-Time of the chart bar, use [sc.BaseDataEndDateTime](#scbasedataenddatetime).

For information about array indexing and array sizes, refer to [Array Indexing and Sizes](ACS_ArraysAndLooping.md#arrayindexing).

The [Time Zone](TimeZone.md) of the Date-Times in the array is the same time zone as the chart.

#### Example

```cpp

// Get the DateTime at the current index.
SCDateTime BarDateTime = sc.BaseDateTimeIn[sc.Index];
            
```

Since this is a [SCDateTime](SCDateTime.md) array, you can use the **DateAt()** and **TimeAt()** member functions to get just the date or just the time at a single bar.

#### Example

```cpp

// Get the date
int BarDate = sc.BaseDateTimeIn.DateAt(sc.Index);

// Get the time
int BarTime = sc.BaseDateTimeIn.TimeAt(sc.Index);
            
```

### sc.BasedOnGraphValueFormat

[Link](#scbasedongraphvalueformat) - [Top](#top)

**Type**: Read-only integer variable.

This variable uses the same values as **sc.ValueFormat** and is set to the Value Format for the graph set with the **Based On**  setting on an instance the study which has been applied to the chart.

### sc.BaseGraphAutoScalePaddingPercentage

[Link](#scbasegraphautoscalepaddingpercentage) - [Top](#top)

**Type**: Read/Write float variable.

The **sc.BaseGraphAutoScalePaddingPercentage** variable is identical to [sc.AutoScalePaddingPercentage](#scautoscalepaddingpercentage) except it is for the main price graph in the chart and not the study instance itself.

### sc.BaseGraphConstantRangeScaleMode

[Link](#scbasegraphconstantrangescalemode) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.BaseGraphConstantRangeScaleMode** variable is the constant range scale mode for the main price graph in the chart.

It can be any of the following constant values:

* CONST\_RANGE\_MODE\_MANUAL = 0
* CONST\_RANGE\_MODE\_AUTO\_CENTER\_LAST\_BAR = 1 (Equivalent to **Keep The Last Bar Within View**)
* CONST\_RANGE\_MODE\_AUTO\_CENTER\_LAST\_PRICE = 2
* CONST\_RANGE\_MODE\_AUTO\_KEEP\_LAST\_BAR\_WITHIN\_TICKS\_FROM\_EDGE = 3
* CONST\_RANGE\_MODE\_AUTO\_CENTER\_WHEN\_BAR\_BEYOND\_TICKS\_FROM\_CENTER = 4

For more information, refer to the [Chart Scale](Scaling.md#constantrangescalerange) page.

### sc.BaseGraphGraphDrawType

[Link](#scbasegraphgraphdrawtype) - [Top](#top)

Type: Read/Write integer variable.

**sc.BaseGraphGraphDrawType** is set to the Graph Draw Type for the base graph in the chart. This is also known as the main price graph. This is a read/write value and can be changed.

Supported Values:

* GDT\_CUSTOM
* GDT\_OHLCBAR
* GDT\_CANDLESTICK
* GDT\_CANDLESTICK\_BODY\_ONLY
* GDT\_LINEONCLOSE
* GDT\_MOUNTAIN
* GDT\_HLCBAR
* GDT\_LINEONOPEN
* GDT\_LINEONHLAVG
* GDT\_STAIRSTEPONCLOSE
* GDT\_HLBAR
* GDT\_KAGI
* GDT\_POINT\_AND\_FIGURE\_BARS
* GDT\_POINT\_AND\_FIGURE\_XO
* GDT\_BID\_ASK\_BAR
* GDT\_PRICE\_VOLUME
* GDT\_CANDLE\_PRICE\_VOLUME\_BAR
* GDT\_BLANK
* GDT\_NUMBERS\_BARS
* GDT\_NUMERIC\_INFORMATION
* GDT\_RENKO\_BRICK
* GDT\_RENKO\_BRICK\_WITH\_WICKS
* GDT\_CANDLESTICK\_HOLLOW
* GDT\_MARKET\_DEPTH
* GDT\_VOLUME\_LEVEL\_TRADES
* GDT\_CANDLE\_PRICE\_VOLUME\_BAR\_HOLLOW

### sc.BaseGraphHorizontalGridLineIncrement

[Link](#scbasegraphhorizontalgridlineincrement) - [Top](#top)

**Type**: Read/Write float variable.

The **sc.BaseGraphHorizontalGridLineIncrement** variable is the increment between the horizontal grid lines for the main price graph in the chart, if the chart is set to display the horizontal grid lines. Zero means that the setting is automatic.

For additional information, refer to [Horizontal Grid Line Increment](Scaling.md#horizgridlineincrement) on the Chart Scale page.

### sc.BaseGraphScaleConstRange

[Link](#scbasegraphscaleconstrange) - [Top](#top)

**Type**: Read/write float variable.

The **sc.BaseGraphScaleConstRange** variable gets and sets the grayscale range for the chart base graph when it is using a Scale Type of **Constant Range**. For additional information, refer to the [Chart Scale and Scale Adjusting](Scaling.md) documentation.

When changing the symbol of the chart, this constant range value gets reset to a default value based upon the **Tick Size** of the chart.

### sc.BaseGraphScaleIncrement

[Link](#scbasegraphscaleincrement) - [Top](#top)

**Type**: Read/write float variable.

This sets the Scale Increment for the main price graph. When it is set to a nonzero value, it will change the Scale Increment for the main price graph.

#### Example

```cpp

sc.BaseGraphScaleIncrement= 0;
            
```

### sc.BaseGraphScaleValueOffset

[Link](#scbasegraphscalevalueoffset) - [Top](#top)

**Type**: Read/Write 32-bit float value.

The **sc.BaseGraphScaleValueOffset** variable is the percentage value, where 1% is .01, for the offset of the chart scale from the center. This applies to the main price graph for the study and not for the study itself.

This can be programmatically set and is also interactively set by the user through the [Interactive Scale Move](Scaling.md#interactivescalingmoveupdown) functionality.

Also refer to [sc.ScaleValueOffset](#scscalevalueoffset).

### sc.BaseGraphScaleRangeBottom

[Link](#scbasegraphscalerangebottom) - [Top](#top)

**Type**: Read/Write float variable.

The **sc.BaseGraphScaleRangeBottom** variable is the bottom/minimum value of a User Defined scale range for the main price graph in the chart.

In the user interface this setting is in **Chart >> Chart Settings >> Scale >> Scale Range >> User-Defined >> Bottom of Range**.

This can be modified by the custom study.

To get and set the bottom of the User Defined scale range for the study itself, use [sc.ScaleRangeBottom](#scscalerangebottom).

#### Example

```cpp

float ScaleBottom = sc.BaseGraphScaleRangeBottom;
            
```

### sc.BaseGraphScaleRangeTop

[Link](#scbasegraphscalerangetop) - [Top](#top)

Type: Read/Write float variable.

The **sc.BaseGraphScaleRangeTop** variable is the top/maximum value of a User Defined scale range for the main price graph in the chart.

In the user interface this setting is in **Chart >> Chart Settings >> Scale >> Scale Range >> User-Defined >> Top of Range**.

This can be modified by the custom study.

To get and set the top of the User Defined scale range for the study itself, use [sc.ScaleRangeTop](#scscalerangetop).

#### Example

```cpp

float ScaleTop = sc.BaseGraphScaleRangeTop;
            
```

### sc.BaseGraphScaleRangeType

[Link](#scbasegraphscalerangetype) - [Top](#top)

Type: Read/Write integer variable.

Initial value: **SCALE\_AUTO**

The **sc.BaseGraphScaleRangeType** member allows you to determine and set the vertical scale range type for the main price graph (base graph) in the chart. It can be any of the following values:

* SCALE\_AUTO
* SCALE\_USERDEFINED
* SCALE\_INDEPENDENT
* SCALE\_SAMEASREGION
* SCALE\_CONSTANT\_RANGE
* SCALE\_CONSTRANGECENTER
* SCALE\_ZEROBASED
* SCALE\_ZEROCENTERED

When using **SCALE\_USERDEFINED**, it is necessary to also set [sc.ScaleRangeTop](#scscalerangetop) and [sc.ScaleRangeBottom](#scscalerangebottom).

#### Example

```cpp

sc.BaseGraphScaleRangeType = SCALE_AUTO;
            
```

### sc.BaseGraphValueFormat

[Link](#scbasegraphvalueformat) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.BaseGraphValueFormat** variable is an Integer indicating the **Price Display Format/Value Format** for the main graph in the chart.

This is set through **Chart >> Chart Settings**. It is most useful to use with the sc.FormatGraphValue() function.

#### Example

```cpp

SCString CurrentHigh = sc.FormatGraphValue(sc.BaseData[SC_HIGH][CurrentVisibleIndex], sc.BaseGraphValueFormat);
            
```

### sc.Bid

[Link](#scbid) - [Top](#top)

**Type**: Read-only float variable.

**sc.Bid** is the current Bid price value for the symbol if Bid and Ask data is available for the symbol.

If the chart is not replaying, then this will only be set and up-to-date when Sierra Chart is connected to the data feed.

During a replay, this value is set. For additional information, refer to [Trade Simulation Accuracy and Bid/Ask Prices During Replays](TradeSimulation.md#tradesimulationbidaskprices).

### sc.BidSize

[Link](#scbidsize) - [Top](#top)

**Type**: Read-only integer variable.

**sc.BidSize** is the current Bid size/quantity value for the symbol if Bid and Ask data is available for the symbol.

If the chart is not replaying, then this will only be set and up-to-date when Sierra Chart is connected to the data feed, and the market is open.

During a replay, this value will be set to 1.

### sc.BlockChartDrawingSelection

[Link](#scblockchartdrawingselection) - [Top](#top)

**Type**: Read/Write integer variable.

Refer to [sc.BlockChartDrawingSelection](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scblockchartdrawingselection).

### sc.CalculationPrecedence

[Link](#sccalculationprecedence) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: **STD\_PREC\_LEVEL**

**sc.CalculationPrecedence** is a variable that can be set to 3 possible values.

The default value is **STD\_PREC\_LEVEL** (standard precedence level), and will mean your study gets calculated relative to other studies on the same chart that your custom study is applied to, based on its position in the **Analysis >> Studies >> Studies to Graph** list for the chart.

A value of **LOW\_PREC\_LEVEL** (low precedence level) will mean your study gets calculated after all other studies with a standard precedence level.

A value of **VERY\_LOW\_PREC\_LEVEL** (very low precedence level) will mean your study gets calculated after all other studies with standard and low precedence levels. You will want to use a very low precedence level if your study depends on other studies that have low precedence level, such as Study Moving Average or a study based on other study.

The reason why you would want to set this variable to a lower precedence level, is when you are using a function such as **[sc.GetStudyArray()](ACSIL_Members_Functions.md#scgetstudyarray)**.

It is not necessary to set a low precedence when you are internally calculating study formulas, like when using **[sc.SimpleMovAvg()](ACSIL_Members_Functions.md#scsimplemovavg)**.

For further information about study calculation precedence, refer to [Study Calculation Precedence And Related Issues](ChartStudies.md#studycalculationprecedence).

#### Example

```cpp

sc.CalculationPrecedence = STD_PREC_LEVEL;
            
```

### sc.CancelAllOrdersOnEntries

[Link](#sccancelallordersonentries) - [Top](#top)

**Type**: Read/Write integer variable.

For the documentation for **sc.CancelAllOrdersOnEntries**, refer to [CancelAllOrdersOnEntries](AutoTradeManagment.md#cancelallordersonentries) on the Automated Trading Management page.

### sc.CancelAllOrdersOnReversals

[Link](#sccancelallordersonreversals) - [Top](#top)

**Type**: Read/Write integer variable.

For the documentation for **sc.CancelAllOrdersOnReversals**, refer to [CancelAllOrdersOnReversals](AutoTradeManagment.md#cancelallordersonreversals) on the Automated Trading Management page.

### sc.CharacterEventCode

[Link](#sccharactereventcode) - [Top](#top)

**Type**: Read integer variable.

The **sc.CharacterEventCode** variable is set to the [ASCII](https://en.wikipedia.org/wiki/ASCII) value of the corresponding character pressed on the keyboard when the study has requested these events by setting [sc.ReceiveCharacterEvents](#screceivecharacterevents).

The study function will be called when a character key is pressed and the chart containing the study has the focus. Otherwise, this variable will not be set.

### sc.ChartBackgroundColor

[Link](#scchartbackgroundcolor) - [Top](#top)

**Type**: Read/Write RGB integer color variable.

**sc.ChartBackgroundColor** sets the background color of the chart. This does not affect the global chart background color setting, only the chart specific setting. When setting this variable, it is also necessary to set **sc.UseGlobalChartColors = 0** outside of the **sc.SetDefaults** code block, otherwise the variable is ignored.

#### Example

```cpp

sc.UseGlobalChartColors = 0;

sc.ChartBackgroundColor = RGB(123,123,123);
            
```

### sc.ChartBarSpacing

[Link](#scchartbarspacing) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.ChartBarSpacing** vvariable is the spacing between the chart bars in pixels. This is for the chart your custom study is applied to.

The bar spacing can be changed by the custom study.

#### Example

```cpp

int ChartBarSpacing = sc.ChartBarSpacing;
            
```

### sc.ChartbookName

[Link](#scchartbookname) - [Top](#top)

**Type**: Function returning [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings).

This member has been changed to a function effective with version 2152.

The **sc.ChartbookName** function which returns a text string which contains the name of the Chartbook that contains the chart the study instance is applied to.

### sc.ChartDataEndDate

[Link](#scchartdataenddate) - [Top](#top)

**Type**: Read/Write integer variable.

When **sc.LoadChartDataByDateRange** is set to a nonzero value, then the [sc.ChartDataEndDate](#scchartdatastartdate) variable specifies the last date to load into the chart.

This variable corresponds to **Chart >> Chart Settings**  **>> Use Date Range >> To**.

If this is set to 0, then the last date available in the chart data file is loaded into the chart. For further information, refer to [Use Date Range >> To](ChartSettings.md#usedaterangefromto).

Changes to this variable do not go into effect until the study function returns. The chart will then be reloaded.

### sc.ChartDataStartDate

[Link](#scchartdatastartdate) - [Top](#top)

**Type**: Read/Write integer variable.

When **sc.LoadChartDataByDateRange** is set to a nonzero value, then the [sc.ChartDataStartDate](#scchartdatastartdate) variable specifies the first date to load into the chart.

This variable corresponds to **Chart >> Chart Settings**  **>> Use Date Range >> From**.

If this is set to 0, then the earliest date available in the chart data file is loaded into the chart. For further information, refer to [Use Date Range >> From](ChartSettings.md#usedaterangefromto).

Changes to this variable do not go into effect until the study function returns. The chart will then be reloaded.

### sc.ChartDataType

[Link](#scchartdatatype) - [Top](#top)

Type: Read/write integer variable.

**sc.ChartDataType** is set to the data type of the underlying chart. This can be either Intraday data or Daily data.

#### Example

```cpp

if (sc.ChartDataType == DAILY_DATA)
{
    // The chart is a Historical Daily chart

}
else if (sc.ChartDataType == INTRADAY_DATA)
{
    // The chart is an Intraday chart

}
            
```

### sc.ChartNumber

[Link](#scchartnumber) - [Top](#top)

**Type**: Read-only integer variable.

Every chart contained within a Chartbook has a unique number.

**sc.ChartNumber** is set to the identifying number of the chart that the study is applied to. This is the same number that is shown on the top [Region Data Line](WorkingWithCharts.md#regiondataline) of the chart and on the chart window title bar.

If the identifying number of the chart calling the study function is #1, then the value of **sc.ChartNumber** will be 1.

### sc.ChartRegion1BottomCoordinate

[Link](#scchartregion1bottomcoordinate) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.ChartRegion1BottomCoordinate** variable contains the Y-axis pixel coordinate that represents the bottom side of the rectangle that makes up Chart Region 1. For more information on chart regions, refer to [Chart Window and Regions](WorkingWithCharts.md#chartwindowandregions).

The top left pixel coordinate of the chart is at 0, 0. These coordinates increase moving towards the bottom and right.

### sc.ChartRegion1LeftCoordinate

[Link](#scchartregion1leftcoordinate) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.ChartRegion1LeftCoordinate** variable contains the X-axis pixel coordinate that represents the left side of the rectangle that makes up Chart Region 1. For more information on chart regions, refer to [Chart Window and Regions](WorkingWithCharts.md#chartwindowandregions).

The top left pixel coordinate of the chart is at 0, 0. These coordinates increase moving towards the bottom and right.

### sc.ChartRegion1RightCoordinate

[Link](#scchartregion1rightcoordinate) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.ChartRegion1RightCoordinate** variable contains the X-axis pixel coordinate that represents the right side of the rectangle that makes up Chart Region 1. For more information on chart regions, refer to [Chart Window and Regions](WorkingWithCharts.md#chartwindowandregions).

The top left pixel coordinate of the chart is at 0, 0. These coordinates increase moving towards the bottom and right.

### sc.ChartRegion1TopCoordinate

[Link](#scchartregion1topcoordinate) - [Top](#top)

**Type**: Read-only integer variable.

The **scChartRegion1TopCoordinate** variable contains the Y-axis pixel coordinate that represents the top side of the rectangle that makes up Chart Region 1. For more information on chart regions, refer to [Chart Window and Regions](WorkingWithCharts.md#chartwindowandregions).

The top left pixel coordinate of the chart is at 0, 0. These coordinates increase moving towards the bottom and right.

### sc.ChartTextFont

[Link](#sccharttextfont) - [Top](#top)

**Type**: Function returning [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings).

This member has been changed to a function effective with version 2152.

The **sc.ChartTextFont** function returns a text string which contains the font name used by the chart. This is useful if you want to create a font that matches the chart text.

### sc.ChartTradeModeEnabled

[Link](#sccharttrademodeenabled) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.ChartTradeModeEnabled** variable indicates whether the [Trade >> Chart Trade Mode On](TradeMenu.md#charttrademodeon) option is enabled or not.

When the **Chart Trade Mode On** is enabled, this variable has a value of **1**. Otherwise, it is **0**.

### sc.ChartTradingOrderPrice

[Link](#sccharttradingorderprice) - [Top](#top)

**Type**: Read-only double precision floating-point variable.

When in Chart Trade Mode, the **sc.ChartTradingOrderPrice**  variable indicates the price level that the mouse pointer is at on the chart. This applies to the chart that the study function is applied to.

### sc.ChartUpdateIntervalInMilliseconds

[Link](#scchartupdateintervalinmilliseconds) - [Top](#top)

**Type**: Read Only integer variable.

**sc.ChartUpdateIntervalInMilliseconds** is the defined update interval for the chart in which this study is applied.

### sc.ChartWindowHandle

[Link](#scchartwindowhandle) - [Top](#top)

**Type**: Read Only integer variable.

**sc.ChartWindowHandle** is the Windows API handle (HWND) for the chart window that the study is applied to. This is useful when making Windows API function calls that require a window handle. This is for advanced programming only.

The window handle is provided even when the study is first calculated after the Chartbook is opened that the study instance is contained within.

### sc.ChartWindowIsActive

[Link](#scchartwindowisactive) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.ChartWindowIsActive** variable is set to 1 when the chart that contains the study instance, is the active chart window within Sierra Chart. This means either that it has the focus, or it is considered the active chart window within Sierra Chart if no Sierra Chart window currently has the focus.

### sc.ConnectToExternalServiceServer

[Link](#scconnecttoexternalserviceserver) - [Top](#top)

**Type**: Write integer variable.

Set the **sc.ConnectToExternalServiceServer**  variable to TRUE to perform the  **File >> Connect to Data Feed**  command from within your custom study. This is not performed immediately at the time you set this to TRUE. It is only done when your study function returns.

Also see [sc.DisconnectFromExternalServiceServer](#scdisconnectfromexternalserviceserver) and [sc.ReconnectToExternalServiceServer](#screconnecttoexternalserviceserver).

#### Example

```cpp

sc.ConnectToExternalServiceServer = TRUE;
            
```

### sc.ConstantRangeScaleModeTicksFromCenterOrEdge

[Link](#scconstantrangescalemodeticksfromcenteroredge) - [Top](#top)

**Type**: Read/Write Integer variable.

The **sc.ConstantRangeScaleModeTicksFromCenterOrEdge** variable is set to the **Ticks from Center** setting for the **Constant Range**  [Scale Range](Scaling.md#scalerange).

This variable applies only to the main price graph scale and not to the study scale.

The study can change this variable.

### sc.ContinuousFuturesContractLoading

[Link](#sccontinuousfuturescontractloading) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.ContinuousFuturesContractLoading** variable is set to 1 when a chart is in the process of loading the historical futures contract data when the **Chart >> Chart Settings >> Symbol >> Continuous Contract** option is enabled. Otherwise, if the option is not enabled or the chart is not loading the historical futures contract data, then this will be 0. This flag is useful to avoid certain processing in your study function during the loading process.

### sc.ContinuousFuturesContractOption

[Link](#sccontinuousfuturescontractoption) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.ContinuousFuturesContractOption** variable is equivalent to the [Continuous Contract](ChartSettings.md#continuousfuturescontract) setting in Chart Settings.

This variable can be changed to update this Chart Setting.

The possible values are listed below.

* **CFCO\_NONE** = 0
* **CFCO\_DATE\_RULE\_ROLLOVER** = 1
* **CFCO\_VOLUME\_BASED\_ROLLOVER** = 2
* **CFCO\_DATE\_RULE\_ROLLOVER\_BACK\_ADJUSTED** = 3
* **CFCO\_VOLUME\_BASED\_ROLLOVER\_BACK\_ADJUSTED** = 4
* **CFCO\_FORWARD\_CURVE\_CURRENT\_DAY** = 5
* **CFCO\_ROLLOVER\_EACH\_YEAR\_SAME\_MONTH** = 6

### sc.ContractRolloverDate

[Link](#sccontractrolloverdate) - [Top](#top)

**Type**: Read Only [SCDateTime](SCDateTime.md) variable.

The **sc.ContractRolloverDate** variable is the rollover date associated with the futures symbol for chart the study instance is applied to.

For an example to use this variable, refer to the scsf\_RolloverDateDisplay function in the /ACS\_Source/studies2.cpp file in the Sierra Chart installation folder.

### sc.CurrencyValuePerTick

[Link](#sccurrencyvaluepertick) - [Top](#top)

**Type**: Read/Write float variable.

**sc.CurrencyValuePerTick** is a variable that is set to the currency value per tick of the chart the study instance is applied to.

This is the same as the [Currency Value per Tick](ChartSettings.md#currencyvaluepertick) setting for the chart.

### sc.CurrentSystemDateTime

[Link](#sccurrentsystemdatetime) - [Top](#top)

**Type:** Read Only [SCDateTime](SCDateTime.md) variable.

**sc.CurrentSystemDateTime** is the current Date and Time from your local computer's date and time, provided as a **[SCDateTime](SCDateTime.md)** variable.

The Time Zone setting in **Global Settings >> Data/Trade Service Settings** is applied to this SCDateTime variable.

This member is not affected by the chart the study is applied to, when being replayed. In other words, it will always indicate the current system Date-Time.

This variable does not contain milliseconds. The resolution is to the second.

If you want to perform a particular action in a custom study at a particular time and want to make sure the study function is called at that time, then you should use [sc.UpdateAlways = 1](#scupdatealways) in the **sc.SetDefaults** block of the study function.

#### Example

```cpp

SCDateTime DateTime = sc.CurrentSystemDateTime;
            
```

### sc.CurrentDateTimeForReplay

[Link](#sccurrentdatetimeforreplay) - [Top](#top)

**Type:** Read Only [SCDateTime](SCDateTime.md) variable.

The sc.CurrentDateTimeForReplay variable is only set when a chart is replaying. It contains the current Date-Time in relation to the replaying chart and is relative to the starting Date-Time of the replaying chart. It is based upon the elapsed amount of time since the replay was started and the replay speed.

If you want to perform a particular action in a custom study at a particular time and want to make sure the study function is called at that time, then you should use [sc.UpdateAlways = 1](#scupdatealways) in the **sc.SetDefaults** block of the study function.

However, when there is an accelerated replay, a study function will not necessarily be called at the interval specified by the [Chart Update Interval](ChartSettings.md#chartupdateinterval) relative to the replay times. For example, if the chart is set to update every 1000 milliseconds, during an accelerated replay it will not necessarily be called every theoretical second when using **sc.UpdateAlways = 1**.

During an accelerated replay, **sc.CurrentDateTimeForReplay** can be ahead of the expected time. For complete information, refer to the function [sc.GetCurrentDateTime](ACSIL_Members_Functions.md#scgetcurrentdatetime). **sc.CurrentDateTimeForReplay** is used with that function during a replay.

#### Example

```cpp

SCDateTime CurrentDateTime;
if (sc.IsReplayRunning())
    CurrentDateTime = sc.CurrentDateTimeForReplay;
else
    CurrentDateTime = sc.CurrentSystemDateTime;
            
```

### sc.CurrentSystemDateTimeMS

[Link](#sccurrentdatetimems) - [Top](#top)

**Type**: Read-only SCDateTimeMS variable.

**sc.CurrentSystemDateTimeMS** is the current Date and Time from your local computer's date and time, provided as a **[SCDateTimeMS](SCDateTime.md)** variable.

**SCDateTimeMS** is derived from [SCDateTime](SCDateTime.md). It contains all of the same functionality, except that it is specialized for milliseconds. Comparisons done using this type are down to the nearest millisecond unlike the nearest second for SCDateTime.

The Time Zone setting in **Global Settings >> Data/Trade Service Settings** is applied to this SCDateTimeMS variable.

This member is not affected by the chart the study is applied to, when being replayed. In other words, it will always indicate the current system Date-Time.

This variable contains the Date-Time of the computer system down to the millisecond.

If you want to perform a particular action in a custom study at a particular time and want to make sure the study function is called at that time, then you should use [sc.UpdateAlways = 1](#scupdatealways) in the **sc.SetDefaults** block of the study function.

#### Example

```cpp

SCDateTimeMS DateTimeWithMilliseconds = sc.CurrentSystemDateTimeMS;
            
```

### sc.CurrentlySelectedDrawingTool

[Link](#sccurrentlyselecteddrawingtool) - [Top](#top)

**Type**: Read-only integer variable.

**sc.CurrentlySelectedDrawingTool**

#### Example

```cpp

int CurrentlySelectedDrawingTool
            
```

### sc.CurrentlySelectedDrawingToolState

[Link](#sccurrentlyselecteddrawingtoolstate) - [Top](#top)

**Type**: Read-only integer variable.

**sc.CurrentlySelectedDrawingToolState** set to a constant indicating the state of the active drawing tool. This will be 0 when the tool is not active and > 0 when the tool is active. For example, when actively drawing a line with the  **Line**  Tool, this will be set to 1.

#### Example

```cpp

int ToolState =  sc.CurrentlySelectedDrawingToolState;
            
```

### sc.CustomAffiliateCode

[Link](#sccustomaffiliatecode) - [Top](#top)

**Type**: Function returning [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings).

This member has been changed to a function effective with version 2152.

The **sc.CustomAffiliateCode** function returns a text string which contains the affiliate code associated with a particular Sierra Chart account.

This function has specialized uses and is not normally used.

### sc.CustomChartTitleBarName

[Link](#sccustomcharttitlebarname) - [Top](#top)

**Type**: Read/Write SCString variable.

The **sc.CustomChartTitleBarName** variable is for getting and setting the **Chart >> Chart Settings** **>> Display >> Title Bar Name** setting.

### sc.DailyHigh

[Link](#scdailyhigh) - [Top](#top)

**Type**: Read Only float variable.

**sc.DailyHigh** is the current daily high for the symbol of the chart.

**sc.DailyHigh** is the same Daily High value displayed in the **Window >> Current Quote Window**. This data comes from the Current Quote Data from the connected data feed.

**sc.DailyHigh** is only valid when connected to the data feed or during a chart replay.

### sc.DailyLow

[Link](#scdailylow) - [Top](#top)

**Type**: Read-only float variable.

**sc.DailyLow** is the current daily low for the symbol of the chart.

**sc.DailyLow** is the same Daily Low value displayed in the **Window >> Current Quote Window**. This data comes from the Current Quote Data from the connected data feed.

**sc.DailyLow** is only valid when connected to the data feed or during a chart replay.

### sc.DailyStatsResetTime

[Link](#scdailystatsresettime) - [Top](#top)

**Type**: Read-only [SCDateTime](SCDateTime.md) variable.

This is no longer used.

### sc.DailyVolume

[Link](#scdailyvolume) - [Top](#top)

**Type**: Read-only integer variable.

**sc.DailyVolume** is the current daily volume for the symbol.

**sc.DailyVolume** is the same Daily Volume value displayed in the **Window >> Current Quote Window**. This data comes from the Current Quote Data from the connect to data feed.

**sc.DailyVolume** is only valid when connected to the data feed.

**sc.DailyVolume** will be 0 during a chart replay.

### sc.DataFeedActivityCounter

[Link](#scdatafeedactivitycounter) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.DataFeedActivityCounter** variable is the activity counter for the incoming data feed that Sierra Chart is currently connected to.

It is the same value shown on the [Status Bar](StatusBar.md) after **DF:**.

### sc.DataFile

[Link](#scdatafile) - [Top](#top)

**Type**: Read/Write SCString variable.

**sc.DataFile** is a text string of the complete path and file name of the chart data file for the chart the study instance is applied to.

This text string can be changed to change the *symbol* of the chart.

When this is changed, the new data file will be loaded *after* the study function returns. So the data file will be changed before the next call into the study function which is called after the new data file is loaded.

Only the filename needs to be set. The path is ignored. The **Global Settings >> General Settings >> Data Files Folder** setting is used for the path.

The file extension has to be set. Use **.dly** for Historical charts and **.scid** for Intraday charts.

#### Example

```cpp

// Specify a new chart data file
sc.DataFile = "QQQQ.scid";
            
```

### sc.DataFilesFolder

[Link](#scdatafilesfolder) - [Top](#top)

**Type**: Function returning [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings).

This member has been changed to a function effective with version 2152.

The **sc.DataFilesFolder** function returns a text string which contains the complete path to the Data files folder used by Sierra Chart.

For further information, refer to [Data Files Folder](GeneralSettings.md#datafilesfolder).

### sc.DataStartIndex

[Link](#scdatastartindex) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0

Set **sc.DataStartIndex** to the index of the first element at which subgraphs should start to be drawn. This is to prevent Sierra Chart from drawing elements at the beginning of the sc.Subgraph arrays that do not have enough prior data to be properly calculated. For example: If you have a 10-bar moving average, this value should be set to 9. It should be set to 9 instead of 10 because array index values always begin at 0.

#### Example

```cpp

sc.DataStartIndex = 9; // Start drawing the subgraphs at element index 9 (the 10th bar)
            
```

### sc.DateTimeOfLastFileRecord

[Link](#scdatetimeoflastfilerecord) - [Top](#top)

**Type:** Read Only [SCDateTime](SCDateTime.md) variable.

**sc.DateTimeOfLastFileRecord** is the Date-Time, as a SCDateTime variable, of the starting time of the last data record read from the chart data file which has been added to the chart.

### sc.DateTimeOut[]

[Link](#scdatetimeout) - [Top](#top)

**Type**: Read/Write SCDateTime array.

**sc.DateTimeOut[]** is an array of the DateTimes for each of the bars you have created in a study which is set up as a custom chart. Each element is a **[SCDateTime](SCDateTime.md)**. This array is only used when **[sc.IsCustomChart](#sciscustomchart)** is set to 1 (TRUE).

For additional information about indexing and array sizes, see [Array Indexing and Sizes](ACS_ArraysAndLooping.md#arrayindexing).

#### Example

```cpp

// Set the element at our CustomIndex in sc.DateTimeOut to match the current index in sc.BaseDateTimeIn
sc.DateTimeOut[CustomIndex] = sc.BaseDateTimeIn[sc.Index];
            
```

### sc.DaysToLoadInChart

[Link](#scdaystoloadinchart) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.DaysToLoadInChart** variable is the number of days of data to load within the chart. It applies to both Intraday and Historical charts.

It is equivalent to **Chart >> Chart Settings >> Use Number of Days to Load >> Days to Load**.

Changes to this variable do not go into effect until the study function returns. At that time the chart will be reloaded and the new setting will go into effect.

If you are reducing the value of this variable, the chart needs to be reloaded to reduce the amount of data in the chart. There is not the capability to remove data in the chart without the chart needing to reload.

### sc.DeltaVolumePerBar

[Link](#scdeltavolumeperbar) - [Top](#top)

**Type**: Read/Write integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.DisconnectFromExternalServiceServer

[Link](#scdisconnectfromexternalserviceserver) - [Top](#top)

**Type**: Write integer variable.

Set the **sc.DisconnectFromExternalServiceServer** variable to TRUE to perform the  **File >> Disconnect** command from within your custom study. This is not performed immediately at the time you set this to TRUE. It is only done when your study function returns.

Also see [sc.ConnectToExternalServiceServer](#scconnecttoexternalserviceserver) and [sc.ReconnectToExternalServiceServer](#screconnecttoexternalserviceserver).

#### Example

```cpp

sc.DisconnectFromExternalServiceServer = TRUE;
            
```

### sc.DisplayAsMainPriceGraph

[Link](#scdisplayasmainpricegraph) - [Top](#top)

Type: Read/Write integer variable.

Initial value: 0 (FALSE)

If **sc.DisplayAsMainPriceGraph** is set to 1 (TRUE), then your study will become the main price graph for the chart. All other studies applied to the chart, will be based on it. You will also need to set **[sc.GraphRegion](#scgraphregion)** to 0, when setting this variable to 1 (TRUE). If it is set to 0 (FALSE), then your study is a standard study based on the existing main price graph.

#### Example

```cpp

sc.DisplayAsMainPriceGraph = 1;
            
```

### sc.DisplayStudyInputValues

[Link](#scdisplaystudyinputvalues) - [Top](#top)

**Type**: Read/Write integer variable.

sc.DisplayStudyInputValues is equivalent to the **Display Input Values** setting on the Study Settings window for the study. This variable can be set to either 1 to enable that option or to 0 to disable it.

#### Example

```cpp

sc.DisplayStudyInputValues = 1;
            
```

### sc.DisplayStudyName

[Link](#scdisplaystudyname) - [Top](#top)

**Type**: Read/Write integer variable.

sc.DisplayStudyName is equivalent to the **Display Study Name** setting on the Study Settings window for the study. This can be set to either 1 to enable that option or to 0 to disable it.

#### Example

```cpp

sc.DisplayStudyName = 1;
            
```

### sc.DLLNameUserServiceLevel

[Link](#scdllnameuserservicelevel) - [Top](#top)

**Type**: Read-only 8-byte integer variable.

**sc.DLLNameUserServiceLevel** is used in conjunction with the [sc.IsUserAllowedForSCDLLName](#scisuserallowedforscdllname) variable.

This variable returns the Service Level setting for an authorized user for the custom studies DLL that the function is in and the user has been authorized to use.

This value is set through the **Custom DLL Studies Management** control panel accessed through your account on the Sierra Chart website.

This is a 64-bit integer variable which can be set to any value. You can set it to the numbers which represent, certain bits within the 64-bit variable being set.

#### Example

```cpp

if (sc.DLLNameUserServiceLevel == 100)//Any number can be used.
{
  // Perform some action like executing the study
}
else
  return;// Do nothing and return
  
            
```

### sc.DocumentationImageURL

[Link](#scdocumentationimageurl) - [Top](#top)

**Type**: Read/Write SCString variable.

**sc.DocumentationImageURL** is a text string variable that can be set to an internet URL to an image providing an example of your study. For complete documentation refer to [ACSIL Study Documentation Interface Members](ACSILDocumentationMembers.md).

#### Example

```cpp

sc.DocumentationImageURL = "http://www.sierrachart.com/images/HomePageImages/HomePage_ChartWithStudies.png";
            
```

### sc.DoNotRedrawChartAfterStudyReturns

[Link](#scdonotredrawchartafterstudyreturns) - [Top](#top)

**Type**: Read/Write Integer variable.

The **sc.DoNotRedrawChartAfterStudyReturns** variable can be set to 1 or a nonzero value to prevent the chart from being redrawn after the study function returns.

Every time the studies on a chart are calculated either as part of a full recalculation or an update calculation, the chart is redrawn. When this variable is set to 1, it prevents the chart from being redrawn. Even if other studies have not set this variable to 1 during the studies calculation, the chart will still be prevented from being redrawn if one of the studies has set this to 1.

The purpose of this variable is to improve performance (reduce CPU usage) when handling certain events that the study is notified of when the study function is called. This includes key events indicated through variables like [sc.KeyboardKeyEventCode](#sckeyboardkeyeventcode) and [Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents). Some of these events should not cause the chart to be redrawn immediately but rather after some series of events as determined by the study function.

### sc.DownloadingHistoricalData

[Link](#scdownloadinghistoricaldata) - [Top](#top)

**Type**: Read-only integer variable.

**sc.DownloadingHistoricalData** is considered out of date and has been replaced by the [sc.ChartIsDownloadingHistoricalData](ACSIL_Members_Functions.md#scchartisdownloadinghistoricaldata) function.

### sc.DrawACSDrawingsAboveOtherDrawings

[link](#scdrawacsdrawingsaboveotherdrawings) - [Top](#top)

**Type**: Read/Write integer variable.

When the **sc.DrawACSDrawingsAboveOtherDrawings** variable is set to a non-zero value, Chart Drawings added by an Advanced Custom Study for the chart will be drawn above other User Drawn drawings.

When this is set to **0**, the Chart Drawings added by an Advanced Custom Study for the chart are drawn in the same way with respect to other Chart Drawing priorities.

### sc.DrawBaseGraphOverStudies

[Link](#scdrawbasegraphoverstudies) - [Top](#top)

**Type**: Read/Write **Integer** variable.

The **sc.DrawBaseGraphOverStudies** variable is the same as the **Chart >> Chart Settings >> Display Main Chart Graph on Top of Studies** setting. When it is set to a nonzero value, then the main chart graph will be displayed on top of other studies on the chart. Otherwise, the studies will be on top of the main chart graph.

#### Example

```cpp

sc.DrawBaseGraphOverStudies = 1;
            
```

### sc.DrawStudyUnderneathMainPriceGraph

[Link](#scdrawstudyunderneathmainpricegraph) - [Top](#top)

**Type**: Read/Write integer variable.

When the **sc.DrawStudyUnderneathMainPriceGraph** variable is set to 1 (TRUE) the study will be displayed underneath the main price graph in the chart. Assuming **sc.GraphRegion** is set to 0. Otherwise, this variable is not relevant. When **sc.DrawStudyUnderneathMainPriceGraph** is set to 0 (FALSE), then the study is displayed above the main price graph in the chart.

#### Example

```cpp

sc.DrawStudyUnderneathMainPriceGraph = 1;
            
```

### sc.EarliestUpdateSubgraphDataArrayIndex

[Link](#scearliestupdatesubgraphdataarrayindex) - [Top](#top)

**Type**: Read/Write Integer Variable

**sc.EarliestUpdateSubgraphDataArrayIndex** is an index variable which can optionally be set to the earliest **sc.Subgraph[].Data[]** array index being modified during a study update in your study function.

There is no need to set this variable if a study does not make changes to a **sc.Subgraph[].Data[]** array at an index earlier than [sc.UpdateStartIndex](#scupdatestartindex) for manual looping, or the earliest [sc.Index](#scindex) set for a study during an update when using automatic looping.

**sc.EarliestUpdateSubgraphDataArrayIndex** is referenced by the **Study/Price Overlay** study, the **Color Bar Based on Alert Condition** study, the **Spreadsheet Studies**, and other studies which depend on other studies so that they are aware of the earliest index that changes have occurred at in a source study in order for them to properly process that data.

This variable should not be set when [sc.IsFullRecalculation](#scisfullrecalculation) is TRUE/1.

### sc.EndTime1

[Link](#scendtime1) - [Top](#top)

**Type**: Read/Write Integer Variable

**sc.EndTime1** is the first end time for a day on the chart.

This is equal to the [Session Times >> End Time](SessionTimes.md#starttime) setting for the chart.

This variable is a SCDateTime [TimeValue](SCDateTime.md#timevalue) in seconds.

Also refer to [sc.StartTime1](#scstarttime1).

### sc.EndTime2

[Link](#scendtime2) - [Top](#top)

**Type**: Read/Write Integer Variable

**sc.EndTime2** is the second end time for a day on the chart. This is only used if **[sc.UseSecondStartEndTimes](#scusesecondstartendtimes)** is set to 1 (TRUE).

This is equal to the [Session Times >> Evening End Time](SessionTimes.md#starttime) setting for the chart.

This variable is a SCDateTime [TimeValue](SCDateTime.md#timevalue) in seconds.

Also refer to [sc.StartTime2](#scstarttime2).

### sc.FileRecordIndexOfLastDataRecordInChart

[Link](#scfilerecordindexoflastdatarecordinchart) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.FileRecordIndexOfLastDataRecordInChart** variable is the index of the last Intraday data record read from the Intraday data file or the file cache, used in the chart.

This is not necessarily the very last data record in the file. For example, if a replay is in progress, it can be earlier than the last record in the file or file cache.

In newer versions of Sierra Chart, due to file caching, this variable could refer to an index which has not yet been written to the Intraday data file.

### sc.FilterChartVolumeGreaterThanEqualTo

[Link](#scfilterchartvolumegreaterthanequalto) - [Top](#top)

**Type**: Read/Write float variable.

**sc.FilterChartVolumeGreaterThanEqualTo** is for setting and getting the Volume Filter value which excludes volume greater than or equal to the specified value.

This is the same **Volume Filter >=** value set through **Chart >> Chart Settings**.

### sc.FilterChartVolumeLessThanEqualTo

[Link](#scfilterchartvolumelessthanequalto) - [Top](#top)

**Type**: Read/Write float variable.

**sc.FilterChartVolumeLessThanEqualTo** is for setting and getting the Volume Filter value which excludes volume less than or equal to the specified value.

This is the same **Volume Filter <=** set through **Chart >> Chart Settings**.

### sc.FilterChartVolumeTradeCompletely

[Link](#scfilterchartvolumetradecompletely) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.FilterChartVolumeTradeCompletely** variable corresponds to the [Filter Trade Completely](ChartSettings.md#filtertradecompletely) Chart Setting.

It is set to 1/TRUE when the setting is enabled. Otherwise, it is 0.

This variable can be changed by the study function and goes into effect after the study function returns.

### sc.FlagFullRecalculate

[Link](#scflagfullrecalculate) - [Top](#top)

Write only integer variable.

The **sc.FlagFullRecalculate** variable can be set to 1 or a nonzero value to cause a full recalculation of all studies on the chart to occur after returning from the study function.

A full recalculation means in the case of automatic looping that the study function will be called for each bar in the chart starting at **sc.Index** 0. In the case of manual looping, the study function will be called and sc.UpdateStartIndex will be set to 0.

It is not recommended to use this because it is highly inefficient. Generally the reason this is used is due to programming problems within the study function itself and this is not an appropriate solution in those cases.

### sc.FlagToReloadChartData

[Link](#scflagtoreloadchartdata) - [Top](#top)

Write only integer variable.

The **sc.FlagToReloadChartData** variable can be set to 1 or a nonzero value to cause a reload of the chart data from the data file after the study function returns. The reload does not happen immediately.

This reload is the same as selecting **Chart >> Reload and Recalculate**  on the menu.

### sc.FreeDLL

[Link](#scfreedll) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0 (FALSE)

**sc.FreeDLL** is no longer required as of version 1836 and higher. As of that version, setting this has no effect.

### sc.GlobalDisplayStudySubgraphsNameAndValue

[Link](#scglobaldisplaystudysubgraphsnameandvalue) - [Top](#top)

**Type**: Read/Write integer variable.

sc.GlobalDisplayStudySubgraphsNameAndValue is equivalent to the **Display Study Name, Subgraph Names and Subgraph Values - Global** setting on the Study Settings window for the study. This can be set to either 1 to enable that option or to 0 to disable it.

#### Example

```cpp

sc.GlobalDisplayStudySubgraphsNameAndValue = 1;
            
```

### sc.GlobalTradeSimulationIsOn

[Link](#scglobaltradesimulationison) - [Top](#top)

**Type**: Read-only integer variable.

**sc.GlobalTradeSimulationIsOn** is set to 1, when **Trade >> Trade Simulation Mode On** is enabled. Otherwise, it is set to zero.

#### Example

```cpp

int TradeSimulationIsOn = sc.GlobalTradeSimulationIsOn;
            
```

### sc.GraphDrawType

[Link](#scgraphdrawtype) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: GDT\_CUSTOM

**sc.GraphDrawType** can be set to one of the values in the list below.

When you use **GDT\_CUSTOM**, which is the default, then the study will be able to use the [sc.Subgraph[].DrawStyle](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphDrawStyle) member to set the [Draw Style](ChartStudies.md#drawstyle) for each Subgraph.

When you use a setting other than GDT\_CUSTOM, then the Graph Draw Type will be a type of price bar which uses the data in the [sc.Subgraph[0 through 4].Data](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData) arrays. Use the: **[sc.Subgraph[SC\_OPEN][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** array for Open values, **[sc.Subgraph[SC\_HIGH][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** array for High values, **[sc.Subgraph[SC\_LOW][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** array for Low values, and the **[sc.Subgraph[SC\_LAST][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** array for Close or Last values.

In the case of **GDT\_CANDLE\_VOLUME\_BAR**, use the **sc.Subgraph[SC\_VOLUME].Data[]** array to control the width of the candlestick.

If you set this to a value other than **GDT\_CUSTOM** and you also set the **[sc.DisplayAsMainPriceGraph](#scdisplayasmainpricegraph)** variable to 1 (TRUE), you should calculate the average values and fill in the sc.Subgraph[SC\_VOLUME][] and sc.Subgraph[SC\_NUM\_TRADES][] arrays. To calculate the averages, make a call to [sc.CalculateOHLCAverages()](ACSIL_Members_Functions.md#sccalculateohlcaverages) near the end of the study function.

When you use a **sc.GraphDrawType** setting value other than  **GDT\_CUSTOM**, then the sc.Subgraph[].DrawStyle variable is automatically set for each of the relevant sc.Subgraphs needed by the sc.GraphDrawType. You cannot change them.

Additionally, it is not possible when you are drawing a price bar type of graph (sc.GraphDrawType not equal to GDT\_CUSTOM), to also use standard study lines or other Draw Styles using sc.Subgraph[4] and higher which are not used by the price bar graph draw types. In this case you will need to use a separate study.

**Colors when using sc.GraphDrawType != GDT\_CUSTOM**: When using a **sc.GraphDrawType** that is not equal to GDT\_CUSTOM, the **PrimaryColor** and **SecondaryColor** members of **sc.Subgraph** set the color of the bars. For more information, refer to [Color Settings for Graph Draw Types](GraphDrawTypesColorSettings.md). If you wish to color certain bars a certain type of color when using a price bar graph draw type, then you can use the [sc.Subgraph[0-4].DataColor[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphDataColor) arrays.

Supported Values:

* GDT\_CUSTOM
* GDT\_OHLCBAR
* GDT\_CANDLESTICK
* GDT\_CANDLESTICK\_BODY\_ONLY
* GDT\_LINEONCLOSE
* GDT\_MOUNTAIN
* GDT\_HLCBAR
* GDT\_LINEONOPEN
* GDT\_LINEONHLAVG
* GDT\_STAIRSTEPONCLOSE
* GDT\_HLBAR
* GDT\_KAGI
* GDT\_POINT\_AND\_FIGURE\_BARS
* GDT\_POINT\_AND\_FIGURE\_XO
* GDT\_BID\_ASK\_BAR
* GDT\_PRICE\_VOLUME
* GDT\_CANDLE\_PRICE\_VOLUME\_BAR
* GDT\_BLANK
* GDT\_NUMBERS\_BARS
* GDT\_NUMERIC\_INFORMATION (For complete documentation, refer to [Numeric Information Table Graph Draw Type](ACSIL_Members_scSubgraph.md#numericinformationtablegraphdrawtype)
* GDT\_RENKO\_BRICK
* GDT\_RENKO\_BRICK\_WITH\_WICKS
* GDT\_CANDLESTICK\_HOLLOW
* GDT\_MARKET\_DEPTH
* GDT\_VOLUME\_LEVEL\_TRADES
* GDT\_CANDLE\_PRICE\_VOLUME\_BAR\_HOLLOW

In the case of when using **GDT\_POINT\_AND\_FIGURE\_XO**, if the Box Size is greater than the chart **Tick Size**, then it is necessary to set [sc.PointAndFigureXOGraphDrawTypeBoxSize](#scpointandfigurexographdrawtypeboxsize) to the Box Size.

To set the Graph Draw Type for the main price graph, it is necessary to use [sc.BaseGraphGraphDrawType](#scbasegraphgraphdrawtype) instead.

#### Example

```cpp

sc.GraphDrawType = GDT_OHLCBAR;
            
```

### sc.GraphName

[Link](#scgraphname) - [Top](#top)

**Type**: Read/Write SCString variable.

**sc.GraphName** is the name of your study. This must be set when **[sc.SetDefaults](#scsetdefaults)** is 1 (TRUE).

#### Example

```cpp

sc.GraphName = "My Study";
            
```

### sc.GraphRegion

[Link](#scgraphregion) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 1 or the next unused Chart Region.

**sc.GraphRegion** is the *zero-based* index of the Chart Region for the study graph to be displayed in. A value of 0 means Chart Region 1, which is where the main price graph is drawn. A value of 1 means Chart Region 2, which is directly under the main price graph.

Currently there are 8 Chart Regions available. Therefore, the maximum value can be 7.

It is not possible for a single study to draw in a Chart Region outside of what is specified with **sc.GraphRegion**. A separate study is required for each Chart Region.

If you want to force a particular Chart Region to be used and not allow it to be automatically selected by Sierra Chart when adding a new study instance to the chart, when you have set **sc.GraphRegion** to 1, then set **sc.GraphRegion** below the **sc.SetDefaults** code block in the study function, to the particular Graph Region you want to display the study in.

#### Example

```cpp

sc.GraphRegion = 0; // Use the main price graph region
            
```

### sc.GraphShortName

[Link](#scgraphshortname) - [Top](#top)

**Type**: Read/write SCString variable.

**sc.GraphShortName** is a text string that is set to the **Short Name** for the instance of the study function applied to the chart.

#### Example

```cpp

SCString ShortName = sc.GraphShortName;
            
```

### sc.GraphUsesChartColors

[Link](#scgraphuseschartcolors) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.GraphUsesChartColors** variable only applies when the **sc.GraphDrawType** is set to one of the price bar types like **GDT\_OHLCBAR** .

When **sc.GraphUsesChartColors** is set to TRUE (1), this means that the colors of the drawn price bars will be set according to the colors specified for the chart itself and not the study **sc.Subgraph[]** colors. These chart colors can either be the global color settings, or the chart specific color settings.

When **sc.GraphUsesChartColors** is set to FALSE (0), this means that the colors of the drawn price bars will be set according to the colors specified by the study **sc.Subgraph[]** colors.

For additional details, refer to [Color Settings for Graph Draw Types](GraphDrawTypesColorSettings.md).

#### Example

```cpp
 
sc.GraphUsesChartColors  = TRUE;
            
```

### sc.HideDLLAndFunctionNames

[Link](#schidedllandfunctionnames) - [Top](#top)

**Type**: Read/Write integer variable.

When **sc.HideDLLAndFunctionNames** is set to 1/TRUE, then the DLL file name and study function name is not displayed on the [Study Settings](ChartStudies.md#technicalstudysettingswindow) window. Otherwise, there is a text field which displays these names.

### sc.HideStudy

[Link](#schidestudy) - [Top](#top)

**Type**: Read/Write integer variable.

**Initial Value**: 0.

**sc.HideStudy** can be set to 1 (TRUE) to prevent the study from being displayed on the chart. Or set it to 0 (FALSE), to display the study.

#### Example

```cpp

sc.HideStudy = 1;
            
```

### sc.HistoricalHighPullbackVolumeAtPriceForBars

[Link](#schistoricalhighpullbackvolumeatpriceforbars) - [Top](#top)

**Type**: Read-only custom data array object of type **c\_VAPContainer**.

The **sc.HistoricalHighPullbackVolumeAtPriceForBars** is like the [sc.VolumeAtPriceForBars](#scvolumeatpriceforbars) array. The data that it contains is the Volume at Price data for each bar in the chart, since the last price pullback from the bar High.

The data in this array will only be maintained when you have enabled **Historical Pullback Data** in **Chart >> Chart Settings**. For complete details, refer to the [Historical Pullback Data](ChartSettings.md#historicalpullbackdata) section in the Chart Settings documentation.

### sc.HistoricalLowPullbackVolumeAtPriceForBars

[Link](#schistoricallowpullbackvolumeatpriceforbars) - [Top](#top)

**Type**: Read-only custom data array object of type **c\_VAPContainer**.

The **sc.HistoricalHighPullbackVolumeAtPriceForBars** is like the [sc.VolumeAtPriceForBars](#scvolumeatpriceforbars) array. The data that it contains is the Volume at Price data for each bar in the chart, since the last price pullback from the bar Low.

The data in this array will only be maintained when you have enabled **Historical Pullback Data** in **Chart >> Chart Settings**. For complete details, refer to the [Historical Pullback Data](ChartSettings.md#historicalpullbackdata) section in the Chart Settings documentation.

### sc.HistoricalPriceMultiplier

[Link](#schistoricalpricemultiplier) - [Top](#top)

**Type**: Read-only float variable.

The **sc.HistoricalPriceMultiplier** variable contains the value of the [Historical Price Multiplier](ChartSettings.md#historicalpricemultiplier) Chart Setting for the chart.

### sc.HTTPBinaryResponse

[Link](#schttpbinaryresponse) - [Top](#top)

**Type**: Read-only character array (SCConstCharArray)

The **sc.HTTPBinaryResponse** character string array contains the resulting response from a  request.

### sc.HTTPRequestID

[Link](#schttprequestid) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.HTTPRequestID** variable is set to the request identifier for a completed [HTTP request](#).

### sc.IncludeInSpreadsheet

[Link](#scincludeinspreadsheet) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.IncludeInSpreadsheet** variable controls the  [Include In Spreadsheet](ChartStudies.md#studysettingsincludeinspreadsheet) Study Setting for the study.

Setting this variable to 1 means the option is enabled. Setting this variable to 0 means the option is disabled.

### sc.IncludeInStudySummary

[Link](#scincludeinstudysummary) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.IncludeInStudySummary** variable controls the  [Include In Study Summary](ChartStudies.md#studysettingsincludeinstudysummary) Study Setting for the study.

Setting this variable to 1 means the option is enabled. Setting this variable to 0 means the option is disabled.

### sc.CurrentIndex / sc.Index

[Link](#scindex) - [Top](#top)

**Type**: Read-only integer variable.

**sc.CurrentIndex** and **sc.Index** are the same. They are two different variables that are set to the same index value always. You can use either one. Normally the documentation will refer to **sc.Index**.

**sc.Index** is used with automatic looping and is equal to the elements in the **[sc.BaseDataIn[][]](#scBaseDataIn)** arrays that need to be processed and/or the elements in the **[sc.Subgraph[].Data[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** arrays that need to be filled in.

If you are creating a custom chart by setting **[sc.IsCustomChart](#sciscustomchart)** to 1 (TRUE), this is very unlikely, then **sc.Index** only refers to the elements in the **[sc.BaseDataIn[][]](#scBaseDataIn)** arrays to process, assuming your custom chart function uses the **[sc.BaseDataIn[][]](#scBaseDataIn)** arrays.

For complete information, refer to [Automatic Looping/Iterating](ACS_ArraysAndLooping.md#automaticloopingiterating).

The range of **sc.Index** is from 0 through and including **sc.ArraySize** -1.

During chart updating when a new bar is added to the chart, sc.Index will always start the *prior* value of **sc.ArraySize** -1 and not the current value.

### sc.IndexOfFirstVisibleBar

[Link](#scindexoffirstvisiblebar) - [Top](#top)

**Type**: Read-only integer variable.

**sc.IndexOfFirstVisibleBar** is the index into the **sc.BaseData[][]** arrays for the first visible bar that is drawn on the chart. When the chart is first loaded, this index will be 0.

If the study function relies on this member and it needs to be aware of changes such as when the user scrolls the chart, then you will need to set [sc.UpdateAlways](#scupdatealways) to 1 (TRUE).

In the case where the study is replacing the main price graph because the study function has set **sc.DisplayAsMainPriceGraph** = 1 or it has set **sc.IsCustomChart** = 1, then as explained previously, this will be set to the index into the **sc.BaseData[][]** arrays, and not to the index into the resulting output array.

#### Example

```cpp

// Get the Close value of the first bar that is drawn
float Value = sc.BaseData[SC_LAST][sc.IndexOfFirstVisibleBar];
            
```

### sc.IndexOfLastVisibleBar

[Link](#scindexoflastvisiblebar) - [Top](#top)

**Type**: Read-only integer variable.

**sc.IndexOfLastVisibleBar** is the index into the **sc.BaseData[][]** arrays for the last visible bar that is drawn on the chart. When the chart is first loaded, this index will be 0. This value is different than **sc.ArraySize**.

If the study function relies on this member and it needs to be aware of changes such as when the user scrolls the chart, then you will need to set [sc.UpdateAlways](#scupdatealways) to 1 (TRUE).

In the case where the study is replacing the main price graph because it has set **sc.DisplayAsMainPriceGraph** = 1 or it has set **sc.IsCustomChart** = 1, then as explained previously, this will be set to the index into the **sc.BaseData[][]** arrays, and not to the index into the resulting output array.

#### Example

```cpp

// Get the Close value of the last bar that is drawn
float Value = sc.BaseData[SC_LAST][sc.IndexOfLastVisibleBar];
            
```

### sc.IntradayDataStorageTimeUnit

[Link](#scintradaydatastoragetimeunit) - [Top](#top)

**Type**: Read-only integer variable.

**sc.IntradayDataStorageTimeUnit** is the Intraday Data Storage Time Unit setting in **Global Settings >> Data/Trade Service Settings**. For more information, refer to  [Data/Trade Service Settings](DataSourceSettings.md).

A value of 0 equals *1 Tick* . A value greater than 0 is the number of Seconds in the Intraday Data Storage Time Unit.

#### Example

```cpp

int IDSTU = sc.IntradayDataStorageTimeUnit;
            
```

### sc.IntradayChartRecordingState

[Link](#scintradaychartrecordingstate) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.IntradayChartRecordingState** variable indicates the current state related to the writing of data to the Intraday data file for the symbol of the chart the study instance is applied to. This is useful to prevent certain processing from occurring in the study function based on this state.

It can be one of the following values:

* IDFRS\_NOT\_RECORDING\_DATA
* IDFRS\_HISTORICAL\_DATA\_DOWNLOAD\_PENDING
* IDFRS\_DOWNLOADING\_HISTORICAL\_DATA
* IDFRS\_RECEIVING\_REALTIME\_DATA
* IDFRS\_FINISHED\_RECEIVING\_DATA

### sc.IsAutoTradingEnabled

[Link](#scisautotradingenabled) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.IsAutoTradingEnabled** variable indicates the state of the  **Trade >> Auto trading Enabled - Global** menu command. A value of 1 means the option is enabled. A value of 0 means it is disabled.

#### Example

```cpp

if(sc.IsAutoTradingEnabled)
{
}
            
```

### sc.IsAutoTradingOptionEnabledForChart

[Link](#scisautotradingoptionenabledforchart) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.IsAutoTradingOptionEnabledForChart** variable indicates the state of the  **Trade >> Auto Trading Enabled - Chart** menu command. A value of 1 means the option is enabled. A value of 0 means it is disabled.

### sc.IsChartbookBeingSaved

[Link](#scischartbookbeingsaved) - [Top](#top)

**Type**: Read Only integer variable.

The **sc.IsChartbookBeingSaved** variable is set to **1** just before the chart that contains the study that uses this variable, is being saved in the Chartbook. Otherwise, the variable is set to **0**.

The study functions are called when a Chartbook is being saved in order for a study to take some action during that time. This would be for more specialized purposes. It is not typically used.

The study which is checking this variable needs to set [sc.UpdateAlways = 1](ACSIL_Members_Variables_And_Arrays.md#scupdatealways) in the [sc.SetDefaults](ACSIL_Members_Variables_And_Arrays.md#scsetdefaults) code block, for it to be called periodically in order for it to know when the Chartbook saving is complete by checking for **sc.IsChartbookBeingSaved** == 0.

### sc.IsChartTradeModeOn

[Link](#scischarttrademodeon) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.IsChartTradeModeOn** variable is set to **1** if the [Trade >> Chart Trade Mode On](TradeMenu.md#charttrademodeon) is active. Otherwise it is set to **0**.

### sc.IsCustomChart

[Link](#sciscustomchart) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0 (FALSE)

Set **sc.IsCustomChart** to 1 (TRUE) in the **sc.SetDefaults** code block to make to make the study work as a *custom chart*.

A custom chart is used when you need to create a bar chart or some other style chart that is of a different size, either or smaller or greater, than the underlying data it is based on. In other words, either smaller or greater than the existing price bars in the chart.

When the study functions as a custom chart, the study needs to control the size of its **sc.Subgraph[].Data** arrays by using the **[sc.ResizeArrays()](ACSIL_Members_Functions.md#scresizearrays)** and **[sc.AddElements()](ACSIL_Members_Functions.md#scaddelements)** functions. The study will also need to set the Date-Times of each chart bar in the **[sc.DateTimeOut[]](#scDateTimeOut)** array.

For a complete example, refer to the **scsf\_CopyOfBaseGraph()** function in the **/ACS\_Source/CustomChart.cpp** file in the Sierra Chart installation folder.

You may want to use a custom chart to create your own specialized Range bar chart or Point and Figure chart.

The **/ACS\_Source/CustomChart.cpp** file in the folder where Sierra Chart is installed to, provides an example of a simple custom chart. The **scsf\_PointAndFigureChart** function in the **/ACS\_Source/studies8.cpp** file provides a more advanced example.

#### Example

```cpp

sc.IsCustomChart = 1; // Set this study as a custom chart

sc.GraphRegion = 0; // Custom charts need to be set to use chart region 0
            
```

### sc.IsFullRecalculation

[Link](#scisfullrecalculation) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.IsFullRecalculation** variable will be set to 1 (TRUE) when the chart is performing a full recalculation of the studies.

For more information about a full recalculation, refer to the  [When the Study Function is Called](ACS_ArraysAndLooping.md#whenthestudyfunctioniscalled) section.

This flag is useful to not perform certain processing in the study function when there is a full recalculation for efficiency or to perform certain initializations in the study function when there is a full recalculation.

However, when performing certain initializations in the study function when there is a full recalculation when using [Automatic Looping](ACS_ArraysAndLooping.md#automaticloopingiterating), also check that **sc.Index**  equals 0 so that the initialization is not performed at every chart bar during the full recalculation. *This is essential*.

Due to how it is determined that there is a full recalculation of the study function, a chart with a single chart bar will always set **sc.IsFullRecalculation** to 1 when the study function is called.

#### Example

```cpp

int& Variable1 = sc.GetPersistentInt(1);
if(sc.IsFullRecalculation)
{
    if (sc.Index == 0)//This line is needed for automatic looping
        Variable1 = 0;
}
            
```

### sc.IsKeyPressed\_Alt

[Link](#sciskeypressedalt) - [Top](#top)

**Type**: Read-only Integer variable.

The **sc.IsKeyPressed\_Alt** variable is used to know when the Alt key has been pressed. The variable is set to 1 when the Alt key is depressed, otherwise it is set to 0.

For this variable to be set, it is necessary to set [sc.SupportKeyboardModifierStates](#scsupportkeyboardmodifierstates) to a value of 1, otherwise the state of this keyboard modifier cannot be checked.

Whether a chart is active or not, it will still have this variable set if the key is pressed. To see if a chart is active, use [sc.ChartWindowIsActive](#scchartwindowisactive).

### sc.IsKeyPressed\_Control

[Link](#sciskeypressedcontrol) - [Top](#top)

**Type**: Read-only Integer variable.

The **sc.IsKeyPressed\_Control** variable is used to know when the Control key has been pressed. The variable is set to 1 when the Control key is depressed, otherwise it is set to 0.

For this variable to be set, it is necessary to set [sc.SupportKeyboardModifierStates](#scsupportkeyboardmodifierstates) to a value of 1, otherwise the state of this keyboard modifier cannot be checked.

Whether a chart is active or not, it will still have this variable set if the key is pressed. To see if a chart is active, use [sc.ChartWindowIsActive](#scchartwindowisactive).

### sc.IsKeyPressed\_Shift

[Link](#sciskeypressedshift) - [Top](#top)

**Type**: Read-only Integer variable.

The **sc.IsKeyPressed\_Shift** variable is used to know when the Shift key has been pressed. The variable is set to 1 when the Shift key is depressed, otherwise it is set to 0.

For this variable to be set, it is necessary to set [sc.SupportKeyboardModifierStates](#scsupportkeyboardmodifierstates) to a value of 1, otherwise the state of this keyboard modifier cannot be checked.

Whether a chart is active or not, it will still have this variable set if the key is pressed. To see if a chart is active, use [sc.ChartWindowIsActive](#scchartwindowisactive).

### sc.IsUserAllowedForSCDLLName

[Link](#scisuserallowedforscdllname) - [Top](#top)

**Type**: Read-only integer variable.

**sc.IsUserAllowedForSCDLLName** is used to authorize access to a study. For more information refer to [Redistributing and Allowing Use Only by a Defined List of Users](AdvancedCustomStudyInterfaceAndLanguage.md#redistributing).

It is also possible to specify a Service-Level for an authorized user for a particular **SCDLLName**  in the **Custom DLL Studies Management**  control panel accessed through your account on the Sierra Chart website. To access this service level programmatically, refer to [sc.DLLNameUserServiceLevel](#scdllnameuserservicelevel).

### sc.KeyboardKeyEventCode

[Link](#sckeyboardkeyeventcode) - [Top](#top)

**Type**: Read integer variable.

The **sc.KeyboardKeyEventCode** variable is set to the standard Windows virtual key code when there is a keyboard keypress event and the study has requested these events by setting [sc.ReceiveKeyboardKeyEvents](#screceivekeyboardkeyevents).

Also refer to [sc.SupportKeyboardModifierStates](#scsupportkeyboardmodifierstates) and [sc.CharacterEventCode](#sccharactereventcode).

### sc.LastCallToFunction

[Link](#sclastcalltofunction) - [Top](#top)

**Type**: Read-only integer variable.

**sc.LastCallToFunction** is set to 1 (TRUE) when an Advanced Custom Study instance is in the process of being removed from the chart or the chart is being closed.

This variable is useful if you want to do something before the study is removed from the chart or when the chart is being closed.

#### Example

```cpp

if (sc.LastCallToFunction)
{

    // This study is being removed from the chart or the chart is being closed
    // Insert cleanup code here
}
            
```

### sc.LastFullCalculationTimeInMicroseconds

[Link](#sclastfullcalculationtimeinmicroseconds) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.LastFullCalculationTimeInMicroseconds** variable indicates the calculation time in microseconds of the last time the study was [fully recalculated](ACS_ArraysAndLooping.md#whenthestudyfunctioniscalled).

This variable does not indicate the time of an update calculation.

An example of a full recalculation is when study settings are modified through **Analysis >> Studies**. When the **OK** or **Apply** buttons are pressed, all studies will be fully recalculated.

### sc.LastSize

[Link](#sclastsize) - [Top](#top)

**Type**: Read-only integer variable.

**sc.LastSize** is the volume of the last trade. This member will only be set when Sierra Chart is connected to the data feed and receiving current market data for the symbol of the chart, or during a chart replay.

This value for the chart is displayed in the **Window >> Current Quote Window**.

#### Example

```cpp

int LastTradeSize = sc.LastSize;
            
```

### sc.LastTradePrice

[Link](#sclasttradeprice) - [Top](#top)

**Type**: Read-only float variable.

**sc.LastTradePrice** is the last trade price for the symbol of the chart the study is applied to.

This is the same value as  **LastPrice**  in **Window >> Current Quote Window**.

**sc.LastTradePrice** usually will be equal to **sc.BaseData[SC\_LAST][sc.ArraySize -1]**  except when the Session Times in Chart Settings are excluding the data from the current time. In this last case, it will be set to the actual last trade price.

This member will only be set when Sierra Chart is connected to the data feed and a nonzero last trade price in the current quote data is being provided by the data feed.

This member will be set during a chart replay.

### sc.LatestDateTimeForLastBar

[Link](#sclatestdatetimeforlastbar) - [Top](#top)

**Type:** Read Only [SCDateTime](SCDateTime.md) variable.

The **sc.LatestDateTimeForLastBar** variable is set to the Date-Time, as a SCDateTime value, of the very latest trade from the data feed that is included in the last bar in the chart. The data feed has a resolution down to the second. Or, it will be set to the starting Date-Time of the very latest chart data file record which has been read into the chart, whichever is greater.

The Date-Time of the latest data file record read into the chart, is affected by the **Intraday Data Storage Time Unit** . If this is set to greater than 1 second, then the Date-Time of that data file record may not be set to the most recent second received in that record.

During a replay, **sc.LatestDateTimeForLastBar** will always be set to the Date-Time of the latest data file record read into the chart.

**sc.LatestDateTimeForLastBar** is adjusted to the Sierra Chart Time Zone setting.

#### Example

```cpp

SCDateTime DateTime = sc.LatestDateTimeForLastBar;
            
```

### sc.LoadChartDataByDateRange

[Link](#scloadchartdatabydaterange) - [Top](#top)

**Type**: Read/Write integer variable.

When **sc.LoadChartDataByDateRange** is set to a nonzero value, then the [sc.ChartDataStartDate](#scchartdatastartdate) and [sc.ChartDataEndDate](#scchartdataenddate) variables specify the date range to load into the chart.

This variable corresponds to **Chart >> Chart Settings**  **>> Use Date Range**.

### sc.MaintainAdditionalChartDataArrays

[Link](#scmaintainadditionalchartdataarrays) - [Top](#top)

**Type**: Read/Write integer variable.

**sc.MaintainAdditionalChartDataArrays** needs to be set to 1 (TRUE) to flag that the chart needs to maintain the following **sc.BaseGraph[]** arrays. This should be set in the **sc.SetDefaults** code block at the beginning of the function. These are the constants for these arrays:

* SC\_UPVOL
* SC\_DOWNVOL
* SC\_BIDNT
* SC\_ASKNT
* SC\_ASKBID\_DIFF\_HIGH
* SC\_ASKBID\_DIFF\_LOW
* SC\_ASKBID\_NUM\_TRADES\_DIFF\_HIGH
* SC\_ASKBID\_NUM\_TRADES\_DIFF\_LOW

When **sc.MaintainAdditionalChartDataArrays** is set to 0 (FALSE), these arrays are not maintained by the chart.

**sc.MaintainAdditionalChartDataArrays** also causes the **sc.BaseDataEndDateTime[]**  array to be filled in and maintained.

#### Example

*No example provided by SierraChart*

### sc.MaintainHistoricalMarketDepthData

[Link](#scmaintainhistoricalmarketdepthdata) - [Top](#top)

**Type**: Read/Write integer variable.

When this variable is set to TRUE/1, then historical market depth data will be loaded into the chart the study instance is applied to. The chart will need to be reloaded once after this has been set if the historical market depth data is not already loaded in the chart. Real-time market depth data will also be stored when this variable is TRUE.

It is necessary to set this to TRUE/1 when using [c\_ACSILDepthBars](c_ACSILDepthBars.md) in the study function.

The default for this variable is FALSE/0.

### sc.MaintainReferenceToOtherChartsForPersistentVariables

[Link](#scmaintainreferencetootherchartsforpersistentvariables) - [Top](#top)

**Type**: 16-bit Integer variable.

The default for **sc.MaintainReferenceToOtherChartsForPersistentVariables** is 1. This means that when using the [sc.GetPersistent\*FromChartStudy](ACSIL_Members_Functions.md#scgetpersistentintfromchartstudy) functions, when there is any update to the chart being referenced, then the chart that had a study that called the **sc.GetPersistent\*FromChartStudy**  function will be calculated so that the studies are aware of changes in the source chart. All of the studies will be calculated in this case.

When **sc.MaintainReferenceToOtherChartsForPersistentVariables** is set to 0, the above does not happen.

### sc.MaintainTradeStatisticsAndTradesData

[Link](#scmaintaintradestatisticsandtradesdata) - [Top](#top)

**Type**: Read/Write integer variable.

If your study function uses the ACSIL Trading functions, uses the **s\_SCPositionData** structure, or uses the [sc.GetTradeStatisticsForSymbol()](ACSIL_Members_Functions.md#scgettradestatisticsforsymbol) function or other Trading related functions which rely on order fill data, then **sc.MaintainTradeStatisticsAndTradesData** needs to be set to 1/true in the study function in order to maintain the necessary data for this functionality to all work properly.

#### Example

```cpp

if(sc.SetDefaults)
{
    sc.MaintainTradeStatisticsAndTradesData = 1;
}
            
```

### sc.MaintainVolumeAtPriceData

[Link](#scmaintainvolumeatpricedata) - [Top](#top)

**Type**: Read/Write integer variable.

Set **sc.MaintainVolumeAtPriceData** to 1 (TRUE), to have Sierra Chart maintain detailed volume at price data for the loaded bars in the chart your custom study is applied to.

#### Example

```cpp

if (sc.SetDefaults)
{
    sc.MaintainVolumeAtPriceData = 1;
}
            
```

### sc.NewBarAtSessionStart

[Link](#scnewbaratsessionstart) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.NewBarAtSessionStart** variable indicates the state of the **Chart >> Chart Settings** **>> Session Times >> New Bar at Session Start** setting. The variable will be 1 if this option is enabled or 0 if it is disabled.

#### Example

```cpp

if (sc.NewBarAtSessionStart)
{
 //Do something when true
}
            
```

### sc.NumberOfArrays

[Link](#scnumberofarrays) - [Top](#top)

**Type**: Read-only integer variable.

Initial value: 1

**sc.NumberOfArrays** is the number of [sc.Subgraph[].Data[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData) arrays that are allocated for the study to use. In other words this is the number of **sc.Subgraph[]** objects which have an allocated Data array starting at index 0. There are not going to be any skipped Subgraphs which would have an unallocated array. They will all be allocated up to the specified number starting 0.

**sc.NumberOfArrays** gets set automatically as the study function uses the [sc.Subgraph[].Data[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData) arrays.

For example, if **sc.Subgraph[3].Data[]** is accessed, then **sc.NumberOfArrays** becomes set to 4. Although this value does not update until after the study function returns.

### sc.NumberOfForwardColumns

[Link](#scnumberofforwardcolumns) - [Top](#top)

**Type**: Read Only Integer variable.

The **sc.NumberOfForwardColumns** is set to the same value as the  [Number of Forward Columns](ChartSettings.md#numberofforwardcolumns) setting in the **Chart >> Chart Settings** for the chart the study is applied to.

### sc.TicksPerBar / sc.NumberOfTradesPerBar

[Link](#scnumberoftradesperbar) - [Top](#top)

**Type**: Read/Write integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.NumFillSpaceBars

[Link](#scnumfillspacebars) - [Top](#top)

**Type**: Read/Write integer variable.

**sc.NumFillSpaceBars** is the number of bars in the fill space on the right side of the chart. For additional information, refer to [Right Side Fill Space](WorkingWithCharts.md#fillspace).

#### Example

```cpp

// Make sure there are at least 10 bars of fill space
if (sc.NumFillSpaceBars < 10)

    sc.NumFillSpaceBars = 10;
            
```

### sc.OutArraySize

[Link](#scoutarraysize) - [Top](#top)

**Type**: Read-only integer variable.

**sc.OutArraySize** is the number of array elements (equivalent to chart bars) that are in the output arrays for the chart the study is applied to.

This includes the **[sc.Subgraph[].Data[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** arrays, the **[sc.Subgraph[].DataColor[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphDataColor)** arrays if used, and the **[sc.DateTimeOut[]](#scDateTimeOut)** array.

Normally **sc.OutArraySize** is the same as **[sc.ArraySize](#scarraysize)**. However, in the case when **[sc.IsCustomChart](#sciscustomchart)** is used, the output arrays can have a different number of elements than the **sc.BaseData[][]** arrays.

**sc.OutArraySize** is updated when you use the **[sc.ResizeArrays()](ACSIL_Members_Functions.md#scresizearrays)** and **[sc.AddElements()](ACSIL_Members_Functions.md#scaddelements)** functions.

#### Example

```cpp

// Resize the output arrays to be half the current size of the output arrays
sc.ResizeArrays(sc.OutArraySize / 2);
            
```

### sc.p\_VolumeLevelAtPriceForBars

[Link](#scpvolumelevelatpriceforbars) - [Top](#top)

**Type**: Read-only custom data array object pointer of type **c\_VAPContainer**.

When using the [Large Volume Trade Indicator](StudiesReference.md) study, this causes volume data for trades with a volume over a particular volume threshold to be maintained for the price levels of those trades.

This data is contained within the **sc.p\_VolumeLevelAtPriceForBars** member.

It is essential that the [Large Volume Trade Indicator](StudiesReference.md) be added to the chart for the **sc.p\_VolumeLevelAtPriceForBars** object to contain data.

sc.VolumeAtPriceForBars is a pointer to a c\_VAPContainer. To access a function member of c\_VAPContainer requires that you use the member of pointer operator **->**. Refer to [Member access operators](http://devdocs.io/cpp/language/operator_member_access).

A c\_VAPContainer container contains many member functions to access the data within. These functions are documented in the [sc.VolumeAtPriceForBars](#scvolumeatpriceforbars) section on this page.

Also refer to the /ACS\_Source/VAPContainer.h header file for all of the available functions.

### sc.PersistVars

[Link](#scpersistvars) - [Top](#top)

**sc.PersistVars**  is no longer supported. It is necessary to use the [GetPersistent\*](ACSIL_Members_Functions.md#scgetpersistentint) functions instead.

Existing compiled code will continue to work which uses the old sc.PersistVars structure, but it will not recompile. It will need to be updated to use the new functions.

### sc.PlaceACSChartShortcutMenuItemsAtTopOfMenu

[Link](#scplaceacschartshortcutmenuitemsattopofmenu) - [Top](#top)

Refer to the [sc.PlaceACSChartShortcutMenuItemsAtTopOfMenu](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scplaceacschartshortcutmenuitemsattopofmenu) page for information on this variable, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.PointAndFigureBoxSizeInTicks

[Link](#scpointandfigureboxsizeinticks) - [Top](#top)

**Type**: Read Only Integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.PointAndFigureReversalSizeNumBoxes

[Link](#scpointandfigurereversalsizenumboxes) - [Top](#top)

**Type**: Read Only Integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.PointAndFigureXOGraphDrawTypeBoxSize

[Link](#scpointandfigurexographdrawtypeboxsize) - [Top](#top)

**Type**: Read/Write Float variable.

In the case of when [sc.GraphDrawType](#scgraphdrawtype) is set to **GDT\_POINT\_AND\_FIGURE\_XO**, **sc.PointAndFigureXOGraphDrawTypeBoxSize** sets the Box Size for the X and O boxes.

### sc.PointerHorzWindowCoord

[Link](#scpointerhorzwindowcoord) - [Top](#top)

**Type**: Read Only integer variable.

The **sc.PointerHorzWindowCoord** is the X coordinate of the pointer in the chart window coordinates.

The chart window coordinate system uses the upper left hand corner to define the (0,0) point and increases to the right and down.

### sc.PointerVertWindowCoord

[Link](#scpointervertwindowcoord) - [Top](#top)

**Type**: Read Only integer variable.

The **sc.PointerVertWindowCoord** is the Y coordinate of the pointer in the chart window coordinates.

The chart window coordinate system uses the upper left hand corner to define the (0,0) point and increases to the right and down.

### sc.PreserveFillSpace

[Link](#scpreservefillspace) - [Top](#top)

**Type**: Read/Write integer variable.

This is the same as the **Lock Fill Space** command on the **Chart** menu.

Set **sc.PreserveFillSpace** to 1 (TRUE) to prevent the fill space from being filled in as new bars are added to the chart or when the chart is being scrolled. Set it to 0 (FALSE) to allow the fill space to be filled in.

### sc.PreviousClose

[Link](#scpreviousclose) - [Top](#top)

**Type**: Read-only float variable.

The **sc.PreviousClose** variable contains the current Settlement Price obtained from the Current Quote data. For more information, refer to [Current Quote Window](WindowMenu.md#currentquotewindow).

### sc.PriceChangesPerBar

[Link](#scpricechangesperbar) - [Top](#top)

**Type**: Read/Write integer variable

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.PriorSelectedCustomStudyControlBarButtonNumber

[Link](#scpriorselectedcustomstudycontrolbarbuttonnumber) - [Top](#top)

**Type**: Read-only integer variable

**sc.PriorSelectedCustomStudyControlBarButtonNumber** contains the number of the previously selected Custom Study Control Bar Button.

### sc.ProcessIdentifier

[Link](#scprocessidentifier) - [Top](#top)

**Type**: Read-only integer variable.

**sc.ProcessIdentifier** is the ID of Sierra Chart process. This variable is for advanced programming only.

### sc.ProtectStudy

[Link](#scprotectstudy) - [Top](#top)

**Type**: Read/Write integer variable.

When **sc.ProtectStudy**  is set to 1, it will prevent the data from the Subgraph arrays from being accessed by other ACSIL studies and also prevents the study from being outputted to Spreadsheets using any of the Spreadsheet Studies.

When this is set to 0, none of the above happens and the data from the study is accessible normally.

### sc.PullbackVolumeAtPrice

[Link](#scpullbackvolumeatprice) - [Top](#top)

**Type**: Read-only custom data array object of type **c\_VAPContainer**.

The **sc.PullbackVolumeAtPrice** array has the same type of data that is contained within the [sc.VolumeAtPriceForBars](#scvolumeatpriceforbars) array. It only contains data for the last bar in the chart. It contains the volume data for each price level since the last price pullback from the last bar High or Low.

The data contained in this array is what is displayed in the Numbers Bars study in the Pullback column, and could be a high or low pullback based on the current bar state. This data is maintained when **sc.MaintainVolumeAtPriceData** is set to 1 (TRUE) in your custom study function.

When specifying the **BarIndex** parameter with the various VAP container functions, you must always use 0 for this parameter, since this array only contains data for a single bar.

### sc.RangeBarType

[Link](#scrangebartype) - [Top](#top)

**Type**: Read/Write integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.RangeBarValue

[Link](#scrangebarvalue) - [Top](#top)

**Type**: Read/Write float variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.RealTimePriceMultiplier

[Link](#screaltimepricemultiplier) - [Top](#top)

**Type**: Read/Write float variable.

The **sc.RealTimePriceMultiplier** variable contains the value of the [Real-Time Price Multiplier](ChartSettings.md#realtimepricemultiplier) for the chart.

### sc.ReceiveCharacterEvents

[Link](#screceivecharacterevents) - [Top](#top)

**Type**: Read/Write integer variable.

When the **sc.ReceiveCharacterEvents** variable is set to 1 or a nonzero value, then the custom study function will be called immediately for any character key press events from the keyboard.

The actual ASCII character code can be determined with the [sc.CharacterEventCode](#sccharactereventcode) variable.

When the custom study function is called when a character key is pressed on the keyboard, this study function call is an efficient standard update calculation where sc.Index and sc.UpdateStartIndex be equal to sc.ArraySize - 1.

The study function will know the reason it is being called by checking that sc.CharacterEventCode is nonzero. If it is nonzero, the study function only has to handle the character event and does not need to do anything else. It can still do whatever it requires, but does not have to do any calculations because at the usual time a calculation needs to be performed when the chart is updated, the study function will be called again.

The flag variable [sc.DoNotRedrawChartAfterStudyReturns](#scdonotredrawchartafterstudyreturns) can be set to specify to not redraw the chart window after a study function is called. This can be set when **sc.CharacterEventCode** is nonzero. This will make the process of handling these types of events very efficient.

### sc.ReceiveKeyboardKeyEvents

[Link](#screceivekeyboardkeyevents) - [Top](#top)

**Type**: Read/Write integer variable.

When the **sc.ReceiveKeyboardKeyEvents** variable is set to 1 or a nonzero value, then the custom study function will be called immediately for any key press events from the keyboard. This also includes the letter keys as well.

The actual key code can be determined with the [sc.KeyboardKeyEventCode](#sckeyboardkeyeventcode) variable. The actual value is a standard Windows virtual key code.

For a listing of the virtual key codes, refer to [Virtual-Key Codes](https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx).

In the case of an alphanumeric key, you can receive the actual ASCII code for the key pressed with the [sc.CharacterEventCode](#sccharactereventcode) variable.

When the custom study function is called when a key is pressed on the keyboard, this study function call is an efficient standard update calculation where sc.Index and sc.UpdateStartIndex be equal to sc.ArraySize - 1.

The study function will know the reason it is being called by checking that **sc.KeyboardKeyEventCode** or [sc.CharacterEventCode](#sccharactereventcode) is nonzero.

If either of these is nonzero, the study function only has to handle the key press event and does not need to do anything else. It can still do whatever it requires, but does not have to do any calculations because at the usual time a calculation needs to be performed when the chart is updated, the study function will be called again.

The flag variable [sc.DoNotRedrawChartAfterStudyReturns](#scdonotredrawchartafterstudyreturns) can be set to specify to not redraw the chart window after a study function is called. This can be set when **sc.KeyboardKeyEventCode**  or [sc.CharacterEventCode](#sccharactereventcode) is nonzero. This will make the process of handling these types of events very efficient.

If a single keyboard key is pressed, like an alphanumeric key, you can use either [sc.KeyboardKeyEventCode](#sckeyboardkeyeventcode) or the [sc.CharacterEventCode](#sccharactereventcode) variables to obtain that particular key value.

When detecting key combinations by using for example [sc.IsKeyPressed\_Control](#sciskeypressedcontrol), and detecting that state along with an alphanumeric key, it is best to use **sc.CharacterEventCode**.

When detecting key combinations which have already been mapped to particular commands through **Global Settings >> Customize Keyboard Shortcuts**, is not possible to detect the usage of these keyboard combinations through ACSIL.

### sc.ReceivePointerEvents

[Link](#screceivepointerevents) - [Top](#top)

**Type**: Read/Write integer variable.

**sc.ReceivePointerEvents**  can be set to  **ACS\_RECEIVE\_NO\_POINTER\_EVENTS, ACS\_RECEIVE\_POINTER\_EVENTS\_WHEN\_ACS\_BUTTON\_ENABLED, ACS\_RECEIVE\_POINTER\_EVENTS\_ALWAYS, ACS\_RECEIVE\_POINTER\_EVENTS\_ALWAYS\_FOR\_ALL\_TOOLS**  for the study function to receive mouse Pointer related events.

For complete details, refer to [Receiving Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#receivingpointerevents).

### sc.ReconnectToExternalServiceServer

[Link](#screconnecttoexternalserviceserver) - [Top](#top)

**Type**: Write integer variable.

Set the **sc.ReconnectToExternalServiceServer** variable to TRUE to perform the  **File >> Disconnect** and then the  **File >> Connect to Data Feed** commands from within your custom study. This is not performed immediately at the time you set this to TRUE. It is only done when your study function returns.

Also see [sc.DisconnectFromExternalServiceServer](#scdisconnectfromexternalserviceserver) and [sc.ConnectToExternalServiceServer](#scconnecttoexternalserviceserver).

#### Example

```cpp

sc.ReconnectToExternalServiceServer = TRUE;
            
```

### sc.RenkoNewBarWhenExceeded

[Link](#screnkonewbarwhenexceeded) - [Top](#top)

**Type**: Read/Write integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.RenkoReversalOpenOffsetInTicks

[Link](#screnkoreversalopenoffsetinticks) - [Top](#top)

**Type**: Read/Write integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.RenkoTicksPerBar

[Link](#screnkoticksperbar) - [Top](#top)

**Type**: Read/Write integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.RenkoTrendOpenOffsetInTicks

[Link](#screnkotrendopenoffsetinticks) - [Top](#top)

The **sc.RenkoTrendOpenOffsetInTicks** is the number of Ticks for the Trend Offset for Flex Renko chart bars. Each tick is equivalent to the chart **Tick Size**.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.ReplayStatus

[Link](#screplaystatus) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.ReplayStatus** variable indicates the current replay status for the chart the study is applied to. It can be one of the following constants:

* **REPLAY\_STOPPED**: The chart is not replaying.
* **REPLAY\_RUNNING**: The chart is replaying.
* **REPLAY\_PAUSED**: The chart is considered in a replaying state, however the replay is paused.

#### Example

```cpp

int ReplayStatus = sc.ReplayStatus;
            
```

### sc.ResetAlertOnNewBar

[Link](#scresetalertonnewbar) - [Top](#top)

**Type**: Read/Write integer variable.

**sc.AlertOnlyOncePerBar** can be set to 1 or 0 (TRUE/FALSE) to force an alert set with [sc.SetAlert](ACSIL_Members_Functions.md#scsetalert)() to reset when there is a new bar. This works with the [sc.SetAlert](ACSIL_Members_Functions.md#scsetalert)() function.

### sc.ResetAllScales

[Link](#scresetallscales) - [Top](#top)

**Type**: Read/Write integer variable.

When the **sc.ResetAllScales** variable is set to a value of **1**, all the graphs in the chart associated with the study that called this function will have their scales reset to their default values.

### sc.ReversalTicksPerBar

[Link](#screversalticksperbar) - [Top](#top)

**Type**: Read/Write integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.RightValuesScaleLeftCoordinate

[Link](#scrightvaluesscaleleftcoordinate) - [Top](#top)

**Type**: Read-only integer variable.

**sc.RightValuesScaleLeftCoordinate** is set to the pixel coordinate for the left of the Values Scale on the right side of the chart that the study function instance is applied to.

Also refer to [sc.RightValuesScaleRightCoordinate](#scrightvaluesscalerightcoordinate).

### sc.RightValuesScaleRightCoordinate

[Link](#scrightvaluesscalerightcoordinate) - [Top](#top)

**Type**: Read-only integer variable.

**sc.RightValuesScaleRightCoordinate** is set to the pixel coordinate for the right of the Values Scale on the right side of the chart that the study function instance is applied to.

This right coordinate is included in the right side Values Scale. It is *not* one pixel beyond the right side which would be the case if bounding coordinates were being provided.

Also refer to [sc.RightValuesScaleLeftCoordinate](#scrightvaluesscaleleftcoordinate).

### sc.RoundTurnCommission

[Link](#scroundturncommission) - [Top](#top)

**Type**: Read-only integer variable.

**sc.RoundTurnCommission** is the Round Turn Commission set for the symbol or symbol pattern in the [Global Symbol Settings](GlobalSymbolSettings.md).

If the chart the study instance is on is open at the time that you have set the **Round Turn Commission** or changed this value in the [Global Symbol Settings](GlobalSymbolSettings.md), it is necessary to go to that chart and select **Chart >> Reload and Recalculate**, to be able to access the value using **sc.RoundTurnCommission**.

### sc.SaveChartImageToFile

[Link](#scsavechartimagetofile) - [Top](#top)

Write-only integer variable.

Set  **sc.SaveChartImageToFile**  to 1 or a nonzero number, to flag to save an image of the chart the study is applied to, to a file in the **Images**  subfolder in the folder where Sierra Chart is installed to.

This operation is performed after your study function returns and all other studies on a chart are calculated. The saving operation is performed when the chart is next updated which occurs at the **Chart Update Interval** setting in **Global Settings >> General Settings** or the chart specific setting in **Chart >> Chart Settings**.

The Filename is the Symbol of the chart plus a timestamp which includes resolution down to the millisecond.

Also refer to  [sc.SaveChartImageToFileExtended()](ACSIL_Members_Functions.md#scsavechartimagetofileextended) and [sc.UploadChartImage()](ACSIL_Members_Functions.md#scuploadchartimage).

#### Example

```cpp

sc.SaveChartImageToFile = 1;//Save the chart image to a file when the study function returns
            
```

### sc.ScaleBorderColor

[Link](#scscalebordercolor) - [Top](#top)

**Type**: Read/Write integer variable.

**sc.ScaleBorderColor**

#### Example

```cpp

unsigned int ScaleBorderColor;
            
```

### sc.ScaleConstRange

[Link](#scscaleconstrange) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0

**sc.ScaleConstRange** is the range, that is the difference between the high and the low, for the constant range scale types. This is only used when **[sc.ScaleRangeType](#scscalerangetype)** is either **SCALE\_CONSTANT\_RANGE** or **SCALE\_CONSTRANGECENTER**. If **[sc.ScaleRangeType](#scscalerangetype)** is set to one of these constant range types, **sc.ScaleConstRange** needs to be greater than 0.

#### Example

```cpp

// Set this study to use a centered constant range scale
sc.ScaleRangeType = SCALE_CONSTRANGECENTER;
// Set the range of the scale to 10 points
sc.ScaleConstRange = 10.0f;
            
```

### sc.ScaleIncrement

[Link](#scscaleincrement) - [Top](#top)

Type: Read/Write integer variable.

Initial value: 0 (auto)

**sc.ScaleIncrement** is the increment at which values in the right side vertical scale on the chart are displayed. This is the same as the **Scale Increment** setting in the **Scale Window**  that can be opened from the **Settings and Inputs** tab in the **Study Settings**  window for the study. A value of 0 means the scale increment is automatically determined by Sierra Chart.

#### Example

```cpp

sc.ScaleIncrement = 0.01f; // Draw values on the scale at every 0.01 point
            
```

### sc.ScaleRangeBottom

[Link](#scscalerangebottom) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0

**sc.ScaleRangeBottom** is the minimum value for the scale range when using a user-defined scale range (**[sc.ScaleRangeType](#scscalerangetype) = SCALE\_USERDEFINED;**). When this variable is set, it must always be less than or equal to **[sc.ScaleRangeTop](#scscalerangebottom)**.

#### Example

```cpp

sc.ScaleRangeType = SCALE_USERDEFINED;

sc.ScaleRangeTop = 100.0f;
sc.ScaleRangeBottom = -100.0f;
            
```

### sc.ScaleRangeTop

[Link](#scscalerangetop) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0

**sc.ScaleRangeTop** is the maximum value for the scale range when using a user-defined scale range (**[sc.ScaleRangeType](#scscalerangetype) = SCALE\_USERDEFINED;**). When this variable is set, it must always be greater than or equal to **[sc.ScaleRangeBottom](#scscalerangebottom)**.

#### Example

```cpp

sc.ScaleRangeType = SCALE_USERDEFINED;

sc.ScaleRangeTop = 100.0f;
sc.ScaleRangeBottom = -100.0f;
            
```

### sc.ScaleRangeType

[Link](#scscalerangetype) - [Top](#top)

**Type**: Read/Write integer variable.

Type: Initial value: **SCALE\_AUTO**

The **sc.ScaleRangeType** member allows you to get and set the vertical Scale Range Type for the study. It can be any of the following constant values:

* SCALE\_AUTO
* SCALE\_USERDEFINED
* SCALE\_INDEPENDENT
* SCALE\_SAMEASREGION
* SCALE\_CONSTANT\_RANGE
* SCALE\_CONSTRANGECENTER
* SCALE\_ZEROBASED R

#### Example

```cpp

sc.ScaleRangeType = SCALE_INDEPENDENT; // Set this study to use an independent scale
            
```

### sc.ScaleType

[Link](#scscaletype) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: **SCALE\_LINEAR**

**sc.ScaleType** is the type of value scaling that is used on the study. This can be set to either **SCALE\_LINEAR** for a basic linear scale, or **SCALE\_LOGARITHMIC** for a logarithmic scale.

#### Example

```cpp

sc.ScaleType = SCALE_LOGARITHMIC; // Set this study to use a logarithmic scale
            
```

### sc.ScaleValueOffset

[Link](#scscalevalueoffset) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0

sc.ScaleValueOffset is a percentage value with a range from -1 to 1 for the offset of the scale from the center. A value of 1 means the graph will be pushed all the way off the bottom, and a value of -1 means the graph will be pushed all the way off the top. This is the value that gets changed when you use the Interactive Scale Move feature when you left click and drag the scale on the right side of the chart.

#### Example

```cpp

sc.ScaleValueOffset = 0.25f
            
```

### sc.SCDataFeedSymbol

[Link](#scscdatafeedsymbol) - [Top](#top)

**Type**: Function returning [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings).

This member has been changed to a function effective with version 2152.

The **sc.SCDataFeedSymbol** function returns a text string which contains the symbol pattern used by the [Real-Time Exchange Data Feeds Available from Sierra Chart](RealTimeDataFeedsAvailableFromSierraChart.md) which corresponds to the symbol of the chart the study is on.

This symbol pattern has specialized uses and is not typically used.

### sc.ScrollToDateTime

[Link](#scscrolltodatetime) - [Top](#top)

**Type**: Write-only SCDateTime variable.

**Initial Value**: 0.

**sc.ScrollToDateTime** is a [SCDateTime](SCDateTime.md) variable that can be set to a specific Date and Time to scroll the chart to.

As soon as the study function returns, the chart will scroll to the specified Date and Time and then the variable is cleared for next use, if required.

### sc.SecondsPerBar

[Link](#scsecondsperbar) - [Top](#top)

**Type**: Read/Write integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.SelectedAlertSound

[Link](#scselectedalertsound) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.SelectedAlertSound** function returns the value of the [Alert Sound / Number](ChartSettings.md#alertnumber) setting on the **Alerts** tab of the [Study Settings](ChartStudies.md#technicalstudysettingswindow) window.

#### Example

```cpp

int AlertSoundNumber = sc.SelectedAlertSound;
            
```

### sc.SelectedTradeAccount

[Link](#scselectedtradeaccount) - [Top](#top)

**Type**: SCString. Read/Write Text string variable.

The **sc.SelectedTradeAccount** is set to the same Trade Account which is selected and displayed on the Trade Window of the chart the study is applied to. For more information, refer to [Selecting Trade Account](TradeWindow.md#selectingtradeaccount).

This can also be set to a different Trade Account to change the Trade Account for the chart. The change goes into effect when the study function returns.

However, this must be set to a valid Trade Account which is also valid based upon whether Trade Simulation Mode is enabled or not. Otherwise, the new Trade Account will be ignored.

### sc.ServerConnectionState

[Link](#scserverconnectionstate) - [Top](#top)

**Type**: Read-only integer variable.

**sc.ServerConnectionState** is an Integer variable which can be one of the constants listed below. It indicates the connection state to the Data and Trade (in the case of a Trading service) servers.

The connection and disconnection to the servers is performed through **File >> Connect to Data Feed** and **File >> Disconnect**.

* SCS\_DISCONNECTED
* SCS\_CONNECTING
* SCS\_RECONNECTING
* SCS\_CONNECTED
* SCS\_CONNECTION\_LOST
* SCS\_DISCONNECTING

When the connection state is disconnected and then the connection becomes connected, the study function will be called. When the connection state is connected and then it is no longer connected, the study function will be called. At either of these times the study function can check the state of the **sc.ServerConnectionState** variable.

### sc.ServiceCodeForSelectedDataTradingService

[Link](#scservicecodeforselecteddatatradingservice) - [Top](#top)

**Type**: Function returning [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings).

This member has been changed to a function effective with version 2152.

The **sc.ServiceCodeForSelectedDataTradingService** function returns a text string which contains the internal Sierra Chart service code for the currently selected Data/Trade service set in **Global Settings >> Data/Trade Service Settings**.

### sc.SetDefaults

[Link](#scsetdefaults) - [Top](#top)

**Type**: Read-only integer variable.

**sc.SetDefaults** is a TRUE (1) or FALSE (0) value that gets set to 1 (TRUE) when a study instance is manually added to a chart through **Analysis >> Studies >> Add >>**, a study instance is added to a chart through a Study Collection which has just been applied to a chart, or when a Chartbook is opened and the study instance is contained on a chart in the Chartbook.

If the study is on more than one chart in the Chartbook or there are multiple instances of it, then the study function will be called once for each instance of it, with **sc.SetDefaults**  set to 1.

This variable is also TRUE (1) and your study function is called when the  **Analysis >> Studies >> Add Custom Study**  window is opened by a user. This is so that the Names and Descriptions of your studies can be listed for selection.

*All study functions must include a code block at the top of the function that checks this member before doing any further processing within the study function.* Refer to the example below. If this value is 1 (TRUE), then *the study function must *return* at the end of the  **sc.SetDefaults** code block.*

The purpose of **sc.SetDefaults** is to allow the study function to configure itself and set defaults.

The **sc.SetDefaults** code block for setting your configuration and defaults is not meant to be used for anything other than configuring the study and *setting the defaults* of the study.

If you [modify the source code](AdvancedCustomStudyInterfaceAndLanguage.md#modifyingadvancedcustomstudycode) for a study and rebuild the DLL when an instance of the study is on a chart and the chart is open, and you do not remove the study from the chart and add it again, then all of the default settings like Input and Subgraphs settings in the **sc.SetDefaults** code block will not change back to defaults. They will remain as they were previously were.

#### What Should Be Located in the sc.SetDefaults Code Block

[Link](#whatshouldbelocatedinscsetdefaultscodeblock) - [Top](#top)

1. **sc** interface structure members that configure the study and should only be set once. An example would be **sc.AutoLoop = 1**. It would not make sense to set a variable like this outside of **sc.SetDefaults** because in some cases it is too late to set them if used outside the **sc.SetDefaults** code block and it would be inefficient to keep setting them.
2. Setting of defaults. For example, you will want to set properties of a **sc.Subgraph[]** like the **sc.Subgraph[].DrawStyle** and the colors. You will want to set default study Input values with the  **sc.Input[].Set\*** functions. Setting of defaults must be done in the **sc.SetDefaults** code block because otherwise when the settings are changed through the **Study Settings** window for the study, those changes will get reverted back to what the study function is setting them to if the code to change the sc.Subgraph, sc.Input and other settings is done outside of the **sc.SetDefaults** code block.
3. **sc** members that need to be set only once. For example, you will want to set **sc.GraphName** , **sc.Subgraph[].Name** and  **sc.Input[].Name** in the **sc.SetDefaults** code block because usually these names will not change during chart updating.
4. Unless otherwise noted in the documentation for the particular ACSIL interface structure member (those that begin with **sc.**), any member used in the **sc.SetDefaults** code block can also be read, set or used outside of sc.SetDefaults block. For example, **[sc.GraphName](#scgraphname)** can be changed later on by also setting it outside of the **sc.SetDefaults** code block.
5. There are some ACSIL members like **sc.BaseData[][]**, where it would not make sense to interact with them within the **sc.SetDefaults** code block because the arrays will be empty.
6. If an  **sc**  member is associated with the chart, it must *not be set* in the **sc.SetDefaults** code block because it will have no effect. For example, you cannot set [sc.StartTime1](#scstarttime1) inside of **sc.SetDefaults**. However, it is possible to read **sc.StartTime1** from within the **sc.SetDefaults** code block. All ACSIL members which are related to the chart itself, like **sc.StartTime1**, are set and valid when **sc.SetDefaults** is TRUE. However, they are *read-only*.
7. When using [ACSIL Functions](ACSIL_Members_Functions.md) within the **sc.SetDefaults** code block and those functions interact with the chart, they will have *no effect*. They will return and do nothing.

#### Example

```cpp

SCSFExport scsf_UniqueFunctionName(SCStudyInterfaceRef sc)
{

    if (sc.SetDefaults)
    {
        // Set the defaults
        sc.GraphName = "My New Study Function";

        sc.Subgraph[0].Name = "Subgraph name";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;

        sc.AutoLoop = 1;

        // You can also enter additional configuration code
        return;
    }

    // Perform your data processing here.

    //This is an example that multiplies the last price by 10.
    sc.Subgraph[0][sc.Index] = sc.BaseData[SC_LAST][sc.Index] * 10;

    return;
}
            
```

### sc.StandardChartHeader

[Link](#scstandardchartheader) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0 (FALSE)

If **sc.StandardChartHeader** is set to 1 (TRUE), then your study will use the standard main Price Graph text header. This text header can be configured by going to **Global Settings >> Customize Chart Header** on the menu. If you set this to 1 (TRUE), you must also set **[sc.DisplayAsMainPriceGraph](#scdisplayasmainpricegraph)** to 1 (TRUE), otherwise it will be ignored.

#### Example

```cpp

sc.DisplayAsMainPriceGraph = 1; // Set the study to the main Price Graph

sc.StandardChartHeader = 1;
            
```

### sc.StartTime1

[Link](#scstarttime1) - [Top](#top)

Read/write integer variable.

**sc.StartTime1** is the first start time for a day on the chart.

This is equal to the [Session Times >> Start Time](SessionTimes.md#starttime) setting for the chart.

This variable is a SCDateTime [TimeValue](SCDateTime.md#timevalue) in seconds.

Also refer to [sc.EndTime1](#scendtime1).

### sc.StartTime2

[Link](#scstarttime2) - [Top](#top)

Read/write integer variable.

**sc.StartTime2** is the second start time for a day on the chart. This is only used if **[sc.UseSecondStartEndTimes](#scusesecondstartendtimes)** is set to 1 (TRUE).

This is equal to the [Session Times >> Evening Start Time](SessionTimes.md#starttime) setting for the chart.

This variable is a SCDateTime [TimeValue](SCDateTime.md#timevalue) in seconds.

Also refer to [sc.EndTime2](#scendtime2).

### sc.StartTimeOfDay

[Link](#scstarttimeofday) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.StartTimeOfDay** variable is set to the starting time of the trading day based on the [Session Times](SessionTimes.md) settings for the chart the study instance is on.

The value returned is a [Time Value](SCDateTime.md#timevalue).

It can be converted to a [SCDateTime](SCDateTime.md) type by using the SCDateTime::SetTime() function. Refer to the example below.

#### Example

```cpp

SCDateTime StartTime;
StartTime.SetTime(sc.StartTimeOfDay);
            
```

### sc.StorageBlock

[Link](#scstorageblock) - [Top](#top)

**Type**: Read/Write block of bytes.

**sc.StorageBlock** is a pointer to a block of 4096 bytes of permanent memory storage. This block of memory can be used for your custom data storage, and it is saved to the Chartbook which is stored as a file on your computer, when the [Chartbook](Chartbooks.md) containing the study is saved.

This storage block is unique to each individual study instance.

Depending upon what you are using the Storage Block for, you may want to enable **Global Settings >> General Settings >> Charts >> Chartbooks >> Autosave Chartbooks Interval in Minutes** to automatically save your Chartbook periodically.

#### Example

```cpp

// This is the structure of our data that is to be
// stored in the storage block
struct s_PermData
{
    int Number;
    char Text[32];
};

// Here we make a pointer to the storage block as if
// it was a pointer to our structure
s_PermData* PermData;
PermData = (s_PermData*)sc.StorageBlock;

// Here we set data using the members of our structure
// This uses the memory of the storage block
PermData->Number = 10;
strcpy(PermData->Text, "Sample Text");
            
```

### sc.StudyDescription

[Link](#scstudydescription) - [Top](#top)

**Type**: Read/Write string variable.

**sc.StudyDescription** is a text string that can be set to a description of the study. This is optional.

If you use this, it needs to be in the [sc.SetDefaults](#scsetdefaults) code block. This study description will be displayed on a webpage when using the **Show Study Description** or **Description** buttons in the Chart Studies and Study Settings windows respectively.

Once **sc.StudyDescription** is set in the [sc.SetDefaults](#scsetdefaults) code block. It cannot later be accessed in the ACSIL function. The string will then be blank.

#### Example

```cpp

sc.StudyDescription = "Here is a description for this study. This description will be shown in the Add Custom Study window when this study is selected.";
            
```

### sc.StudyGraphInstanceID

[Link](#scstudygraphinstanceid) - [Top](#top)

**Type**: Read-only **Integer** variable.

The StudyGraphInstanceID is a unique number assigned to each study on a chart. This identifier number is for the particular instance of your custom study which is applied to the chart. This ID number can be seen in the **Chart Studies** window on the right side of the study name in the **Studies to Graph** list.

This is the same study identifier which is used with functions like **sc.GetStudyArrayUsingID**.

The underlying main price graph in the chart will always have a StudyGraphInstanceID itself of 0. If there is another study which is acting as the main price graph, then it will have a value higher than 0.

#### Example

```cpp

int StudyGraphInstanceID = sc.StudyGraphInstanceID;
            
```

### sc.StudyRegionBottomCoordinate

[Link](#scstudyregionbottomcoordinate) - [Top](#top)

Type: Read-only integer variable.

**sc.StudyRegionBottomCoordinate** is the Y-coordinate of the bottom of the Chart Region that the study is in. This value is given in the coordinate system of the client window and is in pixels.

This variable will only provide a valid value when read outside of the **sc.SetDefaults**  code block.

### sc.StudyRegionLeftCoordinate

[Link](#studyregionleftcoordinate) - [Top](#top)

**Type**: Read Only integer variable.

**sc.StudyRegionLeftCoordinate** is the X-coordinate of the left side of the Chart Region that the study is in. This value is given in the coordinate system of the client window and is in pixels.

This variable will only provide a valid value when read outside of the **sc.SetDefaults** code block.

### sc.StudyRegionRightCoordinate

[Link](#scstudyregionrightcoordinate) - [Top](#top)

**Type**: Read Only integer variable.

**sc.StudyRegionRightCoordinate** is the X-coordinate of the right side of the Chart Region that the study is in. This value is given in the coordinate system of the client window and is in pixels.

This variable will only provide a valid value when read outside of the **sc.SetDefaults** code block.

### sc.StudyRegionTopCoordinate

[Link](#scstudyregiontopcoordinate) - [Top](#top)

**Type**: Read-only integer variable.

**sc.StudyRegionTopCoordinate** is the Y-coordinate of the top of the Chart Region that the study is in. This value is given in the coordinate system of the client window and is in pixels.

This variable will only provide a valid value when read outside of the **sc.SetDefaults** code block.

### sc.StudyVersion

[Link](#scstudyversion) - [Top](#top)

Type: Unsigned integer variable.

**sc.StudyVersion** can be set to any integer value which is then displayed on the [Settings and Inputs](ChartStudies.md#settingsandinputstab) tab of the **Study Settings** window for the study. It is prefixed with the text **Study Version:**.

This simply provides version information to the user and serves no other purpose.

### SC\_SUBGRAPHS\_AVAILABLE

[Link](#scsubgraphsavailable) - [Top](#top)

Type: Constant integer variable.

**SC\_SUBGRAPHS\_AVAILABLE** is the number of study Subgraphs there is available for a custom study. For additional information, refer to [sc.Subgraphs](ACSIL_Members_scSubgraph.md).

### sc.SupportAttachedOrdersForTrading

[Link](#scsupportattachedordersfortrading) - [Top](#top)

Type: integer variable.

When **sc.SupportAttachedOrdersForTrading** is set to TRUE(1), then the [Attached Orders](AttachedOrders.md) set on the Trade Window for the chart the trading study is applied to will be used no matter what the **Use Attached Orders**  setting is set to on the Trade Window.

However, this setting is irrelevant when Targets or Stops are set on the [s\_SCNewOrder](ACSILTrading.md#sscneworder) data structure. In this case it is implied to be on for those Attached Orders.

### sc.SupportKeyboardModifierStates

[Link](#scsupportkeyboardmodifierstates) - [Top](#top)

**Type**: Read/Write Integer variable.

The **sc.SupportKeyboardModifierStates** variable is used to allow the [sc.IsKeyPressed\_Control](#sciskeypressedcontrol), [sc.IsKeyPressed\_Shift](#sciskeypressedshift), [sc.IsKeyPressed\_Alt](#sciskeypressedalt) variables to be set to indicate the state of these keyboard modifiers.

Set this variable to 1 to allow support, or set to 0 to not allow support. If this is set to 0, then it is not possible for ACSIL function to determine the state of these keyboard modifiers. The default is 0.

### sc.SupportTradingScaleIn

[Link](#scsupporttradingscalein) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.SupportTradingScaleIn** variable is set to 1 when the Scaling In option for trading is enabled for the chart. 0 means it is disabled. This variable can also be set by the study function to enable [Scaling In](AttachedOrders.md#scalingin).

This variable must be set outside of and below the **sc.SetDefaults** code block in the study function. Otherwise, it will have no effect.

**sc.SupportTradingScaleIn** is ignored when submitting an order for a different Symbol or Trade Account than the chart is currently set to.

#### Example

```cpp

sc.SupportTradingScaleIn = 1;
            
```

### sc.SupportTradingScaleOut

[Link](#scsupporttradingscaleout) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.SupportTradingScaleOut** variable is set to 1 when the Scaling Out option for trading is enabled for the chart. 0 means it is disabled. This variable can also be set by the study function to enable [Scaling Out](AttachedOrders.md#scalingout).

This variable must be set outside of and below the **sc.SetDefaults** code block in the study function. Otherwise, it will have no effect.

**sc.SupportTradingScaleOut** is ignored when submitting an order for a different Symbol or Trade Account than the chart is currently set to.

#### Example

```cpp

sc.SupportTradingScaleOut = 1;
            
```

### sc.Symbol

[Link](#scsymbol) - [Top](#top)

**Type**: Read-only SCString variable.

**sc.Symbol** is the symbol of the chart.

To perform comparisons to this symbol, or to directly access it see [How To Compare Strings](ACSILProgrammingConcepts.md#howtocomparestrings) and [Directly Accessing a SCString](ACSILProgrammingConcepts.md#directlyaccessingscstring), respectively.

To change the symbol of the chart use [sc.DataFile](#scdatafile).

### sc.SymbolData

[Link](#scsymboldata) - [Top](#top)

**Type**: Read Only data structure.

**sc.SymbolData** is a pointer to a data structure containing all of the current pricing and related data for the symbol of the chart.

The symbol data structure does not include the market depth data. For market depth data, use the [sc.GetBidMarketDepthEntryAtLevel](ACSIL_Members_Functions.md#scgetbidmarketdepthentryatlevel) and [sc.GetBidMarketDepthEntryAtLevel](ACSIL_Members_Functions.md#scgetbidmarketdepthentryatlevel) functions.

The data in this structure is only valid when Sierra Chart is connected to the data feed and the symbol is receiving data from the data feed or the chart is replaying.

Refer to the **ACS\_Source/SCSymbolData.h** file in the folder that Sierra Chart is installed to, for the structure definition.

### sc.TextInput

[Link](#sctextinput) - [Top](#top)

**Type**: Read/Write SCString variable.

Initial value: "" (empty string)

**sc.TextInput** is the text input string that is made available in the study's inputs. The text input can be found at the bottom of the list of inputs shown on the Inputs and Settings tab in the Technical Study Settings window. This string can not be longer than 255 characters.

You must have the **[sc.TextInputName](#sctextinputname)** set if you want to have the text input available to the user.

**sc.TextInput** is considered out of date. It is recommended to use [sc.Input[].SetString()](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputSetString) and [sc.Input[].GetString()](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputGetString) instead.

#### Example

```cpp

// Make a copy of the text input into our own c-style string. Be very careful
// when using this and make sure you will not use an invalid index into the
// string array. If this string is not used properly, the study could crash.
char TextInputCopy[256];

strncpy(TextInputCopy, sc.TextInput.GetChars(), sizeof(TextInputCopy) - 1);
            
```

### sc.TextInputName

[Link](#sctextinputname) - [Top](#top)

**Type**: Read/Write SCString variable.

Initial value: "" (empty string)

**sc.TextInputName** is a string of the name that is shown in the table of inputs on the Inputs and Settings tab in the Technical Study Settings window. You must set this to make the text input available to the user.

#### Example

```cpp

sc.TextInputName = "Letters"; // Show the text input with the name Letters
            
```

### sc.TickSize

[Link](#scticksize) - [Top](#top)

**Type**: Read/Write float variable.

**sc.TickSize** is a variable that is set to the Tick Size of the chart the study instance is applied to.

This is the same as the [Tick Size](ChartSettings.md#ticksize) setting set in the **Chart >> Chart Settings** window.

This variable can be modified by the custom study. When it is modified, to cause the chart to reload which is necessary, the study must set [sc.FlagToReloadChartData](#scflagtoreloadchartdata) = 1.

### sc.TimeScaleAdjustment

[Link](#sctimescaleadjustment) - [Top](#top)

**Type**: Read-only SCDateTime variable.

**sc.TimeScaleAdjustment** is the difference between the global [Time Zone](#) setting in Sierra Chart and GMT/UTC time. Or if there is a separate Time Zone setting on the chart, then it is the difference between the Time Zone setting for the chart and GMT/UTC time.

This value uses the Daylight Savings Time adjustment based upon whether it is currently in effect or not.

This variable is a [SCDateTime](SCDateTime.md) variable. You can add this variable to or subtract this variable from any **[SCDateTime](SCDateTime.md)** variable.

This variable is only useful for when working with Date-Times for the latest day in the chart. For prior days, use the [sc.ConvertDateTimeFromChartTimeZone](ACSIL_Members_Functions.md#scconvertdatetimefromcharttimezone) function.

#### Example

```cpp

// Figure out the Date-Time of the last bar without the time offset applied.
// The Date-Time values of sc.BaseDateTimeIn[] are already adjusted to the Sierra Chart Time Zone setting.
// Subtracting sc.TimeScaleAdjustment will remove the adjustment.
SCDateTime AdjustedDateTime = sc.BaseDateTimeIn[sc.ArraySize - 1] - sc.TimeScaleAdjustment;
            
```

#### Example

```cpp

// Adjust a time and sales record date-time
// TimeSales is a s_TimeAndSales record requested with sc.GetTimeAndSales().
SCDateTime TempDateTime = TimeSales[TSIndex].DateTime;
TempDateTime += sc.TimeScaleAdjustment;  // Apply the time zone offset for the chart
            
```

### sc.TradeAndCurrentQuoteSymbol

[Link](#sctradeandcurrentquotesymbol) - [Top](#top)

**Type**: Read/Write SCString variable.

**sc.TradeAndCurrentQuoteSymbol** is a text string containing the **Trade and Current Quote Symbol** set in **Chart >> Chart Settings**.

This symbol can be changed and one purpose for this is to change it to a Trade and Current Quote Symbol which corresponds with the sc.Symbol text string.

When this is changed, it does not go into effect until after the study function returns. At that time, the [Trades List](TradeActivityLog.md#charttradestatstab) in the chart is rebuilt if necessary.

This symbol is what is used when trading from a chart. All trading related functionality uses this Trade and Current Quote symbol. Although after changing this symbol it is not possible during the same call into the the study function to then submit a trading order which will then use this symbol because the symbol has not yet gone into effect. To avoid this limitation, either wait to submit the trading order until the next call into the study function or it is necessary to use the functionality to submit an order for a different Symbol and/or Trade Account. Refer to [Submitting and Managing Orders for Different Symbol and/or Trade Account](ACSILTrading.md#submittingordersdifferentsymbolaccount).

### sc.TradeServiceAccountBalance

[Link](#sctradeserviceaccountbalance) - [Top](#top)

**Type**: Read-only double precision float variable.

This variable is no longer supported since version 2395 and higher. Instead use the [sc.GetTradeAccountData](ACSIL_Members_Functions.md#scgettradeaccountdata) function.

### sc.TradeServiceAvailableFundsForNewPositions

[Link](#sctradeserviceavailablefundsfornewpositions) - [Top](#top)

**Type**: Read-only double precision float variable.

This variable is no longer supported since version 2395 and higher. Instead use the [sc.GetTradeAccountData](ACSIL_Members_Functions.md#scgettradeaccountdata) function.

### sc.TradeWindowConfigFileName

[Link](#sctradewindowconfigfilename) - [Top](#top)

**Type**: Read/Write SCString variable.

The **sc.TradeWindowConfigFileName** string variable can be set to the file name, not including the folder path, to a previously saved Trade Window configuration file that the custom study on the chart wants to configure the Trade Window to.

For further details about Trade Window Configurations, refer to [Using and Changing Between Different Trade Window and Attached Orders Configurations](TradeWindow.md#tradewindowconfigurations).

**sc.TradeWindowConfigFileName** is set to the current Trade Window configuration file name.

For further information about using this variable, refer to [SupportAttachedOrdersForTrading](AutoTradeManagment.md#supportattachedordersfortrading).

One useful purpose of this is to create a custom study which uses Control Bar buttons and/or Keyboard Shortcuts to change to your own custom Trade Window configuration. For additional information, refer to [Advanced Custom Study Interaction With Menus, Control Bars, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md).

#### Example

```cpp

 // This line can be within the sc.SetDefaults code block or below it.
 sc.TradeWindowConfigFileName = "SimpleBracket.twconfig";
            
```

### sc.TradeWindowOrderQuantity

[Link](#sctradewindoworderquantity) - [Top](#top)

**Type**: Read/Write integer (32-bit version) / double (64-bit version) variable.

**sc.TradeWindowOrderQuantity** is set to the order quantity on the Trade Window for the chart that the study instance is applied to.

#### Example

```cpp

int OrderQuantity = sc.TradeWindowOrderQuantity;
            
```

### sc.TradingIsLocked

[Link](#sctradingislocked) - [Top](#top)

**Type**: Read-only integer variable.

The **sc.TradingIsLocked** variable is set to 1 when **Trade >> Trading Locked** is enabled. Otherwise, it is set to 0.

To change the state of trading locked, use the [sc.SetTradingLockState](ACSIL_Members_Functions.md#scsettradinglockstate) function.

### sc.TransparencyLevel

[Link](#sctransparencylevel) - [Top](#top)

**Type**: Read/Write integer variable.

This variable is no longer available in newer versions of Sierra Chart. Instead use the [sc.SetChartStudyTransparencyLevel](ACSIL_Members_Functions.md#scsetchartstudytransparencylevel) function.

### sc.UpdateAlways

[Link](#scupdatealways) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 0 (FALSE)

When the **sc.UpdateAlways** variable is set to 1 (TRUE), the study instance will update continuously rather than only when new market or order data is available for the symbol.

This means your study function will be called continuously at the update interval.

The update interval is set through **Global Settings >> General Settings >> Chart Update Interval**.

It is possible to set an individual chart to update at a different interval than the global **Chart Update Interval**. To do this, set a nonzero number for **Chart >> Chart Settings >> Display >> Chart Update Interval in Milliseconds**.

One use of this setting is to simulate real time updating during testing. This setting does not affect other studies on the same chart.

To maintain efficiency, the study function will not be called more often than every 200 ms when setting this variable to TRUE and new data is not available. Otherwise, setting this variable to 1 (TRUE) could significantly increase CPU usage if the Chart Update Interval is set very low. Effective with version 1340, the preceding does not apply if the chart has set its own Chart Update Interval.

The setting **Chart >> Chart Settings >> Performance >> Minimum Chart Update Interval In Milliseconds For ACSIL UpdateAlways**, limits how often the study is called when it is only called for the reason when sc.UpdateAlways is true. There may be too much processing to be calculating the studies at every Chart Update Interval. This setting sets the minimum interval that has to elapse, before calling the custom study function again as compared to previously. This setting is new as of version 2575.

The [Chart Update Interval](ChartSettings.md#chartupdateinterval) still drives the update interval for the chart. If the **Chart Update Interval** is lower than **Minimum Chart Update Interval In Milliseconds For ACSIL UpdateAlways**, then **Minimum Chart Update Interval In Milliseconds For ACSIL UpdateAlways** is the minimum update interval when the studies are only being calculated for the purpose of **sc.UpdateAlways** and no other reason. The studies can be calculated more often according to the Chart Update Interval depending upon if there is another event that can trigger a chart update. For example, new market data received.

#### Example

```cpp

sc.UpdateAlways = 1; // Set this study to continuously update
            
```

### sc.UpdateStartIndex

[Link](#scupdatestartindex) - [Top](#top)

**Type**: Read-only integer variable.

**sc.UpdateStartIndex** is only used with Manual Looping. For complete information on Manual Looping, refer to [Working with ACSIL Arrays and Understanding Looping](ACS_ArraysAndLooping.md#manuallooping).

The array indexing variables **sc.Index, sc.CurrentIndex** and **sc.UpdateStartIndex** are all set to the same value when the study function instance is called. All three of these variables can be used interchangeably. However, the behavior of **sc.Index, sc.CurrentIndex** and **sc.UpdateStartIndex** differs significantly depending whether you are using Auto Looping or Manual Looping.

**sc.UpdateStartIndex** is set by Sierra Chart to the index where the primary **for** loop in the study function will start looping from. This is the index into the **[sc.BaseDataIn[][]](#scBaseDataIn)** arrays where data updating has begun. This is the same index where updating should begin in the **[sc.Subgraph[][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** arrays.

If you are creating a custom chart, **[sc.IsCustomChart](#sciscustomchart)** is set to TRUE (this is very unlikely), then **sc.UpdateStartIndex** only refers to the index into the **[sc.BaseDataIn[][]](#scBaseDataIn)** arrays to begin processing at.

**For example:** When a chart is opened, reloaded, recalculated, or a replay is started, the study function instance will be called and **sc.UpdateStartIndex** will be 0. This means the study function needs to update all elements in the **[sc.Subgraph[].Data[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** arrays it is using.

During chart updating, if there are 100 bars in a chart and a trade occurs and either the last bar is updated or a new bar is added to the chart, then **sc.UpdateStartIndex** variable will be set to 99 indicating the value at index 99 (bar 100) has been updated.

For example: **sc.BaseDataIn[SC\_LAST][99]** (bar 100) has been updated. During normal chart updating **sc.UpdateStartIndex** will always be equal to the last index of the prior  **sc.ArraySize**  before the chart update. If a new bar was added, then there will also be a new array element at sc.BaseDataIn[][100] (bar 101). In this case, the study function needs to update the **sc.Subgraph[].Data[]** arrays at index 99 and index 100. The reason you need to use **sc.UpdateStartIndex** is to only perform calculations on the modified data and only update the study values starting from this index. This makes your study very efficient.

It is very possible that more than 1 bar will be added to a chart between updates. There could be hundreds or thousands of bars potentially added when historical data is downloaded into the chart after the initial data load from the local data file on your system. Therefore, you need to update from **sc.UpdateStartIndex** to the last array element in all the **[sc.Subgraph[][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** Data arrays you are using, and not just the element at this index.

The index value provided by **sc.UpdateStartIndex** will never go backwards. However, during a full recalculation of the study, such as when the chart is reloaded or for other reasons, it can start back at 0. Therefore, you can rely that it will not go backwards other than to 0.

It is possible that a chart containing a study instance is making references to other charts which are triggering a full recalculation in the chart which is making the reference. In this particular case, during the full recalculation **sc.UpdateStartIndex** will be set to 0 for the study instances using Manual Looping. For additional information, refer to [References to Other Charts and Tagging](ChartStudies.md#referencesotherchartstagging).

### sc.UseGlobalChartColors

[Link](#scuseglobalchartcolors) - [Top](#top)

**Type**: Read/Write integer variable.

When **sc.UseGlobalChartColors** is set to 1 or a nonzero number, then the global color settings defined in **Global Settings >> Graphics Settings** are used for the chart.

When **sc.UseGlobalChartColors** is set to 0, then the chart specific color settings defined in **Chart >> Graphics Settings** are used for the chart.

Since **sc.UseGlobalChartColors** affects the chart itself, it must be located outside and below the **sc.SetDefaults** code block.

#### Example

```cpp

sc.UseGlobalChartColors = 0;
            
```

### sc.UseGUIAttachedOrderSetting

[Link](#scuseguiattachedordersetting) - [Top](#top)

**Type**: Read/Write integer variable.

When **sc.UseGUIAttachedOrderSetting** is set to a nonzero number, then the [Attached Orders](AttachedOrders.md) defined on the Trade Window for the chart, if any, will be attached to [Buy Entry or Sell Entry](ACSILTrading.md) trade orders submitted from the study function if the **Use Attached Orders** setting is also enabled on the Trade Window.

### sc.UseHighResolutionWindowRelativeCoordinatesForChartDrawings

[Link](#scusehighresolutionwindowrelativecoordinatesforchartdrawings) - [Top](#top)

**Type**:

### sc.UserName

[Link](#scusername) - [Top](#top)

**Type**: Function returning [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings).

This member has been changed to a function effective with version 2152.

The **sc.UserName** function returns a text string which contains the Account Name that was entered at the Sierra Chart Login window, which displays when Sierra Chart starts.

### sc.UseSecondStartEndTimes

[Link](#scusesecondstartendtimes) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.UseSecondStartEndTimes** variable can be set to 1 (TRUE) or 0 (FALSE). This is equivalent to **Chart >> Chart Settings >> Use Evening Session**.

When it is set to 1, then the [sc.StartTime2](#scstarttime2) and **[sc.EndTime2](#scendtime2)** variables are used by the chart the study is on. These variables represent the Evening Session times in **Chart >> Chart Settings**.

### sc.UsesMarketDepthData

[Link](#scusesmarketdepthdata) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.UsesMarketDepthData** variable when set to 1 will cause market depth data to be subscribed to for the Symbol of the chart the custom study applied to.

Sierra Chart needs to be connected to the data feed with **File >> Connect to Data Feed** to receive market depth data.

### sc.ValueFormat

[Link](#scvalueformat) - [Top](#top)

**Type**: Read/Write integer variable.

Initial value: 2.

**sc.ValueFormat** sets the numeric display format for all values in the sc.Subgraph[].Data arrays for the study. This can be one of the following values:

* 0 = Zero decimal places. Example output: 1
* 1 = One decimal place. Example output: 0.1
* 2 = Two decimal places. Example output: 0.01
* 3 = Three decimal places. Example output: 0.001
* 4 = Four decimal places. Example output: 0.0001
* 5 = Five decimal places. Example output: 0.00001
* 6 = Six decimal places. Example output: 0.000001
* 7 = Seven decimal places. Example output: 0.0000001
* 8 = Eight decimal places. Example output: 0.00000001
* 9 = Nine decimal places. Example output: 0.000000001
* 19 = Maximum Digits
* 20 = Time value. Where the value is as a floating-point fractional value where one millisecond is 1/86400000. Example output: 12:30:00
* 21 = Date
* 21 = Date
* 22 = Date-Time
* 23 = Currency
* 24 = Percent
* 25 = Scientific Notation
* 26 = Large Integer with Suffix
* 27 = Boolean
* VALUEFORMAT\_INHERITED = Same Value Format as is set in **Chart >> Chart Settings** .
* 102 = Halves. Example output: 1/2
* 104 = Quarters. Example output: 1/4
* 108 = Eighths. Example output: 1/8
* 116 = Sixteenths. Example output: 1/16
* 132 = Thirty-seconds. Example output: 1/32
* 134 = Half Thirty-seconds. Example output: .5/32
* 136 = Quarter Thirty-seconds. Example output: .25/32
* 140 = Eighth Thirty-seconds. Example output: .125/32
* 164 = Sixty-fourths. Example output: 1/64
* 228 = One-hundred-twenty-eighths. Example output: 1/128
* 356 = Two-hundred-fifty-sixths. Example output: 1/256

#### Example

```cpp

sc.ValueFormat = 4;
            
```

### sc.ValueIncrementPerBar

[Link](#scvalueincrementperbar) - [Top](#top)

**Type**: Read-only float variable.

**sc.ValueIncrementPerBar** is the **Value Increment per Bar in Ticks (Price Unit per Bar in Ticks)** setting in **Chart >> Chart Settings >> Chart Drawings**.

For complete details, refer to [Value Increment per Bar in Ticks (Price Unit per Bar in Ticks)](ChartSettings.md#valueincrementperbarinticks) in the Chart Settings documentation.

#### Example

```cpp

float ValueIncrementPerBar = sc.ValueIncrementPerBar;
            
```

### sc.VersionNumber

[Link](#scversionnumber) - [Top](#top)

**Type**: Function returning [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings).

This member has been changed to a function effective with version 2152.

The **sc.VersionNumber** function returns a text string which contains the current version number of Sierra Chart the user is using.

Note: If your Advanced Custom Study is used on a version of Sierra Chart that does not support all of the interface members compared with the version it was built under, then a warning message will be given and the study cannot be used.

Therefore, using this version number member to perform a check to see if your study will work on a certain version, is unnecessary.

#### Example

```cpp

if (atoi(sc.VersionNumber().GetChars()) < 2100)
{

    //do something
}
            
```

### sc.VolumeAtPriceForBars

[Link](#scvolumeatpriceforbars) - [Top](#top)

**Type**: Read-only custom data array object pointer of type **c\_VAPContainer**.

Sierra Chart internally maintains volume at price data for each price tick of each loaded bar. The tick size is controlled by the **Tick Size** setting for the chart.

This data is maintained when **sc.MaintainVolumeAtPriceData** is set to 1 (TRUE) in the custom study function. Or, when there is a study on the chart which requires this data such as the **Volume by Price** study. This data is fully accessible through the ACSIL using the member **sc.VolumeAtPriceForBars**.

It is essential that **sc.MaintainVolumeAtPriceData** be set to 1 in the study function in the **sc.SetDefaults** code block to ensure that the necessary volume at price data is being maintained for the chart.

For an example on how to use **sc.VolumeAtPriceForBars**, refer to the function **scsf\_VolumeAtPriceArrayTest** in the **/ACS\_Source/studies8.cpp** file in the folder where Sierra Chart is installed to. Or refer to **scsf\_VolumeWeightedAveragePrice** in **/ACS\_Source/studies2.cpp**. Or refer to **scsf\_VolumeAtPriceThresholdAlertV2** in **/ACS\_Source/studies8.cpp**.

All of these are good examples. The basic method to access the volume by price data for a chart bar is given in the code example below.

sc.VolumeAtPriceForBars is a pointer to a c\_VAPContainer. To access a function member of c\_VAPContainer requires that you use the member of pointer operator **->**. Refer to [Member access operators](http://devdocs.io/cpp/language/operator_member_access).

It is no longer recommended to use the  **GetNextHigherVAPElement** or the **GetNextLowerVAPElement** member functions to access the data. These are less efficient than the example below.

The function parameter that is commonly used in the c\_VAPContainer is  **PriceInTicks**. To calculate what you should use for  **PriceInTicks**, divide the price by **sc.TickSize**.

#### Example

```cpp

    unsigned int TotalVolume = 0;
    
    const s_VolumeAtPriceV2 *p_VolumeAtPrice=NULL;
    
	int VAPSizeAtBarIndex = sc.VolumeAtPriceForBars->GetSizeAtBarIndex(sc.Index);
    
	for (int VAPIndex = 0; VAPIndex < VAPSizeAtBarIndex; VAPIndex++)
	{
		if (!sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.Index, VAPIndex, &p_VolumeAtPrice))
			break;
            
        TotalVolume += p_VolumeAtPrice->Volume;   
            
    }
            
```

#### sc.VolumeAtPriceForBars Member Function Descriptions

[Link](#scvolumeatpriceforbarsmemberfunctiondescriptions) - [Top](#top)

The following are descriptions of some of the member functions of sc.VolumeAtPriceForBars.

* **int sc.VolumeAtPriceForBars->GetNumberOfBars**(): This function returns the last chart bar index + 1 that the sc.VolumeAtPriceForBars container has volume at price data for. As long as volume at price data is being maintained for the chart, which will be the case when **sc.MaintainVolumeAtPriceData = 1**, the return value of this function will equal sc.ArraySize. This function takes no parameters. If the **sc.VolumeAtPriceForBars** container is empty, then the return value will be 0.
* **int sc.VolumeAtPriceForBars->GetSizeAtBarIndex**(unsigned int **BarIndex**): This function returns the number of prices that have Volume at Price data for the given **BarIndex**.
* **bool sc.VolumeAtPriceForBars->GetVAPElementAtIndex**(unsigned int **BarIndex**, int **VAPDataIndex**, s\_VolumeAtPriceV2\*\* **p\_VAP** ): This function fills out the given **s\_VolumeAtPriceV2** data structure pointer (**p\_VAP**) for the specified **BarIndex** and **VAPDataIndex**. In the case of automatic looping **BarIndex** normally needs to be set to **sc.Index**. **VAPDataIndex** is the zero-based price index within the chart bar to return the s\_VolumeAtPriceV2 data for. 0 is the lowest price within the chart bar. Higher indexes return higher values. The number of prices can be determined with the **sc.VolumeAtPriceForBars->GetSizeAtBarIndex** function. The maximum value of **VAPDataIndex** can be set to will be the number returned by **sc.VolumeAtPriceForBars->GetSizeAtBarIndex** - 1.
    
     
  Always pass the address of the given s\_VolumeAtPriceV2 structure pointer (**p\_VAP**). If **p\_VAP**  is 0 upon returning from this function, then no data was returned. This function returns **true** upon success and **false** upon no data found for the given parameters.
    
     
  There is another overload of this function which takes a const s\_VolumeAtPriceV2\*\* **p\_VAP**.
* **const s\_VolumeAtPriceV2& sc.VolumeAtPriceForBars->GetVAPElementAtPrice**(const unsigned int **BarIndex**, const int **PriceInTicks**):
    
     
  The GetVAPElementAtPrice function returns a reference to a s\_VolumeAtPriceV2 element for the bar index specified by **BarIndex** and at the price specified by **PriceInTicks**. **PriceInTicks** is an integer specifying the price in ticks, where each tick is specified by chart Tick Size and is equal to 1. So if the Tick Size is .25, then the price value of 10 would be 40 (=10/.25).
* **bool sc.VolumeAtPriceForBars->GetVAPElementForPriceIfExists(const unsigned int BarIndex, const int PriceInTicks, s\_VolumeAtPrice\*\* p\_VAP , unsigned int& r\_InsertionIndex)**:
    
     
  The GetVAPElementForPriceIfExists function fills out the given **s\_VolumeAtPriceV2** data structure pointer (**p\_VAP**) for the specified bar index specified by **BarIndex** and at the price specified by **PriceInTicks**, if the price exists. **PriceInTicks** is an integer specifying the price in ticks, where each tick is specified by chart Tick Size and is equal to 1. So if the Tick Size is .25, then the price value of 10 would be 40 (=10/.25).
    
     
  In the case when the cam volume at Price element is not found and the function returns false, the **r\_InsertionIndex** parameter which is an integer, will be set to the index in the Volume at Price container, where the Volume at Price data will be inserted for the specified **BarIndex** and **PriceInTicks** parameters.
* **sc.VolumeAtPriceForBars->SetVolumeAtPrice(const int PriceInTicks, const unsigned int BarIndex, const t\_VolumeAtPrice& VolumeAtPrice)**:
    
     
  The **VolumeAtPrice** volume at price data structure will be placed at the specified **PriceInTicks** and chart **BarIndex**. If PriceInTicks does not exist, the function will do nothing and return false.

### sc.VolumeAtPriceForStudy

[Link](#scvolumeatpriceforstudy) - [Top](#top)

**Type**: Read/write custom data array object pointer of type **c\_VAPContainer**.

The **sc.VolumeAtPriceForStudy** variable is the same as [sc.VolumeAtPriceForBars](#scvolumeatpriceforbars) except it is the volume at price data for the study itself instead of the main price graph of the chart. Normally this is not applicable and contains no data but it is used for special purposes.

There is no further documentation available at this time.

### sc.VolumeAtPriceMultiplier

[Link](#scvolumeatpricemultiplier) - [Top](#top)

**Type**: Read-only integer variable. Was previously read/write. Read-only as of version 2755.

The **sc.VolumeAtPriceMultiplier** variable is set to the same value as the **Volume At Price Multiplier** setting on the **Chart >> Chart Settings >> Main Settings** tab.

When the value is changed, the chart will reload using this new value, after the study function returns.

### sc.VolumePerBar

[Link](#scvolumeperbar) - [Top](#top)

**Type**: Read/Write integer variable.

This ACSIL structure member is considered out of date/deprecated. Instead use the [sc.GetBarPeriodParameters](ACSIL_Members_Functions.md#scgetbarperiodparameters) and [sc.SetBarPeriodParameters](ACSIL_Members_Functions.md#scsetbarperiodparameters) functions.

### sc.VolumeValueFormat

[Link](#scvolumevalueformat) - [Top](#top)

**Type**: Read/Write integer variable.

The **sc.VolumeValueFormat** variable specifies the format for fractional volume values. This variable is the same as the setting in **Chart >> Chart Settings**  **>> Symbol >> Volume Value Format**.

Normally this will be set to 1. It is only used when a particular symbol trades in a fractional quantity.

---

\*Last modified Wednesday, 23rd April, 2025.
