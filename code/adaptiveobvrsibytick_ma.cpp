// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// Name of the custom study.
//SCDLLName("Adaptive OBV RSI Moving Average By Tick With Filters") 

//Custom study starts here.
SCSFExport scsf_AdaptiveOBVRSIByTick(SCStudyGraphRef sc)
{
	//Aliases to make things easier to read and maintain.
	SCSubgraphRef Graph_AOBVRSI = sc.Subgraph[0];
	SCInputRef In_InputData = sc.Input[0];
	SCInputRef In_VolumeFilterType = sc.Input[1];
	SCInputRef In_MAClipSmoothingPeriod = sc.Input[2];
	SCInputRef In_MAClipSmoothingMAType = sc.Input[3];
	SCInputRef In_OBVSetSmoothing = sc.Input[4];
	SCInputRef In_OBVSmoothingPeriod = sc.Input[5];
	SCInputRef In_OBVSmoothingMAType = sc.Input[6];
	SCInputRef In_RSIPeriod = sc.Input[7];
	SCInputRef In_RSICalcMAType = sc.Input[8];
	SCInputRef In_RSISetSmoothing = sc.Input[9];
	SCInputRef In_RSISmoothingPeriod = sc.Input[10];
	SCInputRef In_RSISmoothingMAType = sc.Input[11];
	SCInputRef In_AOBVRSIScaleFactorChange = sc.Input[12];
	SCInputRef In_InputPriceData = sc.Input[13];
	SCSubgraphRef OBV = sc.Subgraph[1];
	SCSubgraphRef VolumeMA = sc.Subgraph[2];
	SCSubgraphRef OBVSmoothed = sc.Subgraph[3];
	SCSubgraphRef OBVRSI = sc.Subgraph[4];
	SCSubgraphRef OBVRSISmoothed = sc.Subgraph[5];
	//SCFloatArrayRef FloatArray = Graph_AOBVRSI.Arrays[0];
	
	//remember local variables are not persistent.
	int Up, Down, VolumeType;
	float Balance, VolumeScale, ScalingFactor;
	
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		//Long descriptive name.
		sc.GraphName = "Adaptive OBV RSI Moving Average By Tick With Filters";
		
		sc.StudyVersion = 1.1;
		
		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		
		//Data for the "Display Study Documentation" button
sc.StudyDescription = "Adaptive OBV RSI Moving Average By Tick With Filters. To properly use this indicator, Sierra Chart must be set up in tick by tick mode with intraday bars. If all \"Input Data\" options show a straight line at 0.0, then tick by tick data is not available or not enabled. Note that some volume data is only available when the market is open.<p>OBV acts similar for volume for what price does on the main chart. OBV is first calculated and then an RSI is taken of it. The RSI values are then put into an EMA formula to make an Adaptive Moving Average. When RSI goes weak (indicating volume movement has gone weak), the AMA line will slow down. For a more complete picture, it is recommended to use this indicator with Up/Down Volume Ratio or Difference, OBV By Tick using the MA Ribbon option, OBV By Tick MACD, and OBV By Tick RSI to help see the volume moves to identify the trend.<p>This OBV version has a Volume Filter option to handle cases when a volume spike smashes the indicator making it hard to read. Large institutions sometimes do this to hide their activity afterward. The \"Straight\" option passes volume data through without any filtering. The \"Log\" option runs each volume bar through the log function making a type of \"log scale\". The \"Square Root\" option runs each volume bar through the square root function making a type of \"square root scale\". The \"MA Clip\" option will clip volume above a chosen moving average. The final Smoothing option will apply a moving average to take some of the noise out of the final OBV line.<p>This RSI version has recommended extra smoothing options to help take the noise out of the RSI line.<p>Observations. Volume tends to have longer runs than price. Setting the RSI period too small will just smash the indicator during these long runs. The AOBVRSI line tends to be slower than Adaptive IIO and Adaptive Volume Ratio (but a bit noisier at the RSI extremes) because RSI as a base tends to be a little more sluggish. That makes this indicator preferred when looking for slower AMA lines. Like the other tick based volume AMA's, this one tends to ignore weaker price movements.";
		
		//needed for extra tick data.
		sc.MaintainAdditionalChartDataArrays = 1;
		
		sc.GraphRegion = 0; //main price graph

		sc.AutoLoop = 1;  //Auto looping is enabled. 
		
		//Output Graph
		Graph_AOBVRSI.Name = "AOBVRSI"; //drawn graphs must have a name.
		Graph_AOBVRSI.PrimaryColor = RGB(255, 0, 0);
		Graph_AOBVRSI.DrawStyle = DRAWSTYLE_LINE;
		Graph_AOBVRSI.LineStyle = LINESTYLE_SOLID; //if LineWidth>1, lines will appear solid
		Graph_AOBVRSI.LineWidth = 2;
		Graph_AOBVRSI.DrawZeros = 1;
		
		//User Inputs
		
		In_InputData.Name = "Input Volume Data";
		In_InputData.SetCustomInputIndex(0);
		In_InputData.SetCustomInputStrings("Up/Down Volume;Ask/Bid Volume;Up/Down Trades");
		In_InputData.SetDescription("Select volume type to operate on. Not all types may be available. Some types are only available when the market is open.");

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
		
		In_OBVSetSmoothing.Name = "Set OBV Smoothing?";
		In_OBVSetSmoothing.SetYesNo(1);
		In_OBVSetSmoothing.SetDescription("Enables extended smoothing options.");
		
		In_OBVSmoothingPeriod.Name = "OBV Smoothing Period";
		In_OBVSmoothingPeriod.SetInt(7);
		In_OBVSmoothingPeriod.SetIntLimits(2, 50);
		In_OBVSmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-10.");
		
		In_OBVSmoothingMAType.Name = "OBV Smoothing Moving Average Type";
		In_OBVSmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_OBVSmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_RSIPeriod.Name = "RSI Period";
		In_RSIPeriod.SetInt(35);
		In_RSIPeriod.SetIntLimits(3, 100);
		In_RSIPeriod.SetDescription("Number of bars for the period. Useful values are 10 and higher.");
		
		In_RSICalcMAType.Name = "RSI Calculation Moving Average Type";
		In_RSICalcMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_RSICalcMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_RSISetSmoothing.Name = "Set RSI Smoothing?";
		In_RSISetSmoothing.SetYesNo(1);
		In_RSISetSmoothing.SetDescription("Enables extended RSI smoothing options.");
		
		In_RSISmoothingPeriod.Name = "RSI Smoothing Period";
		In_RSISmoothingPeriod.SetInt(7);
		In_RSISmoothingPeriod.SetIntLimits(2, 50);
		In_RSISmoothingPeriod.SetDescription("Number of bars for the period. Usually 3-7.");
		
		In_RSISmoothingMAType.Name = "RSI Smoothing Moving Average Type";
		In_RSISmoothingMAType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		In_RSISmoothingMAType.SetDescription("Usually EMA, but others can be experimented with.");
		
		In_AOBVRSIScaleFactorChange.Name = "AOBVRSI Scale Factor Change";
		In_AOBVRSIScaleFactorChange.SetFloat(0.6);
		In_AOBVRSIScaleFactorChange.SetFloatLimits(0.1, 2.0);
		In_AOBVRSIScaleFactorChange.SetDescription("Percent of Scale Factor to change Adaptive calculation. Range 0.1 to 2.0.");
		
		In_InputPriceData.Name = "Input Price Data";
		In_InputPriceData.SetInputDataIndex(SC_LAST); //default to bar close.
		In_InputPriceData.SetDescription("Usually \"Last\" for Close.");
		
		//Keep alerts from going crazy.
		sc.AlertOnlyOncePerBar = true;
		
		//Set printed output value format. Number is the index of the selected format.
		//sc.ValueFormat = 3;  // 3 decimal places
		sc.ValueFormat = sc.BaseGraphValueFormat;
		
		return;
		}
	
	// Section 2 - Do data processing here

	//if first run. Set persistent variables here.
	if(sc.Index == 0) {
		// Set the index of the first array element to begin drawing at
		sc.DataStartIndex = (In_OBVSetSmoothing.GetYesNo() ? In_OBVSmoothingPeriod.GetInt() : 0) + In_RSIPeriod.GetInt() + (In_RSISetSmoothing.GetYesNo() ? In_RSISmoothingPeriod.GetInt() : 0);
		//local variable
		Balance = 0.0;
		}
	
	//Reload Balance with previous value. Much easier to read this way.
	if(sc.Index >= 1) {Balance = OBV[sc.Index -1];}

	//Select Input Data Type
	if(In_InputData.GetIndex() == 0) {Up = SC_UPVOL; Down = SC_DOWNVOL; VolumeType = SC_VOLUME;}
	else if(In_InputData.GetIndex() == 1) {Up = SC_ASKVOL; Down = SC_BIDVOL; VolumeType = SC_VOLUME;}
	else {Up = SC_ASKNT; Down = SC_BIDNT; VolumeType = SC_NT;}
	
	//Calculate On Balance Volume filter type.
	if(In_VolumeFilterType.GetIndex() == 0) { // 0: straight
		Balance += (float)sc.BaseData[Up][sc.Index];
		Balance -= (float)sc.BaseData[Down][sc.Index];
		}
	else if(In_VolumeFilterType.GetIndex() == 1) { // 1: log
		Balance += log( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= log( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else if(In_VolumeFilterType.GetIndex() == 2) { // 2: sqrt
		Balance += sqrt( (float)sc.BaseData[Up][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Up][sc.Index] );
		Balance -= sqrt( (float)sc.BaseData[Down][sc.Index] < 1.0 ? 1.0 : (float)sc.BaseData[Down][sc.Index] );
		}
	else { // 3: MA Clip
		sc.MovingAverage(sc.BaseData[VolumeType], VolumeMA, In_MAClipSmoothingMAType.GetMovAvgType(), In_MAClipSmoothingPeriod.GetInt() );
		//handle normal volume
		if((float)sc.BaseData[VolumeType][sc.Index] <= VolumeMA[sc.Index]) {
			Balance += (float)sc.BaseData[Up][sc.Index];
			Balance -= (float)sc.BaseData[Down][sc.Index];
			}
		//handle clipped volume
		else {
			VolumeScale = (float)VolumeMA[sc.Index] / (float)sc.BaseData[VolumeType][sc.Index];
			Balance += VolumeScale * (float)sc.BaseData[Up][sc.Index];
			Balance -= VolumeScale * (float)sc.BaseData[Down][sc.Index];
			}
		}
	OBV[sc.Index] = Balance;
	
	//Handle OBV smoothing.
	if( In_OBVSetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBV, OBVSmoothed, In_OBVSmoothingMAType.GetMovAvgType(), In_OBVSmoothingPeriod.GetInt() );
		}
	else {
		OBVSmoothed[sc.Index] = OBV[sc.Index];
		}

	//Generate RSI.
	sc.RSI(OBVSmoothed, OBVRSI, In_RSICalcMAType.GetMovAvgType(), In_RSIPeriod.GetInt() );
	
	//Handle RSI smoothing.
	if( In_RSISetSmoothing.GetYesNo() ) {
		sc.MovingAverage(OBVRSI, OBVRSISmoothed, In_RSISmoothingMAType.GetMovAvgType(), In_RSISmoothingPeriod.GetInt() );
		ScalingFactor = ((OBVRSISmoothed[sc.Index] / 100.0) - 0.5) * 2.0 * In_AOBVRSIScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		//Note that a MA may overshoot the range a little. For this it doesn't matter.
		}
	else {
		ScalingFactor = ((OBVRSI[sc.Index] / 100.0) - 0.5) * 2.0 * In_AOBVRSIScaleFactorChange.GetFloat(); //range -1.0 to 1.0
		}
	
	ScalingFactor = ScalingFactor * ScalingFactor; //Square it to slow down the overly fast parts. Also keeps it positive for the next calculation.
	
	//EMA type calculation.
	Graph_AOBVRSI[sc.Index] = ((sc.BaseDataIn[In_InputPriceData.GetInputDataIndex()][sc.Index] - Graph_AOBVRSI[sc.Index-1]) * ScalingFactor) + Graph_AOBVRSI[sc.Index-1];
}
