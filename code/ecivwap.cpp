/*  ------------------------------------------------------------------------

This program includes : ECIVwap ECIAnchorVwap and ECIVwapChannel

Developped by Emmanuel Chriqui (aka wwwingman).
Contact : ecivwap@chriqui.name

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/gpl.txt
	
The ECIVwap computes Volume Weighted Average Price for Daily/Weekly/Monthly/Quarterly/Yearly periods, and draws extensions of previous periods.
Vwap computation tries to be as accurate as possible since using volume at all prices in each bar, and is compatible with Sierra Vwap when using "Base on Underlying Data" option.
This is also true for the standard deviation calculation.

The ECIAnchorVwap uses Vwap computation algorithm, but the start and end dates are can be set in different ways (manually, automatically, at major reversal points, etc.).

The ECIVwapChannel uses Vwap computation algorithm, but draws a vwap channel of a user based period number of bars.

The ECIVwapBracket uses Vwap computation algorithm, and draws a vwap until price breaks out of bottom/top levels 4 (excess levels).

Changelog
V1.5 :
* Maintenance : adapted code to recent sierra changes on PersisVars and VAP structures.
V1.4 :
* Change : all studies name start with ECIVwap for clarity
* Enhance : add input only computation mode to all studies (no volume per price)
* Enhance : add SetAllColors to ECIVwap
* Enhance : add vpoc drawing to ECIVwapChannel (experimental) 
* New : added ECIVwapBracket, an automatic way to draw vwap brackets (experimental)
* Maintenance : major code cleanup factoring and studies options harmonization
V1.3 : 
* Fix ECIVwapChannel : start drawing stdev on period (was on first bar).
V1.2 :
* New indicator : ECIVwapChannel. draws a vwap channel of a user based period number of bars.
V1.1 :
* Fix : wrong vwap on bars with no volume (thin markets/renko..).
* Misc : removed version from DLL name.
V1.0 :
* Minor : changed default colors to light blue
* Maintenance : code cleanup, filled sierra description fields
* Misc : Distribution of code to Sierra Chart user contributed studies.
V0.10 : 
* Enhance AnchorVwap : start date modes : manual (mouse anchoring), on higher high, on lower low, on last closed bar
* Fix AnchorVwap : when duplicating chart, manual mouse anchoring was not possible (hidden menu)
V0.9 :
* Enhance AnchorVwap : added 2 end date modes : end on previous bar, end on start bar.
* Fix : AnchorVwap was inefficient under some conditions and too heavy for CPU. Rolled back and fixed code.
V0.8 :
* Enhance AnchorVwap : replaced manual start date with contextual menu anchoring
* Enhance AnchorVwap : new option : set all colors automatically
* Enhance Vwap : 4 extension bands to Vwap instead of 2.
* Change Vwap & AnchorVwap : default multiplier is now 0.5
* New : GPL licence in code
* Maintenance : AnchorVwap code simplification and cleanup.
V0.7 :
* Fix : Wrong vwap calculation on very heavy volume bars (ex:ES monthly/quarterly bars..).
* Enhance : 4 extension bands to AnchorVwap instead of 2.
* Minor : default multiplier is now 0.5 (was 1).
V0.6 :
* Enhance AnchorVwap : 4 modes, continuos, end on date, end on higher high, end on lower low
* Fix : removed continous contract start date input from ECIVwap
* Minor : Range scale default is now same as region
V0.5 :
* Change : replaced ECIVwap continuous contract with new study  
* New : added ECIAnchorVwap study, a continuous period vwap with start and end period, and an extension option.
* Enhance : draw study under main price 
* Maintenance : code cleanup and factoring.
V0.4 :
* Enhance : Full compatibility with Sierra Vwap
* Bug fix : Quaterly vwap was broke in V0.3
* Enhance : better compatibility spreadsheet tests (had false positive related to floating point calculation)
V0.3 : 
* Enhance : On intraday charts, Vwap period start on session beginning for daily and weekly vwaps
* Maintenance : code cleanup.
* Maintenance : compatibility with Sierra Vwap testing chartbook.
V0.2 :
* Enhance : 4 bands instead of 2
* Change : replaced value extension option by 3 parameters extensions : vwap/band1/band2
V0.1 : Initial release 
* New : Continuous/Daily/Weekly/Monthly/Quarterly/Yearly vwap
* New : Standard deviation bands
* New : Previous period value extension
------------------------------------------------------------------------ */
#include "sierrachart.h"

#define DEV_FREE_DLL 0 // 1 for development, 0 when operationnal

const SCString g_StudyVersion 	= "V1.5";
const SCString g_VwapName		= "ECIVwap";
const SCString g_VwapAnchorName	= "ECIVwapAnchor";
const SCString g_VwapBracketName= "ECIVwapBracket";
const SCString g_VwapChannelName= "ECIVwapChannel";

const SCString g_ECIVwapStudyDescription = 
"<p>The ECIVwap computes Volume Weighted Average Price for Daily/Weekly/Monthly/Quarterly/Yearly periods, and draws extensions of previous periods. Vwap computation tries to be as accurate as possible since using volume at all prices in each bar, and is compatible with Sierra Vwap when using *Base on Underlying Data* option. This is also true for the standard deviation calculation.</p>"
"<p>Developped by Emmanuel Chriqui (aka wwwingman, contact : ecivwap@chriqui.name)</p>";
const SCString g_ECIVwapAnchorStudyDescription = 
"<p>The ECIVwapAnchor uses ECIVwap computation algorithm, but the start and end dates are can be set in different ways (manually, automatically, at major reversal points, etc.).</p>"
"<p>Developped by Emmanuel Chriqui (aka wwwingman, contact : ecivwap@chriqui.name)</p>";
const SCString g_ECIVwapBracketStudyDescription = 
"<p>The ECIVwapBracket draws bracket based on Vwap. A new bracket starts when the last bar breaks out (closes outside) the 2nd standard deviation.</p>"
"<p>Developped by Emmanuel Chriqui (aka wwwingman, contact : ecivwap@chriqui.name)</p>";
const SCString g_ECIVwapChannelStudyDescription = 
"<p>The ECIVwapChannel uses Vwap computation algorithm, but draws a vwap channel of a user based period number of bars.</p>"
"<p>Developped by Emmanuel Chriqui (aka wwwingman, contact : ecivwap@chriqui.name)</p>";

// Sierra DLL name
const SCString g_ScDllName = g_VwapName+g_StudyVersion;
SCDLLName (g_ScDllName)

// supported period type by ECIVwap
enum ECI_PeriodType
{
	ECI_PERIOD_TYPE_BAR 		= 0,
	ECI_PERIOD_TYPE_DAILY 		= 1,
	ECI_PERIOD_TYPE_WEEKLY 	= 2,
	ECI_PERIOD_TYPE_MONTHLY 	= 3,
	ECI_PERIOD_TYPE_QUARTERLY 	= 4,
	ECI_PERIOD_TYPE_YEARLY 	= 5,
};
#define ECI_PERIOD_INPUT_STRINGS "Bar;Daily;Weekly;Monthly;Quarterly;Yearly"

// supported start dates types for ECIVwapAnchor
enum ECI_StartDateType
{
	ECI_STARTDATETYPE_MANUAL = 0,
	ECI_STARTDATETYPE_HIGHERHIGH = 1,
	ECI_STARTDATETYPE_LOWERLOW = 2,
	ECI_STARTDATETYPE_LASTCLOSEDBAR = 3,
	//WORK IN PROGRESS ECI_STARTDATETYPE_LASTBRACKET = 4
};
#define ECI_STARTDATETYPE_STRINGS "Manual (mouse anchoring);Start on Higher High;Start on Lower Low;Start on Last Closed Bar"

// supported end dates types for ECIVwapAnchor
enum ECI_EndDateType
{
	ECI_ENDDATETYPE_CONTINUOUS = 0,
	ECI_ENDDATETYPE_STOP_ON_ENDDATE = 1,
	ECI_ENDDATETYPE_STOP_ON_HIGHERHIGH = 2,
	ECI_ENDDATETYPE_STOP_ON_LOWERLOW = 3,
	ECI_ENDDATETYPE_STOP_ON_LASTCLOSEDBAR = 4,
	ECI_ENDDATETYPE_STOP_ON_STARTBAR = 5,
};
#define ECI_ENDDATETYPE_STRINGS "Continuous;Stop on End Date;Stop on Higher High;Stop on Lower Low;Stop on Last Closed Bar;Stop on Start Bar"

// misc
#define ECIVWAP_MAIN_COLOR RGB(0,128,255)

#define ECIVWAP_VWAP_COLOR RGB(0,128,255)
#define ECIVWAP_LEVELS_COLOR RGB(0,128,255)

#define ECIVWAP_VPOC_COLOR COLOR_DEEPPINK


/* ==========================================================================
//
// compute bar vwap
// sc : sierra study context
// barIndex : index of bar to compute
// inputOnly : if true, base calculation on main input. otherwise, use input+volume
// barVwap : where result is returned
//
========================================================================== */
void ECIVwap_ComputeBarVwap(const SCStudyGraphRef sc, const unsigned int barIndex, const bool inputOnly, SCFloatArrayRef barVwap)
{
	if ( ! inputOnly )
	{
		unsigned int _barVolume = 0;
		float 		 _barPriceXVolumeSum = 0;
		const s_VolumeAtPriceV2 *_p_vap;

		int _barPriceInTicks = INT_MIN;
		while (sc.VolumeAtPriceForBars->GetNextHigherVAPElement(barIndex, _barPriceInTicks, &_p_vap))
		{
			_barVolume 		+= _p_vap->Volume;
			_barPriceXVolumeSum += ((float)_barPriceInTicks * (float)_p_vap->Volume);
		}
		if ( _barVolume != 0 ) // can happen on thin markets, renko charts, gaps etc...
			barVwap[barIndex] = _barPriceXVolumeSum * sc.TickSize / (float)_barVolume;
		else
			barVwap[barIndex] = ( sc.Open[barIndex] + sc.High[barIndex] + sc.Low[barIndex] + sc.Close[barIndex] ) / 4.0f;
	}
	else
	{
		barVwap[barIndex] = ( sc.Open[barIndex] + sc.High[barIndex] + sc.Low[barIndex] + sc.Close[barIndex] ) / 4.0f;
	}
}

/* ==========================================================================
//
// compute period vwap
//
// sc : sierra study context
// periodStartIndex : where vwap starts
// periodEndIndex : where vwap ends
// barVwap : vwap for each bar of period
// inputOnly : if true, base calculation on main input. otherwise, use input+volume
// vwap : where result is returned
//
========================================================================== */
void ECIVwap_ComputePeriodVwap(const SCStudyGraphRef sc, const int periodStartIndex, const unsigned int periodEndIndex, const SCFloatArrayRef barVwap, const bool inputOnly, SCFloatArrayRef vwap)
{
	if ( ! inputOnly )
	{
		float _periodVolume = 0.f;
		float _periodVwapXVolumeSum = 0.f;
		
		for (unsigned int _i = periodStartIndex; _i <= periodEndIndex ; _i++)
		{
			_periodVolume += sc.Volume[_i];
			_periodVwapXVolumeSum += (barVwap[_i] * sc.Volume[_i]);
		}
		vwap[periodEndIndex] = _periodVwapXVolumeSum / _periodVolume;
	}
	else
	{
		float _periodHeight = 0.f;
		float _periodVwapXHeightSum = 0.f;
		
		for (unsigned int _i = periodStartIndex; _i <= periodEndIndex ; _i++)
		{
			float _height = sc.High[_i] - sc.Low[_i];
			_periodHeight += _height;
			_periodVwapXHeightSum += (barVwap[_i] * _height);
		}
		vwap[periodEndIndex] = _periodVwapXHeightSum / _periodHeight;
	}
}

/* ==========================================================================
//
// compute standard deviation levels of vwaps
//
// sc : sierra study context
// periodStartIndex : where vwap starts
// periodEndIndex : where vwap ends
// vwap : vwap of period
// inputOnly : if true, base calculation on main input. otherwise, use input+volume
// multiplier : multiplier of standard deviation levels
// tb1-tb4 : where result is returned : top of band number 1..2..3..4
// bb1-bb4 : where result is returned : bottom of band number 1..2..3..4
//
========================================================================== */
void ECIVwap_ComputeStddev(const SCStudyGraphRef sc, const unsigned int periodStartIndex, const unsigned int periodEndIndex, const SCFloatArrayRef vwap, const float multiplier, const bool inputOnly, 
							SCFloatArrayRef tb1, SCFloatArrayRef bb1, 
							SCFloatArrayRef tb2, SCFloatArrayRef bb2,
							SCFloatArrayRef tb3, SCFloatArrayRef bb3,
							SCFloatArrayRef tb4, SCFloatArrayRef bb4 ) 
{
	float _offset;

	// compute vwap variance (offset)
	if ( ! inputOnly  )
	{
		float _periodVolume = 0.f;
		float _periodVarianceSum = 0.f;
		
		for (unsigned int _i = periodStartIndex; _i <= periodEndIndex ; _i++)
		{
			_periodVolume += sc.Volume[_i];
			
			float _priceInput = sc.Close[_i]-vwap[_i];
			_periodVarianceSum += (_priceInput*_priceInput*sc.Volume[_i]);
		}
		_offset = sqrt(_periodVarianceSum / _periodVolume);
	}
	else
	{
		float _periodHeight = 0.f;
		float _periodVarianceSum = 0.f;
		
		for (unsigned int _i = periodStartIndex; _i <= periodEndIndex ; _i++)
		{
			float _height = sc.High[_i] - sc.Low[_i];			
			_periodHeight += _height;
			
			float _priceInput = sc.Close[_i]-vwap[_i];
			_periodVarianceSum += (_priceInput*_priceInput*_height);
		}
		_offset = sqrt(_periodVarianceSum / _periodHeight);
	}
	
	// compute standard deviation levels
	tb1[periodEndIndex] = vwap[periodEndIndex] + 1 * multiplier * _offset;
	bb1[periodEndIndex] = vwap[periodEndIndex] - 1 * multiplier * _offset;
	tb2[periodEndIndex] = vwap[periodEndIndex] + 2 * multiplier * _offset;
	bb2[periodEndIndex] = vwap[periodEndIndex] - 2 * multiplier * _offset;
	tb3[periodEndIndex] = vwap[periodEndIndex] + 3 * multiplier * _offset;
	bb3[periodEndIndex] = vwap[periodEndIndex] - 3 * multiplier * _offset;
	tb4[periodEndIndex] = vwap[periodEndIndex] + 4 * multiplier * _offset;
	bb4[periodEndIndex] = vwap[periodEndIndex] - 4 * multiplier * _offset;
}

/* ==========================================================================
//
// Check if a new vwap period need to start (session change/day change...)
//
// sc : sierra study context
// periodStartIndex : where vwap starts
// periodEndIndex : where vwap ends
// vwap : vwap of period
// multiplier : multiplier of standard deviation levels
// tb1-tb4 : where result is returned : top of band number 1..2..3..4
// bb1-bb4 : where result is returned : bottom of band number 1..2..3..4
//
============================================================================ */
void ECIVwap_ComputeNewPeriod(const SCStudyGraphRef sc, const ECI_PeriodType periodType, bool& startNewPeriod)
{
	startNewPeriod = false;
	
	// bar period is simply the bar vwap, so on each bar we have a new period
	if ( periodType == ECI_PERIOD_TYPE_BAR )
	{
		startNewPeriod = true;
		return;
	}

	if ( sc.Index < 1) // need at least two bars
		return;
	
	//
	// New period computation is different with daily sessions periods and overnight periods (crossing 00:00)
	// On daily session we look for the daily start session.
	// On overnight sessions wek look the next day start session.
	//		
	SCDateTime 	currentBarDateTime = sc.BaseDateTimeIn[sc.Index];
	int 		currentBarDate = currentBarDateTime.GetDate();
	SCDateTime  currentBarTradingStartDateTime = sc.GetStartDateTimeForTradingDate(currentBarDate);
	int			currentBarTradingStartDate =  currentBarTradingStartDateTime.GetDate();

	SCDateTime 	previousBarDateTime = sc.BaseDateTimeIn[sc.Index-1];
	int			previousBarDate= previousBarDateTime.GetDate();
	
	// Handle daily sessions
	// Date computation is enough for determining start of period
	if ( currentBarDate == currentBarTradingStartDate )
	{
		int cbPeriod = 0, pbPeriod = 0;	// current and previous bar period (# of day/week/month...)

		switch (periodType)
		{
			case ECI_PERIOD_TYPE_DAILY: 	
				cbPeriod = currentBarDate; // # of days since December 30, 1899
				pbPeriod = previousBarDate;				
				break;
			case ECI_PERIOD_TYPE_WEEKLY: 	
				cbPeriod = currentBarDate / 7; // # of weeks since December 30, 1899
				pbPeriod = previousBarDate / 7 ;				
				break;
			case ECI_PERIOD_TYPE_MONTHLY: 	
				cbPeriod = currentBarDateTime.GetMonth(); // # of month in the year
				pbPeriod = previousBarDateTime.GetMonth();
				break;
			case ECI_PERIOD_TYPE_QUARTERLY: 
				cbPeriod = ((currentBarDateTime.GetMonth()-1) / 3) + 1; // # of quarter in the year,
				pbPeriod = ((previousBarDateTime.GetMonth()-1) / 3) + 1;
				break;
			case ECI_PERIOD_TYPE_YEARLY: 	
				cbPeriod = currentBarDateTime.GetYear(); // # of year
				pbPeriod = previousBarDateTime.GetYear();
				break;
			default:
				return; // should not be here.
		}
		startNewPeriod = (cbPeriod != pbPeriod);
	}
	else 
	{
		// Handle intraday using night sessions
		// We need the DateTime start period for determining start of period
		// and then compare it to the current and previous bars
		//
		SCDateTime 	newPeriodBarDateTime = 0;
		
		if ( periodType == ECI_PERIOD_TYPE_DAILY )
		{
			// new period is tomorrow start session.
			// except when market stopped more than 24h
			if ( currentBarDate - previousBarDate <= 1 )
				newPeriodBarDateTime = sc.GetStartDateTimeForTradingDate(currentBarDate+1);
			else												
				newPeriodBarDateTime = currentBarDateTime;
		}
		else if ( periodType == ECI_PERIOD_TYPE_WEEKLY )
		{
			// new period is start of week. 
			// Use GetDate that gives # of days since December 1899 to determine week number
			int currentBarWeekStartDate = (currentBarDate/7)*7;
			newPeriodBarDateTime = sc.GetStartDateTimeForTradingDate(currentBarWeekStartDate+1);
		}
		else if ( periodType == ECI_PERIOD_TYPE_MONTHLY )
		{
			// new period is tomorrow month start session
			int yyyy, mm, dd;
			DATE_TO_YMD(currentBarDate+1, yyyy, mm, dd);
			
			int monthStartDate = YMD_DATE(yyyy, mm, 1);
		
			newPeriodBarDateTime = sc.GetStartDateTimeForTradingDate(monthStartDate);
		}
		else if ( periodType == ECI_PERIOD_TYPE_QUARTERLY )
		{
			// new period is tomorrow quarter start session
			int yyyy, mm, dd;
			DATE_TO_YMD(currentBarDate+1, yyyy, mm, dd);
			
			int quarterStartDate = YMD_DATE(yyyy, (((mm-1)/3)*3)+1, 1);
		
			newPeriodBarDateTime = sc.GetStartDateTimeForTradingDate(quarterStartDate);
		}
		else if ( periodType == ECI_PERIOD_TYPE_YEARLY )
		{
			// new period is tomorrow year start session
			int yyyy, mm, dd;
			DATE_TO_YMD(currentBarDate+1, yyyy, mm, dd);
			
			int yearStartDate = YMD_DATE(yyyy, 1, 1);
		
			newPeriodBarDateTime = sc.GetStartDateTimeForTradingDate(yearStartDate);
		}
		else // should not be here
			return;

		startNewPeriod = ( currentBarDateTime >= newPeriodBarDateTime && previousBarDateTime < newPeriodBarDateTime );
	}
}

/* ==========================================================================
//
// ECIVwap study
//
============================================================================ */
SCSFExport scsf_ECIVwap(SCStudyGraphRef sc)
{
	SCString logMsg;

	//
	// subgraphs
	//
	SCSubgraphRef _vwap 	= sc.Subgraph[0];
	SCSubgraphRef _tb1 	= sc.Subgraph[1];
	SCSubgraphRef _bb1 	= sc.Subgraph[2];
	SCSubgraphRef _tb2 	= sc.Subgraph[3];
	SCSubgraphRef _bb2 	= sc.Subgraph[4];
	SCSubgraphRef _tb3 	= sc.Subgraph[5];
	SCSubgraphRef _bb3 	= sc.Subgraph[6];
	SCSubgraphRef _tb4 	= sc.Subgraph[7];
	SCSubgraphRef _bb4 	= sc.Subgraph[8];

	SCSubgraphRef _extendVwap 	= sc.Subgraph[9];
	SCSubgraphRef _extendTB1 = sc.Subgraph[10];
	SCSubgraphRef _extendBB1 = sc.Subgraph[11];
	SCSubgraphRef _extendTB2 = sc.Subgraph[12];
	SCSubgraphRef _extendBB2 = sc.Subgraph[13];
	SCSubgraphRef _extendTB3 = sc.Subgraph[14];
	SCSubgraphRef _extendBB3 = sc.Subgraph[15];
	SCSubgraphRef _extendTB4 = sc.Subgraph[16];
	SCSubgraphRef _extendBB4 = sc.Subgraph[17];

	//
	// input
	//
	SCInputRef _userPeriodType 	= sc.Input[0];
	SCInputRef _multiplier = sc.Input[1];
	
	SCInputRef _toExtendVwap 	= sc.Input[2];
	SCInputRef _toExtend1	= sc.Input[3];
	SCInputRef _toExtend2	= sc.Input[4];
	SCInputRef _toExtend3	= sc.Input[5];
	SCInputRef _toExtend4	= sc.Input[6];
	
	SCInputRef _setAllColors 		= sc.Input[7];
	SCInputRef _setAllColorsColor 	= sc.Input[8];

	SCInputRef _userInputOnly		= sc.Input[9];		
	
	//
	// Initialize configuration variables
	//
	if (sc.SetDefaults)
	{
		// General
		sc.GraphName 		= g_VwapName + g_StudyVersion;
		sc.StudyDescription = g_ECIVwapStudyDescription;
		sc.GraphRegion 		= 0;

		// subgraphs			
		_vwap.Name 			= g_VwapName;
		_vwap.DrawStyle 	= DRAWSTYLE_LINE;
		_vwap.PrimaryColor 	= ECIVWAP_VWAP_COLOR;

		_tb1.Name 			= "Top Band 1 of Vwap Standard Deviation";
		_bb1.Name 			= "Bottom Band 1 of Vwap Standard Deviation";
		_tb2.Name 			= "Top Band 2 of Vwap Standard Deviation";
		_bb2.Name 			= "Bottom Band 2 of Vwap Standard Deviation";
		_tb3.Name 			= "Top Band 3 of Vwap Standard Deviation";
		_bb3.Name 			= "Bottom Band 3 of Vwap Standard Deviation";
		_tb4.Name 			= "Top Band 4 of Vwap Standard Deviation";
		_bb4.Name 			= "Bottom Band 4 of Vwap Standard Deviation";
		
		_tb1.DrawStyle 		= _bb1.DrawStyle = DRAWSTYLE_LINE;
		_tb1.LineStyle 		= _bb1.LineStyle = LINESTYLE_DOT;
		_tb1.PrimaryColor 	= _bb1.PrimaryColor = ECIVWAP_LEVELS_COLOR;
		
		_tb2.DrawStyle 		= DRAWSTYLE_FILLTOP_TRANSPARENT;
		_bb2.DrawStyle		= DRAWSTYLE_FILLBOTTOM_TRANSPARENT;
		_tb2.PrimaryColor 	= _bb2.PrimaryColor = ECIVWAP_LEVELS_COLOR;
		
		_tb3.DrawStyle 		= _bb3.DrawStyle = DRAWSTYLE_LINE;
		_tb3.LineStyle 		= _bb3.LineStyle = LINESTYLE_DOT;
		_tb3.PrimaryColor 	= _bb3.PrimaryColor = ECIVWAP_LEVELS_COLOR;
		
		_tb4.DrawStyle 		= _bb4.DrawStyle = DRAWSTYLE_LINE;
		_tb4.PrimaryColor 	= _bb4.PrimaryColor = ECIVWAP_LEVELS_COLOR;
		
		_extendVwap.Name		= "Vwap extension";
		_extendVwap.DrawStyle	= DRAWSTYLE_DASH;
		_extendVwap.PrimaryColor= _vwap.PrimaryColor;	
		
		_extendTB1.Name			= "Top band 1 extension";
		_extendBB1.Name			= "Bottom band 1 extension";
		_extendTB2.Name			= "Top band 2 extension";
		_extendBB2.Name			= "Bottom band 2 extension";
		_extendTB3.Name			= "Top band 3 extension";
		_extendBB3.Name			= "Bottom band 3 extension";
		_extendTB4.Name			= "Top band 4 extension";
		_extendBB4.Name			= "Bottom band 4 extension";
		
		_extendTB1.DrawStyle	= _extendBB1.DrawStyle = DRAWSTYLE_DASH;
		_extendTB1.LineStyle	= _extendBB1.LineStyle = LINESTYLE_DOT;
		_extendTB1.PrimaryColor	= _extendBB1.PrimaryColor = ECIVWAP_LEVELS_COLOR;

		_extendTB2.DrawStyle 	= DRAWSTYLE_FILLRECTTOP_TRANSPARENT;
		_extendBB2.DrawStyle	= DRAWSTYLE_FILLRECTBOTTOM_TRANSPARENT;
		_extendTB2.PrimaryColor	= _extendBB2.PrimaryColor = ECIVWAP_LEVELS_COLOR;
		
		_extendTB3.DrawStyle	= _extendBB3.DrawStyle = DRAWSTYLE_DASH;
		_extendTB3.LineStyle	= _extendBB3.LineStyle = LINESTYLE_DOT;
		_extendTB3.PrimaryColor	= _extendBB3.PrimaryColor = ECIVWAP_LEVELS_COLOR;
		
		_extendTB4.DrawStyle	= _extendBB4.DrawStyle = DRAWSTYLE_DASH;
		_extendTB4.PrimaryColor	= _extendBB4.PrimaryColor = ECIVWAP_LEVELS_COLOR;
		
		// input
		_userPeriodType.Name	= "Vwap period type";
		_userPeriodType.SetDescription("Vwap period type");
		_userPeriodType.SetCustomInputStrings(ECI_PERIOD_INPUT_STRINGS);
		_userPeriodType.SetCustomInputIndex(1);

		_multiplier.Name 	= "Multiplier";
		_multiplier.SetDescription("Standard deviation multiplier");
		_multiplier.SetFloat(0.5);
		
		_toExtendVwap.Name	= "Extend vwap";
		_toExtendVwap.SetDescription("Extend vwap previous period");
		_toExtendVwap.SetYesNo(1);
		_toExtend1.Name		= "Extend stddev #1";
		_toExtend1.SetDescription("Extend standard deviation number 1");
		_toExtend1.SetYesNo(1);
		_toExtend2.Name		= "Extend stddev #2";
		_toExtend2.SetDescription("Extend standard deviation number 2");
		_toExtend2.SetYesNo(1);
		_toExtend3.Name		= "Extend stddev #3";
		_toExtend3.SetDescription("Extend standard deviation number 3");
		_toExtend3.SetYesNo(1);
		_toExtend4.Name		= "Extend stddev #4";
		_toExtend4.SetDescription("Extend standard deviation number 4");
		_toExtend4.SetYesNo(1);		
		
		_setAllColors.Name = "Set all colors";
		_setAllColors.SetDescription("Set all colors automatically");
		_setAllColors.SetYesNo(0);
		_setAllColorsColor.Name = "Set all colors color";
		_setAllColorsColor.SetDescription("Set all colors automatically color");
		_setAllColorsColor.SetColor(ECIVWAP_MAIN_COLOR);

		_userInputOnly.Name = "Based on input only";
		_userInputOnly.SetDescription("Computation based on input only (no volume)");
		_userInputOnly.SetYesNo(0);
		
		// misc
		sc.AutoLoop = 1;
		sc.FreeDLL = DEV_FREE_DLL;
		sc.MaintainVolumeAtPriceData = 1;  // needed for sc.VolumeAtPriceForBars
		sc.DrawStudyUnderneathMainPriceGraph = 1;
		sc.ScaleRangeType = SCALE_SAMEASREGION;

		return;
	}

	//
	// Do data processing
	//
	
	SCFloatArrayRef _barVwap 		= _vwap.Arrays[0]; 	// vwap based on all bar prices X volumes
	SCFloatArrayRef PeriodStddev 	= _vwap.Arrays[1];		// vwap standard deviation offset

	ECI_PeriodType&	_periodType 	= (ECI_PeriodType&)sc.GetPersistentInt(0);	// type of vwap period
	int& 			_periodStartIndex = sc.GetPersistentInt(1);	// start of vwap period
	
	//
	// initialize
	//
	if ( sc.Index == 0 )
	{
		_periodType 		= (ECI_PeriodType)_userPeriodType.GetInt();
		_periodStartIndex 	= 0;
		
		// auto coloring
		if ( _setAllColors.GetYesNo() == 1 )
		{
			int _color = _setAllColorsColor.GetColor();
			
			_vwap.PrimaryColor = _tb1.PrimaryColor = _bb1.PrimaryColor = _tb2.PrimaryColor = _bb2.PrimaryColor = _tb3.PrimaryColor = _bb3.PrimaryColor = _tb4.PrimaryColor = _bb4.PrimaryColor = _extendVwap.PrimaryColor = _extendTB1.PrimaryColor = _extendBB1.PrimaryColor	= _extendTB2.PrimaryColor = _extendBB2.PrimaryColor = _extendTB3.PrimaryColor = _extendBB3.PrimaryColor	= _extendTB4.PrimaryColor = _extendBB4.PrimaryColor = _color;
		}		
	}

	//
	// determine if a new vwap period starts
	//
	bool _startNewPeriod = false, _endNewPeriod = false;

	ECIVwap_ComputeNewPeriod(sc, _periodType, _startNewPeriod);
	if ( _startNewPeriod )
		_periodStartIndex 	= sc.Index;

	//
	// compute vwap. 
	// we start with each bar vwap that is needed on ALL bars.
	// then we compute the period vwap, the standard deviation and the extensions.
	//
	ECIVwap_ComputeBarVwap(sc, sc.Index, _userInputOnly.GetYesNo(), _barVwap);
	ECIVwap_ComputePeriodVwap(sc, _periodStartIndex, sc.Index, _barVwap, _userInputOnly.GetYesNo(), _vwap);
	ECIVwap_ComputeStddev(sc, _periodStartIndex, sc.Index, _vwap, _multiplier.GetFloat(), _userInputOnly.GetYesNo(),
							_tb1, _bb1, 
							_tb2, _bb2,
							_tb3, _bb3, 	
							_tb4, _bb4 );

							
	// extension...
	if ( sc.Index >= 1 )
	{
		if ( _startNewPeriod )
		{
			if ( _toExtendVwap.GetYesNo() )
				_extendVwap[sc.Index] = _vwap[sc.Index-1];
			if ( _toExtend1.GetYesNo() )
			{
				_extendTB1[sc.Index] = _tb1[sc.Index-1];
				_extendBB1[sc.Index] = _bb1[sc.Index-1];
			}
			if ( _toExtend2.GetYesNo() )
			{
				_extendTB2[sc.Index] = _tb2[sc.Index-1];
				_extendBB2[sc.Index] = _bb2[sc.Index-1];
			}
			if ( _toExtend3.GetYesNo() )
			{
				_extendTB3[sc.Index] = _tb3[sc.Index-1];
				_extendBB3[sc.Index] = _bb3[sc.Index-1];
			}
			if ( _toExtend4.GetYesNo() )
			{
				_extendTB4[sc.Index] = _tb4[sc.Index-1];
				_extendBB4[sc.Index] = _bb4[sc.Index-1];
			}
		}
		else
		{
			if ( _toExtendVwap.GetYesNo() )
				_extendVwap[sc.Index] = _extendVwap[sc.Index-1];
			if ( _toExtend1.GetYesNo() )
			{
				_extendTB1[sc.Index] = _extendTB1[sc.Index-1];
				_extendBB1[sc.Index] = _extendBB1[sc.Index-1];
			}
			if ( _toExtend2.GetYesNo() )
			{
				_extendTB2[sc.Index] = _extendTB2[sc.Index-1];
				_extendBB2[sc.Index] = _extendBB2[sc.Index-1];
			}
			if ( _toExtend3.GetYesNo() )
			{
				_extendTB3[sc.Index] = _extendTB3[sc.Index-1];
				_extendBB3[sc.Index] = _extendBB3[sc.Index-1];
			}
			if ( _toExtend4.GetYesNo() )
			{
				_extendTB4[sc.Index] = _extendTB4[sc.Index-1];
				_extendBB4[sc.Index] = _extendBB4[sc.Index-1];
			}
		}
	}


	//logMsg.Format("sc.Index=<%d> periodType=<%d>", sc.Index, periodType);
	//sc.AddMessageToLog(logMsg,0); 
}


/* ==========================================================================
//
// ECIVwapAnchor draw vwap and the standard deviation levels
//
// sc : sierra study context
// periodStartIndex : where vwap starts
// barIndex : bar index to compute, if needed
// inputOnly : if true, base calculation on main input. otherwise, use input+volume
// barVwap : vwap for each bar of period
// vwap : where vwap results are returned, if needed
// multiplier : multiplier of standard deviation levels
// tb1-tb4 : where results are returned  if needed : top of band number 1..2..3..4
// bb1-bb4 : where results are returned  if needed : bottom of band number 1..2..3..4
// userEndDateType : type of end date chosen by user
// userEndDateTime : date time of end, if needed
// periodEndIndex : where end bar index is returned, if needed and found
//
============================================================================ */
void ECIVwapAnchor_DrawVwap(const SCStudyGraphRef sc, const int periodStartIndex, const int barIndex, const bool inputOnly, SCFloatArrayRef barVwap, SCSubgraphRef vwap, const float multiplier,
							SCSubgraphRef tb1, SCSubgraphRef bb1, SCSubgraphRef tb2, SCSubgraphRef bb2,
							SCSubgraphRef tb3, SCSubgraphRef bb3, SCSubgraphRef tb4, SCSubgraphRef bb4,
							const ECI_EndDateType userEndDateType, const SCDateTime userEndDateTime, int& periodEndIndex)
{
	SCString logMsg;
	
	if ( barIndex >= periodStartIndex )
	{
		switch ( userEndDateType )
		{
			case ECI_ENDDATETYPE_CONTINUOUS:
				// no end date. draw from periodStartIndex to end of chart
				ECIVwap_ComputeBarVwap(sc, barIndex, inputOnly, barVwap);
				ECIVwap_ComputePeriodVwap(sc, periodStartIndex, barIndex, barVwap, inputOnly, vwap);
				ECIVwap_ComputeStddev(sc, periodStartIndex, barIndex, vwap, multiplier, inputOnly,
										tb1, bb1, 
										tb2, bb2,
										tb3, bb3, 	
										tb4, bb4 );
				break;
				
			case ECI_ENDDATETYPE_STOP_ON_ENDDATE:
				// user end date. draw from periodStartIndex to end date.	
				{
					SCDateTime currentBarDateTime = sc.BaseDateTimeIn[barIndex];
					SCDateTime previousBarDateTime = (barIndex > 0) ? sc.BaseDateTimeIn[barIndex-1] : currentBarDateTime;

					if ( currentBarDateTime < userEndDateTime )
					{
						ECIVwap_ComputeBarVwap(sc, barIndex, inputOnly, barVwap);
						ECIVwap_ComputePeriodVwap(sc, periodStartIndex, barIndex, barVwap, inputOnly, vwap);
						ECIVwap_ComputeStddev(sc, periodStartIndex, barIndex, vwap, multiplier, inputOnly,
												tb1, bb1, 
												tb2, bb2,
												tb3, bb3, 	
												tb4, bb4 );
					}
					else if ( currentBarDateTime > userEndDateTime && previousBarDateTime <= userEndDateTime )
					{
						periodEndIndex = barIndex-1;
					}
				}
				break;
				
			case ECI_ENDDATETYPE_STOP_ON_HIGHERHIGH:
				// end date on most recent HH. draw from periodStartIndex to HH
				{
					// look for most recent HH
					int hhBarIndex = periodStartIndex;
					for (int i = periodStartIndex; i<= barIndex; i++)
						if ( sc.High[i] > sc.High[hhBarIndex] )
							hhBarIndex = i;	
					
					// bar vwap is needed on all bars after start index
					ECIVwap_ComputeBarVwap(sc, barIndex, inputOnly, barVwap);
					
					// continue drawing if we make new highs
					if ( hhBarIndex == barIndex )
					{
						// draw from previous HH to current HH
						int phhBarIndex = periodStartIndex;
						for (int i = periodStartIndex; i<= max(periodStartIndex,hhBarIndex-1); i++)
							if ( sc.High[i] > sc.High[phhBarIndex] )
								phhBarIndex = i;	

						for ( int i = phhBarIndex; i <= barIndex  ; i++ )
						{
							ECIVwap_ComputePeriodVwap(sc, periodStartIndex, i, barVwap, inputOnly, vwap);
							ECIVwap_ComputeStddev(sc, periodStartIndex, i, vwap, multiplier, inputOnly,
													tb1, bb1, 
													tb2, bb2,
													tb3, bb3, 	
													tb4, bb4 );
						}
					}
					// set end period bar for extension
					else if ( hhBarIndex == barIndex - 1 )
						periodEndIndex = barIndex - 1;
				}
				break;

			case ECI_ENDDATETYPE_STOP_ON_LOWERLOW:
				// end date on most recent LL. draw from periodStartIndex to LL
				{
					// look for most recent LL
					int llBarIndex = periodStartIndex;
					for (int i = periodStartIndex; i<= barIndex; i++)
						if ( sc.Low[i] < sc.Low[llBarIndex] )
							llBarIndex = i;	
					
					// bar vwap is needed on all bars after start index
					ECIVwap_ComputeBarVwap(sc, barIndex, inputOnly, barVwap);
					
					// continue drawing if we make new highs
					if ( llBarIndex == barIndex )
					{
						// draw from previous LL to current LL
						int pllBarIndex = periodStartIndex;
						for (int i = periodStartIndex; i<= max(periodStartIndex,llBarIndex-1); i++)
							if ( sc.Low[i] < sc.Low[pllBarIndex] )
								pllBarIndex = i;	

						for ( int i = pllBarIndex; i <= barIndex  ; i++ )
						{
							ECIVwap_ComputePeriodVwap(sc, periodStartIndex, i, barVwap, inputOnly, vwap);
							ECIVwap_ComputeStddev(sc, periodStartIndex, i, vwap, multiplier, inputOnly,
													tb1, bb1, 
													tb2, bb2,
													tb3, bb3, 	
													tb4, bb4 );
						}
					}
					// set end period bar for extension
					else if ( llBarIndex == barIndex - 1 )
						periodEndIndex = barIndex - 1;
				}
				break;

			case ECI_ENDDATETYPE_STOP_ON_LASTCLOSEDBAR:
				// end date on last closed bar. draw from periodStartIndex to end date.
				periodEndIndex = max(periodStartIndex, barIndex-1);
				
				ECIVwap_ComputeBarVwap(sc, periodEndIndex, inputOnly, barVwap);
				ECIVwap_ComputePeriodVwap(sc, periodStartIndex, periodEndIndex, barVwap, inputOnly, vwap);
				ECIVwap_ComputeStddev(sc, periodStartIndex, periodEndIndex, vwap, multiplier, inputOnly,
										tb1, bb1, 
										tb2, bb2,
										tb3, bb3, 	
										tb4, bb4 );
				break;
								
			case ECI_ENDDATETYPE_STOP_ON_STARTBAR:
				// end date on start bar. draw from periodStartIndex to end date.
				
				if ( barIndex == periodStartIndex )
				{
					ECIVwap_ComputeBarVwap(sc, barIndex, inputOnly, barVwap);
					ECIVwap_ComputePeriodVwap(sc, periodStartIndex, barIndex, barVwap, inputOnly, vwap);
					ECIVwap_ComputeStddev(sc, periodStartIndex, barIndex, vwap, multiplier, inputOnly,
											tb1, bb1, 
											tb2, bb2,
											tb3, bb3, 	
											tb4, bb4 );

					periodEndIndex = barIndex;					
				}
				break;
				
			default: // should not get here
				return;	
		}
	}
}

/* ==========================================================================
//
// ECIVwapAnchor draw vwap extensions
//
// sc : sierra study context
// periodStartIndex : where vwap starts
// barIndex : bar index to compute, if needed
// barVwap : vwap for each bar of period
// vwap : where vwap results are returned, if needed
// multiplier : multiplier of standard deviation levels
// tb1-tb4 : where results are returned  if needed : top of band number 1..2..3..4
// bb1-bb4 : where results are returned  if needed : bottom of band number 1..2..3..4
// userEndDateType : type of end date chosen by user
// userEndDateTime : date time of end, if needed
// periodEndIndex : where end bar index is returned, if needed and found
//
============================================================================ */
void ECIVwapAnchor_DrawVwapExtensions(const SCStudyGraphRef sc, const int periodStartIndex, const int barIndex, const SCSubgraphRef vwap,
									const SCInputRef toExtendVwap, 
									const SCInputRef toExtend1, const SCInputRef toExtend2, const SCInputRef toExtend3, const SCInputRef toExtend4,
									const SCSubgraphRef tb1, const SCSubgraphRef bb1, const SCSubgraphRef tb2, const SCSubgraphRef bb2,
									const SCSubgraphRef tb3, const SCSubgraphRef bb3, const SCSubgraphRef tb4, const SCSubgraphRef bb4,
									SCSubgraphRef extendVwap,
									SCSubgraphRef extendTB1, SCSubgraphRef extendBB1, SCSubgraphRef extendTB2, SCSubgraphRef extendBB2,
									SCSubgraphRef extendTB3, SCSubgraphRef extendBB3, SCSubgraphRef extendTB4, SCSubgraphRef extendBB4,
									const ECI_EndDateType endDateType, const int periodEndIndex)
{
	if ( barIndex > periodEndIndex )
	{
		switch ( endDateType )
		{
			case ECI_ENDDATETYPE_STOP_ON_ENDDATE:
			case ECI_ENDDATETYPE_STOP_ON_HIGHERHIGH:
			case ECI_ENDDATETYPE_STOP_ON_LOWERLOW:
			case ECI_ENDDATETYPE_STOP_ON_LASTCLOSEDBAR:
			case ECI_ENDDATETYPE_STOP_ON_STARTBAR:
				if ( periodEndIndex == barIndex-1 )
				{
					if ( toExtendVwap.GetYesNo() )
						extendVwap[barIndex] = extendVwap[barIndex-1] = vwap[barIndex-1];
					if ( toExtend1.GetYesNo()  )
					{
						extendTB1[barIndex] = extendTB1[barIndex-1] = tb1[barIndex-1];
						extendBB1[barIndex] = extendBB1[barIndex-1] = bb1[barIndex-1];
					}
					if ( toExtend2.GetYesNo() )
					{
						extendTB2[barIndex] = extendTB2[barIndex-1] = tb2[barIndex-1];
						extendBB2[barIndex] = extendBB2[barIndex-1] = bb2[barIndex-1];
					}
					if ( toExtend3.GetYesNo() )
					{
						extendTB3[barIndex] = extendTB3[barIndex-1] = tb3[barIndex-1];
						extendBB3[barIndex] = extendBB3[barIndex-1] = bb3[barIndex-1];
					}
					if ( toExtend4.GetYesNo() )
					{
						extendTB4[barIndex] = extendTB4[barIndex-1] = tb4[barIndex-1];
						extendBB4[barIndex] = extendBB4[barIndex-1] = bb4[barIndex-1];
					}
				}
				else
				{
					if ( toExtendVwap.GetYesNo() )
						extendVwap[barIndex] 	= extendVwap[barIndex-1];
					if ( toExtend1.GetYesNo() )
					{
						extendTB1[barIndex] 	= extendTB1[barIndex-1];
						extendBB1[barIndex] 	= extendBB1[barIndex-1];
					}
					if ( toExtend2.GetYesNo() )
					{
						extendTB2[barIndex] 	= extendTB2[barIndex-1];
						extendBB2[barIndex] 	= extendBB2[barIndex-1];
					}
					if ( toExtend3.GetYesNo() )
					{
						extendTB3[barIndex] 	= extendTB3[barIndex-1];
						extendBB3[barIndex] 	= extendBB3[barIndex-1];
					}
					if ( toExtend4.GetYesNo() )
					{
						extendTB4[barIndex] 	= extendTB4[barIndex-1];
						extendBB4[barIndex] 	= extendBB4[barIndex-1];
					}
				}
				break;
				
			default:
				break;
		}
	}
}

/* ==========================================================================
//
// ECIVwapAnchor study
// 
============================================================================ */
SCSFExport scsf_ECIVwapAnchor(SCStudyGraphRef sc)
{
	SCString logMsg;

	//
	// subgraphs
	//
	SCSubgraphRef _vwap = sc.Subgraph[0];
	SCSubgraphRef _tb1 	= sc.Subgraph[1];
	SCSubgraphRef _bb1 	= sc.Subgraph[2];
	SCSubgraphRef _tb2 	= sc.Subgraph[3];
	SCSubgraphRef _bb2 	= sc.Subgraph[4];
	SCSubgraphRef _tb3 	= sc.Subgraph[5];
	SCSubgraphRef _bb3 	= sc.Subgraph[6];
	SCSubgraphRef _tb4 	= sc.Subgraph[7];
	SCSubgraphRef _bb4 	= sc.Subgraph[8];

	SCSubgraphRef _extendVwap 	= sc.Subgraph[9];
	SCSubgraphRef _extendTB1 = sc.Subgraph[10];
	SCSubgraphRef _extendBB1 = sc.Subgraph[11];
	SCSubgraphRef _extendTB2 = sc.Subgraph[12];
	SCSubgraphRef _extendBB2 = sc.Subgraph[13];
	SCSubgraphRef _extendTB3 = sc.Subgraph[14];
	SCSubgraphRef _extendBB3 = sc.Subgraph[15];
	SCSubgraphRef _extendTB4 = sc.Subgraph[16];
	SCSubgraphRef _extendBB4 = sc.Subgraph[17];

	//
	// input
	//
	SCInputRef _multiplier 	= sc.Input[0];
	
	SCInputRef _toExtendVwap= sc.Input[1];
	SCInputRef _toExtend1	= sc.Input[2];
	SCInputRef _toExtend2	= sc.Input[3];
	SCInputRef _toExtend3	= sc.Input[4];
	SCInputRef _toExtend4	= sc.Input[5];
	
	SCInputRef _userStartDateType 	= sc.Input[6];
	SCInputRef _userEndDateType  	= sc.Input[7];
	SCInputRef _userEndDate 		= sc.Input[8];
	
	SCInputRef _setAllColors 		= sc.Input[9];
	SCInputRef _setAllColorsColor 	= sc.Input[10];

	SCInputRef _userInputOnly		= sc.Input[11];

	SCInputRef _hiddenStartIndex 	= sc.Input[12]; // just for saving
	
	//
	// Initialize configuration variables
	//
	int& 				_periodStartIndex = sc.GetPersistentInt(0);	// start bar index of vwap 
	ECI_StartDateType& 	_startDateType	  = (ECI_StartDateType&)sc.GetPersistentInt(1); // start date tyype
	int& 				_periodEndIndex   = sc.GetPersistentInt(2);	// end bar index of vwap 
	ECI_EndDateType& 	_endDateType	  = (ECI_EndDateType&)sc.GetPersistentInt(3); // vwap period type

	int& 				_menuID = sc.GetPersistentInt(4);
	int&				_lastBracketIndex = sc.GetPersistentInt(5);
		
	float&				_higherHigh		= sc.GetPersistentFloat(1);
	float&				_lowerLow		= sc.GetPersistentFloat(2);

	if (sc.SetDefaults)
	{		
		// General
		sc.GraphName 		= g_VwapAnchorName + g_StudyVersion;
		sc.StudyDescription = g_ECIVwapAnchorStudyDescription;
		sc.GraphRegion 		= 0;

		// subgraphs			
		_vwap.Name 			= g_VwapAnchorName;
		_vwap.DrawStyle 	= DRAWSTYLE_LINE;
		_vwap.PrimaryColor 	= RGB(128,0,128);

		_tb1.Name 			= "Top Band 1 of Vwap Standard Deviation";
		_tb1.DrawStyle 		= DRAWSTYLE_LINE;
		_tb1.LineStyle		= LINESTYLE_DOT;
		_tb1.PrimaryColor 	= ECIVWAP_MAIN_COLOR;
		_bb1.Name 			= "Bottom Band 1 of Vwap Standard Deviation";
		_bb1.DrawStyle 		= DRAWSTYLE_LINE;
		_bb1.LineStyle		= LINESTYLE_DOT;
		_bb1.PrimaryColor 	= ECIVWAP_MAIN_COLOR;
		_tb2.Name 			= "Top Band 2 of Vwap Standard Deviation";
		_tb2.DrawStyle 		= DRAWSTYLE_FILLTOP_TRANSPARENT;
		_tb2.PrimaryColor 	= ECIVWAP_MAIN_COLOR;
		_bb2.Name 			= "Bottom Band 2 of Vwap Standard Deviation";
		_bb2.DrawStyle 		= DRAWSTYLE_FILLBOTTOM_TRANSPARENT;
		_bb2.PrimaryColor 	= ECIVWAP_MAIN_COLOR;
		_tb3.Name 			= "Top Band 3 of Vwap Standard Deviation";
		_tb3.DrawStyle 		= DRAWSTYLE_LINE;
		_tb3.LineStyle		= LINESTYLE_DOT;
		_tb3.PrimaryColor 	= ECIVWAP_MAIN_COLOR;
		_bb3.Name 			= "Bottom Band 3 of Vwap Standard Deviation";
		_bb3.DrawStyle 		= DRAWSTYLE_LINE;
		_bb3.LineStyle		= LINESTYLE_DOT;
		_bb3.PrimaryColor 	= ECIVWAP_MAIN_COLOR;
		_tb4.Name 			= "Top Band 4 of Vwap Standard Deviation";
		_tb4.DrawStyle 		= DRAWSTYLE_LINE;
		_tb4.PrimaryColor 	= ECIVWAP_MAIN_COLOR;
		_bb4.Name 			= "Bottom Band 4 of Vwap Standard Deviation";
		_bb4.DrawStyle 		= DRAWSTYLE_LINE;
		_bb4.PrimaryColor 	= ECIVWAP_MAIN_COLOR;
		
		_extendVwap.Name		= "Vwap extension";
		_extendVwap.DrawStyle	= DRAWSTYLE_LINE;
		_extendVwap.LineStyle	= LINESTYLE_DASH;
		_extendVwap.PrimaryColor= _vwap.PrimaryColor;	
		_extendTB1.Name			= "Top band 1 extension";
		_extendTB1.DrawStyle	= _tb1.DrawStyle;
		_extendTB1.LineStyle	= _tb1.LineStyle;
		_extendTB1.PrimaryColor	= _tb1.PrimaryColor;	
		_extendBB1.Name			= "Bottom band 1 extension";
		_extendBB1.DrawStyle	= _bb1.DrawStyle;
		_extendBB1.LineStyle	= _bb1.LineStyle;
		_extendBB1.PrimaryColor	= _bb1.PrimaryColor;	
		_extendTB2.Name			= "Top band 2 extension";
		_extendTB2.DrawStyle	= _tb2.DrawStyle;
		_extendTB2.LineStyle	= _tb2.LineStyle;
		_extendTB2.PrimaryColor	= _tb2.PrimaryColor;
		_extendBB2.Name			= "Bottom band 2 extension";
		_extendBB2.DrawStyle	= _bb2.DrawStyle;
		_extendBB2.LineStyle	= _bb2.LineStyle;
		_extendBB2.PrimaryColor	= _bb2.PrimaryColor;		
		_extendTB3.Name			= "Top band 3 extension";
		_extendTB3.DrawStyle	= _tb3.DrawStyle;
		_extendTB3.LineStyle	= _tb3.LineStyle;
		_extendTB3.PrimaryColor	= _tb3.PrimaryColor;
		_extendBB3.Name			= "Bottom band 3 extension";
		_extendBB3.DrawStyle	= _bb3.DrawStyle;
		_extendBB3.LineStyle	= _bb3.LineStyle;
		_extendBB3.PrimaryColor	= _bb3.PrimaryColor;			
		_extendTB4.Name			= "Top band 4 extension";
		_extendTB4.DrawStyle	= _tb4.DrawStyle;
		_extendTB4.LineStyle	= _tb4.LineStyle;
		_extendTB4.PrimaryColor	= _tb4.PrimaryColor;		
		_extendBB4.Name			= "Bottom band 4 extension";
		_extendBB4.DrawStyle	= _bb4.DrawStyle;
		_extendBB4.LineStyle	= _bb4.LineStyle;
		_extendBB4.PrimaryColor	= _bb4.PrimaryColor;
		
		// input
		_multiplier.Name 	= "Multiplier";
		_multiplier.SetDescription("Standard deviation multiplier");
		_multiplier.SetFloat(0.5f);
		
		_toExtendVwap.Name	= "Extend vwap";
		_toExtendVwap.SetDescription("Extend vwap previous period");
		_toExtendVwap.SetYesNo(1);
		_toExtend1.Name		= "Extend stddev #1";
		_toExtend1.SetDescription("Extend standard deviation number 1");
		_toExtend1.SetYesNo(1);
		_toExtend2.Name		= "Extend stddev #2";
		_toExtend2.SetDescription("Extend standard deviation number 2");
		_toExtend2.SetYesNo(1);
		_toExtend3.Name		= "Extend stddev #3";
		_toExtend3.SetDescription("Extend standard deviation number 3");
		_toExtend3.SetYesNo(1);
		_toExtend4.Name		= "Extend stddev #4";
		_toExtend4.SetDescription("Extend standard deviation number 4");
		_toExtend4.SetYesNo(1);
		
		_userStartDateType.Name = "Start type";
		_userStartDateType.SetDescription("Start date type");
		_userStartDateType.SetCustomInputStrings(ECI_STARTDATETYPE_STRINGS);
		_userStartDateType.SetCustomInputIndex(0);
		_userEndDateType.Name = "End type";
		_userEndDateType.SetDescription("End date type");
		_userEndDateType.SetCustomInputStrings(ECI_ENDDATETYPE_STRINGS);
		_userEndDateType.SetCustomInputIndex(0);
		_userEndDate.Name	= "End date";
		_userEndDate.SetDescription("End date, if end type is stop on end date chosen");
		_userEndDate.SetDateTime(0);

		_setAllColors.Name = "Set all colors";
		_setAllColors.SetDescription("Set all colors automatically");
		_setAllColors.SetYesNo(0);
		_setAllColorsColor.Name = "Set all colors color";
		_setAllColorsColor.SetDescription("Set all colors automatically color");
		_setAllColorsColor.SetColor(ECIVWAP_MAIN_COLOR);
		
		_userInputOnly.Name = "Based on input only";
		_userInputOnly.SetDescription("Computation based on input only (no volume)");
		_userInputOnly.SetYesNo(0);
		
		//XXHiddenStartIndex.Name = "Hidden start index"; // used to store start index
		_hiddenStartIndex.SetInt(INT_MAX);
		
		// misc
		sc.AutoLoop = 1;
		sc.FreeDLL = DEV_FREE_DLL;
		sc.MaintainVolumeAtPriceData = 1;  // needed for sc.VolumeAtPriceForBars
		sc.DrawStudyUnderneathMainPriceGraph = 1;
		sc.ScaleRangeType = SCALE_SAMEASREGION;

		//MenuID = 0;

		return;
	}

	//
	// Do data processing
	//
	SCFloatArrayRef _barVwap 		= _vwap.Arrays[0]; 	// bar vwap, based on all volume per price in the bar
	SCFloatArrayRef _stddevOffset 	= _vwap.Arrays[1];		// vwap standard deviation offset

	//
	// initilize
	//
	if ( sc.Index == 0 )
	{
		_startDateType = (ECI_StartDateType)_userStartDateType.GetInt();

		// set period start, if available
		sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, _menuID);
		switch ( _startDateType )
		{
			case ECI_STARTDATETYPE_MANUAL:
				{
					// add chart shortcut menu item
					SCString _menuName;
					_menuName.Format("Anchor Vwap <%d>", sc.StudyGraphInstanceID);
					//if (_menuID <= 0) // when duplicating chart _menuID is not at 0
						_menuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, _menuName);
					if (_menuID < 0)
						sc.AddMessageToLog("Failed adding Menu Item", 1);

					_periodStartIndex = _hiddenStartIndex.GetInt();
				}
				break;
				
/*			WORK IN PROGRESS ...

			case ECI_STARTDATETYPE_LASTBRACKET:
				_periodStartIndex = 0;
				break;
*/				

			default:
				_periodStartIndex = INT_MAX;
				break;
		}
		
		_higherHigh = 0.f;
		_lowerLow = FLT_MAX;
		
		// set end period, if available
		_endDateType = (ECI_EndDateType)_userEndDateType.GetInt();
		_periodEndIndex = INT_MIN;
		
		// auto coloring
		if ( _setAllColors.GetYesNo() == 1 )
		{
			int _color = _setAllColorsColor.GetColor();
			
			_vwap.PrimaryColor = _tb1.PrimaryColor = _bb1.PrimaryColor = _tb2.PrimaryColor = _bb2.PrimaryColor = _tb3.PrimaryColor = _bb3.PrimaryColor = _tb4.PrimaryColor = _bb4.PrimaryColor = _extendVwap.PrimaryColor = _extendTB1.PrimaryColor = _extendBB1.PrimaryColor	= _extendTB2.PrimaryColor = _extendBB2.PrimaryColor = _extendTB3.PrimaryColor = _extendBB3.PrimaryColor	= _extendTB4.PrimaryColor = _extendBB4.PrimaryColor = _color;
		}
	}
	
	//
	// Update start period if needed
	//
	bool _needNewStart = false;
	switch ( _startDateType )
	{
		case ECI_STARTDATETYPE_MANUAL:
			if (sc.MenuEventID != 0 && sc.MenuEventID == _menuID)
			{
				_needNewStart = true;

				_periodStartIndex = sc.ActiveToolIndex;			
				_hiddenStartIndex.SetInt(_periodStartIndex);
				
				_periodEndIndex = INT_MIN;
			}
			if (sc.LastCallToFunction)
			{
				// be sure to remove the menu command when study is removed
				sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, _menuID);
				return;
			}
			break;
			
		case ECI_STARTDATETYPE_HIGHERHIGH:
			if ( sc.High[sc.Index] > _higherHigh && _periodStartIndex != sc.Index )
			{
				_needNewStart = true;
				_periodStartIndex = sc.Index;

				_higherHigh = sc.High[sc.Index];
			}			
			break;

		case ECI_STARTDATETYPE_LOWERLOW:
			if ( sc.Low[sc.Index] < _lowerLow && _periodStartIndex != sc.Index )
			{
				_needNewStart = true;
				_periodStartIndex = sc.Index;

				_lowerLow = sc.Low[sc.Index];
			}			
			break;
		
		case ECI_STARTDATETYPE_LASTCLOSEDBAR:
			if ( _periodStartIndex != sc.Index-1 )
			{
				_needNewStart = true;
				_periodStartIndex = max(0, sc.Index-1);
			}
			break;
			
/*		TODO : WORK IN PROGRESS...

		case ECI_STARTDATETYPE_LASTBRACKET:
			{
				ECIVwap_ComputeBarVwap(sc, sc.Index, _userInputOnly.GetYesNo(), _barVwap);		
				float _lastPrice = sc.Close[max(sc.Index-1,0)];
				if ( _lastPrice <= _tb4[_periodStartIndex] && _lastPrice >= _bb4[_periodStartIndex] )
				{
					// nothing...
					logMsg.Format("sc.Index=<%d> _periodStartIndex=<%d>", sc.Index, _periodStartIndex);
					sc.AddMessageToLog(logMsg,0); 					
				}
				else
				{
					//_needNewStart = true;
					_periodStartIndex = 0;
					for (int _i=sc.Index-1 ; _i >= 0 ; _i-- )
					{
						if ( _lastPrice <= _tb2[_i] && _lastPrice >= _bb2[_i] )
						{
							//_needNewStart = true;
							_periodStartIndex = _i;
							break;
						}
					}
				}
			}
			break;
*/			
			
		default: // should not be here
			return;
	}

	// erase all previous vwap/stddev/extensions values if new period set
	if ( _needNewStart )
	{
		for (int _i = 0 ; _i <= sc.Index; _i++)
		{
			_vwap[_i] = _tb1[_i] = _bb1[_i] = _tb2[_i] = _bb2[_i] = _tb3[_i] = _bb3[_i] = _tb4[_i] = _bb4[_i] = 0.f;
			_extendVwap[_i] = _extendTB1[_i] = _extendBB1[_i] = _extendTB2[_i] = _extendBB2[_i] = _extendTB3[_i] = _extendBB3[_i] = _extendTB4[_i] = _extendBB4[_i] = 0.f;
		}
	}
	
	//
	// draw Vwap and extensions
	//
	int _startIndex = _needNewStart ? 0 : sc.Index;
	for (int _i = _startIndex; _i <= sc.Index; _i++)
	{
		ECIVwapAnchor_DrawVwap(sc, _periodStartIndex, _i, _userInputOnly.GetYesNo(), _barVwap, _vwap, _multiplier.GetFloat(),
								_tb1, _bb1, _tb2, _bb2, _tb3, _bb3, _tb4, _bb4,
								_endDateType, _userEndDate.GetDateTime(), _periodEndIndex);
		ECIVwapAnchor_DrawVwapExtensions(sc, _periodStartIndex, _i, _vwap,
										_toExtendVwap, 
										_toExtend1, _toExtend2, _toExtend3, _toExtend4,
										_tb1, _bb1, _tb2, _bb2, _tb3, _bb3, _tb4, _bb4,
										_extendVwap,_extendTB1, _extendBB1, _extendTB2, _extendBB2, _extendTB3, _extendBB3, _extendTB4, _extendBB4,
										_endDateType, _periodEndIndex);
	
	}
	//logMsg.Format("sc.Index=<%d> periodType=<%d>", sc.Index, periodType);
	//sc.AddMessageToLog(logMsg,0); 
}


/* ==========================================================================
//
// ECIVwapBracket study
// 
============================================================================ */
SCSFExport scsf_ECIVwapBracket(SCStudyGraphRef sc)
{
	SCString logMsg;

	//
	// subgraphs
	//
	SCSubgraphRef _vwap = sc.Subgraph[0];
	SCSubgraphRef _tb1 	= sc.Subgraph[1];
	SCSubgraphRef _bb1 	= sc.Subgraph[2];
	SCSubgraphRef _tb2 	= sc.Subgraph[3];
	SCSubgraphRef _bb2 	= sc.Subgraph[4];
	SCSubgraphRef _tb3 	= sc.Subgraph[5];
	SCSubgraphRef _bb3 	= sc.Subgraph[6];
	SCSubgraphRef _tb4 	= sc.Subgraph[7];
	SCSubgraphRef _bb4 	= sc.Subgraph[8];

	//
	// input
	//
	SCInputRef _multiplier 	= sc.Input[0];
	
	SCInputRef _toExtendVwap= sc.Input[1];
	SCInputRef _toExtend1	= sc.Input[2];
	SCInputRef _toExtend2	= sc.Input[3];
	SCInputRef _toExtend3	= sc.Input[4];
	SCInputRef _toExtend4	= sc.Input[5];
		
	SCInputRef _setAllColors 		= sc.Input[9];
	SCInputRef _setAllColorsColor 	= sc.Input[10];

	SCInputRef _userInputOnly		= sc.Input[11];

	SCInputRef _hiddenStartIndex 	= sc.Input[12]; // just for saving
		
	//
	// Initialize configuration variables
	//
	int& 				_periodStartIndex = sc.GetPersistentInt(0);	// start bar index of vwap 
		
	if (sc.SetDefaults)
	{		
		// General
		sc.GraphName 		= g_VwapBracketName + g_StudyVersion;
		sc.StudyDescription = g_ECIVwapBracketStudyDescription;
		sc.GraphRegion 		= 0;

		// subgraphs			
		_vwap.Name 			= g_VwapBracketName;
		_vwap.DrawStyle 	= DRAWSTYLE_DASH;
		_vwap.PrimaryColor 	= RGB(128,0,128);

		_tb1.Name 			= "Top Band 1 of Vwap Standard Deviation";
		_bb1.Name 			= "Bottom Band 1 of Vwap Standard Deviation";
		_tb1.DrawStyle 		= _bb1.DrawStyle = DRAWSTYLE_DASH;
		_tb1.LineStyle		= _bb1.LineStyle = LINESTYLE_DOT;
		_tb1.PrimaryColor 	= _bb1.PrimaryColor = ECIVWAP_MAIN_COLOR;

		_tb2.Name 			= "Top Band 2 of Vwap Standard Deviation";
		_bb2.Name 			= "Bottom Band 2 of Vwap Standard Deviation";
		_tb2.DrawStyle 		= DRAWSTYLE_FILLRECTTOP_TRANSPARENT;
		_bb2.DrawStyle 		= DRAWSTYLE_FILLRECTBOTTOM_TRANSPARENT;
		_tb2.PrimaryColor 	= _bb2.PrimaryColor = ECIVWAP_MAIN_COLOR;
		
		_tb3.Name 			= "Top Band 3 of Vwap Standard Deviation";
		_bb3.Name 			= "Bottom Band 3 of Vwap Standard Deviation";
		_tb3.DrawStyle 		= _bb3.DrawStyle = DRAWSTYLE_DASH;
		_tb3.LineStyle		= _bb3.LineStyle = LINESTYLE_DOT;
		_tb3.PrimaryColor 	= _bb3.PrimaryColor = ECIVWAP_MAIN_COLOR;

		_tb4.Name 			= "Top Band 4 of Vwap Standard Deviation";
		_bb4.Name 			= "Bottom Band 4 of Vwap Standard Deviation";
		_tb4.DrawStyle 		= _bb4.DrawStyle = DRAWSTYLE_DASH;
		_tb4.PrimaryColor 	= _bb4.PrimaryColor = ECIVWAP_MAIN_COLOR;
		
		// input
		_multiplier.Name 	= "Multiplier";
		_multiplier.SetDescription("Standard deviation multiplier");
		_multiplier.SetFloat(0.5f);
		
		_toExtendVwap.Name	= "Extend vwap";
		_toExtendVwap.SetDescription("Extend vwap previous period");
		_toExtendVwap.SetYesNo(1);
		_toExtend1.Name		= "Extend stddev #1";
		_toExtend1.SetDescription("Extend standard deviation number 1");
		_toExtend1.SetYesNo(1);
		_toExtend2.Name		= "Extend stddev #2";
		_toExtend2.SetDescription("Extend standard deviation number 2");
		_toExtend2.SetYesNo(1);
		_toExtend3.Name		= "Extend stddev #3";
		_toExtend3.SetDescription("Extend standard deviation number 3");
		_toExtend3.SetYesNo(1);
		_toExtend4.Name		= "Extend stddev #4";
		_toExtend4.SetDescription("Extend standard deviation number 4");
		_toExtend4.SetYesNo(1);
		
		_setAllColors.Name = "Set all colors";
		_setAllColors.SetDescription("Set all colors automatically");
		_setAllColors.SetYesNo(0);
		_setAllColorsColor.Name = "Set all colors color";
		_setAllColorsColor.SetDescription("Set all colors automatically color");
		_setAllColorsColor.SetColor(ECIVWAP_MAIN_COLOR);
		
		_userInputOnly.Name = "Based on input only";
		_userInputOnly.SetDescription("Computation based on input only (no volume)");
		_userInputOnly.SetYesNo(0);
		
		//XXHiddenStartIndex.Name = "Hidden start index"; // used to store start index
		_hiddenStartIndex.SetInt(INT_MAX);
		
		// misc
		sc.AutoLoop = 1;
		sc.FreeDLL = DEV_FREE_DLL;
		sc.MaintainVolumeAtPriceData = 1;  // needed for sc.VolumeAtPriceForBars
		sc.DrawStudyUnderneathMainPriceGraph = 1;
		sc.ScaleRangeType = SCALE_SAMEASREGION;

		return;
	}

	//
	// Do data processing
	//
	SCFloatArrayRef _hVwap 			= _vwap.Arrays[0]; 	// vwap of each bar
	SCFloatArrayRef _stddevOffset 	= _vwap.Arrays[1];	// standard deviation offset of vwap
	SCFloatArrayRef _hTB1 			= _vwap.Arrays[3];	// 
	SCFloatArrayRef _hBB1 			= _vwap.Arrays[4];	// 
	SCFloatArrayRef _hTB2 			= _vwap.Arrays[5];	// 
	SCFloatArrayRef _hBB2 			= _vwap.Arrays[6];	// 
	SCFloatArrayRef _hTB3 			= _vwap.Arrays[7];	// 
	SCFloatArrayRef _hBB3 			= _vwap.Arrays[8];	// 
	SCFloatArrayRef _hTB4 			= _vwap.Arrays[9];	// 
	SCFloatArrayRef _hBB4 			= _vwap.Arrays[10];	// 

	//
	// initilize
	//
	if ( sc.Index == 0 )
	{
		_periodStartIndex = 0;
		
		// auto coloring
		if ( _setAllColors.GetYesNo() == 1 )
		{
			int _color = _setAllColorsColor.GetColor();
			
			_vwap.PrimaryColor = _tb1.PrimaryColor = _bb1.PrimaryColor = _tb2.PrimaryColor = _bb2.PrimaryColor = 
								 _tb3.PrimaryColor = _bb3.PrimaryColor = _tb4.PrimaryColor = _bb4.PrimaryColor = _color;
		}
	}

	//
	// compute a hidden vwap and stddev for each bar
	//
	ECIVwap_ComputeBarVwap(sc, sc.Index, _userInputOnly.GetYesNo(), _hVwap);
	ECIVwap_ComputePeriodVwap(sc, sc.Index, sc.Index, _hVwap, _userInputOnly.GetYesNo(), _hVwap);
	ECIVwap_ComputeStddev(sc, sc.Index, sc.Index, _hVwap, _multiplier.GetFloat(), _userInputOnly.GetYesNo(),
							_hTB1, _hBB1, 
							_hTB2, _hBB2, 
							_hTB3, _hBB3, 
							_hTB4, _hBB4);
							
	//
	// draw last bracket value
	//
	if ( sc.Index > 0 )
	{
		float _lastPrice = sc.Close[sc.Index-1];
		if ( _lastPrice >= _hBB4[_periodStartIndex] && _lastPrice <= _hTB4[_periodStartIndex] )
		{
			// nothing to do
		}
		else
		{
			for (int _i=sc.Index-1; _i >= 0; _i-- )
			{
				if ( _lastPrice >= _hBB4[_i] && _lastPrice <= _hTB4[_i] )
				{
					_periodStartIndex = _i;
					break;
				}
			}
		}
	}
							
	_vwap[sc.Index] = _hVwap[_periodStartIndex];
	_tb1[sc.Index]  = _hTB1[_periodStartIndex];
	_bb1[sc.Index]  = _hBB1[_periodStartIndex];
	_tb2[sc.Index]  = _hTB2[_periodStartIndex];
	_bb2[sc.Index]  = _hBB2[_periodStartIndex];
	_tb3[sc.Index]  = _hTB3[_periodStartIndex];
	_bb3[sc.Index]  = _hBB3[_periodStartIndex];
	_tb4[sc.Index]  = _hTB4[_periodStartIndex];
	_bb4[sc.Index]  = _hBB4[_periodStartIndex];
							
	//logMsg.Format("sc.Index=<%d> periodType=<%d>", sc.Index, periodType);
	//sc.AddMessageToLog(logMsg,0); 
}

/* ==========================================================================
//
// compute vpoc in channel
//
// sc : sierra study context
// periodStartIndex : where vwap starts
// periodEndIndex : where vwap ends
// vpoc : where vpoc is returned
//
============================================================================ */
void ECIVwap_ComputeChannelVPOC(SCStudyGraphRef sc, unsigned int periodStartIndex, SCSubgraphRef vpoc)
{
	//
	// compute vpoc
	//
	// get highest and lowest of period
	int	_highInTicks = 0, _lowInTicks = INT_MAX;

	for (unsigned int _barIndex = periodStartIndex ; _barIndex <= sc.Index ; _barIndex++)
	{
		int _barHighInTicks, _barLowInTicks;

		if ( ! sc.VolumeAtPriceForBars->GetHighAndLowPriceTicksForBarIndex(_barIndex, _barHighInTicks, _barLowInTicks) )
		{
			sc.AddMessageToLog("Error on sc.VolumeAtPriceForBars->GetHighAndLowPriceTicksForBarIndex",0);			
			return;
		}
			
		if ( _barHighInTicks > _highInTicks )
			_highInTicks = _barHighInTicks;
		if ( _barLowInTicks < _lowInTicks )
			_lowInTicks = _barLowInTicks;
	}
	
	// compute vpoc. 
	// for each price, make the sum on all bars period
	unsigned long _maxVolume = 0;
	int			  _maxVolumePriceInTicks;
	
	for (int _priceInTicks =_lowInTicks ; _priceInTicks <= _highInTicks ; _priceInTicks++ )
	{
		unsigned long 	_sumVolume = 0;
		
		for (unsigned int _barIndex = periodStartIndex ; _barIndex <= sc.Index ; _barIndex++)
		{
			s_VolumeAtPriceV2 _p_vap = _p_vap = sc.VolumeAtPriceForBars->GetVAPElementAtPrice(_barIndex, _priceInTicks);			
			_sumVolume += _p_vap.Volume; // _p_vap.Volume contains 0 if no volume at price
		}
		
		if ( _sumVolume > _maxVolume )
		{
			_maxVolume = _sumVolume;
			_maxVolumePriceInTicks = _priceInTicks;
		}	
	}
	vpoc[sc.Index] = (float)_maxVolumePriceInTicks * sc.TickSize;
}


/* ==========================================================================
//
// ECIVwapChannel study
// 
============================================================================ */
SCSFExport scsf_ECIVwapChannel(SCStudyGraphRef sc)
{
	SCString logMsg;

	//
	// subgraphs
	//
	SCSubgraphRef _vwap = sc.Subgraph[0];
	SCSubgraphRef _tb1 	= sc.Subgraph[1];
	SCSubgraphRef _bb1 	= sc.Subgraph[2];
	SCSubgraphRef _tb2 	= sc.Subgraph[3];
	SCSubgraphRef _bb2 	= sc.Subgraph[4];
	SCSubgraphRef _tb3 	= sc.Subgraph[5];
	SCSubgraphRef _bb3 	= sc.Subgraph[6];
	SCSubgraphRef _tb4 	= sc.Subgraph[7];
	SCSubgraphRef _bb4 	= sc.Subgraph[8];
	
	SCSubgraphRef _vpoc = sc.Subgraph[9];	

	//
	// input
	//
	SCInputRef _period 		= sc.Input[0];
	SCInputRef _multiplier 	= sc.Input[1];
			
	SCInputRef _setAllColors 		= sc.Input[2];
	SCInputRef _setAllColorsColor 	= sc.Input[3];

	SCInputRef _userInputOnly		= sc.Input[4];
	
	SCInputRef _computeVpoc	= sc.Input[5];

	//
	// Initialize configuration variables
	//
	if (sc.SetDefaults)
	{		
		// General
		sc.GraphName 		= g_VwapChannelName + g_StudyVersion;
		sc.StudyDescription = g_ECIVwapChannelStudyDescription;
		sc.GraphRegion 		= 0;

		// subgraphs			
		_vwap.Name 			= g_VwapChannelName;
		_vwap.DrawStyle 	= DRAWSTYLE_LINE;
		_vwap.PrimaryColor 	= ECIVWAP_MAIN_COLOR;
		_vwap.LineWidth		= 2;

		_tb1.Name 			= "Top Band 1 of Vwap Standard Deviation";
		_bb1.Name 			= "Bottom Band 1 of Vwap Standard Deviation";
		_tb1.DrawStyle 		= _bb1.DrawStyle = DRAWSTYLE_LINE;
		_tb1.LineStyle		= _bb1.LineStyle = LINESTYLE_DOT;
		_tb1.PrimaryColor 	= _bb1.PrimaryColor = ECIVWAP_MAIN_COLOR;

		_tb2.Name 			= "Top Band 2 of Vwap Standard Deviation";
		_bb2.Name 			= "Bottom Band 2 of Vwap Standard Deviation";
		_tb2.DrawStyle 		= DRAWSTYLE_FILLTOP_TRANSPARENT;
		_bb2.DrawStyle 		= DRAWSTYLE_FILLBOTTOM_TRANSPARENT;
		_tb2.PrimaryColor 	= _bb2.PrimaryColor = ECIVWAP_MAIN_COLOR;
		
		_tb3.Name 			= "Top Band 3 of Vwap Standard Deviation";
		_bb3.Name 			= "Bottom Band 3 of Vwap Standard Deviation";
		_tb3.DrawStyle 		= _bb3.DrawStyle = DRAWSTYLE_LINE;
		_tb3.LineStyle		= _bb3.LineStyle = LINESTYLE_DOT;
		_tb3.PrimaryColor 	= _bb3.PrimaryColor = ECIVWAP_MAIN_COLOR;

		_tb4.Name 			= "Top Band 4 of Vwap Standard Deviation";
		_bb4.Name 			= "Bottom Band 4 of Vwap Standard Deviation";
		_tb4.DrawStyle 		= _bb4.DrawStyle = DRAWSTYLE_LINE;
		_tb4.PrimaryColor 	= _bb4.PrimaryColor = ECIVWAP_MAIN_COLOR;
		
		_vpoc.Name 			= "Vpoc";
		_vpoc.DrawStyle 	= DRAWSTYLE_LINE;
		_vpoc.PrimaryColor 	= ECIVWAP_VPOC_COLOR;	
		_vpoc.LineWidth		= 2;
		
		// input
		_period.Name		= "Period";
		_period.SetDescription("Vwap channel period");
		_period.SetInt(50);
		
		_multiplier.Name 	= "Multiplier";
		_multiplier.SetDescription("Standard deviation multiplier");
		_multiplier.SetFloat(0.5f);
				
		_setAllColors.Name = "Set all colors";
		_setAllColors.SetDescription("Set all colors automatically");
		_setAllColors.SetYesNo(0);
		_setAllColorsColor.Name = "Set all colors color";
		_setAllColorsColor.SetDescription("Set all colors automatically color");
		_setAllColorsColor.SetColor(ECIVWAP_MAIN_COLOR);
		
		_userInputOnly.Name = "Based on input only";
		_userInputOnly.SetDescription("Computation based on input only (no volume)");
		_userInputOnly.SetYesNo(0);
		
		_computeVpoc.Name = "Compute VPOC (experimental)";
		_computeVpoc.SetYesNo(0);	
		
		// misc
		sc.AutoLoop = 1;
		sc.FreeDLL = DEV_FREE_DLL;
		sc.MaintainVolumeAtPriceData = 1;  // needed for sc.VolumeAtPriceForBars
		sc.DrawStudyUnderneathMainPriceGraph = 1;
		sc.ScaleRangeType = SCALE_SAMEASREGION;

		return;
	}

	//
	// Do data processing
	//

	//
	// initilize
	//
	SCFloatArrayRef _barVwap = _vwap.Arrays[0]; 	// vwap based on all bar prices X volumes

	int _periodStartIndex 	 = max(sc.Index - _period.GetInt() + 1, 0);
	
	if ( sc.Index == 0 )
	{
		// auto coloring
		if ( _setAllColors.GetYesNo() == 1 )
		{
			int _color = _setAllColorsColor.GetColor();
			
			_vwap.PrimaryColor = _tb1.PrimaryColor = _bb1.PrimaryColor = _tb2.PrimaryColor = _bb2.PrimaryColor = 
								 _tb3.PrimaryColor = _bb3.PrimaryColor = _tb4.PrimaryColor = _bb4.PrimaryColor = _color;
		}
	}
	

	//
	// compute a hidden vwap and stddev for each bar
	//
	
	ECIVwap_ComputeBarVwap(sc, sc.Index, _userInputOnly.GetYesNo(), _barVwap);
	ECIVwap_ComputePeriodVwap(sc, _periodStartIndex, sc.Index, _barVwap, _userInputOnly.GetYesNo(), _vwap);
	ECIVwap_ComputeStddev(sc, _periodStartIndex, sc.Index, _vwap, _multiplier.GetFloat(), _userInputOnly.GetYesNo(),
							_tb1, _bb1, 
							_tb2, _bb2,
							_tb3, _bb3, 	
							_tb4, _bb4 );
							
	//
	// compute vpoc
	//
	if ( _computeVpoc.GetYesNo() == 1 )
		ECIVwap_ComputeChannelVPOC(sc, _periodStartIndex, _vpoc);
														
	//logMsg.Format("sc.Index=<%d> periodType=<%d>", sc.Index, periodType);
	//sc.AddMessageToLog(logMsg,0); */
}