#define WIN32_LEAN_AND_MEAN
#include  <iterator>

#include "sierrachart.h"

//SCDLLName("RTscanUBa") 

SCSFExport scsf_RTscanUBa(SCStudyGraphRef sc)
{
		SCSubgraphRef askUB  = sc.Subgraph[0];
		SCSubgraphRef bidUB  = sc.Subgraph[1];
		
		SCSubgraphRef AlertA = sc.Subgraph[2];
		SCSubgraphRef AlertB = sc.Subgraph[3];
									
	if (sc.SetDefaults)
	{
		
		sc.GraphName		= "RTscanUBa";
		sc.GraphRegion		= 0;
		sc.StudyDescription = "RTscanUB rc3 @ganz";
		
		sc.AutoLoop 		= 1;
		
		sc.FreeDLL 			= 0;
		
		sc.MaintainVolumeAtPriceData = 1; 
		
		askUB.Name 			= "askUB";
		askUB.DrawStyle 	= DRAWSTYLE_RIGHTHASH;
		askUB.LineWidth 	= 4;
		
		bidUB.Name 			= "bidUB";
		bidUB.DrawStyle 	= DRAWSTYLE_LEFTHASH;
		bidUB.LineWidth 	= 4;
		
		AlertA.Name 		= "AlertA";
		AlertA.DrawStyle 	= DRAWSTYLE_HIDDEN;
		
		AlertB.Name 		= "AlertB";
		AlertB.DrawStyle 	= DRAWSTYLE_HIDDEN;
				
	 return;
	}
	
	if ((int)sc.VolumeAtPriceForBars->GetNumberOfBars() < sc.ArraySize)		return;

	unsigned int max 		= 0;
	unsigned int min 		= 0;
	    
	unsigned int Ask 		= 0;
	unsigned int Bid 		= 0;
		
	float Price0 			= 0;
	float Price1 			= 0;
	float FlagA 			= 0;
	float FlagB 			= 0;
	
	s_VolumeAtPriceV2 *p_VolumeAtPriceAtIndex;
	int Count = sc.VolumeAtPriceForBars-> GetSizeAtBarIndex(sc.Index);

	for (int ElementIndex = 0;ElementIndex < Count; ElementIndex ++)
	{
						
			sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.Index, ElementIndex, &p_VolumeAtPriceAtIndex);

			if (p_VolumeAtPriceAtIndex)
				{
						
						Bid = p_VolumeAtPriceAtIndex->BidVolume;
						Ask = p_VolumeAtPriceAtIndex->AskVolume;
						max = Count - 1;
						min = 0;
					
					
					if ( (Ask != 0) && (ElementIndex == min) )	 Price0 = p_VolumeAtPriceAtIndex->PriceInTicks * sc.TickSize; 
					if ( (Bid != 0) && (ElementIndex == max) )	 Price1 = p_VolumeAtPriceAtIndex->PriceInTicks * sc.TickSize;
					
					// an alert
					
					if ( (Ask == 0) && (ElementIndex == min) )	 FlagA = p_VolumeAtPriceAtIndex->PriceInTicks * sc.TickSize; 
					if ( (Bid == 0) && (ElementIndex == max) )	 FlagB = p_VolumeAtPriceAtIndex->PriceInTicks * sc.TickSize; 
					
					
				};
				
	};

	askUB[sc.Index] 		=  (float) Price0;
	bidUB[sc.Index] 		=  (float) Price1; 
	
	AlertA[sc.Index] 		=  (float) FlagA;
	AlertB[sc.Index] 		=  (float) FlagB;	 
 }
