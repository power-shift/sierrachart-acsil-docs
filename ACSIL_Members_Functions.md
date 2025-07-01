# ACSIL Interface Members - Functions

## Related Documentation

* [ACSIL Interface Members - Introduction](ACSIL_Members.md)
* [ACSIL Interface Members - Variables and Arrays](ACSIL_Members_Variables_And_Arrays.md)
* [ACSIL Interface Members - sc.Input Array](ACSIL_Members_scInputs.md)
* [ACSIL Interface Members - sc.Subgraph Array](ACSIL_Members_scSubgraph.md)
* **ACSIL Interface Members - Functions**
* [ACSIL Interface Members - Graphics Functions](ACSIL_Members_GraphicsFunctions.md)

---

## On This Page

* [Notes About Output Arrays for Functions](#notesaboutoutputarraysforfunctions)
* [Array Based Study Functions That Do Not Use the Index Parameter](#noindexparam)
* [Return Object of Array Based Study Functions](#returnobjectarraybasedstudyfunction)
* [Working with Intermediate Study Calculation Functions](#workingwithintermediatestudycalculationfunctions)
* [Cumulative Calculations with Intermediate Study Functions](#cumulativecalculationswithintermediatestudyfunctions)
* [Functions](#functions)
  + [sc.AdaptiveMovAvg()](#scadaptivemovavg)
  + [sc.AddACSChartShortcutMenuItem()](#scaddacschartshortcutmenuitem)
  + [sc.AddACSChartShortcutMenuSeparator()](#scaddacschartshortcutmenuseparator)
  + [sc.AddAlertLine()](#scaddalertline)
  + [sc.AddAlertLineWithDateTime()](#scaddalertlinewithdatetime)
  + [sc.AddAndManageSingleTextDrawingForStudy()](#scaddandmanagesingletextdrawingforstudy)
  + [sc.AddAndManageSingleTextUserDrawnDrawingForStudy()](#scaddandmanagesingletextuserdrawndrawingforstudy)
  + [sc.AddDateToExclude()](#scadddatetoexclude)
  + [sc.AddElements()](#scaddelements)
  + [sc.AddLineUntilFutureIntersection()](#scaddlineuntilfutureintersection)
  + [sc.AddLineUntilFutureIntersectionEx()](#scaddlineuntilfutureintersectionex)
  + [sc.AddMessageToLog()](#scaddmessagetolog)
  + [sc.AddStudyToChart()](#scaddstudytochart)
  + [sc.AdjustDateTimeToGMT()](#scadjustdatetimetogmt)
  + [sc.ADX()](#scadx)
  + [sc.ADXR()](#scadxr)
  + [sc.AlertWithMessage()](#scalertwithmessage)
  + [sc.AllocateMemory()](#scallocatememory)
  + [sc.AngleInDegreesToSlope()](#scangleindegreestoslope)
  + [sc.ApplyStudyCollection()](#scapplystudycollection)
  + [sc.ArmsEMV()](#scarmsemv)
  + [sc.ArnaudLegouxMovingAverage()](#scarnaudlegouxmovingaverage)
  + [sc.AroonIndicator()](#scaroonindicator)
  + [sc.ArrayValueAtNthOccurrence()](#scarrayvalueatnthoccurrence)
  + [sc.ATR()](#scatr)
  + [sc.AwesomeOscillator()](#scawesomeoscillator)
  + [sc.BarIndexToXPixelCoordinate()](#scbarindextoxpixelcoordinate)
  + [sc.BollingerBands()](#scbollingerbands)
  + [sc.Butterworth2Pole()](#scbutterworth2pole)
  + [sc.Butterworth3Pole()](#scbutterworth3pole)
  + [sc.CalculateAngle()](#sccalculateangle)
  + [sc.CalculateLogLogRegressionStatistics()](#sccalculateloglogregressionstatistics)
  + [sc.CalculateOHLCAverages()](#sccalculateohlcaverages)
  + [sc.CalculateRegressionStatistics()](#sccalculateregressionstatistics)
  + [sc.CalculateTimeSpanAcrossChartBars()](#sccalculatetimespanacrosschartbars)
  + [sc.CalculateTimeSpanAcrossChartBarsInChart()](#sccalculatetimespanacrosschartbarsinchart)
  + [sc.CancelAllOrders()](#sccancelallorders)
  + [sc.CancelOrder()](#sccancelorder)
  + [sc.CCI()](#sccci)
  + [sc.ChaikinMoneyFlow()](#scchaikinmoneyflow)
  + [sc.ChangeACSChartShortcutMenuItemText()](#scchangeacschartshortcutmenuitemtext)
  + [sc.ChangeChartReplaySpeed()](#scchangechartreplayspeed)
  + [sc.ChartbookName()](#scchartbookname)
  + [sc.ChartDrawingExists()](#scchartdrawingexists)
  + [sc.ChartIsDownloadingHistoricalData()](#scchartisdownloadinghistoricaldata)
  + [sc.ClearAlertSoundQueue()](#scclearalertsoundqueue)
  + [sc.ClearAllPersistentData()](#scclearallpersistentdata)
  + [sc.ClearCurrentTradedBidAskVolume()](#scclearcurrenttradedbidaskvolume)
  + [sc.ClearCurrentTradedBidAskVolumeAllSymbols()](#scclearcurrenttradedbidaskvolumeallsymbols)
  + [sc.ClearKeyboardBufferForChart()](#scclearkeyboardbufferforchart)
  + [sc.ClearMarketDepthPullingStackingData()](#scclearmarketdepthpullingstackingdata)
  + [sc.ClearMessageLog()](#scclearmessagelog)
  + [sc.ClearRecentBidAskVolume()](#scclearrecentbidaskvolume)
  + [sc.ClearRecentBidAskVolumeAllSymbols()](#scclearrecentbidaskvolumeallsymbols)
  + [sc.CloseChart()](#scclosechart)
  + [sc.CloseChartbook()](#scclosechartbook)
  + [sc.CloseFile()](#scclosefile)
  + [sc.CombinedForegroundBackgroundColorRef()](#sccombinedforegroundbackgroundcolorref)
  + [sc.ConvertCurrencyValueToCommonCurrency()](#scconvertcurrencyvaluetocommoncurrency)
  + [sc.ConvertDateTimeFromChartTimeZone()](#scconvertdatetimefromcharttimezone)
  + [sc.ConvertDateTimeToChartTimeZone()](#scconvertdatetimetocharttimezone)
  + [sc.ConvertDateTimeUTCToChartTimeZone()](#scconvertdatetimeutctocharttimezone)
  + [sc.CreateDoublePrecisionPrice()](#sccreatedoubleprecisionprice)
  + [sc.CreateProfitLossDisplayString()](#sccreateprofitlossdisplaystring)
  + [sc.CrossOver()](#sccrossover)
  + [sc.CumulativeDeltaTicks()](#sccumulativedeltaticks)
  + [sc.CumulativeDeltaTickVolume()](#sccumulativedeltatickvolume)
  + [sc.CumulativeDeltaVolume()](#sccumulativedeltavolume)
  + [sc.CumulativeSummation()](#sccumulativesummation)
  + [sc.CustomAffiliateCode()](#sccustomaffiliatecode)
  + [sc.CyberCycle()](#sccybercycle)
  + [sc.DataTradeServiceName()](#scdatatradeservicename)
  + [sc.DatesToExcludeClear()](#scdatestoexcludeclear)
  + [sc.DateStringDDMMYYYYToSCDateTime()](#scdatestringddmmyyyytoscdatetime)
  + [sc.DateStringToSCDateTime()](#scdatestringtoscdatetime)
  + [sc.DateTimeToString()](#scdatetimetostring)
  + [sc.DateToString()](#scdatetostring)
  + [sc.DeleteACSChartDrawing()](#scdeleteacschartdrawing)
  + [sc.DeleteLineUntilFutureIntersection()](#scdeletelineuntilfutureintersection)
  + [sc.DeleteUserDrawnACSDrawing()](#scdeleteuserdrawnacsdrawing)
  + [sc.Demarker()](#scdemarker)
  + [sc.Dispersion()](#scdispersion)
  + [sc.DMI()](#scdmi)
  + [sc.DMIDiff()](#scdmidiff)
  + [sc.DrawGraphics\_LineTo()](#scdrawgraphicslineto)
  + [sc.DrawGraphics\_MoveTo()](#scdrawgraphicsmoveto)
  + [sc.DominantCyclePeriod()](#scdominantcycleperiod)
  + [sc.DominantCyclePhase()](#scdominantcyclephase)
  + [sc.DoubleStochastic()](#scdoublestochastic)
  + [sc.EnvelopeFixed()](#scenvelopefixed)
  + [sc.EnvelopePct()](#scenvelopepct)
  + [sc.Ergodic()](#scergodic)
  + [sc.EvaluateAlertConditionFormulaAsBoolean()](#scevaluatealertconditionformulaasboolean)
  + [sc.EvaluateGivenAlertConditionFormulaAsBoolean()](#scevaluategivenalertconditionformulaasboolean)
  + [sc.EvaluateGivenAlertConditionFormulaAsDouble()](#scevaluategivenalertconditionformulaasdouble)
  + [sc.ExponentialMovAvg()](#scexponentialmovavg)
  + [sc.ExponentialRegressionIndicator()](#scexponentialregressionindicator)
  + [sc.FillSubgraphElementsWithLinearValuesBetweenBeginEndValues()](#scfillsubgraphelementswithlinearvaluesbetweenbeginendvalues)
  + [sc.FlattenAndCancelAllOrders()](#scflattenandcancelallorders)
  + [sc.FlattenAndCancelAllOrdersForSymbolAndNonSimTradeAccount()](#scflattenandcancelallordersforsymbolandnonsimtradeaccount)
  + [sc.FlattenPosition()](#scflattenposition)
  + [sc.FlattenPositionsAndCancelOrdersForTradeAccount()](#scflattenpositionsandcancelordersfortradeaccount)
  + [sc.FormatDateTime()](#scformatdatetime)
  + [sc.FormatDateTimeMS()](#scformatdatetimems)
  + [sc.FormatGraphValue()](#scformatgraphvalue)
  + [sc.FormatString()](#scformatstring)
  + [sc.FormattedEvaluate()](#scformattedevaluate)
  + [sc.FormattedEvaluateUsingDoubles()](#scformattedevaluateusingdoubles)
  + [sc.FormatVolumeValue()](#scformatvolumevalue)
  + [sc.FourBarSymmetricalFIRFilter()](#scfourbarsymmetricalfirfilter)
  + [sc.FreeMemory()](#scfreememory)
  + [sc.GetACSDrawingByIndex()](#scgetacsdrawingbyindex)
  + [sc.GetACSDrawingByLineNumber()](#scgetacsdrawingbylinenumber)
  + [sc.GetACSDrawingsCount()](#scgetacsdrawingscount)
  + [sc.GetAskMarketDepthEntryAtLevel()](#scgetaskmarketdepthentryatlevel)
  + [sc.GetAskMarketDepthEntryAtLevelForSymbol()](#scgetaskmarketdepthentryatlevelforsymbol)
  + [sc.GetAskMarketDepthNumberOfLevels()](#scgetaskmarketdepthnumberoflevels)
  + [sc.GetAskMarketDepthNumberOfLevelsForSymbol()](#scgetaskmarketdepthnumberoflevelsforsymbol)
  + [sc.GetAskMarketDepthStackPullSum()](#scgetaskmarketdepthstackpullsum)
  + [sc.GetAskMarketDepthStackPullValueAtPrice()](#scgetaskmarketdepthstackpullvalueatprice)
  + [sc.GetAskMarketLimitOrdersForPrice()](#scgetaskmarketlimitordersforprice)
  + [sc.GetAttachedOrderIDsForParentOrder()](#scgetattachedorderidsforparentorder)
  + [sc.GetAttachedOrders()](#scgetattachedorders)
  + [sc.GetBarHasClosedStatus()](#scgetbarhasclosedstatus)
  + [sc.GetBarPeriodParameters()](#scgetbarperiodparameters)
  + [sc.GetBarPeriodParametersForChart()](#scgetbarperiodparametersforchart)
  + [sc.GetBarsSinceLastTradeOrderEntry()](#scgetbarssincelasttradeorderentry)
  + [sc.GetBarsSinceLastTradeOrderExit()](#scgetbarssincelasttradeorderexit)
  + [sc.GetBasicSymbolData()](#scgetbasicsymboldata)
  + [sc.GetBasicSymbolDataWithDepthSupport()](#scgetbasicsymboldatawithdepthsupport)
  + [sc.GetBidMarketDepthEntryAtLevel()](#scgetbidmarketdepthentryatlevel)
  + [sc.GetBidMarketDepthEntryAtLevelForSymbol()](#scgetbidmarketdepthentryatlevelforsymbol)
  + [sc.GetBidMarketDepthNumberOfLevels()](#scgetbidmarketdepthnumberoflevels)
  + [sc.GetBidMarketDepthNumberOfLevelsForSymbol()](#scgetbidmarketdepthnumberoflevelsforsymbol)
  + [sc.GetBidMarketDepthStackPullSum()](#scgetbidmarketdepthstackpullsum)
  + [sc.GetBidMarketDepthStackPullValueAtPrice()](#scgetaskmarketdepthstackpullvalueatprice)
  + [sc.GetBidMarketLimitOrdersForPrice()](#scgetbidmarketlimitordersforprice)
  + [sc.GetBuiltInStudyName()](#scgetbuiltinstudyname)
  + [sc.GetCalculationStartIndexForStudy()](#scgetcalculationstartindexforstudy)
  + [sc.GetChartArray()](#scgetchartarray)
  + [sc.GetChartBarWidth()](#scgetchartbarwidth)
  + [sc.GetChartBaseData()](#scgetchartbasedata)
  + [sc.GetChartbookFilePathAndFilename()](#scgetchartbookfilepathandfilename)
  + [sc.GetChartDateTimeArray()](#scgetchartdatetimearray)
  + [sc.GetChartDOMFontProperties()](#scgetchartdomfontproperties)
  + [sc.GetChartDrawing()](#scgetchartdrawing)
  + [sc.GetChartFontProperties()](#scgetchartfontproperties)
  + [sc.GetChartName()](#scgetchartname)
  + [sc.GetChartReplaySpeed()](#scgetchartreplayspeed)
  + [sc.GetChartStudyConstantRangeScaleAmount()](#scgetchartstudyconstantrangescaleamount)
  + [sc.GetChartStudyDisplayAsMainPriceGraph()](#scgetchartstudydisplayasmainpricegraph)
  + [sc.GetChartStudyDisplayStudyInputValues()](#scgetchartstudydisplaystudyinputvalues)
  + [sc.GetChartStudyDisplayStudyName()](#scgetchartstudydisplaystudyname)
  + [sc.GetChartStudyDisplaySubgraphsNameAndValue()](#scgetchartstudydisplaysubgraphsnameandvalue)
  + [sc.GetChartStudyDrawStudyUnderneathMainPriceGraph()](#scgetchartstudydrawstudyunderneathmainpricegraph)
  + [sc.GetChartStudyGraphRegion()](#scgetchartstudygraphregion)
  + [sc.GetChartStudyHideStudy()](#scgetchartstudyhidestudy)
  + [sc.GetChartStudyInputChartStudySubgraphValues()](#scgetchartstudyinputchartstudysubgraphvalues)
  + [sc.GetChartStudyInputCustomStringListSize()](#scgetchartstudyinputcustomstringlistsize)
  + [sc.GetChartStudyInputCustomStringListString()](#scgetchartstudyinputcustomstringliststring)
  + [sc.GetChartStudyInputFloat()](#scgetchartstudyinputfloat)
  + [sc.GetChartStudyInputInt()](#scgetchartstudyinputint)
  + [sc.GetChartStudyInputString()](#scgetchartstudyinputstring)
  + [sc.GetChartStudyInputType()](#scgetchartstudyinputtype)
  + [sc.GetChartStudyScaleIncrement()](#scgetchartstudyscaleincrement)
  + [sc.GetChartStudyScaleRangeType()](#scgetchartstudyscalerangetype)
  + [sc.GetChartStudyScaleType()](#scgetchartstudyscaletype)
  + [sc.GetChartStudyScaleValueOffset()](#scgetchartstudyscalevalueoffset)
  + [sc.GetChartStudyShortName()](#scgetchartstudyshortname)
  + [sc.GetChartStudyTransparencyLevel()](#scgetchartstudytransparencylevel)
  + [sc.GetChartStudyUserDefinedScaleRangeBottom()](#scgetchartstudyuserdefinedscalerangebottom)
  + [sc.GetChartStudyUserDefinedScaleRangeTop()](#scgetchartstudyuserdefinedscalerangetop)
  + [sc.GetChartStudyValueFormat()](#scgetchartstudyvalueformat)
  + [sc.GetChartStudyVersion()](#scgetchartstudyversion)
  + [sc.GetChartSymbol()](#scgetchartsymbol)
  + [sc.GetChartTextFontFaceName()](#scgetcharttextfontfacename)
  + [sc.GetChartTimeZone()](#scgetcharttimezone)
  + [sc.GetChartWindowHandle()](#scgetchartwindowhandle)
  + [sc.GetCombineTradesIntoOriginalSummaryTradeSetting()](#scgetcombinetradesintooriginalsummarytradesetting)
  + [sc.GetContainingIndexForDateTimeIndex()](#scgetcontainingindexfordatetimeindex)
  + [sc.GetContainingIndexForSCDateTime()](#scgetcontainingindexforscdatetime)
  + [sc.GetCorrelationCoefficient()](#scgetcorrelationcoefficient)
  + [sc.GetCountDownText()](#scgetcountdowntext)
  + [sc.GetCurrentDateTime()](#scgetcurrentdatetime)
  + [sc.GetCurrentTradedAskVolumeAtPrice()](#scgetcurrenttradedaskvolumeatprice)
  + [sc.GetCurrentTradedBidVolumeAtPrice()](#scgetcurrenttradedbidvolumeatprice)
  + [sc.GetCustomStudyControlBarButtonEnableState()](#scgetcustomstudycontrolbarbuttonenablestate)
  + [sc.GetCustomStudyInformation()](#scgetcustomstudyinformation)
  + [sc.GetDataDelayFromChart()](#scgetdatadelayfromchart)
  + [sc.GetDispersion()](#scgetdispersion)
  + [sc.GetDOMColumnLeftCoordinate()](#scgetdomcolumnleftcoordinate)
  + [sc.GetDOMColumnRightCoordinate()](#scgetdomcolumnleftcoordinate)
  + [sc.GetEarliestSourceIndexForDestinationDateTime()](#scgetearliestsourceindexfordestinationdatetime)
  + [sc.GetEndingDateTimeForBarIndex()](#scgetendingdatetimeforbarindex)
  + [sc.GetEndingDateTimeForBarIndexFromChart()](#scgetendingdatetimeforbarindexfromchart)
  + [sc.GetExactMatchForSCDateTime()](#scgetexactmatchforscdatetime)
  + [sc.GetFirstIndexForDate()](#scgetfirstindexfordate)
  + [sc.GetFirstNearestIndexForTradingDayDate()](#scgetfirstnearestindexfortradingdaydate)
  + [sc.GetFlatToFlatTradeListEntry()](#scgetflattoflattradelistentry)
  + [sc.GetFlatToFlatTradeListSize()](#scgetflattoflattradelistsize)
  + [sc.GetGraphicsSetting()](#scgetgraphicssetting)
  + [sc.GetGraphicsSettingEnableState()](#scgetgraphicssettingenablestate)
  + [sc.GetGraphVisibleHighAndLow()](#scgetgraphvisiblehighandlow)
  + [sc.GetHideChartDrawingsFromOtherCharts()](#scgethidechartdrawingsfromothercharts)
  + [sc.GetHighest()](#scgethighest)
  + [sc.GetHighestChartNumberUsedInChartBook()](#scgethighestchartnumberusedinchartbook)
  + [sc.GetIndexOfHighestValue()](#scgetindexofhighestvalue)
  + [sc.GetIndexOfLowestValue()](#scgetindexoflowestvalue)
  + [sc.GetIslandReversal()](#scgetislandreversal)
  + [sc.GetKeyboardBufferForChart()](#scgetkeyboardbufferforchart)
  + [sc.GetLastFileErrorCode()](#scgetlastfileerrorcode)
  + [sc.GetLastFileErrorMessage()](#scgetlastfileerrormessage)
  + [sc.GetLastPriceForTrading()](#scgetlastpricefortrading)
  + [sc.GetLatestBarCountdownAsInteger()](#scgetlatestbarcountdownasinteger)
  + [sc.GetLatestSourceIndexForDestinationDateTime()](#scgetlatestsourceindexfordestinationdatetime)
  + [sc.GetLineNumberOfSelectedUserDrawnDrawing()](#scgetlinenumberofselecteduserdrawndrawing)
  + [sc.GetLowest()](#scgetlowest)
  + [sc.GetMainGraphVisibleHighAndLow()](#scgetmaingraphvisiblehighandlow)
  + [sc.GetMarketDepthBars()](#scgetmarketdepthbars)
  + [sc.GetMarketDepthBarsFromChart()](#scgetmarketdepthbarsfromchart)
  + [sc.GetMaximumMarketDepthLevels()](#scgetmaximummarketdepthlevels)
  + [sc.GetNearestMatchForDateTimeIndex()](#scgetnearestmatchfordatetimeindex)
  + [sc.GetNearestMatchForSCDateTime()](#scgetnearestmatchforscdatetime)
  + [sc.GetNearestMatchForSCDateTimeExtended()](#scgetnearestmatchforscdatetimeextended)
  + [sc.GetNearestStopOrder()](#scgetneareststoporder)
  + [sc.GetNearestStopWorkingAttachedOrder()](#scgetneareststopworkingattachedorder)
  + [sc.GetNearestTargetOrder()](#scgetnearesttargetorder)
  + [sc.GetNearestTargetWorkingAttachedOrder()](#scgetnearesttargetworkingattachedorder)
  + [sc.GetNumberOfBaseGraphArrays()](#scgetnumberofbasegrapharrays)
  + [sc.GetNumberOfDataFeedSymbolsTracked()](#scgetnumberofdatafeedsymbolstracked)
  + [sc.GetNumLinesUntilFutureIntersection()](#scgetnumlinesuntilfutureintersection)
  + [sc.GetNumPriceLevelsForStudyProfile()](#scgetnumpricelevelsforstudyprofile)
  + [sc.GetNumStudyProfiles()](#scgetnumstudyprofiles)
  + [sc.GetNumTradeAccounts()](#scgetnumtradeaccounts)
  + [sc.GetOHLCForDate()](#scgetohlcfordate)
  + [sc.GetOHLCOfTimePeriod()](#scgetohlcoftimeperiod)
  + [sc.GetOpenHighLowCloseVolumeForDate()](#scgetopenhighlowclosevolumefordate)
  + [sc.GetOrderByIndex()](#scgetorderbyindex)
  + [sc.GetOrderByOrderID()](#scgetorderbyorderid)
  + [sc.GetOrderFillArraySize()](#scgetorderfillarraysize)
  + [sc.GetOrderFillEntry()](#scgetorderfillentry)
  + [sc.GetOrderForSymbolAndAccountByIndex()](#scgetorderforsymbolandaccountbyindex)
  + [sc.GetParentOrderIDFromAttachedOrderID](#scgetparentorderidfromattachedorderid)
  + [sc.GetPersistentDouble()](#scgetpersistentdouble)
  + [sc.GetPersistentDoubleFast()](#scgetpersistentdoublefast)
  + [sc.GetPersistentDoubleFromChartStudy()](#scgetpersistentdoublefromchartstudy)
  + [sc.GetPersistentFloat()](#scgetpersistentfloat)
  + [sc.GetPersistentFloatFast()](#scgetpersistentfloatfast)
  + [sc.GetPersistentFloatFromChartStudy()](#scgetpersistentfloatfromchartstudy)
  + [sc.GetPersistentInt()](#scgetpersistentint)
  + [sc.GetPersistentInt64()](#scgetpersistentint64)
  + [sc.GetPersistentInt64FromChartStudy()](#scgetpersistentint64fromchartstudy)
  + [sc.GetPersistentIntFast()](#scgetpersistentintfast)
  + [sc.GetPersistentIntFromChartStudy()](#scgetpersistentintfromchartstudy)
  + [sc.GetPersistentPointer()](#scgetpersistentpointer)
  + [sc.GetPersistentPointerFromChartStudy()](#scgetpersistentpointerfromchartstudy)
  + [sc.GetPersistentSCDateTime()](#scgetpersistentscdatetime)
  + [sc.GetPersistentSCDateTimeFast()](#scgetpersistentscdatetimefast)
  + [sc.GetPersistentSCDateTimeFromChartStudy()](#scgetpersistentscdatetimefromchartstudy)
  + [sc.GetPersistentSCString()](#scgetpersistentscstring)
  + [sc.GetPersistentSCStringFromChartStudy()](#scgetpersistentscstringfromchartstudy)
  + [sc.GetPointOfControlAndValueAreaPricesForBar()](#scgetpointofcontrolandvalueareapricesforbar)
  + [sc.GetPointOfControlPriceVolumeForBar()](#scgetpointofcontrolpricevolumeforbar)
  + [sc.GetProfitManagementStringForTradeAccount()](#scgetprofitmanagementstringfortradeaccount)
  + [sc.GetRealTimeSymbol()](#scgetrealtimesymbol)
  + [sc.GetRecentAskVolumeAtPrice()](#scgetrecentaskvolumeatprice)
  + [sc.GetRecentBidVolumeAtPrice()](#scgetrecentaskvolumeatprice)
  + [sc.GetReplayHasFinishedStatus()](#scgetreplayhasfinishedstatus)
  + [sc.GetReplayStatusFromChart()](#scgetreplaystatusfromchart)
  + [sc.GetSelectedUserDrawnDrawingFromChart()](#scgetselecteduserdrawndrawingfromchart)
  + [sc.GetSessionTimesFromChart()](#scgetsessiontimesfromchart)
  + [sc.GetSheetCellAsDouble()](#scgetsheetcellasdouble)
  + [sc.GetSheetCellAsString()](#scgetsheetcellasstring)
  + [sc.GetSpreadsheetColumnAndRowIndexesFromCellReference()](#scgetspreadsheetcolumnandrowindexesfromcellreference)
  + [sc.GetSpreadsheetSheetHandleByIndex()](#scgetspreadsheetsheethandlebyindex)
  + [sc.GetSpreadsheetSheetHandleByName()](#scgetspreadsheetsheethandlebyname)
  + [sc.GetStandardError()](#scgetstandarderror)
  + [sc.GetStartDateTimeForTradingDate()](#scgetstartdatetimefortradingdate)
  + [sc.GetStartDateTimeOfDaySessionForTradingDayDate()](#scgetstartdatetimeofdaysessionfortradingdaydate)
  + [sc.GetStartOfPeriodForDateTime()](#scgetstartofperiodfordatetime)
  + [sc.GetStudyArray()](#scgetstudyarray)
  + [sc.GetStudyArrayFromChart()](#scgetstudyarrayfromchart)
  + [sc.GetStudyArrayFromChartUsingID()](#scgetstudyarrayfromchartusingid)
  + [sc.GetStudyArraysFromChart()](#scgetstudyarraysfromchart)
  + [sc.GetStudyArraysFromChartUsingID()](#scgetstudyarraysfromchartusingid)
  + [sc.GetStudyArrayUsingID()](#scgetstudyarrayusingid)
  + [sc.GetStudyDataColorArrayFromChartUsingID()](#scgetstudydatacolorarrayfromchartusingid)
  + [sc.GetStudyDataStartIndexFromChartUsingID()](#scgetstudydatastartindexfromchartusingid)
  + [sc.GetStudyDataStartIndexUsingID()](#scgetstudydatastartindexusingid)
  + [sc.GetStudyExtraArrayFromChartUsingID()](#scgetstudyextraarrayfromchartusingid)
  + [sc.GetStudyIDByIndex()](#scgetstudyidbyindex)
  + [sc.GetStudyIDByName()](#scgetstudyidbyname)
  + [sc.GetStudyInputName()](#scgetstudyinputname)
  + [sc.GetStudyInternalIdentifier()](#scgetstudyinternalidentifier)
  + [sc.GetStudyLineUntilFutureIntersection()](#scgetstudylineuntilfutureintersection)
  + [sc.GetStudyLineUntilFutureIntersectionByIndex()](#scgetstudylineuntilfutureintersectionbyindex)
  + [sc.GetStudyName()](#scgetstudyname)
  + [sc.GetStudyNameFromChart()](#scgetstudynamefromchart)
  + [sc.GetStudyNameUsingID()](#scgetstudynameusingid)
  + [sc.GetStudyPeakValleyLine()](#scgetstudypeakvalleyline)
  + [sc.GetStudyProfileInformation()](#scgetstudyprofileinformation)
  + [sc.GetStudyStorageBlockFromChart()](#scgetstudystorageblockfromchart)
  + [sc.GetStudySubgraphColors()](#scgetstudysubgraphcolors)
  + [sc.GetStudySubgraphDrawStyle()](#scgetstudysubgraphdrawstyle)
  + [sc.GetStudySubgraphLineStyle()](#scgetstudysubgraphlinestyle)
  + [sc.GetStudySubgraphLineWidth()](#scgetstudysubgraphlinewidth)
  + [sc.GetStudySubgraphName()](#scgetstudysubgraphname)
  + [sc.GetStudySubgraphNameFromChart()](#scgetstudysubgraphnamefromchart)
  + [sc.GetStudySummaryCellAsDouble()](#scgetstudysummarycellasdouble)
  + [sc.GetStudySummaryCellAsString()](#scgetstudysummarycellasstring)
  + [sc.GetStudyVisibilityState()](#scgetstudyvisibilitystate)
  + [sc.GetSummation()](#scgetsummation)
  + [sc.GetSymbolDataValue()](#scgetsymboldatavalue)
  + [sc.GetSymbolDescription()](#scgetsymboldescription)
  + [sc.GetTimeAndSales()](#scgettimeandsales)
  + [sc.GetTimeAndSalesForSymbol()](#scgettimeandsalesforsymbol)
  + [sc.GetTimeSalesArrayIndexesForBarIndex()](#scgettimesalesarrayindexesforbarindex)
  + [sc.GetTotalNetProfitLossForAllSymbols()](#scgettotalnetprofitlossforallsymbols)
  + [sc.GetTradeAccountAtIndex()](#scgettradeaccountatindex)
  + [sc.GetTradeAccountData()](#scgettradeaccountdata)
  + [sc.GetTradeListEntry()](#scgettradelistentry)
  + [sc.GetTradeListSize()](#scgettradelistsize)
  + [sc.GetTradePosition()](#scgettradeposition)
  + [sc.GetTradePositionByIndex()](#scgettradepositionbyindex)
  + [sc.GetTradePositionForSymbolAndAccount()](#scgettradepositionforsymbolandaccount)
  + [sc.GetTradeServiceAccountBalanceForTradeAccount()](#scgettradeserviceaccountbalancefortradeaccount)
  + [sc.GetTradeStatisticsForSymbolV2()](#scgettradestatisticsforsymbolv2)
  + [sc.GetTradeSymbol()](#scgettradesymbol)
  + [sc.GetTradeWindowOrderType()](#scgettradewindowordertype)
  + [sc.GetTradeWindowTextTag()](#scgettradewindowtexttag)
  + [sc.GetTradingDayDate()](#scgettradingdaydate)
  + [sc.GetTradingDayDateForChartNumber()](#scgettradingdaydateforchartnumber)
  + [sc.GetTradingDayStartDateTimeOfBar()](#scgettradingdaystartdatetimeofbar)
  + [sc.GetTradingDayStartDateTimeOfBarForChart()](#scgettradingdaystartdatetimeofbarforchart)
  + [sc.GetTradingErrorTextMessage()](#scgettradingerrortextmessage)
  + [sc.GetTradingKeyboardShortcutsEnableState()](#scgettradingkeyboardshortcutsenablestate)
  + [sc.GetTrueHigh()](#scgettruehigh)
  + [sc.GetTrueLow()](#scgettruelow)
  + [sc.GetTrueRange()](#scgettruerange)
  + [sc.GetUseGlobalGraphicsSettings()](#scgetuseglobalgraphicssettings)
  + [sc.GetUserDrawingByLineNumber()](#scgetuserdrawingbylinenumber)
  + [sc.GetUserDrawnChartDrawing()](#scgetuserdrawnchartdrawing)
  + [sc.GetUserDrawnDrawingByLineNumber()](#scgetuserdrawndrawingbylinenumber)
  + [sc.GetUserDrawnDrawingsCount()](#scgetuserdrawndrawingscount)
  + [sc.GetValueFormat()](#scgetvalueformat)
  + [sc.GetVolumeAtPriceDataForStudyProfile()](#scgetvolumeatpricedataforstudyprofile)
  + [sc.GetVolumeAtPriceForBarsForChart()](#scgetvolumeatpriceforbarsforchart)
  + [sc.GetVolumeOpenInterestMultiplier()](#scgetvolumeopeninterestmultiplier)
  + [sc.GetYValueForChartDrawingAtBarIndex()](#scgetyvalueforchartdrawingatbarindex)
  + [sc.HeikinAshi()](#scheikinashi)
  + [sc.Highest()](#schighest)
  + [sc.HullMovingAverage()](#schullmovingaverage)
  + [sc.HurstExponent()](#schurstexponent)
  + [sc.InstantaneousTrendline()](#scinstantaneoustrendline)
  + [sc.InverseFisherTransform()](#scinversefishertransform)
  + [sc.InverseFisherTransformRSI()](#scinversefishertransformrsi)
  + [sc.IsChartDataLoadingCompleteForAllCharts()](#scischartdataloadingcompleteforallcharts)
  + [sc.IsChartDataLoadingInChartbook()](#scischartdataloadinginchartbook)
  + [sc.IsChartDOMRecenterLineEnabled()](#scischartdomrecenterlineenabled)
  + [sc.IsChartNumberExist()](#scischartnumberexist)
  + [sc.IsChartZoomInStateActive()](#scischartzoominstateactive)
  + [sc.IsDataExportAllowed()](#scisdataexportallowed)
  + [sc.IsDateTimeContainedInBarAtIndex()](#scisdatetimecontainedinbaratindex)
  + [sc.IsDateTimeContainedInBarIndex()](#scisdatetimecontainedinbarindex)
  + [sc.IsDateTimeInDaySession()](#scisdatetimeindaysession)
  + [sc.IsDateTimeInEveningSession()](#scisdatetimeineveningsession)
  + [sc.IsDateTimeInSession()](#scisdatetimeinsession)
  + [sc.IsDrawDOMGraphOnChartEnabled()](#scisdrawdomgraphonchartenabled)
  + [sc.IsLastBarClosedBasedOnElapsedTime()](#scislastbarclosedbasedonelapsedtime)
  + [sc.IsMarketDataColumnsEnabled()](#scismarketdatacolumnsenabled)
  + [sc.IsMarketDepthDataCurrentlyAvailable()](#scismarketdepthdatacurrentlyavailable)
  + [sc.IsNewBar()](#scisnewbar)
  + [sc.IsNewTradingDay()](#scisnewtradingday)
  + [sc.IsOpenGLActive()](#scisopenglactive)
  + [sc.IsReplayRunning()](#scisreplayrunning)
  + [sc.IsSufficientTimePeriodInDate()](#scissufficienttimeperiodindate)
  + [sc.IsSwingHigh()](#scisswinghigh)
  + [sc.IsSwingLow()](#scisswinglow)
  + [sc.IsTradingChartDOMEnabled()](#scistradingchartdomenabled)
  + [sc.IsTradingDOMMode()](#scistradingdommode)
  + [sc.IsVisibleSubgraphDrawStyle()](#scisvisiblesubgraphdrawstyle)
  + [IsWorkingOrderStatus()](#scisworkingorderstatus)
  + [IsWorkingOrderStatusIgnorePendingChildren()](#scisworkingorderstatusignorependingchildren)
  + [sc.Keltner()](#sckeltner)
  + [sc.LaguerreFilter()](#sclaguerrefilter)
  + [sc.LinearRegressionIndicator()](#sclinearregressionindicator)
  + [sc.LinearRegressionIndicatorAndStdErr()](#sclinearregressionindicatorandstderr)
  + [sc.LinearRegressionIntercept()](#sclinearregressionintercept)
  + [sc.LinearRegressionSlope()](#sclinearregressionslope)
  + [sc.Lowest()](#sclowest)
  + [sc.MACD()](#scmacd)
  + [sc.MakeHTTPBinaryRequest()](#scmakehttpbinaryrequest)
  + [sc.MakeHTTPPOSTRequest()](#scmakehttppostrequest)
  + [sc.MakeHTTPRequest()](#scmakehttprequest)
  + [sc.Momentum()](#scmomentum)
  + [sc.MovingAverage()](#scmovingaverage)
  + [sc.MovingAverageCumulative()](#scmovingaveragecumulative)
  + [sc.MovingMedian()](#scmovingmedian)
  + [sc.MultiplierFromVolumeValueFormat()](#scmultiplierfromvolumevalueformat)
  + [sc.NumberOfBarsSinceHighestValue()](#scnumberofbarssincehighestvalue)
  + [sc.NumberOfBarsSinceLowestValue()](#scnumberofbarssincelowestvalue)
  + [sc.OnBalanceVolume()](#sconbalancevolume)
  + [sc.OnBalanceVolumeShortTerm()](#sconbalancevolumeshortterm)
  + [sc.OpenChartbook()](#scopenchartbook)
  + [sc.OpenChartOrGetChartReference()](#scopenchartorgetchartreference)
  + [sc.OpenFile()](#scopenfile)
  + [sc.OpenSpreadsheet()](#scopenspreadsheet)
  + [sc.OrderQuantityToString()](#scorderquantitytostring)
  + [sc.Oscillator()](#scoscillator)
  + [sc.Parabolic()](#scparabolic)
  + [sc.PauseChartReplay()](#scpausechartreplay)
  + [sc.PlaySound()](#scplaysound)
  + [sc.PriceValueToTicks()](#scpricevaluetoticks)
  + [sc.PriceVolumeTrend()](#scpricevolumetrend)
  + [sc.RandomWalkIndicator()](#scrandomwalkindicator)
  + [sc.ReadFile()](#screadfile)
  + [sc.ReadIntradayFileRecordAtIndex()](#screadintradayfilerecordatindex)
  + [sc.ReadIntradayFileRecordForBarIndexAndSubIndex()](#screadintradayfilerecordforbarindexandsubindex)
  + [sc.RecalculateChart()](#screcalculatechart)
  + [sc.RecalculateChartImmediate()](#screcalculatechartimmediate)
  + [sc.ReCenterConstantRangeScale()](#screcenterconstantrangescale)
  + [sc.RefreshChartTradingDrawings()](#screfreshcharttradingdrawings)
  + [sc.RefreshTradeData()](#screfreshtradedata)
  + [sc.RegionValueToYPixelCoordinate()](#scregionvaluetoypixelcoordinate)
  + [sc.RelayDataFeedAvailable()](#screlaydatafeedavailable)
  + [sc.RelayDataFeedUnavailable()](#screlaydatafeedunavailable)
  + [sc.RelayNewSymbol()](#screlaynewsymbol)
  + [sc.RelayServerConnected()](#screlayserverconnected)
  + [sc.RelayTradeUpdate()](#screlaytradeupdate)
  + [sc.RemoveACSChartShortcutMenuItem()](#scremoveacschartshortcutmenuitem)
  + [sc.RemoveStudyFromChart()](#scremovestudyfromchart)
  + [sc.ResizeArrays()](#scresizearrays)
  + [sc.ResumeChartReplay()](#scresumechartreplay)
  + [sc.RGBInterpolate()](#scrgbinterpolate)
  + [sc.Round()](#scround)
  + [sc.RoundToTickSize()](#scroundtoticksize)
  + [sc.RSI()](#scrsi)
  + [sc.SaveChartbook()](#scsavechartbook)
  + [sc.SaveChartImageToFileExtended()](#scsavechartimagetofileextended)
  + [sc.SaveMainWindowImageToFile()](#scsavemainwindowimagetofile)
  + [sc.SCDataFeedSymbol()](#scscdatafeedsymbol)
  + [sc.SecondsSinceStartTime()](#scsecondssincestarttime)
  + [sc.SecurityType()](#scsecuritytype)
  + [sc.SendEmailMessage()](#scsendemailmessage)
  + [sc.SendHeldTradeOrder()](#scsendheldtradeorder)
  + [sc.ServiceCodeForSelectedDataTradingService()](#scservicecodeforselecteddatatradingservice)
  + [sc.SessionStartTime()](#scsessionstarttime)
  + [sc.SetACSChartShortcutMenuItemChecked()](#scsetacschartshortcutmenuitemchecked)
  + [sc.SetACSChartShortcutMenuItemDisplayed()](#scsetacschartshortcutmenuitemdisplayed)
  + [sc.SetACSChartShortcutMenuItemEnabled()](#scsetacschartshortcutmenuitemenabled)
  + [sc.SetACSToolButtonText()](#scsetacstoolbuttontext)
  + [sc.SetACSToolEnable()](#scsetacstoolenable)
  + [sc.SetACSToolToolTip()](#scsetacstooltooltip)
  + [sc.SetAlert()](#scsetalert)
  + [sc.SetAttachedOrders()](#scsetattachedorders)
  + [sc.SetBarPeriodParameters()](#scsetbarperiodparameters)
  + [sc.SetChartDrawingTool()](#scsetchartdrawingtool)
  + [sc.SetChartStudyConstantRangeScaleAmount()](#scsetchartstudyconstantrangescaleamount)
  + [sc.SetChartStudyDisplayAsMainPriceGraph()](#scsetchartstudydisplayasmainpricegraph)
  + [sc.SetChartStudyDisplayStudyInputValues()](#scsetchartstudydisplaystudyinputvalues)
  + [sc.SetChartStudyDisplayStudyName()](#scsetchartstudydisplaystudyname)
  + [sc.SetChartStudyDisplaySubgraphsNameAndValue()](#scsetchartstudydisplaysubgraphsnameandvalue)
  + [sc.SetChartStudyDrawStudyUnderneathMainPriceGraph()](#scsetchartstudydrawstudyunderneathmainpricegraph)
  + [sc.SetChartStudyGraphRegion()](#scsetchartstudygraphregion)
  + [sc.SetChartStudyHideStudy()](#scsetchartstudyhidestudy)
  + [sc.SetChartStudyInputChartStudySubgraphValues()](#scsetchartstudyinputchartstudysubgraphvalues)
  + [sc.SetChartStudyInputFloat()](#scsetchartstudyinputfloat)
  + [sc.SetChartStudyInputInt()](#scsetchartstudyinputint)
  + [sc.SetChartStudyInputString()](#scsetchartstudyinputstring)
  + [sc.SetChartStudyScaleIncrement()](#scsetchartstudyscaleincrement)
  + [sc.SetChartStudyScaleRangeType()](#scsetchartstudyscalerangetype)
  + [sc.SetChartStudyScaleType()](#scsetchartstudyscaletype)
  + [sc.SetChartStudyScaleValueOffset()](#scsetchartstudyscalevalueoffset)
  + [sc.SetChartStudyShortName()](#scsetchartstudyshortname)
  + [sc.SetChartStudyTransparencyLevel()](#scsetchartstudytransparencylevel)
  + [sc.SetChartStudyUserDefinedScaleRangeBottom()](#scsetchartstudyuserdefinedscalerangebottom)
  + [sc.SetChartStudyUserDefinedScaleRangeTop()](#scsetchartstudyuserdefinedscalerangetop)
  + [sc.SetChartStudyValueFormat()](#scsetchartstudyvalueformat)
  + [sc.SetChartStudyVersion()](#scsetchartstudyversion)
  + [sc.SetChartTimeZone()](#scsetcharttimezone)
  + [sc.SetChartTradeMode()](#scsetcharttrademode)
  + [sc.SetChartWindowState()](#scsetchartwindowstate)
  + [sc.SetCombineTradesIntoOriginalSummaryTradeSetting()](#scsetcombinetradesintooriginalsummarytradesetting)
  + [sc.SetCurrentDataTradingService()](#scsetcurrentdatatradingservice)
  + [sc.SetCustomStudyControlBarButtonColor()](#scsetcustomstudycontrolbarbuttoncolor)
  + [sc.SetCustomStudyControlBarButtonEnable()](#scsetcustomstudycontrolbarbuttonenable)
  + [sc.SetCustomStudyControlBarButtonHoverText()](#scsetcustomstudycontrolbarbuttonhovertext)
  + [sc.SetCustomStudyControlBarButtonShortCaption()](#scsetcustomstudycontrolbarbuttonshortcaption)
  + [sc.SetCustomStudyControlBarButtonText()](#scsetcustomstudycontrolbarbuttontext)
  + [sc.SetDrawDOMGraphOnChart()](#scsetdrawdomgraphonchart)
  + [sc.SetGlobalTradeSimulationModeState()](#scsetglobaltradesimulationmodestate)
  + [sc.SetGraphicsSetting()](#scsetgraphicssetting)
  + [sc.SetGraphicsSettingEnableState()](#scsetgraphicssettingenablestate)
  + [sc.SetGraphRegionHeightPercentage()](#scsetgraphregionheightpercentage)
  + [sc.SetHorizontalGridState()](#scsethorizontalgridstate)
  + [sc.SetInvertUnderlyingChartData()](#scsetinvertunderlyingchartdata)
  + [sc.SetNumericInformationDisplayOrderFromString()](#scsetnumericinformationdisplayorderfromstring)
  + [sc.SetNumericInformationGraphDrawTypeConfig()](#scsetnumericinformationgraphdrawtypeconfig)
  + [sc.SetPersistentDouble()](#scsetpersistentdouble)
  + [sc.SetPersistentDoubleForChartStudy()](#scsetpersistentdoubleforchartstudy)
  + [sc.SetPersistentFloat()](#scsetpersistentfloat)
  + [sc.SetPersistentFloatForChartStudy()](#scsetpersistentfloatforchartstudy)
  + [sc.SetPersistentInt()](#scsetpersistentint)
  + [sc.SetPersistentInt64()](#scsetpersistentint64)
  + [sc.SetPersistentInt64ForChartStudy()](#scsetpersistentint64forchartstudy)
  + [sc.SetPersistentIntForChartStudy()](#scsetpersistentintforchartstudy)
  + [sc.SetPersistentPointer()](#scsetpersistentpointer)
  + [sc.SetPersistentPointerForChartStudy()](#scsetpersistentpointerforchartstudy)
  + [sc.SetPersistentSCDateTime()](#scsetpersistentscdatetime)
  + [sc.SetPersistentSCDateTimeForChartStudy()](#scsetpersistentscdatetimeforchartstudy)
  + [sc.SetPersistentSCString()](#scsetpersistentscstring)
  + [sc.SetPersistentSCStringForChartStudy()](#scsetpersistentscstringforchartstudy)
  + [sc.SetSheetCellAsDouble()](#scsetsheetcellasdouble)
  + [sc.SetSheetCellAsString()](#scsetsheetcellasstring)
  + [sc.SetShowMarketDataColumns()](#scsetshowmarketdatacolumns)
  + [sc.SetStudyAlwaysShowNameValueLabelsWhenEnabled()](#scsetstudyalwaysshownamevaluelabelswhenenabled)
  + [sc.SetStudySubgraphColors()](#scsetstudysubgraphcolors)
  + [sc.SetStudySubgraphDrawStyle()](#scsetstudysubgraphdrawstyle)
  + [sc.SetStudySubgraphLineStyle()](#scsetstudysubgraphlinestyle)
  + [sc.SetStudySubgraphLineWidth()](#scsetstudysubgraphlinewidth)
  + [sc.SetStudyVisibilityState()](#scsetstudyvisibilitystate)
  + [sc.SetTradeWindowTextTag()](#scsettradewindowtexttag)
  + [sc.SetTradingKeyboardShortcutsEnableState()](#scsettradingkeyboardshortcutsenablestate)
  + [sc.SetTradingLockState()](#scsettradinglockstate)
  + [sc.SetUseGlobalGraphicsSettings()](#scsetuseglobalgraphicssettings)
  + [sc.SetUseMarketDepthPullingStackingData()](#scsetusemarketdepthpullingstackingdata)
  + [sc.SetVerticalGridState()](#scsetverticalgridstate)
  + [sc.SetVolumeOpenInterestMultiplier()](#scsetvolumeopeninterestmultiplier)
  + [sc.SimpleMovAvg()](#scsimplemovavg)
  + [sc.Slope()](#scslope)
  + [sc.SlopeToAngleInDegrees()](#scslopetoangleindegrees)
  + [sc.SmoothedMovingAverage()](#scsmoothedmovingaverage)
  + [sc.StartChartReplay()](#scstartchartreplay)
  + [sc.StartChartReplayNew()](#scstartchartreplaynew)
  + [sc.StartDownloadHistoricalData()](#scstartdownloadhistoricaldata)
  + [sc.StartScanOfSymbolList()](#scstartscanofsymbollist)
  + [sc.StdDeviation()](#scstddeviation)
  + [sc.StdError()](#scstderror)
  + [sc.Stochastic()](#scstochastic)
  + [sc.StopChartReplay()](#scstopchartreplay)
  + [sc.StopScanOfSymbolList()](#scstopscanofsymbollist)
  + [sc.StringToDouble()](#scstringtodouble)
  + [sc.SubmitOCOOrder()](#scsubmitocoorder)
  + [sc.Summation()](#scsummation)
  + [sc.SuperSmoother2Pole()](#scsupersmoother2pole)
  + [sc.SuperSmoother3Pole()](#scsupersmoother3pole)
  + [sc.T3MovingAverage()](#sct3movingaverage)
  + [sc.TEMA()](#sctema)
  + [sc.TicksToPriceValue()](#sctickstopricevalue)
  + [sc.TimeMSToString()](#sctimemstostring)
  + [sc.TimePeriodSpan()](#sctimeperiodspan)
  + [sc.TimeSpanOfBar()](#sctimespanofbar)
  + [sc.TimeStringToSCDateTime()](#sctimestringtoscdatetime)
  + [sc.TimeToString()](#sctimetostring)
  + [sc.TradingDayStartsInPreviousDate()](#sctradingdaystartsinpreviousdate)
  + [sc.TriangularMovingAverage()](#sctriangularmovingaverage)
  + [sc.TRIX()](#sctrix)
  + [sc.TrueRange()](#sctruerange)
  + [sc.UltimateOscillator()](#scultimateoscillator)
  + [sc.UploadChartImage()](#scuploadchartimage)
  + [sc.UserDrawnChartDrawingExists()](#scuserdrawnchartdrawingexists)
  + [sc.UseTool()](#scusetool)
  + [sc.VersionNumber()](#scversionnumber)
  + [sc.VHF()](#scvhf)
  + [sc.VolumeWeightedMovingAverage()](#scvolumeweightedmovingaverage)
  + [sc.Vortex()](#scvortex)
  + [sc.WeightedMovingAverage()](#scweightedmovingaverage)
  + [sc.WellesSum()](#scwellessum)
  + [sc.WildersMovingAverage()](#scwildersmovingaverage)
  + [sc.WilliamsAD()](#scwilliamsad)
  + [sc.WilliamsR()](#scwilliamsr)
  + [sc.WriteBarAndStudyDataToFile()](#scwritebarandstudydatatofile)
  + [sc.WriteBarAndStudyDataToFileEx()](#scwritebarandstudydatatofileex)
  + [sc.WriteFile()](#scwritefile)
  + [sc.YPixelCoordinateToGraphValue()](#scypixelcoordinatetographvalue)
  + [sc.ZeroLagEMA()](#sczerolagema)
  + [sc.ZigZag()](#sczigzag)
  + [sc.ZigZag2()](#sczigzag2)
  + [min()](#minimumfunction)
  + [max()](#maximumfunction)
* [Persistent Variable Functions](#persistentvariablefunctions)
* [Fast Persistent Variable Functions](#fastpersistentvariablefunctions)
* [Chart Study Persistent Variable Functions](#chartstudypersistentvariablefunctions)
* [Common Function Parameter Descriptions / Common Parameters for Intermediate Study Calculation Functions](#commonfunctionparameterdescriptions)
  + [BarIndex](#commonfunctionparameterdescriptionsbarindex)
  + [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
  + [BaseDateTimeIn](#commonfunctionparameterdescriptionsbasedatetimein)
  + [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
  + [DateTime](#commonfunctionparameterdescriptionsdatetime)
  + [DateTimeMS](#commonfunctionparameterdescriptionsdatetimems)
  + [FileHandle](#commonfunctionparameterdescriptionsfilehandle)
  + [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
  + [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
  + [Index](#commonfunctionparameterdescriptionsindex)
  + [Length](#commonfunctionparameterdescriptionslength)
  + [Price](#commonfunctionparameterdescriptionsprice)
  + [MovingAverageType](#commonfunctionparameterdescriptionsmovingaveragetype)
  + [Multiplier](#commonfunctionparameterdescriptionsmultiplier)
  + [StudyID](#commonfunctionparameterdescriptionsstudyid)
  + [StudySubgraphNumber](#commonfunctionparameterdescriptionsstudysubgraphnumber)
  + [Subgraph](#commonfunctionparameterdescriptionssubgraph)
  + [SubgraphIndex](#commonfunctionparameterdescriptionssubgraphindex)
  + [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout)
  + [Symbol](#commonfunctionparameterdescriptionssymbol)
* [Advanced Custom Study Tool and Chart Drawing Functions (Opens in a new page)](ACSILDrawingTools.md)
* [Automated Trading Functions and Variables for Trading System Studies (Opens in a new page)](ACSILTrading.md)

---

## Notes About Output Arrays for Functions

[Link](#notesaboutoutputarraysforfunctions) - [Top](#top)

In the descriptions below for the functions, Intermediate Study Calculation Functions are identified by ***Type**: Intermediate Study Calculation Function* in the description.

Intermediate Study Calculation Functions in most cases require one or more or arrays for output of the results. These can take one of two types.

These types can be: **SCFloatArrayRef** (a reference to a Sierra Chart array of Float values) or **SCSubgraphRef** (a reference to a sc.Subgraph[] which contains multiple SCFloatArray arrays).

### SCFloatArrayRef

[Link](#scfloatarrayref) - [Top](#top)

**SCFloatArrayRef**: For this type you can pass a **sc.Subgraph[].Data** array using [sc.Subgraph[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData) or [sc.Subgraph[].Data](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData). In the case of **sc.Subgraph[]**, the **Data** array will automatically be passed since there is a conversion operator on that object which returns the **Data** array when a **SCFloatArrayRef** is required.

Both of these are equivalent to each other. In each case, the **sc.Subgraph[].Data[]** array of floats will get passed in.

Or, you can pass in a sc.Subgraph[] internal extra array using **sc.Subgraph[].Arrays[]**. If you do not need visible output on the chart for the results and you want to conserve the visible/graphable sc.Subgraph[].Data arrays, then use a **sc.Subgraph[].Arrays[]** internal extra array by passing a [sc.Subgraph[].Arrays[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphArrays) for the output array parameter.

### SCSubgraphRef

[Link](#scsubgraphref) - [Top](#top)

**SCSubgraphRef**: For this type you can only pass a [sc.Subgraph[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraph).

The **SCSubgraphRef** type is required because internally the function will use the available internal extra arrays which are part of a sc.Subgraph. These arrays are either used for internal calculations or are used for additional output.

If they are used for additional output, then that is clearly explained in the documentation for the function. For example, the [sc.MACD()](#scmacd) function will place output for additional MACD related lines into the sc.Subgraph[].Arrays[].

There is one point of clarification. When an sc.Subgraph is required, you cannot use sc.Subgraph[].Data. You must only use sc.Subgraph[]. This will pass in the entire sc.Subgraph[] object because the function requires an sc.Subgraph[] object.

When using a sc.Subgraph[] object and you do not want to have the result of the Intermediate Study Calculation Function actually drawn on the chart, then set [sc.Subgraph[].DrawStyle](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphDrawStyle) = **DRAWSTYLE\_IGNORE**.

## Array Based Study Functions That Do Not Use the Index Parameter

[Link](#noindexparam) - [Top](#top)

The Advanced Custom Study Interface has versions of functions (function "overloads" as known in C++) that take input and output arrays as parameters, and do not require the **Index** parameter.

These functions are called *Intermediate Study Calculation Functions* whether they require the **Index** parameter or not.

For example, they may calculate a Moving Average from an input data array and place the results into an output data array.

The versions that do not require the **Index** parameter simplify the calling of these functions. If your study function uses **Automatic Looping** by setting **sc.AutoLoop = 1;** in the **if(sc.SetDefaults)** block, then you can use these functions.

The function versions that do not use the **Index** parameter *will not function properly when you are using Manual Looping*.

You will see an example below of a call to an Intermediate Study Calculation Function, that uses the **Index** parameter and another call to a second version of that same function that does not use the **Index** parameter.

If your study function is using Automatic Looping, then you can use a version of an Intermediate Study Calculation Function that takes the **Index** parameter or the one that does not.

Using the version that does not require the **Index** parameter simply makes writing your code simpler.

When an **Index** parameter is not specified, the calculation always begins at sc.Index and will refer to data at that index and prior indexes. For example, calculating a moving average with a **Length** of 10, will start the calculation at sc.Index and go back 9 prior index elements for a total of 10.

### Example

```cpp

if(sc.SetDefaults)
{
    //...
    sc.AutoLoop = 1;
    //...
}

//Calculates a 20 period moving average of Last prices.
sc.SimpleMovAvg(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], sc.Index, 20);

//Calculates a 20 period moving average of Last prices. 
//Index parameter not used. Same as above, but a more simple function call.
sc.SimpleMovAvg(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20);
        
```

## Return Object of Array Based Study Functions

[Link](#returnobjectarraybasedstudyfunction) - [Top](#top)

Intermediate Study Calculation Functions that take an **SCFloatArrayRef** or **SCSubgraphRef** parameter for output, will return a **SCFloatArray** object by reference. This return object is either the SCFloatArray parameter, or the sc.SCSubgraph[].Data array of the sc.SCSubgraph parameter.

### Example

```cpp

SCSubgraphRef MidBand = sc.Subgraph[1];

// Copy the middle Bollinger band value to Subgraph 10 at the current index
sc.Subgraph[10][sc.index]= sc.BollingerBands(

sc.BaseDataIn[SC_LAST],
MidBand,
Length.GetInt(),
StandardDeviations.GetFloat(),

MAType.GetMovAvgType() )[sc.index];
        
```

## Working with Intermediate Study Calculation Functions

[Link](#workingwithintermediatestudycalculationfunctions) - [Top](#top)

The code example below demonstrates using Intermediate Study Calculation Functions.

### Example

```cpp

//Below are example calls to ACSIL intermediate study calculation functions.

//In this example we are giving the study function a graphable sc.Subgraph[].Data array.
//Even though that this Subgraph result can be drawn on the chart, it does not need to be
//if it does not have a visible DrawStyle
sc.SimpleMovAvg(sc.BaseData[SC_LAST], sc.Subgraph[0].Data, 10);

//Get the value from the calculation above
float AverageAtIndex = sc.Subgraph[0].Data[sc.Index];

//In this example we are giving the study function a Subgraph internal extra
//array which is not capable of being graphed.
sc.SimpleMovAvg(sc.BaseData[SC_LAST], sc.Subgraph[0].Arrays[0], 10);

AverageAtIndex = sc.Subgraph[0].Arrays[0][sc.Index];
        
```

The actual source code for intermediate study calculations functions is located in the **SCStudyFunctions.cpp** file in the **/ACS\_Source** folder in the folder Sierra Chart is installed to on your computer system.

## Cumulative Calculations with Intermediate Study Functions

[Link](#cumulativecalculationswithintermediatestudyfunctions) - [Top](#top)

The Output array parameter of a intermediate study calculation function can be used as the Input array parameter for another intermediate study calculation function.

The **scsf\_AverageOfAverage** function in the **/ACS\_Source/studies3.cpp** file in the Sierra Chart installation folder is an example of a function that shows how to use 2 intermediate study calculation functions (sc.LinearRegressionIndicator, sc.ExponentialMovAvg) together.

It calculates the Exponential Moving Average of a Linear Regression Indicator by passing the Output array from the Linear Regression Indicator to the Input array parameter of Exponential Moving Average.

## Functions

[Link](#functions) - [Top](#top)

### sc.AdaptiveMovAvg()

[Link](#scadaptivemovavg) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **AdaptiveMovAvg**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**, float **FastSmoothConstant**, float **SlowSmoothConstant**);

SCFloatArrayRef **AdaptiveMovAvg**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**, float **FastSmoothConstant**, float **SlowSmoothConstant**); [Auto-looping only](#noindexparam).

The **sc.AdaptiveMovAvg()** function calculates the standard Adaptive Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)
* **FastSmoothConstant**: Fast smoothing constant.
* **SlowSmoothConstant**: Slow smoothing constant.

#### Example

```cpp

sc.AdaptiveMovAvg(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20, 2.0f, 30.0f);

float MAValue = sc.Subgraph[0][sc.Index];
            
```

### sc.AddACSChartShortcutMenuItem()

[Link](#scaddacschartshortcutmenuitem) - [Top](#top)

Refer to the [sc.AddACSChartShortcutMenuItem()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scaddacschartshortcutmenuitem) page for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.AddACSChartShortcutMenuSeparator()

{[Link](#scaddacschartshortcutmenuseparator)] - [Top](#top)

Refer to the [sc.AddACSChartShortcutMenuSeparator()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scaddacschartshortcutmenuseparator) section for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.AddAlertLine()

[Link](#scaddalertline) - [Top](#top)

**Type**: Function

**AddAlertLine**(SCString **Message**, int **ShowAlertLog** = 0);

**AddAlertLine**(char\* **Message**, int **ShowAlertLog** = 0);

**sc.AddAlertLine()** is a function for adding an Alert Message to the Sierra Chart **Alerts Log**.

To open the Alerts Log, select **Window >> Alert Manager >> Alert Log**.

This function adds a type of Alert Message to the **Alerts Log** which allows the **Go to Chart**  commands on the **Alerts Log** to be used.

The  **Message**  text can be any text that you want to display in the **Alerts Log**. **Message** can be either a **SCString** type or a plain C++ string ("This is an Example").

**ShowAlertLog** needs to be set to **1** to cause the **Alerts Log** to open, if it is not already, when a message is added. Otherwise, **ShowAlertLog** needs to be **0** or it can be optionally left out to not open the **Alerts Log** when a message is added.

Refer to the **scsf\_LogAndAlertExample()** function in the **/ACS\_Source/studies.cpp** file in the Sierra Chart installation folder for example code to work with this function.

To make an Alert Message that contains formatted variables, refer to the [Working With Text Strings](ACSILProgrammingConcepts.md#workingwithtextstrings) section.

#### Example

```cpp

// Add an alert line to the Alerts Log
sc.AddAlertLine("Condition is TRUE");

sc.AddAlertLine("Condition is TRUE. The Alerts Log will open if it is not already.",1);

SCString MyString= "This is my string.";

sc.AddAlertLine(MyString,1);
            
```

### sc.AddAlertLineWithDateTime()

[Link](#scaddalertlinewithdatetime) - [Top](#top)

**Type**: Function

**AddAlertLineWithDateTime**(const char\* **Message**, int **ShowAlertLog**, SCDateTime **AlertDateTime**);

The **sc.AddAlertLineWithDateTime** function is identical to [sc.AddAlertLine](#scaddalertline) except that it has an AlertDateTime parameter of type [SCDateTime](SCDateTime.md), which can be set to a Date-Time value which will be included in the Alerts Log message.

When using the **Go to Chart** commands on the Alerts Log, the chart will be scrolled to this particular Date-Time.

### sc.AddAndManageSingleTextDrawingForStudy()

[Link](#scaddandmanagesingletextdrawingforstudy) - [Top](#top)

**Type**: Function

void **AddAndManageSingleTextDrawingForStudy**(SCStudyInterfaceRef& **sc**, bool **DisplayInFillSpace**, int **HorizontalPosition**, int **VerticalPosition**, SCSubgraphRef **Subgraph**, int **TransparentLabelBackground**, SCString& **TextToDisplay**, int **DrawAboveMainPriceGraph**, int **BoldFont**);

The **sc.AddAndManageSingleTextDrawingForStudy** function adds a text drawing to the chart based upon the given parameters and implements the low-level management of that drawing.

This drawing is a nonuser drawn type of drawing. It cannot be interacted with by the user on the chart.

Only a single text drawing can be added with this function per study instance. Multiple text drawings are not supported. To do multiple text drawings you need to use the [Text Drawing Tool](ACSILDrawingTools.md) from ACSIL.

Internally this function sets a persistent integer variable for the study instance with the key value of 11110000. Therefore, do not use the sc.GetPersistentInt() function with the same key value in the study function that you call **sc.AddAndManageSingleTextDrawingForStudy** from.

For an example to use this function, refer to the **scsf\_LargeTextDisplayForStudy** study function in the /ACS\_Source/studies3.cpp file in the Sierra Chart installation folder.

#### Parameters

* **sc**: A reference to the SCStudyInterface structure given to the study function. This will be the **sc** structure.
* **DisplayInFillSpace**: Set to 1 to indicate that the drawing should be displayed in the fill space on the right side of the chart.
* **HorizontalPosition**: Sets the horizontal position relative to the left edge of the chart window. For more details, refer to [s\_UseTool::BeginDateTime](ACSILDrawingTools.md#susetoolbegindatetime). This is not a Date-Time value.
* **VerticalPosition**: This is a relative vertical value relative to the bottom of the Chart Region the study is located in. This is not a price value. For more details, refer to [s\_UseTool::BeginValue](ACSILDrawingTools.md#susetoolbeginvalue).
* [Subgraph](#commonfunctionparameterdescriptionssubgraph): This is a reference to the study Subgraph which controls the text color and text size. The Subgraph needs to have the DrawStyle set to DRAWSTYLE\_CUSTOM\_TEXT.
* **TransparentLabelBackground**: Set to 1 to use a transparent background for the text.
* **TextToDisplay**: The text string to display.
* **DrawAboveMainPriceGraph**: Set to 1 to draw above the main price graph, which means it will be displayed above the chart bars.
* **BoldFont**: Set to 1 to use a bold font. Set this to 0 to not use a bold font.

### sc.AddAndManageSingleTextUserDrawnDrawingForStudy()

[Link](#scaddandmanagesingletextuserdrawndrawingforstudy) - [Top](#top)

**Type**: Function

void **AddAndManageSingleTextUserDrawnDrawingForStudy**(SCStudyInterfaceRef& **sc**, int **Unused**, int **HorizontalPosition**, int **VerticalPosition**, SCSubgraphRef **Subgraph**, int **TransparentLabelBackground**, SCString& **TextToDisplay**, int **DrawAboveMainPriceGraph**, int **LockDrawing**, int **UseBoldFont**);

The **sc.AddAndManageSingleTextUserDrawnDrawingForStudy** function adds a text drawing to the chart based upon the given parameters and implements the low-level management of that drawing.

This drawing is a [user drawn type](ACSILDrawingTools.md#susetooladdasuserdrawndrawing) of drawing. It can be interacted with by the user on the chart.

Otherwise, this function is generally functions the same as [sc.AddAndManageSingleTextDrawingForStudy](#scaddandmanagesingletextdrawingforstudy).

There are some differences with parameters. For the parameters of this function, refer to them below.

For an example to use this function, refer to the **scsf\_ClockRealTime** study function in the /ACS\_Source/studies2.cpp file in the Sierra Chart installation folder.

Internally this function uses the first four bytes of the [sc.StorageBlock](ACSIL_Members_Variables_And_Arrays.md#scstorageblock). Therefore, do not use the same part of the storage block in the study function that you call **sc.AddAndManageSingleTextUserDrawnDrawingForStudy** from.

#### Parameters

* **sc**: A reference to the SCStudyInterface structure given to the study function.
* **Unused**: This is an unused variable. Enter any integer value as a placeholder.
* **HorizontalPosition**: Sets the horizontal position relative to the left edge of the chart window. For more details, refer to [s\_UseTool::BeginDateTime](ACSILDrawingTools.md#susetoolbegindatetime). This is not a Date-Time value.
* **VerticalPosition**: This is a relative vertical value relative to the bottom of the Chart Region the study is located in. This is not a price value. For more details, refer to [s\_UseTool::BeginValue](ACSILDrawingTools.md#susetoolbeginvalue).
* **Subgraph**: This is a reference to the study Subgraph which controls the text color and text size. The Subgraph needs to have the DrawStyle set to DRAWSTYLE\_CUSTOM\_TEXT.
* **TransparentLabelBackground**: Set to 1 to use a transparent background for the text.
* **TextToDisplay**: The text string to display.
* **DrawAboveMainPriceGraph**: Set to 1 to draw above the main price graph, which means it will be displayed above the chart bars.
* **LockDrawing**: Set to 1 to have the drawing be locked.
* **BoldFont**: Set to 1 to use a bold font. Set to 0 to not use a bold font.

### sc.AddDateToExclude()

[Link](#scadddatetoexclude) - [Top](#top)

**Type**: Function

int **AddDateToExclude**(const int **ChartNumber**, const SCDateTime& **DateToExclude**);

The **sc.AddDateToExclude()** function adds the specified date for the chart to the list of [Dates to Exclude](ChartSettings.md#datestoexclude).

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **DateToExclude**: The [Date](SCDateTime.md) to add to the list of excluded dates.

### sc.AddElements()

[Link](#scaddelements) - [Top](#top)

**Type**: Function

int **AddElements**(int **NumElements**);

**sc.AddElements()** adds the number of elements specified with the **NumElements** parameter, to the [sc.Subgraph[].Data[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData) arrays.

The arrays up to the last actually used **sc.Subgraph[].Data** array, will actually have elements added. Unused **sc.Subgraph[].Data** arrays will be left un-allocated until they are needed.

This function must only used when you have set **[sc.IsCustomChart](ACSIL_Members_Variables_And_Arrays.md#sciscustomchart)** to 1 (TRUE).

The function returns 0 if it fails to add the requested number of elements to all the arrays.

This function also adds elements to the [sc.DateTimeOut[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scDateTimeOut) , [sc.Subgraph[].DataColor[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphDataColor), and [sc.Subgraph[].Arrays[][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphArrays) arrays if they are used.

#### Example

```cpp

sc.AddElements(5); // Add five elements to the arrays
            
```

### sc.AddLineUntilFutureIntersection()

[Link](#scaddlineuntilfutureintersection) - [Top](#top)

**Type**: Function

**AddLineUntilFutureIntersection**(int **StartBarIndex**
, int **LineIDForBar**
, float **LineValue**
, COLORREF **LineColor**
, unsigned short **LineWidth**
, unsigned short **LineStyle**
, int **DrawValueLabel**
, int **DrawNameLabel**
, const SCString& **NameLabel**);

The **sc.AddLineUntilFutureIntersection()** function draws a line from the chart bar specified by the **StartBarIndex** parameter which specifies its array index, and at the value specified by the **LineValue** parameter. The line extends until it is intersected by a future price bar. The other supported parameters are described below.

All lines added by this function are automatically deleted any time the study they were added by, is removed from the chart or any time [sc.IsFullRecalculation](ACSIL_Members_Variables_And_Arrays.md#scisfullrecalculation) is TRUE.

Therefore, there is no need to delete them by calling [sc.DeleteLineUntilFutureIntersection](#scdeletelineuntilfutureintersection). However, this function can be used in other cases.

The type of line drawn by the **sc.AddLineUntilFutureIntersection()** function is *not* related to [Chart Drawing Tools](Tools.md) or to the [sc.UseTool](ACSILDrawingTools.md#usingtools) function.

#### Parameters

* **StartBarIndex**: This is the array index of the bar that the line begins at.
* **LineIDForBar**: This is the identifier of the extension line for a chart bar. If there is only one line for a chart bar, this can be set to 0 and that will be the identifier. If there are multiple lines for a chart bar, each line needs to have a unique integer identifier. When you want to update the line, specify the same **LineIDForBar** as was previously specified.
* **LineValue**: This the vertical axis level at which the line is drawn at.
* **LineColor**: This is the color of the line.
* **LineWidth**: This is the width of the line in pixels.
* **LineStyle**: This is the style of the line. For the available integer constants which can be used, refer to [sc.Subgraph[].LineStyle](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphLineStyle).
* **DrawValueLabel**: Set this to 1/TRUE to draw value label with the line. This will be the **LineValue** displayed as text.
* **DrawNameLabel**: Set this to 1/TRUE to draw a name label with the line.
* **NameLabel**: When **DrawNameLabel** is set to 1/TRUE, then the specifies the text to display.

#### Example

For an example to use the function, refer to the **scsf\_ExtendClosesUntilFutureIntersection** function in the **/ACS\_Source/studies5.cpp** in the Sierra Chart installation folder.

### sc.AddLineUntilFutureIntersectionEx()

[Link](#scaddlineuntilfutureintersectionex) - [Top](#top)

**Type**: Function

**AddLineUntilFutureIntersectionEx**(const n\_ACSIL::s\_LineUntilFutureIntersection **LineUntilFutureIntersection**);

The **sc.AddLineUntilFutureIntersectionEx()** function draws a line from the chart bar specified by the **n\_ACSIL::s\_LineUntilFutureIntersection::StartBarIndex** parameter which specifies its array index, and at the value specified by the **n\_ACSIL::s\_LineUntilFutureIntersection::LineValue** parameter.

The line extends until it is intersected by a future price bar. The other supported parameters are described below.

All lines added by this function are automatically deleted any time the study they were added by, is removed from the chart or any time [sc.IsFullRecalculation](ACSIL_Members_Variables_And_Arrays.md#scisfullrecalculation) is TRUE.

Therefore, there is no need to delete them by calling [sc.DeleteLineUntilFutureIntersection](#scdeletelineuntilfutureintersection). However, this function can be used in other cases.

The type of line drawn by the **sc.AddLineUntilFutureIntersectionEx()** function is *not* related to [Chart Drawing Tools](Tools.md) or to the [sc.UseTool](ACSILDrawingTools.md#usingtools) function.

#### s\_LineUntilFutureIntersection struct

* **StartBarIndex (int)**: This variable can be set to the chart bar index where the future intersection line needs to stop. Once this is set to a nonzero value, the line will no longer automatically stop when it intersects a price bar. When EndBarIndex is set, the ending chart bar index is controlled by the study directly.
* **EndBarIndex** (int): When this is set to a nonzero value, it specifies at what chart bar index the future intersection line will end. Therefore, it no longer extends until intersecting with a particular price bar.   
     
  When this is set to a nonzero value, it is the study itself which controls the ending chart bar index of the line.
* **LineIDForBar** (int): This is the identifier of the extension line for a chart bar. If there is only one line for a chart bar, this can be set to 0 and that will be the identifier. If there are multiple lines for a chart bar, each line needs to have a unique integer identifier. When you want to update the line, specify the same **LineIDForBar** as was previously specified.
* **LineValue** (float): This the vertical axis level at which the line is drawn at.
* **LineValue2ForRange** (float): Refer to **UseLineValue2**.
* **UseLineValue2** (int): When **UseLineValue2** is set to a nonzero value, then **LineValue2ForRange** specifies the vertical axis value for the other side of the range that is filled with the **LineColor**. **LineValue** specifies one side of the range and **LineValue2ForRange** specifies the other side of the range and it is filled with the **LineColor**.
* **LineColor** (uint32\_t): This is the color of the line or the filled range.
* **LineWidth** (unsigned short): This is the width of the line in pixels. Only applicable when **UseLineValue2** is sent to 0.
* **LineStyle** (unsigned short): This is the style of the line. For the available integer constants which can be used, refer to [sc.Subgraph[].LineStyle](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphLineStyle). Only applicable when **UseLineValue2** is sent to 0.
* **DrawValueLabel** (int): Set this to 1/TRUE to draw value label with the line. This will be the **LineValue** displayed as text.
* **DrawNameLabel** (int): Set this to 1/TRUE to draw a name label with the line.
* **NameLabel** (SCString): When **DrawNameLabel** is set to 1/TRUE, then the specifies the text to display.
* **AlwaysExtendToEndOfChart** (int): When this is set to a nonzero value, then the line always extends to the end of the chart.
* **TransparencyLevel** (int): This specifies the transparency level as a percentage where 0 = 0% and 100 = 100%. 100 means that the extension line would not be visible.
* **PerformCloseCrossoverComparison** (int): When this is set to a nonzero value the future intersection is determined by the future intersection line crossing the closing prices of the bar.

#### Example

For an example to use the function, refer to the **scsf\_VolumeAtPriceThresholdAlertV2** function in the **/ACS\_Source/studies8.cpp** in the Sierra Chart installation folder.

### sc.AddMessageToLog()

[Link](#scaddmessagetolog) - [Top](#top)

**Type**: Function

**AddMessageToLog**( SCString& **Message**, int **Showlog**);

**sc.AddMessageToLog()** is used to add a message to the log. See the **scsf\_LogAndAlertExample()** function in the studies.cpp file inside the ACS\_Source folder inside of the Sierra Chart installation folder for example code on how to work with this function.

#### Example

```cpp

sc.AddMessageToLog("This line of text will be added to the Message Log, but the message log will not pop open.", 0);
sc.AddMessageToLog("This line of text will be added to the Message Log, and this call will show the Message Log.", 1);
            
```

If you want to make a message line that contains formatted variables to add to the Message Log, refer to the [Working With Text Strings and Setting Names](ACSILProgrammingConcepts.md#workingwithtextstrings) section.

### sc.AddStudyToChart()

[Link](#scaddstudytochart) - [Top](#top)

**Type**: Function

int **AddStudyToChart**(const n\_ACSIL::s\_AddStudy& **AddStudy**);

The **sc.AddStudyToChart** is used to add a new study to a chart. This function takes a reference to the **n\_ACSIL::s\_AddStudy** structure which is documented below which specifies all of the parameters.

The various inputs available with a study can be set with the [sc.SetChartStudyInput\*](#scsetchartstudyinputint) functions.

This is a delayed action function. This means that the operation to perform the function is delayed until after the study function which is calling this ACSIL function, returns. In the case of Automatic Looping, this would be the final return for the last element of the chart data arrays.

#### n\_ACSIL::s\_AddStudy structure

* **ChartNumber (int)**: The chart number to add the study to. This needs to be within the same Chartbook as the study function which is adding the study.
* **StudyID (int)**: The configured study identifier to add if it is a Sierra Chart built-in study. To see the Study Identifiers you need to be running a current version of Sierra Chart. The Study Identifiers are listed in the [Studies to Graph](ChartStudies.md#chartstudieswindow) list in the **Studies Window**. They are prefixed with: **S\_ID:**.
    
     
  When adding an advanced custom study this needs to be zero.
* **CustomStudyFileAndFunctionName (SCString)**: In the case of when adding an advanced custom study, this string specifies the DLL filename without extension, followed by a dot (.) character, and the function name to be added. When both StudyID and CustomStudyFileAndFunctionName have not been set and are at default values, then sc.AddStudy returns 0.
    
    
  This method can also be used to add built-in studies. In this case
  the DLL file name and function name can be determined through the **DLLName.FunctionName** setting in the [Study Settings](ChartStudies.md#technicalstudysettingswindow) window for the
  study. Example: ***SierraChartStudies\_64.scsf\_MovingAverageBlock***.
* **ShortName (SCString)**: This will be set as the short name for the added study. This can be used to get the ID for the study later using sc.GetStudyIDByName.

#### Example

```cpp

	// Do data processing
	int& r_MenuID = sc.GetPersistentInt(1);

	if (sc.LastCallToFunction)
	{
		// Remove menu items when study is removed
		sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, r_MenuID);

		return;
	}

	if (sc.UpdateStartIndex == 0 && r_MenuID <= 0)
	{
		r_MenuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "Add Study Example");
	}

	if (sc.MenuEventID == r_MenuID)
	{
		n_ACSIL::s_AddStudy AddStudy;
		AddStudy.ChartNumber = sc.ChartNumber;
		AddStudy.StudyID = 2;
		AddStudy.ShortName = "New Moving Average";

		sc.AddStudyToChart(AddStudy);
	}
            
```

### sc.AdjustDateTimeToGMT()

[Link](#scadjustdatetimetogmt) - [Top](#top)

**Type**: Function

**AdjustDateTimeToGMT**(const SCDateTime& **DateTime**);

The **sc.AdjustDateTimeToGMT()** function converts the given **DateTime** from the time zone Sierra Chart is set to, to the GMT time zone.

#### Parameters

* **DateTime**: An SCDateTime variable that holds the date and time.

#### Example

```cpp

SCDateTime DateTimeInGMT;
sc.AdjustDateTimeToGMT(sc.BaseDateTimeIn[sc.Index]);
            
```

### sc.ADX()

[Link](#scadx) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **ADX** (SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **DXLength**, int **DXMovAvgLength**);

SCFloatArrayRef **ADX** (SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **DXLength**, int **DXMovAvgLength**); [Auto-looping only](#noindexparam).

The **sc.ADX()** function calculates the Average Directional Index (ADX) study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout): For this function, sc.Subgraph[].Arrays[0-3] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [DXLength](#commonfunctionparameterdescriptionslength)
* [DXMovAvgLength](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.ADX(sc.BaseDataIn, sc.Subgraph[0], 14, 14);

float ADXValue = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.ADXR()

[Link](#scadxr) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **ADXR** (SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **DXLength**, int **DXMovAvgLength**, int **ADXRInterval**);

SCFloatArrayRef **ADXR** (SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **DXLength**, int **DXMovAvgLength**, int **ADXRInterval**); [Auto-looping only](#noindexparam).

The **sc.ADXR()** function calculates the Average Directional Movement Rating.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout): For this function, sc.Subgraph[].Arrays[0-4] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [DXLength](#commonfunctionparameterdescriptionslength)
* [DXMovAvgLength](#commonfunctionparameterdescriptionslength)
* [ADXRInterval](#commonfunctionparameterdescriptions)

#### Example

```cpp

sc.ADXR(sc.BaseDataIn, sc.Subgraph[0], 14, 14, 14);

float ADXRValue = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.AllocateMemory()

[Link](#scallocatememory) - [Top](#top)

**Type**: Function

void\* **AllocateMemory** (int **Size**);

The **sc.AllocateMemory** function allocates memory for the number of bytes specified by the **Size** parameter. A pointer to the beginning of the memory block is returned or a null pointer is returned if the memory could not be allocated by the operating system.

It is necessary to release the memory with the [sc.FreeMemory](#scfreememory) function when finished with the memory, or when  [sc.LastCallToFunction](ACSIL_Members_Variables_And_Arrays.md#sclastcalltofunction) is true.

It is also necessary to release the memory when the DLL module containing the custom study is released. For more information, refer to [Modifying Advanced Custom Study Code](AdvancedCustomStudyInterfaceAndLanguage.md#modifyingadvancedcustomstudycode).

#### Parameters

* **Size**: The number of bytes to allocate.

#### Example

*No example provided by SierraChart*

### sc.AngleInDegreesToSlope()

[Link](#scangleindegreestoslope) - [Top](#top)

**Type**: Function

double **AngleInDegreesToSlope**(double **AngleInDegrees**);

The  **sc.AngleInDegreesToSlope** function calculates the slope, rise over run, from the specified AngleInDegrees.

#### Parameters

* **AngleInDegrees**: The angle in degrees.

#### Example

```cpp

            double Slope = sc.AngleInDegreesToSlope(50);
            
```

### sc.ApplyStudyCollection()

[Link](#scapplystudycollection) - [Top](#top)

**Type**: Function

int **ApplyStudyCollection**(int **ChartNumber**, const SCString& **StudyCollectionName**, const int **ClearExistingStudiesFromChart**);

The **sc.ApplyStudyCollection** function applies the specified [Study Collection](StudyCollections.md) to the specified chart.

Returns 1 if there is no error. Returns 0 if **ChartNumber** is invalid. A 1 will be returned even if **StudyCollectionName** is not found.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber): The Chart Number to apply the Study Collection to.
* **StudyCollectionName**: The Study Collection name. This must not include the path or the file extension (.StdyCollct).
* **ClearExistingStudiesFromChart**: This can be set to 1 to clear the existing studies from the chart or 0 to not clear the existing studies from the chart. In either case, there is no prompt when the Study Collection is applied to the chart.

### sc.ArmsEMV()

[Link](#scarmsemv) - [Top](#top)

**Type**: Intermediate Study Calculation Function

This study function calculates the Arms Ease of Movement study.

SCFloatArrayRef **ArmsEMV**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int VolumeDivisor, int **Index**);

SCFloatArrayRef **ArmsEMV**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int VolumeDivisor); [Auto-looping only](#noindexparam).

The **sc.ArmsEMV()** function calculates the Arms Ease of Movement Value.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* **VolumeDivisor**: The Volume Divisor as an Integer.
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.ArmsEMV(sc.BaseDataIn, sc.Subgraph[0], 10);

float ArmsEMV = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.ArnaudLegouxMovingAverage()

[Link](#scarnaudlegouxmovingaverage) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **ArnaudLegouxMovingAverage**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**, float **Sigma**, float **Offset**);

SCFloatArrayRef **ArnaudLegouxMovingAverage**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**, float **Sigma**, float **Offset**); [Auto-looping only](#noindexparam).

The **sc.ArnaudLegouxMovingAverage()** function calculates the Arnaud Legoux Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)
* **Sigma:** This parameter partially controls the width of the Gaussian distribution of the weights. It does **not** play the role of a standard deviation. The standard deviation of the distribution is determined by Length/Sigma.
* **Offset:** This parameter partially controls the center of the Gaussian distribution of the weights. The center is determined by floor(Offset\*(Length - 1)).

#### Example

```cpp

sc.ArnaudLegouxMovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 9, 6.0f, 0.5f);

float ArnaudLegouxMovingAverage = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.AroonIndicator()

[Link](#scaroonindicator) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **AroonIndicator**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **AroonIndicator**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.AroonIndicator()** function calculates the Aroon Indicator.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, 1 sc.Subgraph[].Arrays[] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.AroonIndicator(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 10);
float AroonIndicatorUp = sc.Subgraph[0][sc.Index]; //Access the Aroon Indicator Up study value at the current index 
float AroonIndicatorDown = sc.Subgraph[0].Arrays[0][sc.Index]; //Access the Aroon Indicator Down study value at the current index
            
```

### sc.ArrayValueAtNthOccurrence()

[Link](#scarrayvalueatnthoccurrence) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **ArrayValueAtNthOccurrence**(SCFloatArrayRef **FloatArrayIn1**, SCFloatArrayRef **FloatArrayIn2**, int **Index**, int **NthOccurrence**);

SCFloatArrayRef **ArrayValueAtNthOccurrence**(SCFloatArrayRef **FloatArrayIn1**, SCFloatArrayRef **FloatArrayIn2**, int **NthOccurrence** ); [Auto-looping only](#noindexparam).

The **sc.ArrayValueAtNthOccurrence()** function iterates the **FloatArrayIn1** array for non-zero values starting at **Index** and going back. When the number of non-zero values found in **FloatArrayIn1** equals the number specified by **NthOccurrence**, then the value of **FloatArrayIn2** is returned at the **Index** where the **NthOccurrence** of non-zero values was found in **FloatArrayIn1**.

For an example, refer to the **scsf\_ArrayValueAtNthOccurrenceSample** function in the /ACS\_Source/studies6.cpp file.

#### Parameters

* [FloatArrayIn1](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayIn2](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* **NthOccurrence**: The number of occurrences of the value that need to be found before returning the value.

#### Example

```cpp

SCSubgraphRef ValueAtOccurence = sc.Subgraph[1];
ValueAtOccurence[sc.Index] = sc.ArrayValueAtNthOccurrence(StochasticData.Arrays[1],
StochasticData, NumberOfOccurrences.GetInt());
            
```

### sc.ATR()

[Link](#scatr) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **ATR**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**, unsigned int **MovingAverageType**);

SCFloatArrayRef **ATR**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Length**, unsigned int **MovingAverageType**); [Auto-looping only](#noindexparam).

SCFloatArrayRef **ATR**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut\_1**, SCFloatArrayRef **FloatArrayOut\_2**, int **Index**, int **Length**, unsigned int **MovingAverageType**);

SCFloatArrayRef **ATR**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut\_1**, SCFloatArrayRef **FloatArrayOut\_2** , int **Length**, unsigned int **MovingAverageType**);

THe **sc.ATR()** function calculates the Average TRUE Range.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, 1 sc.Subgraph[].Arrays[] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)
* [MovingAverageType](#commonfunctionparameterdescriptionsmovingaveragetype)
* [FloatArrayOut\_1](#commonfunctionparameterdescriptionsfloatarrayout). This is the True Range output array. This is for the implementation of sc.ATR which does not require a SCSubgraphRef.
* [FloatArrayOut\_2](#commonfunctionparameterdescriptionsfloatarrayout). This is the Average True Range output array. This is for the implementation of sc.ATR which does not require a SCSubgraphRef.

#### Example

```cpp

sc.ATR(sc.BaseDataIn, sc.Subgraph[0], 20, MOVAVGTYPE_SIMPLE);

float ATR = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.AwesomeOscillator()

[Link](#scawesomeoscillator) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **AwesomeOscillator**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length1**, int **Length2**);

SCFloatArrayRef **AwesomeOscillator**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Length1**, int **Length2**); [Auto-looping only](#noindexparam).

The **sc.AwesomeOscillator()** function calculates the Awesome Oscillator study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-1] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length1](#commonfunctionparameterdescriptionslength)
* [Length2](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

SCSubgraphRef MovAvgDiff = sc.Subgraph[0];
sc.AwesomeOscillator(sc.BaseDataIn[InputData.GetInputDataIndex()], MovAvgDiff, MA1Length.GetInt(), MA2Length.GetInt());
            
```

### sc.BarIndexToXPixelCoordinate()

[Link](#scbarindextoxpixelcoordinate) - [Top](#top)

**Type**: Function

int **BarIndexToXPixelCoordinate**(int **Index**);

The **sc.BarIndexToXPixelCoordinate** function will calculate the corresponding X-axis pixel coordinate from the given chart bar **Index** .

The returned x-coordinate is in relation to the chart window itself.

#### Example

```cpp
 
int X = sc.BarIndexToXPixelCoordinate (sc.Index);
            
```

### sc.BollingerBands()

[Link](#scbollingerbands) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **BollingerBands** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**, float **Multiplier**, int **MovingAverageType**);

SCFloatArrayRef **BollingerBands** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Length**, float **Multiplier**, int **MovingAverageType**); [Auto-looping only](#noindexparam).

The **sc.BollingerBands()** function calculates the Bollinger or Standard Deviation bands.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-1] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)
* [Multiplier](#commonfunctionparameterdescriptionsmultiplier)
* [MovingAverageType](#commonfunctionparameterdescriptionsmovingaveragetype)

#### Example

```cpp

sc.BollingerBands(sc.BaseData[SC_LAST], sc.Subgraph[0], 10, 1.8, MOVAVGTYPE_SIMPLE);

//Access the individual lines
float Average = sc.Subgraph[0][sc.Index]; //Access the study value at the current index

float UpperBand = sc.Subgraph[0].Arrays[0][sc.Index];

float LowerBand = sc.Subgraph[0].Arrays[1][sc.Index];

//Copy to Visible Subgraphs
sc.Subgraph[1][sc.Index] = UpperBand;
sc.Subgraph[2][sc.Index] = LowerBand;
            
```

### sc.Butterworth2Pole()

[Link](#scbutterworth2pole) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Butterworth2Pole**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **Butterworth2Pole**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.Butterworth2Pole()** function calculates a smoothing of data and is frequently used in the studies written by John Ehlers.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.Butterworth2Pole(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 10);

float Butterworth2Pole = sc.Subgraph[0][sc.Index]; //Access the function value at the current index
            
```

### sc.Butterworth3Pole()

[Link](#scbutterworth3pole) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Butterworth3Pole**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **Butterworth3Pole**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.Butterworth3Pole()** function calculates a smoothing of data and is frequently used in the studies written by John Ehlers.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.Butterworth3Pole(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 10);

float Butterworth3Pole = sc.Subgraph[0][sc.Index]; //Access the function value at the current index
            
```

### sc.CalculateAngle()

[Link](#sccalculateangle) - [Top](#top)

**Type**: Function

void **CalculateAngle**(SCFloatArrayRef **InputArray**, SCFloatArrayRef **OutputArray**, int **Length**, float **ValuePerPoint**);

void **CalculateAngle**(SCFloatArrayRef **InputArray**, SCFloatArrayRef **OutputArray**, int **Index**, int **Length**, float **ValuePerPoint**);

**sc.CalculateAngle()** calculates the angle from the horizontal of a given line defined by the starting position of InputArray[Index - Length], the ending position of InputArray[Index] and the ValuePerPoint. The results are contained within OutputArray at each Index point.

#### Parameters

* **InputArray**: The array of input values.
* **OutputArray**: The array of output values.
* [Index](#commonfunctionparameterdescriptionsindex): The Index of the ending point within the InputArray.
* [Length](#commonfunctionparameterdescriptionslength): The size of the number of indices to go back to determine the starting point within the InputArray.
* **ValuePerPoint**: The slope of the line as Value per Index as defined in the InputArray.

### sc.CalculateLogLogRegressionStatistics()

[Link](#sccalculateloglogregressionstatistics) - [Top](#top)

**Type**: Function

void **CalculateLogLogRegressionStatistics** (SCFloatArrayRef **In**, double& **Slope**, double& **Y\_Intercept**, int **Index**, int **Length**);

void **CalculateLogLogRegressionStatistics** (SCFloatArrayRef **In**, double& **Slope**, double& **Y\_Intercept**, int **Length**); [Auto-looping only](#noindexparam)

The **CalculateLogLogRegressionStatistics** function returns a log log regression fit line Slope and Y-Intercept for a given set of inputs defined by **In** and over a period of **Length**.

#### Parameters

* [In](#commonfunctionparameterdescriptionsfloatarrayin)
* **Slope**: The returned slope of the log log regression fit line.
* **Y\_Intercept**: The returned y-intercept of the log log regression fit line.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

### sc.CalculateOHLCAverages()

[Link](#sccalculateohlcaverages) - [Top](#top)

**Type**: Function

int **CalculateOHLCAverages**(int **Index**);

int **CalculateOHLCAverages**(); [Auto-looping only](#noindexparam).

**sc.CalculateOHLCAverages()** calculates the averages from the **[sc.Subgraph[].Data[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData)** arrays **SC\_OPEN** (0), **SC\_HIGH** (1), **SC\_LOW** (2), **SC\_LAST** (3), and fills in the [sc.Subgraph[].Data[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData) arrays for subgraphs **SC\_OHLC** (4), **SC\_HLC** (5), and **SC\_HL** (6) for the elements at **Index**. You will want to use this if your study acts as a Main Price Graph. This would be the case when you set **[sc.UsePriceGraphStyle](ACSIL_Members_Variables_And_Arrays.md#scusepricegraphstyle)** and **[sc.DisplayAsMainPriceGraph](ACSIL_Members_Variables_And_Arrays.md#scdisplayasmainpricegraph)** to 1 (TRUE).

#### Parameters

* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

// Fill in the averages arrays
sc.CalculateOHLCAverages(sc.Index);
            
```

### sc.CalculateRegressionStatistics()

[Link](#sccalculateregressionstatistics) - [Top](#top)

**Type**: Function

void **CalculateRegressionStatistics** (SCFloatArrayRef **In**, double& **Slope**, double& **Y\_Intercept**, int **Index**, int **Length**);

void **CalculateRegressionStatistics** (SCFloatArrayRef **In**, double& **Slope**, double& **Y\_Intercept**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.CalculateRegressionStatistics()** function determines the slope and y-intercept of a linear regression fit to the **In** data starting at **Index** and going through **Length**

#### Parameters

* [In](#commonfunctionparameterdescriptionsfloatarrayin)
* **Slope**: The returned slope of the regression fit line to the input data.
* **Y\_Intercept**: the returned y intercept of the regression fit line to the input data.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

### sc.CalculateTimeSpanAcrossChartBars()

[Link](#sccalculatetimespanacrosschartbars) - [Top](#top)

**Type**: Function

double **CalculateTimeSpanAcrossChartBars**(int **FirstIndex**, int **LastIndex**);

The **sc.CalculateTimeSpanAcrossChartBars** function calculates the time span across the chart bars specified by the bar index parameters **FirstIndex** and **LastIndex**. The time length of the bar specified by **LastIndex** is also included in the time span.

If **FirstIndex** and **LastIndex** are the same, then the time length of the single specified bar will be what is returned.

The time span of a chart bar is determined to be the difference between the next bar's time and the bar's starting time. For the last bar in the chart, the time span is the difference between the last Date-Time contained within the chart bar and the bar's starting time.

However, the [Session Times](SessionTimes.md) can affect the calculation of the time span for a bar. The very last bar just before the **Session Times >> End Time** will cause the time span to be limited to this ending time. The **Session Times >> Start Time** is not relevant or used in the calculations.

The return type is a double which is directly equivalent to a [SCDateTime](SCDateTime.md) type and can be assigned to a SCDateTime type.

One useful purpose of this function is to determine if the particular span of time is sufficient enough for other calculations. This can be useful for detecting holidays.

### sc.CalculateTimeSpanAcrossChartBarsInChart()

[Link](#sccalculatetimespanacrosschartbarsinchart) - [Top](#top)

**Type:**: Function

void **CalculateTimeSpanAcrossChartBarsInChart**(int **ChartNumber**, int **FirstIndex**, int **LastIndex**, SCDateTime& **TimeSpan**);

The **sc.CalculateTimeSpanAcrossChartBarsInChart** function is nearly identical to the [sc.CalculateTimeSpanAcrossChartBars](#sccalculatetimespanacrosschartbars) function except that it allows a specific Chart to be referenced in the variable **ChartNumber** and returns the result in the referenced variable **TimeSpan**.

The **sc.CalculateTimespanAcrossChartBarsInChart** function calculates the time span across the chart bars specified by the bar index parameters **FirstIndex** and **LastIndex**. The time length of the bar specified by **LastIndex** is also included in the time span.

If **FirstIndex** and **LastIndex** are the same, then the time length of the single specified bar will be what is returned.

The time span of a chart bar is determined to be the difference between the next bar's time and the bar's starting time. For the last bar in the chart, the time span is the difference between the last Date-Time contained within the chart bar and the bar's starting time.

However, the [Session Times](SessionTimes.md) can affect the calculation of the time span for a bar. The very last bar just before the **Session Times >> End Time** will cause the time span to be limited to this ending time. The **Session Times >> Start Time** is not relevant or used in the calculations.

The information is returned in the **TimeSpan** variable, which is an SCDateTime variable.

### sc.CancelAllOrders()

[Link](#sccancelallorders) - [Top](#top)

Refer to the [sc.CancelAllOrders()](ACSILTrading.md#cancelallorders) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.CancelOrder()

[Link](#sccancelorder) - [Top](#top)

Refer to the [sc.CancelOrder()](ACSILTrading.md#cancelorder) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.CCI()

[Link](#sccci) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **CCI**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**, float **Multiplier**);

SCFloatArrayRef **CCI**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Length**, float **Multiplier**); [Auto-looping only](#noindexparam).

The **sc.CCI()** function calculates the Commodity Channel Index.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0] (Extra Array) is used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)
* [Multiplier](#commonfunctionparameterdescriptionsmultiplier)

#### Example

```cpp

// Subgraph 0 will contain the CCI output
sc.CCI(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20, 0.015);

float CCI = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.ChaikinMoneyFlow()

[Link](#scchaikinmoneyflow) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **ChaikinMoneyFlow**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **ChaikinMoneyFlow**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.ChaikinMoneyFlow()** function calculates the Chaikin Money Flow.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function,
  sc.Subgraph[].Arrays[0] (Extra Array) is used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.ChaikinMoneyFlow(sc.BaseDataIn, sc.Subgraph[0], 10);

float ChaikinMoneyFlow = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.ChangeACSChartShortcutMenuItemText()

[Link](#scchangeacschartshortcutmenuitemtext) - [Top](#top)

Refer to the [sc.ChangeACSChartShortcutMenuItemText()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scchangeacschartshortcutmenuitemtext) page for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.ChangeChartReplaySpeed()

[Link](#scchangechartreplayspeed) - [Top](#top)

**Type**: Function

int **ChangeChartReplaySpeed**(int **ChartNumber**, float **ReplaySpeed**);

The **sc.ChangeChartReplaySpeed** function changes the replay speed for the replaying chart specified by the **ChartNumber** parameter.

It is only possible to specify Chart Numbers that are within the same Chartbook which contains the chart which contains the study instance that this function is called from.

The chart replay speed is changed *after* the study function returns.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* **ReplaySpeed**: The replay speed. A speed of 1 is the same as real time.

#### Example

```cpp

            int Result = sc.ChangeChartReplaySpeed(sc.ChartNumber, 10);
            
```

### sc.ChartbookName()

[Link](#scchartbookname) - [Top](#top)

**Type**: Function

SCString **ChartbookName**();

The **sc.ChartbookName** function returns the name of the chartbook that contains the chart on which the study that is calling this function is applied to.

### sc.ChartDrawingExists()

[Link](#scchartdrawingexists) - [Top](#top)

Refer to the [sc.ChartDrawingExists()](ACSILDrawingTools.md#scchartdrawingexists) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.ChartIsDownloadingHistoricalData()

[Link](#scchartisdownloadinghistoricaldata) - [Top](#top)

**Type**: Function

int **ChartIsDownloadingHistoricalData**(int **ChartNumber**);

The **sc.ChartIsDownloadingHistoricalData()** function returns TRUE (1) if the chart, referred to by the ChartNumber parameter, is downloading historical chart data. This function returns FALSE(0) if historical chart data is not being downloaded even when the chart data is being read from the local data file.

This result can be useful when calling functions that play alert sounds. For example, if historical chart data is being downloaded, then avoid calling the sc.PlaySound() function because many alerts may be generated by your study function from historical data being downloaded.

It is normal that when a chart is first initially opened and historical chart data is not immediately downloaded, for this function to initially return FALSE when the study is initially calculated. Thereafter, the historical data will be downloaded if necessary.

This function should not be called frequently. Normally it is recommended to use it with [manual looping](ACS_ArraysAndLooping.md) and only call it at most once per study function call. Or in the case of [automatic looping](ACS_ArraysAndLooping.md), it should be called only in relation to the most recent chart bar or once during a full recalculation.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

#### Example

```cpp

int IsDownloading = sc.ChartIsDownloadingHistoricalData(sc.ChartNumber);
SCString MessageText;
MessageText.Format("Downloading state: %d", IsDownloading);

sc.AddMessageToLog(MessageText.GetChars(), 0);

//Only play alert sound and add message if chart is not downloading historical data
if (IsDownloading == 0)
    sc.PlaySound(1,"My Alert Message");
            
```

### sc.ClearAlertSoundQueue()

[Link](#scclearalertsoundqueue) - [Top](#top)

**Type**: Function

void **ClearAlertSoundQueue**();

The **sc.ClearAlertSoundQueue** function clears the alert sound queue, stopping any additional sounds from playing.

### sc.ClearAllPersistentData()

[Link](#scclearallpersistentdata) - [Top](#top)

**Type**: Function

void **ClearAllPersistentData**();

The **sc.ClearAllPersistentData** function clears all persistent data variables which have been set through the [sc.GetPersistent\*()](#persistentvariablefunctions) or [sc.SetPersistent\*()](#persistentvariablefunctions)functions.

The persistent data is held in STL maps and these maps are fully cleared.

### sc.ClearCurrentTradedBidAskVolume()

[Link](#scclearcurrenttradedbidaskvolume) - [Top](#top)

**Type**: Function

uint32\_t **ClearCurrentTradedBidAskVolume**();

The **sc.ClearCurrentTradedBidAskVolume** function clears the current traded Bid and Ask volume for the symbol of the chart.

For further information, refer to [Current Traded Bid Volume](GlobalTradeSettings.md#columndescriptioncurrenttradedbidvolume).

### sc.ClearCurrentTradedBidAskVolumeAllSymbols()

[Link](#scclearcurrenttradedbidaskvolumeallsymbols) - [Top](#top)

**Type**: Function

uint32\_t **ClearCurrentTradedBidAskVolumeAllSymbols**();

The **sc.ClearCurrentTradedBidAskVolumeAllSymbols** function clears the Current Traded Bid and Ask Volume for all symbols in the current chartbook.

### sc.ClearKeyboardBufferForChart()

[Link](#scclearkeyboardbufferforchart) - [Top](#top)

**Type**: Function

int32\_t **ClearKeyboardBufferForChart**(const int32\_t **ChartNumber**);

The **sc.ClearKeyboardBufferForChart** function clears the keyboard buffer for the specified chart. For more information, refer to [Changing Chart Bars Period](ChangingPeriodOfBars.md) and [Clearing Character Input Buffer](SwitchingSymbols.md#clearingcharacterinputbuffer).

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

#### Example

```cpp

            sc.ClearKeyboardBufferForChart(sc.ChartNumber);
            
```

### sc.ClearMarketDepthPullingStackingData()

[Link](#scclearmarketdepthpullingstackingdata) - [Top](#top)

**Type**: Function

uint32\_t **ClearMarketDepthPullingStackingData**();

The **sc.ClearMarketDepthPullingStackingData** clears the Bid and Ask Pulling/Stacking columns data.

### sc.ClearMessageLog()

[Link](#scclearmessagelog) - [Top](#top)

**Type**: Function

int32\_t **ClearMessageLog**();

The **sc.ClearMessageLog** function clears the Message Log.

### sc.ClearRecentBidAskVolume()

[Link](#scclearrecentbidaskvolume) - [Top](#top)

**Type**: Function

uint32\_t **ClearRecentBidAskVolume**();

The **sc.ClearRecentBidAskVolume** function clears the Recent Bid and Ask Volume columns data for the symbol of the chart on which the study that calls this function is located.

Clearing this data on one chart for a symbol will clear the data for all charts that share this symbol

### sc.ClearRecentBidAskVolumeAllSymbols()

[Link](#scclearrecentbidaskvolumeallsymbols) - [Top](#top)

**Type**: Function

uint32\_t **ClearRecentBidAskVolumeAllSymbols**();

The **sc.ClearRecentBidAskVolumeAllSymbols** function clears the Recent Bid and Ask volume columns data for all symbols in all charts within the chartbook that contains the chart on which the study that calls this function is located.

### sc.CloseChart()

[Link](#scclosechart) - [Top](#top)

**Type**: Function

void **CloseChart**(int **ChartNumber**);

The **sc.CloseChart()** function closes the chart specified by the **ChartNumber** parameter. The chart must exist within the same Chartbook that the custom study is also contained in.

For an example, refer to the **scsf\_CloseChart** function in the **/ACS\_Source/studies5.cpp** file in the Sierra Chart installation folder.

### sc.CloseChartbook()

[Link](#scclosechartbook) - [Top](#top)

**Type**: Function

void **CloseChartbook**(const SCString& **ChartbookFileName**);

The **sc.CloseChartbook()** function closes the Chartbook specified by the **ChartbookFileName** filename parameter. The filename should not contain the path, only the filename.

For an example, refer to the **scsf\_CloseChartbook** function in the **/ACS\_Source/studies5.cpp** file in the Sierra Chart installation folder.

### sc.CloseFile()

[Link](#scclosefile) - [Top](#top)

**Type**: Function

int **CloseFile**(const int **FileHandle**);

The **sc.CloseFile()** function closes the file with the File Handle, **FileHandle**, for the file which was opened with [sc.OpenFile()](#scopenfile).

The function returns **False** if there is an error closing the file, otherwise it returns **True**.

Also refer to [sc.OpenFile](#scopenfile), [sc.CloseFile](#scclosefile), [sc.ReadFile](#screadfile), [sc.WriteFile](#scwritefile), [sc.GetLastFileErrorCode](#scgetlastfileerrorcode).

### sc.CombinedForegroundBackgroundColorRef()

[Link](#sccombinedforegroundbackgroundcolorref) - [Top](#top)

**Type**: Function

unsigned int **CombinedForegroundBackgroundColorRef**(COLORREF **ForegroundColor**, COLORREF **BackgroundColor**);

The **sc.CombinedForegroundBackgroundColorRef** function combines foreground and background color values into a single 32-bit value. This function is meant to be used to set the foreground and background colors through the [sc.Subgraph[].DataColor[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphDataColor) array when displaying a table of values on a chart.

Since two 24-bit color values are combined into a 32 bit value, it reduces the color detail and the exact colors are not necessarily going to be represented.

Refer to the code example below.

```cpp

sc.Subgraph[0].DataColor[sc.Index] = sc.CombinedForegroundBackgroundColorRef(COLOR_BLACK, COLOR_GREEN);
        
```

### sc.ConvertCurrencyValueToCommonCurrency()

[Link](#scconvertcurrencyvaluetocommoncurrency) - [Top](#top)

**Type**: Function

double **ConvertCurrencyValueToCommonCurrency**(double **CurrencyValue**, const SCString& **SourceSymbol**, SCString **&OutputCurrency**);

The **sc.ConvertCurrencyValueToCommonCurrency** function takes the parameters of **CurrencyValue** and **SourceSymbol**, determines the underlying currency for the given **SourceSymbol** based upon the **Currency** field of the Symbol Settings for that symbol and then returns the equivalent value in the [Common Profit/Loss Currency](GlobalTradeSettings.md#commonplcurrency) setting.

Typically the **SourceSymbol** would be set to sc.Symbol.

The **Common Profit/Loss Currency** setting must be set to a value other than **None** for this function to convert the price.

The **Common Profit/Loss Currency** symbol is also returned in the reference SCString variable **OutputCurrency**.

For additional information, refer to [Common Profit/Loss Currency](GlobalTradeSettings.md#commonplcurrency).

### sc.ConvertDateTimeFromChartTimeZone()

[Link](#scconvertdatetimefromcharttimezone) - [Top](#top)

**Type**: Function

SCDateTime **ConvertDateTimeFromChartTimeZone**(const SCDateTime& **DateTime**, const char\* **TimeZonePOSIXString**);

SCDateTime **ConvertDateTimeFromChartTimeZone**(const SCDateTime& **DateTime**, TimeZonesEnum **TimeZone**);

The **sc.ConvertDateTimeFromChartTimeZone()** function converts the **DateTime** parameter which is a [SCDateTime](SCDateTime.md) variable which should be in the time zone of the chart the study instance is applied to, to the time zone specified by the **TimeZone** parameter.

The destination time zone can also be specified as a POSIX text string specified by the TimeZonePOSIXString parameter. For a list of these strings refer to the TIME\_ZONE\_POSIX\_STRINGS array in the /ACS\_Source/SCConstants.h file in the folder where Sierra Chart is installed to.

List of **TimeZone** constants that can be used:

* TIMEZONE\_HONOLULU
* TIMEZONE\_ANCHORAGE
* TIMEZONE\_LOS\_ANGELES
* TIMEZONE\_PHOENIX\_ARIZONA
* TIMEZONE\_DENVER
* TIMEZONE\_CHICAGO
* TIMEZONE\_NEW\_YORK
* TIMEZONE\_HALIFAX
* TIMEZONE\_UTC
* TIMEZONE\_LONDON
* TIMEZONE\_BRUSSELS
* TIMEZONE\_CAPE\_TOWN
* TIMEZONE\_ATHENS
* TIMEZONE\_BAGHDAD
* TIMEZONE\_MOSCOW
* TIMEZONE\_DUBAI
* TIMEZONE\_ISLAMABAD
* TIMEZONE\_NEW\_DELHI
* TIMEZONE\_DHAKA
* TIMEZONE\_JAKARTA
* TIMEZONE\_HONG\_KONG
* TIMEZONE\_TOKYO
* TIMEZONE\_BRISBANE
* TIMEZONE\_SYDNEY
* TIMEZONE\_UTC\_PLUS\_12
* TIMEZONE\_AUCKLAND

### sc.ConvertDateTimeToChartTimeZone()

[Link](#scconvertdatetimetocharttimezone) - [Top](#top)

**Type**: Function

SCDateTime **ConvertDateTimeToChartTimeZone**(const SCDateTime& **DateTime**, const char\* **TimeZonePOSIXString**);

SCDateTime **ConvertDateTimeToChartTimeZone**(const SCDateTime& **DateTime**, TimeZonesEnum **TimeZone**);

The **sc.ConvertDateTimeToChartTimeZone()** function converts the **DateTime** SCDateTime variable from the specified **TimeZone** to the Time Zone used by the chart the study instance is applied to. This can either be the global Time Zone or a chart specific Time Zone. For additional information, refer to [Time Zone](TimeZone.md).

The source time zone can also be specified as a POSIX text string. For a list of these strings refer to the TIME\_ZONE\_POSIX\_STRINGS array in the /ACS\_Source/SCConstants.h file in the folder where Sierra Chart is installed to.

List of **TimeZone** constants that can be used:

* TIMEZONE\_HONOLULU
* TIMEZONE\_ANCHORAGE
* TIMEZONE\_LOS\_ANGELES
* TIMEZONE\_PHOENIX\_ARIZONA
* TIMEZONE\_DENVER
* TIMEZONE\_CHICAGO
* TIMEZONE\_NEW\_YORK
* TIMEZONE\_HALIFAX
* TIMEZONE\_UTC
* TIMEZONE\_LONDON
* TIMEZONE\_BRUSSELS
* TIMEZONE\_CAPE\_TOWN
* TIMEZONE\_ATHENS
* TIMEZONE\_BAGHDAD
* TIMEZONE\_MOSCOW
* TIMEZONE\_DUBAI
* TIMEZONE\_ISLAMABAD
* TIMEZONE\_NEW\_DELHI
* TIMEZONE\_DHAKA
* TIMEZONE\_JAKARTA
* TIMEZONE\_HONG\_KONG
* TIMEZONE\_TOKYO
* TIMEZONE\_BRISBANE
* TIMEZONE\_SYDNEY
* TIMEZONE\_UTC\_PLUS\_12
* TIMEZONE\_AUCKLAND

#### Example

```cpp

// Convert the DateTime from New York time to the time zone used for charts
DateTime = sc.ConvertDateTimeToChartTimeZone(DateTime, TIMEZONE_NEW_YORK);
DateTime.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);

// Write to the message log
SCString MessageString.Format("Converted from New York time: %d-%02d-%02d %02d:%02d:%02d", Year, Month, Day, Hour, Minute, Second);
sc.AddMessageToLog(MessageString, 1);
            
```

### sc.ConvertDateTimeUTCToChartTimeZone()

[Link](#scconvertdatetimeutctocharttimezone) - [Top](#top)

**Type**: Function

SCDateTime **ConvertDateTimeUTCToChartTimeZone**(const SCDateTime& **DateTime**);

The **sc.ConvertDateTimeUTCToChartTimeZone()** function converts a given DateTime specified in UTC to the date and time equivalent in the time zone of the chart on which the study that calls this function is located.

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime)

### sc.CreateDoublePrecisionPrice()

[Link](#sccreatedoubleprecisionprice) - [Top](#top)

**Type**: Function

double **CreateDoublePrecisionPrice**(const float **PriceValue**);

The **sc.CreateDoublePrecisionPrice()** function returns a double precision price from the given floating point PriceValue.

#### Parameters

* **PriceValue**: A floating point price.

### sc.CreateProfitLossDisplayString()

[Link](#createprofitlossdisplaystring) - [Top](#top)

**Type**: Function

void **CreateProfitLossDisplayString**(double **ProfitLoss**, int **Quantity**, PositionProfitLossDisplayEnum **ProfitLossFormat**, SCString& **Result**);

The **sc.CreateProfitLossDisplayString()** function creates a Profit/Loss text string based on the provided parameters.

The **Result** parameter is passed by reference and receives the formatted Profit/Loss text string.

#### Parameters

* **ProfitLoss**: The profit or loss value as a floating-point number.
* **Quantity**: The Position or Trade quantity.
* **ProfitLossFormat**: The profit or loss format. The possible entries are:
  + PPLD\_DO\_NOT\_DISPLAY
  + PPLD\_CURRENCY\_VALUE
  + PPLD\_POINTS
  + PPLD\_POINTS\_IGNORE\_QUANTITY
  + PPLD\_TICKS
  + PPLD\_TICKS\_IGNORE\_QUANTITY
  + PPLD\_CV\_AND\_POINTS
  + PPLD\_CV\_AND\_POINTS\_IGNORE\_QUANTITY
  + PPLD\_CV\_AND\_TICKS
  + PPLD\_CV\_AND\_TICKS\_IGNORE\_QUANTITYFor descriptions of these, refer to [Profit/Loss Format](ChartSettings.md#profitlossformat).
* **Result**: An [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings) variable to receive the formatted profit/loss string.

#### Example

```cpp

if (ShowOpenPL.GetYesNo())
{
    SCString PLString;
    double Commission = RTCommissionRate * PositionData.PositionQuantity / 2.0;
    sc.CreateProfitLossDisplayString(PositionData.OpenProfitLoss-Commission, PositionData.PositionQuantity, ProfitLossDisplayFormat, PLString);
    Text.Format("Open PL: %s", PLString.GetChars());
}
            
```

### sc.CrossOver()

[Link](#sccrossover) - [Top](#top)

**Type**: Function

int **CrossOver** (SCFloatArrayRef **First**, SCFloatArrayRef **Second**, int **Index**);

int **CrossOver** (SCFloatArrayRef **First**, SCFloatArrayRef **Second**); [Auto-looping only](#noindexparam).

**sc.CrossOver** returns a value indicating if the **First** study Subgraph has crossed the **Second** subgraph at the array index specified by **Index**.

For an example, refer to the **scsf\_StochasticCrossover** function in the /ACS\_Source/Systems.cpp file in the Sierra Chart installation folder.

**Function return values:**

* **CROSS\_FROM\_TOP** - This constant value is returned when the **First** subgraph crosses the **Second** subgraph from the top.
* **CROSS\_FROM\_BOTTOM** - This constant value is returned when the **First** subgraph crosses the **Second** subgraph from the bottom.
* **NO\_CROSS** - This constant value is returned when the **First** subgraph does not cross the **Second** subgraph.

'

#### Example

```cpp

if (sc.CrossOver(sc.Subgraph[3], sc.Subgraph[4]) == CROSS_FROM_BOTTOM)
{

    //Code
}

// This is an example of looking for a crossover between the values in
// a subgraph and a fixed value. We first have to put the fixed value
// into an array. We are using one of the Subgraph internal arrays.
sc.Subgraph[2].Arrays[8][sc.Index] = 100.0;

if (sc.CrossOver(sc.Subgraph[2], sc.Subgraph[2].Arrays[8]) == CROSS_FROM_BOTTOM)
{

    //Code
}
            
```

#### Checking for a Crossover between an Array of Values and a Fixed Value

[Link](#crossoverbetweenarrayandfixedvalue) - [Top](#top)

When you need to check for a crossover between a Subgraph array and a fixed value, you need to put the fixed value in an array first and pass this array to the sc.Crossover function. It is recommended to use one of the [sc.Subgraph. Arrays[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphArrays) for this purpose.

```cpp
	
//Check for crossover of Subgraph 0 and a fixed value set into an extra array on the Subgraph
SCFloatArrayRef FixedValueArray = sc.Subgraph[0].Arrays[4];
FixedValueArray[sc.Index] = 100;

//Check if a crossover occurred
if(sc.CrossOver(sc.Subgraph[0], FixedValueArray) != NO_CROSS)
{

}
            
```

### sc.CumulativeDeltaTicks()

[Link](#sccumulativedeltaticks) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **CumulativeDeltaTicks**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **ResetCumulativeCalculation**);

SCFloatArrayRef **CumulativeDeltaTicks**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **ResetCumulativeCalculation**); [Auto-looping only](#noindexparam).

The **sc.CumulativeDeltaTicks** function calculates the Cumulative Delta Ticks study and provides the Open, High, Low and Last values for each bar. This function can only be used on *Intraday* charts.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-2] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* **ResetCumulativeCalculation**: When this is set to TRUE, the cumulative calculations are reset back to 0. You may want to set this to TRUE at the **Index** which is at the start of a new trading day.

For an example of how to use a function of this type, refer to the **scsf\_CumulativeDeltaBarsTicks** function in the **/ACS\_Source/studies8.cpp** file in the Sierra Chart installation folder.

### sc.CumulativeDeltaTickVolume()

[Link](#sccumulativedeltatickvolume) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **CumulativeDeltaTickVolume**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **ResetCumulativeCalculation**);

SCFloatArrayRef **CumulativeDeltaTickVolume**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **ResetCumulativeCalculation**); [Auto-looping only](#noindexparam).

The **sc.CumulativeDeltaTickVolume** function calculates the Cumulative Delta Up/Down Tick Volume study and provides the Open, High, Low and Last values for each bar. This function can only be used on *Intraday* charts.

For an example of how to use a function of this type, refer to the  **scsf\_CumulativeDeltaBarsTicks**  function in the **/ACS\_Source/studies8.cpp** file in the Sierra Chart installation folder.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-2] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* **ResetCumulativeCalculation**: When this is set to TRUE, the cumulative calculations are reset back to 0. You may want to set this to TRUE at the **Index** which is at the start of a new trading day.

### sc.CumulativeDeltaVolume()

[Link](#sccumulativedeltavolume) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **CumulativeDeltaVolume**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **ResetCumulativeCalculation**);

SCFloatArrayRef **CumulativeDeltaVolume**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **ResetCumulativeCalculation**); [Auto-looping only](#noindexparam).

The **sc.CumulativeDeltaVolume** function calculates the Cumulative Delta Volume study and provides the Open, High, Low and Last values for each bar. This function can only be used on *Intraday* charts.

For an example of how to use a function of this type, refer to the  **scsf\_CumulativeDeltaBarsTicks**  function in the **/ACS\_Source/studies8.cpp** file in the Sierra Chart installation folder.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-2] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* **ResetCumulativeCalculation**: When this is set to TRUE, the cumulative calculations are reset back to 0. You may want to set this to TRUE at the **Index** which is at the start of a new trading day.

### sc.CumulativeSummation()

[Link](#sccumulativesummation) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **CumulativeSummation** (SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut,** int **Index**);

SCFloatArrayRef **CumulativeSummation** (SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**); [Auto-looping only](#noindexparam).

The **sc.CumulativeSummation** function calculates the summation of all of the elements in **FloatArrayIn** up to the current **Index**. Therefore, this function is cumulative in that the summation is across all of the elements in **FloatArrayIn** from the beginning.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.CumulativeSummation(sc.BaseDataIn[SC_HIGH], sc.Subgraph[0]);

float CumulativeSummation = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.CustomAffiliateCode()

[Link](#sccustomaffiliatecode) - [Top](#top)

**Type**: Function

SCString **CustomAffiliateCode**();

This is a deprecated function. It is still available, but will always return a NULL string.

### sc.CyberCycle()

[Link](#sccybercycle) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **CyberCycle**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArraySmoothed**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **CyberCycle**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArraySmoothed**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.CyberCycle()** function calculates Ehlers' Cyber Cycle study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* **FloatArraySmoothed**: This array holds the smoothed data that is used in the study calculation.
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.CyberCycle(sc.BaseDataIn[SC_LAST], Array_SmoothedData, sc.Subgraph[0], 28);

float CyberCycle = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.DataTradeServiceName()

[Link](#scdatatradeservicename) - [Top](#top)

**Type**: Function

SCString **DataTradeServiceName**();

The **sc.DataTradeServiceName()**  function returns the text name of the  **Service** currently set in **Global Settings >> Data/trade Service Settings**. The return type is a SCString.

### sc.DatesToExcludeClear()

[Link](#scdatestoexcludeclear) - [Top](#top)

**Type**: Function

int **sc.DatesToExcludeClear**(const int **ChartNumber**);

The **sc.DatesToExcludeClear()** function removes all dates from the [Dates to Exclude](ChartSettings.md#datestoexclude) for a chart.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

### sc.DateStringDDMMYYYYToSCDateTime()

[Link](#scdatestringddmmyyyytoscdatetime) - [Top](#top)

**Type**: Function

double **sc.DateStringDDMMYYYYToSCDateTime**(const SCString& **DateString**);

The **sc.DateStringDDMMYYYYToSCDateTime()** function converts the **DateString** text string parameter to an [SCDateTime](SCDateTime.md).

**DateString** is a [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings) type.

The return type is a double data type directly compatible with a SCDateTime and can be assigned to a SCDateTime.

#### Parameters

* **DateString**: The date string in the format DDMMYYYY (Day, Month, Year).

#### Example

```cpp

SCDateTime Date = sc.DateStringDDMMYYYYToSCDateTime("05012017");
            
```

### sc.DateStringToSCDateTime()

[Link](#scdatestringtoscdatetime) - [Top](#top)

**Type**: Function

SCDateTime **DateStringToSCDateTime**(const SCString& **DateString**);

The **sc.DateStringToSCDateTime()** function converts the **DateString** text string to an **SCDateTime**  variable. This function only works with dates.

#### Example

```cpp

SCString DateString ("2011-12-1");
SCDateTime DateValue;
DateValue = sc.DateStringToSCDateTime(DateString);
            
```

### sc.DateTimeToString()

[Link](#scdatetimetostring) - [Top](#top)

**Type**: Function

SCString **DateTimeToString**(const double& DateTime, int Flags);

The **sc.DateTimeToString** function will convert the given **DateTime** variable to a text string. The format is specified by the  **Flags**  parameter.

The flags can be any of the following:

* FLAG\_DT\_YEAR
* FLAG\_DT\_MONTH
* FLAG\_DT\_DAY
* FLAG\_DT\_HOUR
* FLAG\_DT\_MINUTE
* FLAG\_DT\_SECOND
* FLAG\_DT\_PLUS\_WITH\_TIME
* FLAG\_DT\_NO\_ZERO\_PADDING\_FOR\_DATE
* FLAG\_DT\_HIDE\_SECONDS\_IF\_ZERO
* FLAG\_DT\_NO\_HOUR\_PADDING
* FLAG\_DT\_MILLISECOND
* FLAG\_DT\_COMPACT\_DATE
* FLAG\_DT\_COMPLETE\_DATE
* FLAG\_DT\_COMPLETE\_TIME
* FLAG\_DT\_COMPLETE\_DATETIME
* FLAG\_DT\_COMPLETE\_DATETIME\_MS

#### Example

```cpp
 
if(sc.Index == sc.ArraySize - 1)
{
    // Log the current time
    SCString DateTimeString = sc.DateTimeToString(sc.CurrentSystemDateTime,FLAG_DT_COMPLETE_DATETIME_MS);

    sc.AddMessageToLog(DateTimeString, 0);
}
            
```

### sc.DateToString()

[Link](#scdatetostring) - [Top](#top)

**Type**: Function

SCString **DateToString**(const SCDateTime& DateTime);

The **sc.DateToString** function returns a text string for the date within the given **DateTime** parameter. Any time component in the given **DateTime** parameter will be ignored.

#### Example

```cpp
 
if (sc.Index == sc.ArraySize - 1)
{
    // Log the current date.
    SCString DateString = sc.DateToString(sc.CurrentSystemDateTime);

    sc.AddMessageToLog(DateString, 0);
}
            
```

### sc.DeleteACSChartDrawing()

[Link](#scdeleteacschartdrawing) - [Top](#top)

Refer to the [sc.DeleteACSChartDrawing()](ACSILDrawingTools.md#scdeleteacschartdrawing) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.DeleteLineUntilFutureIntersection()

[Link](#scdeletelineuntilfutureintersection) - [Top](#top)

**Type**: Function

int **DeleteLineUntilFutureIntersection**(int **StartBarIndex**, int **LineIDForBar**);

The **sc.DeleteLineUntilFutureIntersection** function deletes a line added by the [sc.AddLineUntilFutureIntersection](#scaddlineuntilfutureintersection) function.

#### Parameters

* **StartBarIndex**: This is the array index of the chart bar which was previously specified to the **sc.AddLineUntilFutureIntersection()** function, for the line to delete.
* **LineIDForBar**: This is the identifier of the extension line for the chart bar which was previously specified by the **sc.AddLineUntilFutureIntersection()** function, for the line to delete.

### sc.DeleteUserDrawnACSDrawing()

[Link](#scdeleteuserdrawnacsdrawing) - [Top](#top)

Refer to the [sc.DeleteUserDrawnACSDrawing()](ACSILDrawingTools.md#scdeleteuserdrawnacsdrawing) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.Demarker()

[Link](#scdemarker) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Demarker**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **Demarker**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.Demarker()** function calculates the Demarker study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-4] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.Demarker(sc.BaseDataIn, sc.Subgraph[0], 10);
float Demarker = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.Dispersion()

[Link](#scdispersion) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Dispersion**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **Dispersion**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.Dispersion()** function calculates the Dispersion study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.Dispersion(sc.BaseDataIn[SC_HIGH], sc.Subgraph[0], 10);

float Dispersion = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.DMI()

[Link](#scdmi) - [Top](#top)

**Type**: Intermediate Study Calculation Function

**DMI**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

**DMI**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.DMI()** function calculates the Directional Movement Index study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain): sc.BaseDataIn input arrays.
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-4] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.DMI(sc.BaseDataIn, sc.Subgraph[0], 10);

//Access the individual study values
float DMIPositive = sc.Subgraph[0][sc.Index];

float DMINegative = sc.Subgraph[0].Arrays[0][sc.Index];

//Copy DMINegative to a visible Subgraph
sc.Subgraph[1][sc.Index] = DMINegative;
            
```

### sc.DMIDiff()

[Link](#scdmidiff) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **DMIDiff** (SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **DMIDiff** (SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.DMIDiff()** function calculates the Directional Movement Index Difference study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-2] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.DMIDiff(sc.BaseDataIn, sc.Subgraph[0], 10);

float DMIDiff = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.DrawGraphics\_LineTo()

[Link](#scdrawgraphicslineto) - [Top](#top)

**Type**: Function

int **DrawGraphics\_LineTo**(const int **XCoordinate**, const int **YCoordinate**, const uint32\_t **Color**, const uint32\_t **LineWidth**, const SubgraphLineStyles **LineStyle**);

The **sc.DrawGraphics\_LineTo()** function draws a line from the starting point defined by the **sc.DrawGraphics\_MoveTo()** function, to the coordinates given in this function. It sets the line color, width, and style based on the passed-in variables.

#### Parameters

* **XCoordinate**: The x-axis coordinate for the ending point of the line, specified by the upper left corner being (0, 0) and increasing to the right.
* **YCoordinate**: The y-axis coordinate for the ending point of the line, specified by the upper left corner being (0, 0) and increasing going down.
* **Color**: The color of the line.
* **LineWidth**: The width of the line.
* **LineStyle**: The style of the line.

### sc.DrawGraphics\_MoveTo()

[Link](#scdrawgraphicsmoveto) - [Top](#top)

**Type**: Function

int **DrawGraphics\_MoveTo**(const int **XCoordinate**, const int **YCoordinate**);

The **sc.DrawGraphics\_MoveTo()** function specifies the starting location for a drawing by the specified parameters.

#### Parameters

* **XCoordinate**: The x-axis coordinate to move to, specified by the upper left corner being (0, 0) and increasing to the right.
* **YCoordinate**: The y-axis coordinate to move to, specified by the upper left corner being (0, 0) and increasing going down.

### sc.DominantCyclePeriod()

[Link](#scdominantcycleperiod) - [Top](#top)

**Type**: Intermediate Study Calculation Function.

SCFloatArrayRef **sc.DominantCyclePeriod** (SCFloatArrayRef In, SCSubgraphRef Out, int IndexParam, int MedianLength);

The **sc.DominantCyclePeriod()** function calculates the Dominant Cycle Period and is frequently used in the studies written by John Ehlers.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-6] (Extra Arrays) are used for internal calculations.
* [IndexParam](#commonfunctionparameterdescriptionsindex)
* [MedianLength](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.DominantCyclePeriod(sc.BaseData[SC_LAST], sc.Subgraph[0], 5);
            
```

### sc.DominantCyclePhase()

[Link](#scdominantcyclephase) - [Top](#top)

**Type**: Intermediate Study Calculation Function.

SCFloatArrayRef **sc.DominantCyclePhase** (SCFloatArrayRef In, SCSubgraphRef Out, int Index);

The **sc.DominantCyclePhase()** function calculates the Dominant Cycle Phase and is frequently used in the studies written by John Ehlers.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin): .
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout): For this function, sc.Subgraph[].Arrays[0-6] (Extra Arrays) are used for internal calculations.
* [Index](#commonfunctionparameterdescriptionsindex): .

#### Example

```cpp

sc.DominantCyclePhase(sc.BaseData[SC_LAST], sc.Subgraph[0]);
            
```

### sc.DoubleStochastic()

[Link](#scdoublestochastic) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **DoubleStochastic** (SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Length**, int **MovAvgLength**, int **MovingAverageType**);

SCFloatArrayRef **DoubleStochastic** (SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**, int **MovAvgLength**, int **MovingAverageType**); [Auto-looping only](#noindexparam).

The **sc.DoubleStochastic()** function calculates the Double Stochastic study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function,
  sc.Subgraph[].Arrays[0-3] (Extra Arrays) are used for internal calculations and
  additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)
* [MovAvgLength](#commonfunctionparameterdescriptionslength)
* [MovingAverageType](#commonfunctionparameterdescriptionsmovingaveragetype)

#### Example

```cpp

sc.DoubleStochastic(sc.BaseData, sc.Subgraph[0], Length.GetInt(), MovAvgLength.GetInt(), MovAvgType.GetMovAvgType());

//Access the study value at the current index
float DoubleStochastic = sc.Subgraph[0][sc.Index]; 
            
```

### sc.EnvelopeFixed()

[Link](#scenvelopefixed) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **EnvelopeFixed**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, float **FixedValue**, int **Index**);

SCFloatArrayRef **EnvelopeFixed**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, float **FixedValue**); [Auto-looping only](#noindexparam).

The **sc.EnvelopeFixed()** function calculates the Fixed Envelope study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0] (Extra Array) is used for internal calculations and additional results output.
* **FixedValue**: This is the amount added and subtracted to **FloatArrayIn** at the current **Index**.
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.EnvelopeFixed(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 3.5);
//Access the individual study values at the current index
float EnvelopeTop = sc.Subgraph[0][sc.Index]; 
float EnvelopeBottom = sc.Subgraph[0].Arrays[0][sc.Index];
            
```

### sc.EnvelopePct()

[Link](#scenvelopepct) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **EnvelopePct**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, float **Percent**, int **Index**);

SCFloatArrayRef **EnvelopePct**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, float **Percent**); [Auto-looping only](#noindexparam).

The **sc.EnvelopePct()** function calculates the Percentage Envelope study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0] (Extra Array) is used for internal calculations and additional results output.
* [Percent](#commonfunctionparameterdescriptions)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.EnvelopePct(sc.BaseDataIn[SC_HIGH], sc.Subgraph[0], 0.05);

//Access the individual study values at the current index
float Top = sc.Subgraph[0][sc.Index];

float Bottom = sc.Subgraph[0].Arrays[0][sc.Index];

//Copy to Visible Subgraphs
sc.Subgraph[1][sc.Index] = Bottom;
            
```

### sc.Ergodic()

[Link](#scergodic) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Ergodic**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **LongEMALength**, int **ShortEMALength**, float **Multiplier**);

SCFloatArrayRef **Ergodic**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **LongEMALength**, int **ShortEMALength**, float **Multiplier**); [Auto-looping only](#noindexparam).

The **sc.Ergodic()** function calculates the True Strength Index.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-5] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [LongEMALength](#commonfunctionparameterdescriptionslength)
* [ShortEMALength](#commonfunctionparameterdescriptionslength)
* [Multiplier](#commonfunctionparameterdescriptionsmultiplier)

#### Example

```cpp

sc.Ergodic(
    sc.BaseDataIn[SC_LAST],
    sc.Subgraph[0],
    15, // Long EMA length
    3, // Short EMA length
    1.0f, // Multiplier
);

// You can calculate the signal line and oscillator with the following code:

// Calculate the signal line with an exponential moving average with a length of 10
sc.ExponentialMovAvg(sc.Subgraph[0], sc.Subgraph[1], 10);

// Calculate the oscillator
sc.Subgraph[2][sc.Index] = sc.Subgraph[0][sc.Index] - sc.Subgraph[1][sc.Index];
            
```

### sc.EvaluateAlertConditionFormulaAsBoolean()

[Link](#scevaluatealertconditionformulaasboolean) - [Top](#top)

**Type**: Function

int **EvaluateAlertConditionFormulaAsBoolean**(int **BarIndex**, int **ParseAndSetFormula**);

The **sc.EvaluateAlertConditionFormulaAsBoolean()** function evaluates the Alert formula entered on the study that calls this function, and returns a 1 (true) or 0 (false) depending upon whether the formula is true or false at the specified **BarIndex**.

When the **ParseAndSetFormula** parameter is set to a nonzero value, then the Alert condition is internally formatted and stored prior to testing the condition at the BarIndex. It is necessary to set **ParseAndSetFormula** to a nonzero value the first time running this function or whenever the alert formula changes. It should not be set to a nonzero value every time because it is not efficient doing that.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex): Integer index value of the bar to evaluate the alert condition formula on.
* **ParseAndSetFormula**: Integer variable that when set to any value other than 0, forces an internal format and storage of the alert condition formula prior to evaluation.

### sc.EvaluateGivenAlertConditionFormulaAsBoolean()

[Link](#scevaluategivenalertconditionformulaasboolean) - [Top](#top)

**Type**: Function

int **EvaluateGivenAlertConditionFormulaAsBoolean**(int **BarIndex**, int **ParseAndSetFormula**, const SCString& **Formula**);

The **sc.EvaluateGivenAlertConditionFormulaAsBoolean()** function evaluates the given **Formula** parameter, and returns a 1 (true) or 0 (false) depending upon whether the given Formula at the specified **BarIndex** is true or false.

When the **ParseAndSetFormula** parameter is set to a nonzero value, then the **Formula** is internally formatted and stored prior to testing the condition at the **BarIndex**. It is necessary to set **ParseAndSetFormula** to a nonzero value the first time running this function or whenever the Formula changes. It should not be set to a nonzero value every time because it is not efficient doing that.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex): Integer index value of the bar to evaluate the Formula on.
* **ParseAndSetFormula**: Integer variable that when set to any value other than 0, forces an internal format and storage of the **Formula** parameter prior to evaluation.
* **Formula**: The formula to evaluate as a text string. This only needs to be provided when **ParseAndSetFormula** is a nonzero value. Otherwise, it can be an empty string just by passing "". The formula needs to follow the format documented in the [Alert Condition Formula Format](StudyChartAlertsAndScanning.md#alertconditionformulaformat) section.

### sc.EvaluateGivenAlertConditionFormulaAsDouble()

[Link](#scevaluategivenalertconditionformulaasdouble) - [Top](#top)

**Type**: Function

double **EvaluateGivenAlertConditionFormulaAsDouble**(int **BarIndex**, int **ParseAndSetFormula**, const SCString& **Formula**);

The **sc.EvaluateGivenAlertConditionFormulaAsDouble()** function evaluates the given **Formula** parameter, and returns the calculated value for the formula at the specified **BarIndex**.

When the **ParseAndSetFormula** parameter is set to a nonzero value, then the **Formula** is internally formatted and stored prior to calculating the formula at the **BarIndex**. It is necessary to set **ParseAndSetFormula** to a nonzero value the first time running this function or whenever the Formula changes. It should not be set to a nonzero value every time because it is not efficient doing that.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex): Integer index value of the bar to evaluate the Formula on.
* **ParseAndSetFormula**: Integer variable that when set to any value other than 0, forces an internal format and storage of the **Formula** parameter prior to evaluation.
* **Formula**: The formula to evaluate as a text string. This only needs to be provided when **ParseAndSetFormula** is a nonzero value. Otherwise, it can be an empty string just by passing "". For information about the formula format, refer to [Spreadsheet Formula](StudiesReference.md).

### sc.ExponentialMovAvg()

[Link](#scexponentialmovavg) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **ExponentialMovAvg**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **ExponentialMovAvg**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.ExponentialMovAvg()** function calculates the exponential moving average.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.ExponentialMovAvg(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20);

float ExponentialMovAvg = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.ExponentialRegressionIndicator()

[Link](#scexponentialregressionindicator) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **ExponentialRegressionIndicator**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **ExponentialRegressionIndicator**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.ExponentialRegressionIndicator()** function calculates the Exponential Regression Indicator study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.ExponentialRegressionIndicator(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 10);

float ExponentialRegressionIndicator = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.FillSubgraphElementsWithLinearValuesBetweenBeginEndValues

[Link](#scfillsubgraphelementswithlinearvaluesbetweenbeginendvalues) - [Top](#top)

**Type**: Function

void **FillSubgraphElementsWithLinearValuesBetweenBeginEndValues**(int **SubgraphIndex**, int **BeginIndex**, int **EndIndex**);

The **sc.FillSubgraphElementsWithLinearValuesBetweenBeginEndValues()** function fills the study Subgraph array specified by the **SubgraphIndex** parameter from the element after **BeginIndex** to the element just before the **EndIndex** parameters, with the linear values in between the values specified by those index parameters. **SubgraphIndex** is 0 based, therefore 0 is the first Subgraph.

For example, if the value at BeginIndex is 2.0 and the index is 10, and the value at EndIndex is 2.4 and the index is 14, then at indices 11, 12, and 13 the set values will be 2.1, 2.2, and 2.3 respectively.

#### Parameters

* [SubgraphIndex](#commonfunctionparameterdescriptionssubgraphindex)
* **BeginIndex**: The bar index from which the interpolation will begin.
* **EndIndex**: The bar index at which the interpolation will end.

### sc.FlattenAndCancelAllOrders()

[Link](#scflattenandcancelallorders) - [Top](#top)

Refer to the [sc.FlattenAndCancelAllOrders()](ACSILTrading.md#flattenandcancelallorders) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.FlattenAndCancelAllOrdersForSymbolAndNonSimTradeAccount()

[Link](#scflattenandcancelallordersforsymbolandnonsimtradeaccount) - [Top](#top)

Refer to the [sc.FlattenAndCancelAllOrdersForSymbolAndNonSimAccount()](ACSILTrading.md#flattenandcancelallordersforsymbolandnonsimtradeaccount) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.FlattenPosition()

[Link](#scflattenposition) - [Top](#top)

Refer to the [sc.FlattenPosition()](ACSILTrading.md#flattenposition) section on the  [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.FlattenPositionsAndCancelOrdersForTradeAccount()

[Link](#scflattenpositionsandcancelordersfortradeaccount) - [Top](#top)

Refer to the [sc.FlattenPositionsAndCancelOrdersForTradeAccount()](ACSILTrading.md#scflattenpositionsandcancelordersfortradeaccount) section on the  [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.FormatDateTime()

[Link](#scformatdatetime) - [Top](#top)

**Type**: Function

SCString **FormatDateTime**(const SCDateTime& **DateTime**);

The **sc.FormatDateTime()** function returns a formatted text string for the given **DateTime** parameter. The returned text string will contain both the date and the time.

#### Example

```cpp

SCString Message;

Message.Format("Current Bar Date-Time: %s", sc.FormatDateTime(sc.BaseDateTimeIn[sc.Index]).GetChars());

sc.AddMessageToLog(Message, 0);
            
```

### sc.FormatDateTimeMS()

[Link](#scformatdatetimems) - [Top](#top)

**Type**: Function

SCString **FormatDateTimeMS**(const SCDateTime& **DateTimeMS**);

The **sc.FormatDateTimeMS()** function returns a formatted text string for the given **DateTimeMS** parameter. The returned text string will contain both the date and the time, including milliseconds.

#### Example

```cpp

SCString Message;

Message.Format("Current System Date-Time: %s", sc.FormatDateTimeMS(sc.CurrentSystemDateTimeMS).GetChars());

sc.AddMessageToLog(Message, 0);
            
```

### sc.FormatGraphValue()

[Link](#scformatgraphvalue) - [Top](#top)

**Type**: Function

SCString **FormatGraphValue**(double **Value**, int **ValueFormat**);

**sc.FormatGraphValue()** formats a numeric value as text based on the specified value format. The text is returned as an SCString.

#### Parameters

* **Value**: The Integer or floating-point value to format.
* **ValueFormat**: The formating code. Can be **sc.BaseGraphValueFormat**. This number sets the number of decimal places to display. If ValueFormat is greater than 100, then it will be a fractional format where the denominator is specified as **Denominator + 100**. For example, 132 will format the value in a fractional format using a denominator of 1/32.

#### Example

```cpp

SCString CurHigh = sc.FormatGraphValue(sc.BaseData[SC_HIGH][CurrentVisibleIndex], sc.BaseGraphValueFormat);

s_UseTool Tool;
Tool.Text = CurHigh;
            
```

### sc.FormatString()

[Link](#scformatstring) - [Top](#top)

**Type**: Function

SCString& **FormatString**(SCString& **Out**, const char\* **Format**, [Variable list of parameters]);

The **sc.FormatString()** function creates a text string using the specified **Format**. For more information, refer to the [Setting A Name To A Formatted String](ACSILProgrammingConcepts.md#formattedtextstring) section. **Out** is the SCString you need to provide where the text output is copied to.

#### Example

```cpp

SCString Output;

sc.FormatString(Output, "The result is: %f", sc.Subgraph[0].Data[sc.Index]);
            
```

### sc.FormattedEvaluate()

[Link](#scformattedevaluate) - [Top](#top)

**Type**: Function

int **FormattedEvaluate**(float **Value1**, int **Value1Format**, OperatorEnum **Operator**, float **Value2**, int **Value2Format**, float **PrevValue1** = 0.0f, float **PrevValue2** = 0.0f);

**sc.FormattedEvaluate()** evaluates the relationship between 2 floating-point numbers using the specified  **Operator** and Value Formats (**Value1Format, Value2Format**). The evaluation is performed as follows: **Value1 Operator Value2**.

The more precise of the two Value Formats is used for the comparison. Once this is determined, half of the more precise Value Format is calculated. If the Value Format is 2 which is equivalent to .01, then the tolerance is .005. In this particular example, two values would be considered equal if the difference between them is less than .005.

Another example: Assuming the most precise Value Format is .01, Value1 will be considered less than Value2 if the difference between the two of them is less than -.005.

The function returns 1 if the evaluation is TRUE, and 0 if it is FALSE.

The reason why this function needs to be used when performing floating-point number comparisons is due to what is known as floating point error. Refer to **Accuracy Problems** in the [Floating Point Wikipedia article](https://en.wikipedia.org/wiki/Floating_point). For example, the number .01 may internally be represented in a single precision floating-point variable as .0099998, therefore making comparisons using the built-in operators of the C++ language not accurate.

#### Parameters

* **Value1**: Any number to use on the left side of the  **Operator**.
* **Value1Format**: The formating code. Can be set to **sc.BaseGraphValueFormat** or **sc.GetValueFormat()**. For more information, refer to [sc.ValueFormat](ACSIL_Members_Variables_And_Arrays.md#scvalueformat).
* **Operator**:  
  + NOT\_EQUAL\_OPERATOR
  + LESS\_EQUAL\_OPERATOR
  + GREATER\_EQUAL\_OPERATOR
  + CROSS\_EQUAL\_OPERATOR
  + CROSS\_OPERATOR
  + EQUAL\_OPERATOR
  + LESS\_OPERATOR
  + GREATER\_OPERATOR
* **Value2**: Any number to use on the right side of the  **Operator**.
* **Value2Format**: The formating code. Can be set to **sc.BaseGraphValueFormat** or **sc.GetValueFormat()**. For more information, refer to [sc.ValueFormat](ACSIL_Members_Variables_And_Arrays.md#scvalueformat).
* **PrevValue1**: This only needs to be specified when using the **CROSS\_OPERATOR** operator. In this case, provide the prior value (usually from a line) to use on the left side of the operator in the comparison.
* **PrevValue2**: This only needs to be specified when using the **CROSS\_OPERATOR** operator. In this case, provide the prior value (usually from a line) to use on the right side of the operator in the comparison.

#### Example

```cpp

int Return = sc.FormattedEvaluate(CurrentClose, sc.BaseGraphValueFormat, LESS_OPERATOR, PriorLow, sc.BaseGraphValueFormat);
            
```

### sc.FormattedEvaluateUsingDoubles()

[Link](#scformattedevaluateusingdoubles) - [Top](#top)

**Type**: Function

int **FormattedEvaluateUsingDoubles**(double **Value1**, int **Value1Format**, OperatorEnum **Operator**, double **Value2**, int **Value2Format**, double **PrevValue1** = 0.0f, double **PrevValue2** = 0.0f);

**sc.FormattedEvaluateUsingDoubles()** evaluates the relationship between 2 double precision floating-point numbers using the specified  **Operator** and Value Formats (**Value1Format, Value2Format**).

This function is identical to [sc.FormattedEvaluate()](#scformattedevaluate) except that it uses double precision floating-point numbers instead of single precision floating-point numbers.

For additional details, refer to [sc.FormattedEvaluate()](#scformattedevaluate).

### sc.FormatVolumeValue()

[Link](#scformatvolumevalue) - [Top](#top)

**Type**: Function

SCString **sc.FormatVolumeValue**(int64\_t **Volume**, int **VolumeValueFormat**, int **UseLargeNumberSuffix**);

The **sc.FormatVolumeValue()** function formats an integer volume value into a text string. The result is returned as a [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings) type.

#### Parameters

* **Volume**: The volume value as an integer.
* **VolumeValueFormat**: The Volume Value Format. Normally pass the sc.VolumeValueFormat variable as the parameter.
* **UseLargeNumberSuffix**: 1 to use a large number suffix or 0 not to. For example, in the case of volume values from 1000000 to 9999999, the M suffix will be used when this is set to 1.

### sc.FourBarSymmetricalFIRFilter()

[Link](#scfourbarsymmetricalfirfilter) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **FourBarSymmetricalFIRFilter**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**);

SCFloatArrayRef **FourBarSymmetricalFIRFilter**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**); [Auto-looping only](#noindexparam).

The **sc.FourBarSymmetricalFIRFilter()** function calculates a four-bar smoothing of data and is frequently used in the studies written by John Ehlers.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.FourBarSymmetricalFIRFilter(sc.BaseDataIn[SC_LAST], sc.Subgraph[0]);

float FourBarSymmetricalFIRFilter = sc.Subgraph[0][sc.Index]; //Access the function value at the current index
            
```

### sc.FreeMemory()

[Link](#scfreememory) - [Top](#top)

**Type**: Function

void **FreeMemory** (void\* **Pointer**);

The  **sc.FreeMemory** function releases the memory allocated with the [sc.AllocateMemory](#scallocatememory) function.

#### Parameters

* **Pointer**: The pointer to the memory block to release.

### sc.GetACSDrawingByIndex()

[Link](#scgetacsdrawingbyindex) - [Top](#top)

**Type**: Function

For complete documentation for the **sc.GetACSDrawingByIndex** function, refer to [sc.GetACSDrawingByIndex()](ACSILDrawingTools.md#scgetacsdrawingbyindex).

### sc.GetACSDrawingByLineNumber()

[Link](#scgetacsdrawingbylinenumber) - [Top](#top)

Refer to the [sc.GetACSDrawingByLineNumber()](ACSILDrawingTools.md#scgetacsdrawingbylinenumber) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.GetACSDrawingsCount()

[Link](#scgetacsdrawingscount) - [Top](#top)

Refer to the [sc.GetACSDrawingsCount()](ACSILDrawingTools.md#scgetacsdrawingscount) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.GetAskMarketDepthEntryAtLevel

[Link](#scgetaskmarketdepthentryatlevel) - [Top](#top)

**Type**: Function

int **GetAskMarketDepthEntryAtLevel**(s\_MarketDepthEntry& **DepthEntry**, int **LevelIndex**);

**sc.GetAskMarketDepthEntryAtLevel** returns in the **DepthEntry** structure of type **s\_MarketDepthEntry**, the ask side market depth data for the level specified by the **LevelIndex** variable for the symbol of the chart.

The function returns 1 if the function call was successful, otherwise 0.

To receive Market Depth data it is also necessary to set [sc.UsesMarketDepthData](ACSIL_Members_Variables_And_Arrays.md#scusesmarketdepthdata) to 1 in the study function. This normally should be placed in the **sc.SetDefaults** code block.

For an example to access market depth data, refer to the **scsf\_DepthOfMarketData()** function in the **/ACS\_Source/studies.cpp** file in the folder where Sierra Chart is installed to.

The s\_MarketDepthEntry structure contains a Price member and an AdjustedPrice member. Normally these are the same price. However, when a Real-time Price Multiplier is set to a value other than 1.0 in a chart, then Price will contain the original unadjusted price and AdjustedPrice will contain the Price multiplied by the Real-time Price Multiplier.

#### s\_MarketDepthEntry

```cpp

struct s_MarketDepthEntry
{
	float Price;
	t_MarketDataQuantity Quantity;
	uint32_t NumOrders;
    float AdjustedPrice;
}

            
```

### sc.GetAskMarketDepthEntryAtLevelForSymbol

[Link](#scgetaskmarketdepthentryatlevelforsymbol) - [Top](#top)

**Type**: Function

int **GetAskMarketDepthEntryAtLevelForSymbol**(const SCString& **Symbol**, s\_MarketDepthEntry& **r\_DepthEntry**, int **LevelIndex**);

**sc.GetAskMarketDepthEntryAtLevelForSymbol** returns in the **DepthEntry** structure of type **s\_MarketDepthEntry**, the ask side market depth data for the level specified by the **LevelIndex** variable for the specified **Symbol**.

The function returns 1 if the function call was successful, otherwise 0.

To receive Market Depth data it is also necessary to set [sc.UsesMarketDepthData](ACSIL_Members_Variables_And_Arrays.md#scusesmarketdepthdata) to 1 in the study function. This normally should be placed in the **sc.SetDefaults** code block.

For an example to access market depth data, refer to the **scsf\_DepthOfMarketData()** function in the **/ACS\_Source/studies.cpp** file in the folder where Sierra Chart is installed to.

#### s\_MarketDepthEntry

```cpp

                struct s_MarketDepthEntry
                {
                    float Price;
                    t_MarketDataQuantity Quantity;
                    uint32_t NumOrders;
                    float AdjustedPrice; 
                }
            
```

### sc.GetAskMarketDepthNumberOfLevels

[Link](#scgetaskmarketdepthnumberoflevels) - [Top](#top)

**Type**: Function

int **GetAskMarketDepthNumberOfLevels**();

The **sc.GetAskMarketDepthNumberOfLevels** function returns the number of available market depth levels on the Ask side for the symbol of the chart.

There are settings which affect the number of market depth levels. Refer to [Not Receiving the Full Number of Market Depth Levels](FileMenu.md#notreceivingthefullnumberofmarketdepthlevels).

### sc.GetAskMarketDepthNumberOfLevelsForSymbol

[Link](#scgetaskmarketdepthnumberoflevelsforsymbol) - [Top](#top)

**Type**: Function

int **GetAskMarketDepthNumberOfLevelsForSymbol**(const SCString& **Symbol**);

The **sc.GetAskMarketDepthNumberOfLevelsForSymbol** function returns the number of available market depth levels on the Ask side for the specified symbol.

There are settings which affect the number of market depth levels. Refer to [Not Receiving the Full Number of Market Depth Levels](FileMenu.md#notreceivingthefullnumberofmarketdepthlevels).

#### Parameters

* [Symbol](#commonfunctionparameterdescriptionssymbol): The symbol to get the number of market depth levels for.

#### Example

```cpp
 
int NumberOfLevels = GetAskMarketDepthNumberOfLevelsForSymbol(sc.Symbol);
            
```

### sc.GetAskMarketDepthStackPullSum()

### sc.GetBidMarketDepthStackPullSum()

[Link](#scgetaskmarketdepthstackpullsum) - [Top](#top)

**Type**: Function

double **GetAskMarketDepthStackPullSum**();

double **GetBidMarketDepthStackPullSum**();

The **sc.GetAskMarketDepthStackPullSum** and **sc.GetBidMarketDepthStackPullSum** functions return the current total sum of the [market depth data stacking or pulling values](GlobalTradeSettings.md#columndescriptionbidmarketdepthpullingstacking) for either the Ask or Bid side respectively.

For these functions to return a value, it is necessary that **Trade >> Trading Chart DOM On / Show Market Data Columns** is enabled for one of the charts for the Symbol. And one of the **Pulling/Stacking** columns needs to be added. Refer to [Customize Trade/Chart DOM Columns and Descriptions](GlobalTradeSettings.md#chartdomcolumndescriptions) for instructions.

#### Example

```cpp
 
// Get the current stacking and pulling sum on the Ask side
int MarketDepthStackPullSum = sc.GetAskMarketDepthStackPullSum();
            
```

### sc.GetAskMarketDepthStackPullValueAtPrice()

### sc.GetBidMarketDepthStackPullValueAtPrice()

[Link](#scgetaskmarketdepthstackpullvalueatprice) - [Top](#top)

**Type**: Function

int **GetAskMarketDepthStackPullValueAtPrice**(float **Price**);

int **GetBidMarketDepthStackPullValueAtPrice**(float **Price**);

The **sc.GetAskMarketDepthStackPullValueAtPrice** and **sc.GetBidMarketDepthStackPullValueAtPrice** functions return the current [market depth data stacking or pulling value](GlobalTradeSettings.md#columndescriptionbidmarketdepthpullingstacking) for either the Ask or Bid side respectively, for the given **Price** parameter.

For these functions to return a value, it is necessary that **Trade >> Trading Chart DOM On / Show Market Data Columns** is enabled for one of the charts for the Symbol. And one of the **Pulling/Stacking** columns needs to be added. Refer to [Customize Trade/Chart DOM Columns and Descriptions](GlobalTradeSettings.md#chartdomcolumndescriptions) for instructions.

Also refer to [sc.GetAskMarketDepthStackPullSum()](#scgetaskmarketdepthstackpullsum) and [sc.GetBidMarketDepthStackPullSum()](#scgetbidmarketdepthstackpullsum).

#### Example

```cpp
 
// Get the current stacking and pulling value on the bid side for the current best bid price.            
int StackPullValue = sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid);
            
```

### sc.GetAskMarketLimitOrdersForPrice()

[Link](#scgetaskmarketlimitordersforprice) - [Top](#top)

**Type**: Function

int **GetAskMarketLimitOrdersForPrice**(const int **PriceInTicks**, const int **ArraySize**, n\_ACSIL::s\_MarketOrderData\* **p\_MarketOrderDataArray**);

The **sc.GetAskMarketLimitOrdersForPrice** function is used to get the order ID and order quantity for working limit orders from the market data feed at the specified price level. This data is called [Market by Order](MarketByOrder.md) data. This includes all the working limit orders as provided by the market data feed.

#### Parameters

* **PriceInTicks**: This is the price to get the working limit orders for. This is an integer value. You need to take the floating-point actual price and divide by **sc.TickSize** and round to the nearest integer.
* **ArraySize**: This is the size of the p\_MarketOrderDataArray array as a number of elements, that you provide the function.
* **p\_MarketOrderDataArray**: This is a pointer to the array of type n\_ACSIL::s\_MarketOrderData of the size specified by **ArraySize** that is filled in with the working limit orders data upon return of the function.

#### Example

For an example to use this function, refer to the **scsf\_MarketLimitOrdersForPriceExample** study function in the /ACS\_Source/Studies2.cpp file in the Sierra Chart installation folder.

### sc.GetAttachedOrderIDsForParentOrder()

[Link](#scgetattachedorderidsforparentorder) - [Top](#top)

**Type**: Function

void **GetAttachedOrderIDsForParentOrder**(int **ParentInternalOrderID**, int& **TargetInternalOrderID**, int& **StopInternalOrderID**);

The **sc.GetAttachedOrderIDsForParentOrder** function is used to get the Internal Order IDs for a Target and Stop order for a given Parent Internal Order ID.

The **ParentInternalOrderID** parameter specifies the Parent Internal Order ID. The **TargetInternalOrderID**, **StopInternalOrderID** parameters receive the Target and Stop Internal Order IDs respectively.

For information about Internal Order IDs, refer to the [ACSIL Trading](ACSILTrading.md) page. These Internal Order IDs can be obtained when submitting an order.

#### Example

```cpp

int TargetInternalOrderID = -1;
int StopInternalOrderID = -1;

//This needs to be set to the parent internal order ID search for. Since we do not know what that is in this code example, it is set to zero here.
int ParentInternalOrderID = 0;

sc.GetAttachedOrderIDsForParentOrder(ParentInternalOrderID, TargetInternalOrderID, StopInternalOrderID)
            
```

### sc.GetAttachedOrders()

[Link](#scgetattachedorders) - [Top](#top)

**Type**: Function

int32\_t **GetAttachedOrders**(s\_SCNewOrder& **r\_AttachedOrdersConfiguration**);

Refer to the [sc.GetAttachedOrders()](ACSILTrading.md#scgetattachedorders) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetBarHasClosedStatus()

[Link](#scgetbarhasclosedstatus) - [Top](#top)

**Type**: Function

int **GetBarHasClosedStatus**(int **BarIndex**);

int **GetBarHasClosedStatus**(); [Auto-looping only](#noindexparam).

The **sc.GetBarHasClosedStatus** function is used to determine if the data for a particular bar in the **sc.BaseData[][]** arrays at the specified **BarIndex**  parameter (required for manual looping), has completed and will no longer be updated during real-time or replay updating.

This is useful when you only want to perform calculations on a fully completed bar. It is equivalent to "Signal Only on Bar Close" with the Spreadsheet studies.

This function has several return values described below.

Refer to the **scsf\_GetBarHasClosedStatusExample()** function in the **/ACS\_Source/studies.cpp** file in the Sierra Chart installation folder for example code to work with this function.

This function can be used with [manual or automatic looping](ACS_ArraysAndLooping.md#arrayindexing). It can be given an index of any bar. **sc.BaseData[][]** contains the underlying bar data for the chart. In this function call: **sc.GetBarHasClosedStatus(sc.Index)**, sc.Index is passed through the **BarIndex** parameter and this will refer to the bar data at **sc.BaseData[][sc.Index]**.

The very last bar in the chart is never considered a closed bar until there is a new bar added to the chart. It is not possible to know otherwise because of the following reasons: The chart bars are based upon a variable timeframe like **Number of Trades** or **Volume** and the ending can never be known until there is a new bar, or because there is not a trade at the very final second of a fixed time bar.

In the case of chart bars which are based upon a fixed amount of time, the only way to know when the end of that chart bar has occurred, is to consider the time length of the bar through [sc.SecondsPerBar](ACSIL_Members_Variables_And_Arrays.md#scsecondsperbar). Use [sc.UpdateAlways](ACSIL_Members_Variables_And_Arrays.md#scupdatealways), to have the study function periodically and continuously called. And use the current Date-Time through [sc.GetCurrentDateTime()](#scgetcurrentdatetime) to know when the bar is considered closed.

**Return Values:**

* **BHCS\_BAR\_HAS\_CLOSED**: Element at BarIndex has closed. This will always be returned for any bar in the chart other than the last bar in the chart.
* **BHCS\_BAR\_HAS\_NOT\_CLOSED**: Element at BarIndex has not closed. This will always be returned for the last bar in the chart.
* **BHCS\_SET\_DEFAULTS**: Configuration and defaults are being set. Allow the sc.SetDefaults code block to run. Bar has closed status is not available.

#### Example

```cpp

if(sc.GetBarHasClosedStatus(Index)==BHCS_BAR_HAS_NOT_CLOSED)
{

    return;//do not do any processing if the bar at  the current index has not closed
}
            
```

### sc.GetBarPeriodParameters()

[Link](#scgetbarperiodparameters) - [Top](#top)

**Type**: Function

void **GetBarPeriodParameters**(n\_ACSIL::s\_BarPeriod& **r\_BarPeriod**)

The **sc.GetBarPeriodParameters()** function copies the chart bar period parameters into the structure of type **n\_ACSIL::s\_BarPeriod** which is passed to the function as **r\_BarPeriod**. Refer to the example below.

When using [sc.SetBarPeriodParameter()](#scsetbarperiodparameters) to change the period for a chart bar, and then making a call to **sc.GetBarPeriodParameters()** immediately after, but during the processing in the study function, it will then return these new set parameters.

The **n\_ACSIL::s\_BarPeriod** structure members are the following:

* **s\_BarPeriod::ChartDataType**: Can be one of the following:
  + DAILY\_DATA = 1
  + INTRADAY\_DATA = 2.
* **s\_BarPeriod::HistoricalChartBarPeriodType**: Can be one of the following:
  + HISTORICAL\_CHART\_PERIOD\_DAYS = 1
  + HISTORICAL\_CHART\_PERIOD\_WEEKLY = 2
  + HISTORICAL\_CHART\_PERIOD\_MONTHLY = 3
  + HISTORICAL\_CHART\_PERIOD\_QUARTERLY = 4
  + HISTORICAL\_CHART\_PERIOD\_YEARLY = 5
* **s\_BarPeriod::HistoricalChartDaysPerBar**: When **s\_BarPeriod::HistoricalChartBarPeriodType** is set to HISTORICAL\_CHART\_PERIOD\_DAYS, then this specifies the number of days per historical chart bar.
* **s\_BarPeriod::IntradayChartBarPeriodType**: The type of bar period that is being used in the case of an Intraday chart. To determine the chart data type, use **s\_BarPeriod::ChartDataType**. For example, this would be set to the enumeration value IBPT\_DAYS\_MINS\_SECS if the Intraday Chart **Bar Period Type** is set to **Days-Minutes-Seconds**. Can be any of the following constants:
  + IBPT\_DAYS\_MINS\_SECS = 0: **s\_BarPeriod::IntradayChartBarPeriodParameter1** is the number of seconds in one bar in an Intraday chart. This is set by the **Days-Mins-Secs** setting in the **Chart >> Chart Settings** window for the chart. For example, for a 1 Minute chart this will be set to 60. For a 30 Minute chart this will be set to 1800.
  + IBPT\_VOLUME\_PER\_BAR = 1
  + IBPT\_NUM\_TRADES\_PER\_BAR = 2
  + IBPT\_RANGE\_IN\_TICKS\_STANDARD = 3
  + IBPT\_RANGE\_IN\_TICKS\_NEWBAR\_ON\_RANGEMET = 4
  + IBPT\_RANGE\_IN\_TICKS\_TRUE = 5
  + IBPT\_RANGE\_IN\_TICKS\_FILL\_GAPS = 6
  + IBPT\_REVERSAL\_IN\_TICKS = 7
  + IBPT\_RENKO\_IN\_TICKS = 8
  + IBPT\_DELTA\_VOLUME\_PER\_BAR = 9
  + IBPT\_FLEX\_RENKO\_IN\_TICKS = 10
  + IBPT\_RANGE\_IN\_TICKS\_OPEN\_EQUAL\_CLOSE = 11
  + IBPT\_PRICE\_CHANGES\_PER\_BAR = 12
  + IBPT\_MONTHS\_PER\_BAR = 13
  + IBPT\_POINT\_AND\_FIGURE = 14
  + IBPT\_FLEX\_RENKO\_IN\_TICKS\_INVERSE\_SETTINGS = 15
  + IBPT\_ALIGNED\_RENKO = 16
  + IBPT\_RANGE\_IN\_TICKS\_NEW\_BAR\_ON\_RANGE\_MET\_OPEN\_EQUALS\_PRIOR\_CLOSE = 17
  + IBPT\_ACSIL\_CUSTOM = 18: This is used when the chart contains an advanced custom study that creates custom chart bars. The study name is contained within s\_BarPeriod::ACSILCustomChartStudyName. For complete documentation for building custom chart bars, refer to [ACSIL Interface - Custom Chart Bars](ACSIL_CustomChartBars.md).
  + IBPT\_HISTORICAL\_DAILY\_DATA\_DAYS\_PER\_BAR = 10000
* **s\_BarPeriod::IntradayChartBarPeriodParameter1**: The first parameter for the bar period that is being used. In the case of IntradayChartBarPeriodType being set to IBPT\_DAYS\_MINS\_SECS, this will be set to the number of seconds. In the case of IntradayChartBarPeriodType being set IBPT\_FLEX\_RENKO\_IN\_TICKS, this would be the **Bar Size** value in ticks.
* **s\_BarPeriod::IntradayChartBarPeriodParameter2**: The second parameter for the bar period that is being used. For example, this would be the **Trend Offset** value when using **IBPT\_FLEX\_RENKO\_IN\_TICKS** for the Intraday Chart Bar Period Type. If this parameter is unused for the Intraday Chart Bar Period Type, then the value is set to **0**.
* **s\_BarPeriod::IntradayChartBarPeriodParameter3**: The third parameter for the bar period that is being used. For example, this would be the **Reversal Offset** value when using **IBPT\_FLEX\_RENKO\_IN\_TICKS** for the Intraday Chart Bar Period Type. If this parameter is unused for the Intraday Chart Bar Period Type, then the value is set to **0**.
* **s\_BarPeriod::IntradayChartBarPeriodParameter4**: The fourth parameter for the bar period that is being used. For example, this would be the **Renko New Bar Mode** setting when using any of the  **Renko** Intraday Chart Bar Period Types. If this parameter is unused for the Intraday Chart Bar Period Type, then the value is set to **0**. The values for **Renko New Bar Mode** are listed below.
  + NEW\_TREND\_BAR\_WHEN\_EXCEEDED\_NEW\_REVERSAL\_BAR\_WHEN\_REVERSAL\_AMOUNT\_MET = 0
  + NEW\_TREND\_BAR\_WHEN\_EXCEEDED\_NEW\_BAR\_WHEN\_OPEN\_CROSSED = 1
  + NEW\_TREND\_BAR\_WHEN\_EXCEEDED\_NEW\_REVERSAL\_BAR\_WHEN\_REVERSAL\_AMOUNT\_MET\_PLUS\_1\_TICK = 2
  + NEW\_TREND\_BAR\_WHEN\_RANGE\_MET\_NEW\_REVERSAL\_BAR\_WHEN\_REVERSAL\_AMOUNT\_MET = 3
  + NEW\_TREND\_BAR\_WHEN\_RANGE\_MET\_NEW\_BAR\_WHEN\_OPEN\_CROSSED = 4
  + NEW\_TREND\_BAR\_WHEN\_RANGE\_MET\_NEW\_REVERSAL\_BAR\_WHEN\_REVERSAL\_AMOUNT\_MET\_PLUS\_1\_TICK = 5
  + NEW\_TREND\_BAR\_AFTER\_RANGE\_MET\_NEW\_REVERSAL\_BAR\_WHEN\_REVERSAL\_AMOUNT\_MET = 6
  + NEW\_TREND\_BAR\_AFTER\_RANGE\_MET\_NEW\_BAR\_WHEN\_OPEN\_CROSSED = 7
  + NEW\_TREND\_BAR\_AFTER\_RANGE\_MET\_NEW\_REVERSAL\_BAR\_WHEN\_REVERSAL\_AMOUNT\_MET\_PLUS\_1\_TICK = 8
  + NEW\_TREND\_BAR\_AFTER\_RANGE\_MET\_ALLOW\_CHANGE\_OF\_DIRECTION\_OF\_CURRENT\_BAR = 9
  + NEW\_TREND\_BAR\_AFTER\_RANGE\_MET\_NEW\_REVERSAL\_BAR\_WHEN\_REVERSAL\_AMOUNT\_MET\_FIRST\_TREND\_BAR\_SAME\_LENGTH\_REVERSAL = 10
  + NEW\_TREND\_BAR\_WHEN\_EXCEEDED\_NEW\_REVERSAL\_BAR\_WHEN\_REVERSAL\_AMOUNT\_MET\_PLUS\_1\_TICK\_FIRST\_TREND\_BAR\_SAME\_LENGTH\_REVERSAL = 11
* **s\_BarPeriod::ACSILCustomChartStudyName**: When the chart contains an advanced custom study that creates custom chart bars, this contains the name as a texturing of the custom study which creates those custom chart bars. The name is set through [sc.GraphName](ACSIL_Members_Variables_And_Arrays.md#scgraphname).
    
     
  For complete documentation for building custom chart bars, refer to [ACSIL Interface - Custom Chart Bars](ACSIL_CustomChartBars.md).

#### Example

```cpp

n_ACSIL::s_BarPeriod BarPeriod;
sc.GetBarPeriodParameters(BarPeriod);
if (BarPeriod.ChartDataType == INTRADAY_DATA && BarPeriod.IntradayChartBarPeriodType == IBPT_DAYS_MINS_SECS)
{
    int SecondsPerBar = BarPeriod.IntradayChartBarPeriodParameter1;
}        
            
```

### sc.GetBarPeriodParametersForChart()

[Link](#scgetbarperiodparametersforchart) - [Top](#top)

**Type**: Function

void **GetBarPeriodParametersForChart**(int **ChartNumber**, n\_ACSIL::s\_BarPeriod& **r\_BarPeriod**);

The **sc.GetBarPeriodParametersForChart()** fills out the r\_BarPeriod structure with the bar period parameters for the specified ChartNumber.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **r\_BarPeriod**: An s\_BarPeriod structure. Refer the information in the section for the [sc.GetBarPeriodParameters()](#scgetbarperiodparameters) function for the specifics of this structure.

### sc.GetBarsSinceLastTradeOrderEntry()

[Link](#scgetbarssincelasttradeorderentry) - [Top](#top)

**Type**: Function

int **GetBarsSinceLastTradeOrderEntry**()

This function returns the number of chart bars counting from the end of the chart since the Date-Time of the last entry trade order for the Symbol and Trade Account of the chart the study is applied to, whether the order was from ACSIL or not.

If there has been no entry order or the entry was on the last bar of the chart, then this function returns 0.

### sc.GetBarsSinceLastTradeOrderExit()

[Link](#scgetbarssincelasttradeorderexit) - [Top](#top)

**Type**: Function

int **GetBarsSinceLastTradeOrderExit**()

This function returns the number of chart bars counting from the end of the chart since the Date-Time of the last exit trade order for the Symbol and Trade Account of the chart the study is applied to, whether the order was from ACSIL or not.

If there has been no exit order or the exit was on the last bar of the chart, then this function returns 0.

### sc.GetBasicSymbolData()

[Link](#scgetbasicsymboldata) - [Top](#top)

**Type**: Function

void **GetBasicSymbolData**(const char\* **Symbol**, s\_SCBasicSymbolData& **BasicSymbolData**, bool **Subscribe**)

The **sc.GetBasicSymbolData**  will fill out the  **BasicSymbolData** data structure with all of the Current Quote data for the specified  **Symbol**. This data is only considered valid when connected to the data feed. The Current Quote data is the data that is found in **Window >> Current Quote Window**. Market Depth data is also included in the data structure.

Refer to declaration of s\_SCBasicSymbolData in the /ACS\_Source/scsymboldata.h file in the folder Sierra Chart is installed to for all of the structure members. The data that is returned when calling this function is the most current available data.

The **Subscribe** parameter will subscribe to market data for the symbol when connected to the data feed. Subscribing to a symbol, does not mean that the study function will be called for all updates on the symbol. The study function will only be called based upon the updates of the symbol of the chart the study instance is on.

As an example, you could have a list of 10 symbols to request data for by calling **sc.GetBasicSymbolData()** for each symbol. After each call, examine the returned data and do any required calculations. So in this scenario, you can form an index by adding all of the last price values together and dividing by 10, and placing the results in an **sc.Subgraph[].Data[]** array.

#### Parameters

* [Symbol](#commonfunctionparameterdescriptionssymbol): The symbol to get the Symbol Data for. For information about working with strings, refer to  [Working with Strings](ACSILProgrammingConcepts.md#workingwithtextstrings).
* **BasicSymbolData**: A reference to a data structure of type s\_SCBasicSymbolData
* **SubscribeToData**: Set this to 1 to subscribe to the standard real-time market data. Otherwise, set this to zero to not subscribe.
* **SubsribeToMarketDepth**: Set this to 1 to subscribe to the real-time market depth data. This parameter is only supported by the [sc.GetBasicSymbolDataWithDepthSupport](#scgetbasicsymboldatawithdepthsupport) function. Otherwise, set this to zero to not subscribe.

#### Example

```cpp

// Get the daily high price for another symbol. The first time this  
// function is called after connecting to the data feed, the symbol data 
// will not be available initially. Once the data becomes available, when  
// this function is called after, the symbol data will be available.  If  
// this study is used on a chart for a symbol which does not frequently  
// update, then it will be a good idea to set sc.UpdateAlways = 1. 
const char * Symbol = "ABC"; 
s_SCBasicSymbolData BasicSymbolData; 
sc.GetBasicSymbolData(Symbol,BasicSymbolData, true); 
float DailyHigh = BasicSymbolData.High;

float LatestAsk = BasicSymbolData.Ask;// Also refer to the latest ask price
            
```

### sc.GetBasicSymbolDataWithDepthSupport

[Link](#scgetbasicsymboldatawithdepthsupport) - [Top](#top)

**Type**: Function

void **GetBasicSymbolDataWithDepthSupport**(const char\* **Symbol**, s\_SCBasicSymbolData& **BasicSymbolData**, int **SubscribeToData**, int **SubsribeToMarketDepth**);

The **sc.GetBasicSymbolDataWithDepthSupport()** function is identical to the [sc.GetBasicSymbolData](#scgetbasicsymboldata) function.

The difference is that it supports subscribing to market depth data.

### sc.GetBidMarketDepthEntryAtLevel

[Link](#scgetbidmarketdepthentryatlevel) - [Top](#top)

**Type**: Function

int **GetBidMarketDepthEntryAtLevel**(s\_MarketDepthEntry& **DepthEntry**, int **LevelIndex**);

**sc.GetBidMarketDepthEntryAtLevel** returns in the **DepthEntry** structure of type **s\_MarketDepthEntry**, the bid side market depth data for the level specified by the **LevelIndex** variable for the symbol of the chart.

The function returns 1 if the function call was successful, otherwise 0.

To receive Market Depth data it is also necessary to set [sc.UsesMarketDepthData](ACSIL_Members_Variables_And_Arrays.md#scusesmarketdepthdata) to 1 in the study function. This normally should be placed in the **sc.SetDefaults** code block.

For an example to access market depth data, refer to the **scsf\_DepthOfMarketData()** function in the **/ACS\_Source/studies.cpp** file in the folder where Sierra Chart is installed to.

The s\_MarketDepthEntry structure contains a Price member and an AdjustedPrice member. Normally these are the same price. However, when a Real-time Price Multiplier is set to a value other than 1.0 in a chart, then Price will contain the original unadjusted price and AdjustedPrice will contain the Price multiplied by the Real-time Price Multiplier.

#### s\_MarketDepthEntry

```cpp

struct s_MarketDepthEntry
{
	float Price;
	t_MarketDataQuantity Quantity;
	uint32_t NumOrders;
    float AdjustedPrice; 
}
            
```

### sc.GetBidMarketDepthEntryAtLevelForSymbol

[Link](#scgetbidmarketdepthentryatlevelforsymbol) - [Top](#top)

**Type**: Function

int **GetBidMarketDepthEntryAtLevelForSymbol**(const SCString& **Symbol**, s\_MarketDepthEntry& **r\_DepthEntry**, int **LevelIndex**);

**sc.GetBidMarketDepthEntryAtLevelForSymbol** returns in the **DepthEntry** structure of type **s\_MarketDepthEntry**, the bid side market depth data for the level specified by the **LevelIndex** variable for the specified **Symbol**.

The function returns 1 if the function call was successful, otherwise 0.

To receive Market Depth data it is also necessary to set [sc.UsesMarketDepthData](ACSIL_Members_Variables_And_Arrays.md#scusesmarketdepthdata) to 1 in the study function. This normally should be placed in the **sc.SetDefaults** code block.

For an example to access market depth data, refer to the **scsf\_DepthOfMarketData()** function in the **/ACS\_Source/studies.cpp** file in the folder where Sierra Chart is installed to.

#### s\_MarketDepthEntry

```cpp

                struct s_MarketDepthEntry
                {
                    float Price;
                    t_MarketDataQuantity Quantity;
                    uint32_t NumOrders;
                    float AdjustedPrice; 
                }
            
```

### sc.GetBidMarketDepthNumberOfLevels

[Link](#scgetbidmarketdepthnumberoflevels) - [Top](#top)

**Type**: Function

int **GetBidMarketDepthNumberOfLevels**();

The **sc.GetBidMarketDepthNumberOfLevels** function returns the number of available market depth levels on the Bid side for the symbol of the chart.

There are settings which affect the number of market depth levels. Refer to [Not Receiving the Full Number of Market Depth Levels](FileMenu.md#notreceivingthefullnumberofmarketdepthlevels).

### sc.GetBidMarketDepthNumberOfLevelsForSymbol

[Link](#scgetbidmarketdepthnumberoflevelsforsymbol) - [Top](#top)

**Type**: Function

int **GetBidMarketDepthNumberOfLevelsForSymbol**(const SCString& **Symbol**);

The **sc.GetBidMarketDepthNumberOfLevelsForSymbol** function returns the number of available market depth levels on the Bid side for the specified symbol.

There are settings which affect the number of market depth levels. Refer to [Not Receiving the Full Number of Market Depth Levels](FileMenu.md#notreceivingthefullnumberofmarketdepthlevels).

#### Parameters

* [Symbol](#commonfunctionparameterdescriptionssymbol): The symbol to get the number of market depth levels for.

#### Example

```cpp
 
int NumberOfLevels = GetBidMarketDepthNumberOfLevelsForSymbol(sc.Symbol);
            
```

### sc.GetBidMarketDepthStackPullSum()

[Link](#scgetbidmarketdepthstackpullsum) - [Top](#top)

**Type**: Function

double **GetBidMarketDepthStackPullSum**();

The **sc.GetBidMarketDepthStackPullSum()** returns the sum of the Bid side pulling/stacking values.

### sc.GetBidMarketLimitOrdersForPrice()

[Link](#scgetbidmarketlimitordersforprice) - [Top](#top)

**Type**: Function

int **GetBidMarketLimitOrdersForPrice**(const int **PriceInTicks**, const int **ArraySize**, n\_ACSIL::s\_MarketOrderData\* **p\_MarketOrderDataArray**);

The **sc.GetBidMarketLimitOrdersForPrice** function is used to get the order ID and order quantity for working limit orders from the market data feed at the specified price level. This data is called [Market by Order](MarketByOrder.md) data. This includes all the working limit orders as provided by the market data feed.

#### Parameters

* **PriceInTicks**: This is the price to get the working limit orders for. This is an integer value. You need to take the floating-point actual price and divide by **sc.TickSize** and round to the nearest integer.
* **ArraySize**: This is the size of the p\_MarketOrderDataArray array as a number of elements, that you provide the function.
* **p\_MarketOrderDataArray**: This is a pointer to the array of type n\_ACSIL::s\_MarketOrderData of the size specified by **ArraySize** that is filled in with the working limit orders data upon return of the function.

#### Example

For an example to use this function, refer to the **scsf\_MarketLimitOrdersForPriceExample** study function in the /ACS\_Source/Studies2.cpp file in the Sierra Chart installation folder.

### sc.GetBuiltInStudyName()

[Link](#scgetbuiltinstudyname) - [Top](#top)

**Type**: Function

int **GetBuiltInStudyName**(const int **InternalStudyIdentifier**, SCString& **r\_StudyName**);

The **sc.GetBuiltInStudyName** function returns the name of a built-in study, for the specified Internal Study Identifier.

Returns 1 on success or 0 on an error.

#### Parameters

* **InternalStudyIdentifier**: The internal study identifier. You can see the built-in study identifier for a study through the [Studies to Graph](ChartStudies.md#studiestograph) list. It is prefixed with: **S\_ID**.
* **r\_StudyName**: This string variable is set to the study name.

### sc.GetCalculationStartIndexForStudy()

[Link](#scgetcalculationstartindexforstudy) - [Top](#top)

**Type**: Function

int **GetCalculationStartIndexForStudy**();

The **sc.GetCalculationStartIndexForStudy()** function returns the starting index where a study function needs to begin its calculations at when it has a dependency on a study which has started a calculation at an earlier start index than normal. This function is for specialized purposes. It is not normally used.

For example, the Zig Zag study during a chart update may change the Zig Zag line at a chart bar index which is earlier than the chart bar being updated and any new bars added to the chart.

Any study function which uses this function, must use [Manual Looping](ACS_ArraysAndLooping.md#manuallooping).

For a related variable, also refer to [sc.EarliestUpdateSubgraphDataArrayIndex](ACSIL_Members_Variables_And_Arrays.md#scearliestupdatesubgraphdataarrayindex).

#### Example

The following code example is from the **Study Subgraph Add**  study.

```cpp

int CalculationStartIndex = sc.GetCalculationStartIndexForStudy();

for (int Index = CalculationStartIndex; Index < sc.ArraySize; Index++)
{

    float BasedOnStudySubgraphValue = sc.BaseData[InputData.GetInputDataIndex()][Index];

    if (AddToZeroValuesInBasedOnStudy.GetYesNo() == 0 && BasedOnStudySubgraphValue == 0.0)
    {
        Result[Index] = 0.0;
    }
    else
        Result[Index] = BasedOnStudySubgraphValue + AmountToAdd.GetFloat();
}

sc.EarliestUpdateSubgraphDataArrayIndex = CalculationStartIndex;   
            
```

### sc.GetChartArray()

[Link](#scgetchartarray) - [Top](#top)

**Type**: Function

**GetChartArray**(int **ChartNumber**, int **InputData**, SCFloatArrayRef **PriceArray**);

**sc.GetChartArray()** is for accessing the main/primary base graph data in other loaded charts in the same chartbook containing the chart that your study function is applied to. This is an older function and it is highly recommended that you use **sc.GetChartBaseData** instead. See the **scsf\_GetChartArrayExample()** function in the studies.cpp file in the ACS\_Source folder in the Sierra Chart installation folder for example code to work with this function.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber): If this is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart your study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.
* **InputData**: This can be one of the following:  
  + **SC\_OPEN or 0:** The array of opening prices for each bar.
  + **SC\_HIGH or 1:** The array of high prices for each bar.
  + **SC\_LOW or 2:** The array of low prices for each bar.
  + **SC\_LAST or 3:** The array of closing/last prices for each bar.
  + **SC\_VOLUME or 4:** The array of trade volumes for each bar.
  + **SC\_NUM\_TRADES / SC\_OPEN\_INTEREST or 5:** The array of the number of trades for each bar for Intraday charts. Or the open interest for each bar for daily charts.
  + **SC\_OHLC or 6:** The array of the average prices of the open, high, low, and close prices for each bar.
  + **SC\_HLC or 7:** The array of the average prices of the high, low, and close prices for each bar.
  + **SC\_HL or 8:** The array of the average prices of the high and low prices for each bar.
  + **SC\_BIDVOL or 9:** The array of Bid Volumes for each bar. This represents the volumes of the trades that occurred at the bid.
  + **SC\_ASKVOL or 10:**The array of Ask Volumes for each bar. This represents the volumes of the trades that occurred at the ask.
* **PriceArray**: A SCFloatArray object which will be set to the data array that you requested. If the data array that you requested could not be retrieved, then the size of this array, **PriceArray.GetArraySize()**, will be 0.

#### Example

```cpp

SCFloatArray PriceArray;

// Get the close/last array from chart #1

sc.GetChartArray(1, SC_LAST, PriceArray);

// The PriceArray may not exist or is empty. Either way we can not do anything with it.
if (PriceArray.GetArraySize() == 0)

    return;
            
```

### sc.GetChartBarWidth()

[Link](#scgetchartbarwidth) - [Top](#top)

**Type**: Function

int32\_t **GetChartBarWidth**(int32\_t **ChartNumber**);

The **sc.GetChartBarWidth()** returns the width of the chart bars in pixels, for the specified ChartNumber.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.GetChartBaseData()

[Link](#scgetchartbasedata) - [Top](#top)

**Type**: Function

**GetChartBaseData**(int ChartNumber, SCGraphData & BaseData);

The **sc.GetChartBaseData()** function is for accessing all of the main/primary Base Data arrays in another loaded chart in the same Chartbook as the one containing the chart that your custom study function is applied to which calls this function.

The main Base Data arrays refer to the arrays of the main price graph in a chart. If the main price graph has been replaced by using a custom chart study such as the Point and Figure chart study, then this function will get this new main price graph from the specified ChartNumber.

Refer to the example below. For a complete working example, refer to [Referencing Other Time Frames and Symbols When Using the ACSIL](ACSILRefOtherTimeFrames.md).

For information about getting the corresponding index in the arrays returned, refer to [Accessing Correct Array Indexes in Other Chart Arrays](ACSILRefOtherTimeFrames.md#accessingcorrectarrayindexes).

When you are getting data from another chart with this function, this other chart during a chart replay may not have the data which is up to date to the time of the chart containing the study calling the **sc.GetChartBaseData** function.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber): If this is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart your study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.
* **BaseData**: A SCGraphData object which will be set to all of the main/primary base graph arrays from the specified chart.

#### Example

```cpp

// The following code is for getting the High array
// and corresponding index from another chart.

// Define a graph data object to get all of the base graph data
SCGraphData BaseGraphData;

// Get the base graph data from the specified chart
sc.GetChartBaseData(ChartNumber.GetInt(), BaseGraphData);

// Define a reference to the High array
SCFloatArrayRef HighArray = BaseGraphData[SC_HIGH];

// Array is empty. Nothing to do.
if(HighArray.GetArraySize() == 0)

return;

// Get the index in the specified chart that is
// nearest to current index.
int RefChartIndex =
sc.GetNearestMatchForDateTimeIndex(ChartNumber.GetInt(), sc.Index);

float NearestRefChartHigh = HighArray[RefChartIndex];
            
```

### sc.GetChartbookFilePathAndFilename()

[Link](#scgetchartbookfilepathandfilename) - [Top](#top)

**Type**: Function

int32\_t **GetChartbookFilePathAndFilename**( SCString& **r\_FilePathAndFilename**);

The **sc.GetChartbookFilePathAndFilename()** function returns the complete path and filename of the Chartbook that the chart containing the study instance that is calling this function, is contained within.

This function returns 1 on success, or 0 on an error.

#### Parameters

* **r\_FilePathAndFilename**: This is an SCString. The complete path and filename, is returned in this variable.

### sc.GetChartDateTimeArray()

[Link](#scgetchartdatetimearray) - [Top](#top)

**Type**: Function

**GetChartDateTimeArray**(int **ChartNumber**, SCDateTimeArray& **DateTimeArray**);

**sc.GetChartDateTimeArray()** is used to access the [SCDateTime](SCDateTime.md) array ([sc.BaseDateTimeIn[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scBaseDateTimeIn)) in other loaded charts in the same chartbook containing the chart that your study is applied to. See the **scsf\_GetChartArrayExample()** function in the studies.cpp file inside the ACS\_Source folder inside of the Sierra Chart installation folder for example code to work with this function.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber): If this is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart your study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.
* **DateTimeArray**: A SCDateTimeArray object which will be set to the SCDateTime array that you requested. If the SCDateTime array that you requested could not be retrieved, then the size of this array (**DateTimeArray.GetArraySize()**) will be 0.

#### Example

```cpp

SCDateTimeArray DateTimeArray;

// Get the DateTime array from chart #1
sc.GetChartDateTimeArray(1, DateTimeArray);

// The array may not exist or is empty. Either way we can not do anything with it.
if (DateTimeArray.GetArraySize() == 0)
    return;
            
```

### sc.GetChartDOMFontProperties()

[Link](#scgetchartdomfontproperties) - [Top](#top)

**Type**: Function

int32\_t **GetChartDOMFontProperties**(SCString& **r\_FontName**, int32\_t& **r\_FontSize**, int32\_t& **r\_FontBold**, int32\_t& **r\_FontUnderline**, int32\_t& **r\_FontItalic**);

The **sc.GetChartDOMFontProperties()** function gets the information for the Chart DOM Quantities/Sizes font that is in use for the chart associated with the study from which this function is called.

The function returns a value of **1** if it is able to successfully get the Chart DOM Quantities/Sizes Font information, otherwise it returns a value of **0**.

#### Parameters

* **r\_FontName**: An SCString that contains the name of the font.
* **r\_FontSize**: An integer that contains the size of the font.
* **r\_FontBold**: An integer that specifies if the font is bold or not. A value of **0** indicates it is not bold. A value of 1 indicates the font is bold.
* **r\_FontUnderline**: An integer that specifies if the font is underlined or not. A value of **0** indicates it is not underlined. A value of 1 indicates the font is underlined.
* **r\_Font\_Italic**: An integer that specifies if the font is italic or not. A value of **0** indicates it is not italic. A value of 1 indicates the font is italic.

### sc.GetChartDrawing()

[Link](#scgetchartdrawing) - [Top](#top)

**Type**: Function

For more information, refer to the [sc.GetUserDrawnChartDrawing()](ACSILDrawingTools.md#scgetuserdrawnchartdrawing) section on the **Using Tools From an Advanced Custom Study** page.

### sc.GetChartFontProperties()

[Link](#scgetchartfontproperties) - [Top](#top)

**Type**: Function

int **GetChartFontProperties**(SCString& **r\_FontName**, int32\_t& **r\_FontSize**, int32\_t& **r\_FontBold**, int32\_t& **r\_FontUnderline**, int32\_t& **r\_FontItalic**);

The **sc.GetChartFontProperties** function gets the information for the Chart Text Font that is in use for the chart associated with the study from which this function is called.

The function returns a value of **1** if it is able to successfully get the Chart Text Font information, otherwise it returns a value of **0**.

#### Parameters

* **r\_FontName**: An SCString that contains the name of the font.
* **r\_FontSize**: An integer that contains the size of the font.
* **r\_FontBold**: An integer that specifies if the font is bold or not. A value of **0** indicates it is not bold. A value of 1 indicates the font is bold.
* **r\_FontUnderline**: An integer that specifies if the font is underlined or not. A value of **0** indicates it is not underlined. A value of 1 indicates the font is underlined.
* **r\_Font\_Italic**: An integer that specifies if the font is italic or not. A value of **0** indicates it is not italic. A value of 1 indicates the font is italic.

### sc.GetChartName()

[Link](#scgetchartname) - [Top](#top)

**Type**: Function

SCString **GetChartName**(int **ChartNumber**);

The **sc.GetChartName** function, returns the name of the chart specified by the ChartNumber parameter.

It is only possible to access charts which are in the same Chartbook as the chart containing the study function which is calling this function.

The name contains the symbol of the chart as well as the timeframe per bar and the chart number.

For an example of how to use this function, refer to the **scsf\_Spread3Chart** function in the **/ACS\_Source/studies7.cpp** file in the folder where Sierra Chart is installed to.

#### Example

```cpp

SCString Chart1Name = sc.GetChartName(sc.ChartNumber);
            
```

### sc.GetChartReplaySpeed()

[Link](#scgetchartreplayspeed) - [Top](#top)

**Type**: Function

float **GetChartReplaySpeed**(int **ChartNumber**);

The **sc.GetChartReplaySpeed** function gets the replay speed of the chart specified by the **ChartNumber** parameter.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber): If this is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart your study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.

### sc.GetChartStudyConstantRangeScaleAmount()

[Link](#scgetchartstudyconstantrangescaleamount) - [Top](#top)

**Type**: Function

float **GetChartStudyConstantRangeScaleAmount**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyConstantRangeScaleAmount()** function returns the Range value associated with a Constant Range scale setting for the specified chart and study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyDisplayAsMainPriceGraph()

[Link](#scgetchartstudydisplayasmainpricegraph) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyDisplayAsMainPriceGraph**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyDisplayAsMainPriceGraph()** returns a value of **1** if the specified Chart and Study has the option for **Display as Main Price Graph** enabled. Otherwise, the functions returns a value of **0**.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyDisplayStudyInputValues()

[Link](#scgetchartstudydisplaystudyinputvalues) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyDisplayStudyInputValues**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyDisplayStudyInputValues()** function returns a value of **1** if the specified Chart and Study has the option for **Display Input Values** on the Subgraphs tab enabled. Otherwise, this function returns a value of **0**.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyDisplayStudyName()

[Link](#scgetchartstudydisplaystudyname) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyDisplayStudyName**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyDisplayStudyName()** function returns a value of **1** if the specified Chart and Study has the option for **Display Study Name** on the Subgraphs tab enabled. Otherwise, this function returns a value of **0**.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyDisplaySubgraphsNameAndValue()

[Link](#scgetchartstudydisplaysubgraphsnameandvalue) - [[Top](#top)

**Type**: Function

int32\_t **GetChartStudyDisplaySubgraphsNameAndValue**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyDisplaySubgraphsNameAndValue()** function returns 1 if the specified chart and study have the option for **Display Study Subgraphs Name and Value - Global** enabled. Otherwise, this function returns 0.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyDrawStudyUnderneathMainPriceGraph()

[Link](#scgetchartstudydrawstudyunderneathmainpricegraph) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyDrawStudyUnderneathMainPriceGraph**( int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyDrawStudyUnderneathMainPriceGraph()** function returns 1 if the specified chart and study have the option for **Draw Study Underneath Main Price Graph** enabled. Otherwise, this function returns 0.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyGraphRegion()

[Link](#scgetchartstudygraphregion) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyGraphRegion**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyGraphRegion** function returns the index value of the chart region for the specified chart and study.

The chart region index is a zero-based index, therefore if the study is displayed in the Main Price Graph region, this will return a value of 0.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyHideStudy()

[Link](#scgetchartstudyhidestudy) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyHideStudy**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyHideStudy()** function returns a value of 1 if the option for **Hide Study** is enabled for the specified chart and study. Otherwise, this function returns a value of 0.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyInputChartStudySubgraphValues()

[Link](#scgetchartstudyinputchartstudysubgraphvalues) - [Top](#top)

**Type**: Function

int **GetChartStudyInputChartStudySubgraphValues**(int **ChartNumber**, int **StudyID**, int **InputIndex**, s\_ChartStudySubgraphValues& **r\_ChartStudySubgraphValues**);

The **sc.GetChartStudyInputChartStudySubgraphValues** function gets the study Input value as an s\_ChartStudySubgraphValues structure from the specified ChartNumber and StudyID.

This function works with ChartStudySubgraphValue Input types.

The function returns 1 if successful. Otherwise, 0.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the Input to get the value for. The Input index values + 1 are displayed in the Inputs list on the Study Settings window for the study. Example: (In:1).
* **r\_ChartStudySubgraphValues**: An instance of the s\_ChartStudySubgraphValues structure passed as a reference to receive the Input values.

#### Example

```cpp

s_ChartStudySubgraphValues ChartStudySubgraphValues;

sc.GetChartStudyInputChartStudySubgraphValues(sc.ChartNumber, 1, 1, ChartStudySubgraphValues);			
            
```

### sc.GetChartStudyInputCustomStringListSize()

[Link](#scgetchartstudyinputcustomstringlistsize) - [Top](#top)

**Type**: Function

int **GetChartStudyInputCustomStringListSize**(int **ChartNumber**, int **StudyID**, int **InputIndex**);

The **sc.GetChartStudyInputCustomStringListSize()** function returns the size of the custom string list for the specified chart, study, and input.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the Input to get the value for. The Input index values + 1 are displayed in the Inputs list on the Study Settings window for the study. Example: (In:1).

### sc.GetChartStudyInputCustomStringListString()

[Link](#scgetchartstudyinputcustomstringliststring) - [Top](#top)

**Type**: Function

int **GetChartStudyInputCustomStringListString**( int **ChartNumber**, int **StudyID**, int **InputIndex**);

The **sc.GetChartStudyInputCustomStringListString()** function returns the semicolon separated string which consists of all of the text string items in a [custom string Input](ACSIL_Members_scInputs.md#scinputsetcustominputstrings). The parameters specified, which specific input to get the text strings for.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based Input index, for the study to get the custom text strings for.

### sc.GetChartStudyInputFloat()

[Link](#scgetchartstudyinputfloat) - [Top](#top)

**Type**: Function

int **GetChartStudyInputFloat**(int **ChartNumber**, int **StudyID**, int **InputIndex**, double& **r\_FloatValue**);

The **sc.GetChartStudyInputFloat** function gets the study Input value as a double from the specified Chart Number and Study ID.

This function works with all Input types and returns the value as a double. The necessary conversions are automatically made.

When working with Date and Time Inputs which use [SCDateTime](SCDateTime.md), use this function for getting the value of the Date and Time Input as a double. See the example below to set this into an SCDateTime variable.

The function returns 1 if successful. Otherwise, 0.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the Input to get the value for. The Input index values + 1 are displayed in the Inputs list on the Study Settings window for the study. Example: (In:1).
* **FloatValue**: This parameter receives the double value. It is a reference.

#### Example

```cpp

double FloatInput = 0;
sc.GetChartStudyInputFloat(sc.ChartNumber, 1, 1, FloatInput);

// If the above is obtaining the value from a Date and Time type of Input, then the following code will set this into a SCDateTime variable
SCDateTime DateTimeFromInput;
DateTimeFromInput.SetDateTimeAsDouble(FloatInput);
            
```

### sc.GetChartStudyInputInt()

[Link](#scgetchartstudyinputint) - [Top](#top)

**Type**: Function

int **GetChartStudyInputInt**(int **ChartNumber**, int **StudyID**, int **InputIndex**, int& **r\_IntegerValue**);

The **sc.GetChartStudyInputInt** function gets the study Input value as an integer from the specified Chart Number and Study ID.

This function works with all Input types and returns the value as an integer. The necessary conversions are automatically made.

The function returns 1 if successful. Otherwise, 0.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the Input to get the value for. The Input index values + 1 are displayed in the Inputs list on the Study Settings window for the study. Example: (In:1).
* **IntegerValue**: This parameter receives the integer value. It is a reference.

#### Example

```cpp

	int IntegerInput = 0;
	sc.GetChartStudyInputInt(sc.ChartNumber, 1, 1, IntegerInput);
            
```

### sc.GetChartStudyInputString()

[Link](#scgetchartstudyinputstring) - [Top](#top)

**Type**: Function

int **GetChartStudyInputString**(int **ChartNumber**, int **StudyID**, int **InputIndex**, SCString& **r\_StringValue**);

The **sc.GetChartStudyInputString** function gets the study Input value as a text string from the specified Chart Number and Study ID.

This function works with only string Input types and returns the value as a string.

The function returns 1 if successful. Otherwise, 0.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the Input to get the value for. The Input index values + 1 are displayed in the Inputs list on the Study Settings window for the study. Example: (In:1).
* **r\_StringValue**: This [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings) parameter receives the string. It is a reference.

#### Example

```cpp

	SCString StringInput;
	sc.GetChartStudyInputString(sc.ChartNumber, 1, 1, StringInput);
            
```

### sc.GetChartStudyInputType()

[Link](#scgetchartstudyinputtype) - [Top](#top)

**Type**: Function

int **GetChartStudyInputType**(int **ChartNumber**, int **StudyID**, int **InputIndex**);

The **sc.GetChartStudyInputType** function returns the input type index of the specified chart, study, and input.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the Input to get the value for. The Input index values + 1 are displayed in the Inputs list on the Study Settings window for the study. Example: (In:1).

### sc.GetChartStudyScaleIncrement()

[Link](#scgetchartstudyscaleincrement) - [Top](#top)

**Type**: Function

float **GetChartStudyScaleIncrement**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyScaleIncrement()** function returns the value of the **Scale Increment** for the specified chart and study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyScaleRangeType()

[Link](#scgetchartstudyscalerangetype) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyScaleRangeType**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyScaleRangeType()** returns an integer value that specifies the scale range type of the specified chart and study.

The scale range types and associated integer values are the following (range type with value 5 is not used):

* Automatic: 0
* User Defined: 1
* Independent: 2
* Same As Region: 3
* Constant Range: 4
* Automatic Zero-Based: 6
* Automatic Zero-Centered: 7

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyScaleType()

[Link](#scgetchartstudyscaletype) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyScaleType**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyScaleType()** function returns a value of 0 if the chart scale type is set to **Linear**. Otherwise a value of 1 is returned meaning the scale type is set to **Logarithmic**.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyScaleValueOffset()

[Link](#scgetchartstudyscalevalueoffset) - [Top](#top)

**Type**: Function

float **GetChartStudyScaleValueOffset**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyScaleValueOffset()** returns the value of the scale value offset for the specified chart and study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyShortName()

[Link](#scgetchartstudyshortname) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyShortName**(int32\_t **ChartNumber**, int32\_t **StudyID**, SCString& **r\_ShortName**);

The **GetChartStudyShortName()** function fills out the **Short Name** of the specified chart and study in the r\_ShortName parameter.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **r\_ShortName**: An SCString parameter that contains the short name of the specified chart and study.

### sc.GetChartStudyTransparencyLevel()

[Link](#scgetchartstudytransparencylevel) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyTransparencyLevel**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyTransparencyLevel()** function gets the current transparency level (0 to 100) for Draw Styles which use transparency for the study specified by the [ChartNumber](#commonfunctionparameterdescriptionschartnumber) and [StudyID](#commonfunctionparameterdescriptionsstudyid) parameters.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyUserDefinedScaleRangeBottom()

[Link](#scgetchartstudyuserdefinedscalerangebottom) - [Top](#top)

**Type**: Function

float **GetChartStudyUserDefinedScaleRangeBottom**( int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyUserDefinedScaleRangeBottom()** function returns the **Bottom of Range** value for a User Defined Scale for the defined chart and study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyUserDefinedScaleRangeTop()

[Link](#scgetchartstudyuserdefinedscalerangetop) - [Top](#top)

**Type**: Function

float **GetChartStudyUserDefinedScaleRangeTop**( int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyUserDefinedScaleRangeTop()** function returns the **Top of Range** value for a User Defined Scale for the defined chart and study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyValueFormat()

[Link](#scgetchartstudyvalueformat) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyValueFormat**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyValueFormat()** function returns the Value Format defined for the given Chart and Study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartStudyVersion()

[Link](#scgetchartstudyversion) - [Top](#top)

**Type**: Function

int32\_t **GetChartStudyVersion**(int32\_t **ChartNumber**, int32\_t **StudyID**);

The **sc.GetChartStudyVersion()** returns the version number of the defined Chart and Study.

The version is defined for a study using the **sc.SetChartStudyVersion()** function.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetChartSymbol()

[Link](#scgetchartsymbol) - [Top](#top)

**Type**: Function

SCString **GetChartSymbol**(int **ChartNumber**);

The **sc.GetChartSymbol()** function returns a text string of type [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings), the symbol of the chart specified by the **ChartNumber** parameter. To get the symbol of the chart the study instance is applied to, specify [sc.ChartNumber](ACSIL_Members_Variables_And_Arrays.md#scchartnumber) for the **ChartNumber** parameter.

If the returned text string is blank, this indicates the chart does not exist.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.GetChartTextFontFaceName()

[Link](#scgetcharttextfontfacename) - [Top](#top)

**Type**: Function

SCString **sc.GetChartTextFontFaceName**();

The **sc.GetChartTextFontFaceName()** function returns the font name as a text string of the font that the chart the study instance is applied to, is set to use.

#### Parameters

* This function has no parameters

#### Example

```cpp

Tool.FontFace = sc.GetChartTextFontFaceName();
            
```

### sc.GetChartTimeZone()

[Link](#scgetcharttimezone) - [Top](#top)

**Type**: Function

SCString **sc.GetChartTimeZone**(const int **ChartNumber**);

The **sc.GetChartTimeZone()** function returns the time zone as a string, for the specified ChartNumber.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

### sc.GetChartWindowHandle()

[Link](#getchartwindowhandle) - [Top](#top)

**Type**: Function

HWND **sc.GetChartWindowHandle**(int **ChartNumber**);

The **sc.GetChartWindowHandle()** function returns the window handle as an integer for the specified **ChartNumber**.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

#### Example

```cpp

HWND WindowHandle = sc.GetChartWindowHandle(sc.ChartNumber)
            
```

### sc.GetCombineTradesIntoOriginalSummaryTradeSetting()

[Link](#scgetcombinetradesintooriginalsummarytradesetting) - [Top](#top)

**Type**: Function

int **sc.GetCombineTradesIntoOriginalSummaryTradeSetting**();

The **sc.GetCombineTradesIntoOriginalSummaryTradeSetting()** function gets the state of the [Combine Trades into Original Summary Trade](ChartSettings.md#combinetradesintooriginalsummarytrade) Chart Setting.

#### Parameters

* This function has no parameters.

### sc.GetContainingIndexForDateTimeIndex()

[Link](#scgetcontainingindexfordatetimeindex) - [Top](#top)

**Type**: Function

int **GetContainingIndexForDateTimeIndex**(int **ChartNumber**, int **DateTimeIndex**);

**sc.GetContainingIndexForDateTimeIndex()** returns the index into the Base Data arrays of the chart specified by **ChartNumber** that contains the Date-Time at the index, on the chart your study function is applied to, specified by **DateTimeIndex**. If the Date-Time at **DateTimeIndex** is before any Date-Time in the chart specified with **ChartNumber**, then the index of the first element is given which will be 0. If the Date-Time at **DateTimeIndex** is after any Date-Time in the chart specified with **ChartNumber**, then the index of the last element is given which will be sc.ArraySize - 1.

Containing means that the chart bar starting Date-Time and ending Date-Time in **ChartNumber** contains the Date-Time specified by the **DateTimeIndex** parameter.

This function can be used on the **sc.BaseData[]** arrays for the same chart that your study function is applied to when searching for the Date-Time. To do this, pass **sc.ChartNumber** for the **ChartNumber** parameter.

If **ChartNumber** is given as a negative number, the bar period and other Chart Settings are synchronized between the two charts. If it is positive, this does not occur. For example, if you want to get the index from chart #5, and you want to synchronize the charts, then use -5 for the **ChartNumber** parameter.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* **DateTimeIndex**: The index from the chart on which this study is applied that contains the Date and Time of interest.

#### Error Return Value

This function will return -1 if the chart it is referencing does not exist or its data is not fully loaded.

When the chart it is referencing is opened and fully loaded, then the study instance that made this call will be called again and will be fully recalculated. What actually happens in this case is that the chart the reference was made from, will have all of its studies recalculated.

#### Example

```cpp

// Get the index in the Base Data arrays for chart #2 that contains
// the Date-Time at the current Index of the chart that this study
// is applied to.

int Chart2Index = sc.GetContainingIndexForDateTimeIndex(2, sc.Index);
            
```

### sc.GetContainingIndexForSCDateTime()

[Link](#scgetcontainingindexforscdatetime) - [Top](#top)

**Type**: Function

int **GetContainingIndexForSCDateTime**(int **ChartNumber**, [SCDateTime](SCDateTime.md) **DateTime**);

**sc.GetContainingIndexForSCDateTime()** returns the index into the Base Data arrays of the chart specified by **ChartNumber** that contains **DateTime** . If **DateTime**  is before any Date-Time in the chart specified with **ChartNumber**, then the index of the first element is given which is 0. If **DateTime** is after any Date-Time in the chart specified with **ChartNumber** , then the index of the last element is given which is sc.ArraySize - 1.

Containing means that the chart bar starting Date-Time and ending Date-Time in  **ChartNumber** contains the Date-Time specified by the **DateTime** parameter.

This function can be used on the **sc.BaseData[]** arrays for the same chart that your study function is applied to when searching for the Date-Time. To do this, pass **sc.ChartNumber** for the **ChartNumber** parameter.

If **ChartNumber** is given as a negative number, the bar period and other Chart Settings are synchronized between the two charts. If it is positive, this does not occur. For example, if you want to get the index from chart #5, and you want to synchronize the charts, then use -5 for the **ChartNumber** parameter.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [DateTime](#commonfunctionparameterdescriptionsdatetime)

#### Error Return Value

This function will return -1 if the chart it is referencing does not exist or its data is not fully loaded.

When the chart it is referencing is opened and fully loaded, then the study instance that made this call will be called again and will be fully recalculated. What actually happens in this case, is that the chart the reference was made from, will have all of its studies recalculated.

#### Example

```cpp

// Get the index in the Base Data arrays for chart #2 that contains the specified Date-Time.

SCDateTime DateTime = sc.BaseDateTimeIn[sc.Index];

int Chart2Index = sc.GetContainingIndexForSCDateTime(2, DateTime);
            
```

### sc.GetCorrelationCoefficient()

[Link](#scgetcorrelationcoefficient) - [Top](#top)

**Type**: Intermediate Study Calculation Function

float **GetCorrelationCoefficient**(SCFloatArrayRef **FloatArrayIn1**, SCFloatArrayRef **FloatArrayIn2**, int **Index**, int **Length**);

float **GetCorrelationCoefficient**(SCFloatArrayRef **FloatArrayIn1**, SCFloatArrayRef **FloatArrayIn2**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.GetCorrelationCoefficient()** function calculates the [Pearson product-moment correlation coefficient](https://en.wikipedia.org/wiki/Correlation) from the data in the FloatArrayIn1 and FloatArrayIn2 arrays. The result is returned as a single float value.

#### Parameters

* [FloatArrayIn1](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayIn2](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

float Coefficient = sc.GetCorrelationCoefficient(sc.Subgraph[0], sc.Subgraph[1], 10);
            
```

### sc.GetCountDownText()

[Link](#scgetcountdowntext) - [Top](#top)

**Type**: Function

SCString **GetCountDownText**();

The **sc.GetCountDownText()** function gets the current countdown timer text for the chart.

#### Parameters

* This function has no parameters

#### Example

```cpp

s_UseTool Tool;
Tool.Text.Format("%s",sc.GetCountDownText().GetChars());
            
```

### sc.GetCurrentDateTime()

[Link](#scgetcurrentdatetime) - [Top](#top)

**Type**: Function

SCDateTime **GetCurrentDateTime**();

The **sc.GetCurrentDateTime()** function returns an [SCDateTime](SCDateTime.md) variable which indicates the current Date-Time in the time zone of the chart the study is applied to.

This is obtained from the local system time. So it can be inaccurate if your system time is not set accurately.

During a chart replay, this time is calculated by Sierra Chart based upon the starting Date-Time in the chart where the replay began, the actual elapsed time, and the replay speed. In this particular case you need to be careful when using the returned value. If your computer and Sierra Chart are not able to keep up with the amount of data that needs to be processed during a fast replay, then this Date-Time can be significantly ahead of the Date-Time of the most recently added bar during a chart replay.

During a chart replay, this function returns the same value as [sc.CurrentDateTimeForReplay](ACSIL_Members_Variables_And_Arrays.md#sccurrentdatetimeforreplay).

In general, this Date-Time should never be considered an accurate reference in relation to the last bar start or end Date-Time. And it should not be used during fast Back Testing because it would be inherently inaccurate and unstable because it is a calculated time based on time. The only built-in study which uses this is the **Countdown Timer** study and that is meant to be used for real-time updating and slow speed replays only and only provides indicative visual information.

To access the bar times themselves which is recommended, use the array [sc.BaseDateTimeIn[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scBaseDateTimeIn) for the bar beginning times, and the array [sc.BaseDataEndDateTime[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scBaseDataEndDateTime) for the bar ending times.

Also refer to [sc.LatestDateTimeForLastBar](ACSIL_Members_Variables_And_Arrays.md#sclatestdatetimeforlastbar).

#### Parameters

* This function has no parameters

### sc.GetCurrentTradedAskVolumeAtPrice()

[Link](#scgetcurrenttradedaskvolumeatprice) - [Top](#top)]

**Type**: Function

uint32\_t **GetCurrentTradedAskVolumeAtPrice**(float **Price**);

The **sc.GetCurrentTradedAskVolumeAtPrice** returns the Ask Volume traded at the given **Price** for the symbol of the chart of which the study instance that calls this function is applied to. For more detailed information, refer to [Chart/Trade DOM Column Descriptions](GlobalTradeSettings.md#charttradedomcolumndescriptions).

For this data to be up-to-date and available, there must be a connection to the [data feed](FileMenu.md#connecttodatafeed), or the chart needs to be [replaying](ReplayChart.md).

#### Parameters

* [Price](#commonfunctionparameterdescriptionsprice)

### sc.GetCurrentTradedBidVolumeAtPrice()

[Link](#scgetcurrenttradedbidvolumeatprice) - [Top](#top)

**Type**: Function

uint32\_t **GetCurrentTradedBidVolumeAtPrice**(float **Price**);

The **sc.GetCurrentTradedBidVolumeAtPrice** returns the Bid Volume traded at the given **Price** for the symbol of the chart of which the study instance that calls this function is applied to. For more detailed information, refer to [Chart/Trade DOM Column Descriptions](GlobalTradeSettings.md#charttradedomcolumndescriptions).

For this data to be up-to-date and available, there must be a connection to the [data feed](FileMenu.md#connecttodatafeed), or the chart needs to be [replaying](ReplayChart.md).

#### Parameters

* [Price](#commonfunctionparameterdescriptionsprice)

### sc.GetCustomStudyControlBarButtonEnableState()

[Link](#scgetcustomstudycontrolbarbuttonenablestate) - [Top](#top)

**Type**: Function

int **sc.GetCustomStudyControlBarButtonEnableState**(int **ControlBarButtonNum**);

The **GetCustomStudyControlBarButtonEnableState()** function gets the enable state of the specified Advanced Custom Study Control Bar button.

Returns 1 if the button is enabled. Returns 0 if the button is disabled.

For further details about Advanced Custom study Control Bar buttons, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).

#### Parameters

* **ControlBarButtonNum**: The integer number of the Advanced Custom study Control Bar button. For further details, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).

### sc.GetCustomStudyInformation()

[Link](#scgetcustomstudyinformation) - [Top](#top)

**Type**: Function

int32\_t **GetCustomStudyInformation**(int32\_t **ChartNumber**, int32\_t **StudyID**, n\_ACSIL::s\_CustomStudyInformation& **r\_CustomStudyInformation**);

The **sc.GetCustomStudyInformation()** function fills in the r\_CustomStudyInformation structure with the information for the defined Chart and Study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **r\_CustomStudyInformation**: a structure containing the following items:
  + SCString **DLLPath**: The file structure path to the referenced study.
  + SCString **DLLFileName**: The file name of the DLL containing the referenced study.
  + SCString **DLLFunctionName**: The function name of the referenced study in the DLL file.
  + SCString **StudyOriginalName**: The original name of the referenced study.

### sc.GetDataDelayFromChart()

[Link](#scgetdatadelayfromchart) - [Top](#top)

**Type**: Function

SCDateTime **GetDataDelayFromChart**(const int **ChartNumber**);

The **GetDataDelayFromChart()** function returns the data delay as an SCDateTime variable of the chart specified by the ChartNumber parameter.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

### sc.GetDispersion()

[Link](#scgetdispersion) - [Top](#top)

**Type**: Intermediate Study Calculation Function

float **GetDispersion**(SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

float **GetDispersion**(SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.GetDispersion()** function calculates the dispersion. The result is returned as a single float value.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

float Dispersion = sc.GetDispersion(sc.BaseDataIn[SC_HIGH], 10);
            
```

### sc.GetDOMColumnLeftCoordinate()

### sc.GetDOMColumnRightCoordinate()

[Link](#scgetdomcolumnleftcoordinate) - [Top](#top)

**Type**: Function

int **GetDOMColumnLeftCoordinate**(n\_ACSIL::DOMColumnTypeEnum **DOMColumn**);

int **GetDOMColumnRightCoordinate**(n\_ACSIL::DOMColumnTypeEnum **DOMColumn**);

The **sc.GetDOMColumnLeftCoordinate** and **sc.GetDOMColumnRightCoordinate** functions return the X-axis pixel coordinates for the left and right sides of the given **DOMColumn** on the current chart. If the requested **DOMColumn** does not exist on the chart, the functions will return a value of 0.

One use of these functions is to draw into the general purpose Chart/Trade DOM columns by using the [Custom Free Form Drawing](ACSILProgrammingConcepts.md#customfreeformdrawing) operating system API.

#### Parameters

* **DOMColumn**: The DOMColumnTypeEnum to define the column for which the the left or right coordinate is retrieved.
    
  Valid values for the **DOMColumn** parameter can be found in the **DOMColumnTypeEnum** located in the **n\_ACSIL** namespace. These include the following:
  + DOM\_COLUMN\_PRICE
  + DOM\_COLUMN\_BUY\_ORDER
  + DOM\_COLUMN\_SELL\_ORDER
  + DOM\_COLUMN\_BID\_SIZE
  + DOM\_COLUMN\_ASK\_SIZE
  + DOM\_COLUMN\_COMBINED\_BID\_ASK\_SIZE
  + DOM\_COLUMN\_BID\_SIZE\_BUY
  + DOM\_COLUMN\_ASK\_SIZE\_SELL
  + DOM\_COLUMN\_LAST\_SIZE
  + DOM\_COLUMN\_CUMULATIVE\_LAST\_SIZE
  + DOM\_COLUMN\_RECENT\_BID\_VOLUME
  + DOM\_COLUMN\_RECENT\_ASK\_VOLUME
  + DOM\_COLUMN\_CURRENT\_TRADED\_BID\_VOLUME
  + DOM\_COLUMN\_CURRENT\_TRADED\_ASK\_VOLUME
  + DOM\_COLUMN\_CURRENT\_TRADED\_TOTAL\_VOLUME
  + DOM\_COLUMN\_BID\_MARKET\_DEPTH\_PULLING\_STACKING
  + DOM\_COLUMN\_ASK\_MARKET\_DEPTH\_PULLING\_STACKING
  + DOM\_COLUMN\_COMBINED\_BID\_ASK\_MARKET\_DEPTH\_PULLING\_STACKING
  + DOM\_COLUMN\_PROFIT\_AND\_LOSS
  + DOM\_COLUMN\_SUBGRAPH\_LABELS
  + DOM\_COLUMN\_GENERAL\_PURPOSE\_1
  + DOM\_COLUMN\_GENERAL\_PURPOSE\_2

#### Example

```cpp

int GeneralPurposeColumnLeft = sc.GetDOMColumnLeftCoordinate(n_ACSIL::DOM_COLUMN_GENERAL_PURPOSE_1);

int GeneralPurposeColumnRight = sc.GetDOMColumnRightCoordinate(n_ACSIL::DOM_COLUMN_GENERAL_PURPOSE_1);
            
```

### sc.GetEarliestSourceIndexForDestinationDateTime()

[Link](#scgetearliestsourceindexfordestinationdatetime) - [Top](#top)

**Type**: Function

int **GetEarliestSourceIndexForDestinationDateTime**(int **DestinationDateTimeIndex**, const SCDateTime& **BarTimeDuration**, int **BarTimeMatchingMethod**, int **DestinationChartNumber**, int **SourceChartNumber**, int **SourceMaximumDisplacement**, int **DestinationBarsForward**);

#### Parameters

* **DestinationDateTimeIndex**:
* **BarTimeDuration**:
* **BarTimeMatchingMethod**:
* **DestinationChartNumber**:
* **SourceChartNumber**:
* **SourceMaximumDisplacement**:
* **DestinationBarsForward**:

#### Example

*No example provided by SierraChart*

### sc.GetEndingDateTimeForBarIndex()

[Link](#scgetendingdatetimeforbarindex) - [Top](#top)

**Type**: Function

double **GetEndingDateTimeForBarIndex**(int **BarIndex**);

The **sc.GetEndingDateTimeForBarIndex** function returns the ending Date-Time of a chart bar specified by its bar index. The chart bar index is specified with the **BarIndex** parameter.

The time returned has microsecond precision and can be assigned to an [SCDateTime](SCDateTime.md) variable.

This Date-Time is calculated for bars other than at the last bar in the chart. For the last bar in the chart, the ending date time is known precisely if the **Global Settings >> Data/Trade Service Settings >> Intraday Data Storage Time Unit** is **1 Tick** or **1 Second Per Bar** .

The chart [Session Times](SessionTimes.md) are also used in the calculation where necessary. For example, if a chart bar is cut short because it has encountered the end of a specified Intraday session, the end of the session is used as the ending Date-Time for the bar.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex)

### sc.GetEndingDateTimeForBarIndexFromChart()

[Link](#scgetendingdatetimeforbarindexfromchart) - [Top](#top)

**Type**: Function

double **GetEndingDateTimeForBarIndexFromChart**(int **ChartNumber**, int **BarIndex**);

The **sc.GetEndingDateTimeForBarIndexFromChart** function returns the ending Date-Time of a chart bar specified by its bar index. This function can reference any chart in the same Chartbook containing the chart the study function is called from.

The return type is a double which can be directly assigned to an [SCDateTime](SCDateTime.md) variable.

The returned Date-Time is calculated for bars prior to the last bar in the chart. The calculation is simply the Date-Time of the following bar minus 1 second. However, if the particular time is outside of the Session Times, then it is adjusted to be within the Session Times as explained below.

For the last bar in the chart, the ending Date-Time is known precisely if the **Global Settings >> Data/Trade Service Settings >> Intraday Data Storage Time Unit** is **1 Tick** or **1 Second Per Bar**  and is the Date-Time of the last trade.

The chart [Session Times](SessionTimes.md) are also used in the calculation where necessary. For example, if a chart bar is cut short because it has encountered the end of a specified Intraday session, the end of the session is used at the ending Date-Time for the bar.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [BarIndex](#commonfunctionparameterdescriptionsbarindex)

### sc.GetExactMatchForSCDateTime()

[Link](#scgetexactmatchforscdatetime) - [Top](#top)

**Type**: Function

int **GetExactMatchForSCDateTime**(int **ChartNumber**, SCDateTime **DateTime**);

**sc.GetExactMatchForSCDateTime()** returns the index into the Base Data arrays of the chart specified by **ChartNumber** that exactly matches the **DateTime**. If there is no exact match, this function returns **-1**.

This function can be used on the **sc.BaseData[]** arrays for the same chart that your study function is applied to when searching for the Date-Time. To do this, pass **sc.ChartNumber** for the **ChartNumber** parameter.

If **ChartNumber** is given as a negative number, the bar period and other Chart Settings are synchronized between the two charts. If it is positive, this does not occur. For example, if you want to get the index from chart #5, and you want to synchronize the charts, then use -5 for the **ChartNumber** parameter.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [DateTime](#commonfunctionparameterdescriptionsdatetime)

#### Example

```cpp

// Get the index into the Base Data of chart #2
// that exactly matches the DateTime given through the Input

// Get the DateTime from Input 0
SCDateTime DateTime = sc.Input[0].GetDateTime();

int Chart2Index = sc.GetExactMatchForSCDateTime(2, DateTime);

if(Chart2Index != -1)
{
    //Your Code
}
            
```

### sc.GetFirstIndexForDate()

[Link](#scgetfirstindexfordate) - [Top](#top)

**Type**: Function

int **GetFirstIndexForDate**(int **ChartNumber**, int **TradingDayDate**);

The **sc.GetFirstIndexForDate()** function returns the first array index into the **sc.BaseDateTimeIn[][]** array for the specified **ChartNumber** where the given **TradingDayDate** first occurs.

For an understanding of Trading day dates, refer to [Understanding Trading Day Dates Based on Session Times](SessionTimes.md#understandingtradingdaydatesbasedonsessiontimes).

If there are no bars in the array matching the requested TradingDayDate, then the index of the first array index after the requested TradingDayDate is returned.

The **TradingDayDate**  parameter is a [SCDateTime](SCDateTime.md) type that contains the date only. If it contains a time, the time part will be ignored.

#### Example

```cpp

FirstIndexOfReferenceDay = sc.GetFirstIndexForDate(sc.ChartNumber, ReferenceDay);

if (sc.GetTradingDayDate(sc.BaseDateTimeIn[FirstIndexOfReferenceDay]) == ReferenceDay)
    --InNumberOfDaysBack;
            
```

### sc.GetFirstNearestIndexForTradingDayDate()

[Link](#scgetfirstnearestindexfortradingdaydate) - [Top](#top)

**Type**: Function

int **sc.GetFirstNearestIndexForTradingDayDate**(int **ChartNumber**, int **TradingDayDate**);

The **sc.GetFirstNearestIndexForTradingDayDate()** function returns the first array index into the **sc.BaseDateTimeIn[][]** array for the specified **ChartNumber** where the given **TradingDayDate** first occurs.

For an understanding of Trading day dates, refer to [Understanding Trading Day Dates Based on Session Times](SessionTimes.md#understandingtradingdaydatesbasedonsessiontimes).

If there are no bars in the array matching the requested TradingDayDate, then the index with the date-time that is nearest to the given TradingDayDate is returned.

The **TradingDayDate**  parameter is a [SCDateTime](SCDateTime.md) type that contains the date only. If it contains a time, the time part will be ignored.

### sc.GetFlatToFlatTradeListEntry()

[Link](#scgetflattoflattradelistentry) - [Top](#top)

Refer to the [sc.GetFlatToFlatTradeListEntry()](ACSILTrading.md#scgetflattoflattradelistentry) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetFlatToFlatTradeListSize()

[Link](#scgetflattoflattradelistsize) - [Top](#top)

Refer to the [sc.GetFlatToFlatTradeListSize()](ACSILTrading.md#scgetflattoflattradelistsize) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetGraphicsSetting()

[Link](#scgetgraphicssetting) - [Top](#top)

**Type**: Function

int32\_t **GetGraphicsSetting**(const int32\_t **ChartNumber**, const n\_ACSIL::GraphicsSettingsEnum **GraphicsSetting**, uint32\_t& **r\_Color**, uint32\_t& **r\_LineWidth**, SubgraphLineStyles& **r\_LineStyle**);

The **sc.GetGraphicsSetting** function .

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* **GraphicsSetting**: .
* **r\_Color**: .
* **r\_LineWidth**: .
* **r\_LineStyle**: .

#### Example

*No example provided by SierraChart*

### sc.GetGraphicsSettingEnableState()

[Link](#scgetgraphicssettingenablestate) - [Top](#top)

**Type**: Function

int32\_t **GetGraphicsSettingEnableState**(const int32\_t **ChartNumber**, const n\_ACSIL::GraphicsSettingsEnum **GraphicsSetting**);

The **sc.GetGraphicsSettingEnableState()** function returns a value of 1 if the given graphics setting has the **Enable** option enabled. If there is not an option to Enable/Disable the given graphics setting, then a value of 1 is also returned. A value of 0 is returned if the graphics setting has the **Enable** option disabled.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **GraphicsSetting**: The enumeration value for the desired graphics setting to test. This enumeration can be found in the **ACS\_Source/scconstants.h** file located in the main Sierra Chart installation folder.

### sc.GetGraphVisibleHighAndLow()

[Link](#scgetgraphvisiblehighandlow) - [Top](#top)

**Type**: Function

void **GetGraphVisibleHighAndLow**(double& **High**, double& **Low**);

The **sc.GetGraphVisibleHighAndLow** function determines the highest and lowest price values for the scale of the study instance from which this function is called at the time of the function call and puts that information into the referenced variables.

#### Parameters

* **High**: The highest price of the Scale for the study.
* **Low**: The lowest price of the Scale for the study.

### sc.GetHideChartDrawingsFromOtherCharts()

[Link](#scgethidechartdrawingsfromothercharts) - [Top](#top)

**Type**: Function

int **GetHideChartDrawingsFromOtherCharts**(const int **ChartNumber**);

The **sc.GetHideChartDrawingsFromOtherCharts** function .

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

#### Example

*No example provided by SierraChart*

### sc.GetHighest()

[Link](#scgethighest) - [Top](#top)

**Type**: Intermediate Study Calculation Function

float **GetHighest**(SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

float **GetHighest**(SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.GetHighest()** function returns the highest value over the specified Length in the FloatArrayIn array.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

//Get the highest high from the base graph over the last 20 bars
float Highest = sc.GetHighest(sc.BaseDataIn[SC_HIGH], 20);

//Get the highest value from sc.Subgraph[0] over the last 20 bars
Highest = sc.GetHighest(sc.Subgraph[0], 20);
            
```

### sc.GetHighestChartNumberUsedInChartBook()

[Link](#scgethighestchartnumberusedinchartbook) - [Top](#top)

**Type**: Function

int **GetHighestChartNumberUsedInChartBook**();

The **sc.GetHighestChartNumberUsedInChartBook** function returns the highest Chart Number used in the Chartbook the chart the study function is applied to, belongs to.

Each chart has a number which is displayed on its title bar. This is its Chart Number for identification purposes.

#### Parameters

* This function has no parameters

### sc.GetIndexOfHighestValue()

[Link](#scgetindexofhighestvalue) - [Top](#top)

**Type**: Function

float **GetIndexOfHighestValue**(SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

float **GetIndexOfHighestValue**(SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.GetIndexOfHighestValue()** function returns the [bar index](ACS_ArraysAndLooping.md#arrayindexing) of the highest value over the specified Length in the FloatArrayIn array.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

### sc.GetIndexOfLowestValue()

[Link](#scgetindexoflowestvalue) - [Top](#top)

(SCFloatArrayRef In, int Length)

**Type**: Function

float **GetIndexOfLowestValue**(SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

float **GetIndexOfLowestValue**(SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.GetIndexOfLowestValue()** function returns the [bar index](ACS_ArraysAndLooping.md#arrayindexing) of the lowest value over the specified Length in the FloatArrayIn array.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

### sc.GetIslandReversal()

[Link](#scgetislandreversal) - [Top](#top)

**Type**: Intermediate Study Calculation Function

int **GetIslandReversal**(SCBaseDataRef **BaseDataIn**, int **Index**);

int **GetIslandReversal**(SCBaseDataRef **BaseDataIn**); [Auto-looping only](#noindexparam).

The **sc.GetIslandReversal()** function determines an Island Reversal. This function returns one of the following values:  
0 = No Gap.  
1 = Gap Up.  
-1 = Gap Down.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

int IslandReversal = sc.GetIslandReversal(sc.BaseDataIn);
            
```

### sc.GetKeyboardBufferForChart()

[Link](#scgetkeyboardbufferforchart) - [Top](#top)

**Type**: Function

int32\_t **GetKeyboardBufferForChart**(const int32\_t **ChartNumber**, SCString& **r\_KeyboardInputBuffer**);

The **GetKeyboardBufferForChart()** function fills in the **r\_KeyboardInputBuffer** parameter with the keyboard buffer string that is entered for the given chart.

The function returns a value of 0 if the chart can not be found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **r\_KeyboardInputBuffer**: This is a reference parameter. It holds the string for the keyboard buffer of the given chart.

### sc.GetLastFileErrorCode()

[Link](#scgetlastfileerrorcode) - [Top](#top)

**Type**: Function

int **GetLastFileErrorCode**(const int **FileHandle**);

The **sc.GetLastFileErrorCode** function returns the last error code associated with the **FileHandle** parameter which is obtained by [sc.OpenFile()](#scopenfile).

The returned code is the standard operating system error code.

Additionally the following error codes are defined:

* ERROR\_MISSING\_PATH\_AND\_FILE\_NAME = 0x20000001
* ERROR\_NO\_BUFFER\_GIVEN\_INPUT = 0x20000002
* ERROR\_NO\_BUFFER\_GIVEN\_OUTPUT = 0x20000003
* ERROR\_NOT\_ENOUGH\_DATA\_FOR\_VALUE = 0x20000004
* ERROR\_AT\_END\_OF\_FILE = 0x20000005
* ERROR\_END\_OF\_LINE\_NOT\_FOUND = 0x20000006
* ERROR\_FILE\_NOT\_OPEN = 0x20000007
* ERROR\_ALLOCATING\_MEMORY = 0x20000008

#### Parameters

* [FileHandle](#commonfunctionparameterdescriptionsfilehandle)

### sc.GetLastFileErrorMessage()

[Link](#scgetlastfileerrormessage) - [Top](#top)

**Type**: Function

SCString **GetLastFileErrorMessage**(const int **FileHandle**);

The **sc.GetLastFileErrorMessage()** function returns the last error message, if there is one, associated with the File Handle defined by **FileHandle**.

If there is no error message, an empty string is returned.

#### Parameters

* [FileHandle](#commonfunctionparameterdescriptionsfilehandle)

### sc.GetLastPriceForTrading()

[Link](#scgetlastpricefortrading) - [Top](#top)

**Type**: Function

double **GetLastPriceForTrading**();

**GetLastPriceForTrading** returns the most current last trade price for the Symbol of the chart either from the connected data feed or from the last bar in the chart if the data feed price is 0 meaning it is not available.

This function also works during a chart replay.

#### Parameters

* This function has no parameters

#### Example

```cpp

double LastPrice = sc.GetLastPriceForTrading();       
            
```

### sc.GetLatestBarCountdownAsInteger()

[[Link](#)] - [Top](#top)

**Type**: Function

int **scGetLatestBarCountdownAsInteger**();

The **sc.GetLatestBarCountdownAsInteger()** function returns the remaining time/value for the most recent chart bar until it is considered finished, as an integer value.

#### Parameters

* This function has no parameters

#### Example

```cpp

int CountdownValue = sc.GetLatestBarCountdownAsInteger();
RemainingAmountForSubgraphValue = (float)CountdownValue;

Tool.Text.Format("%d",CountdownValue);
            
```

### sc.GetLatestSourceIndexForDestinationDateTime()

[Link](#scgetlatestsourceindexfordestinationdatetime) - [Top](#top)

**Type**: Function

int **GetLatestSourceIndexForDestinationDateTime**( int **DestinationDateTimeIndex**, const SCDateTime& **BarTimeDuration**, int **BarTimeMatchingMethod**, int **DestinationChartNumber**, int **SourceChartNumber**, int **SourceMaximumDisplacement**, int **DestinationBarsForward**);

#### Parameters

* **DestinationDateTimeIndex**:
* **BarTimeDuration**:
* **BarTimeMatchingMethod**:
* **DestinationChartNumber**:
* **SourceChartNumber**:
* **SourceMaximumDisplacement**:
* **DestinationBarsForward**:

### sc.GetLineNumberOfSelectedUserDrawnDrawing

[Link](#scgetlinenumberofselecteduserdrawndrawing) - [Top](#top)

Refer to the [sc.GetLineNumberOfSelectedUserDrawnDrawing()](ACSILDrawingTools.md#scgetlinenumberofselecteduserdrawndrawing) section on the [Using Drawing Tools From an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.GetLowest()

[Link](#scgetlowest) - [Top](#top)

**Type**: Intermediate Study Calculation Function

float **GetLowest**(SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

float **GetLowest**(SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.GetLowest()** function returns the lowest value over the specified Length in the FloatArrayIn array.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

float Lowest = sc.GetLowest(sc.BaseDataIn[SC_LOW], 20);

Lowest = sc.GetLowest(sc.Subgraph[0], 20);
            
```

### sc.GetMainGraphVisibleHighAndLow()

[Link](#scgetmaingraphvisiblehighandlow) - [Top](#top)

**Type**: Function

**GetMainGraphVisibleHighAndLow** (float& **High**, float& **Low**);

**sc.GetMainGraphVisibleHighAndLow** will get the highest High and lowest Low for the visible bars of the main price graph in the chart.

#### Parameters

* **High**: The highest high value found.
* **Low**: The lowest low value found.

#### Example

```cpp

float High, Low;

sc.GetMainGraphVisibleHighAndLow(High,Low);
            
```

### sc.GetMarketDepthBars()

[link](#scgetmarketdepthbars) - [Top](#top)

**Type**: Function

c\_ACSILDepthBars\* **GetMarketDepthBars**();

**sc.GetMarketDepthBars** returns access to the historical market depth bars that are on the same chart that your custom study is applied to. The return value is a pointer to a c\_ACSILDepthBars object, which has various functions for retrieving data from the historical market depth bars. See the [c\_ACSILDepthBars class](c_ACSILDepthBars.md) for details.

**sc.GetMarketDepthBars** should never return a null pointer, but it is still good practice to check to make sure the returned pointer is not null before using it.

#### Parameters

* This function has no parameters.

### sc.GetMarketDepthBarsFromChart()

[link](#scgetmarketdepthbarsfromchart) - [Top](#top)

**Type**: Function

c\_ACSILDepthBars\* **GetMarketDepthBarsFromChart**(int **ChartNumber**);

**sc.GetDepthBarFromChart** returns access to the historical market depth bar from the chart that matches the given **ChartNumber** parameter. The return value is a pointer to a c\_ACSILDepthBars object, which has various functions for retrieving data from the historical market depth bars. See the [c\_ACSILDepthBars class](c_ACSILDepthBars.md) for details.

**sc.GetDepthBarFromChart** should never return a null pointer, but it is still good practice to check to make sure the returned pointer is not null before using it.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber): If this is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart the study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.

### sc.GetMaximumMarketDepthLevels

[Link](#scgetmaximummarketdepthlevels) - [Top](#top)

**Type**: Function

int **GetMaximumMarketDepthLevels**();

The **sc.GetMaximumMarketDepthLevels** function returns the maximum number of available market depth levels for the symbol of the chart. This will be the maximum for both the bid and ask sides, whichever is greater.

#### Parameters

* This function has no parameters

### sc.GetNearestMatchForDateTimeIndex()

[Link](#scgetnearestmatchfordatetimeindex) - [Top](#top)

**Type**: Function

int **GetNearestMatchForDateTimeIndex**(int **ChartNumber**, int **DateTimeIndex**);

**sc.GetNearestMatchForDateTimeIndex()** returns the index into the Base Data arrays of the chart specified by **ChartNumber** with the Date-Time closest to the Date-Time at the index specified by **DateTimeIndex** in the chart your study is applied to. If the Date-Time at **DateTimeIndex** is before any Date-Time in the specified chart, then the index of the first element is given (0). If the Date-Time at **DateTimeIndex** is after any Date-Time in the specified chart, then the index of the last element is given (sc.ArraySize - 1).

This function can be used on the **sc.BaseData[]** arrays for the same chart that your study function is applied to when searching for the Date-Time. To do this, pass **sc.ChartNumber** for the **ChartNumber** parameter.

If **ChartNumber** is given as a negative number, the bar period and other Chart Settings are synchronized between the two charts. If it is positive, this does not occur. For example, if you want to get the index from chart #5, and you want to synchronize the charts, then use -5 for the **ChartNumber** parameter.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **DateTimeIndex**: The index containing the date and time of interest from the chart on which the study calling this function is applied to.

#### Error Return Value

This function will return -1 if the chart it is referencing does not exist or its data is not fully loaded.

When the chart it is referencing is opened and fully loaded, then the study instance that made this call will be called again and will be fully recalculated. What actually happens in this case, is that the chart the reference was made from, will have all of its studies recalculated.

#### Matching Rules for a Nearest Date-Time Match

Refer to the [Matching Rules for a Nearest Date-Time Match](#nearestmatchingrules) section.

#### Example

```cpp

// Get the index in the Base Data arrays for chart #2 that
// has the nearest matching Date-Time to the Date-Time
// at the current index being calculated for the chart that
// this study is on.

int Chart2Index = sc.GetNearestMatchForDateTimeIndex(2, sc.Index);

SCGraphData ReferenceArrays;
sc.GetChartBaseData(2, ReferenceArrays);

if (ReferenceArrays[SC_HIGH].GetArraySize() < 1)//Array is empty, nothing to do.

   return;

//Get the corresponding High 
float High = ReferenceArrays[SC_HIGH][Chart2Index];
            
```

### sc.GetNearestMatchForSCDateTime()

[Link](#scgetnearestmatchforscdatetime) - [Top](#top)

**Type**: Function

int **GetNearestMatchForSCDateTime**(int **ChartNumber**, [SCDateTime](SCDateTime.md) **DateTime**);

**sc.GetNearestMatchForSCDateTime()** returns the index into the Base Data arrays of the chart specified by the **ChartNumber** parameter with the Date-Time closest to the **DateTime** parameter.

If the specified **DateTime** is before any Date-Time in the specified chart, then the index of the first element is given (0). If **DateTime** is after any Date-Time in the specified chart, then the index of the last element is given (**sc.ArraySize** - 1).

The extended array elements of the chart in the forward projection area of the chart are not included in the search.

This function can be used on the **sc.BaseData[]** arrays for the same chart that your study function is applied to when searching for the Date-Time. To do this, pass **sc.ChartNumber** for the **ChartNumber** parameter.

If **ChartNumber** is given as a negative number, the bar period and other Chart Settings are synchronized between the two charts. If it is positive, this does not occur. For example, if you want to get the index from chart #5, and you want to synchronize the charts, then use -5 for the **ChartNumber** parameter.

For complete information about the **SCDateTime** parameter type, refer to [SCDateTime](SCDateTime.md).

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [DateTime](#commonfunctionparameterdescriptionsdatetime)

#### Error Return Value

This function will return -1 if the chart it is referencing does not exist or its data is not fully loaded.

When the chart it is referencing is opened and fully loaded, then the study instance that made this call will be called again and will be fully recalculated. What actually happens in this case, is that the chart the reference was made from, will have all of its studies recalculated.

#### Matching Rules for a Nearest Date-Time Match

1. If an exact match can be done, then the index with the exact match will be returned. If there are repeating timestamps, then the first index in the repeating times is given.
2. If there is not an exact match, then the index of the nearest matching date-time is given.
3. If the given date-time is equidistant between two date-times, then the index for the higher date-time is given.

#### Example

```cpp

// Get the index in the Base Data arrays for chart #2 that
// has the nearest matching Date-Time to the given DateTime.

SCDateTime DateTime = sc.BaseDateTimeIn[sc.Index];

int Chart2Index = sc.GetNearestMatchForSCDateTime(2, DateTime);

SCGraphData ReferenceArrays;
sc.GetChartBaseData(2, ReferenceArrays);

if (ReferenceArrays[SC_HIGH].GetArraySize() < 1)//Array is empty, nothing to do.

   return;

//Get the corresponding High 
float High = ReferenceArrays[SC_HIGH][Chart2Index];
            
```

### sc.GetNearestMatchForSCDateTimeExtended()

[Link](#scgetnearestmatchforscdatetimeextended) - [Top](#top)

**Type**: Function

int **GetNearestMatchForSCDateTimeExtended**(int **ChartNumber**, const SCDateTime& **DateTime**);

The **sc.GetNearestMatchforSCDateTimeExtended()** function is identical to the [sc.GetNearestMatchForSCDateTime()](#scgetnearestmatchforscdatetime) function, except that it also searches the extended array elements of the chart in the forward projection area.

For complete documentation for this function, refer to [sc.GetNearestMatchForSCDateTime()](#scgetnearestmatchforscdatetime). The only other difference has been explained here.

For a complete example to use this function, refer to the **scsf\_VerticalDateTimeLine** function in the **/ACS\_Source/studies2.cpp** file in the folder Sierra Chart is installed to.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [DateTime](#commonfunctionparameterdescriptionsdatetime)

### sc.GetNearestStopOrder()

[Link](#scgetneareststoporder) - [Top](#top)

Refer to the [sc.GetNearestStopOrder()](ACSILTrading.md#scgetneareststoporder) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetNearestStopWorkingAttachedOrder()

[Link](#scgetneareststopworkingattachedorder) - [Top](#top)

Refer to the [sc.GetNearestStopWorkingAttachedOrder()](ACSILTrading.md#scgetneareststopworkingattachedorder) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetNearestTargetOrder()

[Link](#scgetnearesttargetorder) - [Top](#top)

Refer to the [sc.GetNearestTargetOrder()](ACSILTrading.md#scgetnearesttargetorder) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetNearestTargetWorkingAttachedOrder()

[Link](#scgetnearesttargetworkingattachedorder) - [Top](#top)

Refer to the [sc.GetNearestTargetWorkingAttachedOrder()](ACSILTrading.md#scgetnearesttargetworkingattachedorder) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetNumberOfBaseGraphArrays()

[Link](#scgetnumberofbasegrapharrays) - [Top](#top)

**Type**: Function

int **GetNumberOfBaseGraphArrays**();

The **sc.GetNumberOfBaseGraphArrays()** function gets the number of arrays allocated in **sc.BaseData[]**.

#### Parameters

* This function has no parameters

#### Example

```cpp

int NumberOfBaseDataArrays = sc.GetNumberOfBaseGraphArrays();
            
```

### sc.GetNumberOfDataFeedSymbolsTracked()

[Link](#scgetnumberofdatafeedsymbolstracked) - [Top](#top)

**Type**: Function

int **GetNumberOfDataFeedSymbolsTracked**();

The **sc.GetNumberOfDataFeedSymbolsTracked()** function returns the number of symbols Sierra Chart is currently tracking through the connected data feed. This function has no parameters.

For additional information, refer to [Status Bar](StatusBar.md).

#### Parameters

* This function has no parameters

### sc.GetNumLinesUntilFutureIntersection()

[Link](#scgetnumlinesuntilfutureintersection) - [Top](#top)

**Type**: Function

int **GetStudyLineUntilFutureIntersection**(int **ChartNumber**, int **StudyID**, int **Index**);

The **sc.GetNumLinesUntilFutureIntersection** function is used to get the number of lines which have been added to a particular study through the [sc.AddLineUntilFutureIntersection](#scaddlineuntilfutureintersection) function.

Return Value: The number lines. Returns 0 if there are no lines.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [Index](#commonfunctionparameterdescriptionsindex)

### sc.GetNumPriceLevelsForStudyProfile()

[Link](#scgetnumpricelevelsforstudyprofile) - [Top](#top)

**Type**: Function

int **GetNumPriceLevelsForStudyProfile**(int **StudyID**, int **ProfileIndex**);

The **sc.GetNumPriceLevelsForStudyProfile** function is to be used with the [sc.GetVolumeAtPriceDataForStudyProfile](#scgetvolumeatpricedataforstudyprofile) function. It is used to return the number of price levels contained within a Volume Profile.

These Volume Profiles are from a [TPO Profile Chart](StudiesReference/TimePriceOpportunityCharts.md) or [Volume by Price](StudiesReference.md) study on the chart.

The function returns the number of price levels within the specified Volume Profile.

#### Parameters

* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ProfileIndex**: The zero-based index of the volume profile relative to the end of the chart. 0 equals the latest profile in the chart at the end or rightmost side. This needs to always be set to a positive number.

### sc.GetNumStudyProfiles()

[Link](#scgetnumstudyprofiles) - [Top](#top)

**Type**: Function

int **GetNumStudyProfiles**(int **StudyID**);

**sc.GetNumStudyProfiles** will get the number of TPO Profiles or Volume Profiles for the [TPO Profile Chart](StudiesReference/TimePriceOpportunityCharts.md) and the [Volume by Price](StudiesReference.md) study respectively in the instance of the study specified by the **StudyID** parameter.

#### Parameters

* [StudyID](#commonfunctionparameterdescriptionsstudyid)

#### Example

```cpp

            int NumProfiles = sc.GetNumStudyProfiles(1);
            
```

### sc.GetNumTradeAccounts()

[Link](#scgetnumtradeaccounts) - [Top](#top)

**Type**: Function

int32\_t**GetNumTradeAccounts**();

The **sc.GetNumTradeAccounts()** function returns the number of trade accounts that are available.

#### Parameters

* This function has no parameters

### sc.GetOHLCForDate()

[Link](#scgetohlcfordate) - [Top](#top)

**Type**: Function

int **GetOHLCForDate**(double **Date**, float& **Open**, float& **High**, float& **Low**, float& **Close**);

The **sc.GetOHLCForDate()** function returns the Open, High, Low and Close of the period of time in an Intraday chart that is for the date specified by the **Date** parameter.

The Period of time is 1 Day. The starting and ending times are controlled by the [Session Times](SessionTimes.md) settings in **Chart >> Chart Settings** for the Chart.

The end of the day is the time set by the **End Time** Session Time. The day includes the 24 hours prior to that time.

For efficiency, this function should only be called once a day while iterating through the chart bars in the study function. The values returned should be saved for the next iteration until a new day is encountered according to the Session Times.

#### Parameters

* **Date**: The date of interest specified using the same concept as an SCDateTime, only the time portion (right of the decimal point) is ignored).
* **Open**: The Open for the defined date.
* **High**: The High for the defined date.
* **Low**: The Low for the defined date.
* **Close**: The Close for the defined date.

#### Example

```cpp

float Open;
float High;
float Low;
float Close;

sc.GetOHLCForDate(sc.BaseDateTimeIn[sc.ArraySize-1], Open, High, Low, Close);

SCString Message;
Message.Format("O: %f, H: %f, L: %f , C: %f",Open,High,Low,Close);

sc.AddMessageToLog(Message,1);
            
```

### sc.GetOHLCOfTimePeriod()

[Link](#scgetohlcoftimeperiod) - [Top](#top)

**Type**: Function

int **GetOHLCOfTimePeriod**(SCDateTime **StartDateTime**, SCDateTime **EndDateTime**, float& **Open**, float& **High**, float& **Low**, float& **Close**, float& **NextOpen**);

**sc.GetOHLCOfTimePeriod()** returns the Open, High, Low, Close and NextOpen of the period of time in an Intraday chart specified by the **StartDateTime** and **EndDateTime** parameters.

#### Parameters

* **StartDateTime**: The starting date and time for the desired period.
* **EndDateTime**: The ending date and time for the desired period.
* **Open**: The Open for the defined time period.
* **High**: The High for the defined time period.
* **Low**: The Low for the defined time period.
* **Close**: The Close for the defined time period.
* **NextOpen**: The Open of the next bar that is present after the **EndDateTime**.

#### Example

```cpp

// In this example these are not set to anything. You will need to
// set them to the appropriate starting DateTime and ending DateTime
SCDateTime dt_StartTime
SCDateTime dt_EndTime;

float Open = 0;
float High = 0;
float Low = 0;
float Close = 0;
float NextOpen = 0;

sc.GetOHLCOfTimePeriod( dt_StartTime, dt_EndTime, Open, High, Low, Close, NextOpen); 
            
```

### sc.GetOpenHighLowCloseVolumeForDate()

[Link](#scgetopenhighlowclosevolumefordate) - [Top](#top)

int **GetOpenHighLowCloseVolumeForDate**(double **Date**, float& **r\_Open**, float& **r\_High**, float& **r\_Low**, float& **r\_Close**, float& **r\_Volume**);

The sc.GetOpenHighLowCloseVolumeForDate function returns the Open, High, Low, Close and Volume values for the specified trading day **Date**.

This function is affected by the chart [Session Times](SessionTimes.md) when determining the specific date-time range for these values.

This function returns 1 if it is successful or 0 if an error was encountered or the date is not found.

#### Parameters

* **r\_Open**: The Open for the defined date.
* **r\_High**: The High for the defined date.
* **r\_Low**: The Low for the defined date.
* **r\_Close**: The Close for the defined date.
* **r\_Volume**: The Volume for the defined date.

### sc.GetOrderByIndex()

[Link](#scgetorderbyindex) - [Top](#top)

Refer to the [sc.GetOrderByIndex()](ACSILTrading.md#getorderbyindex) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetOrderByOrderID()

[Link](#scgetorderbyorderid) - [Top](#top)

Refer to the [sc.GetOrderByOrderID()](ACSILTrading.md#getorderbyorderid) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetOrderFillArraySize()

[Link](#scgetorderfillarraysize) - [Top](#top)

Refer to the [sc.GetOrderFillArraySize()](ACSILTrading.md#scgetorderfillarraysize) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetOrderFillEntry()

[Link](#scgetorderfillentry) - [Top](#top)

Refer to the [sc.GetOrderFillEntry()](ACSILTrading.md#scgetorderfillentry) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

#### sc.GetOrderForSymbolAndAccountByIndex()

[Link](#scgetorderforsymbolandaccountbyindex) - [Top](#top)

Refer to the [sc.GetOrderForSymbolAndAccountByIndex()](ACSILTrading.md#scgetorderforsymbolandaccountbyindex) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetParentOrderIDFromAttachedOrderID()

[Link](#scgetparentorderidfromattachedorderid) - [Top](#top)

Refer to the [sc.GetParentOrderIDFromAttachedOrderID()](ACSILTrading.md#scgetparentorderidfromattachedorderid) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetPersistentDouble()

[Link](#scgetpersistentdouble) - [Top](#top)

### sc.SetPersistentDouble()

[Link](#scsetpersistentdouble) - [Top](#top)

double& **GetPersistentDouble**(int **Key**);

void **SetPersistentDouble**(int **Key**, double **Value**);

Refer to the common [Persistent Variable Functions](#persistentvariablefunctions) documentation.

### sc.GetPersistentDoubleFast()

[Link](#scgetpersistentdoublefast) - [Top](#top)

double& **GetPersistentDoubleFast**(int32\_t **Index**);

Refer to the common [Fast Persistent Variable Functions](#fastpersistentvariablefunctions) documentation.

### sc.GetPersistentDoubleFromChartStudy()

[Link](#scgetpersistentdoublefromchartstudy) - [Top](#top)

### sc.SetPersistentDoubleForChartStudy()

[Link](#scsetpersistentdoubleforchartstudy) - [Top](#top)

double& **GetPersistentDoubleFromChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**);

void **SetPersistentDoubleForChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**, double **Value**);

Refer to the common [Chart Study Persistent Variable Functions](#chartstudypersistentvariablefunctions) documentation.

### sc.GetPersistentFloat()

[Link](#scgetpersistentfloat) - [Top](#top)

### sc.SetPersistentFloat()

[Link](#scsetpersistentfloat) - [Top](#top)

float& **GetPersistentFloat**(int **Key**);

void **SetPersistentFloat**(int **Key**, float **Value**);

Refer to the common [Persistent Variable Functions](#persistentvariablefunctions) documentation.

### sc.GetPersistentFloatFast()

[Link](#scgetpersistentfloatfast) - [Top](#top)

float& **GetPersistentFloatFast**(int32\_t **Index**);

Refer to the common [Fast Persistent Variable Functions](#fastpersistentvariablefunctions) documentation.

### sc.GetPersistentFloatFromChartStudy()

[Link](#scgetpersistentfloatfromchartstudy) - [Top](#top)

### sc.SetPersistentFloatForChartStudy()

[Link](#scsetpersistentfloatforchartstudy) - [Top](#top)

float& **GetPersistentFloatFromChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**);

void **SetPersistentFloatForChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**, float **Value**);

Refer to the common [Chart Study Persistent Variable Functions](#chartstudypersistentvariablefunctions) documentation.

### sc.GetPersistentInt()

[Link](#scgetpersistentint) - [Top](#top)

### sc.SetPersistentInt()

[Link](#scsetpersistentint) - [Top](#top)

int& **GetPersistentInt**(int **Key**);

void **SetPersistentInt**(int **Key**, int **Value**);

Refer to the common [Persistent Variable Functions](#persistentvariablefunctions) documentation.

### sc.GetPersistentInt64()

[Link](#scgetpersistentint64) - [Top](#top)

### sc.SetPersistentInt64()

[Link](#scsetpersistentint64) - [Top](#top)

\_\_int64& **GetPersistentInt64**(int **Key**);

void **SetPersistentInt64**(int **Key**, \_\_int64 **Value**);

Refer to the common [Persistent Variable Functions](#persistentvariablefunctions) documentation.

### sc.GetPersistentInt64FromChartStudy()

[Link](#scgetpersistentint64fromchartstudy) - [Top](#top)

### sc.SetPersistentInt64ForChartStudy()

[Link](#scsetpersistentint64forchartstudy) - [Top](#top)

\_\_int64& **GetPersistentInt64FromChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**);

void **SetPersistentInt64ForChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**, \_\_int64 **Value**);

Refer to the common [Chart Study Persistent Variable Functions](#chartstudypersistentvariablefunctions) documentation.

### sc.GetPersistentIntFast()

[Link](#scgetpersistentintfast) - [Top](#top)

int& **GetPersistentIntFast**(int32\_t **Index**);

Refer to the common [Fast Persistent Variable Functions](#fastpersistentvariablefunctions) documentation.

### sc.GetPersistentIntFromChartStudy()

[Link](#scgetpersistentintfromchartstudy) - [Top](#top)

### sc.SetPersistentIntForChartStudy()

[Link](#scsetpersistentintforchartstudy) - [Top](#top)

int& **GetPersistentIntFromChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**);

void **SetPersistentIntForChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**, int **Value**);

Refer to the common [Chart Study Persistent Variable Functions](#chartstudypersistentvariablefunctions) documentation.

### sc.GetPersistentPointer()

[Link](#scgetpersistentpointer) - [Top](#top)

### sc.SetPersistentPointer()

[Link](#scsetpersistentpointer) - [Top](#top)

void\*& **GetPersistentPointer**(int **Key**);

void **SetPersistentPointer**(int **Key**, void\* **Value**);

Refer to the common [Persistent Variable Functions](#persistentvariablefunctions) documentation.

### sc.GetPersistentPointerFromChartStudy()

[Link](#scgetpersistentpointerfromchartstudy) - [Top](#top)

### sc.SetPersistentPointerForChartStudy()

[Link](#scsetpersistentpointerforchartstudy) - [Top](#top)

void\*& **GetPersistentPointerFromChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**);

void **SetPersistentPointerForChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**, void\* **Value**);

Refer to the common [Chart Study Persistent Variable Functions](#chartstudypersistentvariablefunctions) documentation.

### sc.GetPersistentSCDateTime()

[Link](#scgetpersistentscdatetime) - [Top](#top)

### sc.SetPersistentSCDateTime()

[Link](#scsetpersistentscdatetime) - [Top](#top)

SCDateTime& **GetPersistentSCDateTime**(int **Key**);

void **SetPersistentSCDateTime**(int **Key**, SCDateTime **Value**);

Refer to the common [Persistent Variable Functions](#persistentvariablefunctions) documentation.

### sc.GetPersistentSCDateTimeFast()

[Link](#scgetpersistentscdatetimefast) - [Top](#top)

SCDateTime& **GetPersistentSCDateTimeFast**(int32\_t **Index**);

Refer to the common [Fast Persistent Variable Functions](#fastpersistentvariablefunctions) documentation.

### sc.GetPersistentSCDateTimeFromChartStudy()

[Link](#scgetpersistentscdatetimefromchartstudy) - [Top](#top)

### sc.SetPersistentSCDateTimeForChartStudy()

[Link](#scsetpersistentscdatetimeforchartstudy) - [Top](#top)

SCDateTime& **GetPersistentSCDateTimeFromChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**);

void **SetPersistentSCDateTimeForChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**, SCDateTime **Value**);

Refer to the common [Chart Study Persistent Variable Functions](#chartstudypersistentvariablefunctions) documentation.

### sc.GetPersistentSCString()

[Link](#scgetpersistentscstring) - [Top](#top)

### sc.SetPersistentSCString()

[Link](#scsetpersistentscstring) - [Top](#top)

[SCString](ACSILProgrammingConcepts.md#workingwithtextstrings)& **GetPersistentSCString**(int **Key**);

void **SetPersistentSCString**(int **Key**, [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings) **Value**);

Refer to the common [Persistent Variable Functions](#persistentvariablefunctions) documentation.

### sc.GetPersistentSCStringFromChartStudy()

[Link](#getpersistentscstringfromchartstudy) - [Top](#top)

SCDateTime& **GetPersistentSCStringFromChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**);

void **setPersistentSCStringForChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**, SCDateTime **Value**);

Refer to the common [Chart Study Persistent Variable Functions](#chartstudypersistentvariablefunctions) documentation.

### sc.GetPointOfControlAndValueAreaPricesForBar()

[Link](#scgetpointofcontrolandvalueareapricesforbar) - [Top](#top)

**Type**: Function

int **GetPointOfControlAndValueAreaPricesForBar**(int **BarIndex**, double& **r\_PointOfControl**, double& **r\_ValueAreaHigh**, double& **r\_ValueAreaLow**, float **ValueAreaPercentage**);

The **sc.GetPointOfControlAndValueAreaPricesForBar()** function gets the price values for the Point of Control, Value Area High, and Value Area Low into their respective variables, for the given BarIndex and ValueAreaPercentage.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex)
* **r\_PointOfControl**: The returned price level of the Point of Control for the given BarIndex.
* **r\_ValueAreaHigh**: The returned price level of the Value Area High for the **ValueAreaPercentage**.
* **r\_ValueAreaLow**: The returned price level of the Value Area Low for the **ValueAreaPercentage**.
* **ValueAreaPercentage**: The Value Area Percentage to be used for the Value Area Calculations. This number is to be entered as a percentage value (example 80.5).

### sc.GetPointOfControlPriceVolumeForBar()

[Link](#scgetpointofcontrolpricevolumeforbar) - [Top](#top)

**Type**: Function

void **GetPointOfControlPriceVolumeForBar**(int **BarIndex**, s\_VolumeAtPriceV2& **VolumeAtPrice**);

The **sc.GetPointOfControlPriceVolumeForBar** function fills out a s\_VolumeAtPriceV2 structure object passed to the function for the Point of Control price level based on volume for the chart bar at the index specified by **BarIndex**.

It is necessary to set **sc.MaintainVolumeAtPriceData = 1;** in the **sc.SetDefaults** code block at the top of the function in order to have the volume at price data maintained so that this function returns valid data.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex)
* **VolumeAtPrice**: A s\_VolumeAtPriceV2 structure that is filled in with the volume data at the price level of the Point Of Control of the chart bar.

#### Example

```cpp

s_VolumeAtPriceV2 VolumeAtPrice;
sc.GetPointOfControlPriceVolumeForBar(sc.Index, VolumeAtPrice);           
            
```

### sc.GetProfitManagementStringForTradeAccount()

[Link](#scgetprofitmanagementstringfortradeaccount) - [Top](#top)

**Type**: Function

void **GetProfitManagementStringForTradeAccount**(SCString& **r\_TextString**);

The **sc.GetProfitManagementStringForTradeAccount** function returns the Profit/Loss Status text string for the Trade Account the chart is set to, from the [Global Profit/Loss Management](GlobalProfitLossManagement.md), into the variable **r\_TextString**.

For an example of how this function is used, refer to the study function **scsf\_TradingProfitManagementStatus**  in the **/ACS\_Source/studies5.cpp** file in the Sierra\_ Chart installation folder.

#### Parameters

* **r\_TextString**: The returned Profit/Loss Status text.

### sc.GetRealTimeSymbol()

[Link](#scgetrealtimesymbol) - [Top](#top)

**Type**: Function

SCString& **GetRealTimeSymbol**();

The **sc.GetRealTimeSymbol()** function returns the trading symbol that is set for the chart on which the study that contains this function is added. The trading symbol will be the **Trade and Current Quote** symbol if one is entered, otherwise it will return the **Symbol**.

#### Parameters

* This function has no parameters

### sc.GetRecentAskVolumeAtPrice() / sc.GetRecentBidVolumeAtPrice()

[Link](#scgetrecentaskvolumeatprice) - [Top](#top)

**Type**: Function

unsigned int **GetRecentAskVolumeAtPrice**(float **Price**);

unsigned int **GetRecentBidVolumeAtPrice**(float **Price**);

The **sc.GetRecentAskVolumeAtPrice** and **sc.GetRecentBidVolumeAtPrice** functions return the recent Ask or Bid volume respectively, for the given **Price** parameter. This is one of the market data columns on the Chart/Trade DOM. This data is maintained from the real-time market data and also during a chart replay.

For a description of this particular market data column, refer to [Recent Bid Volume/Recent Ask Volume](GlobalTradeSettings.md#columndescriptionrecentbidvolume).

For these functions to return a volume value, it is necessary **Trade >> Trading Chart DOM On** is enabled for one of the charts for the Symbol. And the **Recent Bid/Ask Volume** columns need to be added. Refer to [Customize Trade/Chart DOM Columns and Descriptions](GlobalTradeSettings.md#chartdomcolumndescriptions) for instructions.

#### Parameters

* [Price](#commonfunctionparameterdescriptionsprice)

#### Example

```cpp

 unsigned int RecentAskVolume = sc.GetRecentAskVolumeAtPrice(sc.LastTradePrice);
            
```

### sc.GetReplayHasFinishedStatus()

[Link](#scgetreplayhasfinishedstatus) - [Top](#top)

**Type**: Function

int **GetReplayHasFinishedStatus**();

When a [Chart Replay](ReplayChart.md) has finished in a chart, at that time the study function will be called one more time and you can check that it has finished, by calling the **sc.GetReplayHasFinishedStatus** function.

The return value of this function will be 1 if the replay has just finished. If it is 0, then the replay has not finished or the finished state has been cleared. A return value of 1 is only going to be provided for one chart calculation.

#### Parameters

* This function has no parameters

### sc.GetReplayStatusFromChart()

[Link](#scgetreplaystatusfromchart) - [Top](#top)

**Type**: Function

int32\_t **GetReplayStatusFromChart**(int **ChartNumber**);

The **sc.GetReplayStatusFromChart** function returns one of the following values indicating the replay status for the specified Chart Number.

* REPLAY\_STOPPED = 0
* REPLAY\_RUNNING = 1
* REPLAY\_PAUSED = 2

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

### sc.GetSelectedUserDrawnDrawingFromChart()

[Link](#scgetselecteduserdrawndrawingfromchart) - [Top](#top)

**Type**: Function

int32\_t **GetSelectedUserDrawnDrawingFromChart**(const int **ChartNumber**, s\_UseTool& **r\_ACSILChartDrawing**);

The **sc.GetSelectedUserDrawnDrawingFromChart()** function fills in an s\_UseTool structure for a selected drawing on another chart.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **r\_ACSILChartDrawing**: A reference to an s\_UseTool structure.

### sc.GetSessionTimesFromChart()

[Link](#scgetsessiontimesfromchart) - [Top](#top)

**Type**: Function

int **GetSessionTimesFromChart**(const int **ChartNumber**, n\_ACSIL::s\_ChartSessionTimes& **r\_ChartSessionTimes**);

The **sc.GetSessionTimesFromChart()** function sets the chart session times in **r\_ChartSessionTimes** for the chart defined by **ChartNumber**.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* **r\_ChartSessionTimes**: A reference to an s\_ChartSessionTimes structure that contains the session times for the given chart. The s\_ChartSessionTimes members are the following:
  + SCDateTime StartTime
  + SCDateTime EndTime
  + SCDateTime EveningStartTime
  + SCDateTime EveningEndTime
  + int UseEveningSessionTimes
  + int NewBarAtSessionStart
  + int LoadWeekendDataSetting

### sc.GetSheetCellAsDouble()

[Link](#scgetsheetcellasdouble) - [Top](#top)

**Type**: Function

int **GetSheetCellAsDouble**(void\*  **SheetHandle**, const int **Column**, const int **Row**, double& **r\_CellValue**);

The **sc.GetSheetCellAsDouble()** function places the value of the requested Spreadsheet Sheet Cell in the double variable **r\_CellValue**.

If the cell does not contain a value, then this function returns a value of **0**. Otherwise, it returns a value of **1**.

#### Parameters

* **SheetHandle**: The handle of the Spreadsheet Sheet as returned by the [sc.GetSpreadsheetSheetHandleByName()](#scgetspreadsheetsheethandlebyname) function.
* **Column**: The column number for the Sheet Cell to get the value from. This is a zero-based array, so column B in the Sheet would be a value of 1.
* **Row**: The row number for the Sheet Cell to get the value from. This is a zero-based array, so row 2 in the Sheet would be a value of 1.
* **r\_CellValue**: A reference to a double variable that receives the value of the Sheet Cell.

Also refer to the following functions: [sc.SetSheetCellAsDouble()](#scsetsheetcellasdouble), [sc.GetSheetCellAsString()](#scgetsheetcellasstring), [sc.SetSheetCellAsString()](#scsetsheetcellasstring), [sc.GetSpreadsheetSheetHandleByName()](#scgetspreadsheetsheethandlebyname).

#### Example

```cpp

    const char* SheetCollectionName = "ACSILInteractionExample";

    const char* SheetName = "Sheet1";

    void* SheetHandle = sc.GetSpreadsheetSheetHandleByName(SheetCollectionName, SheetName, false);

    // Get the result from cell B4. Column and row indexes are zero-based.
    double CellValue = 0.0;
    sc.GetSheetCellAsDouble(SheetHandle, 1, 3, CellValue);
            
```

### sc.GetSheetCellAsString()

[Link](#scgetsheetcellasstring) - [Top](#top)

**Type**: Function

int **GetSheetCellAsString**(void\* **SheetHandle**, const int **Column**, const int **Row**, SCString& **r\_CellString**);

The **sc.GetSheetCellAsString()** function places the value of the requested Spreadsheet Sheet Cell in the SCString variable **r\_CellValue**.

If the cell does not contain a value, then this function returns a value of **0**. Otherwise, it returns a value of **1**.

#### Parameters

* **SheetHandle**: The handle of the Spreadsheet Sheet as returned by the [sc.GetSpreadsheetSheetHandleByName()](#scgetspreadsheetsheethandlebyname) function.
* **Column**: The column number for the Sheet Cell to get the value from. This is a zero-based array, so column B in the Sheet would be a value of 1.
* **Row**: The row number for the Sheet Cell to get the value from. This is a zero-based array, so row 2 in the Sheet would be a value of 1.
* **r\_CellString**: A reference to an SCString variable that receives the value of the Sheet Cell.

Also refer to the following functions: [sc.GetSheetCellAsDouble()](#scgetsheetcellasdouble), [sc.SetSheetCellAsDouble()](#scsetsheetcellasdouble), [sc.SetSheetCellAsString()](#scsetsheetcellasstring), [sc.GetSpreadsheetSheetHandleByName()](#scgetspreadsheetsheethandlebyname).

#### Example

```cpp

const char* SheetCollectionName = "ACSILInteractionExample";

const char* SheetName = "Sheet1";

void* SheetHandle = sc.GetSpreadsheetSheetHandleByName(SheetCollectionName, SheetName, false);

// Get the text from cell B6, if it exists, and add it to the message log.
SCString CellString;
if (sc.GetSheetCellAsString(SheetHandle, 1, 5, CellString))
    sc.AddMessageToLog(CellString, 0);
            
```

### sc.GetSpreadsheetColumnAndRowIndexesFromCellReference()

[Link](#scgetspreadsheetcolumnandrowindexesfromcellreference) - [Top](#top)

**Type**: Function

int32\_t **GetSpreadsheetColumnAndRowIndexesFromCellReference**(const SCString& **CellReference**, int\* **p\_ColumnIndex**, int\* **p\_RowIndex**);

The **sc.GetSpreadsheetColumnAndRowIndexesFromCellReference()** function takes a cell parameter as a string and gives a pointer to the Column Index (p\_ColumnIndex) and Row Index (p\_RowIndex) for that cell.

#### Parameters

* **CellReference**: An SCString of the spreadsheet cell.
* **p\_ColumnIndex**: An integer pointer to the column of the given cell.
* **p\_RowIndex**: An integer point to the row of the given cell.

### sc.GetSpreadsheetSheetHandleByIndex()

[Link](#scgetspreadsheetsheethandlebyindex) - [Top](#top)

**Type**: Function

void\* **GetSpreadsheetSheetHandleByIndex**(const char\* **SheetCollectionName**, const int **SheetIndex**);

The **sc.GetSpreadsheetSheetHandleByIndex()** function returns a pointer to the handle for the given spreadsheet and sheet.

#### Parameters

* **SheetCollectionName**: Either the complete path and file extension for the Spreadsheet, or just the name of the spreadsheet file itself without the extension if the Spreadsheet is located in the Sierra Chart [Data Files Folder](GeneralSettings.md#datafilesfolder).
* **SheetIndex**: The index of the desired sheet within the sheet collection.

### sc.GetSpreadsheetSheetHandleByName()

[Link](#scgetspreadsheetsheethandlebyname) - [Top](#top)

**Type**: Function

void\* **GetSpreadsheetSheetHandleByName**(const char\* **SheetCollectionName**, const char\* **SheetName**, const int **CreateSheetIfNotExist**);

The **GetSpreadsheetSheetHandleByName()** function returns a pointer to the Spreadsheet Handle for the given **SheetCollectionName** and **SheetName**.

#### Parameters

* **SheetCollectionName**: Either the complete path and file extension for the Spreadsheet, or just the name of the spreadsheet file itself without the extension if the Spreadsheet is located in the Sierra Chart [Data Files Folder](GeneralSettings.md#datafilesfolder).
* **SheetName**: The Sheet name as found within the Spreadsheet.
* **CreateSheetIfNotExist**: If this value is non-zero (true), then the specified SheetName will be created if it does not already exist within the SheetCollectionName.

Also refer to the following functions: [sc.GetSheetCellAsDouble()](#scgetsheetcellasdouble), [sc.SetSheetCellAsDouble()](#scsetsheetcellasdouble), [sc.GetSheetCellAsString()](#scgetsheetcellasstring), [sc.SetSheetCellAsString()](#scsetsheetcellasstring).

#### Example

```cpp

void* SheetHandle = sc.GetSpreadsheetSheetHandleByName(SheetCollectionName, SheetName, false);
            
```

### sc.GetStandardError()

[Link](#scgetstandarderror) - [Top](#top)

**Type**: Intermediate Study Calculation Function

double **GetStandardError**(SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

double **GetStandardError**(SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.GetStandardError()** function calculates the Standard Error. The result is returned as a double precision float value.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

double StandardErrorValue = sc.GetStandardError(sc.BaseDataIn[SC_LAST], Length.GetInt());
            
```

### sc.GetStartDateTimeForTradingDate()

[Link](#scgetstartdatetimefortradingdate) - [Top](#top)

**Type**: Function

double **GetStartDateTimeForTradingDate**(int **TradingDate**);

The **sc.GetStartDateTimeForTradingDate()** function returns a Date-Time as a double which can be assigned to an SCDateTime variable, which is the starting Date and Time of the trading session that the given **TradingDate** is within. **TradingDate** is considered the date of the trading day independent of the actual date of trading. For example, trading during the evening session the day before next days Day session will have a TradingDate 1 day ahead of the actual date of trading. Therefore, if a trading session spans over midnight according to the Session Times of the chart the study is applied to, then the Date of the returned Date-Time will always be one less than the given **TradingDate**.

#### Example

```cpp

SCDateTime TradingDate;
SCDateTime SessionStartDateTime = sc.GetStartDateTimeForTradingDate(TradingDate);
            
```

### sc.GetStartDateTimeOfDaySessionForTradingDayDate()

[Link](#scgetstartdatetimeofdaysessionfortradingdaydate) - [Top](#top)

**Type**: Function

SCDateTime **GetStartDateTimeOfDaySessionForTradingDayDate**(const SCDateTime& **TradingDate**);

The **sc.GetStartDateTimeOfDaySessionForTradingDayDate()** function returns an SCDateTime of the Date and Time of the start of the Day Trading Session associated with the given TradingDate.

#### Parameters

* **TradingDate**: An SCDateTime variable that defines the Trading Date of interest.

### sc.GetStartOfPeriodForDateTime()

[Link](#scgetstartofperiodfordatetime) - [Top](#top)

**Type**: Function

SCDateTime **GetStartOfPeriodForDateTime**(SCDateTime **DateTime**, unsigned int **TimePeriodType**, int **TimePeriodLength**, int **PeriodOffset**, int **NewPeriodAtBothSessionStarts**);

The **sc.GetStartOfPeriodForDateTime()** function gets the beginning of a time period of a length specified by the **TimePeriodType** and **TimePeriodLength** parameters, for a given Date-Time.

The start of a time period will always be aligned to the session Start Time in the case of Intraday charts. For periods based on more than one day, the starting reference point will be 1950-1-1. For periods based on weeks, the start will be either Sunday or Monday depending upon the setting of **Global Settings >> General Settings** **>> General >> Data >> Use Monday as Start of Week instead of Sunday**. For months, the start will be the first day of the month. For years, the start will be January 1.

The specified time length, will organize time into blocks of the specified length. For example, if the specified time length is 30 minutes, time will be organized this way, assuming the Session Times in **Chart >> Chart Settings** use a Start Time that begins at the beginning of an hour: **|9:30--------------|10:00--------------|10:30--------------**. Given a **DateTime** with a time of 10:07, this function will return 10:00 and the Date of **DateTime**, since it falls within that section. The return type is an [SCDateTime](SCDateTime.md).

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime): The Date-Time value used to return the starting Date-Time of the time period that it is contained within.
* **TimePeriodType**: The type of time period. This can be any of:
  + TIME\_PERIOD\_LENGTH\_UNIT\_MINUTES
  + TIME\_PERIOD\_LENGTH\_UNIT\_DAYS
  + TIME\_PERIOD\_LENGTH\_UNIT\_WEEKS
  + TIME\_PERIOD\_LENGTH\_UNIT\_MONTHS
  + TIME\_PERIOD\_LENGTH\_UNIT\_YEARS
* **TimePeriodLength**: The number of units specified with **TimePeriodType**. For example if you want 1 Day, then you will set this to 1 and **TimePeriodType** to TIME\_PERIOD\_LENGTH\_UNIT\_DAYS.
* **PeriodOffset**: This normally should be set to 0. When it is set to -1, the function will return the prior block of time which is before the block of time that **DateTime** is within. When it is set to +1, the function will return next block of time which is after the block of time that **DateTime** is within. Any positive or negative nonzero number can be used to shift the period forward or backward. For example, +2 will get 2 periods forward from the block of time that **DateTime** is within.
* **NewPeriodAtBothSessionStarts** : When this is set to 1 and you have defined and enabled **Evening Session** times in **Chart >> Chart Settings** for an Intraday Chart, **TimePeriodType** is set to **TIME\_PERIOD\_LENGTH\_UNIT\_DAYS**, **TimePeriodLength** is set to 1, a new period will also begin at the **Session Times >> Start Time** in addition to the **Session Times >> Evening Start Time**. Otherwise, a new period only begins at the **Session Times >> Evening Start Time**.

#### Example

For an example, refer to the **scsf\_PivotPointsVariablePeriod** function in the /ACS\_Source folder in the folder that Sierra Chart is installed to.

### sc.GetStudyArray()

[Link](#scgetstudyarray) - [Top](#top)

**Type**: Function

**GetStudyArray**(int **StudyNumber**, int **StudySubgraphNumber**, SCFloatArrayRef **SubgraphArray**);

It is recommended that you use the [sc.GetStudyArrayUsingID](#scgetstudyarrayusingid) function. It is a newer function which replaces this function.

**sc.GetStudyArray()** works similar to the **[sc.GetChartArray()](#scgetchartarray)** function. It gets a sc.Subgraph[].Data array from another study on a chart. This way you can use the data from other studies on the same chart as your Advanced Custom Study function is on. The **StudyNumber** is 1-based, where 1 refers to the first study on the chart. If you specify 0 for **StudyNumber**, then this function will refer to the main price graph of the chart your study instance is applied to. The **StudySubgraphNumber** is 1-based and refers to a Subgraph of the study, where 1 is the first subgraph.

Refer to the **scsf\_GetStudyArrayExample()** function in the **studies.cpp** file inside the ACS\_Source folder inside of the Sierra Chart installation folder for example code to work with this function. When calling this function, it fills in the **SubgraphArray** parameter. If the function fails to get the requested study array for any reason, **SubgraphArray** will be empty and indicated by **SubgraphArray.GetArraySize()** equaling 0.

A reason you would want to access studies on a chart rather than internally calculating them and putting the results into sc.Subgraph[].Data[] or Extra Arrays, is so that you can see the studies on the chart and allow the inputs to be easily adjusted by the user. This saves memory and calculations if the studies that you are working with internally in your study are needed to be viewed on the chart anyway.

You need to set the [Calculation Precedence](ACSIL_Members_Variables_And_Arrays.md#sccalculationprecedence) to **LOW\_PREC\_LEVEL**, in the [sc.SetDefaults](ACSIL_Members_Variables_And_Arrays.md#scsetdefaults) code block when using this function. Otherwise, you may get an array that has a size of zero and is empty. By setting the calculation precedence to LOW\_PREC\_LEVEL, you ensure that your custom study will get calculated after other studies on the chart. This will ensure you get an array filled with up to date values.

#### Parameters

* **StudyNumber**: The 1-based number for the study on the chart, where 1 refers to the first study on the specified chart. If you specify 0 for **StudyNumber**, then this function will refer to the main price graph of the chart.
* **StudySubgraphNumber**: The 1-based number for the subgraph in the study, where 1 is the first Subgraph.
* **SubgraphArray**: This will be filled in with the found data.

#### Example

```cpp

if (sc.SetDefaults)
{
    sc.CalculationPrecedence = LOW_PREC_LEVEL;
    return;
}

SCFloatArray SubgraphArray;

// Get the third (3) Subgraph data array from the second (2) study
sc.GetStudyArray(2, 3, SubgraphArray);

if (SubgraphArray.GetArraySize() == 0)
{
    return; // The SubgraphArray may not exist or is empty. Either way we can not do anything with it.
}
            
```

### sc.GetStudyArrayFromChart()

[Link](#scgetstudyarrayfromchart) - [Top](#top)

**Type**: Function

**GetStudyArrayFromChart**(int **ChartNumber**, int **StudyNumber**, int **StudySubgraphNumber**, SCFloatArrayRef **SubgraphArray**);

**sc.GetStudyArrayFromChart()** works identically to the **[sc.GetStudyArray()](#scgetstudyarray)** function, except that it will also access studies on another chart.

It is recommended to use the [sc.GetStudyArrayFromChartUsingID](#scgetstudyarrayfromchartusingid) study instead as it references a study by its unique ID, rather than the sc.GetStudyArrayFromChart() function.

If the function is unable to get the subgraph array, the array's size will be zero (For example, **SubgraphArray.GetArraySize() == 0**).

One reason you may want to access a study from another chart is to use the results of a study which is calculated over a different time period per bar.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber): If this is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart your study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.
* **StudyNumber**: The 1-based number for the study on the chart, where 1 refers to the first study on the specified chart. If you specify 0 for **StudyNumber**, then this function will refer to the main price graph of the chart.
* **StudySubgraphNumber**: The 1-based number for the subgraph in the study, where 1 is the first Subgraph.
* **SubgraphArray**: This will be filled in with the found data.

#### Example

```cpp

SCFloatArray SubgraphArray;

// Get the subgraph number 3 data array from the study number 2 on chart number 1
sc.GetStudyArrayFromChart(1, 2, 3, SubgraphArray);

if (SubgraphArray.GetArraySize() == 0)
    return; // The SubgraphArray may not exist or is empty. Either way we can not do anything with it.
            
```

### sc.GetStudyArrayFromChartUsingID()

[Link](#scgetstudyarrayfromchartusingid) - [Top](#top)

**Type**: Function

void **GetStudyArrayFromChartUsingID**(const s\_ChartStudySubgraphValues& **ChartStudySubgraphValues**, SCFloatArrayRef **SubgraphArray**);

The **sc.GetStudyArrayFromChartUsingID()** function gets an **sc.Subgraph[].Data[]** array from another study on another chart specified with the **ChartStudySubgraphValues** parameter. The array is set into the **SubgraphArray** parameter. This function works with the **sc.Input[].GetChartStudySubgraphValues()** input function.

Note: if ChartStudySubgraphValues.ChartNumber is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart your study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.

#### Parameters

* **ChartStudySubgraphValues**:
* **SubgraphArray**:

#### Example

```cpp

SCInputRef StudySubgraphReference = sc.Input[0];

if (sc.SetDefaults)
{
    StudySubgraphReference.Name = "Study And Subgraph To Display";

    StudySubgraphReference.SetChartStudySubgraphValues(1, 1, 0);
    return;
}

SCFloatArray StudyReference;
sc.GetStudyArrayFromChartUsingID(StudySubgraphReference.GetChartStudySubgraphValues(), StudyReference);
            
```

### sc.GetStudyArraysFromChart()

[Link](#scgetstudyarraysfromchart) - [Top](#top)

**Type**: Function

**GetStudyArraysFromChart**(int **ChartNumber**, int **StudyNumber**, SCGraphData& **GraphData**);

**sc.GetStudyArraysFromChart()** is for getting all of the Subgraph arrays from a study on another chart or the same chart. A more up-to-date version of this function is the [sc.GetStudyArraysFromChartUsingID()](#scgetstudyarraysfromchartusingid) function.

One reason you may want to access a study from another chart is to use the results of a study which is calculated over a different time frame per bar.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber): If this is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart your study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.
* **StudyNumber**: This is 1-based, where 1 refers to the first study on the specified chart number. If you specify 0 for **StudyNumber**, then this function will refer to the main price graph of the chart.
* **GraphData**: An SCGraphData object.

#### Example

```cpp

int ChartNumber = 1;

// Get the study arrays from the first study in the specified chart
SCGraphData StudyData;
sc.GetStudyArraysFromChart(ChartNumber, 1, StudyData);

// Check if we got the data and then get the first subgraph array from the study data

if(StudyData.GetArraySize() == 0)
    return;

SCFloatArrayRef StudyArray = StudyData[0];

if(StudyArray.GetArraySize() == 0)
    return;
            
```

### sc.GetStudyArraysFromChartUsingID()

[Link](#scgetstudyarraysfromchartusingid) - [Top](#top)

**Type**: Function

void **GetStudyArraysFromChartUsingID**(int **ChartNumber**, int **StudyID**, SCGraphData& **GraphData**);

The **sc.GetStudyArraysFromChartUsingID()** function gets *all* of the Subgraph arrays from a study specified by the **ChartNumber** and the unique **StudyID** parameters.

The [StudyID](ACSILProgrammingConcepts.md#uniquestudyinstanceidentifiers) is the unique study identifier.

This function establishes a reference between the chart containing the study which called this function, and the chart specified by the **ChartNumber** parameter. When the chart specified by **ChartNumber** is reloaded or an historical data download completes for it, or it is fully recalculated, then the chart calling this function will be tagged for a full recalculation. In this way, the study making reference to another chart, will always be kept up to date automatically without having to do anything special.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber): If this is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart your study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **GraphData**: An SCGraphData type object.

#### Example

```cpp
 
// Define a graph data object to get all of the study data
SCGraphData StudyData;

// Get the study data from the specified chart
sc.GetStudyArraysFromChartUsingID(ChartStudyInput.GetChartNumber(), ChartStudyInput.GetStudyID(), StudyData);

//Check if the study has been found.  If it has, GetArraySize() will return the number of Subgraphs in the study.
if(StudyData.GetArraySize() == 0)
return;

// Define a reference to the first subgraph array
SCFloatArrayRef Array1 = StudyData[0];

// Check if array is not empty.
if(Array1.GetArraySize() != 0)
{
    // Get last value in array
    float LastValue = Array1[Array1.GetArraySize() - 1];
}
            
```

### sc.GetStudyArrayUsingID()

[Link](#scgetstudyarrayusingid) - [Top](#top)

**Type**: Function

int **GetStudyArrayUsingID**(unsigned int **StudyID**, unsigned int **StudySubgraphIndex**, SCFloatArrayRef **SubgraphArray**);

**sc.GetStudyArrayUsingID()** gets the specified sc.Subgraph[].Data array from a study using the study's unique identifier. These are studies that are on the same chart that your custom study is applied to.

If the study you are referencing is moved up or down in the list of **Studies to Graph** in the **Chart Studies** window for the chart, the reference still stays valid.

This function works with the [sc.Input](ACSIL_Members_scInputs.md) functions **sc.Input[].SetStudyID()** or **sc.Input[].SetStudySubgraphValues** and the related functions for getting the study ID and the study Subgraph values.

Set the [Calculation Precedence](ACSIL_Members_Variables_And_Arrays.md#sccalculationprecedence) to **LOW\_PREC\_LEVEL**, in the [sc.SetDefaults](ACSIL_Members_Variables_And_Arrays.md#scsetdefaults) code block when using this function.

Otherwise, you may get an array that has a size of zero and is empty. By setting the calculation precedence to **LOW\_PREC\_LEVEL**, you ensure that the custom study will get calculated after other studies on the chart. This will ensure the study instance receives an array filled with up to date values.

When using this function or any of the ACSIL functions for getting a study array, it is possible to get the **sc.Subgraph.Data[]** arrays of a **Spreadsheet** study on the chart. This will allow you to get any of the formula columns data (K-Z and more depending upon the setting of the **Number of Formula Columns** input). Additionally, by using the appropriate formulas in the Spreadsheete formula columns, you are able to reference other data on the Spreadsheet by having those formula column formulas reference the particular cells that you need.

**Return Value**: Returns 1 on success or 0 if the StudyID is not found or the StudySubgraphIndex parameter is outside the valid range of subgraph indexes.

For an example, refer to the **scsf\_ReferenceStudyData** function in the **/ACS\_Source/studies8.cpp** file or to the **scsf\_StudySubgraphsDifference** function in the **/ACS\_Source/studies5.cpp** file which are located in the Sierra Chart installation folder.

#### Parameters

* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **StudySubgraphIndex** parameter: This is a 0 based index indicating which Subgraph to get from the study specified by **StudyID**. These indices directly correspond to the Subgraphs listed in the [Subgraphs tab](ChartStudies.md#subgraphstab) of the Study Settings window for the study. Although this is zero-based and the Subgraphs are 1-based as they are listed. For example, Subgraph 1 (**SG1**) in the Study Settings window will have a **StudySubgraphIndex** of 0.
* **SubgraphArray**: The subgraph data array for the given Study and Subgraph.

#### Example

```cpp
 
if (sc.SetDefaults)
{
    sc.CalculationPrecedence = LOW_PREC_LEVEL;
    
    sc.Input[1].Name = "Study Reference";
    sc.Input[1].SetStudyID(1);
}

SCFloatArray StudyReference;

//Get the first (0) subgraph from the study the user has selected.

if (sc.GetStudyArrayUsingID(sc.Input[1].GetStudyID(), 0, StudyReference) > 0
    && StudyReference.GetArraySize() > 0)
{

    //Copy the study data that we retrieved using GetStudyArrayUsingID, into a subgraph data output array
    sc.Subgraph[0][sc.Index] = StudyReference[sc.Index];
}
            
```

### sc.GetStudyDataColorArrayFromChartUsingID()

[Link](#scgetstudydatacolorarrayfromchartusingid) - [Top](#top)

**Type**: Function

void **GetStudyDataColorArrayFromChartUsingID**(int **ChartNumber**, int **StudyID**, int **SubgraphIndex**, SCColorArrayRef **DataColorArray**);

The **sc.GetStudyDataColorArrayFromChartUsingID**  function is used to get the [sc.Subgraph[].DataColor](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphDataColor) array at the Subgraph index specified by **SubgraphIndex** for the study specified by the **StudyID** parameter, in the chart specified by the **ChartNumber** parameter.

The [sc.Subgraph[].DataColor](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphDataColor) array being returned, must be used by the study Subgraph for it to contain data. Otherwise, it will be empty.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [SubgraphIndex](#commonfunctionparameterdescriptionssubgraphindex)

#### Example

```cpp
       
//Example for sc.GetStudyDataColorArrayFromChartUsingID
//SCInputRef ChartStudySubgraphInput  = sc.Input[4];
//ChartStudySubgraphInput.SetChartStudySubgraphValues(1, 1, 0);

SCColorArray DataColorArray;
sc.GetStudyDataColorArrayFromChartUsingID(ChartStudySubgraphInput.GetChartNumber(), ChartStudySubgraphInput.GetStudyID(), ChartStudySubgraphInput.GetSubgraphIndex(), DataColorArray);

if (DataColorArray.GetArraySize() > 0)//size is nonzero meaning that we have gotten a valid array
{
    //Use the array for something
}
            
```

### sc.GetStudyDataStartIndexFromChartUsingID()

[Link](#scgetstudydatastartindexfromchartusingid) - [Top](#top)

**Type**: Function

int **sc.GetStudyDataStartIndexFromChartUsingID**(int **ChartNumber**, unsigned int **StudyID**);

The **sc.GetStudyDataStartIndexFromChartUsingID()** function returns the [sc.DataStartIndex](ACSIL_Members_Variables_And_Arrays.md#scdatastartindex) from the study specified by the **StudyID** parameter and the chart specified by the **ChartNumber** parameter.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetStudyDataStartIndexUsingID()

[Link](#scgetstudydatastartindexusingid) - [Top](#top)

**Type**: Function

int **GetStudyDataStartIndexUsingID**(unsigned int **StudyID**);

The **sc.GetStudyDataStartIndexUsingID()** function gets the **sc.DataStartIndex** value from another study on the same chart that your custom study is applied to, using the study's unique ID. This is for specialised purposes.

#### Example

```cpp

SCInputRef StudyReference = sc.Input[0];

sc.DataStartIndex = sc.GetStudyDataStartIndexUsingID(StudyReference.GetStudyID());
            
```

### sc.GetStudyExtraArrayFromChartUsingID()

[Link](#scgetstudyextraarrayfromchartusingid) - [Top](#top)

**Type**: Function

int **GetStudyExtraArrayFromChartUsingID**(int **ChartNumber**, int **StudyID**, int **SubgraphIndex**, int **ExtraArrayIndex**, SCFloatArrayRef **ExtraArrayRef**);

The **sc.GetStudyExtraArrayFromChartUsingID()** function is used for getting one of the [sc.Subgraph[].Arrays[][]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphArrays) on an sc.Subgraph from another study. This study can also be on another chart.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [SubgraphIndex](#commonfunctionparameterdescriptionssubgraphindex)
* **ExtraArrayIndex**: The index of the extra array to be returned.
* **ExtraArrayREf**: The data for the extra array from the other chart, study, and subgraph.

#### Example

```cpp
       
SCFloatArray ExtraArrayFromChart ; 
sc.GetStudyExtraArrayFromChartUsingID(1, 1, 0, 0, ExtraArrayFromChart); 
if (ExtraArrayFromChart.GetArraySize()>0) 
{ 

}
            
```

### sc.GetStudyIDByIndex()

[Link](#scgetstudyidbyindex) - [Top](#top)

**Type**: Function

int **GetStudyIDByIndex**(int **ChartNumber**, int **StudyIndex**);

The **sc.GetStudyIDByIndex()** function returns the unique **sc.StudyGraphInstanceID** for the study specified by the [ChartNumber](#commonfunctionparameterdescriptionschartnumber) and the one based **StudyIndex** parameters.

Setting **StudyIndex** to 0 will refer to the underlying main price graph of the chart.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **StudyIndex**: The one based index of the study in the **Studies to Graph** list in the [Chart Studies](ChartStudies.md#chartstudieswindow) window.

### sc.GetStudyIDByName()

[Link](#scgetstudyidbyname) - [Top](#top)

**Type**: Function

int **sc.GetStudyIDByName**(int **ChartNumber**, const char\* **Name**, const int **UseShortNameIfSet**);

The **sc.GetStudyIDByName()** function returns the unique **sc.StudyGraphInstanceID** for the study specified by the **Name** parameter. The study is looked up by its current name.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* **Name**: This is the name to search for. This needs to match the current name of the study which can change if using a [Short Name](ChartStudies.md#shortname).
* **UseShortNameIfSet**: Set this to 1 to compare to the set short name of the study. In which case name is matched against the study [Short Name](ChartStudies.md#shortname) which is set through the Study Settings.

### sc.GetStudyInputName()

[Link](#scgetstudyinputname) - [Top](#top)

**Type**: Function

int32\_t **GetStudyInputName**(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **InputIndex**, SCString& **r\_InputName**);

The **sc.GetStudyInputName()** function returns the name of the Input for the specified study.

Returns 1 on success or 0 on an error.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the study [Input](ChartStudies.md#settingsandinputstab)
* **r\_InputName**: The name of the Input is returned through this [string](ACSILProgrammingConcepts.md#workingwithtextstrings) variable.

#### Example

```cpp

SCString InputName;
int Result = sc.GetStudyInputName(sc.ChartNumber, 1, 0, InputName);         
            
```

### sc.GetStudyInternalIdentifier()

[Link](#scgetstudyinternalidentifier) - [Top](#top)

**Type**: Function

uint32\_t **sc.GetStudyInternalIdentifier**(int **ChartNumber**, int **StudyID**, SCString& **r\_StudyName**);

The **sc.GetStudyInternalIdentifier()** function fills in the name of the study specified by the ChartNumber and StudyID.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **r\_StudyName**: The returned study name.

### sc.GetStudyLineUntilFutureIntersection()

[Link](#scgetstudylineuntilfutureintersection) - [Top](#top)

**Type**: Function

int **GetStudyLineUntilFutureIntersection**(int **ChartNumber**, int **StudyID**, int **BarIndex**, int **LineIndex**, int& **LineIDForBar**, float **&LineValue**, int **&ExtensionLineChartColumnEndIndex)**);

The **sc.GetStudyLineUntilFutureIntersection** function is used to get the details of a line until future intersection from a study which has added one of these lines using the function [sc.AddLineUntilFutureIntersection()](#scaddlineuntilfutureintersection).

Return Value: If the line is found, 1 is returned. If the line is not found, 0 is returned.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [BarIndex](#commonfunctionparameterdescriptionsbarindex)
* **LineIndex**: The line index for the future intersection line. This is a zero-based index. The first future intersection line at a chart bar will have an index of 0.
* **LineIDForBar**: This parameter is a reference. This is the identifier of the extension line for a chart bar.
* **LineValue**: This parameter is a reference and is set to the vertical axis level at which the line is drawn at.
* **ExtensionLineChartColumnEndIndex**: This parameter is a reference. This is set to the bar index the line ends at. A value of zero means that the line has not yet intersected a future price bar.

### sc.GetStudyLineUntilFutureIntersectionByIndex()

[Link](#scgetstudylineuntilfutureintersectionbyindex) - [Top](#top)

**Type**: Function

int **GetStudyLineUntilFutureIntersectionByIndex**(int **ChartNumber**, int **StudyID**, int **Index**, int& **r\_LineIDForBar**, int& **r\_StartIndex**, float& **r\_LineValue**, int& **r\_ExtensionLineChartColumnEndIndex**);

The **sc.GetStudyLineUntilFutureIntersectionByIndex** function is used to get the details of a line until future intersection from a study which has added one of these lines using the function [sc.AddLineUntilFutureIntersection](#scaddlineuntilfutureintersection).

This function specifies the future intersection line by its zero-based index (**Index**) in the container where the lines are stored for the study. The upper bound of this parameter will be the value returned by [sc.GetNumLinesUntilFutureIntersection](#scgetnumlinesuntilfutureintersection) -1.

Return Value: If the line is found, 1 is returned. If the line is not found, 0 is returned.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [Index](#commonfunctionparameterdescriptionsindex)
* **r\_LineIDForBar**: This parameter is a reference and is an output value. Upon return it is set to the identifier of the extension line for a chart bar.
* **r\_StartIndex**: This parameter is a reference and is an output value. Upon return it is set to the starting bar index of the extension line.
* **r\_LineValue**: This parameter is a reference and is an output value. Upon return it is set to the vertical axis value at which the line is drawn.
* **r\_ExtensionLineChartColumnEndIndex**: This parameter is a reference and is an output value. Upon return it is set to the chart bar index the line ends at. A value of zero means that the line has not yet intersected a future price bar.

### sc.GetStudyName()

[Link](#scgetstudyname) - [Top](#top)

**Type**: Function

SCString **GetStudyName**(int **StudyIndex**);

**sc.GetStudyName()** returns the name of the study at the index **StudyIndex**.

#### Parameters

* **StudyIndex**: The one-based index based on the order of the studies in the **Studies to Graph** list in the Chart Studies window for the chart. The main price/base graph for the chart is a **StudyIndex** of 0.

### sc.GetStudyNameFromChart()

[Link](#scgetstudynamefromchart) - [Top](#top)

**Type**: Function

SCString **GetStudyNameFromChart**(int **ChartNumber**, int **StudyID**);

The **sc.GetStudyNameFromChart()** function gets the name of the study identified by **StudyID** from the chart specified by **ChartNumber**. **StudyID** can be 0 to get the name of the underlying main graph of the chart.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

#### Example

```cpp

SCInputRef ChartStudySubgraphReference = sc.Input[4];

int ChartNumber = ChartStudySubgraphReference.GetChartNumber();
int StudyID = ChartStudySubgraphReference.GetStudyID();

SCString StudyName = sc.GetStudyNameFromChart(ChartNumber, StudyID);
            
```

### sc.GetStudyNameUsingID()

[Link](#scgetstudynameusingid) - [Top](#top)

**Type**: Function

SCString **GetStudyNameUsingID**(unsigned int **StudyID**);

The **sc.GetStudyNameUsingID()** function gets the name of a study on the same chart that your custom study is applied to, using the study's unique ID.

#### Parameters

* [StudyID](#commonfunctionparameterdescriptionsstudyid)

#### Example

```cpp

SCInputRef StudyReference = sc.Input[3];

SCString StudyName = sc.GetStudyNameUsingID(StudyReference.GetStudyID());

sc.GraphName.Format("Avg of %s", StudyName);
            
```

### sc.GetStudyPeakValleyLine()

[Link](#scgetstudypeakvalleyline) - [Top](#top)

**Type**: Function

int **GetStudyPeakValleyLine**(int **ChartNumber**, int **StudyID**, float& **PeakValleyLinePrice**, int& **PeakValleyType**, int& **StartIndex**, int& **PeakValleyExtensionChartColumnEndIndex**, int **ProfileIndex** , int **PeakValleyIndex**);

The **sc.GetStudyPeakValleyLine()** function is used for obtaining the details about a Peak or Valley line from a study if the study supports Peak and Valley lines.

Studies that support these Peak and Valley lines are the **TPO Profile Chart** and the **Volume by Price** studies. Peak and Valley lines *cannot* be obtained for a **Volume by Price** study which uses **Visible Bars** for the **Volume Graph Period Type** Input.

This function returns 1 if a Peak or Valley line was found. It returns 0 if none were found.

For an example of how to use this function, refer to the **scsf\_GetStudyPeakValleyLineExample** function in the **/ACS\_Source/studies2.cpp** file in the ACS\_Source folder under the Sierra Chart installation folder.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **PeakValleyLinePrice**: This parameter is a reference. On return, this is the price of the Peak or Valley line that has been found according to the **ProfileIndex** and **PeakValleyIndex** parameters. It will be 0 if the line was not found.
* **PeakValleyType**: This parameter is a reference. On return, this is the type of the Peak or Valley line that has been found according to the **ProfileIndex**  and **PeakValleyIndex** parameters. It will be 0 if the line was not found. It will be set to one of the following: PEAKVALLEYTYPE\_NONE = 0, PEAKVALLEYTYPE\_PEAK = 1, PEAKVALLEYTYPE\_VALLEY =2.
* **StartIndex**: This parameter is a reference. On return, this is the start chart bar array index of the Peak or Valley line that has been found according to the **ProfileIndex** and **PeakValleyIndex** parameters. It will be 0 if the line was not found.
* **PeakValleyExtensionChartColumnEndIndex**: This parameter is a reference. On return, this is the ending chart bar array index of the Peak or Valley line that has been found according to the **ProfileIndex** and **PeakValleyIndex** parameters. It will be 0 if the line was not found. If this line extends to the very end of the chart, this variable will be set to 0. This will also be 0 in the case where the Peak or Valley line is not set to extend until future intersection.
* **ProfileIndex**: The **ProfileIndex** specifies the zero-based index of the profile to obtain the Peak or Valley line from when the **Volume by Price** or **TPO Profile Chart** consist of multiple profiles. This can be a negative number - in which case a value of -1 will reference the last profile in the chart, -2 references the second to last profile in the chart and so on.
* **PeakValleyIndex**: The **PeakValleyIndex** is the zero-based index of the Peak or Valley line within the profile to return. Start setting this to 0 and increment it until there are no longer any Peak or Valley lines obtained and then you know you have obtained them all from a particular profile in the study.

### sc.GetStudyProfileInformation

[Link](#scgetstudyprofileinformation) - [Top](#top)

**Type**:Function

int **GetStudyProfileInformation**(const int **StudyID**, const int **ProfileIndex**, n\_ACSIL::s\_StudyProfileInformation& **StudyProfileInformation**);

This function when called fills out a **StudyProfileInformation** structure of type **n\_ACSIL::s\_StudyProfileInformation** with all of the numerical details of a Volume Profile or TPO profile when using the [Volume by Price](StudiesReference.md) study or the [TPO Profile Chart](StudiesReference/TimePriceOpportunityCharts.md) study, respectively.

The members of the **n\_ACSIL::s\_StudyProfileInformation** structure are listed below.

#### Parameters

* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ProfileIndex**: The zero-based index of the Volume or TPO profile relative to the end of the chart. 0 equals the latest profile in the chart at the end or rightmost side. 1 equals the second to last profile in the chart. This needs to always be set to a positive number.
* **StudyProfileInformation**: This is a reference to a structure of type **n\_ACSIL::s\_StudyProfileInformation** which receives the information for the volume or TPO profile specified by **StudyID** and **ProfileIndex**.

#### n\_ACSIL::s\_StudyProfileInformation Members

* m\_StartDateTime
* m\_NumberOfTrades
* m\_Volume
* m\_BidVolume
* m\_AskVolume
* m\_TotalTPOCount
* m\_OpenPrice
* m\_HighestPrice
* m\_LowestPrice
* m\_LastPrice
* m\_TPOMidpointPrice
* m\_TPOMean
* m\_TPOStdDev
* m\_TPOErrorOfMean
* m\_TPOPOCPrice
* m\_TPOValueAreaHigh
* m\_TPOValueAreaLow
* m\_TPOCountAbovePOC
* m\_TPOCountBelowPOC
* m\_VolumeMidpointPrice
* m\_VolumePOCPrice
* m\_VolumeValueAreaHigh
* m\_VolumeValueAreaLow
* m\_VolumeAbovePOC
* m\_VolumeBelowPOC
* m\_POCAboveBelowVolumeImbalancePercent
* m\_VolumeAboveLastPrice
* m\_VolumeBelowLastPrice
* m\_BidVolumeAbovePOC
* m\_BidVolumeBelowPOC
* m\_AskVolumeAbovePOC
* m\_AskVolumeBelowPOC
* m\_VolumeTimesPriceInTicks
* m\_TradesTimesPriceInTicks
* m\_TradesTimesPriceSquaredInTicks
* m\_IBRHighPrice
* m\_IBRLowPrice
* m\_OpeningRangeHighPrice
* m\_OpeningRangeLowPrice
* m\_VolumeWeightedAveragePrice
* m\_MaxTPOBlocksCount
* m\_TPOCountMaxDigits
* m\_DisplayIndependentColumns
* m\_EveningSession
* m\_AverageSubPeriodRange
* m\_RotationFactor
* m\_VolumeAboveTPOPOC
* m\_VolumeBelowTPOPOC
* m\_EndDateTime
* m\_BeginIndex
* m\_EndIndex

### sc.GetStudyStorageBlockFromChart

[Link](#scgetstudystorageblockfromchart) - [Top](#top)

**Type**:Function

void\* **GetStudyStorageBlockFromChart**(int **ChartNumber**, int **StudyID**);

This function returns a pointer to the [Storage Block](ACSIL_Members_Variables_And_Arrays.md#scstorageblock) for the specified ChartNumber and StudyID.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetStudySubgraphColors()

[Link](#scgetstudysubgraphcolors) - [Top](#top)

**Type**: Function

int32\_t GetStudySubgraphColors(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **StudySubgraphNumber**, uint32\_t& **r\_PrimaryColor**, uint32\_t& **r\_SecondaryColor**, uint32\_t& **r\_SecondaryColorUsed**);

The **sc.GetStudySubgraphColors()** function gets the primary and secondary colors of a Subgraph in another study in the Chartbook along with whether the secondary color is specified to be used. The study can be in a different chart.

The **ChartNumber**, **StudyID**, and **StudySubgraphNumber** parameters should be obtained using the [sc.Input[].GetChartStudySubgraphValues](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputGetChartStudySubgraphValues) function.

The function returns 1 if the study was found. Otherwise, 0 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [StudySubgraphNumber](#commonfunctionparameterdescriptionsstudysubgraphnumber)
* **r\_PrimaryColor**: This parameter is a reference. Upon return of the function, this variable contains the primary color of the specified subgraph.
* **r\_SecondaryColor**: This parameter is a reference. Upon return of the function, this variable contains the secondary color of the specified subgraph.
* **r\_SecondaryColorUsed**: This parameter is a reference. Upon return of the function, this parameter will be set to 1 if the Secondary Color is set to be used, or 0 if it is not.

#### Example

```cpp

uint32_t PrimaryColor = 0;
uint32_t SecondaryColor = 0;    
uint32_t SecondaryColorUsed = 0;      
sc.GetStudySubgraphColors(1, 1, 0, PrimaryColor, SecondaryColor, SecondaryColorUsed);
            
```

### sc.GetStudySubgraphDrawStyle()

[Link](#scgetstudysubgraphdrawstyle) - [Top](#top)

**Type**: Function

int GetStudySubgraphDrawStyle(int **ChartNumber**, int **StudyID**, int **StudySubgraphNumber**, int& **r\_DrawStyle**);

The **sc.GetStudySubgraphDrawStyle()** function gets the Draw Style of a Subgraph in another study in the Chartbook. The study can be in a different chart.

The **ChartNumber**, **StudyID**, and **StudySubgraphNumber** parameters should be obtained using the [sc.Input[].GetChartStudySubgraphValues](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputGetChartStudySubgraphValues) function.

The function returns 1 if the study was found, otherwise 0 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [StudySubgraphNumber](#commonfunctionparameterdescriptionsstudysubgraphnumber)
* **r\_DrawStyle**: This parameter is a reference. Upon return of the function, this parameter will contain the [draw style](ACSIL_Members_scSubgraph.md#scsubgraphdrawstyle) of the given subgraph.

#### Example

```cpp

int DrawStyle = 0;            
sc.GetStudySubgraphDrawStyle(1, 1, 0, DrawStyle);
            
```

### sc.GetStudySubgraphLineStyle()

[Link](#scgetstudysubgraphlinestyle) - [Top](#top)

**Type**: Function

int32\_t GetStudySubgraphLineStyle(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **StudySubgraphNumber**, SubgraphLineStyles& **r\_LineStyle**);

The **sc.GetStudySubgraphLineStyle()** function gets the Line Style of a subgraph from the specified chart, study, and subgraph.

The function returns 1 if the study and subgraph was found, otherwise 0 is returned.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [StudySubgraphNumber](#commonfunctionparameterdescriptionsstudysubgraphnumber)
* **r\_LineStyle**: This parameter is a reference. Upon return of the function, this parameter will contain the [line style](ACSIL_Members_scSubgraph.md#scsubgraphlinestyle) defined for the given chart, study, and subgraph.

### sc.GetStudySubgraphLineWidth()

[Link](#scgetstudysubgraphlinewidth) - [Top](#top)

**Type**: Function

int32\_t GetStudySubgraphLineWidth(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **StudySubgraphNumber**, int32\_t& **r\_LineWidth**);

The **sc.GetStudySubgraphLineWidth()** function gets the line width of a subgraph from the specified chart, study and subgraph.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [StudySubgraphNumber](#commonfunctionparameterdescriptionsstudysubgraphnumber)
* **r\_LineWidth**: This parameter is a reference. Upon return of the function, this parameter contains the [line width](#) defined for the given chart, study, and subgraph.

### sc.GetStudySubgraphName

[Link](#scgetstudysubgraphname) - [Top](#top)

**Type**: Function

SCString **GetStudySubgraphName**(int **StudyID**, int **SubgraphIndex**);

The **sc.GetStudySubgraphName()** function gets the name of a Subgraph for a study on the same chart that the study instance is applied to.

The general method to easily select and determine a StudyID and SubgraphIndex is through the related study Input functions. Refer to [sc.Input[].SetStudySubgraphValues()](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputSetStudySubgraphValues).

#### Paremeters

* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [SubgraphIndex](#commonfunctionparameterdescriptionssubgraphindex)

### sc.GetStudySubgraphNameFromChart()

[Link](#scgetstudysubgraphnamefromchart) - [Top](#top)

**Type**: Function

int32\_t **GetStudySubgraphNameFromChart**(int **ChartNumber**, int **StudyID**, int **SubgraphIndex**, SCString& **r\_SubgraphName**);

The **sc.GetStudySubgraphNameFromChart()** function gets the name of a Subgraph for a study on the same or a different chart as the study instance calling this function is applied to.

There are various Inputs available to support obtaining the **ChartNumber**, **StudyID**, **SubgraphIndex** parameters through a Study Input in the user interface. Refer to [sc.Input[]](index0fb1.html?page=doc/ACSIL_Members_scInputs.html).

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [SubgraphIndex](#commonfunctionparameterdescriptionssubgraphindex)
* **r\_SubgraphName**: This parameter is a reference. Upon return of the function, this parameter will contain the name of the specified subgraph from the given chart, study, and subgraph.

### sc.GetStudySummaryCellAsDouble()

[Link](#scgetstudysummarycellasdouble) - [Top](#top)

**Type**: Function

int **GetStudySummaryCellAsDouble**(const int **Column**, const int **Row**, double& **r\_CellValue**);

The **sc.GetStudySummaryCellAsDouble** function is used to obtain the data from a cell of the [Study Summary](StudySummaryWindow.md) window as a numeric double type. The cell is specified by the row and column.

#### Parameters

* **Column**: This is a zero-based integer specifying the column index of the cell to get the numeric double from.
* **Row**: This is a zero-based integer specifying the row index of the cell to get the numeric double from.
* **r\_CellValue**: This is a reference to a double variable that receives the value from the Study Summary window.

#### Example

```cpp

double StudySummaryCellValue;
sc.GetStudySummaryCellAsDouble(5, 3, StudySummaryCellValue);
            
```

### sc.GetStudySummaryCellAsString()

[Link](#scgetstudysummarycellasstring) - [Top](#top)

**Type**: Function

int **GetStudySummaryCellAsString**(const int **Column**, const int **Row**, SCString& **r\_CellString**);

The **sc.GetStudySummaryCellAsString** function is used to obtain the data from a cell of the [Study Summary](StudySummaryWindow.md) window as a text string. The cell is specified by the row and column.

#### Parameters

* **Column**: This is a zero-based integer specifying the column index of the cell to get the text string from.
* **Row**: This is a zero-based integer specifying the row index of the cell to get the text string from.
* **r\_CellString**: This is a reference to an SCString that receives the text string from the Study Summary window.

#### Example

```cpp

SCString StudySummaryCellText;
sc.GetStudySummaryCellAsString(5, 3, StudySummaryCellText);
            
```

### sc.GetStudyVisibilityState()

[Link](#scgetstudyvisibilitystate) - [Top](#top)

**Type**: Function

int **GetStudyVisibilityState**(int **StudyID**);

The **sc.GetStudyVisibilityState()** function returns 1 if the study specified by the **StudyID** parameter is visible, or 0 if it is set to be hidden.

#### Parameters

* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.GetSummation()

[Link](#scgetsummation) - [Top](#top)

**Type**: Intermediate Study Calculation Function

float **GetSummation**(SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

float **GetSummation**(SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.GetSummation()** function calculates the sum of the values in **FloatArrayIn** over the specified **Length**. The result is returned as a single float value.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

float Summation = sc.GetSummation(sc.BaseDataIn[SC_LAST],sc.Index,10);
            
```

### sc.GetSymbolDataValue()

[Link](#scgetsymboldatavalue) - [Top](#top)

**Type**: Function

**GetSymbolDataValue**(SymbolDataValuesEnum **ValueToReturn**, const SCString& **SymbolForData** = SCString(), int **SubscribeToMarketData** = false, int **SubscribeToMarketDepth** = false);

The **sc.GetSymbolDataValue** function is used to obtain a particular data value for the specified symbol and also subscribe to market data. The data value could be for example the last trade price or the bid or ask prices. Refer to the list below.

This function also can be used during a [chart replay](ReplayChart.md) but during a chart replay, when **SymbolForData** is an empty string, not all fields of data will have valid values. When **SymbolForData** is set to a particular symbol, the fields of data always come from the connected streaming data feed and the current values are provided. In this last case they do not come from a replaying chart.

#### Parameters

* **ValueToReturn**: Refer to the SymbolDataValuesEnum list below.
* **SymbolForData**: This is an *optional symbol* to return the data value for. If it is not set, it will be the symbol of the chart the study is applied to. Also refer to [Symbol](#commonfunctionparameterdescriptionssymbol).
* **SubscribeToMarketData**: Set this to 1 to subscribe to streaming market data for the symbol of the chart or the specified symbol.
* **SubscribeToMarketDepth**: Set this to 1 to subscribe to streaming market depth data for the symbol of the chart or the specified symbol.

The following are the possible constant values to use for **ValueToReturn**. They are also listed in **/ACS\_Source/scconstants.h** file. They are an enumeration of type SymbolDataValuesEnum.

* SYMBOL\_DATA\_UNSET = 0
* SYMBOL\_DATA\_DAILY\_OPEN = 1
* SYMBOL\_DATA\_DAILY\_HIGH = 2
* SYMBOL\_DATA\_DAILY\_LOW = 3
* SYMBOL\_DATA\_DAILY\_NUMBER\_OF\_TRADES = 4
* SYMBOL\_DATA\_LAST\_TRADE\_PRICE = 5
* SYMBOL\_DATA\_LAST\_TRADE\_VOLUME = 6
* SYMBOL\_DATA\_ASK\_QUANTITY = 7
* SYMBOL\_DATA\_BID\_QUANTITY = 8
* SYMBOL\_DATA\_BID\_PRICE = 9
* SYMBOL\_DATA\_ASK\_PRICE = 10
* SYMBOL\_DATA\_CURRENCY\_VALUE\_PER\_TICK = 11
* SYMBOL\_DATA\_SETTLEMENT\_PRICE = 12
* SYMBOL\_DATA\_OPEN\_INTEREST = 13
* SYMBOL\_DATA\_DAILY\_VOLUME = 14
* SYMBOL\_DATA\_SHARES\_OUTSTANDING = 15
* SYMBOL\_DATA\_EARNINGS\_PER\_SHARE = 16
* SYMBOL\_DATA\_TICK\_DIRECTION = 17
* SYMBOL\_DATA\_LAST\_TRADE\_AT\_SAME\_PRICE = 18
* SYMBOL\_DATA\_STRIKE\_PRICE = 19
* SYMBOL\_DATA\_SELL\_ROLLOVER\_INTEREST = 20
* SYMBOL\_DATA\_PRICE\_FORMAT = 21
* SYMBOL\_DATA\_BUY\_ROLLOVER\_INTEREST = 22
* SYMBOL\_DATA\_TRADE\_INDICATOR = 23
* SYMBOL\_DATA\_LAST\_TRADE\_AT\_BID\_ASK = 24
* SYMBOL\_DATA\_VOLUME\_VALUE\_FORMAT = 25
* SYMBOL\_DATA\_TICK\_SIZE = 26
* SYMBOL\_DATA\_LAST\_TRADE\_DATE\_TIME = 27
* SYMBOL\_DATA\_ACCUMULATED\_LAST\_TRADE\_VOLUME = 28
* SYMBOL\_DATA\_LAST\_TRADING\_DATE\_FOR\_FUTURES = 29
* SYMBOL\_DATA\_TRADING\_DAY\_DATE = 30
* SYMBOL\_DATA\_LAST\_MARKET\_DEPTH\_UPDATE\_DATE\_TIME = 31
* SYMBOL\_DATA\_DISPLAY\_PRICE\_MULTIPLIER = 32
* SYMBOL\_DATA\_SETTLEMENT\_PRICE\_DATE = 33
* SYMBOL\_DATA\_DAILY\_OPEN\_PRICE\_DATE = 34
* SYMBOL\_DATA\_DAILY\_HIGH\_PRICE\_DATE = 35
* SYMBOL\_DATA\_DAILY\_LOW\_PRICE\_DATE = 36
* SYMBOL\_DATA\_DAILY\_VOLUME\_DATE = 37
* SYMBOL\_DATA\_NUMBER\_OF\_TRADES\_AT\_CURRENT\_PRICE = 38

### sc.GetSymbolDescription()

[Link](#scgetsymboldescription) - [Top](#top)

**Type**: Function

int **GetSymbolDescription**(SCString& **r\_Description**);

The **sc.GetSymbolDescription** function sets the r\_Description with the full text description, if available, for the symbol of the chart the study is on.

The function returns 1 if successful. Otherwise, 0 is returned.

#### Parameters

* **r\_Description**: This is an SCString parameter which receives the full text description if available.

### sc.GetTimeAndSales()

[Link](#scgettimeandsales) - [Top](#top)

**Type**: Function

**GetTimeAndSales**(c\_SCTimeAndSalesArray& **TSArray**);

**sc.GetTimeAndSales()** gets the Time and Sales data for the symbol of the chart that the study is on.

This data also includes Bid and Ask price and size/quantity updates as well.

Refer to any of the following functions in the folder Sierra Chart is installed to for an example to work with the **sc.GetTimeAndSales** function:

* **TimeAndSales()** in the **/ACS\_Source/studies.cpp** file.
* [scsf\_TimeAndSalesPrice()](StudiesReference.md#timeandsalesprice) in the **/ACS\_Source/studies.cpp** file.
* [scsf\_TimeAndSalesVolume()](StudiesReference.md#timeandsalesvolume) in the **/ACS\_Source/studies.cpp** file.
* [scsf\_TimeAndSalesTime()](StudiesReference.md#timeandsalestime) in the **/ACS\_Source/studies.cpp** file.
* **scsf\_TimeAndSalesIterationExample**  in the **/ACS\_Source/studies5.cpp** file.

The possible values of the **Type** member of the **s\_TimeAndSales** structure are listed below:

1. **SC\_TS\_MARKER**: This indicates a gap in the time and sales data.
2. **SC\_TS\_BID**: This is a trade and it is considered to have occurred at Bid price or lower.
3. **SC\_TS\_ASK**: This is a trade and it is considered to have occurred at Ask price or higher.
4. **SC\_TS\_BIDASKVALUES**: This is a Bid and Ask quote data update only.

The possible values of the **UnbundledTradeIndicator** member of the **s\_TimeAndSales** structure are listed below. These values only apply when using the **Sierra Chart Exchange Data Feed** and only for CME symbols.

1. **UNBUNDLED\_TRADE\_NONE**: The trade is not part of a bundled trade.
2. **FIRST\_SUB\_TRADE\_OF\_UNBUNDLED\_TRADE**: This is the first trade in a larger trade consisting of multiple sub trades.
3. **LAST\_SUB\_TRADE\_OF\_UNBUNDLED\_TRADE**: This is the last trade in a larger trade consisting of multiple sub trades.

For the complete definition of the **s\_TimeAndSales** structure members, refer to the **/ACS\_Source/sierrachart.h** file in the Sierra Chart installation folder.

The **s\_TimeAndSales::Price, s\_TimeAndSales::Bid, s\_TimeAndSales::Ask** price related members in some cases need to be multiplied by the [sc.RealTimePriceMultiplier](ACSIL_Members_Variables_And_Arrays.md#screaltimepricemultiplier) multiplier variable. As a general rule, it is best practice to always apply the multiplier in case it is needed.

This function also gets all Bid, Ask, Bid Size, and Ask Size data received from the data feed.

When iterating through the Time and Sales data, to only process those records which are trades, you need to compare the s\_TimeAndSales::Type member to SC\_TS\_BID and SC\_TS\_ASK and only process records with these types.

For Time and Sales related settings, select **Global Settings >> Data/Trade Service Settings** on the menu. Refer to [Number of Stored Time and Sales Records](DataSourceSettings.md#storedtimesalesrecords). This setting controls the maximum Time and Sales records you will receive when calling **sc.GetTimeAndSales**.

After changing this setting, you need to reconnect to the data feed using the Disconnect and Connect commands on the **File** menu. You will only be able to get Time and Sales data when there is active trading activity for a symbol. It is only maintained during a Sierra Chart session. When you restart Sierra Chart, this data is lost.

The [Combine Records](TimeandSalesWindow.md#combinerecordsdonotcombine) options in the Time and Sales window settings for the chart, has no effect on the Time and Sales records obtained with the **sc.GetTimeAndSales**function.

Every Time and Sales record has a unique sequence number (**s\_TimeAndSales::Sequence** member) internally calculated by a Sierra Chart instance. This number is not reset when reconnecting to the data feed. The only time it is reset back to 1, is when Sierra Chart is restarted. In that case, Time and Sales data is lost. This unique sequence number is used to determine what Time and Sales records the study function has already processed and what records it needs to process.

In the case of a [Chart Replay](ReplayChart.md) the record sequence number is reset back to 1 when the replay is started and any other time the chart is reloaded which can occur if the chart is scrolled back in time and the replay is started again.

If the last record sequence number available during the prior call to your function was 100, then only records after that number will your study function need to process. You can store the last sequence number processed by using the [sc.GetPersistentInt()](#scgetpersistentint) function, in order to know it on the next call into your function.

For a particular symbol, the Time and Sales sequence numbers are not necessarily consecutive. There can be skipped sequence numbers. However, the sequence number will always ascend.

If you require your study function to be aware of every new tick/trade as it occurs, then you will want to use the  **sc.GetTimeAndSales** function to get all of the trades that occurred between calls to your study function. Your study function is not called at every trade, rather instead at the  **Chart Update Interval**. The **Chart Update Interval** is set through **Global Settings >> General Settings**. You might want to reduce that setting in this particular case.

The DateTime member of the **s\_TimeAndSales** data structure is in UTC time. The below code example shows how to adjust it to the time zone in Sierra Chart.

When the real-time market data subscribed to for a symbol from the data feed, the time and sales data is stored from that point in time using data from the streaming data feed. There is no historical time and sales data. However, the existing time and sales data is remembered between data feed connections. It is only cleared on a restart of Sierra Chart. There is a limit to the number of records stored. Refer to [Number of Stored Time and Sales Records](DataSourceSettings.md#storedtimesalesrecords).

#### Parameters

* **TSArray**: This parameter is a reference to an array of **s\_TimeAndSales** structures.

#### Example

```cpp

// Get the Time and Sales
c_SCTimeAndSalesArray TimeSales;
sc.GetTimeAndSales(TimeSales);

if (TimeSales.Size() == 0)
    return;  // No Time and Sales data available for the symbol

// Loop through the Time and Sales
int OutputArrayIndex = sc.ArraySize;
for (int TSIndex = TimeSales.Size() - 1; TSIndex >= 0; --TSIndex)
{
    //Adjust timestamps to Sierra Chart TimeZone
    SCDateTime AdjustedDateTime = TimeSales[TSIndex].DateTime;
    AdjustedDateTime += sc.TimeScaleAdjustment;
}
            
```

#### Alternative Way For Obtaining Time and Sales Data

[Link](#alternativewayforobtainingtimesalesdata) - [Top](#top)

Open a separate chart that is set to 1 **Number of Trades Per Bar** for the symbol you want Time and Sales for.

Select **Global Settings >> Data/Trade Service Settings** and make sure the **Intraday Data Storage Time Unit** is set to **1 Tick**.

Use the [sc.GetChartArray](#scgetchartarray) and the [sc.GetChartDateTimeArray](#scgetchartdatetimearray) functions to access the price, volume and DateTime arrays from this separate chart. Every element in these arrays is 1 trade. This may actually be a preferred way of accessing trade by trade data since there will be an abundant amount of history available.

#### Total Bid and Ask Depth Data

[Link](#totalbidaskdepthdata) - [Top](#top)

The **s\_TimeAndSales** data structure also contains the **s\_TimeAndSales::TotalBidDepth** and the **s\_TimeAndSales::TotalAskDepth** members.

These members are only set when **s\_TimeAndSales::Type** is set to the constant **SC\_TS\_BIDASKVALUES** which means that the Time and Sales record contains a Bid and Ask quote update.

The **s\_TimeAndSales::TotalBidDepth** and **s\_TimeAndSales::TotalAskDepth** members are set to the total of the Bid Sizes/Quantities and Ask Sizes/Quantities, respectively for all of the market depth levels available for the symbol.

If there are no market depth features being used in Sierra Chart or the ACSIL function has not set **sc.UsesMarketDepthData** to a nonzero value, then market depth data usually is not being received and maintained for the symbol. Therefore, these members will equal the best Bid Size and Ask Size, respectively at each record with a **s\_TimeAndSales::Type** set to **SC\_TS\_BIDASKVALUES**.

### sc.GetTimeAndSalesForSymbol()

[Link](#scgettimeandsalesforsymbol) - [Top](#top)

**Type**: Function

int **GetTimeAndSalesForSymbol**(const SCString& **Symbol**, c\_SCTimeAndSalesArray& **TSArray**);

The **sc.GetTimeAndSalesForSymbol** function is identical to [sc.GetTimeAndSales](#scgettimeandsales) except that it has a **Symbol** parameter allowing the study to get Time and Sales data for a different symbol.

Refer to the documentation for [sc.GetTimeAndSales](#scgettimeandsales) for the documentation for this function.

The **sc.GetTimeAndSalesForSymbol** function is only able to get the current Time and Sales data received from the real-time data feed, and not Time and Sales data for a different symbol during a chart replay. This function will also not return the Time and Sales data based on a chart replay for the same symbol as the chart which contains the custom study this function is called from.

#### Parameters

* [Symbol](#commonfunctionparameterdescriptionssymbol)
* **TSArray**: This parameter is a reference to an array of **s\_TimeAndSales** structures.

### sc.GetTimeSalesArrayIndexesForBarIndex()

[Link](#scgettimesalesarrayindexesforbarindex) - [Top](#top)

**Type**: Function

void **GetTimeSalesArrayIndexesForBarIndex**(int **BarIndex**, int& **r\_BeginIndex**, int& **r\_EndIndex**);

The **sc.GetTimeSalesArrayIndexesForBarIndex** function receives a **BarIndex** parameter specifying a particular chart bar index. It gets the Date-Time of that chart bar and returns the beginning and ending indices into the **c\_SCTimeAndSalesArray** array set by the [sc.GetTimeAndSales()](#scgettimeandsales) function. The beginning and ending time and sales array indices are set through the **r\_BeginIndex** and **r\_EndIndex** integers passed by reference to the **sc.GetTimeSalesArrayIndexesForBarIndex** function.

**r\_BeginIndex** and **r\_EndIndex** will be set to -1 if there is no element in the time and sales array contained within the bar specified by **BarIndex**.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex)
* **r\_BeginIndex**: A reference parameter that contains the beginning index of the time and sales arrays for the specified bar index.
* **r\_EndIndex**: A reference paramter that contains the ending index of the time and sales arrays for the specified bar index.

#### Example

```cpp

int BeginIndex = 0, EndIndex = 0;
sc.GetTimeSalesArrayIndexesForBarIndex(sc.UpdateStartIndex, BeginIndex, EndIndex);
SCString DebugString;
DebugString.Format("Time and Sales BeginIndex = %d, EndIndex = %d", BeginIndex, EndIndex);
sc.AddMessageToLog(DebugString, 0);
            
```

### sc.GetTotalNetProfitLossForAllSymbols()

[Link](#scgettotalnetprofitlossforallsymbols) - [Top](#top)

**Type**: Function

double **GetTotalNetProfitLossForAllSymbols**(int **DailyValues**);

The **sc.GetTotalNetProfitLossForAllSymbols** function returns the total Closed Trades Profit/Loss and Open Trades Profit/Loss (net profit/loss) for the unique symbols for open charts which are maintaining a Trades list and match the Trade Account of the chart that the study function is called from.

The Profit/Loss value can be controlled to give the results for just the current trading day, or for all days for which there is order fill data. This is controlled through the **DailyValues** variable.

The amount is a Currency Value and it is also converted to the [Common Profit/Loss Currency](GlobalTradeSettings.md#commonprofitlosscurrency) if that is set in the Global Trade Settings.

#### Parameters

* **DailyValues**: When this variable is set to a nonzero value, then the Daily Net Profit/Loss is returned. Otherwise, it returns the Net Profit/Loss for all days for which there is order fill data.

### sc.GetTradeAccountAtIndex()

[Link](#scgettradeaccountatindex) - [Top](#top)

**Type**: Function

int32\_t **GetTradeAccountAtIndex**(const int32\_t **Index**, SCString& **r\_TradeAccount**);

The **sc.GetTradeAccountAtIndex()** function fills in the trade account defined by the Index into the r\_TradeAccount string.

#### Parameters

* **Index**: The zero-based index number of the desired trade account
* **r\_TradeAccount**: A string that holds the trade account name defined at the specified index.

### sc.GetTradeAccountData()

[Link](#scgettradeaccountdata) - [Top](#top)

Refer to the [sc.GetTradeAccountData()](ACSILTrading.md#scgettradeaccountdata) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetTradeListEntry()

[Link](#scgettradelistentry) - [Top](#top)

Refer to the [sc.GetTradeListEntry()](ACSILTrading.md#scgettradelistentry) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetTradeListSize()

[Link](#scgettradelistsize) - [Top](#top)

Refer to the [sc.GetTradeListSize()](ACSILTrading.md#scgettradelistsize) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetTradePosition()

[Link](#scgettradeposition) - [Top](#top)

Refer to the [sc.GetTradePosition()](ACSILTrading.md#scgettradeposition) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetTradePositionByIndex()

[Link](#scgettradepositionbyindex) - [Top](#top)

Refer to the [sc.GetTradePositionByIndex()](ACSILTrading.md#scgettradepositionbyindex) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetTradePositionForSymbolAndAccount()

[Link](#scgettradepositionforsymbolandaccount) - [Top](#top)

Refer to the [sc.GetTradePositionForSymbolAndAccount()](ACSILTrading.md#scgettradepositionforsymbolandaccount) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetTradeServiceAccountBalanceForTradeAccount()

[Link](#scgettradeserviceaccountbalancefortradeaccount) - [Top](#top)

Refer to the [sc.GetTradeServiceAccountBalanceForTradeAccount()](ACSILTrading.md#scgettradeserviceaccountbalancefortradeaccount) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetTradeStatisticsForSymbolV2()

[Link](#scgettradestatisticsforsymbolv2) - [Top](#top)

Refer to the [sc.GetTradeStatisticsForSymbolV2()](ACSILTrading.md#scgettradestatisticsforsymbolv2) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetTradeSymbol()

[Link](#scgettradesymbol) - [Top](#top)

**Type**: Function

const SCString& **GetTradeSymbol**() const;

The **sc.GetTradeSymbol()** function returns the trading symbol for the chart. If the **Trade and Current Quote Symbol** is set, then this will be the returned string, otherwise the entered symbol for the chart will be returned.

#### Parameters

* This function has no parameters

### sc.GetTradeWindowOrderType()

[Link](#scgettradewindowordertype) - [Top](#top)

**Type**: Function

The **sc.GetTradeWindowOrderType** function returns the [Order Type](OrderTypes.md) which is currently set on the Trade Window of the chart the study instance is applied to.

For the possible return values, refer to [Order Type Constants](ACSILTrading.md#ordertypeconstants).

### sc.GetTradeWindowTextTag()

[Link](#scgettradewindowtexttag) - [Top](#top)

**Type**: Function

int **GetTradeWindowTextTag**(SCString& **r\_TextTag**);

The **sc.GetTradeWindowTextTag** function gets the [Text Tag](TradeWindow.md#texttag) setting from the Trade Window for the chart the study instance is applied to. Pass an SCString for the r\_TextTag parameter to receive this text.

The function returns 1 if successful, otherwise 0 is returned.

#### Parameters

* **r\_TextTag**: A reference to an SCSTring variable that returns the Text Tag text.

#### Example

```cpp

SCString TextTag;            
sc.GetTradeWindowTextTag(TextTag);
            
```

### sc.GetTradingDayDate()

[Link](#scgettradingdaydate) - [Top](#top)

**Type**: Function

int **GetTradingDayDate**(const SCDateTime& **DateTime**);

The **sc.GetTradingDayDateForChartNumber()** function returns a [Date Value](SCDateTime.md#datevalue) which is the *trading day date* for the given **DateTime** parameter.

The *trading day date* is the date of the trading day that the **DateTime** belongs to based upon the **Session Times** set in **Chart >> Chart Settings** for the chart the study function is applied to.

The returned date will be the same date as the given **DateTime** parameter when the Session Times do not span over midnight. However, in the case where the **Session Start Time** is greater than the **Session End Time** and spans over midnight, then the trading day date will always be the date of the day beginning with midnight during the trading session.

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime)

#### Example

```cpp

SCDateTime TradingDayDate = sc.GetTradingDayDate(sc.BaseDateTimeIn[sc.Index]);
            
```

### sc.GetTradingDayDateForChartNumber()

[Link](#scgettradingdaydateforchartnumber) - [Top](#top)

**Type**: Function

int **GetTradingDayDateForChartNumber**(int **ChartNumber**, const SCDateTime& **DateTime**);

The **sc.GetTradingDayDateForChartNumber()** function returns a [Date Value](SCDateTime.md#datevalue) which is the *trading day date* for the given **ChartNumber** and **DateTime** parameters.

The *trading day date* is the date of the trading day that the **DateTime** belongs to based upon the **Session Times** set in **Chart >> Chart Settings** for the chart the study function is applied to.

The returned date will be the same date as the given **DateTime** parameter when the Session Times do not span over midnight. However, in the case where the **Session Start Time** is greater than the **Session End Time** and spans over midnight, then the trading day date will always be the date of the day beginning with midnight during the trading session.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber): If this is negative, the bar period and other Chart Settings are synchronized between the two charts. The relevant Chart Settings for the specified ChartNumber are set to the same settings as the chart your study is applied to. If it is positive, this does not occur. For example, if you want to get the base data from chart #5 and you want to synchronize the charts, then pass -5.
* [DateTime](#commonfunctionparameterdescriptionsdatetime)

#### Example

```cpp

SCDateTime TradingDayDate = sc.GetTradingDayDateForChartNumber(sc.ChartNumber, sc.BaseDateTimeIn[sc.Index]);
            
```

### sc.GetTradingDayStartDateTimeOfBar()

[Link](#scgettradingdaystartdatetimeofbar) - [Top](#top)

**Type**: Function

SCDateTime GetTradingDayStartDateTimeOfBar(SCDateTime& BarDateTime);

The **sc.GetTradingDayStartDateTimeOfBar()** function will return the starting Date-Time of the trading day given the SCDateTime of a bar. The starting Date-Time is based upon the Intraday Session Times settings for the chart.

For an example, refer to the function **scsf\_CumulativeSumOfStudy** in the **/ACS\_Source/studies8.cpp** file in the folder Sierra Chart is installed to.

#### Parameters

* **BarDateTime**: The bar date-time for which the trading day start date tiem is requested.

#### Example

```cpp

SCDateTime CurrentBarTradingDayStartDateTime = GetTradingDayStartDateTimeOfBar(BaseDateTimeIn[BarIndex]);
SCDateTime CurrentBarTradingDayEndDateTime = CurrentBarTradingDayStartDateTime + 24 * HOURS - 1 * MILLISECONDS;
            
```

### sc.GetTradingDayStartDateTimeOfBarForChart()

[Link](#scgettradingdaystartdatetimeofbarforchart) - [Top](#top)

**Type**: Function

void GetTradingDayStartDateTimeOfBarForChart(SCDateTime& **BarDateTime**, SCDateTime& **r\_TradingDayStartDateTime**, int **ChartNumber**);

The **sc.GetTradingDayStartDateTimeOfBarForChart()** function is identical to the [sc.GetTradingDayStartDateTimeOfBar](#scgettradingdaystartdatetimeofbar) function except that it also takes a **ChartNumber** parameter to specify the chart number which it will apply to, which normally will be a different chart than the study that this function is called from, is on.

The resulting trading day start date-time is returned in the **r\_TradingDayStartDateTime** SCDateTime parameter which is passed by reference.

#### Parameters

* **BarDateTime**: An SCDateTime variable of the bar Date-Time.
* **r\_TradingDayStartDateTime**: An reference to a SCDateTime variable which receives trading day start date-Time.
* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

### sc.GetTradingErrorTextMessage()

[Link](#scgettradingerrortextmessage) - [Top](#top)

Refer to the [sc.GetTradingErrorTextMessage()](ACSILTrading.md#scgettradingerrortextmessage) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.GetTradingKeyboardShortcutsEnableState()

[Link](#scgettradingkeyboardshortcutsenablestate) - [Top](#top)

**Type**: Function

int **GetTradingKeyboardShortcutsEnableState**();

The **sc.GetTradingKeyboardShortcutsEnableState** function gets the state of **Trade >> Trading Keyboard Shortcuts Enabled**.

Refer to [Trading Keyboard Shortcuts Enabled](TradeMenu.md#tradingkeyboardshortcutsenabled).

A return of 0 indicates disabled keyboard shortcuts. A return of 1 indicates enabled keyboard shortcuts.

#### Parameters

* This function has no parameters

### sc.GetTrueHigh()

[Link](#scgettruehigh) - [Top](#top)

**Type**: Intermediate Study Calculation Function

float **GetTrueHigh**(SCBaseDataRef **BaseDataIn**, int **Index**);

float **GetTrueHigh**(SCBaseDataRef **BaseDataIn**); [Auto-looping only](#noindexparam).

The **sc.GetTrueHigh()** function calculates the True High of a bar. The result is returned as a single float value. The True High is either the high of the bar at **Index** or the close of the prior bar, whichever is higher.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

float TrueHigh = sc.GetTrueHigh(sc.BaseDataIn);
            
```

### sc.GetTrueLow()

[Link](#scgettruelow) - [Top](#top)

**Type**: Intermediate Study Calculation Function

float **GetTrueLow**(SCBaseDataRef **BaseDataIn**, int **Index**);

float **GetTrueLow**(SCBaseDataRef **BaseDataIn**); [Auto-looping only](#noindexparam).

The **sc.GetTrueLow()** function calculates the True Low of a bar. The result is returned as a single float value. The True Low is either the low of the bar at **Index** or the close of the prior bar. Whichever is lower.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

float TrueLow = sc.GetTrueLow(sc.BaseDataIn);
            
```

### sc.GetTrueRange()

[Link](#scgettruerange) - [Top](#top)

**Type**: Intermediate Study Calculation Function

float **GetTrueRange**(SCBaseDataRef **BaseDataIn**, int **Index**);

float **GetTrueRange**(SCBaseDataRef **BaseDataIn**); [Auto-looping only](#noindexparam).

The **sc.GetTrueRange()** function calculates the True Range of a bar at **Index**. The result is returned as a single float value.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

float TrueRange = sc.GetTrueRange(sc.BaseDataIn);
            
```

### sc.GetUseGlobalGraphicsSettings()

[Link](#scgetuseglobalgraphicssettings) - [Top](#top)

**Type**: Function

int **GetUseGlobalGraphicsSettings**(const int **ChartNumber**);

The **sc.GetUseGlobalGraphicsSettings()** function returns a value of 1 if the option for **Use Global Graphics Settings Instead of These Settings** is enabled, indicating the Global Graphics settings are being used. Otherwise, a value of 0 is returned indicating that the referenced chart has the option for **Use Global Graphics Settings Instead of These Settings** disabled, and therefore is using chart specific graphics settings.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.GetUserDrawingByLineNumber()

[Link](#scgetuserdrawingbylinenumber) - [Top](#top)

Refer to the [sc.GetUserDrawingByLineNumber()](ACSILDrawingTools.md#scgetuserdrawingbylinenumber) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.GetUserDrawnChartDrawing()

[Link](#scgetuserdrawnchartdrawing) - [Top](#top)

Refer to the [sc.GetUserDrawnChartDrawing()](ACSILDrawingTools.md#scgetuserdrawnchartdrawing) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.GetUserDrawnDrawingByLineNumber()

[Link](#scgetuserdrawndrawingbylinenumber) - [Top](#top)

Refer to the [sc.GetUserDrawnDrawingByLineNumber()](ACSILDrawingTools.md#scgetuserdrawndrawingbylinenumber) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.GetUserDrawnDrawingsCount()

[Link](#scgetuserdrawndrawingscount) - [Top](#top)

Refer to the [sc.GetUserDrawnDrawingsCount()](ACSILDrawingTools.md#scgetuserdrawndrawingscount) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.GetValueFormat()

[Link](#scgetvalueformat) - [Top](#top)

**Type**: Function

int **GetValueFormat**();

The **sc.GetValueFormat** function returns the **Value Format** for the study in which this function is called.

#### Parameters

* This function has no parameters.

### sc.GetVolumeAtPriceDataForStudyProfile()

[Link](#scgetvolumeatpricedataforstudyprofile) - [Top](#top)

**Type**: Function

int **GetVolumeAtPriceDataForStudyProfile**(const int **StudyID**, const int **ProfileIndex**, const int **PriceIndex**, s\_VolumeAtPriceV2& **r\_VolumeAtPrice**);

The **sc.GetVolumeAtPriceDataForStudyProfile** function fills out an **s\_VolumeAtPriceV2** structure passed to the function. When filled in, the structure contains the volume data for a price level for the specified Volume Profile or TPO profile.

The Volume Profile can be obtained from a [TPO Profile Chart](StudiesReference/TimePriceOpportunityCharts.md) or a [Volume by Price](StudiesReference.md) study on the chart.

TPO profiles also contain volume data at each price level which can be obtained. In the case of TPO Profiles, the **s\_VolumeAtPriceV2::NumberOfTrades** member contains the number of TPOs at the price level.

The function returns 1 if successful. Otherwise, 0 is returned.

For an example to use this function, refer to the scsf\_GetVolumeAtPriceDataForStudyProfileExample function in **/ACS\_Source/Studies2.cpp** file in the Sierra Chart installation folder.

#### Parameters

* **StudyID**: The unique study identifier for the **Volume by Price** or **TPO Profile Chart** study. Refer to [UniqueStudyInstanceIdentifiers](ACSILProgrammingConcepts.md#uniquestudyinstanceidentifiers).
* **ProfileIndex**: The zero-based index of the volume profile relative to the end of the chart. 0 equals the latest profile in the chart at the end or rightmost side. This needs to always be set to a positive number.
* **PriceIndex**: The zero-based price index. Zero is the lowest price and increasing numbers are for increasing prices. The last valid **PriceIndex** can be determined by calling [sc.GetNumPriceLevelsForStudyProfile](#scgetnumpricelevelsforstudyprofile) and subtracting 1.
* **r\_VolumeAtPrice**: A reference to the **s\_VolumeAtPriceV2** data structure. This structure will be filled in with the volume data for **PriceIndex** parameter when the function returns. For the data members of this structure, refer to the **/ACS\_Source/VAPContainer.h** file. To access the data members of this structure, just simply directly access the member variables. There are no functions used with it.

### sc.GetVolumeAtPriceForBarsForChart()

[Link](#scgetvolumeatpriceforbarsforchart) - [Top](#top)

**Type**: Function

c\_VAPContainer \***GetVolumeAtPriceForBarsForChart**(const int32\_t **ChartNumber**);

The **sc.GetVolumeAtPriceForBarsForChart()** function gets a pointer to the **c\_VAPContainer** object which contains the Volume at Price data for the chart bars for the specified chart.

For more information about c\_VAPContainer, refer to [sc.VolumeAtPriceForBars](ACSIL_Members_Variables_And_Arrays.md#scvolumeatpriceforbars).

The function returns a null pointer if the c\_VAPContainer container cannot be obtained. In which case do not attempt to use the pointer. It is important to test that it is a non-null pointer before attempting to use it.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.GetVolumeOpenInterestMultiplier()

[Link](#scgetvolumeopeninterestmultiplier) - [Top](#top)

**Type**: Function

double **GetVolumeOpenInterestMultiplier**();

The **sc.GetVolumeOpenInterestMultiplier()** returns the value of the **Open Interest Multiplier** set for the chart on which the study that calls this function is located.

#### Parameters

* This function has not parameters.

### sc.GetYValueForChartDrawingAtBarIndex()

[Link](#scgetyvalueforchartdrawingatbarindex) - [Top](#top)

Refer to the [sc.GetYValueForChartDrawingAtBarIndex()](ACSILDrawingTools.md#scgetyvalueforchartdrawingatbarindex) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.HeikinAshi()

[Link](#scheikinashi) - [Top](#top)

**Type**: Function

void **HeikinAshi**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **HeikinAshiOut**, int **Index**, int **Length**, int **SetCloseToCurrentPriceAtLastBar**);

void **HeikinAshi**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **HeikinAshiOut**, int **Length**, int **SetCloseToCurrentPriceAtLastBar**); [Auto-looping only](#noindexparam).

The **sc.HeikinAshi()** function fills in the HeikinAshiOut parameter with the Heikin-Ashi bar components for the given Index of the BaseDataIn, or for the current index when using auto-looping.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [HeikinAshiOut](#commonfunctionparameterdescriptions). For this function, sc.Subgraph[].Arrays[0-2] (Extra Arrays) are used for additional results output. HeikinAshiOut.Data is the Open price array. HeikinAshiOut.Arrays[0] is the High price array. HeikinAshiOut.Arrays[1] is the Low price array. HeikinAshiOut.Arrays[2] is the Last/Close price array.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength): This parameter is unused. Enter any integer value as a placeholder.
* **SetCloseToCurrentPriceAtLastBar**: When this is set to a nonzero value, then the last/close price of the last Heikin-Ashi bar is set to the current price of the underlying data.

### sc.Highest()

[Link](#schighest) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Highest**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **Highest**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.Highest()** function calculates the highest value of the data in **FloatArrayIn** over the specified **Length** beginning at **Index**. The result is put into the **FloatArrayOut** array.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.Highest(sc.BaseDataIn[SC_HIGH], sc.Subgraph[0], 20);

float Highest = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.HullMovingAverage()

[Link](#schullmovingaverage) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **HullMovingAverage** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **HullMovingAverage** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.HullMovingAverage()** function calculates the Hull Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-3] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.HullMovingAverage(sc.BaseData[SC_LAST], sc.Subgraph[0], 10);

float HullMovingAverage = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.HurstExponent()

[Link](#schurstexponent) - [Top](#top)

**Type**: Function

SCFloatArrayRef **HurstExponent** (SCFloatArrayRef **In**, SCSubgraphRef **Out**, int **Index**, int **LengthIndex**);

SCFloatArrayRef **HurstExponent** (SCFloatArrayRef **In**, SCSubgraphRef **Out**, int **LengthIndex**); [Auto-looping only](#noindexparam).

The **sc.HurstExponent()** function calculates the Hurst Exponent study.

#### Parameters

* [In](#commonfunctionparameterdescriptionsfloatarrayin)
* [Out](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [LengthIndex](#commonfunctionparameterdescriptionslength)

### sc.InstantaneousTrendline()

[Link](#scinstantaneoustrendline) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **InstantaneousTrendline**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **InstantaneousTrendline**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.InstantaneousTrendline()** function calculates Ehlers' Instantaneous Trendline study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.InstantaneousTrendline(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 10);

float InstantaneousTrendline = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.InverseFisherTransform()

[Link](#scinversefishertransform) - [Top](#top)

**Type**: Function

void **InverseFisherTransform** (SCFloatArrayRef **In**, SCSubgraphRef **Out**, int **Index**, int **HighestLowestLength**, int **MovingAverageLength**, int **MovAvgType**);

void **InverseFisherTransform** (SCFloatArrayRef **In**, SCSubgraphRef **Out**, int **HighestLowestLength**, int **MovingAverageLength**, int **MovAvgType**); [Auto-looping only](#noindexparam).

The **sc.InverseFisherTransform()** function calculates the Inverse Fisher Transform for the given In data.

For information on how the Inverse Fisher Transform is calculated, refer to the information for the [Inverse Fisher Transform](StudiesReference.md) study.

#### Parameters

* [In](#commonfunctionparameterdescriptionsfloatarrayin)
* [Out](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [HighestLowestLength](#commonfunctionparameterdescriptionslength)
* [MovingAverageLength](#commonfunctionparameterdescriptionslength)
* [MovAvgType](#commonfunctionparameterdescriptionsmovingaveragetype)

### sc.InverseFisherTransformRSI()

[Link](#scinversefishertransformrsi) - [Top](#top)

**Type**: Function

void **InverseFisherTransformRSI** (SCFloatArrayRef **In**, SCSubgraphRef **Out**, int **Index**, int **RSILength**, int **InternalRSIMovAvgType**, int **RSIMovingAverageLength**, int **MovingAverageOfRSIType**);

void **InverseFisherTransformRSI** (SCFloatArrayRef **In**, SCSubgraphRef **Out**, int **RSILength**, int **InternalRSIMovAvgType**, int **RSIMovingAverageLength**, int **MovingAverageOfRSIType**); [Auto-looping only](#noindexparam).

The **sc.InverseFisherTransformRSI()** study calculateds the Inverse Fisher Transform from RSI data.

For information on how the Inverse Fisher Transform RSI is calculated, refer to the information for the [Inverse Fisher Transform RSI](StudiesReference.md) study.

#### Parameters

* [In](#commonfunctionparameterdescriptionsfloatarrayin)
* [Out](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [RSILength](#commonfunctionparameterdescriptionslength)
* [InternalRSIMovAvgType](#commonfunctionparameterdescriptionsmovingaveragetype)
* [RSIMovingAverageLength](#commonfunctionparameterdescriptionslength)
* [MovingAverageOfRSIType](#commonfunctionparameterdescriptionsmovingaveragetype)

### sc.IsChartDataLoadingCompleteForAllCharts()

[Link](#scischartdataloadingcompleteforallcharts) - [Top](#top)

**Type**: Function

int **IsChartDataLoadingCompleteForAllCharts**();

The **sc.IsChartDataLoadingCompleteForAllCharts** function returns a nonzero value when the loading of chart data from the local chart data files is complete for all charts within the Chartbook containing the chart that the study instance calling this function is applied to.

Otherwise, this function returns 0 while one or more charts is loading data from the local chart data files.

#### Parameters

* This function has no parameters.

#### Example

```cpp

bool LoadingIsComplete = sc.IsChartDataLoadingCompleteForAllCharts();
            
```

### sc.IsChartDataLoadingInChartbook()

[Link](#scischartdataloadinginchartbook) - [Top](#top)

**Type**: Function

int **IsChartDataLoadingInChartbook**();

The **sc.IsChartDataLoadingInChartbook()** function returns 1 when it is called and an Intraday chart is loading data in the same Chartbook that the chart belongs to that the study instance is applied to. So this can be during the time the Chartbook is in the process of being opened or at any time after. An example of an intraday chart loading data would be when certain chart settings are changed through **Chart >> Chart Settings**.

If none of the Intraday charts are loading data within the Chartbook, then the return value is 0.

#### Parameters

* This function has no parameters

### sc.IsChartDOMRecenterLineEnabled()

[Link](#scischartdomrecenterlineenabled) - [Top](#top)

**Type**: Function

int32\_t **IsChartDOMRecenterLineEnabled**(const int32\_t **ChartNumber**);

The **sc.IsChartDOMRecenterLineEnabled()** function returns a value of 1 if the option for the Recenter Line is enabled for the referenced chart number. If the Recenter Line option is not enabled, then this function returns a value of 0.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.IsChartNumberExist()

[Link](#scischartnumberexist) - [Top](#top)

**Type**: Function

int **IsChartNumberExist**(int **ChartNumber**, const SCString& **ChartbookFileName**);

The **sc.IsChartNumberExist** function returns a value of 1 if the specified **ChartNumber** exists within the given **ChartbookFileName**, otherwise it returns a value of 0.

The parameter **ChartbookFileName** may be an empty string (**""**), in which case the Chartbook used to check for the **ChartNumber** is the Chartbook that contains the study from which this function is called. The **ChartbookFileName** must also contain the **.cht** extension, but it does not need to contain the complete path. Only the file name.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **ChartbookFileName**: The name of the chartbook file.

### sc.IsChartZoomInStateActive()

[Link](#scischartzoominstateactive) - [Top](#top)

**Type**: Function

int **IsChartZoomInStateActive**();

The **sc.IsChartZoomInStateActive** function returns 1 if **Tools >> Zoom In** mode is active for the chart the study instance is applied to. Otherwise, 0 is returned.

#### Parameters

* This function has no parameters.

### sc.IsDataExportAllowed()

[Link](#scisdataexportallowed) - [Top](#top)

**Type**: Function

int32\_t **IsDataExportAllowed**();

The **sc.IsDataExportAllowed()** function returns 1 if exporting the data for the particular exchange is allowed. Otherwise a value of 0 is returned, meaning the data can not be exported.

#### Parameters

* This function has no parameters

### sc.IsDateTimeContainedInBarAtIndex()

[Link](#scisdatetimecontainedinbaratindex) - [Top](#top)

**Type**: Function

bool **IsDateTimeContainedInBarAtIndex**(const SCDateTime& **DateTime**, int **BarIndex**);

The **sc.IsDateTimeContainedInBarAtIndex()** function returns a value of TRUE if the given DateTime is greater than or equal to the start time of the given bar index, and less than the start time of the next bar index. Otherwise, the function returns FALSE.

This function and the function **sc.IsDateTimeContainedInBarIndex** are functionally the same, although the **sc.IsDateTimeContainedInBarIndex** does perform additional checks to ensure the Index is contained within the chart.

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime)
* [Index](#commonfunctionparameterdescriptionsindex)

### sc.IsDateTimeContainedInBarIndex()

[Link](#scisdatetimecontainedinbarindex) - [Top](#top)

**Type**: Function

int **IsDateTimeContainedInBarIndex**(const SCDateTime& **DateTime**, int **BarIndex**) const;

The **sc.IsDateTimeContainedInBarIndex()** function returns a value of TRUE if the given DateTime is greater than or equal to the start time of the given bar index, and less than the start time of the next bar index. Otherwise, the function returns FALSE.

This function also checks to ensure that the given Index is contained within the chart itself, returning a value of FALSE if it does not exist in the chart.

This function and the function **sc.IsDateTimeContainedInBarAtIndex** are functionally the same, although the **sc.IsDateTimeContainedInBarAtIndex** does not perform the check to ensure the Index is contained within the chart.

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime)
* [BarIndex](#commonfunctionparameterdescriptionsindex)

### sc.IsDateTimeInDaySession()

[Link](#scisdatetimeindaysession) - [Top](#top)

**Type**: Function

int **IsDateTimeInDaySession**(const SCDateTime& **DateTime**);

The **sc.IsDateTimeInDaySession()** function returns TRUE (non-zero value) or FALSE indicating whether the given **DateTime** is within the Day Session Times in **Chart >> Chart Settings**. **DateTime** is a [SCDateTime](SCDateTime.md) type.

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime)

#### Example

```cpp

int IsInDaySession = sc.IsDateTimeInDaySession(sc.BaseDateTimeIn[sc.Index]+ 1*HOURS);
            
```

### sc.IsDateTimeInEveningSession()

[Link](#scisdatetimeineveningsession) - [Top](#top)

**Type**: Function

int **IsDateTimeInEveningSession**(const SCDateTime **&DateTime**);

The **sc.IsDateTimeInEveningSession** returns a value of **1** if the specified time in **DateTime** is within the defined hours for the Evening Session as set by the [Evening Start](SessionTimes.md#eveningstarttime) and [Evening End](SessionTimes.md#eveningendtime) times and a **0** otherwise. If the option for [Use Evening Session](SessionTimes.md#eveningsession) is not set, then this function returns a value of **0**.

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime)

### sc.IsDateTimeInSession()

[Link](#scisdatetimeinsession) - [Top](#top)

**Type**: Function

int **IsDateTimeInSession**(const SCDateTime& **DateTime**);

The **sc.IsDateTimeInSession()** function returns TRUE (non-zero value) or FALSE indicating whether the given **DateTime** is within the Session Times in **Chart >> Chart Settings**. **DateTime** is an [SCDateTime](SCDateTime.md) type.

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime)

#### Example

```cpp

int IsInSession = sc.IsDateTimeInSession(sc.BaseDateTimeIn[sc.Index]+ 1*HOURS);
            
```

### sc.IsDrawDOMGraphOnChartEnabled()

[Link](#scisdrawdomgraphonchartenabled) - [Top](#top)

**Type**: Function

int32\_t **IsDrawDOMGraphOnChartEnabled**(const int32\_t **ChartNumber**);

The **sc.IsDrawDOMGraphOnChartEnabled()** function returns 1/true if the DOM Graph is enabled for the specified chart.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.IsLastBarClosedBasedOnElapsedTime()

[Link](#scislastbarclosedbasedonelapsedtime) - [Top](#top)

**Type**: Function

int **IsLastBarClosedBasedOnElapsedTime**(const int **ChartNumber**);

The **IsLastBarClosedBasedOnElapsedTime()** function returns a value of 1 if the last bar in the chart is defined as closed based on whether the amount of time for the bar has elapsed. Otherwise it returns a value of 0.

For example, if the bar period is set to 2 minutes, then this function will return a value of 1 if the last bar in the chart has a starting bar time that is more than 2 minutes in the past.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.IsMarketDataColumnsEnabled()

[Link](#scismarketdatacolumnsenabled) - [Top](#top)

**Type**: Function

int32\_t **IsMarketDataColumnsEnabled**(const int32\_t **ChartNumber**);

The **sc.IsMarketDataColumnsEnabled()** function returns a value of 1 if the option for **Trade >> Show Market Data Columns** is enabled for the given chart number. Otherwise, this function returns a value of 0.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.IsMarketDepthDataCurrentlyAvailable()

[Link](#scismarketdepthdatacurrentlyavailable) - [Top](#top)

**Type**: Function

int **IsMarketDepthDataCurrentlyAvailable**()

The **sc.IsMarketDepthDataCurrentlyAvailable** function returns 1 when the **sc.SymbolData->BidDOM** and **sc.SymbolData->AskDOM** contain market depth data at levels 1 and 2. This is an indication that market depth data is currently available in those arrays.

For additional information, refer to [sc.SymbolData](#scsymboldata).

#### Parameters

* This function has no parameters

### sc.IsNewBar()

[Link](#scisnewbar) - [Top](#top)

**Type**: Function

bool **IsNewBar**(int **BarIndex**);

The **sc.IsNewBar()** function returns a value of TRUE, if the bar defined by BarIndex is the currently updating bar in the chart. Otherwise, this function returns a value of FALSE.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex)

### sc.IsNewTradingDay()

[Link](#scisnewtradingday) - [Top](#top)

**Type**: Function

bool **IsNewTradingDay**(int **BarIndex**);

The **sc.IsNewTradingDay()** function returns 1 if the chart bar index specified by the **BarIndex** parameter is the start of a new trading day according to the [Session Times](SessionTimes.md) set for the chart the study instance is applied to. Otherwise, 0 is returned.

Even if the prior bar has the same date as the date of the **BarIndex** bar, this can still be the start of a new trading day in the case when reversed session times are used or when the **Use Evening Session** option is enabled. Refer to [Session Times](SessionTimes.md).

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex)

### sc.IsOpenGLActive()

[Link](#scisopenglactive) - [Top](#top)

**Type**: Function

int **IsOpenGLActive()**;

The **sc.IsOpenGLActive** function returns 1 if the setting for **Use OpenGL for Chart Graphics** is enabled. Otherwise zero is returned.

#### Parameters

* This function has no parameters

### sc.IsReplayRunning()

[Link](#scisreplayrunning) - [Top](#top)

**Type**: Function

int **IsReplayRunning**();

**sc.IsReplayRunning()** returns TRUE (1) if a replay is running on the chart the study instance is applied to or the replay is paused. Otherwise, it returns FALSE (0).

Internally this function simply checks the state of **sc.ReplayStatus** and checks if the replay is *not stopped*.

#### Parameters

* This function has no parameters

#### Example

```cpp

int ReplayRunning = sc.IsReplayRunning();
            
```

### sc.IsSufficientTimePeriodInDate()

[Link](#scissufficienttimeperiodindate) - [Top](#top)

**Type**: Function

bool **IsSufficientTimePeriodInDate**(const SCDateTime& **DateTime**, float **Percentage**);

The **sc.IsSufficientTimePeriodInDate()** function determines whether the amount of time for which data exists in a trading day (defined by the DateTime), has at least the amount of data required by the defined Percentage.

The function returns a value of TRUE if the amount of time for which data is present is more than the entered percentage. Otherwise a value of FALSE is returned.

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime)
* **Percentage**: A percentage value to test against for the amount of time for which data exists in a trading day. This value needs to be entered as a whole percentage, for example 80.0 for 80.0%.

### sc.IsSwingHigh()

[Link](#scisswinghigh) - [Top](#top)

**Type**: Intermediate Study Calculation Function

int **IsSwingHigh** (SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

int **IsSwingHigh** (SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.IsSwingHigh()** function returns TRUE (1) if there is a Swing High. Otherwise, it returns FALSE (0).

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

int SwingHigh = sc.IsSwingHigh(sc.BaseData[SC_HIGH],2);
            
```

### sc.IsSwingLow()

[Link](#scisswinglow) - [Top](#top)

**Type**: Intermediate Study Calculation Function

int **IsSwingLow**(SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

int **IsSwingLow**(SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.IsSwingLow()** function returns TRUE (1) if there is a Swing Low. Otherwise, it returns FALSE (0).

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

int SwingLow = sc.IsSwingLow(sc.BaseData[SC_LOW],2);
            
```

### sc.IsTradingChartDOMEnabled()

[Link](#scistradingchartdomenabled) - [Top](#top)

**Type**: Function

int32\_t **IsTradingChartDOMEnabled**(const int32\_t **ChartNumber**);

The **sc.IsTradingChartDOMEnabled()** function returns a value of 1 if the option for **Trade >> Chart Trading DOM On** is enabled for the given chart number. Otherwise, this function returns a value of 0.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.IsTradingDOMMode()

[Link](#scistradingdommode) - [Top](#top)

**Type**: Function

int **IsTradingDOMMode**();

The **sc.IsTradingDOMMode()** function returns a value of 1 if the chart on which the study that contains this function is a trading DOM. Otherwise, the function returns a value of 0.

#### Parameters

* This function has no parameters.

### sc.IsVisibleSubgraphDrawStyle()

[Link](#scisvisiblesubgraphdrawstyle) - [Top](#top)

**Type**: Function

bool **IsVisibleSubgraphDrawStyle**(int **DrawStyle**);

The **sc.IsVisibleSubgraphDrawStyle()** function returns a value of TRUE (1) if the given draw style is not one of **Hidden** or **Ignore**. Otherwise, this function returns a value of FALSE (0).

This function is intended to be used with the [sc.GetStudySubgraphDrawStyle()](ACSIL_Members_Functions.md#scgetstudysubgraphdrawstyle) or other related functions in which the Draw Style is not already known.

#### Parameters

* **DrawStyle**: One of the [Drawing Type Enumerations](ACSILDrawingTools.md#susetooldrawingtype).

### IsWorkingOrderStatus()

[Link](#scisworkingorderstatus) - [Top](#top)

Refer to the [IsWorkingOrderStatus()](ACSILTrading.md#isworkingorderstatus) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### IsWorkingOrderStatusIgnorePendingChildren()

[Link](#scisworkingorderstatusignorependingchildren) - [Top](#top)

Refer to the [IsWorkingOrderStatusIgnorePendingChildren()](ACSILTrading.md#isworkingorderstatusignorependingchildren) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.Keltner()

[Link](#sckeltner) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Keltner**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayIn**, SCSubgrapRef **SubgraphOut**, int **Index**, int **KeltnerMovAvgLength**, unsigned int **KeltnerMovAvgType**, int **TrueRangeMovAvgLength**, unsigned int **TrueRangeMovAvgType**, float **TopBandMultiplier**, float **BottomBandMultiplier**);

SCFloatArrayRef **Keltner**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayIn**, SCSubgrapRef **SubgraphOut**, int **KeltnerMovAvgLength**, unsigned int **KeltnerMovAvgType**, int **TrueRangeMovAvgLength**, unsigned int **TrueRangeMovAvgType**, float **TopBandMultiplier**, float **BottomBandMultiplier**); [Auto-looping only](#noindexparam).

The **sc.Keltner()** function calculates the Keltner study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-3] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [KeltnerMovAvgLength](#commonfunctionparameterdescriptionslength)
* [KeltnerMovAvgType](#commonfunctionparameterdescriptionsmovingaveragetype)
* [TrueRangeMovAvgLength](#commonfunctionparameterdescriptionslength)
* [TrueRangeMovAvgType](#commonfunctionparameterdescriptionsmovingaveragetype)
* [TopBandMultiplier](#commonfunctionparameterdescriptionsmultiplier)
* [BottomBandMultiplier](#commonfunctionparameterdescriptionsmultiplier)

#### Example

```cpp

sc.Keltner(
    sc.BaseDataIn,

    sc.BaseDataIn[SC_LAST],
    sc.Subgraph[0],
    10,

    MOVAVGTYPE_SIMPLE,
    10,
    MOVAVGTYPE_WILDERS,
    1.8f,
    1.8f,
);

//Access the individual Keltner lines
float KeltnerAverageOut = sc.Subgraph[0][sc.Index];

float TopBandOut = sc.Subgraph[0].Arrays[0][sc.Index];

float BottomBandOut = sc.Subgraph[0].Arrays[1][sc.Index];

//Copy to Visible Subgraphs
sc.Subgraph[1][sc.Index] = TopBandOut;
sc.Subgraph[2][sc.Index] = BottomBandOut; 
            
```

### sc.LaguerreFilter()

[Link](#sclaguerrefilter) - [Top](#top)

**Type**: [Intermediate Study Calculation Function](#workingwithintermediatestudycalculationfunctions)

SCFloatArrayRef **LaguerreFilter**(SCFloatArrayRef In, SCSubgraphRef Out, int IndexParam, float DampingFactor);

SCFloatArrayRef **LaguerreFilter**(SCFloatArrayRef In, SCSubgraphRef Out, float DampingFactor); [Auto-looping only](#noindexparam).

The **sc.LaguerreFilter()** function calculates the Laguerre Filter study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-3] (Extra Arrays) are used for internal calculations and additional results output.
* [IndexParam](#commonfunctionparameterdescriptionsindex)
* **DampingFactor**: A factor to determine the weight given to both current and previous values of the Input Data.

#### Example

```cpp

sc.LaguerreFilter(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 0.8);

float LaguerreFilter = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.LinearRegressionIndicator()

[Link](#sclinearregressionindicator) - [Top](#top)

**Type**: [Intermediate Study Calculation Function](#workingwithintermediatestudycalculationfunctions)

SCFloatArrayRef **LinearRegressionIndicator**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **LinearRegressionIndicator**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.LinearRegressionIndicator()** function calculates the [Moving Average - Linear Regression](StudiesReference.md#movingaverage-linearregression) study. The result is placed into **FloatArrayOut** at the array index specified by **Index**.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.LinearRegressionIndicator(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20);

float LinearRegression = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.LinearRegressionIndicatorAndStdErr()

[Link](#sclinearregressionindicatorandstderr) - [Top](#top)

**Type**: [Intermediate Study Calculation Function](#workingwithintermediatestudycalculationfunctions)

SCFloatArrayRef **LinearRegressionIndicatorAndStdErr**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, SCFloatArrayRef **StdErr**, int **Length**);

SCFloatArrayRef **LinearRegressionIndicatorAndStdErr**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, SCFloatArrayRef **StdErr**, int **Index**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.LinearRegressionIndicatorAndStdErr()** function calculates the [Moving Average - Linear Regression](StudiesReference.md#movingaverage-linearregression) study along with the Standard Error for the regression. The result is placed into **FloatArrayOut** at the array index specified by **Index**.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* **StdErr**: The standard error for the given regression
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

### sc.LinearRegressionIntercept()

[Link](#sclinearregressionintercept) - [Top](#top)

**Type**: Function

SCFloatArrayRef **LinearRegressionIntercept**(SCFloatArrayRef **In**, SCFloatArrayRef **Out**, int **Index**, int **Length**);

The **LinearRegressionIntercept()** function calculates the [Moving Average - Linear Regression](StudiesReference.md#movingaverage-linearregression) study y-intercept. The result is placed into **Out** at the array index specified by **Index**.

#### Parameters

* [In](#commonfunctionparameterdescriptionsfloatarrayin)
* [Out](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

### sc.LinearRegressionSlope()

[Link](#sclinearregressionslope) - [Top](#top)

**Type**: Function

SCFloatArrayRef **LinearRegressionSlope**(SCFloatArrayRef **In**, SCFloatArrayRef **Out**, int **Index**, int **Length**);

The **LinearRegressionSlope()** function calculates the [Moving Average - Linear Regression](StudiesReference.md#movingaverage-linearregression) study slope. The result is placed into **Out** at the array index specified by **Index**.

#### Parameters

* [In](#commonfunctionparameterdescriptionsfloatarrayin)
* [Out](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

### sc.Lowest()

[Link](#sclowest) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Lowest**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **Lowest**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.Lowest()** function calculates the lowest value of the data in **FloatArrayIn** over the specified **Length** beginning at **Index**. The result is put into the **FloatArrayOut** array.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.Lowest(sc.BaseDataIn[SC_LOW], sc.Subgraph[0], 20);

float Lowest = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.MACD()

[Link](#scmacd) - [Top](#top)

**Type**: Intermediate Study Calculation Function.

SCFloatArrayRef **sc.MACD** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **FastMALength**, int **SlowMALength**, int **MACDMALength**, int **MovAvgType**);

SCFloatArrayRef **sc.MACD** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **FastMALength**, int **SlowMALength**, int **MACDMALength**, int **MovAvgType**); [Auto-looping only](#noindexparam).

The **sc.MACD()** function calculates the standard Moving Average Convergence Divergence study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-3] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [FastMALength](#commonfunctionparameterdescriptionslength)
* [SlowMALength](#commonfunctionparameterdescriptionslength)
* [MACDMALength](#commonfunctionparameterdescriptionslength)
* [MovingAverageType](#commonfunctionparameterdescriptionsmovingaveragetype)

#### Example

```cpp

sc.MACD(sc.BaseData[SC_LAST], sc.Subgraph[0], 5, 10, 10, MOVAVGTYPE_SIMPLE);

//Access the individual lines
float MACD = sc.Subgraph[0][sc.Index]; //Access the study value at the current index

float MACDMovingAverage = sc.Subgraph[0].Arrays[2][sc.Index];

float MACDDifference = sc.Subgraph[0].Arrays[3][sc.Index];

//Copy to Visible Subgraphs
sc.Subgraph[1][sc.Index] = MACDMovingAverage;
sc.Subgraph[2][sc.Index] = MACDDifference;
            
```

### sc.MakeHTTPBinaryRequest()

[Link](#scmakehttpbinaryrequest) - [Top](#top)

**Type**: Function

int **MakeHTTPBinaryRequest**(const SCString& **URL**);

The **sc.MakeHTTPBinaryRequest()** function is identical to [sc.MakeHTTPRequest()]( #scMakeHTTPRequest), except that it is designed to be used in cases where the data returned by the Web server is *non-text data*.

When the request completes, the returned data from the Web server is placed into the **sc.HTTPBinaryResponse** variable and the study function will be called again.

This response is an SCConstCharArray type and holds an array of bytes/characters. Refer to **/ACS\_Source/SCStructures.h** for additional information on this class type.

The return value is zero if there is an error. If there is no error, the return value is the request identifier which is later returned in the **sc.HTTPRequestID** member when the study function is called when the data is received after the response completes.

#### Parameters

* **URL**: The full URL of the website resource. Example: *http://www.sierrachart.com/ACSILHTTPTest.txt*. Can be HTTP or HTTPS for secure connections.

### sc.MakeHTTPPOSTRequest()

[Link](#scmakehttppostrequest) - [Top](#top)

**Type**: Function

int **MakeHTTPPOSTRequest**(const SCString& **URL**, const SCString& **POSTData**, const n\_ACSIL::s\_HTTPHeader\* **Headers**, int **NumberOfHeaders**);

The **sc.MakeHTTPPOSTRequest()** function is identical to [sc.MakeHTTPRequest()]( #scMakeHTTPRequest), except that it submits the request to the server as a POST operation rather than GET operation. It also supports additional parameters which are described below.

#### Parameters

* **URL**: The full URL of the website resource. Example: "https://www.sierrachart.com/Test/ACSILPOSTTest.php"
* **POSTData**: The POST data to include in the request. See the example below.
* **Headers**: The address of an **n\_ACSIL::s\_HTTPHeader** structure of an additional header to add to the request. This can also be the address of an array. This can also be a null pointer (nullptr). If it is a single structure, set the **NumberOfHeaders** parameter to 1. If it is an array of **n\_ACSIL::s\_HTTPHeader** structures, specify the number of array elements with the **NumberOfHeaders** parameter documented below.
* **NumberOfHeaders**: The number of headers specified with the **Headers** parameter. Set this to 0 if the **Headers**parameter is a null pointer.

#### Example

```cpp

n_ACSIL::s_HTTPHeader HTTPHeader;
HTTPHeader.Name = "Custom";
HTTPHeader.Value = "Value";

// Make a request to the server.  
// When the request is complete and all of the data has been downloaded,  
// this study function will be called with the file placed into the
// sc.HTTPResponse character string array. 
if (!sc.MakeHTTPPOSTRequest("https://www.sierrachart.com/Test/ACSILPOSTTest.php", "Message=PostData", &HTTPHeader, 1))
{
    sc.AddMessageToLog("Error making HTTP request.", 1);
}            
            
```

### sc.MakeHTTPRequest()

[Link](#scmakehttprequest) - [Top](#top)

**Type**: Function

int **MakeHTTPRequest**(const SCString& **URL**);

The **sc.MakeHTTPRequest()** function makes a website Hypertext Transfer Protocol (HTTP/HTTPS) request over the network. The website address and the file to request are contained in the **URL** parameter.

The **URL** parameter needs to contain the website address and the file to retrieve. Standard HTTP GET parameters can also be added.

This function is nonblocking and immediately returns.

When the request is complete, the response will be placed into the **sc.HTTPResponse** SCString member. At the time the request is complete, the study instance which made the request will be called and at that time the **sc.HTTPResponse** member can be checked.

If there is an error with making the request to the remote server or the server returns an error, **sc.HTTPResponse** will be set to "ERROR".

Returns 1 if successful. Returns 0 on error.

If **sc.MakeHTTPRequest** returns 0, then **sc.HTTPResponse** will be set to "HTTP\_REQUEST\_ERROR". Otherwise, **sc.HTTPResponse** will be set to an empty string after calling the **sc.MakeHTTPRequest** function and **sc.HTTPResponse** will be set to the response from the server when the server later responds *after* the study function returns.

It is only supported to make one request *at a time*. The current request must finish before another one can be made.

The only persistent memory used for a HTTP/HTTPS request will be the maximum size of the data received among the HTTP/HTTPS requests by a study. There will be some temporary memory use for the network socket connection, but that will get released when the request is complete.

Also refer to [sc.MakeHTTPBinaryRequest](#scmakehttpbinaryrequest), [sc.MakeHTTPPOSTRequest()](#scmakehttppostrequest).

Each chart has its own HTTP object. Therefore, when the chart is closed, all of the outstanding HTTP requests are deleted at that time and will not complete.

#### Example

```cpp

enum {REQUEST_NOT_SENT = 0,  REQUEST_SENT, REQUEST_RECEIVED};
int& RequestState = sc.GetPersistentInt(1);

if (sc.Index == 0)
{
    if (RequestState == REQUEST_NOT_SENT)
    {
        // Make a request for a text file on the server. When the request is complete and all of the data
        //has been downloaded, this study function will be called with the file placed into the sc.HTTPResponse character string array.

        if (!sc.MakeHTTPRequest("https://www.sierrachart.com/ACSILHTTPTest.txt"))
        {
            sc.AddMessageToLog("Error making HTTP request.", 1);
            
            // Indicate that the request was not sent. 
            // Therefore, it can be made again when sc.Index equals 0.
            RequestState = REQUEST_NOT_SENT;
        }
        else
        {   
            RequestState = REQUEST_SENT;
        }
    }
}

if (RequestState == REQUEST_SENT && sc.HTTPResponse != "")
{
    RequestState = REQUEST_RECEIVED;

    // Display the response from the Web server in the Message Log

    sc.AddMessageToLog(sc.HTTPResponse, 1); 
}
else if (RequestState == REQUEST_SENT && sc.HTTPResponse == "")
{
    //The request has not completed, therefore there is nothing to do so we will return
    return;
}
            
```

### sc.Momentum()

[Link](#scmomentum) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Momentum**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **Momentum**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.Momentum()** function calculates the momentum.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.Momentum(sc.BaseDataIn[SC_LAST], sc.Subgraph[0].Arrays[0], 20);

float Momentum = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.MovingAverage()

[Link](#scmovingaverage) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **MovingAverage**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, unsigned int **MovingAverageType**, int **Index**, int **Length**);

SCFloatArrayRef **MovingAverage**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, unsigned int **MovingAverageType**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.MovingAverage()** function calculates a Moving Average of the specified Type and Length.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)
* [MovingAverageType](#movavgtype)

#### Example

```cpp

sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], MOVAVGTYPE_SIMPLE, 20);

float MovingAverage = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.MovingAverageCumulative()

[Link](#scmovingaveragecumulative) - [Top](#top)

**Type**: Intermediate Study Calculation Function

void **MovingAverageCumulative**(SCFloatArrayRef **In**, SCFloatArrayRef **Out**, int **Index**);

void **MovingAverageCumulative**(SCFloatArrayRef **In**, SCFloatArrayRef **Out**); [Auto-looping only](#noindexparam).

The **sc.MovingAverageCumulative()** function calculates a cumulative moving average.

#### Parameters

* [In](#commonfunctionparameterdescriptionsfloatarrayin)
* [Out](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)

### sc.MovingMedian()

[Link](#scmovingmedian) - [Top](#top)

**Type**: Function

SCFloatArrayRef **MovingMedian**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **MovingMedian**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Length**);

The **sc.MovingMedian()** function calculates the Moving Median of the specified Length.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

SCSubgraphRef Median = sc.Subgraph[0];

SCInputRef InputData = sc.Input[0];
SCInputRef Length = sc.Input[1];
SCFloatArrayRef In = sc.BaseDataIn[InputData.GetInputDataIndex()];

sc.MovingMedian(In, Median,  Length.GetInt());
            
```

### sc.MultiplierFromVolumeValueFormat()

[Link](#scmultiplierfromvolumevalueformat) - [Top](#top)

**Type**: Function

float **MultiplierFromVolumeValueFormat**() const;

The **sc.MultiplierFromVolumeValueFormat()** function returns the value of the **Chart >> Chart Settings** **>> Symbol >> Volume Value Format** setting for the chart on which the study that contains this function is applied.

This is used when volumes have fractional values that are stored as an integer.

#### Parameters

* This function has no parameters

#### Example

```cpp

float ActualVolume = sc.Volume[sc.Index] * sc.MultiplierFromVolumeValueFormat();
            
```

### sc.NumberOfBarsSinceHighestValue()

[Link](#scnumberofbarssincehighestvalue) - [Top](#top)

**Type**: Intermediate Study Calculation Function

int **NumberOfBarsSinceHighestValue** (SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

int **NumberOfBarsSinceHighestValue** (SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.NumberOfBarsSinceHighestValue()** function calculates the number of bars between the highest value in the **FloatArrayIn** array, which is determined over the specified **Length**, and the **Index** element of the **FloatArrayIn** array. The highest value is calculated over the range from **Index** to **Index-Length+1**.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

int NumBars = sc.NumberOfBarsSinceHighestValue(sc.BaseDataIn[SC_LAST], 10);
            
```

### sc.NumberOfBarsSinceLowestValue()

[Link](#scnumberofbarssincelowestvalue) - [Top](#top)

**Type**: Intermediate Study Calculation Function

int **NumberOfBarsSinceLowestValue** (SCFloatArrayRef **FloatArrayIn**, int **Index**, int **Length**);

int **NumberOfBarsSinceLowestValue** (SCFloatArrayRef **FloatArrayIn**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.NumberOfBarsSinceLowestValue()** function calculates the number of bars between the lowest value in the **FloatArrayIn** array, which is determined over the specified **Length**, and the **Index** element of the **FloatArrayIn** array. The lowest value is calculated over the range from **Index** to **Index-Length+1**.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

int NumBars = sc.NumberOfBarsSinceLowestValue(sc.BaseDataIn[SC_LAST],  10);
            
```

### sc.OnBalanceVolume()

[Link](#sconbalancevolume) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **OnBalanceVolume** (SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**);

SCFloatArrayRef **OnBalanceVolume** (SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**); [Auto-looping only](#noindexparam).

The **sc.OnBalanceVolume()** function calculates the On Balance Volume study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.OnBalanceVolume(sc.BaseDataIn, sc.Subgraph[0]);

float OnBalanceVolume = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.OnBalanceVolumeShortTerm()

[Link](#sconbalancevolumeshortterm) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **OnBalanceVolumeShortTerm**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **OnBalanceVolumeShortTerm**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.OnBalanceVolumeShortTerm()** function calculates the On Balance Volume Short Term study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.OnBalanceVolumeShortTerm(sc.BaseDataIn, sc.Subgraph[0], 20);

float ShortTermOnBalanceVolume = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.OpenChartbook()

[Link](#scopenchartbook) - [Top](#top)

**Type**: Function

void **OpenChartbook**(const SCString& **ChartbookFileName**);

The **sc.OpenChartbook** function opens the Chartbook specified by the **ChartbookFileName** parameter.

#### Parameters

* **ChartbookFileName**: The path and filename of the chartbook to be opened. This must include the file extension (.cht). The full path can be included, but if not present then the default path to the data files folder, as defined by the [Data Files Folder](GeneralSettings.md#datafilesfolder) setting is used.

### sc.OpenChartOrGetChartReference()

[Link](#scopenchartorgetchartreference) - [Top](#top)

**Type**: Function

int **OpenChartOrGetChartReference**(s\_ACSOpenChartParameters & ACSOpenChartParameters);

The **sc.OpenChartOrGetChartReference** function returns the Chart Number of a chart matching a given set of parameters if there is already an open chart within the Chartbook that contains the study calling the **sc.OpenChartOrGetChartReference** function, that matches all of the given set of parameters. In this case the Chart Number of that chart will be returned.

Otherwise, a new chart will be automatically opened with the given set of parameters, and the Chart Number of the new chart will be returned.

If there is an error encountered within the function, the function return value will be **0**.

For an example to use this function, refer to the **scsf\_OpenChartOrGetChartReferenceExample** function in the **/ACS\_Source/studies.cpp** file located in the Sierra Chart installation folder on your system.

If the chart that has been automatically opened with this function, does not need to be viewed, then its window can be minimized to prevent any graphics output which eliminates the CPU load related to graphics output.

After you obtain the Chart Number with this function, then you can access the data from this chart with the [sc.GetChartBaseData()](#scgetchartbasedata) function.

For efficiency, only call the **sc.OpenChartOrGetChartReference** function when **sc.IsFullRecalculation** is nonzero.

This function cannot be called from within the [sc.SetDefaults](ACSIL_Members_Variables_And_Arrays.md#scsetdefaults) code block. It will result in an incorrect Chart Number being used, when a Chartbook is being opened and one of the studies in the Chartbook makes a call to the **sc.OpenChartOrGetChartReference()** function. Therefore, it must be called below the **sc.SetDefaults** code block.

#### Parameters

The parameters of the requested chart are specified using the **s\_ACSOpenChartParameters** structure. This structure contains the following parameters:

* **PriorChartNumber**: This is the first parameter that gets checked. If the **sc.OpenChartOrGetChartReference** function has been called at least once before, remember the Chart Number that gets returned, and set it into this parameter. This allows for a more efficient lookup. Set this parameter to **0** if the Chart Number is unknown.
* **ChartDataType**: Set this to **DAILY\_DATA** for a Historical Daily data chart, or **INTRADAY\_DATA** for an Intraday data chart.
* [Symbol](#commonfunctionparameterdescriptionssymbol): Set this to the symbol for the requested chart. The symbol must be in the format required by the selected **Service** in **Global Settings >> Data/Trade Service Settings**.
    
     
  These will be the same symbols that you will see listed in **File >> Find Symbol**.
    
     
  When you need to use the Symbol of the chart the study function is on, the easiest way to get the correct symbol is to use the **sc.Symbol** ACSIL structure member.
* **IntradayBarPeriodType**: This is used for an Intraday chart and sets the period/type of the chart bar. Must be one of the below values. It is also necessary to set the actual associated value through the **IntradayBarPeriodLength** member.
  + IBPT\_DAYS\_MINS\_SECS
  + IBPT\_VOLUME\_PER\_BAR
  + IBPT\_NUM\_TRADES\_PER\_BAR
  + IBPT\_RANGE\_IN\_TICKS\_STANDARD
  + IBPT\_RANGE\_IN\_TICKS\_NEWBAR\_ON\_RANGEME
  + IBPT\_RANGE\_IN\_TICKS\_TRUE
  + IBPT\_RANGE\_IN\_TICKS\_FILL\_GAPS
  + IBPT\_REVERSAL\_IN\_TICKS
  + IBPT\_RENKO\_IN\_TICKS
  + IBPT\_DELTA\_VOLUME\_PER\_BAR
  + IBPT\_FLEX\_RENKO\_IN\_TICKS
  + IBPT\_RANGE\_IN\_TICKS\_OPEN\_EQUAL\_CLOSE
  + IBPT\_PRICE\_CHANGES\_PER\_BAR
  + IBPT\_MONTHS\_PER\_BAR
  + IBPT\_POINT\_AND\_FIGURE
  + IBPT\_FLEX\_RENKO\_IN\_TICKS\_INVERSE\_SETTINGS
  + IBPT\_ALIGNED\_RENKO
  + IBPT\_RANGE\_IN\_TICKS\_NEW\_BAR\_ON\_RANGE\_MET\_OPEN\_EQUALS\_PRIOR\_CLOSE
  + IBPT\_ACSIL\_CUSTOM
  + IBPT\_HISTORICAL\_DAILY\_DATA\_DAYS\_PER\_BARTo determine the **Bar Period Type** that the chart currently uses, call functions like [sc.AreTimeSpecificBars()](#scaretimespecificbars).
* **IntradayBarPeriodLength**: This is used for Intraday charts, in conjunction with the **IntradayBarPeriodType** parameter.
* **DaysToLoad**: This sets the number of days of data that will be loaded into the chart whether it is a Historical Daily chart or an Intraday chart. If this value is left at 0, then the **Chart >> Chart Settings >> Use Number of Days to Load >> Days to Load** setting of the calling chart is used.
    
     
  When getting a reference to an existing chart, if the existing chart has a higher Days to Load setting, then that chart will be returned and that Days to Load setting for the existing chart will remain.
* **SessionStartTime**, **SessionEndTime**: These specify the primary Session Start and End times. These session times are optional and only apply to Intraday charts. If the session times are not specified, then the Intraday Session Times from [Global Symbol Settings](GlobalSymbolSettings.md) are used.
* **EveningSessionStartTime**, **EveningSessionEndTime**: The evening session times are optional, and only apply to Intraday charts. If the evening session times are not specified, then the Intraday Session Times from [Global Symbol Settings](GlobalSymbolSettings.md) are used.
* **IntradayBarPeriodParm2**: This is used when **IntradayBarPeriodType** is set to IBPT\_FLEX\_RENKO\_IN\_TICKS. This is the Trend Offset.
* **IntradayBarPeriodParm3**: This is used when **IntradayBarPeriodType** is set to IBPT\_FLEX\_RENKO\_IN\_TICKS. This is the Reversal Offset.
* **IntradayBarPeriodParm4**: This is used when **IntradayBarPeriodType** is set to IBPT\_FLEX\_RENKO\_IN\_TICKS. This is the **New Bar When Exceeded** option. This can be set to 1 or 0.
* **HistoricalChartBarPeriod**: In the case of when **ChartDataType** is set to **DAILY\_CHART**, then this specifies the time period for each chart bar. It can be one of the following constants:
  + **HISTORICAL\_CHART\_PERIOD\_DAYS**
  + **HISTORICAL\_CHART\_PERIOD\_WEEKLY**
  + **HISTORICAL\_CHART\_PERIOD\_MONTHLY**
  + **HISTORICAL\_CHART\_PERIOD\_QUARTERLY**
  + **HISTORICAL\_CHART\_PERIOD\_YEARLY**
* **HistoricalChartBarPeriodLengthInDays**: When **HistoricalChartBarPeriod** is set to **HISTORICAL\_CHART\_PERIOD\_DAYS**, then this variable can be set to the number of days per bar in a Historical Chart. The default is 1. This variable only applies to Historical charts and not Intraday charts.
* **int ChartLinkNumber**: This can be optionally set to a nonzero [Chart Link Number](WorkingWithCharts.md#chartlinking). The default is 0.
* **ContinuousFuturesContractOption**: This can be set to one of the following constants:
  + **CFCO\_NONE**
  + **CFCO\_DATE\_RULE\_ROLLOVER**
  + **CFCO\_VOLUME\_BASED\_ROLLOVER**
  + **CFCO\_DATE\_RULE\_ROLLOVER\_BACK\_ADJUSTED**
  + **CFCO\_VOLUME\_BASED\_ROLLOVER\_BACK\_ADJUSTED**
* **LoadWeekendData**: Set this to 1 to load weekend (Saturday and Sunday) data, the default, or to zero to not load weekend data. This only applies to Intraday charts.
* **UseEveningSession**: Set this to 1 to use the Session Times >> Evening Start and Evening End times set for the chart.
* **HideNewChart**: Set this to 1 to cause the chart to be hidden and not visible. It can be displayed through the **CW** menu. To minimize system resources, it is recommended to enable **Global Settings >> General Settings >> GUI >> Application GUI**  **>> Destroy Chart Windows When Hidden**.
* **AlwaysOpenNewChart**: Set this to 1 to always open a new chart when calling the **sc.OpenChartOrGetChartReferencefunction** function under all conditions.
* **IsNewChart**: This variable is set to 1, if a new chart is opened by the **sc.OpenChartOrGetChartReferencefunction** function. So this variable is not set by your study function but it is set by **sc.OpenChartOrGetChartReferencefunction** upon returning.
* **IncludeColumnsWithNoData**: Set this to 1, to enable the [Include Columns With No Data](ChartSettings.md#includecolumnswithnodata) setting for the chart.
* **UpdatePriorChartNumberParametersToMatch**: This variable only applies when **PriorChartNumber** has been set and the chart number specified actually exists within the Chartbook which contains the chart, which contains the study instance calling the **sc.OpenChartOrGetChartReferencefunction** function.
    
     
  When this is set to 1 and the chart parameters do not match the existing found chart, that chart will have its parameters updated to match.
* **ChartTimeZone**: This is an optional parameter and specifies the Time Zone to use for the chart as a string. If is not specified, the global time zone will be used. The available time zones are listed in the /ACS\_Source/SCConstants.h file. You can get the time zone for the chart, that your study instance is applied to, through the **sc.GetChartTimeZone()** function.

### sc.OpenFile()

[Link](#scopenfile) - [Top](#top)

**Type**: Function

int **OpenFile**(const SCString& **PathAndFileName**, const int **Mode**, int& **FileHandle**);

The **sc.OpenFile** function opens the file specified by **PathAndFileName** per the specified **Mode** and puts the File Handle into **FileHandle**.

The function returns **True** if the file is able to be opened in the specified Mode. Otherwise it returns **False**.

#### Parameters

* **PathAndFileName**: An [SCString](ACSILProgrammingConcepts.md#workingwithtextstrings) variable with the path and filename to the file.
* **Mode**: An enumeration that sets the mode in which the file will be opened. The following are available:
  + FILE\_MODE\_CREATE\_AND\_OPEN\_FOR\_READ\_WRITE
  + FILE\_MODE\_OPEN\_EXISTING\_FOR\_SEQUENTIAL\_READING
  + FILE\_MODE\_OPEN\_TO\_APPEND
  + FILE\_MODE\_OPEN\_TO\_REWRITE\_FROM\_START
* [FileHandle](#commonfunctionparameterdescriptionsfilehandle): A integer variable that contains the File Handle of the opened file. This handle is used with the [sc.ReadFile](#screadfile) and [sc.WriteFile](#scwritefile) functions.

Also refer to [sc.OpenFile](#scopenfile), [sc.CloseFile](#scclosefile), [sc.ReadFile](#screadfile), [sc.WriteFile](#scwritefile), [sc.GetLastFileErrorCode](#scgetlastfileerrorcode).

### sc.OpenSpreadsheet()

[Link](#scopenspreadsheet) - [Top](#top)

**Type**: Function

int32\_t **OpenSpreadsheet**(const SCString& **SheetCollectionName**);

The **sc.OpenSpreadsheet()** function opens an existing spreadsheet or creates a new one if an existing spreadsheet of the given name does not already exist.

#### Parameters

* **SheetCollectionName**: The name of the spreadsheet to open. The full path to the spreadsheet can be given. If the full path is not included, then the default path for a spreadsheet (the **Data** folder under the main Sierra Chart installation folder) is used.

### sc.OrderQuantityToString()

[Link](#scorderquantitytostring) - [Top](#top)

**Type**: Function

void **OrderQuantityToString**(const t\_OrderQuantity32\_64 **Value**, SCString& **OutputString**);

The **sc.OrderQuantityToString** function converts a given Order Quantity to a string format. The result is given in the **OutputString** parameter.

#### Parameters

* **Value**: The Order Quantity value to covert. Note the type of this variable is a t\_OrderQuantity32\_64.
* **OutputString**: The string output from the given order quantity.

### sc.Oscillator()

[Link](#scoscillator) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Oscillator**(SCFloatArrayRef **FloatArrayIn1**, SCFloatArrayRef **FloatArrayIn2**, SCFloatArrayRef **FloatArrayOut**, int **Index**);

SCFloatArrayRef **Oscillator**(SCFloatArrayRef **FloatArrayIn1**, SCFloatArrayRef **FloatArrayIn2**, SCFloatArrayRef **FloatArrayOut**); [Auto-looping only](#noindexparam).

The **sc.Oscillator()** function calculates the difference between FloatArrayIn1 and FloatArrayIn2 at the given Index.

#### Parameters

* [FloatArrayIn1](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayIn2](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

//Calculate the Oscillator between the first two extra arrays in sc.Subgraph[0]
// and output the results to sc.Subgraph[0].Data.
sc.Oscillator(sc.Subgraph[0].Arrays[0], sc.Subgraph[0].Arrays[1], sc.Subgraph[0])

 //Access the study value at the current index
float Oscillator = sc.Subgraph[0][sc.Index];
            
```

### sc.Parabolic()

[Link](#scparabolic) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Parabolic**(SCBaseDataRef **BaseDataIn**, SCDateTimeArray **BaseDateTimeIn**, SCSubgraphRef **SubGraphOut**, int **Index**, float **InStartAccelFactor**, float **InAccelIncrement**, float **InMaxAccelFactor**, unsigned int **InAdjustForGap**);

SCFloatArrayRef **Parabolic**(SCBaseDataRef **BaseDataIn**, SCDateTimeArray **BaseDateTimeIn**, SCSubgraphRef **SubGraphOut**, float **InStartAccelFactor**, float **InAccelIncrement**, float **InMaxAccelFactor**, unsigned int **InAdjustForGap**); [Auto-looping only](#noindexparam).

The **sc.Parabolic()** function calculates the standard parabolic study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [BaseDateTimeIn](#commonfunctionparameterdescriptionsbasedatetimein)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-4] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* **InStartAccelFactor**: The starting acceleration factor. For reference, refer to the default value with the Parabolic study in Sierra Chart.
* **InAccelIncrement**: The acceleration increment. For reference, refer to the default value with the Parabolic study in Sierra Chart.
* **InMaxAccelFactor**: The maximum acceleration factor. For reference, refer to the default value with the Parabolic study in Sierra Chart.
* **InAdjustForGap**: Set this to 1 to adjust the parabolic for price gaps. Otherwise, set it to 0.

#### Example

```cpp

SCSubgraphRef Parabolic = sc.Subgraph[0];

sc.Parabolic(
    sc.BaseDataIn,
    sc.BaseDateTimeIn,

    Parabolic,
    sc.Index,
    StartAccelerationFactor.GetFloat(),
    AccelerationIncrement.GetFloat(),

    MaxAccelerationFactor.GetFloat(),
    AdjustForGap.GetYesNo(),
    InputDataHigh.GetInputDataIndex(),

    InputDataLow.GetInputDataIndex()
);

float SAR = Parabolic[sc.Index]; //Access the study value at the current index
            
```

### sc.PauseChartReplay()

[Link](#scpausechartreplay) - [Top](#top)

**Type**: Function

int **PauseChartReplay**(int **ChartNumber**);

The **sc.PauseChartReplay** function pauses a chart replay for the chart specified by the **ChartNumber** parameter. This function can only pause the replay for the single specified chart.

It is only possible to specify Chart Numbers that are within the same Chartbook which contains the chart which contains the study instance that this function is called from.

The function returns a value of 0 if the chart is not able to be found. Otherwise, the function returns a value of 1.

The chart replay is paused *after* the study function returns.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

#### Example

```cpp

            int Result = sc.PauseChartReplay(sc.ChartNumber);
            
```

### sc.PlaySound()

[Link](#scplaysound) - [Top](#top)

### sc.AlertWithMessage()

[Link](#scalertwithmessage) - [Top](#top)

**Type**: Function

int **PlaySound**(int **AlertNumber**);

int **PlaySound**(int **AlertNumber**, const SCString& **AlertMessage**, int **ShowAlertLog** = 0)

int **PlaySound**(SCString& **AlertPathAndFileName**, int **NumberTimesPlayAlert** = 1);

int **PlaySound**(const char \*AlertPathAndFileName, int NumberTimesPlayAlert = 1);

int **PlaySound**(SCString& **AlertPathAndFileName**, int **NumberTimesPlayAlert**, const SCString &**AlertMessage**, int **ShowAlertLog** = 0)

int **AlertWithMessage**(int **AlertNumber**, const SCString& **AlertMessage**, int **ShowAlertLog** = 0)

int **AlertWithMessage**(int **AlertNumber**, const char\* **AlertMessage**, int **ShowAlertLog** = 0)

To play an alert sound when a condition is TRUE, it is recommended to use the [sc.SetAlert](#scsetalert) function, instead of the **sc.PlaySound/sc.AlertWithMessage** function, since it provides a more controlled logic for providing alerts.

The **sc.PlaySound/sc.AlertWithMessage** function is used to play the alert sound associated with the **AlertNumber** parameter or the file specified by the **AlertPathAndFileName** parameter.

A sound will be played every time this function is called. There is no restriction logic used as is the case with the [sc.SetAlert()](#scsetalert) function.

The alerts sounds are queued up and played asynchronously. This function returns 1 on success, and 0 on failure.

Refer to the **scsf\_LogAndAlertExample()** function in the **/ACS\_Source/studies.cpp** file in the Sierra Chart installation folder for example code to work with this function.

An Alert Message is added to the **Alerts Log** when this function is called. To open the Alerts Log, select **Window >> Alert Manager >> Alerts Log**.

#### Parameters

* **AlertNumber**: The **AlertNumber** parameter specifies a particular alert sound to play which is associated with this number. These Alert Numbers are configured through the **Global Settings >> General Settings** window. For complete documentation, refer to [Alert Sound Settings](GeneralSettings.md#tabalerts). Specify one of the numbers which is supported in the Alert Sound Settings.
* **AlertMessage**: The alert message to add to the **Alerts Log**. **AlertMessage** can either be an **SCString** type or a plain C++ string. For information about **AlertMessage** and how to set this parameter, refer to the [sc.AddAlertLine()](#scaddalertline) function.
* **ShowAlertLog**: **ShowAlertLog** needs to be set to **1** to cause the **Alerts Log** to open up when a message is added. Otherwise, **ShowAlertLog** needs to be **0** or it can be left out.
* **AlertPathAndFileName**: The complete path and filename text string for the **wav** sound file to play.
* **NumberTimesPlayAlert**: The number of times to play the specified Alert Number or specified sound file.

#### Example

```cpp

sc.PlaySound(45); // Plays Alert Sound Number 45

sc.PlaySound(1,"My Alert Message");

sc.PlaySound(1,"My Alert Message that opens the Alerts Log",1);

sc.PlaySound("C:\WavFiles\MyAlert.wav",1,"My Alert Message"); 
            
```

### sc.PriceValueToTicks()

[Link](#scpricevaluetoticks) - [Top](#top)

**Type**: Function

unsigned int **PriceValueToTicks**(float **PriceValue**);

The **sc.PriceValueToTicks** function returns the number of ticks represented by the given price value.

#### Parameters

* **PriceValue**: The price for which the number of ticks is to be determined.

### sc.PriceVolumeTrend()

[Link](#scpricevolumetrend) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **PriceVolumeTrend**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**);

SCFloatArrayRef **PriceVolumeTrend**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**); [Auto-looping only](#noindexparam).

The **sc.PriceVolumeTrend()** function calculates the Price Volume Trend study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.PriceVolumeTrend(sc.BaseDataIn, sc.Subgraph[0]);

float PriceVolumeTrends = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.RandomWalkIndicator()

[Link](#scrandomwalkindicator) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **RandomWalkIndicator**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **RandomWalkIndicator**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.RandomWalkIndicator()** function calculates the Random Walk Indicator study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-3] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.RandomWalkIndicator(sc.BaseDataIn, sc.Subgraph[0], 10);

//Access the individual lines
float High = sc.Subgraph[0][sc.Index];

float Low = sc.Subgraph[0].Arrays[0][sc.Index];

//Copy Low to a visible Subgraph
sc.Subgraph[1][sc.Index] = Low; 
            
```

### sc.ReadFile()

[Link](#screadfile) - [Top](#top)

**Type**: Function

int **ReadFile**(const int **FileHandle**, char\* **Buffer**, const int **BytesToRead**, unsigned int\* **p\_BytesRead**);

The **sc.ReadFile()** function reads a file opened with [sc.OpenFile()](#scopenfile) using the **FileHandle**. It reads the number of **BytesToRead** and stores them in **Buffer**. The actual number of bytes read is then stored in **p\_BytesRead**, which could be less than the number of bytes requested, if for instance, it reaches the end of the file before reading in the requested number of bytes.

The function returns **0** if there is an error reading the bytes from the file (this does not include hitting the End of File). Otherwise, the function returns **1**.

#### Parameters

* [FileHandle](#commonfunctionparameterdescriptionsfilehandle)
* **Buffer**: The pointer to the buffer where the data read will be placed into. This buffer needs to be allocated ahead of calling this function. It can be allocated either on the stack or heap.
* **BytesToRead**: The size of the  **Buffer** in bytes.
* **p\_BytesRead**: A pointer to the variable that stores the actual number of bytes read from the file. This will not exceed **BytesToRead**.

Also refer to [sc.OpenFile](#scopenfile), [sc.CloseFile](#scclosefile), [sc.ReadFile](#screadfile), [sc.WriteFile](#scwritefile), [sc.GetLastFileErrorCode](#scgetlastfileerrorcode).

### sc.ReadIntradayFileRecordAtIndex()

[Link](#screadintradayfilerecordatindex) - [Top](#top)

**Type**: Function

int **ReadIntradayFileRecordAtIndex**(int64\_t **Index**, s\_IntradayRecord& **r\_Record**, IntradayFileLockActionEnum **IntradayFileLockAction**);

The **sc.ReadIntradayFileRecordAtIndex()** function is for reading the actual Intraday chart data file records in the Intraday chart data file for the chart the study instance is applied to which is calling this function.

The **Index** parameter specifies the Intraday file index. It is a zero-based index.

For an example to use this function, refer to the function **scsf\_ReadFromUnderlyingIntradayFileExample** in the **/ACS\_Source/Studies2.cpp** file in the folder Sierra Chart is installed to.

When reading records from the Intraday chart data file a lock is necessary. This is specified through the **IntradayFileLockAction** function parameter. The use of the lock must be completely efficient and proper during the reading of Intraday file records within a call into the study function.

The lock will need to be obtained when reading the first record and released after reading the last record during the call to the study function. If only a single record is read, the lock will need to be obtained before reading that record and released after.

If reading multiple records, the first record needs to be read using this lock enumeration: IFLA\_LOCK\_READ\_HOLD. When reading additional records but not the last record use: IFLA\_NO\_CHANGE. When reading the last record, use: IFLA\_RELEASE\_AFTER\_READ. If there is only a need to read one record, then use: IFLA\_LOCK\_READ\_RELEASE.

#### Parameters

* [Index](#commonfunctionparameterdescriptionsindex)
* **r\_Record**: A reference to a structure of type s\_IntradayRecord, that returns the record that is read at the Index.
* **IntradayFileLockAction**: The file lock action to take when using this function. This can be one of the following:
  + **IFLA\_LOCK\_READ\_HOLD = 1**
  + **IFLA\_NO\_CHANGE = 2**
  + **IFLA\_RELEASE\_AFTER\_READ = 3**
  + **IFLA\_LOCK\_READ\_RELEASE = 4**

### sc.ReadIntradayFileRecordForBarIndexAndSubIndex()

[Link](#screadintradayfilerecordforbarindexandsubindex) - [Top](#top)

**Type**: Function

int **ReadIntradayFileRecordForBarIndexAndSubIndex**)(int **BarIndex**, int **SubRecordIndex**, s\_IntradayRecord& **r\_Record**, IntradayFileLockActionEnum **IntradayFileLockAction**);

The **sc.ReadIntradayFileRecordForBarIndexAndSubIndex()** function is for reading the Intraday chart data file records from the chart data file (**.scid** file extension) for the chart at a particular chart bar index. This will allow you to access all of the individual Intraday chart data records contained within each chart bar.

This function should not be used to read the records in every chart bar at a time since that will cause the user interface of Sierra Chart to freeze for an extended time if there is a lot of tick by tick data loaded into the chart. It should be used only on the current day as needed.

For an example to use this function, refer to the function **scsf\_ReadChartBarRecordsFromUnderlyingIntradayFileExample** in the **/ACS\_Source/Studies2.cpp** file.

In the case of tick by tick data, the s\_IntradayRecord& **r\_Record** record parameter will have the Ask price in the High field and the Bid price in the Low field. The open will be 0.

When reading records from the Intraday chart data file a lock is necessary. This is specified through the **IntradayFileLockAction** function parameter. The use of the lock must be completely efficient and proper during the reading of Intraday file records within a call into the study function. The lock will need to be obtained when reading the first record and released after reading the last record during the call to the study function. If only a single record is read, the lock will need to be locked and released during the reading of that record.

If reading multiple records, the first record needs to be read using this lock enumeration: IFLA\_LOCK\_READ\_HOLD. When reading additional records but not the last record use: IFLA\_NO\_CHANGE. When reading the last record, use: IFLA\_RELEASE\_AFTER\_READ. If there is only a need to read one record, then use: IFLA\_LOCK\_READ\_RELEASE.

The **sc.ReadIntradayFileRecordForBarIndexAndSubIndex()** function is in no way affected by the [Session Times](SessionTimes.md) for the chart containing the ACSIL function which calls this function. If you want to stop reading data outside of the Session Times, that needs to be implemented by you.

When Intraday records are [combined into a Summary Trade](ChartSettings.md#combinetradesintooriginalsummarytrade), the first underlying Intraday file record index which is set to be the starting index for an Intraday chart bar, is the *ending* index among the underlying Intraday file records which makes up the summary trade. This is something to be aware of when using this function. In this case you are not going to necessarily get the first Intraday record associated with the specified **BarIndex** and when **SubRecordIndex** is set to 0.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex)
* **SubRecordIndex**: The index within the bar for which the file record is to be retrieved.
* **r\_Record**: A reference to a structure of type s\_IntradayRecord, that returns the record that is read at the Index.
* **IntradayFileLockAction**: The file lock action to take when using this function. This can be one of the following:
  + **IFLA\_LOCK\_READ\_HOLD = 1**
  + **IFLA\_NO\_CHANGE = 2**
  + **IFLA\_RELEASE\_AFTER\_READ = 3**
  + **IFLA\_LOCK\_READ\_RELEASE = 4**

### sc.RecalculateChart()

[Link](#screcalculatechart) - [Top](#top)

**Type**: Function

int **RecalculateChart**(int **ChartNumber**);

The **sc.RecalculateChart()** function recalculates the chart specified by the **ChartNumber** parameter. The recalculation happens on a delay. It happens the next time the specified chart performs an update.

For more information about the ChartNumber parameter, refer to [sc.ChartNumber](ACSIL_Members_Variables_And_Arrays.md#scchartnumber).

This function is normally used after changing a study Input with functions like [sc.SetChartStudyInputInt()](#scsetchartstudyinputint).

When using **sc.RecalculateChart**, the study arrays will not be cleared. The study function will be called with sc.Index, assuming auto looping, initially being set to 0. Your study needs to perform calculations that it normally does starting at that bar index. In the case of when opening the Chart Studies window and then pressing OK, in that particular case the study arrays are completely cleared and reallocated and will have a default value of 0 at each element. This clearing of arrays does not happen when sc.RecalculateChart is used.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.RecalculateChartImmediate()

[Link](#screcalculatechartimmediate) - [Top](#top)

**Type**: Function

int **RecalculateChart**(int **ChartNumber**);

The **sc.RecalculateChartImmediate()** function recalculates the chart specified by the **ChartNumber** parameter. The recalculation happens immediately before the study function returns.

It is not possible to recalculate the chart that the study function instance that is calling this function is applied to. In this case 0 is returned and nothing happens.

This function is normally used after changing a study Input with functions like [sc.SetChartStudyInputInt()](#scsetchartstudyinputint).

When using **sc.RecalculateChartImmediate**, the study arrays will not be cleared. The study functions will be called with sc.Index, assuming auto looping, initially being set to 0. Your study needs to perform calculations that it normally does starting at that bar index. In the case of when opening the Chart Studies window and then pressing OK, in that particular case the study arrays are completely cleared and reallocated and will have a default value of 0 at each element. This clearing of arrays does not happen when sc.RecalculateChartImmediate is used.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.ReCenterConstantRangeScale()

[Link](#screcenterconstantrangescale) - [Top](#top)

**Type**: Function

int32\_t **ReCenterConstantRangeScale**(const int32\_t **ChartNumber**);

The **sc.ReCenterConstantRangeScale()** function recenters the given chart if that chart is setup with a Constant Range scale.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.RefreshChartTradingDrawings()

[Link](#screfreshcharttradingdrawings) - [Top](#top)

**Type**: Function

int32\_t **RefreshChartTradingDrawings**(int32\_t **ChartNumber**);

The **sc.RefreshChartTradingDrawings()** function forces an update to the Position and Working Orders lines for the specified chart.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)

### sc.RefreshTradeData()

[Link](#screfreshtradedata) - [Top](#top)

**Type**: Function

int **RefreshTradeData**();

The **sc.RefreshTradeData()** function performs the very same action as selecting **Trade >> Refresh Trade Data from Service**. Refer to the [Refresh Trade Data From Service](TradeMenu.md#refreshtradedatafromservice) documentation for further information.

Normally there is never a reason to use this function. It is generally *never recommended* to make a call to this function. It can cause a problem where the trading server ignores one or more requests related to the requests made in response to this function call if there are too many of them over a short period of time, potentially causing an inconsistent state with the orders table in Sierra Chart, or Sierra Chart ignores the request because there is already an outstanding request in progress.

#### Parameters

* This function has no parameters

### sc.RegionValueToYPixelCoordinate()

[Link](#scregionvaluetoypixelcoordinate) - [Top](#top)

**Type**: Function

int **RegionValueToYPixelCoordinate** (float **RegionValue**, int **ChartRegionNumber**);

The **sc.RegionValueToYPixelCoordinate** function calculates the Y-axis pixel coordinate for the given **RegionValue** and the zero-based **ChartRegionNumber** which specifies the Chart Region.

The returned y-coordinate is in relation to the chart window itself.

#### Parameters

* **RegionValue**: The scale value within the Scale Range of the specified Chart Region.
* **ChartRegionNumber**: The zero-based index of the Chart Region.

#### Example

```cpp

int YPixelCoordinate = sc.RegionValueToYPixelCoordinate(sc.ActiveToolYValue, sc.GraphRegion);
            
```

### sc.RelayDataFeedAvailable()

[Link](#screlaydatafeedavailable) - [Top](#top)

**Type**: Function

void **RelayDataFeedAvailable**();

#### Parameters

* This function has no parameters

### sc.RelayDataFeedUnavailable()

[Link](#screlaydatafeedunavailable) - [Top](#top)

**Type**: Function

void **RelayDataFeedUnavailable**();

#### Parameters

* This function has no parameters

### sc.RelayNewSymbol()

[Link](#screlaynewsymbol) - [Top](#top)

**Type**: Function

int **RelayNewSymbol**(const SCString& **Symbol**, int **ValueFormat**, float **TickSize**, const SCString& **ServiceCode**);

The **sc.RelayNewSymbol** function is used along with the [sc.RelayTradeUpdate](#screlaytradeupdate) function to allow an Advanced Custom Study to be able to generate its own custom trading data which can be independently charted as a normal symbol through an Intraday chart.

The first step is to make a call to the **sc.RelayNewSymbol** function after Sierra Chart is connected to the data feed. Use the [sc.ServerConnectionState](ACSIL_Members_Variables_And_Arrays.md#scserverconnectionstate) member variable to determine when connected to the data feed.

#### Parameters

* [Symbol](#commonfunctionparameterdescriptionssymbol)
* **ValueFormat**: The [ValueFormat](ACSIL_Members_Variables_And_Arrays.md#scvalueformat) for the symbol.
* **TickSize**: The tick size for the symbol. This is a floating-point value.
* **ServiceCode**: The symbol can have a custom identifier associated with it when it is sent through the Sierra Chart DTC Protocol server. This is set into the **Exchange** field of messages. The **ServiceCode** is this identifier.

### sc.RelayServerConnected()

[Link](#screlayserverconnected) - [Top](#top)

**Type**: Function

int **RelayServerConnected**();

#### Parameters

* This function has no parameters.

### sc.RelayTradeUpdate()

[Link](#screlaytradeupdate) - [Top](#top)

**Type**: Function

int **RelayTradeUpdate**(SCString& **Symbol**, SCDateTime& **DateTime**, float **TradeValue**, unsigned int **TradeVolume**, int **WriteRecord**);

The **sc.RelayTradeUpdate** function is used along with the [sc.RelayNewSymbol](#screlaynewsymbol) function to allow an Advanced Custom Study to be able to generate its own custom trading data which can be independently charted as a normal symbol through an Intraday chart.

Call the **sc.RelayTradeUpdate** when the custom study wants to generate a trade for its own custom calculations and have that recorded in the Intraday data file for its custom symbol.

#### Parameters

* [Symbol](#commonfunctionparameterdescriptionssymbol)
* [DateTime](#commonfunctionparameterdescriptionsdatetime)
* **TradeValue**: The value of the trade as a floating-point value.
* **TradeVolume**: The volume of the trade as an integer.
* **WriteRecord**: A flag indicating whether data should be written to the Intraday data file or not. Use 1 to cause the data to be written. Use 0 to cause the data not to be written.

### sc.RemoveACSChartShortcutMenuItem()

[Link](#scremoveacschartshortcutmenuitem) - [Top](#top)

Refer to the [sc.RemoveACSChartShortcutMenuItem()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scremoveacschartshortcutmenuitem) page for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.RemoveStudyFromChart()

[Link](#scremovestudyfromchart) - [Top](#top)

**Type**: Function

void **RemoveStudyFromChart**(const int **ChartNumber**, const int **StudyID**);

The **sc.RemoveStudyFromChart** removes the given study from a chart.

The study is removed after a delay. Not immediately.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)

### sc.ResizeArrays()

[Link](#scresizearrays) - [Top](#top)

**Type**: Function

int **ResizeArrays**(int **NewSize**);

**sc.ResizeArrays()** resizes all of the [sc.Subgraph[].Data[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphData) arrays to the size specified with the **NewSize** parameter. This function is only useful when you have set **[sc.IsCustomChart](ACSIL_Members_Variables_And_Arrays.md#sciscustomchart)** to 1 (TRUE). The function returns 0 if it fails to resize all the arrays. This function also affects the [sc.DateTimeOut[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scDateTimeOut) and [sc.Subgraph[].DataColor[]](index40e9.html?page=doc/ACSIL_Members_scSubgraph.html#scSubgraphDataColor) arrays.

#### Parameters

* **NewSize**: The size to which the arrays will be changed.

#### Example

```cpp

sc.ResizeArrays(100); // Resize the arrays to 100 elements
            
```

### sc.ResumeChartReplay()

[Link](#scresumechartreplay) - [Top](#top)

**Type**: Function

int **ResumeChartReplay**(int **ChartNumber**);

The **sc.ResumeChartReplay** function resumes a chart replay for the chart specified by the **ChartNumber** parameter.

It is only possible to specify Chart Numbers that are within the same Chartbook which contains the chart which contains the study instance that this function is called from.

The chart replay is resumed *after* the study function returns.

A return value of 0 is sent if the referenced chart is not found. Otherwise a return value of 1 is returned.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

#### Example

```cpp

            int Result = sc.ResumeChartReplay(sc.ChartNumber);
            
```

### sc.RGBInterpolate()

[Link](#scrgbinterpolate) - [Top](#top)

**Type**: Function

COLORREF **RGBInterpolate**(const COLORREF& **Color1**, const COLORREF& **Color2**, float **ColorDistance**);

The **sc.RGBInterpolate()** function returns the color at the RGB distance between **Color1** and **Color2**, where **ColorDistance** is a value between 0 and 1. If **ColorDistance** is 0, then **Color1** is returned. If **ColorDistance** is 1, then **Color2** is returned. If **ColorDistance** is 0.5f, then the color half way between **Color1** and **Color2** is returned.

#### Parameters

* **Color1**: A COLORREF parameter that sets the first color for the interpolation. This can be specified directly in hexadecimal, or with the use of the RGB() function.
* **Color2**: A COLORREF parameter that sets the second color for the interpolation. This can be specified directly in hexadecimal, or with the use of the RGB() function.
* **ColorDistance**: The relative percentage as a decimal value, for the interpolation between Color1 and Color2.

#### Example

```cpp

COLORREF NewColor = sc.RGBInterpolate(RGB(255,0,0), RGB(0,255,0), 0.5);
            
```

### sc.Round()

[Link](#scround) - [Top](#top)

**Type**: Function

int **Round**(float **Number**)

The **sc.Round()** function rounds the given floating-point **Number** to the nearest integer.

#### Parameters

* **Number**: The floating point value to be rounded.

#### Example

```cpp

int Rounded = sc.Round(1.2);

//1.2 rounded will be equal to 1
            
```

### sc.RoundToTickSize() / sc.RoundToIncrement()

[Link](#scroundtoticksize) - [Top](#top)

**Type**: Function

float **RoundToTickSize**(float **Number**, float **Increment**)

The **sc.RoundToTickSize()** and **sc.RoundToIncrement()** functions round the given floating-point **Number** to the nearest **Increment**. These functions are the same, they just have different names.

#### Parameters

* **Number**: The floating point number to be rounded.
* **Increment**: The increment at which the floating point value should be rounded.

#### Example

```cpp

int Rounded = sc.RoundToTickSize(1.2,0.25);

//1.2 rounded to the increment of .25 will equal 1.25
            
```

### sc.RSI()

[Link](#scrsi) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **RSI**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, unsigned int **MovingAverageType**, int **Length**)

SCFloatArrayRef **RSI**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, unsigned int **MovingAverageType**, int **Length**) [Auto-looping only](#noindexparam).

The **sc.RSI()** function calculates the Wilders Relative Strength Index study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-3] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)
* [MovingAverageType](#movavgtype)

#### Example

```cpp

sc.RSI(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], MOVAVGTYPE_SIMPLE, 20);

float RSI = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.SaveChartbook()

[Link](#scsavechartbook) - [Top](#top)

**Type**: Function

int **SaveChartbook**();

The **sc.SaveChartbook()** function will save the Chartbook containing the chart this study function instance is applied to.

This saving occurs immediately when this function is called and will be complete when it returns. So it occurs synchronously.

#### Parameters

* This function has no parameters

### sc.SaveChartImageToFileExtended()

[Link](#scsavechartimagetofileextended) - [Top](#top)

**Type**: Function

void **SaveChartImageToFileExtended**(int **ChartNumber**, SCString& **OutputPathAndFileName**, int **Width**, int **Height**, int **IncludeOverlays**);

The **sc.SaveChartImageToFileExtended()** function saves the chart specified by the **ChartNumber** parameter to the file specified by the **OutputPathAndFileName** parameter. The saving of the chart occurs on a delay and happens *after* the study function returns.

If this function is called multiple times during a call into a study function, only the most recent call will be processed. The other calls to this function will be disregarded.

A chart image can be taken with this function, when it is hidden (**Window >> Hide Window**). Although the **IncludeOverlays** parameter must be set to 0 in this case. A chart image cannot be taken when it is destroyed. Refer to the setting [DestroyChartWindowsWhenHidden](GeneralSettings.md#destroychartwindowswhenhidden).

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* **OutputPathAndFileName**: The path and filename to save the chart image to. The format of the image is PNG so the file extension should be .png.
* **Width**: The width of the chart image in pixels. The chart will be resized if this is set to a nonzero value. Set this to 0 to not use this parameter.
* **Height**: The height of the chart image in pixels. The chart will be resized if this is set to a nonzero value. Set this to 0 to not use this parameter.
* **IncludeOverlays**: When this is set to 1 or any nonzero value, then any other windows which overlay the chart will also be included in the chart image.

Also refer to [sc.SaveChartImageToFile](ACSIL_Members_Variables_And_Arrays.md#scsavechartimagetofile) and [sc.UploadChartImage()](#scuploadchartimage).

#### Example

```cpp

sc.SaveChartImageToFileExtended( sc.ChartNumber, "ImageFilename.PNG", 0, 0, 0);
            
```

### sc.SaveMainWindowImageToFile()

[Link](#scsavemainwindowimagetofile) - [Top](#top)

**Type**: Function

int **SaveMainWindowImageToFile**(const SCString& **OutputPathAndFileName**);

The **sc.SaveMainWindowImageToFile()** function saves an image of the main window to the specified output path and filename.

#### Parameters

* **OutputPathAndFileName**: The path and filename for where to save the image.

### sc.SCDataFeedSymbol()

[Link](#scscdatafeedsymbol) - [Top](#top)

**Type**: Function

SCString **SCDataFeedSymbol**();

The **sc.SCDataFeedSymbol()** function returns an SCString that contains the name of the symbol used for the Sierra Chart Data Feed as defined in the symbol settings for the symbol of the chart that has the study that calls this function.

#### Parameters

* This function has no parameters.

### sc.SecondsSinceStartTime()

[Link](#scsecondssincestarttime) - [Top](#top)

**Type**: Function

int **SecondsSinceStartTime**(const SCDateTime& **BarDateTime**);

The **sc.SecondsSinceStartTime()** function returns the number of seconds from the beginning of the trading session as defined by the [Start Time](SessionTimes.md#starttime) until the given **BarDateTime** parameter.

#### Parameters

* **BarDateTime**: An SCDateTime parameter that defines the ending time for which the seconds since the start of the trading session is determined.

### sc.SecurityType

[Link](#scsecuritytype) - [Top](#top)

**Type**: Function.

n\_ACSIL::DTCSecurityTypeEnum SecurityType()

The **sc.SecurityType()** function returns the security type for the symbol of the chart the study is applied to. The return type is n\_ACSIL::DTCSecurityTypeEnum.

It returns one of the following values. Currently it is only set for some Data/Trading services.

* n\_ACSIL::SECURITY\_TYPE\_UNSET = 0
* n\_ACSIL::SECURITY\_TYPE\_FUTURES = 1
* n\_ACSIL::SECURITY\_TYPE\_STOCK = 2
* n\_ACSIL::SECURITY\_TYPE\_FOREX = 3
* n\_ACSIL::SECURITY\_TYPE\_INDEX = 4
* n\_ACSIL::SECURITY\_TYPE\_FUTURES\_STRATEGY = 5
* n\_ACSIL::SECURITY\_TYPE\_FUTURES\_OPTION = 7
* n\_ACSIL::SECURITY\_TYPE\_STOCK\_OPTION = 6
* n\_ACSIL::SECURITY\_TYPE\_INDEX\_OPTION = 8
* n\_ACSIL::SECURITY\_TYPE\_BOND = 9
* n\_ACSIL::SECURITY\_TYPE\_MUTUAL\_FUND = 10

#### Parameters

* This function has no parameters

### sc.SendEmailMessage

[Link](#scsendemailmessage) - [Top](#top)

**Type**: Function

int **SendEmailMessage**(const SCString& **ToEmailAddress**, const SCString& **Subject**, const SCString& **MessageBody**);

The **sc.SendEmailMessage** function will send an email message to the **ToEmailAddress** with the given **Subject** and **MessageBody**.

There are sending limits which will be applied over a period of time. So you cannot always expect an email message to be sent when using this function.

#### Parameters

* **ToEmailAddress**: The email address to which the email is to be sent.
* **Subject**: The subject of the email to be sent.
* **MessageBody**: The body of the email message to be sent.

### sc.SendHeldTradeOrder()

[Link](#scsendheldtradeorder) - [Top](#top)

**Type**: Function

Refer to the [sc.SendHeldTradeOrder()](ACSILTrading.md#scsendheldtradeorder) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.ServiceCodeForSelectedDataTradingService()

[Link](#scservicecodeforselecteddatatradingservice) - [Top](#top)

**Type**: Function

SCString **ServiceCodeForSelectedDataTradingService**();

The **sc.ServiceCodeForSelectedDataTradingService()** function returns the unique Service Code for the currently selected service as set in the **Data/Trade Service Settings**.

#### Parameters

* This function has no parameters

### sc.SessionStartTime()

[Link](#scsessionstarttime) - [Top](#top)

**Type**: Function

int **SessionStartTime**();

The **sc.SessionStartTime()** function gets the start of the trading day in Intraday charts which is based on the Session Times set in **Chart >> Chart Settings**.

If **Use Evening Session** is enabled in the Chart Settings, then this function returns the Start Time of the evening session. Otherwise, the **Session Times >> Start Time** will be returned.

The value returned is a [Time Value](SCDateTime.md#timevalue).

#### Parameters

* This function has no parameters

#### Example

```cpp

int StartTime = sc.SessionStartTime();
            
```

### sc.SetACSChartShortcutMenuItemChecked()

[Link](#scsetacschartshortcutmenuitemchecked) - [Top](#top)

Refer to the [sc.SetACSChartShortcutMenuItemChecked()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scsetacschartshortcutmenuitemchecked) page for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.SetACSChartShortcutMenuItemDisplayed()

[Link](#scsetacschartshortcutmenuitemdisplayed) - [Top](#top)

Refer to the [sc.SetACSChartShortcutMenuItemDisplayed()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scsetacschartshortcutmenuitemdisplayed) page for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.SetACSChartShortcutMenuItemEnabled()

[Link](#scsetacschartshortcutmenuitemenabled) - [Top](#top)

Refer to the [sc.SetACSChartShortcutMenuItemEnabled()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scsetacschartshortcutmenuitemenabled) page for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.SetACSToolButtonText()

[Link](#scsetacstoolbuttontext) - [Top](#top)

Refer to the [sc.SetACSToolButtonText()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scsetacstoolbuttontext) page for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.SetACSToolEnable()

[Link](#scsetacstoolenable) - [Top](#top)

Refer to the [sc.SetACSToolEnable()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scsetacstoolenable) page for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.SetACSToolToolTip()

[Link](#scsetacstooltooltip) - [Top](#top)

Refer to the [sc.SetACSToolToolTip()](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#scsetacstooltooltip) page for information on this function, as it is part of the [Advanced Custom Study Interaction With Menus, Control Bar Buttons, Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md) documentation.

### sc.SetAlert()

[Link](#scsetalert) - [Top](#top)

**Type**: Function

int **SetAlert**(int **AlertNumber**, int **Index**, SCString **Message**);

int **SetAlert**(int **AlertNumber**, int **Index**);

int **SetAlert**(int **AlertNumber**, SCString **Message**); [Auto-looping only](#noindexparam).

int **SetAlert**(int **AlertNumber**); [Auto-looping only](#noindexparam).

The **sc.SetAlert()** function will play an alert sound and add a message to the **Window >> Alert Manager >> Log**.

This can be used when you have a condition that you want to provide a signal for at the specified **sc.Subgraph[].Data** array **Index**. **Index** is a parameter to the function specifying the array index the alert is associated with.

The versions of the functions that do not use this parameter, internally set it to **sc.Index** when using Automatic Looping.

To open the Alerts Log, select **Window >> Alert Manager >> Log**  on the menu.

Since the **sc.Subgraph[].Data[]** arrays directly correspond to the sc.BaseData[][] arrays, **Index** corresponds to the **sc.BaseData[][]** arrays indices. If you are using [Automatic Looping](ACS_ArraysAndLooping.md#automaticloopingiterating), then the **Index** parameter is automatically set for you and does not need to be specified.

The **AlertNumber** parameter sets an Alert Sound Number to play. This can be anywhere from 1 to 150. To configure the specific sound file to play for a particular Alert Number, select **Global Settings >> General Settings >> Alerts** on the Sierra Chart menu. For more information, refer to the [Alert Sound Settings](GeneralSettings.md#tabalerts).

Using an **AlertNumber** of 0 means there will be no Alert Sound played.

The optional **Message** parameter specifies the text message to be added to the **Alerts Log**. If it is not specified, a standard message will be added to the log.

If you set an Alert on an **Index** that is *not at the end* of a **sc.Subgraph[].Data** array, it will be ignored. However, if there are multiple chart bars added during an update, the alerts will be processed for those new bars as well as the prior bar. Therefore, if you are providing an alert on a bar which has just closed, it will be processed.

If historical data is being downloaded in the chart, then calls to **sc.SetAlert()** are ignored. This is to prevent Alert sounds and Messages from occurring when historical data is being downloaded.

During a call into a study function, if there are multiple calls to **sc.SetAlert()** at the same or different bar indices, only one will actually generate an alert. The rest will be ignored. However, if [sc.ResetAlertOnNewBar](ACSIL_Members_Variables_And_Arrays.md#scresetalertonnewbar) is set to a nonzero value, then calling **sc.SetAlert()** at different bar indices will generate separate alerts.

If at every call into the study function you make a call to **sc.SetAlert()**, only the first time **sc.SetAlert()** is called will that generate an alert. There must be at least one call into the study function where **sc.SetAlert()** is not called, to reset the internal alert state for the study to allow for another call to **sc.SetAlert()** to generate an alert. However, if [sc.ResetAlertOnNewBar](ACSIL_Members_Variables_And_Arrays.md#scresetalertonnewbar) is set to a nonzero value, then calling **sc.SetAlert()** at a new bar index will generate a new alert.

The [sc.AlertOnlyOncePerBar](ACSIL_Members_Variables_And_Arrays.md#scalertonlyonceperbar) and the [sc.ResetAlertOnNewBar](ACSIL_Members_Variables_And_Arrays.md#scresetalertonnewbar) variables work with **sc.SetAlert()**. They control the alert processing. These variables only need to be set once in the **sc.SetDefaults** code block.

Even if [sc.AlertOnlyOncePerBar](ACSIL_Members_Variables_And_Arrays.md#scalertonlyonceperbar) is set to 0, then multiple calls to **sc.SetAlert()** during a call into a study function at the same or different bar indices, will still only generate one alert, as explained above.

For an example to work with the **sc.SetAlert()** function, see **scsf\_SimpMovAvg()** in **studies.cpp** inside the ACS\_Source folder in the Sierra Chart installation folder.

When the alert by the **sc.SetAlert()**  function is processed, and a message is added to the Alerts Log, the Alerts Log can be automatically opened by enabling the **Global Settings >> General Settings** **>> Alerts >> Additional Settings >> Show Alerts Log on Study Alert** option.

The [Study Summary Window](StudySummaryWindow.md) will use the **Study Summary: Alert True Background** color set through the **Graphics Settings** window for the displayed study Subgraphs for a study included in the Study Summary window, when the Alert Condition (alert state) is true for a study.

#### Parameters

* **AlertNumber**: The Alert Sound Number to define the sound to play when this function is called.
* [Index](#commonfunctionparameterdescriptionsindex)
* **Message**: The message to be added to the Alert Manager.

#### Example

```cpp

sc.SetAlert(5, "Condition #1 is TRUE.");
            
```

An ACSIL study can set the alert state for itself to true for the last bar by using the following code. This assumes [Automatic Looping](ACS_ArraysAndLooping.md#automaticloopingiterating) is being used.

#### Example

```cpp

if (sc.Index == sc.ArraySize - 1)
    sc.SetAlert(1); 
            
```

### sc.SetAttachedOrders()

[Link](#scsetattachedorders) - [Top](#top)

**Type**: Function

void **SetAttachedOrders**(const s\_SCNewOrder& **AttachedOrdersConfiguration**);

Refer to the [sc.SetAttachedOrders()](ACSILTrading.md#scsetattachedorders) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.SetBarPeriodParameters()

[Link](#scsetbarperiodparameters) - [Top](#top)

**Type**: Function

void **SetBarPeriodParameters**(const n\_ACSIL::s\_BarPeriod& **BarPeriod**);

The **sc.SetBarPeriodParameters()** function sets the chart bar period parameters according to the structure of type **n\_ACSIL::s\_BarPeriod** which is passed to the function as **BarPeriod**.

After calling the **sc.SetBarPeriodParameters()** function, the changes go into effect *after returning* from this ACSIL study function. The necessary chart reload will occur before the next call into the study function.

#### Parameters

* **BarPeriod**: The n\_ACSIL::s\_BarPeriod structure that holds the bar period parameters.
    
    
  The n\_ACSIL::s\_BarPeriod structure members are the following:
  + **s\_BarPeriod::ChartDataType**: Can be one of the following:
    - DAILY\_DATA = 1
    - INTRADAY\_DATA = 2If this is not set, the chart will retain the current setting.
  + **s\_BarPeriod::HistoricalChartBarPeriodType**: Can be one of the following:
    - HISTORICAL\_CHART\_PERIOD\_DAYS = 1
    - HISTORICAL\_CHART\_PERIOD\_WEEKLY = 2
    - HISTORICAL\_CHART\_PERIOD\_MONTHLY = 3
    - HISTORICAL\_CHART\_PERIOD\_QUARTERLY = 4
    - HISTORICAL\_CHART\_PERIOD\_YEARLY = 5
  + **s\_BarPeriod::HistoricalChartDaysPerBar**: When **s\_BarPeriod::HistoricalChartBarPeriodType** is set to HISTORICAL\_CHART\_PERIOD\_DAYS, then this specifies the number of days per historical chart bar.
  + **s\_BarPeriod::IntradayChartBarPeriodType**: The type of bar period to be used in the case of an Intraday chart. To determine the chart data type, use **s\_BarPeriod::ChartDataType**. For example, set to the enumeration value IBPT\_DAYS\_MINS\_SECS for an Intraday Chart **Bar Period Type** of **Days-Minutes-Seconds**. Can be any of the following constants:
    - IBPT\_DAYS\_MINS\_SECS = 0: **s\_BarPeriod::IntradayChartBarPeriodParameter1** is the number of seconds in one bar in an Intraday chart. This is set by the **Days-Mins-Secs** setting in the **Chart >> Chart Settings** window for the chart. For example, for a 1 Minute chart this will be set to 60. For a 30 Minute chart this will be set to 1800.
    - IBPT\_VOLUME\_PER\_BAR = 1
    - IBPT\_NUM\_TRADES\_PER\_BAR = 2
    - IBPT\_RANGE\_IN\_TICKS\_STANDARD = 3
    - IBPT\_RANGE\_IN\_TICKS\_NEWBAR\_ON\_RANGEMET = 4
    - IBPT\_RANGE\_IN\_TICKS\_TRUE = 5
    - IBPT\_RANGE\_IN\_TICKS\_FILL\_GAPS = 6
    - IBPT\_REVERSAL\_IN\_TICKS = 7
    - IBPT\_RENKO\_IN\_TICKS = 8
    - IBPT\_DELTA\_VOLUME\_PER\_BAR = 9
    - IBPT\_FLEX\_RENKO\_IN\_TICKS = 10
    - IBPT\_RANGE\_IN\_TICKS\_OPEN\_EQUAL\_CLOSE = 11
    - IBPT\_PRICE\_CHANGES\_PER\_BAR = 12
    - IBPT\_MONTHS\_PER\_BAR = 13
    - IBPT\_POINT\_AND\_FIGURE = 14
    - IBPT\_FLEX\_RENKO\_IN\_TICKS\_INVERSE\_SETTINGS = 15
    - IBPT\_ALIGNED\_RENKO = 16
    - IBPT\_RANGE\_IN\_TICKS\_NEW\_BAR\_ON\_RANGE\_MET\_OPEN\_EQUALS\_PRIOR\_CLOSE = 17
    - IBPT\_ACSIL\_CUSTOM = 18: This is used when the chart contains an advanced custom study that creates custom chart bars. The study name is contained within s\_BarPeriod::ACSILCustomChartStudyName. For complete documentation for building custom chart bars, refer to [ACSIL Interface - Custom Chart Bars](ACSIL_CustomChartBars.md).
    - IBPT\_HISTORICAL\_DAILY\_DATA\_DAYS\_PER\_BAR = 10000
  + **s\_BarPeriod::IntradayChartBarPeriodParameter1**: The first parameter for the bar period to be used. In the case of IntradayChartBarPeriodType being set to IBPT\_DAYS\_MINS\_SECS, this will be set to the number of seconds. In the case of IntradayChartBarPeriodType being set IBPT\_FLEX\_RENKO\_IN\_TICKS, this would be the **Bar Size** value in ticks.
  + **s\_BarPeriod::IntradayChartBarPeriodParameter2**: The second parameter for the bar period that to be used. For example, this would be the **Trend Offset** value when using **IBPT\_FLEX\_RENKO\_IN\_TICKS** for the Intraday Chart Bar Period Type. If this parameter is unused for the Intraday Chart Bar Period Type, then either do not set this value or set it to **0**.
  + **s\_BarPeriod::IntradayChartBarPeriodParameter3**: The third parameter for the bar period that to be used. For example, this would be the **Reversal Offset** value when using **IBPT\_FLEX\_RENKO\_IN\_TICKS** for the Intraday Chart Bar Period Type. If this parameter is unused for the Intraday Chart Bar Period Type, then either do not set this value or set it to **0**.
  + **s\_BarPeriod::IntradayChartBarPeriodParameter4**: The fourth parameter for the bar period that is being used. For example, this would be the **Renko New Bar Mode** setting when using any of the **Renko** Intraday Chart Bar Period Types. If this parameter is unused for the Intraday Chart Bar Period Type, then either do not set this value or set it to **0**.
  + **s\_BarPeriod::ACSILCustomChartStudyName**: Not relevant when setting bar period parameters.

#### Example

```cpp

n_ACSIL::s_BarPeriod NewBarPeriod;
NewBarPeriod.ChartDataType = INTRADAY_DATA;
NewBarPeriod.IntradayChartBarPeriodType = IBPT_DAYS_MINS_SECS;
NewBarPeriod.IntradayChartBarPeriodParameter1 = 300;// 300 seconds per bar which is 5 minutes

//Set the bar period parameters. This will go into effect after the study function returns.
sc.SetBarPeriodParameters(NewBarPeriod);      
            
```

### sc.SetChartDrawingTool()

[Link](#scsetchartdrawingtool) - [Top](#top)

**Type**: Function

int32\_t **SetChartDrawingTool**(const DrawingTypeEnum **DrawingType**);

The **sc.SetChartDrawingTool()** sets the selected drawing tool for the chart that contains the study that calls this function.

#### Parameters

* **DrawingType**: A DrawingTypeEnum that defines the drawing tool to be selected. The enumeration values can be found in the file **ACS\_Source/scconstants.h** under the main Sierra Chart installation folder.

### sc.SetChartStudyConstantRangeScaleAmount()

[Link](#scsetchartstudyconstantrangescaleamount) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyConstantRangeScaleAmount**(int32\_t **ChartNumber**, int32\_t **StudyID**, const float **ScaleConstRange**);

The **sc.SetChartStudyConstantRangeScaleAmount()** function sets the constant range scale **Range** value for a given chart and study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ScaleConstRange**: The constant range scale Range value.

### sc.SetChartStudyDisplayAsMainPriceGraph()

[Link](#scsetchartstudydisplayasmainpricegraph) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyDisplayAsMainPriceGraph**(int32\_t **ChartNumber**, int32\_t **StudyID**,const int32\_t **DisplayAsMainPriceGraph**);

The **sc.SetChartStudyDisplayAsMainPriceGraph()** function sets the option for **Display As Main Price Graph** for the given chart and study based on the value of the **DisplayAsMainPriceGraph** parameter.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **DisplayAsMainPriceGraph**: Contains the value to define whether this option is enabled or disabled. Setting this to a value of **0** will disable this option. Any other non-zero value will enable this option.

### sc.SetChartStudyDisplayStudyInputValues()

[Link](#scsetchartstudydisplaystudyinputvalues) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyDisplayStudyInputValues**(int32\_t **ChartNumber**, int32\_t **StudyID**,const int32\_t **DisplayStudyInputValues**);

The **sc.SetChartStudyDisplayStudyInputValues** function sets the option for **Display Input Values** for the given chart and study based on the value of the **DisplayStudyInputValues** parameter.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **DisplayStudyInputValues**: Contains the value to define whether this option is enabled or disabled. Setting this to a value of **0** will disable this option. Any other non-zero value will enable this option.

### sc.SetChartStudyDisplayStudyName()

[Link](#scsetchartstudydisplaystudyname) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyDisplayStudyName**(int32\_t **ChartNumber**, int32\_t **StudyID**, const int32\_t **DisplayStudyName**);

The **sc.SetChartStudyDisplayStudyName()** function sets the option for **Display Study Name** for the given chart and study based on the value of the **DisplayStudyName** parameter.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **DisplayStudyName**: Contains the value to define whether the option is enabled or disabled. Setting this to a value of **0** will disable this option. Any other non-zero value will enable this option.

### sc.SetChartStudyDrawStudyUnderneathMainPriceGraph()

[Link](#scsetchartstudydrawstudyunderneathmainpricegraph) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyDisplaySubgraphsNameAndValue**(int32\_t **ChartNumber**, int32\_t **StudyID**, const int32\_t **DisplaySubgraphsNameAndValue**);

The **sc.SetChartStudyDisplaySubgraphsNameAndValue()** function sets the option for **Display Study Subgraphs Name and Value - Global** for the specified chart and study based on the value of the **DisplaySubgraphsNameAndValue**.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **DisplaySubgraphsNameAndValue**: Contains the value to define whether the option is enabled or disabled. Setting this to a value of **0** will disable this option. Any other non-zero value will enable this option.

### sc.SetChartStudyGraphRegion()

[Link](#scsetchartstudygraphregion) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyGraphRegion**(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **GraphRegion**);

The **sc.SetChartStudyGraphRegion()** function sets the region for the specified chart and study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **GraphRegion**: The zero-based index that defines the region for the study. A value of zero is the Main Price Graph region.

### sc.SetChartStudyHideStudy()

[Link](#scsetchartstudyhidestudy) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyHideStudy**(int32\_t **ChartNumber**, int32\_t **StudyID**, const int32\_t **HideStudy**);

The **sc.SetChartStudyHideStudy()** function sets the option for **Hide Study** for the given chart and study based on the value of the **HideStudy** parameter.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **HideStudy**: Contains the value to define whether the option is enabled or disabled. Setting this to a value of **0** will disable this option. Any other non-zero value will enable this option.

### sc.SetChartStudyInputChartStudySubgraphValues()

[Link](#scsetchartstudyinputchartstudysubgraphvalues) - [Top](#top)

**Type**: Function

int **SetChartStudyInputChartStudySubgraphValues**(int **ChartNumber**, int **StudyID**, int **InputIndex**, s\_ChartStudySubgraphValues **ChartStudySubgraphValues**);

The **sc.SetChartStudyInputChartStudySubgraphValues()** function sets the study subgraph Input values for a given chart, study, and input. The values to set are contained within the ChartStudySubgraphValues structure.

The referenced InputIndex must already be one of the following value types in order for this change to take place:

* CHART\_STUDY\_SUBGRAPH\_VALUES
* CHART\_NUMBER
* STUDY\_SUBGRAPH\_VALUES

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index for the Input to be modified.
* **ChartStudySubgraphValues**: a structure of type s\_ChartStudySubgraphValues that contains the Chart Number, Study ID, and Subgraph Index to which the InputIndex input will be changed.

### sc.SetChartStudyInputFloat()

[Link](#scsetchartstudyinputfloat) - [Top](#top)

**Type**: Function

int **SetChartStudyInputFloat**(int **ChartNumber**, int **StudyID**, int **InputIndex**, double **FloatValue**);

The **sc.SetChartStudyInputFloat** function sets the study Input value as a double data type in the specified Chart Number and Study ID.

This function works with all Input types with conversions between types automatically occurring. For example, if a FloatValue of 152.25 is given for an integer input, the input will be changed to 152 (the double value is converted to an integer).

When working with Date and Time Inputs which use [SCDateTime](SCDateTime.md), use this function for setting them. See the example below for how to set a specific Date and Time into a Date and Time study Input.

After changing a study Input, in most cases you will need to recalculate the chart the study is on in order for the new Input to be used. But this depends upon how the study is using it. If it is a study that you have developed and you know that a recalculation is not necessary, then this is not necessary. To recalculate the chart, use the [sc.RecalculateChart()](#screcalculatechart) function.

The function returns 1 if successful. Otherwise, 0.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the Input to set the value for. The Input index values + 1 are displayed in the Inputs list on the Study Settings window for the study. Example: (In:1).
* **FloatValue**: This parameter is the value to set.

#### Example

```cpp

int Result = sc.SetChartStudyInputFloat(sc.ChartNumber, 1, 1, 1.5);

//Example to set study (with ID 2) Date-Time Input (with index 1), to a specific Date-Time
SCDateTime NewDateTimeForInput;
NewDateTimeForInput.SetDateTimeYMDHMS_MS(2024, 7, 1, 13, 5, 0, 0);

sc.SetChartStudyInputFloat(sc.ChartNumber, 2, 1, NewDateTimeForInput.GetAsDouble());           
            
```

### sc.SetChartStudyInputInt()

[Link](#scsetchartstudyinputint) - [Top](#top)

**Type**: Function

int **SetChartStudyInputInt**(int **ChartNumber**, int **StudyID**, int **InputIndex**, int **IntegerValue**);

The **sc.SetChartStudyInputInt** function sets the study Input value as an integer in the specified Chart Number and Study ID.

This function works with all Input types with conversions between types automatically occurring. For example, if an IntegerValue of 45813 is given for a Date-Time input, the date will be set to the specified date with the time set to midnight (00:00:00) since there is no time portion to be derived from the integer.

After changing a study Input, in most cases you will need to recalculate the chart the study is on in order for the new Input to be used. But this depends upon how the study is using it. If it is a study that you have developed and you know that a recalculation is not necessary, then this is not necessary. To recalculate the chart, use the [sc.RecalculateChart()](#screcalculatechart) function.

Another reason why you would not have to do a recalculate with **sc.RecalculateChart()** is if after changing a study Input you are then starting a replay for the chart using the [sc.StartChartReplayNew()](#scstartchartreplaynew) function.

The function returns 1 if successful. Otherwise, 0.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the Input to set the value for. The Input index values + 1 are displayed in the Inputs list on the Study Settings window for the study. Example: (In:1).
* **IntegerValue**: This parameter is the value to set.

#### Example

```cpp

            int Result = sc.SetChartStudyInputInt(sc.ChartNumber, 1, 1, 20);
            
```

### sc.SetChartStudyInputString()

[Link](#scsetchartstudyinputstring) - [Top](#top)

**Type**: Function

int **SetChartStudyInputString**(int **ChartNumber**, int **StudyID**, int **InputIndex**, const SCString& **StringValue**);

The **sc.SetChartStudyInputString** function sets the study Input with the specified text string in the specified Chart Number and Study ID.

This function works only with string Input types. If the Input is not already a string, then the function will return 0 and does nothing.

After changing a study Input, in most cases you will need to recalculate the chart the study is on in order for the new Input to be used. But this depends upon how the study is using it. If it is a study that you have developed and you know that a recalculation is not necessary, then this is not necessary. To recalculate the chart, use the [sc.RecalculateChart()](#screcalculatechart) function.

The function returns 1 if successful. Otherwise, 0.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **InputIndex**: The zero-based index of the Input to set the value for. The Input index values + 1 are displayed in the Inputs list on the Study Settings window for the study. Example: (In:1).
* **StringValue**: This parameter is the string to set.

#### Example

```cpp

            int Result = sc.SetChartStudyInputString(sc.ChartNumber, 1, 1, "My Text String");
            
```

### sc.SetChartStudyScaleIncrement()

[Link](#scsetchartstudyscaleincrement) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyScaleIncrement**( int32\_t **ChartNumber**, int32\_t **StudyID**, const float **ScaleIncrement**);

The **sc.SetChartStudyScaleIncrement()** function sets the **Scale Increment** for the given chart and study.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ScaleIncrement**: The value to which the Scale Increment is to be set.

### sc.SetChartStudyScaleRangeType()

[Link](#scsetchartstudyscalerangetype) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyScaleRangeType**( int32\_t **ChartNumber**, int32\_t **StudyID**, const ScaleRangeTypeEnum **ScaleRangeType**);

The **sc.SetChartStudyScaleRangeType()** function sets the **Scale Range Type** for the given chart and study.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ScaleRangeType**: The Scale Range Type to be set. This is one of the following values:
  + SCALE\_AUTO
  + SCALE\_USERDEFINED
  + SCALE\_INDEPENDENT
  + SCALE\_SAMEASREGION
  + SCALE\_CONSTANT\_RANGE
  + SCALE\_CONSTRANGECENTER
  + SCALE\_ZEROBASED
  + SCALE\_ZEROCENTERED

### sc.SetChartStudyScaleType()

[Link](#scsetchartstudyscaletype) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyScaleType**( int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **ScaleType**);

The **sc.SetChartStudyScaleType()** function sets the Scale Type (Linear or Logarithmic) for the given chart and study.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ScaleType**: The scale type to which the given chart and study will be set. A value of **0** sets the study scale type to **Linear**. A value of **1** sets the study scale type to **Logarithmic**.

### sc.SetChartStudyScaleValueOffset()

[Link](#scsetchartstudyscalevalueoffset) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyScaleValueOffset**( int32\_t **ChartNumber**, int32\_t **StudyID**, const float **ScaleValueOffset**);

The **sc.SetChartStudyScaleValueOffset()** function sets the scale value offset amount.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ScaleValueOffset**: The amount of the offset.

### sc.SetChartStudyShortName()

[Link](#scsetchartstudyshortname) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyShortName**( int32\_t **ChartNumber**, int32\_t **StudyID**, const SCString& **ShortName**);

The **sc.SetChartStudyShortName()** function sets the **Short Name** for the given chart and study.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ShortName**: An SCString that contains the name for the Short Name.

### sc.SetChartStudyTransparencyLevel()

[Link](#scsetchartstudytransparencylevel) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyTransparencyLevel**(int32\_t **ChartNumber**, int32\_t **StudyID**, const int32\_t **TransparencyLevel**);

The **sc.SetChartStudyTransparencyLevel()** function sets the current transparency level (0 to 100) for Draw Styles which use transparency for the study specified by the [ChartNumber](#commonfunctionparameterdescriptionschartnumber) and [StudyID](#commonfunctionparameterdescriptionsstudyid) parameters.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **TransparencyLevel**: Sets the transparency level as a percentage. This can be a value anywhere from 0 to 100.

### sc.SetChartStudyUserDefinedScaleRangeBottom()

[Link](#scsetchartstudyuserdefinedscalerangebottom) - [Top](#top)

**Type**: Function

float **SetChartStudyUserDefinedScaleRangeBottom**(int32\_t **ChartNumber**, int32\_t **StudyID**, const float **ScaleRangeBottom**);

The **sc.SetChartStudyUserDefinedScaleRangeBottom()** function sets the **Bottom of Range** for a User Defined range type.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ScaleRangeBottom**: The value to which the Scale Range Botttom will be set.

### sc.SetChartStudyUserDefinedScaleRangeTop()

[Link](#scsetchartstudyuserdefinedscalerangetop) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyUserDefinedScaleRangeTop**( int32\_t **ChartNumber**, int32\_t **StudyID**, const float **ScaleRangeTop**);

The **sc.SetChartStudyUserDefinedScaleRangeTop()** function sets the **Top of Range** for a User Defined range type.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ScaleRangeTop**: The value to which the Scale Range Top will be set.

### sc.SetChartStudyValueFormat()

[Link](#scsetchartstudyvalueformat) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyValueFormat**(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **ValueFormat**);

The **sc.SetChartStudyValueFormat()** function sets the **Value Format** for the given chart and study.

The available value formats are defined in the **ACS\_Source/scconstants.h** file located in the main Sierra Chart installation folder.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **ValueFormat**: The value to which the Value Format will be set.

### sc.SetChartStudyVersion()

[Link](#scsetchartstudyversion) - [Top](#top)

**Type**: Function

int32\_t **SetChartStudyVersion**(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **Version**);

The **sc.SetChartStudyVersion()** function sets the version for the given chart and study.

The function returns a value of 0 if the chart and/or study are not found. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **Version**: The value to which the version will be set.

### sc.SetChartTimeZone()

[Link](#scsetcharttimezone) - [Top](#top)

**Type**: Function

int **SetChartTimeZone**(const int **ChartNumber**, const TimeZonesEnum **TimeZone**);

The **sc.SetChartTimeZone()** function sets the time zone for the given chart.

The function returns a value of 0 if the chart and/or study are not found or if an invalid time zone value is sent. Otherwise a value of 1 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **TimeZone**: The time zone to which the Chart Time Zone will be set. The time zone enumeration can be found in the **ACS\_Source/scconstants.h** file located under the main Sierra Chart installation folder.

### sc.SetChartTradeMode()

[Link](#scsetcharttrademode) - [Top](#top)

**Type**: Function

int **SetChartTradeMode**(int **ChartNumber**, int **Enabled**);

The **sc.SetChartTradeMode** function enables or disables chart trade mode, for the specified **ChartNumber**.

The function returns the state of the **Chart Trade Mode On** prior to the function call.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* **Enabled**: 1 to enable chart trade mode. 0 to disable chart trade mode.

#### Example

```cpp

sc.SetChartTradeMode(sc.ChartNumber, 1);
            
```

### sc.SetChartWindowState

[Link](#scsetchartwindowstate) - [Top](#top)

**Type**: Function

int **SetChartWindowState**(int **ChartNumber**, int **WindowState**);

The **sc.SetChartWindowState** function is used to minimize, restore or maximize the chart specified by the **ChartNumber** parameter in the same Chartbook containing the chart the study instance is applied to.

The function returns 1 on success and 0 if the Chart Number is not found.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **WindowState**: The state the window is to be set to. The following are the possible values:
  + CWS\_MINIMIZE = 1
  + CWS\_RESTORE = 2
  + CWS\_MAXIMIZE = 3

### sc.SetCombineTradesIntoOriginalSummaryTradeSetting

[Link](#scsetcombinetradesintooriginalsummarytradesetting) - [Top](#top)

**Type**: Function

void **sc.SetCombineTradesIntoOriginalSummaryTradeSetting**(int **NewState**);

The **sc.SetCombineTradesIntoOriginalSummaryTradeSetting()** function sets the **Combine Trades Into Original Summary Trade** setting for the chart containing the study on which this function is called, to **Yes** or **No**.

#### Parameters

* **NewState**: The state to which the setting for **Combine Trades Into Original Summary Trade** will be changed. A value of **0** sets the option to **No**. A value of **1** sets the option to **Yes**.

### sc.SetCurrentDataTradingService

[Link](#scsetcurrentdatatradingservice) - [Top](#top)

**Type**: Function

int32\_t **sc.SetCurrentDataTradingService**(const SCString& **ServiceCodeString**);

This function has not yet been implemented.

### sc.SetCustomStudyControlBarButtonColor

[Link](#scsetcustomstudycontrolbarbuttoncolor) - [Top](#top)

**Type**: Function

void **SetCustomStudyControlBarButtonColor**(int **ControlBarButtonNum**, const COLORREF **Color**);

The **sc.SetCustomStudyControlBarButtonColor** function sets the background color of the specified Advanced Custom study Control Bar button. For further details about Advanced Custom Study Control Bar buttons, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).

The change of the color goes into effect immediately.

#### Parameters

* **ControlBarButtonNum**: The integer number of the Advanced Custom study Control Bar button that is to be modified. For further details, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).
* **Color**: The color in [RGB Format](ACSILDrawingTools.md#rgb) for the Control Bar button background.

### sc.SetCustomStudyControlBarButtonEnable

[Link](#scsetcustomstudycontrolbarbuttonenable) - [Top](#top)

**Type**: Function

void **SetCustomStudyControlBarButtonEnable**(int **ControlBarButtonNum**, int **Enabled**);

The **sc.SetCustomStudyControlBarButtonEnable** function sets the enabled/disabled state of the specified Advanced Custom Study Control Bar button. For further details about Advanced Custom Study Control Bar buttons, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).

#### Parameters

* **ControlBarButtonNum**: The integer number of the Advanced Custom Study Control Bar button that is to be modified. For further details, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).
* **Enabled**: The state to which the button is to be set. A value of **1** sets the button to enabled. A value of **0** sets the button to disabled.

### sc.SetCustomStudyControlBarButtonHoverText

[Link](#scsetcustomstudycontrolbarbuttonhovertext) - [Top](#top)

**Type**: Function

void **SetCustomStudyControlBarButtonHoverText**(int **ControlBarButtonNum**, const char\* **HoverText**);

The **sc.SetCustomStudyControlBarButtonHoverText** function sets the hover text of the specified Advanced Custom Study Control Bar button. For further details about Advanced Custom Study Control Bar buttons, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).

#### Parameters

* **ControlBarButtonNum**: The integer number of the Advanced Custom study Control Bar button that is to be modified. For further details, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).
* **HoverText**: The text to display when the pointer hovers over the button.

### sc.SetCustomStudyControlBarButtonShortCaption

[Link](#scsetcustomstudycontrolbarbuttonshortcaption) - [Top](#top)

**Type**: Function

int **SetCustomStudyControlBarButtonShortCaption**(int **ControlBarButtonNum**, const SCString& **ButtonText**);

The **sc.SetCustomStudyControlBarButtonShortCaption** function sets the short caption of the specified Advanced Custom Study Control Bar button. For further details about Advanced Custom Study Control Bar buttons, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).

#### Parameters

* **ControlBarButtonNum**: The integer number of the Advanced Custom Study Control Bar button that is to be modified. For further details, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).
* **ButtonText**: The text to be set for the short caption.

### sc.SetCustomStudyControlBarButtonText

[Link](#scsetcustomstudycontrolbarbuttontext) - [Top](#top)

**Type**: Function

void **SetCustomStudyControlBarButtonText**(int **ControlBarButtonNum**, const char\* **ButtonText**);

The **sc.SetCustomStudyControlBarButtonText** function sets the caption of the specified Advanced Custom Study Control Bar button. For further details about Advanced Custom Study Control Bar buttons, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).

#### Parameters

* **ControlBarButtonNum**: The integer number of the Advanced Custom study Control Bar button that is to be modified. For further details, refer to [Advanced Custom Study Buttons and Pointer Events](ACSInteractionWithMenusControlBarButtonsPointerEvents.md#advancedcustomstudycontrolbarbuttonsandpointerevents).
* **ButtonText**: The text to be set for the caption.

### sc.SetDrawDOMGraphOnChart()

[Link](#scsetdrawdomgraphonchart) - [Top](#top)

**Type**: Function

int32\_t **SetDrawDOMGraphOnChart**(const int32\_t **ChartNumber**, const int32\_t **Enabled**);

The **sc.SetDrawDOMGraphOnChart()** function controls whether the DOM Graph is displayed or not for the given chart.

The function returns 1 on success and 0 if the Chart Number is not found.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **Enabled**: Setting this to a value of **0** sets the DOM Graph to not be displayed. Setting this to any other value sets the DOM Graph to be displayed.

### sc.SetGlobalTradeSimulationModeState()

[Link](#scsetglobaltradesimulationmodestate) - [Top](#top)

**Type**: Function

int32\_t **SetGlobalTradeSimulationModeState**(const int **Enabled**);

The **sc.SetGlobalTradeSimulationModeState()** function enables or disables the setting for **Simulation Mode On**.

If the system is not able to access trading services at the time the function is called, then a value of 0 is returned. Otherwise, the state of **Simulation Mode On**, after processing (0 for disabled, 1 for enabled), is returned.

#### Parameters

* **Enabled**: A value of **0** disables the **Simulation Mode On** option. Any other non-zero value enables **Simulation Mode On**.

### sc.SetGraphicsSetting

[Link](#scsetgraphicssetting) - [Top](#top)

**Type**: Function

int32\_t **SetGraphicsSetting**(const int32\_t **ChartNumber**, const n\_ACSIL::GraphicsSettingsEnum **GraphicsSetting**, uint32\_t **Color**, uint32\_t **LineWidth**, SubgraphLineStyles **LineStyle**);

The **sc.SetGraphicsSetting** function sets the Color, Line Width, and Line Style for a given chart's graphics settings.

The function returns a value of **0** if the chart is not found. Otherwise a value of **1** is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **GraphicsSetting**: An enumeration value specifying the graphics setting item to be changed. The **GraphicsSettingsEnum** can be found in the **ACS\_Source/scconstants.h** file under the main Sierra Chart installation folder.
* **Color**: The color to which the graphics setting will be changed. This can be set using the RGB(r, g, b) macro where r, g, and b is each a value bewteen 0 and 255. Set this parameter to -1 to not change it.
* **LineWidth**: The width to which the graphic setting will be changed. Set this parameter to -1 to not change it.
* **LineStyle**: The style to which the graphic setting will be changed. Set this parameter to -1 to not change it.

### sc.SetGraphicsSettingEnableState()

[Link](#scsetgraphicssettingenablestate) - [Top](#top)

**Type**: Function

int32\_t **SetGraphicsSettingEnableState**(const int32\_t **ChartNumber**, const n\_ACSIL::GraphicsSettingsEnum **GraphicsSetting**, int32\_t **EnableState**);

The **sc.SetGraphicsSettingEnableState** function enables or disables the enable state for a given chart's graphics setting

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **GraphicsSetting**: An enumeration value specifying the graphics setting item to be changed. The **GraphicsSettingsEnum** can be found in the **ACS\_Source/scconstants.h** file under the main Sierra Chart installation folder.
* **EnableState**: Set this to **0** to disable the enable state for the graphics setting. Setting this to any other value will enable the enable state.

### sc.SetGraphRegionHeightPercentage

[Link](#scsetgraphregionheightpercentage) - [Top](#top)

**Type**: Function

int32\_t **SetGraphRegionHeightPercentage**(const int32\_t **ChartNumber**, int32\_t **GraphRegionIndex**, double **Percentage**);

The **sc.SetGraphRegionHeightPercentage** function sets the height of a Chart Region to the specified percentage.

The function returns a value of **0** if the region can not be changed to the given percentage. Otherwise, a value of **1** is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **GraphRegionIndex**: The zero-based index for the region to be changed. A value of zero is the main price graph region.
* **Percentage**: The percentage to which the region height is set. This number needs to be entered as a whole percentage between the values of 1.00 and 95.00.

### sc.SetHorizontalGridState

[Link](#scsethorizontalgridstate) - [Top](#top)

**Type**: Function

int **SetHorizontalGridState**(int **GridIndex**, int **State**);

The **sc.SetHoriontalGrideState** function enables or disables the Horizontal Grid for a given [Chart Region](WorkingWithCharts.md#chartwindowandregions) or for all Chart Regions. The function returns the state of the Horizontal Grid for the given Chart Region prior to the changes.

#### Parameters

* **GridIndex**: The one-based Chart Region number for the Horizontal Grid. If a value of **0** is passed, then all Chart Regions will be affected.
* **State**: A value of **0** disables the Horizontal Grid for the specified Chart Region. A nonzero value will enable the Horizontal Grid for the specified Chart Region.

### sc.SetInvertUnderlyingChartData()

[Link](#scsetinvertunderlyingchartdata) - [Top](#top)

**Type**: Function

int **SetInvertUnderlyingChartData**(int **InvertData**);

The **sc.SetInvertUnderlyingChartData()** function sets the state of the **Invert Prices** setting for the chart containing the study from which this function is called.

The function returns the prior state of the setting before the change (0 for No, 1 for Yes).

#### Parameters

* **InvertData**: Send a value of **0** to set **Invert Prices** to **No**. Otherwise send any non-zero value to set **Invert Prices** to **Yes**.

### sc.SetNumericInformationDisplayOrderFromString

[Link](#scsetnumericinformationdisplayorderfromstring) - [Top](#top)

**Type**: Function

void **SetNumericInformationDisplayOrderFromString**(const SCString& **CommaSeparatedDisplayOrder**);

For complete documentation for this function, refer to [Numeric Information Table Graph Draw Type](ACSIL_Members_scSubgraph.md#numericinformationtablegraphdrawtype).

### sc.SetNumericInformationGraphDrawTypeConfig()

[Link](#scsetnumericinformationgraphdrawtypeconfig) - [Top](#top)

**Type**: Function

void **SetNumericInformationGraphDrawTypeConfig**(const s\_NumericInformationGraphDrawTypeConfig& **NumericInformationGraphDrawTypeConfig**);

For complete documentation for this function, refer to [Numeric Information Table Graph Draw Type](ACSIL_Members_scSubgraph.md#numericinformationtablegraphdrawtype).

### sc.SetPersistentSCStringForChartStudy()

[Link](#scsetpersistentscstringforchartstudy) - [Top](#top)

**Type**: Function

void **SetPersistentSCStringForChartStudy**(int **ChartNumber**, int **StudyID**, int **Key**, const SCString& **Value**);

The **sc.SetPersistentSCStringForChartStudy()** function sets a string for a peristent string variable noted by Key for the given chart and study.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **Key**: The persistent string variable key.
* **Value**: The value to which the persistent variable will be set.

### sc.SetSheetCellAsDouble()

[Link](#scsetsheetcellasdouble) - [Top](#top)

**Type**: Function

int **SetSheetCellAsDouble**(void\* **SheetHandle**, const int **Column**, const int **Row**, const double **CellValue**);

The **sc.SetSheetCellAsDouble()** function places the value of the double variable **CellValue** into the specified Spreadsheet Sheet Cell.

If the function is unable to determine the Spreadsheet Sheet Cell then it returns a value of **0**. Otherwise it returns a value of **1**.

#### Parameters

* **SheetHandle**: The handle of the Spreadsheet Sheet as returned by the [sc.GetSpreadsheetSheetHandleByName()](#scgetspreadsheetsheethandlebyname) function
* **Column**: The column number for the Sheet Cell to set the value in. This is a zero-based array, so column B in the Sheet would be a value of 1.
* **Row**: The row number for the Sheet Cell to set the value in. This is a zero-based array, so row 2 in the Sheet would be a value of 1.
* **CellValue**: The double value that is entered into the Sheet Cell.

Also refer to the following functions: [sc.GetSheetCellAsDouble()](#scgetsheetcellasdouble), [sc.GetSheetCellAsString()](#scgetsheetcellasstring), [sc.SetSheetCellAsString()](#scsetsheetcellasstring), [sc.GetSpreadsheetSheetHandleByName()](#scgetspreadsheetsheethandlebyname).

#### Example

```cpp

const char* SheetCollectionName = "ACSILInteractionExample";

const char* SheetName = "Sheet1";

void* SheetHandle = sc.GetSpreadsheetSheetHandleByName(SheetCollectionName, SheetName, false);

// Set values in column B, row 2.
sc.SetSheetCellAsDouble(SheetHandle, 1, 1, sc.BaseData[SC_HIGH][sc.Index]);
            
```

### sc.SetSheetCellAsString()

[Link](#scsetsheetcellasstring) - [Top](#top)

**Type**: Function

int **SetSheetCellAsString**(void\* **SheetHandle**, const int **Column**, const int **Row**, const SCString& **CellString**);

The **sc.SetSheetCellAsString()** function places the value of the SCString variable **CellString** into the specified Spreadsheet Sheet Cell.

If the function is unable to determine the Spreadsheet Sheet Cell, then it returns a value of **0**. Otherwise it returns a value of **1**.

#### Parameters

* **SheetHandle**: The handle of the Spreadsheet Sheet as returned by the [sc.GetSpreadsheetSheetHandleByName()](#scgetspreadsheetsheethandlebyname) function
* **Column**: The column number for the Sheet Cell to set the value in. This is a zero-based array, so column B in the Sheet would be a value of 1.
* **Row**: The row number for the Sheet Cell to set the value in. This is a zero-based array, so row 2 in the Sheet would be a value of 1.
* **CellString**: An SCString value to be entered into the Sheet Cell.

Also refer to the following functions: [sc.GetSheetCellAsDouble()](#scgetsheetcellasdouble), [sc.SetSheetCellAsDouble()](#scsetsheetcellasdouble), [sc.GetSheetCellAsString()](#scgetsheetcellasstring), [sc.GetSpreadsheetSheetHandleByName()](#scgetspreadsheetsheethandlebyname).

#### Example

```cpp

const char* SheetCollectionName = "ACSILInteractionExample";

const char* SheetName = "Sheet1";

void* SheetHandle = sc.GetSpreadsheetSheetHandleByName(SheetCollectionName, SheetName, false);

// Set labels in column A.
sc.SetSheetCellAsString(SheetHandle, 0, 1, "High");
sc.SetSheetCellAsString(SheetHandle, 0, 2, "Low");
sc.SetSheetCellAsString(SheetHandle, 0, 3, "Enter Formula");
sc.SetSheetCellAsString(SheetHandle, 0, 5, "Log Message");
            
```

### sc.SetShowMarketDataColumns()

[Link](#scsetshowmarketdatacolumns) - [Top](#top)

**Type**: Function

int32\_t **SetShowMarketDataColumns**(const int32\_t **ChartNumber**, const int32\_t **Enabled**);

The **sc.SetShowMarketDataColumns()** function enables or disables the option for **Show Market Data Columns** for the given chart.

The function returns a value of **0** if the chart is not found, otherwise a value of **1** is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* **Enabled**: Setting this to a value of **0** disables **Show Market Data Columns**. Setting this to any non-zero value enables **Show Market Data Columns**.

### sc.SetStudyAlwaysShowNameValueLabelsWhenEnabled()

[Link](#scsetstudyalwaysshownamevaluelabelswhenenabled) - [Top](#top)

**Type**: Function

int32\_t **SetStudyAlwaysShowNameValueLabelsWhenEnabled**(int32\_t **ChartNumber**, int32\_t& **StudyID**, int32\_t& **Value**);

The **sc.SetStudyAlwaysShowNameValueLabelsWhenEnabled()** function enables or disables the setting for **Always Show Name and Value Labels When Enabled** for the given chart and study.

This function returns a value of **0** if the chart or study cannot be found. Otherwise a value of **1** is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **Value**: Setting this to a value of **0** disables the setting for **Always Show Name and Value Labels When Enabled**. Setting this to any non-zero value will enable the setting for **Always Show Name and Value Labels When Enabled**.

### sc.SetStudySubgraphColors()

[Link](#scsetstudysubgraphcolors) - [Top](#top)

**Type**: Function

int32\_t SetStudySubgraphColors(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **StudySubgraphNumber**, uint32\_t **PrimaryColor**, uint32\_t **SecondaryColor**, uint32\_t **SecondaryColorUsed**);

The **sc.SetStudySubgraphColors()** function sets the primary and secondary colors of a Subgraph in another study in the Chartbook. The study can be in a different chart.

The **ChartNumber**, **StudyID**, and **StudySubgraphNumber** parameters should be obtained using the [sc.Input[].GetChartStudySubgraphValues](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputGetChartStudySubgraphValues) function.

The function returns 1 if the study was found. Otherwise, 0 is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [StudySubgraphNumber](#commonfunctionparameterdescriptionsstudysubgraphnumber)
* **PrimaryColor**: The color for which the primary color will be set.
* **SecondaryColor**: The color for which the secondary color will be set.
* **SecondaryColorUserd**: Defines whether the secondary color is used or not. Setting this to a value of **0** sets the secondary color to not be used. Settings this to any non-zero value sets the secondary color to be used.

#### Example

```cpp

uint32_t PrimaryColor = RGB(128, 0, 0);
uint32_t SecondaryColor = RGB(0, 255, 0);    
uint32_t SecondaryColorUsed = 1;      
sc.SetStudySubgraphColors(1, 1, 0, PrimaryColor, SecondaryColor, SecondaryColorUsed);
            
```

### sc.SetStudySubgraphDrawStyle()

[Link](#scsetstudysubgraphdrawstyle) - [Top](#top)

**Type**: Function

void **SetStudySubgraphDrawStyle**(int **ChartNumber**, int **StudyID**, int **StudySubgraphNumber**, int **DrawStyle**);

The **sc.SetStudySubgraphDrawStyle()** function sets the Draw Style of a Subgraph in another study in the Chartbook. The study can be in a different chart. The **ChartNumber**, **StudyID**, and **StudySubgraphNumber** parameters should be obtained using the [sc.Input[].GetChartStudySubgraphValues](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputGetChartStudySubgraphValues) function.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [StudySubgraphNumber](#commonfunctionparameterdescriptionsstudysubgraphnumber)
* **DrawStyle**: The draw style to which the subgraph will be set. An enumeration for the draw styles (SubgraphDrawStyles) can be found in the **ACS\_Source/scconstants.h** file under the main Sierra Chart installation folder.

#### Example

```cpp

sc.SetStudySubgraphDrawStyle(1, 1, 0, DRAWSTYLE_LINE);
            
```

### sc.SetStudySubgraphLineStyle()

[Link](#scsetstudysubgraphlinestyle) - [Top](#top)

**Type**: Function

int32\_t **SetStudySubgraphLineStyle**(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **StudySubgraphNumber**, SubgraphLineStyles **LineStyle**);

The **sc.SetStudySubgraphLineStyle()** function sets the line style for a subgraph that is part of the given chart and study.

The function returns a value of **0** if the chart, study or subgraph are not found. Otherwise a value of **1** is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [StudySubgraphNumber](#commonfunctionparameterdescriptionsstudysubgraphnumber)
* **LineStyle**: The line style to which the subgraph will be set to. The SubgraphLineStyles enumeration can be found in the **ACS\_Source/scconstants.h** file under the main Sierra Chart installation folder.

### sc.SetStudySubgraphLineWidth()

[Link](#scsetstudysubgraphlinewidth) - [Top](#top)

**Type**: Function

int32\_t **SetStudySubgraphLineWidth**(int32\_t **ChartNumber**, int32\_t **StudyID**, int32\_t **StudySubgraphNumber**, int32\_t **LineWidth**);

The **sc.SetStudySubgraphLineWidth()** function sets the line width for a subgraph that is part of the given chart and study.

The function returns a value of **0** if the chart, study or subgraph are not found. Otherwise a value of **1** is returned.

#### Parameters

* [ChartNumber](#commonfunctionparameterdescriptionschartnumber)
* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* [StudySubgraphNumber](#commonfunctionparameterdescriptionsstudysubgraphnumber)
* **LineWidth**: The line width to which the subgraph will be set.

### sc.SetStudyVisibilityState

[Link](#scsetstudyvisibilitystate) - [Top](#top)

**Type**: Function

int **SetStudyVisibilityState**(int **StudyID**, int **Visible**);

The **sc.SetStudyVisibilityState()** function sets the visibility state of a study by either making it visible or hiding it.

#### Parameters

* [StudyID](#commonfunctionparameterdescriptionsstudyid)
* **Visible**: Set this to **1** to make the study visible or **0** to make the study hidden.

### sc.SetTradeWindowTextTag()

[Link](#scsettradewindowtexttag) - [Top](#top)

**Type**: Function

void **SetTradeWindowTextTag**(const SCString& **TextTag**);

The **sc.SetTradeWindowTextTag** function sets the specified **TextTag** to the Trade Window of the Chart that the study instance is applied to. For more information, refer to [Text Tag](TradeWindow.md#texttag).

#### Parameters

* **TextTag**: The string to set into the Text Tag.

### sc.SetTradingKeyboardShortcutsEnableState()

[Link](#scsettradingkeyboardshortcutsenablestate) - [Top](#top)

**Type**: Function

void **SetTradingKeyboardShortcutsEnableState**(int **State**);

The **sc.SetTradingKeyboardShortcutsEnableState** function enables or disables the state of **Trade >> Trading Keyboard Shortcuts Enabled**. Refer to [Trading Keyboard Shortcuts Enabled (Trade menu)](TradeMenu.md#tradingkeyboardshortcutsenabled).

#### Parameters

* **State**: Setting this to **0** will disable **Trading Keyboard Shortcuts Enabled**. Setting this to **1** will enable **Trading Keyboard Shortcuts Enabled**.

### sc.SetTradingLockState()

[Link](#scsettradinglockstate) - [Top](#top)

**Type**: Function

int32\_t **SetTradingLockState**(int32\_t **NewState**);

The **sc.SetTradingLockState()** function enables or disables the state of **Trade >> Trading Locked**.

#### Parameters

* **NewState**: Setting this to **0** disables **Trading Locked**. Setting this to **1** enables **Trading Locked**.

### sc.SetUseGlobalGraphicsSettings

[Link](#scsetuseglobalgraphicssettings) - [Top](#top)

**Type**: Function

int **SetUseGlobalGraphicsSettings**(const int **ChartNumber**, int **State**);

The **sc.SetUseGlobalGraphicsSettings** function sets the chart specified by the ChartNumber parameter to use the global graphics settings or not.

The function returns a value of **0** if the chart cannot be found. Otherwise it returns the state of the **Use Global Graphics Settings Instead of These Settings** prior to the change.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* **State**: Use a state of **1** to use the global graphics settings. Use a state of **0** to not use the global graphics settings and instead use the graphics settings specific to the chart.

### sc.SetUseMarketDepthPullingStackingData

[Link](#scsetusemarketdepthpullingstackingdata) - [Top](#top)

**Type**: Function

int32\_t **SetUseMarketDepthPullingStackingData**(int32\_t **Value**);

The **sc.SetUseMarketDepthPullingStackingData()** function enables or disables the option to control whether pulling/stacking data is calculated and made available for the study that calls this function.

The function returns a value of **0** at all times.

#### Parameters

* **Value**: A value of **0** disables the calculation of pulling/stacking data. A non-zero value enables the calculation of pulling/stacking data.

### sc.SetVerticalGridState

[Link](#scsetverticalgridstate) - [Top](#top)

**Type**: Function

int **SetVerticalGridState**(int **State**);

The **sc.SetVerticalGrideState()** function turns on or off the Vertical Grid. The function returns the state of the Horizontal Grid for the given region prior to the changes.

The function returns the value of the vertical grid display state prior to the change.

#### Parameters

* **State**: A value of **0** turns the Horizontal Grid **Off**. Any other value will turn the Horizontal Grid **On**.

### sc.SetVolumeOpenInterestMultiplier()

[Link](#scsetvolumeopeninterestmultiplier) - [Top](#top)

**Type**: Function

int32\_t **SetVolumeOpenInterestMultiplier**(const double **Multiplier**);

The **sc.SetVolumeOpenInterestMultiplier()** function sets the value of the **Volume/Open Interest Multiplier**.

The function returns a value of **0** if the chart containing the study that calls this function is not valid. Otherwise a value of **1** is returned.

#### Parameters

* [Multiplier](#commonfunctionparameterdescriptionsmultiplier)

### sc.SimpleMovAvg()

[Link](#scsimplemovavg) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **SimpleMovAvg**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **SimpleMovAvg**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.SimpleMovAvg()** function calculates the simple moving average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.SimpleMovAvg(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20);

float SimpleMovAvg = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.Slope()

[Link](#scslope) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Slope**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**);

SCFloatArrayRef **Slope**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**); [Auto-looping only](#noindexparam).

The **sc.Slope()** function calculates a simple slope.

This is the difference between the **FloatArrayIn** at the **Index** currently being calculated and the prior **FloatArrayIn** value.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.Slope(sc.BaseData[SC_LAST], sc.Subgraph[0]);

//Access the study value at the current index
float SlopeValue = sc.Subgraph[0][sc.Index]; 
            
```

### sc.SlopeToAngleInDegrees()

[Link](#scslopetoangleindegrees) - [Top](#top)

**Type**: Function

double **SlopeToAngleInDegrees**(double **Slope**);

The **sc.SlopeToAngleInDegrees()** function returns the angle in degrees defined by the given slope.

#### Parameters

* **Slope**: The value to be converted to degrees.

### sc.SmoothedMovingAverage()

[Link](#scsmoothedmovingaverage) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **SmoothedMovingAverage** (SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **SmoothedMovingAverage** (SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.SmoothedMovingAverage()** function calculates the Smoothed Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.SmoothedMovingAverage(sc.BaseData[SC_LAST], sc.Subgraph[0], 10);

float SmoothedMovingAverage = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.StartChartReplay()

[Link](#scstartchartreplay) - [Top](#top)

**Type**: Function

int **StartChartReplay**(int **ChartNumber**, float **ReplaySpeed**, const SCDateTime& **StartDateTime**);

The **sc.StartChartReplay** function starts a chart replay for the chart specified by the **ChartNumber** parameter. It is only possible to specify Chart Numbers that are within the same Chartbook which contains the chart which contains the study instance that this function is called from.

The chart replay is started *after* the study function returns.

.

It is not possible to start a replay on a chart which is still in the process of loading data from the chart data file. There will be no error returned but the replay will not start. It is possible to know when all charts are loaded in a Chartbook by using the [sc.IsChartDataLoadingCompleteForAllCharts]( #scIsChartDataLoadingCompleteForAllCharts) function.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)
* **ReplaySpeed**: The replay speed. A speed of 1 is the same as real time.
* **StartDateTime**: An [SCDateTime](SCDateTime.md) variable set to the starting Date-Time to start the replay at.

### sc.StartChartReplayNew()

[Link](#scstartchartreplaynew) - [Top](#top)

**Type**: Function

int **StartChartReplayNew**(n\_ACSIL::s\_ChartReplayParameters& **ChartReplayParameters**);

The **sc.StartChartReplayNew** function starts a chart replay for a chart. The parameters of the replay including the particular Chart Number to start the replay on are specified by the **ChartReplayParameters** data structure parameter.

It is only possible to start a replay for a chart which is within the same Chartbook which contains the chart which contains the study instance that this function is called from.

The chart replay is started *after* the study function returns.

It is not possible to start a replay on a chart which is still in the process of loading data from the chart data file. There will be no error returned but the replay will not start. It is possible to know when all charts are loaded in a Chartbook by using the [sc.IsChartDataLoadingCompleteForAllCharts]( #scIsChartDataLoadingCompleteForAllCharts) function.

#### Parameters

* **n\_ACSIL::s\_ChartReplayParameters**: The following are the members of this structure:
  + [Chart Number](#commonfunctionparameterdescriptionschartnumber)
  + **ReplaySpeed**: The replay speed. A speed of 1 is the same as real time. It is possible to use a fractional value for this.
  + **StartDateTime**: An [SCDateTime](SCDateTime.md) variable set to the starting Date-Time to start the replay at. This is in the chart's time zone.
  + **SkipEmptyPeriods**: When set to 1 this enables the [Skip Empty Periods](ReplayChart.md#automaticskippingofperiodswherethereisnotradingandsynchronization) option during a replay.
  + **ReplayMode**: Sets the replay mode for the replay. Can be one of the following values. The default for this is: REPLAY\_MODE\_UNSET.
    - REPLAY\_MODE\_UNSET = 0
    - REPLAY\_MODE\_STANDARD = 1
    - REPLAY\_MODE\_ACCURATE\_TRADING\_SYSTEM\_BACK\_TEST = 2
    - REPLAY\_MODE\_CALCULATE\_AT\_EVERY\_TICK = 3
    - REPLAY\_MODE\_CALCULATE\_SAME\_AS\_REAL\_TIME = 4
  + **ClearExistingTradeSimulationDataForSymbolAndTradeAccount**: Set this to 1, to clear Trade Activity, Orders and Position for the symbol and Trade Account to be replayed. Set this to 0 to not clear this data when starting the replay.

### sc.StartDownloadHistoricalData()

[Link](#scstartdownloadhistoricaldata) - [Top](#top)

**Type**: Function

int **StartDownloadHistoricalData**(double **StartingDateTime**);

The **sc.StartDownloadHistoricalData()** function starts a historical data download in the chart. This function can be used with Historical Daily data charts and Intraday charts.

The **StartingDateTime** is an [SCDateTime](SCDateTime.md) type and specifies the starting date-time of the historical data download in UTC. Set this to 0.0 to download from the last date in the chart data file or all available data in the case of an empty chart data file.

When **StartingDateTime** specifies a Date-Time which is earlier than the last Date-Time in the chart, then the historical data request starts at that time and the downloaded data replaces the data already in the chart.

This function only downloads historical data for the symbol of the chart and not prior contracts, in the case of a Continuous Futures Contract chart.

### sc.StartScanOfSymbolList()

[Link](#scstartscanofsymbollist) - [Top](#top)

**Type**: Function

int **StartScanOfSymbolList**(const int **ChartNumber**);

The **sc.StartScanOfSymbolList()** function initiates a scan for a chart in the same manner as if **Chart >> Start Scan** were selected.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

### sc.StdDeviation()

[Link](#scstddeviation) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **StdDeviation**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **StdDeviation**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.StdDeviation()** function calculates the standard deviation of the data.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.StdDeviation(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20);

float StdDeviation = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.StdError()

[Link](#scstderror) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **StdError**(SCFloatArrayRef **FloarArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **StdError**(SCFloatArrayRef **FloarArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.StdError()** function calculates the standard error of the data.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.StdError(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20);

float StdError = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.Stochastic()

[Link](#scstochastic) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Stochastic**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **FastKLength**, int **FastDLength**, int **SlowDLength**, unsigned int **MovingAverageType**);

SCFloatArrayRef **Stochastic**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut**, int **FastKLength**, int **FastDLength**, int **SlowDLength**, unsigned int **MovingAverageType**); [Auto-looping only](#noindexparam).

The **sc.Stochastic()** function calculates the Fast %K, Fast %D, and Slow %D Stochastic lines.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-1] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [FastKLength](#commonfunctionparameterdescriptionslength)
* [FastDLength](#commonfunctionparameterdescriptionslength)
* [SlowDLength](#commonfunctionparameterdescriptionslength)
* [MovingAverageType](#commonfunctionparameterdescriptionsmovingaveragetype)

#### Example

```cpp

sc.Stochastic(sc.BaseDataIn, sc.Subgraph[0], 10, 3, 3, MOVAVGTYPE_SIMPLE);

//Access the individual study values at the current index
float FastK = sc.Subgraph[0][sc.Index];

float FastD = sc.Subgraph[0].Arrays[0][sc.Index];

float SlowD = sc.Subgraph[0].Arrays[1][sc.Index];

//Copy to Visible Subgraphs
sc.Subgraph[1][sc.Index] = FastD;
sc.Subgraph[2][sc.Index] = SlowD;
            
```

### sc.StopChartReplay()

[Link](#scstopchartreplay) - [Top](#top)

**Type**: Function

int **StopChartReplay**(int **ChartNumber**);

The **sc.StopChartReplay** function stops a chart replay for the chart specified by the **ChartNumber** parameter.

It is only possible to specify Chart Numbers that are within the same Chartbook which contains the chart which contains the study instance that this function is called from.

The chart replay is stopped *after* the study function returns.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

#### Example

```cpp

            int Result = sc.StopChartReplay(sc.ChartNumber);
            
```

### sc.StopScanOfSymbolList()

[Link](#scstopscanofsymbollist) - [Top](#top)

**Type**: Function

int **StopScanOfSymbolList**(const int **ChartNumber**);

The **sc.StopScanOfSymbolList()** function stops a running scan on the given chart.

#### Parameters

* [Chart Number](#commonfunctionparameterdescriptionschartnumber)

### sc.StringToDouble()

[Link](#scstringtodouble) - [Top](#top)

**Type**: Function

double **StringToDouble** (const char\* **NumberString**);

The **sc.StringToDouble** function returns the number value represented by the character string **NumberString** as a double variable.

#### Parameters

* **NumberString**: The character string that represents the number to be converted.

### sc.SubmitOCOOrder()

[Link](#scsubmitocoorder) - [Top](#top)

**Type**: Function

int **sc.SubmitOCOOrder**(s\_SCNewOrder& **NewOrder**); Note: For use with Auto-Looping only.

Refer to the [sc.SubmitOCOOrder()](ACSILTrading.md#scsubmitocoorder) section on the [Automated Trading From an Advanced Custom Study](ACSILTrading.md) page for information on this function.

### sc.Summation()

[Link](#scsummation) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **Summation** (SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **Summation** (SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.Summation** function calculates the summation over the specified Length.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

Summation(sc.BaseDataIn[SC_HIGH], sc.Subgraph[0], 10);

float Summation = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.SuperSmoother2Pole()

[Link](#scsupersmoother2pole) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **SuperSmoother2Pole**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **SuperSmoother2Pole**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.SuperSmoother2Pole()** function calculates a smoothing of data and is frequently used in the studies written by John Ehlers.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.SuperSmoother2Pole(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 10);

float SuperSmoother2Pole = sc.Subgraph[0][sc.Index]; //Access the function value at the current index
            
```

### sc.SuperSmoother3Pole()

[Link](#scsupersmoother3pole) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **SuperSmoother3Pole**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **SuperSmoother3Pole**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.SuperSmoother3Pole()** function calculates a smoothing of data and is frequently used in the studies written by John Ehlers.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.SuperSmoother3Pole(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 10);

float SuperSmoother3Pole = sc.Subgraph[0][sc.Index]; //Access the function value at the current index
            
```

### sc.T3MovingAverage()

[Link](#sct3movingaverage) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **T3MovingAverage** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, float **Multiplier**, int **Index**, int **Length**);

SCFloatArrayRef **T3MovingAverage** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, float **Multiplier**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.T3MovingAverage()** function calculates the T3 Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-5] (Extra Arrays) are used for internal calculations and additional results output.
* [Multiplier](#commonfunctionparameterdescriptionsmultiplier)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.T3MovingAverage(sc.BaseDataIn[InputData.GetInputDataIndex()], T3, Multiplier.GetFloat(), Length.GetInt());
            
```

### sc.TEMA()

[Link](#sctema) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **TEMA** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **TEMA** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.TEMA()** function calculates the Triple Exponential Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-2] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.TEMA(sc.BaseData[SC_LAST], sc.Subgraph[0], 10);

float TEMA = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.TicksToPriceValue()

[Link](#sctickstopricevalue) - [Top](#top)

**Type**: Function

float **TicksToPriceValue**(unsigned int **Ticks**);

The **sc.TicksToPriceValue()** function converts a number of ticks into the floating point price value.

As noted in the below example, the ticks can come from a structure member that stores the information as ticks such as in the case of the s\_VolumeAtPriceV2::PriceInTicks.

#### Parameters

* **Ticks**: The number of ticks to be converted to a price value.

#### Example

```cpp

s_VolumeAtPriceV2 VolumeAtPrice;
sc.GetPointOfControlPriceVolumeForBar(BarIndex, VolumeAtPrice);

if (VolumeAtPrice.PriceInTicks != 0)
	Subgraph_VPOC.Data[BarIndex] = sc.TicksToPriceValue(VolumeAtPrice.PriceInTicks);
            
```

### sc.TimeMSToString()

[Link](#sctimemstostring) - [Top](#top)

**Type**: Function

SCString **TimeMSToString**(const SCDateTime& DateTimeMS);

The **sc.TimeMSToString** function returns a text string for the time within the given **DateTimeMS** parameter. This includes the milliseconds part of the time component. Any date component in the given **DateTime** parameter will be ignored.

#### Parameters

* [DateTimeMS](#commonfunctionparameterdescriptionsdatetimems)

#### Example

```cpp
 
if (sc.Index == sc.ArraySize - 1)
{
    // Log the current time.
    SCString TimeString = sc.TimeMSToString(sc.CurrentSystemDateTimeMS);

    sc.AddMessageToLog(TimeString, 0);
}
            
```

### sc.TimePeriodSpan()

[Link](#sctimeperiodspan) - [Top](#top)

**Type**: Function

double **TimePeriodSpan**(unsigned int **TimePeriodType**, int **TimePeriodLength**);

The **sc.TimePeriodSpan()** function calculates the span of time based upon a time period length unit enumeration constant and a length parameter specifying the number of units.

#### Parameters

* **TimePeriodType**: The type of time period. This can be any of:
  + TIME\_PERIOD\_LENGTH\_UNIT\_MINUTES
  + TIME\_PERIOD\_LENGTH\_UNIT\_DAYS
  + TIME\_PERIOD\_LENGTH\_UNIT\_WEEKS
  + TIME\_PERIOD\_LENGTH\_UNIT\_MONTHS
  + TIME\_PERIOD\_LENGTH\_UNIT\_YEARS
* **TimePeriodLength**: The number of units specified with **TimePeriodType**. For example if you want 1 Day, then you will set TimePeriodLength to 1 and **TimePeriodType** to **TIME\_PERIOD\_LENGTH\_UNIT\_DAYS**.

#### Example

```cpp

SCDateTime TimeIncrement = sc.TimePeriodSpan(TimePeriodType.GetTimePeriodType(),  TimePeriodLength.GetInt());
            
```

### sc.TimeSpanOfBar()

[Link](#sctimespanofbar) - [Top](#top)

**Type**: Function

SCDateTime **TimeSpanOfBar**(int **BarIndex**);

This function returns the time span of the bar specified by the **BarIndex** parameter.

#### Parameters

* [BarIndex](#commonfunctionparameterdescriptionsbarindex)

### sc.TimeStringToSCDateTime()

[Link](#sctimestringtoscdatetime) - [Top](#top)

**Type**: Function

SCDateTime **TimeStringToSCDateTime**(const SCString& **TimeString**)

The **sc.TimeStringToSCDateTime()** function converts the given **TimeString** parameter to an [SCDateTime](SCDateTime.md) type.

For information about the SCString type, refer to [Working With Text Strings and Setting Names](ACSILProgrammingConcepts.md#workingwithtextstrings).

#### Parameters

* **TimeString**: A string that represents the time to be converted. The supported format is is: **HH:MM:SS.MS**. Milliseconds are optional. The hours can have a negative sign in front of it.

### sc.TimeToString()

[Link](#sctimetostring) - [Top](#top)

**Type**: Function

SCString **TimeToString**(const SCDateTime& DateTime);

The **sc.TimeToString** function returns a text string for the time within the given **DateTime** parameter. Any date component in the given **DateTime** parameter will be ignored.

#### Parameters

* [DateTime](#commonfunctionparameterdescriptionsdatetime)

#### Example

```cpp
 
if (sc.Index == sc.ArraySize - 1)
{
    // Log the current time.
    SCString TimeString = sc.TimeToString(sc.CurrentSystemDateTime);

    sc.AddMessageToLog(TimeString, 0);
}
            
```

### sc.TradingDayStartsInPreviousDate()

[Link](#sctradingdaystartsinpreviousdate) - [Top](#top)

**Type**: Function

int **TradingDayStartsInPreviousDate**();

The **sc.TradingDayStartsInPreviousDate()** function returns a value of 1 if the Session Times for the chart on which the study that calls this function is located, is set to have the trading day start in the previous day. This will typically be the case if the option for **Use Evening Session** is set to **Yes**.

#### Parameters

* This function has no parameters

### sc.TriangularMovingAverage()

[Link](#sctriangularmovingaverage) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **TriangularMovingAverage** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **TriangularMovingAverage** (SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.TriangularMovingAverage()** function calculates the Triangular Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0] (Extra Array) is used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.TriangularMovingAverage(sc.BaseData[SC_LAST], sc.Subgraph[0], 10);

float TriangularMovingAverage = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.TRIX()

[Link](#sctrix) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **TRIX**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Index**, int **Length**);

SCFloatArrayRef **TRIX**(SCFloatArrayRef **FloatArrayIn**, SCSubgraphRef **SubgraphOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.TRIX()** function calculates the TRIX study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [SubgraphOut](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-2] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.TRIX(sc.BaseDataIn[SC_LAST], sc.Subgraph[0].Arrays[0], 20);

float TRIX = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.TrueRange()

[Link](#sctruerange) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **TrueRange**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**);

SCFloatArrayRef **TrueRange**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**); [Auto-looping only](#noindexparam).

The **sc.TrueRange()** function calculates the True Range study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.TrueRange(sc.BaseDataIn, sc.Subgraph[0]);

float TrueRange = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.UltimateOscillator()

[Link](#scultimateoscillator) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **UltimateOscillator**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut1**, SCSubgraphRef **SubgraphOut2**, int **Index**, int **Length1**, int **Length2**, int **Length3**);

SCFloatArrayRef **UltimateOscillator**(SCBaseDataRef **BaseDataIn**, SCSubgraphRef **SubgraphOut1**, SCSubgraphRef **SubgraphOut2**, int **Length1**, int **Length2**, int **Length3**); [Auto-looping only](#noindexparam).

The **sc.UltimateOscillator()** function calculates the Ultimate Oscillator.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [SubgraphOut1](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-8] (Extra Arrays) are used for internal calculations and additional results output.
* [SubgraphOut2](#commonfunctionparameterdescriptionssubgraphout). For this function, sc.Subgraph[].Arrays[0-3] (Extra Arrays) are used for internal calculations and additional results output.
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length1](#commonfunctionparameterdescriptionslength)
* [Length2](#commonfunctionparameterdescriptionslength)
* [Length3](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.UltimateOscillator(sc.BaseDataIn, sc.Subgraph[0], sc.Subgraph[1], 7, 14, 28);

 //Access the study value at the current index
float UltimateOscillator = sc.Subgraph[0][sc.Index];
            
```

### sc.UploadChartImage()

[Link](#scuploadchartimage) - [Top](#top)

**Type**: Function

The **sc.UploadChartImage** function when called will upload an image of the chart the study instance is applied to, to the Sierra Chart server. The full URL to the image is saved in a text file (**[Sierra Chart installation folder]\Images\ImageLog.txt**).

This functionality is documented on the [Image Upload Service](Image_to_Server.md) page.

Also refer to  [sc.SaveChartImageToFile](ACSIL_Members_Variables_And_Arrays.md#scsavechartimagetofile) and [sc.SaveChartImageToFileExtended()](#scsavechartimagetofileextended).

#### Parameters

* This function has no parameters

#### Example

```cpp

sc.UploadChartImage();
            
```

### sc.UserDrawnChartDrawingExists()

[Link](#scuserdrawnchartdrawingexists) - [Top](#top)

Refer to the [sc.UserDrawnChartDrawingExists()](ACSILDrawingTools.md#scuserdrawnchartdrawingexists) section on the [Using Tools from an Advanced Custom Study](ACSILDrawingTools.md) page for information on this function.

### sc.UseTool()

[Link](#scusetool) - [Top](#top)

**Type**: Function

For more information, refer to the [Using Tools with sc.UseTool()](ACSILDrawingTools.md#usingtools) section on the **Using Tools From an Advanced Custom Study** page.

### sc.VersionNumber()

[Link](#scversionnumber) - [Top](#top)

**Type**: Function

SCString **VersionNumber**();

The **sc.VersionNumber()** function returns the Sierra Chart software version as a string.

#### Parameters

* This function has no parameters

### sc.VHF()

[Link](#scvhf) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **VHF**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **VHF**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.VHF()** function calculates the Vertical Horizontal Filter study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.VHF(sc.BaseDataIn[SC_HIGH], sc.Subgraph[0], 10);

float VHF = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.VolumeWeightedMovingAverage()

[Link](#scvolumeweightedmovingaverage) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **VolumeWeightedMovingAverage** (SCFloatArrayRef **FloatArrayDataIn**, SCFloatArrayRef **FloatArrayVolumeIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **VolumeWeightedMovingAverage** (SCFloatArrayRef **InData**, SCFloatArrayRef **InVolume**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.VolumeWeightedMovingAverage()** function calculates the Volume Weighted Moving Average study.

#### Parameters

* [FloatArrayDataIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayVolumeIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.VolumeWeightedMovingAverage(sc.BaseData[SC_LAST], sc.BaseData[SC_VOLUME], sc.Subgraph[0], 10);

float VolumeWeightedMovingAverage = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.Vortex()

[Link](#scvortex) - [Top](#top)

**Type**: Intermediate Study Calculation Function

void **Vortex** (SCBaseDataRef **ChartBaseDataIn**, SCSubgraphRef **VMPlusOut**, SCSubgraphRef **VMMinusOut**, int **Index**, int **VortexLength**);

void **Vortex** (SCBaseDataRef **ChartBaseDataIn**, SCSubgraphRef **VMPlusOut**, SCSubgraphRef **VMMinusOut**, int **VortexLength**); [Auto-looping only](#noindexparam).

The **sc.Vortex()** study calculates the Vortex study.

#### Parameters

* [ChartBaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [VMPlusOut](#commonfunctionparameterdescriptionssubgraphout)
* [VMMinusOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [VortexLength](#commonfunctionparameterdescriptionslength)

### sc.WeightedMovingAverage()

[Link](#scweightedmovingaverage) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **WeightedMovingAverage**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **WeightedMovingAverage**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.WeightedMovingAverage()** function calculates the Weighted Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.WeightedMovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20);

float WeightedMovingAverage = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.WellesSum()

[Link](#scwellessum) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **WellesSum** (SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **WellesSum** (SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.WellesSum()** function calculates the Welles Summation of the **FloatArrayIn** data.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.WellesSum(sc.Subgraph[1], sc.Subgraph[0], 10);

float WellesSum = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.WildersMovingAverage()

[Link](#scwildersmovingaverage) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **WildersMovingAverage**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **WildersMovingAverage**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.WildersMovingAverage()** function calculates the Wilders Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.WildersMovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 20);

float WildersMovingAverage = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.WilliamsAD()

[Link](#scwilliamsad) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **WilliamsAD**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**);

SCFloatArrayRef **WilliamsAD**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**); [Auto-looping only](#noindexparam).

The **sc.WilliamsAD()** function calculates the Williams Accumulation/Distribution study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)

#### Example

```cpp

sc.WilliamsAD(sc.BaseDataIn, sc.Subgraph[0]);

float WilliamsAD = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.WilliamsR()

[Link](#scwilliamsr) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **WilliamsR**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **WilliamsR**(SCBaseDataRef **BaseDataIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.WilliamsR()** function calculates the Williams %R study.

#### Parameters

* [BaseDataIn](#commonfunctionparameterdescriptionsbasedatain)
* [FloatArrayOut](#commonfunctionparameterdescriptionsfloatarrayout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.WilliamsR(sc.BaseDataIn, sc.Subgraph[0], 10);

float WilliamsR = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.WriteBarAndStudyDataToFile()

[Link](#scwritebarandstudydatatofile) - [Top](#top)

**Type**: Function

int **sc.WriteBarAndStudyDataToFile**(int **StartingIndex**, SCString &**OutputPathAndFileName**, int **IncludeHiddenStudies**);

The **sc.WriteBarAndStudyDataToFile()** function writes the chart bar data and all of the Subgraphs data for all of the studies on the chart, to the specified file for the chart the study function instance is applied to.

#### Parameters

* **StartingIndex**: When this parameter is set to 0, then a new file is created, and data for all chart columns/bars are written to the file except for the last chart column/bar. A header line is also written to the file when this parameter is 0. When this is set to an index greater than zero, then the chart bar and study data starting at this bar index are appended to the existing specified file.
* **OutputPathAndFileName**: This is the complete path and filename for the file to output the chart bar and study data to.
* **IncludeHiddenStudies**: When this is set to a nonzero number, then hidden studies are also written to the file. Otherwise, they are not.

#### Example

For an example to use this function, refer to the **scsf\_WriteBarAndStudyDataToFile** function in the **/ACS\_Source/studies6.cpp** file in the folder Sierra Chart is installed to.

### sc.WriteBarAndStudyDataToFileEx()

[Link](#scwritebarandstudydatatofileex) - [Top](#top)

**Type**: Function

int WriteBarAndStudyDataToFileEx(const n\_ACSIL::s\_WriteBarAndStudyDataToFile& WriteBarAndStudyDataToFileParams);

The **sc.WriteBarAndStudyDataToFileEx** function writes the chart bar data and all of the Subgraphs data for all of the studies on the chart, to the specified file for the chart the study function instance is applied to.

It supports additional parameters for more control as compared to the [sc.WriteBarAndStudyDataToFile](#scwritebarandstudydatatofile) function.

#### Parameters

* **WriteBarAndStudyDataToFileParams**: An n\_ACSIL::s\_WriteBarAndStudyDataToFile structure that contains the information for writing the data to file. The members of the s\_WriteBarAndStudyDataToFile structure are as follows:
  + **int StartingIndex**: When this parameter is set to 0, then a new file is created, and data for all chart columns/bars are written to the file except for the last chart column/bar. A header line is also written to the file when this parameter is 0. When this is set to an index greater than zero, then the chart bar and study data starting at this bar index are appended to the existing specified file.
  + **SCString &OutputPathAndFileName**: This is the complete path and filename for the file to output the chart bar and study data to.
  + **int IncludeHiddenStudies**: When this is set to a nonzero number, then hidden studies are also written to the file. Otherwise, they are not.
  + **int IncludeHiddenSubgraphs**: When this is set to a nonzero number, then study Subgraphs which have the Draw Style set to either Hidden or Ignore are also written to the file. Otherwise, they are not.
  + **int AppendOnlyToFile**: When this is set to a nonzero number, then the rows of data beginning at **StartingIndex** are always appended to the file rather than the file being rewritten. An append will also occur when StartingIndex is > 0.
  + **int IncludeLastBar**: When this is set to a nonzero number, then the data for the last bar in the chart will be written to the file as well. You have to be careful when setting this to a nonzero number because during study updating, you will not want to use the same **StartingIndex** unless that is 0. Otherwise, the last bar and study data will be outputted more than once to the file.
  + **int UseUTCTime**: The default for this is 0. When this is set to 1, the exported Date-Time values will be in the UTC time zone.
  + **int WriteStudyData**: The default for this is 1. When this is set to 1, The study Subgraph data will also be exported.
  + **int UseTabDelimiter**: The default for this is 0. 0 means use a comma delimiter. 1 means use a tab delimiter.
  + **int RenkoBarsReplaceHighLowWithRenkoOpenClose**: The default for this is 0. When this is set to 1, the High and Low values for the bar data, are replaced with the Renko Open and Close values to represent original Renko bars that do not show the true High and Low values.

### sc.WriteFile()

[Link](#scwritefile) - [Top](#top)

**Type**: Function

int **WriteFile**(const int **FileHandle**, const char\* **Buffer**, const int **BytesToWrite**, unsigned int\* **p\_BytesWritten**);

The **sc.WriteFile()** function writes to a file opened with [sc.OpenFile()](#scopenfile) using the provided **FileHandle** from the sc.OpenFile function.

It writes the number of **BytesToWrite** that are stored in **Buffer**. The actual number of bytes written is then stored in **p\_BytesWritten**.

The function returns **0** if there is an error writing the bytes to the file. Otherwise, the function returns **1**.

#### Parameters

* [FileHandle](#commonfunctionparameterdescriptionsfilehandle)
* **Buffer**: Holds the data to write to the file.
* **BytesToWrite**: The number of bytes to write to the file.
* **p\_BytesWritten**: A pointer to the variable that stores the actual number of bytes written to the file.

#### Example

```cpp

	if (sc.Index == sc.ArraySize - 1)
	{
		int FileHandle;
		sc.OpenFile("Testing.txt", n_ACSIL::FILE_MODE_OPEN_TO_APPEND, FileHandle);
		
        unsigned int BytesWritten = 0;
        
		sc.WriteFile(FileHandle, "Test Line\r\n", 11, &BytesWritten);
        
		sc.CloseFile(FileHandle);
	} 
            
```

Also refer to [sc.OpenFile](#scopenfile), [sc.CloseFile](#scclosefile), [sc.ReadFile](#screadfile), [sc.WriteFile](#scwritefile), [sc.GetLastFileErrorCode](#scgetlastfileerrorcode).

### sc.YPixelCoordinateToGraphValue()

[Link](#scypixelcoordinatetographvalue) - [Top](#top)

**Type**: Function

double **YPixelCoordinateToGraphValue**(int **YPixelCoordinate**);

The **sc.YPixelCoordinateToGraphValue()** function calculates the study or main price graph value from the given Y-axis pixel coordinate. Each chart is divided into Chart Regions and each Chart Region can contain one or more graphs. This function will determine the value used by a graph based upon the scaling of the Chart Region for the given Y-axis coordinate.

This function can only function properly after the chart is actually drawn. Otherwise, 0 will be returned. It will return a value-based upon what was last drawn and not what the study function is currently doing. This is something to keep in mind because the function is going to be returning data based upon the last time the chart was drawn. The chart is always drawn after the study is calculated. So a study function may be receiving a value from this function which is not current relative to changes with the data in the study instance.

#### Parameters

* **YPixelCoordinate**: The Y-axis coordinate to convert to the graph value.

#### Example

```cpp

float GraphValue= sc.YPixelCoordinateToGraphValue(sc.ActiveToolYPosition);
            
```

### sc.ZeroLagEMA()

[Link](#sczerolagema) - [Top](#top)

**Type**: Intermediate Study Calculation Function

SCFloatArrayRef **ZeroLagEMA**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Index**, int **Length**);

SCFloatArrayRef **ZeroLagEMA**(SCFloatArrayRef **FloatArrayIn**, SCFloatArrayRef **FloatArrayOut**, int **Length**); [Auto-looping only](#noindexparam).

The **sc.ZeroLagEMA()** function calculates Ehlers' Zero Lag Exponential Moving Average study.

#### Parameters

* [FloatArrayIn](#commonfunctionparameterdescriptionsfloatarrayin)
* [FloatArrayOut](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* [Length](#commonfunctionparameterdescriptionslength)

#### Example

```cpp

sc.ZeroLagEMA(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], 10);

float ZeroLagEMA = sc.Subgraph[0][sc.Index]; //Access the study value at the current index
            
```

### sc.ZigZag()

[Link](#sczigzag) - [Top](#top)

**Type**: Function

SCFloatArrayRef **ZigZag** (SCFloatArrayRef **InputDataHigh**, SCFloatArrayRef **InputDataLow**, SCSubgraphRef **Out**, int **Index**, float **ReversalPercent**, int **StartIndex**);

SCFloatArrayRef **ZigZag** (SCFloatArrayRef **InputDataHigh**, SCFloatArrayRef **InputDataLow**, SCSubgraphRef **Out**, float **ReversalPercent**, int **StartIndex**); [Auto-looping only](#noindexparam).

SCFloatArrayRef **ZigZag** (SCFloatArrayRef **InputDataHigh**, SCFloatArrayRef **InputDataLow**, SCSubgraphRef **Out**, int **Index**, float **ReversalPercent**, float **ReversalAmount**, int **StartIndex**);

SCFloatArrayRef **ZigZag** (SCFloatArrayRef **InputDataHigh**, SCFloatArrayRef **InputDataLow**, SCSubgraphRef **Out**, float **ReversalPercent**, float **ReversalAmount**, int **StartIndex**); [Auto-looping only](#noindexparam).

The **sc.ZigZag()** function calculates the ZigZag study.

#### Parameters

* [InputDataHigh](#commonfunctionparameterdescriptionsfloatarrayin)
* [InputDataLow](#commonfunctionparameterdescriptionsfloatarrayin)
* [Out](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* **ReversalPercent**: The percentage change of the price values that must occur to begin a new Zig Zag line. Enter a value of **0.00** in order to use the **ReversalAmount** instead of this percentage.
* **ReversalAmount**: The price change of the price values that must occur to begin a new Zig Zag line.
* [StartIndex](#commonfunctionparameterdescriptionsindex)

### sc.ZigZag2()

[Link](#sczigzag2) - [Top](#top)

**Type**: Function

SCFloatArrayRef **ZigZag2** (SCFloatArrayRef **InputDataHigh**, SCFloatArrayRef **InputDataLow**, SCSubgraphRef **Out**, int **Index**, int **NumberOfBars**, float **ReversalAmount**, int **StartIndex**);

SCFloatArrayRef **ZigZag2** (SCFloatArrayRef **InputDataHigh**, SCFloatArrayRef **InputDataLow**, SCSubgraphRef **Out**, int **NumberOfBars**, float **ReversalAmount**, int **StartIndex**); [Auto-looping only](#noindexparam).

The sc.ZigZag2() function calculates the [Zig Zag](StudiesReference.md) study using [Calculation Mode 2](StudiesReference.md#inputs).

#### Parameters

* [InputDataHigh](#commonfunctionparameterdescriptionsfloatarrayin)
* [InputDataLow](#commonfunctionparameterdescriptionsfloatarrayin)
* [Out](#commonfunctionparameterdescriptionssubgraphout)
* [Index](#commonfunctionparameterdescriptionsindex)
* **NumberOfBars**: For information about this parameter, refer to [ZigZag Study Inputs](StudiesReference.md#inputs).
* **ReversalAmount**: For information about this parameter, refer to [ZigZag Study Inputs](StudiesReference.md#inputs).
* [StartIndex](#commonfunctionparameterdescriptionsindex)

### min()

[Link](#minimumfunction) - [Top](#top)

**Type**: Function

**min**(**a**, **b**)

**min()** takes two parameters (**a** and **b**) and returns the lesser of the two.

#### Parameters

* **a**: A value to be tested.
* **b**: A value to be tested.

#### Example

```cpp

int MinValue = min(-5, 3);

// MinValue will equal -5
            
```

### max()

[Link](#minimumfunction) - [Top](#top)

**Type**: Function

**max**(**a**, **b**)

**max()** takes two parameters (**a** and **b**) and returns the greater of the two.

#### Parameters

* **a**: A value to be tested.
* **b**: A value to be tested.

#### Example

```cpp

int MaxValue = max(-5, 3);

// MaxValue will equal 3
            
```

## Persistent Variable Functions

[Link](#persistentvariablefunctions) - [Top](#top)

The **GetPersistent\*** functions are for getting a reference to a persistent variable identified by the **Key** parameter. The **Key** parameter is an integer and can be any integer value in the range 0 to INT\_MAX. It can also be a negative number in the range of 0 to INT\_MIN.

The **SetPersistent\*** functions are for setting a value into a persistent variable identified by the **Key** parameter. The **Key** parameter is an integer and can be any integer value in the range 0 to INT\_MAX. It can also be a negative number in the range of 0 to INT\_MIN.

There are also the [sc.GetPersistent\*Fast](#scgetpersistentdoublefast) functions, which internally are much faster than the **GetPersistent\*** / **SetPersistent\*** functions. Especially when storing a large amount of data. These functions use an **Index** parameter instead of a **Key**. The stored value is looked up, as an offset from a stored memory address. Rather than the use of a map. There are no Set versions of these functions since the sc.GetPersistent\*Fast function returns a modifiable reference and is used for both getting and setting a persistent variable.

When using the **sc.GetPersistent\*Fast** functions, use an **Index** value of zero, and increment by one from there, for every persistent variable that you need. Each version of the function, Double/Float/Integer/SCDateTime, uses a unique Index variable which does not conflict with the other functions. And the Index for each of these functions is independent and unique from other study instances. The maximum value for **Index** is 9999 as of version 2657. Previous to that the maximum value is 999.

Since the **GetPersistent\*** functions return a reference to a persistent variable, usually this reference is what is used to set a value into the persistent variable and normally the **SetPersistent\*** functions will not be used.

The persistent variables are specific to *each individual study instance*. Each study has its own persistent variable storage.

The following example code explains how to define a variable which holds a reference to the reference returned.

```cpp

int& Variable = sc.GetPersistentInt(1);
    
```

All of the basic data types that Sierra Chart works with are supported for persistent variables.

The initial value for all persistent variables when they have not been previously set, is 0.

You may want to have the value in a variable remain persistent between calls to your study function. For example, when using [Automatic-Looping](ACS_ArraysAndLooping.md#automaticloopingiterating) (the default and recommended method of looping) your study function is called for every bar in the chart. If you want to have a variable retain its value between calls into your study function, then you need to use persistent variables.

For each data type, up to 50000 persistent variables are supported. You can use any **Key**  value to identify these 50000 values. When the 50000 values have been exceeded, getting or setting a persistent variable with a new key which exceeds the limit will only set the internal dummy value which is not persistent. Although using this number of persistent variables will have a performance impact and it is recommended to avoid if possible having this large number of persistent variables.

The persistent variables remain persistent between calls to your study function. However, they are not saved when a Chartbook is saved and closed, or when Sierra Chart is closed. They are unique to each and every instance of your study.

**Persistence of Persistent Variables**: Persistent variables remain persistent until the study is removed from the chart or when a chart is closed either individually or when a Chartbook is closed that the chart is part of.

Therefore, when a study is added to a chart either through the Chart Studies window or through Study Collections, persistent variables are initially set to 0 for that study. When a chart that is saved as part of a chartbook is opened, all of the persistent variables for all of the studies on that chart, are set to 0.

You can get and set persistent variables in the [sc.SetDefaults](ACSIL_Members_Variables_And_Arrays.md#scsetdefaults) code block at the top of the study function.

If you need to have permanent storage that is saved when a Chartbook is saved, then you will need to use the [sc.StorageBlock](ACSIL_Members_Variables_And_Arrays.md#scstorageblock) instead of persistent variables.

Also refer to [Chart Study Persistent Variable Functions](#chartstudypersistentvariablefunctions) for functions to get/set persistent data from other studies on the chart or different charts.

If these functions which get references to persistent data do not meet your requirements, then you will need to allocate your own memory. Refer to [Dynamic Memory Allocations](ACSILProgrammingConcepts.md#dynamicmemoryallocations).

### References to Persistent Variables

You can use references to give names to the persistent variables by defining new variables that refer to the persistent variables. This is helpful because it makes your code easier to understand and work with. This really is the usual way in which persistent variables should be worked with since the sc.GetPersistent\* functions always return a reference. Refer to the code example below for how to do this.

```cpp

// Use persistent variables to remember attached order IDs so they can be modified or canceled. 
int& Target1OrderID = sc.GetPersistentInt(1);
int& Stop1OrderID = sc.GetPersistentInt(2);

sc.SetPersistentFloat(1, 25.4f);

int& r_MenuID = sc.GetPersistentIntFast(1);
        
```

### Resetting Persistent Variables Example

Usually you will want to reset persistent variables back to default values when a study is recalculated. This does not happen automatically and must be specifically programmed when there is an indication a study is being fully recalculated. This can be done by using the following code below.

```cpp

if (sc.IsFullRecalculation && sc.Index == 0)//This indicates a study is being recalculated.
{

    // When there is a full recalculation of the study,
    // reset the persistent variables we are using
    sc.GetPersistentInt(0) = 0;
    sc.GetPersistentInt(1) = 0;
    sc.GetPersistentInt(2) = 0;
    sc.GetPersistentInt(3) = 0;
}
        
```

### References to SCDateTime Variables

[SCDateTime and SCDateTimeMS](SCDateTime.md) variables internally are of the same type. **sc.GetPersistentSCDateTime** can be used to obtain a persistent variable for either of these types.

## Fast Persistent Variable Functions

[Link](#fastpersistentvariablefunctions) - [Top](#top)

The **sc.GetPersistent\*Fast** functions perform in the same way as the sc.GetPersistent\* functions except that the retrieval of the persistent variable is faster. This makes a difference when there are hundreds of persistent variables being used of a particular type.

The other difference is they use an **Index** parameter as the key in the range of 0 to 999. Start at zero and increment up to 999 according to the number of variables needed. The maximum **Index** value has been increased in version 2657 to 9999. Always use as low of a value you can for **Index**. Since the higher the value, the more memory that is allocated.

Each version of the **sc.GetPersistent\*Fast** functions, Double/Float/Integer/SCDateTime, uses a unique Index variable which does not conflict with the other functions. And the Index for each of these functions is independent and unique from other study instances.

Minimize the number of calls into the persistent variable functions as much as possible whether the fast ones are used or not. The best performance is achieved when using [manual looping](ACS_ArraysAndLooping.md#manuallooping). Although if there are less than 50 persistent variables used within a function, the lookup of these variables is very fast and next to no processing time whether the fast persistent variable functions are used or not.

For complete documentation to use the persistent variable functions, refer to [Persistent Variable Functions](#persistentvariablefunctions)

```cpp

int& r_IntValue = sc.GetPersistentIntFast(0); 
r_IntValue = sc.Index;

int& r_MenuID = sc.GetPersistentIntFast(1);
    
```

## Chart Study Persistent Variable Functions

[Link](#chartstudypersistentvariablefunctions) - [Top](#top)

The **sc.GetPersistent\*FromChartStudy** and **sc.SetPersistent\*ForChartStudy** functions are identical to the [**GetPersistent\***](#persistentvariablefunctions) and the [**SetPersistent\***](#persistentvariablefunctions) functions except that they will get and set a persistent variable from/for the study specified by the **ChartNumber**  and **StudyID** parameters.

If the **ChartNumber** parameter is not valid, then an internal dummy variable is referenced with a value of zero and will not have the intended effect.

If setting or getting a persistent variable in another chart (Source chart), then when that Source chart is updated for any reason, the chart that made the reference to it (Destination chart), will have its studies calculated. In this way your study on the Destination chart will be aware of the changes to the persistent variable in a Source chart. When running a multiple chart Back Test, charts will be calculated in the proper order as well.

Refer to the code example below for usage.

```cpp

SCSFExport scsf_GetStudyPersistentVariableFromChartExample(SCStudyInterfaceRef sc)
{
    SCInputRef  ChartStudyReference = sc.Input[0];

    if (sc.SetDefaults)
    {
        // Set the configuration and defaults

        sc.GraphName = "Get Study Persistent Variable from Chart Example";
        sc.AutoLoop = 1;
    

        ChartStudyReference.Name = "Chart Study Reference";
        ChartStudyReference.SetChartStudyValues(1, 0);

        return;
    }

    //Get a reference to a persistent variable with key value 100 in the chart and study specified by the ChartStudyReference Input.
    float& FloatFromChartStudy =  sc.GetPersistentFloatFromChartStudy(ChartStudyReference.GetChartNumber(), ChartStudyReference.GetStudyID(), 100);
}
    
```

## Common Function Parameter Descriptions

[Link](#commonfunctionparameterdescriptions) - [Top](#top)

This is a list of all of the parameter descriptions for the common parameters for ACSIL functions in general.

This also includes Intermediate Study Calculation functions. For example, [sc.SimpleMovAvg()](#scsimplemovavg) is an intermediate study calculation function.

### BarIndex

[Link](#commonfunctionparameterdescriptionsbarindex) - [Top](#top)

int **BarIndex**: This specifies the index of the chart bar the function needs to perform a calculation on or perform some other function on.

### BaseDataIn

[Link](#commonfunctionparameterdescriptionsbasedatain) - [Top](#top)

SCBaseDataRef **BaseDataIn**: The BaseDataIn parameter is defined as a reference to a **SCFloatArrayArray**. This is the main chart graph arrays. The only object that you can use is **sc.BaseDataIn** for this parameter type.

### BaseDateTimeIn

[Link](#commonfunctionparameterdescriptionsbasedatetimein) - [Top](#top)

SCDateTimeArray **BaseDateTimeIn**: The type is a reference to a **SCDateTimeArray** . This is the main price/chart graph date and time array. Can only be **sc.BaseDateTimeIn**.

### ChartNumber

[Link](#commonfunctionparameterdescriptionschartnumber) - [Top](#top)

int **ChartNumber**: This specifies the specific chart identified by a number, within the same Chartbook the study instance using this parameter is contained within, that the function call is related to.

Each chart has a number and can be seen on the title bar of the chart window after the #. Depending upon the configuration of the [Chart Header](WorkingWithCharts.md#regiondataline) it may also be displayed along the top header line of the chart.

To specify the same chart number of the chart the study instance is on, use [sc.ChartNumber](ACSIL_Members_Variables_And_Arrays.md#scchartnumber) for this parameter.

The ChartNumber parameter can also be obtained through a Study Input. Refer to the [sc.Input[].SetChartStudyValues](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputSetChartStudyValues) Input and the related **sc.Input[].Get\*** functions.

### DateTime

[Link](#commonfunctionparameterdescriptionsdatetime) - [Top](#top)

SCDateTime **DateTime**: This specifies a Date-Time as an [SCDateTime](SCDateTime.md) type.

### DateTimeMS

[Link](#commonfunctionparameterdescriptionsdatetimems) - [Top](#top)

SCDateTime **DateTimeMS**: This specifies a Date-Time as an [SCDateTimeMS](SCDateTime.md) type which is identical to an SCDateTime type.

### FileHandle

[Link](#commonfunctionparameterdescriptionsfilehandle) - [Top](#top)

int **FileHandle**: This is a file handle obtained with the function [sc.OpenFile](#scopenfile).

### FloatArrayIn

[Link](#commonfunctionparameterdescriptionsfloatarrayin) - [Top](#top)

SCFloatArrayRef **FloatArrayIn**: The FloatArrayIn parameter is defined as a reference to a **SCFloatArray**. This is a data array of float values which is used as input to the intermediate study calculation function. This parameter type can be one of the following types: **sc.Subgraph[], sc.Subgraph[].Data, sc.Subgraph[].Arrays[]**, **sc.BaseDataIn[ArrayIndex]**, or **sc.BaseData[ArrayIndex]**.

### FloatArrayOut

[Link](#commonfunctionparameterdescriptionsfloatarrayout) - [Top](#top)

SCFloatArrayRef **FloatArrayOut**: The type is a reference to a **SCFloatArray**. This is an output data array of float values. You need to pass a **sc.Subgraph[], sc.Subgraph[].Data** or **sc.Subgraph[].Arrays** array.

### Index

[Link](#commonfunctionparameterdescriptionsindex) - [Top](#top)

int **Index**: This parameter is the Index to the element in an output array (**SubgraphOut**, **FloatArrayOut**) where the calculation result is outputted to. And the Index to the element or elements in the input array or arrays (**FloatArrayIn**, **BaseDataIn**, **BaseDateTimeIn**) that are used in the internal calculations of the intermediate study calculation function, and where the calculation begins when back referencing the data in the input arrays. This parameter is *optional* when using Automatic Looping. It can be left out in all of the intermediate study calculation functions and will internally be set to **sc.Index** .

### Length

[Link](#commonfunctionparameterdescriptionslength) - [Top](#top)

int **Length**: The number of data array elements used in the calculations. This definition applies to all parameters with **Length** in their name.

### Price

[Link](#commonfunctionparameterdescriptionsprice) - [Top](#top)

float **Price**: This is a price value as a float.

### MovingAverageType

[Link](#commonfunctionparameterdescriptionsmovingaveragetype) - [Top](#top)

int **MovingAverageType**: MovingAverageType needs to be set to the type of moving average you want to use. This description also applies to parameters that have **MovAvgType**, **MovingAverageType**, or **MAType** in their name. The following are the Moving Average type constants that you can use:

* **MOVAVGTYPE\_SIMPLE**: Simple moving average.
* **MOVAVGTYPE\_EXPONENTIAL**: Exponential moving average.
* **MOVAVGTYPE\_LINEARREGRESSION**: Linear regression or least-squares moving average.
* **MOVAVGTYPE\_WEIGHTED** : Weighted moving average.
* **MOVAVGTYPE\_WILDERS**: Wilder's moving average.
* **MOVAVGTYPE\_SIMPLE\_SKIP\_ZEROS**: Simple Moving Average that skips zero values.
* **MOVAVGTYPE\_SMOOTHED**: Smoothed moving average.

### Multiplier

[Link](#commonfunctionparameterdescriptionsmultiplier) - [Top](#top)

float **Multiplier**: A multiplier parameter is simply a value which is used to multiply another value used in the calculation. Such as multiplying the data from the input data array or a sub calculation from that input data array.

### StudyID

[Link](#commonfunctionparameterdescriptionsstudyid) - [Top](#top)

int **StudyID**: This is the study ID which is obtained using the following functions.

The StudyID is a unique ID of the study. For more information, refer to [Unique Study Instance Identifiers](ACSILProgrammingConcepts.md#uniquestudyinstanceidentifiers).

* [sc.Input[].GetStudyID](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputGetStudyID)
* [sc.Input[].SetStudyID](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputSetStudyID)
* [sc.Input[].GetChartStudySubgraphValues](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputGetChartStudySubgraphValues)
* [sc.Input[].SetChartStudySubgraphValues](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputSetChartStudySubgraphValues)
* [sc.Input[].SetChartStudyValues](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputSetChartStudyValues)
* [sc.Input[].SetStudySubgraphValues](index0fb1.html?page=doc/ACSIL_Members_scInputs.html#scInputSetStudySubgraphValues)
* [sc.StudyGraphInstanceID](ACSIL_Members_Variables_And_Arrays.md#scstudygraphinstanceid)

### StudySubgraphNumber

[Link](#commonfunctionparameterdescriptionsstudysubgraphnumber) - [Top](#top)

int32\_t **StudySubgraphNumber**: The one-based number for a specific subgraph in a study.

### Subgraph

[Link](#commonfunctionparameterdescriptionssubgraph) - [Top](#top)

SCSubgraphRef **Subgraph**: The type is a reference to an **sc.Subgraph[]**. You need to pass an **sc.Subgraph[]** object.

This type is either used for data input or output. In the case of data output, the results are written to the **sc.Subgraph[].Data** and **sc.Subgraph[].Arrays** arrays. The **sc.Subgraph[].Arrays** arrays are used for intermediate calculations and additional output.

### SubgraphIndex

[Link](#commonfunctionparameterdescriptionssubgraphindex) - [Top](#top)

int **SubgraphIndex**: The zero-based index for a specific subgraph in a study.

### SubgraphOut

[Link](#commonfunctionparameterdescriptionssubgraphout) - [Top](#top)

SCSubgraphRef **SubgraphOut**: The type is a reference to a **sc.Subgraph[]**. You need to pass a **sc.Subgraph[]** object. The results are written to the **sc.Subgraph[].Data** and **sc.Subgraph[].Arrays** arrays. The **sc.Subgraph[].Arrays** arrays are used for intermediate calculations and additional output.

### Symbol

[Link](#commonfunctionparameterdescriptionssymbol) - [Top](#top)

SCString **Symbol**: This specifies a [symbol](GettingStarted.md#notes) where a function requires that a symbol is specified.

To use the symbol of the chart which contains the study instance which is calling the function which requires this parameter, use [sc.Symbol](ACSIL_Members_Variables_And_Arrays.md#scsymbol).

---

\*Last modified Monday, 23rd June, 2025.
