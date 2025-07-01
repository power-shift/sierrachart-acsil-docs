#include "sierrachart.h"
double mycci(SCFloatArrayRef In, int pos, int ccilength, float ccifactor);
int ckpos2( int pos2, int size, int reference);
float myhomodyne(const float *Price, int pos, float *Array, float *SmoothPeriod);


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
#define LAST Last[pos]

#if  0                                // 1 = dll is freed up, this allows debugging. Change back to 0 when code is complete
#define UNLOCKDLL 1                   // 1 = dll is freed up, this allows debugging. Change back to 0 when code is complete
#define LOCKTEXT "DLLs are UnLocked"  // if UNLOCKDLL =0 LOCKTEXT = "Locked" else set it to "UnLocked"
#else
#define UNLOCKDLL 0                   // 1 = dll is freed up, this allows debugging. Change back to 0 when code is complete
#define LOCKTEXT "DLLs are Locked"    // if UNLOCKDLL =0 LOCKTEXT = "Locked" else set it to "UnLocked"
#endif

// This line is required.
// Change the text within the quote marks to what you want to name
// your group of custom studies.
//SCDLLInit("Dominant Cycle CCI") 

/***********************************************************************/
// October 13, 2005
// Version 1.0

// extern "C" __declspec( dllexport ) void ChoppyCCI(struct s_sc &sc)
SCSFExport scsf_CCIDominantCycle(SCStudyGraphRef sc)
{
	// Set configuration variables
	if (sc.SetDefaults)
	{
		sc.GraphName="CCI - Dominant Cycle";

		sc.StudyDescription="CCI using Dominant Cycle. Source code adapted from Rocket Science for Traders by John F. Ehlers, copyright 2001 by John F. Ehlers.";
		sc.ValueFormat = 0;
		sc.DrawZeros = 0;
		sc.ScaleRangeType = SCALE_USERDEFINED; 
		sc.ScaleRangeTop = 250.0f;
		sc.ScaleRangeBottom = -250.0f;
		
		sc.Subgraph[0].Name="DC Period";
		sc.Subgraph[0].PrimaryColor = BLACK;
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_HIDDEN;
		sc.Subgraph[1].Name="UpCCI";
		sc.Subgraph[1].PrimaryColor = GREEN;
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[1].LineStyle = LINESTYLE_SOLID;
		sc.Subgraph[1].LineWidth = 2;
		sc.Subgraph[2].Name="DownCCI";
		sc.Subgraph[2].PrimaryColor = RED;
		sc.Subgraph[2].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[2].LineStyle = LINESTYLE_SOLID;
		sc.Subgraph[2].LineWidth = 2;
		sc.Subgraph[3].Name="CCI";
		sc.Subgraph[3].SecondaryColorUsed = 1;
		sc.Subgraph[3].PrimaryColor = GREEN;
		sc.Subgraph[3].SecondaryColor = RED;
		sc.Subgraph[3].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[3].LineStyle = LINESTYLE_SOLID;
		sc.Subgraph[3].LineWidth = 2;
		sc.Subgraph[7].Name="Line";
		sc.Subgraph[7].PrimaryColor = BLACK;
		sc.Subgraph[7].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[7].LineStyle = LINESTYLE_DOT;
		sc.Subgraph[7].LineWidth = 1;
		sc.Subgraph[8].Name="Line";
		sc.Subgraph[8].PrimaryColor = BLACK;
		sc.Subgraph[8].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[8].LineStyle = LINESTYLE_SOLID;
		sc.Subgraph[8].LineWidth = 1;
		sc.Subgraph[9].Name="Line";
		sc.Subgraph[9].PrimaryColor = BLACK;
		sc.Subgraph[9].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[9].LineStyle = LINESTYLE_DOT;
		sc.Subgraph[9].LineWidth = 1;

		//	sc.Subgraph[13].Name="WorkSpaceBelow";
		//	sc.Subgraph[14].Name="WorkSpaceBelow";
		//	sc.Subgraph[15].Name="WorkSpaceBelow";

		sc.Input[0].Name="Select Input Type";
		sc.Input[0].SetInputDataIndex(SC_HLC);
		sc.Input[1].Name="";                                   // 1.0 Original try
		sc.Input[2].Name="";
		sc.Input[3].Name="Upper line (200)";
		sc.Input[3].SetInt(200);
		sc.Input[3].SetIntLimits(1,400);
		sc.Input[4].Name="Middle line (0)";
		sc.Input[4].SetInt(0);
		sc.Input[4].SetIntLimits(-400,400);
		sc.Input[5].Name="Lower line (-200)";
		sc.Input[5].SetInt(-200);
		sc.Input[5].SetIntLimits(-400, -1);
		return;
	}       
	sc.FreeDLL=UNLOCKDLL;
	if(sc.ArraySize<50) return;

	const float *Price=&sc.BaseDataIn[sc.Input[0].GetInt()][0];
	int     pos;
	int     cciprice=sc.Input[0].GetInt();
	double  sum0=0.0,cci=0.0;
	//float   lsmaangle=0.0,emaangle=0.0,lsma=0.0,location=0.0;

	float *SmoothPeriod=      &sc.Subgraph[13].Data[0]; 
	float *DC=                &sc.Subgraph[14].Data[0]; 
	float *WorkSpace =        &sc.Subgraph[15].Data[0];        // array space for function overhead
	SCFloatArrayRef line1=     sc.Subgraph[7];
	SCFloatArrayRef line2=     sc.Subgraph[8];
	SCFloatArrayRef line3=     sc.Subgraph[9];

	int upper=sc.Input[3].GetInt();
	int middle=sc.Input[4].GetInt();
	int lower=sc.Input[5].GetInt();

	sc.DataStartIndex=50;

	for (pos= max(sc.DataStartIndex,sc.UpdateStartIndex); pos < sc.ArraySize;pos++)
	{

		SmoothPeriod[pos]= myhomodyne( Price, pos, WorkSpace, SmoothPeriod);
		DC[pos]= int(SmoothPeriod[pos] + .5);
		//     ccilength= int(SmoothPeriod[pos] + .5);

		// Calculate CCI
		cci=mycci(sc.BaseDataIn[cciprice],pos,int(DC[pos]),0.015);
		sc.Subgraph[0][pos] = DC[pos];
		if (cci>0.0) sc.Subgraph[1][pos]=cci; else sc.Subgraph[1][pos]=0.0;
		if (cci<0.0) sc.Subgraph[2][pos]=cci; else sc.Subgraph[2][pos]=0.0;
		sc.Subgraph[3][pos]=cci;
		if(sc.Subgraph[3][pos]>=0.0) sc.Subgraph[3].DataColor[pos]=sc.Subgraph[3].PrimaryColor ; else
			sc.Subgraph[3].DataColor[pos]=sc.Subgraph[3].SecondaryColor ;        
		line1[pos]=upper;
		if(middle==0)line2[pos]=middle+0.0000001; else line2[pos]=middle;
		line3[pos]=lower;
	}
};
float myhomodyne(const float *Price, int pos, float *Array, float *SmoothPeriod)
{

	int pos2, size=10;
	float *Smooth=        &Array[10]; // need multiple arrays, so parsing up one of the available arrays
	float *Detrender=     &Array[20]; //                      ""
	float *I1=            &Array[30]; //                      ""
	float *Q1=            &Array[40]; //                      ""
	float *jI=            &Array[50]; //                      ""
	float *jQ=            &Array[60]; //                      ""
	float *I2=            &Array[70]; //                      ""
	float *Q2=            &Array[80]; //                      ""
	float *Re=            &Array[90]; //                      ""
	float *Im=            &Array[100]; //                      ""
	float *Period=        &Array[110]; // need multiple arrays, so parsing up one of the available arrays
	{
		pos2=pos%size;
		Smooth[pos2]=(4.0*Price[pos]+3.0*Price[pos-1]+2.0*Price[pos-2]+Price[pos-3])/10.0;
		Detrender[pos2]=(.0962*Smooth[pos2]+.5769*Smooth[ckpos2(pos2,size,-2)]-.5769*Smooth[ckpos2(pos2,size,-4)]-.0962*Smooth[ckpos2(pos2,size,-6)])*(.075*Period[ckpos2(pos2,size,-1)]+.54);

		// Compute InPhase and Quadrature componenets
		Q1[pos2]=(.0962*Detrender[pos2]+.5769*Detrender[ckpos2(pos2,size,-2)]-.5769*Detrender[ckpos2(pos2,size,-4)]-.0962*Detrender[ckpos2(pos2,size,-6)])*(.075*Period[ckpos2(pos2,size,-1)]+.54);
		I1[pos2]=Detrender[ckpos2(pos2,size,-3)];

		// Advance the phase of I1 and Q1 by 90 degrees
		jI[pos2]=(.0962*I1[pos2]+.5769*I1[ckpos2(pos2,size,-2)]-.5769*I1[ckpos2(pos2,size,-4)]-.0962*I1[ckpos2(pos2,size,-6)])*(.075*Period[ckpos2(pos2,size,-1)]+.54);
		jQ[pos2]=(.0962*Q1[pos2]+.5769*Q1[ckpos2(pos2,size,-2)]-.5769*Q1[ckpos2(pos2,size,-4)]-.0962*Q1[ckpos2(pos2,size,-6)])*(.075*Period[ckpos2(pos2,size,-1)]+.54);

		// Phasor additon for 3 bar averaging
		I2[pos2]=I1[pos2]-jQ[pos2];
		Q2[pos2]=Q1[pos2]+jI[pos2];

		// Smooth the I and Q components before applying the discriminator
		I2[pos2]=.2*I2[pos2]+.8*I2[ckpos2(pos2,size,-1)];                      ;
		Q2[pos2]=.2*Q2[pos2]+.8*Q2[ckpos2(pos2,size,-1)];

		// Homodyne Discriminator
		Re[pos2]=I2[pos2]*I2[ckpos2(pos2,size,-1)]+Q2[pos2]*Q2[ckpos2(pos2,size,-1)];
		Im[pos2]=I2[pos2]*Q2[ckpos2(pos2,size,-1)]-Q2[pos2]*I2[ckpos2(pos2,size,-1)];
		Re[pos2]=.2*Re[pos2]+.8*Re[ckpos2(pos2,size,-1)];
		Im[pos2]=.2*Im[pos2]+.8*Im[ckpos2(pos2,size,-1)];
		if ((Im[pos2]!=0.0) && (Re[pos2]!=0.0)) Period[pos2]=360.0/(57.3*atan(Im[pos2]/Re[pos2]));
		if (Period[pos2]>1.5*Period[ckpos2(pos2,size,-1)]) Period[pos2]=1.5*Period[ckpos2(pos2,size,-1)];
		if (Period[pos2]<.67*Period[ckpos2(pos2,size,-1)]) Period[pos2]=.67*Period[ckpos2(pos2,size,-1)];
		if (Period[pos2]<6.0) Period[pos2]=6.0;
		if (Period[pos2]>50.0) Period[pos2]=50.0;
		Period[pos2]=.2*Period[pos2]+.8*Period[ckpos2(pos2,size,-1)];
		SmoothPeriod[pos]=.33*Period[pos2]+.67*SmoothPeriod[pos-1];
	}
	return int(SmoothPeriod[pos]);
} 
double mycci(SCFloatArrayRef In, int pos, int ccilength, float ccifactor)

{
	double cci=0.0, md1=0.0;
	if (ccilength<=0) return 0.0;
	// Calculate CCI
	if ( pos>=ccilength)
	{
		double total=0.0;
		md1=0.0;
		for (int i=0; i<ccilength; i++)
		{
			total=total+In[pos-i];
		}
		double ma=total/ccilength;
		for (int i=0; i<ccilength; i++)
		{
			md1=md1+fabs(ma - In[pos-i]);
		}
		md1=md1/ccilength;
		cci=(In[pos]-ma)/(ccifactor*md1);
		return cci;
	} else
		return 0.0;
}

int ckpos2( int pos2, int size, int reference)

{
	if ((pos2+reference)<0)
		return size+pos2+reference; else
		return pos2+reference;
}
