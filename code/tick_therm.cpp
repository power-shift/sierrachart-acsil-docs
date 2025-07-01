#include "sierrachart.h"


SCSFExport scsf_ticktherm2(SCStudyInterfaceRef sc)
{
	SCInputRef ChartStudy = sc.Input[0];
	SCInputRef max = sc.Input[1];
	SCInputRef Enabled = sc.Input[2];
	SCInputRef ChartStudy2 = sc.Input[3];
	SCInputRef max2 = sc.Input[4];
	SCInputRef Enabled2 = sc.Input[5];
	SCInputRef ChartStudy3 = sc.Input[6];
	SCInputRef max3 = sc.Input[7];
	SCInputRef Enabled3 = sc.Input[8];
	SCInputRef lnw = sc.Input[9];

	float& emrcl = sc.PersistVars->f1;
	float& emrcl2 = sc.PersistVars->f2;
	float& emrcl3 = sc.PersistVars->f3;

	if (sc.SetDefaults)
	{
		sc.GraphName = "Tick_Therm2";
		sc.StudyDescription = "Tick_Therm2";

		ChartStudy.Name = "Study Reference 1";
		ChartStudy.SetChartStudyValues(1,1);

		max.Name = "Max Value 1";
		max.SetFloat(800.0f);

		Enabled.Name = "Display Style 1, 2, 3";
		Enabled.SetInt(1);

		ChartStudy2.Name = "Study Reference 2";
		ChartStudy2.SetChartStudyValues(2,2);

		max2.Name = "Max Value 2";
		max2.SetFloat(500.0f);

		Enabled2.Name = "Display Style 1, 2, 3";
		Enabled2.SetInt(1);

		ChartStudy3.Name = "Study Reference 3";
		ChartStudy3.SetChartStudyValues(3,3);

		max3.Name = "Max Value 3";
		max3.SetFloat(500.0f);

		Enabled3.Name = "Display Style 1, 2, 3";
		Enabled3.SetInt(1);

		lnw.Name = "Bar Width";
		lnw.SetInt(4);

		sc.AutoLoop = 1;
		sc.GraphRegion = 0;
		sc.ScaleRangeType = SCALE_INDEPENDENT;
		sc.ValueFormat = 0;

		sc.FreeDLL = 0;

		return;
	}
	float mult = max.GetFloat() / 100.0f;
	float mult2 = max2.GetFloat() / 100.0f;
	float mult3 = max3.GetFloat() / 100.0f;
	SCGraphData BaseGraphData;
	sc.GetChartBaseData(ChartStudy.GetChartNumber(), BaseGraphData);
	SCFloatArrayRef LastArray = BaseGraphData[SC_LAST];
	SCGraphData BaseGraphData2;
	sc.GetChartBaseData(ChartStudy2.GetChartNumber(), BaseGraphData2);
	SCFloatArrayRef LastArray2 = BaseGraphData2[SC_LAST];
	SCGraphData BaseGraphData3;
	sc.GetChartBaseData(ChartStudy3.GetChartNumber(), BaseGraphData3);
	SCFloatArrayRef LastArray3 = BaseGraphData3[SC_LAST];
	if(LastArray.GetArraySize() == 0 || LastArray2.GetArraySize() == 0 || LastArray3.GetArraySize() == 0)
	{
		return;
	}
	int RefChartIndex = sc.GetNearestMatchForDateTimeIndex(ChartStudy.GetChartNumber(), sc.Index);
	float NearestRefChart = LastArray[RefChartIndex];
	RefChartIndex = sc.GetContainingIndexForDateTimeIndex(ChartStudy.GetChartNumber(), sc.Index);
	float ContainingRefChartLast = LastArray[RefChartIndex];
	RefChartIndex = sc.GetExactMatchForSCDateTime(ChartStudy.GetChartNumber(), sc.BaseDateTimeIn[sc.Index]);

	int RefChartIndex2 = sc.GetNearestMatchForDateTimeIndex(ChartStudy2.GetChartNumber(), sc.Index);
	float NearestRefChart2 = LastArray2[RefChartIndex2];
	RefChartIndex2 = sc.GetContainingIndexForDateTimeIndex(ChartStudy2.GetChartNumber(), sc.Index);
	float ContainingRefChartLast2 = LastArray2[RefChartIndex];
	RefChartIndex2 = sc.GetExactMatchForSCDateTime(ChartStudy2.GetChartNumber(), sc.BaseDateTimeIn[sc.Index]);

	int RefChartIndex3 = sc.GetNearestMatchForDateTimeIndex(ChartStudy3.GetChartNumber(), sc.Index);
	float NearestRefChart3 = LastArray3[RefChartIndex3];
	RefChartIndex3 = sc.GetContainingIndexForDateTimeIndex(ChartStudy3.GetChartNumber(), sc.Index);
	float ContainingRefChartLast3 = LastArray3[RefChartIndex3];
	RefChartIndex3 = sc.GetExactMatchForSCDateTime(ChartStudy3.GetChartNumber(), sc.BaseDateTimeIn[sc.Index]);

	if(RefChartIndex != -1 || RefChartIndex2 != -1 || RefChartIndex3 != -1)
	{
		emrcl = LastArray[RefChartIndex];
		emrcl2 = LastArray2[RefChartIndex2];
		emrcl3 = LastArray3[RefChartIndex3];
	}
	s_UseTool Tool;
	const int UniqueLine = 78191;
	for(int i = 1; i < 4; i++) {
		Tool.Clear();
		Tool.ChartNumber = sc.ChartNumber;
		Tool.DrawingType = DRAWING_LINE;
		Tool.LineWidth = lnw.GetInt();
		Tool.LineNumber = UniqueLine + i;
		Tool.BeginDateTime = sc.BaseDateTimeIn[sc.ArraySize + i];
		Tool.EndDateTime = sc.BaseDateTimeIn[sc.ArraySize + i];
		Tool.UseRelativeVerticalValues = 1;

		if (i == 1) 
		{
			if (Enabled.GetInt() == 1)
			{
				Tool.BeginValue = 0.0f;
				if (emrcl < 0.0f)
				{
					Tool.EndValue = -emrcl / mult;
				}
				else
				{
					Tool.EndValue = emrcl / mult;
				}
			}
			else if (Enabled.GetInt() == 2)
			{
				Tool.BeginValue = 50.0f;
				Tool.EndValue = 50.0f + ((emrcl / mult) / 2.0f);
			}
			else
			{
				if (emrcl > 0.0f)
				{	
					Tool.BeginValue = 0.0f;
					Tool.EndValue = (emrcl / mult);
				}
				else
				{
					Tool.BeginValue = 100.0f;
					Tool.EndValue = 100.0f + (emrcl / mult);
				}
			}
			if (emrcl > 0.0f)
			{
				Tool.Color = RGB(0,255,0);
			}
			else
			{
				Tool.Color = RGB(255,0,0);
			}
			Tool.AddMethod = UTAM_ADD_OR_ADJUST;
			sc.UseTool(Tool);
		}
		else if (i == 2) {
			if (Enabled2.GetInt() == 1)
			{
				Tool.BeginValue = 0.0f;
				if (emrcl2 < 0.0f)
				{
					Tool.EndValue = -emrcl2 / mult2;
				}
				else
				{
					Tool.EndValue = emrcl2 / mult2;
				}
			}
			else if (Enabled2.GetInt() == 2)
			{
				Tool.BeginValue = 50.0f;
				Tool.EndValue = 50.0f + ((emrcl2 / mult2) / 2.0f);
			}
			else
			{
				if (emrcl2 > 0.0f)
				{	
					Tool.BeginValue = 0.0f;
					Tool.EndValue = (emrcl2 / mult2);
				}
				else
				{
					Tool.BeginValue = 100.0f;
					Tool.EndValue = 100.0f + (emrcl2 / mult2);
				}
			}
			if (emrcl2 > 0.0f)
			{
				Tool.Color = RGB(0,255,0);
			}
			else
			{
				Tool.Color = RGB(255,0,0);
			}
			Tool.AddMethod = UTAM_ADD_OR_ADJUST;
			sc.UseTool(Tool);
		}
		else if (i == 3) {
			if (Enabled3.GetInt() == 1)
			{
				Tool.BeginValue = 0.0f;
				if (emrcl3 < 0.0f)
				{
					Tool.EndValue = -emrcl3 / mult3;
				}
				else
				{
					Tool.EndValue = emrcl3 / mult3;
				}
			}
			else if (Enabled3.GetInt() == 2)
			{
				Tool.BeginValue = 50.0f;
				Tool.EndValue = 50.0f + ((emrcl3 / mult3) / 2.0f);
			}
			else
			{
				if (emrcl3 > 0.0f)
				{	
					Tool.BeginValue = 0.0f;
					Tool.EndValue = (emrcl3 / mult3);
				}
				else
				{
					Tool.BeginValue = 100.0f;
					Tool.EndValue = 100.0f + (emrcl3 / mult3);
				}
			}
			if (emrcl3 > 0.0f)
			{
				Tool.Color = RGB(0,255,0);
			}
			else
			{
				Tool.Color = RGB(255,0,0);
			}
			Tool.AddMethod = UTAM_ADD_OR_ADJUST;
			sc.UseTool(Tool);
		}
	}
}

