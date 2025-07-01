#include "sierrachart.h"

#define ADXVMA			sc.Subgraph[0]
#define DI_Sum			sc.Subgraph[3]
#define ma				sc.Subgraph[4]
#define pdm				sc.Subgraph[5]
#define mdm				sc.Subgraph[6]
#define pdi				sc.Subgraph[7]
#define mdi				sc.Subgraph[8]
#define HHV				sc.Subgraph[12]
#define LLV				sc.Subgraph[13]
#define out				sc.Subgraph[14]

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

SCSFExport scsf_ADXVMA(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "ADXVMA";
		sc.StudyDescription = "ADXVMA";
		sc.FreeDLL = 0;

		sc.AutoLoop = 1;  // true

		sc.GraphRegion = 0;

		// Set the name of the first subgraph
		sc.Subgraph[0].Name = "ADXVMA";
		sc.Subgraph[0].PrimaryColor = RED ;
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_POINT ;
		sc.Subgraph[0].LineWidth = 2 ;

		sc.Input[0].Name = "Input Data";
		sc.Input[0].SetInputDataIndex(SC_LAST);
		
		sc.Input[1].Name = "Length";
		sc.Input[1].SetInt(14);
		
		sc.Input[2].Name = "RisingColor";
		sc.Input[2].SetColor(BLUE);
		
		sc.Input[3].Name = "FlatColor";
		sc.Input[3].SetColor(YELLOW);
		
		sc.Input[4].Name = "FallingColor";
		sc.Input[4].SetColor(RED);

		return;
	}

	int i ;
	
	SCFloatArrayRef Price = sc.BaseDataIn[sc.Input[0].GetInputDataIndex()];
	int len = sc.Input[1].GetInt();
	
	sc.DataStartIndex = len;
	i = sc.CurrentIndex;
	
	ma[i] = Price[i];
	
	if (Price[i] > Price[i-1]) {
		pdm[i] = Price[i] - Price[i-1];
		mdm[i] = mdm[i-1];
	}
	else if (Price[i] < Price[i-1]) {
		mdm[i] = Price[i-1] - Price[i]; //This array is not displayed.
		pdm[i] = pdm[i-1];
	}
	else {
		mdm[i] = 0.0f;
		pdm[i] = pdm[i-1];
	}
	

	pdm[i] = ((len - 1) * pdm[i-1] + pdm[i]) / len; //ema.
	mdm[i] = ((len - 1) * mdm[i-1] + mdm[i]) / len; //ema.

	float TR = pdm[i] + mdm[i];
	
	if (TR > 0) 
	{
		pdi[i] =pdm[i] / TR;
		mdi[i] = mdm[i] / TR;
	}
	else 
	{
		pdi[i] = 0;
		mdi[i] = 0;
	}
	
	pdi[i] = ((len - 1) * pdi[i-1] + pdi[i]) / len; //ema.
	mdi[i] = ((len - 1) * mdi[i-1] + mdi[i]) / len; //ema.
	
	double DI_Diff = pdi[i] - mdi[i];
 
	if (DI_Diff < 0) DI_Diff = -DI_Diff; //Only positive momentum signals are used.

	DI_Sum[i] = pdi[i] + mdi[i];
	double DI_Factor = 0; //Zero case, DI_Diff will also be zero when DI_Sum i  s zero.

	if (DI_Sum[i] > 0)
		out[i] = (float) DI_Diff / DI_Sum[i];
	else 
		out[i]= 0;

	out[i] = ((len - 1) * out[i-1] + out[i]) / len;

	if (out[i] > out[i-1]) {
		HHV[i] = out[i];
		LLV[i] = out[i-1];
	} 
	else {
		HHV[i] = out[i-1];
		LLV[i] = out[i];
	}

	for (int j = 1; j < len; j++) {    
		if (out[i-j-1] > HHV[i]) HHV[i] = out[i-j-1];
		if (out[i-j-1] < LLV[i]) LLV[i] = out[i-j-1];
	}

	double diff = HHV[i] - LLV[i];
	double VI = 0;

	if (diff > 0) 
		VI = (out[i] - LLV[i]) / diff;

	ma[i] = (float) ((len - VI) * ma[i-1] + VI * Price[i]) / len; //Chande VMA formula with ema built in.

	ADXVMA[i] = ma[i];
	if (ADXVMA[i] > ADXVMA[i-1]) sc.Subgraph[0].DataColor[i] = sc.Input[2].GetColor();
	else if (ADXVMA[i] < ADXVMA[i-1]) sc.Subgraph[0].DataColor[i] = sc.Input[4].GetColor();
	else if (ADXVMA[i] == ADXVMA[i-1]) sc.Subgraph[0].DataColor[i] = sc.Input[3].GetColor();
}
