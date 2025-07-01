// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Klinger Volume Oscillator With Filters") 

//Custom study starts here.
SCSFExport scsf_KVOWithFilters(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef ZeroLine = sc.Subgraph[0];
	SCSubgraphRef Graph_Histogram = sc.Subgraph[1];
	SCSubgraphRef Graph_KVOTrigger = sc.Subgraph[2];
	SCSubgraphRef Graph_KVO = sc.Subgraph[3]; //last graph is drawn on top.
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_PriceSetSmoothing = sc.Input[1];
	SCInputRef In_PriceSmoothingPeriod = sc.Input[2];
	SCInputRef In_PriceSmoothingMAType = sc.Input[3];
	SCInputRef In_VolumeFilterType = sc.Input[4];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[5];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[6];
	SCInputRef In_KVOFastSmoothingPeriod = sc.Input[7];
	SCInputRef In_KVOSlowSmoothingPeriod = sc.Input[8];
	SCInputRef In_KVOFastSlowSmoothingMAType = sc.Input[9];
	SCInputRef In_KVOSetExtraSmoothing = sc.Input[10];
	SCInputRef In_KVOExtraSmoothingPeriod = sc.Input[11];
	SCInputRef In_KVOExtraSmoothingMAType = sc.Input[12];
	SCInputRef In_KVOTriggerSmoothingPeriod = sc.Input[13];
	SCInputRef In_KVOTriggerSmoothingMAType = sc.Input[14];
	SCInputRef In_OutputMultiplier = sc.Input[15];
	SCSubgraphRef Price = sc.Subgraph[4];
	SCSubgraphRef VolumeFiltered = sc.Subgraph[5];
	SCSubgraphRef VolumeMA = sc.Subgraph[6];
	SCSubgraphRef VolumeForce = sc.Subgraph[7];
	SCSubgraphRef KVOFast = sc.Subgraph[8];
	SCSubgraphRef KVOSlow = sc.Subgraph[9];
	SCSubgraphRef KVO = sc.Subgraph[10];
	SCSubgraphRef KVOSmoothed = sc.Subgraph[11];
	SCSubgraphRef HighLow = sc.Subgraph[12];
	//SCFloatArrayRef FloatArray = Graph_KVO.Arrays[0];
	
	//remember local variables are not persistent.
	int itemp;
	float ScalingFactor;
	
	//persistent variables.
	int &Trend = sc.PersistVars->i1;
	int &TrendPrevious = sc.PersistVars->i2;
	float &HighLowSum = sc.PersistVars->f1;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Klinger Volume Oscillator With Filters";
		
		sc.StudyVersion = 1.0;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Klinger Volume Oscillator With Filters (KVO). A price and volume based oscillator developed by Stephen J. Klinger to handle both short term and long term time frame analysis of money flowing into and out of a security. It's output is very similar to MACD and can be traded in the same way. It is somewhat unique as its algorithm keeps track of current direction and accounts for it in the calculations. Klinger defined volume as a force behind price movement and accumulation/distribution as the overall volume change from period to period. He labeled it Volume Force. A positive Volume Force is more accumulation than distribution, a negative volume force is more distribution than accumulation. As a trend starts to end, the Volume Force should noticeably reduce before the price reversal. Klinger has some guidelines for his oscillator. The most reliable signals from KVO are in the direction of the current price trend so don't trade against the trend. KVO divergence from current price action is a trend weakening signal (similar to MACD divergence). Klinger uses an 89 period EMA for price to determine the current price trend. An up trend is price above EMA89, and a down trend is price below EMA89. In an up trend, if KVO tops then down crosses the trigger line, that's a signal that the trend is near completion (invert that for a down trend). Klinger recommends other indicators like Stochastic, RSI, and MACD to help confirm movement into over bought/sold conditions.<p>Brett Johnson's Programming Rant: Most people are totally clueless about how to properly implement this indicator. Initially I thought I found a web page that properly explained it, but continued searching over the next couple hours proved me very wrong. I've found several variations that are incorrect. I've found some web pages with 3 different versions written in 3 different stock chart languages. I've found a couple web pages showing the proper algorithm in math form, but then they screw up the code several lines down. Nobody seems to pay attention. Some people seem to give up and implement a simplified version. If you're trying to program this indicator yourself and are stuck, check my source code. It's open and excessively documented. There's no reason for a simple algorithm to be this screwed up on so many other platforms and web pages.<p>This KVO version has multiple smoothing options to handle an extremely noisy indicator.<p>This KVO version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.<p>To use KVO in its original form, turn off all extra options and use the default values.<p>Observations. To say that this is a noisy indicator is an understatement. Turn on MA Clip 3 and all the filters to their default values (or higher) to greatly clean this up. In addition to the recommended indicators, also add trend lines as a price shouldn't be traded until it breaks the trend line. Always remember, just because KVO moves doesn't mean that price will move with it. This indicator doesn't do very well with ranging data. To be fair, that's true of many indicators. This indicator was originally developed in the mid 1990's for daily bars that almost always had volume. Low time scale intraday bars (like 1 minute) with 0 volume will make the KVO line very noisy. Zoom out time wise until all the bars have enough volume for a clean signal.";
		
		//sc.GraphRegion = 1; //in this case, not main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graph
		
		Graph_KVO.Name = "KVO"; //drawn graphs must have a name.
		Graph_KVO.PrimaryColor = RGB(0, 0, 255);
		Graph_KVO.DrawStyle = DRAWSTYLE_LINE;
		Graph_KVO.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_KVO.LineWidth = 1;
		Graph_KVO.DrawZeros = 1;
		
		Graph_KVOTrigger.Name = "KVOTrigger"; //drawn graphs must have a name.
		Graph_KVOTrigger.PrimaryColor = RGB(255, 0, 0);
		Graph_KVOTrigger.DrawStyle = DRAWSTYLE_LINE;
		Graph_KVOTrigger.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_KVOTrigger.LineWidth = 1;
		Graph_KVOTrigger.DrawZeros = 1;
		
		Graph_Histogram.Name = "KVOHistogram"; //drawn graphs must have a name.
		Graph_Histogram.PrimaryColor = RGB(64, 64, 64);
		Graph_Histogram.DrawStyle = DRAWSTYLE_BAR;
		Graph_Histogram.LineStyle = LINESTYLE_SOLID;
		Graph_Histogram.LineWidth = 2;
		Graph_Histogram.DrawZeros = 1;
		
		ZeroLine.Name="Zero";
		ZeroLine.DrawStyle = DRAWSTYLE_LINE;
		ZeroLine.LineStyle = LINESTYLE_DOT;
		ZeroLine.LineWidth = 1;
		ZeroLine.PrimaryColor = RGB(128, 128, 128);;
		ZeroLine.DisplayNameValueInWindowsFlags = 0;
		ZeroLine.DrawZeros = 1;
		
		//User Inputs
		
		In_InputData.Name = "Input Data";
		In_InputData.SetInputDataIndex(SC_HLC); //default to bar close.
		In_InputData.SetDescription("Usually \"HLC Avg\" for Typical Price.");

		In_PriceSetSmoothing.Name = "Set Price Smoothing?";
		In_PriceSetSmoothing.SetYesNo(0);
		In_PriceSetSmoothing.SetDescription("Enables extended price smoothing options.");
		
		In_PriceSmoothingPeriod.Name = "Price Smoothing Period";
		In_PriceSmoothingPeriod.SetInt(3);
		In_PriceSmoothingPeriod.SetIntLimits(2, 50);
		In_PriceSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_PriceSmoothingMAType.Name = "Price Smoothing Moving Average Type";
		In_PriceSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_PriceSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_VolumeFilterType.Name = "Volume Filtering Type";
		In_VolumeFilterType.SetCustomInputIndex(0);
		In_VolumeFilterType.SetCustomInputStrings("Straight;Log;Square Root;MA Clip");
		In_VolumeFilterType.SetDescription("\"Straight\" for no filtering and normal calculations. \"Log\" for applying log(Volume). \"Square Root\" for applying sqrt(Volume). \"MA Clip\" for clipping the volume above the chosen moving average.");
		
		In_MAClipSmoothingPeriod.Name = "MA Clip Smoothing Period";
		In_MAClipSmoothingPeriod.SetInt(3);
		In_MAClipSmoothingPeriod.SetIntLimits(2, 100);
		In_MAClipSmoothingPeriod.SetDescription("Only if MA Clip is selected. Number of bars for the period. Usually 3-30.");
		
		In_MAClipSmoothingMAType.Name = "MA Clip Moving Average Type";
		In_MAClipSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_MAClipSmoothingMAType.SetDescription("Only if MA Clip is selected. Usually EMA, but others can be experimented with.");		
		
		In_KVOFastSmoothingPeriod.Name = "KVO Fast Period";
		In_KVOFastSmoothingPeriod.SetInt(34);
		In_KVOFastSmoothingPeriod.SetIntLimits(2, 300);
		In_KVOFastSmoothingPeriod.SetDescription("Number of bars for the period. Usually over 20.");
		
		In_KVOSlowSmoothingPeriod.Name = "KVO Slow Period";
		In_KVOSlowSmoothingPeriod.SetInt(55);
		In_KVOSlowSmoothingPeriod.SetIntLimits(3, 300);
		In_KVOSlowSmoothingPeriod.SetDescription("Number of bars for the period. Usually over 40.");
		
		In_KVOFastSlowSmoothingMAType.Name = "KVO Moving Average Type";
		In_KVOFastSlowSmoothingMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_KVOFastSlowSmoothingMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_KVOSetExtraSmoothing.Name = "Set Extra KVO Smoothing?";
		In_KVOSetExtraSmoothing.SetYesNo(0);
		In_KVOSetExtraSmoothing.SetDescription("The KVO line is noisy. Enables extended KVO smoothing options.");
		
		In_KVOExtraSmoothingPeriod.Name = "Extra KVO Smoothing Period";
		In_KVOExtraSmoothingPeriod.SetInt(5);
		In_KVOExtraSmoothingPeriod.SetIntLimits(2, 50);
		In_KVOExtraSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_KVOExtraSmoothingMAType.Name = "Extra KVO Smoothing Moving Average Type";
		In_KVOExtraSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_KVOExtraSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_KVOTriggerSmoothingPeriod.Name = "KVO Trigger Period";
		In_KVOTriggerSmoothingPeriod.SetInt(13);
		In_KVOTriggerSmoothingPeriod.SetIntLimits(3, 300);
		In_KVOTriggerSmoothingPeriod.SetDescription("Number of bars for the period. Usually 9-15.");
		
		In_KVOTriggerSmoothingMAType.Name = "KVO Trigger Moving Average Type";
		In_KVOTriggerSmoothingMAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		In_KVOTriggerSmoothingMAType.SetDescription("Usually SMA, but others can be experimented with.");
		
		In_OutputMultiplier.Name = "Output Multiplier";
		In_OutputMultiplier.SetFloat(100.0);
		In_OutputMultiplier.SetFloatLimits(1.0e-6, 100.0);
		In_OutputMultiplier.SetDescription("Range 1.0e-6 to 100.0. The Output Multiplier of 100.0 is part of the original formula. It does nothing more than to increase the output values to something more human readable. On larger time frame bars (like daily) the numbers will be excessively large. It would be better to shrink those numbers to something more manageable.");
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = 1;
		
		return;
		}
	
	// Section 2 - Do data processing here

	//Handle the zero line.
	ZeroLine[sc.Index] = 0.0;
	
	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		//Make sure smoothing periods are in the right order.
		if(In_KVOFastSmoothingPeriod.GetInt() > In_KVOSlowSmoothingPeriod.GetInt()) {
			itemp = In_KVOSlowSmoothingPeriod.GetInt();
			In_KVOSlowSmoothingPeriod.SetInt( In_KVOFastSmoothingPeriod.GetInt() );
			In_KVOFastSmoothingPeriod.SetInt( itemp );
			}
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = In_KVOSlowSmoothingPeriod.GetInt();
		// Initialize persistent variables.
		Trend = 0; //Initializing Trend to 0 will block early garbage in the later VolumeForce calculation.
		TrendPrevious = 0; //Initializing TrendPrevious to 0 will block early garbage in the later VolumeForce calculation.
		HighLowSum = 0.0;
		}
	
	//Handle price smoothing.
	if( In_PriceSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(sc.BaseDataIn[In_InputData.GetInputDataIndex()], Price, In_PriceSmoothingMAType.GetMovAvgType(), In_PriceSmoothingPeriod.GetInt() );
		}
	else {
		Price[sc.Index] = sc.BaseDataIn[In_InputData.GetInputDataIndex()][sc.Index];
		}
	
	//Handle volume filtering.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		VolumeFiltered[sc.Index] = (float)sc.Volume[sc.Index];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		VolumeFiltered[sc.Index] = log( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		VolumeFiltered[sc.Index] = sqrt( (float)sc.Volume[sc.Index] < 1.0 ? 1.0 : (float)sc.Volume[sc.Index] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.Volume, VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		if((float)sc.Volume[sc.Index] <= VolumeMA[sc.Index]) {VolumeFiltered[sc.Index] = (float)sc.Volume[sc.Index];} //handle normal volume
		else {VolumeFiltered[sc.Index] = (float)VolumeMA[sc.Index];} //handle clipped volume
		}
	
	//Do the KVO calculations.
	
	//Typical Price handled by In_InputData and Price[] already. Using "High+Low+Close" without the "divide by 3" can create false movements.
	//Variable names cleaned up for clarity and understanding:
	//DM[] or Daily Measurement = HighLow[]
	//CM or Cumulative Measurement = HighLowSum
	//ScalingFactor = that part of the VolumeForce equation where a lot of people screw up. Watch the parenthesis everyone. Order of operation is very important here. The absolute value of ScalingFactor is designed to be above 1.0 most of the time. The longer the run, the higher ScalingFactor gets to 2.0.
	//The WRONG Scaling Factor: abs(2.0 * (HighLow[sc.Index]/HighLowSum) -1.0); The range on this one is mostly 0.0 to 1.0. A value of 0.0 in a running average will whiplash the MA line. 0 vales are generally useless to everyone.
	//The right Scaling Factor: abs(2.0 * ((HighLow[sc.Index]/HighLowSum) -1.0)); The range on this one is mostly 1.0 to 2.0. This means the values are passed through ranging from untouched to doubled. The whiplash potential is much less and the signal will be cleaner.
	
	//Load HighLow array.
	HighLow[sc.Index] = sc.High[sc.Index] - sc.Low[sc.Index];
	
	//not enough data yet to finish the calculation.
	if(sc.Index < 1) {return;}
	
	//Determine if the current trend direction.
	if(Price[sc.Index] == Price[sc.Index-1]) {Trend = TrendPrevious;} //no trend, leave it unchanged
	else if(Price[sc.Index] > Price[sc.Index-1]) {Trend = 1;} //up trend
	else {Trend = -1;} //down trend
	
	//Handle price summation.
	if(Trend == TrendPrevious) {HighLowSum += HighLow[sc.Index];} //continue trending
	else { //trend reversal
		HighLowSum = HighLow[sc.Index-1] + HighLow[sc.Index]; //initialize with the previous and current values
		TrendPrevious = Trend; //register trend change
		}
	
	/*
	Scaling Factor divide by 0 problems. These should be rare but can happen on low volume securities. This is poorly addressed in all the documentation, so it needs to be analyzed in depth.
	Under normal circumstances, HighLowSum is initialized with 2 bars of HighLow[] and should keep increasing with each additional bar until reversal. The HighLow[i]/HighLowSum number is a fraction that should always be getting smaller until the next reversal because of the constantly increasing denominator.
	Real world data shows the Scaling Factor range to mostly be between 1.0 and 2.0 with the number approaching 2.0 the longer it goes without a reversal.
	If HighLowSum is 0.0, then there was probably a recent reversal reset on junk data.
	To find out what the Scaling Factor would be in general after a reversal, set up a test with boring data, in this case 1.0 for the 2 previous HighLow[] bars:
	ScalingFactor = abs(2.0 * ((1.0/(1.0+1.0)) - 1.0)) = 1.0
	We already know the range is mostly 1.0-2.0 and generally starts out low. The value of 1.0 is a good choice for "pass through and don't mess with it".
	To find out what the Scaling Factor would be with a whiplash reset, set up another test with 1.0 and 0.1:
	ScalingFactor = abs(2.0 * ((0.1/(1.0+0.1)) - 1.0)) = 1.8
	This starts out very high in the range. A near full boost starting out on garbage amplifying a bad signal is a bad idea.
	To find out what the Scaling Factor would be with the previous whiplashed flipped around, set up another test with 0.1 and 1.0:
	ScalingFactor = abs(2.0 * ((1.0/(0.1+1.0)) - 1.0)) = 0.18
	This damps the output and would bring the final equation value down close to 0.0. Unnecessary zeros in a moving average cause whiplash. This isn't a very good choice either.
	If we take the middle of the last 2 extremes, we get 0.8. This isn't far from 1.0 in the boring example. In general, it looks like setting Scaling Factor to 1.0 on bad data and just letting it pass through would probably be the most logical choice.
	Keep in mind there's always the possibility volume will be 0, thus zeroing out the equation and handling the problem by itself.
	*/
	
	//Calculate a proper Scaling Factor
	if(HighLowSum == 0.0) {ScalingFactor = 1.0;} //handle any divide by 0 problems
	else {
		ScalingFactor = 2.0 * ((HighLow[sc.Index]/HighLowSum) -1.0);
		if(ScalingFactor < 0.0) {ScalingFactor *= -1.0;} //ScalingFactor must be positive.		
		}
		
	//Do the VolumeForce Calculation
	VolumeForce[sc.Index] = VolumeFiltered[sc.Index] * ScalingFactor * Trend * In_OutputMultiplier.GetFloat();
	
	//Fast moving average.
	sc.MovingAverage(VolumeForce, KVOFast, In_KVOFastSlowSmoothingMAType.GetMovAvgType(), In_KVOFastSmoothingPeriod.GetInt() );
	//Slow moving average.
	sc.MovingAverage(VolumeForce, KVOSlow, In_KVOFastSlowSmoothingMAType.GetMovAvgType(), In_KVOSlowSmoothingPeriod.GetInt() );
	
	//Generate the KVO value.
	KVO[sc.Index] = KVOFast[sc.Index] - KVOSlow[sc.Index];
	
	//Handle KVO extra smoothing.
	if( In_KVOSetExtraSmoothing.GetYesNo() ) {
		sc.MovingAverage(KVO, KVOSmoothed, In_KVOExtraSmoothingMAType.GetMovAvgType(), In_KVOExtraSmoothingPeriod.GetInt() );
		Graph_KVO[sc.Index] = KVOSmoothed[sc.Index];
		}
	else {
		Graph_KVO[sc.Index] = KVO[sc.Index];
		}
		
	//KVO Trigger line.
	sc.MovingAverage(Graph_KVO, Graph_KVOTrigger, In_KVOTriggerSmoothingMAType.GetMovAvgType(), In_KVOTriggerSmoothingPeriod.GetInt() );
	
	//KVO Histogram.
	Graph_Histogram[sc.Index] = Graph_KVO[sc.Index] - Graph_KVOTrigger[sc.Index];
}
