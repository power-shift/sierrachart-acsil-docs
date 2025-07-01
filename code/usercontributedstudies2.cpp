
#include "sierrachart.h"


/*******************************************************************************
 * % change chart for upto 5 symbols

 * Use SC_OPEN for the reference point. This ensures that a 1 minute chart & a
 * 30 minute chart both uses the same reference point
 ******************************************************************************/
SCSFExport scsf_iCiPctChgComparison(SCStudyGraphRef sc) 
{
	// Study variables /////////////////////////////////////////////////////////
	float& sym1ZeroVal = sc.PersistVars->f1;
	float& sym2ZeroVal = sc.PersistVars->f2;
	float& sym3ZeroVal = sc.PersistVars->f3;
	float& sym4ZeroVal = sc.PersistVars->f4;
	float& sym5ZeroVal = sc.PersistVars->f5;

	SCSubgraphRef sym1plot  = sc.Subgraph[0];
	SCSubgraphRef sym2plot  = sc.Subgraph[1];
	SCSubgraphRef sym3plot  = sc.Subgraph[2];
	SCSubgraphRef sym4plot  = sc.Subgraph[3];
	SCSubgraphRef sym5plot  = sc.Subgraph[4];

	SCSubgraphRef sym1sym2diffplot  = sc.Subgraph[5];

	SCInputRef RefDateTime = sc.Input[0];
	SCInputRef Sym2 = sc.Input[1];
	SCInputRef Plotsym1sym2diff = sc.Input[2];
	SCInputRef UseSym3 = sc.Input[3];
	SCInputRef Sym3 = sc.Input[4];
	SCInputRef UseSym4 = sc.Input[5];
	SCInputRef Sym4 = sc.Input[6];
	SCInputRef UseSym5 = sc.Input[7];
	SCInputRef Sym5 = sc.Input[8];


	// This section only run once upon adding an instance of the study to a chart
	if(sc.SetDefaults) 
	{
		sc.GraphName = "iCiPctChgComparison";
		sc.StudyDescription = "% change chart for up to 5 symbols. Reference: <a href=""https://www.sierrachart.com/supportboard/showpost.php?p=215252&postcount=3"">https://www.sierrachart.com/supportboard/showpost.php?p=215252&postcount=3</a>";
		sc.DocumentationImageURL = "https://www.sierrachart.com/supportboard/attachment.php?attachmentid=8773&d=1339687965";
	
		sc.GraphRegion = 0;

		sc.FreeDLL = 0;

		sc.AutoLoop = 1;
		
		RefDateTime.Name = "Reference Date Time";
		RefDateTime.SetDateTime(0);
		Sym2.Name = "Symbol 2 chart reference (mandatory)";
		Sym2.SetChartNumber(2);
		Plotsym1sym2diff.Name = "Plot sym2 - sym1 diff";
		Plotsym1sym2diff.SetYesNo(1);
		UseSym3.Name = "Use symbol 3";
		UseSym3.SetYesNo(0);
		Sym3.Name = "Symbol 3 chart reference (optional)";
		Sym3.SetChartNumber(3);
		UseSym4.Name = "Use symbol 4";
		UseSym4.SetYesNo(0);
		Sym4.Name = "Symbol 4 chart reference (optional)";
		Sym4.SetChartNumber(4);
		UseSym5.Name = "Use symbol 5";
		UseSym5.SetYesNo(0);
		Sym5.Name = "Symbol 5 chart reference (optional)";
		Sym5.SetChartNumber(5);

		sym1plot.Name = "Sym 1 % change";
		sym1plot.PrimaryColor = RGB(0, 0, 0);
		sym1plot.DrawStyle = DRAWSTYLE_LINE;
		sym1plot.LineWidth = 1;

		sym2plot.Name = "Sym 2 % change";
		sym2plot.PrimaryColor = RGB(0, 0, 255);
		sym2plot.DrawStyle = DRAWSTYLE_LINE;
		sym2plot.LineWidth = 1;

		sym1sym2diffplot.Name = "Sym2 - Sym1 % chg. diff";
		sym1sym2diffplot.PrimaryColor = RGB(124, 124, 124);
		sym1sym2diffplot.DrawStyle = DRAWSTYLE_LINE;
		sym1sym2diffplot.LineWidth = 1;

		sym3plot.Name = "Sym 3 % change";
		sym3plot.PrimaryColor = RGB(18, 114, 16);
		sym3plot.DrawStyle = DRAWSTYLE_LINE;
		sym3plot.LineWidth = 1;

		sym4plot.Name = "Sym 4 % change";
		sym4plot.PrimaryColor = RGB(255, 0, 128);
		sym4plot.DrawStyle = DRAWSTYLE_LINE;
		sym4plot.LineWidth = 1;

		sym5plot.Name = "Sym 5 % change";
		sym5plot.PrimaryColor = RGB(255, 128, 64);
		sym5plot.DrawStyle = DRAWSTYLE_LINE;
		sym5plot.LineWidth = 1;

		return;	// Must return before doing any data processing if sc.SetDefaults is true
	}


	// Data processing /////////////////////////////////////////////////////////
	SCFloatArray SubgraphArray1, SubgraphArray2, SubgraphArray3, SubgraphArray4, SubgraphArray5;
	SCFloatArray SubgraphArrayO1, SubgraphArrayO2, SubgraphArrayO3, SubgraphArrayO4, SubgraphArrayO5;

	SubgraphArray1 = sc.BaseData[SC_LAST];
	SubgraphArrayO1 = sc.BaseData[SC_OPEN];

	sc.GetChartArray(Sym2.GetChartNumber(), SC_LAST, SubgraphArray2);
	sc.GetChartArray(Sym2.GetChartNumber(), SC_OPEN, SubgraphArrayO2);

	if(UseSym3.GetYesNo()) {
		sc.GetChartArray(Sym3.GetChartNumber(), SC_LAST, SubgraphArray3);
		sc.GetChartArray(Sym3.GetChartNumber(), SC_OPEN, SubgraphArrayO3);
	}

	if(UseSym4.GetYesNo()) {
		sc.GetChartArray(Sym4.GetChartNumber(), SC_LAST, SubgraphArray4);
		sc.GetChartArray(Sym4.GetChartNumber(), SC_OPEN, SubgraphArrayO4);
	}

	if(UseSym5.GetYesNo()) {
		sc.GetChartArray(Sym5.GetChartNumber(), SC_LAST, SubgraphArray5);
		sc.GetChartArray(Sym5.GetChartNumber(), SC_OPEN, SubgraphArrayO5);
	}

	if(sc.Index == 0) {
		// Get the reference to all the timeseries
		// Get the base values for all charts (SC_OPEN)
		int i = -1;
		int j = -1;
		
		i = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, RefDateTime.GetDateTime());
		if(i < 0)
			return;
		else
			sym1ZeroVal = SubgraphArrayO1[i];
		
		if(SubgraphArray2.GetArraySize() == 0)
			return;
		j = sc.GetNearestMatchForDateTimeIndex(Sym2.GetChartNumber(), i);
		if(j < 0)
			return;
		else
			sym2ZeroVal = SubgraphArrayO2[j];

		if(UseSym3.GetYesNo()) {
			if(SubgraphArray3.GetArraySize() == 0)
				return;
			j = sc.GetNearestMatchForDateTimeIndex(Sym3.GetChartNumber(), i);
			if(j < 0)
				return;
			else
				sym3ZeroVal = SubgraphArrayO3[j];
		}

		if(UseSym4.GetYesNo()) {
			if(SubgraphArray4.GetArraySize() == 0)
				return;
			j = sc.GetNearestMatchForDateTimeIndex(Sym4.GetChartNumber(), i);
			if(j < 0)
				return;
			else
				sym4ZeroVal = SubgraphArrayO4[j];
		}

		if(UseSym5.GetYesNo()) {
			if(SubgraphArray5.GetArraySize() == 0)
				return;
			j = sc.GetNearestMatchForDateTimeIndex(Sym5.GetChartNumber(), i);
			if(j < 0)
				return;
			else
				sym5ZeroVal = SubgraphArrayO5[j];
		}
	}
	else {
		sym1plot[sc.Index] = (SubgraphArray1[sc.Index] - sym1ZeroVal) / sym1ZeroVal * 100;

		// Negative chart numbers synchronize the charts
		sym2plot[sc.Index] = (SubgraphArray2[sc.GetNearestMatchForDateTimeIndex(Sym2.GetChartNumber() * -1, sc.Index)] - sym2ZeroVal) / sym2ZeroVal * 100;

		if(Plotsym1sym2diff.GetYesNo()) {
			sym1sym2diffplot[sc.Index] = sym2plot[sc.Index] - sym1plot[sc.Index];
		}
		
		if(UseSym3.GetYesNo()) {
			sym3plot[sc.Index] = (SubgraphArray3[sc.GetNearestMatchForDateTimeIndex(Sym3.GetChartNumber() * -1, sc.Index)] - sym3ZeroVal) / sym3ZeroVal * 100;
		}

		if(UseSym4.GetYesNo()) {
			sym4plot[sc.Index] = (SubgraphArray4[sc.GetNearestMatchForDateTimeIndex(Sym4.GetChartNumber() * -1, sc.Index)] - sym4ZeroVal) / sym4ZeroVal * 100;
		}

		if(UseSym5.GetYesNo()) {
			sym5plot[sc.Index] = (SubgraphArray5[sc.GetNearestMatchForDateTimeIndex(Sym5.GetChartNumber() * -1, sc.Index)] - sym5ZeroVal) / sym5ZeroVal * 100;
		}
	}
}

/*===========================================================================*/
SCSFExport scsf_VervoortCrossoverThinkScriptStyle(SCStudyInterfaceRef sc)
{
	// Inputs
	SCInputRef InputLength = sc.Input[0];

	// Subgraphs
	SCSubgraphRef Buy = sc.Subgraph[0];
	SCSubgraphRef Sell = sc.Subgraph[1];

	SCSubgraphRef tpTEMA1 = sc.Subgraph[10];
	SCSubgraphRef tpTEMA2 = sc.Subgraph[11];
	SCSubgraphRef TPZeroLagTEMA = sc.Subgraph[12];

	SCSubgraphRef haTEMA1 = sc.Subgraph[20];
	SCSubgraphRef haTEMA2 = sc.Subgraph[21];
	SCSubgraphRef HAZeroLagTEMA = sc.Subgraph[22];

	// SubgraphArrays
	SCFloatArrayRef tpPrice = sc.Subgraph[12].Arrays[0];
	SCFloatArrayRef haPrice = sc.Subgraph[22].Arrays[0];
	SCFloatArrayRef tpTEMAdiff = sc.Subgraph[12].Arrays[1];
	SCFloatArrayRef haTEMAdiff = sc.Subgraph[22].Arrays[1];

	// Set configuration variables
	if (sc.SetDefaults)
	{
		sc.GraphName = "Vervoort Crossover (ThinkScript Style)";
		sc.StudyDescription = "Sylvian Vervoort's Crossover";
		sc.GraphRegion = 0;

		InputLength.Name = "Length";
		InputLength.SetInt(55);
		InputLength.SetIntLimits(1, 99);
		InputLength.SetDescription("The number of bars to average.");

		Buy.Name = "Buy";
		Buy.PrimaryColor = COLOR_GREEN;
		Buy.DrawStyle = DRAWSTYLE_ARROWUP;
		Buy.LineWidth = 2;

		Sell.Name = "Sell";
		Sell.DrawStyle = DRAWSTYLE_ARROWDOWN;
		Sell.PrimaryColor = COLOR_RED;
		Sell.LineWidth = 2;

		TPZeroLagTEMA.Name = "TPZeroLagTEMA";
		TPZeroLagTEMA.PrimaryColor = COLOR_GREEN;
		TPZeroLagTEMA.DrawStyle = DRAWSTYLE_LINE;
		TPZeroLagTEMA.LineWidth = 1;

		HAZeroLagTEMA.Name = "HAZeroLagTEMA";
		HAZeroLagTEMA.PrimaryColor = COLOR_RED;
		HAZeroLagTEMA.DrawStyle = DRAWSTYLE_LINE;
		HAZeroLagTEMA.LineWidth = 1;

		// Auto Looping On
		sc.AutoLoop = 1;

		// During development only set to 1
		sc.FreeDLL = 0;

		// Must return
		return;
	}

	//
	// TYPICAL PRICE TEMA
	//

	tpPrice = sc.HLCAvg;

	sc.TEMA(tpPrice, tpTEMA1, InputLength.GetInt());
	sc.TEMA(tpTEMA1, tpTEMA2, InputLength.GetInt());
	tpTEMAdiff[sc.Index] = tpTEMA1[sc.Index] - tpTEMA2[sc.Index];

	TPZeroLagTEMA[sc.Index] = tpTEMA1[sc.Index] + tpTEMAdiff[sc.Index];

	//
	// HEIKIN ASHI TEMA
	//

	float haOpen;

	if (sc.Index == 0) {
		haOpen = sc.OHLCAvg[sc.Index];
	}
	else if (sc.Index == 1) {
		haOpen = (sc.OHLCAvg[sc.Index] + sc.OHLCAvg[sc.Index-1])/2;
	}
	else if (sc.Index == 2) {
		haOpen = (sc.OHLCAvg[sc.Index] + sc.OHLCAvg[sc.Index-1] + sc.OHLCAvg[sc.Index-2])/3;
	}
	else {
		haOpen = (sc.OHLCAvg[sc.Index] + sc.OHLCAvg[sc.Index-1] + sc.OHLCAvg[sc.Index-2] + sc.OHLCAvg[sc.Index-3])/4;
	}

	float haClose = sc.OHLCAvg[sc.Index];
	float haHigh = max(sc.High[sc.Index], haOpen);
	float haLow = min(sc.Low[sc.Index], haOpen);

	haPrice[sc.Index] = (haClose + haOpen + haHigh + haLow) / 4.0f;

	sc.TEMA(haPrice, haTEMA1, InputLength.GetInt());
	sc.TEMA(haTEMA1, haTEMA2, InputLength.GetInt());
	haTEMAdiff[sc.Index] = haTEMA1[sc.Index] - haTEMA2[sc.Index];

	HAZeroLagTEMA[sc.Index] = haTEMA1[sc.Index] + haTEMAdiff[sc.Index];

	//
	// CROSSOVER
	//

	Buy[sc.Index] = 0;
	Sell[sc.Index] = 0;

	if (sc.CrossOver(TPZeroLagTEMA, HAZeroLagTEMA) == CROSS_FROM_BOTTOM) {
		Buy[sc.Index] = sc.Low[sc.Index] - sc.TickSize;
	}
	else if (sc.CrossOver(TPZeroLagTEMA, HAZeroLagTEMA) == CROSS_FROM_TOP) {
		Sell[sc.Index] = sc.High[sc.Index] + sc.TickSize;
	}

} 


/************************************************************************/
int IsSwingHighAllowEqual(SCStudyInterfaceRef sc, int AllowEqual, int Index, int Length)
{
	for(int i = 1; i <= Length; i++)
	{

		if (AllowEqual)
		{
			if (sc.FormattedEvaluate(sc.BaseData [SC_HIGH][Index] , sc.BaseGraphValueFormat, LESS_OPERATOR, sc.BaseData [SC_HIGH][Index-i], sc.BaseGraphValueFormat)
				||
				sc.FormattedEvaluate(sc.BaseData [SC_HIGH][Index] , sc.BaseGraphValueFormat, LESS_OPERATOR, sc.BaseData [SC_HIGH][Index+i], sc.BaseGraphValueFormat)
				)
				return 0;


		}
		else
		{
			if (sc.FormattedEvaluate(sc.BaseData [SC_HIGH][Index] , sc.BaseGraphValueFormat, LESS_EQUAL_OPERATOR, sc.BaseData [SC_HIGH][Index-i], sc.BaseGraphValueFormat)
				||
				sc.FormattedEvaluate(sc.BaseData [SC_HIGH][Index] , sc.BaseGraphValueFormat, LESS_EQUAL_OPERATOR, sc.BaseData [SC_HIGH][Index+i], sc.BaseGraphValueFormat)
				)
				return 0;


		}
	}

	return 1;
}

//Taken from the SCSTUDYFUNCTIONS.CPP
/*==========================================================================*/
int IsSwingLowAllowEqual(SCStudyInterfaceRef sc, int AllowEqual, int Index, int Length)
{
	for(int i = 1; i <= Length; i++)
	{

		if (AllowEqual)
		{
			if (sc.FormattedEvaluate(sc.BaseData [SC_LOW][Index] , sc.BaseGraphValueFormat, GREATER_OPERATOR, sc.BaseData [SC_LOW][Index-i], sc.BaseGraphValueFormat)
				||
				sc.FormattedEvaluate(sc.BaseData [SC_LOW][Index] , sc.BaseGraphValueFormat, GREATER_OPERATOR, sc.BaseData [SC_LOW][Index+i], sc.BaseGraphValueFormat)
				)
				return 0;


		}
		else
		{
			if (sc.FormattedEvaluate(sc.BaseData [SC_LOW][Index] , sc.BaseGraphValueFormat, GREATER_EQUAL_OPERATOR, sc.BaseData [SC_LOW][Index-i], sc.BaseGraphValueFormat)
				||
				sc.FormattedEvaluate(sc.BaseData [SC_LOW][Index] , sc.BaseGraphValueFormat, GREATER_EQUAL_OPERATOR, sc.BaseData [SC_LOW][Index+i], sc.BaseGraphValueFormat)
				)
				return 0;


		}
	}

	return 1;
}

/************************************************************************/
SCSFExport scsf_SwingMarketStructure(SCStudyInterfaceRef sc)
{
	SCSubgraphRef SwingShortHigh = sc.Subgraph[0];
	SCSubgraphRef SwingShortLow = sc.Subgraph[1];
	SCSubgraphRef SwingIntermediateHigh = sc.Subgraph[2];
	SCSubgraphRef SwingIntermediateLow = sc.Subgraph[3];
	SCSubgraphRef SwingLongHigh = sc.Subgraph[4];
	SCSubgraphRef SwingLongLow = sc.Subgraph[5];

	SCInputRef ArrowOffsetValue= sc.Input[0];
	SCInputRef Length = sc.Input[1];
	SCInputRef AllowEqualBars = sc.Input[2];

	if ( sc.SetDefaults )
	{
		sc.GraphName = "Swing Market Structure Points";
		sc.StudyDescription = "Market Structure Short/Intermediate/Long Points";

		sc.FreeDLL = 0;
		sc.GraphRegion = 0;
		sc.ValueFormat= VALUEFORMAT_INHERITED;

		SwingShortHigh.Name = "Swing Short High";
		SwingShortHigh.DrawStyle = DRAWSTYLE_TEXT;
		SwingShortHigh.TextDrawStyleText = "s";
		SwingShortHigh.LineWidth = 9;
		SwingShortHigh.PrimaryColor = RGB(0,255,255);
		SwingShortHigh.DrawZeros = false;

		SwingShortLow.Name = "Swing Short Low";
		SwingShortLow.DrawStyle = DRAWSTYLE_TEXT;
		SwingShortLow.TextDrawStyleText = "s";
		SwingShortLow.LineWidth = 9;
		SwingShortLow.PrimaryColor = RGB(255,128,128);
		SwingShortLow.DrawZeros = false;

		SwingIntermediateHigh.Name = "Swing Intermediate High";
		SwingIntermediateHigh.DrawStyle = DRAWSTYLE_TEXT;
		SwingIntermediateHigh.TextDrawStyleText = "I";
		SwingIntermediateHigh.LineWidth = 13;
		SwingIntermediateHigh.PrimaryColor = RGB(0,255,255);
		SwingIntermediateHigh.DrawZeros = false;

		SwingIntermediateLow.Name = "Swing Intermediate Low";
		SwingIntermediateLow.DrawStyle = DRAWSTYLE_TEXT;
		SwingIntermediateLow.TextDrawStyleText = "I";
		SwingIntermediateLow.LineWidth = 13;
		SwingIntermediateLow.PrimaryColor = RGB(255,128,128);
		SwingIntermediateLow.DrawZeros = false;

		SwingLongHigh.Name = "Swing Long High";
		SwingLongHigh.DrawStyle = DRAWSTYLE_TEXT;
		SwingLongHigh.TextDrawStyleText = "L";
		SwingLongHigh.LineWidth = 15;
		SwingLongHigh.PrimaryColor = RGB(0,255,255);
		SwingLongHigh.DrawZeros = false;

		SwingLongLow.Name = "Swing Long Low";
		SwingLongLow.DrawStyle = DRAWSTYLE_TEXT;
		SwingLongLow.TextDrawStyleText = "L";
		SwingLongLow.LineWidth = 15;
		SwingLongLow.PrimaryColor = RGB(255,128,128);
		SwingLongLow.DrawZeros = false;

		ArrowOffsetValue.Name = "Arrow Offset as Percentage";
		ArrowOffsetValue.SetFloat(1.5f);

		Length.Name = "Length";
		Length.SetInt(2);
		Length.SetIntLimits(1,MAX_STUDY_LENGTH);

		// Need to add/repeat code for false - comments in BOLD below
		AllowEqualBars.Name = "Allow Equal High/Low Bars";
		AllowEqualBars.SetYesNo(true);

		sc.AutoLoop = true;
		return;
	}

	//Persistant Variables to retain the previous Swing High/Low info when going through the Index
	int& tempITHIndex     = sc.PersistVars->i1;
	int& tempLTHIndex     = sc.PersistVars->i2;
	int& tempITLIndex     = sc.PersistVars->i3;
	int& tempLTLIndex     = sc.PersistVars->i4;

	int& ITHFlag       = sc.PersistVars->i5;
	int& LTHFlag       = sc.PersistVars->i6;
	int& ITLFlag       = sc.PersistVars->i7;
	int& LTLFlag       = sc.PersistVars->i8;

	float& tempSTHigh    = sc.PersistVars->f1;
	float& tempITHigh   = sc.PersistVars->f2;
	float& tempSTLow      = sc.PersistVars->f3;
	float& tempITLow   = sc.PersistVars->f4;

	int IndexToEvaluate = sc.Index - Length.GetInt();

	if(IndexToEvaluate -Length.GetInt() < 0)
	{
		return;
	}

	float ArrowOffsetHighs=(sc.High[IndexToEvaluate])*(ArrowOffsetValue.GetFloat() * 0.01f);
	float ArrowOffsetLows=(sc.Low[IndexToEvaluate])*(ArrowOffsetValue.GetFloat() * 0.01f);

	SwingShortHigh[IndexToEvaluate] = 0;
	SwingShortLow[IndexToEvaluate] = 0;
	SwingIntermediateHigh[IndexToEvaluate] = 0;
	SwingIntermediateLow[IndexToEvaluate] = 0;
	SwingLongHigh[IndexToEvaluate] = 0;
	SwingLongLow[IndexToEvaluate] = 0;

	if(sc.Index == 0)
	{
		// Swing Highs
		tempSTHigh   = 0;
		tempITHigh     = 0;
		tempITHIndex   = 0;
		tempLTHIndex   = 0;
		ITHFlag     = 0;
		LTHFlag     = 0;

		//  Swing Lows
		tempSTLow   = 0;
		tempITLow     = 0;
		tempITLIndex   = 0;
		tempLTLIndex   = 0;
		ITLFlag     = 0;
		LTLFlag     = 0;

	}

	// check for Swing High
	if ( !AllowEqualBars.GetYesNo() )
	{
		if (sc.IsSwingHigh(sc.High, IndexToEvaluate, Length.GetInt() ) )
		{
			//BASICALLY THE SAME CODE FOR THE SWING HIGH AllowEqualBars 'ELSE IF' CONDITION (JUST BELOW) WOULD GO HERE
			//PROBABLY BEST TO WRITE A SEPERATE FUNCTION()... MOST EFFICIENT WAY?
		}
	}
	else if ( IsSwingHighAllowEqual( sc, true , IndexToEvaluate, Length.GetInt()))
	{
		//As we have a swing high, label it as a Short Term High
		SwingShortHigh[IndexToEvaluate] = sc.High[IndexToEvaluate] + ArrowOffsetHighs;

		//Potentially the first Short Term High could be part of a more important Intermediate high
		if(tempSTHigh == 0)
			tempSTHigh = sc.High[IndexToEvaluate];

		//A higher swing high than the last so potentially it could be an Intermediate Term High if the next swing high is lower, Flag it as potential.    
		if(sc.High[IndexToEvaluate] > tempSTHigh)
		{
			tempSTHigh = sc.High[IndexToEvaluate];
			ITHFlag = 1;
			tempITHIndex = IndexToEvaluate;
		}

		//We have a lower Short Term high and have now confirmed that potential Intermediate High, label Intermediate High and reset flags
		if((sc.High[IndexToEvaluate] < tempSTHigh) && (ITHFlag == 1))
		{
			SwingIntermediateHigh[tempITHIndex] = sc.High[tempITHIndex] + ArrowOffsetHighs;
			SwingShortHigh[tempITHIndex] = 0;
			ITHFlag = 0;
			tempSTHigh = sc.High[IndexToEvaluate]; // log the Short Term High for further checks

			//Potentially the first Intermediate Term High could be part of a more important Long Term High
			if(tempITHigh == 0)
				tempITHigh=sc.High[tempITHIndex];

			//A higher Intermediate swing high than the last so potentially could be a Long Term High, flag it as potential
			if(sc.High[tempITHIndex] > tempITHigh)
			{
				tempITHigh = sc.High[tempITHIndex];
				LTHFlag = 1;
				tempLTHIndex = tempITHIndex;
			}

			// We have a lower Intermediate High, so that potential Long Term high is confirmed, label Long Term High and reset flags
			if((sc.High[tempITHIndex] < tempITHigh) && (LTHFlag == 1))
			{
				SwingLongHigh[tempLTHIndex] = sc.High[tempLTHIndex] + ArrowOffsetHighs;
				SwingIntermediateHigh[tempLTHIndex] = 0;
				LTHFlag = 0;
				tempITHigh=sc.High[tempITHIndex];
			}
			else  //otherwise just another successive higher Intermediate high so log it
				tempITHigh=sc.High[tempITHIndex];          
		}
		else //otherwise just another successive higher Short Term high so log it
		{
			tempSTHigh = sc.High[IndexToEvaluate];
		}
	}

	// check for Swing Low
	if ( !AllowEqualBars.GetYesNo() )
	{
		if (sc.IsSwingLow(sc.Low, IndexToEvaluate, Length.GetInt() ) )
		{
			//BASICALLY THE SAME CODE FOR THE SWING LOW 'ELSE IF' CONDITION JUST BELOW WOULD GO HERE
			//PROBABLY BEST TO WRITE A SEPERATE FUNCTION()
		}
	}
	else if (IsSwingLowAllowEqual( sc, true , IndexToEvaluate, Length.GetInt()) )
	{
		// Similar to the logic for the Swing High (see above), only for lows obviously
		SwingShortLow[IndexToEvaluate] = sc.Low[IndexToEvaluate] - ArrowOffsetLows;

		if(tempSTLow == 0)
			tempSTLow = sc.Low[IndexToEvaluate];

		if(sc.Low[IndexToEvaluate] < tempSTLow)
		{
			tempSTLow = sc.Low[IndexToEvaluate];
			ITLFlag = 1;
			tempITLIndex = IndexToEvaluate;
		}

		if((sc.Low[IndexToEvaluate] > tempSTLow) && (ITLFlag == 1))
		{
			SwingIntermediateLow[tempITLIndex] = sc.Low[tempITLIndex] - ArrowOffsetLows;
			SwingShortLow[tempITLIndex] = 0;
			ITLFlag = 0;
			tempSTLow = sc.Low[IndexToEvaluate];
			if(tempITLow == 0)
				tempITLow=sc.Low[tempITLIndex];

			if(sc.Low[tempITLIndex] < tempITLow)
			{
				tempITLow = sc.Low[tempITLIndex];
				LTLFlag = 1;
				tempLTLIndex = tempITLIndex;
			}

			if((sc.Low[tempITLIndex] > tempITLow) && (LTLFlag == 1))
			{
				SwingLongLow[tempLTLIndex] = sc.Low[tempLTLIndex] - ArrowOffsetLows;
				SwingIntermediateLow[tempLTLIndex] = 0;
				LTLFlag = 0;
				tempITLow=sc.Low[tempITLIndex];
			}
			else
				tempITLow=sc.Low[tempITLIndex];          
		}
		else
		{
			tempSTLow = sc.Low[IndexToEvaluate];
		}
	}
}

/*===========================================================================*/
/*
jdt RSI Trend
Author: jsyd
Date: 11/25/2011
*/

/***********************************************************************/
SCSFExport scsf_RSITrend(SCStudyGraphRef sc)
{
	SCSubgraphRef rsiSubgraph = sc.Subgraph[0];
	SCSubgraphRef ma1Subgraph = sc.Subgraph[1];
	SCSubgraphRef ma2Subgraph = sc.Subgraph[2];
	SCSubgraphRef ma3Subgraph = sc.Subgraph[3];
	SCSubgraphRef macdSubgraph = sc.Subgraph[4];
	SCSubgraphRef neutralSubgraph = sc.Subgraph[5];
	
	SCInputRef version = sc.Input[0];
	SCInputRef neutralZone = sc.Input[1];
	SCInputRef rsiLength = sc.Input[2];
	SCInputRef rsiMALength = sc.Input[3];
	SCInputRef rsiType = sc.Input[4];
	SCInputRef rsiData = sc.Input[5];
	SCInputRef ma1Length = sc.Input[6];
	SCInputRef ma2Length = sc.Input[7];
	SCInputRef ma3Length = sc.Input[8];
	SCInputRef maType = sc.Input[9];
	SCInputRef maData = sc.Input[10];
	SCInputRef macdFastMA = sc.Input[11];
	SCInputRef macdSlowMA = sc.Input[12];
	SCInputRef macdMA = sc.Input[13];
	SCInputRef macdType = sc.Input[14];
	SCInputRef macdData = sc.Input[15];
	SCInputRef rsiLowLine = sc.Input[16];
	SCInputRef rsiLowerLine = sc.Input[17];
	
	if(sc.SetDefaults)
	{
		sc.GraphName="RSI w/Trend";
		sc.StudyDescription="Trend dependent RSI Overbought/Oversold signals";
		
		rsiSubgraph.Name = "RSI";
		rsiSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		rsiSubgraph.PrimaryColor = RGB(255, 255, 255);
		rsiSubgraph.LineWidth = 1;
		
		ma1Subgraph.Name = "Fast MA";
		ma1Subgraph.DrawStyle = DRAWSTYLE_FILLTOP_TRANSPARENT;
		ma1Subgraph.PrimaryColor = RGB(0, 128, 0);
		ma1Subgraph.SecondaryColor = RGB(128, 0, 0);
		ma1Subgraph.SecondaryColorUsed = 1;
		ma1Subgraph.LineWidth = 1;
		
		ma2Subgraph.Name = "Medium MA";
		ma2Subgraph.DrawStyle = DRAWSTYLE_FILLBOTTOM_TRANSPARENT;
		ma2Subgraph.PrimaryColor = RGB(128, 0, 0);
		ma2Subgraph.SecondaryColor = RGB(0, 128, 0);
		ma2Subgraph.SecondaryColorUsed = 1;
		ma2Subgraph.LineWidth = 1;
		
		ma3Subgraph.Name = "Slow MA";
		ma3Subgraph.DrawStyle = DRAWSTYLE_LINE;
		ma3Subgraph.PrimaryColor = RGB(0, 128, 0);
		ma3Subgraph.SecondaryColor = RGB(128, 0, 0);
		ma3Subgraph.SecondaryColorUsed = 1;
		ma3Subgraph.LineWidth = 5;
		
		macdSubgraph.Name = "MACD";
		macdSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		
		neutralSubgraph.Name = "Neutral Color";
		neutralSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		neutralSubgraph.PrimaryColor = RGB(128, 128, 128);
		
		// Inputs
		
		neutralZone.Name = "Neutral Zone - Fast/Medium MA Diff";
        neutralZone.SetFloat(.001);			
		
		rsiLowLine.Name = "RSI Trigger Line (with trend)";
        rsiLowLine.SetInt(40);
		rsiLowLine.SetIntLimits(1, 100);		
		
		rsiLowerLine.Name = "RSI Trigger Line (against trend/neutral)";
        rsiLowerLine.SetInt(30);
		rsiLowerLine.SetIntLimits(1, 100);		
		
		rsiLength.Name = "RSI Length";
        rsiLength.SetInt(21);
		
		rsiMALength.Name = "RSI MA Length";
        rsiMALength.SetInt(10);						

		rsiType.Name = "RSI MA Type";
		rsiType.SetMovAvgType(MOVAVGTYPE_WILDERS);
		
		rsiData.Name = "RSI Input Data";
		rsiData.SetInputDataIndex(SC_LAST);
		
		ma1Length.Name = "Fast MA Length";
		ma1Length.SetInt(34);
		
		ma2Length.Name = "Medium MA Length";
		ma2Length.SetInt(233);
		
		ma3Length.Name = "Slow MA Length";
		ma3Length.SetInt(377);						

		maType.Name = "MA Type";
		maType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		
		maData.Name = "MA Input Data";
		maData.SetInputDataIndex(SC_LAST);
		
		macdFastMA.Name = "MACD Fast MA Length";
		macdFastMA.SetInt(52);
		
		macdSlowMA.Name = "MACD Slow MA Length";
		macdSlowMA.SetInt(104);	
		
		macdMA.Name = "MACD MA Length";
		macdMA.SetInt(36);							

		macdType.Name = "MACD MA Type";
		macdType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);	
		
		version.Name = "Version";
		version.SetInt(1);
		version.SetIntLimits(1,1);	

		sc.DrawZeros = false;
        sc.AutoLoop = 1;
		sc.FreeDLL = 0;
		sc.GraphRegion = 0;
		sc.ValueFormat = 6;
		sc.ScaleRangeType=SCALE_SAMEASREGION;

		return;
	}

	int cur = sc.Index;
	int toolID = 827736;

/*======================================================================================
MA
========================================================================================*/
	sc.MovingAverage(sc.BaseDataIn[maData.GetInputDataIndex()], ma1Subgraph, maType.GetMovAvgType() , cur, ma1Length.GetInt());
	sc.MovingAverage(sc.BaseDataIn[maData.GetInputDataIndex()], ma2Subgraph, maType.GetMovAvgType() , cur, ma2Length.GetInt());
	sc.MovingAverage(sc.BaseDataIn[maData.GetInputDataIndex()], ma3Subgraph, maType.GetMovAvgType() , cur, ma3Length.GetInt());
	
/*=====================================================================================
RSI-W
=====================================================================================*/
	sc.RSI(sc.BaseDataIn[rsiData.GetInputDataIndex()], rsiSubgraph, rsiType.GetMovAvgType(), rsiLength.GetInt());
	
/*=====================================================================================
MACD
=====================================================================================*/
	float macdTrend = 0;
	sc.MACD(sc.BaseDataIn[macdData.GetInputDataIndex()], macdSubgraph, macdFastMA.GetInt(), macdSlowMA.GetInt(), macdMA.GetInt(), macdType.GetMovAvgType());
	float MACDMA = macdSubgraph.Arrays[2][cur];
//	if(macdSubgraph[cur] > MACDMA & macdSubgraph[cur] > 0) {
//		macdTrend = 1;
//	} else if(macdSubgraph[cur] < MACDMA & macdSubgraph[cur] < 0) {
//		macdTrend = -1;
//	}
	if(macdSubgraph[cur] > 0) {
		macdTrend = 1;
	} else if(macdSubgraph[cur] < 0) {
		macdTrend = -1;
	}
	
/*=======================================================================================
MA Trend Detection
========================================================================================*/
	int sTrend = 0;
	if(ma1Subgraph[cur] > ma2Subgraph[cur]) {
		sTrend = 1;
	} else if(ma1Subgraph[cur] < ma2Subgraph[cur]) {
		sTrend = -1;
	}
/*=======================================================================================
 Trend
========================================================================================*/
	int Trend = 0;
	float neuLength = neutralZone.GetFloat();
	float ma48Diff = ma2Subgraph[cur] - ma1Subgraph[cur];
	if(ma48Diff < 0) {
		ma48Diff = ma48Diff * -1;
	}
	if(ma48Diff > neuLength) {
		if((macdTrend == 1) && (sTrend == 1)) {
			Trend = 1;
		} else if((macdTrend == -1) && (sTrend == -1)) {
			Trend = -1;
		}
	}
	
	if(Trend == 1) {
		ma3Subgraph.DataColor[cur] = ma3Subgraph.PrimaryColor;
	} else if(Trend == -1) {
		ma3Subgraph.DataColor[cur] = ma3Subgraph.SecondaryColor;
	} else {
		ma3Subgraph.DataColor[cur] = neutralSubgraph.PrimaryColor;
	}
	
/*==========================================================================
 Overbought/Oversold
==========================================================================*/
	int obi = 0;
	int osi = 0;
	if(Trend == 1) { // Up Trend
		if((rsiSubgraph[cur] >= rsiLowLine.GetInt()) && ((rsiSubgraph[cur-1] < rsiLowLine.GetInt()) || (rsiSubgraph[cur-2] < rsiLowLine.GetInt()))) {
			osi = 1;
		}
		if((rsiSubgraph[cur] <= (100-rsiLowerLine.GetInt())) && ((rsiSubgraph[cur-1] > (100-rsiLowerLine.GetInt())) || (rsiSubgraph[cur-2] > (100-rsiLowerLine.GetInt())))) {
			obi = 1;
		}
	} else if(Trend == -1) { // Down Trend
		if((rsiSubgraph[cur] <= (100-rsiLowLine.GetInt())) && ((rsiSubgraph[cur-1] > (100-rsiLowLine.GetInt())) || (rsiSubgraph[cur-2] > (100-rsiLowLine.GetInt())))) {
			obi = 1;
		}
		if((rsiSubgraph[cur] >= rsiLowerLine.GetInt()) && ((rsiSubgraph[cur-1] < rsiLowerLine.GetInt()) || (rsiSubgraph[cur-2] < rsiLowerLine.GetInt()))) {
			osi = 1;
		}
	} else { // Trend is neutral
		if((rsiSubgraph[cur] >= rsiLowerLine.GetInt()) && ((rsiSubgraph[cur-1] < rsiLowerLine.GetInt()) || (rsiSubgraph[cur-2] < rsiLowerLine.GetInt()))) {
			osi = 1;
		} else if((rsiSubgraph[cur] <= (100-rsiLowerLine.GetInt())) && ((rsiSubgraph[cur-1] > (100-rsiLowerLine.GetInt())) || (rsiSubgraph[cur-2] > (100-rsiLowerLine.GetInt())))) {
			obi = 1;
		}
	}
	
	s_UseTool Tool;
	if((obi == 1) || (osi ==1)) {
		Tool.Clear();
		Tool.UseRelativeVerticalValues = 1;
		Tool.ChartNumber = sc.ChartNumber;
		Tool.DrawingType = DRAWING_LINE;
		Tool.Region = sc.GraphRegion;
		Tool.AddMethod = UTAM_ADD_OR_ADJUST;
		Tool.BeginDateTime = sc.BaseDateTimeIn[cur];
		Tool.EndDateTime = sc.BaseDateTimeIn[cur];
		Tool.BeginValue = 0;
		Tool.EndValue = 100;
		Tool.LineNumber = toolID+cur;
		Tool.LineWidth = 1;
	}
	if(obi == 1) {
		Tool.Color = ma1Subgraph.SecondaryColor;
		sc.UseTool(Tool);
	} else if(osi == 1) {
		Tool.Color = ma1Subgraph.PrimaryColor;
		sc.UseTool(Tool);
	}

}
