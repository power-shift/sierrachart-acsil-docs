#include "sierrachart.h"

float LRS(SCStudyInterfaceRef sc, SCFloatArrayRef Price, int Period, int i);


#define GREEN RGB(0,255,0)
#define DKGREEN RGB(0,128,0)
#define YELLOW RGB(255,255,0)
#define LTYELLOW RGB(255,255,128)
#define RED RGB(255,0,0)
#define DKRED RGB(198,0,0)
#define BLACK RGB(0,0,1)
#define WHITE RGB(255,255,255)
#define CYAN RGB(0,255,255)
#define PURPLE RGB(255,0,255)
#define GREY RGB(192,192,192)
#define BLUE RGB(0,128,255)
#define ORANGE RGB(255, 127, 0)


SCSFExport scsf_SVAPO(SCStudyInterfaceRef sc)
{

	SCSubgraphRef SVAPO = 			sc.Subgraph[0];
	SCSubgraphRef line0 = 			sc.Subgraph[1];
	SCSubgraphRef lineupper = 		sc.Subgraph[2];
	SCSubgraphRef linelower = 		sc.Subgraph[3];
	SCSubgraphRef haC = 			sc.Subgraph[4];
	SCSubgraphRef vtr = 			sc.Subgraph[5];

	SCInputRef INperiod = 			sc.Input[0];
	SCInputRef INmatype =			sc.Input[1];
	SCInputRef INcutoff =			sc.Input[2];
	SCInputRef INstdevper =			sc.Input[3];
	SCInputRef INdevH =				sc.Input[4];
	SCInputRef INdevL =				sc.Input[5];

	if (sc.SetDefaults)
	{
		// Stocks and Commodities November 2007 
		//http://www.traders.com/Documentation/FEEDbk_docs/Archive/112007/TradersTips/TradersTips.html#metastock  conversion

		sc.GraphName = "Short Term Volume and Price Oscillator";
		sc.StudyDescription = "Short Term Volume and Price Oscillator by ertrader";

		sc.DrawZeros = 0;
		sc.AutoLoop = 1;
		sc.GraphRegion = 1;
		sc.FreeDLL=0; // 1 = dll is freed up, this allows debugging. Change back to 0 when code is complete

		SVAPO.Name = "SVAPO";
		SVAPO.DrawStyle = DRAWSTYLE_LINE;
		SVAPO.PrimaryColor = BLUE;
		SVAPO.SecondaryColor = RED;
		SVAPO.LineWidth = 3;

		lineupper.Name = "Upper Line";
		lineupper.DrawStyle = DRAWSTYLE_LINE;
		lineupper.PrimaryColor = YELLOW;

		linelower.Name = "Lower Line";
		linelower.DrawStyle = DRAWSTYLE_LINE;
		linelower.PrimaryColor = YELLOW;

		line0.Name = "Zero Line";
		line0.DrawStyle = DRAWSTYLE_IGNORE;
		line0.PrimaryColor = YELLOW;

		INperiod.Name = "Period";
		INperiod.SetInt(8);
		INperiod.SetIntLimits(2,200);

		INmatype.Name = "Moving Average Type";
		INmatype.SetMovAvgType(MOVAVGTYPE_SIMPLE);

		INcutoff.Name = "Input Cutoff";
		INcutoff.SetFloat(0);
		INcutoff.SetFloatLimits(0,10);

		INstdevper.Name = "Standard Deviation Period";
		INstdevper.SetInt(100);
		INstdevper.SetIntLimits(1,200);		

		INdevH.Name = "Enter Standard Deviation High";
		INdevH.SetFloat(1.5f);
		INdevH.SetFloatLimits(.5f,5);	

		INdevL.Name = "Enter Standard Deviation Low";
		INdevL.SetFloat(1.3f);
		INdevL.SetFloatLimits(.5f,5);			


		return;
	}

	SCFloatArrayRef haO = 			sc.Subgraph[20].Arrays[0];
	SCFloatArrayRef haC1 = 			sc.Subgraph[20].Arrays[1];
	SCFloatArrayRef H = 			sc.Subgraph[20].Arrays[2];
	SCFloatArrayRef L = 			sc.Subgraph[20].Arrays[3];	
	SCFloatArrayRef C = 			sc.Subgraph[20].Arrays[4];
	SCFloatArrayRef O = 			sc.Subgraph[20].Arrays[5];
	SCFloatArrayRef V = 			sc.Subgraph[20].Arrays[6];	
	SCFloatArrayRef vave = 			sc.Subgraph[20].Arrays[7];
	SCFloatArrayRef vave1 = 		sc.Subgraph[21].Arrays[0];	
	SCFloatArrayRef vmax = 			sc.Subgraph[21].Arrays[1];
	SCFloatArrayRef vc = 			sc.Subgraph[21].Arrays[2];
	SCFloatArrayRef vc1 = 			sc.Subgraph[21].Arrays[3];
	SCFloatArrayRef vcsum = 		sc.Subgraph[21].Arrays[4];	
	SCFloatArrayRef LinRS = 		sc.Subgraph[21].Arrays[5];
	SCFloatArrayRef vcsumv = 		sc.Subgraph[21].Arrays[6];
	SCFloatArrayRef stdev = 		sc.Subgraph[21].Arrays[7];
	SCFloatArrayRef AvgPrice= 		sc.Subgraph[22].Arrays[0];		

	int period = 					INperiod.GetInt();
	int stdevper = 					INstdevper.GetInt();
	int i;
	float cutoff = 					INcutoff.GetFloat();
	float devH = 					INdevH.GetFloat();
	float devL = 					INdevL.GetFloat();
	float haC2, haC3;

	unsigned long DFI  = 			INmatype.GetInputDataIndex(); 

	C = sc.Close;
	H = sc.High;
	L = sc.Low;	
	O = sc.Open;	
	V = sc.Volume;		

	sc.DataStartIndex = period;
	i = sc.Index;
	//calculate the heikin-ashi closing average haCl and get the input variables: Note: changed to more conventional heikin-ashi code seen in other code (Tradestation and AMIBroker)
	AvgPrice[i] = (O[i]+H[i]+L[i]+C[i])/4;
	haO[i] = (AvgPrice[i-1] + haO[i-1])/2;
	haC1[i] = ((O[i]+H[i]+L[i]+C[i])/4+haO[i]+max((O[i]+H[i]+L[i]+C[i])/4,max(H[i],haO[i]))+min((O[i]+H[i]+L[i]+C[i])/4,min(L[i],haO[i])))/4;

	sc.TEMA(haC1, haC, i, (int)(period/1.6f));

	sc.MovingAverage(V,vave1,DFI,i,period*5);

	//Medium term MA of Volume to limit extremes and division factor
	vave[i]=vave1[i-1];
	vmax[i] = 2*vave[i];

	if (V[i] < vmax[i])
	{vc[i] = V[i];}
	else
	{vc[i] = vmax[i];}

	//Basic volume trend
	// first get the linear regression slope
	LinRS[i] = LRS(sc,V,period,i);
	sc.TEMA(LinRS, vtr, i, period);

	//SVAPO result of price and volume
	// The following is the same as the Alert command in metastock.  It returns a 1 (or True) if the conditions below are met.
	// NOTE: The following code converts the Metastock Alert function.
	haC2 = (vtr[i] >= vtr[i-1]) || (vtr[i] >= vtr[i-2]) || (vtr[i-1] >= vtr[i-2]);
	haC3 = (vtr[i] > vtr[i-1]) || (vtr[i] > vtr[i-2]) || (vtr[i-1] > vtr[i-2]);

	if (haC[i] > (haC[i-1]*(1+cutoff/1000)) && (haC2)) vc1[i] = vc[i];	
	else if (haC[i] < (haC[i-1]*(1-cutoff/1000)) && (haC3)) vc1[i] = -vc[i];	
	else vc1[i]=0;

	sc.Summation(vc1, vcsum, i, period);

	vcsumv[i] = vcsum[i]/(vave[i]+1);

	// now calculate SVAPO. 
	// NOTE: TEMA results here are slightly different from Metastock: example: 5.4397 for SC and 5.43298 for Metastock.  The prior calculation
	// for vcsumv matches exactly.  There appears to be a slight difference in how SC and Metastock calculation TEMA.  The difference is negligible in my opionion.
	sc.TEMA(vcsumv, SVAPO, i, period);

	// Now calculation stdev to get the upper and lower values
	//NOTE: because of the small difference in TEMA above, stdev is slightly different too.
	sc.StdDeviation(SVAPO, stdev, i, stdevper);

	// Draw line 0
	line0[i] = 0.000000001f;
	// upper lines 
	lineupper[i] = devH*stdev[i];
	// lower line
	linelower[i] = -devL*stdev[i];
}

/*********************************************************************/

float LRS(SCStudyInterfaceRef sc, SCFloatArrayRef Price, int Period, int i)
{
	// Linear Regression Slope
	float X(0),Num1(0),Num2(0),SumBars(0);
	float SumSqrBars(0),SumY(0),Sum1(0),Sum2(0),Len=(float)Period, LRS(0);

	SumBars = Len*(Len-1)/2.0f;
	SumSqrBars = (Len-1)*Len*(2*Len-1)/6.0f;

	Sum1       = 0;
	for(int i1=i; i1 > (i-Len);i1--)
	{
		int x =i-i1;
		Sum1= Sum1 + x*Price[i1];
		SumY += Price[i1];
	}

	Sum2 = SumBars * SumY;
	Num1 = Len*Sum1 - Sum2;
	Num2 = SumBars*SumBars - Len*SumSqrBars;
	LRS = (float)(Num1 / Num2);

	return LRS;
}

// converted from:
//http://www.traders.com/Documentation/FEEDbk_docs/Archive/112007/TradersTips/TradersTips.html#metastock
//calculate the heikin-ashi closing average haCl and get the input variables
// changed code {haO:= (Ref((O+H+L+C)/4,-1) + PREV)/2;} to the following for more conventional heikin-ashi without prev command - see AMIbroker code too.
//haO:=(Ref((O+H+L+C)/4,-1) + Ref((O+H+L+C)/4,-2))/2;
//haCl:= ((O+H+L+C)/4+haO+Max((O+H+L+C)/4,Max(H,haO))+Min((O+H+L+C)/4,Min(L,haO)))/4;
//period:= Input("SVAPO period :", 2, 20, 8);
//cutoff:= Input("Minimum % price change :", 0, 10, 1);

//Inputs for standard deviation bands
//devH:= Input("Standard Deviation High :", 0.1, 5, 1.5);
//devL:= Input("Standard Deviation Low :", 0.1, 5, 1.3);
//stdevper:= Input("Standard Deviation Period :", 1, 200, 100);

//Smooth HaCl closing price
//haC:= Tema(haCl, period/1.6;

//Medium term MA of Volume to limit extremes and division factor
//vave:= Ref(Mov(V, period*5, S), -1);
//vmax:= vave*2;
//vc:= If(V < vmax, V, vmax);

//Basic volume trend
//vtr:= Tema(LinRegSlope(V, period), period);

//SVAPO result of price and volume modified this portion of metastock code to better illustrate code flow
//haC2 := (vtr >= Ref(vtr,-1)) OR (vtr >= Ref(vtr,-2)) OR (Ref(vtr,-1) >= Ref(vtr,-2));
//haC3 := (vtr > Ref(vtr,-1)) OR (vtr > Ref(vtr,-2)) OR (Ref(vtr,-1) > Ref(vtr,-2));

//SVAPO:= Tema(Sum(If(haC > (Ref(haC, -1)*(1+cutoff/1000)) AND
//        (haC2), vc, If(haC < (Ref(haC, -1)*(1-cutoff/1000)) AND
//        (haC3), -vc, 0)), period)/(vave+1), period);
//devH*Stdev(SVAPO, stdevper);
//-devL*Stdev(SVAPO, stdevper);
//zeroref:=0;
//SVAPO


/***************************************************************/
SCSFExport scsf_RSI_Bands(SCStudyInterfaceRef sc)
{
	enum SubgraphIndexes
	{
		INDEX_UPRSI = 0,
		INDEX_DNRSI,
		INDEX_RSI,		
	};

	enum InputIndexes
	{
		INPUT_LENGTH=0,
		INPUT_MATYPE,
		INPUT_UPPER,
		INPUT_LOWER,
		INPUT_CLAMP,
		INPUT_CLAMPPERCENT,
		INPUT_CLAMP_YN,		
	};
	if (sc.SetDefaults)
	{

		sc.GraphName = "RSI Bands";
		sc.StudyDescription = "RSI Bands by ertrader";

		sc.DrawZeros = 0;
		sc.AutoLoop = 1;
		sc.GraphRegion = 0;
		sc.FreeDLL=0; 

		sc.Subgraph[INDEX_RSI].Name = "RSI Bands";
		sc.Subgraph[INDEX_RSI].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Subgraph[INDEX_RSI].PrimaryColor = BLUE;
		sc.Subgraph[INDEX_RSI].SecondaryColor = RED;
		sc.Subgraph[INDEX_RSI].LineWidth = 1;

		sc.Subgraph[INDEX_UPRSI].Name = "Up RSI Band";
		sc.Subgraph[INDEX_UPRSI].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[INDEX_UPRSI].PrimaryColor = YELLOW;
		sc.Subgraph[INDEX_UPRSI].LineWidth = 1;

		sc.Subgraph[INDEX_DNRSI].Name = "Down RSI Band";
		sc.Subgraph[INDEX_DNRSI].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[INDEX_DNRSI].PrimaryColor = YELLOW;
		sc.Subgraph[INDEX_DNRSI].LineWidth = 1;

		sc.Input[INPUT_LENGTH].Name = "Length";
		sc.Input[INPUT_LENGTH].SetInt(14);
		sc.Input[INPUT_LENGTH].SetIntLimits(2,200);

		sc.Input[INPUT_MATYPE].Name = "Moving Average Type";
		sc.Input[INPUT_MATYPE].SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);

		sc.Input[INPUT_UPPER].Name = "Input Upper";
		sc.Input[INPUT_UPPER].SetFloat(70.0f);
		sc.Input[INPUT_UPPER].SetFloatLimits(0,1000);

		sc.Input[INPUT_LOWER].Name = "Input Lower";
		sc.Input[INPUT_LOWER].SetFloat(30.0f);
		sc.Input[INPUT_LOWER].SetFloatLimits(0,1000);

		sc.Input[INPUT_CLAMP_YN].Name = "Clamp? 1=Yes, 0=No";
		sc.Input[INPUT_CLAMP_YN].SetInt(0);
		sc.Input[INPUT_CLAMP_YN].SetIntLimits(0,1);	

		sc.Input[INPUT_CLAMPPERCENT].Name = "Clamp Percent";
		sc.Input[INPUT_CLAMPPERCENT].SetInt(5);
		sc.Input[INPUT_CLAMPPERCENT].SetIntLimits(1,100);		

		return;
	}

	SCSubgraphRef rsi = 				sc.Subgraph[INDEX_RSI];
	SCSubgraphRef upRSI = 				sc.Subgraph[INDEX_UPRSI];
	SCSubgraphRef dnRSI = 				sc.Subgraph[INDEX_DNRSI];

	SCFloatArrayRef Close = 			sc.Close;
	SCFloatArrayRef P = 				sc.Subgraph[10].Arrays[0];
	SCFloatArrayRef S = 				sc.Subgraph[10].Arrays[1];
	SCFloatArrayRef N = 				sc.Subgraph[10].Arrays[2];	
	SCFloatArrayRef U = 				sc.Subgraph[10].Arrays[3];
	SCFloatArrayRef U1 = 				sc.Subgraph[10].Arrays[4];	
	SCFloatArrayRef D = 				sc.Subgraph[10].Arrays[5];		
	SCFloatArrayRef D1 = 				sc.Subgraph[10].Arrays[6];	
	SCFloatArrayRef avgU = 				sc.Subgraph[11].Arrays[0];
	SCFloatArrayRef avgD = 				sc.Subgraph[11].Arrays[1];
	SCFloatArrayRef avgU1 = 			sc.Subgraph[11].Arrays[2];
	SCFloatArrayRef avgD1 = 			sc.Subgraph[11].Arrays[3];
	SCFloatArrayRef upRSIr = 			sc.Subgraph[11].Arrays[4];
	SCFloatArrayRef dnRSIr = 			sc.Subgraph[11].Arrays[5];	
	SCFloatArrayRef upRSIc = 			sc.Subgraph[11].Arrays[6];
	SCFloatArrayRef dnRSIc = 			sc.Subgraph[11].Arrays[7];	

	int period = 						sc.Input[INPUT_LENGTH].GetInt();
	int clamp = 						sc.Input[INPUT_CLAMP_YN].GetInt();	
	int i, W1, L1;

	float upTgt = 						sc.Input[INPUT_UPPER].GetFloat();
	float dnTgt = 						sc.Input[INPUT_LOWER].GetFloat();
	float clamppct = 					sc.Input[INPUT_CLAMPPERCENT].GetFloat();	
	float upFact, dnFact;

	unsigned long DFI  = 				sc.Input[INPUT_MATYPE].GetInputDataIndex(); 	

	sc.DataStartIndex = period;
	i = sc.Index;

	U1[i] = Close[i] - Close[i-1];
	D1[i] = Close[i-1] - Close[i];
	W1 = period;
	L1 = 2 * W1 - 1;

	if (U1[i]>0) 
	{
		U[i] = U1[i];
	}
	else
	{
		U[i] = 0;
	}
	sc.MovingAverage(U,avgU,DFI,i,L1);

	if (D1[i]>=0) 
	{
		D[i] = D1[i];
	}
	else
	{
		D[i] = 0;
	}
	sc.MovingAverage(D,avgD,DFI,i,L1);

	rsi[i] = 100-(100/(1+(avgU[i]/avgD[i])));

	avgU1[i] = avgU[i-1];

	avgD1[i] = avgD[i-1];

	upFact = 100 / (100 - upTgt) - 1;

	dnFact = 100 / (100 - dnTgt) - 1;

	upRSIr[i] = Close[i-1] + (upFact*avgD1[i]*(period-1) - avgU1[i]*(period-1));

	dnRSIr[i] = Close[i-1] - (avgU1[i]*(period-1)/dnFact - avgD1[i]*(period-1));

	if (clamp == 0)
	{	
		upRSI[i]=upRSIr[i];
		dnRSI[i]=dnRSIr[i];	
	}
	else
	{
		upRSI[i] = max(min(upRSIr[i], Close[i-1]*(1+clamppct/100)),max(dnRSIr[i], Close[i-1]*(1-clamppct/100)));
		dnRSI[i] = min(max(dnRSIr[i], Close[i-1]*(1-clamppct/100)),min(upRSIr[i], Close[i-1]*(1+clamppct/100)));	
	}
}

/************************************************************************/
SCSFExport scsf_HourlyOpenLine2(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "Hourly Open Line 2";

		sc.StudyDescription = "New Hourly Open Line to use new function to calculate the open price";

		sc.AutoLoop = 0;

		//During development set this flag to 1, so the DLL can be modified. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;

		sc.Input[1].Name = "Line Color" ;
		sc.Input[1].SetColor(RGB(255,255,255));

		return;
	}


	// Do data processing


	s_UseTool Tool ;
	SCDateTime dt_StartTime, dt_EndTime ;
	int i_year, i_month, i_day, i_hour, i_minute, i_second ;
	float f_open, f_high, f_low, f_close, f_nextOpen ;

	// Break out the current time into it's component parts
	sc.BaseDateTimeIn[sc.ArraySize - 1].GetDateTimeYMDHMS( i_year, i_month, i_day, i_hour, i_minute, i_second ) ;

	// Build the start time to a specific hour
	dt_StartTime.SetDateTimeYMDHMS( i_year, i_month, i_day, i_hour, 0, 0 ) ;

	// Build the end time for the specific hour
	dt_EndTime.SetDateTimeYMDHMS( i_year, i_month, i_day, i_hour, 59, 59 ) ;

	// Get the values from the data
	sc.GetOHLCOfTimePeriod( dt_StartTime, dt_EndTime, f_open, f_high, f_low, f_close, f_nextOpen ) ;

	SCString log_message;

	log_message.Format("Open Price: %.3f", f_open ) ;

	sc.AddMessageToLog( log_message, 1 ) ;

	// Plot the Candle Heading
	Tool.Clear() ;
	Tool.ChartNumber = sc.ChartNumber ;
	Tool.DrawingType = DRAWING_LINE;
	Tool.LineNumber = 1039404905 ;
	Tool.BeginDateTime = sc.BaseDateTimeIn[ sc.ArraySize - 12 ];
	Tool.EndDateTime = sc.BaseDateTimeIn[sc.ArraySize - 1] ;
	Tool.BeginValue = f_open ;
	Tool.EndValue = f_open ;
	Tool.LineStyle = LINESTYLE_DASHDOT ;
	Tool.Color = sc.Input[1].GetColor();
	Tool.AddMethod = UTAM_ADD_OR_ADJUST ;

	sc.UseTool(Tool) ;

	Tool.Clear() ;
	Tool.ChartNumber = sc.ChartNumber ;
	Tool.DrawingType = DRAWING_TEXT;
	Tool.LineNumber = 1938495893 ;
	Tool.BeginDateTime = -1 ;
	Tool.BeginValue = f_open ;
	Tool.Text.Format( "%.2f Hourly", f_open ) ;
	Tool.Color = sc.Input[1].GetColor() ;
	Tool.TextAlignment = DT_VCENTER | DT_LEFT ;
	Tool.AddMethod = UTAM_ADD_OR_ADJUST ;

	sc.UseTool(Tool) ;
}

/************************************************************************/


SCSFExport scsf_VWAPwithSD(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{        
		sc.GraphName = "VwapBands";
		sc.GraphRegion = 0;
		sc.ScaleRangeType = SCALE_SAMEASREGION; //So it doesn't squish the chart

		sc.StudyDescription = "VwapBands";


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
	Vol[sc.Index] = sc.Volume[sc.Index];

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
/************************************************************************/


SCSFExport scsf_ColorLast(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "ColorLast";

		sc.StudyDescription = "";

		// during development set this flag to 1, so the dll can be modified. When development is done set it to 0 to improve performance.
		sc.FreeDLL = 0;

		sc.DrawZeros = 0;  // false
		sc.GraphRegion = 0;

		sc.Subgraph[0].Name = "Color";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[0].SecondaryColorUsed = 1;
		sc.Subgraph[0].LineWidth = 1;
		sc.Subgraph[0].PrimaryColor   = RGB(138,43,266);
		sc.Subgraph[0].SecondaryColor = RGB(0,0,255);

		sc.AutoLoop = 1;

		return;
	}

	// Do data processing

	// Array references
	SCFloatArrayRef High  = sc.BaseDataIn[SC_HIGH];
	SCFloatArrayRef Low   = sc.BaseDataIn[SC_LOW];
	SCFloatArrayRef Open = sc.BaseDataIn[SC_OPEN];
	SCFloatArrayRef Last  = sc.BaseDataIn[SC_LAST];
	SCFloatArrayRef Out  = sc.Subgraph[0].Data;


	if (Last[sc.Index] <= High[sc.Index - 1] && Last[sc.Index] >= Low[sc.Index - 1])

	{
		Out[sc.Index] = Last[sc.Index];
		sc.Subgraph[0].DataColor[sc.Index] = sc.Subgraph[0].PrimaryColor;
	}
	else
		Out[sc.Index] = 0;


}

/*----------------------------------------------------------------------*/
SCSFExport scsf_GBSlopeTwoRatio_New(SCStudyInterfaceRef sc)
{
	SCSubgraphRef UpUp = sc.Subgraph[0];
	SCSubgraphRef Up = sc.Subgraph[1];
	SCSubgraphRef Dn = sc.Subgraph[2];
	SCSubgraphRef DnDn = sc.Subgraph[3];
	SCSubgraphRef Slow = sc.Subgraph[4];

	SCInputRef Unused0 = sc.Input[0];
	SCInputRef Unused1 = sc.Input[1];
	SCInputRef BarsForAngle = sc.Input[2];
	SCInputRef PriceChangeForSteeper = sc.Input[3];
	SCInputRef PriceChangeForShallow = sc.Input[4];
	SCInputRef EmaLength = sc.Input[5];
	SCInputRef StudyNumberUsed = sc.Input[6];
	SCInputRef FixedValue_1000 = sc.Input[7];

	if (sc.SetDefaults)
	{
		sc.GraphName = "Slope of MA34 (two stage)";

		UpUp.Name="UpUp";

		Up.Name="Up";
		Up.DrawStyle = DRAWSTYLE_IGNORE;

		Dn.Name="Dn";
		Dn.DrawStyle = DRAWSTYLE_IGNORE;

		DnDn.Name="DnDn";
		DnDn.DrawStyle = DRAWSTYLE_IGNORE;

		Slow.Name="Slow";
		Slow.DrawStyle = DRAWSTYLE_IGNORE;

		BarsForAngle.Name = "Bars for Angle";
		BarsForAngle.SetInt(4);

		PriceChangeForSteeper.Name = "Price change for Steeper Angle";
		PriceChangeForSteeper.SetFloat(0.000001f);

		PriceChangeForShallow.Name = "Price change for Shallow Angle";

		EmaLength.Name = "EMA Length";
		EmaLength.SetFloat(34.0f);

		StudyNumberUsed.Name = "Study Number used instead of Price if non-zero (uses G1)";

		FixedValue_1000.Name = "Fixed Value/1000";

		return;
	}

	if(sc.ArraySize < 100)
		return;



	sc.DataStartIndex = 50;

	int start= max(sc.UpdateStartIndex, sc.DataStartIndex - 1);

	SCFloatArray StudyArray;
	int UseStudyArray = 0;
	if(StudyNumberUsed.GetInt() >= 1) 
	{ 
		sc.GetStudyArray(StudyNumberUsed.GetInt(), 1, StudyArray); 
		if(StudyArray.GetArraySize() != 0) 
			UseStudyArray = 1;
	}

	if(sc.UpdateStartIndex == 0) 
	{
		for (int i = 0; i < 100; i++)
		{    
			Slow[i] = sc.Close[i];  
			UpUp[i] = sc.Close[i]; 
		}
	}

	for (int pos = start; pos < sc.ArraySize; pos++)
	{
		if(UseStudyArray == 1)
		{ 
			Slow[pos] = (1 - (2 / (EmaLength.GetFloat() + 1))) * Slow[pos - 1] + 
				(2 / (EmaLength.GetFloat() + 1)) * StudyArray[pos]; 
		} 
		else 
		{ 
			Slow[pos] = (1 - (2 / (EmaLength.GetFloat() + 1))) * Slow[pos - 1] +
				(2 / (EmaLength.GetFloat() + 1)) * sc.Close[pos]; 
		}

		if (FixedValue_1000.GetFloat() == 0.0f)
			UpUp[pos] = Slow[pos];
		else
			UpUp[pos] = FixedValue_1000.GetFloat() / 1000.0f;

		if (Slow[pos] - Slow[pos - BarsForAngle.GetInt()] >= PriceChangeForSteeper.GetFloat())
			UpUp.DataColor[pos] = UpUp.PrimaryColor; 
		else if (Slow[pos] - Slow[pos - BarsForAngle.GetInt()] >= PriceChangeForShallow.GetFloat())
			UpUp.DataColor[pos] = Up.PrimaryColor; 
		else if (Slow[pos] - Slow[pos - BarsForAngle.GetInt()] <= - PriceChangeForSteeper.GetFloat())
			UpUp.DataColor[pos] = DnDn.PrimaryColor; 
		else if (Slow[pos] - Slow[pos - BarsForAngle.GetInt()]<= - PriceChangeForShallow.GetFloat())
			UpUp.DataColor[pos] = Dn.PrimaryColor; 
		else
			UpUp.DataColor[pos] = Slow.PrimaryColor;
	}
}

/***********************************************************************/
SCSFExport scsf_WattsMACD(SCStudyInterfaceRef sc)
{
	if(sc.SetDefaults)
	{
		sc.GraphName="WattsMACD";
		sc.StudyDescription="Watts MACD";
		sc.Subgraph[0].Name="MACD Hist";
		sc.Subgraph[1].Name="SMA";
		sc.Subgraph[2].Name="Signal";
		sc.Subgraph[3].Name="Ref Line";
		sc.Input[2].Name="EMA (yes) or Weighted MA";

		sc.Input[2].SetYesNo(false);

		sc.Input[3].Name="Fast MA Length";
		sc.Input[3].SetFloat(12);

		sc.Input[4].Name="Slow MA Length";
		sc.Input[4].SetFloat(26);

		sc.Input[5].Name="MACD's MA Length";
		sc.Input[5].SetFloat(9);

		sc.Input[6].Name="Ref Line Level";
		sc.Input[6].SetFloat(0);

		sc.Input[7].Name="SMA Length";
		sc.Input[7].SetFloat(5);


		sc.Subgraph[0].SecondaryColorUsed = 1;
		sc.Subgraph[2].SecondaryColorUsed = 1;

		sc.DrawZeros=1;

		sc.FreeDLL=0; 

		return;
	}

	int    c,pos,spoint;
	float  sum3=0,sum4=0,sum5=0,high=0,low=99999,
		factor1,factor2,factor3,csum3,csum4,csum5;


	if(sc.Input[2].BooleanValue)
	{	
		factor1 = 2/(sc.Input[3].FloatValue+1);	factor2 = 2/(sc.Input[4].FloatValue+1);	factor3 = 2/(sc.Input[5].FloatValue+1);
	} 
	else
	{   
		csum3=(sc.Input[3].FloatValue*(sc.Input[3].FloatValue+1))/2;	csum4=(sc.Input[4].FloatValue*(sc.Input[4].FloatValue+1))/2;	csum5=(sc.Input[5].FloatValue*(sc.Input[5].FloatValue+1))/2;
	}


	sc.DataStartIndex=(int)(sc.Input[3].FloatValue+sc.Input[4].FloatValue);
	sc.Subgraph[6].Data[0] = sc.BaseDataIn[3][0];  sc.Subgraph[7].Data[0] = sc.BaseDataIn[3][0];
	sc.Subgraph[5].Data[0] = 0;
	spoint=(int)sc.Input[4].FloatValue;
	int start = max(sc.UpdateStartIndex, spoint);
	for (pos=start; pos < sc.ArraySize; pos++)
	{
		if(sc.Input[2].BooleanValue)
		{
			sc.Subgraph[6].Data[pos] = ((1-factor1)*sc.Subgraph[6].Data[pos-1]) + (factor1*sc.BaseDataIn[3][pos]);
			sc.Subgraph[7].Data[pos] = ((1-factor2)*sc.Subgraph[7].Data[pos-1]) + (factor2*sc.BaseDataIn[3][pos]);
			sc.Subgraph[4].Data[pos] = sc.Subgraph[6].Data[pos] - sc.Subgraph[7].Data[pos];
			sc.Subgraph[5].Data[pos] = ((1-factor3)*sc.Subgraph[5].Data[pos-1]) + (factor3*sc.Subgraph[4].Data[pos]);

			sc.Subgraph[0].Data[pos] = sc.Subgraph[4].Data[pos] - sc.Subgraph[5].Data[pos];
			sc.Subgraph[3].Data[pos] = sc.Input[6].FloatValue;
			if ( sc.Subgraph[0].Data[pos]>=0) sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].PrimaryColor; else sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].SecondaryColor; 

			sc.Subgraph[8].Data[pos] = sc.Subgraph[8].Data[pos-1] + sc.Subgraph[0].Data[pos];
			sc.Subgraph[1].Data[pos] = sc.Subgraph[8].Data[pos] / sc.Input[7].FloatValue;
			if(pos>=1+sc.Input[7].FloatValue-1) {sc.Subgraph[8].Data[pos] = sc.Subgraph[8].Data[pos] - sc.Subgraph[0].Data[pos-(int)sc.Input[7].FloatValue+1];};
		} else
		{
			sum3=0;
			for(c=0; c<=(sc.Input[3].FloatValue-1); c++) { sum3=sum3+sc.BaseDataIn[3][pos-c]*(sc.Input[3].FloatValue-c);};
			sum3=sum3/csum3;
			sum4=0;
			for(c=0; c<=(sc.Input[4].FloatValue-1); c++) { sum4=sum4+sc.BaseDataIn[3][pos-c]*(sc.Input[4].FloatValue-c);};
			sum4=sum4/csum4;
			sc.Subgraph[7].Data[pos] = sum3 - sum4;
			sum5=0;
			for(c=0; c<=(sc.Input[5].FloatValue-1); c++) { sum5=sum5+sc.Subgraph[7].Data[pos-c]*(sc.Input[5].FloatValue-c);};
			sum5=sum5/csum5;
			sc.Subgraph[0].Data[pos] = sc.Subgraph[7].Data[pos] - sum5;

			sc.Subgraph[3].Data[pos] = sc.Input[6].FloatValue;
			if ( sc.Subgraph[0].Data[pos]>=0) sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].PrimaryColor; else sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].SecondaryColor; 

			sc.Subgraph[6].Data[pos] = sc.Subgraph[6].Data[pos-1] + sc.Subgraph[0].Data[pos];
			sc.Subgraph[1].Data[pos] = sc.Subgraph[6].Data[pos] / sc.Input[7].FloatValue;
			if(pos>=spoint+sc.Input[7].FloatValue-1) {sc.Subgraph[6].Data[pos] = sc.Subgraph[6].Data[pos] - sc.Subgraph[0].Data[pos-(int)sc.Input[7].FloatValue+1];};

		};


		sc.Subgraph[2].Data[pos] = sc.Subgraph[0].Data[pos];
		if ( sc.Subgraph[2].Data[pos]>sc.Subgraph[2].Data[pos-1] && sc.Subgraph[2].Data[pos]>sc.Subgraph[1].Data[pos]) sc.Subgraph[2].DataColor[pos] = sc.Subgraph[2].PrimaryColor; else 
			if( sc.Subgraph[2].Data[pos]<sc.Subgraph[2].Data[pos-1] && sc.Subgraph[2].Data[pos]<sc.Subgraph[1].Data[pos]) sc.Subgraph[2].DataColor[pos] = sc.Subgraph[2].SecondaryColor; else  
				sc.Subgraph[2].DataColor[pos] = sc.Subgraph[1].PrimaryColor;

	}
};


/***********************************************************************/



#define EPSILON 0.000001
#define GREEN_BOX 1
#define RED_BOX -1
#define RK_OPEN SC_OPEN						// 0
#define RK_HIGH SC_HIGH						// 1
#define RK_LOW SC_LOW						// 2
#define RK_LAST SC_LAST						// 3
#define RK_VOLUME SC_VOLUME					// 4
#define RK_BOXSIZE SC_OI					// 5
#define RK_OHLC SC_OHLC						// 6
#define RK_HLC SC_HLC						// 7
#define RK_HL SC_HL							// 8 
#define RK_RCLOSE SC_BIDVOL					// 9
#define RK_OCR SC_UPVOL						// 11
#define RK_OC SC_DOWNVOL					// 12
#define RK_COLORCNT SC_BIDNT				// 13
#define RK_COLOR SC_ASKNT					// 14


// round double n to d decimal places
inline double fround(double n, int d)
{
	return floor(n * pow(10.0, d) + 0.5) / pow(10.0, d);
}

/******************************************************
* A version of the renko chart study for Sierra Chart.*
* By Sock 2009  									  *
* windysock@gmail.com                                 *
******************************************************/
SCSFExport scsf_SockRenkoChart(SCStudyInterfaceRef sc)
{
	SCFloatArrayRef InOpen = sc.Open;
	SCFloatArrayRef InHigh = sc.High;
	SCFloatArrayRef InLow = sc.Low;
	SCFloatArrayRef InClose = sc.Close;
	SCFloatArrayRef InVolume = sc.Volume;
	SCSubgraphRef OutOpen = sc.Subgraph[RK_OPEN]; 				
	SCSubgraphRef OutHigh = sc.Subgraph[RK_HIGH]; 				
	SCSubgraphRef OutLow = sc.Subgraph[RK_LOW]; 			
	SCSubgraphRef OutClose = sc.Subgraph[RK_LAST]; 			
	SCSubgraphRef OutVolume = sc.Subgraph[RK_VOLUME]; 		
	SCSubgraphRef OutBoxSize = sc.Subgraph[RK_BOXSIZE]; 	
	SCSubgraphRef OutOCR = sc.Subgraph[RK_OCR]; 			
	SCSubgraphRef OutOC = sc.Subgraph[RK_OC]; 			
	SCSubgraphRef OutColorCount = sc.Subgraph[RK_COLORCNT];
	SCSubgraphRef OutColor = sc.Subgraph[RK_COLOR];
	SCSubgraphRef OutRenkoClose = sc.Subgraph[RK_RCLOSE];
	SCSubgraphRef OutHL = sc.Subgraph[RK_HL];
	SCSubgraphRef OutHLC = sc.Subgraph[RK_HLC];
	SCSubgraphRef OutOHLC = sc.Subgraph[RK_OHLC];

	// Set configuration variables

	if (sc.SetDefaults)
	{
		// Set the defaults	
		sc.GraphName = "Sock Renko Chart";
		sc.StudyDescription = "Renko chart study by Sock. Comments to windysock@gmail.com";
		sc.IsCustomChart = 1;	
		sc.GraphRegion = 0; 		
		sc.DrawZeros = 0;  
		sc.GraphDrawType = GDT_CANDLESTICK_BODY_ONLY;
		sc.StandardChartHeader = 1;
		sc.AutoLoop = 0;
		sc.FreeDLL = 0;

		// Subgraphs		
		OutOpen.Name = "Open";
		OutOpen.PrimaryColor = COLOR_GREEN;
		OutHigh.Name = "High";
		OutHigh.PrimaryColor = COLOR_GREEN;
		OutLow.Name = "Low";
		OutLow.PrimaryColor = COLOR_RED;
		OutClose.Name = "Close";
		OutClose.PrimaryColor = COLOR_RED;
		OutVolume.Name = "Volume";
		OutRenkoClose.Name = "R-Renko Close";
		OutBoxSize.Name = "Box Size";
		OutOCR.Name = "OCR Avg";
		OutOC.Name = "OC Avg";
		OutColorCount.Name = "Same colour box count";
		OutColor.Name = "Box colour";
		OutHL.Name = "HL Avg";
		OutHLC.Name = "HLC Avg";
		OutOHLC.Name = "OHLC Avg";
		// Inputs		
		sc.Input[0].Name = "Fixed box size";
		sc.Input[0].SetFloat(1.0f);
		sc.Input[1].Name = "Start chart on multiples of:";
		sc.Input[1].SetFloat(1.0f);
		sc.Input[2].Name = "Display wicks & tails:";
		sc.Input[2].SetYesNo(0);
		sc.Input[3].Name = "Set box size using ATR from another chart?:";
		sc.Input[3].SetYesNo(0);
		sc.Input[4].Name = "ATR chart number:";
		sc.Input[4].SetInt(0);
		sc.Input[5].Name = "ATR study number:";
		sc.Input[5].SetInt(0);
		sc.Input[6].Name = "ATR subgraph number:";
		sc.Input[6].SetInt(0);
		sc.Input[7].Name = "ATR multiplier:";
		sc.Input[7].SetFloat(1.0f);
		sc.Input[8].Name = "Round ATR to nearest:";
		sc.Input[8].SetFloat(1.0f);

		return;
	}
	try {

		long i = 0;		// input index - underlying bar chart
		long o = 0;		// output index - renko chart
		long OtherIndex = 0;  // other chart study index
		if (sc.BaseGraphValueFormat > 6) {
			throw "Set Price Display Format to decimals, not fractions";
		}
		int d = sc.BaseGraphValueFormat == 0 ? 1 : sc.BaseGraphValueFormat; // Decimal places - min = 1
		sc.ValueFormat = sc.BaseGraphValueFormat;
		int Volume, m, n, PrevBoxColor, NewBoxColor;
		OperatorEnum cond;
		double limit, HighLimit, LowLimit;
		SCFloatArray OtherArray;
		// Input vars
		float  BoxSize = sc.Input[0].GetFloat();
		float ChartMulti = sc.Input[1].GetFloat();
		sc.GraphDrawType = sc.Input[2].GetYesNo() ? GDT_CANDLESTICK:GDT_CANDLESTICK_BODY_ONLY;
		int UseDynamicBoxSize = sc.Input[3].GetYesNo();
		int ChartNum = sc.Input[4].GetInt();
		int StudyNum = sc.Input[5].GetInt();
		int SubgraphNum = sc.Input[6].GetInt();
		float StudyMulti = sc.Input[7].GetFloat();
		float RoundTo = sc.Input[8].GetFloat();

		// Initial load
		if (sc.UpdateStartIndex == 0) {
			sc.ResizeArrays(0);
			// Add 2 boxes, 1st is anchor box to start the chart, 2nd is the current box.
			sc.AddElements(2);
			sc.DateTimeOut[1] = sc.DateTimeOut[0] = sc.BaseDateTimeIn[0];  
			OutOpen[1] = OutOpen[0] = (sc.RoundToTickSize(InOpen[0], ChartMulti*10))+ChartMulti; // Start chart on input multiple 
			OutHigh[1] = OutHigh[0] = OutOpen[0];
			OutLow[1] = OutLow[0] = OutOpen[0];
			OutClose[1] = OutClose[0] = OutOpen[0];
		}

		o = sc.OutArraySize - 1;
		// Get array from other chart if using dynamic box sizing
		if (UseDynamicBoxSize) {
			sc.GetStudyArrayFromChart(ChartNum, StudyNum, SubgraphNum, OtherArray);
			if (OtherArray.GetArraySize() == 0)	{
				throw "Error accessing ATR study on other chart, check inputs and retry";
			}
		}
		// Draw the renko chart
		for (i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
		{
			PrevBoxColor = OutClose[o-1] >= OutOpen[o-1] ? GREEN_BOX:RED_BOX;

			if (UseDynamicBoxSize) {
				OtherIndex = sc.GetNearestMatchForDateTimeIndex(ChartNum, i);
				if (OtherIndex == 0) {
					throw "Other chart start date/time must be before current chart start";
				}
				BoxSize = OtherArray[OtherIndex]*StudyMulti;
				BoxSize = sc.RoundToTickSize(BoxSize, RoundTo);
				if (BoxSize <= 0.0) {
					throw "Invalid box size detected, check other chart settings and retry ";
				}
			}

			// Update current box with input bar data
			sc.DateTimeOut[o] = sc.BaseDateTimeIn[i];
			OutOpen[o] = InClose[i];
			OutClose[o] = InClose[i];
			OutColor[o] = 0;
			OutHigh[o] = InHigh[i] > OutHigh[o] ? InHigh[i] : OutHigh[o];
			if (OutLow[o] <= 0.0 || InLow[i] < OutLow[o]) {
				OutLow[o] = InLow[i];
			}
			if (InClose[i] > OutClose[o-1] && InClose[i] > OutOpen[o-1]) {
				OutOpen[o] = PrevBoxColor==GREEN_BOX ? OutClose[o-1] : OutOpen[o-1];
				OutColor[o] = GREEN_BOX; 
			}
			else if (InClose[i] < OutClose[o-1] && InClose[i] < OutOpen[o-1]) {
				OutOpen[o] = PrevBoxColor==RED_BOX ? OutClose[o-1] : OutOpen[o-1];
				OutColor[o] = RED_BOX; 
			}
			OutVolume[o] += InVolume[i]; 
			OutBoxSize[o] = BoxSize;
			OutRenkoClose[o] = InClose[i];
			OutOCR[o] = (OutOpen[o]+OutClose[o]+OutRenkoClose[o])/3.0f;
			OutOC[o] = (OutOpen[o]+OutClose[o])/2.0f;
			OutHL[o] = (OutHigh[o]+OutLow[o])/2.0f;
			OutHLC[o] = (OutHigh[o]+OutLow[o]+OutClose[o])/3.0f;
			OutOHLC[o] = (OutOpen[o]+OutHigh[o]+OutLow[o]+OutClose[o])/4.0f;
			OutColorCount[o] = OutColor[o-1]==OutColor[o] ? OutColorCount[o-1]+1.0f:1.0f;

			// If the input bar has closed check if new renko box(es) can be added
			if (i < sc.ArraySize-1) {
				if (PrevBoxColor == GREEN_BOX) {
					HighLimit = OutClose[o-1] + BoxSize;
					LowLimit = OutOpen[o-1] - BoxSize;
				}
				else {
					HighLimit = OutOpen[o-1] + BoxSize;
					LowLimit = OutClose[o-1] - BoxSize;
				}
				NewBoxColor = 0;
				if (sc.FormattedEvaluate((double)InClose[i],d,GREATER_EQUAL_OPERATOR,HighLimit,d)) {
					NewBoxColor = GREEN_BOX;
					cond = GREATER_EQUAL_OPERATOR;
					limit = HighLimit;
				}
				else if (sc.FormattedEvaluate((double)InClose[i],d,LESS_EQUAL_OPERATOR,LowLimit,d)) {
					NewBoxColor = RED_BOX;
					cond = LESS_EQUAL_OPERATOR;
					limit = LowLimit;
				}
				if (NewBoxColor != 0) {
					n = 0; // init box count
					do {								// keep adding boxes until limit reached
						if (NewBoxColor == GREEN_BOX) { 
							OutClose[o+n] = (float)fround(OutOpen[o+n]+BoxSize, d);
							limit += BoxSize;
						}
						else {
							OutClose[o+n] = (float)fround(OutOpen[o+n]-BoxSize, d);
							limit -= BoxSize;
						}
						sc.DateTimeOut[o+n] = sc.DateTimeOut[o];
						OutHigh[o+n] = OutHigh[o];
						OutLow[o+n] = OutLow[o];
						OutBoxSize[o+n] = BoxSize;
						OutRenkoClose[o+n] = InClose[i];
						OutOCR[o+n] = (OutOpen[o+n]+OutClose[o+n]+OutRenkoClose[o+n])/3.0f;
						OutOC[o+n] = (OutOpen[o+n]+OutClose[o+n])/2.0f;
						OutHL[o+n] = (OutHigh[o+n]+OutLow[o+n])/2.0f;
						OutHLC[o+n] = (OutHigh[o+n]+OutLow[o+n]+OutClose[o+n])/3.0f;
						OutOHLC[o+n] = (OutOpen[o+n]+OutHigh[o+n]+OutLow[o+n]+OutClose[o+n])/4.0f;
						OutColor[o+n] = (float)NewBoxColor;
						OutColorCount[o+n] = OutColor[(o+n)-1]==OutColor[o+n] ? OutColorCount[(o+n)-1]+1.0f:1.0f;
						sc.AddElements(1);
						OutOpen[(o+n)+1] = OutClose[o+n];  // Set next open, on last iter this is open of new current box
						n++;  // incr box count
					} while (sc.FormattedEvaluate((double)InClose[i],d, cond, limit,d));

					Volume = int(OutVolume[o]/n);
					for (m = 0; m < n; m++) {
						OutVolume[o+m] = (float)Volume;
					}
				}
				// All done adding boxes, now set initial values for the new current box
				o = sc.OutArraySize - 1;
				OutClose[o] = OutOpen[o];
				sc.DateTimeOut[o] = sc.BaseDateTimeIn[i]+sc.SecondsPerBar;
			}
		}	
		return;
	}
	catch (char *ErrMsg){
		sc.AddMessageToLog(ErrMsg, 1);
	}
}		

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SCSFExport scsf_BMS(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName="Blau Midprice Stochastic";
		sc.Subgraph[0].Name="K";
		sc.Subgraph[1].Name="D";
		sc.Subgraph[2].Name="Line 1";
		sc.Subgraph[3].Name="Line 2";

		sc.Input[2].Name="L";
		sc.Input[2].SetInt(7);

		sc.Input[3].Name="K";
		sc.Input[3].SetFloat(3);

		sc.Input[4].Name="D";
		sc.Input[4].SetFloat(3.0);

		sc.Input[5].Name="Line 1 Value";
		sc.Input[6].Name="Line 2 Value";


		return;	

	}


	// Do data processing

	int    pos,c,L=sc.Input[2].GetInt();
	float  range,avg, h, l, sk, sk1, sd, sd1, fk, factork, factord,K=sc.Input[3].GetFloat(),D=sc.Input[4].GetFloat(),sumk,sumd;




	fk= sc.Close[9]; sk=fk; sd=fk;
	factork=2/(K+1); factord=2/(D+2);


	sc.DataStartIndex=50;  sumk=0; sumd=0;

	for (pos=50,c=1; pos < sc.ArraySize; pos++,c++)
	{
		h=0; l=9999999;
		for(int i=0;i<L;i++)
		{if(h<sc.High[pos-i]) h=sc.High[pos-i];
		if(l>sc.Low[pos-i]) l=sc.Low[pos-i];
		}
		range=(h-l);
		avg=  (h+l)/2;
		if(range>0) fk=100*(sc.Close[pos]-avg)/range; else fk=0;
		sk1=sk; sd1=sd;
		sk=factork*fk + (1-factork)*sk1; sd=factord*sk + (1-factord)*sd1;

		sc.Subgraph[0].Data[pos] = sk;
		sc.Subgraph[1].Data[pos] = sd;
		sc.Subgraph[2].Data[pos] = sc.Input[5].FloatValue;
		sc.Subgraph[3].Data[pos] = sc.Input[6].FloatValue;
	}
}

/************************************************************************/

SCSFExport scsf_VSANDNS(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "VSA No Demand/Supply";
		sc.GraphRegion = 0;

		sc.Subgraph[0].Name = "No Demand";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[0].PrimaryColor = RGB(255,0,0);  //red
		sc.Subgraph[1].Name = "No Supply";
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[1].PrimaryColor = RGB(0,255,0);  // green

		sc.AutoLoop = 1;
		sc.FreeDLL = 0;

		return;
	}

	bool vol1 = ((sc.BaseDataIn[SC_VOLUME][sc.Index]<sc.BaseDataIn[SC_VOLUME][sc.Index -1])&&(sc.BaseDataIn[SC_VOLUME][sc.Index]<sc.BaseDataIn[SC_VOLUME][sc.Index -2])); 
	bool ndman = (sc.BaseDataIn[SC_LAST][sc.Index]>sc.BaseDataIn[SC_LAST][sc.Index -1]);
	bool nsply = (sc.BaseDataIn[SC_LAST][sc.Index]<sc.BaseDataIn[SC_LAST][sc.Index -1]);

	sc.Subgraph[0][sc.Index] = 0;
	sc.Subgraph[1][sc.Index] = 0;

	if (vol1 && ndman)
	{
		sc.Subgraph[0][sc.Index] = 1;
		sc.Subgraph[0].DataColor[sc.Index] = sc.Subgraph[0].PrimaryColor;
	}

	else if (vol1 && nsply)
	{
		sc.Subgraph[1][sc.Index] = 1;
		sc.Subgraph[1].DataColor[sc.Index] = sc.Subgraph[1].PrimaryColor;
	}

}
////////////////////////////////////////////////////////////////////////////////////////
SCSFExport scsf_VSANDNS2(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "VSA No Demand/Supply Colorbar 2010";
		sc.GraphRegion = 0;

		sc.Subgraph[0].Name = "No Demand";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[0].PrimaryColor = RGB(255,0,0);  
		sc.Subgraph[1].Name = "No Supply";
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[1].PrimaryColor = RGB(0,255,0);  
		sc.Subgraph[2].Name = "Close";
		sc.Subgraph[2].DrawStyle = DRAWSTYLE_DASH;
		sc.Subgraph[2].PrimaryColor = RGB(0,0,0); 

		sc.Input[0].Name = "Enable Alert Sound"; 
		sc.Input[0].SetYesNo(1); 
		sc.Input[1].Name = "No Supply Alert #1-50";
		sc.Input[1].SetInt(1);
		sc.Input[1].SetIntLimits(1,50);
		sc.Input[2].Name = "No Demand Alert #1-50";
		sc.Input[2].SetInt(2);
		sc.Input[2].SetIntLimits(1,50);

		sc.AutoLoop = 1;
		sc.AlertOnlyOncePerBar = true;
		sc.FreeDLL = 0;

		return;
	}
	float vol1 = sc.BaseDataIn[SC_VOLUME][sc.Index-1];
	float vol2 = sc.BaseDataIn[SC_VOLUME][sc.Index-2];
	float vol3 = sc.BaseDataIn[SC_VOLUME][sc.Index-3];
	float high1 = sc.BaseDataIn[SC_HIGH][sc.Index-1];
	float high2 = sc.BaseDataIn[SC_HIGH][sc.Index-2];
	float high3 = sc.BaseDataIn[SC_HIGH][sc.Index-3];
	float low1 = sc.BaseDataIn[SC_LOW][sc.Index-1];
	float low2 = sc.BaseDataIn[SC_LOW][sc.Index-2];
	float low3 = sc.BaseDataIn[SC_LOW][sc.Index-3];
	float range1 = (high1-low1);
	float range2 = (high2-low2);
	float range3 = (high3-low3);
	float close1 = sc.BaseDataIn[SC_LAST][sc.Index-1];
	int nodemand = sc.Input[2].GetInt();
	int nosupply = sc.Input[1].GetInt();

	bool higherh = ((high1>high2)&&(high1>high3));
	bool lowerl = ((low1<low2)&&(low1<low3));
	bool volrange = ((vol1<vol2)&&(vol1<vol3)&&((range1<range2)||(range1<range3)));

	sc.Subgraph[0][sc.Index] = 0;
	sc.Subgraph[1][sc.Index] = 0;
	sc.Subgraph[2][sc.Index] = 0;

	if (higherh)
	{
		if (volrange)
		{
			sc.Subgraph[0][sc.Index-1] = 1;
			sc.Subgraph[0].DataColor[sc.Index-1] = sc.Subgraph[0].PrimaryColor;
			sc.Subgraph[2][sc.Index-1] = close1;
			sc.Subgraph[2].DataColor[sc.Index-1] = sc.Subgraph[2].PrimaryColor;
			if (sc.Input[0].GetYesNo())
			{
				sc.SetAlert(nodemand);
			}
		}
	}
	else if (lowerl)
	{	
		if (volrange)
		{
			sc.Subgraph[1][sc.Index-1] = 1;
			sc.Subgraph[1].DataColor[sc.Index-1] = sc.Subgraph[1].PrimaryColor;
			sc.Subgraph[2][sc.Index-1] = close1;
			sc.Subgraph[2].DataColor[sc.Index-1] = sc.Subgraph[2].PrimaryColor;
			if (sc.Input[0].GetYesNo())
			{
				sc.SetAlert(nosupply);
			}
		}
	}

}
/************************************************************************/

SCSFExport scsf_WideRangeBar(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{

		sc.GraphName = "Wide Range Bar";
		sc.StudyDescription = "Wide Range Bar";
		sc.FreeDLL = 0;

		sc.DrawZeros = 0; // false
		sc.GraphRegion = 0;

		sc.Subgraph[0].Name = "WRB";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[0].LineWidth = 1;
		sc.Subgraph[0].PrimaryColor = RGB(255,128,0);
		sc.AutoLoop = 1;

		return;
	}

	SCFloatArrayRef High = sc.BaseDataIn[SC_HIGH];
	SCFloatArrayRef Low = sc.BaseDataIn[SC_LOW];
	SCFloatArrayRef Out = sc.Subgraph[0].Data;


	if ((High[sc.Index]-Low[sc.Index])>(High[sc.Index - 1]-Low[sc.Index - 1])&&(High[sc.Index]-Low[sc.Index])>(High[sc.Index - 2]-Low[sc.Index - 2])&&(High[sc.Index]-Low[sc.Index])>(High[sc.Index -3]-Low[sc.Index -3])&&(High[sc.Index]-Low[sc.Index])>(High[sc.Index -4] - Low[sc.Index -4])&&(High[sc.Index]-Low[sc.Index])>(High[sc.Index -5]-Low[sc.Index -5])&&(High[sc.Index] - Low[sc.Index])>(High[sc.Index -6] - Low[sc.Index -6])&&(High[sc.Index] - Low[sc.Index])>(High[sc.Index -7]-Low[sc.Index -7]))
		Out[sc.Index] = High[sc.Index];
	else
		Out[sc.Index] = 0;

} 
/************************************************************************/

SCSFExport scsf_VolumeHHH(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "volumeHHH";

		sc.StudyDescription = "This study function mark a vol bar if it is higher than prior 2 bars.";

		sc.GraphRegion = 2;

		sc.Subgraph[0].Name = "Volume Color Bar";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[0].SecondaryColorUsed = 1;  // true
		sc.Subgraph[0].PrimaryColor = RGB(0,255,0);
		sc.Subgraph[0].SecondaryColor = RGB(255,0,0);
		sc.Subgraph[1].Name = "NA";
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[1].PrimaryColor = RGB(192,192,192);

		sc.AutoLoop = 1;

		// during development set this flag to 1, so the dll can be modified. When development is done set it to 0 to improve performance.
		sc.FreeDLL = 0;

		return;
	}


	// Do data processing


	float HighValue = sc.BaseDataIn[SC_VOLUME][sc.Index];
	float LowValue = sc.BaseDataIn[SC_LOW][sc.Index];
	float PrevHighValue = sc.BaseDataIn[SC_VOLUME][sc.Index-1];
	float PrevHighValue2 = sc.BaseDataIn[SC_VOLUME][sc.Index-2];
	float PrevLowValue = sc.BaseDataIn[SC_LOW][sc.Index-1];

	sc.Subgraph[0][sc.Index] = 0;
	sc.Subgraph[1][sc.Index] = 0;

	if (HighValue > PrevHighValue && HighValue > PrevHighValue2 )
	{
		sc.Subgraph[0][sc.Index] = sc.BaseDataIn[SC_VOLUME][sc.Index];
		sc.Subgraph[0].DataColor[sc.Index] = sc.Subgraph[0].PrimaryColor;

	}
}

/***********************************************************************/

SCSFExport scsf_KiwisTrailingStop(SCStudyInterfaceRef sc)
{	
	SCSubgraphRef TSUp = sc.Subgraph[0];
	SCSubgraphRef TSDown = sc.Subgraph[1];	

	SCSubgraphRef direction = sc.Subgraph[3];
	SCSubgraphRef hiclose = sc.Subgraph[4];
	SCSubgraphRef loclose = sc.Subgraph[5];

	SCFloatArrayRef e1 = sc.Subgraph[6];
	SCFloatArrayRef e2 = sc.Subgraph[7];
	SCFloatArrayRef e3 = sc.Subgraph[8];
	SCFloatArrayRef e4 = sc.Subgraph[9];
	SCFloatArrayRef e5 = sc.Subgraph[10];
	SCFloatArrayRef e6 = sc.Subgraph[11];

	SCSubgraphRef TempRange = sc.Subgraph[6];
	SCSubgraphRef TempAvgRange = sc.Subgraph[7];
	SCSubgraphRef diff2 = sc.Subgraph[8];
	SCSubgraphRef atrmod = sc.Subgraph[9];

	SCInputRef Use2Subgraphs = sc.Input[0];
	SCInputRef ATRLength = sc.Input[2];
	SCInputRef ATRFactor = sc.Input[3];
	SCInputRef Vervoort = sc.Input[4];
	SCInputRef ATRMax = sc.Input[5];



	if(sc.SetDefaults)
	{
		sc.GraphName="Kiwi's Trailing Stop";
		sc.StudyDescription = "Kiwi's Trailing Stop (Chandelier) plus Sylvain Vervoort variation";

		TSUp.Name="TS";
		TSUp.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		TSUp.SecondaryColorUsed = 1;
		TSUp.PrimaryColor = RGB(0,255,0);
		TSUp.SecondaryColor = RGB(255,0,0);
		TSUp.DrawZeros = 0;

		TSDown.Name = "TS";
		TSDown.DrawStyle = DRAWSTYLE_LINE_SKIPZEROS;
		TSDown.PrimaryColor = RGB(255,0,0);
		TSDown.DrawZeros = 0;

		TempRange.Name = "TR";
		TempAvgRange.Name = "TAR";
		diff2.Name = "diff2";
		atrmod.Name = "atrmod";

		sc.AutoLoop = 0;

		ATRLength.Name="ATR Length";
		ATRLength.SetFloat(9.0);

		ATRFactor.Name="ATR Factor";
		ATRFactor.SetFloat(2.5);

		Vervoort.Name="Vervoort Variation?";
		Vervoort.SetYesNo(false);

		ATRMax.Name="Vervoort Maximum Range";
		ATRMax.SetFloat(1.5);

		Use2Subgraphs.Name="Use 2 subgraphs";
		Use2Subgraphs.SetYesNo(true);

		sc.GraphRegion = 0;

		return;
	}

	int 	pos;
	float 	Ave;
	float  	b,b2,b3,c1,c2,c3,c4,w1=0,w2=0;

	sc.DataStartIndex=10;

	if(Use2Subgraphs.GetYesNo())
	{
		TSUp.Name = "TS Up";
		TSDown.Name = "TS Down";

		TSUp.SecondaryColorUsed = false;
	}
	else
	{
		TSUp.Name="TS";

		TSUp.SecondaryColorUsed = 1;
	}


	if (sc.UpdateStartIndex == 0)
	{
		direction[sc.UpdateStartIndex] = 1;
		loclose[sc.UpdateStartIndex] = sc.Close[sc.UpdateStartIndex]; 
		hiclose[sc.UpdateStartIndex] = loclose[sc.UpdateStartIndex];

		e1[sc.UpdateStartIndex]=sc.High[sc.UpdateStartIndex]-sc.Low[sc.UpdateStartIndex]; 
		e2[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex]; 
		e3[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex]; 
		e4[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex]; 
		e5[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex]; 
		e6[sc.UpdateStartIndex]=e1[sc.UpdateStartIndex];
	}

	if(!Vervoort.GetYesNo()) 
	{
		b=0.5;					// 0.5
		b2=(b*b);				// 0.25
		b3=(b2*b);				// 0.125

		c1=-b3;					// - 0.125
		c2=(3*(b2+b3));			// 0.45
		c3=(-3*(2*b2+b+b3)); 
		c4=(1+3*b+b3+3*b2);
		w1 = 2/(ATRLength.GetFloat()+1);  
		w2 = 1-w1;

		for (pos=max(sc.UpdateStartIndex, 1); pos < sc.ArraySize; pos++)
		{
			float temp = max(sc.High[pos]-sc.Low[pos], sc.High[pos]-sc.Close[pos-1]);
			float P   = max(temp,sc.Close[pos-1]-sc.Low[pos]);

			e1[pos] = w1*P + w2*e1[pos - 1];
			e2[pos] = w1*e1[pos] + w2*e2[pos - 1];
			e3[pos] = w1*e2[pos] + w2*e3[pos - 1];
			e4[pos] = w1*e3[pos] + w2*e4[pos - 1];
			e5[pos] = w1*e4[pos] + w2*e5[pos - 1];
			e6[pos] = w1*e5[pos] + w2*e6[pos - 1];

			Ave = c1*e6[pos] + c2*e5[pos] + c3*e4[pos] + c4*e3[pos];

			if((direction[pos-1]==1 && sc.Close[pos]<(loclose[pos-1]))
				|| 
				(direction[pos-1]==-1 && sc.Close[pos]>(hiclose[pos-1])))
			{
				if(direction[pos-1]==1)
				{
					direction[pos] = -1; //reverse short
					hiclose[pos] = sc.Close[pos]+(Ave*ATRFactor.GetFloat());
					loclose[pos] = 0;
				} 
				else
				{
					direction[pos] = 1; //reverse long
					loclose[pos] = sc.Close[pos]-(Ave*ATRFactor.GetFloat());
					hiclose[pos] = 0;
				}
			} 
			else
			{
				if(direction[pos-1]==1)
				{
					if(sc.Close[pos]-(Ave*ATRFactor.GetFloat())>loclose[pos-1])
					{
						loclose[pos] = sc.Close[pos]-(Ave*ATRFactor.GetFloat());
						hiclose[pos] = hiclose[pos-1];
					}
					else
					{
						loclose[pos] = loclose[pos-1];
						hiclose[pos] = hiclose[pos-1];
					}
				} 
				else
				{
					if(sc.Close[pos]+(Ave*ATRFactor.GetFloat())<hiclose[pos-1])
					{
						loclose[pos] = loclose[pos-1];
						hiclose[pos] = sc.Close[pos]+(Ave*ATRFactor.GetFloat());
					}
					else
					{
						loclose[pos] = loclose[pos-1];
						hiclose[pos] = hiclose[pos-1];
					}
				};

				direction[pos] = direction[pos-1]; // no change
			};

			if(direction[pos]==1) 
			{
				if(Use2Subgraphs.GetYesNo() == false)
				{
					TSUp[pos] = (loclose[pos]); 
					TSUp.DataColor[pos] = TSUp.PrimaryColor;
				}
				else
				{
					TSUp[pos] = (loclose[pos]); 
					TSDown[pos] = 0;
				}
			} 
			else
			{
				if(Use2Subgraphs.GetYesNo() == false)
				{
					TSUp[pos] = (hiclose[pos]); 
					TSUp.DataColor[pos] =  TSUp.SecondaryColor;
				}
				else
				{
					TSDown[pos] = (hiclose[pos]);  
					TSUp[pos] = 0;
				}
			}	
		}
	} else
	{

		/*	
		HiLo:=If(H-L<1.5*Mov(H-L,period,S),H-L, 1.5*Mov
		(H-L,period,S));
		Href:=If(L<=Ref(H,-1),H-Ref(C,-1),(H-Ref(C,-1))-(L-Ref(H,-1))/2);
		Lref:=If(H>=Ref(L,-1),Ref(C,-1)-L,(Ref(C,-1)-L)-(Ref(L,-1)-H)/2);
		diff1:=Max(HiLo,Href);
		diff2:=Max(diff1,Lref);
		atrmod:=Wilders(diff2,period);
		loss:=atrfact*atrmod;
		trail:= 
		If(C>PREV AND Ref(C,-1)>PREV,
		Max(PREV,C-loss),
		If(C<PREV AND Ref(C,-1)<PREV,
		Min(PREV,C+loss),
		If(C>PREV,C-loss,C+loss)));
		*/	


		for (pos=max(sc.UpdateStartIndex, 1); pos < sc.ArraySize; pos++)
		{
			float HiLo,Href,Lref;
			int period = (int)ATRLength.GetFloat();
			TempRange[pos] = sc.High[pos]-sc.Low[pos];
			sc.MovingAverage(TempRange, TempAvgRange, MOVAVGTYPE_SIMPLE, pos, period);

			HiLo=min(TempRange[pos],ATRMax.GetFloat()*TempAvgRange[pos]);
			if(sc.Low[pos]<=sc.High[pos-1]) Href=sc.High[pos]-sc.Close[pos-1]; else Href=(sc.High[pos]-sc.Close[pos-1])-(sc.Low[pos]-sc.High[pos-1])/2;
			if(sc.High[pos]>=sc.Low[pos-1]) Lref=sc.Close[pos-1]-sc.Low[pos];  else Lref=(sc.Close[pos-1]-sc.Low[pos])- (sc.Low[pos-1]-sc.High[pos])/2;

			diff2[pos] = max(Lref,max(HiLo,Href));
			sc.MovingAverage(diff2, atrmod, MOVAVGTYPE_WILDERS, pos, period);

			Ave = atrmod[pos];

			if((direction[pos-1]==1 && sc.Close[pos]<(loclose[pos-1]))
				|| 
				(direction[pos-1]==-1 && sc.Close[pos]>(hiclose[pos-1])))
			{
				if(direction[pos-1]==1)
				{
					direction[pos] = -1; //reverse short
					hiclose[pos] = sc.Close[pos]+(Ave*ATRFactor.GetFloat());
					loclose[pos] = 0;
				} 
				else
				{
					direction[pos] = 1; //reverse long
					loclose[pos] = sc.Close[pos]-(Ave*ATRFactor.GetFloat());
					hiclose[pos] = 0;
				}
			} 
			else
			{
				if(direction[pos-1]==1)
				{
					if(sc.Close[pos]-(Ave*ATRFactor.GetFloat())>loclose[pos-1])
					{
						loclose[pos] = sc.Close[pos]-(Ave*ATRFactor.GetFloat());
						hiclose[pos] = hiclose[pos-1];
					}
					else
					{
						loclose[pos] = loclose[pos-1];
						hiclose[pos] = hiclose[pos-1];
					}
				} 
				else
				{
					if(sc.Close[pos]+(Ave*ATRFactor.GetFloat())<hiclose[pos-1])
					{
						loclose[pos] = loclose[pos-1];
						hiclose[pos] = sc.Close[pos]+(Ave*ATRFactor.GetFloat());
					}
					else
					{
						loclose[pos] = loclose[pos-1];
						hiclose[pos] = hiclose[pos-1];
					}
				};

				direction[pos] = direction[pos-1]; // no change
			};

			if(direction[pos]==1) 
			{
				if(Use2Subgraphs.GetYesNo() == false)
				{
					TSUp[pos] = (loclose[pos]); 
					TSUp.DataColor[pos] = TSUp.PrimaryColor;
				}
				else
				{
					TSUp[pos] = (loclose[pos]); 
					TSDown[pos] = 0;
				}
			} 
			else
			{
				if(Use2Subgraphs.GetYesNo() == false)
				{
					TSUp[pos] = (hiclose[pos]); 
					TSUp.DataColor[pos] =  TSUp.SecondaryColor;
				}
				else
				{
					TSDown[pos] = (hiclose[pos]);  
					TSUp[pos] = 0;
				}
			}
		}
	}
}
/*==========================================================================*/


int myDCPeriod(SCStudyInterfaceRef sc, SCFloatArrayRef Price, int i);
float percentile(SCStudyInterfaceRef sc, SCFloatArrayRef In, SCFloatArrayRef Out, int numBars, int pos, float Pct);

int compare (const void *a, const void *b);



SCSFExport scsf_AdaptiveMovingPercentile(SCStudyInterfaceRef sc)
{

	SCSubgraphRef SGPercentile	= 		sc.Subgraph[0];

	SCInputRef INlength 		= 		sc.Input[0];
	SCInputRef INperiod			= 		sc.Input[1];
	SCInputRef INadaptive		= 		sc.Input[2];
	SCInputRef INPCT			=		sc.Input[3];

	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "Adaptive Moving Percentile";

		sc.StudyDescription = "This study calculates the Moving Percentile. Lengths are Adaptive or Manual";

		sc.DrawZeros = 0;
		sc.AutoLoop = 1;
		sc.GraphRegion = 0;
		sc.FreeDLL=0; // 1 = dll is freed up, this allows debugging. Change back to 0 when code is complete	

		SGPercentile.Name = "Percentile";
		SGPercentile.DrawStyle = DRAWSTYLE_LINE;
		SGPercentile.LineWidth = 1;
		SGPercentile.PrimaryColor = GREEN;
		SGPercentile.SecondaryColor = RED;

		INlength.Name = "Input Data";
		INlength.SetInputDataIndex(SC_LAST);

		INperiod.Name = "Length";
		INperiod.SetInt(11);
		INperiod.SetIntLimits(1, 1000);

		INadaptive.Name = "Adaptive Period? (1-Yes,0-No)?";
		INadaptive.SetInt(1);
		INadaptive.SetIntLimits(0,1);

		INPCT.Name = "Percentile - 50 is median";
		INPCT.SetFloat(50.0f);
		INPCT.SetFloatLimits(0.05f,99.95f);

		return;
	}
	int Length 					= INperiod.GetInt();
	int adaptive 				= INadaptive.GetInt();	
	float PCT	 				= INPCT.GetFloat();	
	unsigned long SC_DataType 	= INlength.GetInputDataIndex();

	SCFloatArrayRef Price 		= sc.Subgraph[0].Arrays[0];
	SCFloatArrayRef PriceHL		= sc.Subgraph[0].Arrays[1];
	SCFloatArrayRef Temp 		= sc.Subgraph[0].Arrays[2];
	SCFloatArrayRef Out 		= sc.Subgraph[0].Arrays[3];	

	Price						= sc.BaseDataIn[SC_DataType];
	PriceHL 					= sc.BaseDataIn[SC_HL];	

	if (adaptive == 1)	
		Length = myDCPeriod(sc, PriceHL, sc.Index);
	else 
		Length = INperiod.GetInt();

	sc.DataStartIndex = Length+10;
	SGPercentile[sc.Index] = percentile(sc, Price, Out, Length, sc.Index, PCT);

}


int myDCPeriod(SCStudyInterfaceRef sc, SCFloatArrayRef Price, int i)
{
	// John Ehlers Dominant Cycle code for SC
	SCFloatArrayRef Phase = sc.Subgraph[22].Arrays[1];
	SCFloatArrayRef MAMA =				sc.Subgraph[22].Arrays[2];
	SCFloatArrayRef FAMA =				sc.Subgraph[22].Arrays[3];
	SCFloatArrayRef Smooth =			sc.Subgraph[22].Arrays[4];
	SCFloatArrayRef Detrender =		sc.Subgraph[22].Arrays[5];
	SCFloatArrayRef Q1	=				sc.Subgraph[22].Arrays[6];
	SCFloatArrayRef I1 =				sc.Subgraph[22].Arrays[7];
	SCFloatArrayRef jI =				sc.Subgraph[23].Arrays[0];
	SCFloatArrayRef jQ =				sc.Subgraph[23].Arrays[1];
	SCFloatArrayRef I2 =				sc.Subgraph[23].Arrays[2];
	SCFloatArrayRef Q2 = 				sc.Subgraph[23].Arrays[3];
	SCFloatArrayRef Re =				sc.Subgraph[23].Arrays[4];
	SCFloatArrayRef Im =				sc.Subgraph[23].Arrays[5];
	SCFloatArrayRef Period =			sc.Subgraph[23].Arrays[6];
	SCFloatArrayRef SmoothPeriod =		sc.Subgraph[23].Arrays[7];	
	// smooth
	Smooth[i] = (4*Price[i] + 3*Price[i-1] + 2*Price[i-2] + Price[i-3])/10; 		

	// detrender
	Detrender[i] = (0.0962f*Smooth[i] + 0.5769f*Smooth[i-2] - 0.5769f*Smooth[i-4] - 0.0962f*Smooth[i-6])*(0.075f*Period[i-1] + 0.54f); 		

	// compute InPhase and Quadrature components
	Q1[i] = (0.0962f*Detrender[i] + 0.5769f*Detrender[i-2] - 0.5769f*Detrender[i-4] - 0.0962f*Detrender[i-6])*(0.075f*Period[i-1] + 0.54f); 
	I1[i] = Detrender[i-3];

	// Advance the phase of I1 and Q1 by 90 degrees
	jI[i] = (0.0962f*I1[i] + 0.5769f*I1[i-2] - 0.5769f*I1[i-4] - 0.0962f*I1[i-6])*(0.075f*Period[i-1] + 0.54f); 
	jQ[i] = (0.0962f*Q1[i] + 0.5769f*Q1[i-2] - 0.5769f*Q1[i-4] - 0.0962f*Q1[i-6])*(0.075f*Period[i-1] + 0.54f);

	// Phasor addition for 3 bar averaging
	I2[i] = I1[i] - jQ[i]; 
	Q2[i] = Q1[i] + jI[i];

	// Smooth the I and Q components before applying the discriminator
	I2[i] = 0.2f*I2[i] + 0.8f*I2[i-1]; 
	Q2[i] = 0.2f*Q2[i] + 0.8f*Q2[i-1];

	// Homodyne Discriminator
	Re[i] = I2[i]*I2[i-1] + Q2[i]*Q2[i-1]; 
	Im[i] = I2[i]*Q2[i-1] - Q2[i]*I2[i-1]; 
	Re[i] = 0.2f*Re[i] + 0.8f*Re[i-1]; 
	Im[i] = 0.2f*Im[i] + 0.8f*Im[i-1]; 

	if (Im[i] != 0.0f && Re[i] != 0.0f)
		Period[i] = 360/(57.3f*atan(Im[i]/Re[i]));
	if (Period[i] > 1.5f*Period[i-1])
		Period[i] = 1.5f*Period[i-1];
	if (Period[i] < 0.67f*Period[i-1])
		Period[i] = 0.67f*Period[i-1] ;
	if (Period[i] < 6)
		Period[i] = 6 ;
	if (Period[i] > 50)
		Period[i] = 50 ;
	Period[i] = 0.2f*Period[i] + 0.8f*Period[i-1];
	SmoothPeriod[i] = 0.33f*Period[i] + 0.67f*SmoothPeriod[i-1];
	return int(SmoothPeriod[i]);
}

float percentile(SCStudyInterfaceRef sc, SCFloatArrayRef In, SCFloatArrayRef Out, int numBars, int pos, float Pct)
{
	float* pTmp;
	pTmp = new float[numBars];
	int x, ir;
	double rank, fractpart, intpart;

	// transfer elements to temp array
	for (x=0;x < numBars;x++)
	{
		pTmp[x] = In[pos-x];
	}

	//sort array in ascending order
	//http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/
	qsort(pTmp, numBars, sizeof(float), compare);

	// get the rank and fraction of the array
	//http://cnx.org/content/m10805/latest/
	rank = ((Pct/100.0f)*(numBars-1.0f)) + 1.0f;

	// separate the fractional part and the value to the left of decimal
	//http://www.cplusplus.com/reference/clibrary/cmath/modf/
	fractpart = modf (rank , &intpart);

	// get the rank.  1 is subtracted to match the array which starts at zero
	ir = int(intpart)-1;

	// calculate the percentile
	Pct = (float)(fractpart*(pTmp[ir+1] - pTmp[ir]) + pTmp[ir]);
	delete[] pTmp;

	// return the value
	Out[pos] = Pct;
	return(Out[pos]);
}

int compare (const void *a, const void *b)
{
	return ( *(int*)a - *(int*)b );
}

/************************************************************************/

SCSFExport scsf_MovingPercentile(SCStudyGraphRef sc)
{

	SCSubgraphRef SGPercentile	= 		sc.Subgraph[0];

	SCInputRef INlength 		= 		sc.Input[0];
	SCInputRef INdata 			= 		sc.Input[1];
	SCInputRef INPercentile		= 		sc.Input[2];	

	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "Moving Percentile";

		sc.StudyDescription = "This is like a simple moving average, except it is calculating the Percentile instead of the average.";

		sc.DrawZeros = 0;
		sc.AutoLoop = 1;
		sc.GraphRegion = 0;
		sc.FreeDLL=0; // 1 = dll is freed up, this allows debugging. Change back to 0 when code is complete	

		SGPercentile.Name = "Percentile";

		INdata.Name = "Input Data";
		INdata.SetInputDataIndex(SC_LAST);

		INlength.Name = "Length";
		INlength.SetInt(14);
		INlength.SetIntLimits(1, 1000);

		INPercentile.Name = "Percentile";
		INPercentile.SetFloat(50.0f);
		INPercentile.SetFloatLimits(0.0f,100.0f);
		return;
	}
	int Length 					= INlength.GetInt();
	float Perc					= INPercentile.GetFloat();
	unsigned long SC_DataType 	= INdata.GetInputDataIndex();
	float tick					= sc.TickSize; 

	sc.DataStartIndex = Length;

	SCFloatArrayRef Price 		= sc.Subgraph[0].Arrays[0];
	SCFloatArrayRef Out 		= sc.Subgraph[0].Arrays[1];

	Price						= sc.BaseDataIn[SC_DataType];

	SGPercentile[sc.Index] = sc.RoundToTickSize(percentile(sc, Price, Out, Length, sc.Index, Perc),tick);
}


/************************************************************************/



#define ASKCOLOR RGB(255, 128, 128)
#define BIDCOLOR RGB(128, 255, 128)
#define POSDELTACOLOR RGB(32, 255, 32)
#define NEGDELTACOLOR RGB(255, 32, 32)


SCSFExport scsf_DeltaMomentum(SCStudyGraphRef sc) 
{ 
	SCSubgraphRef askVol 			= sc.Subgraph[0];
	SCSubgraphRef bidVol 			= sc.Subgraph[1];
	SCSubgraphRef deltaVol 			= sc.Subgraph[2];
	SCSubgraphRef deltaMomentum 	= sc.Subgraph[3];


	if (sc.SetDefaults) {
		sc.GraphName = "DeltaMomentum"; 
		sc.GraphRegion = 1; 
		sc.ScaleRangeType = SCALE_AUTO;
		sc.StudyDescription = "DeltaMomentum"; 


		sc.FreeDLL = 0; 

		sc.AutoLoop = 0; // Manual looping 

		askVol.Name = "Ask Volume";
		askVol.PrimaryColor = ASKCOLOR;
		askVol.DrawStyle = DRAWSTYLE_IGNORE;

		bidVol.Name = "Bid Volume";
		bidVol.PrimaryColor = BIDCOLOR;
		bidVol.DrawStyle = DRAWSTYLE_IGNORE;

		deltaVol.Name = "Delta";
		deltaVol.DrawStyle = DRAWSTYLE_IGNORE;


		deltaMomentum.Name = "Delta Momentum";
		deltaMomentum.PrimaryColor = POSDELTACOLOR;
		deltaMomentum.SecondaryColor = NEGDELTACOLOR;
		deltaMomentum.LineWidth = 2;
		deltaMomentum.DrawStyle = DRAWSTYLE_BAR;
		deltaMomentum.AutoColoring = AUTOCOLOR_POSNEG;
		return; 
	} 
	int ind = sc.UpdateStartIndex;	
	if (ind == 0)
	{
		askVol[ind] 	= sc.BaseDataIn[SC_ASKVOL][ind];
		bidVol[ind] 	= -sc.BaseDataIn[SC_BIDVOL][ind];
		deltaVol[ind]	= askVol[ind] + bidVol[ind];
		deltaMomentum[ind] = deltaVol[ind];
		++ind;
	}	
	for (; ind < sc.ArraySize; ++ind)
	{
		askVol[ind] 	= sc.BaseDataIn[SC_ASKVOL][ind];
		bidVol[ind] 	= -sc.BaseDataIn[SC_BIDVOL][ind];
		deltaVol[ind]	= askVol[ind] + bidVol[ind];
		if (deltaVol[ind] > 0) 
		{
			if (deltaMomentum[ind-1] >= 0)
			{
				deltaMomentum[ind] = deltaMomentum[ind-1] + deltaVol[ind];
			}
			else
			{
				deltaMomentum[ind] = deltaVol[ind];
			}
		}
		else if (deltaVol[ind] < 0)
		{
			if (deltaMomentum[ind-1] <= 0)
			{
				deltaMomentum[ind] = deltaMomentum[ind-1] + deltaVol[ind];
			}
			else
			{
				deltaMomentum[ind] = deltaVol[ind];
			}
		}
		else 
		{
			deltaMomentum[ind] = deltaMomentum[ind-1]; 
		}
	}
} 

/************************************************************************/

//
// PRC - Polynomial Regression Channel
//
// 20110329 - written by aslan
// 20100330 - added redraw option
//

SCSFExport scsf_PolynomialRegressionChannel(SCStudyInterfaceRef sc)
{
	SCInputRef PolyDegree  = sc.Input[0];
	SCInputRef Period      = sc.Input[1];
	SCInputRef StdDev1     = sc.Input[2];
	SCInputRef StdDev2     = sc.Input[3];
	SCInputRef Redraw      = sc.Input[4];

	SCSubgraphRef Fx     = sc.Subgraph[0];
	SCSubgraphRef Upper2 = sc.Subgraph[1];
	SCSubgraphRef Upper1 = sc.Subgraph[2];
	SCSubgraphRef Lower1 = sc.Subgraph[3];
	SCSubgraphRef Lower2 = sc.Subgraph[4];

	if ( sc.SetDefaults )
	{
		sc.GraphName = "Polynomial Regression Channel";
		sc.StudyDescription = "Polynomial Regression Channel";

		PolyDegree.Name = "Polynomial Degree (1-4)";
		PolyDegree.SetInt(3);
		PolyDegree.SetIntLimits(1, 4);

		Period.Name = "PRC Period";
		Period.SetInt(150);
		Period.SetIntLimits(1, 10000);

		StdDev1.Name = "Standard Deviation Level 1";
		StdDev1.SetFloat(1.618f);
		StdDev1.SetFloatLimits(0, 1000);

		StdDev2.Name = "Standard Deviation Level 2";
		StdDev2.SetFloat(2.0);
		StdDev2.SetFloatLimits(0, 1000);

		Redraw.Name = "Use Redraw";
		Redraw.SetYesNo(1);

		Fx.Name = "Mid";
		Fx.DrawZeros = false;
		Fx.DrawStyle = DRAWSTYLE_LINE;
		Fx.LineWidth = 1;
		Fx.LineStyle = LINESTYLE_DOT;
		Fx.PrimaryColor = COLOR_GRAY;

		Upper2.Name = "Upper 2";
		Upper2.DrawZeros = false;
		Upper2.DrawStyle = DRAWSTYLE_FILLTOP_TRANSPARENT;
		Upper2.PrimaryColor = COLOR_RED;

		Upper1.Name = "Upper 1";
		Upper1.DrawZeros = false;
		Upper1.DrawStyle = DRAWSTYLE_FILLBOTTOM_TRANSPARENT;
		Upper1.PrimaryColor = COLOR_RED;

		Lower1.Name = "Lower 1";
		Lower1.DrawZeros = false;
		Lower1.DrawStyle = DRAWSTYLE_FILLTOP_TRANSPARENT;
		Lower1.PrimaryColor = COLOR_BLUE;

		Lower2.Name = "Lower 2";
		Lower2.DrawZeros = false;
		Lower2.DrawStyle = DRAWSTYLE_FILLBOTTOM_TRANSPARENT;
		Lower2.PrimaryColor = COLOR_BLUE;

		sc.AutoLoop = true;
		sc.DrawZeros = false;
		sc.GraphRegion = 0;
		sc.FreeDLL = 0;  

		sc.GlobalDisplayStudyNameSubgraphNamesAndValues = 0;
		sc.DisplayStudyName = 0;
		sc.DisplayStudyInputValues = 0;

		return;
	}


	struct s_PRCData
	{
		double ai[10][10];
		double b[10];
		double x[10];
		double sx[20];
	};


	int&  lastIndex = sc.GetPersistentInt(1);
	int&  nn        = sc.GetPersistentInt(2);
	s_PRCData *p_PRCMemory    = (s_PRCData *) sc.GetPersistentPointer(1);

	if (sc.LastCallToFunction)
	{
		// This study is being removed from the chart or the chart is being closed - cleanup
		if (p_PRCMemory != 0) 
		{
			sc.FreeMemory(p_PRCMemory);
			p_PRCMemory = 0;
			sc.SetPersistentPointer(1, p_PRCMemory);
		}
		return;
	}

	if (sc.Index == 0)
	{
		lastIndex = -1;
		sc.ValueFormat = sc.BaseGraphValueFormat;

		if (p_PRCMemory != 0)
			sc.FreeMemory(p_PRCMemory);

		p_PRCMemory = (s_PRCData*)sc.AllocateMemory(sizeof(s_PRCData));

		sc.SetPersistentPointer(1,p_PRCMemory);

		if (p_PRCMemory == 0) 
			return;	


		// set up static vars
		s_PRCData& PRCData = *p_PRCMemory;

		nn = PolyDegree.GetInt() + 1;

		//----------------------sx------------
		PRCData.sx[1] = Period.GetInt() + 1;
		for(int i=1;i<=nn*2-2;i++) {
			double sum = 0.0;
			for(int n=0;n<=Period.GetInt();n++) {
				sum+=pow((double)n,i);
			}
			PRCData.sx[i+1]=sum;
		}  
	}

	// make sure we have enough bars to start
	if (sc.Index < Period.GetInt())
		return;

	// erase old data on new bar
	if (sc.Index != lastIndex)
	{
		lastIndex = sc.Index;
		if (Redraw.GetYesNo())
		{
			Fx[sc.Index-Period.GetInt()-1] = 0;
			Upper2[sc.Index-Period.GetInt()-1] = 0;
			Upper1[sc.Index-Period.GetInt()-1] = 0;
			Lower1[sc.Index-Period.GetInt()-1] = 0;
			Lower2[sc.Index-Period.GetInt()-1] = 0;
		}
	}

	// now lets do the real work
	if (p_PRCMemory == 0) 
		return;

	s_PRCData& PRCData = *p_PRCMemory;

	//----------------------syx-----------
	for(int i=1;i<=nn;i++) {
		double sum=0.0;
		for(int n=0;n<=Period.GetInt();n++) {
			if(i==1) sum+=sc.Close[sc.Index-n];
			else sum+=sc.Close[sc.Index-n]*pow((double)n,i-1);
		}
		PRCData.b[i]=sum;
	} 
	//===============Matrix===============
	for(int j=1;j<=nn;j++) {
		for(int i=1; i<=nn; i++)	{
			int k=i+j-1;
			PRCData.ai[i][j]=PRCData.sx[k];  // reset ai matrix
		}
	}  
	//===============Gauss================
	for(int k=1; k<=nn-1; k++) {
		int    l=0;
		double m=0.0;
		for(int i=k; i<=nn; i++) {
			if(abs(PRCData.ai[i][k])>m) {
				m=abs(PRCData.ai[i][k]);
				l=i;
			}
		}
		if(l==0) return;   
		if (l!=k)	{
			double tt = 0.0;
			for(int j=1; j<=nn; j++)	{
				tt=PRCData.ai[k][j];
				PRCData.ai[k][j]=PRCData.ai[l][j];
				PRCData.ai[l][j]=tt;
			}
			tt=PRCData.b[k];
			PRCData.b[k]=PRCData.b[l];
			PRCData.b[l]=tt;
		}  
		for(int i=k+1;i<=nn;i++) {
			double qq=PRCData.ai[i][k]/PRCData.ai[k][k];
			for(int j=1;j<=nn;j++) {
				if(j==k) PRCData.ai[i][j]=0;
				else PRCData.ai[i][j]=PRCData.ai[i][j]-qq*PRCData.ai[k][j];
			}
			PRCData.b[i]=PRCData.b[i]-qq*PRCData.b[k];
		}
	}  
	PRCData.x[nn]=PRCData.b[nn]/PRCData.ai[nn][nn];
	for(int i=nn-1;i>=1;i--)	{
		double tt=0.0;
		for(int j=1;j<=nn-i;j++) {
			tt=tt+PRCData.ai[i][i+j]*PRCData.x[i+j];
			PRCData.x[i]=(1/PRCData.ai[i][i])*(PRCData.b[i]-tt);
		}
	} 
	//====================================
	for(int n=0;n<=Period.GetInt();n++) {
		double sum=0.0;
		for(int k=1;k<=PolyDegree.GetInt();k++) {
			sum+=PRCData.x[k+1]*pow((double)n,k);
		}
		if (n==0 || Redraw.GetYesNo())
			Fx[sc.Index-n] = (float)(PRCData.x[1]+sum);
	} 
	//-------------------Std--------------
	double sq=0.0, sq1=0.0, sq2=0.0;
	for(int n=0;n<=Period.GetInt();n++) {
		sq+=pow(sc.Close[sc.Index-n]-Fx[sc.Index-n],2);
	}
	sq=sqrt(sq/(Period.GetInt()+1));
	sq1=sq*StdDev1.GetFloat();
	sq2=sq*StdDev2.GetFloat();

	for(int n=0;n<=Period.GetInt();n++) {
		if (n==0 || Redraw.GetYesNo())
		{
			Upper1[sc.Index-n] = (float)(Fx[sc.Index-n]+sq1);
			Lower1[sc.Index-n] = (float)(Fx[sc.Index-n]-sq1);
			Upper2[sc.Index-n] = (float)(Fx[sc.Index-n]+sq2);
			Lower2[sc.Index-n] = (float)(Fx[sc.Index-n]-sq2);
		}
	}
}


/***********************************************************************/

/*
Volatility Profit Indicator (VPI)
Author: jsyd
Date: 05/04/2011
*/

SCSFExport scsf_VPI(SCStudyGraphRef sc)
{
	SCSubgraphRef uBandSubgraph = sc.Subgraph[0];
	SCSubgraphRef mBandSubgraph = sc.Subgraph[1];
	SCSubgraphRef lBandSubgraph = sc.Subgraph[2];
	SCSubgraphRef atrSubgraph = sc.Subgraph[3];
	SCSubgraphRef uMaSubgraph = sc.Subgraph[4];
	SCSubgraphRef lMaSubgraph = sc.Subgraph[5];
	
	SCInputRef maTypeInput = sc.Input[0];
	SCInputRef ulPeriodInput = sc.Input[1];
	SCInputRef mPeriodInput = sc.Input[2];
	SCInputRef atrPeriodInput = sc.Input[3];
	SCInputRef atrMultiInput = sc.Input[4];
	
	if(sc.SetDefaults)
	{
		sc.GraphName="Volatility Profit Indicator";
		sc.StudyDescription="OverBought/OverSold based on ATR";
		
		uBandSubgraph.Name = "Upper Band";
		uBandSubgraph.DrawStyle = DRAWSTYLE_LINE;
		uBandSubgraph.PrimaryColor = RGB(255, 128, 0);
		uBandSubgraph.LineWidth = 2;
		
		mBandSubgraph.Name = "Middle Band (Moving Average)";
		mBandSubgraph.DrawStyle = DRAWSTYLE_LINE;
		mBandSubgraph.PrimaryColor = RGB(255, 255, 255);
		mBandSubgraph.LineWidth = 1;
		
		lBandSubgraph.Name = "Lower Band";
		lBandSubgraph.DrawStyle = DRAWSTYLE_LINE;
		lBandSubgraph.PrimaryColor = RGB(255, 128, 0);
		lBandSubgraph.LineWidth = 2;
		
		atrSubgraph.Name = "ATR";
		atrSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		
		uMaSubgraph.Name = "Upper MA";
		uMaSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		
		lMaSubgraph.Name = "Lower MA";
		lMaSubgraph.DrawStyle = DRAWSTYLE_HIDDEN;
		
		// Inputs
		maTypeInput.Name = "Moving Average Type";
		maTypeInput.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);	
		
		ulPeriodInput.Name = "Upper/Lower Band Period";
		ulPeriodInput.SetInt(13);
		ulPeriodInput.SetIntLimits(1, 10000);	
		
		mPeriodInput.Name = "Middle Band Period";
		mPeriodInput.SetInt(20);
		mPeriodInput.SetIntLimits(1, 10000);		
		
		atrPeriodInput.Name = "ATR Period";
		atrPeriodInput.SetInt(20);
		atrPeriodInput.SetIntLimits(1, 10000);	
		
		atrMultiInput.Name = "ATR Multiplier";
		atrMultiInput.SetFloat(2);
		
		sc.DrawZeros = false;
        sc.AutoLoop = 1;
		sc.FreeDLL = 0;
		sc.GraphRegion = 0;
		sc.ScaleRangeType=SCALE_SAMEASREGION;

		return;
	}
	
	int cur = sc.Index;
	/*
	VPI High Band   = MA(HI, type, x) + y * ATR(z)
	VPI Low Band   = MA(LO, type, x) - y * ATR(z)
	where...
		type = MA Type (default to Exponential)
		x = MA Period (default to 13)
		y = True Range Multiplier (default to 2)
		z = True Range Period (default to 20)
	*/
	/*===========================================================
	ATR
	===========================================================*/
	sc.ATR(sc.BaseDataIn, atrSubgraph, atrPeriodInput.GetInt(), MOVAVGTYPE_SIMPLE);
	
	sc.MovingAverage(sc.BaseDataIn[SC_HIGH], uMaSubgraph, maTypeInput.GetMovAvgType() , cur, ulPeriodInput.GetInt());
	sc.MovingAverage(sc.BaseDataIn[SC_LAST], mBandSubgraph, maTypeInput.GetMovAvgType() , cur, mPeriodInput.GetInt());
	sc.MovingAverage(sc.BaseDataIn[SC_LOW], lMaSubgraph, maTypeInput.GetMovAvgType() , cur, ulPeriodInput.GetInt());
	
	uBandSubgraph[cur] = uMaSubgraph[cur] + (atrMultiInput.GetFloat() * atrSubgraph[cur]);
	lBandSubgraph[cur] = lMaSubgraph[cur] - (atrMultiInput.GetFloat() * atrSubgraph[cur]);
}


/***********************************************************************/
SCSFExport scsf_MACDCOLOR(SCStudyGraphRef sc)
{
	if(sc.SetDefaults)
	{
		sc.GraphName="MACDcolor2";
		sc.StudyDescription="MACDcolor2";

		sc.Subgraph[0].Name="MACDcolor BAR";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_COLORBAR;
		sc.Subgraph[0].LineWidth = 3;

		sc.Input[0].Name = "Fast MA Length";
		sc.Input[0].SetInt(12);
		sc.Input[0].SetIntLimits(1, 1000);

		sc.Input[1].Name = "Slow MA Length";
		sc.Input[1].SetInt(26);
		sc.Input[1].SetIntLimits(1, 1000);

		sc.Input[2].Name = "MACD MA LENGTH TRIGGER";
		sc.Input[2].SetInt(9);
		sc.Input[2].SetIntLimits(1, 1000);

		sc.Input[3].Name = "Input Data";
		sc.Input[3].SetInputDataIndex(SC_LAST);  

		sc.Input[4].Name = "Moving average type";
		sc.Input[4].SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);

		sc.FreeDLL = 0;
		sc.AutoLoop = 1;
		sc.GraphRegion = 0;
		return;
	}
	int i = sc.Index;
	int len1 = sc.Input[0].GetInt();
	int len2 = sc.Input[1].GetInt();
	int len3 = sc.Input[2].GetInt();
	int ma_type	= sc.Input[4].GetInt();
	int data_type_indx = (int)sc.Input[3].GetInputDataIndex();

	SCFloatArrayRef in= sc.BaseDataIn[data_type_indx];


	const DWORD upColor = RGB(0, 255, 0);	
	const DWORD downColor = RGB(255, 0, 0);	
	const DWORD neturalColor = RGB(0, 0, 255);	




	sc.MACD(in, sc.Subgraph[0], sc.Index, len1, len2, len3,ma_type);

	float MACD = sc.Subgraph[0][sc.Index];
	float MACDMA = sc.Subgraph[0].Arrays[2][sc.Index];
	float MACDDifference = sc.Subgraph[0].Arrays[3][sc.Index];
	//Copy to Visible Subgraphs

	sc.Subgraph[3][sc.Index] = MACDDifference;



	SCFloatArrayRef macd = sc.Subgraph[3];

	sc.ExponentialMovAvg(in, sc.Subgraph[4], i, 8);
	sc.ExponentialMovAvg(in, sc.Subgraph[5], i, 21);  

	SCFloatArrayRef ema8 = sc.Subgraph[4];
	SCFloatArrayRef ema21 = sc.Subgraph[5];

	if(
		(macd[i] > macd[i-1])
		&&(ema8[i]>=ema8[i-1])
		)
	{
		sc.Subgraph[0].DataColor[sc.Index] =upColor ;		
	}
	else if ( 
		(macd[i] < macd[i-1])
		&&(ema8[i]<=ema8[i-1])
		)
	{
		sc.Subgraph[0].DataColor[sc.Index] = downColor;		
	}
	else 
	{
		sc.Subgraph[0].DataColor[sc.Index] = neturalColor;		
	}
}

/************************************************************************/

SCSFExport scsf_HorizontalGrid(SCStudyGraphRef sc)
{
	SCSubgraphRef L1 = sc.Subgraph[0];
	SCSubgraphRef L2 = sc.Subgraph[1];
	SCSubgraphRef L3 = sc.Subgraph[2];
	SCSubgraphRef L4 = sc.Subgraph[3];
	SCSubgraphRef L5 = sc.Subgraph[4];
	SCSubgraphRef L6 = sc.Subgraph[5];
	SCSubgraphRef L7 = sc.Subgraph[6];
	SCSubgraphRef L8 = sc.Subgraph[7];
	SCSubgraphRef L9 = sc.Subgraph[8];
	SCSubgraphRef L10 = sc.Subgraph[9];
	SCSubgraphRef L11 = sc.Subgraph[10];
	SCSubgraphRef L12 = sc.Subgraph[11];
	SCSubgraphRef L13 = sc.Subgraph[12];
	SCSubgraphRef L14 = sc.Subgraph[13];
	SCSubgraphRef L15 = sc.Subgraph[14];
	SCSubgraphRef L16 = sc.Subgraph[15];
	SCSubgraphRef L17 = sc.Subgraph[16];
	SCSubgraphRef L18 = sc.Subgraph[17];
	SCSubgraphRef L19 = sc.Subgraph[18];
	SCSubgraphRef L20 = sc.Subgraph[19];
	SCSubgraphRef L21 = sc.Subgraph[20];
	SCSubgraphRef L22 = sc.Subgraph[21];
	SCSubgraphRef L23 = sc.Subgraph[22];
	SCSubgraphRef L24 = sc.Subgraph[23];
	SCSubgraphRef L25 = sc.Subgraph[24];
	SCSubgraphRef L26 = sc.Subgraph[25];
	SCSubgraphRef L27 = sc.Subgraph[26];
	SCSubgraphRef L28 = sc.Subgraph[27];
	SCSubgraphRef L29 = sc.Subgraph[28];
	SCSubgraphRef L30 = sc.Subgraph[29];
	SCSubgraphRef L31 = sc.Subgraph[30];
	SCSubgraphRef L32 = sc.Subgraph[31];
	SCSubgraphRef L33 = sc.Subgraph[32];
	SCSubgraphRef L34 = sc.Subgraph[33];
	SCSubgraphRef L35 = sc.Subgraph[34];
	SCSubgraphRef L36 = sc.Subgraph[35];
	SCSubgraphRef L37 = sc.Subgraph[36];
	SCSubgraphRef L38 = sc.Subgraph[37];
	SCSubgraphRef L39 = sc.Subgraph[38];
	SCSubgraphRef L40 = sc.Subgraph[39];


	SCInputRef GridStart = sc.Input[0];
	SCInputRef GridSpacing = sc.Input[1];

	if (sc.SetDefaults)
	{
		sc.GraphName = "Horizontal Grid";

		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.DrawZeros = 0;
		sc.GraphRegion = 0;
		sc.ValueFormat = 3;
		sc.AutoLoop = 1;
		sc.FreeDLL= 0;

		GridStart.Name = "Grid Starting Number";
		GridStart.SetFloat(1200.0);

		GridSpacing.Name = "Grid Spacing";
		GridSpacing.SetFloat(5.0);

		L1.Name = "L1";
		L2.Name = "L2";
		L3.Name = "L3";
		L4.Name = "L4";
		L5.Name = "L5";
		L6.Name = "L6";
		L7.Name = "L7";
		L8.Name = "L8";
		L9.Name = "L9";
		L10.Name = "L10";
		L11.Name = "L11";
		L12.Name = "L12";
		L13.Name = "L13";
		L14.Name = "L14";
		L15.Name = "L15";
		L16.Name = "L16";
		L17.Name = "L17";
		L18.Name = "L18";
		L19.Name = "L19";
		L20.Name = "L20";
		L21.Name = "L21";
		L22.Name = "L22";
		L23.Name = "L23";
		L24.Name = "L24";
		L25.Name = "L25";
		L26.Name = "L26";
		L27.Name = "L27";
		L28.Name = "L28";
		L29.Name = "L29";
		L30.Name = "L30";
		L31.Name = "L31";
		L32.Name = "L32";
		L33.Name = "L33";
		L34.Name = "L34";
		L35.Name = "L35";
		L36.Name = "L36";
		L37.Name = "L37";
		L38.Name = "L38";
		L39.Name = "L39";
		L40.Name = "L40";


		return;
	}

	float GridSpacingVal = GridSpacing.GetFloat();
	float GridStartVal = GridStart.GetFloat()-GridSpacingVal;

	L1[sc.Index] = GridStartVal+GridSpacingVal;
	L2[sc.Index] = GridStartVal+GridSpacingVal*2;
	L3[sc.Index] = GridStartVal+GridSpacingVal*3;
	L4[sc.Index] = GridStartVal+GridSpacingVal*4;
	L5[sc.Index] = GridStartVal+GridSpacingVal*5;
	L6[sc.Index] = GridStartVal+GridSpacingVal*6;
	L7[sc.Index] = GridStartVal+GridSpacingVal*7;
	L8[sc.Index] = GridStartVal+GridSpacingVal*8;
	L9[sc.Index] = GridStartVal+GridSpacingVal*9;
	L10[sc.Index] = GridStartVal+GridSpacingVal*10;
	L11[sc.Index] = GridStartVal+GridSpacingVal*11;
	L12[sc.Index] = GridStartVal+GridSpacingVal*12;
	L13[sc.Index] = GridStartVal+GridSpacingVal*13;
	L14[sc.Index] = GridStartVal+GridSpacingVal*14;
	L15[sc.Index] = GridStartVal+GridSpacingVal*15;
	L16[sc.Index] = GridStartVal+GridSpacingVal*16;
	L17[sc.Index] = GridStartVal+GridSpacingVal*17;
	L18[sc.Index] = GridStartVal+GridSpacingVal*18;
	L19[sc.Index] = GridStartVal+GridSpacingVal*19;
	L20[sc.Index] = GridStartVal+GridSpacingVal*20;
	L21[sc.Index] = GridStartVal+GridSpacingVal*21;
	L22[sc.Index] = GridStartVal+GridSpacingVal*22;
	L23[sc.Index] = GridStartVal+GridSpacingVal*23;
	L24[sc.Index] = GridStartVal+GridSpacingVal*24;
	L25[sc.Index] = GridStartVal+GridSpacingVal*25;
	L26[sc.Index] = GridStartVal+GridSpacingVal*26;
	L27[sc.Index] = GridStartVal+GridSpacingVal*27;
	L28[sc.Index] = GridStartVal+GridSpacingVal*28;
	L29[sc.Index] = GridStartVal+GridSpacingVal*29;
	L30[sc.Index] = GridStartVal+GridSpacingVal*30;
	L31[sc.Index] = GridStartVal+GridSpacingVal*31;
	L32[sc.Index] = GridStartVal+GridSpacingVal*32;
	L33[sc.Index] = GridStartVal+GridSpacingVal*33;
	L34[sc.Index] = GridStartVal+GridSpacingVal*34;
	L35[sc.Index] = GridStartVal+GridSpacingVal*35;
	L36[sc.Index] = GridStartVal+GridSpacingVal*36;
	L37[sc.Index] = GridStartVal+GridSpacingVal*37;
	L38[sc.Index] = GridStartVal+GridSpacingVal*38;
	L39[sc.Index] = GridStartVal+GridSpacingVal*39;
	L40[sc.Index] = GridStartVal+GridSpacingVal*40;

}


/************************************************************************/

SCSFExport scsf_RunningVwapBands(SCStudyGraphRef sc)
{
    if (sc.SetDefaults)
    {
        sc.GraphName = "RunningVwapBands";
        sc.GraphRegion = 0;
        sc.ScaleRangeType = SCALE_SAMEASREGION; // So it does not squish the chart
        
		sc.StudyDescription = "RunningVwapBands. Discussion Subtopic: <a href=""http://www.sierrachart.com/supportboard/showthread.php?t=21886"">http://www.sierrachart.com/supportboard/showthread.php?t=21886</a>";
        

        sc.FreeDLL = 0;

        sc.AutoLoop = 0; // Manual looping
        
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
        
        sc.Subgraph[7].Name = "Index";
        sc.Subgraph[7].PrimaryColor = RGB(255, 255, 255);
        
        sc.Subgraph[8].Name = "FirstBarIndex";
        sc.Subgraph[8].PrimaryColor = RGB(255, 255, 255);
        
        sc.Subgraph[9].Name = "TradingSessionIndex";
        sc.Subgraph[9].PrimaryColor = RGB(255, 255, 255);
        
        
        sc.Input[0].Name  = "Input Data";
        sc.Input[0].SetInputDataIndex(SC_LAST);
        
        sc.Input[1].Name = "Display Historically";
        sc.Input[1].SetYesNo(1);
        
        sc.Input[2].Name = "Use Chart Settings Start Time instead of 0:00";
        sc.Input[2].SetYesNo(0);
        
        sc.Input[3].Name = "Number of Trading Sessions";
        sc.Input[3].SetInt(1);
        sc.Input[3].SetIntLimits(1, 260);
        
        sc.Input[4].Name = "Reset Running Average";
        sc.Input[4].SetYesNo(1);
        
        
        return;
    }

    long InputDataIndex = sc.Input[0].GetInputDataIndex();
    int DisplayHistorically = sc.Input[1].GetYesNo(); // Display historically (Yes/No)
    int UseChartSettingsStartTime = sc.Input[2].GetYesNo(); // Use Chart Settings Start Time instead of 0:00 (Yes/No)
    int NumberTradingSessions = sc.Input[3].GetInt();
    int ResetRunningAverage = sc.Input[4].GetYesNo();

    
    int Tsst, Cbd; // Trading session start time / Current bar date
    SCDateTime Cbdt, Pbdt, Tssdt; // Current bar date/time / Previous bar date/time / Trading session start date/time
    
    bool NewTradingSession; // New trading session
    SCFloatArrayRef TradingSessionIndex = sc.Subgraph[1].Arrays[0];

    int& FirstBarIndex = sc.PersistVars->i1; // New trading session bar index

    
    SCFloatArrayRef InputData = sc.Subgraph[0].Arrays[0]; // InputData
    SCFloatArrayRef Vol = sc.Subgraph[0].Arrays[1]; // Volume of bar
    SCFloatArrayRef Rsidtv = sc.Subgraph[0].Arrays[2]; // Running sum of (InputData) * (Volume)
    SCFloatArrayRef Rsv = sc.Subgraph[0].Arrays[3]; // Running sum of Volume
    SCFloatArrayRef Vwap = sc.Subgraph[0].Arrays[4]; // Volume weighted average price
    SCFloatArrayRef Rssd = sc.Subgraph[0].Arrays[5]; // Running sum of (squared deviations of InputData from Vwap) * (Volume)
    SCFloatArrayRef Vwsd = sc.Subgraph[0].Arrays[6]; // Volume weighted standard deviation
    
    
    int Index = sc.UpdateStartIndex;
    
    
    // If "Use Chart Settings Start Time instead of 0:00" is "Yes", then if using the evening session times, then use evening session
    // start time otherwise use day session start time
    // If "Use Chart Settings Start Time instead of 0:00" is "No" then use 0:00 as start time
    Tsst = UseChartSettingsStartTime ? (sc.UseSecondStartEndTimes ? sc.StartTime2 : sc.StartTime1) : 0;

    
    if (Index == 0)
    {
        TradingSessionIndex[Index] = 0;
        FirstBarIndex = 0;
        
        InputData[Index] = sc.BaseDataIn[InputDataIndex][Index];
        Vol[Index] = sc.BaseDataIn[SC_VOLUME][Index];
        
        Rsidtv[Index] = InputData[Index] * Vol[Index];
        Rsv[Index] = Vol[Index];
        
        if (Rsv[Index] > 0)
        {
            Vwap[Index] = Rsidtv[Index] / Rsv[Index];
            Rssd[Index] = pow(InputData[Index] - Vwap[Index], 2) * Vol[Index];
            Vwsd[Index] = sqrt(Rssd[Index] / Rsv[Index]);
        }
        else
        {
            Vwap[Index] = 0;
            Rssd[Index] = 0;
            Vwsd[Index] = 0;    
        }

        
        sc.Subgraph[0][Index] = Vwap[Index];
        sc.Subgraph[1][Index] = Vwap[Index] + 1 * Vwsd[Index];
        sc.Subgraph[2][Index] = Vwap[Index] - 1 * Vwsd[Index];
        sc.Subgraph[3][Index] = Vwap[Index] + 2 * Vwsd[Index];
        sc.Subgraph[4][Index] = Vwap[Index] - 2 * Vwsd[Index];
        sc.Subgraph[5][Index] = Vwap[Index] + 3 * Vwsd[Index];
        sc.Subgraph[6][Index] = Vwap[Index] - 3 * Vwsd[Index];
        
        
        ++Index;
    }
    
    
    for (; Index < sc.ArraySize; ++Index)
    {
        Cbd = sc.BaseDateTimeIn[Index].GetDate();
        Tssdt = COMBINE_DATE_TIME(Cbd, Tsst);
        Cbdt = sc.BaseDateTimeIn[Index];
        Pbdt = sc.BaseDateTimeIn[Index - 1];
        
        if (Cbdt >= Tssdt && Pbdt < Tssdt)
        {
            NewTradingSession = true;
            TradingSessionIndex[Index] = TradingSessionIndex[Index - 1] + 1;
        }
        else
        {
            NewTradingSession = false;
            TradingSessionIndex[Index] = TradingSessionIndex[Index - 1];
        }
        
        InputData[Index] = sc.BaseDataIn[InputDataIndex][Index];
        Vol[Index] = sc.BaseDataIn[SC_VOLUME][Index];
        
        if (NewTradingSession)
        {
            if (!DisplayHistorically)
            {
                int Ptslbi = Index - 1; // Previous trading session last bar index
                
                int a = Ptslbi - 1;
                
                while ( int(TradingSessionIndex[Ptslbi] + 0.5f) == int(TradingSessionIndex[a] + 0.5f) && a >= 0 )
                {
                    sc.Subgraph[0][a] = Vwap[Ptslbi];
                    sc.Subgraph[1][a] = Vwap[Ptslbi] + 1 * Vwsd[Ptslbi];
                    sc.Subgraph[2][a] = Vwap[Ptslbi] - 1 * Vwsd[Ptslbi];
                    sc.Subgraph[3][a] = Vwap[Ptslbi] + 2 * Vwsd[Ptslbi];
                    sc.Subgraph[4][a] = Vwap[Ptslbi] - 2 * Vwsd[Ptslbi];
                    sc.Subgraph[5][a] = Vwap[Ptslbi] + 3 * Vwsd[Ptslbi];
                    sc.Subgraph[6][a] = Vwap[Ptslbi] - 3 * Vwsd[Ptslbi];
                    
                    --a;
                }
            }
            
            if ( int(TradingSessionIndex[Index] + 0.5f) >= NumberTradingSessions )
            {
                if (ResetRunningAverage)
                {
                    Rsidtv[Index - 1] = 0;
                    Rsv[Index - 1] = 0;
                    Rssd[Index - 1] = 0;
                    
                    TradingSessionIndex[Index] = 0;
                    FirstBarIndex = Index;
                }
                else
                {
                    while ( int(TradingSessionIndex[Index] + 0.5f) - int(TradingSessionIndex[FirstBarIndex] + 0.5f) > NumberTradingSessions )
                    {
                        Rsidtv[Index - 1] -= InputData[FirstBarIndex] * Vol[FirstBarIndex];
                        Rsv[Index - 1] -= Vol[FirstBarIndex];
                        Rssd[Index - 1] -= pow(InputData[FirstBarIndex] - Vwap[FirstBarIndex], 2) * Vol[FirstBarIndex];
                        
                        ++FirstBarIndex;
                    }
                }
            }
        }
        else
        {
            if (!ResetRunningAverage)
            {
                SCDateTime FirstBarofRunningAverageDateTime;
                int CurrentBarTime;
                int FirstBarofRunningAverageTime;
                int FirstBarofRunningAverageDate;
                
                CurrentBarTime = sc.BaseDateTimeIn[Index].GetTime();
                FirstBarofRunningAverageTime = sc.BaseDateTimeIn[FirstBarIndex].GetTime();
                
                if (CurrentBarTime < Tsst && FirstBarofRunningAverageTime >= Tsst)
                {
                    FirstBarofRunningAverageDate = sc.BaseDateTimeIn[FirstBarIndex].GetDate() + 1;
                }
                else
                {
                    FirstBarofRunningAverageDate = sc.BaseDateTimeIn[FirstBarIndex].GetDate();
                }
                
                FirstBarofRunningAverageDateTime = COMBINE_DATE_TIME(FirstBarofRunningAverageDate, CurrentBarTime);
                
                
                while (FirstBarofRunningAverageDateTime >= sc.BaseDateTimeIn[FirstBarIndex] && 
                int(TradingSessionIndex[Index] + 0.5f) - int(TradingSessionIndex[FirstBarIndex] + 0.5f) == NumberTradingSessions)
                {
                    Rsidtv[Index - 1] -= InputData[FirstBarIndex] * Vol[FirstBarIndex];
                    Rsv[Index - 1] -= Vol[FirstBarIndex];
                    Rssd[Index - 1] -= pow(InputData[FirstBarIndex] - Vwap[FirstBarIndex], 2) * Vol[FirstBarIndex];                
                    
                    ++FirstBarIndex;
                }
            }        
        }
        
        Rsidtv[Index] = InputData[Index] * Vol[Index] + Rsidtv[Index - 1];
        Rsv[Index] = Vol[Index] + Rsv[Index - 1];
            
        if (Rsv[Index] > 0)
        {
            Vwap[Index] = Rsidtv[Index] / Rsv[Index];
            Rssd[Index] = pow(InputData[Index] - Vwap[Index], 2) * Vol[Index] + Rssd[Index - 1];
            Vwsd[Index] = sqrt(Rssd[Index] / Rsv[Index]);
        }
        else
        {
            Vwap[Index] = 0;
            Rssd[Index] = 0;
            Vwsd[Index] = 0;
        }
            
            
        if (!DisplayHistorically && Index == sc.ArraySize - 1)
        {
            int Ctslbi = Index; // Current trading session last bar index
            
            int a = Ctslbi - 1;
            
            while ( int(TradingSessionIndex[Ctslbi] + 0.5f) == int(TradingSessionIndex[a] + 0.5f) && a >= 0 )
            {
                sc.Subgraph[0][a] = Vwap[Ctslbi];
                sc.Subgraph[1][a] = Vwap[Ctslbi] + 1 * Vwsd[Ctslbi];
                sc.Subgraph[2][a] = Vwap[Ctslbi] - 1 * Vwsd[Ctslbi];
                sc.Subgraph[3][a] = Vwap[Ctslbi] + 2 * Vwsd[Ctslbi];
                sc.Subgraph[4][a] = Vwap[Ctslbi] - 2 * Vwsd[Ctslbi];
                sc.Subgraph[5][a] = Vwap[Ctslbi] + 3 * Vwsd[Ctslbi];
                sc.Subgraph[6][a] = Vwap[Ctslbi] - 3 * Vwsd[Ctslbi];
                
                --a;
            }
        }
        
        
        sc.Subgraph[0][Index] = Vwap[Index];
        sc.Subgraph[1][Index] = Vwap[Index] + 1 * Vwsd[Index];
        sc.Subgraph[2][Index] = Vwap[Index] - 1 * Vwsd[Index];
        sc.Subgraph[3][Index] = Vwap[Index] + 2 * Vwsd[Index];
        sc.Subgraph[4][Index] = Vwap[Index] - 2 * Vwsd[Index];
        sc.Subgraph[5][Index] = Vwap[Index] + 3 * Vwsd[Index];
        sc.Subgraph[6][Index] = Vwap[Index] - 3 * Vwsd[Index];
        sc.Subgraph[7][Index] = Index;
        sc.Subgraph[8][Index] = FirstBarIndex;
        sc.Subgraph[9][Index] = TradingSessionIndex[Index];
    }
}  

/************************************************************************/

SCSFExport scsf_VIDYA(SCStudyInterfaceRef sc)
{
	// Inputs
	SCInputRef InputData            = sc.Input[0];
	SCInputRef InputLength            = sc.Input[1];
	SCInputRef SigmaPeriod            = sc.Input[2];

	// Graphs
	SCSubgraphRef VIDYA                = sc.Subgraph[0];

	// Arrays
	SCFloatArrayRef CMO                = sc.Subgraph[0].Arrays[0];

	// Defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "VIDYA";
		sc.StudyDescription = "VIDYA (Variable Index Dynamic Average)";
		sc.GraphRegion = 0;

		// Inputs

		InputData.Name = "Input Data";
		InputData.SetInputDataIndex(SC_LAST);

		InputLength.Name = "Input Length";
		InputLength.SetInt(20);

		SigmaPeriod.Name = "Sigma Period";
		SigmaPeriod.SetInt(10);

		// Graphs

		VIDYA.Name = "VIDYA";
		VIDYA.DrawStyle = DRAWSTYLE_LINE;
		VIDYA.PrimaryColor = COLOR_CYAN;
		VIDYA.LineWidth = 2;

		// Set Graph Region
		sc.GraphRegion = 0;

		// Auto Looping On
		sc.AutoLoop = 1;

		// During development only set to 1
		sc.FreeDLL = 0;

		// Must return
		return;
	}

	//
	// CMO
	//

	float sum_up = 0;
	float sum_down = 0;
	for (int j = (sc.Index-InputLength.GetInt()+1);j<=sc.Index;j++)
	{
		if (sc.BaseData[InputData.GetInputDataIndex()][j]<sc.BaseData[InputData.GetInputDataIndex()][j-1])
		{
			sum_down += sc.BaseData[InputData.GetInputDataIndex()][j-1] - sc.BaseData[InputData.GetInputDataIndex()][j];
		}
		else if (sc.BaseData[InputData.GetInputDataIndex()][j]>sc.BaseData[InputData.GetInputDataIndex()][j-1])
		{
			sum_up += sc.BaseData[InputData.GetInputDataIndex()][j] - sc.BaseData[InputData.GetInputDataIndex()][j-1];
		}
	}

	float fCMO;

	if(sum_up+sum_down == 0)
		fCMO = CMO[sc.Index-1];
	else
		fCMO = 100.0f*((sum_up-sum_down)/(sum_up+sum_down));

	//
	// VIDYA
	//

	float absCMO = fabs(fCMO)/100;
	float sigmaConstant = 2/(float(SigmaPeriod.GetInt()+1));

	if (sc.Index == 0)
		VIDYA[sc.Index] = sc.Close[sc.Index];
	else
		VIDYA[sc.Index] = (sigmaConstant*absCMO*sc.Close[sc.Index]) + (1-(sigmaConstant*absCMO)) * VIDYA[sc.Index-1];

}  
/************************************************************************/