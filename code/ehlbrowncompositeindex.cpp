// The top of every source code file must include this line
#include "sierrachart.h"

//SCDLLName("ehlBrownComposteIndex") 


SCSFExport scsf_BrownCompositeIndex(SCStudyGraphRef sc)
{
// Reference the Plots and the inputs
	SCSubgraphRef 	BCI		= sc.Subgraph[0];
	SCSubgraphRef 	RSI1	= sc.Subgraph[1];
	SCSubgraphRef 	RSI2	= sc.Subgraph[2];
	SCSubgraphRef 	MA13	= sc.Subgraph[3];
	SCSubgraphRef 	MA33	= sc.Subgraph[4];

	SCFloatArrayRef RSIMOM = BCI.Arrays[0];
	SCFloatArrayRef RSISMA = BCI.Arrays[1];

	SCInputRef 		RSIMOMperiod	= sc.Input[0];
	SCInputRef 		MomentumPeriod	= sc.Input[1];
	SCInputRef 		RSISMAperiod	= sc.Input[2];
	SCInputRef 		AveragePeriod	= sc.Input[3];
	SCInputRef 		ynWelles		= sc.Input[4];
	
	if (sc.SetDefaults)
	{
	// Section 1 - Set the configuration variables and defaults
		sc.GraphName 			= "Brown Composite Index";
		sc.StudyDescription 	= "Constance Brown Composite Index based on Cardwell RSI";		
				
		//sc.GraphRegion 		= 1;	// Set the Chart Region to draw the graph in.  Region 0 is the main price graph
		sc.FreeDLL 				= 0;	// During dev set this flag to 1, so DLL can be rebuilt without restarting Sierra 
		sc.AutoLoop 			= 1;	//Auto looping is enabled. 
		sc.ValueFormat 			= 2;
		sc.ScaleRangeType		= SCALE_AUTO;
		
	// Reference the Plots and the inputs and define them
		BCI.Name = "BCI";
		BCI.DrawStyle = DRAWSTYLE_LINE;			// Look in scconstants.h for other draw styles
		BCI.PrimaryColor = RGB(0, 128, 0);		// Green
		BCI.LineWidth = 2;
		
		MA13.Name = "MA13";
		MA13.DrawStyle = DRAWSTYLE_LINE;			// Look in scconstants.h for other draw styles
		MA13.PrimaryColor = RGB(255, 128, 64);		// Light Red
		MA13.LineWidth = 1;

		MA33.Name = "MA33";
		MA33.DrawStyle = DRAWSTYLE_LINE;			// Look in scconstants.h for other draw styles
		MA33.PrimaryColor = RGB(0, 128, 255);		// Blue
		MA33.LineWidth = 1;

		RSIMOMperiod.Name = "RSI Momentum Period";
		RSIMOMperiod.SetInt(14);
		RSIMOMperiod.SetIntLimits(1, INT_MAX);

		MomentumPeriod.Name = "Momentum Period";
		MomentumPeriod.SetInt(9);
		MomentumPeriod.SetIntLimits(1, INT_MAX);

		RSISMAperiod.Name = "RSI SMA Period";
		RSISMAperiod.SetInt(3);
		RSISMAperiod.SetIntLimits(1, INT_MAX);

		AveragePeriod.Name = "SMA Period";
		AveragePeriod.SetInt(3);
		AveragePeriod.SetIntLimits(1, INT_MAX);

		ynWelles.Name = "Use Welles average";
		ynWelles.SetYesNo(1);
		ynWelles.SetIntLimits(1, INT_MAX);
		
		return;
	}
	// Section 2 - Do data processing here
		if (ynWelles.GetYesNo()) sc.RSI(sc.BaseDataIn[SC_LAST], RSI1, MOVAVGTYPE_WILDERS, RSIMOMperiod.GetInt());
		else sc.RSI(sc.BaseDataIn[SC_LAST], RSI1, MOVAVGTYPE_EXPONENTIAL, RSIMOMperiod.GetInt());
		
		if (ynWelles.GetYesNo()) sc.RSI(sc.BaseDataIn[SC_LAST], RSI2, MOVAVGTYPE_WILDERS, RSISMAperiod.GetInt());
		else sc.RSI(sc.BaseDataIn[SC_LAST], RSI2, MOVAVGTYPE_EXPONENTIAL, RSISMAperiod.GetInt());
		
		sc.Momentum(RSI1, RSIMOM, MomentumPeriod.GetInt());
		sc.MovingAverage(RSI2, RSISMA, MOVAVGTYPE_SIMPLE, AveragePeriod.GetInt());
		
		BCI[sc.Index] = (RSIMOM[sc.Index] + RSISMA[sc.Index])  ;

		sc.MovingAverage(BCI, MA13, MOVAVGTYPE_SIMPLE, 13);
		sc.MovingAverage(BCI, MA33, MOVAVGTYPE_SIMPLE, 33);		
}



