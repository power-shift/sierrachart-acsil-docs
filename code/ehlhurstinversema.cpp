// The top of every source code file must include this line
#include "sierrachart.h"

/*****************************************************************************

For reference, please refer to the Advanced Custom Study Interface
and Language documentation on the Sierra Chart website.

*****************************************************************************/

// This line is required. Change the text within the quote
// marks to what you want to name your group of custom studies. 
//SCDLLName("ehlHurstInverseMa")


SCSFExport scsf_HurstInverseMa(SCStudyGraphRef sc)
{
	// Reference the Plots and the inputs
	SCSubgraphRef 	HIM			= sc.Subgraph[0];
	SCSubgraphRef 	Null		= sc.Subgraph[1];
	SCSubgraphRef 	arrLongMa	= sc.Subgraph[2];

	SCInputRef 		cyclePeriod = sc.Input[0];
	SCInputRef 		inputData	= sc.Input[1];
	SCInputRef 		MAType		= sc.Input[2];

	if (sc.SetDefaults)
	{
		// Section 1 - Set the configuration variables and defaults
		sc.GraphName			= "Hurst Inverse MA";
		sc.StudyDescription 	= "Inverse MA bases on Hurst";

		//sc.GraphRegion 		= 1;	// Set the Chart Region to draw the graph in.  Region 0 is the main price graph
		sc.FreeDLL				= 0;	// During dev set this flag to 1, so DLL can be rebuilt without restarting Sierra 
		sc.AutoLoop				= 1;	//Auto looping is enabled. 
		sc.ValueFormat			= 2;
		sc.ScaleRangeType		= SCALE_AUTO;

		// Reference the Plots and the inputs and define them
		HIM.Name 				= "MCH";
		HIM.DrawStyle 			= DRAWSTYLE_FILLTOZERO;		// Look in scconstants.h for other draw styles
		HIM.PrimaryColor 		= RGB(128, 128, 128);		// Green
		HIM.LineWidth 			= 2;
		HIM.DrawZeros 			= 1;

		Null.Name 				= "Zeo line";
		Null.DrawStyle 			= DRAWSTYLE_LINE;
		Null.LineStyle 			= LINESTYLE_DOT;
		Null.PrimaryColor 		= RGB(128, 128, 128);
		Null.LineWidth 			= 1;
		Null.DrawZeros 			= 1;
		
		cyclePeriod.Name 		= "Cycle Period";
		cyclePeriod.SetInt(20);
		cyclePeriod.SetIntLimits(1, INT_MAX);

		inputData.Name 			= "Input Data";
		inputData.SetInputDataIndex(SC_LAST);

		MAType.Name = "MA extension type";
		MAType.SetMovAvgType(MOVAVGTYPE_SIMPLE);
		
		return;
	}
	// Section 2 - Do data processing here
	int intMaPeriod = cyclePeriod.GetInt();
	int halfSpan = INT(intMaPeriod / 2);
	
	int InputDataIndex = inputData.GetInputDataIndex();
	arrLongMa.GraphicalDisplacement  = INT(-cyclePeriod.GetInt() / 2);

	sc.MovingAverage(sc.BaseDataIn[InputDataIndex], arrLongMa, MAType.GetMovAvgType(), intMaPeriod);

	if (sc.Index < halfSpan || sc.Index > (sc.ArraySize - halfSpan))
	{
		HIM[sc.Index] = 0;
	}
	else
	{
		HIM[sc.Index] = sc.BaseDataIn[InputDataIndex][sc.Index] - arrLongMa[sc.Index];
	}

		
}



