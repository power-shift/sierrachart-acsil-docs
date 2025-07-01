// The top of every source code file must include this line
#include "sierrachart.h"
#include <time.h>
//#include <math.h> 


/*****************************************************************************

	This file contains Sierra Chart custom study template functions and example functions.
	
	For reference, please refer to the Advanced Custom Study Interface
	and Language documentation on the Sierra Chart website. 
	
*****************************************************************************/


// This line is required. Change the text within the quote
// marks to what you want to name your group of custom studies. 
//SCDLLName("NYSEvolume") 


SCSFExport scsf_NYSEvolume(SCStudyGraphRef sc)
{

	SCInputRef Divider = sc.Input[0];


	if (sc.SetDefaults)
	{
		
		
		sc.GraphName = "NYSE Volume";
		
		sc.StudyDescription = "NYSE Volume study";

		sc.AutoLoop = 1;  // true

		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance. 
		sc.FreeDLL = 0; 
		sc.GraphRegion=1;

		

		sc.Subgraph[0].Name = "NYSE Volume";
		sc.Subgraph[0].PrimaryColor = RGB(255,255,255);  // white
		sc.Subgraph[0].DrawStyle = DRAWSTYLE_BAR;
		sc.Subgraph[0].LineWidth = 4;		
		sc.Subgraph[0].SecondaryColorUsed=1;
		sc.Subgraph[0].PrimaryColor = RGB(0,255,0);
		sc.Subgraph[0].SecondaryColor = RGB(255,0,0);
		sc.Subgraph[0].AutoColoring = AUTOCOLOR_SLOPE;

		
	

		Divider.Name = " Divide NYSE Volume by this number (1-500,000)";
		Divider.SetInt(1);
		Divider.SetIntLimits(1,500000);
		
		return;
	}
	
	

	float CurrentVolume= sc.BaseData[SC_LAST][sc.Index]  - sc.BaseData[SC_LAST][sc.Index-1];
	
	if (CurrentVolume <= 0 )
		CurrentVolume=sc.BaseData[SC_LAST][sc.Index];
		

	sc.Subgraph[0][sc.Index]=CurrentVolume/Divider.GetInt();	  
	
	
}


/*SCString Buffer;
Buffer.Format("Got Here: %5.2f",CurrentLow);
sc.AddMessageToLog(Buffer,0);  */

