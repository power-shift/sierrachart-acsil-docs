// The top of every source code file must include this line
#include <math.h>
#include "sierrachart.h"

/*****************************************************************************

	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/

// This line is required. Change the text within the quote
// marks to what you want to name your group of custom studies. 
//SCDLLName("ehlEhlersUniversalOscillator") 


SCSFExport scsf_UniversalOscillator(SCStudyInterfaceRef sc)
{
	// Reference the Plots and the inputs
		SCSubgraphRef 	Universal	= sc.Subgraph[0];
		SCSubgraphRef 	Null		= sc.Subgraph[1];
	
		SCInputRef 		BandEdge	= sc.Input[0];
		
		SCFloatArrayRef Filt		= Universal.Arrays[0];
		SCFloatArrayRef Peak  		= Universal.Arrays[1];
		SCFloatArrayRef WhiteNoise  = Universal.Arrays[2];
	
	if (sc.SetDefaults)
	{
	// Section 1 - Set the configuration variables and defaults
		sc.GraphName 			= "Ehlers Universal Oscillator"; // Name in study overview
		sc.StudyDescription 	= "Ehlers Universal Oscillator from TASC Magazine jan 2015";		
				
		//sc.GraphRegion 		= 1;	// Set the Chart Region to draw the graph in.  Region 0 is the main price graph
		sc.FreeDLL 				= 0;	// During dev set this flag to 1, so DLL can be rebuilt without restarting Sierra 
		sc.AutoLoop 			= 1;	//Auto looping is enabled. 
		sc.ValueFormat 			= 2;
		sc.ScaleRangeType		= SCALE_AUTO;
		
	// Reference the Plots and the inputs and define them
		Universal.Name			= "Universal Oscillator";
		Universal.DrawStyle		= DRAWSTYLE_LINE;		// Look in scconstants.h for other draw styles
		Universal.PrimaryColor	= RGB(255, 128, 64);		// Orange	
		Universal.LineWidth		= 2;
				
		Null.Name 				= "Zero line";
		Null.DrawStyle 			= DRAWSTYLE_LINE;
		Null.PrimaryColor 		= RGB(128,128,128);
		Null.LineWidth 			= 1;
		Null.DrawZeros 			= 1;
		
		BandEdge.Name = "BandEdge";  
		BandEdge.SetInt(20);
		BandEdge.SetIntLimits(1, INT_MAX);
		
		return;
	}
	// Section 2 - Do data processing here
		float a1, b1, c1, c2, c3;
		
		WhiteNoise[sc.Index] = (sc.BaseDataIn[SC_LAST][sc.Index] - sc.BaseDataIn[SC_LAST][sc.Index - 2]) / 2;
		
	//SuperSmoother Filter
		a1 = exp( (-1.414f) * 3.14159f / BandEdge.GetInt());
		b1 = 2 * a1 * cos(1.414f * (180 * 3.14159f / 180) / BandEdge.GetInt());
		c2 = b1;
		c3 = (-1)*a1*a1;
		c1 = 1 - c2 - c3;	
		
		Filt[sc.Index] = c1*(WhiteNoise[sc.Index] + WhiteNoise[sc.Index - 1]) / 2 + c2*Filt[sc.Index - 1] + c3*Filt[sc.Index - 2];
		if (sc.Index == 0) Filt[sc.Index] = 0;
		if (sc.Index == 1) Filt[sc.Index] = c1 * (sc.BaseDataIn[SC_LAST][sc.Index] + sc.BaseDataIn[SC_LAST][sc.Index - 1]) / 2 + c2 * Filt[sc.Index - 1];
		if (sc.Index == 2) Filt[sc.Index] = c1 * (sc.BaseDataIn[SC_LAST][sc.Index] + sc.BaseDataIn[SC_LAST][sc.Index - 1]) / 2 + c2 * Filt[sc.Index - 1] + c3 * Filt[sc.Index - 2];

	//Automatic Gain Control (AGC)
		Peak[sc.Index] = .991f * Peak[sc.Index - 1];
		if (sc.Index == 0) Peak[sc.Index] = .0000001f;
		if (fabs(Filt[sc.Index]) > Peak[sc.Index]) Peak[sc.Index] = fabs(Filt[sc.Index]);
		if (Peak[sc.Index] !=0) Universal[sc.Index] = Filt[sc.Index] / Peak[sc.Index];
	
		//Plot		
		Null[sc.Index]	= 0;

}





