// The top of every source code file must include this line
#include <math.h>
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// This line is required. Change the text within the quote
// marks to what you want to name your group of custom studies. 
//SCDLLName("ehlEarlyOnsetTrend") 


SCSFExport scsf_EarlyOnsetTrend(SCStudyInterfaceRef sc)
{
	// Reference the Plots and the inputs
	SCSubgraphRef 	Quotient	= sc.Subgraph[0];
	SCSubgraphRef 	Roofing		= sc.Subgraph[1];
	SCSubgraphRef 	Null		= sc.Subgraph[2];
	SCSubgraphRef 	Line1		= sc.Subgraph[3];
	SCSubgraphRef 	Line2		= sc.Subgraph[4];
	
	SCInputRef 		LPPeriod	= sc.Input[0];
	SCInputRef 		K			= sc.Input[1];
	SCInputRef 		Bars		= sc.Input[2];
	SCInputRef 		ynRoofing	= sc.Input[3];
	
	SCFloatArrayRef HP  		= Quotient.Arrays[0]; 
	SCFloatArrayRef Peak  		= Quotient.Arrays[1];
	
	if (sc.SetDefaults)
	{
	// Section 1 - Set the configuration variables and defaults
		sc.GraphName 			= "Early-Onset Trend Indicator";
		sc.StudyDescription 	= "Early-Onset Trend Indicator based on Ehlers";		
				
		//sc.GraphRegion 	= 1;	// Set the Chart Region to draw the graph in.  Region 0 is the main price graph
		sc.FreeDLL 				= 0;	// During dev set this flag to 1, so DLL can be rebuilt without restarting Sierra 
		sc.AutoLoop 			= 1;	//Auto looping is enabled. 
		sc.ValueFormat 			= 2;
		sc.ScaleRangeType		= SCALE_AUTO;
		
	// Reference the Plots and the inputs and define them
		Quotient.Name 			= "EOT";
		Quotient.DrawStyle 		= DRAWSTYLE_LINE;		// Look in scconstants.h for other draw styles
		Quotient.PrimaryColor 	= RGB(0,128,0);			// Green	
		Quotient.SecondaryColor = RGB(255, 128, 128);	// Light Red
		Quotient.LineWidth 		= 3;
		Quotient.AutoColoring	= AUTOCOLOR_SLOPE;
		
		Roofing.Name 			= "Roofing filter";
		Roofing.DrawStyle 		= DRAWSTYLE_IGNORE;		// Look in scconstants.h for other draw styles
		Roofing.PrimaryColor 	= RGB(0,128,0);			// Nice Green	
		Roofing.LineWidth 		= 2;
		
		Null.Name 				= "Null";
		Null.DrawStyle 			= DRAWSTYLE_LINE;
		Null.PrimaryColor 		= RGB(128,128,128);
		Null.LineWidth 			= 1;
		Null.DrawZeros 			= 1;

		Line1.Name				= "0.89";
		Line1.DrawStyle			= DRAWSTYLE_LINE;
		Line1.LineStyle			= LINESTYLE_DOT;
		Line1.PrimaryColor		= RGB(0, 0, 0);
		Line1.LineWidth			= 1;
		Line1.DrawZeros			= 1;

		Line2.Name				= "-0.89";
		Line2.DrawStyle			= DRAWSTYLE_LINE;
		Line2.LineStyle			= LINESTYLE_DOT;
		Line2.PrimaryColor		= RGB(0, 0, 0);
		Line2.LineWidth			= 1;
		Line2.DrawZeros			= 1;
		
		LPPeriod.Name			= "Period";
		LPPeriod.SetInt(20);
		LPPeriod.SetIntLimits(1, INT_MAX);

		ynRoofing.Name = "show Roofing";
		ynRoofing.SetYesNo(0);
		ynRoofing.SetIntLimits(1, INT_MAX);
		
		K.Name 					= "Quotient parameter";
		K.SetFloat(0.9f);
		K.SetFloatLimits(-99.9f, 99.9f);	
		
		Bars.Name = "Periods shorter then";  //Highpass filter cyclic components whose periods are shorter than ... bars (100)
		Bars.SetInt(100);
		Bars.SetIntLimits(1, INT_MAX);
		
		return;
	}

	// Section 2 - Do data processing here
	if (ynRoofing.GetYesNo())
	{
		Roofing.DrawStyle = DRAWSTYLE_LINE;
		Quotient.DrawStyle = DRAWSTYLE_IGNORE;
	}
	else
	{
		Roofing.DrawStyle = DRAWSTYLE_IGNORE;
		Quotient.DrawStyle = DRAWSTYLE_LINE;	
	}
	
		float alpha1, a1, b1, c1, c2, c3, X;

	//SuperSmoother Filter
		a1 = exp( (-1.414) * 3.14159 / LPPeriod.GetInt());
		b1 = 2 * a1 * cos(1.414*(180*3.14159/180)/LPPeriod.GetInt());
		c2 = b1;
		c3 = (-1)*a1*a1;
		c1 = 1 - c2 - c3;	
		
	//Highpass filter cyclic components whose periods are shorter than ... bars (100)
		float tr, fi;
		tr = 360 * 3.14159 / 180;
		fi = 0.707 * tr / Bars.GetInt();
		alpha1 = (cos(fi) + sin(fi) - 1) / cos(fi);
		
		HP[sc.Index] = (1 - alpha1 / 2) * (1 - alpha1 / 2) * (sc.BaseDataIn[SC_LAST][sc.Index] - 2 * sc.BaseDataIn[SC_LAST][sc.Index-1] + sc.BaseDataIn[SC_LAST][sc.Index-2]) + 2*(1 - alpha1) * HP[sc.Index-1] - (1 - alpha1) * (1-alpha1) * HP[sc.Index-2];
		Roofing[sc.Index] = c1*(HP[sc.Index] + HP[sc.Index-1] ) / 2 + c2*Roofing[sc.Index-1] + c3*Roofing[sc.Index-2];
			
	//Fast Attack - Slow Decay Algorithm
		Peak[sc.Index] = .991 * Peak[sc.Index-1];
		if (fabs(Roofing[sc.Index]) > Peak[sc.Index]) Peak[sc.Index] = fabs(Roofing[sc.Index]);
					
	//Normalized Roofing Filter
		if (Peak[sc.Index] !=0) X = Roofing[sc.Index] / Peak[sc.Index];
		else X = 0;

		Quotient[sc.Index] = (X + K.GetFloat()) / (K.GetFloat() * X + 1);
		Null[sc.Index]	= 0;
		Line1[sc.Index] = 0.89;
		Line2[sc.Index] = -0.89;

}



