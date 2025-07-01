#include "sierrachart.h"
#include "RobBooker.h"

//const char* msgStr = "This study requires a license. Please contact GMM International (gmm.intl@gmail.com)";

//SCDLLName("Rob Booker Studies")


bool check_license(SCStudyInterfaceRef sc)
{
return true;
/*
	if (sc.SetDefaults) 
	{
		return true;
	}
	
	if(sc.IsUserAllowedForSCDLLName == false)
	{
		
		if (sc.Index == 0)
		{
			SCString msg;
			msg.Format(msgStr);
			sc.AddMessageToLog(msg, 1);
		}

		return false;
	}
	
	return true;
*/
}


SCSFExport scsf_knoxville_divergence(SCStudyInterfaceRef sc)
{
	if(check_license(sc) == false)
	{
		return;
	}

	knoxville_divergence::process(sc);
}

SCSFExport scsf_reversal_arrows(SCStudyInterfaceRef sc)
{
	if(check_license(sc) == false)
	{
		return;
	}

	reversal_arrows::process(sc);
}

