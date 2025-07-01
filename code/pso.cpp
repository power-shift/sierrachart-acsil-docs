#include "sierrachart.h"

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

//SCDLLInit("PSO")



SCSFExport scsf_PSO(SCStudyGraphRef sc)
{

	SCSubgraphRef pso 			= 		sc.Subgraph[0];
	SCSubgraphRef line0 		= 		sc.Subgraph[1];
	SCSubgraphRef lineouter1 	= 		sc.Subgraph[2];
	SCSubgraphRef lineouter2 	= 		sc.Subgraph[3];
	SCSubgraphRef lineinner1 	= 		sc.Subgraph[4];
	SCSubgraphRef lineinner2 	= 		sc.Subgraph[5];	
	SCSubgraphRef s 			= 		sc.Subgraph[6];
	
	SCInputRef INperiod 	= 		sc.Input[0];
	SCInputRef INstlength 	=		sc.Input[1];
	SCInputRef INmatype 	=		sc.Input[2];
	SCInputRef INouter 		=		sc.Input[3];
	SCInputRef INinner 		=		sc.Input[4];	
	
	if (sc.SetDefaults)
	{
		// Stocks and Commodities August 2008 
		// Premier Stochastic Oscillator Page 30
		
		sc.GraphName = "Premier Stochastic Oscillator";
		sc.StudyDescription = "Here is an interesting modification of the stochastic oscillator. I (tcast) wrote it from this months S&C article starting on page 30 called Premier Stochastic Oscillator. It's actually not bad.... surprisingly!";

        sc.DrawZeros = 0;
        sc.AutoLoop = 1;
        sc.GraphRegion = 1;
		sc.FreeDLL= 0 ; // 1 = dll is freed up, this allows debugging. Change back to 0 when code is complete
		
		pso.Name = "PSO";
		pso.DrawStyle = DRAWSTYLE_BAR;
		pso.PrimaryColor = BLUE;
		pso.SecondaryColor = RED;
		pso.LineWidth = 3;
		
		lineouter1.Name = "Outer Line 1";
		lineouter1.DrawStyle = DRAWSTYLE_LINE;
		lineouter1.PrimaryColor = ORANGE;

		lineouter2.Name = "Outer Line 2";
		lineouter2.DrawStyle = DRAWSTYLE_LINE;
		lineouter2.PrimaryColor = ORANGE;
		
		lineinner1.Name = "Inner Line 1";
		lineinner1.DrawStyle = DRAWSTYLE_LINE;
		lineinner1.PrimaryColor = RED;
			
		lineinner2.Name = "Inner Line 2";
		lineinner2.DrawStyle = DRAWSTYLE_LINE;
		lineinner2.PrimaryColor = RED;
		
		line0.Name = "Zero Line";
		line0.DrawStyle = DRAWSTYLE_LINE;
		line0.PrimaryColor = YELLOW;
		
		INperiod.Name = "Input Period";
        INperiod.SetInt(25);
        INperiod.SetIntLimits(1,100);
		
		INstlength.Name = "Stochastic Length";
        INstlength.SetInt(8);
        INstlength.SetIntLimits(2,25);
		
		INmatype.Name = "Moving Average Type";
		INmatype.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		
		INouter.Name = "Input Outer Limits";
        INouter.SetFloat(.9f);
        INouter.SetFloatLimits(0,1000);
		
		INinner.Name = "Input Inner Limits";
        INinner.SetFloat(.2f);
        INinner.SetFloatLimits(0,1000);
		
		return;
	}
	

	SCFloatArrayRef nsto = 		sc.Subgraph[20].Arrays[0];
	SCFloatArrayRef ssto = 		sc.Subgraph[20].Arrays[1];
	SCFloatArrayRef Ma1 = 		sc.Subgraph[20].Arrays[3];
    
	unsigned long DFI  = 		INmatype.GetInputDataIndex();
	int x = 					INstlength.GetInt();
	int y = 					INperiod.GetInt();
	float outer = 				INouter.GetFloat();
	float inner = 				INinner.GetFloat();
	int len = 					sqrt((float)y);
	int i;

	sc.DataStartIndex = x;
	i = sc.Index;
	
	sc.Stochastic(sc.BaseDataIn, s, i , x, 1, 1, DFI);
	nsto[i] = .1f*(s[i]-50);
	sc.MovingAverage(nsto,Ma1,DFI,i,len);
	sc.MovingAverage(Ma1,ssto,DFI,i,len);
	pso[i] = (exp(ssto[i])-1)/(exp(ssto[i])+1);

	if(pso[i]>=0) pso.DataColor[i]=pso.PrimaryColor; else
	pso.DataColor[i]=pso.SecondaryColor;	
	
	// Draw line 0
	line0[i] = 0.000000001f;

	// oute lines 
	lineouter1[i] = outer;
	lineouter2[i] = -outer;
	
	// inner line
	lineinner1[i] = inner;
	lineinner2[i] = -inner;
}
