#include "sierrachart.h"

#define Sine			sc.Subgraph[0]
#define LeadSine		sc.Subgraph[1]
#define Smooth			sc.Subgraph[2]
#define Detrender		sc.Subgraph[3]
#define Q1				sc.Subgraph[4]
#define I1				sc.Subgraph[5]
#define jI				sc.Subgraph[6]
#define jQ				sc.Subgraph[7]
#define I2				sc.Subgraph[8]
#define Q2				sc.Subgraph[9]
#define Re				sc.Subgraph[10]
#define Im				sc.Subgraph[11]
#define DCPhase			sc.Subgraph[12]
#define SmoothPeriod	sc.Subgraph[13]
#define Period			sc.Subgraph[16]

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
#define BLUE RGB(0,128,255)
#define ORANGE RGB(255, 127, 0)
#define PI 3.1415926


SCSFExport scsf_HilbertSineWave(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "Hilbert Sine Wave";
		sc.StudyDescription = "Hilbert Sine Wave";
		sc.FreeDLL = 0;

		sc.AutoLoop = 1;  // true

		sc.GraphRegion = 1;

		// Set the name of the first subgraph
		sc.Subgraph[0].Name = "Sine";
		sc.Subgraph[0].PrimaryColor = CYAN ;
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE ;
		sc.Subgraph[0].LineWidth = 2 ;

		sc.Subgraph[1].Name = "LeadSine";
		sc.Subgraph[1].PrimaryColor = RED ;
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_LINE ;
		sc.Subgraph[1].LineWidth = 2 ;
		
		sc.Input[0].Name = "Input Data";
		sc.Input[0].SetInputDataIndex(SC_HL);
		
		return;
	}

	int i ;
	
	SCFloatArrayRef Price = sc.BaseDataIn[sc.Input[0].GetInputDataIndex()];
	
	sc.DataStartIndex=50;
	i = sc.CurrentIndex;

	// smooth
	Smooth[i] = (4*Price[i] + 3*Price[i-1] + 2*Price[i-2] + Price[i-3])*10; 		
	
	// detrender
	Detrender[i] = (0.0962*Smooth[i] + 0.5769*Smooth[i-2] - 0.5769*Smooth[i-4] - 0.0962*Smooth[i-6])*(0.075*Period[i-1] + 0.54); 		
		
	// compute InPhase and Quadrature components
	Q1[i] = (0.0962*Detrender[i] + 0.5769*Detrender[i-2] - 0.5769*Detrender[i-4] - 0.0962*Detrender[i-6])*(0.075*Period[i-1] + 0.54); 
	I1[i] = Detrender[i-3];
		
	// Advance the phase of I1 and Q1 by 90 degrees
	jI[i] = (0.0962*I1[i] + 0.5769*I1[i-2] - 0.5769*I1[i-4] - 0.0962*I1[i-6])*(0.075*Period[i-1] + 0.54); 
	jQ[i] = (0.0962*Q1[i] + 0.5769*Q1[i-2] - 0.5769*Q1[i-4] - 0.0962*Q1[i-6])*(0.075*Period[i-1] + 0.54);

	// Phasor addition for 3 bar averaging
	I2[i] = I1[i] - jQ[i]; 
	Q2[i] = Q1[i] + jI[i];
		
	// Smooth the I and Q components before applying the discriminator
	I2[i] = 0.2*I2[i] + 0.8*I2[i-1]; 
	Q2[i] = 0.2*Q2[i] + 0.8*Q2[i-1];
		
	// Homodyne Discriminator
	Re[i] = I2[i]*I2[i-1] + Q2[i]*Q2[i-1]; 
	Im[i] = I2[i]*Q2[i-1] - Q2[i]*I2[i-1]; 
	Re[i] = 0.2*Re[i] + 0.8*Re[i-1]; 
	Im[i] = 0.2*Im[i] + 0.8*Im[i-1]; 
		
	if (Im[i] != 0.0 && Re[i] != 0.0)
		Period[i] = 360/(180/PI*atan(Im[i]/Re[i]));
	if (Period[i] > 1.5*Period[i-1])
		Period[i] = 1.5*Period[i-1];
	if (Period[i] < 0.67*Period[i-1])
		Period[i] = 0.67*Period[i-1] ;
	if (Period[i] < 6)
		Period[i] = 6 ;
	if (Period[i] > 50)
		Period[i] = 50 ;
	Period[i] = 0.2*Period[i] + 0.8*Period[i-1];
	SmoothPeriod[i] = 0.33*Period[i] + 0.67*SmoothPeriod[i-1];

	double DCPeriod, fractpart;
	fractpart = modf( SmoothPeriod[i] + 0.5 , &DCPeriod);
	
	double RealPart = 0;
	double ImagPart = 0;
		
	for (int count = 0; count < DCPeriod; count++) {
		RealPart = RealPart + sin(PI*2*count/DCPeriod ) * (Smooth[i-count]);
		ImagPart = ImagPart + cos(PI*2*count/DCPeriod ) * (Smooth[i-count]);
	}

	if (abs(ImagPart) > 0) DCPhase[i] = atan(RealPart /ImagPart )*180/PI;
	
	if (abs(ImagPart) <= 0.001) {
		if (RealPart >= 0) DCPhase[i] = DCPhase[i] + 90;
		if (RealPart < 0) DCPhase[i] = DCPhase[i] - 90;
	}
	
	DCPhase[i] = DCPhase[i] + 90;
	DCPhase[i] = DCPhase[i] +360/SmoothPeriod[i];

	if (ImagPart < 0) 
		DCPhase[i] = DCPhase[i] + 180;

	if (DCPhase[i] > 315)
		DCPhase[i] = DCPhase[i] - 360;
	
	
	Sine[i] = sin(PI/180*DCPhase[i])*100;
	
	LeadSine[i] = sin(PI/180*(DCPhase[i]+45))*100;
	
}
