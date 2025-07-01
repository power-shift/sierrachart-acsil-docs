#include "sierrachart.h"

/*==========================================================================*/
SCSFExport scsf_OCInsideBar(SCStudyInterfaceRef sc)
{
	SCSubgraphRef IB = sc.Subgraph[0];

	// Set configuration variables

	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "Open and Close Inside Or Equals Previous Bar";

		sc.StudyDescription = "";

		//During development set this flag to 1, so the DLL can be modified. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;

		sc.GraphRegion = 0;

		IB.Name = "IB";
		IB.DrawStyle = DRAWSTYLE_COLORBAR;
		IB.PrimaryColor = RGB(0, 0, 255);
		IB.DrawZeros = false;

		sc.AutoLoop = 1;

		return;
	}


	// Do data processing

	if (sc.Index < 1)
		return;

	// Array references
	SCFloatArrayRef High = sc.High;
	SCFloatArrayRef Low = sc.Low;

	float upper = max(sc.Close[sc.Index], sc.Open[sc.Index]);
	float lower = min(sc.Close[sc.Index], sc.Open[sc.Index]);
	
	if (upper <= High[sc.Index - 1] && lower >= Low[sc.Index - 1])
		IB[sc.Index] = 1;
	else
		IB[sc.Index] = 0;
}