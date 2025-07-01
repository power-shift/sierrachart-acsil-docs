// The top of every source code file must include this line
#include <math.h>
#include "sierrachart.h"

//SCDLLName("ehlEhlersButterworth") 


SCSFExport scsf_3poleButterworth(SCStudyInterfaceRef sc)
{
// Reference the Plots and the inputs
	SCSubgraphRef 	ButterLine			= sc.Subgraph[0];
	
	SCInputRef 		Period				= sc.Input[0];
	SCInputRef 		Price				= sc.Input[1];
	SCInputRef 		ynEHL				= sc.Input[2];
	
	if (sc.SetDefaults)
	{
	// Section 1 - Set the configuration variables and defaults
		sc.GraphName 					= "Ehlers 3 pole Butterworth"; // Name in study overview
		sc.StudyDescription 			= "3 pole Butterworth Filter based on Ehlers";		
				
		sc.GraphRegion 					= 0;  // Set the Chart Region to draw the graph in.  Region 0 is the main price graph region.
		sc.FreeDLL 						= 0;  
		sc.AutoLoop 					= 1;  //Auto looping is enabled. 
		
	// Reference the Plots and the inputs and define them
		ButterLine.Name 				= "3 pole Butterworth";
		ButterLine.DrawStyle 			= DRAWSTYLE_LINE;  // Look in scconstants.h for other draw styles
		ButterLine.PrimaryColor 		= RGB(0,128,255);
		ButterLine.LineWidth 			= 2;
		
		Period.Name						= "Period";
		Period.SetInt(11);
		Period.SetIntLimits(1, INT_MAX);
		
		Price.Name 						= "Price";
		Price.SetInputDataIndex(SC_HL);

		ynEHL.Name						= "show EHL version"; // almost same as Supersmoother filter
		ynEHL.SetYesNo(1);
		ynEHL.SetIntLimits(1, INT_MAX);
		
		return;
	}
	// Section 2 - Do data processing here
		float a1, b1, c1, coef1, coef2, coef3, coef4;
	
		a1 = exp( (-3.14159) / (Period.GetInt()) );
		
		if (ynEHL.GetYesNo()) b1 = 2 * a1 * cos(1.738 * 180 / (Period.GetInt())); //ehl version like Supersmoother
		else b1 = 2 * a1 * cos(1.738 * (180 * 3.14159 / 180) / Period.GetInt()); //Ehlers original
				
		c1 = a1 * a1;
		coef2 = b1 + c1;
		coef3 = -(c1 + b1 * c1);
		coef4 = c1 * c1;
		coef1 = (1 - b1 + c1) * (1 - c1) / 8;
	
		float p0, p1, p2, p3;
	// alternative sc.BaseDataIn[SC_LAST][sc.Index]
	// sc.BaseData[SC_LAST] or sc.Close[]: The array of closing/last prices for each bar.
		p0 = sc.BaseData[Price.GetInputDataIndex()][sc.Index]; 
		p1 = sc.BaseData[Price.GetInputDataIndex()][sc.Index-1]; 
		p2 = sc.BaseData[Price.GetInputDataIndex()][sc.Index-2];
		p3 = sc.BaseData[Price.GetInputDataIndex()][sc.Index-3];
	
		if ( sc.Index < 4 ) ButterLine[sc.Index] = p0;
		else ButterLine[sc.Index] = coef1 * (p0 + 3*p1 + 3*p2 + p3) + coef2*ButterLine[sc.Index-1] + coef3*ButterLine[sc.Index-2] + coef4*ButterLine[sc.Index-3];
		
}



