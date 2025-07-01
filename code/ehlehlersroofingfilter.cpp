// The top of every source code file must include this line
#include <math.h>
#include "sierrachart.h"

//SCDLLName("ehlEhlersRoofingFilter") 


SCSFExport scsf_RoofingFilter(SCStudyInterfaceRef sc)
{
	// Reference the Plots and the inputs
	SCSubgraphRef 	Roofing		= sc.Subgraph[0];
	SCSubgraphRef 	Null		= sc.Subgraph[1];
		
	SCInputRef 		LPPeriod	= sc.Input[0];
	SCInputRef 		Bars		= sc.Input[1];
		
	SCFloatArrayRef HP  		= Roofing.Arrays[0]; 
		
	if (sc.SetDefaults)
	{
	// Section 1 - Set the configuration variables and defaults
		sc.GraphName 			= "Ehlers Roofing Filter"; // Name in study overview
		sc.StudyDescription 	= "Roofing Filter from TASC Magazine Jan 2014";		
				
		//sc.GraphRegion 		= 1;	// Set the Chart Region to draw the graph in.  Region 0 is the main price graph
		sc.FreeDLL 				= 0;	

		sc.AutoLoop 			= 1;	//Auto looping is enabled. 
		sc.ValueFormat 			= 2;
		sc.ScaleRangeType		= SCALE_AUTO;
		
	// Reference the Plots and the inputs and define them
		Roofing.Name 			= "Roofing filter";
		Roofing.DrawStyle 		= DRAWSTYLE_LINE;		// Look in scconstants.h for other draw styles
		Roofing.PrimaryColor 	= RGB(0,128,0);			// Nice Green	
		Roofing.LineWidth 		= 2;
		
		Null.Name 				= "Null";
		Null.DrawStyle 			= DRAWSTYLE_LINE;
		Null.PrimaryColor 		= RGB(128,128,128);
		Null.LineWidth 			= 1;
		Null.DrawZeros 			= 1;

		LPPeriod.Name			= "Period";
		LPPeriod.SetInt(10);
		LPPeriod.SetIntLimits(1, INT_MAX);
		
		Bars.Name = "Highpass filter < 48 bars";  //Highpass filter cyclic components whose periods are shorter than ... bars (100)
		Bars.SetInt(48);
		Bars.SetIntLimits(1, INT_MAX);
		
		return;
	}
	// Section 2 - Do data processing here
		float alpha1, a1, b1, c1, c2, c3, X;
				
	//Highpass filter cyclic components whose periods are shorter than ... bars (100)
		float tr, fi;
		tr = 360 * 3.14159f / 180;
		fi = 0.707f * tr / Bars.GetInt();
		alpha1 = (cos(fi) + sin(fi) - 1) / cos(fi);
		
		HP[sc.Index] = (1 - alpha1 / 2) * (1 - alpha1 / 2) * (sc.BaseDataIn[SC_LAST][sc.Index] - 2 * sc.BaseDataIn[SC_LAST][sc.Index - 1] +
			sc.BaseDataIn[SC_LAST][sc.Index - 2]) + 2 * (1 - alpha1) * HP[sc.Index - 1] - (1 - alpha1) * (1 - alpha1) * HP[sc.Index - 2];
					
	//SuperSmoother Filter
		a1 = exp((-1.414f) * 3.14159f / LPPeriod.GetInt());
		b1 = 2 * a1 * cos(1.414f * (180 * 3.14159f / 180) / LPPeriod.GetInt());
		c2 = b1;
		c3 = (-1)*a1*a1;
		c1 = 1 - c2 - c3;

	//Plot
		Roofing[sc.Index] = c1*(HP[sc.Index] + HP[sc.Index - 1]) / 2 + c2*Roofing[sc.Index - 1] + c3*Roofing[sc.Index - 2];
		Null[sc.Index]	= 0;

}





