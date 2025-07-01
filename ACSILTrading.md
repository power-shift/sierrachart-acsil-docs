# Automated Trading From an Advanced Custom Study

* [General Information about Trading From an Advanced Custom Study](#generaltradeinformation)
* [General Steps to Create an ACSIL Automated Trading System](#generalstepstocreateanacsilautomatedtradingsystem)
* [Advanced Custom Study Interface Variable Members Relevant to Trading](#scmembers)
  + [sc.AllowOnlyOneTradePerBar](#allowonlyonetradeperbar)
  + [sc.GlobalTradeSimulationIsOn](#globaltradesimulationison)
  + [sc.SupportAttachedOrdersForTrading](#supportattachedordersfortrading)
  + [sc.UseGUIAttachedOrderSetting](#useguiattachedordersetting)
* [Submitting and Modifying an Order (Entry and Exit Order Action Functions)](#submittinganorder)
  + [Buy Entry | Buy Order](#buyentry)
  + [Buy Exit](#buyexit)
  + [Sell Entry | Sell Order](#sellentry)
  + [Sell Exit](#sellexit)
  + [sc.SubmitOCOOrder()](#scsubmitocoorder)
  + [sc.SetAttachedOrders()](#scsetattachedorders)
  + [sc.ModifyOrder()](#scmodifyorder)
  + [s\_SCNewOrder Structure Members](#sscneworder)
    - [[Type: integer] s\_SCNewOrder::OrderQuantity](#s_SCNewOrder_OrderQuantity)
    - [[Type: integer] s\_SCNewOrder::OrderType](#s_SCNewOrder_OrderType)
    - [[Type: double] s\_SCNewOrder::Price1](#s_SCNewOrder_Price1)
    - [[Type: double] s\_SCNewOrder::Price2](#s_SCNewOrder_Price2)
    - [[Type: double] s\_SCNewOrder::StopLimitOrderLimitOffset](#s_SCNewOrder_StopLimitOrderLimitOffset)
    - [[Type: integer] s\_SCNewOrder::InternalOrderID](#s_SCNewOrder_InternalOrderID)
    - [[Type: SCString] s\_SCNewOrder::TextTag](#s_SCNewOrder_TextTag)
    - [[Type: integer] s\_SCNewOrder::TimeInForce](#s_SCNewOrder_TimeInForce)
    - [[Type: double] s\_SCNewOrder::Target1Offset](#s_SCNewOrder_Target1Offset)
    - [[Type: integer] s\_SCNewOrder::Target1InternalOrderID](#s_SCNewOrder_Target1InternalOrderID)
    - [[Type: double] s\_SCNewOrder::Stop1Offset](#s_SCNewOrder_Stop1Offset)
    - [[Type: double] s\_SCNewOrder::StopAllOffset](#s_SCNewOrder_StopAllOffset)
    - [[Type: double] s\_SCNewOrder::Target1Price](#s_SCNewOrder_Target1Price)
    - [[Type: double] s\_SCNewOrder::Stop1Price](#s_SCNewOrder_Stop1Price)
    - [[Type: double] s\_SCNewOrder::StopAllPrice](#s_SCNewOrder_StopAllPrice)
    - [[Type: integer] s\_SCNewOrder::Stop1InternalOrderID](#s_SCNewOrder_Stop1InternalOrderID)
    - [[Type: unsigned integer] s\_SCNewOrder::OCOGroup1Quantity](#s_SCNewOrder_OCOGroup1Quantity)
    - [[Type: char] s\_SCNewOrder::AttachedOrderTarget1Type](#s_SCNewOrder_AttachedOrderTarget1Type)
    - [[Type: char] s\_SCNewOrder::AttachedOrderStop1Type](#s_SCNewOrder_AttachedOrderStop1Type)
    - [[Type: double] s\_SCNewOrder::MaximumChaseAsPrice](#s_SCNewOrder_MaximumChaseAsPrice)
    - [[Type: double] s\_SCNewOrder::AttachedOrderMaximumChase](#s_SCNewOrder_AttachedOrderMaximumChase)
    - [[Type: double] s\_SCNewOrder::TrailStopStepPriceAmount](#s_SCNewOrder_TrailStopStepPriceAmount)
    - [[Type: double] s\_SCNewOrder::AttachedOrderStop1\_TriggeredTrailStopTriggerPriceOffset](#s_SCNewOrder_AttachedOrderStop1_TriggeredTrailStopTriggerPriceOffset)
    - [[Type: double] s\_SCNewOrder::AttachedOrderStop1\_TriggeredTrailStopTrailPriceOffset](#s_SCNewOrder_AttachedOrderStop1_TriggeredTrailStopTrailPriceOffset)
    - [[Type: integer] s\_SCNewOrder::MoveToBreakEven.Type](#s_SCNewOrder_MoveToBreakEvenType)
    - [[Type: integer] s\_SCNewOrder::MoveToBreakEven.BreakEvenLevelOffsetInTicks](#s_SCNewOrder_MoveToBreakEvenBreakEvenLevelOffsetInTicks)
    - [[Type: integer] s\_SCNewOrder::MoveToBreakEven.TriggerOffsetInTicks](#s_SCNewOrder_MoveToBreakEvenTriggerOffsetInTicks)
    - [[Type: integer] s\_SCNewOrder::MoveToBreakEven.TriggerOCOGroup](#s_SCNewOrder_MoveToBreakEvenTriggerOCOGroup)
    - [[Type: SCString] s\_SCNewOrder::Symbol](#s_SCNewOrder_Symbol)
    - [[Type: SCString] s\_SCNewOrder::TradeAccount](#s_SCNewOrder_TradeAccount)
    - [[Type: int] s\_SCNewOrder::SubmitAsHeldOrder](#s_SCNewOrder_SubmitAsHeldOrder)
    - [[Type: function] s\_SCNewOrder::Reset()](#s_SCNewOrder_Reset)
* [Attached Orders and OCO Main Order Types](#attachedordersocomainordertypes)
* [Modifying Orders in OCO Order Types](#modifyingocoorders)
* [Submitting and Managing Orders for Different Symbol and/or Trade Account](#submittingordersdifferentsymbolaccount)
  + [Data Feed Connection and Streaming Data Required](#datafeedconnectionandstreamingdatarequired)
  + [Understanding when Unmanaged Automated Trading Applies](#understandingwhenunmanagedautotradingapplies)
  + [Symbol Settings for Symbol Being Traded](#symbolsettingsforsymbolbeingtraded)
  + [Stop-Limit Order Prices](#stoplimitorderprices)
* [Getting Order Information](#gettingorderinformation)
  + [Determining the Status of an Order](#determiningthestatusofanorder)
  + [Determining if an Order is an Attached Order](#determiningifanorderisanattachedorder)
  + [Accessing Orders which are No Longer Available](#accessingorderswhicharenolongeravailable)
  + [sc.GetOrderByIndex](#getorderbyindex)
  + [sc.GetOrderByOrderID](#getorderbyorderid)
  + [sc.GetTradeListEntry()](#scgettradelistentry)
  + [sc.GetTradeListSize()](#scgettradelistsize)
  + [sc.GetFlatToFlatTradeListEntry()](#scgetflattoflattradelistentry)
  + [sc.GetFlatToFlatTradeListSize()](#scgetflattoflattradelistsize)
  + [sc.GetOrderFillEntry()](#scgetorderfillentry)
  + [sc.GetOrderFillArraySize()](#scgetorderfillarraysize)
  + [sc.GetOrderForSymbolAndAccountByIndex()](#scgetorderforsymbolandaccountbyindex)
  + [sc.GetParentOrderIDFromAttachedOrderID()](#scgetparentorderidfromattachedorderid)
  + [sc.GetNearestStopOrder()](#scgetneareststoporder)
  + [sc.GetNearestTargetOrder()](#scgetnearesttargetorder)
  + [sc.GetTradeStatisticsForSymbolV2()](#scgettradestatisticsforsymbolv2)
  + [IsWorkingOrderStatus()](#isworkingorderstatus)
  + [IsWorkingOrderStatusIgnorePendingChildren()](#isworkingorderstatusignorependingchildren)
  + [s\_SCTradeOrder Structure Members](#ssctradeorder)
    - [[Type: integer] InternalOrderID](#s_SCTradeOrder_InternalOrderID)
    - [[Type: SCString] Symbol](#s_SCTradeOrder_Symbol)
    - [[Type: SCString] OrderType](#s_SCTradeOrder_OrderType)
    - [[Type: integer] OrderQuantity](#s_SCTradeOrder_OrderQuantity)
    - [[Type: integer] FilledQuantity](#s_SCTradeOrder_FilledQuantity)
    - [[Type: integer] BuySell](#s_SCTradeOrder_BuySell)
    - [[Type: double] Price1](#s_SCTradeOrder_Price1)
    - [[Type: double] Price2](#s_SCTradeOrder_Price2)
    - [[Type: double] AvgFillPrice](#s_SCTradeOrder_AvgFillPrice)
    - [[Type: integer] OrderStatusCode](#s_SCTradeOrder_OrderStatusCode)
    - [[Type: integer] ParentInternalOrderID](#s_SCTradeOrder_ParentInternalOrderID)
    - [[Type: integer] LinkID](#s_SCTradeOrder_LinkID)
    - [[Type: SCDateTime] LastActivityTime](#s_SCTradeOrder_LastActivityTime)
    - [[Type: SCDateTime] EntryDateTime](#s_SCTradeOrder_EntryDateTime)
    - [[Type: integer] OrderTypeAsInt](#s_SCTradeOrder_OrderTypeAsInt)
    - [[Type: SCString] TextTag](#s_SCTradeOrder_TextTag)
    - [[Type: unsigned int] LastModifyQuantity](#s_SCTradeOrder_LastModifyQuantity)
    - [[Type: double] LastModifyPrice1](#s_SCTradeOrder_LastModifyPrice1)
    - [[Type: double] LastFillPrice](#s_SCTradeOrder_LastFillPrice)
    - [[Type: int] LastFillQuantity](#s_SCTradeOrder_LastFillQuantity)
    - [[Type: int] SourceChartNumber](#s_SCTradeOrder_SourceChartNumber)
    - [[Type: SCString] SourceChartbookFileName](#s_SCTradeOrder_SourceChartbookFileName)
    - [[Type: int] IsSimulated](#s_SCTradeOrder_IsSimulated)
    - [[Type: uint64\_t] TargetChildInternalOrderID](#s_SCTradeOrder_TargetChildInternalOrderID)
    - [[Type: uint64\_t] StopChildInternalOrderID](#s_SCTradeOrder_StopChildInternalOrderID)
    - [[Type: uint64\_t] OCOSiblingInternalOrderID](#s_SCTradeOrder_OCOSiblingInternalOrderID)
    - [[Type: int32\_t] EstimatedPositionInQueue](#s_SCTradeOrder_EstimatedPositionInQueue)
    - [[Type: integer] TriggeredTrailingStopTriggerHit](#s_SCTradeOrder_TriggeredTrailingStopTriggerHit)
    - [[Type: SCString] LastOrderActionSource](#s_SCTradeOrder_LastOrderActionSource)
    - [[Type: SCString] TradeAccount](#s_SCTradeOrder_TradeAccount)
* [Cancel Orders and Flatten Position Functions](#cancelflattenfunctions)
  + [sc.CancelOrder](#cancelorder)
  + [sc.CancelAllOrders](#cancelallorders)
  + [sc.FlattenAndCancelAllOrders](#flattenandcancelallorders)
  + [sc.FlattenPosition](#flattenposition)
  + [sc.FlattenAndCancelAllOrdersForSymbolAndNonSimTradeAccount](#flattenandcancelallordersforsymbolandnonsimtradeaccount)
* [Getting Trade Position Data](#gettingpositioninformation)
  + [sc.GetTradePosition](#scgettradeposition)
  + [sc.GetTradePositionByIndex](#scgettradepositionbyindex)
  + [sc.GetTradePositionForSymbolAndAccount()](#scgettradepositionforsymbolandaccount)
  + [s\_SCPositionData Position Structure](#sscpositiondata)
* [Other Trade Related Items](#othertraderelateditems)
  + [sc.FlattenPositionsAndCancelOrdersForTradeAccount()](#scflattenpositionsandcancelordersfortradeaccount)
  + [sc.GetAttachedOrders()](#scgetattachedorders)
  + [sc.GetNearestStopWorkingAttachedOrder()](#scgetneareststopworkingattachedorder)
  + [sc.GetNearestTargetWorkingAttachedOrder()](#scgetnearesttargetworkingattachedorder)
  + [sc.GetNumAttachedOrders()](#scgetnumattachedorders)
  + [sc.GetNumTradeAccounts()](#scgetnumtradeaccounts)
  + [sc.GetStopOrderInOCOGroupNumber()](#scgetstoporderinocogroupnumber)
  + [sc.GetTargetOrderInOCOGroupNumber()](#scgettargetorderinocogroupnumber)
  + [sc.GetTradeAccountAtIndex()](#scgettradeaccountatindex)
  + [sc.GetTradeAccountData()](#scgettradeaccountdata)
  + [sc.GetTradeServiceAccountBalanceForTradeAccount()](#scgettradeserviceaccountbalancefortradeaccount)
  + [sc.GetTradingErrorTextMessage()](#scgettradingerrortextmessage)
  + [sc.GetUseAttachedOrdersEnabledState()](#scgetuseattachedordersenabledstate)
  + [sc.SendHeldTradeOrder()](#scsendheldtradeorder)
* [Programmatically Setting Trade Window Configuration](#programmaticallysettingtradewindowconfiguration)
* [Going from Simulation Mode to Live Trading](#simulationtolive)
* [Constants](#constants)
  + [Order Type Constants](#ordertypeconstants)
  + [Order Error Constants](#ignoredordererror)
* [Example Trading Systems and Code](#examplecode)
* [Debugging/Troubleshooting Automated Trading Systems](#debuggingtradingsystems)
* [Back-Testing (Opens a New Page)](Backtesting.md)

---

## General Information about Trading From an Advanced Custom Study

[Link](#generaltradeinformation) - [Top](#top)

This page provides documentation for automated trading functions for the Sierra Chart Advanced Custom Study Interface and Language (ACSIL). If you are not familiar with ACSIL, refer to the [Advanced Custom Study Interface and Language](AdvancedCustomStudyInterfaceAndLanguage.md) page.

Sierra Chart provides a fully managed environment for automated trading to make it very easy to perform automated trading and not get involved in all the low-level details of keeping track of Positions and working Orders.

Sierra Chart provides a very solid, stable and robust environment for automated trading. Support for server-side brackets to exit a position entered through automated trading, is supported.

[Unmanaged automated trading](AutoTradeManagment.md#unmanagedautomatedtrading) is supported as well if you do not want to rely on or use the automated trade management of Sierra Chart.

The trading functions in the Advanced Custom Study Interface work the same as the BuyEntry, SellEntry, BuyExit, SellExit Spreadsheet columns in the **Spreadsheet System For Trading** study. Orders are submitted through the [sc.BuyEntry](#buyentry), [sc.BuyExit](#buyexit), [sc.SellEntry](#sellentry) and [sc.SellExit](#sellexit) trading functions that process **Buy Entries, Buy Exits, Sell Entries,** and **Sell Exits**.

These functions examine the Position Quantity and Working Orders for the Symbol and Trade Account of the chart that your trading study is applied to, and the related Auto Trade Management variables and will only send an order (whether simulated or live) if the right conditions are met. For more information about these functions, refer to the [Submitting And Modifying An Order Through the Advanced Custom Study Interface](#submittinganorder) section.

Automated trading order processing occurs when the [sc.BuyEntry](#buyentry), [sc.BuyExit](#buyexit), [sc.SellEntry](#sellentry) and [sc.SellExit](#sellexit) trading functions are called, but *do not occur on historical bars or while historical data is being downloaded*. One exception is the current chart bar which becomes an historical bar during normal chart updating. Order processing can occur on that bar and any new bars added.

On historical bars and during a historical data download, these Entry and Exit Order Action functions are ignored and will return [SCT\_SKIPPED\_FULL\_RECALC or SCT\_SKIPPED\_DOWNLOADING\_HISTORICAL\_DATA](#ignoredordererror).

Only real time updating or data added to the chart during a replay can cause order processing. This is designed for safety. For example, if you are running a replay, since replays start at the very last visible bar where you begin the replay, by default, all historical bars prior to that will cause these functions to return [SCT\_SKIPPED\_FULL\_RECALC](#ignoredordererror) since a recalculation occurs on a chart reload and replays perform a chart reload.

Any order submitted from ACSIL, can be interacted with on the chart assuming it is an open order, in the same way as if it were manually submitted. To support this, the chart containing the automated trading study needs to have [Chart Trade Mode](ChartTrading.md#charttrading) enabled.

## General Steps to Create an ACSIL Automated Trading System

[Link](#generalstepstocreateanacsilautomatedtradingsystem) - [Top](#top)

Below are the general steps to create an ACSIL (Advanced Custom Study Interface and Language) based automated trading system, using that automated trading system, back testing it and viewing the results from that back test.

1. Follow the [Step-By-Step Instructions to Create an Advanced Custom Study Function](AdvancedCustomStudyInterfaceAndLanguage.md#stepbystepinstructions) to create a custom trading study.
2. Refer to the [Submitting and Modifying An Order Through the Advanced Custom Study Interface](#submittinganorder) documentation for the functions to submit orders, and the other documentation on this page to actually implement the trading system in the source code.
3. Add the compiled trading study to the chart you want to perform automated trading on. The [Step-By-Step Instructions to Create an Advanced Custom Study Function](AdvancedCustomStudyInterfaceAndLanguage.md#stepbystepinstructions) instructions explain how to do this.
4. The automated trading system will be functional when **Trade >> Auto Trading Enabled - Global** and **Trade >> Auto Trading Enabled - Chart** are both enabled. For information about when a chart updates and when the trading study function will be called, refer to [When the Study Function Is Called](ACS_ArraysAndLooping.md#whenthestudyfunctioniscalled).
5. Refer to [Example Trading Systems and Code](#examplecode) for examples of trading studies.
6. To perform back testing of the automated trading system, refer to [Back-Testing](Backtesting.md).
7. When you are ready to perform live trading, if at all, then refer to the [Going from Simulation Mode to Live Trading](#simulationtolive).

## Advanced Custom Study Interface Variable Members Relevant to Trading

[Link](#scmembers) - [Top](#top)

For a complete list of the variable members of the Advanced Custom Study Interface that are related to automated trading, refer to the [Variables](AutoTradeManagment.md#variables) section on the Auto Trade Management page.

Variables which are specific for ACSIL trading and not Spreadsheet trading systems, are listed below.

For the other members of the Advanced Custom Study Interface, refer to the [Definitions of Advanced Custom Study/System Interface Members](ACSIL_Members.md) page.

#### sc.AllowOnlyOneTradePerBar

[Link](#allowonlyonetradeperbar) - [Top](#top)

The default value for this variable is **1 (TRUE)**. When this variable is set to **1 (TRUE)** (by default), only one order for each Order Action type (Buy Entry, Buy Exit, Sell Entry, Sell Exit) is allowed for a single chart bar.

When the trading system has exceeded one order for a bar for a particular Order Action, the Order Action function will return **SCT\_SKIPPED\_ONLY\_ONE\_TRADE\_PER\_BAR**. This applies to order submissions by the Order Action functions to Sierra Chart Trade Simulation Mode or to the connected external Trading service, regardless of whether the order filled or not.

For example, once **sc.BuyEntry** is called and is successful with an order submission (whether the order fills or not), additional calls to **sc.BuyEntry** will be ignored on the same chart bar and will return **SCT\_SKIPPED\_ONLY\_ONE\_TRADE\_PER\_BAR**.

On the next chart bar, the call will succeed. **sc.BuyExit, sc.SellEntry**, and **sc.SellExit** all work the same way, however independently from each other.

For example, you may have one Buy Entry and one Sell Entry at the same bar, just not two Buy Entries or two Sell Entries.

If an Order Action like **sc.BuyEntry** is called and the Order Action is ignored for some reason other than relating to **sc.AllowOnlyOneTradePerBar**, this will not be considered a trade on the chart bar, and another order will still be allowed.

For most cases, having 1 trade per bar should be sufficient. We recommend that this variable be set to **1 (TRUE)** unless you are confident you are not going to run into unexpected logic in your code which could cause numerous or endless trades to occur on a chart bar.

If you want more control over your trading, then set this variable to **0 (FALSE)**. If you set this to **0 (FALSE)**, thoroughly test your trading study through backtesting and in Sierra Chart Trade Simulation Mode with live data. Otherwise, you could run into some unexpected results where there are continuous trades made on the same chart bar.

Sometimes users will incorrectly interpret that the **sc.AllowOnlyOneTradePerBar** variable when enabled does not work properly because when they look at the order fills on the chart, more than one fill of the same Order Action type on the same chart bar may exist. This is an *incorrect* method of coming to this conclusion as it can be possible that on the same chart bar there can be a **Buy Entry, Buy Exit, Sell Entry**, and **Sell Exit**.

The location of the order fill represents the Date-Time of that fill. That Date-Time may be on a subsequent chart bar compared to the chart bar that actually triggered the order entry. The most current Date-Time is going to be used when filling an order. When the chart is replaying it will be the most recent Date-Time loaded into the chart at that time. And also the Date-Time of the data feed is going to affect the placement of the order fill during simulated and non-simulated trading using real-time data (Not during a replay).

To determine what chart bar actually submitted the order, you need to look at the [Trade Activity Log](TradeActivityLog.md#viewinghistoricaltradeactivity). The Date-Time of the chart bar triggering the submission of the order will be given in the **Order Action Source** field. In the Order Action Source field look for the text beginning with **| Bar start date-time**.

#### sc.GlobalTradeSimulationIsOn

[Link](#globaltradesimulationison) - [Top](#top)

This variable is set to **1 (TRUE)** when Sierra Chart Trade Simulation Mode On is enabled on the Trade menu, and set to **0 (FALSE)** when Trade Simulation Mode on the Trade menu is disabled.

#### sc.SupportAttachedOrdersForTrading

[Link](#supportattachedordersfortrading) - [Top](#top)

Refer to the [sc.SupportAttachedOrdersForTrading](ACSIL_Members_Variables_And_Arrays.md#scsupportattachedordersfortrading) section.

#### sc.UseGUIAttachedOrderSetting

[Link](#useguiattachedordersetting) - [Top](#top)

Refer to the [sc.UseGUIAttachedOrderSetting](ACSIL_Members_Variables_And_Arrays.md#scuseguiattachedordersetting) section.

## Submitting an Order (Entry and Exit Order Action Functions)

[Link](#submittinganorder) - [Top](#top)

Order submission is done through the [Buy Entry](#buyentry), [Buy Exit](#buyexit), [Sell Entry](#sellentry) and [Sell Exit](#sellexit) Order Action functions.

These functions take an [s\_SCNewOrder](#sscneworder) structure parameter.

These Entry and Exit functions can be used with either [Automatic Looping](ACS_ArraysAndLooping.md#automaticloopingiterating) or with [Manual Looping](ACS_ArraysAndLooping.md#manuallooping). There are different versions of these functions whether you are using automatic looping or manual looping.

The versions of these functions for manual looping require a **DataArrayIndex** parameter which needs to be set to the bar index currently being processed by the study function when the particular Order Action function is called. The functions that do not require this parameter, internally have **DataArrayIndex** set to [sc.Index](ACSIL_Members_Variables_And_Arrays.md#scindex) at the time they are called.

For information about the global Trade Simulation Mode setting and the **sc.SendOrdersToTradeService** variable which controls whether orders will be simulated or non-simulated, refer to [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice).

### Buy Entry | Buy Order

[Link](#buyentry) - [Top](#top)

int **sc.BuyEntry**(s\_SCNewOrder& **NewOrder**); Note: For use with Auto-Looping only.

int **sc.BuyEntry**(s\_SCNewOrder& **NewOrder**, int **DataArrayIndex**); Note: For use with Manual Looping only.

int **sc.BuyOrder**(s\_SCNewOrder& **NewOrder**); Note: For use with Auto-Looping only.

int **sc.BuyOrder**(s\_SCNewOrder& **NewOrder**, int **DataArrayIndex**); Note: For use with Manual Looping only.

**sc.BuyEntry**  and **sc.BuyOrder** are the same. However, when submitting an order for a different Symbol or Trade Account compared to the chart the trading study is on, you must use the **sc.BuyOrder** function.

For a complete description of the behavior of this Order Action type, refer to the [Auto Trade Management](AutoTradeManagment.md#buyentry) page.

**Returns:** A return value > 0 indicates the order was successfully submitted; the actual value returned is the quantity of the submitted order. If the return value is negative, < 0, the order submission was ignored.

If [SCTRADING\_ORDER\_ERROR](#sctradingordererror) is returned, then the reason the order was ignored is logged in the [Trade Service Log](TradeStatusWindows.md#tradeservicelog). The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror).

#### Parameters

* **NewOrder**: A reference to an [s\_SCNewOrder](#sscneworder) structure.
* [DataArrayIndex](ACSIL_Members_Functions.md#commonfunctionparameterdescriptionsbarindex)

### Buy Exit

[Link](#buyexit) - [Top](#top)

int **sc.BuyExit**(s\_SCNewOrder& **NewOrder**); Note: For use with Auto-Looping only.

int **sc.BuyExit**(s\_SCNewOrder& **NewOrder**, int **DataArrayIndex**); Note: For use with Manual Looping only.

For a complete description of the behavior of this Order Action type, refer to the [Auto Trade Management](AutoTradeManagment.md#buyexit) page.

**Returns:** A return value > 0 indicates the order was successfully submitted; the actual value returned is the quantity of the submitted order. If the return value is negative, < 0, the order submission was ignored.

If [SCTRADING\_ORDER\_ERROR](#sctradingordererror) is returned, then the reason the order was ignored is logged in the [Trade Service Log](TradeStatusWindows.md#tradeservicelog). The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror).

#### Parameters

* **NewOrder**: A reference to an [s\_SCNewOrder](#sscneworder) structure.
* [DataArrayIndex](ACSIL_Members_Functions.md#commonfunctionparameterdescriptionsbarindex)

### Sell Entry | Sell Order

[Link](#sellentry) - [Top](#top)

int **sc.SellEntry**(s\_SCNewOrder& **NewOrder**); Note: For use with Auto-Looping only.

int **sc.SellEntry**(s\_SCNewOrder& **NewOrder**, int **DataArrayIndex**); Note: For use with Manual Looping only.

int **sc.SellOrder**(s\_SCNewOrder& **NewOrder**); Note: For use with Auto-Looping only.

int **sc.SellOrder**(s\_SCNewOrder& **NewOrder**, int **DataArrayIndex**); Note: For use with Manual Looping only.

**sc.SellEntry** and **sc.SellOrder** are the same. However, when submitting an order for a different Symbol or Trade Account compared to the chart the trading study is on, you must the **sc.SellOrder** function.

For a complete description of the behavior of this Order Action type, refer to the [Auto Trade Management](AutoTradeManagment.md#sellentry) page.

**Returns:** A return value > 0 indicates the order was successfully submitted; the actual value returned is the quantity of the submitted order. If the return value is negative, < 0, the order submission was ignored.

If [SCTRADING\_ORDER\_ERROR](#sctradingordererror) is returned, then the reason the order was ignored is logged in the [Trade Service Log](TradeStatusWindows.md#tradeservicelog). The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror).

#### Parameters

* **NewOrder**: A reference to an [s\_SCNewOrder](#sscneworder) structure.
* [DataArrayIndex](ACSIL_Members_Functions.md#commonfunctionparameterdescriptionsbarindex)

### Sell Exit

[Link](#sellexit) - [Top](#top)

int **sc.SellExit**(s\_SCNewOrder& **NewOrder**); Note: For use with Auto-Looping only.

int **sc.SellExit**(s\_SCNewOrder& **NewOrder**, int **DataArrayIndex**); Note: For use with Manual Looping only.

For a complete description of the behavior of this Order Action type, refer to the [Auto Trade Management](AutoTradeManagment.md#sellexit) page.

**Returns:** A return value > 0 indicates the order was successfully submitted; the actual value returned is the quantity of the submitted order. If the return value is negative, < 0, the order submission was ignored.

If [SCTRADING\_ORDER\_ERROR](#sctradingordererror) is returned, then the reason the order was ignored is logged in the [Trade Service Log](TradeStatusWindows.md#tradeservicelog). The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror).

#### Parameters

* **NewOrder**: A reference to an [s\_SCNewOrder](#sscneworder) structure.
* [DataArrayIndex](ACSIL_Members_Functions.md#commonfunctionparameterdescriptionsbarindex)

### sc.SubmitOCOOrder()

[Link](#scsubmitocoorder) - [Top](#top)

int **sc.SubmitOCOOrder**(s\_SCNewOrder& **NewOrder**); Note: For use with Auto-Looping only.

int **sc.SubmitOCOOrder**(s\_SCNewOrder& **NewOrder**, int **BarIndex**); Note: For use with Manual Looping only.

The **sc.SubmitOCOOrder()** function is for submitting OCO (Order Cancels Order) orders. It is only to be used when **s\_SCNewOrder::OrderType** is set to one of the following: **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP**, **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_LIMIT\_SELL\_STOP\_LIMIT**, or **SCT\_ORDERTYPE\_OCO\_BUY\_LIMIT\_SELL\_LIMIT**.

**Returns:** A return value > 0 indicates the order was successfully submitted; the actual value returned is the quantity of the submitted order. If the return value is negative, < 0, the order submission was ignored.

If [SCTRADING\_ORDER\_ERROR](#sctradingordererror) is returned, then the reason the order was ignored is logged in the [Trade Service Log](TradeStatusWindows.md#tradeservicelog).

The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror).

#### Parameters

* **NewOrder**: A reference to an [s\_SCNewOrder](#sscneworder) structure.
* [BarIndex](ACSIL_Members_Functions.md#commonfunctionparameterdescriptionsbarindex)

### sc.SetAttachedOrders

[Link](#scsetattachedorders) - [Top](#top)

**Type**: Function

void **SetAttachedOrders**(const s\_SCNewOrder& **AttachedOrdersConfiguration**);

The **sc.SetAttachedOrders()** function is used to set the Attached Orders configuration on the Trade Window for the chart the study is applied to. It does not submit any orders.

#### Parameters

**AttachedOrdersConfiguration**: An [s\_SCNewOrder](#sscneworder) structure that contains the configuration for the Attached Orders. This structure needs to be set in the same way it would be set for a new order which uses Attached Orders.

Only the Attached Order (Target and Stop) related members are going to be used. It is not necessary to set the variables which relate to the parent order like the following: **OrderType, Price1, Price2**.

### sc.ModifyOrder()

[Link](#scmodifyorder) - [Top](#top)

**Type**: Function

int **sc.ModifyOrder**(s\_SCNewOrder& **OrderModification**);

The **sc.ModifyOrder()** function is used to perform order modifications.

Only Price1 and/or Price2 of an order and the order quantity can be modified.

When this function is called, an order modification request will be sent to the Sierra Chart Trade Simulation System or the connected Trading service depending upon whether you are in Trade Simulation Mode and whether the order was originally a simulated order.

This function is affected by the **sc.SendOrdersToTradeService** variable. For more information, refer to [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice).

When modifying an order, if the specified Price and/or Quantity is not different than the current values or the prior pending modification, then no modification will be performed. In this case a message will be added to the **Trade >> Trade Service Log** indicating this.

The entire [s\_SCNewOrder](#sscneworder) does not need to be filled in, except for the **InternalOrderID** member. That must be set to the [InternalOrderID](#sscneworderinternalorderid) of the order that you want to modify. The **InternalOrderID** can be obtained when you submitted the order. The **InternalOrderID** can also be obtained with the [sc.GetOrderByIndex(), sc.GetNearestTargetOrder(), sc.GetNearestStopOrder()](#gettingorderinformation) functions.

Only the members that you want to modify, need to be set. For example, if you only want to change the quantity of an order, simply pass in an **s\_SCNewOrder** structure with the **OrderQuantity** member set to the new quantity and the InternalOrderID set.

If your automated trading system is making an order modification when another order modification is pending, then this is something to consider. For example, if you are changing the quantity, you should consider what the quantity is of the prior modification which may still be pending. When you [get order data](#gettingorderinformation), the returned Price1 and Quantity will be the latest values based upon the most recent modification even if it is a pending modification.

Only the following members of the s\_SCNewOrder can be set when modifying an order: **OrderQuantity, Price1, Price2, InternalOrderID**. All other members are not relevant because only Price and Quantity can be modified.

When setting the Prices in the **s\_SCNewOrder** structure, these do not have to be set exactly to a number which is an exact multiple of the Tick Size. Sierra Chart will automatically round them to the nearest tick.

In the case of Target and Stop orders specified with a parent order (Target1Offset, Stop1Offset, Target1Price, Stop1Price, ...), when these orders have been submitted, they exist as individual orders that can be individually modified. If you wish to modify the prices of these Attached Orders, then you will need to set the **Price1** member, and not the **\*Offset/\*Price** members of the s\_SCNewOrder structure. After order submission, these prices are always actual prices and never offsets. The order prices for all orders can be clearly seen in the **Trade >> Trade Orders Window**.

When order is modified, all other working orders that are linked to the order you are modifying, will also be modified. This applies to price modifications only. Not to the modification of the Order Quantity. Orders may be linked when the order is part of an order set that contains an Attached Order with an OCO Group setting of All Groups and there was more than OCO Group 1 through 5 used. You can see if an order is part of a linked group by looking at the **Link ID** field in **Trade >> Trade Orders Window**. Orders that share the same Link ID are linked.

**Return Values**:

* 1 on a successful order modification. This does not necessarily mean the actual order modification will be successful. Only that it succeeded with the initial basic processing. If there is no order found to modify, the function returns [SCTRADING\_ORDER\_ERROR](#sctradingordererror). The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror).
* If the chart is in the process of downloading historical data, the order modification will be ignored and the return value will be **SCT\_SKIPPED\_DOWNLOADING\_HISTORICAL\_DATA**.
* If the chart is being fully recalculated, which happens when the study is added to the chart, the Chartbook the study is contained within is opened and other conditions, the order modification will be ignored and the return value will be **SCT\_SKIPPED\_FULL\_RECALC**.
* If automated trading is disabled, the order modification will be ignored and the return value will be **SCTRADING\_ORDER\_ERROR**.

For a code example to modify an Attached Order, refer to the **scsf\_TradingExampleWithAttachedOrdersDirectlyDefined** function in the **/ACS\_Source/TradingSystem.cpp** file in the folder that Sierra Chart is installed to.

#### Parameters

* **OrderModification**: A reference to an [s\_SCNewOrder](#sscneworder) structure.

#### Example

```cpp

s_SCNewOrder ModifyOrder;
ModifyOrder.InternalOrderID = StopAllOrderID;
ModifyOrder.Price1 = NewPrice;

sc.ModifyOrder(ModifyOrder);
            
```

### s\_SCNewOrder Structure Members

[Link](#sscneworder) - [Top](#top)

The Order Action and the order modification functions require an **s\_SCNewOrder** structure. The following is a description of each member of the **s\_SCNewOrder** structure.

#### [Type: integer] s\_SCNewOrder::OrderQuantity

[Link](#sscneworderorderquantity) - [Top](#top)

Specifies order quantity for the order. The default for this is 0. This must be set to a nonzero positive number in the case of **sc.BuyEntry, sc.SellEntry, sc.BuyOrder, sc.SellOrder**. Otherwise, you will receive an order error when submitting an order.

The Quantity setting on the [Trade Window](TradeWindow.md) for the chart the trading study is applied to is never used, even when this is set to 0.

In the case of an **sc.BuyExit**  or  **sc.SellExit**, if this is set to 0, then the current Trade Position will be flattened. Be sure to expressly set it to 0, if this is what you want to do. If it is set to a nonzero number in the case of an Exit, and the quantity is less than the quantity required to flatten the current Trade Position, then that will be the order quantity. If it exceeds the quantity necessary to flatten the Trade Position, then the current Trade Position will be flattened and the extra quantity will be ignored.

When providing a quantity, always use the actual required quantity. If you set 1, the quantity will be 1. In the case of the spot Forex markets, you will want to specify the actual number of currency units. For example, 50000 unless the particular Forex trading service being used, requires different quantity units like with LMAX.

In the case of when using [sc.ModifyOrder](#ordermodification), and it is the intention to only modify the price of the order and not the quantity, then set the **OrderQuantity** variable to 0 to let Sierra Chart manage the quantity. This minimizes the possibility of the quantity being incorrectly set, when there is a previous order quantity modification still outstanding or the server is changing the quantity of the order due to child order management.

#### [Type: integer] s\_SCNewOrder::OrderType

[Link](#sscneworderordertype) - [Top](#top)

Specifies the order type of the new order to submit. Refer to the [Order Type Constants](#ordertypeconstants) section. Order Modifications ignore this member.

#### [Type: double] s\_SCNewOrder::Price1

[Link](#sscneworderprice1) - [Top](#top)

Specifies the order price. This must be set as an actual price value. This member needs to be set when you have set the **OrderType** member to one of the following:

* **SCT\_ORDERTYPE\_LIMIT**
* **SCT\_ORDERTYPE\_STOP**
* **SCT\_ORDERTYPE\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_MARKET\_IF\_TOUCHED**
* **SCT\_ORDERTYPE\_LIMIT\_CHASE**
* **SCT\_ORDERTYPE\_LIMIT\_TOUCH\_CHASE**
* **SCT\_ORDERTYPE\_TRAILING\_STOP**
* **SCT\_ORDERTYPE\_TRAILING\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS**
* **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_LIMIT\_3\_OFFSETS**
* **SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP**
* **SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP**
* **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_OCO\_LIMIT\_STOP**
* **SCT\_ORDERTYPE\_OCO\_LIMIT\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP**
* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_LIMIT\_SELL\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_OCO\_BUY\_LIMIT\_SELL\_LIMIT**
* **SCT\_ORDERTYPE\_LIMIT\_IF\_TOUCHED**
* **SCT\_ORDERTYPE\_BID\_ASK\_QUANTITY\_TRIGGERED\_STOP**
* **SCT\_ORDERTYPE\_TRIGGERED\_LIMIT**
* **SCT\_ORDERTYPE\_TRADE\_VOLUME\_TRIGGERED\_STOP**
* **SCT\_ORDERTYPE\_STOP\_WITH\_BID\_ASK\_TRIGGERING**
* **SCT\_ORDERTYPE\_STOP\_WITH\_LAST\_TRIGGERING**
* **SCT\_ORDERTYPE\_LIMIT\_IF\_TOUCHED\_CLIENT\_SIDE**
* **SCT\_ORDERTYPE\_MARKET\_IF\_TOUCHED\_CLIENT\_SIDE**
* **SCT\_ORDERTYPE\_TRADE\_VOLUME\_TRIGGERED\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_STOP\_LIMIT\_CLIENT\_SIDE**
* **SCT\_ORDERTYPE\_TRIGGERED\_STOP**

In the case of SCT\_ORDERTYPE\_LIMIT or SCT\_ORDERTYPE\_MARKET\_IF\_TOUCHED, if **Price1** is set to 0, then it will be set to the current Bid price if the order is a Sell order or it will be set to the current Ask price if the order is a Buy order.

Price1 is always rounded to the nearest tick upon final order submission. So it does not have to be precisely set.

The current bid price can be accessed with **sc.Bid** and the current ask price with **sc.Ask**.

##### s\_SCNewOrder::Price1 Code Example

```cpp

    float BarLow = sc.Low[sc.Index];            
            
    s_SCNewOrder NewOrder;
    NewOrder.OrderQuantity = 1;
    NewOrder.OrderType = SCT_ORDERTYPE_STOP;
    NewOrder.TimeInForce = SCT_TIF_DAY;
    NewOrder.Price1 = BarLow;            
                
```

#### [Type: double] s\_SCNewOrder::Price2

[Link](#sscneworderprice2) - [Top](#top)

Depending upon the Order Type, **Price2** specifies a second price for the order. Refer to the table below for what specific price it sets based on the order type and whether it is optional or not.

In the case of Stop-Limit orders if **Price2** is not set, then the Limit price will be automatically calculated based upon the [Stop-Limit Order Limit Offset >> Primary Orders](TradeWindow.md#sscneworderstoplimitorderlimitoffset) setting on the Trade Window.

In the case of Stop-Limit orders, the **Stop-Limit Order Limit Offset >> Primary Orders** setting can also be set by the [s\_SCNewOrder::StopLimitOrderLimitOffset](#sscneworderstoplimitorderlimitoffset) member.

Based on the below table, if the Limit price of a Stop-Limit order cannot be set with **Price2**, then it needs to be set by using [s\_SCNewOrder::StopLimitOrderLimitOffset](#sscneworderstoplimitorderlimitoffset) instead.

**Price2** must be set as an actual price value. It is not an offset.

The following are the order types which support **Price2**:

* **SCT\_ORDERTYPE\_STOP\_LIMIT**: Optional. Limit price.
* **SCT\_ORDERTYPE\_TRAILING\_STOP\_LIMIT**: Optional. Limit price.
* **SCT\_ORDERTYPE\_OCO\_LIMIT\_STOP**: Required. Stop price.
* **SCT\_ORDERTYPE\_OCO\_LIMIT\_STOP\_LIMIT**: Required. Stop price.
* **SCT\_ORDERTYPE\_OCO\_BUY\_LIMIT\_SELL\_LIMIT**: Required. Sell Limit price.
* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP**: Required. Sell Stop price.
* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_LIMIT\_SELL\_STOP\_LIMIT**: Required. Sell Stop price.
* **SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP**: Required. Step Amount as price value, not in ticks.
* **SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP\_LIMIT**: Required. Step Amount as price value, not in ticks.
* **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS**: Required. Trigger price.
* **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_LIMIT\_3\_OFFSETS**: Required. Trigger price.
* **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP**: Required. Trigger price. Step Amount is automatically set to the trailing stop initial offset.
* **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP\_LIMIT**: Required. Trigger price. Step Amount is automatically set to the trailing stop initial offset.
* **SCT\_ORDERTYPE\_TRIGGERED\_LIMIT**: Required. Sets the Trigger price.
* **SCT\_ORDERTYPE\_TRADE\_VOLUME\_TRIGGERED\_STOP**: Required. Sets the volume amount.
* **SCT\_ORDERTYPE\_TRADE\_VOLUME\_TRIGGERED\_STOP\_LIMIT**: Required. Sets the volume amount.
* **SCT\_ORDERTYPE\_STOP\_LIMIT\_CLIENT\_SIDE**: Optional. Limit price.
* **SCT\_ORDERTYPE\_TRIGGERED\_STOP**: Required. Sets the Trigger price.

**Price2** is always rounded to the nearest tick upon final order submission. So it does not have to be precisely set.

When modifying a Stop-Limit type order, if **Price2** is not set, then the Limit price will be adjusted to maintain the identical offset it had to the original **Price1** price if a new **Price1** is set when modifying the order.

#### [Type: double] s\_SCNewOrder::StopLimitOrderLimitOffset

[Link](#sscneworderstoplimitorderlimitoffset) - [Top](#top)

When the **StopLimitOrderLimitOffset** variable is set, this will set the **Set >> Stop Limit Order Limit Offset >> Primary Orders** setting on the [Trade Window](TradeWindow.md#openingtradewindow) for the chart.

The value needs to be specified as an actual price value and is converted to Ticks.

Setting **StopLimitOrderLimitOffset** is one way to control the Limit price of a Stop-Limit order. The other method is to set [Price2](#sscneworderprice2).

In the case of when using the [Submitting and Managing Orders for Different Symbol and/or Trade Account](#submittingordersdifferentsymbolaccount) functionality, **StopLimitOrderLimitOffset** is used as the offset for the Limit price of Stop-Limit *Attached Orders*. If this member is not set, then the Stop order Price2 will be set the same as Price1. This member does not control the Limit price (Price2) of the parent/main Stop-Limit order. That must be set through the [Price2](#sscneworderprice2) member.

#### [Type: integer] s\_SCNewOrder::InternalOrderID

[Link](#sscneworderinternalorderid) - [Top](#top)

When submitting a new order, this is a member that you do *not* set. When you call one of the Order Action functions (**sc.BuyEntry()**,**sc.BuyExit()**, **sc.SellEntry()**, **sc.SellExit**), then this will be set to the Sierra Chart InternalOrderID of the order if the order has been accepted.

If the variable has not been set, it remains at 0 and this means the order submission was ignored. The reason an order can be ignored is explained in detail in the documentation for each of the [Order Action](AutoTradeManagment.md#orderactions) functions.

This InternalOrderID can be later used to [cancel the order](#cancelflattenfunctions), [modify the order](#ordermodification), or get the details of an order including its status by using the [sc.GetOrderByOrderID](#getorderbyorderid) function.

When you submit an order and get the **InternalOrderID** for a subsequent order modification or cancellation, most likely you will not need it at that time and you need to remember it. Therefore, assign it to a [Persistent Variable](ACSIL_Members_Functions.md#scgetpersistentint) for use on subsequent calls into the study function. Refer to the code example below.

The **InternalOrderID** member needs to be set when you are modifying an order.

There is one special consideration with the Internal Order ID. This is when an order is split into more than one order when there are multiple OCO Groups used for the Attached Orders. In this case there will be more than one order, each with their own Internal Order ID. The number of orders is equal to the number of OCO Groups used.

For example, if an order has 2 Targets attached to it, the main order will be split into two orders. The other orders will have the [s\_SCTradeOrder::LinkID](#ssctradeorderlinkid) set to this InternalOrderID you get back when submitting the order. To access these other orders, iterate through the order list with the [sc.GetOrderByIndex](#getorderbyindex) function and check the **s\_SCTradeOrder::LinkID** member, to find these other orders.

##### s\_SCNewOrder::InternalOrderID Code Example

```cpp

    //Create a reference to a persistent integer variable for the order ID so it can be modified or canceled. 
    int& InternalOrderID = sc.GetPersistentInt(1);

    // Create an s_SCNewOrder object. 
    s_SCNewOrder NewOrder;
    NewOrder.OrderQuantity = 1;
    NewOrder.OrderType = SCT_MARKET;

    // Buy when the last price crosses the moving average from below.
    if (sc.CrossOver(Last, SimpMovAvgSubgraph) == CROSS_FROM_BOTTOM && sc.GetBarHasClosedStatus() == BHCS_BAR_HAS_CLOSED)
    {
    int Result = sc.BuyEntry(NewOrder);
    if (Result > 0) //If there has been a successful order entry, then draw an arrow at the low of the bar.
    {
        BuyEntrySubgraph[sc.Index] = sc.Low[sc.Index];

        // Remember the order ID for subsequent modification and cancellation
        InternalOrderID = NewOrder.InternalOrderID;
    }
    }
                
```

#### [Type: integer] s\_SCNewOrder::InternalOrderID2

[Link](#sscneworderinternalorderid2) - [Top](#top)

This is the same as InternalOrderID except that it is used to receive the InternalOrderID of the second order when you have submitted an OCO order pair.

#### [Type: SCString] s\_SCNewOrder::TextTag

[Link](#sscnewordertexttag) - [Top](#top)

This is an optional text string that can be set to any free-form text that you want, to help identify an order. It is displayed at the end of the **Order Action Source** field for the order in the **Trade >> Trade Activity Log >> Trade Activity** tab.

It is only displayed in the **Order Action Source** field for the initial order entry. Therefore, you will only see it for the very first line for the order in the Trade Activity Log.

It is automatically prefixed with the Chart Name and the Study Name. So you will have clear identification as to the source of an order. Even without specifying the **TextTag**, the **Order Action Source** will display the originating chart and Study Names for the order.

This field also sets the Text Tag field of the order as well. For further details, refer to [Text Tag](TradeWindow.md#texttag).

**TextTag** also sets the **Note** field in the Trade Activity Log.

#### [Type: integer] s\_SCNewOrder::TimeInForce

[Link](#sscnewordertimeinforce) - [Top](#top)

This member sets the Time in Force for the order. These are the available constants that can be used:

* SCT\_TIF\_DAY
* SCT\_TIF\_GTC
* SCT\_TIF\_GOOD\_TILL\_CANCELED
* SCT\_TIF\_IMMEDIATE\_OR\_CANCEL
* SCT\_TIF\_FILL\_OR\_KILL

This member also sets the Time in Force for any Attached Orders used as well. If this is not specified, then the Time in Force will be **SCT\_TIF\_DAY**.

#### [Type: double] s\_SCNewOrder::Target1Offset

[Link](#sscnewordertarget1offset) - [Top](#top)

#### [Type: double] s\_SCNewOrder::Target2Offset

#### [Type: double] s\_SCNewOrder::Target3Offset

#### [Type: double] s\_SCNewOrder::Target4Offset

#### [Type: double] s\_SCNewOrder::Target5Offset

#### [Type: double] s\_SCNewOrder::Target1Offset\_2

#### [Type: double] s\_SCNewOrder::Target2Offset\_2

#### [Type: double] s\_SCNewOrder::Target3Offset\_2

#### [Type: double] s\_SCNewOrder::Target4Offset\_2

#### [Type: double] s\_SCNewOrder::Target5Offset\_2

The description here applies to all of the above s\_SCNewOrder members.

This specifies the offset for a Target [Attached Order](AttachedOrders.md) (1, 2, 3, 4, 5) to submit along with the parent order. This member only applies when using the **sc.BuyEntry** and **sc.SellEntry** Order Actions.

When this member is set to a nonzero value, then a **Limit** Attached Order will be attached to the main order unless a different order type is specified with the **AttachedOrderTarget#Type** member. If this member is set to 0, the default, a Target Attached order will not be used.

The offset needs to be specified as an actual price value. For example, to specify an actual offset of 2 points from the parent order, use **2.0**. To specify an offset as a number of price ticks, it needs to be specified as NumberOfTicks \* [sc.TickSize](ACSIL_Members_Variables_And_Arrays.md#scticksize). Example: **4\*sc.TickSize**.

When this variable is set, you will notice that the associated Trade Window for the chart that the trading system is applied to, will list this Target 1, 2, 3, 4, 5 order. 1, 2, 3, 4, 5 corresponds to the [OCO Group](AttachedOrders.md#ocogroup) setting on the Attached Orders tab of the Trade Window.

The **Target#Offset\_2** member sets the Attached Order for the second OCO order in an OCO parent order, like SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP.

It is not necessary to set **sc.SupportAttachedOrdersForTrading** to TRUE (1) for these Attached Orders to be used.

For a code example, refer to the **scsf\_TradingExampleWithAttachedOrdersDirectlyDefined** function in the **/ACS\_Source/TradingSystem.cpp** file in the folder that Sierra Chart is installed to.

When you are modifying one of these Attached Order prices, you will not use the **Target#Offset** members, instead you will use the **Price1** member instead and [modify the individual Attached Order](#ordermodification) by specifying the [InternalOrderID](#sscneworderinternalorderid) of the order. After the order is initially submitted, you will need to specify the actual order price you want to modify the order to. You will no longer use an offset.

#### [Type: integer] s\_SCNewOrder::Target1InternalOrderID

[Link](#sscnewordertarget1internalorderid) - [Top](#top)

#### [Type: integer] s\_SCNewOrder::Target2InternalOrderID

#### [Type: integer] s\_SCNewOrder::Target3InternalOrderID

#### [Type: integer] s\_SCNewOrder::Target4InternalOrderID

#### [Type: integer] s\_SCNewOrder::Target5InternalOrderID

#### [Type: integer] s\_SCNewOrder::Target1InternalOrderID\_2

#### [Type: integer] s\_SCNewOrder::Target2InternalOrderID\_2

#### [Type: integer] s\_SCNewOrder::Target3InternalOrderID\_2

#### [Type: integer] s\_SCNewOrder::Target4InternalOrderID\_2

#### [Type: integer] s\_SCNewOrder::Target5InternalOrderID\_2

This is set to the Internal Order ID of the Target 1, 2, 3, 4, 5 Attached Order, after you call one of the Order Action functions and the order has been accepted by the Auto-Trade Management System.

The **Target#InternalOrderID\_2** members are for the Attached Orders for the second OCO order in an OCO parent order, like SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP.

#### [Type: double] s\_SCNewOrder::Stop1Offset

[Link](#sscneworderstop1offset) - [Top](#top)

#### [Type: double] s\_SCNewOrder::Stop2Offset

#### [Type: double] s\_SCNewOrder::Stop3Offset

#### [Type: double] s\_SCNewOrder::Stop4Offset

#### [Type: double] s\_SCNewOrder::Stop5Offset

#### [Type: double] s\_SCNewOrder::Stop1Offset\_2

#### [Type: double] s\_SCNewOrder::Stop2Offset\_2

#### [Type: double] s\_SCNewOrder::Stop3Offset\_2

#### [Type: double] s\_SCNewOrder::Stop4Offset\_2

#### [Type: double] s\_SCNewOrder::Stop5Offset\_2

The description here applies to all of the above members.

This specifies the offset for a Stop [Attached Order](AttachedOrders.md) (1, 2, 3, 4, 5) to submit along with the parent order. This member only applies when using the **sc.BuyEntry** and **sc.SellEntry** Order Actions.

When this member is set to a nonzero value, then a **Stop** Attached Order will be attached to the main order unless a different order type is specified with the **AttachedOrderStop#Type** member. When this member is set to a zero value, then a Stop Attached order will not be used.

The offset needs to be specified as an actual price value. For example, to specify an actual offset of 2 points from the parent order, use **2.0**. To specify an offset as a number of price ticks, it needs to be specified as NumberOfTicks \* [sc.TickSize](ACSIL_Members_Variables_And_Arrays.md#scticksize). Example: **4\*sc.TickSize**.

When this variable is set, you will notice that the associated Trade Window for the chart that the trading system is applied to, will list this Stop 1, 2, 3, 4, 5 order. 1, 2, 3, 4, 5 corresponds to the [OCO Group](AttachedOrders.md#ocogroup) setting on the Attached Orders tab of the Trade Window.

The **Stop#Offset\_2** member sets the Attached Order for the second OCO order in an OCO parent order, like SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP.

It is not necessary to set **sc.SupportAttachedOrdersForTrading** to TRUE (1) for these Attached Orders to be used.

For a code example, refer to the **scsf\_TradingExampleWithAttachedOrdersDirectlyDefined** function in the **/ACS\_Source/TradingSystem.cpp** file in the folder that Sierra Chart is installed to.

When you are modifying one of these Attached Order prices, you will not use the **Stop#Offset**  members, instead you will use the **Price1** member instead and [modify the individual Attached Order](#ordermodification) by specifying the [InternalOrderID](#sscneworderinternalorderid) of the order. After the order is initially submitted, you will need to specify the actual order price you want to modify the order to. You will no longer use an offset.

#### [Type: double] s\_SCNewOrder::StopAllOffset

[Link](#sscneworderstopalloffset) - [Top](#top)

#### [Type: double] s\_SCNewOrder::StopAllOffset\_2

**StopAllOffset** works identically to [Stop#Offset](#sscneworderstop1offset), except that the [OCO Group](AttachedOrders.md#ocogroup) is **All Groups**. When using **StopAllOffset**, the **Stop#Offset** members are ignored.

**StopAllOffset** cannot be used if there are no Target orders set since the Stop orders will depend on the Target orders for the order Quantity for each of the corresponding attached stops. In this case use [Stop1Offset](#sscneworderstop1offset) instead.

The **StopAllOffset\_2** member is for the Stop Attached Order for the second OCO order in an OCO parent order, like SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP.

#### [Type: double] s\_SCNewOrder::Target1Price

[Link](#sscnewordertarget1price) - [Top](#top)

#### [Type: double] s\_SCNewOrder::Target2Price

#### [Type: double] s\_SCNewOrder::Target3Price

#### [Type: double] s\_SCNewOrder::Target4Price

#### [Type: double] s\_SCNewOrder::Target5Price

#### [Type: double] s\_SCNewOrder::Target1Price\_2

#### [Type: double] s\_SCNewOrder::Target2Price\_2

#### [Type: double] s\_SCNewOrder::Target3Price\_2

#### [Type: double] s\_SCNewOrder::Target4Price\_2

#### [Type: double] s\_SCNewOrder::Target5Price\_2

The description here applies to all of the above members.

These variables allow you to specify an actual Target price for an Attached Order rather than an offset.

These variables specify the price for a Target Attached Order (1, 2, 3, 4, 5) to submit along with the parent order. This member only applies to the **sc.BuyEntry** and **sc.SellEntry** Order Actions.

When the variable is set to a nonzero value, then a Limit Attached Order will be attached to the main parent order. Otherwise, it will not be. Use an actual price value.

When this variable is set, you will notice that the associated Trade Window for the chart that the trading system is applied to, will list this Target 1, 2, 3, 4, 5 order.

By default the Target order is a **Limit** order type. 1, 2, 3, 4, 5 in the member name corresponds to the **OCO Group** setting on the Attached Orders tab of the Trade Window.

The **Target#Price\_2** members set the Attached Order for the second OCO order in an OCO parent order, like SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP.

It is not necessary to set **sc.SupportAttachedOrdersForTrading** to TRUE (1) for these Attached Orders to be used.

For a code example, refer to the **scsf\_TradingExampleWithAttachedOrdersUsingActualPrices** function in the **/ACS\_Source/TradingSystem.cpp** file in the folder that Sierra Chart is installed to.

Although you specify an actual Target price with these variables, this price is converted to an offset based upon the parent order price or based upon the expected fill price of a parent Market order. Additionally, when there is a fill of the parent order, the Target orders will be adjusted to maintain the original specified offset relative to the fill price of the parent. Therefore, the actual price may change slightly.

For example, if the parent order price is 100 or is expected to fill at 100, you specify a Target price of 105, and the parent order fills at 100.50, then the Target will be adjusted to 105.50 even though you specified 105 originally. The offset at the time of order submission was 5, so that offset is maintained on a fill of the parent. Therefore, you might have to modify the order after the status changes to **Open** to make sure it has the price you originally specified.

When you are modifying one of these Attached Order prices, you will not use the **Target#Price** members, instead you will use the **Price1** member instead.

#### [Type: double] s\_SCNewOrder::Stop1Price

[Link](#sscneworderstop1price) - [Top](#top)

#### [Type: double] s\_SCNewOrder::Stop2Price

#### [Type: double] s\_SCNewOrder::Stop3Price

#### [Type: double] s\_SCNewOrder::Stop4Price

#### [Type: double] s\_SCNewOrder::Stop5Price

#### [Type: double] s\_SCNewOrder::Stop1Price\_2

#### [Type: double] s\_SCNewOrder::Stop2Price\_2

#### [Type: double] s\_SCNewOrder::Stop3Price\_2

#### [Type: double] s\_SCNewOrder::Stop4Price\_2

#### [Type: double] s\_SCNewOrder::Stop5Price\_2

The description here applies to all of the above members.

These variables allow you to specify an actual Stop price for an Attached Order rather than an offset.

These variables specify the price for a Stop Attached Order (1, 2, 3, 4, 5) to submit along with the parent order. This member only applies to the **sc.BuyEntry** and **sc.SellEntry** Order Actions.

When the variable is set to a nonzero value, then a Stop Attached Order will be attached. Otherwise, it will not. Use an actual price value.

When this variable is set, you will notice that the associated Trade Window for the chart that the trading system is applied to, will list this Stop 1, 2, 3, 4, 5 order.

By default the Stop order is a **Stop** order type. 1, 2, 3, 4, 5 in the member name corresponds to the **OCO Group** setting on the Attached Orders tab of the Trade Window.

The **Stop#Price\_2** members set the Attached Order for the second OCO order in an OCO parent order, like SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP.

It is not necessary to set **sc.SupportAttachedOrdersForTrading** to TRUE (1) for these Attached Orders to be used. This is implied when setting one of these members.

For a code example, refer to the **scsf\_TradingExampleWithAttachedOrdersUsingActualPrices** function in the **/ACS\_Source/TradingSystem.cpp** file in the folder that Sierra Chart is installed to.

Although you specify an actual Stop price with these variables, this price is converted to an offset based upon the parent order price or based upon the expected fill price of a parent Market order. Additionally, when there is a fill of the parent order, the Stop orders will be adjusted to maintain the original specified offset relative to the fill price of the parent. Therefore, the actual price may change slightly.

For example, if the parent order price is 100 or is expected to fill at 100, you specify a Stop price of 95, and the parent order fills at 100.50, then the Stop will be adjusted to 95.50 even though you specified 95 originally. The offset at the time of order submission was 5, so that offset is maintained on a fill of the parent. Therefore, you might have to modify the order after the status changes to **Open**  to make sure it has the price you originally specified.

When you are modifying one of these Attached Order prices, you will not use the **s\_SCNewOrder::Stop#Price** members, instead you will use the **Price1** member instead.

#### [Type: double] s\_SCNewOrder::StopAllPrice

[Link](#sscneworderstopallprice) - [Top](#top)

#### [Type: double] s\_SCNewOrder::StopAllPrice\_2

**StopAllPrice** works idetically to [Stop#Price](#sscneworderstop1price), except that the OCO Group is **All Groups**. When using **StopAllPrice**, **Stop#Offset** members are ignored.

The **StopAllPrice\_2** member is for the Stop Attached Order for the second OCO order in an OCO parent order, like SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP.

#### [Type: integer] s\_SCNewOrder::Stop1InternalOrderID

[Link](#sscneworderstop1internalorderid) - [Top](#top)

#### [Type: integer] s\_SCNewOrder::Stop2InternalOrderID

#### [Type: integer] s\_SCNewOrder::Stop3InternalOrderID

#### [Type: integer] s\_SCNewOrder::Stop4InternalOrderID

#### [Type: integer] s\_SCNewOrder::Stop5InternalOrderID

#### [Type: integer] s\_SCNewOrder::StopAllInternalOrderID

#### [Type: integer] s\_SCNewOrder::Stop1InternalOrderID\_2

#### [Type: integer] s\_SCNewOrder::Stop2InternalOrderID\_2

#### [Type: integer] s\_SCNewOrder::Stop3InternalOrderID\_2

#### [Type: integer] s\_SCNewOrder::Stop4InternalOrderID\_2

#### [Type: integer] s\_SCNewOrder::Stop5InternalOrderID\_2

#### [Type: integer] s\_SCNewOrder::StopAllInternalOrderID\_2

This is set to the Internal Order ID of the Stop 1, 2, 3, 4, 5 Attached Order after calling one of the Order Action functions and the order has been accepted by the Auto-Trade Management System.

In the case when you are using **StopAllOffset**, then for every Target# being used, the corresponding **Stop#InternalOrderID** will be set, since there will be multiple Stop orders, one for each Target#.

The **StopAllInternalOrderID** member is set when using **StopAllOffset** to specify the offset for the Stop order or orders. It will be set to the **Link Internal Order ID** used by all of the Stop orders. The **Link Internal Order ID (Link ID)** is displayed in the **Trade >> Trade Orders Window**.

When there is an Attached Order that uses the OCO Group **All Groups** which occurs when using **StopAllOffset**, and there are multiple Target orders, this Attached Order will be split up into multiple orders to match the number of Target orders. In the case when there are multiple Stop orders, then **StopAllInternalOrderID** is set to the Internal Order ID of the first Stop order. This Internal Order ID is also the same as the **Link Internal Order ID** for the multiple Stop orders which are linked together.

In the case when **StopAllInternalOrderID**  is set, **Stop1InternalOrderID#**(1 through 5) will also be set for each of the multiple orders resulting from the split as explained above.

#### [Type: unsigned integer] s\_SCNewOrder::OCOGroup1Quantity

[Link](#sscneworderocogroup1quantity) - [Top](#top)

#### [Type: unsigned integer] s\_SCNewOrder::OCOGroup2Quantity

#### [Type: unsigned integer] s\_SCNewOrder::OCOGroup3Quantity

#### [Type: unsigned integer] s\_SCNewOrder::OCOGroup4Quantity

#### [Type: unsigned integer] s\_SCNewOrder::OCOGroup5Quantity

Set this to the Order Quantity you want for the Target and Stop Attached Orders 1, 2, 3, 4, 5 respectively. Keep in mind that the total of all the Attached Order OCO Groups must equal the quantity of the parent order. If they do not, the order will be rejected. This is an optional variable to set and will be automatically set if left at the default of 0.

#### [Type: char] s\_SCNewOrder::AttachedOrderTarget1Type

[Link](#sscneworderattachedordertarget1type) - [Top](#top)

#### [Type: char] s\_SCNewOrder::AttachedOrderTarget2Type

#### [Type: char] s\_SCNewOrder::AttachedOrderTarget3Type

#### [Type: char] s\_SCNewOrder::AttachedOrderTarget4Type

#### [Type: char] s\_SCNewOrder::AttachedOrderTarget5Type

By default when you specify an Attached Order Target Price or Offset, the order type is **Limit**. Use any of these members to change the order type for the corresponding Target OCO group. The possible order types are listed below:

* SCT\_ORDERTYPE\_LIMIT
* SCT\_ORDERTYPE\_LIMIT\_CHASE
* SCT\_ORDERTYPE\_LIMIT\_TOUCH\_CHASE
* SCT\_ORDERTYPE\_MARKET\_IF\_TOUCHED
* SCT\_ORDERTYPE\_MARKET\_IF\_TOUCHED\_CLIENT\_SIDE
* SCT\_ORDERTYPE\_LIMIT\_IF\_TOUCHED\_CLIENT\_SIDE

For complete documentation for these Order Types, refer to [Order Types](OrderTypes.md). The Order Types documentation is useful to understand the related structure members for these order types.

#### [Type: char] s\_SCNewOrder::AttachedOrderStop1Type

[Link](#sscneworderattachedorderstop1type) - [Top](#top)

#### [Type: char] s\_SCNewOrder::AttachedOrderStop2Type

#### [Type: char] s\_SCNewOrder::AttachedOrderStop3Type

#### [Type: char] s\_SCNewOrder::AttachedOrderStop4Type

#### [Type: char] s\_SCNewOrder::AttachedOrderStop5Type

#### [Type: char] s\_SCNewOrder::AttachedOrderStopAllType

By default when you specify an Attached Order Stop Price or Stop Offset, the order type is **Stop**. Use any of these members to change the order type for the corresponding Stop OCO group. The possible order types are listed below:

* SCT\_ORDERTYPE\_STOP
* SCT\_ORDERTYPE\_STOP\_LIMIT
* SCT\_ORDERTYPE\_TRAILING\_STOP
* SCT\_ORDERTYPE\_TRAILING\_STOP\_LIMIT
* SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS
* SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_LIMIT\_3\_OFFSETS
* SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP
* SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP\_LIMIT
* SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP
* SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP\_LIMIT
* SCT\_ORDERTYPE\_BID\_ASK\_QUANTITY\_TRIGGERED\_STOP
* SCT\_ORDERTYPE\_TRADE\_VOLUME\_TRIGGERED\_STOP
* SCT\_ORDERTYPE\_STOP\_WITH\_BID\_ASK\_TRIGGERING
* SCT\_ORDERTYPE\_STOP\_WITH\_LAST\_TRIGGERING
* SCT\_ORDERTYPE\_TRADE\_VOLUME\_TRIGGERED\_STOP\_LIMIT
* SCT\_ORDERTYPE\_STOP\_LIMIT\_CLIENT\_SIDE
* SCT\_ORDERTYPE\_TRIGGERED\_LIMIT: The Trigger price offset is set with the **s\_SCNewOrder::TriggeredLimitOrStopAttachedOrderTriggerOffset** member.
* SCT\_ORDERTYPE\_TRIGGERED\_STOP: The Trigger price offset is set with the **s\_SCNewOrder::TriggeredLimitOrStopAttachedOrderTriggerOffset** member.

For complete documentation for these Order Types, refer to [Order Types](OrderTypes.md). The Order Types documentation is useful to understand the related structure members for these order types.

#### [Type: double] s\_SCNewOrder::MaximumChaseAsPrice

[Link](#sscnewordermaximumchaseasprice) - [Top](#top)

When using a Limit Chase order type for the main order, not an Attached Order, this specifies the maximum chase amount.

Specify the maximum chase amount as a price value and not in Ticks. For example, if you want the maximum chase amount to be 2.0, then set this to 2.0.

#### [Type: double] s\_SCNewOrder::AttachedOrderMaximumChase

[Link](#sscneworderattachedordermaximumchase) - [Top](#top)

When using a Limit Chase order type for a Target Attached Order, this specifies the maximum chase amount.

Specify this as a price value, not in Ticks. For example, if you want the maximum chase amount to be 2.0, then set this to 2.0.

This is a common setting and applies to all OCO Attached Order groups.

#### [Type: double] s\_SCNewOrder::TrailStopStepPriceAmount

[Link](#sscnewordertrailstopsteppriceamount) - [Top](#top)

When using the SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP, SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP\_LIMIT, SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP, SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP\_LIMIT order types for a Stop Attached Order, this variable specifies the step amount as a price value.

Do not specify this in Ticks. This is a common setting and applies to all OCO Attached Order groups.

In the case of when using one of these order types as the main order and not an Attached Order, then the step amount can only be specified with the SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP and SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP\_LIMIT order types, and it needs to be specified using the [Price2](#sscneworderprice2) variable.

#### [Type: double] s\_SCNewOrder::AttachedOrderStop1\_TriggeredTrailStopTriggerPriceOffset

[Link](#sscneworderattachedorderstop1triggeredtrailstoptriggerpriceoffset) - [Top](#top)

#### [Type: double] s\_SCNewOrder::AttachedOrderStop1\_TriggeredTrailStopTriggerPriceOffset

#### [Type: double] s\_SCNewOrder::AttachedOrderStop2\_TriggeredTrailStopTriggerPriceOffset

#### [Type: double] s\_SCNewOrder::AttachedOrderStop3\_TriggeredTrailStopTriggerPriceOffset

#### [Type: double] s\_SCNewOrder::AttachedOrderStop4\_TriggeredTrailStopTriggerPriceOffset

#### [Type: double] s\_SCNewOrder::AttachedOrderStop5\_TriggeredTrailStopTriggerPriceOffset

The description here applies to all of the above structure members.

These variables allow you to set the trigger offset for the following Triggered Trailing Stop Attached Order types: **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS**, **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_LIMIT\_3\_OFFSETS**, **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP**, **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP\_LIMIT**.

This corresponds to the **Trigger Offset** setting for a Triggered Trailing Stop on the [Targets](TradeWindow.md#attachedorders) tab of the [Trade Window](TradeWindow.md).

These variables (1, 2, 3, 4, 5) apply to the 5 different OCO groups available for Attached Orders.

Specify this as an actual price value, *not* in Ticks.

#### [Type: double] s\_SCNewOrder::AttachedOrderStop1\_TriggeredTrailStopTrailPriceOffset

[Link](#sscneworderattachedorderstop1triggeredtrailstoptrailpriceoffset) - [Top](#top)

#### [Type: double] s\_SCNewOrder::AttachedOrderStop1\_TriggeredTrailStopTrailPriceOffset

#### [Type: double] s\_SCNewOrder::AttachedOrderStop2\_TriggeredTrailStopTrailPriceOffset

#### [Type: double] s\_SCNewOrder::AttachedOrderStop3\_TriggeredTrailStopTrailPriceOffset

#### [Type: double] s\_SCNewOrder::AttachedOrderStop4\_TriggeredTrailStopTrailPriceOffset

#### [Type: double] s\_SCNewOrder::AttachedOrderStop5\_TriggeredTrailStopTrailPriceOffset

The description here applies to all of the above structure members.

These variables allow you to set the trailing offset for the following Triggered Trailing Stop Attached Order types: **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS**, **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_LIMIT\_3\_OFFSETS**, **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP**, **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP\_LIMIT**.

This corresponds to the **Trail Offset** setting for a Triggered Trailing Stop on the [Targets](TradeWindow.md#attachedorders) tab of the [Trade Window](TradeWindow.md).

These variables (1, 2, 3, 4, 5) apply to the 5 different OCO groups available for Attached Orders.

Specify this as an actual price value, *not* in Ticks.

#### [Type: integer] s\_SCNewOrder::MoveToBreakEven.Type

[Link](#sscnewordermovetobreakeventype) - [Top](#top)

When you have set a Stop Attached Order to an order, then this member allows you to set a move to breakeven action to be applied to the Stop orders.

This can be set to one of the following integer constants:

* MOVETO\_BE\_ACTION\_TYPE\_OFFSET\_TRIGGERED
* MOVETO\_BE\_ACTION\_TYPE\_OCO\_GROUP\_TRIGGERED
* MOVETO\_BE\_ACTION\_TYPE\_TRAIL\_TO\_BREAKEVEN
* MOVETO\_BE\_ACTION\_TYPE\_OFFSET\_TRIGGERED\_TRAIL\_TO\_BREAKEVEN

For documentation for the move to breakeven action that can be applied to a stop, refer to [Move to Breakeven For Stop](AttachedOrders.md#movebreakevenforstop) on the Attached Orders page.

This is a common setting and applies to all Stop Attached Orders set on the main order.

Also, refer to [s\_SCNewOrder::MoveToBreakEven.BreakEvenLevelOffsetInTicks](#sscnewordermovetobreakevenbreakevenleveloffsetinticks), [s\_SCNewOrder::MoveToBreakEven.TriggerOffsetInTicks](#sscnewordermovetobreakeventriggeroffsetinticks), [s\_SCNewOrder::MoveToBreakEven.TriggerOCOGroup](#sscnewordermovetobreakeventriggerocogroup).

##### Example Code

```cpp

    //Set up a move to breakeven action for the common stop.When Target 1 is filled, the order will be moved to breakeven +1
    NewOrder.MoveToBreakEven.Type = MOVETO_BE_ACTION_TYPE_OCO_GROUP_TRIGGERED;
    NewOrder.MoveToBreakEven.BreakEvenLevelOffsetInTicks= 1;
    NewOrder.MoveToBreakEven.TriggerOCOGroup= OCO_GROUP_1; 
                
```

#### [Type: integer] s\_SCNewOrder::MoveToBreakEven.BreakEvenLevelOffsetInTicks

[Link](#sscnewordermovetobreakevenbreakevenleveloffsetinticks) - [Top](#top)

When using a move to breakeven action on a Stop Attached Order, then this sets the **Breakeven Level Offset**. This is specified in Ticks. For a complete description, refer to [Move to Breakeven For Stop](AttachedOrders.md#movebreakevenforstop) on the Attached Orders page.

#### [Type: integer] s\_SCNewOrder::MoveToBreakEven.TriggerOffsetInTicks

[Link](#sscnewordermovetobreakeventriggeroffsetinticks) - [Top](#top)

When using a move to breakeven action on a Stop Attached Order, then this sets the **Trigger Offset**. This is specified in Ticks. For a complete description, refer to [Move to Breakeven For Stop](AttachedOrders.md#movebreakevenforstop) on the Attached Orders page.

#### [Type: integer] s\_SCNewOrder::MoveToBreakEven.TriggerOCOGroup

[Link](#sscnewordermovetobreakeventriggerocogroup) - [Top](#top)

When using a move to breakeven action on a Stop Attached Order, then this sets the **Trigger OCO Group Number**. This can be set to OCO\_GROUP\_1, OCO\_GROUP\_2, OCO\_GROUP\_3, OCO\_GROUP\_4, or OCO\_GROUP\_5. For a complete description, refer to [Move to Breakeven For Stop](AttachedOrders.md#movebreakevenforstop) on the Attached Orders page.

#### [Type: SCString] s\_SCNewOrder::Symbol

[Link](#sscnewordersymbol) - [Top](#top)

When submitting an order for a symbol different than the chart the trading study is applied to, set this member to that symbol. Otherwise, this member must *not be set*.

This must only be specified when submitting an order for a symbol different than the chart the trading study is applied to.

For more information, refer to [Submitting and Managing Orders for Different Symbol and/or Trade Account](#submittingordersdifferentsymbolaccount).

#### [Type: SCString] s\_SCNewOrder::TradeAccount

[Link](#sscnewordertradeaccount) - [Top](#top)

When submitting an order for a Trade Account different than selected on the Trade Window for the chart the trading study is applied to, set this member to that Trade Account identifier. These are the very same Trade Account identifiers listed on the Trade Window [Trade Accounts list](TradeWindow.md#selectingtradeaccount).

This must only be specified when submitting an order for a different Trade Account than selected on the Trade Window for the chart the trading study is applied to.

For more information, refer to [Submitting and Managing Orders for Different Symbol and/or Trade Account](#submittingordersdifferentsymbolaccount).

#### [Type: int] s\_SCNewOrder::SubmitAsHeldOrder

[Link](#sscnewordersubmitasheldorder) - [Top](#top)

Set this variable to 1 to cause the order to be submitted in a held state. It will be held on the Sierra Chart side.

It can be sent through the [Trade Orders Window](TradeStatusWindows.md#tradeorders) by selecting the order in the list and using the **Send Held** menu command.

#### [Type: function] s\_SCNewOrder::Reset()

[Link](#sscneworderreset) - [Top](#top)

The **Reset** function resets all of the variables/members of the s\_SCNewOrder structure object that you have defined in your study function, back to the defaults. This is useful if you wish to submit or modify another order and want to have the structure object reset back to the defaults.

## Attached Orders and OCO Main Order Types

[Link](#attachedordersocomainordertypes) - [Top](#top)

When you have specified Attached Orders by using Target#Offset, Stop#Offset, Target#Price, and/or Stop#Price members of s\_SCNewOrder, and the **OrderType** member, which sets the parent order type, is set to one of the following order types:

* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP**
* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_LIMIT\_SELL\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_OCO\_BUY\_LIMIT\_SELL\_LIMIT**

Then the Attached Orders will be attached to each of the 2 orders in the OCO order pair. So you will have 2 sets of Attached Orders.

## Modifying Orders in OCO Order Types

[Link](#modifyingocoorders) - [Top](#top)

When you submit an order using one of the OCO order types that are listed below, there are two independent orders submitted. Although these orders are in an OCO group. When one of them is filled or canceled, the other one will be canceled as well. Each of these orders exist as independent orders that are modified separately in the case when you need to modify the price or quantity of one of these orders. When using the [sc.ModifyOrder](#ordermodification) function, you will need to specify the Internal Order ID of the specific order to modify, and set either the new price and/or quantity. When setting the price you will always use the **s\_SCNewOrder::Price1** member no matter which order in the OCO group you are modifying the price of.

* **SCT\_ORDERTYPE\_OCO\_LIMIT\_STOP**
* **SCT\_ORDERTYPE\_OCO\_LIMIT\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP**
* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_LIMIT\_SELL\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_OCO\_BUY\_LIMIT\_SELL\_LIMIT**

## Submitting and Managing Orders for Different Symbol and/or Trade Account

[Link](#submittingordersdifferentsymbolaccount) - [Top](#top)

It is supported to submit an order, modify that order and cancel that order for a different Symbol and/or Trade Account than the chart the trading study is applied to.

The standard method for trading a different Symbol than the Symbol for the chart bars themselves, is by setting the [Trade and Current Quote Symbol](ChartSettings.md#tradeandcurrentquotesymbol) to the Symbol that you want to submit, modify, and cancel orders for. This setting is in **Chart >> Chart Settings**.

The ACSIL variable for this is [sc.TradeAndCurrentQuoteSymbol](ACSIL_Members_Variables_And_Arrays.md#sctradeandcurrentquotesymbol).

However, it is possible to directly specify a different Symbol and/or Trade Account when submitting an order from ACSIL. This section documents this.

This order must be submitted by using the [sc.BuyOrder](#buyentry) or the [sc.SellOrder](#sellentry) functions. *Note: You cannot use the **sc.BuyEntry**, **sc.SellEntry**, **sc.BuyExit**, or **sc.SellExit** functions*.

Attached Orders are supported with these functions. Although only 1 Target and/or 1 Stop is supported when submitting an order for a different Symbol and/or Trade Account.

When submitting an order for a different Symbol and/or Trade Account, the trading is *unmanaged*. So therefore the [Automated Trading Management Variables](AutoTradeManagment.md#variables) do not apply. However, the following still apply and can reject orders:

* [SCT\_SKIPPED\_DOWNLOADING\_HISTORICAL\_DATA](#ignoredordererror)
* [SCT\_SKIPPED\_FULL\_RECALC](#ignoredordererror): To avoid this error in your automated trading system study, add an *if* check for **sc.IsFullRecalculation**, after the **sc.SetDefaults** code block. When **sc.IsFullRecalculation** is true, then return from the study function to prevent any order actions from occurring.
* [SCT\_SKIPPED\_INVALID\_INDEX\_SPECIFIED](#ignoredordererror)
* [SCT\_SKIPPED\_TOO\_MANY\_NEW\_BARS\_DURING\_UPDATE](#ignoredordererror)
* [SCTRADING\_ATTACHED\_ORDER\_OFFSET\_NOT\_SUPPORTED\_WITH\_MARKET\_PARENT](#ignoredordererror)
* [SCTRADING\_UNSUPPORTED\_ATTACHED\_ORDER](#ignoredordererror)
* [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice)
* [Trade >> Auto Trading Enabled](TradeMenu.md#autotradingenabled)

If the Symbol for the order is *different* than the Symbol the chart the trading study is applied to, then it is necessary to set the [s\_SCNewOrder::Symbol](#sscneworder) member to the Symbol that you want to submit an order for.

If the Trade Account for the order is *different* than the selected Trade Account for the chart the trading study is applied to, then set the [s\_SCNewOrder::TradeAccount](#sscneworder) to the Trade Account for the order. Or leave it blank or set it to [sc.SelectedTradeAccount](ACSIL_Members_Variables_And_Arrays.md#scselectedtradeaccount).

To modify the order use the [sc.ModifyOrder](#ordermodification) function like it would normally be used.

To cancel the order use the [sc.CancelOrder](#cancelflattenfunctions) function like it would normally be used.

To cause a study function to be called any time there is any order activity for the order for a different Symbol and/or Trade Account set the **sc.ReceiveNotificationsForChangesToOrdersPositionsForAnySymbol** variable to 1 in the [sc.SetDefaults](ACSIL_Members_Variables_And_Arrays.md#scsetdefaults) code block.

To get the current Trade Position data for a different Symbol and Trade Account use the function [sc.GetTradePositionForSymbolAndAccount()](#scgettradepositionforsymbolandaccount).

For a complete code example that uses non-simulated trading, refer to the **scsf\_TradingExampleOrdersForDifferentSymbolAndAccount** function in the **/ACS\_Source/TradingSystem.cpp** file in the folder that Sierra Chart is installed to.

### Data Feed Connection and Streaming Data Required

[Link](#datafeedconnectionandstreamingdatarequired) - [Top](#top)

When submitting an order for a different Symbol and Trade Account and Sierra Chart is in Trade Simulation Mode, it is necessary for Sierra Chart to be [connected to the data feed](FileMenu.md#connecttodatafeed) and for real-time or delayed data to be recei0ved for the symbol for the order to be able to be filled.

### Understanding when Unmanaged Automated Trading Applies

[Link](#understandingwhenunmanagedautotradingapplies) - [Top](#top)

When submitting an order for a different Symbol and/or Trade Account compared to the chart the automated trading study is applied to, it is necessary to use the [sc.BuyOrder](#buyentry) and the [sc.SellOrder](#buyentry) functions. These functions can also be used for trading the same Symbol of the chart.

It is important to understand how Sierra Chart determines that a different Symbol and/or Trade Account is specified and therefore that *unmanaged automated trading applies* to that order.

When the [s\_SCNewOrder::Symbol](#sscneworder) member is set to a symbol which differs from **Chart >> Chart Settings >> Symbol** or to the **Trade and Current Quote Symbol** if that *is set*, for the chart the trading system study is applied to, then unmanaged automated trading applies.

When the [s\_SCNewOrder::TradeAccount](#sscneworder) member is set to a different Trade Account compared to the Trade Account on the Trade Window for the chart the trading system study is applied to, then unmanaged automated trading applies. To see what Trade Account the Trade Window is set to, refer to [Selecting Trade Account](TradeWindow.md#selectingtradeaccount).

### Symbol Settings for Symbol Being Traded

[Link](#symbolsettingsforsymbolbeingtraded) - [Top](#top)

When trading a symbol, it is essential that the symbol or symbol pattern exists in the [Global Symbol Settings](GlobalSymbolSettings.md) and has the **Price Display Format** and **Tick Size** properly set for the symbol. These settings are *essential* and used during order submission.

When using a symbol pattern it is necessary to enable the **Use Pattern Matching** option in the Global Symbol Settings for the symbol. Otherwise, the pattern matching cannot function properly.

### Stop-Limit Order Prices

[Link](#stoplimitorderprices) - [Top](#top)

When submitting an order for a different Symbol and/or Trade Account, in the case of when using Stop-Limit orders, then the Limit *must* be set with the [s\_SCNewOrder::Price2](#sscneworderprice2) member. It will not be automatically set.

In the case of Stop-Limit Attached Orders, the Limit price is set by specifying an offset with the [s\_SCNewOrder::StopLimitOrderLimitOffset](#sscneworderstoplimitorderlimitoffset) member. This needs to be specified as an actual offset price value and not in ticks.

## Getting Order Information

[Link](#gettingorderinformation) - [Top](#top)

### Determining the Status of an Order

[Link](#determiningthestatusofanorder) - [Top](#top)

To determine the status of an order it is first necessary to obtain the Trade Order data with the [sc.GetOrderByOrderID](#getorderbyorderid) or [sc.GetOrderByIndex](#getorderbyindex) functions.

The current order status can be determined with the [s\_SCTradeOrder::OrderStatusCode](#ssctradeorderorderstatuscode) structure member.

### Determining if an Order is an Attached Order

[Link](#determiningifanorderisanattachedorder) - [Top](#top)

To determine if an order is an Attached Order it is first necessary to obtain the Trade Order data with the [sc.GetOrderByOrderID](#getorderbyorderid) or [sc.GetOrderByIndex](#getorderbyindex) functions.

If the [s\_SCTradeOrder::ParentInternalOrderID](#ssctradeorderparentinternalorderid) structure member is nonzero, then the order is an Attached Order.

### Accessing Orders which are No Longer Available

[Link](#accessingorderswhicharenolongeravailable) - [Top](#top)

When a Trade Order is Canceled, Rejected, or has Filled (considered no longer in a working state), there is no guarantee of being able to get the data or details of this Order after one of these conditions has been met and after a period of time.

It is normal that external Trading services that Sierra Chart works with no longer make the order data available if the order is no longer working.

For orders that are no longer working, Sierra Chart does not maintain this order data across Sierra Chart sessions.

After a period of time, Sierra Chart will [automatically clear](TradeStatusWindows.md#autoclearingorders) order data for orders that are not working.

It is necessary to get the Trade Order details/data, shortly after the Trade Order is no longer working If you want to be able to access this data. Refer to [sc.GetOrderByOrderID](#getorderbyorderid).

The Sierra Chart study function will be called any time there is a change in Status of the order.

If the Trade Order data is no longer available, then you will know that the order is no longer working. If the order has filled, it is possible to access this order fill data at any time. So long as it is loaded into a chart (Refer to [Understanding and Setting the Start Date-Time for a Trades List](TradeActivityLog.md#understandingandsettingthestartdatetimeforatradeslist).

To get the order fills, refer to [sc.GetOrderFillEntry()](#scgetorderfillentry).

### sc.GetOrderByIndex

[Link](#getorderbyindex) - [Top](#top)

int **sc.GetOrderByIndex**(int **OrderIndex**, s\_SCTradeOrder& **r\_SCTradeOrder**);

**Description:** The **sc.GetOrderByIndex** function returns the order fields of an order based on an index value. The index value is passed through the **OrderIndex** parameter. This is a zero based index.

Beginning from 0, you can increment the OrderIndex parameter by 1 and keep calling **sc.GetOrderByIndex** until the function returns [**SCTRADING\_ORDER\_ERROR**](#sctradingordererror) indicating there are no more orders.

The function only returns orders that have the same Symbol and Trade Account as the chart the trading study is applied to. To get orders for other Symbols and Trade Accounts, use [sc.GetOrderForSymbolAndAccountByIndex()](#scgetorderforsymbolandaccountbyindex).

The order fields returned are the same as what you see listed in the [Trade >> Trade Orders Window](TradeStatusWindows.md#tradeorders).

When calling the **sc.GetOrderByIndex** function and **Trade >> Trade Simulation Mode On** is enabled or **sc.SendOrdersToTradeService** is false, then only *simulated* orders are returned.

If **Trade >> Trade Simulation Mode On** is disabled and **sc.SendOrdersToTradeService** is true, then only *non-simulated* orders are returned.

When an order is no longer working, it is automatically cleared from the Trade Orders List in Sierra Chart after a period of time. So therefore the order can no longer be retrieved with this function. For complete details, refer to [Automatic Clearing of Orders](TradeStatusWindows.md#autoclearingorders).

In the case where the trade order is no longer available to be retrieved with the **sc.GetOrderByIndex** function, and you need to determine whether it has filled, use the [sc.GetOrderFillEntry()](#scgetorderfillentry) function instead.

This function is less efficient than the function [sc.GetOrderByOrderID](#getorderbyorderid). It is most efficient to get an order by its Internal Order ID. To find an order at a particular index, orders have to be iterated through for each index. If there are large amount of trade orders in the list, then it takes more time. If the order list is small, like 20 or less orders, then the time is of no consequence. The number of iterations performed is based upon the index. An index of 0 means one iteration. Index of 9 means 10 iterations.

**Returns:** 1 on success or [SCTRADING\_ORDER\_ERROR](#sctradingordererror) on an error.

#### Parameters

* **OrderIndex**: The index number of the order for which order information is desired. This is a zero-based index.
* **r\_SCTradeOrder**: A reference to an [s\_SCTradeOrder](#ssctradeorder) structure that contains the order information for the order specified by the OrderIndex.

#### Example Code

```cpp

// This is an example of iterating the order list in Sierra Chart for orders
// matching the Symbol and Trade Account of the chart, and finding the orders
// that have a Status of Open and are not Attached Orders.

int Index = 0;
s_SCTradeOrder OrderDetails;
while( sc.GetOrderByIndex (Index, OrderDetails) != SCTRADING_ORDER_ERROR)
{
    Index++; // Increment the index for the next call to sc.GetOrderByIndex
  
    if (OrderDetails.OrderStatusCode !=  SCT_OSC_OPEN)
        continue;

    if (OrderDetails.ParentInternalOrderID != 0)//This means this is an Attached Order
      continue;

    //Get the internal order ID
    int InternalOrderID = OrderDetails.InternalOrderID;

}
            
```

### sc.GetOrderByOrderID

[Link](#getorderbyorderid) - [Top](#top)

int **sc.GetOrderByOrderID**(int **InternalOrderID**, s\_SCTradeOrder& **r\_SCTradeOrder**);

**Description:** The **GetOrderByOrderID** function returns the fields of the order specified by the **InternalOrderID** parameter.

The order fields returned by this function are the very same order fields you see in the [Trade >> Trade Orders Window](TradeStatusWindows.md#tradeorders) for the order.

**Returns:** 1 on success or [SCTRADING\_ORDER\_ERROR](#sctradingordererror) on an error. An error would mean that an order specified by the **InternalOrderID** parameter has not been found. When SCTRADING\_ORDER\_ERROR is returned, all of the member variables of the **OrderDetails** structure parameter will be in a default and unchanged state.

When an order is no longer working (Filled, Canceled, or Error status), it is automatically cleared from the Trade Orders List in Sierra Chart after a period of time. So therefore the order can no longer be retrieved with this function. For complete details, refer to [Automatic Clearing of Orders](TradeStatusWindows.md#autoclearingorders).

In the case where the trade order is no longer available to be retrieved with the **sc.GetOrderByOrderID** function, and you need to determine whether it has filled, use the [sc.GetOrderFillEntry()](#scgetorderfillentry) function instead for that order.

For an example to use this function, refer to the **scsf\_TradingExample** function in the **/ACS\_Source/TradingSystem.cpp** file which is located in the folder that Sierra Chart is installed to.

#### Parameters

* **InternalOrderID**: An identifier returned in the [s\_SCNewOrder::InternalOrderID](#sscneworderinternalorderid) member after submitting an order. This order ID can be remembered into a persistent variable and used with the **sc.GetOrderByOrderID** function.
* **r\_SCTradeOrder**: A reference to an [s\_SCTradeOrder](#ssctradeorder) structure that contains the order information for the order specified by the InternalOrderID.

### sc.GetTradeListEntry()

[Link](#scgettradelistentry) - [Top](#top)

**Type**: Function

void **GetTradeListEntry**(unsigned int **TradeIndex**, s\_ACSTrade& **TradeEntry**)

The **sc.GetTradeListEntry()** function takes a **TradeIndex** parameter specifying a particular Trade from the internal Trades list in a chart, and fills in the **TradeEntry** parameter.

This function fills in the **TradeEntry** with *Trade* data at the **TradeIndex** specified.

Each chart which is used for trading, maintains its own list of Trades. A trade consists of a both a Buy and Sell order fill. This trade data is for the Symbol and Trade Account of the chart the study instance is applied to. This *Trade* data is from the very same data on the [Trades](TradeActivityLog.md#tradestab) tab of the **Trade >> Trade Activity Log**. However, a **Fill to Fill** order fill grouping method is always used. Each of the members of the **s\_ACSTrade** structure are described below.

This function returns 1 if the Trade was found and set into **TradeEntry**. Otherwise, 0 is returned.

When Sierra Chart is in Trade Simulation Mode, then simulated Trades are returned. When Sierra Chart is not in Trade Simulation Mode, then non-simulated Trades are returned. For more information, refer to [Going from Simulation Mode to Live Trading](#simulationtolive).

To locate the latest trades first, set the **TradeIndex** parameter to [sc.GetTradeListSize()](#) - 1, and and decrement it towards zero until you have retrieved the particular Trades that you want.

#### Parameters

* **TradeIndex**: The zero-based index of the desired trade.
* **TradeEntry**: A reference to an instance of a structure of type **s\_ACSTrade** that holds the trade information for the given TradeIndex.
    
    
  Members of the **s\_ACSTrade** structure are listed below. For documentation for each of these, refer to [Trades >> Field Descriptions](TradeActivityLog.md#tradestabfieldsdescriptions) in the Trade Activity Log documentation.
  + SCDateTime **OpenDateTime**
  + SCDateTime **CloseDateTime**
  + int **TradeType** (+1=long, -1=short)
  + int **TradeQuantity**
  + int **MaxClosedQuantity**
  + int **MaxOpenQuantity**
  + double **EntryPrice**
  + double **ExitPrice**
  + double **TradeProfitLoss**
  + double **MaximumOpenPositionLoss**
  + double **MaximumOpenPositionProfit**
  + double **FlatToFlatMaximumOpenPositionProfit**
  + double **FlatToFlatMaximumOpenPositionLoss**
  + double **Commission** (This is only valid if [Use Symbol Commission Setting in Trade List and Statistics Calculations](ChartSettings.md#usesymbolcommissionsettingintradelistandstatisticscalculations) is enabled in the Chart Settings)
  + int **IsTradeClosed**

#### Example

```cpp

std::vector <s_ACSTrade> TradesList;

s_ACSTrade TradeEntry;
int Size = sc.GetTradeListSize();

for(int Index = 0; Index < Size;Index++)
{
    if(sc.GetTradeListEntry(Index, TradeEntry))
      TradesList.push_back(TradeEntry);
}

for (unsigned int TradeIndex = 0; TradeIndex < TradesList.size(); TradeIndex++)
{
    double ProfitLoss = TradesList[TradeIndex].ClosedProfitLoss;
}
            
```

### sc.GetTradeListSize()

[Link](#scgettradelistsize) - [Top](#top)

**Type**: Function

int **GetTradeListSize()**

The **sc.GetTradeListSize** returns the number of trades in the internal Trades list in a chart.

The returned value minus 1 is the maximum value that can be used for the **TradeIndex** parameter of the [sc.GetTradeListEntry](#scgettradelistentry) function.

The size returned by this function can change upon the following conditions: A fill for the Symbol and Trade Account of the chart the study instance is on, occurs in real time. The Symbol of the chart changes. The Trade Account of the chart changes. After connected to the data feed, new order fills are received for the Symbol and Trade Account of the chart. Historical order fills are received during the connection to the trading server at some other time.

The size is also affected by the [Order Fills Start Date-Time](ChartSettings.md#orderfillsstartdatetime) Chart Setting.

#### Parameters

* This function has no parameters

### sc.GetFlatToFlatTradeListEntry()

[Link](#scgetflattoflattradelistentry) - [Top](#top)

**Type**: Function

void **GetFlatToFlatTradeListEntry**(unsigned int **TradeIndex**, s\_ACSTrade& **TradeEntry**)

The **sc.GetFlatToFlatTradeListEntry()** function is the same as [sc.GetTradeListEntry](#scgettradelistentry), except that it gets a [Flat to Flat](TradeActivityLog.md#orderfillmatchingmethods) trade entry.

#### Parameters

* **TradeIndex**: The zero-based index of the desired trade.
* **TradeEntry**: A reference to an instance of a structure of type **s\_ACSTrade** that holds the trade information for the given TradeIndex.

### sc.GetFlatToFlatTradeListSize()

[Link](#scgetflattoflattradelistsize) - [Top](#top)

**Type**: Function

int **GetFlatToFlatTradeListSize**()

The **sc.GetFlatToFlatTradeListSize** function is the same as [sc.GetTradeListSize](#scgettradelistsize) except that it gets the size of the Flat to Flat Trades list.

#### Parameters

* This function has no parameters

### sc.GetOrderFillEntry()

[Link](#scgetorderfillentry) - [Top](#top)

**Type**: Function

int **GetOrderFillEntry**(unsigned int **FillIndex**, s\_SCOrderFillData& **FillData**);

The **sc.GetOrderFillEntry()** function returns an order fill for the given FillIndex for the Symbol and Trade Account of the chart the study instance is applied to.

A **FillIndex** of 0 is the oldest fill. Higher numbered indices are newer fills.

The maximum number of fills can be determined from the [sc.GetOrderFillArraySize](#scgetorderfillarraysize) function. Therefore, the highest **FillIndex** that can be used will be what this function returns minus 1.

To get the most recent order fill use  **sc.GetOrderFillArraySize() - 1** for the **FillIndex** parameter.

All available order fills for the Symbol and Trade Account can be accessed. These order fills are stored in the [Trade Activity Log](TradeActivityLog.md). However, there is a limit to the order fills loaded in the chart which will limit the number of fills accessible through the **sc.GetOrderFillEntry** function. You can control that with the [Order Fills Start Date-Time](ChartSettings.md#orderfillsstartdatetime) setting.

To ensure order fills are in a chart are maintained, set [sc.MaintainTradeStatisticsAndTradesData](ACSIL_Members_Variables_And_Arrays.md#scmaintaintradestatisticsandtradesdata) to 1 in your study function.

Order fills loaded in a chart are not instantly available after a reload of chart data, or after changing Chart Settings. There is an asynchronous request made for the data and it will take time to complete. For more information, refer to [Trade Activity Not Displaying or Clearing](TradeActivityLog.md#tradeactivitynotdisplayingorclearingimprovingtradeactivityqueryperformance).

When Sierra Chart is in Trade Simulation Mode, then simulated order fill data is returned. When Sierra Chart is not in Trade Simulation Mode, then non-simulated order fill data is returned. For more information, refer to [Going from Simulation Mode to Live Trading](#simulationtolive).

If you want to determine the order fills for the current Position which is currently nonzero, then a technique is to reverse iterate the fills by using a **FillIndex** parameter which is equal to [sc.GetOrderFillArraySize](#scgetorderfillarraysize) minus 1 and decrement it. Sum the quantities of the order fills using a positive quantity for a buy fill and a negative quantity for a sell fill. When you meet or exceed, the Position Quantity, then you have all of the fills for that position.

The function returns 1 on success and 0 if the order fill is not found.

#### Parameters

* **FillIndex**: The zero-based index of the desired fill.
* **FillData**: A reference to an s\_SCOrderFillData structure which is filled in for the given FillIndex.
    
    
  Refer to the **/ACS\_Source/SCStructures.h** file for a complete definition of the **s\_SCOrderFillData** structure for order fills. The following are the current member variables.
  + SCString **Symbol**: The symbol for the order fill.
  + SCString **TradeAccount**: The Trade Account for the order fill
  + int **InternalOrderID**: The Internal Order identifier the order fill is associated with.
  + SCDateTime **FillDateTime**: The order fill date and time.
  + BuySellEnum **BuySell**: Whether the order fill is for a Buy or Sell order.
  + unsigned int **Quantity**: The quantity of the order fill.
  + double **FillPrice**: The price at which the order filled.
  + SCString **FillExecutionServiceID**:
  + int **TradePositionQuantity**:
  + int **IsSimulated**: Defines whether the fill is for a Simulated or Non-Simulated order. A value of 1 is simulated, a value of 0 is non-simulated.
  + SCString **OrderActionSource**: Information on the source of the order fill.
  + SCString **Note**: Any note set on the order for which the order fill is associated.
  + SCString **ServiceOrderID**: The Service order identifier for which the order fill is associated

### sc.GetOrderFillArraySize()

[Link](#scgetorderfillarraysize) - [Top](#top)

**Type**: Function

int **GetOrderFillArraySize**();

The **sc.GetOrderFillArraySize** function returns the number of order fills available. This function is used with the [sc.GetOrderFillEntry](#scgetorderfillentry) function.

To ensure order fills are in a chart are maintained, set [sc.MaintainTradeStatisticsAndTradesData](ACSIL_Members_Variables_And_Arrays.md#scmaintaintradestatisticsandtradesdata) to 1 in your study function.

Order fills loaded in a chart are not instantly available after a reload of chart data, or after changing Chart Settings. There is an asynchronous request made for the data and it will take time to complete. For more information, refer to [Trade Activity Not Displaying or Clearing](TradeActivityLog.md#tradeactivitynotdisplayingorclearingimprovingtradeactivityqueryperformance).

#### Parameters

* This function has no parameters

### sc.GetOrderForSymbolAndAccountByIndex()

[Link](#scgetorderforsymbolandaccountbyindex) - [Top](#top)

**Type**: Function

int **GetOrderForSymbolAndAccountByIndex**(const char\* **Symbol**, const char\* **TradeAccount**, int **OrderIndex**, s\_SCTradeOrder& **r\_SCTradeOrder**);

The **sc.GetOrderForSymbolAndAccountByIndex()** function fills out the **r\_SCTradeOrder** structure with the order that matches the **Symbol**, **TradeAccount** and **OrderIndex**.

Beginning from 0, you can increment the OrderIndex parameter by 1 and keep calling **sc.GetOrderForSymbolAndAccountByIndex** until the function returns [**SCTRADING\_ORDER\_ERROR**](#sctradingordererror) indicating there are no more orders.

The function returns a value of **1** if it successfully finds the order and fills out the **ACSOrderDetails** structure. Otherwise, it returns [**SCTRADING\_ORDER\_ERROR**](#sctradingordererror). [**SCTRADING\_ORDER\_ERROR**](#sctradingordererror) will also be returned for an invalid OrderIndex.

When calling the **sc.GetOrderForSymbolAndAccountByIndex** function and **Trade >> Trade Simulation Mode On** is enabled or **sc.SendOrdersToTradeService** is false, then only *simulated* orders are returned.

If **Trade >> Trade Simulation Mode On** is disabled and **sc.SendOrdersToTradeService** is true, then only *non-simulated* orders are returned.

#### Parameters

* **Symbol**: The symbol to get the order data for. For information about working with strings, refer to [Working with Strings](ACSILProgrammingConcepts.md#workingwithtextstrings). This parameter can be an empty string to get orders for all symbols.
* **TradeAccount**: The Trade Account to get the order data for. This parameter must be specified. No orders will be returned if it is an empty string.
* **OrderIndex**: The zero-based order index for the order to return. Start by setting this to 0 and increment by 1 until there is an error returned.
* **r\_SCTradeOrder**: An s\_SCTradeOrder structure containing the Order details.

### sc.GetParentOrderIDFromAttachedOrderID()

[Link](#scgetparentorderidfromattachedorderid) - [Top](#top)

**Type**: Function

void **GetParentOrderIDFromAttachedOrderID**(int **AttachedOrderInternalOrderID**);

The **sc.GetParentOrderIDFromAttachedOrderID()** function is to return the parent Internal Order ID for the given Attached Order Internal Order ID.

#### Parameters

* **AttachedOrderInternalOrderID**: The Internal Order ID for the attached order. For information about Internal Order IDs, refer to the [ACSIL Trading](ACSILTrading.md) page. These Internal Order IDs can be obtained when submitting an order.

### sc.GetNearestStopOrder()

[Link](#scgetneareststoporder) - [Top](#top)

**Type**: Function

int **GetNearestStopOrder**(s\_SCTradeOrder& **OrderDetails**);

The **sc.GetNearestStopOrder()** function searches for an Open or Pending Child **Stop** Attached Order which is nearest to the current trade price. If it finds one, it will fill out the **OrderDetails** parameter.

If an Attached Order is not found, then other OCO type orders are searched instead.

Returns 1 if a Stop Attached Order is found. Otherwise, 0 is returned.

This function is affected by the setting of the [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice) variable. Therefore, if this is set to false, then only simulated orders will be searched.

#### Parameters

* **OrderDetails**: A reference to an [s\_SCTradeOrder structure](#ssctradeorder) that holds the order details for the nearest stop order.

#### Example

```cpp

s_SCTradeOrder Order;
int Result = 0;

if (OrderType.IntValue == 0)
    Result = sc.GetNearestStopOrder(Order);
else
    Result = sc.GetNearestTargetOrder(Order);

// only process open orders
if (Result == 0 || Order.OrderStatusCode != SCT_OSC_OPEN)
    return;
            
```

### sc.GetNearestTargetOrder()

[Link](#scgetnearesttargetorder) - [Top](#top)

**Type**: Function

int **GetNearestTargetOrder**(s\_SCTradeOrder& **OrderDetails**);

The **sc.GetNearestTargetOrder()** function searches for an Open or Pending Child **Target (Limit)** Attached Order which is nearest to the current trade price. If it finds one, it will fill out the **OrderDetails** parameter, with the details of the order.

If an Attached Order is not found, then other OCO type orders are searched instead.

Returns 1 if a Target Attached Order is found. Otherwise, 0 is returned.

This function is affected by the setting of the [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice) variable. Therefore, if this is set to false, then only simulated orders will be searched.

#### Parameters

* **OrderDetails**: A reference to an [s\_SCTradeOrder structure](#ssctradeorder) that contains the order details for the nearest target order.

#### Example

```cpp

s_SCTradeOrder Order;
int Result;

if (OrderType.IntValue == 0)
    Result = sc.GetNearestStopOrder(Order);
else
    Result = sc.GetNearestTargetOrder(Order);

// only process open orders
if (Result == 0 || Order.OrderStatusCode != SCT_OSC_OPEN)
    return;  
            
```

### sc.GetTradeStatisticsForSymbolV2()

[Link](#scgettradestatisticsforsymbolv2) - [Top](#top)

**Type**: Function

int **GetTradeStatisticsForSymbolV2**(n\_ACSIL::TradeStatisticsTypeEnum **StatsType**, n\_ACSIL::s\_TradeStatistics& **TradeStatistics**);

The **sc.GetTradeStatisticsForSymbolV2** function obtains the trade statistics for the Symbol and Trade Account of the chart that the study is applied to. These are the same Trade Statistics as the data on the [Trade Statistics](TradeActivityLog.md#tradestatisticstab) tab of the Trade Activity Log.

The **sc.GetTradeStatisticsForSymbolV2** function provides a lot more trade statistics and Flat to Flat trade statistics as compared to the **sc.GetTradeStatisticsForSymbol** function. Refer to that section for field descriptions.

The trade statistics are calculated in the internal Trades list in the chart which loads the available order fills for the Symbol and Trade Account of the chart.

To control the starting Date-Time of the fills, refer to [Understanding and Setting the Start Date-Time for a Trades List](TradeActivityLog.md#understandingandsettingthestartdatetimeforatradeslist).

In order for this function to work properly, there needs to be a Trades list being maintained in the chart the study instance is applied to. Therefore, it is necessary to set **sc.MaintainTradeStatisticsAndTradesData = true** in the **sc.SetDefaults** section of the study function when using **sc.GetTradeStatisticsForSymbolV2**.

When the **Trade >> Trade Simulation Mode On** setting is enabled, then the trade statistics will be for *simulated trading*. When the **Trade >> Trade Simulation Mode On** setting is disabled, then the trade statistics will be for *non-simulated trading*.

In the case of daily trade statistics it is important to understand the [Daily Reset Time](TradeActivityLog.md#understandingdailytradestatisticsresettime).

#### Parameters

* **StatsType**: Can be one of the following constants:
  + STATS\_TYPE\_ALL\_TRADES
  + STATS\_TYPE\_LONG\_TRADES
  + STATS\_TYPE\_SHORT\_TRADES
  + STATS\_TYPE\_DAILY\_ALL\_TRADES  
    
  These constants will retrieve the Trade Statistics for all trades, long trades, short trades, or all trades for the most recent trading day loaded in the Trades list, respectively.
* **TradeStatistics**: The passed n\_ACSIL::s\_TradeStatistics structure is filled with the requested Trade Statistics data. The Trade Statistics values can then be retrieved from any of the member variables of that structure. For the complete definition of that structure, refer to the */ACS\_Source/scstructures.h* file in the Sierra Chart installation folder.

#### Example

```cpp
        
n_ACSIL::s_TradeStatistics  TradeStatistics;
if (sc.GetTradeStatisticsForSymbolV2(n_ACSIL::STATS_TYPE_DAILY_ALL_TRADES, TradeStatistics))
{

     double ClosedTradesProfitLoss = TradeStatistics.ClosedTradesProfitLoss;
}
            
```

### IsWorkingOrderStatus()

[Link](#isworkingorderstatus) - [Top](#top)

bool **IsWorkingOrderStatus**(SCOrderStatusCodeEnum **OrderStatusCode**);

The **IsWorkingOrderStatus** function returns TRUE if the order is a working/open order. This means the order status code is: **SCT\_OSC\_ORDERSENT**, **SCT\_OSC\_PENDINGOPEN**, **SCT\_OSC\_OPEN**, **SCT\_OSC\_PENDINGCANCEL**, **SCT\_OSC\_PENDINGMODIFY**, **SCT\_OSC\_PENDING\_CHILD\_CLIENT**, or **SCT\_OSC\_PENDING\_CHILD\_SERVER**. Otherwise, FALSE is returned.

#### Parameters

* This function has no parameters

#### Example

```cpp

if (IsWorkingOrderStatus(ExistingOrder.OrderStatusCode))
{
}
            
```

### IsWorkingOrderStatusIgnorePendingChildren()

[Link](#isworkingorderstatusignorependingchildren) - [Top](#top)

**Type**: Function

bool **IsWorkingOrderStatusIgnorePendingChildren**(SCOrderStatusCodeEnum **OrderStatusCode**);

The **IsWorkingOrderStatusIgnorePendingChildren()** function returns TRUE if the order status code is for a working/open order. Otherwise, FALSE is returned.

A pending child order whether on the client or server side is *not* considered working, therefore an order status code associated with one of these orders will return FALSE.

A working order means the order status code is **SCT\_OSC\_ORDERSENT**, **SCT\_OSC\_PENDINGOPEN**, **SCT\_OSC\_OPEN**, **SCT\_OSC\_PENDINGCANCEL**, or **SCT\_OSC\_PENDINGMODIFY**.

#### Parameters

* **OrderStatusCode**: The order status code for the given working order.

#### Example

```cpp

//Order is considered working
if (IsWorkingOrderStatusIgnorePendingChildren(ExistingOrder.OrderStatusCode))
{
}
            
```

### s\_SCTradeOrder Structure Members

[Link](#ssctradeorder) - [Top](#top)

#### [Type: integer] **InternalOrderID**

[Link](#ssctradeorderinternalorderid) - [Top](#top)

The InternalOrderID of the order displayed in the **Trade >> Trade Orders Window**.

InternalOrderID is always set to a positive nonzero value. This will never be zero unless there was no order returned.

#### [Type: SCString] **Symbol**

[Link](#ssctradeordersymbol) - [Top](#top)

The Symbol of the order displayed in the **Trade >> Trade Orders Window**.

#### [Type: SCString] **OrderType**

[Link](#ssctradeorderordertype) - [Top](#top)

The Order Type of the order as shown in the **Trade >> Trade Orders Window**.

This member is the Order Type as a text string. To access the Order Type as an integer, use the [OrderTypeAsInt](#ssctradeorderordertypeasint) member instead.

#### [Type: integer] **OrderQuantity**

[Link](#ssctradeorderorderquantity) - [Top](#top)

The Order Quantity of the order as displayed in the **Trade >> Trade Orders Window**.

#### [Type: integer] **FilledQuantity**

[Link](#ssctradeorderfilledquantity) - [Top](#top)

The FilledQuantity member is set to the number of shares/contracts that have already been filled. This is an important member that you may need to check if there is a partial fill. A working order that is only partially filled does not update the Internal Position data. It is only when an order completely fills that the Internal Position data is updated and will then reflect the position from the order.

#### [Type: integer] **BuySell**

[Link](#ssctradeorderbuysell) - [Top](#top)

This field indicates if the order is a Buy or Sell order as shown in the **Trade >> Trade Orders Window**.

This is an integer enumeration and can be either **BSE\_BUY** or **BSE\_SELL**.

#### [Type: double] **Price1**

[Link](#ssctradeorderprice1) - [Top](#top)

This is the price of the order. This applies to all order types that are not Market orders.

#### [Type: double] **Price2**

[Link](#ssctradeorderprice2) - [Top](#top)

In the case of Stop-Limit orders, this is the Limit order price. For Stop-Limit orders, the Stop price is specified with Price1.

#### [Type: double] **AvgFillPrice**

[Link](#ssctradeorderavgfillprice) - [Top](#top)

The average price for all of the fills for this order.

##### AvgFillPrice Code Example

```cpp

    // Enter a new order as a Buy Entry order.
    s_SCNewOrder NewOrder;
    NewOrder.OrderQuantity = 1;

    NewOrder.OrderType = SCT_MARKET;
    int ReturnValue;
    ReturnValue = sc.BuyEntry(NewOrder);

    // Remember the internal order id if we have one into a Persistent variable
    int &OrderID = sc.PersistVars->Integers[0];
    if (ReturnValue > 0 && NewOrder.InternalOrderID != 0)
    {
        OrderID = NewOrder.InternalOrderID;
    }

    // Once the order fills, after submitting the order, we can
    // determine the actual fill price with the following code. Keep in
    // mind that we may not obtain the fill price at this moment, but
    // on a subsequent call into the study function.

    // Get the available order data for the submitted order by using
    // the InternalOrderID that was assigned after calling the Order
    // Action function sc.BuyEntry.

    if (OrderID != 0)
    {
        s_SCTradeOrder TradeOrderData;

        int Result = sc.GetOrderByOrderID(NewOrder.InternalOrderID, TradeOrderData);

        if (Result != SCTRADING_ORDER_ERROR)
        {
            double FillPrice = TradeOrderData.AvgFillPrice;
        }

        int OrderStatusCode = TradeOrderData.OrderStatusCode;
        if (OrderStatusCode == SCT_OSC_FILLED)
        {
            // The order has completely filled
        }
    }
                
```

#### [Type: integer] **OrderStatusCode**

[Link](#ssctradeorderorderstatuscode) - [Top](#top)

The following are the various constants that the OrderStatusCode can be set to. They indicate the status of the order. For complete descriptions for these, refer to [Order Field Descriptions](TradeStatusWindows.md#orderfielddescriptions). These constants are in the **/ACS\_Source/SCConstants.h** file in the folder where Sierra Chart is installed to.

* SCT\_OSC\_UNSPECIFIED
* SCT\_OSC\_ORDERSENT
* SCT\_OSC\_PENDINGOPEN
* SCT\_OSC\_PENDING\_CHILD\_CLIENT (Client-side held child order)
* SCT\_OSC\_PENDING\_CHILD\_SERVER (Server-side held child order)
* SCT\_OSC\_OPEN
* SCT\_OSC\_PENDINGMODIFY
* SCT\_OSC\_PENDINGCANCEL
* SCT\_OSC\_ERROR
* SCT\_OSC\_FILLED
* SCT\_OSC\_CANCELED

An order which has been rejected and also assigned an Internal Order ID will have a status of SCT\_OSC\_ERROR.

#### [Type: integer] **ParentInternalOrderID**

[Link](#ssctradeorderparentinternalorderid) - [Top](#top)

If the order is an Attached Order, then this member is set to the Internal Order ID of the Parent. Otherwise it will be 0.

If it is 0, then it is not an Attached Order. If you are trying to find Attached Orders to be able to modify them after the Parent order is submitted, then you need to use the [sc.GetOrderByIndex()](#getorderbyindex) function and iterate through all of the orders, looking for the orders that have the OrderStatusCode set to SCT\_OSC\_WORKING and have a non-zero ParentInternalOrderID.

You will then have access to the InternalOrderID of the Attached Order. This internal order ID can be used with the [sc.ModifyOrder()](#ordermodification) function to modify the price or quantity of the order.

#### [Type: integer] **LinkID**

[Link](#ssctradeorderlinkid) - [Top](#top)

This member will be set to the Link ID of the order as displayed in the **Trade >> Trade Orders Window** for the order.

If orders are linked together they will have a nonzero Link ID. Orders which have the same Link ID, are linked together.

Orders will be linked together if they are split into smaller order quantities when Attached Orders are used and you are using more than one OCO Group. For more information about this, refer to the [Attached Orders](AttachedOrders.md) documentation.

When orders are linked together, this means that when one of them is canceled, the other orders that share the same Link ID will be canceled as well. When one of the linked orders has its price modified, the other orders that share the same Link ID will be modified to the same price. When one of the linked orders has its quantity modified, the other orders that share the same Link ID will not be modified.

#### [Type: SCDateTime] **LastActivityTime**

[Link](#ssctradeorderlastactivitytime) - [Top](#top)

This member is set to the last activity Date-Time for the order. Once an order is canceled or filled and there is no longer any activity on the order, then this Date-Time will represent the time of completion of the order. This will be when it was canceled or completely filled. Although when Sierra Chart is restarted, canceled and filled orders are received from an external Trading service and they are not already in the Trade Orders List, then this will be set to the current time.

In the case of Working orders which remain in the Trade Orders List, the last Activity Time is not reset when Sierra Chart is started. However, once the order receives an update as happens when connecting to the Trade service, then this Date-Time will be updated.

#### [Type: SCDateTime] **EntryDateTime**

[Link](#ssctradeorderentrydatetime) - [Top](#top)

This member is set to the Date-Time the order was placed into the Trade Orders List. It is not necessarily the time that the order was actually submitted because the order could have been submitted at a different time outside of Sierra Chart when Sierra Chart was not running and connected to the external Trading service. There are other reasons why this may not be accurate as well.

#### [Type: integer] **OrderTypeAsInt**

[Link](#ssctradeorderordertypeasint) - [Top](#top)

This member indicates the order type as an integer. For the possible values, refer to [Order Type Constants](#ordertypeconstants).

#### [Type: SCString] **TextTag**

[Link](#ssctradeordertexttag) - [Top](#top)

This member is set to the TextTag variable which was originally sent in the [s\_SCNewOrder Structure](#sscneworder) when submitting the order.

#### [Type: unsigned int] **LastModifyQuantity**

[Link](#ssctradeorderlastmodifyquantity) - [Top](#top)

This member is the order quantity specified at the last order modification. If an order modification is still in progress and that order modification changed the order quantity, then this quantity will be different than the **OrderQuantity** member.

#### [Type: double] **LastModifyPrice1**

[Link](#ssctradeorderlastmodifyprice1) - [Top](#top)

This member is the Price1 specified at the last order modification. If an order modification is still in progress and that order modification changed Price1, then this price will be different than the **Price1** member.

#### [Type: double] **LastFillPrice**

[Link](#ssctradeorderlastfillprice) - [Top](#top)

This member is the price of the most recent order fill for the order. If there has not been an order fill yet for the order, this will be set to 0.0.

#### [Type: int] **LastFillQuantity**

[Link](#ssctradeorderlastfillquantity) - [Top](#top)

This member is the quantity of the most recent order fill for the order.If there has not been an order fill yet for the order, this will be set to 0.

#### [Type: int] **SourceChartNumber**

[Link](#ssctradeordersourcechartnumber) - [Top](#top)

This is the chart number that the order originated from if it originated from a chart or Trade DOM. This will be set to 0 in the case of an externally received order from the trading service.

#### [Type: SCString] **SourceChartbookFileName**

[Link](#ssctradeordersourcechartbookfilename) - [Top](#top)

This is the file name of the Chartbook containing the chart or Trade DOM that the order originated from. This will be an empty string in the case of an externally received order from the trading service.

#### [Type: int] **IsSimulated**

[Link](#ssctradeorderissimulated) - [Top](#top)

This variable is set to 1 for a simulated order. And set to 0 for a non-simulated order.

#### [Type: uint64\_t] **TargetChildInternalOrderID**

[Link](#ssctradeordertargetchildinternalorderid) - [Top](#top)

This variable is set to the Internal Order ID of the Target order which is a child of the parent order, if this is a parent order and it has a child Target order.

#### [Type: uint64\_t] **StopChildInternalOrderID**

[Link](#ssctradeorderstopchildinternalorderid) - [Top](#top)

This variable is set to the Internal Order ID of the Stop order which is a child of the parent order, if this is a parent order and it has a child Stop order.

#### [Type: uint64\_t] **OCOSiblingInternalOrderID**

[Link](#ssctradeorderocosiblinginternalorderid) - [Top](#top)

This variable is set to the Internal Order ID of the sibling of this order if this order is part of an OCO order.

#### [Type: int32\_t] **EstimatedPositionInQueue**

[Link](#ssctradeorderestimatedpositioninqueue) - [Top](#top)

This variable is set to the estimated position within the queue for the order. This will only be set if [Enable Estimated Position in Queue Tracking](GlobalTradeSettings.md#charttradesettingsenableestimatedpositioninqueuetracking) is enabled.

#### [Type: integer] **TriggeredTrailingStopTriggerHit**

[Link](#ssctradeordertriggeredtrailingstoptriggerhit) - [Top](#top)

The **TriggeredTrailingStopTriggerHit** variable is 1 when the trigger price has been hit or touched for any of the [Triggered Trailing Stop](OrderTypes.md#triggeredtrailingstop) type of orders. This includes SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS , SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_LIMIT\_3\_OFFSETS, SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP, and SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP\_LIMIT.

Otherwise, this variable is 0.

#### [Type: [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings)] **LastOrderActionSource**

[Link](#ssctradeorderlastorderactionsource) - [Top](#top)

The **LastOrderActionSource** text string contains the very same text as the [Last Order Action Source](TradeStatusWindows.md#orderfielddescriptions) field for an order.

If an order has been rejected, this string will contain the reason for the rejection to the extent it has been provided from the external Trading service or from the Trade Simulation system in Sierra Chart when using [Trade Simulation Mode](TradeSimulation.md).

#### [Type: [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings)] **TradeAccount**

[Link](#ssctradeordertradeaccount) - [Top](#top)

The Trade Account identifier the order is associated with.

## Cancel Orders and Flatten Position Functions

[Link](#cancelflattenfunctions) - [Top](#top)

### sc.CancelOrder

[Link](#cancelorder) - [Top](#top)

int **sc.CancelOrder**(int **InternalOrderID**);

The **sc.CancelOrder()** function cancels the order with the given Internal Order ID.

The [InternalOrderID](#sscneworderinternalorderid) can be obtained when you called one of the order submission functions and an order was accepted. It will be contained in the **s\_SCNewOrder::InternalOrderID** member. There are other members for Attached Order IDs.

The **InternalOrderID** can also be determined with the [sc.GetOrderByIndex()](#gettingorderinformation) function.

When an order is canceled, all other working orders that are linked to the order you are canceling, will also be canceled. Orders may be linked when the order is part of an order set that contains an Attached Order with an OCO Group setting of **All OCO Groups** and there was more than one OCO Group used.

You can see if an order is part of a linked group by looking at the **Link ID** field in **Trade >> Trade Orders Window** for the order. Orders that share the same Link ID are linked.

This function is affected by the **sc.SendOrdersToTradeService** variable. For more information, refer to [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice).

**Returns:** 1 on success or [SCTRADING\_ORDER\_ERROR](#sctradingordererror) on failure. The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror).

#### Parameters

* **InternalOrderID**: The Internal Order ID of the order to be cancelled.

#### Code Example

```cpp

int &RememberedOrderID= sc.PersistVars->Integers[0];
bool CancelOrder = false;

// Create a s_SCNewOrder object.  
s_SCNewOrder NewOrder; 
NewOrder.OrderQuantity = 1;
NewOrder.OrderType = SCT_MARKET; 

int Result =sc.BuyEntry(NewOrder);

if (Result > 0) //If there has been a successful order entry
{
    //Remember the order ID for subsequent order modification or cancellation.
    RememberedOrderID = NewOrder.InternalOrderID;

    //Put an arrow on the chart to indicate the order entry
    BuyEntrySubgraph[sc.Index] = sc.Low[sc.Index];
}

if(CancelOrder)
{
    int Result = sc.CancelOrder(RememberedOrderID);
}
            
```

### sc.CancelAllOrders

[Link](#cancelallorders) - [Top](#top)

int **sc.CancelAllOrders**();

The **sc.CancelAllOrders()** function cancels all working orders for the Symbol and [Trade Account](TradeWindow.md#selectingtradeaccount) of the chart that the trading study is applied to.

When Sierra Chart is in Trade Simulation Mode, only simulated orders are canceled. Otherwise, non-simulated orders are canceled.

This function is affected by the **sc.SendOrdersToTradeService** variable. For more information, refer to [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice).

**Returns:** 1 on success or [SCTRADING\_ORDER\_ERROR](#sctradingordererror) on failure. The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror).

#### Parameters

* This function has no parameters

### sc.FlattenAndCancelAllOrders

[Link](#flattenandcancelallorders) - [Top](#top)

int **sc.FlattenAndCancelAllOrders**();

The **sc.FlattenAndCancelAllOrders()** function flattens the current Trade Position for the Symbol and Trade Account of the chart that the trading study is applied to and cancels all working orders for the same Symbol and Trade Account. The working orders are canceled first but all of these actions are immediately executed.

This function only applies to simulated Trade Positions and simulated orders when the global Trade Simulation Mode is enabled. Otherwise, it only applies to non-simulated Trade Positions and non-simulated orders.

This function is affected by the **sc.SendOrdersToTradeService** variable. For more information, refer to [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice).

**Returns:** 1 on success or [SCTRADING\_ORDER\_ERROR](#sctradingordererror) on an error. The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror). It is important to look at this return value to understand the reason why the action did not get performed on an error. If there is no error, and the Flatten and Cancel action did not get performed, then refer to the [Trade Activity Log](TradeActivityLog.md#viewinghistoricaltradeactivity) for the detailed order activity.

A call to **sc.FlattenAndCancelAllOrders** is ignored and will return an error when the chart is downloading historical data, the studies are being fully recalculated, or **Trade >> Auto Trading Enabled** is disabled.

It is important to be aware that the Market order sent with the **sc.FlattenAndCancelAllOrders** function can be rejected by the connected Trading service. For more information about this, refer to [Rejected Market Order When Using Flatten or Reverse Because of Position Limit Exceeded](TradeWindow.md#rejectedmarketorderwhenusingflatten).

You may also want to enable the option [Hold Market Order Until Pending Cancel Orders Confirmed](GlobalTradeSettings.md#holdmarketorderuntilpendingcancelordersconfirmed).

The solution to this kind problem described in the section linked to above is to use [sc.CancelAllOrders](#cancelallorders) to first cancel the working/open orders. Wait for these orders to be canceled by checking the [s\_SCTradeOrder::OrderStatusCode](#ssctradeorder) for them by getting the trade order data with the [sc.GetOrderByOrderID](#getorderbyorderid) function and make sure they are no longer working by using the [IsWorkingOrderStatus](#isworkingorderstatus) function. Finally make a call to [sc.FlattenPosition](#flattenposition) to flatten the Trade Position.

#### Parameters

* This function has no parameters

#### Example

```cpp

sc.FlattenAndCancelAllOrders();
            
```

### sc.FlattenPosition

[Link](#flattenposition) - [Top](#top)

int **sc.FlattenPosition**();

The **sc.FlattenPosition()** function flattens the current Trade Position for the Symbol and Trade Account of the chart that the trading study is applied to.

This function only applies to simulated Trade Positions when the global Trade Simulation Mode is enabled. Otherwise, it only applies to non-simulated Trade Positions when global Trade Simulation Mode is disabled.

This function is affected by the **sc.SendOrdersToTradeService** variable. For more information, refer to [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice).

**Returns:** 1 on success or [SCTRADING\_ORDER\_ERROR](#sctradingordererror) on failure. The return value can also be one of the [Ignored Order Error Constants](#ignoredordererror).

#### Parameters

* This function has no parameters

#### Example

```cpp

sc.FlattenPosition();
            
```

### sc.FlattenAndCancelAllOrdersForSymbolAndNonSimTradeAccount

[Link](#flattenandcancelallordersforsymbolandnonsimtradeaccount) - [Top](#top)

int **sc.FlattenAndCancelAllOrdersForSymbolAndNonSimTradeAccount**(const SCString& **Symbol**, const SCString& **TradeAccount**);

The **sc.FlattenAndCancelAllOrdersForSymbolAndNonSimTradeAccount()** function flattens all of the Trade Positions for the specified **Symbol** and the specified non-simulated **Trade Account**. All working orders for the same Symbol and Trade Account are cancelled.

**Returns:** 1 on success or 0 if there is an error. The function will return 1 if it is successful sending the trading commands to the trading service to perform the specified actions. However, this does not mean there is any success with these particular commands.

#### Parameters

* **Symbol**: The symbol for which positions are to be flattened and orders cancelled.
* **TradeAccount**: The trading account for which positions are to be flattened and orders cancelled.

#### Example

```cpp

sc.FlattenAndCancelAllOrdersForSymbolAndNonSimTradeAccount(sc.Symbol, sc.SelectedTradeAccount);
            
```

## Getting Trade Position Data

[Link](#gettingpositioninformation) - [Top](#top)

### sc.GetTradePosition

[Link](#scgettradeposition) - [Top](#top)

int **sc.GetTradePosition**(s\_SCPositionData& **PositionData**);

The **sc.GetTradePosition()** function returns the Trade Position data into the structure **PositionData**, for the Symbol and Trade Account of the chart the trading system study is on.

**sc.GetTradePosition()** is for getting the Trade Position data which comes from the Trade Position data displayed in the **Trade >> Trade Positions Window**. For simulated Trade Positions data, the data comes from the internal Trades list of a chart.

Refer to the table below to understand whether simulated or non-simulated Trade Position data is returned.

The s\_SCPositionData::PositionQuantity is updated when an order fill occurs in Trade Simulation Mode or is received from the external Trading service. Therefore, in the case of non-simulated trading, there is not an immediate update. Only when an order fill occurs.

When an ACSIL trading system study is using Trade Simulation Mode, **Trade >> Trade Simulation Mode On**, then the Trade Position data is for trades made in Trade Simulation mode only. The symbol of these Trade Positions begin with **[Sim]**. Otherwise, non-simulated Trade Position data is provided.

Note that when **Trade >> Open Trade Window for Chart >> M/Menu >> Settings >> Use Order Fill Calculated Position** is checked, then the order fill calculated Trade Position data will be used when *not* in Trade Simulation Mode.

For more information about Trade Positions data, refer to [Trade Positions](TradeStatusWindows.md#positionswindow).

**Returns:** Returns 1 on success. Returns [SCTRADING\_ORDER\_ERROR](#sctradingordererror) on an error.

The only current reason for an error is that when a study function is using Automatic Looping (sc.AutoLoop = 1) and there is a full recalculation. In this case SCTRADING\_ORDER\_ERROR is returned when **sc.Index < (sc.ArraySize - 1)**. This is for efficiency reasons to not slow processing during a full recalculation. Since this function only returns the current Trade Position data, it is not relevant across historical data in a chart.

Trade Position data will always be returned when processing the very last bar in the chart. An error will *not* be returned during a Back Test as historical data is being processed.

|  | Trade Simulation Mode On | Trade Simulation Mode Off |
| --- | --- | --- |
| sc.GetTradePosition | Gets Simulated Trade Positions data | Gets Non-Simulated Trade Positions data |

In the above table, **Trade Simulation Mode On** means: **Trade >> Trade Simulation Mode On** is enabled.

**Trade Simulation Mode Off** means: **Trade >> Trade Simulation Mode On** is disabled.

#### Parameters

* **PositionData**: A reference to a structure of type [s\_SCPositionData](#sscpositiondata) that is filled in when this function is called.
    
    
  This structure holds a copy of the Trade Position data at the time you make a call to **sc.GetTradePosition()**. The data in the structure will not change until you make a call into the **sc.GetTradePosition** function again.

#### Example

```cpp

//Get Position data for the symbol that this trading study is applied to.
s_SCPositionData PositionData;
int Result = sc.GetTradePosition(PositionData);

int Quantity = PositionData.PositionQuantity;//Access the quantity
            
```

### sc.GetTradePositionByIndex()

[Link](#scgettradepositionbyindex) - [Top](#top)

int **sc.GetTradePositionByIndex**(s\_SCPositionData& **r\_PositionData**, int **Index**);

The **sc.GetTradePositionByIndex()** function, returns the trade position data for the position at Index.

The **sc.GetTradePositionByIndex** function returns a value of **1** if the Position at Index was found. Otherwise a value of 0 is returned.

In order to obtain all available Trade Positions, increment the Index starting from zero with each call and when the function returns 0, then you have received all of the available Trade Positions. Only non-simulated Trade Positions are supported.

The Trade Position the **sc.GetTradePositionByIndex** function returns comes from the corresponding Position displayed in the **Trade >> Trade Positions Window**.

#### Parameters

* **r\_PositionData**: A reference to an [s\_SCPositionData](#sscpositiondata) structure that is filled in for the position at the given index.
* **Index**: The zero-based index number of the position for which position data is to be returned.

### sc.GetTradePositionForSymbolAndAccount()

[Link](#scgettradepositionforsymbolandaccount) - [Top](#top)

int **sc.GetTradePositionForSymbolAndAccount**(s\_SCPositionData& **PositionData**, const SCString& **Symbol**, const SCString& **TradeAccount**);

The **sc.GetTradePositionForSymbolAndAccount()** function returns the current Trade Position data for the specified **Symbol** and **TradeAccount**.

This function works identically to the [sc.GetTradePosition](#scgettradeposition) function except that the Symbol and TradeAccount are specified to get the Trade Position data for those. Therefore, the documentation for the [sc.GetTradePosition](#scgettradeposition) also applies to this function.

Only the following members of the [s\_SCPositionData](#sscpositiondata) structure are filled out when this function returns.

* **s\_SCPositionData::Symbol**
* **s\_SCPositionData::PositionQuantity**
* **s\_SCPositionData::AveragePrice**: Accurate for Trade Simulation Mode Positions. For non-simulated trading it may or may not be set.
* **s\_SCPositionData::PositionQuantityWithAllWorkingOrders**
* **s\_SCPositionData::PositionQuantityWithExitWorkingOrders**
* **s\_SCPositionData::WorkingOrdersExist**
* **s\_SCPositionData::PositionQuantityWithExitMarketOrders**

#### Parameters

* **PositionData**: A reference to an [s\_SCPositionData](#sscpositiondata) structure that is filled in for the position at the given index.
* **Symbol**: The symbol for which position data is requested.
* **TradeAccount**: The trading account for which position data is requested.

### s\_SCPositionData Structure Members

[Link](#sscpositiondata) - [Top](#top)

#### [Type: SCString] **Symbol**

[Link](#sscpositiondatasymbol) - [Top](#top)

The Symbol of the Trade Position.

#### [Type: double] **PositionQuantity**

[Link](#sscpositiondatapositionquantity) - [Top](#top)

The quantity of the current Trade Position as displayed in the **Trade >> Trade Positions Window**.

A positive quantity represents a Long position and a negative quantity represents a Short position.

#### [Type: double] **AveragePrice**

[Link](#sscpositiondataaverageprice) - [Top](#top)

The average fill price of the current Trade Position.

The average price will be according to the [Open Position Average Price](ChartSettings.md#openpositionaverageprice) setting. For more information refer to [How Average Price for Positions Is Calculated and Used](TradeStatusWindows.md#howaveragepriceforpositionsiscalculatedandused).

#### [Type: double] **OpenProfitLoss**

[Link](#sscpositiondataopenprofitloss) - [Top](#top)

This is the Profit or Loss of the current open Trade Position. This is calculated using the most recent last trade price for the symbol.

If a **Currency Value per Tick** is set in the **Chart >> Chart Settings**, then this is provided as a Currency Value.

#### [Type: double] **CumulativeProfitLoss**

[Link](#sscpositiondatacumulativeprofitloss) - [Top](#top)

This is the Profit or Loss of closed trades that have been made where order fill data is available for those trades. This uses a **Fill to Fill** order fill grouping method.

If a **Currency Value per Tick** is set in the **Chart >> Chart Settings**, then this is provided as a Currency Value.

For this member to be set, you need to set **sc.MaintainTradeStatisticsAndTradesData** to TRUE (1) in your study function.

This is calculated from the order fill data in the **Trade >> Trade Activity Log >> Trade Activity** tab.

#### [Type: double] **DailyProfitLoss**

[Link](#sscpositiondatadailyprofitloss) - [Top](#top)

This is the Profit or Loss of trades made that have been closed during the day for the symbol. This uses a **Fill to Fill** order fill grouping method.

This is calculated from the order fill data in **Trade >> Trade Activity Log >> Trade Activity** tab.

This is considered a Daily Trade Statistic which resets daily. For complete details, refer to [Understanding Daily Trade Statistics Reset Time](TradeActivityLog.md#understandingdailytradestatisticsresettime).

If a **Currency Value per Tick** is set in the **Chart >> Chart Settings**, then this is provided as a Currency Value.

For this member to be set, you need to set **sc.MaintainTradeStatisticsAndTradesData** to TRUE in your study function.

#### [Type: double] **MaximumOpenPositionLoss**

[Link](#sscpositiondatamaximumopenpositionloss) - [Top](#top)

This is the maximum loss that occurred during the currently open Trade Position. This is calculated from the current Trade Position data which consists of the PriceHighDuringPosition, PriceLowDuringPosition, and [Position Average Price](TradeStatusWindows.md#howaveragepriceforpositionsiscalculatedandused) values.

It is reset to 0 every time there is a new order fill for the symbol which changes the current Trade Position.

If a **Currency Value per Tick** is set in the **Chart >> Chart Settings**, then this is provided as a Currency Value.

#### [Type: double] **MaximumOpenPositionProfit**

[Link](#sscpositiondatamaximumopenpositionprofit) - [Top](#top)

This is the maximum profit that occurred during the currently open Trade Position. This is calculated from the current Trade Position data which consists of the PriceHighDuringPosition, PriceLowDuringPosition, and [Position Average Price](TradeStatusWindows.md#howaveragepriceforpositionsiscalculatedandused) values.

It is reset to 0 every time there is a new order fill for the symbol which changes the current Trade Position.

If a **Currency Value per Tick** is set in the **Chart >> Chart Settings**, then this is provided as a Currency Value.

#### [Type: double] **LastTradeProfitLoss**

[Link](#sscpositiondatalasttradeprofitloss) - [Top](#top)

This member provides the Profit or Loss for the last trade that was made that closes out a Trade Position or reduces the size of the Trade Position. This is calculated from the order fill data in the **Trade >>Trade Activity Log >> Trade Activity** tab.

This uses a Fill to Fill order fill grouping method for Trades.

If a **Currency Value per Tick** is set in the **Chart >> Chart Settings**, then this is provided as a Currency Value.

For this member to be set, you need to set **sc.MaintainTradeStatisticsAndTradesData** to TRUE in your study function.

#### [Type: integer] **PositionQuantityWithAllWorkingOrders**

[Link](#sscpositiondatapositionquantitywithallworkingorders) - [Top](#top)

This variable indicates the Internal Position Quantity for the symbol as displayed in the **Trade >> Trade Positions Window**, combined with the quantities of all working orders.

Working Sell orders decrease the Position Quantity and Buy orders increase the Position Quantity. In the case of when there are two orders in an OCO group, the quantity of only one of those orders is counted.

Example: There is a Position Quantity of +1, there are two working sell orders each with a quantity of 1. These working sell orders are in an OCO group. Therefore, this variable would return: 0 = +1 + -1.

#### [Type: integer] **PositionQuantityWithExitWorkingOrders**

[Link](#sscpositiondatapositionquantitywithexitworkingorders) - [Top](#top)

This variable indicates the Position quantity for the symbol as displayed in the **Trade >> Trade Positions Window**, combined with the quantities of working orders that will reduce the size of the Position.

Working Sell orders decrease the position and Buy orders increase the position. In the case of when there are two orders in an OCO group, the quantity of only one of those orders is counted.

Example: There is a position of +1, there are two working sell orders each with a quantity of 1. These working sell orders are in an OCO group. Therefore, this variable would return 0 = +1 + -1.

#### [Type: integer] **WorkingOrdersExist**

[Link](#sscpositiondataworkingordersexist) - [Top](#top)

This variable will be set to a nonzero value when there are working orders. Otherwise, it will be 0.

#### [Type: SCDateTime] **LastFillDateTime**

[Link](#sscpositiondatalastfilldatetime) - [Top](#top)

This is the Date-Time of the most recent order fill for the symbol.

This data is from the **Trade >>Trade Activity Log >> Trade Activity** tab. The order fill data in the Trade Activity Log consists of order fills received in real-time and downloaded upon the initial connection to the trade server.

This time is adjusted to the Time Zone setting in Sierra Chart and is derived from your local computer clock, or from the chart bars if the fill occurred during a chart replay.

For this member to be set, you need to set **sc.MaintainTradeStatisticsAndTradesData** to TRUE in your study function.

#### [Type: SCDateTime] **LastEntryDateTime**

[Link](#sscpositiondatalastentrydatetime) - [Top](#top)

This is the Date-Time of the most recent order fill for the symbol that established or increased the size of the Trade Position.

This data is from the **Trade >>Trade Activity Log >> Trade Activity** tab. The order fill data in the Trade Activity Log consists of order fills received in real-time and downloaded upon the initial connection to the trade server.

This time is adjusted to the Time Zone setting in Sierra Chart and is derived from your local computer clock, or from the chart bars if the fill occurred during a chart replay.

For this member to be set, you need to set **sc.MaintainTradeStatisticsAndTradesData** to TRUE in your study function.

#### [Type: SCDateTime] **LastExitDateTime**

[Link](#sscpositiondatalastexitdatetime) - [Top](#top)

This is the Date-Time of the most recent order fill for the symbol that decreased the size of the Trade Position or flattened the Trade Position.

This data is from the **Trade >>Trade Activity Log >> Trade Activity** tab. The order fill data in the Trade Activity Log consists of order fills received in real-time and downloaded upon the initial connection to the trade server.

This time is adjusted to the Time Zone setting in Sierra Chart and is derived from your local computer clock, or from the chart bars if the fill occurred during a chart replay.

For this member to be set, you need to set **sc.MaintainTradeStatisticsAndTradesData** to TRUE in your study function.

#### [Type: integer] **PriorPositionQuantity**

[Link](#sscpositiondatapriorpositionquantity) - [Top](#top)

This variable indicates what the Prior Trade Position Quantity was before it last changed.

#### [Type: integer] **PositionQuantityWithExitMarketOrders**

[Link](#sscpositiondatapositionquantitywithexitmarketorders) - [Top](#top)

This variable indicates the Trade Position Quantity reduced by the quantities of market orders which reduce the Position Quantity.

#### [Type: integer] **TotalQuantityFilled**

[Link](#sscpositiondatatotalquantityfilled) - [Top](#top)

This variable indicates the total quantity of the order fills among all of the order fills for the Symbol and Trade Account loaded in the chart.

It is not the total quantity filled for the trading day.

#### [Type: integer] **LastTradeQuantity**

[Link](#sscpositiondatalasttradequantity) - [Top](#top)

This variable indicates the quantity of the last order fill.

#### [Type: integer] **NonAttachedWorkingOrdersExist**

[Link](#sscpositiondatanonattachedworkingordersexist) - [Top](#top)

This variable is 1 if there are working/open trade orders that exist for the Symbol and Trade Account of the chart, that are not Attached Orders. Otherwise, it is 0.

## Other Trade Related Items

[Link](#othertraderelatedfunctions) - [Top](#top)

### sc.FlattenPositionsAndCancelOrdersForTradeAccount()

[Link](#scflattenpositionsandcancelordersfortradeaccount) - [Top](#top)

**Type**: Function

int32\_t **FlattenPositionsAndCancelOrdersForTradeAccount**(const SCString& **TradeAccount**);

The **sc.FlattenPositionsAndCancelOrdersForTradeAccount** flattens open positions and cancels orders for the given trade account.

#### Parameters

* **TradeAccount**: The trading account for which the flatten and cancel actions should be applied.

### sc.GetAttachedOrders()

[Link](#scgetattachedorders) - [Top](#top)

**Type**: Function

int32\_t **GetAttachedOrders**(s\_SCNewOrder& **r\_AttachedOrdersConfiguration**);

The **sc.GetAttachedOrders()** function, fills out the given r\_AttachedOrdersConfiguration parameter with the Attached Order configuration currently set on the Trade Window for the chart the study instance which is calling this function is applied to.

#### Parameters

* **r\_AttachedOrdersConfiguration**: This is a data structure of type [s\_SCNewOrder](#sscneworder) which is passed by reference and receives the Attached Order configuration by having its Attached Order members set.

#### Example

```cpp

	s_SCNewOrder AttachedOrdersConfiguration;
	sc.GetAttachedOrders(AttachedOrdersConfiguration);

	double PriceOffset = AttachedOrdersConfiguration.Target1Offset;            
            
```

### sc.GetNearestStopWorkingAttachedOrder()

[Link](#scgetneareststopworkingattachedorder) - [Top](#top)

**Type**: Function

int32\_t **GetNearestStopWorkingAttachedOrder**(s\_SCTradeOrder& **OrderDetails**);

The **sc.GetNearestStopWorkingAttachedOrder()** function gets the working Stop Attached Order nearest the current price for the symbol of the chart.

#### Parameters

* **OrderDetails**: This is a data structure of type [s\_SCTradeOrder](#ssctradeorder) which receives all of the details of the Stop Attached order.

#### Example

```cpp

s_SCTradeOrder OrderDetails;

sc.GetNearestStopWorkingAttachedOrder(OrderDetails);    
            
```

### sc.GetNearestTargetWorkingAttachedOrder()

[Link](#scgetnearesttargetworkingattachedorder) - [Top](#top)

**Type**: Function

int32\_t **GetNearestTargetWorkingAttachedOrder**(s\_SCTradeOrder& **OrderDetails**);

The **sc.GetNearestTargetWorkingAttachedOrder()** function gets the working Target Attached Order nearest the current price for the symbol of the chart. The Target order is typically a [Limit order type](OrderTypes.md#limit).

#### Parameters

* **OrderDetails**: This is a data structure of type [s\_SCTradeOrder](#ssctradeorder) which receives the details of the Stop Attached order.

#### Example

```cpp

s_SCTradeOrder OrderDetails;

sc.GetNearestTargetWorkingAttachedOrder(OrderDetails);   
            
```

### sc.GetNumAttachedOrders()

[Link](#scgetnumattachedorders) - [Top](#top)

**Type**: Function

int32\_t **GetNumAttachedOrders**();

The **sc.GetNumAttachedOrders()** function returns the number of attached orders set in the Targets tab of the Trade Window for the chart on which the study that calls this function is located.

#### Parameters

* This function has no parameters

### sc.GetNumTradeAccounts()

[Link](#scgetnumtradeaccounts) - [Top](#top)

**Type**: Function

int32\_t **GetNumTradeAccounts**();

This function returns an integer value of the number of Trade Accounts available for the chart on which the study is applied.

#### Parameters

* This function has no parameters

### sc.GetStopOrderInOCOGroupNumber()

[Link](#scgetstoporderinocogroupnumber) - [Top](#top)

**Type**: Function

int **GetStopOrderInOCOGroupNumber**( const int **OCOGroupNumber**, s\_SCTradeOrder& **OrderDetails**);

This function fills in the Stop Order details for the Stop that is part of the specified OCO Group Number.

#### Parameters

* **OCOGroupNumber**: The [OCO Group](AttachedOrders.md#ocogroup) number as an integer. This is a one based value. Ranging from 1 through 8.
* **OrderDetails**: This is a reference to a structure of type s\_SCTradeOrder which receives the order details.

#### Example

```cpp

s_SCTradeOrder TradeOrder;           
int Result = sc.GetStopOrderInOCOGroupNumber(1, TradeOrder);
            
```

### sc.GetTargetOrderInOCOGroupNumber()

[Link](#scgettargetorderinocogroupnumber) - [Top](#top)

**Type**: Function

int **GetTargetOrderInOCOGroupNumber**(const int **OCOGroupNumber**, s\_SCTradeOrder& **OrderDetails**);

The **sc.GetTargetOrderInOCOGroupNumber()** function fills in the Target Order details for the Target is that is part of the specfied OCO Group Number.

#### Parameters

* **OCOGroupNumber**: The OCO group number. This is the one based group number that is defined on the Trade Window.
* **OrderDetails**:a reference to an [s\_SCTradeOrder](#ssctradeorder) structure that contains the order details for the given OCO group number.

### sc.GetTradeAccountAtIndex()

[Link](#scgettradeaccountatindex) - [Top](#top)

**Type**: Function

int32\_t **GetTradeAccountAtIndex**(const int32\_t **Index**, SCString& **r\_TradeAccount**);

The **sc.GetTradeAccountAtIndex()** function fills in the trade account name for the trade account defined at the given index.

#### Parameters

* **Index**: The zero-based index for the trade accounts.
* **r\_TradeAccount**: An SCString that holds the trade account name for the given trade account index.

### sc.GetTradeAccountData()

[Link](#scgettradeaccountdata) - [Top](#top)

**Type**: Function

int **GetTradeAccountData**(n\_ACSIL::s\_TradeAccountDataFields& **r\_TradeAccountDataFields**, const SCString& **TradeAccount**);

The **sc.GetTradeAccountData()** function gets all of the Trade Account Data fields for the specified Trade Account.

#### Parameters

* **r\_TradeAccountDataFields**: This is a reference to a variable of structure type n\_ACSIL::s\_TradeAccountDataFields which receives the Trade Account Data fields.
* **TradeAccount**: This is the trade account identifier as a string. To specify the same trade account the chart is set to that the study instance is applied to, use **sc.SelectedTradeAccount** for this parameter.

#### Example

```cpp
        
n_ACSIL::s_TradeAccountDataFields TradeAccountDataFields;
if (sc.GetTradeAccountData(TradeAccountDataFields, sc.SelectedTradeAccount))
{
    double AccountValue = TradeAccountDataFields.m_AccountValue;
}
            
```

### sc.GetTradeServiceAccountBalanceForTradeAccount()

[Link](#scgettradeserviceaccountbalancefortradeaccount) - [Top](#top)

**Type**: Function

double **GetTradeServiceAccountBalanceForTradeAccount**(const SCString& **TradeAccount**);

The **sc.GetTradeServiceAccountBalanceForTradeAccount()** function, returns the account balance from the external trading service for the specified **TradeAccount**.

#### Parameters

* **TradeAccount**: The trade account for which the account balance is desired.

### sc.GetTradingErrorTextMessage()

[Link](#scgettradingerrortextmessage) - [Top](#top)

**Type**: Function

const char \* **GetTradingErrorTextMessage**(int **ErrorCode**);

The **sc.GetTradingErrorTextMessage()** function retrieves the full text error message for a given error code.

#### Parameters

* **ErrorCode**: The error code itself, such as **SCTRADING\_ORDER\_ERROR**.

### sc.GetUseAttachedOrdersEnabledState()

[Link](#scgetuseattachedordersenabledstate) - [Top](#top)

**Type**: Function

int32\_t **GetUseAttachedOrdersEnabledState**();

The **sc.GetUseAttachedOrdersEnabledState()** function returns the enabled/disabled state of the **Use Attached Orders** option for the trading window associated with the chart on which the study that calls this function is located.

A return value of 1 indicates **Use Attached Orders** is Enabled. A return value of 0 indicates **Use Attached Orders** is Disabled.

#### Parameters

* This function has no parameters

### sc.SendHeldTradeOrder()

[Link](#scsendheldtradeorder) - [Top](#top)

**Type**: Function

int32\_t **SendHeldTradeOrder**(const uint64\_t **InternalOrderID**);

The **SendHeldTradeOrder()** function sends a held order defined by the InternalOrderID to the trade service.

#### Parameters

* **InternalOrderID**: The Internal Order ID of the held order to send.

## Programmatically Setting Trade Window Configuration

[Link](#programmaticallysettingtradewindowconfiguration) - [Top](#top)

It is supported to programmatically change the Trade Window configuration to a previously saved configuration. For information about Trade Window configurations, refer to [Using and Changing Between Different Trade Window and Attached Orders Configurations](TradeWindow.md#tradewindowconfigurations).

To change the saved Trade Window configuration through ACSIL, refer to [sc.TradeWindowConfigFileName](ACSIL_Members_Variables_And_Arrays.md#sctradewindowconfigfilename).

## Going from Simulation Mode to Live Trading

[Link](#simulationtolive) - [Top](#top)

An ACSIL automated trading system can either send orders to the internal Sierra Chart Trade Simulation system or to the connected Trading service.

This is controlled by the **Trade >> Trade Simulation Mode On** setting *and* the **sc.SendOrdersToTradeService** ACSIL variable. For complete information, refer to [sc.SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice).

For the automated trading system study to be allowed to send orders whether simulated or non-simulated, it is also necessary to enable **Trade >> Auto Trading Enabled**.

When you want the automated trading system to be able to respond to real-time updating data, it is necessary that Sierra Chart is connected to the data feed. This is done through **File >> Connect to Data Feed**. Refer to [When the Study Function Is Called](ACS_ArraysAndLooping.md#whenthestudyfunctioniscalled) to understand when the study function will be called and therefore when it will do processing which can submit orders.

It is important to be aware that even if you have set your automated trading system and Sierra Chart to send the orders to the connected Trading service, if Sierra Chart is connected to a simulation account with your Trading service, then the submitted orders *will still be simulated through your Trading service*.

*Verify* with your Trading service whether Sierra Chart is actually connected to a simulation account. Check to make certain that any orders your automated trading system is sending are being processed in a simulation environment with your trading service, *or if the orders are live*. There is the potential for confusion and you need to be aware if the orders are live or simulated. This can avoid costly mistakes.

It is a good idea to add an Input to your study that controls **sc.SendOrdersToTradeService**. Refer to the code example below.

### Code Example

```cpp

SCInputRef SendOrdersToService = sc.Input[10];

if (sc.SetDefaults)
{
    SendOrdersToService.Name = "Send Orders to Trade Service";
    SendOrdersToService.SetYesNo(false);
    return;
}

sc.SendOrdersToTradeService = SendOrdersToService.GetYesNo();
        
```

## Constants

[Link](#constants) - [Top](#top)

This section lists various constant identifiers used by ACSIL trading functions and the meaning of them.

### Order Type Constants

[Link](#ordertypeconstants) - [Top](#top)

The Order Type constants are listed below. For descriptions of these Order Types, refer to [Order Types](OrderTypes.md).

* **SCT\_ORDERTYPE\_MARKET**
* **SCT\_ORDERTYPE\_LIMIT**
* **SCT\_ORDERTYPE\_STOP**
* **SCT\_ORDERTYPE\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_MARKET\_IF\_TOUCHED**
* **SCT\_ORDERTYPE\_LIMIT\_CHASE**
* **SCT\_ORDERTYPE\_LIMIT\_TOUCH\_CHASE**
* **SCT\_ORDERTYPE\_TRAILING\_STOP**
* **SCT\_ORDERTYPE\_TRAILING\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS**: When used as an Attached Order, the initial offset is specified by [s\_SCNewOrder::Target1Offset](#sscnewordertarget1offset). The trigger offset is specified by [s\_SCNewOrder::AttachedOrderStop1\_TriggeredTrailStopTriggerPriceOffset](#sscneworderattachedorderstop1triggeredtrailstoptriggerpriceoffset). The trailing offset is specified by [s\_SCNewOrder::AttachedOrderStop1\_TriggeredTrailStopTrailPriceOffset](#sscneworderattachedorderstop1triggeredtrailstoptrailpriceoffset)
* **SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_LIMIT\_3\_OFFSETS**: Refer to the notes above for SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS.
* **SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP**
* **SCT\_ORDERTYPE\_STEP\_TRAILING\_STOP\_LIMIT**
* **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP**: Refer to the notes above for SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS.
* **SCT\_ORDERTYPE\_TRIGGERED\_STEP\_TRAILING\_STOP\_LIMIT**: Refer to the notes above for SCT\_ORDERTYPE\_TRIGGERED\_TRAILING\_STOP\_3\_OFFSETS.
* **SCT\_ORDERTYPE\_OCO\_LIMIT\_STOP**: Use **s\_NewOrder::Price1**  to set the Limit price and **s\_NewOrder::Price2** to set the Stop price. Use **sc.BuyOrder()** or **sc.SellOrder** to submit the order when using this order type. All of the standard [Auto Trade Management](AutoTradeManagment.md) logic applies when using this order type, so you may want to use [Unmanaged Automated Trading](AutoTradeManagment.md#unmanagedautomatedtrading) when submitting this type of order, so there are no restrictions.
* **SCT\_ORDERTYPE\_OCO\_LIMIT\_STOP\_LIMIT**: Use **s\_NewOrder::Price1** to set the Limit price and **s\_NewOrder::Price2** to set the Stop price. Use **sc.BuyOrder()** or **sc.SellOrder** to submit the order when using this order type. All of the standard [Auto Trade Management](AutoTradeManagment.md) logic applies when using this order type, so you may want to use [Unmanaged Automated Trading](AutoTradeManagment.md#unmanagedautomatedtrading) when submitting this type of order, so there are no restrictions.
* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP**: Use **s\_NewOrder::Price1** to set the first Stop price and **s\_NewOrder::Price2** to set the second Stop price. Use **sc.SubmitOCOOrder()** to submit the order when using this Order type. There will be both a Buy and a Sell order submitted. None of the [Auto Trade Management](AutoTradeManagment.md) logic applies when using this order type, so there are no restrictions when submitting this order.
* **SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_LIMIT\_SELL\_STOP\_LIMIT**: Use **s\_NewOrder::Price1**  to set the first Stop price and **s\_NewOrder::Price2**  to set the second Stop price. Use **sc.SubmitOCOOrder()** to submit the order when using this Order type. There will be both a Buy and a Sell order submitted. None of the [Auto Trade Management](AutoTradeManagment.md) logic applies when using this order type, so there are no restrictions when submitting this order.
* **SCT\_ORDERTYPE\_OCO\_BUY\_LIMIT\_SELL\_LIMIT**: Use **s\_NewOrder::Price1** to set the first Limit price and **s\_NewOrder::Price2** to set the second Limit price. Use **sc.SubmitOCOOrder()** to submit the order when using this Order type. There will be both a Buy and a Sell order submitted. None of the [Auto Trade Management](AutoTradeManagment.md) logic applies when using this order type, so there are no restrictions when submitting this order.
* **SCT\_ORDERTYPE\_LIMIT\_IF\_TOUCHED**.
* **SCT\_ORDERTYPE\_BID\_ASK\_QUANTITY\_TRIGGERED\_STOP**: When used as an Attached Order, the quantity is set through s\_SCNewOrder::QuantityTriggeredAttachedStop\_QuantityForTrigger.
* **SCT\_ORDERTYPE\_TRIGGERED\_LIMIT**: When used as the main order, the Limit is set with **s\_SCNewOrder::Price1** and the Trigger is set with **s\_SCNewOrder::Price2**.
* **SCT\_ORDERTYPE\_TRADE\_VOLUME\_TRIGGERED\_STOP**: When used as an Attached Order, the quantity is set through **s\_SCNewOrder::QuantityTriggeredAttachedStop\_QuantityForTrigger**.
* **SCT\_ORDERTYPE\_STOP\_WITH\_BID\_ASK\_TRIGGERING**.
* **SCT\_ORDERTYPE\_STOP\_WITH\_LAST\_TRIGGERING**.
* **SCT\_ORDERTYPE\_LIMIT\_IF\_TOUCHED\_CLIENT\_SIDE**.
* **SCT\_ORDERTYPE\_MARKET\_IF\_TOUCHED\_CLIENT\_SIDE**.
* **SCT\_ORDERTYPE\_TRADE\_VOLUME\_TRIGGERED\_STOP\_LIMIT**: When used as an Attached Order, the quantity is set through **s\_SCNewOrder::QuantityTriggeredAttachedStop\_QuantityForTrigger**.
* **SCT\_ORDERTYPE\_STOP\_LIMIT\_CLIENT\_SIDE**.
* **SCT\_ORDERTYPE\_TRIGGERED\_STOP**.

### Order Error Constants

[Link](#ignoredordererror) - [Top](#top)

These order error constant codes indicate specific reasons an order or other trading action may have been skipped and not processed.

To programmatically obtain the text description for one of these numeric error codes returned from a trading function, call the function **const char \* sc.GetTradingErrorTextMessage(int ErrorCode)** and pass the error code.

* **SCTRADING\_ORDER\_ERROR** (-1): The ACSIL trading functions will return this error.
    
    
  In this particular case, a detailed error message explaining the specific issue will be listed in the **Trade >> Trade Service Log**.
    
    
  In the case where the error is related to a version number, the error instead will be displayed in the **Window >> Message Log**.
    
    
  In the case of a non-simulated order submission to an external trading service, if Sierra Chart is not connected to an external service this will cause **SCTRADING\_ORDER\_ERROR** to be returned. In the case where a non-simulated order is successfully submitted, but it is later rejected by the external service, the order submission function will not return**SCTRADING\_ORDER\_ERROR**. You will need to check the order status by getting the [details of the order](#gettingorderinformation).
* **SCTRADING\_NOT\_OCO\_ORDER\_TYPE**(-2): This error occurs when the **sc.SubmitOCOOrder** function is called and the OrderType is not one of SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_SELL\_STOP, SCT\_ORDERTYPE\_OCO\_BUY\_STOP\_LIMIT\_SELL\_STOP\_LIMIT, or SCT\_ORDERTYPE\_OCO\_BUY\_LIMIT\_SELL\_LIMIT.
* **SCTRADING\_ATTACHED\_ORDER\_OFFSET\_NOT\_SUPPORTED\_WITH\_MARKET\_PARENT**(-3): When using the [Submitting and Managing Orders for Different Symbol and/or Trade Account](#submittingordersdifferentsymbolaccount) functionality, and an attached order *offset* is specified instead of a *price*, with a parent order that is a Market order type, then this error will be returned and the orders are rejected.
* **SCTRADING\_UNSUPPORTED\_ATTACHED\_ORDER**(-4): When using the [Submitting and Managing Orders for Different Symbol and/or Trade Account](#submittingordersdifferentsymbolaccount) functionality, and one or more attached orders are specified for OCO Group 2 or higher, then this error will be returned and the orders are rejected.
* **SCTRADING\_SYMBOL\_SETTINGS\_NOT\_FOUND**(-5): This error code is returned by the **sc.BuyOrder** and **sc.SellOrder** functions. This error indicates that there is a dependency upon the **Tick Size** and **Price Display Format** for the Symbol being traded and that the Symbol is not defined in [Global Symbol Settings](GlobalSymbolSettings.md). The Symbol or Symbol Pattern needs to be added in that settings window to be able to submit an order for it.
* **ACSIL\_GENERAL\_NULL\_POINTER\_ERROR**(-6): This indicates that a null pointer was encountered when accessing one of the dependent objects needed for the particular function. This should never be returned.
* **SCT\_SKIPPED\_DOWNLOADING\_HISTORICAL\_DATA**: The trade action was skipped because historical data is currently being downloaded for the chart.
* **SCT\_SKIPPED\_FULL\_RECALC**: The trade action was skipped because the trading study is performing a full recalculation. A full recalculation occurs when the trading study is applied to the chart, **Chart >> Reload and Recalculate** is selected, a chart replay has been started, or a condition which causes a reload of chart data has occured such as modifying the settings for the trading study, a full recalculation is being performed due to a study on the chart that references another chart requires a full recalculation.
    
     
  Once there is a full recalculation, then any additional updating of the chart from real-time data or from a chart replay, is not a full recalculation and the trade actions will be followed assuming there are no other conditions causing them to be ignored.
* **SCT\_SKIPPED\_ONLY\_ONE\_TRADE\_PER\_BAR**: An order was skipped because the trading study has specified that only one Order Action type can occur per bar and the same Order Action type has already occurred. This is set with sc.AllowOnlyOneTradePerBar.
* **SCT\_SKIPPED\_INVALID\_INDEX\_SPECIFIED**: An order was skipped because the trading study has specified an invalid sc.Subgraph[][] array index to one of the Order Action functions.
* **SCT\_SKIPPED\_TOO\_MANY\_NEW\_BARS\_DURING\_UPDATE**: The trade action was skipped because there have been more than 100 new bars during the chart update. This is meant to be a safety feature in order to prevent trade actions from occurring on new chart bar data that might not possibly be from normal real-time or replay updating.
* **SCT\_SKIPPED\_AUTO\_TRADING\_DISABLED**: The trade action was skipped because **Trade >> Auto Trading Enabled** is disabled.

## Example Trading Systems and Code

[Link](#examplecode) - [Top](#top)

There are many ACSIL trading system study and other trading related study examples provided.

Refer to the [Example ACSIL Trading Systems](ACSIL_ExampleTradingSystems.md) page for an example.

Additionally, look in the **/ACS\_Source/TradingSystem.cpp** file in the folder Sierra Chart is installed to on your system. This file contains many ACSIL trading system studies that use the ACSIL trading functions. These functions demonstrate all of the available functionality.

The following files contain trading related code which serve as good examples for specific trading related tasks:

* **/ACS\_Source/TradingTriggeredLimitOrderEntry.cpp**
* **/ACS\_Source/AutomatedTradeManagementBySubgraph.cpp**
* **/ACS\_Source/OrderEntryStudies.cpp**

### How to Apply the Trading Example System Studies To The Chart For Testing

1. These steps explain using the trading system studies provided in the **TradingSystem.cpp** file.
2. Select **Analysis >> Studies >> Add Custom Study >> Sierra Chart Custom Studies and Examples**.
3. In the list you will see several studies that begin with: **Trading Example:**. Choose one of them.
4. Press the **Add** button.
5. Press **Settings** on the **Chart Studies** window to display the **Study Settings** window. Or, it may have already opened if you have the option to open it upon adding a study enabled.
6. Make certain the **Settings and Inputs** tab is selected. Set the **Enabled** Input to **Yes**. If this is not set to **Yes**, the auto trading system will not function.
7. Press OK. Press OK.
8. You will need to enable auto trading in Sierra Chart. To do this make certain there is a checkmark by **Trade >> Auto Trading Enabled**. You may also want to uncheck **Disable Auto Trading on Start Up**.
9. Initially, the study will not display any Buy or Sell arrows on the chart because a trading system will only work with new data added to the chart during live updating, with new data added during a chart Replay, or by performing a Back Test.
     
      
   Therefore, you will need to wait for some live data to be received in the chart or you can perform a Back Test. You can perform a *Replay* or *Bar Based* back test. Refer to the [Back Testing](Backtesting.md) documentation section for instructions.
10. Check the **Trade >> Trade Service Log** for any ignored order signals.
11. To view the results of the Back Test, refer to [Viewing Back Test Results](Backtesting.md#viewingbacktestresults).

## Debugging/Troubleshooting Automated Trading Systems

[Link](#debuggingtradingsystems) - [Top](#top)

When an automated trading system is not submitting orders when expected or performing some other trading action, then you need to add the trading error handling code as shown in the below code example.

However, the first thing to check is that **Trade >> Auto Trading Enabled** is checked. Also, refer to [SendOrdersToTradeService](AutoTradeManagment.md#sendorderstotradeservice).

The exact reason why a particular order action, **sc.BuyEntry**, **sc.BuyExit**, **sc.SellEntry**, **sc.SellExit**, **sc.BuyOrder**, **sc.SellOrder**, or one of the [Cancel Order or Trade Position Flatten](#cancelflattenfunctions) function calls is being ignored due to the automated trading management logic, will be listed in the Sierra Chart [Message Log](MesssageLog.md) when using the trading error handling code below. In some cases this message may say to refer to the **Trade >> Trade Service Log** for a descriptive error message. In that case refer to the Trade Service Log.

This **Window >> Message Log** entry will help you understand the reason for the trading action being ignored. If you need help understanding a specific message, contact Sierra Chart support on the [Support Board](https://www.sierrachart.com/SupportBoard.php).

```cpp
    
// Example of submitting an order and handling error condition
s_SCNewOrder NewOrder;
NewOrder.OrderQuantity = 1;
NewOrder.OrderType = SCT_LIMIT;
NewOrder.TimeInForce = SCT_TIF_DAY;
NewOrder.Price1 = sc.Close[sc.Index] ;
int Result = sc.BuyEntry(NewOrder);
if (Result > 0)//order was accepted
{
    //Take appropriate action if order is successful
}
else//order error
{
    //Only report error if at the last bar
    if (sc.Index == sc.ArraySize -1)
    {
        //Add error message to the Sierra Chart Message Log for interpretation
        sc.AddMessageToLog(sc.GetTradingErrorTextMessage(Result), 0);
    }
}
    
```

If there is no error returned, then use the [Trade Activity Log](TradeActivityLog.md) to have a better understanding of the particular problem you are encountering.

Another method of debugging an automated trading system and custom studies in general, is to perform step-by-step debugging using the Visual C++ debugger. For instructions, refer to [Step-by-step ACSIL Debugging](StepByStepACSILDebugging.md).

---

\*Last modified Monday, 30th June, 2025.
