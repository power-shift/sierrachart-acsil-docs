#include "SierraChart.h"



/***********************************************************************/
SCSFExport scsf_rMA(SCStudyGraphRef sc)
{
  if (sc.SetDefaults)
	{
	sc.GraphName="rma";
    sc.StudyDescription="EMAs that restart each day";
	sc.Subgraph[0].Name="Ema1";
	sc.Subgraph[1].Name="Ema2";
	sc.Input[0].Name="OHLC";
	sc.Input[2].Name="Offset from 1st bar";
	sc.Input[3].Name="Number of bars to continue showing extra emas";

	sc.Input[5].Name="Ema1 length";
	sc.Input[6].Name="Ema2 length";
	if(sc.Input[5].FloatValue==0) sc.Input[5].FloatValue=21;
	if(sc.Input[6].FloatValue==0) sc.Input[6].FloatValue=34;
	sc.DrawZeros=0;
	sc.GraphRegion=0;
    sc.FreeDLL=0; 
    return;
	}

	int		pos;
	float	fac1=0, fac1i=0, fac2=0, fac2i=0;
	
	float& bar= sc.Subgraph[6].Data[4];  
	float& ohlc = sc.Input[0].FloatValue;
	float& offset = sc.Input[2].FloatValue;
	float& barmax = sc.Input[3].FloatValue;

	fac1=2/(sc.Input[5].FloatValue+1); fac1i= 1-fac1;
	fac2=2/(sc.Input[6].FloatValue+1); fac2i= 1-fac2;

	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++,bar++)
	{

		if (sc.BaseDateTimeIn[pos-1].GetDate()!=sc.BaseDateTimeIn[pos-2].GetDate() && pos>50)
		 {sc.Subgraph[0].Data[pos-1]=sc.BaseDataIn[ohlc][pos-1+offset]; sc.Subgraph[1].Data[pos-1]=sc.BaseDataIn[ohlc][pos-1+offset]; bar=0;};

		if(bar<=barmax)
		{
			sc.Subgraph[0].Data[pos] = (fac1i*sc.Subgraph[0].Data[pos-1]) + (fac1*sc.BaseDataIn[3][pos]);
			sc.Subgraph[1].Data[pos] = (fac2i*sc.Subgraph[1].Data[pos-1]) + (fac2*sc.BaseDataIn[3][pos]);
		} else
		{	sc.Subgraph[0].Data[pos]=0; sc.Subgraph[1].Data[pos]=0;}
	}

}


/***********************************************************************/
SCSFExport scsf_wMACD(SCStudyGraphRef sc)
{
  if(sc.SetDefaults)
  {
    sc.GraphName="wMACD";
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
	sc.Input[6].SetFloat(0.0);

	sc.Input[7].Name="SMA Length";
	sc.Input[7].SetFloat(5);


	

	sc.DrawZeros=1;
	sc.FreeDLL=0; 

	return;
  }
	
	sc.Subgraph[0].SecondaryColorUsed = 1;

	sc.Subgraph[2].SecondaryColorUsed = 1;

 	
    if(sc.ArraySize<100)
		return;

	int    c,pos,spoint;
	float  sum3=0,sum4=0,sum5=0,high=0,low=99999,
           factor1,factor2,factor3,csum3,csum4,csum5;
	
	
    if(sc.Input[2].BooleanValue)
    {	factor1 = 2/(sc.Input[3].FloatValue+1);	factor2 = 2/(sc.Input[4].FloatValue+1);	factor3 = 2/(sc.Input[5].FloatValue+1);} else
	{   csum3=(sc.Input[3].FloatValue*(sc.Input[3].FloatValue+1))/2;	csum4=(sc.Input[4].FloatValue*(sc.Input[4].FloatValue+1))/2;	csum5=(sc.Input[5].FloatValue*(sc.Input[5].FloatValue+1))/2;};
	

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
}


/***********************************************************************/
SCSFExport scsf_wStoch(SCStudyGraphRef sc)
{
if(sc.SetDefaults)
  {
	sc.GraphName="Stoch with SMA";
    sc.StudyDescription="Watts Stoch";
	sc.Subgraph[0].Name="K";
	sc.Subgraph[1].Name="D";
	sc.Subgraph[2].Name="Line 1";
	sc.Subgraph[3].Name="Line 2";
	sc.Subgraph[4].Name="MA";

	sc.Input[2].Name="L";
	sc.Input[2].SetFloat(8);

    sc.Input[3].Name="K";
	sc.Input[3].SetFloat(3);

	sc.Input[4].Name="D";
	sc.Input[4].SetFloat(3);

	sc.Input[5].Name="Line 1 Value";
	sc.Input[5].SetFloat(0);

	sc.Input[6].Name="Line 2 Value";
	sc.Input[6].SetFloat(0);

	sc.Input[7].Name="SMA Length";
	sc.Input[7].SetFloat(10);

    sc.FreeDLL=0;   

	return;
  } 

	if(sc.ArraySize<100)
		return;

   sc.Subgraph[0].SecondaryColorUsed = 1;
   int    pos,c,L;
   double  range, h, l, sk, sk1, sd, sd1, fk, factork, factord,K,D,sumk,sumd;


   L = (int)sc.Input[2].FloatValue;
 K = sc.Input[3].FloatValue;
    D = sc.Input[4].FloatValue;

   fk= sc.BaseDataIn[3][9]; sk=fk; sd=fk;
   factork=2/(K+1); factord=1/D; 
   float factors=2/(sc.Input[7].FloatValue+1); 

	sc.DataStartIndex=50;  sumk=0; sumd=0;
	int start = max(sc.UpdateStartIndex, 8);
	for (pos=start,c=1; pos < sc.ArraySize; pos++,c++)
	{
		h=0; l=9999999;
		for(int i=0;i<L;i++)
			{if(h<sc.BaseDataIn[1][pos-i]) h=sc.BaseDataIn[1][pos-i];
			 if(l>sc.BaseDataIn[2][pos-i]) l=sc.BaseDataIn[2][pos-i];
			}
		//fk=	sc.Subgraph[5].Data[pos]  sk=sc.Subgraph[6].Data[pos] sd=sc.Subgraph[7].Data[pos]
		range=(h-l);
		if(range>0) sc.Subgraph[5].Data[pos]=100*(sc.BaseDataIn[3][pos]-l)/range; else sc.Subgraph[5].Data[pos]=0;
		sk1=sk; sd1=sd;
		sc.Subgraph[6].Data[pos]=factork*sc.Subgraph[5].Data[pos] + (1-factork)*sc.Subgraph[6].Data[pos-1]; 
        sc.Subgraph[7].Data[pos]=factord*sc.Subgraph[6].Data[pos] + (1-factord)*sc.Subgraph[7].Data[pos-1];

		sc.Subgraph[0].Data[pos] = sc.Subgraph[6].Data[pos];
		sc.Subgraph[1].Data[pos] = sc.Subgraph[7].Data[pos];
		sc.Subgraph[2].Data[pos] = sc.Input[5].FloatValue;
		sc.Subgraph[3].Data[pos] = sc.Input[6].FloatValue;
		
		sc.Subgraph[4].Data[pos] = factors*sc.Subgraph[0].Data[pos] + (1-factors)*sc.Subgraph[4].Data[pos-1];     
        if( sc.Subgraph[0].Data[pos]>sc.Subgraph[0].Data[pos-1]) sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].PrimaryColor; else 
        if( sc.Subgraph[0].Data[pos]<sc.Subgraph[0].Data[pos-1]) sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].SecondaryColor;
	}
}


/***********************************************************************/
SCSFExport scsf_Volume(SCStudyInterfaceRef sc)
{
	SCSubgraphRef Vol = sc.Subgraph[0];
	SCSubgraphRef OeC = sc.Subgraph[1];
	SCSubgraphRef PGraph = sc.Subgraph[2];
	SCSubgraphRef OverVolColor = sc.Subgraph[3];
	SCSubgraphRef Temp9 = sc.Subgraph[9];

	SCInputRef MaxVolBarSize = sc.Input[3];
	SCInputRef Use2Colors = sc.Input[4];

	if(sc.SetDefaults)
	{
		sc.GraphName="Kiwis Volume Study";

		Vol.Name="Volume";
		Vol.DrawStyle = DRAWSTYLE_BAR;
		Vol.PrimaryColor = RGB(0,255,0);
		Vol.SecondaryColorUsed = 1;
		Vol.SecondaryColor = RGB(0,127,0);

		OeC.Name="O=C";
		OeC.DrawStyle = DRAWSTYLE_HIDDEN;
		OeC.PrimaryColor = RGB(255,0,255);

		PGraph.Name="P";
		PGraph.DrawStyle = DRAWSTYLE_POINT;
		PGraph.PrimaryColor = RGB(255,255,0);
		PGraph.SecondaryColorUsed = 1;
		PGraph.SecondaryColor = RGB(127,127,0);

		OverVolColor.Name="OverVol Color";
		OverVolColor.DrawStyle = DRAWSTYLE_IGNORE;
		OverVolColor.PrimaryColor = RGB(255,127,0);

		MaxVolBarSize.Name="Max Size of Vol Bar ";
		MaxVolBarSize.SetFloat(1500);

		Use2Colors.Name="Use Only 2 Colors";
		Use2Colors.SetYesNo(0);

		sc.FreeDLL=0;

		return;
	}

	int	pos, lookback=39;
	float vol, projection;
	s_UseTool Tool;    

	if(Temp9[1] != sc.BaseDateTimeIn[sc.ArraySize-1].GetTime() || sc.UpdateStartIndex==0)
	{
		for (int i=1; i<50; i++) // -1 = last object added, -2 = 2nd to last, etc
		{
			if (sc.GetUserDrawnChartDrawing(sc.ChartNumber, DRAWING_UNKNOWN, Tool, -i))
			{
				if(Tool.Region==sc.GraphRegion )  
				{
					if(Tool.DrawingType<=DRAWING_RAY) 
					{
						if(Tool.BeginValue > (Tool.EndValue-3) && Tool.BeginValue < (Tool.EndValue+3))
						{
							MaxVolBarSize.SetFloat(Tool.BeginValue*2);
							i=99999;
						}
					}
				}
			} 
			else 
				i=99999;
		}
	}
	Temp9[1] = (float)sc.BaseDateTimeIn[sc.ArraySize-1].GetTime();  // Seconds since 0:00

	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		if(sc.Close[pos]>sc.Open[pos]){Vol.DataColor[pos] = Vol.PrimaryColor;} else
			if(sc.Close[pos]<sc.Open[pos]){Vol.DataColor[pos] = Vol.SecondaryColor;} else
				if(!Use2Colors.GetYesNo()) {Vol.DataColor[pos] = OeC.PrimaryColor;} else
				{Vol.DataColor[pos] = Vol.DataColor[pos-1];};
		vol= fabs(sc.Volume[pos]);
		if(vol<MaxVolBarSize.GetFloat()) Vol[pos]=vol; else 
		{
			Vol[pos]=MaxVolBarSize.GetFloat();
			if(vol>1.1*MaxVolBarSize.GetFloat())
				Vol.DataColor[pos] = OverVolColor.PrimaryColor;
		};
	}

	pos=sc.ArraySize-1;
	if(fabs(sc.NumberOfTrades[pos])>3) // wait 3 ticks before putting volume up
	{
		projection=Vol[pos]/
			(float(sc.DateTimeOfLastFileRecord.GetTime()-sc.BaseDateTimeIn[pos].GetTime())/sc.SecondsPerBar);
	}

	if(projection > MaxVolBarSize.GetFloat()) 
	{
		projection = MaxVolBarSize.GetFloat(); 
		PGraph.DataColor[pos] = PGraph.SecondaryColor; 
	}
	else
		PGraph.DataColor[pos] = PGraph.PrimaryColor;

	PGraph[pos]=projection;
	PGraph[pos-1]=0; 
	PGraph[pos-40]=0; 
	OeC[pos]=0.0000000001f;
}

/***********************************************************************/
SCSFExport scsf_WeeklyPivot(SCStudyGraphRef sc)
{
	if(sc.Subgraph[8].Data[1]==sc.BaseDateTimeIn[sc.ArraySize-1].GetTime() && sc.UpdateStartIndex!=0) return;
	sc.Subgraph[8].Data[1]= sc.BaseDateTimeIn[sc.ArraySize-1].GetTime();

	if (sc.SetDefaults)
	{    
		sc.GraphName="W_P";
		sc.StudyDescription="Weekly High & Low";
		sc.Subgraph[0].Name="H1";        
		sc.Subgraph[1].Name="H"; 
		sc.Subgraph[2].Name="L";        
		sc.Subgraph[3].Name="L1"; 
		sc.Subgraph[6].Name="O";        
		sc.Subgraph[7].Name="C"; 
		sc.Input[3].Name="Weekly 0, Monthly 1, Annual 2";
		sc.Input[4].Name="Fix this month to hh & ll";
		sc.Input[4].ValueType=YESNO_VALUE; 
		sc.GraphRegion=0;
		sc.FreeDLL=0; 
		return;
	}


	int 	pos, Rollover;
	int& 	Start = sc.PersistVars->i1;
	int Year, Month, Day, Year1, Month1, Day1;
	float&  h=sc.Subgraph[8].Data[3];		float&  l=sc.Subgraph[8].Data[4];
	float&  sh=sc.Subgraph[8].Data[5];		float&  sl=sc.Subgraph[8].Data[6];
	float&  oo=sc.Subgraph[8].Data[7];		float&  cc=sc.Subgraph[8].Data[8];
	if(sc.UpdateStartIndex==0)
	{
		pos=1;	h=sc.BaseDataIn[1][pos]; l=sc.BaseDataIn[2][pos]; sh=h; sl=l;
	}


	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{	
		sc.BaseDateTimeIn[pos].GetDateYMD(Year, Month, Day);	sc.BaseDateTimeIn[pos-1].GetDateYMD(Year1, Month1, Day1);
		if( (sc.Input[3].FloatValue==0 && sc.BaseDateTimeIn[pos-1].GetDayOfWeek() > sc.BaseDateTimeIn[pos].GetDayOfWeek()) ||
			(sc.Input[3].FloatValue==1 && Month != Month1) ||
			(sc.Input[3].FloatValue==2 && Year != Year1)  )
		{ Rollover=1; Start=pos;}

		if(h<sc.BaseDataIn[1][pos]) h=sc.BaseDataIn[1][pos];
		if(l>sc.BaseDataIn[2][pos]) l=sc.BaseDataIn[2][pos];
		if(Rollover==1)	{ sh=h; sl=l; h=sc.BaseDataIn[1][pos]; l=sc.BaseDataIn[2][pos]; 
		oo=sc.BaseDataIn[0][pos]; cc=sc.BaseDataIn[3][pos-1]; Rollover=0;} 

		sc.Subgraph[0].Data[pos]=sh; 	
		sc.Subgraph[1].Data[pos]=h;
		sc.Subgraph[2].Data[pos]=l; 	
		sc.Subgraph[3].Data[pos]=sl;
		sc.Subgraph[6].Data[pos]=oo; 	
		sc.Subgraph[7].Data[pos]=cc;

		if(sc.Input[4].BooleanValue) 
		{ 
			for(int i=Start; i<sc.ArraySize-1; i++)
			{
				sc.Subgraph[1].Data[i]=h;
				sc.Subgraph[2].Data[i]=l; 
			}
		}; 
	};
}

/***********************************************************************/
SCSFExport scsf_Pivot_H(SCStudyGraphRef sc)
{
	if(sc.Subgraph[8].Data[1]==sc.BaseDateTimeIn[sc.ArraySize-1].GetTime() && sc.UpdateStartIndex!=0) return;
	sc.Subgraph[8].Data[1]= sc.BaseDateTimeIn[sc.ArraySize-1].GetTime();

	if (sc.SetDefaults)
	{    
		sc.GraphName="Pivots_Hourly";
		sc.StudyDescription="Hourly Pivots";
		sc.Subgraph[0].Name="R2";        
		sc.Subgraph[1].Name="R1"; 
		sc.Subgraph[2].Name="P";       
		sc.Subgraph[3].Name="S1";     
		sc.Subgraph[4].Name="S2";  
		sc.Subgraph[5].Name="R3";        
		sc.Subgraph[6].Name="S3";   
		sc.Subgraph[7].Name="R4";     
		sc.Subgraph[8].Name="S4";  
		sc.Subgraph[9].Name="R05"; 
		sc.Subgraph[10].Name="R15";
		sc.Subgraph[11].Name="R25";
		sc.Subgraph[12].Name="S05";
		sc.Subgraph[13].Name="S15"; 
		sc.Subgraph[14].Name="S25";
		sc.Subgraph[15].Name="RS35";
		sc.Input[3].Name="Divide Hour by: ";
		if(sc.Input[3].FloatValue==0) sc.Input[3].FloatValue = 1;
		sc.Input[4].Name="Offset to add to hours if start of multihour period is incorrect";
		sc.Input[5].Name="Use Minutes instead of Hours";
		sc.Input[5].ValueType=YESNO_VALUE;  
		sc.GraphRegion=0;
		sc.FreeDLL=0; 
		return;
	}

	float&  h=sc.Subgraph[8][3];          float&  l=sc.Subgraph[8][4];
	float&  sh=sc.Subgraph[8][5];         float&  sl=sc.Subgraph[8][6];
	float&  r2=sc.Subgraph[8][10];        float&  r1=sc.Subgraph[8][11];

	float&  pp=sc.Subgraph[8][12];        float&  scl=sc.Subgraph[8][13]; 
	float&  s1=sc.Subgraph[8][14];        float&  s2=sc.Subgraph[8][15];
	float&  r3=sc.Subgraph[8][16];        float&  s3=sc.Subgraph[8][17];
	float&  r4=sc.Subgraph[8][18];        float&  s4=sc.Subgraph[8][19];
	float&  r05=sc.Subgraph[8][20];       float&  s05=sc.Subgraph[8][21];
	float&  r15=sc.Subgraph[8][22];       float&  s15=sc.Subgraph[8][23];
	float&  r25=sc.Subgraph[8][24];       float&  s25=sc.Subgraph[8][25];
	float&  r35=sc.Subgraph[8][26];       float&  s35=sc.Subgraph[8][27];

	int pos;
	int H1, M1, M2, S1, H2, firsttime;
	float k1,k2;

	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		sc.BaseDateTimeIn[pos-1].GetTimeHMS(H1, M1, S1); sc.BaseDateTimeIn[pos].GetTimeHMS(H2, M2, S1);
		if(sc.Input[5].BooleanValue)
		{k1=M1/sc.Input[3].FloatValue; k2=M2/sc.Input[3].FloatValue; } else
		{k1=(H1-sc.Input[4].FloatValue)/sc.Input[3].FloatValue; k2=(H2-sc.Input[4].FloatValue)/sc.Input[3].FloatValue; }
		H1=int(k1); H2=int(k2); 
		if(H1!=H2)
		{
			if(firsttime==1)
			{
				sh=h; sl=l; scl=sc.BaseDataIn[3][pos-1]; firsttime=0;
				//float range=sh-sl, range2=2*range, range3=3*range;
				pp=(sh+sl+scl)/3; 
				r1=2*pp-sl; s1=2*pp-sh; r2=pp+sh-sl; s2=pp-sh+sl; 
				r3=2*pp+sh-2*sl; s3=2*pp+sl-2*sh; r4=3*pp+sh-3*sl; s4=3*pp+sl-3*sh;
				//r3=pp+range2; s3=pp-range2; r4=pp+range3; s4=pp-range3;
				r05=(pp+r1)/2; r15=(r2+r1)/2; r25=(r2+r3)/2; r35=(r4+r3)/2; 
				s05=(pp+s1)/2; s15=(s2+s1)/2; s25=(s2+s3)/2; s35=(s4+s3)/2; 
				h=sc.BaseDataIn[1][pos]; l=sc.BaseDataIn[2][pos];
			};
		} else firsttime=1;
		if(h<sc.BaseDataIn[1][pos]) h=sc.BaseDataIn[1][pos];
		if(l>sc.BaseDataIn[2][pos]) l=sc.BaseDataIn[2][pos];
		sc.Subgraph[0].Data[pos]=r2;sc.Subgraph[1].Data[pos]=r1;sc.Subgraph[2].Data[pos]=pp;sc.Subgraph[3].Data[pos]=s1;sc.Subgraph[4].Data[pos]=s2;
		sc.Subgraph[5].Data[pos]=r3;sc.Subgraph[6].Data[pos]=s3;sc.Subgraph[7].Data[pos]=r4;sc.Subgraph[8].Data[pos]=s4;
		sc.Subgraph[9].Data[pos]=r05;sc.Subgraph[10].Data[pos]=r15;sc.Subgraph[11].Data[pos]=r25;
		sc.Subgraph[12].Data[pos]=s05;sc.Subgraph[13].Data[pos]=s15; sc.Subgraph[14].Data[pos]=s25;
		if(sc.Subgraph[15].Data[pos-1]==s35) sc.Subgraph[15].Data[pos]=r35; else sc.Subgraph[15].Data[pos]=s35;
	};
}

/***********************************************************************/
SCSFExport scsf_TimePivots(SCStudyGraphRef sc)
{
	if(sc.Subgraph[8].Data[1]==sc.BaseDateTimeIn[sc.ArraySize-1].GetTime() && sc.UpdateStartIndex!=0) return;
	sc.Subgraph[8].Data[1]= sc.BaseDateTimeIn[sc.ArraySize-1].GetTime();

	if (sc.SetDefaults)
	{    
		sc.GraphName="Show OHL or C of Time Bars";
		sc.StudyDescription="Time Values";
		sc.Subgraph[0].Name="T1 Colour";        
		sc.Subgraph[1].Name="T2 Colour"; 
		sc.Subgraph[2].Name="T3 Colour";       
		sc.Subgraph[3].Name="T4 Colour";    
		sc.Input[2].Name="Time 1";
		sc.Input[3].Name="Time 2";
		sc.Input[4].Name="Time 3";
		sc.Input[5].Name="Time 4";
		sc.Input[2].ValueType=TIME_VALUE;
		sc.Input[3].ValueType=TIME_VALUE;
		sc.Input[4].ValueType=TIME_VALUE;
		sc.Input[5].ValueType=TIME_VALUE;
		sc.Input[6].Name="T1: O,H,L,C (0,1,2,3)";
		sc.Input[7].Name="T2: O,H,L,C (0,1,2,3)";
		sc.Input[8].Name="T3: O,H,L,C (0,1,2,3)";
		sc.Input[9].Name="T4: O,H,L,C (0,1,2,3)";
		sc.GraphRegion=0;  
		sc.FreeDLL=0; 
		return;
	}

	float&  t1=sc.Subgraph[8].Data[3];          float&  t2=sc.Subgraph[8].Data[4];
	float&  t3=sc.Subgraph[8].Data[5];          float&  t4=sc.Subgraph[8].Data[6];
	float 	t1t=0, t2t=0, t3t=0, t4t=0;
	int pos;

	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		if(sc.BaseDateTimeIn[pos-1].GetDate()!=sc.BaseDateTimeIn[pos].GetDate())
			//   {t1=t1t; t2=t2t; t3=t3t; t4=t4t; }
		{t1=0; t2=0; t3=0; t4=0; }

		if(sc.BaseDateTimeIn[pos-1].GetTime()<sc.Input[2].GetTime() && sc.BaseDateTimeIn[pos].GetTime()>=sc.Input[2].GetTime())
		{t1=sc.BaseDataIn[int(sc.Input[6].FloatValue)][pos];} else
		if(sc.BaseDateTimeIn[pos-1].GetTime()<sc.Input[3].GetTime() && sc.BaseDateTimeIn[pos].GetTime()>=sc.Input[3].GetTime())
		{t2=sc.BaseDataIn[int(sc.Input[7].FloatValue)][pos];} else
		if(sc.BaseDateTimeIn[pos-1].GetTime()<sc.Input[4].GetTime() && sc.BaseDateTimeIn[pos].GetTime()>=sc.Input[4].GetTime())
		{t3=sc.BaseDataIn[int(sc.Input[8].FloatValue)][pos];} else
		if(sc.BaseDateTimeIn[pos-1].GetTime()<sc.Input[5].GetTime() && sc.BaseDateTimeIn[pos].GetTime()>=sc.Input[5].GetTime())
		{t4=sc.BaseDataIn[int(sc.Input[9].FloatValue)][pos];};

		sc.Subgraph[0].Data[pos]=t1;sc.Subgraph[1].Data[pos]=t2;sc.Subgraph[2].Data[pos]=t3;sc.Subgraph[3].Data[pos]=t4;
	};
}



/*==========================================================================*/
SCSFExport scsf_FibBands(SCStudyGraphRef sc)
{
	if(sc.SetDefaults)
	{
		sc.GraphName = "FibBands";
		sc.GraphRegion = 0;
		sc.Subgraph[0].Name = "MA";
		sc.Subgraph[1].Name = "U1";
		sc.Subgraph[2].Name = "L1";
		sc.Subgraph[3].Name = "U2";
		sc.Subgraph[4].Name = "L2";
		sc.Subgraph[5].Name = "U3";
		sc.Subgraph[6].Name = "L3";
		sc.Subgraph[4].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[5].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[6].DrawStyle = DRAWSTYLE_LINE;

		sc.Input[0].Name = "Study And Subgraph Reference";
		sc.Input[0].SetStudySubgraphValues(0,  SC_LAST);

		sc.Input[2].Name = "MA Type";
		sc.Input[2].SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);

		sc.Input[3].Name = "True Range MA Type";
		sc.Input[3].SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);

		sc.Input[4].Name = "MA Length (Set to 1 if using study and want to match it exactly)";

		sc.Input[5].Name = "ATR MA Length";

		sc.Input[4].SetFloat(8.0);
		sc.Input[5].SetFloat(14.0);

		sc.Input[6].Name = "Fib 1";
		sc.Input[7].Name = "Fib 2";
		sc.Input[8].Name = "Fib 3";

		sc.Input[6].SetFloat(0.382);
		sc.Input[7].SetFloat(0.618);
		sc.Input[8].SetFloat(1.0);


		sc.CalculationPrecedence = LOW_PREC_LEVEL;
		sc.AutoLoop = 1;
		sc.FreeDLL = 0;
		return;
	}

	SCFloatArray SubgraphArray;

	sc.GetStudyArrayUsingID(sc.Input[0].GetStudyID(), sc.Input[0].GetSubgraphIndex(), SubgraphArray); 


	sc.MovingAverage(SubgraphArray, sc.Subgraph[0], sc.Input[2].GetMovAvgType(), sc.Index, sc.Input[4].FloatValue);
	sc.ATR(sc.BaseDataIn, sc.Subgraph[8], sc.Index, sc.Input[5].FloatValue, sc.Input[3].GetMovAvgType());

	float gap = sc.Subgraph[8][sc.Index]; 
	float t1 = sc.Subgraph[0][sc.Index]+sc.Input[6].FloatValue*gap;
	float b1 = sc.Subgraph[0][sc.Index]-sc.Input[6].FloatValue*gap;
	float t2 = sc.Subgraph[0][sc.Index]+sc.Input[7].FloatValue*gap;
	float b2 = sc.Subgraph[0][sc.Index]-sc.Input[7].FloatValue*gap;
	float t3 = sc.Subgraph[0][sc.Index]+sc.Input[8].FloatValue*gap;
	float b3 = sc.Subgraph[0][sc.Index]-sc.Input[8].FloatValue*gap;

	sc.Subgraph[1][sc.Index] = t1;
	sc.Subgraph[2][sc.Index] = b1;
	sc.Subgraph[3][sc.Index] = t2;
	sc.Subgraph[4][sc.Index] = b2;
	sc.Subgraph[5][sc.Index] = t3;
	sc.Subgraph[6][sc.Index] = b3;

}



/***********************************************************************/
SCSFExport scsf_Trend(SCStudyGraphRef sc)
{
	SCSubgraphRef e1 =	sc.Subgraph[0];		SCSubgraphRef e2 =	sc.Subgraph[1];			
	SCSubgraphRef lh =	sc.Subgraph[2];		SCSubgraphRef ll =	sc.Subgraph[3];
	SCSubgraphRef Up =	sc.Subgraph[4];		SCSubgraphRef Dn =	sc.Subgraph[5];		
	SCSubgraphRef Dirn = sc.Subgraph[6];	SCSubgraphRef Trend = sc.Subgraph[7];	
	if (sc.SetDefaults)
	{
		sc.GraphName="KiwiSuperTrend";
		sc.StudyDescription="Uses LSMA of Bar Highs and Lows to determine trend";
		e1.Name="e1";		e1.SecondaryColorUsed=1;
		e2.Name="e2";		e2.SecondaryColorUsed=1;
		lh.Name="lh";		lh.DrawStyle=5;
		ll.Name="ll";		ll.DrawStyle=5;        	
		Up.Name="Up";		Up.DrawStyle=5;
		Dn.Name="Dn";		Dn.DrawStyle=5;
		Dirn.Name="Dirn";	Dirn.DrawStyle=5;
		Trend.Name="Trend";	Trend.SecondaryColorUsed=1;
		sc.Input[2].Name="EMA1";		sc.Input[2].SetFloat(21);
		sc.Input[3].Name="EMA2";		sc.Input[3].SetFloat(34);
		sc.Input[4].Name="LSMA";		sc.Input[4].SetFloat(8);
		sc.Input[5].Name="Bars for Trend Start";					sc.Input[5].SetFloat(5);
		sc.Input[6].Name="Bars for Trend Confirmed";				sc.Input[6].SetFloat(15);
		sc.Input[7].Name="Bars back when Trend Not Confirmed";		sc.Input[7].SetFloat(2);
		sc.GraphRegion=0;
		sc.ScaleRangeType=SCALE_SAMEASREGION;
		sc.DrawZeros=0;
		return;
	}

	int ps, i, upcnt=0,dncnt=0;
	for (ps=sc.UpdateStartIndex; ps < sc.ArraySize; ps++)
	{
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], e1, MOVAVGTYPE_EXPONENTIAL, ps, (int)sc.Input[2].FloatValue);
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], e2, MOVAVGTYPE_EXPONENTIAL, ps, (int)sc.Input[3].FloatValue);
		sc.MovingAverage(sc.BaseDataIn[SC_HIGH], lh, MOVAVGTYPE_LINEARREGRESSION, ps, (int)sc.Input[4].FloatValue);
		sc.MovingAverage(sc.BaseDataIn[SC_LOW],  ll, MOVAVGTYPE_LINEARREGRESSION, ps, (int)sc.Input[4].FloatValue);

		Up[ps]=0; Dn[ps]=0;
		upcnt=0; dncnt=0; 
		for(i=0;i<sc.Input[5].FloatValue;i++) {
			if(lh[ps-i]>e1[ps-i] || lh[ps-i]>e2[ps-i]) ++upcnt;
			if(ll[ps-i]<e1[ps-i] || ll[ps-i]<e2[ps-i]) ++dncnt;
		}
		if(upcnt>=sc.Input[5].FloatValue) Up[ps]=5;	
		if(dncnt>=sc.Input[5].FloatValue) Dn[ps]=5;
		upcnt=0; dncnt=0; 
		for(i=0;i<sc.Input[5].FloatValue;i++) {
			if(Up[ps-i]==10) ++upcnt;
			if(Dn[ps-i]==10) ++dncnt;
		}
		if(upcnt>0 && lh[ps]>e1[ps] && lh[ps-1]>e1[ps-1]) Up[ps]=5;	
		if(dncnt>0 && ll[ps]>e1[ps] && ll[ps-1]>e1[ps-1]) Dn[ps]=5;
		upcnt=0; dncnt=0; 
		for(i=0;i<(sc.Input[6].FloatValue+sc.Input[7].FloatValue);i++) {
			if(lh[ps-i]>e1[ps-i] || lh[ps-i]>e2[ps-i]) ++upcnt;
			if(ll[ps-i]<e1[ps-i] || ll[ps-i]<e2[ps-i]) ++dncnt;
		}
		if(upcnt>=sc.Input[6].FloatValue) Up[ps]=10;	
		if(dncnt>=sc.Input[6].FloatValue) Dn[ps]=10;


		if(Dirn[ps-1]==10 && Up[ps]==10) Dirn[ps]=10;	else if(Dirn[ps-1]==-10 && Dn[ps]==10) Dirn[ps]=-10;		
		else if(Up[ps]>Dn[ps]) {if(Up[ps]==10) Dirn[ps]=10; else if(Up[ps]==5) Dirn[ps]=5; } else
		{if(Dn[ps]==10) Dirn[ps]=-10; else if(Dn[ps]==5) Dirn[ps]=-5; }

		if(Up[ps]==10) {e1.DataColor[ps]=e1.PrimaryColor;} else if(Up[ps]==5) {e1.DataColor[ps]=e1.SecondaryColor;} 
		else {e1.DataColor[ps]=lh.PrimaryColor;}
		if(Dn[ps]==10) {e2.DataColor[ps]=e2.PrimaryColor;} else if(Dn[ps]==5) {e2.DataColor[ps]=e2.SecondaryColor;} 
		else {e2.DataColor[ps]=lh.PrimaryColor;}

		if(Trend.DrawStyle!=5) {
			Trend[ps]=e2[ps]; e1.DataColor[ps]=lh.PrimaryColor;
			if(Dirn[ps]==10 && Dn[ps]==0) {Trend.DataColor[ps]=e1.PrimaryColor;} 
			else if(Dirn[ps]>0) {Trend.DataColor[ps]=e1.SecondaryColor;} 
			else if(Dirn[ps]==-10 && Up[ps]==0) {Trend.DataColor[ps]=e2.PrimaryColor;} 
			else if(Dirn[ps]<0) {Trend.DataColor[ps]=e2.SecondaryColor;} 
			else {Dirn.DataColor[ps]=lh.PrimaryColor;}
		}

	}
}



/*==========================================================================*/
SCSFExport scsf_HullMovingAverage(SCStudyGraphRef sc)
{
	// Configuration
	if (sc.SetDefaults)
	{
		sc.GraphName = "Hull Moving Average (varSqrt)"; // study name shown in F6 menu and on the chart
		sc.StudyDescription = "Alan Hull's MA with options for truncation of the Sqrt of the Period"; // F6-study-function - r-pane
		sc.GraphRegion = 0;    // zero based region number


		sc.DrawZeros = 0;
		// during development set this flag to 1, so the dll can be modified. When development is done set it to 0 to speed up the function calling.
		//sc.FreeDLL = 0;

		sc.Subgraph[0].Name = "HMA";
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[0].PrimaryColor = RGB(0,185,47); // green

		sc.Input[0].Name = "Input Data";
		sc.Input[0].SetInputDataIndex(SC_LAST); // default data field

		sc.Input[1].Name = "Length";
		sc.Input[1].SetInt(14);            // default integer value
		sc.Input[1].SetIntLimits(1, 1000); // min-max value

		sc.Input[2].Name = "Round Sqrt of Period to Nearest Integer";
		sc.Input[2].ValueType=YESNO_VALUE;

		sc.AutoLoop = 1;

		return;
	}

	// Data processing

	unsigned long DFI  = sc.Input[0].GetInputDataIndex(); // Data Field Index
	int           Length  = sc.Input[1].GetInt();

	int ipd2 = Length/2;                           // integer of Length/2

	sc.WeightedMovingAverage(sc.BaseData[DFI], sc.Subgraph[1], sc.Index, ipd2);
	sc.WeightedMovingAverage(sc.BaseData[DFI], sc.Subgraph[2], sc.Index, Length);

	float wma1 = sc.Subgraph[1][sc.Index];
	float wma2 = sc.Subgraph[2][sc.Index];
	sc.Subgraph[3][sc.Index] = 2*wma1 - wma2;

	int isrp ;
	if(sc.Input[2].BooleanValue)     	{isrp = int(sqrt((double)Length) + 0.5);}         // rounded square root of Length
	else 								{isrp = int(sqrt((double)Length) - 0.5);};

	sc.WeightedMovingAverage(sc.Subgraph[3], sc.Subgraph[0], sc.Index, isrp);        // HMA

	sc.Subgraph[5].Name = "isrpflex";
	sc.Subgraph[5][sc.ArraySize-1]=isrp; sc.Subgraph[5][sc.ArraySize-2]=sc.Input[2].BooleanValue;

}

/*==========================================================================*/
SCSFExport scsf_UpsideDown(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "Upside Down";
		sc.StudyDescription = " ";
		sc.IsCustomChart = 1;  // true		
		sc.GraphRegion = 0;  // First region		
		sc.DrawZeros = 0;  // false		
		sc.GraphDrawType=GDT_OHLCBAR ;
		sc.StandardChartHeader = 1; // true
		sc.UpdateAlways=1;

		sc.Subgraph[0].Name = "Open";		sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[1].Name = "High";		sc.Subgraph[1].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[2].Name = "Low";		sc.Subgraph[2].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[3].Name = "Last";		sc.Subgraph[3].DrawStyle = DRAWSTYLE_LINE;
		sc.Subgraph[4].Name = "Volume";		sc.Subgraph[3].DrawStyle = DRAWSTYLE_IGNORE;
		sc.Input[2].Name = "Other Chart Number"; sc.Input[2].SetFloat(1);
		sc.Input[3].Name = "Subtrace Price from: ";
		sc.FreeDLL=0;
		return;
	}

	SCFloatArray PO,PH,PL,PC,PV;
	SCDateTimeArray DTA;

	int i, size;
	int ChartNumber = -(int)sc.Input[2].FloatValue;
	float Sub=sc.Input[3].FloatValue;
	int& LastBarStart  	= sc.PersistVars->i1;

	sc.GetChartArray(ChartNumber,0,PO);
	sc.GetChartArray(ChartNumber,1,PH);
	sc.GetChartArray(ChartNumber,2,PL);
	sc.GetChartArray(ChartNumber,3,PC);
	sc.GetChartArray(ChartNumber,4,PV);
	sc.GetChartDateTimeArray(ChartNumber,DTA);
	size = DTA.GetArraySize();

	if (sc.UpdateStartIndex == 0)
	{
		LastBarStart=0;
		sc.ResizeArrays(0);
	}


	for (i = LastBarStart; i < size; i++)
	{
		if (sc.OutArraySize - 1 < i) sc.AddElements(1);
		sc.DateTimeOut[i] = DTA[i];
		sc.Subgraph[SC_OPEN][i] = 	Sub-PO[i];
		sc.Subgraph[SC_HIGH][i] = 	Sub-PH[i];
		sc.Subgraph[SC_LOW][i] =  	Sub-PL[i];
		sc.Subgraph[SC_LAST][i] = 	Sub-PC[i];
		sc.Subgraph[SC_VOLUME][i] = PV[i];
	}
	i=size-1;
	sc.Subgraph[SC_OPEN][i] = 	Sub-PO[i];
	sc.Subgraph[SC_HIGH][i] = 	Sub-PH[i];
	sc.Subgraph[SC_LOW][i] =  	Sub-PL[i];
	sc.Subgraph[SC_LAST][i] = 	Sub-PC[i];
	sc.Subgraph[SC_VOLUME][i] = PV[i];
}






/***********************************************************************/
SCSFExport scsf_NR7(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="NR7 ";
		sc.StudyDescription="Narrow Range Bars";
		sc.Subgraph[0].Name=" ";
		sc.Subgraph[1].Name=" ";
		sc.Subgraph[2].Name=" ";
		sc.Subgraph[3].Name=" ";
		sc.GraphRegion=0;
		sc.ScaleRangeType=SCALE_SAMEASREGION;
		sc.GraphDrawType=GDT_OHLCBAR ;
		sc.Input[2].Name="Number of Bars"; sc.Input[2].SetFloat(7);
		sc.DrawZeros=0;
		return;
	}

	int bars = sc.Input[2].FloatValue+2;
	float range, rangetemp;
	if(sc.UpdateStartIndex == 0) {
		sc.Subgraph[1].PrimaryColor = sc.Subgraph[0].PrimaryColor;
		sc.Subgraph[2].PrimaryColor = sc.Subgraph[0].PrimaryColor;
		sc.Subgraph[3].PrimaryColor = sc.Subgraph[0].PrimaryColor;
	}

	for(int pos=sc.UpdateStartIndex; pos<sc.ArraySize; pos++)  
	{
		range=sc.BaseDataIn[1][pos-2]-sc.BaseDataIn[2][pos-2];
		for(int i=3; i<bars; i++) {
			rangetemp=sc.BaseDataIn[1][pos-i]-sc.BaseDataIn[2][pos-i];
			if(rangetemp<range) range=rangetemp;
		}
		int postemp=pos-1;
		if((sc.BaseDataIn[1][postemp]-sc.BaseDataIn[2][postemp])<=range) {
			sc.Subgraph[1][postemp] = sc.BaseDataIn[1][postemp];
			sc.Subgraph[2][postemp] = sc.BaseDataIn[2][postemp]; //+(range*0.5)
		} else {
			sc.Subgraph[1][postemp] = 0;	sc.Subgraph[2][postemp] = 0;
		}
		sc.Subgraph[0][postemp] = 0;        sc.Subgraph[3][postemp] = 0;
	}	
}




/***********************************************************************/
SCSFExport scsf_Times(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{    
		sc.GraphName="Times set background color";
		sc.StudyDescription="Changes chart colour if chart has bars outside your set timezone";
		sc.StudyDescription="T";
		sc.Subgraph[0].Name="Day Colour";        
		sc.Subgraph[1].Name="Extended Day Colour"; 
		sc.Input[2].Name="Extended if times are before";
		sc.Input[3].Name="Extended if times are after";
		sc.Input[2].ValueType=TIME_VALUE;
		sc.Input[3].ValueType=TIME_VALUE;
		sc.GraphRegion=0;
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.FreeDLL = 0; 
		return;
	}

	if(sc.UpdateStartIndex==0)  {
		sc.ChartBackgroundColor=sc.Subgraph[0].PrimaryColor;
	}

	for (int pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		if( (sc.BaseDateTimeIn[pos].GetTime()>sc.Input[3].GetTime() && sc.Input[3].GetTime()!=0) || 
			sc.BaseDateTimeIn[pos].GetTime()<sc.Input[2].GetTime() )
			sc.ChartBackgroundColor=sc.Subgraph[1].PrimaryColor;

	}
}



/***********************************************************************/
SCSFExport scsf_RTHTimes(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{    
		sc.GraphName="RTH set background color";
		sc.StudyDescription="Changes chart colour if chart has non-RTH bars";
		sc.StudyDescription="T";
		sc.Subgraph[0].Name="Day Colour";        
		sc.Subgraph[1].Name="Extended Day Colour"; 
		sc.Input[2].ValueType=TIME_VALUE;
		sc.Input[3].ValueType=TIME_VALUE;
		sc.GraphRegion=0;
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.FreeDLL = 0; 
		return;
	}


	if(sc.UpdateStartIndex==0) {
		sc.ChartBackgroundColor=sc.Subgraph[0].PrimaryColor;
	}

	for (int pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		if(sc.UseSecondStartEndTimes==1) sc.ChartBackgroundColor=sc.Subgraph[1].PrimaryColor;

	}

}


/***********************************************************************/
SCSFExport scsf_AR(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="Average Range";
		sc.StudyDescription="Average Range";
		sc.Subgraph[0].Name="AR";
		sc.Input[2].Name="AR Length";
		sc.Input[2].SetInt(10);
		sc.Input[3].Name="AR MA Type";
		sc.Input[3].ValueType = MOVAVGTYPE_VALUE; 
		sc.Input[3].SetMovAvgType(MOVAVGTYPE_SIMPLE); 
		sc.Input[4].Name="Use Current Bar (vs stop with last bar)";
		sc.Input[4].SetYesNo(1);  // Yes
		sc.FreeDLL=0; 
		return;
	}

	for (int i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		int j=0;
		if(sc.Input[4].GetYesNo()==0) j=1;
		sc.Subgraph[2][i]=sc.BaseDataIn[SC_HIGH][i-j]-sc.BaseDataIn[SC_LOW][i-j];
		sc.MovingAverage(sc.Subgraph[2], sc.Subgraph[0],  sc.Input[3].GetMovAvgType(), i, sc.Input[2].GetInt());		
	}

};



/***********************************************************************/
SCSFExport scsf_GoslinTL(SCStudyGraphRef sc)
{
	sc.GraphName="Goslin Trend or Long Line";
	sc.Subgraph[0].Name="SMA";
	sc.Subgraph[1].Name="Early Close";
	sc.FreeDLL=0; 
	if(sc.SetDefaults) {return;}
	sc.Subgraph[0].SecondaryColorUsed = 1;
	float prev0=0;

	sc.Input[2].Name="Trend SMA Length";

	if(sc.ArraySize<100) return;


	int    i,j,pos;
	double sum1=0;	double avg1=0;

	if(sc.Input[2].FloatValue==0) sc.Input[2].FloatValue=49;
	i=sc.ArraySize-(int)sc.Input[2].FloatValue;

	for (pos=1; pos < sc.ArraySize; pos++)
	{

		sum1 = sum1 + sc.BaseDataIn[3][pos];
		avg1 = sum1 / sc.Input[2].FloatValue;
		j=pos-(int)sc.Input[2].FloatValue+1;
		if(pos>=1+sc.Input[2].FloatValue-1) {sum1 = sum1 - sc.BaseDataIn[3][j];};

		if(pos>sc.Input[2].FloatValue-1)
		{
			sc.Subgraph[0].Data[pos] = avg1;
			if ( sc.Subgraph[0].Data[pos]>prev0) sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].PrimaryColor; else sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].SecondaryColor; prev0= sc.Subgraph[0].Data[pos];

			if(pos==sc.ArraySize-1) sc.Subgraph[1].Data[pos]=sc.BaseDataIn[3][i]; else
				if(pos==i) sc.Subgraph[1].Data[pos]=sc.BaseDataIn[3][pos]; else
					sc.Subgraph[1].Data[pos]=0;
		};
	};
}


/***********************************************************************/
SCSFExport scsf_GoslinML(SCStudyGraphRef sc)
{
	sc.GraphName="Goslin Medium Line & Concurrency Indicator";
	sc.Subgraph[0].Name="Concurrent";
	sc.Subgraph[1].Name="Early Medium";
	sc.Subgraph[2].Name="Medium (going Up)";
	sc.Subgraph[3].Name="Medium (going Down)";

	sc.Input[2].Name="MACD Short MA Length";
	sc.Input[3].Name="MACD Long MA Length";
	sc.Input[4].Name="Medium Line Length (SMA of the MACD)";
	sc.Input[5].Name="Trend or Long Line Length for Concurrency Indicator";
	sc.FreeDLL=0; 
	if(sc.SetDefaults) {return;}

	if(sc.ArraySize<100) return;


	int    i,j,pos;

	if(sc.Input[2].FloatValue==0) sc.Input[2].FloatValue=3;
	if(sc.Input[3].FloatValue==0) sc.Input[3].FloatValue=10;
	if(sc.Input[4].FloatValue==0) sc.Input[4].FloatValue=16;
	if(sc.Input[5].FloatValue==0) sc.Input[5].FloatValue=49;
	i=sc.ArraySize-(int)sc.Input[4].FloatValue;

	double sum1=0; double sum2=0; double sum3=0; double sum4=0; double sum5=0;
	double avg1=0; double avg2=0; double avg3=0; double avg4=0; double avg5=0;
	double avg4p=0; double avg5p=0;

	for (pos=50; pos < sc.ArraySize; pos++)
	{
		sum1 = sum1 + sc.BaseDataIn[3][pos];
		avg1 = sum1 / sc.Input[2].FloatValue;
		j=pos-(int)sc.Input[2].FloatValue+1;
		if(pos>50+sc.Input[2].FloatValue-2) {sum1 = sum1 - sc.BaseDataIn[3][j];};

		sum2 = sum2 + sc.BaseDataIn[3][pos];
		avg2 = sum2 / sc.Input[3].FloatValue;
		j=pos-(int)sc.Input[3].FloatValue+1;
		if(pos>50+sc.Input[3].FloatValue-2) {sum2 = sum2 - sc.BaseDataIn[3][j];};

		avg3 = avg1 - avg2;

		sc.Subgraph[5].Data[pos] = avg3;
		sum4 = sum4 + avg3;
		avg4p= avg4;
		avg4 = sum4 / sc.Input[4].FloatValue;
		j=pos-(int)sc.Input[4].FloatValue+1;
		if(pos>50+sc.Input[4].FloatValue-2) {sum4 = sum4 - sc.Subgraph[5].Data[j];};

		sum5 = sum5 + sc.BaseDataIn[3][pos];
		avg5p= avg5;
		avg5 = sum5 / sc.Input[5].FloatValue;
		j=pos-(int)sc.Input[5].FloatValue+1;
		if(pos>50+sc.Input[5].FloatValue-2) {sum5 = sum5 - sc.BaseDataIn[3][j];};

		if(pos>sc.Input[2].FloatValue+sc.Input[3].FloatValue)
		{
			if(((avg4p>avg4) && (avg5p>avg5)) || ((avg4p<avg4) && (avg5p<avg5))) 
				sc.Subgraph[0].Data[pos] = 1; else sc.Subgraph[0].Data[pos] = 0; 

			if(pos==sc.ArraySize-1) sc.Subgraph[1].Data[pos]=sc.Subgraph[5].Data[i]; else
				if(pos==i) sc.Subgraph[1].Data[pos]=sc.Subgraph[5].Data[pos]; else
					sc.Subgraph[1].Data[pos]=0;
			if(avg4>avg4p)  {sc.Subgraph[2].Data[pos]=avg4;sc.Subgraph[3].Data[pos]=0;} else
			{sc.Subgraph[2].Data[pos]=0;sc.Subgraph[3].Data[pos]=avg4;}
		};


	};}


/***********************************************************************/
SCSFExport scsf_Swing(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="GannSwing";
		sc.Subgraph[0].Name="SwingUp";
		sc.Subgraph[1].Name="SwingDn";
		sc.Input[2].Name="Display Numbers";
		sc.Input[2].ValueType=YESNO_VALUE;
		sc.Input[3].Name="Number Font Size";	
		sc.Input[4].Name="Price Adjust for Time";
		sc.Input[5].Name="Price Adjust for Price Swing";
		sc.Input[8].Name="Paintbar?";
		sc.Input[8].ValueType=YESNO_VALUE;
		sc.FreeDLL=0; 
		return;
	}
	if(sc.ArraySize<5) return;
	sc.GraphRegion=0;

	if(sc.Input[8].GetYesNo())  
	{
		sc.GraphDrawType=GDT_OHLCBAR ;
		sc.Subgraph[0].SecondaryColorUsed = 1;
		sc.Subgraph[1].SecondaryColorUsed = 1;
		sc.Subgraph[2].SecondaryColorUsed = 1;
		sc.Subgraph[3].SecondaryColorUsed = 1;
	} else
	{
		sc.Subgraph[0].DrawStyle=DRAWSTYLE_STAIR;
		sc.Subgraph[1].DrawStyle=DRAWSTYLE_STAIR;
	};

	int 	pos, direction=1;
	float  	hi=sc.BaseDataIn[3][9], hinext=hi, h1=hi, h2=hi,  lo=hi, lonext=lo, l1=lo, l2=lo,
		highest=0, lowest=999999, swing, start, end, length=0;

	int fs= (int) sc.Input[3].FloatValue;
	if(sc.Input[4].FloatValue==sc.Input[5].FloatValue) sc.Input[5].FloatValue=sc.Input[5].FloatValue+2;
	char cperiod[16];

	sc.DataStartIndex=2;
	sc.DeleteACSChartDrawing(sc.ChartNumber, 0, 562);
	s_UseTool Tool; 
	Tool.ChartNumber = sc.ChartNumber;
	Tool.DrawingType = DRAWING_TEXT;
	Tool.LineWidth = 1;
	Tool.Region = 0;
	Tool.AddMethod = UTAM_ADD_OR_ADJUST;
	Tool.FontSize = fs;
	Tool.LineNumber = 562; 
	Tool.AddMethod = UTAM_ADD_ALWAYS;


	for (pos=10; pos < sc.ArraySize-1; pos++)
	{
		Tool.BeginDateTime = sc.BaseDateTimeIn[pos-2];
		if(direction==1)
		{
			if(sc.BaseDataIn[1][pos]>highest) highest=sc.BaseDataIn[1][pos]; if(sc.BaseDataIn[2][pos]<lowest) lowest=sc.BaseDataIn[2][pos]; 
			end=pos; swing=highest-lowest;  length=end-start;
			if(sc.Input[2].BooleanValue && (sc.BaseDataIn[3][pos] < lo || pos == sc.ArraySize-1))
			{
				Tool.BeginValue = highest-(int) sc.Input[4].FloatValue;	Tool.Text=itoa((int)length,cperiod,10); Tool. Color = sc.Subgraph[0].PrimaryColor;
				sc.UseTool(Tool);
				Tool.BeginValue = highest-(int) sc.Input[5].FloatValue;	Tool.Text=itoa((int)swing,cperiod,10); Tool. Color = sc.Subgraph[0].PrimaryColor;
				sc.UseTool(Tool);
			}
			if(sc.BaseDataIn[3][pos] < lo) // broken 3 day trailing lows on close
			{
				direction=-1; l1=l2; l2=lonext; //reverse short
				highest=989898; lowest=999999;  start=pos;
			} 
		} else // direction==-1
		{
			if(sc.BaseDataIn[1][pos]>highest) highest=sc.BaseDataIn[1][pos]; if(sc.BaseDataIn[2][pos]<lowest) lowest=sc.BaseDataIn[2][pos]; 
			end=pos; swing=highest-lowest;  length=end-start;
			if(sc.Input[2].BooleanValue && (sc.BaseDataIn[3][pos] > hi || pos == sc.ArraySize-1))
			{
				Tool.BeginValue = lowest+(int) sc.Input[4].FloatValue;	Tool.Text=itoa((int)length,cperiod,10); Tool. Color = sc.Subgraph[1].PrimaryColor;
				sc.UseTool(Tool);
				Tool.BeginValue = lowest+(int) sc.Input[5].FloatValue;	Tool.Text=itoa((int)swing,cperiod,10); Tool. Color = sc.Subgraph[1].PrimaryColor;
				sc.UseTool(Tool);
			}
			if(sc.BaseDataIn[3][pos] > hi) // broken 3 day trailing  on close
			{
				direction=1; h1=h2; h2=hinext; //reverse 
				highest=0; lowest=989898;  start=pos;
			} 
		};


		if(sc.BaseDataIn[1][pos] > h2) // higher bar
		{
			h1=h2; h2=sc.BaseDataIn[1][pos];
			if(sc.BaseDataIn[2][pos-1]<lonext) lonext=sc.BaseDataIn[2][pos-1];
			lo=lonext; lonext=sc.BaseDataIn[2][pos];
			if(lonext<lo) lo=lonext;
		} else
			if(sc.BaseDataIn[1][pos] > sc.BaseDataIn[1][pos-1])
			{ h2=sc.BaseDataIn[1][pos]; lonext=sc.BaseDataIn[2][pos]; };


		if(sc.BaseDataIn[2][pos] < l2) // lower bar
		{
			l1=l2; l2=sc.BaseDataIn[2][pos];
			if(sc.BaseDataIn[1][pos-1]>hinext) hinext=sc.BaseDataIn[1][pos-1];
			hi=hinext; hinext=sc.BaseDataIn[1][pos];
			if(hinext>hi) hi=hinext;
		} else
			if(sc.BaseDataIn[2][pos] < sc.BaseDataIn[2][pos-1])
			{ l2=sc.BaseDataIn[2][pos]; hinext=sc.BaseDataIn[1][pos]; };



		if(sc.BaseDataIn[1][pos] > hi) // pushed up trailing   
			hi=sc.BaseDataIn[1][pos]; // pop it  because of push 
		if(sc.BaseDataIn[2][pos] < lo) // pushed down trailing lows  
			lo=sc.BaseDataIn[2][pos]; // pop it down because of push down 

		if(sc.Input[8].BooleanValue)  
		{
			sc.Subgraph[0].Data[pos] = sc.BaseDataIn[0][pos];  sc.Subgraph[1].Data[pos] = sc.BaseDataIn[1][pos];
			sc.Subgraph[2].Data[pos] = sc.BaseDataIn[2][pos];  sc.Subgraph[3].Data[pos] = sc.BaseDataIn[3][pos];
			if(direction==1) sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].PrimaryColor; else
				sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].SecondaryColor;
			sc.Subgraph[1].DataColor[pos]= sc.Subgraph[0].DataColor[pos];
			sc.Subgraph[2].DataColor[pos]= sc.Subgraph[0].DataColor[pos];  
			sc.Subgraph[3].DataColor[pos]= sc.Subgraph[0].DataColor[pos]; 

		} else
		{
			if(highest==989898) highest=hi;  if(lowest==989898) lowest=lo; 
			if(direction==1) {sc.Subgraph[0].Data[pos+1] = lo; sc.Subgraph[1].Data[pos+1] = 0;}
			else             {sc.Subgraph[0].Data[pos+1] =  0; sc.Subgraph[1].Data[pos+1] = hi;}
			sc.Subgraph[2].Data[pos] = h1; sc.Subgraph[3].Data[pos] = h2;
			sc.Subgraph[4].Data[pos] = l1; sc.Subgraph[5].Data[pos] = l2;
		}
	}

};


/***********************************************************************/
SCSFExport scsf_Pivots(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="Kiwi's old pivots";
		sc.Subgraph[0].Name="SwingUp";
		sc.Subgraph[1].Name="SwingDn";
		sc.Input[2].Name="Opening Price(0) or Floor (Closing Price)(1) Pivot";
		sc.Input[3].Name="Pvts 1,2(0);3,H,L(1),4(2);Todays H&L(3);Pvt Attractor(4);Yesterday HLC & Todays O(5);0.5,1.5(10);2.5(11);Camarillo(20)";
		sc.Input[4].Name="Open Time (9999 if day)";
		sc.Input[5].Name="Close Time (9999 if day)";
		sc.Input[7].Name="Pivot Attractor - Points to next pivot";
		sc.GraphRegion=0;
		sc.FreeDLL=0; 
		return;
	}

	int 	opentime, closetime,  pos,start=sc.UpdateStartIndex;
	float  	h=sc.BaseDataIn[1][10],l=sc.BaseDataIn[2][10];
	float   so=0,sh=0,sl=0,scl=0,sph=0,spl=0,spc=0;
	float  	r1,r2,r3,r4,r5,s1,s2,s3,s4,s5,pp,
		r05,r15,r25,s05,s15,s25, clb, cs, cl, csb;

	if(sc.UpdateStartIndex == 0) 
	{	
		sc.UpdateStartIndex=50;

		if(sc.Input[4].FloatValue==0 && sc.Input[5].FloatValue==0) { opentime=9999; closetime=9999;sc.Input[4].FloatValue=9999; sc.Input[5].FloatValue=9999;} else
		{ opentime=sc.Input[4].FloatValue; closetime=sc.Input[5].FloatValue;}


		if(sc.Input[3].FloatValue==0) { 	sc.Subgraph[0].Name="R1"; 	sc.Subgraph[1].Name="R2"; 	sc.Subgraph[2].Name="S1"; 	sc.Subgraph[3].Name="S2";
		if(sc.Input[2].FloatValue==1) sc.GraphName="Floor Pivots - R1 R2 S1 S2"; else sc.GraphName="OpenPrice Pivots - R1 R2 S1 S2";
		} else

			if(sc.Input[3].FloatValue==1) {	sc.Subgraph[0].Name="PP"; 	sc.Subgraph[1].Name="R3"; 	sc.Subgraph[2].Name="S3";
		if(sc.Input[2].FloatValue==1) sc.GraphName="Floor Pivots - PP R3 S3"; else sc.GraphName="OpenPrice Pivots - PP R3 S3";
		} else

			if(sc.Input[3].FloatValue==2) { 	sc.Subgraph[0].Name="R4"; 	sc.Subgraph[1].Name="H"; 	sc.Subgraph[2].Name="S4"; 	sc.Subgraph[3].Name="L";
		if(sc.Input[2].FloatValue==1) sc.GraphName="Floor Pivots - O H R4 S4"; else sc.GraphName="OpenPrice Pivots - O H R4 S4";
		} else

			if(sc.Input[3].FloatValue==3) { sc.Subgraph[0].Name=""; 	sc.Subgraph[1].Name="H"; 	sc.Subgraph[2].Name="L"; 	sc.Subgraph[3].Name="";
		sc.GraphName="Todays High and Low";
		} else

			if(sc.Input[3].FloatValue==4) { sc.Subgraph[0].Name="Remora R"; sc.Subgraph[1].Name="Remora P";
		sc.GraphName="Pivot Attractor";
		} else

			if(sc.Input[3].FloatValue==5) { sc.Subgraph[0].Name="O"; 	sc.Subgraph[1].Name="H"; 	sc.Subgraph[2].Name="L"; 	sc.Subgraph[3].Name="C";
		sc.GraphName="O H L C";
		} else

			if(sc.Input[3].FloatValue==10) { 	sc.Subgraph[0].Name="R0.5"; 	sc.Subgraph[1].Name="R1.5"; 	sc.Subgraph[2].Name="S0.5"; 	sc.Subgraph[3].Name="S1.5";
		if(sc.Input[2].FloatValue==1) sc.GraphName="Floor Pivots - R0.5 R1.5 S0.5 S1.5"; else sc.GraphName="OpenPrice Pivots - R1 R2 S1 S2";
		} else

			if(sc.Input[3].FloatValue==11) {	sc.Subgraph[0].Name="R2.5"; 	sc.Subgraph[1].Name="S2.5";
		if(sc.Input[2].FloatValue==1) sc.GraphName="Floor Pivots - R2.5 S2.5"; else sc.GraphName="OpenPrice Pivots - R2.5 S2.5";
		} else

			if(sc.Input[3].FloatValue==20) {	sc.Subgraph[0].Name="LongBreakout"; sc.Subgraph[1].Name="Short"; sc.Subgraph[2].Name="Long"; sc.Subgraph[3].Name="Short Breakout";
		sc.GraphName="Camarillo Pivots";
		};

	}


	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		if( (opentime>=9999 && sc.BaseDateTimeIn[pos-1].GetDate()!=sc.BaseDateTimeIn[pos].GetDate()) ||
			(opentime<9999 && sc.BaseDateTimeIn[pos-1].GetTime()/60<closetime && (sc.BaseDateTimeIn[pos].GetTime()/60>=closetime || sc.BaseDateTimeIn[pos-1].GetDate()!=sc.BaseDateTimeIn[pos].GetDate())))
		{sh=h; sl=l; scl=sc.BaseDataIn[3][pos-1]; h=sc.BaseDataIn[1][pos]; l=sc.BaseDataIn[2][pos]; }
		if( (opentime>=9999 && sc.BaseDateTimeIn[pos-1].GetDate()!=sc.BaseDateTimeIn[pos].GetDate()) ||
			(opentime<9999 && (sc.BaseDateTimeIn[pos-1].GetTime()/60<opentime || sc.BaseDateTimeIn[pos-1].GetDate()!=sc.BaseDateTimeIn[pos].GetDate()) && (sc.BaseDateTimeIn[pos].GetTime()/60>=opentime )))
		{so=sc.BaseDataIn[0][pos]; h=sc.BaseDataIn[1][pos]; l=sc.BaseDataIn[2][pos];
		if(sc.Input[2].FloatValue==1)
		{pp=(sh+sl+scl)/3;} else {pp=(sh+sl+so+so)/4;}

		r1=2*pp-sl; s1=2*pp-sh; r2=pp+r1-s1; s2=pp+s1-r1; r3=pp+r1-s2; s3=pp-r2+s1;
		r4=pp+r2-s2; s4=pp-r2+s2; r5=pp+r2-s2; s5=pp-r2+s2;
		r05=(pp+r1)/2; r15=(r2+r1)/2; r25=(r3+r2)/2;  s05=(pp+s1)/2; s15=(s2+s1)/2; s25=(s3+s2)/2;
		clb=((sh-sl)*(1.1/2))+scl; cs=((sh-sl)*(1.1/4))+scl; cl=scl-((sh-sl)*(1.1/4)); csb=scl-((sh-sl)*(1.1/2));
		}

		if(h<sc.BaseDataIn[1][pos]) h=sc.BaseDataIn[1][pos];
		if(l>sc.BaseDataIn[2][pos]) l=sc.BaseDataIn[2][pos];

		if(sc.Input[3].FloatValue==0) {sc.Subgraph[0][pos]=r1;sc.Subgraph[1][pos]=r2;sc.Subgraph[2][pos]=s1;sc.Subgraph[3][pos]=s2;} else
			if(sc.Input[3].FloatValue==1) {sc.Subgraph[0][pos]=pp;sc.Subgraph[1][pos]=r3;sc.Subgraph[2][pos]=s3;sc.Subgraph[3][pos]=0;} else
				if(sc.Input[3].FloatValue==2) {sc.Subgraph[0][pos]=r4;sc.Subgraph[1][pos]=sh;sc.Subgraph[2][pos]=s4;sc.Subgraph[3][pos]=sl;} else
					if(sc.Input[3].FloatValue==3) {sc.Subgraph[1][pos]=h;sc.Subgraph[2][pos]=l;} else
						if(sc.Input[3].FloatValue==5) {sc.Subgraph[0][pos]=so;sc.Subgraph[1][pos]=sh;sc.Subgraph[2][pos]=sl;sc.Subgraph[3][pos]=scl;} else
							if(sc.Input[3].FloatValue==10) {sc.Subgraph[0][pos]=r05;sc.Subgraph[1][pos]=r15;sc.Subgraph[2][pos]=s05;sc.Subgraph[3][pos]=s15;} else
								if(sc.Input[3].FloatValue==11) {sc.Subgraph[0][pos]=r25;sc.Subgraph[1][pos]=s25;} else
									if(sc.Input[3].FloatValue==20) {sc.Subgraph[0][pos]=clb;sc.Subgraph[1][pos]=cs;sc.Subgraph[2][pos]=cl;sc.Subgraph[3][pos]=csb;} else
										if(sc.Input[3].FloatValue==4)
										{
											if(pos==sc.ArraySize-1 && sc.Input[7].FloatValue!=0)
											{
												float X=sc.Input[7].FloatValue;
												float SxR=0, SxS=0;

												if(fabs(r1-sc.BaseDataIn[1][pos])<=X || fabs(r1-sc.BaseDataIn[2][pos])<=X) {if(SxR==0) {SxR=r1;} else {if(SxR<r1) SxR=r1;};};
												if(fabs(r2-sc.BaseDataIn[1][pos])<=X || fabs(r2-sc.BaseDataIn[2][pos])<=X) {if(SxR==0) {SxR=r2;} else {if(SxR<r2) SxR=r2;};};
												if(fabs(r3-sc.BaseDataIn[1][pos])<=X || fabs(r3-sc.BaseDataIn[2][pos])<=X) {if(SxR==0) {SxR=r3;} else {if(SxR<r3) SxR=r3;};};
												if(fabs(r4-sc.BaseDataIn[1][pos])<=X || fabs(r4-sc.BaseDataIn[2][pos])<=X) {if(SxR==0) {SxR=r4;} else {if(SxR<r4) SxR=r4;};};
												if(fabs(sh-sc.BaseDataIn[1][pos])<=X || fabs(sh-sc.BaseDataIn[2][pos])<=X) {if(SxR==0) {SxR=sh;} else {if(SxR<sh) SxR=sh;};};
												if(fabs( h-sc.BaseDataIn[1][pos])<=X || fabs( h-sc.BaseDataIn[2][pos])<=X) {if(SxR==0) {SxR= h;} else {if(SxR< h) SxR= h;};};

												if(fabs( l-sc.BaseDataIn[2][pos])<=X || fabs( l-sc.BaseDataIn[1][pos])<=X) {if(SxR==0) {SxR= l;} else {if(SxR< l) SxR= l;};};
												if(fabs(sl-sc.BaseDataIn[2][pos])<=X || fabs(sl-sc.BaseDataIn[1][pos])<=X) {if(SxR==0) {SxR=sl;} else {if(SxR<sl) SxR=sl;};};
												if(fabs(s1-sc.BaseDataIn[2][pos])<=X || fabs(s1-sc.BaseDataIn[1][pos])<=X) {if(SxR==0) {SxR=s1;} else {if(SxR<s1) SxR=s1;};};
												if(fabs(s2-sc.BaseDataIn[2][pos])<=X || fabs(s2-sc.BaseDataIn[1][pos])<=X) {if(SxR==0) {SxR=s2;} else {if(SxR<s2) SxR=s2;};};
												if(fabs(s3-sc.BaseDataIn[2][pos])<=X || fabs(s3-sc.BaseDataIn[1][pos])<=X) {if(SxR==0) {SxR=s3;} else {if(SxR<s3) SxR=s3;};};
												if(fabs(s4-sc.BaseDataIn[2][pos])<=X || fabs(s4-sc.BaseDataIn[1][pos])<=X) {if(SxR==0) {SxR=s4;} else {if(SxR<s4) SxR=s4;};};

												if(fabs(pp-sc.BaseDataIn[1][pos])<=X || fabs(pp-sc.BaseDataIn[2][pos])<=X) {if(SxR==0) {SxR=pp;} else {if(SxR<pp) SxR=pp;};};
												if(fabs(pp-sc.BaseDataIn[2][pos])<=X || fabs(pp-sc.BaseDataIn[1][pos])<=X) {if(SxS==0) {SxS=pp;} else {if(SxS>pp) SxS=pp;};};

												if(fabs(r1-sc.BaseDataIn[1][pos])<=X || fabs(r1-sc.BaseDataIn[2][pos])<=X) {if(SxS==0) {SxS=r1;} else {if(SxS>r1) SxS=r1;};};
												if(fabs(r2-sc.BaseDataIn[1][pos])<=X || fabs(r2-sc.BaseDataIn[2][pos])<=X) {if(SxS==0) {SxS=r2;} else {if(SxS>r2) SxS=r2;};};
												if(fabs(r3-sc.BaseDataIn[1][pos])<=X || fabs(r3-sc.BaseDataIn[2][pos])<=X) {if(SxS==0) {SxS=r3;} else {if(SxS>r3) SxS=r3;};};
												if(fabs(r4-sc.BaseDataIn[1][pos])<=X || fabs(r4-sc.BaseDataIn[2][pos])<=X) {if(SxS==0) {SxS=r4;} else {if(SxS>r4) SxS=r4;};};
												if(fabs(sh-sc.BaseDataIn[1][pos])<=X || fabs(sh-sc.BaseDataIn[2][pos])<=X) {if(SxS==0) {SxS=sh;} else {if(SxS>sh) SxS=sh;};};
												if(fabs( h-sc.BaseDataIn[1][pos])<=X || fabs( h-sc.BaseDataIn[2][pos])<=X) {if(SxS==0) {SxS= h;} else {if(SxS> h) SxS= h;};};

												if(fabs( l-sc.BaseDataIn[2][pos])<=X || fabs( l-sc.BaseDataIn[1][pos])<=X) {if(SxS==0) {SxS= l;} else {if(SxS> l) SxS= l;};};
												if(fabs(sl-sc.BaseDataIn[2][pos])<=X || fabs(sl-sc.BaseDataIn[1][pos])<=X) {if(SxS==0) {SxS=sl;} else {if(SxS>sl) SxS=sl;};};
												if(fabs(s1-sc.BaseDataIn[2][pos])<=X || fabs(s1-sc.BaseDataIn[1][pos])<=X) {if(SxS==0) {SxS=s1;} else {if(SxS>s1) SxS=s1;};};
												if(fabs(s2-sc.BaseDataIn[2][pos])<=X || fabs(s2-sc.BaseDataIn[1][pos])<=X) {if(SxS==0) {SxS=s2;} else {if(SxS>s2) SxS=s2;};};
												if(fabs(s3-sc.BaseDataIn[2][pos])<=X || fabs(s3-sc.BaseDataIn[1][pos])<=X) {if(SxS==0) {SxS=s3;} else {if(SxS>s3) SxS=s3;};};
												if(fabs(s4-sc.BaseDataIn[2][pos])<=X || fabs(s4-sc.BaseDataIn[1][pos])<=X) {if(SxS==0) {SxS=s4;} else {if(SxS>s4) SxS=s4;};};;
												sc.Subgraph[0][pos]=SxR;sc.Subgraph[1][pos]=SxS;

											} else
											{sc.Subgraph[0][pos]=0;sc.Subgraph[1][pos]=0;};
										};

		if(closetime>opentime && (sc.BaseDateTimeIn[pos].GetTime()/60>closetime || (sc.BaseDateTimeIn[pos].GetTime()/60<opentime && opentime!=9999)))
		{sc.Subgraph[0][pos]=0.1; sc.Subgraph[1][pos]=0.1; sc.Subgraph[2][pos]=0.1; sc.Subgraph[3][pos]=0.1;} else
		if(closetime<opentime && (sc.BaseDateTimeIn[pos].GetTime()/60>closetime && (sc.BaseDateTimeIn[pos].GetTime()/60<opentime && opentime!=9999)))
		{sc.Subgraph[0][pos]=0.1; sc.Subgraph[1][pos]=0.1; sc.Subgraph[2][pos]=0.1; sc.Subgraph[3][pos]=0.1;}

	}
};




/***********************************************************************/
SCSFExport scsf_LSMAOnCCI(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="LSMA & Close on 14CCI";
		sc.Input[2].Name="LSMA Length";
		sc.Input[2].SetFloat(25);

		sc.Input[3].Name="ExtraNuances (0,1,2,3)";
		sc.Input[4].Name="CCI Length";
		sc.Input[4].SetFloat(14);

		sc.Input[7].Name="Bars (0) or Points (n/1000) or LSMA (9999)";
		if(sc.Input[3].FloatValue==0 || sc.Input[3].FloatValue==1)
		{
			sc.Subgraph[0].Name="Above";
			sc.Subgraph[1].Name="Below";
		} 
		else if(sc.Input[3].FloatValue==2)
		{
			sc.Subgraph[0].Name="Above";
			sc.Subgraph[1].Name="Below";
			sc.Subgraph[2].Name="AboveDn";
			sc.Subgraph[3].Name="BelowUp";
		} 
		else if(sc.Input[3].FloatValue==3)
		{
			sc.Subgraph[0].Name="Up";
			sc.Subgraph[1].Name="Dn";
			sc.Subgraph[2].Name="UpBelow";
			sc.Subgraph[3].Name="DnAbove";
		}
		sc.GraphRegion=0;
		sc.FreeDLL=0; 
		return;
	}

	int     pos,i,c,Len,ccilength=14;
	float  	sum1=0,sum2=0,sum3=0, 
		y=0,y1,ysmoothed=0,
		Sum1=0,SumY=0,Sum2=0,SumBars,SumSqrBars, Num1, Num2, Slope, Intercept;

	double sum0=0; double cci0=0;


	Len= sc.Input[2].GetFloat();
	ccilength= sc.Input[4].GetFloat();

	SumBars= Len*(Len+1)*0.5;                 // sum(x)
	SumSqrBars=(Len+1)*Len*(2*Len+1)/6;       // sum(x2)
	Num2=(SumBars*SumBars)-(Len*SumSqrBars);  // normal denominator * n   { n*(sum(x2)-(sum(x))2/n) }

	sc.DataStartIndex=Len*2+1;

	for (pos=sc.UpdateStartIndex,c=1; pos < sc.ArraySize; pos++,c++)
	{
		y1=y;
		sc.Subgraph[6][pos] = (sc.BaseDataIn[1][pos]+sc.BaseDataIn[2][pos]+sc.BaseDataIn[3][pos])/3;
		sum0 = sum0 + sc.Subgraph[6][pos] ;
		if ( c>=ccilength)
		{
			Sum1=0; SumY=0;
			for (i=0; i<Len; i++) {Sum1 = Sum1 + (i+1) * sc.BaseDataIn[3][pos-i];} // sum(xy)
			for (i=0; i<Len; i++) {SumY = SumY + sc.BaseDataIn[3][pos-i];}       // sum(y)
			Sum2=SumBars*SumY;														  // sum(x)*sum(y)
			Num1=(Len*Sum1)-Sum2;												 // n*( sum(xy) - sum(x)sum(y)/n  )


			if(Num2!=0) Slope = Num1/Num2; else
				Slope=0;
			Intercept = (SumY - Slope * SumBars) / (Len);    // ( sum(y) - b*sum(x) )/n
			y= Intercept + (Slope*(Len));

			double md1=0;
			sc.Subgraph[5][pos] = sum0;
			for (i=1; i<=ccilength; i++)
			{
				double ma=sc.Subgraph[5][pos]/ccilength;
				md1=md1+fabs(ma - sc.Subgraph[6][pos-i+1]);
			}
			md1=md1/ccilength;
			cci0=(sc.Subgraph[6][pos]-(sum0/ccilength))/(0.015*md1);
			sum0 = sum0 - sc.Subgraph[6][pos-ccilength+1];


			sc.Subgraph[0][pos]=0;	sc.Subgraph[1][pos]=0;	sc.Subgraph[2][pos]=0;	sc.Subgraph[3][pos]=0;

			if(sc.Input[3].FloatValue==0 || sc.Input[3].FloatValue==1)
			{	if (sc.BaseDataIn[3][pos]>y)
			{if(sc.Input[7].FloatValue==0) sc.Subgraph[0][pos] = cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[0][pos] = y; else sc.Subgraph[0][pos] = sc.Input[7].FloatValue/1000;} else
			if (sc.BaseDataIn[3][pos]<y)
			{if(sc.Input[7].FloatValue==0) sc.Subgraph[1][pos]= cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[1][pos] = y; else  sc.Subgraph[1][pos]=sc.Input[7].FloatValue/1000;}
			} else

				if(sc.Input[3].FloatValue==2)
				{	if (sc.BaseDataIn[3][pos]>y && y>=y1 )
				{if(sc.Input[7].FloatValue==0) sc.Subgraph[0][pos] = cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[0][pos] = y; else sc.Subgraph[0][pos] = sc.Input[7].FloatValue/1000;} else
				if (sc.BaseDataIn[3][pos]>y)
				{if(sc.Input[7].FloatValue==0) sc.Subgraph[2][pos] = cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[2][pos] = y; else sc.Subgraph[2][pos] = sc.Input[7].FloatValue/1000;} else

				if (sc.BaseDataIn[3][pos]<y && y<=y1)
				{if(sc.Input[7].FloatValue==0) sc.Subgraph[1][pos]=cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[1][pos] = y; else  sc.Subgraph[1][pos]=sc.Input[7].FloatValue/1000;} else
				if (sc.BaseDataIn[3][pos]<y)
				{if(sc.Input[7].FloatValue==0) sc.Subgraph[3][pos]=cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[3][pos] = y; else  sc.Subgraph[3][pos]=sc.Input[7].FloatValue/1000;}
				} else

					if(sc.Input[3].FloatValue==3)
					{	if (y>=y1 && sc.BaseDataIn[3][pos]>y)
					{if(sc.Input[7].FloatValue==0) sc.Subgraph[0][pos] = cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[0][pos] = y; else sc.Subgraph[0][pos] = sc.Input[7].FloatValue/1000;} else
					if (y>=y1)
					{if(sc.Input[7].FloatValue==0) sc.Subgraph[2][pos] = cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[2][pos] = y; else sc.Subgraph[2][pos] = sc.Input[7].FloatValue/1000;} else

					if (y<=y1 && sc.BaseDataIn[3][pos]<y)
					{if(sc.Input[7].FloatValue==0) sc.Subgraph[1][pos]=cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[1][pos] = y; else  sc.Subgraph[1][pos]=sc.Input[7].FloatValue/1000;} else
					if (y<=y1)
					{if(sc.Input[7].FloatValue==0) sc.Subgraph[3][pos]=cci0; else if(sc.Input[7].FloatValue==9999) sc.Subgraph[3][pos] = y; else  sc.Subgraph[3][pos]=sc.Input[7].FloatValue/1000;}
					}
		}
	}
}



/***********************************************************************/
SCSFExport scsf_SoF(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="Higher Timeframe";
		sc.StudyDescription="Slow Chart on Fast Chart as Background bars";
		sc.Subgraph[0].Name="Up Colour";
		sc.Subgraph[0].DrawStyle= DRAWSTYLE_FILLRECTTOP;
		sc.Subgraph[3].DrawStyle= DRAWSTYLE_FILLRECTBOTTOM;
		sc.Subgraph[1].DrawStyle= DRAWSTYLE_IGNORE;		
		sc.Subgraph[2].DrawStyle= DRAWSTYLE_IGNORE;

		sc.Subgraph[1].Name="Dn Colour";
		sc.Subgraph[2].Name="Outside Colour";
		sc.Subgraph[3].Name="Last Bar Colour";
		sc.Subgraph[4].Name="38.2";
		sc.Subgraph[5].Name="50";
		sc.Subgraph[6].Name="LoC";
		sc.Subgraph[7].Name="38.2a";

		sc.Input[2].Name="Slow Chart No";
		sc.Input[2].  SetInt(1);

		sc.Input[3].Name="Fib No";
		sc.Input[3].SetFloat(0.0);

		sc.Input[5].Name="Offset to start new direction";
		sc.Input[5].SetFloat(0.0);

		sc.Input[6].Name="Cosmetic Offset Down";
		sc.Input[6].SetFloat(0.0);

		sc.Input[7].Name="Adjust Slow";
		sc.Input[7].SetFloat(1.0); 

		sc.Input[8].Name="Colour Inside Bars";
		sc.Input[8].SetYesNo(false);

		sc.GraphRegion=0;


		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.CalculationPrecedence = STD_PREC_LEVEL;
		sc.DrawZeros=0;
		sc.FreeDLL=0;
		return;
	}


	float& h = sc.PersistVars->f8;		float& l = sc.PersistVars->f9;
	SCFloatArray inH,inL;	SCDateTimeArray DTA;	
	sc.GetChartArray((int)sc.Input[2].GetInt(),1,inH);
	sc.GetChartArray((int)sc.Input[2].GetInt(),2,inL);
	long oSize=inH.GetArraySize();

	sc.Subgraph[9][3]= sc.BaseDateTimeIn[sc.ArraySize-1].GetTime();
	sc.GetChartDateTimeArray((int)sc.Input[2].GetInt(),DTA); 

	int  ps;
	int& flagit = sc.PersistVars->i1;								int& bartimeofsource = sc.PersistVars->i7;
	int& os = sc.PersistVars->i10;
	int& ps_m1 = sc.PersistVars->i11;								int& ps_m2 = sc.PersistVars->i12;	
	int& os_m1 = sc.PersistVars->i13;								int& os_m2 = sc.PersistVars->i14;
	float& high_m1 = sc.PersistVars->f1;							float& high_m2 = sc.PersistVars->f2;
	float& low_m1 = sc.PersistVars->f3;								float& low_m2 = sc.PersistVars->f4;
	float& ud_m1 = sc.PersistVars->f5;								float& ud_m2 = sc.PersistVars->f6;		
	float& Color = sc.PersistVars->f7;
	float& h38 = sc.PersistVars->f10;								float& l38 = sc.PersistVars->f11;	
	float& fib_no = sc.PersistVars->f12;	
	SCSubgraphRef f38 = sc.Subgraph[4];								SCSubgraphRef f50 = sc.Subgraph[5];
	SCSubgraphRef LoC = sc.Subgraph[6];								SCSubgraphRef f38a = sc.Subgraph[7];
	float& offset = sc.Input[5].FloatValue;							float& cosmetic_offset = sc.Input[6].FloatValue;

	int updown, outside=0, Recalc, i;
	float highestlow,lowesthigh,EndTime; //h,l,
	unsigned int& UpColor=sc.Subgraph[0].PrimaryColor;			unsigned int& DnColor=sc.Subgraph[1].PrimaryColor;
	unsigned int& OutsideColor=sc.Subgraph[2].PrimaryColor;	unsigned int& InsideColor=sc.Subgraph[3].PrimaryColor;

	if( bartimeofsource != DTA[5].GetTime()-DTA[4].GetTime()) 
	{bartimeofsource = DTA[5].GetTime()-DTA[4].GetTime(); os=0; ps=0; highestlow=0.0; lowesthigh=99999.0; flagit=1;
	for(i=1;i<sc.ArraySize;i++) {f38[i]=0;}};
	if (sc.UpdateStartIndex == 0) 
	{ os=0; ps=0; highestlow=0.0; lowesthigh=99999.0; flagit=1; fib_no=sc.Input[3].FloatValue; if(fib_no==0) fib_no=0.382;} else
	{ os=os_m2; ps=ps_m2;  highestlow=low_m2; lowesthigh=high_m2; updown=ud_m2;};

	for ( ; ps < sc.ArraySize; )
	{
		if(os==oSize-2) 
		{
			ps_m2=ps; os_m2=os;
			high_m2=lowesthigh; low_m2=highestlow;
			ud_m2=updown;
		};
		if(os==oSize-1) ps_m1=ps-1;
		if( (sc.BaseDateTimeIn[ps].GetDate()==DTA[os].GetDate() &&  sc.BaseDateTimeIn[ps].GetTime()==DTA[os].GetTime())		||
			(sc.BaseDateTimeIn[ps-1].GetDate()<DTA[os].GetDate() && sc.BaseDateTimeIn[ps].GetDate()==DTA[os].GetDate() 
			&& sc.BaseDateTimeIn[ps].GetTime()<DTA[os+1].GetTime() && sc.BaseDateTimeIn[ps].GetTime()>=DTA[os].GetTime())	|| 
			(sc.BaseDateTimeIn[ps-1].GetDate()==DTA[os-1].GetDate())
			&& sc.BaseDateTimeIn[ps].GetTime()<DTA[os+1].GetTime() && sc.BaseDateTimeIn[ps].GetTime()>=DTA[os].GetTime() 
			)
		{
			os++; ps++;
		} 
		else 
		{ 		
			if(sc.BaseDateTimeIn[ps].GetDate()>DTA[os].GetDate() || 
				(sc.BaseDateTimeIn[ps].GetDate()==DTA[os].GetDate() && sc.BaseDateTimeIn[ps].GetTime()>DTA[os].GetTime())) 
			{ os++; if(os>=oSize-1) { ps++; }} else
			{ ps++; }
		};
		os_m1=os;
		h=inH[os-1]; l=inL[os-1];
		if(updown==1) {if(l>highestlow) highestlow=l;} else
		{if(h<lowesthigh) lowesthigh=h;};
		outside=0; if(h>h38) h38=h; if(l<l38) l38=l; 

		if(h>lowesthigh+offset && l>=inL[os-2]-offset) 
		{
			if(updown==-1 && (flagit==1 || os >= oSize-1))
			{ 
				f38[ps]=lowesthigh-(lowesthigh-l38)*fib_no;  
				f38[ps-1]=f38[ps];f38[ps-2]=f38[ps-1];
			};
			updown=1; highestlow=l; lowesthigh=h; h38=h;
		} else
			if(l<highestlow-offset && h<=inH[os-2]+offset) 
			{
				if(updown==+1 && (flagit==1 || os >= oSize-1)) 
				{  
					f38[ps]=highestlow+(h38-highestlow)*fib_no; 
					f38[ps-1]=f38[ps];f38[ps-2]=f38[ps-1];
				}
				updown=-1;lowesthigh=h; highestlow=l; l38=l;
			} else
				if(h>inH[os-2]+offset && l<inL[os-2]-offset) {outside=1;};
			if(sc.Input[8].GetYesNo() && ((h<inH[os-2] && l>=inL[os-2]) || (h<=inH[os-2] && l>inL[os-2]))) Color=InsideColor; else
				if(!sc.Input[8].GetYesNo() && outside == 1) Color=OutsideColor; else
					if(updown ==  1) Color=UpColor; else
						if(updown == -1) Color=DnColor;

			sc.Subgraph[0].DataColor[ps-1] = (long)Color;	sc.Subgraph[3].DataColor[ps-1] = (long)Color;
			sc.Subgraph[0][ps-1] = inH[os-1];	sc.Subgraph[3][ps-1] = inL[os-1]-cosmetic_offset;
			LoC[ps]=sc.BaseDataIn[3][ps];
			if(ps >= sc.ArraySize-1) flagit=0;
	}; 
	if(updown==-1)
	{ f38a[sc.ArraySize-11]=lowesthigh-(lowesthigh-l38)*fib_no; } else
	{ f38a[sc.ArraySize-11]=highestlow+(h38-highestlow)*fib_no; };
	f38a[sc.ArraySize-12]=0;f38a[sc.ArraySize-13]=0;
	if(updown==-1)
	{ f50[sc.ArraySize-1]=lowesthigh-(lowesthigh-l38)*fib_no;} else
	{ f50[sc.ArraySize-1]=highestlow+(h38-highestlow)*fib_no; };
	f50[sc.ArraySize-2]=0;f50[sc.ArraySize-3]=0;f50[sc.ArraySize-4]=0;


	Recalc=0;
	EndTime=DTA[oSize-1].GetTime()+(DTA[oSize-2].GetTime()-DTA[oSize-3].GetTime());

	if(sc.DateTimeOfLastFileRecord.GetTime()<EndTime && sc.Input[7].FloatValue>=1)  //  
	{
		if(sc.BaseDataIn[1][sc.ArraySize-1]>h)  {h = sc.BaseDataIn[1][sc.ArraySize-1];Recalc=1;};
		if(sc.BaseDataIn[2][sc.ArraySize-1]<l  && sc.BaseDataIn[2][sc.ArraySize-1]>0) {l = sc.BaseDataIn[2][sc.ArraySize-1];Recalc=1;};
	};
	if(Recalc==1)
	{  
		for (ps=sc.ArraySize-1; (ps > sc.ArraySize-30 && ps > ps_m1); ps--) // && ps > ps_m1
		{ sc.Subgraph[0][ps]=h; sc.Subgraph[3][ps]=l-cosmetic_offset; }
	}	

	for(int j=0;j<10;j++) { f38a[10-j]=inH[oSize-1-j];  f38a[20-j]=inL[oSize-1-j]; };
	f38a[0]= EndTime;
}

/***********************************************************************/
SCSFExport scsf_COG(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="CoG";
		sc.StudyDescription="CoG";
		sc.Subgraph[0].Name="C";
		sc.Subgraph[1].Name="Cave";
		sc.Subgraph[2].Name="Line1";
		sc.Subgraph[3].Name="Line2";
		sc.Subgraph[4].Name="Line3";
		if(sc.Input[0].IndexValue==3) sc.Input[0].IndexValue=8;
		if(sc.Input[2].FloatValue==0) sc.Input[2].FloatValue=10;
		if(sc.Input[3].FloatValue==0) sc.Input[3].FloatValue=3;

		sc.Input[0].Name="Input Data";
		sc.Input[2].Name="Length";
		sc.Input[3].Name="Avg Length";
		sc.Input[4].Name="Line1 Value";
		sc.Input[5].Name="Line2 Value";
		sc.Input[6].Name="Line3 Value";

		sc.DrawZeros=1;
		sc.FreeDLL=0; 
		return;
	}
	int pos,i;
	float num, den;
	float factor1  = 2/(sc.Input[3].FloatValue+1);  float factor10 = 1-factor1;

	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		num=0; den=0;
		for(i=0;i<=sc.Input[2].FloatValue;i++)
		{
			num=num+sc.BaseDataIn[sc.Input[0].IndexValue][pos-i]*(i+1);
			den=den+sc.BaseDataIn[sc.Input[0].IndexValue][pos-i];
			sc.Subgraph[0].Data[pos]= -num/den;
			sc.Subgraph[1].Data[pos]= sc.Subgraph[1].Data[pos-1]*factor10+sc.Subgraph[0].Data[pos]*factor1;
		}
		sc.Subgraph[2].Data[pos]=sc.Input[5].FloatValue;
		sc.Subgraph[3].Data[pos]=sc.Input[5].FloatValue;
		sc.Subgraph[4].Data[pos]=sc.Input[6].FloatValue;
	}
};



/***********************************************************************/
SCSFExport scsf_LRSI(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="LRSI";
		sc.Subgraph[0].Name="L";
		sc.Subgraph[1].Name="LSmooth";
		sc.Subgraph[2].Name="Line 1";
		sc.Subgraph[3].Name="Line 2";
		sc.Input[3].Name="Gamma";
		sc.Input[4].Name="EmaSmoothing";
		sc.Input[5].Name="Line1 Value";
		sc.Input[6].Name="Line2 Value";
		sc.Input[3].SetFloat(.5);
		sc.Input[4].SetFloat(3);
		sc.Input[5].SetFloat(80);
		sc.Input[6].SetFloat(20);
		sc.FreeDLL=0; 
		sc.DrawZeros=1;
		return;
	}

	SCSubgraphRef L0 = sc.Subgraph[5];		SCSubgraphRef L1 = sc.Subgraph[6];
	SCSubgraphRef L2 = sc.Subgraph[7];		SCSubgraphRef L3 = sc.Subgraph[8];

	int    ps;
	float  CU,CD;
	float gamma=sc.Input[3].GetFloat();
	float factor1 = 2/(sc.Input[4].GetFloat()+1);
	float UpAmt=0, DnAmt=0, UpSum=0, DnSum=0, UpAvg=0, DnAvg=0, PDnAvg=0, PUpAvg=0;

	for (ps=sc.DataStartIndex; ps < sc.ArraySize; ps++)
	{
		L0[ps] = (1 - gamma)*sc.BaseDataIn[3][ps] + gamma*L0[ps-1];
		L1[ps] = - gamma*L0[ps] + L0[ps-1] + gamma*L1[ps-1];
		L2[ps] = - gamma*L1[ps] + L1[ps-1] + gamma*L2[ps-1];
		L3[ps] = - gamma*L2[ps] + L2[ps-1] + gamma*L3[ps-1];

		CU = 0;	CD = 0;

		if(L0[ps] >= L1[ps]) CU = L0[ps] - L1[ps]; else CD = L1[ps] - L0[ps];
		if(L1[ps] >= L2[ps]) CU = CU + L1[ps] - L2[ps]; else CD = CD + L2[ps] - L1[ps];
		if(L2[ps] >= L3[ps]) CU = CU + L2[ps] - L3[ps]; else CD = CD + L3[ps] - L2[ps];

		if(CU+CD!=0) 	sc.Subgraph[0].Data[ps]=100*CU/(CU+CD); else 
			sc.Subgraph[0].Data[ps]=sc.Subgraph[0].Data[ps-1];

		sc.Subgraph[1].Data[ps] = ((1-factor1)*sc.Subgraph[1].Data[ps-1]) + (factor1*sc.Subgraph[0].Data[ps]);

		sc.Subgraph[2].Data[ps] = sc.Input[5].GetFloat();
		sc.Subgraph[3].Data[ps] = sc.Input[6].GetFloat();
	}
};


/************************************************************/

SCSFExport scsf_DiMACD(SCStudyGraphRef sc)
{
	SCSubgraphRef Macd		= sc.Subgraph[0];
	SCSubgraphRef MaMacd	= sc.Subgraph[1];
	SCSubgraphRef MacdDiff	= sc.Subgraph[2];
	SCSubgraphRef RefLine	= sc.Subgraph[3];
	SCSubgraphRef FastMAOut = sc.Subgraph[4];
	SCSubgraphRef SlowMAOut = sc.Subgraph[5];

	SCInputRef InputData	= sc.Input[0];
	SCInputRef FastLen		= sc.Input[3];
	SCInputRef SlowLen		= sc.Input[4];
	SCInputRef MacdLen		= sc.Input[5];
	SCInputRef MaType		= sc.Input[6];


	if(sc.SetDefaults)
	{
		sc.GraphName = "DiNapoli MACD";
		sc.DrawZeros				= 1;
		sc.GraphRegion				= 1;
		sc.ValueFormat				= 3;		
		sc.FreeDLL=0; 

		Macd.Name = "MACD";
		MaMacd.Name	= "MA of MACD";
		MacdDiff.Name = "MACD Diff";
		MacdDiff.DrawStyle = DRAWSTYLE_BAR;
		RefLine.Name = "Line";

		InputData.Name = "Input Data";
		InputData.SetInputDataIndex(SC_LAST); 
		FastLen.Name ="Fast Moving Average Length";
		FastLen.SetFloat(8.3896);  
		SlowLen.Name = "Slow Moving Average Length";
		SlowLen.SetFloat(17.5185);  
		MacdLen.Name = "MACD Moving Average Length";
		MacdLen.SetFloat(9.0503);   
		MaType.Name = "Moving Average Type";
		MaType.SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);

		return;
	}

	sc.DataStartIndex = MacdLen.GetInt() + max(FastLen.GetFloat(), SlowLen.GetFloat());

	for(int i = sc.UpdateStartIndex;  i < sc.ArraySize;  i++)
	{
		FastMAOut[i] = (1-(2/(FastLen.GetFloat()+1)))*FastMAOut[i-1] + (2/(FastLen.GetFloat()+1))*sc.BaseDataIn[InputData.GetInputDataIndex()][i];
		SlowMAOut[i] = (1-(2/(SlowLen.GetFloat()+1)))*SlowMAOut[i-1] + (2/(SlowLen.GetFloat()+1))*sc.BaseDataIn[InputData.GetInputDataIndex()][i];
		Macd[i] = FastMAOut[i] - SlowMAOut[i];
		if(i< max(SlowLen.GetFloat(),FastLen.GetFloat()) + MacdLen.GetFloat())
			Macd[i]=0;
		MaMacd[i] = (1-(2/(MacdLen.GetFloat()+1)))*MaMacd[i-1] + (2/(MacdLen.GetFloat()+1))*Macd[i];
		MacdDiff[i] = Macd[i] - MaMacd[i];
		RefLine[i]	= 0;
	}
}


/***********************************************************************/
SCSFExport scsf_GBema34(SCStudyGraphRef sc)
{
	float& emalength = sc.Input[2].FloatValue;	float& bars4slope = sc.Input[3].FloatValue;	
	float& range = sc.Input[4].FloatValue;		float& pricediff = sc.Input[5].FloatValue;	
	float& gap = sc.Input[6].FloatValue;		float& minmult = sc.Input[8].FloatValue;
	if (sc.SetDefaults)
	{
		sc.GraphName="GB's 34EMA";
		sc.StudyDescription="34ema";
		sc.Subgraph[0].Name="Extreme Slope Colours";
		sc.Subgraph[1].Name="Trend Slope Colours";
		sc.Subgraph[2].Name="Low Slope Colours";
		sc.Subgraph[3].Name="Proximity to EMA Warning";
		sc.Subgraph[0].SecondaryColorUsed = 1;
		sc.Subgraph[1].SecondaryColorUsed = 1;
		sc.Subgraph[2].SecondaryColorUsed = 1;

		sc.Input[2].Name="Ema Length";
		sc.Input[3].Name="Number of bars for the slope";
		sc.Input[4].Name="Range to Check Slope";
		sc.Input[5].Name="Price difference for the slope";
		sc.Input[6].Name="Warn if close-ema is lower than this number";
		sc.Input[7].Name="Show EMA Slope Bars actual difference not the max difference over the range";
		sc.Input[7].ValueType=YESNO_VALUE;  
		sc.Input[8].Name="Min Angle Multiplier (default 0.1, 0.5773 gives 30 degrees)";
		sc.Input[9].Name="LSMA instead of EMA";
		sc.Input[9].ValueType=YESNO_VALUE;  

		if(bars4slope==0) bars4slope=2;
		if(range==0) range=6;
		if(pricediff==0) pricediff=1.0;
		if(minmult==0) minmult=0.1;
		if(emalength==0) emalength=34;

		sc.FreeDLL=0; 
		return;
	}

	if(sc.GraphRegion==0) { sc.Subgraph[1].DrawStyle=5; sc.Subgraph[2].DrawStyle=5; if(sc.Subgraph[0].DrawStyle==5) sc.Subgraph[0].DrawStyle=0;}
	else  { sc.Subgraph[0].DrawStyle=5; sc.Subgraph[2].DrawStyle=1; };
	sc.Subgraph[3].DrawStyle=5; // dont draw as only used for neutral colour

	if(sc.UpdateStartIndex==0) {for (int c=0; c < 50; c++) {sc.Subgraph[0].Data[c]=sc.BaseDataIn[3][c];sc.Subgraph[1].Data[c]=sc.BaseDataIn[3][c];};};

	int    pos,i;
	float  difference, difposmax,difnegmax;



	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		if(sc.Input[9].BooleanValue)
		{sc.LinearRegressionIndicator(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], pos, emalength);} else
		{sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], MOVAVGTYPE_EXPONENTIAL, pos,  emalength);}

		difference=sc.Subgraph[0].Data[pos]-sc.Subgraph[0].Data[pos-bars4slope];
		sc.Subgraph[2].Data[pos] = difference;
		if(fabs(sc.BaseDataIn[3][pos]-sc.Subgraph[0].Data[pos])<=gap) 
			sc.Subgraph[1].Data[pos] = 0.000000001; else
			sc.Subgraph[1].Data[pos] = 0;

		difposmax=0; difnegmax=0;
		for(i=0; i<range; i++)
		{
			difference=sc.Subgraph[0].Data[pos-i]-sc.Subgraph[0].Data[pos-bars4slope-i];
			if(difference>difposmax) difposmax=difference; else
				if(difference<difnegmax) difnegmax=difference;
		}
		if(difposmax>(-difnegmax)) difference=difposmax; else difference=difnegmax;
		sc.Subgraph[2].Data[pos] = difference;

		if(difference > pricediff) 
		{sc.Subgraph[0].DataColor[pos]=sc.Subgraph[0].PrimaryColor;} else
		if(difference < -pricediff) 
		{sc.Subgraph[0].DataColor[pos]=sc.Subgraph[0].SecondaryColor;} else
		if(difference >= pricediff*minmult)
		{sc.Subgraph[0].DataColor[pos]=sc.Subgraph[1].PrimaryColor;} else
		if(difference <= -pricediff*minmult)	
		{sc.Subgraph[0].DataColor[pos]=sc.Subgraph[1].SecondaryColor;} else
		if(difference >= 0)
		{sc.Subgraph[0].DataColor[pos]=sc.Subgraph[2].PrimaryColor;} else
		if(difference <= 0)	
		{sc.Subgraph[0].DataColor[pos]=sc.Subgraph[2].SecondaryColor;};
		sc.Subgraph[2].DataColor[pos]=sc.Subgraph[0].DataColor[pos];
		sc.Subgraph[1].DataColor[pos]=sc.Subgraph[3].PrimaryColor;			
	}
};


/***********************************************************************/
SCSFExport scsf_TimeLines(SCStudyGraphRef sc)
{
	if(sc.Subgraph[8].Data[1]==sc.BaseDateTimeIn[sc.ArraySize-1].GetTime() && sc.UpdateStartIndex!=0) return;
	sc.Subgraph[8].Data[1]= sc.BaseDateTimeIn[sc.ArraySize-1].GetTime();

	if (sc.SetDefaults)
	{    
		sc.GraphName="Times";
		sc.StudyDescription="Show Times as Vertical Lines";
		sc.StudyDescription="T";
		sc.Subgraph[0].Name="T1 Colour";        
		sc.Subgraph[1].Name="T2 Colour"; 
		sc.Subgraph[2].Name="T3 Colour";       
		sc.Subgraph[3].Name="T4 Colour"; 
		sc.Subgraph[4].Name="T5 Colour";        
		sc.Subgraph[5].Name="T6 Colour"; 
		sc.Subgraph[6].Name="T7 Colour";       
		sc.Subgraph[7].Name="T8 Colour"; 
		sc.Input[2].Name="Time 1";
		sc.Input[3].Name="Time 2";
		sc.Input[4].Name="Time 3";
		sc.Input[5].Name="Time 4";
		sc.Input[6].Name="Time 5";
		sc.Input[7].Name="Time 6";
		sc.Input[8].Name="Time 7";
		sc.Input[9].Name="Time 8";
		sc.Input[2].ValueType=TIME_VALUE;
		sc.Input[3].ValueType=TIME_VALUE;
		sc.Input[4].ValueType=TIME_VALUE;
		sc.Input[5].ValueType=TIME_VALUE;
		sc.Input[6].ValueType=TIME_VALUE;
		sc.Input[7].ValueType=TIME_VALUE;
		sc.Input[8].ValueType=TIME_VALUE;
		sc.Input[9].ValueType=TIME_VALUE;
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.FreeDLL = 0; 
		return;
	}  
	float High, Low;	sc.GetMainGraphVisibleHighAndLow(High,Low);

	int i;
	for (i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		sc.Subgraph[0][i] = High+1;
		if(sc.BaseDateTimeIn[i-1].GetTime()<sc.Input[2].GetTime() && sc.BaseDateTimeIn[i].GetTime()>=sc.Input[2].GetTime())
			sc.Subgraph[0].DataColor[i] = sc.Subgraph[0].PrimaryColor; else
			if(sc.BaseDateTimeIn[i-1].GetTime()<sc.Input[3].GetTime() && sc.BaseDateTimeIn[i].GetTime()>=sc.Input[3].GetTime())
				sc.Subgraph[0].DataColor[i] = sc.Subgraph[1].PrimaryColor; else
				if(sc.BaseDateTimeIn[i-1].GetTime()<sc.Input[4].GetTime() && sc.BaseDateTimeIn[i].GetTime()>=sc.Input[4].GetTime())
					sc.Subgraph[0].DataColor[i] = sc.Subgraph[2].PrimaryColor; else
					if(sc.BaseDateTimeIn[i-1].GetTime()<sc.Input[5].GetTime() && sc.BaseDateTimeIn[i].GetTime()>=sc.Input[5].GetTime())
						sc.Subgraph[0].DataColor[i] = sc.Subgraph[3].PrimaryColor; else

						if(sc.BaseDateTimeIn[i-1].GetTime()<sc.Input[6].GetTime() && sc.BaseDateTimeIn[i].GetTime()>=sc.Input[6].GetTime())
							sc.Subgraph[0].DataColor[i] = sc.Subgraph[4].PrimaryColor; else
							if(sc.BaseDateTimeIn[i-1].GetTime()<sc.Input[7].GetTime() && sc.BaseDateTimeIn[i].GetTime()>=sc.Input[7].GetTime())
								sc.Subgraph[0].DataColor[i] = sc.Subgraph[5].PrimaryColor; else
								if(sc.BaseDateTimeIn[i-1].GetTime()<sc.Input[8].GetTime() && sc.BaseDateTimeIn[i].GetTime()>=sc.Input[8].GetTime())
									sc.Subgraph[0].DataColor[i] = sc.Subgraph[6].PrimaryColor; else
									if(sc.BaseDateTimeIn[i-1].GetTime()<sc.Input[9].GetTime() && sc.BaseDateTimeIn[i].GetTime()>=sc.Input[9].GetTime())
										sc.Subgraph[0].DataColor[i] = sc.Subgraph[7].PrimaryColor; else

										sc.Subgraph[0][i] = 0;		
	};
}


/*==========================================================================*/
SCSFExport scsf_AccelBands(SCStudyGraphRef sc)
{
	if(sc.SetDefaults)
	{
		sc.GraphName = "ABands";
		sc.StudyDescription = "Price Headley's Big Trends Acceleration Bands";
		sc.GraphRegion = 0;
		sc.Subgraph[0].Name = "MA";
		sc.Subgraph[1].Name = "UAL";
		sc.Subgraph[2].Name = "LAL";
		sc.Input[4].Name = "MA Length";		
		sc.Input[4].SetInt(20); 
		sc.FreeDLL = 0;
		return;
	}

	float high, low;	

	for (int i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		high=sc.BaseDataIn[1][i]; 	low=sc.BaseDataIn[2][i];
		sc.Subgraph[3][i]= high * (1 + 2*( ((high - low) / ((high + low)/2))*1000 )*.001);
		sc.Subgraph[4][i]= low  * (1 - 2*( ((high - low) / ((high + low)/2))*1000 )*.001);

		sc.MovingAverage(sc.BaseDataIn[3], sc.Subgraph[0],   MOVAVGTYPE_SIMPLE, i, sc.Input[4].IntValue);
		sc.MovingAverage(sc.Subgraph[3],   sc.Subgraph[1],   MOVAVGTYPE_SIMPLE, i, sc.Input[4].IntValue);
		sc.MovingAverage(sc.Subgraph[4],   sc.Subgraph[2],   MOVAVGTYPE_SIMPLE, i, sc.Input[4].IntValue);
	}
}



/***********************************************************************/
SCSFExport scsf_ALMA(SCStudyGraphRef sc)
{
	//
	// ALMA by Arnaud Legoux / Dimitris Kouzis-Loukas / Anthony Cascino
	// www.arnaudlegoux.com
	// Adapted and coded by kiwi / kiwi_trader for Sierra Chart
	// from MQ4 code by IgorAD,igorad2003@yahoo.co.uk
	//
	SCSubgraphRef 	ALMA = sc.Subgraph[0], Uptrend = sc.Subgraph[1], Dntrend = sc.Subgraph[2], trend = sc.Subgraph[3], 
					stdevALMA = sc.Subgraph[4], wALMA = sc.Subgraph[5], o6 = sc.Subgraph[6], o7 = sc.Subgraph[7], o8 = sc.Subgraph[8];
	if (sc.SetDefaults)
	{
	   	sc.GraphName="ALMA";
	    sc.StudyDescription="ALMA by Arnaud Legoux / Dimitris Kouzis-Loukas / Anthony Cascino";
		sc.Subgraph[0].Name="ALMA";					sc.Subgraph[0].DrawStyle=DRAWSTYLE_LINE;
		sc.Subgraph[1].Name="Uptrend";				sc.Subgraph[1].DrawStyle=DRAWSTYLE_LINE_SKIPZEROS;
		sc.Subgraph[2].Name="Dntrend";				sc.Subgraph[2].DrawStyle=DRAWSTYLE_LINE_SKIPZEROS;
		sc.Subgraph[3].Name="trend";				sc.Subgraph[3].DrawStyle=DRAWSTYLE_IGNORE;
		sc.Subgraph[4].Name="stdevALMA";
		sc.Subgraph[5].Name="wALMA";
		sc.Subgraph[6].Name="6";
		sc.Subgraph[7].Name="7";
		sc.Subgraph[8].Name="8";
		
		sc.Input[0].Name = "Input Data";			sc.Input[0].SetInputDataIndex(SC_LAST);
		sc.Input[3].Name="Size";					sc.Input[3].SetFloat(9); 
		sc.Input[4].Name="Sigma";					sc.Input[4].SetFloat(6.0); 
		sc.Input[5].Name="Offset";					sc.Input[5].SetFloat(0.85); 
		sc.Input[6].Name="PctFilter";				sc.Input[6].SetInt(0); 
		sc.Input[7].Name="ColorMode";				sc.Input[7].SetYesNo(1); 
		sc.Input[8].Name="ColorBarBack";			sc.Input[8].SetInt(1); 
		sc.Input[9].Name="AlertMode";				sc.Input[9].SetYesNo(0); 
		sc.Input[10].Name="WarningMode";			sc.Input[10].SetYesNo(0); 
		
		sc.GraphRegion=0;
		sc.ScaleRangeType = SCALE_SAMEASREGION;
	    sc.FreeDLL=0; 
	    return;
	}
		

	int i=0,j=0;
	bool UpTrendAlert=false, DownTrendAlert=false;
	double& Size=sc.PersistVars->d1;		double& Sigma=sc.PersistVars->d2;	double& Offset=sc.PersistVars->d3;
	double& PctFilter=sc.PersistVars->d4;	double& ColorMode=sc.PersistVars->d5;  int& ColorBarBack=sc.PersistVars->i1;
	
	if(sc.UpdateStartIndex==0)	{	
		Size = sc.Input[3].GetFloat(); 			Sigma = sc.Input[4].GetFloat(); 	Offset = sc.Input[5].GetFloat();
		PctFilter = sc.Input[6].GetFloat(); 	ColorMode = sc.Input[7].GetFloat(); ColorBarBack=sc.Input[8].GetInt();	
				
		double m = floor(Offset * (Size - 1)), s = Size/Sigma, wsum = 0;		
		for (j=0;j < Size;j++) 
		{
			wALMA[j] = exp(-((j-m)*(j-m))/(2*s*s));
			wsum += wALMA[j];
		}
		for (j=0;j < Size;j++) wALMA[j] = wALMA[j]/wsum; 
	}
	
		
	for(i = sc.UpdateStartIndex;  i < sc.ArraySize;  i++)
	{	
		double sum=0;
		for(j=0;j < Size;j++) { sum += wALMA[j] * sc.BaseDataIn[sc.Input[0].GetInputDataIndex()][i-(Size - 1 - j)]; }
		ALMA[i] = sum;
		
		double Filter=0;
		if(PctFilter>0)	{
			sc.StdDeviation(ALMA, stdevALMA, i, Size);
			Filter = PctFilter * stdevALMA[i];
			if( abs(ALMA[i]-ALMA[i-1]) < Filter ) ALMA[i]=ALMA[i-1];
		}
		   
		if (ColorMode>0){
			trend[i] = trend[i-1];
			if (ALMA[i] - ALMA[i-1] > Filter) trend[i] = 1;
			if (ALMA[i-1] - ALMA[i] > Filter) trend[i] =-1;

			if (trend[i]>0)	{
				Uptrend[i] = ALMA[i]; 
				if (trend[i-ColorBarBack]<0) Uptrend[i-ColorBarBack]=ALMA[i-ColorBarBack];
				Dntrend[i] = 0;
			}
			else              
			if (trend[i]<0)	{ 
				Dntrend[i] = ALMA[i]; 
				if (trend[i-ColorBarBack]>0) Dntrend[i-ColorBarBack]=ALMA[i-ColorBarBack];
				Uptrend[i] = 0;
			}               
		}
	
		
	}
}

/***********************************************************************/
SCSFExport scsf_Weekly(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "Weekly";
		sc.StudyDescription = " ";
		sc.IsCustomChart = 1;  // true		
		sc.GraphRegion = 0;  // First region		
		sc.DrawZeros = 0;  // false		
		sc.GraphDrawType=GDT_OHLCBAR ;
		sc.StandardChartHeader = 1; // true
		sc.Subgraph[0].Name = "Open";		sc.Subgraph[1].Name = "High";		sc.Subgraph[2].Name = "Low";
		sc.Subgraph[3].Name = "Last";		sc.Subgraph[4].Name = "Volume";		sc.Subgraph[5].Name = "# of Trades";
		sc.Subgraph[6].Name = "HL";		sc.Subgraph[7].Name = "HLC";	sc.Subgraph[8].Name = "OHLC";
		sc.Subgraph[9].Name = "1";		sc.Subgraph[10].Name = "2";		sc.Subgraph[11].Name = "3";
		sc.FreeDLL=0;
		return;
	} 
		
	int i, as=sc.ArraySize-1;	
	int& out  = sc.PersistVars->i1; 	int& CurrentBarTime = sc.PersistVars->i2;	int& CurrentBarDate = sc.PersistVars->i3;
	float& o  = sc.PersistVars->f1;		float& h  = sc.PersistVars->f2;	float& l  = sc.PersistVars->f3;
	float& c  = sc.PersistVars->f4;		float& v  = sc.PersistVars->f5;	float& oi  = sc.PersistVars->f6;	
		
	
	if (sc.UpdateStartIndex == 0)
	{
		sc.ResizeArrays(0); out=0;
	}
	
	if (sc.UpdateStartIndex == 0)
	{
		for (i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
		{
			if(	sc.BaseDateTimeIn[i].GetDayOfWeek()==MONDAY	|| sc.BaseDateTimeIn[i].GetDayOfWeek()<sc.BaseDateTimeIn[i-1].GetDayOfWeek() ) //sc.BaseDateTimeIn[i].GetDate()>0 ) // 
			{ 
				if (sc.OutArraySize - 1 < i) {
					sc.AddElements(1);
					sc.DateTimeOut[out].SetTime(CurrentBarTime);
					sc.DateTimeOut[out].SetDate(CurrentBarDate);
					sc.Subgraph[0][out] = o;
					sc.Subgraph[1][out] = h;
					sc.Subgraph[2][out] = l;
					sc.Subgraph[3][out] = sc.BaseDataIn[3][i-1];
					sc.Subgraph[4][out] = v;
					sc.Subgraph[5][out] = oi;
					sc.CalculateOHLCAverages(out);
					o=sc.BaseDataIn[0][i]; h=sc.BaseDataIn[1][i]; l=sc.BaseDataIn[2][i]; v=sc.BaseDataIn[4][i]; oi=sc.BaseDataIn[5][i];
					CurrentBarTime=sc.BaseDateTimeIn[i].GetTime();	CurrentBarDate=sc.BaseDateTimeIn[i].GetDate();
					out++;	
				}
			} else
			{
					if(h<sc.BaseDataIn[1][i]) { h=sc.BaseDataIn[1][i];}
					if(l>sc.BaseDataIn[2][i]) {	l=sc.BaseDataIn[2][i];}
			}
		}
		sc.AddElements(1);
	}
	
	if(h<sc.BaseDataIn[1][as]) { h=sc.BaseDataIn[1][as];}
	if(l>sc.BaseDataIn[2][as]) { l=sc.BaseDataIn[2][as];}
	out=sc.OutArraySize-1; 
	sc.DateTimeOut[out].SetTime(CurrentBarTime);
	sc.DateTimeOut[out].SetDate(CurrentBarDate);
	sc.Subgraph[0][out] = o;
	sc.Subgraph[1][out] = h;
	sc.Subgraph[2][out] = l;
	sc.Subgraph[3][out] = sc.BaseDataIn[3][as];
	sc.Subgraph[4][out] = v;
	sc.Subgraph[5][out] = oi;
	sc.CalculateOHLCAverages(out);
}

/***********************************************************************/
SCSFExport scsf_CF60(SCStudyGraphRef sc)
{	
	
	SCSubgraphRef 	Trend=sc.Subgraph[8],  ma8 = sc.Subgraph[0], ma12 = sc.Subgraph[1], ma24 = sc.Subgraph[2], ma72 = sc.Subgraph[3];
			
	
	if (sc.SetDefaults)
    {
        sc.GraphName="Cornflower 60 for Fx";			
		sc.FreeDLL=0;
        sc.StudyDescription="Fx Cornflower for 60m";
		ma8.Name="ma8"; ma12.Name="ma12"; ma24.Name="ma24"; ma72.Name="ma72"; 
		sc.Input[3].Name="Show Trend On Last Bar Only";	 sc.Input[3].ValueType=YESNO_VALUE;
		sc.Input[17].Name="ma8";  sc.Input[17].SetInt(8); sc.Input[18].Name="ma12"; sc.Input[18].SetInt(12); 
		sc.Input[19].Name="ma24"; sc.Input[19].SetInt(24); sc.Input[20].Name="ma72";  sc.Input[20].SetInt(72);
		sc.GraphRegion=0;		sc.ScaleRangeType=SCALE_SAMEASREGION;        return;
    }
	
	sc.Input[3].Name="Show Trend On Last Bar Only";	 sc.Input[3].ValueType=YESNO_VALUE;

	SCBaseDataRef DIn = sc.BaseDataIn;			int const hx = 1;	int const lx = 2; 

	for(int i = sc.UpdateStartIndex;  i < sc.ArraySize;  i++)
	{	
		int p=i-1, p2=i-2;//, p3=i-3, p4=i-4;
	
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], ma8, MOVAVGTYPE_EXPONENTIAL, i, sc.Input[17].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], ma12, MOVAVGTYPE_EXPONENTIAL, i, sc.Input[18].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], ma24, MOVAVGTYPE_EXPONENTIAL, i, sc.Input[19].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], ma72, MOVAVGTYPE_EXPONENTIAL, i, sc.Input[20].GetInt());

		if(sc.Input[3].BooleanValue) {
			if(ma8[p]>ma12[p] && ma12[p]>ma24[p] && ma24[p]>ma72[p]) { Trend[p]=+60; } else
			if(ma8[p]<ma12[p] && ma12[p]<ma24[p] && ma24[p]<ma72[p]) { Trend[p]=-60; } else
			if(Trend[p2]>=+20 && ma12[p]<ma24[p]) 	Trend[p]=+20; else
			if(Trend[p2]>=+20 && ma8[p]<ma12[p]) 	Trend[p]=+30; else
			if(Trend[p2]<=-20 && ma12[p]>ma24[p]) 	Trend[p]=-20; else
			if(Trend[p2]<=-20 && ma8[p]>ma12[p]) 	Trend[p]=-30;

			ma72.DataColor[i]=0xFFFFFF;
			if(Trend[p]>=+20 && Trend[p]<+30) ma72.DataColor[p]=RGB(0,0,127); 	else if(Trend[p]==-20 && Trend[p]>-30) ma72.DataColor[p]=RGB(127,0,0); else
			if(Trend[p]>=+30 && Trend[p]<+40) ma72.DataColor[p]=RGB(0,0,255);	else if(Trend[p]<=-30 && Trend[p]>-40) ma72.DataColor[p]=RGB(255,0,0); else
			if(Trend[p]>=+60) ma72.DataColor[p]=RGB(0,200,255); 				else if(Trend[p]<=-60) ma72.DataColor[p]=RGB(255,128,128); 
		} else
		{
			if(ma8[i]>ma12[i] && ma12[i]>ma24[i] && ma24[i]>ma72[i]) { Trend[i]=+60; } else
			if(ma8[i]<ma12[i] && ma12[i]<ma24[i] && ma24[i]<ma72[i]) { Trend[i]=-60; } else
			if(Trend[p2]>=+20 && ma12[i]<ma24[i]) 	Trend[i]=+20; else
			if(Trend[p2]>=+20 && ma8[i]<ma12[i]) 	Trend[i]=+30; else
			if(Trend[p2]<=-20 && ma12[i]>ma24[i]) 	Trend[i]=-20; else
			if(Trend[p2]<=-20 && ma8[i]>ma12[i]) 	Trend[i]=-30;

			ma72.DataColor[i]=0xFFFFFF;
			if(Trend[i]>=+20 && Trend[i]<+30) ma72.DataColor[i]=RGB(0,0,127); 	else if(Trend[i]==-20 && Trend[i]>-30) ma72.DataColor[i]=RGB(127,0,0); else
			if(Trend[i]>=+30 && Trend[i]<+40) ma72.DataColor[i]=RGB(0,0,255);	else if(Trend[i]<=-30 && Trend[i]>-40) ma72.DataColor[i]=RGB(255,0,0); else
			if(Trend[i]>=+60) ma72.DataColor[i]=RGB(0,200,255); 				else if(Trend[i]<=-60) ma72.DataColor[i]=RGB(255,128,128); 
		}
	}
};

/***********************************************************************/
SCSFExport scsf_CF05(SCStudyGraphRef sc)
{	
	
	SCSubgraphRef 	Trend=sc.Subgraph[8],  ma5 = sc.Subgraph[0], ma10 = sc.Subgraph[1], ma21 = sc.Subgraph[2], ma50 = sc.Subgraph[3];
			
	
	if (sc.SetDefaults)
    {
        sc.GraphName="Cornflower 5m for Fx";			
		sc.FreeDLL=0;
        sc.StudyDescription="Fx Cornflower for 5m chart";
		ma5.Name="ma5"; ma10.Name="ma10"; ma21.Name="ma21"; ma50.Name="ma50"; 
		sc.Input[17].Name="ma5";  sc.Input[17].SetInt(5); sc.Input[18].Name="ma10"; sc.Input[18].SetInt(10); 
		sc.Input[19].Name="ma21"; sc.Input[19].SetInt(21); sc.Input[20].Name="ma50";  sc.Input[20].SetInt(50);
		sc.GraphRegion=0;		sc.ScaleRangeType=SCALE_SAMEASREGION;        return;
    }

	SCBaseDataRef DIn = sc.BaseDataIn;			int const hx = 1;	int const lx = 2; 

	for(int i = sc.UpdateStartIndex;  i < sc.ArraySize;  i++)
	{	
		int p=i-1, p2=i-2, p3=i-3, p4=i-4;
	
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], ma5, MOVAVGTYPE_EXPONENTIAL, i, sc.Input[17].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], ma10, MOVAVGTYPE_EXPONENTIAL, i, sc.Input[18].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], ma21, MOVAVGTYPE_EXPONENTIAL, i, sc.Input[19].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], ma50, MOVAVGTYPE_EXPONENTIAL, i, sc.Input[20].GetInt());		
	}
};


/***********************************************************************/
SCSFExport scsf_Direction(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
    {
        sc.GraphName="Direction";
		sc.StudyDescription = "Direction";

			sc.Subgraph[0].Name="Up/Dn Bar Colour";
		sc.Subgraph[1].Name="Day Inside Bar Colour";
		sc.Subgraph[2].Name="Night Colour";
		sc.Subgraph[3].Name="Night Inside Bar Colour";
		sc.Subgraph[0].SecondaryColorUsed=1;
		sc.Subgraph[2].SecondaryColorUsed=1;
		sc.Subgraph[4].SecondaryColorUsed=1;
		sc.GraphRegion=0;
		sc.ScaleRangeType=SCALE_SAMEASREGION;
		sc.GraphDrawType=GDT_OHLCBAR ;
        sc.Input[2].Name="Early Before";        sc.Input[3].Name="Late After";
		sc.Input[6].Name="Bracket Start";       sc.Input[7].Name="Bracket Over";
        sc.Input[2].ValueType=TIME_VALUE;       sc.Input[3].ValueType=TIME_VALUE;
        sc.Input[6].ValueType=TIME_VALUE;       sc.Input[7].ValueType=TIME_VALUE;
		sc.Input[4].Name="Show IBs";			sc.Input[4].ValueType=YESNO_VALUE;
		sc.Input[5].Name="Offset to start new direction";
		
		sc.CalculationPrecedence = VERY_LOW_PREC_LEVEL;
		sc.FreeDLL=0;
		sc.DataStartIndex=10;
        return;
	}
	int    pos,updown=1,os;
    float  highestlow=0.0,lowesthigh=999999.9;
	if(sc.UpdateStartIndex==0) sc.UpdateStartIndex=1;
    double offset= sc.Input[5].FloatValue*sc.TickSize;

    for (pos=sc.UpdateStartIndex-1; pos < sc.ArraySize; pos++)
    {
		int upcolour, dncolour, oscolour;
		if(sc.BaseDateTimeIn[pos].GetTime()<sc.Input[2].GetTime() || (sc.Input[3].GetTime()!=0 && sc.BaseDateTimeIn[pos].GetTime()>=sc.Input[3].GetTime())
			|| (sc.Input[6].GetTime()!=0 && sc.BaseDateTimeIn[pos].GetTime()>=sc.Input[6].GetTime() && sc.BaseDateTimeIn[pos].GetTime()<sc.Input[7].GetTime()))
		{
				upcolour = sc.Subgraph[2].PrimaryColor; 
				dncolour = sc.Subgraph[2].SecondaryColor; 
				oscolour = (sc.Subgraph[3].PrimaryColor); 
		} else
		{
				upcolour = sc.Subgraph[0].PrimaryColor; 
				dncolour = sc.Subgraph[0].SecondaryColor;
				oscolour = sc.Subgraph[1].PrimaryColor;
		}
	
		updown=(int)sc.Subgraph[5][pos-1]; os=(int)sc.Subgraph[6][pos-1]; if(updown==0) updown=1;
		lowesthigh=sc.Subgraph[7][pos-1]; highestlow=sc.Subgraph[8][pos-1];

		float& h = sc.BaseDataIn[1][pos]; float& l = sc.BaseDataIn[2][pos];
		if(updown== 1) {if(l>highestlow) highestlow=l;} else
				{if(h<lowesthigh) lowesthigh=h;};
		os=0; // sc.Subgraph[4][pos] = h;
		
		if(h>lowesthigh+offset && l>=sc.BaseDataIn[2][pos-1]-offset) {updown=1; highestlow=l; lowesthigh=h;} else
		if(l<highestlow-offset && h<=sc.BaseDataIn[1][pos-1]+offset) {updown=-1;lowesthigh=h; highestlow=l;} 
	//	if(sc.BaseDataIn[1][pos]>sc.BaseDataIn[1][pos-1]+offset && sc.BaseDataIn[2][pos]<sc.BaseDataIn[2][pos-1]-offset)  {os=1;};
		if((sc.BaseDataIn[1][pos]<sc.BaseDataIn[1][pos-1] && sc.BaseDataIn[2][pos]>=sc.BaseDataIn[2][pos-1] ||
			sc.BaseDataIn[1][pos]<=sc.BaseDataIn[1][pos-1] && sc.BaseDataIn[2][pos]>sc.BaseDataIn[2][pos-1]) && sc.Input[4].GetYesNo())  {os=1;};
			
		if(os==1)
		{ sc.Subgraph[0].DataColor[pos] = oscolour; sc.Subgraph[1].DataColor[pos] = oscolour;
		  sc.Subgraph[2].DataColor[pos] = oscolour; sc.Subgraph[3].DataColor[pos] = oscolour;
		} else
		if(updown==1)
		{ sc.Subgraph[0].DataColor[pos] = upcolour; sc.Subgraph[1].DataColor[pos] = upcolour;
		  sc.Subgraph[2].DataColor[pos] = upcolour; sc.Subgraph[3].DataColor[pos] = upcolour;
		} else
		if(updown==-1)
		{ sc.Subgraph[0].DataColor[pos] = dncolour; sc.Subgraph[1].DataColor[pos] = dncolour;
		  sc.Subgraph[2].DataColor[pos] = dncolour; sc.Subgraph[3].DataColor[pos] = dncolour;
		};
		
        sc.Subgraph[0][pos] = sc.BaseDataIn[0][pos];        sc.Subgraph[1][pos] = sc.BaseDataIn[1][pos];
        sc.Subgraph[2][pos] = sc.BaseDataIn[2][pos];        sc.Subgraph[3][pos] = sc.BaseDataIn[3][pos];

        sc.Subgraph[5][pos]=updown; sc.Subgraph[6][pos]=os;
        sc.Subgraph[7][pos]=lowesthigh; sc.Subgraph[8][pos]=highestlow;
    }
}



/***********************************************************************/
SCSFExport scsf_2TrendAdd(SCStudyGraphRef sc)
{
	SCSubgraphRef 	EnterNow = sc.Subgraph[0], LTF = sc.Subgraph[1], TF = sc.Subgraph[2], R1 = sc.Subgraph[3], 
					se5 = sc.Subgraph[12], se12 = sc.Subgraph[13], sr = sc.Subgraph[14], xe5 = sc.Subgraph[15], xe12 = sc.Subgraph[16], xr = sc.Subgraph[17],
					lc = sc.Subgraph[20], le5 = sc.Subgraph[21], le12 = sc.Subgraph[22], lr = sc.Subgraph[23],	ple5 = sc.Subgraph[24], ple12 = sc.Subgraph[25], plr = sc.Subgraph[26];	

	if (sc.SetDefaults)
	{
		sc.GraphName="Two Timeframe Trend Additive";
		EnterNow.Name="EnterNow";	LTF.Name="LTF";		TF.Name="TF";	R1.Name="R1";
		se5.Name="se5";		se12.Name="se12";	sr.Name="sr";		xe5.Name="se5";		xe12.Name="se12";	xr.Name="sr";		
		lc.Name="lc";		le5.Name="le5";		le12.Name="le12";	lr.Name="lr";	ple5.Name="ple5";		ple12.Name="ple12";	plr.Name="plr";	
		sc.CalculationPrecedence = STD_PREC_LEVEL ;		sc.DrawZeros=0;		return;
	}
	/*
		This takes the trend from 5m and 30m using rsi>50 and ema1>ema2 for +ve
		When both trends are in the same direciton positive trend exists and price/value signals can be taken
		So it is the addition of 2 trends
	*/
	int 	i,p,p2,lp,hour,minute,second, minute2, as=sc.ArraySize-1, ST_Direction;
	int& li = sc.PersistVars->i1; int& offset = sc.PersistVars->i2;	int& lastshifted = sc.PersistVars->i3;
	int& lastdot = sc.PersistVars->i4; float& LT_Direction = sc.PersistVars->f1; 
	
	if(sc.UpdateStartIndex==0) { li=0; offset=5; lastshifted=0; LT_Direction=0; ST_Direction=0; }
	
	for (i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		p=i-1; lp=li-1; p2=i-2;
		sc.BaseDateTimeIn[i-1].GetTimeHMS(hour, minute, second);  sc.BaseDateTimeIn[i].GetTimeHMS(hour, minute2, second);
		if( (minute2 % 30)==0 || (((minute+5) % 30)==0 && (minute2 % 30)!=0) ) {   //|| (fmod(minute+5,30)==0 && fmod(minute2,30)!=0)
			lc[li]=sc.BaseDataIn[SC_LAST][p];
			sc.MovingAverage(lc, le5,  MOVAVGTYPE_EXPONENTIAL, li, 5 );
			sc.MovingAverage(lc, le12, MOVAVGTYPE_EXPONENTIAL, li, 12);
			sc.RSI(lc, lr, li, MOVAVGTYPE_SIMPLE, 20);	
			if(lr[li]>50 && (le5[li]>le12[li] || (le5[li]==le12[li] && le5[lp]>le12[lp]))) LT_Direction=+1; else
			if(lr[li]<50 && (le5[li]<le12[li] || (le5[li]==le12[li] && le5[lp]<le12[lp]))) LT_Direction=-1; else
				LT_Direction=0;
			if(i<as) li++;
		} 
		LTF[i]=LT_Direction/1.1;
		
	
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], se5,  MOVAVGTYPE_EXPONENTIAL, i, 5 );
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], se12, MOVAVGTYPE_EXPONENTIAL, i, 12);
		sc.RSI(sc.BaseDataIn[SC_LAST], sr, i, MOVAVGTYPE_SIMPLE, 20);	
		if(sr[p]>50 && (se5[p]>se12[p] || (se5[p]==se12[p] && se5[p2]>se12[p2]))) TF[i]=+0.8; else
		if(sr[p]<50 && (se5[p]<se12[p] || (se5[p]==se12[p] && se5[p2]<se12[p2]))) TF[i]=-0.8; else
			TF[i]=0;
			
 		EnterNow[i]=0;
	//	if( sc.BaseDateTimeIn[i].GetTime()>=HMS_TIME(10,00,00) && sc.BaseDateTimeIn[i].GetTime()<=HMS_TIME(12,00,00) ) {
			if(LTF[i]>0 && TF[i]>0) EnterNow[i]=.6; else 
				if(LTF[i]<0 && TF[i]<0)  EnterNow[i]=-.6;
	//	}		
	
	}
};


/***********************************************************************/
SCSFExport scsf_ScrPdr(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "Screen Padder";
		sc.StudyDescription = "Inserts White Space at top and bottom of screen (half the pips at the bottom";		
		sc.GraphRegion = 0;  		sc.DrawZeros = 0;  		sc.ScaleRangeType = SCALE_AUTO;
		sc.Subgraph[0].Name = "H";	sc.Subgraph[1].Name = "L";	sc.Subgraph[0].DrawStyle=4; sc.Subgraph[1].DrawStyle=4;
		sc.Input[3].Name="Pips Above (half below)";				sc.Input[3].SetFloat(2);
		sc.Input[4].Name="Update Always";						sc.Input[4].SetYesNo(FALSE);
		sc.FreeDLL=0;
		return;
	} 
	float& up = sc.PersistVars->f1; float& dn = sc.PersistVars->f2;	float& endbar = sc.PersistVars->f3; 
	int lastbar=sc.IndexOfLastVisibleBar;
	
	if( sc.UpdateStartIndex == 0 || endbar!=lastbar )
	{
		if(sc.Input[4].GetYesNo()) sc.UpdateAlways=1; else sc.UpdateAlways=0; 
		up=sc.Input[3].GetFloat()*sc.TickSize; dn=sc.Input[3].GetFloat()*sc.TickSize;
		for(int j=sc.IndexOfFirstVisibleBar; j<lastbar; j++)
		{
			sc.Subgraph[0][j]=sc.BaseDataIn[1][j]+up;
			sc.Subgraph[1][j]=sc.BaseDataIn[2][j]-dn; 
		}
		endbar=lastbar;
	} 
	sc.Subgraph[11][lastbar]=sc.BaseDataIn[1][lastbar]+up;
	sc.Subgraph[12][lastbar]=sc.BaseDataIn[2][lastbar]-dn; 
}


/***********************************************************************/
SCSFExport scsf_QQE(SCStudyGraphRef sc)
{
// QQE (Quantative Qualitative Estimation)
SCSubgraphRef 	QQE_RSI_MA = sc.Subgraph[0], QQE_FastSignal = sc.Subgraph[1], QQE_SlowSignal = sc.Subgraph[2], mid = sc.Subgraph[3],
				QQE_ATR_RSI = sc.Subgraph[5], QQE_MA_ATR_RSI = sc.Subgraph[6], 
				QQE_DAR = sc.Subgraph[7], QQE_DAR_Fast = sc.Subgraph[8], QQE_RSI = sc.Subgraph[9], QQE_DAR_Temp = sc.Subgraph[10];
	if (sc.SetDefaults)
	{
	   	sc.GraphName="QQE";
	    sc.StudyDescription="QQE (Quantative Qualitative Estimation)";
		sc.Subgraph[0].Name="RSI_MA";
		sc.Subgraph[1].Name="FastSignal";
		sc.Subgraph[2].Name="SlowSignal";
		sc.Subgraph[3].Name="50";
		sc.Subgraph[4].Name="QQE_RSI_MA";
		sc.Subgraph[5].Name="QQE_ATR_RSI";
		sc.Subgraph[6].Name="QQE_MA_ATR_RSI";
		sc.Subgraph[7].Name="QQE_DAR";
		sc.Subgraph[8].Name="QQE_DAR_Fast";
		sc.Input[3].Name="QQE_Periods";				sc.Input[3].SetInt(14); 
		sc.Input[4].Name="QQE_Smoothing factor";	sc.Input[4].SetInt(5); 
	    sc.FreeDLL=0; 
	    return;
	}
	/*
	QQE_Periods    = Param("Period", 14, 3, 30, 1 );
	QQE_SF         = Param("Smoothing factor", 5, 1, 30, 1 );
	QQE_RSI_MA     = EMA(RSI(QQE_Periods),QQE_SF); 
	QQE_ATR_RSI    = abs(Ref(QQE_RSI_MA,-1)-QQE_RSI_MA);
	QQE_MA_ATR_RSI = EMA(QQE_ATR_RSI, 2*QQE_Periods-1);
	QQE_DAR        = EMA(QQE_MA_ATR_RSI, 2*QQE_Periods-1)*4.236;
	QQE_DAR_Fast   = EMA(QQE_MA_ATR_RSI, 2*QQE_Periods-1)*2.618;
	*/
		
	for(int i = sc.UpdateStartIndex;  i < sc.ArraySize;  i++)
	{	
		int p=i-1, QQE_Periods=sc.Input[3].GetInt(), QQE_SF=sc.Input[4].GetInt(), QQE_PeriodsX2m1=2*QQE_Periods-1;
		sc.RSI(sc.BaseDataIn[SC_LAST], QQE_RSI, i, MOVAVGTYPE_SIMPLE, QQE_Periods);
		sc.MovingAverage(QQE_RSI, QQE_RSI_MA, MOVAVGTYPE_EXPONENTIAL, i, QQE_SF); 
		QQE_ATR_RSI[i]=fabs(QQE_RSI_MA[p]-QQE_RSI_MA[i]);
		sc.MovingAverage(QQE_ATR_RSI,  QQE_MA_ATR_RSI, MOVAVGTYPE_EXPONENTIAL, i, QQE_PeriodsX2m1); 
		sc.MovingAverage(QQE_MA_ATR_RSI, QQE_DAR_Temp, MOVAVGTYPE_EXPONENTIAL, i, QQE_PeriodsX2m1); 
		QQE_DAR[i]=QQE_DAR_Temp[i]*4.236; 
		QQE_DAR_Fast[i]=QQE_DAR_Temp[i]*2.618; 

		// QQE_FastSignal = QQE_TR(QQE_RSI_MA,QQE_DAR_Fast);
		if (QQE_RSI_MA[i] < QQE_FastSignal[p]) {
           QQE_FastSignal[i]=QQE_RSI_MA[i]+QQE_DAR_Fast[i];
           if ((QQE_RSI_MA[p] < QQE_FastSignal[p]) && (QQE_FastSignal[i] > QQE_FastSignal[p]))
              { QQE_FastSignal[i] = QQE_FastSignal[p]; }
		}  else
		if (QQE_RSI_MA[i] > QQE_FastSignal[p]) {
              QQE_FastSignal[i]=QQE_RSI_MA[i]-QQE_DAR_Fast[i];
              if ((QQE_RSI_MA[p] > QQE_FastSignal[p]) && (QQE_FastSignal[i] < QQE_FastSignal[p]))
                 { QQE_FastSignal[i] = QQE_FastSignal[p]; }
		}
		// QQE_SlowSignal = QQE_TR(QQE_RSI_MA,QQE_DAR);
		if (QQE_RSI_MA[i] < QQE_SlowSignal[p]) {
           QQE_SlowSignal[i]=QQE_RSI_MA[i]+QQE_DAR[i];
           if ((QQE_RSI_MA[p] < QQE_SlowSignal[p]) && (QQE_SlowSignal[i] > QQE_SlowSignal[p]))
              { QQE_SlowSignal[i] = QQE_SlowSignal[p]; }
		}  else
		if (QQE_RSI_MA[i] > QQE_SlowSignal[p]) {
              QQE_SlowSignal[i]=QQE_RSI_MA[i]-QQE_DAR[i];
              if ((QQE_RSI_MA[p] > QQE_SlowSignal[p]) && (QQE_SlowSignal[i] < QQE_SlowSignal[p]))
                 { QQE_SlowSignal[i] = QQE_SlowSignal[p]; }
		}
		mid[i]=50;
	}
}

/***********************************************************************/
SCSFExport scsf_Alerter(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "Alerter";
		sc.StudyDescription = "Reads Alerts from C:\\SierraChart\\Alerts.txt";		
		
		sc.Subgraph[0].Name = "AlertLine";		
		sc.Subgraph[0].SecondaryColorUsed=1;
		sc.Input[0].Name="Input Data";		
		sc.Input[0].SetInputDataIndex(SC_LAST);
		sc.Input[1].Name="Alert Number";		
		sc.Input[1].SetInt(1);
		sc.Input[2].Name="Alert Only Once Per Bar?";		
		sc.Input[2].SetYesNo(true);
		sc.Input[3].Name="Reset Alert On New Bar?";		
		sc.Input[3].SetYesNo(true);
		sc.TextInputName = "Alerts File Path and Name";	
		if(sc.TextInput=="")
			sc.TextInput = "C:\\SierraChart\\Alerts.txt";

		sc.FreeDLL=0;
		sc.GraphRegion = 0;
		sc.DrawZeros = 0; 
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		return;
	} 
		
	if (sc.UpdateStartIndex == 0)
	{
		sc.AlertOnlyOncePerBar = sc.Input[1].GetYesNo();
		sc.ResetAlertOnNewBar = sc.Input[2].GetYesNo();
	}
		
		
	unsigned long InputDataIndex = sc.Input[0].GetInputDataIndex();
	double alertline=0; 
	int as=sc.ArraySize-1, i;
	
	FILE * pFile;  
	pFile = fopen (sc.TextInput.GetChars(),"r");
	if (pFile!=NULL) {
		// obtain file size:
		long lSize;  char filetxt[80]=""; char AlertNum[7]=""; char UpOrDn[1]=""; char Up[1]=""; char Dn[1]="";
		strcpy(Up,"+"); strcpy(Dn,"-"); 
		fseek (pFile , 0 , SEEK_END);
		lSize = ftell (pFile);
		rewind (pFile);
		for(int j=0; j<20 && !feof(pFile); j++) {
			fgets(filetxt,20,pFile);
			if(sc.Symbol.CompareNoCase(filetxt,7)==0) {
				alertline=0; strcpy(AlertNum,"nulvoid");
				UpOrDn[0]=filetxt[8];
				for(int k=0; k<6; k++) { AlertNum[k]=filetxt[k+9]; }
				alertline=atof(AlertNum);
				if(alertline!=0) {
					if(sc.Subgraph[0][as-20]!=alertline) i=0; else i=sc.UpdateStartIndex;
					for ( ; i < sc.ArraySize; i++) { 
						sc.Subgraph[0][i]=alertline; sc.Subgraph[0].DataColor[i] = 0xC0C0C0;
						if(strncmp(UpOrDn,Up,1)==0) {
							sc.Subgraph[0].DataColor[i] = sc.Subgraph[0].PrimaryColor; 
							if(sc.BaseDataIn[sc.Input[0].GetInputDataIndex()][as]>alertline) sc.SetAlert(sc.Input[1].GetInt(),as);
						} 
						else if(strncmp(UpOrDn,Dn,1)==0) {
							sc.Subgraph[0].DataColor[i] = sc.Subgraph[0].SecondaryColor; 
							if(sc.BaseDataIn[sc.Input[0].GetInputDataIndex()][as]<alertline) sc.SetAlert(sc.Input[1].GetInt(),as);
						}
					}
				} else {
					if(sc.Subgraph[0][as-20]!=0) { for ( i=0; i < sc.ArraySize; i++) {sc.Subgraph[0][i]=0;} }				
				}
			}
		}
		fclose (pFile);
	}
}




/***********************************************************************/
SCSFExport scsf_MACDHull(SCStudyGraphRef sc)
{
  if(sc.SetDefaults) {
	sc.GraphName="MACDHull";
	sc.Subgraph[0].Name="MACD";
	sc.Subgraph[1].Name="MA of MACD";
	sc.Subgraph[2].Name="MACD Diff";
	sc.Subgraph[3].Name="Zero Line";

	sc.Input[2].Name="MACD Fast MA Length";	sc.Input[2].SetInt(12);
	sc.Input[3].Name="MACD Slow MA Length";	sc.Input[3].SetInt(26);
	sc.Input[4].Name="MACD MA Length";		sc.Input[4].SetInt(9);
	sc.DrawZeros=1;
	sc.FreeDLL=0; 
    return;
  }
	

	for (int i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		sc.HullMovingAverage(sc.BaseData[SC_LAST], sc.Subgraph[6], i, sc.Input[2].GetInt());
		sc.HullMovingAverage(sc.BaseData[SC_LAST], sc.Subgraph[7], i, sc.Input[3].GetInt());
		sc.Subgraph[0][i]=sc.Subgraph[6][i]-sc.Subgraph[7][i];
		sc.HullMovingAverage(sc.Subgraph[0], sc.Subgraph[1], i, sc.Input[4].GetInt());
		sc.Subgraph[2][i]=sc.Subgraph[0][i]-sc.Subgraph[1][i];
		sc.Subgraph[3][i]=0;

};}




/***********************************************************************/
SCSFExport scsf_MTF_TRIX(SCStudyGraphRef sc)
{
	SCSubgraphRef T = sc.Subgraph[0];
	SCSubgraphRef Ta = sc.Subgraph[1];
	SCSubgraphRef T2 = sc.Subgraph[2];
	SCSubgraphRef T2a = sc.Subgraph[3];
	SCSubgraphRef T3 = sc.Subgraph[4];
	SCSubgraphRef T3a = sc.Subgraph[5];
	SCSubgraphRef X1 = sc.Subgraph[6];
	SCSubgraphRef X2 = sc.Subgraph[7];
	SCSubgraphRef X3 = sc.Subgraph[8];
	SCSubgraphRef lc2=sc.Subgraph[10];
	SCSubgraphRef lc3=sc.Subgraph[11];
	SCSubgraphRef l12=sc.Subgraph[12];
	SCSubgraphRef l13=sc.Subgraph[13];
	
	if (sc.SetDefaults)
	{	
		sc.GraphName="MTF_Trix";
		T.Name="TF & Up colour";	
		Ta.Name="TF & Dn colour";	
		T2.Name="TF2 & Neutral Colour";	
		T2a.Name="TF2";
		T3.Name="TF3";
		T3a.Name="TF3";	
		X1.Name="X1";
		X2.Name="X2";
		X3.Name="X3";	
		T.DrawStyle=DRAWSTYLE_BARTOP;
		Ta.DrawStyle=DRAWSTYLE_BARBOTTOM;	
		T2.DrawStyle=DRAWSTYLE_BARTOP;
		T2a.DrawStyle=DRAWSTYLE_BARBOTTOM;	
		T3.DrawStyle=DRAWSTYLE_BARTOP;
		T3a.DrawStyle=DRAWSTYLE_BARBOTTOM;	
		sc.Input[2].Name="Length";
		sc.Input[2].SetInt(3);
		sc.Input[3].Name="Second Time Frame (minutes)";
		sc.Input[3].SetInt(15);
		sc.Input[4].Name="Third Time Frame (minutes)";	
		sc.Input[4].SetInt(60);
		sc.Input[5].Name="Bar Width";	
		sc.Input[5].SetInt(8);
		sc.AutoLoop = 0;
		sc.FreeDLL=0;

		return;
	}		
	
	
	int& li = sc.PersistVars->i1;
	int& lj = sc.PersistVars->i2;
	int as=sc.ArraySize-1;
	float& oi = sc.PersistVars->f1;
	if(sc.UpdateStartIndex==0)
	{ 
		li=lj=oi=0;	
		
	}
	
	for (int BarIndex=sc.UpdateStartIndex; BarIndex < sc.ArraySize; BarIndex++)
	{
		int hour;
		int minute;
		int second;
		sc.BaseDateTimeIn[BarIndex+1].GetTimeHMS(hour, minute, second);
		float mini1=60*hour+minute;
		sc.BaseDateTimeIn[BarIndex].GetTimeHMS(hour, minute, second);
		float mini=60*hour+minute;
		
		sc.TRIX(sc.BaseDataIn[SC_LAST], X1, BarIndex, sc.Input[2].GetInt());		
		
		if( fmod(mini1,sc.Input[3].GetInt())==0 || fmod(mini1,sc.Input[3].GetInt())<fmod(mini,sc.Input[3].GetInt()) || BarIndex==as ) 
		{	
				if(BarIndex<as) li++;			
				lc2[li]=sc.BaseDataIn[SC_LAST][BarIndex]; 	
		} 					

		sc.TRIX(lc2, l12, li, sc.Input[2].GetInt());	
		X2[BarIndex] = l12[li];
		
		if( fmod(mini1,sc.Input[4].GetInt())==0 || fmod(mini1,sc.Input[4].GetInt())<fmod(mini,sc.Input[4].GetInt()) || BarIndex==as ) 
			{	if(BarIndex<as) lj++;			lc3[lj]=sc.BaseDataIn[SC_LAST][BarIndex]; 	} 					
		sc.TRIX(lc3, l13, lj, sc.Input[2].GetInt());	
		X3[BarIndex] = l13[lj];
		
		if(X1[BarIndex]>X1[BarIndex-1]) 		{ T.DataColor[BarIndex]=T.PrimaryColor;  } else { T.DataColor[BarIndex]=Ta.PrimaryColor;  } 
		if(l12[li]>l12[li-1]) 	{ T2.DataColor[BarIndex]=T.PrimaryColor; } else { T2.DataColor[BarIndex]=Ta.PrimaryColor; } 
		if(l13[lj]>l13[lj-1]) 	{ T3.DataColor[BarIndex]=T.PrimaryColor; } else { T3.DataColor[BarIndex]=Ta.PrimaryColor; } 
		
		T[BarIndex]=80; Ta[BarIndex]=65; T2[BarIndex]=60;  T2a[BarIndex]=45; T3[BarIndex]=40;  T3a[BarIndex]=25; 
	
	}
}




/***********************************************************************/
SCSFExport scsf_WeeklyHL(SCStudyGraphRef sc)
{
if(sc.Subgraph[9][1]==sc.BaseDateTimeIn[sc.ArraySize-1].GetTime() && sc.UpdateStartIndex!=0
	&& sc.BaseDataIn[1][sc.ArraySize-1]<(sc.Subgraph[1][sc.ArraySize-1]-sc.Input[4].FloatValue) 
	&& sc.BaseDataIn[2][sc.ArraySize-1]>(sc.Subgraph[2][sc.ArraySize-1]+sc.Input[4].FloatValue) ) return;
	sc.Subgraph[9][1] = sc.BaseDateTimeIn[sc.ArraySize-1].GetTime();

	if (sc.SetDefaults)
	{
	   	sc.GraphName="Weekly HL";
	    sc.StudyDescription="Weekly Highs and Lows";
		sc.Subgraph[0].Name="LW H";
		sc.Subgraph[1].Name="LW L";
		sc.Subgraph[2].Name="W H";
		sc.Subgraph[3].Name="W L";
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.GraphRegion = 0; 
	    sc.FreeDLL=0; 
		sc.DrawZeros=0;
	    return;
	}
	
	float& High  	= sc.PersistVars->f1;	float& Low 		= sc.PersistVars->f2;
	float& LHigh  	= sc.PersistVars->f3;	float& LLow 	= sc.PersistVars->f4;
	int& iWstart	= sc.PersistVars->i1;	
	int    i,j;
		
	// DayOfWeekEnum SUNDAY = 0, MONDAY = 1, TUESDAY = 2, WEDNESDAY = 3, THURSDAY = 4, FRIDAY = 5, SATURDAY = 6
	if (sc.UpdateStartIndex == 0)
	{	iWstart=0;	High=sc.BaseDataIn[1][0]; Low=sc.BaseDataIn[2][0];}

	
	for ( i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{ 
		int p=i-1, dp, di;
		di=sc.BaseDateTimeIn[i].GetDayOfWeek(); dp=sc.BaseDateTimeIn[p].GetDayOfWeek();
		
		if( dp>di ) // yesterday was a higher day than today so its a new week
		{ 
			LHigh=High; LLow=Low; iWstart=i; 
			High=sc.BaseDataIn[1][i]; Low=sc.BaseDataIn[2][i];
		} else
		{
			if(sc.BaseDataIn[1][i]>High) High=sc.BaseDataIn[1][i];
			if(sc.BaseDataIn[2][i]<Low)  Low=sc.BaseDataIn[2][i];
		}
		
		sc.Subgraph[0][i]=LHigh; sc.Subgraph[1][i]=LLow; 		
		for(j=i; j>=iWstart; j--)
		{	sc.Subgraph[2][j]=High; sc.Subgraph[3][j]=Low; 	}	
	}
}; 



/*==========================================================================*/


/*==========================================================================*/
SCSFExport scsf_MAs(SCStudyGraphRef sc)
{
  SCSubgraphRef 	m0 = sc.Subgraph[0], m1 = sc.Subgraph[2];
  if (sc.SetDefaults)
	{
		sc.GraphName="Flexible MAs";
		sc.StudyDescription=" Flexible Mas so that you can mix up and still use the fill or transparent fill";
		m0.Name="MA 1 (Up Colour)";		m1.Name="MA 2 (Down Colour)";	
		sc.Input[1].Name="MA 1 Input Data";		sc.Input[1].SetInputDataIndex(SC_LAST);
		sc.Input[2].Name="MA 1 Type"; 			sc.Input[2].SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		sc.Input[3].Name="MA 1 Length";			sc.Input[3].SetInt(9);
		sc.Subgraph[0].DrawStyle=DRAWSTYLE_FILLTOP_TRANSPARENT;
		sc.Input[4].Name="MA 2 Input Data";		sc.Input[4].SetInputDataIndex(SC_LAST);
		sc.Input[5].Name="MA 2 Type"; 			sc.Input[5].SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		sc.Input[6].Name="MA 2 Length";			sc.Input[6].SetInt(18);
		sc.Subgraph[2].DrawStyle=DRAWSTYLE_FILLBOTTOM_TRANSPARENT;
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.DrawZeros=0;
		sc.GraphRegion=0;
		sc.FreeDLL=0; 
		return;
	}
	

	for (int i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		sc.MovingAverage(sc.BaseDataIn[sc.Input[1].GetInputDataIndex()], m0, sc.Input[2].GetMovAvgType(), i, sc.Input[3].GetInt());
		sc.MovingAverage(sc.BaseDataIn[sc.Input[4].GetInputDataIndex()], m1, sc.Input[5].GetMovAvgType(), i, sc.Input[6].GetInt());		
	}
}

/***********************************************************************/
SCSFExport scsf_Dchg(SCStudyGraphRef sc)
{
	SCSubgraphRef o0 = sc.Subgraph[0];
	
	if(sc.SetDefaults)
    {
        sc.GraphName="Daily Change";
		sc.Subgraph[0].Name = " "; sc.Subgraph[0].SecondaryColorUsed=1;
		sc.Input[2].Name="Time for final bar of day";			sc.Input[2].SetTime(0);
		sc.Input[3].Name="decimal places (7=1/4 9=1/32)";		sc.Input[3].SetInt(4);
		sc.Input[4].Name="Font Size";				sc.Input[4].SetInt(11);
		sc.Input[5].Name="Vertical Proportion";		sc.Input[5].SetFloat(0.1);
		sc.Input[6].Name="Horizontal Proportion";	sc.Input[6].SetFloat(0.1);
      	sc.GraphRegion=0;		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.UpdateAlways=0;		
		sc.FreeDLL=0;
        return;
    } 
		
	int as=sc.ArraySize-1;	float& dClose = sc.PersistVars->f1;	int& format = sc.PersistVars->i1;	
	
	if(o0[as]==0) { 
		o0[as]=8; format=sc.Input[3].GetInt();
		for(int i=sc.ArraySize; i>0; i--) {	if(sc.BaseDateTimeIn[i].GetTime()==sc.Input[2].GetTime()) { dClose=sc.Close[i]; i=0; } }
	}
	
	float gap = sc.Close[as]-dClose;
	SCString StrDChg;
	s_UseTool Tool; 
	Tool.Clear(); // reset tool structure for our next use
	float High, Low;	sc.GetMainGraphVisibleHighAndLow(High,Low);
	Tool.BeginValue = High*(sc.Input[5].GetFloat())+Low*(1.0-sc.Input[5].GetFloat());
	int horizposn = sc.IndexOfLastVisibleBar*(sc.Input[6].GetFloat())+sc.IndexOfFirstVisibleBar*(1.0-sc.Input[6].GetFloat());
	Tool.BeginDateTime = sc.BaseDateTimeIn[horizposn]; //sc.BaseDateTimeIn[sc.ArraySize-15];
	Tool.ChartNumber = sc.ChartNumber;
	Tool.DrawingType = DRAWING_TEXT;
	Tool.LineWidth = 1; Tool.FontSize=sc.Input[4].GetInt();
	Tool.Region = 0;
	Tool.AddMethod = UTAM_ADD_OR_ADJUST;
	switch(format)
	{
		case 4: StrDChg.Format("%0.4f", gap); break;
		case 0: StrDChg.Format("%0.0f", gap); break;
		case 1: StrDChg.Format("%0.1f", gap); break;
		case 3: StrDChg.Format("%0.3f", gap); break;
		case 5: StrDChg.Format("%0.5f", gap); break;
		case 6: StrDChg.Format("%0.6f", gap); break;
		case 7: {
					float gapmod=fmod(gap*4,4);
					StrDChg.Format("%0.0f  %0.0f/4", floor(gap), gapmod); 
				} break;
		case 8: {
					float gapmod=fmod(gap*16,16);
					StrDChg.Format("%0.0f  %0.0f/16", floor(gap), gapmod); 
				} break;
		case 9: {
					float gapmod=fmod(gap*32,32);
					StrDChg.Format("%0.0f  %0.0f/32", floor(gap), gapmod); 
				} break;
		case 2: StrDChg.Format("%0.2f", gap); break;
	}
	if(gap>=0) Tool.Color = sc.Subgraph[0].PrimaryColor; else Tool.Color = sc.Subgraph[0].SecondaryColor;		
	Tool.Text = StrDChg;
	Tool.LineNumber = 164;
	sc.UseTool(Tool);	
}
/*if(format==4) StrDChg.Format("%0.4f", gap); else
	if(format==0) StrDChg.Format("%0.0f", gap); else
	if(format==1) StrDChg.Format("%0.1f", gap); else
	if(format==3) StrDChg.Format("%0.3f", gap); else
	if(format==5) StrDChg.Format("%0.5f", gap); else
	if(format==6) StrDChg.Format("%0.6f", gap); else
	if(format==7) {
		float gapmod=fmod(gap*4,4);
		StrDChg.Format("%0.0f  %0.0f/4", floor(gap), gapmod); 
	} else
	if(format==8) {
		float gapmod=fmod(gap*16,16);
		StrDChg.Format("%0.0f  %0.0f/16", floor(gap), gapmod); 
	} else
	if(format==9) {
		float gapmod=fmod(gap*32,32);
		StrDChg.Format("%0.0f  %0.0f/32", floor(gap), gapmod); 
	} else
	StrDChg.Format("%0.2f", gap);
	*/
	
	
	
/***********************************************************************/
SCSFExport scsf_5MinBars(SCStudyGraphRef sc)
{
	SCSubgraphRef ud = sc.Subgraph[5];	SCSubgraphRef UD = sc.Subgraph[6];	SCSubgraphRef M0 = sc.Subgraph[3];
	if (sc.SetDefaults)
	{
	   	sc.GraphName="5MinBars";
	    sc.StudyDescription=" ";
		sc.Subgraph[0].Name="D";
		sc.Subgraph[1].Name="H";
		sc.Subgraph[2].Name="L";
		sc.Subgraph[3].Name=" ";
		sc.Subgraph[4].Name="ma21";
		sc.Subgraph[5].Name="ud";
		sc.Subgraph[6].Name="UD";
		sc.Input[4].Name="Cosmetic Offset Down";
		sc.Input[6].ValueType=FLOAT_VALUE; 
	    sc.FreeDLL=0; 
		sc.DrawZeros=0;
	    return;
	}
		
			
	float& High  	= sc.PersistVars->f1;	float& Low 		= sc.PersistVars->f2;
	int& bstartm1	= sc.PersistVars->i10;	int& bstartm2	= sc.PersistVars->i12;
	float& cosmetic_offset = sc.Input[4].FloatValue;
	int  pos, i,m0;
	
	
	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[4], MOVAVGTYPE_EXPONENTIAL, pos, 21); 
		sc.BaseDateTimeIn[pos].GetTimeHMS(i,m0,i); M0[pos]=m0;
	}
	
	
	for (pos=min(bstartm2,sc.UpdateStartIndex) ; pos < sc.ArraySize; pos++)
	{ 
		if(	fmod(M0[pos],5) == 0 )
		{ 
			if(sc.Subgraph[0][pos] != 999) { sc.Subgraph[0][pos]= 999; bstartm2=bstartm1; bstartm1=pos; } //bstartm1=pos;
			High=sc.BaseDataIn[1][pos]; Low=sc.BaseDataIn[2][pos];
			for(i=1; i<=4 && (pos+i)<sc.ArraySize; i++)
			{
				if(sc.BaseDataIn[1][pos+i]>High) 	High=sc.BaseDataIn[1][pos+i]; 
				if(sc.BaseDataIn[2][pos+i]< Low) 	Low=sc.BaseDataIn[2][pos+i];
			}	
		} 			
		sc.Subgraph[1][pos]= High+cosmetic_offset;
		sc.Subgraph[2][pos]= Low-cosmetic_offset;
	}
}


/*==========================================================================*/

SCSFExport scsf_MarkSomeBars(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "MarkBars";
		sc.StudyDescription = "Illustrate how to mark some bars";
		sc.Subgraph[0].Name = "Open (change this colour)";		sc.Subgraph[1].Name = "High";
		sc.Subgraph[2].Name = "Low";							sc.Subgraph[3].Name = "Last";	
		sc.Subgraph[4].Name = "o4";								sc.Subgraph[5].Name = "o5";
		
		sc.Input[1].Name = "Mark First Days of Each Month";		sc.Input[1].SetYesNo(false);		
		sc.Input[2].Name = "Day 1";				sc.Input[2].SetDate(0);	
		sc.Input[3].Name = "Day 2";				sc.Input[3].SetDate(0);	
		sc.Input[4].Name = "Day 3";				sc.Input[4].SetDate(0);	
		sc.Input[5].Name = "Day 4";				sc.Input[5].SetDate(0);	
			
		sc.GraphRegion = 0;  // First region		
		sc.DrawZeros = 0;  // false		
		sc.GraphDrawType = GDT_HLBAR;
		sc.DisplayAsMainPriceGraph=0;  // no just draw some bars over the others
		sc.UpdateAlways=1;
        sc.FreeDLL=0;
		return;
	}
		
	if (sc.UpdateStartIndex == 0)	{ 
		sc.Subgraph[3].PrimaryColor=sc.Subgraph[2].PrimaryColor=sc.Subgraph[1].PrimaryColor=sc.Subgraph[0].PrimaryColor; 
	}
	
	
	for(int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		bool markbar=false;
		
		if(sc.Input[1].GetYesNo()) 
		{
			int yd, imonth, pmonth;
			sc.BaseDateTimeIn[i].GetDateYMD(yd,imonth,yd);		sc.BaseDateTimeIn[i-1].GetDateYMD(yd,pmonth,yd);
			if(imonth!=pmonth) markbar=true;  // new month so mark the bar
		}
		
		if( sc.BaseDateTimeIn[i].GetDate()==sc.Input[2].GetDate() ||  sc.BaseDateTimeIn[i].GetDate()==sc.Input[3].GetDate() ||
			sc.BaseDateTimeIn[i].GetDate()==sc.Input[4].GetDate() ||  sc.BaseDateTimeIn[i].GetDate()==sc.Input[5].GetDate() )
		markbar=true;
		
		if(markbar)
		{
			sc.Subgraph[SC_OPEN][i] = sc.BaseDataIn[SC_OPEN][i];		sc.Subgraph[SC_LAST][i] = sc.BaseDataIn[SC_LAST][i];
			sc.Subgraph[SC_LOW][i] = sc.BaseDataIn[SC_LOW][i];		sc.Subgraph[SC_HIGH][i] = sc.BaseDataIn[SC_HIGH][i];
			sc.Subgraph[4][i] = 9999; // an alert condition say
		} else
		{
			sc.Subgraph[SC_OPEN][i] = sc.Subgraph[SC_HIGH][i] = sc.Subgraph[SC_LOW][i] = sc.Subgraph[SC_LAST][i] = sc.Subgraph[4][i] = 0;
		}
	}
	
}


/*==========================================================================*/
SCSFExport scsf_NMinBars(SCStudyInterfaceRef sc) {
	
	if (sc.SetDefaults)	{
	   	sc.GraphName="NMinBars";
		sc.StudyDescription="My old 5 Min Bar Study much improved and generalized by blueberrycake";
		sc.Subgraph[0].Name="H";
		sc.Subgraph[1].Name="L";
		
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_FILLRECTTOP_TRANSPARENT;
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_FILLRECTBOTTOM_TRANSPARENT;
		sc.Subgraph[0].PrimaryColor = sc.Subgraph[1].PrimaryColor = RGB(128,128,128);
		
		sc.Input[0].Name="Min Count";
		sc.Input[0].SetInt(5);
		sc.GraphRegion = 0;
		sc.FreeDLL=0; 
		sc.DrawZeros=0;
		return;
	}
		
	float High, Low;
	int  pos, i, secs, isResetBar, prevFirstBarPos;
	
	secs = sc.Input[0].GetInt() * 60;
	
	if (sc.AreTimeSpecificBars() && ((secs % sc.SecondsPerBar) == 0)) {
		prevFirstBarPos = sc.ArraySize;
		for (pos = (sc.ArraySize - 1); (pos >= 0) && (prevFirstBarPos > sc.UpdateStartIndex); pos--) {
		
			isResetBar = prevFirstBarPos == (pos + 1);
			High = (isResetBar || (sc.High[pos] > High)) ? sc.High[pos] : High;
			Low = (isResetBar || (sc.Low[pos] < Low)) ? sc.Low[pos] : Low;
			
			if ((pos == 0) || 
					((sc.BaseDateTimeIn[pos].GetTime() / secs) > (sc.BaseDateTimeIn[pos - 1].GetTime() / secs)) || 
					(sc.BaseDateTimeIn[pos].GetDate() > sc.BaseDateTimeIn[pos - 1].GetDate())) {
				
				for (i = pos; i < prevFirstBarPos; i++) {
					sc.Subgraph[0][i] = High;
					sc.Subgraph[1][i] = Low;
				}
				prevFirstBarPos = pos;
			}
		}
	}
};


/***********************************************************************/
SCSFExport scsf_sHL(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "HL";
		sc.StudyDescription = "Show Tool High and Low";	
		sc.Subgraph[0].Name = " H";	sc.Subgraph[1].Name = " L";	sc.Subgraph[0].DrawStyle=4; sc.Subgraph[1].DrawStyle=4;
		sc.Subgraph[2].Name = "  +";	sc.Subgraph[2].DrawStyle=4; 
		sc.Subgraph[3].Name = " H";	sc.Subgraph[4].Name = " L";	sc.Subgraph[3].DrawStyle=4; sc.Subgraph[4].DrawStyle=4;
		sc.ScaleRangeType=SCALE_AUTO;
		sc.GraphRegion=0;
		sc.DrawZeros=0;
		sc.UpdateAlways=1;
		sc.FreeDLL=0;
		return;
	} 	
	
	
	// Tool based filter: only show for Chart Values Tool and when it is On
	// comment out if you want to demonstrate how to show the currently selected drawing tool
	if(sc.CurrentlySelectedDrawingTool==2 && sc.CurrentlySelectedDrawingToolState==1)
	{
		int as=sc.ArraySize-1;
		sc.Subgraph[0][as]=sc.BaseDataIn[1][sc.ActiveToolIndex]; 
		sc.Subgraph[1][as]=sc.BaseDataIn[2][sc.ActiveToolIndex]; 
		sc.Subgraph[2][as]=sc.ActiveToolYValue;
		sc.Subgraph[3][as]=sc.BaseDataIn[1][as]; 
		sc.Subgraph[4][as]=sc.BaseDataIn[2][as]; 
	
		SCString StrInput; char ARout[40]="";
		s_UseTool Tool;
		Tool.Clear(); // reset tool structure for our next use
		float High, Low;	sc.GetMainGraphVisibleHighAndLow(High,Low);
		Tool.BeginValue = sc.ActiveToolYValue-((High-Low)/50);	
		Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ActiveToolIndex-6]; ;
		Tool.ChartNumber = sc.ChartNumber;
		Tool.DrawingType = DRAWING_TEXT;
		Tool.LineWidth = 1; Tool.FontSize=11;
		Tool.Region = 0;
		Tool.AddMethod = UTAM_ADD_OR_ADJUST;
		Tool.Color = RGB(28,28,28);		
		char output[60]="";  //int temp;
		//temp=(int)(sc.BaseDataIn[1][sc.ActiveToolIndex]); StrInput.Format("%d\n", temp); strcpy(ARout,StrInput);
		//temp=(int)(sc.BaseDataIn[1][as]); StrInput.Format("%d \n", temp); strcat(ARout,StrInput);
		//temp=(int)(sc.BaseDataIn[2][sc.ActiveToolIndex]); StrInput.Format("%d\n", temp); strcat(ARout,StrInput);
		//temp=(int)(sc.BaseDataIn[2][as]); StrInput.Format("%d \n", temp); strcat(ARout,StrInput); 
		//strcpy(output,ARout); 	
		// with improved coding to display values ... thanks to blueberrycake
		strcpy(ARout,sc.FormatGraphValue((sc.High[sc.ActiveToolIndex]), sc.BaseGraphValueFormat));
		strcat(ARout, "\n");
		strcat(ARout,sc.FormatGraphValue((sc.Low[sc.ActiveToolIndex]), sc.BaseGraphValueFormat)); 
		strcat(ARout, "\n");
		// Show the number and state of the currently selected drawing tool
		// uncomment the 2 lines below to demonstrate and comment out the tool based filter before the brackets above
		//StrInput.Format("%d \n", sc.CurrentlySelectedDrawingTool); strcat(ARout,StrInput); 
		//StrInput.Format("%d ", sc.CurrentlySelectedDrawingToolState); strcat(ARout,StrInput); 
		
		Tool.LineNumber = 126;
		Tool.Text=ARout;
		sc.UseTool(Tool);
	} 
	//else sc.DeleteLineOrText(0,TOOL_TEXT,126); // uncomment if you don't want the high and low to remain after you unselect the CV tool
}



/***********************************************************************/
SCSFExport scsf_StatusFloat(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "Status Bar";
		sc.Input[3].Name="Horizontal Position from right";		sc.Input[3].SetInt(50);
		sc.Input[4].Name="Vertical Position (percentage of range)";		sc.Input[4].SetFloat(5);
		sc.Input[5].Name="Font Size";					sc.Input[5].SetInt(11);
		sc.ScaleRangeType=SCALE_SAMEASREGION;
		sc.GraphRegion=0;
		sc.UpdateAlways=1;
		sc.FreeDLL=0;
		return;
	} 	
		
	int& Command =  sc.PersistVars->i1;		int& existingorders = sc.PersistVars->i5;	int& period = sc.PersistVars->i6;	
	float& entryswing = sc.PersistVars->f3;		float& stoptriggered = sc.PersistVars->f4;
	int& CloseTWSOnce =  sc.PersistVars->i13;	int& ResetWithLivePosnOrders = sc.PersistVars->i14;	
	int& temp = sc.PersistVars->i15;
	SCString StrRemainingTime, StrTime;
	int j, Hour, Minute, Second;	int as=sc.ArraySize-1;
	
	SCDateTime BarTime=sc.SecondsPerBar;
	SCDateTime RemainingTime=sc.BaseDateTimeIn[as].GetTime()+sc.SecondsPerBar-sc.CurrentSystemDateTime.GetTime();
	if(sc.IsReplayRunning()) RemainingTime=sc.BaseDateTimeIn[as].GetTime()+sc.SecondsPerBar-sc.LatestDateTimeForLastBar.GetTime();
	
		
	int minbar; sc.CurrentSystemDateTime.GetTimeHMS(j,minbar,j); int tofive=4-fmod(float(minbar),5.0f);
	if(sc.IsReplayRunning())
		{ sc.LatestDateTimeForLastBar.GetTimeHMS(j,minbar,j);	tofive=4-fmod(float(minbar),5.0f);}
		
	s_UseTool Tool; 
	Tool.Clear(); // reset tool structure for our next use
	float High, Low;	sc.GetMainGraphVisibleHighAndLow(High,Low);
	float Position=sc.Input[4].GetFloat()/100;
	if(sc.BaseDataIn[3][sc.IndexOfLastVisibleBar]<((High+Low)/2)) Tool.BeginValue = High-((High-Low)*Position); else Tool.BeginValue = Low+(3*(High-Low)*Position);	
	Tool.BeginDateTime = sc.BaseDateTimeIn[sc.IndexOfLastVisibleBar-sc.Input[3].IntValue]; //sc.BaseDateTimeIn[sc.ArraySize-15];
	Tool.ChartNumber = sc.ChartNumber;
	Tool.DrawingType = DRAWING_TEXT;
	Tool.LineWidth = 1; Tool.FontSize=sc.Input[5].GetInt();
	Tool.Region = 0;
	Tool.AddMethod = UTAM_ADD_OR_ADJUST;
	Tool.Color = RGB(28,28,28);
	
	char output[80]="";	
	
	
	
	sc.CurrentSystemDateTime.GetTimeHMS(Hour,Minute,Second);
	if(Hour>12) Hour=Hour-12;
	if(Minute>=10 && Second>=10) StrTime.Format("%d:%d:%d", Hour, Minute, Second); else
	if(Minute>=10) StrTime.Format("%d:%d:0%d", Hour, Minute, Second); else
	if(Second>=10) StrTime.Format("%d:0%d:%d", Hour, Minute, Second); else
					StrTime.Format("%d:0%d:0%d", Hour, Minute, Second); 
	
	if(RemainingTime<=0 && RemainingTime>=-BarTime) { RemainingTime=RemainingTime+sc.SecondsPerBar; Tool.Color = RGB(255,0,0); } else
	if(RemainingTime>BarTime || RemainingTime<-BarTime)  { RemainingTime=0; }
	Hour=(int) (RemainingTime/3600);
	Minute=((int) (RemainingTime/60))-(Hour*60);
	Second= RemainingTime-(Hour*3600)-(Minute*60);
	if(Second>=10) 	StrRemainingTime.Format("    %d:%d", Minute, Second);
	  else {
				StrRemainingTime.Format("    %d:0%d", Minute, Second);	
			}
	
	
	strcpy(output,sc.FormatGraphValue(sc.ActiveToolYValue, sc.BaseGraphValueFormat)); strcat(output, "  ");
	strcat(output,StrTime); strcat(output, "  ");
			
	strcat(output, "O:");strcat(output,sc.FormatGraphValue(sc.Open[sc.ActiveToolIndex], sc.BaseGraphValueFormat)); strcat(output, "  ");
	strcat(output, "H:");strcat(output,sc.FormatGraphValue(sc.High[sc.ActiveToolIndex], sc.BaseGraphValueFormat)); strcat(output, "  ");
	strcat(output, "L:");strcat(output,sc.FormatGraphValue(sc.Low[sc.ActiveToolIndex], sc.BaseGraphValueFormat));  strcat(output, "  ");
	strcat(output, "C:");strcat(output,sc.FormatGraphValue(sc.Close[sc.ActiveToolIndex], sc.BaseGraphValueFormat));strcat(output, "  ");
	strcat(output,StrRemainingTime); 
	
	Tool.LineNumber = 124;
	Tool.Text=output;
	sc.UseTool(Tool);

}



/***********************************************************************/
SCSFExport scsf_Connection(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "Connection Status";
		sc.StudyDescription="Options for Showing Connection Status on Chart ";
		sc.Subgraph[0].Name="MA, top of box";			sc.Subgraph[0].DrawStyle = DRAWSTYLE_LINE;	
		sc.Subgraph[1].Name="bottom of box & connected colour";		sc.Subgraph[1].DrawStyle = 4;	
		sc.Subgraph[2].Name="disconnected colour";		sc.Subgraph[2].DrawStyle = 4;
		sc.Subgraph[3].Name="Alarm (one instead of zero) & alarm alternate colour";	sc.Subgraph[3].DrawStyle = 4;
		sc.Subgraph[4].Name="connecting colour";		sc.Subgraph[4].DrawStyle = 4;
		sc.Subgraph[5].Name="reconnecting colour";		sc.Subgraph[5].DrawStyle = 4;
		sc.Subgraph[6].Name="connection lost colour";	sc.Subgraph[6].DrawStyle = 4;
		sc.Subgraph[7].Name="disconnecting colour";		sc.Subgraph[7].DrawStyle = 4;
		
	/*	enum ServerConnectionStateEnum
		{ DISCONNECTED
		, CONNECTING
		, RECONNECTING
		, CONNECTED
		, CONNECTION_LOST
		, DISCONNECTING
	*/
		
		sc.Input[2].Name="Use box instead of ma";					sc.Input[2].SetYesNo(false);
		sc.Input[3].Name="Move box away from price (vs stay at top)";	sc.Input[3].SetYesNo(true);
		sc.Input[4].Name="Flash alarm colours";						sc.Input[4].SetYesNo(true);
		sc.Input[5].Name="Update Always? (higher cpu)";				sc.Input[5].SetYesNo(false);
		sc.Input[6].Name="----";									sc.Input[6].SetYesNo(false);		
		sc.Input[7].Name="Horizontal Position from right";			sc.Input[7].SetInt(15);	
		sc.Input[8].Name="Horizontal width (bars)";					sc.Input[8].SetInt(5);
		sc.Input[9].Name="Vertical Position (% of range)";			sc.Input[9].SetFloat(5);
		sc.Input[10].Name="Vertical Depth (% of range)";			sc.Input[10].SetFloat(5);
		sc.Input[12].Name="MA Type";								sc.Input[12].SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		sc.Input[13].Name="MA Length";								sc.Input[13].SetInt(21);
		
		sc.ScaleRangeType=SCALE_SAMEASREGION;
		sc.GraphRegion=0;
		sc.DrawZeros=0;
		sc.UpdateAlways=0;
		sc.FreeDLL=0;
		return;
	} 
	
	int as=sc.ArraySize-1;
	// evaluate color based on status
	// for any state except connected subgraph[3] = SG4 in list will be non zero so alarm can be set
	int& color =  sc.PersistVars->i1;
	if(sc.ServerConnectionState == SCS_CONNECTED) 		{ color=sc.Subgraph[1].PrimaryColor; sc.Subgraph[3][as]=0; } else
	if(sc.ServerConnectionState == SCS_DISCONNECTED) 	{ color=sc.Subgraph[2].PrimaryColor; sc.Subgraph[3][as]=1; } else
	if(sc.ServerConnectionState == SCS_CONNECTING) {
		if(color==sc.Subgraph[4].PrimaryColor) sc.Subgraph[0].PrimaryColor=sc.Subgraph[3].PrimaryColor; 
			else { color=sc.Subgraph[4].PrimaryColor;  sc.Subgraph[3][as]=2; } 
	} else
	if(sc.ServerConnectionState == SCS_RECONNECTING) {
		if(color==sc.Subgraph[5].PrimaryColor) color=sc.Subgraph[3].PrimaryColor; 
			else { color=sc.Subgraph[5].PrimaryColor;  sc.Subgraph[3][as]=3; }
	} else
	if(sc.ServerConnectionState == SCS_CONNECTION_LOST) {
		if(color==sc.Subgraph[6].PrimaryColor) color=sc.Subgraph[3].PrimaryColor; 
			else { color=sc.Subgraph[6].PrimaryColor;  sc.Subgraph[3][as]=4; }
	} else
	if(sc.ServerConnectionState == SCS_DISCONNECTING) {
		if(color==sc.Subgraph[7].PrimaryColor) color=sc.Subgraph[3].PrimaryColor; 
			else { color=sc.Subgraph[7].PrimaryColor;  sc.Subgraph[3][as]=5; }
	}

		
	// first do the ma version
	if(!sc.Input[2].GetYesNo()) {
		if (sc.UpdateStartIndex == 0) {	
			if(sc.Input[5].GetYesNo()) sc.UpdateAlways=1; else sc.UpdateAlways=0;
		}
		sc.Subgraph[0].PrimaryColor=color;
		for (int i=0; i < sc.ArraySize; i++)
		{
				sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], sc.Input[12].GetMovAvgType(), i, sc.Input[13].GetInt());
		}
	// then do the box box on chart version
	} else {
		if (sc.UpdateStartIndex == 0) {	
			if(sc.Input[5].GetYesNo()) sc.UpdateAlways=1; else sc.UpdateAlways=0;
		}
		
		s_UseTool Tool; 
		Tool.Clear();
		float High, Low;	sc.GetMainGraphVisibleHighAndLow(High,Low);
		if(sc.BaseDataIn[3][sc.IndexOfLastVisibleBar]>((High+Low)/2) && sc.Input[3].GetYesNo())
			{ Tool.BeginValue = Low+(3*(High-Low)*sc.Input[9].GetFloat()/100); Tool.EndValue = Tool.BeginValue+((High-Low)*sc.Input[10].GetFloat()/100); }	else
			{ Tool.BeginValue = High-((High-Low)*sc.Input[9].GetFloat()/100);  Tool.EndValue = Tool.BeginValue-((High-Low)*sc.Input[10].GetFloat()/100); } 
		
		Tool.BeginDateTime = sc.BaseDateTimeIn[sc.IndexOfLastVisibleBar-sc.Input[7].IntValue];
		Tool.EndDateTime = sc.BaseDateTimeIn[sc.IndexOfLastVisibleBar-sc.Input[7].IntValue-sc.Input[8].IntValue];
		Tool.ChartNumber = sc.ChartNumber;	
		Tool.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
		Tool.LineWidth = 0; 
		Tool.Region = 0;
		Tool.LineNumber = 134;
		if(sc.UpdateStartIndex == 0 || Tool.Color != color)
		{
			Tool.SecondaryColor = Tool.Color = color;	
			sc.DeleteACSChartDrawing(Tool.ChartNumber,TOOL_DELETE_CHARTDRAWING,Tool.LineNumber);
		} else Tool.AddMethod = UTAM_ADD_OR_ADJUST;
		Tool.LineNumber = 134;
		sc.UseTool(Tool);		
	}
	
}







/* ********************************************************************** /
SCSFExport scsf_VolBPrice(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "VolByPrice";
		sc.StudyDescription="Uses Fib Tool 2 to define Volume by Price DateTime range";
		
		// I use the two point retrace as the input with all the fibs between 0 and 100 deleted ... but the trendline (type 1)
		// might suit you better.  The types are listed below.  You put ONE ONLY example of the type on the chart
		// and the function reads its start and end and saves that to the file StartEnd.txt in the directory below.
		// Then it invokes InputTimes.ahk to put those points into the SierraChart Volume By Price function
		// which must be the top function in the studies to graph (with this function somewhere below it)
		sc.TextInputName="Directory to save files";							sc.TextInput="C:\\SierraChart\\";
		sc.Input[2].Name="Autohotkey Installed (otherwise .exe version used)";		sc.Input[2].SetYesNo(true);		
		sc.Input[7].Name="InterStuff Gap (ms)";						sc.Input[7].SetInt(150);	
		sc.Input[8].Name="Send Delay";								sc.Input[8].SetInt(5);
		sc.Input[9].Name="Click Delay";								sc.Input[9].SetInt(5);
		// the input data file and the ahk script will be in the same directory ....
		/*
		enum DrawingTypeEnum
		{ DRAWING_UNKNOWN = 0
		, DRAWING_TRENDLINE = 1
		, DRAWING_EXTENDINGTRENDLINE = 2
		, DRAWING_HORIZONTALLINE = 3
		, DRAWING_VERTICALLINE = 4
		, DRAWING_ARROW = 5
		, DRAWING_TEXT = 6
		, DRAWING_CHARTCALCULATOR = 7
		, DRAWING_TWOPOINT_RETRACE_EXTEN = 8
		, DRAWING_UNUSED = 9
		 // old fan drawing type
		, DRAWING_THREEPOINT_RETRACE_EXTEN = 11

		, DRAWING_RECTANGLEHIGHLIGHT  = 12
		, DRAWING_ELLIPSEHIGHLIGHT = 13
		, DRAWING_FAN_GANN = 14
		, DRAWING_PITCHFORK = 15
		, DRAWING_FLOWELLIPSEHIGHLIGHT = 16

		, DRAWING_WORKING_ORDER = 17
		, DRAWING_SYMBOL_POSITION = 18

		, DRAWING_CYCLE = 19
		, DRAWING_FIBTIMEZONES = 20
		, DRAWING_GANNGRID = 21

		, DRAWING_TWOPOINT_RETRACE_EXTEN2 = 22
		, DRAWING_THREEPOINT_RETRACE_EXTEN2 = 23

		, DRAWING_FILLED_ORDERS = 24
		, DRAWING_ENTRYEXIT_CONNECTLINE = 25

		, DRAWING_RECTANGLE_EXT_HIGHLIGHT = 26

		, DRAWING_FAN_FIBONACCI = 27

		, DRAWING_PARALLEL_TRENDLINES = 28
		, DRAWING_PARALLEL_EXTENDINGTRENDLINES = 29
		};
		* /
		sc.ScaleRangeType=SCALE_SAMEASREGION;
		sc.GraphRegion=0;
		sc.DrawZeros=0;
		sc.UpdateAlways=0;
		sc.FreeDLL=0;
		return;
	} 
	
	int& Y1 =  sc.PersistVars->i1;	int& M1 =  sc.PersistVars->i2;	int& D1 =  sc.PersistVars->i3;
	int& Y2 =  sc.PersistVars->i4;	int& M2 =  sc.PersistVars->i5;	int& D2 =  sc.PersistVars->i6;
	int& h1 =  sc.PersistVars->i7;	int& m1 =  sc.PersistVars->i8;	int& s1 =  sc.PersistVars->i9;
	int& h2 =  sc.PersistVars->i10;	int& m2 =  sc.PersistVars->i11;	int& s2 =  sc.PersistVars->i12;	
	int& counter =  sc.PersistVars->i13;	int& checksum =  sc.PersistVars->i14;
	
	s_UseTool ChartDrawing;
	
	if ( sc.UpdateStartIndex == 0 &&
			sc.GetChartDrawing(0, DRAWING_RETRACEMENT, ChartDrawing, -1))// <<< if you want a different drawing type change here
	{
		if(ChartDrawing.EndDateTime > ChartDrawing.BeginDateTime) {
			ChartDrawing.BeginDateTime.GetDateYMD(Y1,M1,D1);		ChartDrawing.BeginDateTime.GetTimeHMS(h1,m1,s1);
			ChartDrawing.EndDateTime.GetDateYMD(Y2,M2,D2);			ChartDrawing.EndDateTime.GetTimeHMS(h2,m2,s2);
		} else {
			ChartDrawing.EndDateTime.GetDateYMD(Y1,M1,D1);			ChartDrawing.EndDateTime.GetTimeHMS(h1,m1,s1);
			ChartDrawing.BeginDateTime.GetDateYMD(Y2,M2,D2);		ChartDrawing.BeginDateTime.GetTimeHMS(h2,m2,s2);		
		}
		int tempchk = Y1+Y2+M1+M2+D1+D2+3600*(h1+h2)+60*(m1+m2)+s1+s2;
		if(checksum != tempchk) { counter=1; checksum=tempchk; } else counter=0; // no change so nothing for ahk to do
		char output[100]="";
		strcpy(output,sc.TextInput.GetChars()); 		strcat(output,"VBPStartEnd.txt"); 
		FILE * pFile;  
		pFile = fopen (output,"w");
		if (pFile!=NULL) {
			fprintf (pFile, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\r\n",counter,M1,D1,Y1,h1,m1,s1,M2,D2,Y2,h2,m2,s2);
			fclose (pFile); 
		}
		char tmp[40]=""; strcpy(tmp,"start ");		strcat(tmp,sc.TextInput.GetChars());
		if(sc.Input[2].GetYesNo()) strcat(tmp,"VBPInputTimes.ahk"); else strcat(tmp,"VBPInputTimes.exe");
		//snprintf(output, sizeof(output), "%s%s", tmp," ");
		snprintf(output, sizeof(output), "%s%s%d%s%d%s%d", tmp," ",sc.Input[7].GetInt()," ",sc.Input[8].GetInt()," ",sc.Input[9].GetInt());
		/*strcpy(output,"start ");		strcat(output,sc.TextInput.GetChars()); 
		strcat(output," "); strcat(output,atoi(sc.Input[7].GetInt())); 
		strcat(output," "); strcat(output,atoi(sc.Input[8].GetInt())); 
		strcat(output," "); strcat(output,atoi(sc.Input[9].GetInt())); * /
		system(output);
	} else 
	
	
	if ( sc.UpdateStartIndex == 0 &&
		!sc.GetChartDrawing(0, DRAWING_RETRACEMENT, ChartDrawing, -1))
	{
		counter=0;
		char output[80]="";
		strcpy(output,sc.TextInput.GetChars()); 
		strcat(output,"VBPStartEnd.txt"); 
		FILE * pFile;  
		pFile = fopen (output,"w");
		if (pFile!=NULL) {
			fprintf (pFile, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\r\n",counter,0,0,0,0,0,0,0,0,0,0,0,0);
			fclose (pFile); 
		}
	}
}

*/


/***********************************************************************/
SCSFExport scsf_ScTC(SCStudyInterfaceRef sc)
{
  if (sc.SetDefaults)
  {
    sc.GraphName="ScTC";
    sc.StudyDescription="Schaff Trend Cycle";
	sc.Subgraph[0].Name="STC";
	sc.Subgraph[5].Name="macd";
	sc.Subgraph[6].Name="stoch macd";
	sc.Subgraph[7].Name="stoch stoch";
	sc.Subgraph[1].Name="Upper Line";
	sc.Subgraph[2].Name="Lower Line";
	
	sc.Input[3].Name="Fast MA Length";				sc.Input[3].SetInt(23);
	sc.Input[4].Name="Slow MA Length";				sc.Input[4].SetInt(50);
	sc.Input[5].Name="Stoch(s) Length";				sc.Input[5].SetInt(10);
	sc.Input[6].Name="Stoch ema Length";			sc.Input[6].SetFloat(0.5);
	sc.Input[8].Name="Upper Line Level";			sc.Input[8].SetInt(70);
	sc.Input[9].Name="Lower Line Level";			sc.Input[9].SetInt(30);	
	sc.DrawZeros=1;
	sc.FreeDLL=0; 
	return;
  }

	int& L = sc.Input[5].IntValue;
	float& factor = sc.Input[6].FloatValue;
	int j; double h, l, range;
	
	for (int i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		sc.MACD(sc.BaseData[SC_LAST], sc.Subgraph[5], i, sc.Input[3].GetInt(), sc.Input[4].GetInt(), 1, MOVAVGTYPE_EXPONENTIAL);
		h=-999999, l=9999999;
		for(j=0;j<L;j++)
			{if(h<sc.Subgraph[5][i-j]) h=sc.Subgraph[5][i-j];
			 if(l>sc.Subgraph[5][i-j]) l=sc.Subgraph[5][i-j];
			}
		range=(h-l);
		if(range>0) sc.Subgraph[8][i]=100*(sc.Subgraph[5][i]-l)/range; else sc.Subgraph[8][i]=sc.Subgraph[8][i-1];
		sc.Subgraph[6][i]= sc.Subgraph[6][i-1] + factor*(sc.Subgraph[8][i] - sc.Subgraph[6][i-1]); 
				
		
		h=-999999, l=9999999;
		for(j=0;j<L;j++)
			{if(h<sc.Subgraph[6][i-j]) h=sc.Subgraph[6][i-j];
			 if(l>sc.Subgraph[6][i-j]) l=sc.Subgraph[6][i-j];
			}
		range=(h-l);
		if(range>0) sc.Subgraph[9][i]=100*(sc.Subgraph[6][i]-l)/range; else sc.Subgraph[9][i]=sc.Subgraph[9][i-1];
		sc.Subgraph[7][i]=sc.Subgraph[7][i-1] + factor*(sc.Subgraph[9][i] - sc.Subgraph[7][i-1]);
		
	
		sc.Subgraph[0][i]=sc.Subgraph[7][i];
		sc.Subgraph[1][i]=sc.Input[8].GetInt();
		sc.Subgraph[2][i]=sc.Input[9].GetInt();
	}
};


/***********************************************************************/
SCSFExport scsf_KiwiVolume(SCStudyInterfaceRef sc)
{
  // from the old kiwi7 just hacked around to get the vol projection working
  if (sc.SetDefaults)
  {
   	sc.GraphName="Kiwi's Volume Study";
	sc.Subgraph[0].Name="Volume";
	sc.Subgraph[1].Name=" ";
	sc.Subgraph[2].Name="Projected Last Bar Volume";
	sc.Subgraph[3].Name="%";  
	sc.Subgraph[5].Name="Cumulative Up Volume - Down Volume";
	sc.Subgraph[6].Name="Cumulative Up Volume";
	sc.Subgraph[7].Name="Cumulative Down Volume";
	
	sc.Subgraph[0].DrawStyle=DRAWSTYLE_BAR;
    sc.Subgraph[1].DrawStyle=DRAWSTYLE_HIDDEN;
    sc.Subgraph[2].DrawStyle = DRAWSTYLE_BAR;
	sc.Subgraph[3].DrawStyle=DRAWSTYLE_IGNORE;
	sc.Subgraph[0].SecondaryColorUsed = 1;
	sc.Subgraph[2].SecondaryColorUsed = 1;
		    	
	sc.Input[3].Name="Max Size of Vol Bar ";	
	sc.Input[3].SetFloat(9000000);
	sc.Input[4].Name="Use only two colours";   
	sc.Input[4].ValueType=YESNO_VALUE; 
    
	return;
  }
  
	int	pos, dirn;
	float vol;  
	
	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
        vol= fabs(sc.BaseDataIn[4][pos]);
		sc.Subgraph[0][pos]=min(vol,sc.Input[3].FloatValue);
		
		if(sc.BaseDataIn[3][pos]>sc.BaseDataIn[0][pos]) dirn=1; else
        if(sc.BaseDataIn[3][pos]<sc.BaseDataIn[0][pos]) dirn=-1; else dirn=0;
        if(dirn==1 ){sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].PrimaryColor;} else
        if(dirn==-1){sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].SecondaryColor;} else
		if(!sc.Input[4].BooleanValue) {sc.Subgraph[0].DataColor[pos] = sc.Subgraph[1].PrimaryColor;} else
			{sc.Subgraph[0].DataColor[pos] = sc.Subgraph[0].DataColor[pos-1];};
		
		if(sc.BaseDateTimeIn[pos-1].GetDate()!=sc.BaseDateTimeIn[pos].GetDate())
			{ sc.Subgraph[5][pos-1]=0; sc.Subgraph[6][pos-1]=0; sc.Subgraph[7][pos-1]=0;};
		if(dirn==1 ){sc.Subgraph[6][pos]=sc.Subgraph[6][pos-1]+vol; sc.Subgraph[7][pos]=sc.Subgraph[7][pos-1];} else
        if(dirn==-1){sc.Subgraph[6][pos]=sc.Subgraph[6][pos-1]; sc.Subgraph[7][pos]=sc.Subgraph[7][pos-1]+vol;} else
					{sc.Subgraph[6][pos]=sc.Subgraph[6][pos-1]; sc.Subgraph[7][pos]=sc.Subgraph[7][pos-1];}
		sc.Subgraph[5][pos]=sc.Subgraph[5][pos-1]+dirn*vol;
	}

	pos=sc.ArraySize-1;
	float barout;
	float timedelta=float(sc.LatestDateTimeForLastBar.GetTime()-sc.BaseDateTimeIn[pos].GetTime())/sc.SecondsPerBar;
	if(fabs(sc.BaseDataIn[5][pos])>1)	barout=sc.Subgraph[0][pos]/timedelta;
	// stop wildly high values in the first few seconds of a new bar
	if(timedelta<0.2) { 
		float recentvolumes=max(max(max(sc.BaseDataIn[4][pos],sc.BaseDataIn[4][pos-1]),sc.BaseDataIn[4][pos-2]),sc.BaseDataIn[4][pos-3]);
		sc.Subgraph[2][pos] = min(barout,recentvolumes);
	} else
		sc.Subgraph[2][pos]=barout;

	sc.Subgraph[3][pos]=sc.Subgraph[2][pos]/sc.Subgraph[0][pos-1];
	if(sc.Subgraph[2][pos]>sc.Input[3].FloatValue) 
	{
		sc.Subgraph[2][pos]=sc.Input[3].FloatValue; 
		sc.Subgraph[2].DataColor[pos] = sc.Subgraph[2].SecondaryColor;
	} 
	else
		sc.Subgraph[2].DataColor[pos] = sc.Subgraph[2].PrimaryColor;

    sc.Subgraph[2][pos-1]=0; 
    sc.Subgraph[1][pos]=0.0000000001;
};


/***********************************************************************/
SCSFExport scsf_sALF(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "ALF";
		sc.StudyDescription = "EasyLanguage Code for the Adaptive Laguerre Filter";	
		sc.Subgraph[0].Name = "Laguerre";	
		sc.Subgraph[1].Name = "L0";			sc.Subgraph[1].DrawStyle=5;
		sc.Subgraph[2].Name = "L1";			sc.Subgraph[2].DrawStyle=5; 
		sc.Subgraph[3].Name = "L2";			sc.Subgraph[3].DrawStyle=5;	
		sc.Subgraph[4].Name = "L3";			sc.Subgraph[4].DrawStyle=5;
		sc.Subgraph[5].Name = "InSort";		sc.Subgraph[5].DrawStyle=5;
		sc.Subgraph[6].Name = "OutSort";	sc.Subgraph[6].DrawStyle=5;		
		sc.Input[3].Name="Length";			sc.Input[3].SetInt(20);		 
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.GraphRegion=0;
		sc.DrawZeros=0;
		
		sc.FreeDLL=0;
		return;
	} 	
	
	SCSubgraphRef Filt = sc.Subgraph[0];
	SCSubgraphRef L0 = sc.Subgraph[1];
	SCSubgraphRef L1 = sc.Subgraph[2];
	SCSubgraphRef L2 = sc.Subgraph[3];
	SCSubgraphRef L3 = sc.Subgraph[4];
	SCSubgraphRef iS = sc.Subgraph[5];
	SCSubgraphRef oS = sc.Subgraph[6];
	SCSubgraphRef Diff = sc.Subgraph[7];
	int& Length = sc.Input[3].IntValue;
	double HH,	LL, alpha;
	
	
	for (int i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		int as=sc.ArraySize-1;
		double Price = (sc.High[i]+sc.Low[i])/2;
		HH = LL = Diff[i] = fabs( Price - Filt[i-1] );
		for ( int count = 0; count<Length; count++ ) {
			if(Diff[i-count] > HH) HH = Diff[i-count];
			if(Diff[i-count] < LL) LL = Diff[i-count];
		}
		
		iS[i]=((Diff[i] - LL) / (HH - LL));
		if ( i > 2*Length && (HH - LL) != 0 ) { // alpha = Median(, 5);
			int j; double temp;
			for( j=0; j<=4; j++ ) { oS[as-j]=iS[i-j];} // fill array
			for( j=3; j>=0; j-- ) { if(oS[as-j]<oS[as-j-1]) {temp=oS[as-j];oS[as-j]=oS[as-j-1];oS[as-j-1]=temp;} } // highest to 4
			for( j=3; j>=1; j-- ) { if(oS[as-j]<oS[as-j-1]) {temp=oS[as-j];oS[as-j]=oS[as-j-1];oS[as-j-1]=temp;} } // next to 3
			for( j=3; j>=2; j-- ) { if(oS[as-j]<oS[as-j-1]) {temp=oS[as-j];oS[as-j]=oS[as-j-1];oS[as-j-1]=temp;} } // next to 2
			alpha=oS[as-2];
		}

		L0[i] = alpha*Price + (1 - alpha)*L0[i-1];
		L1[i] = -(1 - alpha)*L0[i] + L0[i-1] + (1 - alpha)*L1[i-1];
		L2[i] = -(1 - alpha)*L1[i] + L1[i-1] + (1 - alpha)*L2[i-1];
		L3[i] = -(1 - alpha)*L2[i] + L2[i-1] + (1 - alpha)*L3[i-1];

		Filt[i] = (L0[i] + 2*L1[i] + 2*L2[i] + L3[i]) / 6;	
	} 
}


/***********************************************************************/
SCSFExport scsf_J_TPO(SCStudyInterfaceRef sc)
{
  if (sc.SetDefaults)
    {
        sc.GraphName="J_TPO";
        sc.StudyDescription="";
		sc.Subgraph[0].Name = "TPO";
		sc.Subgraph[1].Name = "High";
		sc.Subgraph[2].Name = "Low";
		sc.Input[3].Name="Length";		sc.Input[3].SetFloat(10);
		sc.Input[4].Name="High";		sc.Input[4].SetFloat(0.85);
		sc.Input[5].Name="Low";			sc.Input[5].SetFloat(-0.85);
		sc.DrawZeros=1;
		sc.FreeDLL=0;
        return;
    }
	int& lasti = sc.PersistVars->i4;		int& Len = sc.PersistVars->i5; 
	float& normalization = sc.PersistVars->f4; float& HalfLen = sc.PersistVars->f5;	float& Len1 = sc.PersistVars->f6; 
	
	double posn, accum, lowestclose;
	float temp;
	int j,klc, m, n, p, loop;
	SCSubgraphRef arr0 = sc.Subgraph[5]; SCSubgraphRef arr1 = sc.Subgraph[6]; 
	SCSubgraphRef arr2 = sc.Subgraph[7]; SCSubgraphRef arr3 = sc.Subgraph[8]; 
	
	if(sc.UpdateStartIndex == 0) {
		if(sc.Input[3].FloatValue<3) sc.Input[3].FloatValue=3;		Len=sc.Input[3].FloatValue;  		Len1=sc.Input[3].FloatValue-1;
		arr0[1]= sc.BaseDataIn[3][1];
		float z = Len;  	normalization=12/(z*(z-1)*(z+1));		 HalfLen=(Len + 1) * 0.5;
	}
	
	int start=sc.UpdateStartIndex;
	if(sc.GetBarHasClosedStatus()==BHCS_BAR_HAS_CLOSED) start=0;
	
	for(int i=start; i<sc.ArraySize; i++)
	{
		if(i!=lasti) { for(m=2; m<=Len; m++) {arr0[m-1]=arr0[m];} arr0[Len]=sc.BaseDataIn[3][i]; } // shuffle em all along 1 and put in the latest close
		for(m=1; m<=Len; m++) {arr2[m]=m; arr3[m]=m; arr1[m]=arr0[m];}  // arrays 2 & 3 get their number, array 1 gets array 0's closes
		lasti=i;
		// seems to have ordered the closes from high to low in array 1 ... and put their original position numbers in array 2
		for(m=1; m<=(Len-1); m++)
		{
			lowestclose=arr1[m];  klc=m;  j=m+1;
			for(j=m+1; j<=Len; j++) { if (arr1[j] < lowestclose) {lowestclose=arr1[j]; klc=j;} }  // lowestclose = lowest close, klc = posn of lowestclose
			temp=arr1[m]; arr1[m]=arr1[klc]; arr1[klc]=temp;
			temp=arr2[m]; arr2[m]=arr2[klc]; arr2[klc]=temp;
		} 
		// arr3[1..Len] is nominally 1..m, but this here adjusts for ties.
		m=1; loop=-Len;
		while(m < Len)
		{  // Search for repeated values. 
			j=m+1; p=1; posn=arr3[m];
			while(p!=0 && loop<Len)
			{
			   if (arr1[m]!=arr1[j])
			   {
				  if ((j - m) > 1)
				  { // a streak of repeated values was found and so replace arr3[] for those with its average
					 posn=posn/(j - m);
					 for(n=m; n<=(j-1); n++) arr3[n]=posn;
				  }
				  p=0;
				}
				else
				{ posn=posn + arr3[j]; j++;}
				loop++;
			}
			m=j;
		}
		for(m=1,accum=0; m<=Len; m++) { accum = accum + (arr3[m]-HalfLen) * (arr2[m]-HalfLen); }
		sc.Subgraph[0][i] = normalization * accum;
		sc.Subgraph[1][i]= sc.Input[4].FloatValue;		sc.Subgraph[2][i]= sc.Input[5].FloatValue;
	}
}



/***********************************************************************/
SCSFExport scsf_momentum(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="Mom";
		sc.StudyDescription="Classic John Murphy Momentum http://www.investopedia.com/articles/technical/03/070203.asp";
		sc.Subgraph[0].Name = "Mom";
		sc.Subgraph[1].Name = "MidLine";
		sc.Input[3].Name="Length";		sc.Input[3].SetInt(20);
		sc.Input[4].Name="ZeroLine";	sc.Input[4].SetFloat(0.0);
		sc.DrawZeros=1;
		sc.FreeDLL=0;
		return;
	}
	
	int& Length = sc.Input[3].IntValue;		
	float& Line = sc.Input[4].FloatValue;	

		
	for(int i=sc.UpdateStartIndex; i<sc.ArraySize; i++)
	{
		sc.Subgraph[0][i] = sc.BaseDataIn[3][i]-sc.BaseDataIn[3][i-Length];
		sc.Subgraph[1][i] = Line;
	}
}

/***********************************************************************/
SCSFExport scsf_MA_Coloured(SCStudyInterfaceRef sc)
{
  if (sc.SetDefaults)
    {
        sc.GraphName="MA Colour";
        sc.StudyDescription="Colour Band MAs";	
		sc.Subgraph[0].Name = "UpUp Colour";	sc.Subgraph[0].DrawStyle=DRAWSTYLE_FILLTOP;
		sc.Subgraph[1].Name = "Up Colour";		sc.Subgraph[1].DrawStyle=DRAWSTYLE_FILLBOTTOM;
		sc.Subgraph[2].Name = "Dn Colour";		sc.Subgraph[2].DrawStyle=DRAWSTYLE_IGNORE;
		sc.Subgraph[3].Name = "DnDn Colour";	sc.Subgraph[3].DrawStyle=DRAWSTYLE_IGNORE;
		
		sc.Input[0].Name="MA Type";				sc.Input[0].SetMovAvgType(MOVAVGTYPE_EXPONENTIAL);
		sc.Input[1].Name="MA Input";			sc.Input[1].SetInputDataIndex(SC_LAST);
		sc.Input[3].Name="Short MA Length";		sc.Input[3].SetInt(13);
		sc.Input[4].Name="Long MA Length";		sc.Input[4].SetInt(21);
	//	sc.Input[5].Name="Only Close outside MAs";	sc.Input[5].SetYesNo(TRUE);
		
		sc.GraphRegion = 0;  // First region	
		sc.DrawZeros=1;
        return;
    }
	
	//sc.FreeDLL=TRUE;
	
	int& SLength = sc.Input[3].IntValue;		
	int& LLength = sc.Input[4].IntValue;	

		
	for(int i=sc.UpdateStartIndex; i<sc.ArraySize; i++)
	{
		sc.MovingAverage(sc.BaseDataIn[sc.Input[1].GetInputDataIndex()], sc.Subgraph[5], sc.Input[0].GetMovAvgType(), i, SLength);
		sc.MovingAverage(sc.BaseDataIn[sc.Input[1].GetInputDataIndex()], sc.Subgraph[6], sc.Input[0].GetMovAvgType(), i, LLength);
		if(sc.Subgraph[5][i] > sc.Subgraph[6][i]) {
			sc.Subgraph[0][i]=sc.Subgraph[5][i];
			sc.Subgraph[1][i]=sc.Subgraph[6][i];
			if(sc.BaseDataIn[3][i]>sc.Subgraph[5][i]) 
			sc.Subgraph[0].DataColor[i]=sc.Subgraph[0].PrimaryColor; else sc.Subgraph[0].DataColor[i]=sc.Subgraph[1].PrimaryColor;
		} else {
			sc.Subgraph[0][i]=sc.Subgraph[6][i];
			sc.Subgraph[1][i]=sc.Subgraph[5][i];		
			if(sc.BaseDataIn[3][i]<sc.Subgraph[5][i]) 
			sc.Subgraph[0].DataColor[i]=sc.Subgraph[3].PrimaryColor; else sc.Subgraph[0].DataColor[i]=sc.Subgraph[2].PrimaryColor;
		} 
	}
}


/***********************************************************************/
SCSFExport scsf_DayBeforeCandle(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "Less One Day";
		sc.StudyDescription = " ";
		sc.IsCustomChart = 1;  // true		
		sc.GraphRegion = 0;  // First region		
		sc.DrawZeros = 0;  // false		
		sc.StandardChartHeader = 1; // true
		sc.Subgraph[0].Name = "Open";
		sc.Subgraph[1].Name = "High";
		sc.Subgraph[2].Name = "Low";
		sc.Subgraph[3].Name = "Last";
		sc.Subgraph[4].Name = "Volume";
		sc.Subgraph[5].Name = "Ticks";
		sc.Input[5].Name="Offset to start new direction";
        sc.Input[6].Name="Hourly Chart";		sc.Input[6].SetFloat(1);
        sc.Input[7].Name="Open Study";			sc.Input[7].SetFloat(3);
		sc.CalculationPrecedence = VERY_LOW_PREC_LEVEL;
		sc.FreeDLL=0;
		return;
	} 
	
	int& Count  = sc.PersistVars->i1; 
	int    updown=1,os;
    float  highestlow=0.0,lowesthigh=999999.9;	
	
	if (sc.UpdateStartIndex == 0)
	{
		if( sc.Symbol.CompareNoCase("USD.JPY", 7)==0 || 
			sc.Symbol.CompareNoCase("EUR.JPY", 7)==0 || 
			sc.Symbol.CompareNoCase("GBP.JPY", 7)==0   )
		  {sc.ValueFormat=2; sc.ScaleIncrement = 0.5f;}
		  else 
		  {sc.ValueFormat=4; sc.ScaleIncrement = 0.005f;} 
		sc.ResizeArrays(0);
	}
	
	
	for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		if (sc.OutArraySize - 1 < i)
			sc.AddElements(1);
		sc.DateTimeOut[i].SetTime(sc.BaseDateTimeIn[i].GetTime());
		sc.DateTimeOut[i].SetDate(sc.BaseDateTimeIn[i].GetDate()-1);
		sc.Subgraph[0][i] = sc.BaseDataIn[0][i];
		sc.Subgraph[1][i] = sc.BaseDataIn[1][i];
		sc.Subgraph[2][i] = sc.BaseDataIn[2][i];
		sc.Subgraph[3][i] = sc.BaseDataIn[3][i];
		sc.Subgraph[4][i] = sc.BaseDataIn[4][i];
		
		int pos=i;  float& offset= sc.Input[5].FloatValue;
		int upcol = sc.Subgraph[0].PrimaryColor, dncol = sc.Subgraph[1].PrimaryColor, 
			oscol = sc.Subgraph[2].PrimaryColor, wkcol = sc.Subgraph[3].PrimaryColor;
	

		float& oo = sc.BaseDataIn[0][pos]; float& cc = sc.BaseDataIn[3][pos];
		os=0;
		
		if((sc.BaseDataIn[1][pos]<sc.BaseDataIn[1][pos-1] && sc.BaseDataIn[2][pos]>=sc.BaseDataIn[2][pos-1]) ||
			(sc.BaseDataIn[1][pos]<=sc.BaseDataIn[1][pos-1] && sc.BaseDataIn[2][pos]>sc.BaseDataIn[2][pos-1]) )  {os=1;};
		
		if(os==1)
		{ sc.Subgraph[0].DataColor[pos] = oscol; sc.Subgraph[1].DataColor[pos] = oscol;
		  sc.Subgraph[2].DataColor[pos] = oscol; sc.Subgraph[3].DataColor[pos] = oscol;
		} else if(cc>oo)
		{ sc.Subgraph[0].DataColor[pos] = upcol; sc.Subgraph[1].DataColor[pos] = upcol;
		  sc.Subgraph[2].DataColor[pos] = upcol; sc.Subgraph[3].DataColor[pos] = upcol;
		} else if(oo>cc)
		{ sc.Subgraph[0].DataColor[pos] = dncol; sc.Subgraph[1].DataColor[pos] = dncol;
		  sc.Subgraph[2].DataColor[pos] = dncol; sc.Subgraph[3].DataColor[pos] = dncol;
		} else
		{ sc.Subgraph[0].DataColor[pos] = wkcol; sc.Subgraph[1].DataColor[pos] = wkcol;
		  sc.Subgraph[2].DataColor[pos] = wkcol; sc.Subgraph[3].DataColor[pos] = wkcol;
		}

		
	}

	
	SCFloatArray LastBar;
	sc.GetStudyArrayFromChart((int)sc.Input[6].FloatValue,(int)sc.Input[7].FloatValue,1,LastBar);
	int i=sc.ArraySize-1;
	if(LastBar[1]!=0 && sc.BaseDateTimeIn[i].GetDate()==LastBar[0]+1) {
		sc.Subgraph[1][i] = LastBar[1];
		sc.Subgraph[2][i] = LastBar[2];
		sc.Subgraph[3][i] = LastBar[3];
	}
	sc.Subgraph[4][i]=sc.BaseDateTimeIn[i].GetDate();
	sc.Subgraph[5][i]=LastBar[0];
	
}



/***********************************************************************/
SCSFExport scsf_YQMW_HL(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
	   	sc.GraphName="HLC50s";
	    sc.StudyDescription="Highs, Lows, etc";
		sc.Subgraph[0].Name="YC";
		sc.Subgraph[1].Name="YH";
		sc.Subgraph[2].Name="YL";
		sc.Subgraph[3].Name="Y50";
		sc.Subgraph[4].Name="Y+1";
		sc.Subgraph[5].Name="Y+50";
		sc.Subgraph[6].Name="Y-50";
		sc.Subgraph[7].Name="Y-1";
		sc.Subgraph[8].Name="Info8";
		sc.Subgraph[9].Name="Info9";
		sc.Subgraph[10].Name="QC";
		sc.Subgraph[11].Name="QH";
		sc.Subgraph[12].Name="QL";
		sc.Subgraph[13].Name="Q50";
		sc.Subgraph[14].Name="Q+1";
		sc.Subgraph[15].Name="Q+50";
		sc.Subgraph[16].Name="Q-50";
		sc.Subgraph[17].Name="Q-1";
		sc.Subgraph[20].Name="MC";
		sc.Subgraph[21].Name="MH";
		sc.Subgraph[22].Name="ML";
		sc.Subgraph[23].Name="M50";
		sc.Subgraph[24].Name="M+1";
		sc.Subgraph[25].Name="M+50";
		sc.Subgraph[26].Name="M-50";
		sc.Subgraph[27].Name="M-1";
		sc.Subgraph[30].Name="WC";
		sc.Subgraph[31].Name="WH";
		sc.Subgraph[32].Name="WL";
		sc.Subgraph[33].Name="W50";
		sc.Subgraph[34].Name="W+1";
		sc.Subgraph[35].Name="W+50";
		sc.Subgraph[36].Name="W-50";
		sc.Subgraph[37].Name="W-1";
		sc.Input[3].Name="YQMW 8 4 2 1 (logical or)";				sc.Input[3].SetInt(15);
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.GraphRegion = 0; 
		sc.DrawZeros=0;
	    return;
	}
	
	float& High = sc.PersistVars->f1;	float& Low = sc.PersistVars->f2;
	float& LHigh = sc.PersistVars->f3;	float& LLow = sc.PersistVars->f4;
	float& Close= sc.PersistVars->f5;	
	int& ii = sc.PersistVars->i1;		int& iWstart = sc.PersistVars->i2;
	int& YQMW = sc.Input[3].IntValue;
	int    i,j;
		
	// DayOfWeekEnum SUNDAY = 0, MONDAY = 1, TUESDAY = 2, WEDNESDAY = 3, THURSDAY = 4, FRIDAY = 5, SATURDAY = 6
	if (sc.UpdateStartIndex == 0 || ii != sc.UpdateStartIndex) {	
		
		iWstart=0;	High=sc.BaseDataIn[1][0]; Low=sc.BaseDataIn[2][0];
		int p, yp, yi, mp, mi, dp, di;
		int  newyear=0, newquarter=0, newmonth=0;
	
	sc.Subgraph[8][sc.ArraySize-1]=YQMW;	
	sc.Subgraph[9][sc.ArraySize-1]=YQMW&8;
	
	for ( i=0; i < sc.ArraySize && (YQMW&8); i++) // Do Yearly
		{ 
			p=i-1;
			yi=sc.BaseDateTimeIn[i].GetYear(); 			yp=sc.BaseDateTimeIn[p].GetYear();
			mi=sc.BaseDateTimeIn[i].GetMonth(); 		mp=sc.BaseDateTimeIn[p].GetMonth();
			
			if( yp != yi  ) // yesterday was different so its a new year
			{ 
				LHigh=High; LLow=Low; iWstart=i; newyear=2;
				High=sc.BaseDataIn[1][i]; Low=sc.BaseDataIn[2][i]; Close=sc.BaseDataIn[3][p];
			} 
			else	
			if( newyear != 0)
			{
				if(mp != mi) { // not first day, so if month is diff its second month
					 newyear=0;  
				} else
				{
					if(sc.BaseDataIn[1][i]>High) High=sc.BaseDataIn[1][i];
					if(sc.BaseDataIn[2][i]<Low)  Low=sc.BaseDataIn[2][i];
				}
			}
				
			for(j=i; j>=iWstart; j--) {	
				float gap = High-Low, halfgap=gap/2;
				sc.Subgraph[0][j]=Close; sc.Subgraph[1][j]=High; sc.Subgraph[2][j]=Low; 
				sc.Subgraph[3][j]=(High+Low)/2; 
				sc.Subgraph[4][j]=High+gap; sc.Subgraph[5][j]=High+halfgap; 
				sc.Subgraph[7][j]=Low-gap; 	sc.Subgraph[6][j]=Low-halfgap; 
				
			}	
		}
	
	
	
	
		for ( i=0; i < sc.ArraySize && (YQMW&4); i++) // Do Quarterly
		{ 
			p=i-1;
			mi=sc.BaseDateTimeIn[i].GetMonth(); 		mp=sc.BaseDateTimeIn[p].GetMonth();
			di=sc.BaseDateTimeIn[i].GetDayOfWeek(); 	dp=sc.BaseDateTimeIn[p].GetDayOfWeek();
			
			if( mp != mi && ( mi==1 || mi==4 || mi==7 || mi==10 ) ) // yesterday was different so its a new month
			{ 
				LHigh=High; LLow=Low; iWstart=i; newquarter=2;
				High=sc.BaseDataIn[1][i]; Low=sc.BaseDataIn[2][i]; Close=sc.BaseDataIn[3][p];
			} 
			else	
			if( newquarter != 0)
			{
				if(dp > di) { // not first day, so if day is lower then its the second week of the month
					 newquarter=newquarter-1;  // use the first two weeks for quarterly
				} 
				if(newquarter != 0)
				{
					if(sc.BaseDataIn[1][i]>High) High=sc.BaseDataIn[1][i];
					if(sc.BaseDataIn[2][i]<Low)  Low=sc.BaseDataIn[2][i];
				}
			}
				
			for(j=i; j>=iWstart; j--) {	
				float gap = High-Low, halfgap=gap/2;
				sc.Subgraph[10][j]=Close; sc.Subgraph[11][j]=High; sc.Subgraph[12][j]=Low; 
				sc.Subgraph[13][j]=(High+Low)/2; 
				sc.Subgraph[14][j]=High+gap; 	sc.Subgraph[15][j]=High+halfgap; 
				sc.Subgraph[17][j]=Low-gap; 	sc.Subgraph[16][j]=Low-halfgap; 
				
			}	
		}
	
	
	
	
		for ( i=0; i < sc.ArraySize && (YQMW&2); i++) // Do Monthly
		{ 
			p=i-1;
			mi=sc.BaseDateTimeIn[i].GetMonth(); 		mp=sc.BaseDateTimeIn[p].GetMonth();
			di=sc.BaseDateTimeIn[i].GetDayOfWeek(); 	dp=sc.BaseDateTimeIn[p].GetDayOfWeek();
			
			if( mp != mi ) // yesterday was different so its a new month
			{ 
				LHigh=High; LLow=Low; iWstart=i; newmonth=mi;
				High=sc.BaseDataIn[1][i]; Low=sc.BaseDataIn[2][i]; Close=sc.BaseDataIn[3][p];
			} else
			if( newmonth != 0 )
			{
				if(dp > di) { // not first day, so if day is lower then its the second week of the month
					 newmonth=0;
				} else {
					if(sc.BaseDataIn[1][i]>High) High=sc.BaseDataIn[1][i];
					if(sc.BaseDataIn[2][i]<Low)  Low=sc.BaseDataIn[2][i];
				}
			}
				
			for(j=i; j>=iWstart; j--) {	
				float gap = High-Low, halfgap=gap/2;
				sc.Subgraph[20][j]=Close; sc.Subgraph[21][j]=High; sc.Subgraph[22][j]=Low; 
				sc.Subgraph[23][j]=(High+Low)/2; 
				sc.Subgraph[24][j]=High+gap; 	sc.Subgraph[25][j]=High+halfgap; 
				sc.Subgraph[27][j]=Low-gap; 	sc.Subgraph[26][j]=Low-halfgap; 
				
				sc.Subgraph[0][j]=newmonth;
			}	
		}
	
	
	
	
		for ( i=0; i < sc.ArraySize && (YQMW&1); i++)  // Do Weekly
		{ 
			p=i-1;
			di=sc.BaseDateTimeIn[i].GetDayOfWeek(); dp=sc.BaseDateTimeIn[p].GetDayOfWeek();
			
			if( dp>di ) // yesterday was a higher day than today so its a new week
			{ 
				iWstart=i; 
				High=sc.BaseDataIn[1][i]; Low=sc.BaseDataIn[2][i]; Close=sc.BaseDataIn[3][p];
			} 
				
			for(j=i; j>=iWstart; j--) {	
				float gap = High-Low, halfgap=gap/2;
				sc.Subgraph[30][j]=Close; sc.Subgraph[31][j]=High; sc.Subgraph[32][j]=Low; 
				sc.Subgraph[33][j]=(High+Low)/2; 
				sc.Subgraph[34][j]=High+gap; 	sc.Subgraph[35][j]=High+halfgap; 
				sc.Subgraph[37][j]=Low-gap; 	sc.Subgraph[36][j]=Low-halfgap; 
			}	
		}
	}
}; 




/***********************************************************************/
SCSFExport scsf_D_HL(SCStudyInterfaceRef sc)
{
	if (sc.SetDefaults)
	{
	   	sc.GraphName="D50s";
	    sc.StudyDescription="Highs, Lows, etc";
		sc.Subgraph[0].Name="DC";
		sc.Subgraph[1].Name="DH";
		sc.Subgraph[2].Name="DL";
		sc.Subgraph[3].Name="D50";
		sc.Subgraph[4].Name="D+1";
		sc.Subgraph[5].Name="D+50";
		sc.Subgraph[6].Name="D-50";
		sc.Subgraph[7].Name="D-1";
		sc.Subgraph[8].Name="Info8";
		sc.Subgraph[9].Name="Info9";
        sc.Input[2].Name="OR Starts";		sc.Input[3].Name="OR Finishes";
        sc.Input[2].ValueType=TIME_VALUE;  	sc.Input[3].ValueType=TIME_VALUE;  
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.GraphRegion = 0; 
		sc.DrawZeros=0;
	    return;
	}
	
	if(sc.Subgraph[9][1]==sc.BaseDateTimeIn[sc.ArraySize-1].GetTime() && sc.UpdateStartIndex!=0 ) return;
	sc.Subgraph[9][1] = sc.BaseDateTimeIn[sc.ArraySize-1].GetTime();
	
	float& High = sc.PersistVars->f1;	float& Low = sc.PersistVars->f2;
	float& LHigh = sc.PersistVars->f3;	float& LLow = sc.PersistVars->f4;
	float& Close= sc.PersistVars->f5;	
	int& iWstart = sc.PersistVars->i2;
	int    i,j,p;
		
	if (sc.UpdateStartIndex == 0) {		
		iWstart=0;	High=sc.BaseDataIn[1][0]; Low=sc.BaseDataIn[2][0];
	}

	
	for ( i=0; i < sc.ArraySize; i++) 
		{ 
			p=i-1;			
			if( sc.BaseDateTimeIn[i].GetTime() >=  sc.Input[2].GetTime() && 
				(sc.BaseDateTimeIn[p].GetTime() <  sc.Input[2].GetTime() || 
				 sc.BaseDateTimeIn[p].GetDate() != sc.BaseDateTimeIn[i].GetDate()) ) // yesterday was different so its a new day
			{ 
				LHigh=High; LLow=Low; iWstart=i; 
				High=sc.BaseDataIn[1][i]; Low=sc.BaseDataIn[2][i]; Close=sc.BaseDataIn[3][p];
			} 
			else	
			if( sc.BaseDateTimeIn[p].GetTime() >=  sc.Input[2].GetTime() && 
				sc.BaseDateTimeIn[i].GetTime() <=  sc.Input[3].GetTime() )
			{
					if(sc.BaseDataIn[1][i]>High) High=sc.BaseDataIn[1][i];
					if(sc.BaseDataIn[2][i]<Low)  Low=sc.BaseDataIn[2][i];
			}
				
			for(j=i; j>=iWstart; j--) {	
				float gap = High-Low, halfgap=gap/2;
				sc.Subgraph[0][j]=Close; sc.Subgraph[1][j]=High; sc.Subgraph[2][j]=Low; 
				sc.Subgraph[3][j]=(High+Low)/2; 
				sc.Subgraph[4][j]=High+gap; sc.Subgraph[5][j]=High+halfgap; 
				sc.Subgraph[7][j]=Low-gap; 	sc.Subgraph[6][j]=Low-halfgap; 
				
			}	
		}
	
} 

/*
		if (sc.UpdateStartIndex == 0) {
			for(i=0; i<40; i++) { sc.Subgraph[i].DrawStyle=DRAWSTYLE_DASH; sc.Subgraph[i].PrimaryColor=0; }
		}
*/

/*==========================================================================*/
int CalculatePivotPoints
(  float Open
 , float High
 , float Low
 , float Close
 , float NextOpen
 , float& PivotPoint
 , float& R_5
 , float& R1, float& R1_5
 , float& R2, float& R2_5
 , float& R3
 , float& S_5
 , float& S1, float& S1_5
 , float& S2, float& S2_5
 , float& S3
 , float& R4
 , float& S4
 , int FormulaType

 )
{

	if(  FormulaType == 0 )
	{
		PivotPoint = (High + Low + Close) / 3;
		R1 = (PivotPoint * 2) - Low;
		R_5 = (PivotPoint + R1) / 2;
		R2 = PivotPoint + (High - Low);
		R1_5 = (R1 + R2) / 2;
		S1 = (2 * PivotPoint) - High;
		S_5 = (PivotPoint + S1) / 2;
		S2 = PivotPoint - (High - Low);
		S1_5 = (S1 + S2) / 2;
		R3 = 2 * PivotPoint + (High - 2*Low); // R3 std
		R2_5 = (R2 + R3) / 2;
		S3 = 2 * PivotPoint - (2 * High - Low); // S3 std
		S2_5 = (S2 + S3) / 2;
		R4 = 3 * PivotPoint + (High - 3 * Low);
		S4 = 3 * PivotPoint - (3 * High - Low);
	}

	else if( FormulaType == 1 )
	{
		float YesterdaysRange;

		PivotPoint = (High + Low + Close) / 3;
		R1 = (PivotPoint * 2) - Low;
		R_5 = (PivotPoint + R1) / 2;
		R2 = PivotPoint + (High-Low);
		R1_5 = (R1 + R2) / 2;
		S1 = (2 * PivotPoint) - High;
		S_5 = (PivotPoint + S1) / 2;
		S2 = PivotPoint - (High - Low);
		S1_5 = (S1 + S2) / 2;
		YesterdaysRange = (High - Low);

		// This is R3 Pattern Trapper
		R3 = High + YesterdaysRange; // 2 * High - Low
		R2_5 = (R2 + R3)/2;

		// This is S3 Pattern Trapper
		S3 = 2*PivotPoint - High - YesterdaysRange; // 2 * PivotPoint - (2 * High + Low)
		S2_5 = (S2 + S3) / 2;

		R4 = PivotPoint + 3 * (High - Low);
		S4 = PivotPoint - 3 * (High - Low);
	}
	else if(  FormulaType == 2 )
	{
		PivotPoint = (NextOpen + High + Low + Close) / 4;
		R1 = (PivotPoint * 2) - Low;
		R_5 = (PivotPoint + R1) / 2;
		R2 = PivotPoint + (High - Low);
		R1_5 = (R1 + R2) / 2;
		S1 = (2 * PivotPoint) - High;
		S_5 = (PivotPoint + S1) / 2;
		S2 = PivotPoint - (High - Low);
		S1_5 = (S1 + S2) / 2;
		R3 = 2*PivotPoint + (High - 2*Low); // R3 std
		R2_5 = (R2 + R3) / 2;
		S3 = 2*PivotPoint - (2*High - Low); // S3 std
		S2_5 = (S2 + S3) / 2;
		R4 = 3 * PivotPoint + (High - 3 * Low);
		S4 = 3 * PivotPoint - (3 * High - Low);
	}
	else if(FormulaType == 3)
	{
		PivotPoint = (High + Low + NextOpen+NextOpen) / 4;
		R1 = (PivotPoint * 2) - Low;
		R_5 = (PivotPoint + R1) / 2;
		R2 = PivotPoint + (High - Low);
		R1_5 = (R1 + R2) / 2;
		S1 = (2 * PivotPoint) - High;
		S_5 = (PivotPoint + S1) / 2;
		S2 = PivotPoint - (High - Low);
		S1_5 = (S1 + S2) / 2;
		R3 = 2 * PivotPoint + (High - 2*Low); // R3 std
		R2_5 = (R2 + R3) / 2;
		S3 = 2 * PivotPoint - (2 * High - Low); // S3 std
		S2_5 = (S2 + S3) / 2;
		R4 = 3 * PivotPoint + (High - 3 * Low);
		S4 = 3 * PivotPoint - (3 * High - Low);
	}
	else if (FormulaType == 4)
	{
		PivotPoint = (High + Low + Close) / 3;
		R1 = (PivotPoint * 2) - Low;
		R_5 = (PivotPoint + R1) / 2;
		R2 = PivotPoint + (High - Low);
		R1_5 = (R1 + R2) / 2;
		S1 = (2 * PivotPoint) - High;
		S_5 = (PivotPoint + S1) / 2;
		S2 = PivotPoint - (High - Low);
		S1_5 = (S1 + S2) / 2;
		R3 = PivotPoint + 2 * (High - Low); 
		R2_5 = (R2 + R3) / 2;
		S3 = PivotPoint - 2 * (High - Low); 
		S2_5 = (S2 + S3) / 2;
		R4 = PivotPoint + 3 * (High - Low);
		S4 = PivotPoint - 3 * (High - Low);
	}
	else if (FormulaType == 5) // Camarilla Pivot Points
	{
		float Range = High - Low;
		PivotPoint = (High + Low + Close) / 3;

		R_5 = Close + Range * 1.1f/18;
		R1 = Close + Range * 1.1f/12;
		R1_5 = Close + Range * 1.1f/9;
		R2 = Close + Range * 1.1f/6;
		R2_5 = Close + Range * 1.1f/5;
		R3 = Close + Range * 1.1f/4;
		R4 = Close + Range * 1.1f/2;

		S_5 = Close - Range * 1.1f/18;
		S1 = Close - Range * 1.1f/12;
		S1_5 = Close - Range * 1.1f/9;
		S2 = Close - Range * 1.1f/6;
		S2_5 = Close - Range * 1.1f/5;
		S3 = Close - Range * 1.1f/4;
		S4 = Close - Range * 1.1f/2;
	}
	else if (FormulaType == 6)  // Tom DeMark's Pivot Points
	{
		float X = 0;
		if (Close < Open)
			X = High + Low + Low + Close;
		else if (Close > Open)
			X = High + High + Low + Close;
		else if (Close == Open)
			X = High + Low + Close + Close;

		PivotPoint = X / 4;
		R1 = X / 2 - Low;
		S1 = X / 2 - High;
		R_5 = R2 = R1_5 = S_5 = S2 = S1_5 = R3 = 
			R2_5 = S3 = S2_5 = R4 = S4 = 0;
	}
	else if (FormulaType == 7) // Frank Dilernia Pivots
	{
		PivotPoint = (High + Low + Close) / 3;
		R1 = PivotPoint + (High - Low)/2;
		R2 = PivotPoint + (High - Low) * 0.618f;
		R3 = PivotPoint + (High - Low);
		S1 = PivotPoint - (High - Low)/2;
		S2 = PivotPoint - (High - Low) * 0.618f;
		S3 = PivotPoint - (High - Low);

		S2_5 = (S3 + S2)/2;				
		S1_5 = (S2 + S1)/2;				
		S_5 = (S1 + PivotPoint)/2;			
		R_5 = (R1 + PivotPoint)/2;			
		R1_5 = (R2 + R1)/2;				
		R2_5 = (R3 + R2)/2;				
	}
	else if (FormulaType == 8) // Shadow Trader. www.shadowtrader.net
	{
		PivotPoint = (High + Low + Close) / 3; //PIVOT = (High + Close + Low)/3
		R1 = (2 * PivotPoint) - Low; //R1 = (2*Pivot) - Low
		S1 = (2 * PivotPoint) - High; //S1 = (2*Pivot) - High
		R2 = PivotPoint + (R1 - S1); // R2 = Pivot + (R1 - S1)
		R3 = 2*(PivotPoint - Low) + High; //R3 = High + 2(Pivot - Low)
		S2 = PivotPoint - (R1 - S1); //S2 = Pivot - (R1 - S1)
		S3 = Low - 2 * (High - PivotPoint); //S3 = Low - 2(Hi - Pivot)

		S2_5 = (S3 + S2)/2;				
		S1_5 = (S2 + S1)/2;				
		S_5 = (S1 + PivotPoint)/2;			
		R_5 = (R1 + PivotPoint)/2;			
		R1_5 = (R2 + R1)/2;				
		R2_5 = (R3 + R2)/2;				

	}
	else if (FormulaType == 9)
	{

		PivotPoint = (High + Low + Close)/3; //PP = H + L + C /3
		float PPSquareRoot = sqrt(sqrt(PivotPoint));
		R1 = PivotPoint + PPSquareRoot; //R1 = PP + SQRT(SQRT(PP))
		R2 = R1 + PPSquareRoot; //R2 = R1 + SQRT(SQRT(PP))
		R3 = R2 + PPSquareRoot; //R3 = R2 + SQRT(SQRT(PP))
		S1 = PivotPoint - PPSquareRoot; //S1 = PP - SQRT(SQRT(PP))
		S2 = S1 - PPSquareRoot; //S2 = S1 - SQRT(SQRT(PP))
		S3 = S2 - PPSquareRoot; //S3 = S2 - SQRT(SQRT(PP))

		S2_5 = (S3 + S2)/2;				
		S1_5 = (S2 + S1)/2;				
		S_5 = (S1 + PivotPoint)/2;			
		R_5 = (R1 + PivotPoint)/2;			
		R1_5 = (R2 + R1)/2;				
		R2_5 = (R3 + R2)/2;				

	}
	else if (FormulaType == 10)
	{
		PivotPoint = (High + Low + Close)/3;	//PIVOT = H + L + C /3
		R1 = 2 * PivotPoint - Low;				//R1 = 2X PIVOT -LOW
		R2 = PivotPoint + High - Low;			//R2 = PIVOT + (HIGH - LOW)
		R3 = R1 + High - Low;					//R3 = R1+ (HIGH - LOW)

		S1 = 2 * PivotPoint - High;			//S1 = 2X PIVOT -HIGH
		S2 = PivotPoint - (High - Low);		//S2 = PIVOT - (HIGH - LOW)
		S3 = S1 - (High - Low);				//S3 = S1 - (HIGH - LOW)

		S2_5 = (S3 + S2)/2;					//M0 = S3+S2 /2
		S1_5 = (S2 + S1)/2;					//M1 = S2+S1 /2
		S_5 = (S1 + PivotPoint)/2;				//M2 = S1+PIVOT /2
		R_5 = (R1 + PivotPoint)/2;				//M3 = R1+PIVOT /2
		R1_5 = (R2 + R1)/2;					//M4 = R2+R1/2
		R2_5 = (R3 + R2)/2;					//M5 = R3 + R2 /2
	}
	else if (FormulaType == 11)
	{
		PivotPoint = (High + Low + Close)/3;
		float DailyRange = High - Low;

		R_5 = PivotPoint + 0.5f*DailyRange;
		R1 = PivotPoint + 0.618f*DailyRange;
		R1_5 = PivotPoint + DailyRange;
		R2 = PivotPoint + 1.272f*DailyRange;
		R2_5 = PivotPoint + 1.618f*DailyRange;
		R3 = PivotPoint + 2*DailyRange;
		R4 = PivotPoint + 2.618f*DailyRange;

		S_5 = PivotPoint - 0.5f*DailyRange;
		S1 = PivotPoint - 0.618f*DailyRange;
		S1_5 = PivotPoint - DailyRange;
		S2 = PivotPoint - 1.272f*DailyRange;
		S2_5 = PivotPoint - 1.618f*DailyRange;
		S3 = PivotPoint - 2*DailyRange;
		S4 = PivotPoint - 2.618f*DailyRange;

	
	}
	else if (FormulaType == 12)
	{
		PivotPoint = NextOpen;

		R_5 = PivotPoint;
		R1 = PivotPoint;
		R1_5 = PivotPoint;
		R2 = PivotPoint;
		R2_5 = PivotPoint;
		R3 = PivotPoint;
		R4 = PivotPoint;

		S_5 = PivotPoint;
		S1 = PivotPoint;
		S1_5 = PivotPoint;
		S2 = PivotPoint;
		S2_5 = PivotPoint;
		S3 = PivotPoint;
		S4 = PivotPoint;
	}
	else if (FormulaType == 13) // Fibonacci's Pivot Points
	{
		PivotPoint = (High + Low + Close)/3;
		float DailyRange = High - Low;

	
		R1 = PivotPoint + 0.382f*DailyRange;
		R2 = PivotPoint + 0.618f*DailyRange;
		R3 = PivotPoint + 1*DailyRange;

		S1 = PivotPoint - 0.382f*DailyRange;
		S2 = PivotPoint - 0.618f*DailyRange;
		S3 = PivotPoint - 1*DailyRange;

		S2_5 = (S3 + S2)/2;				
		S1_5 = (S2 + S1)/2;				
		S_5 = (S1 + PivotPoint)/2;			
		R_5 = (R1 + PivotPoint)/2;			
		R1_5 = (R2 + R1)/2;				
		R2_5 = (R3 + R2)/2;				

	}
	else if (FormulaType == 14) 
	{
		PivotPoint = (High + Low + Close) / 3;
		
		R1 = (2 * PivotPoint) - Low;
		R2 = (PivotPoint - S1) + R1;
		R3 = (PivotPoint - S1) + R2;
		
		S1 = (2 * PivotPoint) - High;
		S2 = PivotPoint - (R1 - S1);
		S3 = PivotPoint - (R2 - S1) ;
	}
	else if (FormulaType == 15) // Fibonacci Zone Pivots
	{
		PivotPoint = (High + Low + Close) / 3;

		R1 = PivotPoint + (High - Low)/2;
		R2 = PivotPoint + (High - Low);

		S1 = PivotPoint - (High - Low)/2;
		S2 = PivotPoint - (High - Low);

		// 0.5 to 0.618 defines resistance/support band 1
		// 1.0 to 1.382 defines resistance/support band 2
		// the bands could start as lines and if the user 
		// wishes they can use Fill Rect top and bottom
		// or the transparent versions to suit visual tastes
		R1_5 = PivotPoint + (High - Low)*0.618f;
		R2_5 = PivotPoint + (High - Low)*1.382f;

		S1_5 = PivotPoint - (High - Low)*0.618f;
		S2_5 = PivotPoint - (High - Low)*1.382f;
	}
	else	if(  FormulaType ==16 )
	{
		/*
		THE CENTRAL PIVOT RANGE FORMULA:

		TC (TOPCENTRAL) = (PIVOT-BC)+PIVOT
		PIVOT = (HIGH+LOW+CLOSE)/3
		BC (BOTTOM CENTRAL) =(HIGH+LOW)/2
		*/
		PivotPoint = (High + Low + Close) / 3;
		S1 = (High + Low) / 2;
		R1 = (PivotPoint - S1) + PivotPoint;
	}

	
	return 1;
}



/*

	SCSubgraphRef o1 = sc.Subgraph[21];
	SCSubgraphRef o2 = sc.Subgraph[22];
	SCSubgraphRef o3 = sc.Subgraph[23];

		o1.Name = "o1";
		o2.Name = "o2";
		o3.Name = "o3";
		
		
			o1[index] = High;
			o2[index] = Low;
			o3[index] = Close;

*/



/***********************************************************************************/
SCSFExport scsf_PivotPointsVariablePeriod(SCStudyInterfaceRef sc)
{
	SCSubgraphRef R1 = sc.Subgraph[0];
	SCSubgraphRef R2 = sc.Subgraph[1];
	SCSubgraphRef S1 = sc.Subgraph[2];
	SCSubgraphRef S2 = sc.Subgraph[3];
	SCSubgraphRef R0_5 = sc.Subgraph[4];
	SCSubgraphRef R1_5 = sc.Subgraph[5];
	SCSubgraphRef R2_5 = sc.Subgraph[6];
	SCSubgraphRef R3 = sc.Subgraph[7];
	SCSubgraphRef S0_5 = sc.Subgraph[8];
	SCSubgraphRef S1_5 = sc.Subgraph[9];
	SCSubgraphRef S2_5 = sc.Subgraph[10];
	SCSubgraphRef S3 = sc.Subgraph[11];
	SCSubgraphRef PP = sc.Subgraph[12];
	SCSubgraphRef R4 = sc.Subgraph[13];
	SCSubgraphRef S4 = sc.Subgraph[14];
	SCSubgraphRef o1 = sc.Subgraph[21];
	SCSubgraphRef o2 = sc.Subgraph[22];
	SCSubgraphRef o3 = sc.Subgraph[23];
	SCSubgraphRef oH = sc.Subgraph[24];
	SCSubgraphRef oL = sc.Subgraph[25];
	SCSubgraphRef oC = sc.Subgraph[26];

	SCInputRef TimePeriodType = sc.Input[0];
	SCInputRef TimePeriodLength = sc.Input[1];
	SCInputRef FormulaType = sc.Input[2];
	SCInputRef MinimumRequiredTP = sc.Input[3];
	SCInputRef RoundToTickSize = sc.Input[4];
	SCInputRef DisplayDebuggingOutput = sc.Input[5];
	SCInputRef ForwardProjectLines = sc.Input[6];
	SCInputRef NumberOfDaysToCalculate = sc.Input[7];
	SCInputRef AggregateDays = sc.Input[8];


	if (sc.SetDefaults)
	{
		sc.GraphName = "PPVP for 3 day aggregation (24h)";

		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.DrawZeros = 0;
		sc.GraphRegion = 0;
		sc.ValueFormat = 3;

		R1.Name = "R1";
		R2.Name = "R2";
		S1.Name = "S1";
		S2.Name = "S2";
		R0_5.Name = "R.5";
		R1_5.Name = "R1.5";
		R2_5.Name = "R2.5";
		R3.Name = "R3";
		S0_5.Name = "S.5";
		S1_5.Name = "S1.5";
		S2_5.Name = "S2.5";
		S3.Name = "S3";
		PP.Name = "PP";
		R4.Name = "R4";
		S4.Name = "S4";
		o1.Name = "o1";
		o2.Name = "o2";
		o3.Name = "o3";
		oH.Name = "H";
		oL.Name = "L";
		oC.Name = "C";

		R1.DrawStyle = DRAWSTYLE_DASH;
		R2.DrawStyle = DRAWSTYLE_DASH;
		S1.DrawStyle = DRAWSTYLE_DASH;
		S2.DrawStyle = DRAWSTYLE_DASH;
		R0_5.DrawStyle = DRAWSTYLE_HIDDEN;
		R1_5.DrawStyle = DRAWSTYLE_HIDDEN;
		R2_5.DrawStyle = DRAWSTYLE_HIDDEN;
		R3.DrawStyle = DRAWSTYLE_DASH;
		S0_5.DrawStyle = DRAWSTYLE_HIDDEN;
		S1_5.DrawStyle = DRAWSTYLE_HIDDEN;
		S2_5.DrawStyle = DRAWSTYLE_HIDDEN;
		S3.DrawStyle = DRAWSTYLE_DASH;
		PP.DrawStyle = DRAWSTYLE_DASH;
		R4.DrawStyle = DRAWSTYLE_HIDDEN;
		S4.DrawStyle = DRAWSTYLE_HIDDEN;

		R1.PrimaryColor = RGB(255,0,0);
		R2.PrimaryColor = RGB(255,0,0);
		R0_5.PrimaryColor = RGB(255,0,0);
		R1_5.PrimaryColor = RGB(255,0,0);
		R2_5.PrimaryColor = RGB(255,0,0);
		R3.PrimaryColor = RGB(255,0,0);
		R4.PrimaryColor = RGB(255, 0, 0);

		S1.PrimaryColor = RGB(0,255,0);
		S2.PrimaryColor = RGB(0,255,0);
		S0_5.PrimaryColor = RGB(0,255,0);
		S1_5.PrimaryColor = RGB(0,255,0);
		S2_5.PrimaryColor = RGB(0,255,0);
		S3.PrimaryColor = RGB(0,255,0);
		PP.PrimaryColor = RGB(255,0,255);
		S4.PrimaryColor = RGB(0,255,0);

		for (int i = 0; i < 15; i++)
		{
			sc.Subgraph[i].LineLabel = 
				LL_DISPLAY_NAME | LL_DISPLAY_VALUE | LL_NAME_ALIGN_ABOVE | LL_NAME_ALIGN_LEFT | 
				LL_VALUE_ALIGN_CENTER | LL_VALUE_ALIGN_VALUES_SCALE;
		}

		TimePeriodType.Name = "Time Period Type";
		TimePeriodType.SetTimePeriodType(TIME_PERIOD_LENGTH_UNIT_DAYS);

		TimePeriodLength.Name = "Time Period Length";
		TimePeriodLength.SetInt(3);
		TimePeriodLength.SetIntLimits(1, 7*MINUTES_PER_DAY);

		FormulaType.Name = "Formula Type";
		FormulaType.SetInt(7);

		MinimumRequiredTP.Name = "Minimum Required Time Period as %";
		MinimumRequiredTP.SetFloat(25.0f);
		MinimumRequiredTP.SetFloatLimits(1.0f, 100.0f);

		RoundToTickSize.Name = "Round Off to Tick Size";
		RoundToTickSize.SetYesNo(0);

		DisplayDebuggingOutput.Name = "Display Debugging Output (slows study calculations)";
		DisplayDebuggingOutput.SetYesNo(0);

		ForwardProjectLines.Name ="Forward Project Pivot Point Lines";
		ForwardProjectLines.SetYesNo(0);

		NumberOfDaysToCalculate.Name = "Number Of Days To Calculate";
		NumberOfDaysToCalculate.SetInt(1000);
		
		
		AggregateDays.Name = "Aggregate Days";
		AggregateDays.SetYesNo(TRUE);

		return;
	}
	sc.FreeDLL=0;
	
	float fR0_5 = 0, fR1 = 0, fR1_5 = 0, fR2 = 0, fR2_5 = 0, fR3 = 0, fR4 = 0, fS4 = 0;
	float fS0_5 = 0, fS1 = 0, fS1_5 = 0, fS2 = 0, fS2_5 = 0, fS3 = 0, fPivotPoint= 0;

	int ValidPivotPoint = 1;
	SCDateTime BeginOfRefDateTime,EndOfRefDateTime;
	SCDateTime CurrentPeriodBeginDateTime;
	SCDateTime CurrentPeriodEndDateTime;

	int PeriodLength = TimePeriodLength.GetInt();
	SCDateTime FirstBarDateTime = sc.BaseDateTimeIn[0];

	SCDateTime ChartStartTime = sc.StartTime1;
	if (sc.UseSecondStartEndTimes)
		ChartStartTime = sc.StartTime2;


	int NumberOfForwardBars = 0;

	if (ForwardProjectLines.GetYesNo())
	{
		NumberOfForwardBars = 10;

		if(sc.UpdateStartIndex == 0)
		{
			PP.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			R1.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			R2.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			S1.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			S2.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			R0_5.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			R1_5.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			R2_5.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			R3.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			S0_5.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			S1_5.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			S2_5.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			S3.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			R4.ExtendedArrayElementsToGraph = NumberOfForwardBars;
			S4.ExtendedArrayElementsToGraph = NumberOfForwardBars;

		}
	}

	if (NumberOfDaysToCalculate.GetInt() < 1)
		NumberOfDaysToCalculate.SetInt(1000);

	int LastDateInChart = sc.BaseDateTimeIn[sc.ArraySize - 1].GetDate();
	int FirstDateToCalculate = LastDateInChart - NumberOfDaysToCalculate.GetInt() + 1;

	float Open = 0, High = 0, Low = 0, Close = 0, NextOpen = 0;

	for (int index = sc.UpdateStartIndex; index < sc.ArraySize-1+NumberOfForwardBars; index++ )
	{
		//This variable is used to determine the start of a period which is used to align the reference period for pivot calculations.
		SCDateTime StartDTForRefPeriodCalculations;
		SCDateTime CurrentBarDT = sc.BaseDateTimeIn[index];
		SCDateTime TimeIncrement;

		if (CurrentBarDT < FirstDateToCalculate)
			continue;

		bool GetReferenceData = true;

		if(CurrentBarDT >= CurrentPeriodBeginDateTime && CurrentBarDT <= CurrentPeriodEndDateTime)
			GetReferenceData = false;

		if ( GetReferenceData && (TimePeriodType.GetTimePeriodType() == TIME_PERIOD_LENGTH_UNIT_MINUTES
			|| (TimePeriodType.GetTimePeriodType() == TIME_PERIOD_LENGTH_UNIT_DAYS && (PeriodLength == 1 || AggregateDays.GetYesNo()))))
		{

			int NumMins = 0;

			if (TimePeriodType.GetTimePeriodType() == TIME_PERIOD_LENGTH_UNIT_DAYS)
			{
				NumMins = MINUTES_PER_DAY;
			}
			else 
				NumMins = PeriodLength;

			TimeIncrement = NumMins*MINUTES;

			if (ChartStartTime.GetTime()<= CurrentBarDT.GetTime())
			{
				StartDTForRefPeriodCalculations = ChartStartTime;
				StartDTForRefPeriodCalculations.SetDate(CurrentBarDT.GetDate());
			}
			else
			{
				StartDTForRefPeriodCalculations = ChartStartTime;
				StartDTForRefPeriodCalculations.SetDate(CurrentBarDT.GetDate()-1);
			}

			int TimeDiffInMinutes = sc.Round((float)((CurrentBarDT-StartDTForRefPeriodCalculations)/MINUTES));
			int NumberOfTimeBlocks = TimeDiffInMinutes/NumMins;

			if (NumberOfTimeBlocks == 0)
				EndOfRefDateTime = StartDTForRefPeriodCalculations-(1*SECONDS);
			else
				EndOfRefDateTime = StartDTForRefPeriodCalculations+((NumberOfTimeBlocks*NumMins*MINUTES)-(1*SECONDS));
		
			BeginOfRefDateTime = EndOfRefDateTime - (NumMins*MINUTES) + (1*SECONDS);
		}
		else if ( GetReferenceData && TimePeriodType.GetTimePeriodType() == TIME_PERIOD_LENGTH_UNIT_DAYS)
		{

			int NumMins = PeriodLength*MINUTES_PER_DAY;

			TimeIncrement = NumMins*MINUTES;


			if (ChartStartTime.GetTime()<= CurrentBarDT.GetTime())
			{
				StartDTForRefPeriodCalculations = ChartStartTime;
				StartDTForRefPeriodCalculations.SetDate(FirstBarDateTime.GetDate());
			}
			else
			{
				StartDTForRefPeriodCalculations = ChartStartTime;
				StartDTForRefPeriodCalculations.SetDate(FirstBarDateTime.GetDate()-1);
			}

			int TimeDiffInMinutes = sc.Round((float)((CurrentBarDT-StartDTForRefPeriodCalculations)/MINUTES));

			int NumberOfTimeBlocks = TimeDiffInMinutes/NumMins;

			if (NumberOfTimeBlocks == 0)
				continue;

			EndOfRefDateTime = StartDTForRefPeriodCalculations+((NumberOfTimeBlocks*NumMins*MINUTES)-(1*SECONDS));

			BeginOfRefDateTime = EndOfRefDateTime - ((NumMins-1)*MINUTES);
		}
		else if ( GetReferenceData &&  TimePeriodType.GetTimePeriodType() == TIME_PERIOD_LENGTH_UNIT_WEEKS)
		{
			int NumMins = PeriodLength*DAYS_PER_WEEK*MINUTES_PER_DAY;

			TimeIncrement = NumMins*MINUTES;

			int DayOfWeek = CurrentBarDT.GetDayOfWeek();
			StartDTForRefPeriodCalculations = CurrentBarDT.GetDate()-DayOfWeek;

			BeginOfRefDateTime = StartDTForRefPeriodCalculations-TimeIncrement;
			EndOfRefDateTime = StartDTForRefPeriodCalculations - (1*SECONDS);
		}
		else if ( GetReferenceData &&  TimePeriodType.GetTimePeriodType() == TIME_PERIOD_LENGTH_UNIT_MONTHS)
		{

			if(PeriodLength > 4)// && PeriodLength != 12)
				PeriodLength = 4;

			//For the monthly period we are going to use a fixed time increment of the average number of the days in a month.  This is not exact and if we have to walk back it will not be exact.  And when seeing if the current bar is within the same period  as the prior period, it will not be exact and we may have to do calculations again. 

			TimeIncrement = PeriodLength*(365/12.0);

			int CurrentYear, CurrentMonth, CurrentDay;
			CurrentBarDT.GetDateYMD(CurrentYear, CurrentMonth, CurrentDay);

			int NumberofPrecedingPeriods = (CurrentMonth - 1)/PeriodLength;


			int StartingMonth = 1+ (NumberofPrecedingPeriods-1)*PeriodLength;
			int StartingYear =  CurrentYear;

			if(StartingMonth <= 0)
			{
				StartingMonth = 12+StartingMonth;
				StartingYear = CurrentYear-1;
			}


			BeginOfRefDateTime.SetDateTimeYMDHMS(StartingYear, StartingMonth, 1, 0, 0, 0);

			if (StartingMonth+PeriodLength>=13)
			{
				StartingMonth = (StartingMonth)-12;
				StartingYear = StartingYear+1;
			}

			EndOfRefDateTime.SetDateTimeYMDHMS(StartingYear, StartingMonth+PeriodLength, 1, 0, 0, 0);
			EndOfRefDateTime -= 1 * SECONDS; // 1 second before the current month
		}
		else if ( GetReferenceData &&  TimePeriodType.GetTimePeriodType() == TIME_PERIOD_LENGTH_UNIT_YEARS)
		{
			continue; //unsupported.			
		}
		else if (GetReferenceData == false)
		{
			//Do nothing
		}
		else
			continue;


		//If there are insufficient bars for a reference period, then we will walk back 1 block/period at a time. 
		
		o1[index]=index;
		o2[index]=CurrentBarDT;
		if(GetReferenceData)
		{
			CurrentPeriodBeginDateTime = EndOfRefDateTime + (1*SECONDS);
			CurrentPeriodEndDateTime = CurrentPeriodBeginDateTime + (TimeIncrement) - (1*SECONDS);
			
			for (int i = 0;i<24;i++)
			{
//	oH[index-2]= BeginOfRefDateTime; oH[index-1]= EndOfRefDateTime; oH[index]= CurrentBarDT; 
				//if (i >= 1) //Walk back 1 period.
				{
					int daystolookback = TimePeriodLength.GetInt()-1;
					EndOfRefDateTime   = CurrentBarDT - (1*SECONDS);
					BeginOfRefDateTime = floor(CurrentBarDT) - TimeIncrement;
					
					int k=1, l=1;
					
					while( (sc.GetNearestMatchForSCDateTime(sc.ChartNumber, BeginOfRefDateTime) == index || sc.GetNearestMatchForSCDateTime(sc.ChartNumber, BeginOfRefDateTime) == index-1) && k<5) 
						{ BeginOfRefDateTime -= TimeIncrement; k++; }
						
					int lastindex=sc.GetNearestMatchForSCDateTime(sc.ChartNumber, BeginOfRefDateTime);
					while( daystolookback > 0 && l < 15) {
						BeginOfRefDateTime -= TimeIncrement;  
						daystolookback--; l++; 
						o3[index+1+daystolookback]=sc.GetNearestMatchForSCDateTime(sc.ChartNumber, BeginOfRefDateTime);
						while( (sc.GetNearestMatchForSCDateTime(sc.ChartNumber, BeginOfRefDateTime) == lastindex || sc.GetNearestMatchForSCDateTime(sc.ChartNumber, BeginOfRefDateTime) == lastindex-1) && k<5) 
							{ BeginOfRefDateTime -= TimeIncrement; k++; }
						lastindex=sc.GetNearestMatchForSCDateTime(sc.ChartNumber, BeginOfRefDateTime);	
					}
					
					
					//if( sc.GetNearestMatchForSCDateTime(sc.ChartNumber, BeginOfRefDateTime) == index ) BeginOfRefDateTime -= 2*TimeIncrement;
					//if(daystolookback )
					
				//	EndOfRefDateTime-=TimeIncrement;
				//	BeginOfRefDateTime-=TimeIncrement;					
				}

				int NumberOfBars = 0;
				SCDateTime TotalTimeSpan;
				int r = sc.GetOHLCOfTimePeriod(BeginOfRefDateTime, EndOfRefDateTime, Open, High, Low, Close, NextOpen, NumberOfBars, TotalTimeSpan);
				
				if (!r)
					continue;


				SCDateTime MinimumTimeSpan = (TimeIncrement * MinimumRequiredTP.GetFloat()/100.0f);
				if (TotalTimeSpan >= MinimumTimeSpan)
					break;
			}
		}


		ValidPivotPoint = 
			CalculatePivotPoints(Open,High,Low,Close,NextOpen,
			fPivotPoint, fR0_5, fR1, fR1_5, fR2, fR2_5, fR3, fS0_5, 
			fS1, fS1_5, fS2, fS2_5, fS3, fR4, fS4, FormulaType.GetInt());				


		if (!ValidPivotPoint)
			continue;

		if (RoundToTickSize.GetYesNo() != 0)
		{
			R1[index] = (float)sc.RoundToTickSize(fR1, sc.TickSize);
			R2[index] = (float)sc.RoundToTickSize(fR2, sc.TickSize);
			S1[index] = (float)sc.RoundToTickSize(fS1, sc.TickSize);
			S2[index] = (float)sc.RoundToTickSize(fS2, sc.TickSize);

			R0_5[index] = (float)sc.RoundToTickSize(fR0_5, sc.TickSize);
			R1_5[index] = (float)sc.RoundToTickSize(fR1_5, sc.TickSize);
			R2_5[index] = (float)sc.RoundToTickSize(fR2_5, sc.TickSize);
			R3[index] = (float)sc.RoundToTickSize(fR3, sc.TickSize);
			S0_5[index] = (float)sc.RoundToTickSize(fS0_5, sc.TickSize);
			S1_5[index] = (float)sc.RoundToTickSize(fS1_5, sc.TickSize);
			S2_5[index] = (float)sc.RoundToTickSize(fS2_5, sc.TickSize);
			S3[index] = (float)sc.RoundToTickSize(fS3, sc.TickSize);
			PP[index] = (float)sc.RoundToTickSize(fPivotPoint, sc.TickSize);
			R4[index] = (float)sc.RoundToTickSize(fR4, sc.TickSize);
			S4[index] = (float)sc.RoundToTickSize(fS4, sc.TickSize);
		}
		else 
		{
			R1[index] = fR1;
			R2[index] = fR2;
			S1[index] = fS1;
			S2[index] = fS2;

			R0_5[index] = fR0_5;
			R1_5[index] = fR1_5;
			R2_5[index] = fR2_5;
			R3[index] = fR3;
			S0_5[index] = fS0_5;
			S1_5[index] = fS1_5;
			S2_5[index] = fS2_5;
			S3[index] = fS3;
			PP[index] = fPivotPoint;
			R4[index] = fR4;
			S4[index] = fS4;
		}
			//o3[index] = NextOpen;
			oH[index] = High;
			oL[index] = Low;
			oC[index] = Close;
	} //for
}	
			


/***********************************************************************/
SCSFExport scsf_KER(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="KER";
		sc.StudyDescription="Kaufman's Efficiency Ratio";
		sc.Subgraph[0].Name="k1";
		sc.Subgraph[1].Name="k2";
		sc.Subgraph[2].Name="k3";
		sc.Subgraph[3].Name="Kave";
		sc.Input[2].Name="Period 1";  			sc.Input[2].SetFloat(20);
		sc.Input[3].Name="Period 2"; 			sc.Input[3].SetFloat(0);
		sc.Input[4].Name="Period 3";  			sc.Input[4].SetFloat(0);
		sc.DrawZeros=1;
		sc.FreeDLL=0; 
		return;
	}


	int		pos;
	float	w1=0,w2=0,w3=0;

	float& p1 = sc.Input[2].FloatValue; 
	float& p2 = sc.Input[3].FloatValue;
	float& p3 = sc.Input[4].FloatValue;


	for (pos=sc.UpdateStartIndex; pos < sc.ArraySize; pos++)
	{
		sc.Subgraph[4].Data[pos]=fabs(sc.BaseDataIn[3][pos]-sc.BaseDataIn[3][pos-1]);
		sc.Subgraph[5].Data[pos]=(sc.Subgraph[5].Data[pos-1]+sc.Subgraph[4].Data[pos]-sc.Subgraph[4].Data[pos-p1]);
		sc.Subgraph[6].Data[pos]=(sc.Subgraph[6].Data[pos-1]+sc.Subgraph[4].Data[pos]-sc.Subgraph[4].Data[pos-p2]);
		sc.Subgraph[7].Data[pos]=(sc.Subgraph[7].Data[pos-1]+sc.Subgraph[4].Data[pos]-sc.Subgraph[4].Data[pos-p3]);

		if(p1>0) {w1=1; sc.Subgraph[0].Data[pos] = fabs(sc.BaseDataIn[3][pos] - sc.BaseDataIn[3][pos-p1])/sc.Subgraph[5].Data[pos];};
		if(p2>0) {w2=1; sc.Subgraph[1].Data[pos] = fabs(sc.BaseDataIn[3][pos] - sc.BaseDataIn[3][pos-p2])/sc.Subgraph[6].Data[pos];};
		if(p3>0) {w3=1; sc.Subgraph[2].Data[pos] = fabs(sc.BaseDataIn[3][pos] - sc.BaseDataIn[3][pos-p3])/sc.Subgraph[7].Data[pos];};
		if((w1+w2+w3)>0) {sc.Subgraph[3].Data[pos]=(sc.Subgraph[0].Data[pos]+sc.Subgraph[1].Data[pos]+sc.Subgraph[2].Data[pos])/(w1+w2+w3);};


	}

};


/***********************************************************************/
SCSFExport scsf_GMMA(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="Guppy MMA";
		sc.Subgraph[0].Name="149";	sc.Subgraph[0].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[1].Name="139";	sc.Subgraph[1].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[2].Name="129";	sc.Subgraph[2].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[3].Name="119";	sc.Subgraph[3].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[4].Name="109";	sc.Subgraph[4].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[5].Name="99";	sc.Subgraph[5].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[6].Name="89";	sc.Subgraph[6].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[7].Name="55";	sc.Subgraph[7].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[8].Name="50";	sc.Subgraph[8].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[9].Name="45";	sc.Subgraph[9].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[10].Name="40";	sc.Subgraph[10].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[11].Name="35";	sc.Subgraph[11].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[12].Name="30";	sc.Subgraph[12].DrawStyle=DRAWSTYLE_LINE; 
		sc.Subgraph[13].Name="25";	sc.Subgraph[13].DrawStyle=DRAWSTYLE_LINE;

		sc.Input[10].Name="149";	sc.Input[10].SetInt(149);
		sc.Input[11].Name="139";	sc.Input[11].SetInt(139);
		sc.Input[12].Name="129";	sc.Input[12].SetInt(129);
		sc.Input[13].Name="119";	sc.Input[13].SetInt(119);
		sc.Input[14].Name="109";	sc.Input[14].SetInt(109);
		sc.Input[15].Name="99";		sc.Input[15].SetInt(99);
		sc.Input[16].Name="89";		sc.Input[16].SetInt(89);
		sc.Input[17].Name="55";		sc.Input[17].SetInt(55);
		sc.Input[18].Name="50";		sc.Input[18].SetInt(50);
		sc.Input[19].Name="45";		sc.Input[19].SetInt(45);
		sc.Input[20].Name="40";		sc.Input[20].SetInt(40);
		sc.Input[21].Name="35";		sc.Input[21].SetInt(35);
		sc.Input[22].Name="30";		sc.Input[22].SetInt(30);
		sc.Input[23].Name="25";		sc.Input[23].SetInt(25);
		sc.GraphRegion=0;
		return;
	}

	if(sc.UpdateStartIndex==0) {
		sc.FreeDLL=0; 
		sc.Subgraph[1].PrimaryColor=sc.Subgraph[0].PrimaryColor;	sc.Subgraph[2].PrimaryColor=sc.Subgraph[0].PrimaryColor;
		sc.Subgraph[3].PrimaryColor=sc.Subgraph[0].PrimaryColor;	sc.Subgraph[4].PrimaryColor=sc.Subgraph[0].PrimaryColor;
		sc.Subgraph[5].PrimaryColor=sc.Subgraph[0].PrimaryColor;	sc.Subgraph[6].PrimaryColor=sc.Subgraph[0].PrimaryColor;
		sc.Subgraph[8].PrimaryColor=sc.Subgraph[7].PrimaryColor;	sc.Subgraph[9].PrimaryColor=sc.Subgraph[7].PrimaryColor;
		sc.Subgraph[10].PrimaryColor=sc.Subgraph[7].PrimaryColor;	sc.Subgraph[11].PrimaryColor=sc.Subgraph[7].PrimaryColor;
		sc.Subgraph[12].PrimaryColor=sc.Subgraph[7].PrimaryColor;	sc.Subgraph[13].PrimaryColor=sc.Subgraph[7].PrimaryColor;

	}
	for (int i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[0], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[10].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[1], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[11].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[2], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[12].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[3], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[13].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[4], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[14].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[5], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[15].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[6], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[16].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[7], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[17].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[8], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[18].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[9], MOVAVGTYPE_EXPONENTIAL, i, sc.Input[19].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[10], MOVAVGTYPE_EXPONENTIAL, i,sc.Input[20].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[11], MOVAVGTYPE_EXPONENTIAL, i,sc.Input[21].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[12], MOVAVGTYPE_EXPONENTIAL, i,sc.Input[22].GetInt());
		sc.MovingAverage(sc.BaseDataIn[SC_LAST], sc.Subgraph[13], MOVAVGTYPE_EXPONENTIAL, i,sc.Input[23].GetInt());
	}
};



/***********************************************************************/
SCSFExport scsf_sTDI(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "TDI";
		sc.StudyDescription = "<p><strong>Traders Dynamic Index</strong></p><p>with thanks to Dean Malone <a href=http://www.compassfx.com>CompassFX</a></p><p><a href=http://www.earnforex.com/metatrader-indicators/Traders-Dynamic-Index>Earnforex description</a></p>";	

		sc.Subgraph[0].Name = "RSI";			sc.Subgraph[0].DrawStyle=5;  
		sc.Subgraph[1].Name = "UpVol";			sc.Subgraph[1].DrawStyle=0;
		sc.Subgraph[2].Name = "Mid";			sc.Subgraph[2].DrawStyle=0; 
		sc.Subgraph[3].Name = "DnVol";			sc.Subgraph[3].DrawStyle=0;	
		sc.Subgraph[4].Name = "Ma";				sc.Subgraph[4].DrawStyle=0;
		sc.Subgraph[5].Name = "Mb";				sc.Subgraph[5].DrawStyle=0;
		//sc.Subgraph[6].Name = "O1";				sc.Subgraph[6].DrawStyle=5;
		sc.Input[3].Name="RSI Length";					sc.Input[3].SetInt(13);		 	sc.Input[3].SetDescription("<strong>RSI_Period</strong> (default = 13) &#151; period in bars for calculation of RSI.");
		sc.Input[4].Name="RSI Price";					sc.Input[4].SetInputDataIndex(SC_LAST);	sc.Input[4].SetDescription("<strong>RSI_Price</strong> (default = MODE_CLOSE) &#151; price type to use in RSI calculation");
		sc.Input[5].Name="Volatility Band Length";		sc.Input[5].SetInt(34);		 	sc.Input[5].SetDescription("<strong>Volatility_Band</strong> (default = 34) &#151; parameter for  volatility band calculation. Can be between 20 and 40. The lower this value is the curvier becomes the band.");
		sc.Input[6].Name="RSI Price Line";				sc.Input[6].SetInt(2);		 	sc.Input[6].SetDescription("<strong>RSI_Price_Line</strong> (default = 2) &#151; period of the first moving average (fast).");
		sc.Input[7].Name="RSI Price Type";				sc.Input[7].SetMovAvgType(MOVAVGTYPE_SIMPLE);		 
		sc.Input[8].Name="RSI Trade Signal Line";		sc.Input[8].SetInt(7);		 	sc.Input[8].SetDescription("<strong>Trade_Signal_Line</strong> (default = 7) &#151; period of the second moving average (slow)");
		sc.Input[9].Name="Trade Signal Type";			sc.Input[9].SetMovAvgType(MOVAVGTYPE_SIMPLE);
		sc.DocumentationImageURL="http://codebase.mql4.com/c/codebase/2008/03/indicatori_gtradersmdynamicmindexuvisualqalerts.gif";
		//sc.UpdateAlways=1;
		return;
	} 	
	sc.FreeDLL=0;


	for (int i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		sc.RSI( sc.BaseDataIn[sc.Input[4].GetInputDataIndex()], sc.Subgraph[0], i, MOVAVGTYPE_SIMPLE, sc.Input[3].GetInt() );
		sc.MovingAverage( sc.Subgraph[0], sc.Subgraph[4], sc.Input[7].GetMovAvgType(), i, sc.Input[6].GetInt() );
		sc.MovingAverage( sc.Subgraph[0], sc.Subgraph[5], sc.Input[9].GetMovAvgType(), i, sc.Input[8].GetInt() );
		sc.BollingerBands (sc.Subgraph[0], sc.Subgraph[2], i, sc.Input[5].GetInt(), 1.6185, MOVAVGTYPE_SIMPLE);
		sc.Subgraph[1][i]=sc.Subgraph[2].Arrays[0][i];
		sc.Subgraph[3][i]=sc.Subgraph[2].Arrays[1][i];
	}
}




/*==========================================================================*/
SCSFExport _scsf_NMinBars(SCStudyGraphRef sc) {

	if (sc.SetDefaults)	{
		sc.GraphName="NMinBars";
		sc.StudyDescription="";
		sc.Subgraph[0].Name="H";
		sc.Subgraph[1].Name="L";	
		sc.Subgraph[2].Name="o2";		
		sc.Subgraph[3].Name="o3";			
		sc.Subgraph[4].Name="o4";				
		sc.Input[0].Name="Second Count";
		sc.Input[0].SetInt(300);		
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_FILLRECTTOP_TRANSPARENT;
		sc.Subgraph[1].DrawStyle = DRAWSTYLE_FILLRECTBOTTOM_TRANSPARENT;
		sc.Subgraph[0].PrimaryColor = sc.Subgraph[1].PrimaryColor = RGB(128,128,128);
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.GraphRegion = 0;
		sc.DrawZeros=0;
		return;
	}
	//sc.FreeDLL=0; 

	int  pos,m,s, as=sc.ArraySize - 1;
	float High, Low;
	int& secs = sc.Input[0].IntValue;
	int&  deeperRecalc =  sc.PersistVars->i1;	int&  deeperRecalcDepth =  sc.PersistVars->i2;	
	int isResetBar, prevFirstBarPos = sc.ArraySize;


	//sc.Subgraph[4][as] = 999+((sc.BaseDateTimeIn[as].GetTime() / secs) - (sc.BaseDateTimeIn[as - 1].GetTime() / secs));

	sc.CurrentSystemDateTime.GetTimeHMS(m,m,s);
	if( s > 4 && s < 13 && ((sc.BaseDateTimeIn[as].GetTime() / secs) > (sc.BaseDateTimeIn[as - 1].GetTime() / secs))) {	
		deeperRecalc=1;	
		deeperRecalcDepth = as-2*secs/sc.SecondsPerBar;	
		sc.ScaleRangeType = SCALE_SAMEASREGION;
	} else {
		deeperRecalc=0;	
	}

	for (pos = (as); (pos >= 0) && 
		(prevFirstBarPos > sc.UpdateStartIndex || (deeperRecalc>0 && pos>=deeperRecalcDepth)); pos--) {
			isResetBar = prevFirstBarPos == (pos + 1);
			High = (isResetBar || (sc.High[pos] > High)) ? sc.High[pos] : High;
			Low = (isResetBar || (sc.Low[pos] < Low)) ? sc.Low[pos] : Low;

			if ((pos == 0) || 
				((sc.BaseDateTimeIn[pos].GetTime() / secs) > (sc.BaseDateTimeIn[pos - 1].GetTime() / secs)) || 
				(sc.BaseDateTimeIn[pos].GetDate() > sc.BaseDateTimeIn[pos - 1].GetDate())) {

					for (int i = pos; i < prevFirstBarPos; i++) {
						sc.Subgraph[0][i] = High;
						sc.Subgraph[1][i] = Low;
					}
					prevFirstBarPos = pos;
			}
			//if(deeperRecalc>0 && pos<as) { sc.Subgraph[4][pos]=pos; sc.Subgraph[4][pos-1]=pos;}
	}	
};





/*==========================================================================*/

SCSFExport _scsf_TradingOnOff(SCStudyGraphRef sc)
{
	SCSubgraphRef o0 = sc.Subgraph[0]; SCSubgraphRef o2 =	sc.Subgraph[2]; SCSubgraphRef o1 = sc.Subgraph[1]; SCSubgraphRef o3 =	sc.Subgraph[3]; SCSubgraphRef o4 =	sc.Subgraph[4];		SCSubgraphRef o5 =	sc.Subgraph[5];	
	SCSubgraphRef OrderStore = sc.Subgraph[10]; SCSubgraphRef PositionStore = sc.Subgraph[11]; SCSubgraphRef ALERT = sc.Subgraph[12]; SCSubgraphRef Cmd = sc.Subgraph[13];
	SCSubgraphRef arF =	sc.Subgraph[17]; SCSubgraphRef arS =	sc.Subgraph[18]; SCSubgraphRef arVS = sc.Subgraph[19]; SCSubgraphRef M5SIH = sc.Subgraph[8]; SCSubgraphRef M5SIL = sc.Subgraph[9];

	if (sc.SetDefaults)
	{
		sc.GraphName="TradingOnOff";
		sc.StudyDescription="Turn live trading on or off";
		sc.Subgraph[0].Name="Cmd";	
		sc.Subgraph[1].Name="SendOrders";	
		sc.Subgraph[2].Name="GlobalTradeSim";	
		sc.TextInputName="Symbol to Trade";		sc.TextInput="C:\\SierraChart\\TurnTradingOnOff.txt";
		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.GraphRegion=0;
		sc.UpdateAlways=1;
		sc.FreeDLL=0;	
		return;
	}



	//	int const EnType=0, EnTrail=1, EnStpLmt=2, ExType=3, ExTrail=4, ExStpLmt=5;
	//	int const doNothing=1, doBuyNow=2, doBuy=3, doSellNow=4, doSell=5, TrailBar=6, bePlus=7, killAll=9;	
	FILE * pFile;   char filetxt[14]="";  char errormessage[40]="";	int cmdchk=0;
	pFile = fopen (sc.TextInput,"r");
	if (pFile!=NULL) {
		long lSize;   char out[1];	out[1]=0;		fseek (pFile , 0 , SEEK_END);
		lSize = ftell (pFile);						rewind (pFile);
		fread (filetxt,1,lSize,pFile);				fclose (pFile);

		out[0] = filetxt[0]; int command = atoi(out);
		sc.Subgraph[0][sc.ArraySize-1] = command;
		if(command == 2) { sc.SendOrdersToTradeService=1;   sc.GlobalTradeSimulationIsOn=0; }
		else  { sc.SendOrdersToTradeService=0;   sc.GlobalTradeSimulationIsOn=1; }
		sc.Subgraph[1][sc.ArraySize-1] = sc.SendOrdersToTradeService; 
		sc.Subgraph[2][sc.ArraySize-1] = sc.GlobalTradeSimulationIsOn;

		//		bool carryon=true;	char M5break[5], M5start[5]; M5break[5]=0; M5start[5]=0;
		//		for(j=0;j<3;j++) { out[0]=filetxt[j]; if(atoi(out)<10) {Cmd[j]=atoi(out);} cmdchk=cmdchk+(j+1)*Cmd[j]; }  //if(atoi(out)<10) {Cmd[j]=atoi(out);} 
		//		M5break[0]=filetxt[3]; M5break[1]=filetxt[4]; M5break[2]=filetxt[5];  M5break[3]=filetxt[6];  M5break[4]=filetxt[7];
		//		M5start[0]=filetxt[8]; M5start[1]=filetxt[9]; M5start[2]=filetxt[10]; M5start[3]=filetxt[11]; M5start[4]=filetxt[12];
		//		float temp=atoi(M5break);	if(fabs(temp-DIn[cx][as])<190) iBreak=temp;
		//			  temp=atoi(M5start);	if(fabs(temp-DIn[cx][as])<190) iStart=temp; 
	}


}



/***********************************************************************/
SCSFExport _scsf_DayBeforeCandle(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName = "Less One Day";
		sc.StudyDescription = " ";
		sc.IsCustomChart = 1;  // true		
		sc.GraphRegion = 0;  // First region		
		sc.DrawZeros = 0;  // false		
		sc.GraphDrawType = GDT_CANDLESTICK;  // true
		sc.StandardChartHeader = 1; // true
		sc.Subgraph[0].Name = "Up Color";
		sc.Subgraph[1].Name = "Dn Color";
		sc.Subgraph[2].Name = "Low";
		sc.Subgraph[3].Name = "Doji (O-C) color";
		sc.Subgraph[4].Name = "Volume";
		sc.Subgraph[5].Name = "Ticks";
		sc.Input[5].Name="Offset to start new direction";
		sc.Input[6].Name="Intraday Chart";		sc.Input[6].SetInt(5);
		sc.CalculationPrecedence = VERY_LOW_PREC_LEVEL;
		sc.FreeDLL=0;
		return;
	} 

	int& Count  = sc.PersistVars->i1; 
	int    updown=1,os;
	float  highestlow=0.0,lowesthigh=999999.9;	

	if (sc.UpdateStartIndex == 0)
	{
		sc.ResizeArrays(0);
	}


	for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		if (sc.OutArraySize - 1 < i)
			sc.AddElements(1);
		sc.DateTimeOut[i].SetTime(sc.BaseDateTimeIn[i].GetTime());
		sc.DateTimeOut[i].SetDate(sc.BaseDateTimeIn[i].GetDate()-1);
		sc.Subgraph[0][i] = sc.BaseDataIn[0][i];
		sc.Subgraph[1][i] = sc.BaseDataIn[1][i];
		sc.Subgraph[2][i] = sc.BaseDataIn[2][i];
		sc.Subgraph[3][i] = sc.BaseDataIn[3][i];
		sc.Subgraph[4][i] = sc.BaseDataIn[4][i];

		int pos=i;  float& offset= sc.Input[5].FloatValue;
		int upcol = sc.Subgraph[0].PrimaryColor, dncol = sc.Subgraph[1].PrimaryColor, 
			oscol = sc.Subgraph[2].PrimaryColor, wkcol = sc.Subgraph[3].PrimaryColor;


		os=0;

		//if((sc.BaseDataIn[1][pos]<sc.BaseDataIn[1][pos-1] && sc.BaseDataIn[2][pos]>=sc.BaseDataIn[2][pos-1]) ||
		//	(sc.BaseDataIn[1][pos]<=sc.BaseDataIn[1][pos-1] && sc.BaseDataIn[2][pos]>sc.BaseDataIn[2][pos-1]) )  {os=1;};


		if(sc.BaseDataIn[3][pos]>sc.BaseDataIn[0][pos])
		{ sc.Subgraph[0].DataColor[pos] = upcol; sc.Subgraph[1].DataColor[pos] = upcol;
		sc.Subgraph[2].DataColor[pos] = upcol; sc.Subgraph[3].DataColor[pos] = upcol;
		} else 
			if(sc.BaseDataIn[0][pos]>sc.BaseDataIn[3][pos])
			{ sc.Subgraph[0].DataColor[pos] = dncol; sc.Subgraph[1].DataColor[pos] = dncol;
		sc.Subgraph[2].DataColor[pos] = dncol; sc.Subgraph[3].DataColor[pos] = dncol;
		} else
			{ sc.Subgraph[0].DataColor[pos] = wkcol; sc.Subgraph[1].DataColor[pos] = wkcol;
		sc.Subgraph[2].DataColor[pos] = wkcol; sc.Subgraph[3].DataColor[pos] = wkcol;
		}


	}


	SCFloatArray LastHigh, LastLow;
	sc.GetChartArray(sc.Input[6].GetInt(),1,LastHigh);
	sc.GetChartArray(sc.Input[6].GetInt(),2,LastLow);
	int i=sc.ArraySize-1;
	int j = LastLow.GetArraySize();
	if( j!=0 && LastLow[j-1]!=0 ) {
		sc.Subgraph[1][i] = LastHigh[j-1];
		sc.Subgraph[2][i] = LastLow[j-1];
	}
	//sc.Subgraph[4][i]=sc.BaseDateTimeIn[i].GetDate();
	//sc.Subgraph[5][i]=LastBar[0];

}




/***********************************************************************/
SCSFExport scsf_VC(SCStudyGraphRef sc)
{
	if (sc.SetDefaults)
	{
		sc.GraphName="VC";
		sc.StudyDescription="Stendahl's Value Chart";
		sc.Subgraph[4].Name="H and up colour";	sc.Subgraph[4].DrawStyle = DRAWSTYLE_BARTOP;
		sc.Subgraph[5].Name="L and dn colour";	sc.Subgraph[5].DrawStyle = DRAWSTYLE_BARBOTTOM;	
		sc.Subgraph[0].Name="T1";	sc.Subgraph[0].DrawStyle = DRAWSTYLE_FILLTOP;
		sc.Subgraph[1].Name="T2";	sc.Subgraph[1].DrawStyle = DRAWSTYLE_FILLBOTTOM;	
		sc.Subgraph[2].Name="B2";	sc.Subgraph[2].DrawStyle = DRAWSTYLE_FILLTOP;
		sc.Subgraph[3].Name="B1 & neutral colour for bars";	sc.Subgraph[3].DrawStyle = DRAWSTYLE_FILLBOTTOM;

		sc.Input[5].Name="Top Line";			sc.Input[5].SetInt(8);
		sc.Input[6].Name="T2  Line";			sc.Input[6].SetInt(4);
		sc.Input[7].Name="B2  Line";			sc.Input[7].SetInt(-4);
		sc.Input[8].Name="Bottome Line";        sc.Input[8].SetInt(-8);
		// sc.FreeDLL=0; 
		return;
	}

	int& bars1 = sc.Input[2].IntValue; int& bars2 = sc.Input[3].IntValue; 
	SCSubgraphRef 	AR = sc.Subgraph[7], ARz = sc.Subgraph[6], AM = sc.Subgraph[9], AMz = sc.Subgraph[8],
		RelativeHi = sc.Subgraph[10], RelativeLo = sc.Subgraph[11], ValueHi = sc.Subgraph[12], ValueLo = sc.Subgraph[13],
		VolatilityUnit = sc.Subgraph[14];
	SCSubgraphRef 	oH = sc.Subgraph[4], oL = sc.Subgraph[5], op8=sc.Subgraph[0] , op4=sc.Subgraph[1], om4=sc.Subgraph[2], om8=sc.Subgraph[3];

	for ( int i=sc.UpdateStartIndex; i < sc.ArraySize; i++)
	{
		ARz[i]=sc.BaseDataIn[SC_HIGH][i-1]-sc.BaseDataIn[SC_LOW][i-1];
		sc.MovingAverage(ARz, AR, MOVAVGTYPE_SIMPLE, i, 5);  
		AMz[i]=(sc.BaseDataIn[SC_HIGH][i-1]+sc.BaseDataIn[SC_LOW][i-1])/2;
		sc.MovingAverage(AMz, AM, MOVAVGTYPE_SIMPLE, i, 5);  

		VolatilityUnit[i] = AR[i] * 0.2;
		RelativeHi[i] = sc.BaseDataIn[SC_HIGH][i] - AM[i];
		RelativeLo[i] = sc.BaseDataIn[SC_LOW][i] - AM[i];
		ValueHi[i] = RelativeHi[i]/VolatilityUnit[i];
		ValueLo[i] = RelativeLo[i]/VolatilityUnit[i];

		oH[i] = min(12,max(-11.8,ValueHi[i]));
		oL[i] = min(11.8,max(-12,ValueLo[i]));
		op8[i] = sc.Input[5].IntValue;
		op4[i] = sc.Input[6].IntValue;
		om4[i] = sc.Input[7].IntValue;
		om8[i] = sc.Input[8].IntValue;

		if(oH[i]>=op8[i]) oH.DataColor[i]=oH.PrimaryColor; else
			if(oL[i]<=om8[i]) oH.DataColor[i]=oL.PrimaryColor; else
				if(oH[i]>=op4[i] && oL[i]>om4[i]) oH.DataColor[i]=oH.PrimaryColor; else
					if(oL[i]<=om4[i] && oH[i]<op4[i]) oH.DataColor[i]=oL.PrimaryColor; else
						oH.DataColor[i]=om8.PrimaryColor;
	}

}



/*==========================================================================*/
SCSFExport scsf_TrueLive_2014(SCStudyInterfaceRef sc) 
{

	SCFloatArray&   O = sc.BaseDataIn[0], H = sc.BaseDataIn[1], 
		L = sc.BaseDataIn[2], C = sc.BaseDataIn[3],
		V = sc.BaseDataIn[4], T = sc.BaseDataIn[5];
	SCSubgraphRef   oO = sc.Subgraph[0], oH = sc.Subgraph[1], 
		oL = sc.Subgraph[2], oC = sc.Subgraph[3],
		oV = sc.Subgraph[4], oT = sc.Subgraph[5];
	SCSubgraphRef   o = sc.Subgraph[10], h = sc.Subgraph[11], 
		l = sc.Subgraph[12], c = sc.Subgraph[13],
		v = sc.Subgraph[14], t = sc.Subgraph[15], 
		o2 = sc.Subgraph[22], o3 = sc.Subgraph[23], 
		o4 = sc.Subgraph[24], o5 = sc.Subgraph[25]; 

	if (sc.SetDefaults) {
		sc.GraphName = "TrueLive 2014";
		sc.StudyDescription = "True Live using Custom Chart 2014 Release";
		sc.Subgraph[0].Name = "Open";       
		sc.Subgraph[1].Name = "High";
		sc.Subgraph[2].Name = "Low";        
		sc.Subgraph[3].Name = "Last";
		sc.Subgraph[4].Name = "Volume";     
		sc.Subgraph[5].Name = "# of Trades";
		sc.Subgraph[6].Name = "HL";
		sc.Subgraph[7].Name = "HLC";
		sc.Subgraph[8].Name = "OHLC";
		o2.Name="o2";  o3.Name="o3";  
		o4.Name="o4";   o5.Name="o5";
		sc.GraphRegion = 0;  // First region
		sc.GraphDrawType = GDT_CANDLESTICK;
		sc.DisplayAsMainPriceGraph=1;
		sc.IsCustomChart = 1;
		sc.UpdateAlways=1;
		sc.DrawZeros=0;
		sc.FreeDLL = 0;
		return;
	}


	int as = sc.ArraySize-1;
	int ap = as - 1;
	int& seqno  = sc.PersistVars->i1;
	int& tnsno  = sc.PersistVars->i2;
	SCTimeAndSalesArray TSArray;
	sc.GetTimeAndSales(TSArray);
	int ts = TSArray.GetArraySize() - 1;

	if (sc.UpdateStartIndex == 0) {
		int os = 0;  // os stores the position of the out array
		tnsno = seqno = 0;
		if (ts >= 0) 
			seqno = TSArray[ts].Sequence; 
		sc.ResizeArrays(0);
		for ( ; os < sc.ArraySize; os++) {
			sc.AddElements(1);
			sc.DateTimeOut[os] = sc.BaseDateTimeIn[os];
			oO[os] = O[os];      
			oH[os] = H[os];
			oL[os] = L[os];       
			oC[os] = C[os];
			oV[os] = V[os];        
			oT[os] = T[os];
			sc.Subgraph[SC_HL][os] = (oH[os] + oL[os]) / 2;
			sc.Subgraph[SC_HLC][os]  = (oH[os] + oL[os] + oC[os]) / 3;
			sc.Subgraph[SC_OHLC][os] = (oH[os] + oL[os] + oC[os] + oO[os]) / 4;
		}
	}

	// First deal with underlying data
	int os = sc.OutArraySize-1;
	// add an extra bar if the underlying is later than the output bar
	if( sc.BaseDateTimeIn[as] > sc.DateTimeOut[os] ) {
		// only add element if there isn't a spurious t&s element present
		if(tnsno == 0) os++;  
		sc.AddElements(1);
		sc.DateTimeOut[os] = sc.BaseDateTimeIn[as];
		oO[os] = oH[os] = oL[os] = oC[os] = O[as];
	}
	int op = os - 1;
	if (sc.DateTimeOut[os] == sc.BaseDateTimeIn[as]) {
		// Only apply 5 second data if its changed (ie dont reset live changes)
		if(c[os] != C[as] || v[os] != V[as] || h[os] != H[as] || l[os] != L[as])
		{
			tnsno = 0;
			h[os] = H[as];   l[os] = L[as];    
			c[os] = C[as];   v[os] = V[as];
			// update this bar
			oO[os] = O[as];  oH[os] = H[as];
			oL[os] = L[as];  // oC[os] = C[as];
			oV[os] = V[as];  oT[os] = T[as];
			// match prior bar to 5 second data
			oO[op] = O[ap];  oH[op] = H[ap];
			oL[op] = L[ap];  oC[op] = C[ap];
			oV[op] = V[ap];  oT[op] = T[ap];
		}
	} 
	else if (sc.DateTimeOut[op] == sc.BaseDateTimeIn[as]) {
		// must be in first 5 seconds of new bar so
		// update prior bar with 5 second data
		oO[op] = O[as];  
		oH[op] = max(H[as], oH[op]);
		oL[op] = min(L[as], oL[op]);
		if (sc.CurrentSystemDateTime.GetTime() > 
			sc.BaseDateTimeIn[as].GetTime() + sc.SecondsPerBar + 15) { 
				oC[op] = C[as];
		}
		oV[op] = V[as];  oT[op] = T[as];
	}

	// then look at live data
	if (ts >= 0 && TSArray[ts].Sequence > seqno) {
		int tp = ts;
		int adjt = sc.TimeScaleAdjustment.GetTime();
		double adj = sc.TimeScaleAdjustment;
		while (TSArray[tp].Sequence > seqno) {tp--;}
		// iterate through each time & sales value
		for ( ; tp <= ts; tp++) {
			// if its a new bar start one
			if (tnsno == 0 && TSArray[tp].DateTime.GetTime() + adjt >=
				sc.DateTimeOut[os].GetTime() + sc.SecondsPerBar) { 
					tnsno = 1;  // flag that a time&sales bar has been created
					os++;  
					sc.AddElements(1);
					sc.DateTimeOut[os].SetDate(sc.DateTimeOut[as].GetDate());
					sc.DateTimeOut[os].SetTime(sc.DateTimeOut[as].GetTime() +
						sc.SecondsPerBar);
					// note that for new session this bar time is wrong
					// and it will be cancelled as spurious so the new bar
					// will be formed when the first 5 sec bar arrives
					oO[os] = oH[os] = oL[os] = oC[os] = TSArray[tp].Price;
					oV[os] = TSArray[tp].Volume;
			}
			// else update high low and close for this bar
			else if (TSArray[tp].DateTime.GetTime() + adjt >= 
				sc.DateTimeOut[os].GetTime() &&
				TSArray[tp].DateTime.GetTime() + adjt <
				sc.DateTimeOut[os].GetTime() + sc.SecondsPerBar) {
					oH[os] = max(TSArray[tp].Price, oH[os]);
					if (TSArray[tp].Price > 0 && oL[os] > 0) 
						oL[os] = min(TSArray[tp].Price, oL[os]);
					else
						oL[os] = max(TSArray[tp].Price, oL[os]);
					oC[os] = TSArray[tp].Price;
			}
		}
		seqno = TSArray[ts].Sequence;
	}
	// Check for spurious time & sales based bars (> 10 seconds with no 5sec)
	if(tnsno != 0) {
		// spurious if no 5 second confirmation within 15 seconds
		if(sc.CurrentSystemDateTime.GetDate() > sc.DateTimeOut[os].GetDate() ||
			sc.CurrentSystemDateTime.GetTime() > sc.DateTimeOut[os].GetTime()
			+ 15) {
				sc.AddElements(-1);
				tnsno = 0;
		}
	}

	sc.Subgraph[SC_HL][os]   = (oH[os] + oL[os]) / 2;
	sc.Subgraph[SC_HLC][os]  = (oH[os] + oL[os] + oC[os]) / 3;
	sc.Subgraph[SC_OHLC][os] = (oH[os] + oL[os] + oC[os] + oO[os]) / 4;
	sc.Subgraph[SC_HL][op]   = (oH[op] + oL[op]) / 2;
	sc.Subgraph[SC_HLC][op]  = (oH[op] + oL[op] + oC[op]) / 3;
	sc.Subgraph[SC_OHLC][op] = (oH[op] + oL[op] + oC[op] + oO[op]) / 4;
}


/*==========================================================================*/
SCSFExport scsf_TrueLive_2014pvm(SCStudyInterfaceRef sc) {

	SCFloatArray&   O = sc.BaseDataIn[0], H = sc.BaseDataIn[1], 
		L = sc.BaseDataIn[2], C = sc.BaseDataIn[3],
		V = sc.BaseDataIn[4], T = sc.BaseDataIn[5];
	SCSubgraphRef   oO = sc.Subgraph[0], oH = sc.Subgraph[1], 
		oL = sc.Subgraph[2], oC = sc.Subgraph[3],
		oV = sc.Subgraph[4], oT = sc.Subgraph[5];
	SCSubgraphRef   o = sc.Subgraph[10], h = sc.Subgraph[11], 
		l = sc.Subgraph[12], c = sc.Subgraph[13],
		v = sc.Subgraph[14], t = sc.Subgraph[15], 
		o2 = sc.Subgraph[22], o3 = sc.Subgraph[23], 
		o4 = sc.Subgraph[24], o5 = sc.Subgraph[25]; 

	if (sc.SetDefaults) {
		sc.GraphName = "TrueLive 2014 pvm";
		sc.StudyDescription = "True Live using Custom Chart 2014 Release with PriceVol Multipliers";
		sc.Subgraph[0].Name = "Open";       
		sc.Subgraph[1].Name = "High";
		sc.Subgraph[2].Name = "Low";        
		sc.Subgraph[3].Name = "Last";
		sc.Subgraph[4].Name = "Volume";     
		sc.Subgraph[5].Name = "# of Trades";
		sc.Subgraph[6].Name = "HL";
		sc.Subgraph[7].Name = "HLC";
		sc.Subgraph[8].Name = "OHLC";
		o2.Name="o2";  o3.Name="o3";  o4.Name="o4";   o5.Name="o5";
		sc.GraphRegion = 0;  // First region
		sc.GraphDrawType = GDT_CANDLESTICK;
		sc.DisplayAsMainPriceGraph=1;
		sc.IsCustomChart = 1;
		sc.UpdateAlways=1;
		sc.DrawZeros=0;
		sc.FreeDLL =  0;
		return;
	}


	int as = sc.ArraySize-1;
	int ap = as - 1;
	int& seqno  = sc.PersistVars->i1;
	int& tnsno  = sc.PersistVars->i2;
	SCTimeAndSalesArray TSArray;
	sc.GetTimeAndSales(TSArray);
	int ts = TSArray.GetArraySize() - 1;

	if (sc.UpdateStartIndex == 0) {
		int os = 0;  // os stores the position of the out array
		tnsno = seqno = 0;
		if (ts >= 0) 
			seqno = TSArray[ts].Sequence; 
		sc.ResizeArrays(0);
		for ( ; os < sc.ArraySize; os++) {
			sc.AddElements(1);
			sc.DateTimeOut[os] = sc.BaseDateTimeIn[os];
			oO[os] = O[os];      
			oH[os] = H[os];
			oL[os] = L[os];       
			oC[os] = C[os];
			oV[os] = V[os];        
			oT[os] = T[os];
			sc.Subgraph[SC_HL][os] = (oH[os] + oL[os]) / 2;
			sc.Subgraph[SC_HLC][os]  = (oH[os] + oL[os] + oC[os]) / 3;
			sc.Subgraph[SC_OHLC][os] = (oH[os] + oL[os] + oC[os] + oO[os]) / 4;
		}
	}


	// First deal with underlying data
	int os = sc.OutArraySize-1;
	// add an extra bar if the underlying is later than the output bar
	if( sc.BaseDateTimeIn[as] > sc.DateTimeOut[os] ) {
		// only add element if there isn't a spurious t&s element present
		if(tnsno == 0) os++;  
		sc.AddElements(1);
		sc.DateTimeOut[os] = sc.BaseDateTimeIn[as];
		oO[os] = oH[os] = oL[os] = oC[os] = O[as];
	}
	int op = os - 1;
	if (sc.DateTimeOut[os] == sc.BaseDateTimeIn[as]) {
		// Only apply 5 second data if its changed (ie, dont reset live changes)
		if(c[os] != C[as] || v[os] != V[as] || h[os] != H[as] || l[os] != L[as])
		{
			tnsno = 0;
			h[os] = H[as];   l[os] = L[as];    
			c[os] = C[as];   v[os] = V[as];
			// update this bar
			oO[os] = O[as];  oH[os] = H[as];
			oL[os] = L[as];  // oC[os] = C[as];
			oV[os] = V[as];  oT[os] = T[as];
			// match prior bar to 5 second data
			oO[op] = O[ap];  oH[op] = H[ap];
			oL[op] = L[ap];  oC[op] = C[ap];
			oV[op] = V[ap];  oT[op] = T[ap];
		}
	} 
	else if (sc.DateTimeOut[op] == sc.BaseDateTimeIn[as]) {
		// must be in first 5 seconds of new bar so
		// update prior bar with 5 second data
		oO[op] = O[as];  
		oH[op] = max(H[as], oH[op]);
		oL[op] = min(L[as], oL[op]);
		if (sc.CurrentSystemDateTime.GetTime() > 
			sc.BaseDateTimeIn[as].GetTime() + sc.SecondsPerBar + 15) { 
				oC[op] = C[as];
		}
		oV[op] = V[as];  oT[op] = T[as];
	}

	// then look at live data
	if (ts >= 0 && TSArray[ts].Sequence > seqno) {
		int tp = ts;
		int adjt = sc.TimeScaleAdjustment.GetTime();
		double adj = sc.TimeScaleAdjustment;
		while (TSArray[tp].Sequence > seqno) {tp--;}
		// iterate through each time & sales value
		for ( ; tp <= ts; tp++) {
			// if its a new bar start one
			if (tnsno == 0 && TSArray[tp].DateTime.GetTime() + adjt >=
				sc.DateTimeOut[os].GetTime() + sc.SecondsPerBar) { 
					tnsno = 1;  // flag that a time&sales bar has been created
					os++;  
					sc.AddElements(1);
					sc.DateTimeOut[os].SetDate(sc.DateTimeOut[as].GetDate());
					sc.DateTimeOut[os].SetTime(sc.DateTimeOut[as].GetTime() +
						sc.SecondsPerBar);
					// note that for new session this bar time is wrong
					// and it will be cancelled as spurious so the new bar
					// will be formed when the first 5 sec bar arrives
					oO[os] = oH[os] = oL[os] = oC[os] = TSArray[tp].Price * sc.RealTimePriceMultiplier;
					oV[os] = TSArray[tp].Volume * sc.MultiplierFromVolumeValueFormat();
			}
			// else update high low and close for this bar
			else if (TSArray[tp].DateTime.GetTime() + adjt >= 
				sc.DateTimeOut[os].GetTime() &&
				TSArray[tp].DateTime.GetTime() + adjt <
				sc.DateTimeOut[os].GetTime() + sc.SecondsPerBar) {
					oH[os] = max(TSArray[tp].Price * sc.RealTimePriceMultiplier, oH[os]);
					if (TSArray[tp].Price > 0 && oL[os] > 0) 
						oL[os] = min(TSArray[tp].Price * sc.RealTimePriceMultiplier, oL[os]);
					else
						oL[os] = max(TSArray[tp].Price * sc.RealTimePriceMultiplier, oL[os]);
					oC[os] = TSArray[tp].Price * sc.RealTimePriceMultiplier;
			}
		}
		seqno = TSArray[ts].Sequence;
	}
	// Check for spurious time & sales based bars (> 10 seconds with no 5sec)
	if(tnsno != 0) {
		// spurious if no 5 second confirmation within 15 seconds
		if(sc.CurrentSystemDateTime.GetDate() > sc.DateTimeOut[os].GetDate() ||
			sc.CurrentSystemDateTime.GetTime() > sc.DateTimeOut[os].GetTime()
			+ 15) {
				sc.AddElements(-1);
				tnsno = 0;
		}
	}

	sc.Subgraph[SC_HL][os]   = (oH[os] + oL[os]) / 2;
	sc.Subgraph[SC_HLC][os]  = (oH[os] + oL[os] + oC[os]) / 3;
	sc.Subgraph[SC_OHLC][os] = (oH[os] + oL[os] + oC[os] + oO[os]) / 4;
	sc.Subgraph[SC_HL][op]   = (oH[op] + oL[op]) / 2;
	sc.Subgraph[SC_HLC][op]  = (oH[op] + oL[op] + oC[op]) / 3;
	sc.Subgraph[SC_OHLC][op] = (oH[op] + oL[op] + oC[op] + oO[op]) / 4;
}

