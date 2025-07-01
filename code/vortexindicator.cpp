#include "sierrachart.h"


float myFAMA(SCStudyGraphRef sc, SCFloatArrayRef Price, int i, SCFloatArrayRef FAMA);

int outLen;
// Vortex indicator
// Adapted for SC by ertrader
// from Technical analysis of Stocks and commodities
// January 2010
// Page 21
// Backtest results are on page 80
// Modifications:
// Added histogram and added auto length

// the following define words for common usage
#define FALSE 0
#define TRUE 1
#define LONG 1
#define SHORT -1
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
#define BLUE RGB(0,0,255)
#define ORANGE RGB(255, 127, 0)
#define DRKBLUE RGB(0, 0, 127)

//SCDLLInit("VortexIndicator")




SCSFExport scsf_VortexIndicator(SCStudyGraphRef sc)
{

	SCSubgraphRef vip	 		= 		sc.Subgraph[0];
	SCSubgraphRef vim	 		= 		sc.Subgraph[1];
	SCSubgraphRef vihist 		= 		sc.Subgraph[2];
	SCSubgraphRef line0 		= 		sc.Subgraph[3];	
	
	SCInputRef INperiod	 		= 		sc.Input[0];
	SCInputRef INadaptive		=		sc.Input[1];
	SCInputRef INhistogram		=		sc.Input[2];
	
	if (sc.SetDefaults)
	{
		sc.GraphName = "Vortex Indicator";
		sc.StudyDescription = "Here is an updated vortex indicator with the option to display as a histogram and to include auto lengths. <a href=""http://www.sierrachart.com/supportboard/showthread.php?p=145193#post145193"">Discussion subtopic (A little help for a dll tool I'm making)</a>";
        sc.DrawZeros = 0;
        sc.AutoLoop = 1;
        sc.GraphRegion = 1;
		sc.FreeDLL=0; // 1 = dll is freed up, this allows debugging. Change back to 0 when code is complete
		
		vip.Name = "VI+";
		vip.PrimaryColor = BLUE;
		vip.LineWidth = 3;
		
		vim.Name = "VI-";
		vim.PrimaryColor = RED;
		vim.LineWidth = 3;		
		
		// In SC subgraph, to draw histogram, change drawstyle on VI histogram to DRAWSTYLE_BAR 
		// then change VI+ and VI- to DRAWSTYLE_IGNORE
		vihist.Name = "VI Histogram";
		vihist.PrimaryColor = BLUE;
		vihist.SecondaryColor = RED;		
		vihist.LineWidth = 3;		

		// use to draw a line at 0 
		line0.Name="Line 0";
        line0.LineWidth = 1;
        line0.PrimaryColor = YELLOW;
		
		INadaptive.Name = "Adaptive Period? (1-Yes,0-No)?";
		INadaptive.SetInt(1);
        INadaptive.SetIntLimits(0,1);		

		INhistogram.Name = "Draw Histogram? (1-Yes,0-No)?";
		INhistogram.SetInt(1);
        INhistogram.SetIntLimits(0,1);
		
		INperiod.Name = "Period";
		INperiod.SetInt(14);
        INperiod.SetIntLimits(2,200);
		
		return;
	}

	SCFloatArrayRef H 			= sc.Subgraph[0].Arrays[0];
	SCFloatArrayRef L		 	= sc.Subgraph[0].Arrays[1];
	SCFloatArrayRef vmp			= sc.Subgraph[0].Arrays[2];
	SCFloatArrayRef vmm			= sc.Subgraph[0].Arrays[3];
	SCFloatArrayRef str			= sc.Subgraph[0].Arrays[4];	
	SCFloatArrayRef HL			= sc.Subgraph[0].Arrays[5];
	SCFloatArrayRef LH			= sc.Subgraph[0].Arrays[6];	
	SCFloatArrayRef TR			= sc.Subgraph[0].Arrays[7];	
	SCFloatArrayRef PriceHL		= sc.Subgraph[1].Arrays[0];
	SCFloatArrayRef ma			= sc.Subgraph[1].Arrays[1];	
	SCFloatArrayRef FAMA		= sc.Subgraph[1].Arrays[2];	
	
	int period 					= INperiod.GetInt();
	int adaptive 				= INadaptive.GetInt();
	int histogram				= INhistogram.GetInt();
  	int i 						= sc.Index;
			
	// get the High, Low and HL
	H 							= sc.BaseDataIn[SC_HIGH];
	L 							= sc.BaseDataIn[SC_LOW];
	PriceHL 					= sc.BaseDataIn[SC_HL];	
	
	// adaptive length.  If adaptive,  call Dominant Cycle FAMA code to get length.
	if (adaptive == 1) 
	{
		// autolength code
		ma[i] = myFAMA(sc, PriceHL, i, FAMA);
		// used global variable from myFAMA
		period = outLen;
	}		
		// if not use manual input
		else period = INperiod.GetInt();
	
	// determine which to draw, VI+, VI- or in histogram format
	if	(histogram ==1)
		{
		// if histogram, draw line and bar and ignore others
		vihist.DrawStyle = DRAWSTYLE_BAR;	
        line0.DrawStyle = DRAWSTYLE_LINE;	
		vip.DrawStyle = DRAWSTYLE_IGNORE;
		vim.DrawStyle = DRAWSTYLE_IGNORE;	
		}
		else
		{
		// if no histogram, just draw VIP and VIM 
		vihist.DrawStyle = DRAWSTYLE_IGNORE;	
        line0.DrawStyle = DRAWSTYLE_IGNORE;	
		vip.DrawStyle = DRAWSTYLE_LINE;
		vim.DrawStyle = DRAWSTYLE_LINE;			
		}
	// start displaying after period is determined
	sc.DataStartIndex = period;	

	// calculate the VM plus
	HL[i] = fabs(H[i]-L[i-1]);
	sc.Summation(HL,vmp,i,period);
	
	// Calculate the VM minus
	LH[i] = fabs(L[i]-H[i-1]);
	sc.Summation(LH,vmm,i,period);	
	
	// get the true ranges
	sc.TrueRange(sc.BaseDataIn,TR,i);
	
	// get the summation of the true range
	sc.Summation(TR,str,i,period);	
	
	// calculate the Velocity Indicator Pluse VI+
	vip[i] = vmp[i]/str[i];
	
	// calculate the Velocity Indicator Minus VI-	
	vim[i] = vmm[i]/str[i];
	
	// calculat the vi histogram
	vihist[i] = vip[i] - vim[i];
	
	// Draw line 0
	line0[i] = 0.000000001f;
	
}
float myFAMA(SCStudyGraphRef sc, SCFloatArrayRef Price, int i, SCFloatArrayRef FAMA)
{
	// John Ehlers Dominant Cycle code for SC
	 SCFloatArrayRef Phase = 			sc.Subgraph[22].Arrays[1];
	 SCFloatArrayRef MAMA =				sc.Subgraph[22].Arrays[2];
	 //SCFloatArrayRef FAMA =				sc.Subgraph[22].Arrays[3];
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
	float FastLimit = sc.Input[10].GetFloat() ;
	float SlowLimit = sc.Input[11].GetFloat() ;
	float alpha, DeltaPhase;
	
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
	outLen = int(SmoothPeriod[i]);
	if (I1[i] != 0)	
		Phase[i] = 57.3f*atan(Q1[i]/I1[i]) ;	
		
	DeltaPhase = Phase[i-1] - Phase[i] ;
	
	if (DeltaPhase < 1) DeltaPhase = 1 ;
		
	alpha = FastLimit / DeltaPhase ;
	if (alpha < SlowLimit) alpha = SlowLimit ;
	
	MAMA[i] = alpha*Price[i] + (1 - alpha)*MAMA[i-1];
	FAMA[i] = 0.5f*alpha*MAMA[i] + (1 - 0.5f*alpha)*FAMA[i-1];
	return FAMA[i];
}
