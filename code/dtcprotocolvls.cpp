#include <float.h>
#include <limits.h>
#include <string.h>
#include <memory.h> 
#include <stddef.h>

#include "DTCProtocolVLS.h"


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


namespace DTC_VLS
{

	/****************************************************************************/
	// s_LogonRequest

	/*============================================================================
	Will get the size of the message received over the network
	----------------------------------------------------------------------------*/
	uint16_t s_LogonRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_LogonRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_LogonRequest::GetProtocolVersion() const
	{
		if (BaseSize < offsetof(s_LogonRequest, ProtocolVersion) + sizeof(ProtocolVersion))
			return 0;

		return ProtocolVersion;
	}

	/*==========================================================================*/
	int32_t s_LogonRequest::GetInteger_1() const
	{
		if (BaseSize < offsetof(s_LogonRequest, Integer_1) + sizeof(Integer_1))
			return 0;

		return Integer_1;
	}
	
	/*==========================================================================*/
	int32_t s_LogonRequest::GetInteger_2() const
	{
		if (BaseSize < offsetof(s_LogonRequest, Integer_2) + sizeof(Integer_2))
			return 0;

		return Integer_2;
	}

	/*==========================================================================*/
	int32_t s_LogonRequest::GetHeartbeatIntervalInSeconds() const
	{
		if (BaseSize < offsetof(s_LogonRequest, HeartbeatIntervalInSeconds) + sizeof(HeartbeatIntervalInSeconds))
			return 0;

		return HeartbeatIntervalInSeconds;
	}

	/*==========================================================================*/

	int32_t s_LogonRequest::GetMarketDataTransmissionInterval() const
	{
		if (BaseSize < offsetof(s_LogonRequest, MarketDataTransmissionInterval) + sizeof(MarketDataTransmissionInterval))
			return 0;

		return MarketDataTransmissionInterval;
	}

	/****************************************************************************/
	// s_LogonResponse

	/*==========================================================================*/
	uint16_t s_LogonResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_LogonResponse::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_LogonResponse::GetProtocolVersion() const
	{
		if (BaseSize < offsetof(s_LogonResponse, ProtocolVersion) + sizeof(ProtocolVersion))
			return 0;

		return ProtocolVersion;
	}

	/*==========================================================================*/
	DTC::LogonStatusEnum s_LogonResponse::GetResult() const
	{
		if (BaseSize < offsetof(s_LogonResponse, Result) + sizeof(Result))
			return static_cast<DTC::LogonStatusEnum>(0);

		return Result;
	}
	
	/*==========================================================================*/
	int32_t s_LogonResponse::GetInteger_1() const
	{
		if (BaseSize < offsetof(s_LogonResponse, Integer_1) + sizeof(Integer_1))
			return 0;

		return Integer_1;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetMarketDepthUpdatesBestBidAndAsk() const
	{
		if (BaseSize < offsetof(s_LogonResponse, MarketDepthUpdatesBestBidAndAsk) + sizeof(MarketDepthUpdatesBestBidAndAsk))
			return 0;

		return MarketDepthUpdatesBestBidAndAsk;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetTradingIsSupported() const
	{
		if (BaseSize < offsetof(s_LogonResponse, TradingIsSupported) + sizeof(TradingIsSupported))
			return 0;

		return TradingIsSupported;
	}


	/*==========================================================================*/
	uint8_t s_LogonResponse::GetOCOOrdersSupported() const
	{
		if (BaseSize < offsetof(s_LogonResponse, OCOOrdersSupported) + sizeof(OCOOrdersSupported))
			return 0;

		return OCOOrdersSupported;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetOrderCancelReplaceSupported() const
	{
		if (BaseSize < offsetof(s_LogonResponse, OrderCancelReplaceSupported) + sizeof(OrderCancelReplaceSupported))
			return 0;

		return OrderCancelReplaceSupported;
	}


	/*==========================================================================*/
	uint8_t s_LogonResponse::GetSecurityDefinitionsSupported() const
	{
		if (BaseSize < offsetof(s_LogonResponse, SecurityDefinitionsSupported) + sizeof(SecurityDefinitionsSupported))
			return 0;

		return SecurityDefinitionsSupported;
	}


	/*==========================================================================*/
	uint8_t s_LogonResponse::GetHistoricalPriceDataSupported() const
	{
		if (BaseSize < offsetof(s_LogonResponse, HistoricalPriceDataSupported) + sizeof(HistoricalPriceDataSupported))
			return 0;

		return HistoricalPriceDataSupported;
	}


	/*==========================================================================*/
	uint8_t s_LogonResponse::GetResubscribeWhenMarketDataFeedAvailable() const
	{
		if (BaseSize < offsetof(s_LogonResponse, ResubscribeWhenMarketDataFeedAvailable) + sizeof(ResubscribeWhenMarketDataFeedAvailable))
			return 0;

		return ResubscribeWhenMarketDataFeedAvailable;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetMarketDepthIsSupported() const
	{
		if (BaseSize < offsetof(s_LogonResponse, MarketDepthIsSupported) + sizeof(MarketDepthIsSupported))
			return 0;

		return MarketDepthIsSupported;
	}
	/*==========================================================================*/
	uint8_t s_LogonResponse::GetOneHistoricalPriceDataRequestPerConnection() const
	{
		if (BaseSize < offsetof(s_LogonResponse, OneHistoricalPriceDataRequestPerConnection) + sizeof(OneHistoricalPriceDataRequestPerConnection))
			return 0;

		return OneHistoricalPriceDataRequestPerConnection;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetBracketOrdersSupported() const
	{
		if (BaseSize < offsetof(s_LogonResponse, BracketOrdersSupported) + sizeof(BracketOrdersSupported))
			return 0;

		return BracketOrdersSupported;
	}
	
	/*==========================================================================*/
	uint8_t s_LogonResponse::GetUsesMultiplePositionsPerSymbolAndTradeAccount() const
	{
		if (BaseSize < offsetof(s_LogonResponse, UsesMultiplePositionsPerSymbolAndTradeAccount) + sizeof(UsesMultiplePositionsPerSymbolAndTradeAccount))
			return 0;

		return UsesMultiplePositionsPerSymbolAndTradeAccount;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetMarketDataSupported() const
	{
		if (BaseSize < offsetof(s_LogonResponse, MarketDataSupported) + sizeof(MarketDataSupported))
			return 0;

		return MarketDataSupported;
	}

	/****************************************************************************/
	// s_LogoffRequest

	/*==========================================================================*/
	uint16_t s_Logoff::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_Logoff::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	uint8_t s_Logoff::GetDoNotReconnect() const
	{
		if (BaseSize < offsetof(s_Logoff, DoNotReconnect) + sizeof(DoNotReconnect))
			return 0;

		return DoNotReconnect;
	}


	/****************************************************************************/
	// s_MarketDataRequest

	/*==========================================================================*/
	uint16_t s_MarketDataRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_MarketDataRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	DTC::RequestActionEnum s_MarketDataRequest::GetRequestAction() const
	{
		if (BaseSize < offsetof(s_MarketDataRequest, RequestAction) + sizeof(RequestAction))
			return static_cast<DTC::RequestActionEnum>(0);

		return RequestAction;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataRequest::GetSymbolID() const
	{
		if (BaseSize < offsetof(s_MarketDataRequest, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataRequest::GetIntervalForSnapshotUpdatesInMilliseconds() const
	{
		if (BaseSize < offsetof(s_MarketDataRequest, IntervalForSnapshotUpdatesInMilliseconds) + sizeof(IntervalForSnapshotUpdatesInMilliseconds))
			return 0;

		return IntervalForSnapshotUpdatesInMilliseconds;
	}

	/****************************************************************************/
	// s_MarketDepthRequest

	/*==========================================================================*/
	uint16_t s_MarketDepthRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_MarketDepthRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	DTC::RequestActionEnum s_MarketDepthRequest::GetRequestAction() const
	{
		if (BaseSize < offsetof(s_MarketDepthRequest, RequestAction) + sizeof(RequestAction))
			return static_cast<DTC::RequestActionEnum>(0);

		return RequestAction;
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthRequest::GetSymbolID() const
	{
		if (BaseSize < offsetof(s_MarketDepthRequest, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	int32_t s_MarketDepthRequest::GetNumLevels() const
	{
		if (BaseSize < offsetof(s_MarketDepthRequest, NumLevels) + sizeof(NumLevels))
			return 0;

		return NumLevels;
	}


	/****************************************************************************/
	// s_MarketDataReject

	/*==========================================================================*/
	uint16_t s_MarketDataReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_MarketDataReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataReject::GetSymbolID() const
	{
		if (BaseSize < offsetof(s_MarketDataReject, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/****************************************************************************/
	// s_MarketDepthReject

	/*==========================================================================*/
	uint16_t s_MarketDepthReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_MarketDepthReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthReject::GetSymbolID() const
	{
		if (BaseSize < offsetof(s_MarketDepthReject, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}
	
/****************************************************************************/
//s_MarketOrdersRequest

/*==========================================================================*/
	uint16_t DTC_VLS::s_MarketOrdersRequest::GetMessageSize() const
	{
		return Size;
	}
	/*==========================================================================*/
	uint16_t DTC_VLS::s_MarketOrdersRequest::GetBaseSize() const
	{
		return BaseSize;
	}
	/*==========================================================================*/
	DTC::RequestActionEnum s_MarketOrdersRequest::GetRequestAction() const
	{
		if (BaseSize < offsetof(s_MarketOrdersRequest, RequestAction) + sizeof(RequestAction))
			return DTC::RequestActionEnum::SUBSCRIBE;

		return RequestAction;
	}
	/*==========================================================================*/
	uint32_t s_MarketOrdersRequest::GetSymbolID() const
	{
		if (BaseSize < offsetof(s_MarketOrdersRequest, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}
	/*==========================================================================*/
	uint32_t s_MarketOrdersRequest::GetSendQuantitiesGreaterOrEqualTo() const
	{
		if (BaseSize < offsetof(s_MarketOrdersRequest, SendQuantitiesGreaterOrEqualTo) + sizeof(SendQuantitiesGreaterOrEqualTo))
			return 0;

		return SendQuantitiesGreaterOrEqualTo;
	}

	/****************************************************************************/
	//s_MarketOrdersReject

	/*==========================================================================*/
	uint16_t DTC_VLS::s_MarketOrdersReject::GetMessageSize() const
	{
		return Size;
	}
	/*==========================================================================*/
	uint16_t DTC_VLS::s_MarketOrdersReject::GetBaseSize() const
	{
		return BaseSize;
	}
	/*==========================================================================*/
	uint32_t s_MarketOrdersReject::GetSymbolID() const
	{
		if (BaseSize < offsetof(s_MarketOrdersReject, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}
	/*==========================================================================*/
	/****************************************************************************/
	// s_SubmitNewSingleOrder

	/*==========================================================================*/
	uint16_t s_SubmitNewSingleOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_SubmitNewSingleOrder::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	DTC::OrderTypeEnum s_SubmitNewSingleOrder::GetOrderType() const
	{			
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, OrderType) + sizeof(OrderType))
			return DTC::ORDER_TYPE_UNSET;

		return OrderType;	
	}

	/*==========================================================================*/
	DTC::BuySellEnum s_SubmitNewSingleOrder::GetBuySell() const
	{			
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, BuySell) + sizeof(BuySell))
			return DTC::BUY_SELL_UNSET;

		return BuySell;	
	}

	/*==========================================================================*/
	double s_SubmitNewSingleOrder::GetPrice1() const
	{
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, Price1) + sizeof(Price1))
			return 0.0;

		return Price1;
	}

	/*==========================================================================*/
	double s_SubmitNewSingleOrder::GetPrice2() const
	{
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, Price2) + sizeof(Price2))
			return 0.0;

		return Price2;
	}

	/*==========================================================================*/
	double s_SubmitNewSingleOrder::GetQuantity() const
	{
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, Quantity) + sizeof(Quantity))
			return 0.0;

		return Quantity;
	}

	/*==========================================================================*/
	DTC::TimeInForceEnum s_SubmitNewSingleOrder::GetTimeInForce() const
	{			
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, TimeInForce) + sizeof(TimeInForce))
			return DTC::TIF_UNSET;

		return TimeInForce;	
	}

	/*==========================================================================*/	 
	DTC::t_DateTime s_SubmitNewSingleOrder::GetGoodTillDateTime() const
	{
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}

	/*==========================================================================*/
	uint8_t s_SubmitNewSingleOrder::GetIsAutomatedOrder() const
	{
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, IsAutomatedOrder) + sizeof(IsAutomatedOrder))
			return 0;

		return IsAutomatedOrder;
	}

	/*==========================================================================*/
	uint8_t s_SubmitNewSingleOrder::GetIsParentOrder() const
	{
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, IsParentOrder) + sizeof(IsParentOrder))
			return 0;

		return IsParentOrder;
	}

	/*==========================================================================*/
	DTC::OpenCloseTradeEnum s_SubmitNewSingleOrder::GetOpenOrClose() const
	{
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, OpenOrClose) + sizeof(OpenOrClose))
			return DTC::TRADE_UNSET;

		return OpenOrClose;
	}

	/*==========================================================================*/
	double s_SubmitNewSingleOrder::GetMaxShowQuantity() const
	{
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, MaxShowQuantity) + sizeof(MaxShowQuantity))
			return 0.0;

		return MaxShowQuantity;
	}

	/*==========================================================================*/
	double s_SubmitNewSingleOrder::GetIntendedPositionQuantity() const
	{
		if (BaseSize < offsetof(s_SubmitNewSingleOrder, IntendedPositionQuantity) + sizeof(IntendedPositionQuantity))
			return 0;

		return IntendedPositionQuantity;
	}

	/****************************************************************************/
	// s_SubmitFlattenPositionOrder

	/*==========================================================================*/
	uint16_t s_SubmitFlattenPositionOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_SubmitFlattenPositionOrder::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	uint8_t s_SubmitFlattenPositionOrder::GetIsAutomatedOrder() const
	{
		if (BaseSize < offsetof(s_SubmitFlattenPositionOrder, IsAutomatedOrder) + sizeof(IsAutomatedOrder))
			return 0;

		return IsAutomatedOrder;
	}

	/****************************************************************************/
	// s_CancelReplaceOrder

	/*==========================================================================*/
	uint16_t s_CancelReplaceOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_CancelReplaceOrder::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	double s_CancelReplaceOrder::GetPrice1() const
	{
		if (BaseSize < offsetof(s_CancelReplaceOrder, Price1) + sizeof(Price1))
			return 0.0;

		return Price1;
	}

	/*==========================================================================*/
	double s_CancelReplaceOrder::GetPrice2() const
	{
		if (BaseSize < offsetof(s_CancelReplaceOrder, Price2) + sizeof(Price2))
			return 0.0;

		return Price2;
	}

	/*==========================================================================*/
	double s_CancelReplaceOrder::GetQuantity() const
	{
		if (BaseSize < offsetof(s_CancelReplaceOrder, Quantity) + sizeof(Quantity))
			return 0.0;

		return Quantity;
	}

	/*==========================================================================*/
	int8_t s_CancelReplaceOrder::GetPrice1IsSet() const
	{
		if (BaseSize < offsetof(s_CancelReplaceOrder, Price1IsSet) + sizeof(Price1IsSet))
			return 1;

		return Price1IsSet;
	}

	/*==========================================================================*/
	int8_t s_CancelReplaceOrder::GetPrice2IsSet() const
	{
		if (BaseSize < offsetof(s_CancelReplaceOrder, Price2IsSet) + sizeof(Price2IsSet))
			return 1;

		return Price2IsSet;
	}

	/*==========================================================================*/
	DTC::TimeInForceEnum s_CancelReplaceOrder::GetTimeInForce() const
	{
		if (BaseSize < offsetof(s_CancelReplaceOrder, TimeInForce) + sizeof(TimeInForce))
			return DTC::TIF_UNSET;

		return TimeInForce;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_CancelReplaceOrder::GetGoodTillDateTime() const
	{
		if (BaseSize < offsetof(s_CancelReplaceOrder, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}

	/*==========================================================================*/
	uint8_t s_CancelReplaceOrder::GetUpdatePrice1OffsetToParent() const
	{
		if (BaseSize < offsetof(s_CancelReplaceOrder, UpdatePrice1OffsetToParent) + sizeof(UpdatePrice1OffsetToParent))
			return 0;

		return UpdatePrice1OffsetToParent;
	}


	/****************************************************************************/
	// s_CancelOrder

	/*==========================================================================*/
	uint16_t s_CancelOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_CancelOrder::GetBaseSize() const
	{
		return BaseSize;
	}

	/****************************************************************************/
	// s_SubmitNewOCOOrder

	/*==========================================================================*/
	uint16_t s_SubmitNewOCOOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_SubmitNewOCOOrder::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	DTC::OrderTypeEnum s_SubmitNewOCOOrder::GetOrderType_1() const
	{			
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, OrderType_1) + sizeof(OrderType_1))
			return DTC::ORDER_TYPE_UNSET;

		return OrderType_1;	
	}

	/*==========================================================================*/
	DTC::OrderTypeEnum s_SubmitNewOCOOrder::GetOrderType_2() const
	{			
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, OrderType_2) + sizeof(OrderType_2))
			return DTC::ORDER_TYPE_UNSET;

		return OrderType_2;	
	}

	/*==========================================================================*/			 
	DTC::BuySellEnum s_SubmitNewOCOOrder::GetBuySell_1() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, BuySell_1) + sizeof(BuySell_1))
			return static_cast<DTC::BuySellEnum>(0);

		return BuySell_1;
	}

	/*==========================================================================*/
	DTC::BuySellEnum s_SubmitNewOCOOrder::GetBuySell_2() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, BuySell_2) + sizeof(BuySell_2))
			return static_cast<DTC::BuySellEnum>(0);

		return BuySell_2;
	}

	/*==========================================================================*/
	DTC::TimeInForceEnum s_SubmitNewOCOOrder::GetTimeInForce() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, TimeInForce) + sizeof(TimeInForce))
			return static_cast<DTC::TimeInForceEnum>(0);

		return TimeInForce;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_SubmitNewOCOOrder::GetGoodTillDateTime() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}	

	/*==========================================================================*/
	uint8_t s_SubmitNewOCOOrder::GetIsAutomatedOrder() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, IsAutomatedOrder) + sizeof(IsAutomatedOrder))
			return 0;

		return IsAutomatedOrder;
	}

	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetPrice1_1() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, Price1_1) + sizeof(Price1_1))
			return 0.0;

		return Price1_1;
	}

	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetPrice2_1() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, Price2_1) + sizeof(Price2_1))
			return 0.0;

		return Price2_1;
	}

	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetPrice1_2() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, Price1_2) + sizeof(Price1_2))
			return 0.0;

		return Price1_2;
	}

	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetPrice2_2() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, Price2_2) + sizeof(Price2_2))
			return 0.0;

		return Price2_2;
	}

	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetQuantity_1() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, Quantity_1) + sizeof(Quantity_1))
			return 0.0;

		return Quantity_1;
	}

	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetQuantity_2() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, Quantity_2) + sizeof(Quantity_2))
			return 0.0;

		return Quantity_2;
	}

	/*==========================================================================*/
	DTC::OpenCloseTradeEnum s_SubmitNewOCOOrder::GetOpenOrClose() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, OpenOrClose) + sizeof(OpenOrClose))
			return DTC::TRADE_UNSET;

		return OpenOrClose;
	}

	/*==========================================================================*/
	DTC::PartialFillHandlingEnum s_SubmitNewOCOOrder::GetPartialFillHandling() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, PartialFillHandling) + sizeof(PartialFillHandling))
			return DTC::PARTIAL_FILL_UNSET;

		return PartialFillHandling;
	}

	/*==========================================================================*/
	uint8_t s_SubmitNewOCOOrder::GetUseOffsets() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, UseOffsets) + sizeof(UseOffsets))
			return 0;

		return UseOffsets;
	}

	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetOffsetFromParent1() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, OffsetFromParent1) + sizeof(OffsetFromParent1))
			return 0.0;

		return OffsetFromParent1;
	}

	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetOffsetFromParent2() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, OffsetFromParent2) + sizeof(OffsetFromParent2))
			return 0.0;

		return OffsetFromParent2;
	}

	/*==========================================================================*/
	uint8_t s_SubmitNewOCOOrder::GetMaintainSamePricesOnParentFill() const
	{
		if (BaseSize < offsetof(s_SubmitNewOCOOrder, MaintainSamePricesOnParentFill) + sizeof(MaintainSamePricesOnParentFill))
			return 0;

		return MaintainSamePricesOnParentFill;
	}

	/****************************************************************************/
	// s_OpenOrdersRequest

	/*==========================================================================*/
	uint16_t s_OpenOrdersRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_OpenOrdersRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_OpenOrdersRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_OpenOrdersRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	int32_t s_OpenOrdersRequest::GetRequestAllOrders() const
	{
		if (BaseSize < offsetof(s_OpenOrdersRequest, RequestAllOrders) + sizeof(RequestAllOrders))
			return 0;

		return RequestAllOrders;
	}



	/****************************************************************************/
	// s_HistoricalOrderFillsRequest

	/*==========================================================================*/
	uint16_t s_HistoricalOrderFillsRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalOrderFillsRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_HistoricalOrderFillsRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillsRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	int32_t s_HistoricalOrderFillsRequest::GetNumberOfDays() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillsRequest, NumberOfDays) + sizeof(NumberOfDays))
			return 0;

		return NumberOfDays;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_HistoricalOrderFillsRequest::GetStartDateTime() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillsRequest, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}

	/****************************************************************************/
	// s_HistoricalOrderFillsReject

	/*==========================================================================*/
	uint16_t s_HistoricalOrderFillsReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalOrderFillsReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_HistoricalOrderFillsReject::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillsReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/****************************************************************************/
	// s_CurrentPositionsRequest

	/*==========================================================================*/
	uint16_t s_CurrentPositionsRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_CurrentPositionsRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_CurrentPositionsRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_CurrentPositionsRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}


	/****************************************************************************/
	// s_CurrentPositionsRequestReject

	/*==========================================================================*/
	uint16_t s_CurrentPositionsReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_CurrentPositionsReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_CurrentPositionsReject::GetRequestID() const
	{
		if (BaseSize < offsetof(s_CurrentPositionsReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}


	/****************************************************************************/
	// s_OrderUpdateReport

	/*==========================================================================*/
	uint16_t s_OrderUpdate::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_OrderUpdate::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetOrderQuantity() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, OrderQuantity) + sizeof(OrderQuantity))
			return DBL_MAX;

		return OrderQuantity;
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetFilledQuantity() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, FilledQuantity) + sizeof(FilledQuantity))
			return DBL_MAX;

		return FilledQuantity;
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetRemainingQuantity() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, RemainingQuantity) + sizeof(RemainingQuantity))
			return DBL_MAX;

		return RemainingQuantity;
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetLastFillQuantity() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, LastFillQuantity) + sizeof(LastFillQuantity))
			return DBL_MAX;

		return LastFillQuantity;
	}
	
	/*==========================================================================*/
	int32_t s_OrderUpdate::GetRequestID() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	
	/*==========================================================================*/
	int32_t s_OrderUpdate::GetTotalNumMessages() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, TotalNumMessages) + sizeof(TotalNumMessages))
			return 0;

		return TotalNumMessages;
	}

	/*==========================================================================*/
	int32_t s_OrderUpdate::GetMessageNumber() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}
	
	/*==========================================================================*/
	DTC::OrderStatusEnum s_OrderUpdate::GetOrderStatus() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, OrderStatus) + sizeof(OrderStatus))
			return static_cast<DTC::OrderStatusEnum>(0);

		return OrderStatus;
	}
	
	/*==========================================================================*/
	DTC::OrderUpdateReasonEnum s_OrderUpdate::GetOrderUpdateReason() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, OrderUpdateReason) + sizeof(OrderUpdateReason))
			return static_cast<DTC::OrderUpdateReasonEnum>(0);

		return OrderUpdateReason;
	}
	
	/*==========================================================================*/
	DTC::OrderTypeEnum s_OrderUpdate::GetOrderType() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, OrderType) + sizeof(OrderType))
			return static_cast<DTC::OrderTypeEnum>(0);

		return OrderType;
	}
	
	/*==========================================================================*/
	DTC::BuySellEnum s_OrderUpdate::GetBuySell() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, BuySell) + sizeof(BuySell))
			return static_cast<DTC::BuySellEnum>(0);

		return BuySell;
	}
	
	/*==========================================================================*/
	double s_OrderUpdate::GetPrice1() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, Price1) + sizeof(Price1))
			return DBL_MAX;

		return Price1;
	}
	
	/*==========================================================================*/
	double s_OrderUpdate::GetPrice2() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, Price2) + sizeof(Price2))
			return DBL_MAX;

		return Price2;
	}

	/*==========================================================================*/
	DTC::TimeInForceEnum s_OrderUpdate::GetTimeInForce() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, TimeInForce) + sizeof(TimeInForce))
			return static_cast<DTC::TimeInForceEnum>(0);

		return TimeInForce;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_OrderUpdate::GetGoodTillDateTime() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetAverageFillPrice() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, AverageFillPrice) + sizeof(AverageFillPrice))
			return DBL_MAX;

		return AverageFillPrice;
	}
	
	/*==========================================================================*/
	double s_OrderUpdate::GetLastFillPrice() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, LastFillPrice) + sizeof(LastFillPrice))
			return DBL_MAX;

		return LastFillPrice;
	}
	
	/*==========================================================================*/
	DTC::t_DateTime s_OrderUpdate::GetLastFillDateTime() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, LastFillDateTime) + sizeof(LastFillDateTime))
			return 0;

		return LastFillDateTime;
	}

	/*==========================================================================*/
	uint8_t s_OrderUpdate::GetNoOrders() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, NoOrders) + sizeof(NoOrders))
			return 0;

		return NoOrders;
	}

	/*==========================================================================*/
	DTC::OpenCloseTradeEnum s_OrderUpdate::GetOpenOrClose() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, OpenOrClose) + sizeof(OpenOrClose))
			return DTC::TRADE_UNSET;

		return OpenOrClose;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_OrderUpdate::GetOrderReceivedDateTime() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, OrderReceivedDateTime) + sizeof(OrderReceivedDateTime))
			return 0;

		return OrderReceivedDateTime;
	}

	/*==========================================================================*/
	DTC::t_DateTimeWithMilliseconds s_OrderUpdate::GetLatestTransactionDateTime() const
	{
		if (BaseSize < offsetof(s_OrderUpdate, LatestTransactionDateTime) + sizeof(LatestTransactionDateTime))
			return 0.0;

		return LatestTransactionDateTime;
	}

	/****************************************************************************/
	// s_OpenOrdersRequestReject

	/*==========================================================================*/
	uint16_t s_OpenOrdersReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_OpenOrdersReject::GetBaseSize() const
	{
		return BaseSize;
	}
	/*==========================================================================*/
	int32_t s_OpenOrdersReject::GetRequestID() const
	{
		if (BaseSize < offsetof(s_OpenOrdersReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/****************************************************************************/
	// s_HistoricalOrderFillResponse

	/*==========================================================================*/
	uint16_t s_HistoricalOrderFillResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalOrderFillResponse::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_HistoricalOrderFillResponse::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	int32_t s_HistoricalOrderFillResponse::GetMessageNumber() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}

	/*==========================================================================*/
	int32_t s_HistoricalOrderFillResponse::GetTotalNumberMessages() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, TotalNumberMessages) + sizeof(TotalNumberMessages))
			return 0;

		return TotalNumberMessages;
	}

	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetPrice() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetQuantity() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_HistoricalOrderFillResponse::GetDateTime() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	DTC::BuySellEnum s_HistoricalOrderFillResponse::GetBuySell() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, BuySell) + sizeof(BuySell))
			return static_cast<DTC::BuySellEnum>(0);

		return BuySell;
	}

	/*==========================================================================*/
	DTC::OpenCloseTradeEnum s_HistoricalOrderFillResponse::GetOpenClose() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, OpenClose) + sizeof(OpenClose))
			return static_cast<DTC::OpenCloseTradeEnum>(0);

		return OpenClose;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalOrderFillResponse::GetNoOrderFills() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, NoOrderFills) + sizeof(NoOrderFills))
			return 0;

		return NoOrderFills;
	}

	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetHighPriceDuringPosition() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, HighPriceDuringPosition) + sizeof(HighPriceDuringPosition))
			return 0.0;

		return HighPriceDuringPosition;
	}

	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetLowPriceDuringPosition() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, LowPriceDuringPosition) + sizeof(LowPriceDuringPosition))
			return 0.0;

		return LowPriceDuringPosition;
	}

	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetPositionQuantity() const
	{
		if (BaseSize < offsetof(s_HistoricalOrderFillResponse, PositionQuantity) + sizeof(PositionQuantity))
			return DBL_MAX;

		return PositionQuantity;
	}

	/****************************************************************************/
	// s_PositionUpdate

	/*==========================================================================*/
	uint16_t s_PositionUpdate::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_PositionUpdate::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_PositionUpdate::GetRequestID() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	int32_t s_PositionUpdate::GetMessageNumber() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}

	/*==========================================================================*/
	int32_t s_PositionUpdate::GetTotalNumberMessages() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, TotalNumberMessages) + sizeof(TotalNumberMessages))
			return 0;

		return TotalNumberMessages;
	}	

	/*==========================================================================*/
	double s_PositionUpdate::GetQuantity() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}
	
	/*==========================================================================*/
	double s_PositionUpdate::GetAveragePrice() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, AveragePrice) + sizeof(AveragePrice))
			return 0;

		return AveragePrice;
	}
	
	/*==========================================================================*/	
	uint8_t s_PositionUpdate::GetNoPositions() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, NoPositions) + sizeof(NoPositions))
			return 0;

		return NoPositions;
	}
	
	/*==========================================================================*/
	uint8_t s_PositionUpdate::GetUnsolicited() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, Unsolicited) + sizeof(Unsolicited))
			return 0;

		return Unsolicited;
	}

	/*==========================================================================*/
	double s_PositionUpdate::GetMarginRequirement() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, MarginRequirement) + sizeof(MarginRequirement))
			return 0.0;

		return MarginRequirement;
	}

	/*==========================================================================*/
	DTC::t_DateTime4Byte s_PositionUpdate::GetEntryDateTime() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, EntryDateTime) + sizeof(EntryDateTime))
			return 0;

		return EntryDateTime;
	}

	/*==========================================================================*/
	double s_PositionUpdate::GetOpenProfitLoss() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, OpenProfitLoss) + sizeof(OpenProfitLoss))
			return 0;

		return OpenProfitLoss;
	}

	/*==========================================================================*/
	double s_PositionUpdate::GetHighPriceDuringPosition() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, HighPriceDuringPosition) + sizeof(HighPriceDuringPosition))
			return 0;

		return HighPriceDuringPosition;
	}

	/*==========================================================================*/
	double s_PositionUpdate::GetLowPriceDuringPosition() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, LowPriceDuringPosition) + sizeof(LowPriceDuringPosition))
			return 0;

		return LowPriceDuringPosition;
	}

	/*==========================================================================*/
	double s_PositionUpdate::GetQuantityLimit() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, QuantityLimit) + sizeof(QuantityLimit))
			return 0;

		return QuantityLimit;
	}

	/*==========================================================================*/
	double s_PositionUpdate::GetMaxPotentialPostionQuantity() const
	{
		if (BaseSize < offsetof(s_PositionUpdate, MaxPotentialPostionQuantity) + sizeof(MaxPotentialPostionQuantity))
			return 0;

		return MaxPotentialPostionQuantity;
	}

	/****************************************************************************/
	// s_AddCorrectingOrderFill

	/*==========================================================================*/
	uint16_t s_AddCorrectingOrderFill::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_AddCorrectingOrderFill::GetBaseSize() const
	{
		return BaseSize;
	}
	/*==========================================================================*/
	DTC::BuySellEnum s_AddCorrectingOrderFill::GetBuySell() const
	{
		if (BaseSize < offsetof(s_AddCorrectingOrderFill, BuySell) + sizeof(BuySell))
			return DTC::BUY_SELL_UNSET;

		return BuySell;
	}
	/*==========================================================================*/
	double s_AddCorrectingOrderFill::GetFillPrice() const
	{
		if (BaseSize < offsetof(s_AddCorrectingOrderFill, FillPrice) + sizeof(FillPrice))
			return 0;

		return FillPrice;
	}
	/*==========================================================================*/
	double s_AddCorrectingOrderFill::GetFillQuantity() const
	{
		if (BaseSize < offsetof(s_AddCorrectingOrderFill, FillQuantity) + sizeof(FillQuantity))
			return 0;

		return FillQuantity;
	}

	/****************************************************************************/
	// s_CorrectingOrderFillResponse

	/*==========================================================================*/
		uint16_t s_CorrectingOrderFillResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_CorrectingOrderFillResponse::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	uint8_t s_CorrectingOrderFillResponse::GetIsError() const
	{
		if (BaseSize < offsetof(s_CorrectingOrderFillResponse, IsError) + sizeof(IsError))
			return 0;

		return IsError;
	}

	/*==========================================================================*/

	/****************************************************************************/
	// s_TradeAccountResponse

	/*==========================================================================*/
	uint16_t s_TradeAccountResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_TradeAccountResponse::GetBaseSize() const
	{
		return BaseSize;
	}
	
	/*==========================================================================*/
	int32_t s_TradeAccountResponse::GetTotalNumberMessages() const
	{
		if (BaseSize < offsetof(s_TradeAccountResponse, TotalNumberMessages) + sizeof(TotalNumberMessages))
			return 0;

		return TotalNumberMessages;
	}	

	/*==========================================================================*/
	int32_t s_TradeAccountResponse::GetMessageNumber() const
	{
		if (BaseSize < offsetof(s_TradeAccountResponse, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}

	/*==========================================================================*/
	int32_t s_TradeAccountResponse::GetRequestID() const
	{
		if (BaseSize < offsetof(s_TradeAccountResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}


	/*==========================================================================*/
	int32_t s_TradeAccountResponse::GetTradingIsDisabled() const
	{
		if (BaseSize < offsetof(s_TradeAccountResponse, TradingIsDisabled) + sizeof(TradingIsDisabled))
			return 0;

		return TradingIsDisabled;
	}

	/****************************************************************************/
	// s_ExchangeListResponse

	/*==========================================================================*/
	uint16_t s_ExchangeListResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_ExchangeListResponse::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_ExchangeListResponse::GetRequestID() const
	{
		if (BaseSize < offsetof(s_ExchangeListResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	uint8_t s_ExchangeListResponse::GetIsFinalMessage() const
	{
		if (BaseSize < offsetof(s_ExchangeListResponse, IsFinalMessage) + sizeof(IsFinalMessage))
			return 0;

		return IsFinalMessage;
	}


	/****************************************************************************/
	// s_SymbolsForExchangeRequest

	/*==========================================================================*/
	uint16_t s_SymbolsForExchangeRequest::GetMessageSize() const
	{
		return Size;
	}

	uint16_t s_SymbolsForExchangeRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_SymbolsForExchangeRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_SymbolsForExchangeRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::SecurityTypeEnum s_SymbolsForExchangeRequest::GetSecurityType() const
	{
		if (BaseSize < offsetof(s_SymbolsForExchangeRequest, SecurityType) + sizeof(SecurityType))
			return static_cast<DTC::SecurityTypeEnum>(0);

		return SecurityType;
	}

	/*==========================================================================*/
	DTC::RequestActionEnum s_SymbolsForExchangeRequest::GetRequestAction() const
	{
		if (BaseSize < offsetof(s_SymbolsForExchangeRequest, RequestAction) + sizeof(RequestAction))
			return DTC::RequestActionEnum::SUBSCRIBE;

		return RequestAction;
	}

	/****************************************************************************/
	// s_UnderlyingSymbolsForExchangeRequest

	/*==========================================================================*/
	uint16_t s_UnderlyingSymbolsForExchangeRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_UnderlyingSymbolsForExchangeRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_UnderlyingSymbolsForExchangeRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_UnderlyingSymbolsForExchangeRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::SecurityTypeEnum s_UnderlyingSymbolsForExchangeRequest::GetSecurityType() const
	{
		if (BaseSize < offsetof(s_UnderlyingSymbolsForExchangeRequest, SecurityType) + sizeof(SecurityType))
			return static_cast<DTC::SecurityTypeEnum>(0);

		return SecurityType;
	}

	/****************************************************************************/
	// s_SymbolsForUnderlyingRequest

	/*==========================================================================*/
	uint16_t s_SymbolsForUnderlyingRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_SymbolsForUnderlyingRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_SymbolsForUnderlyingRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_SymbolsForUnderlyingRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::SecurityTypeEnum s_SymbolsForUnderlyingRequest::GetSecurityType() const
	{
		if (BaseSize < offsetof(s_SymbolsForUnderlyingRequest, SecurityType) + sizeof(SecurityType))
			return static_cast<DTC::SecurityTypeEnum>(0);

		return SecurityType;
	}


	/****************************************************************************/
	// s_SymbolSearchRequest

	/*==========================================================================*/
	uint16_t s_SymbolSearchRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_SymbolSearchRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_SymbolSearchRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_SymbolSearchRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::SecurityTypeEnum s_SymbolSearchRequest::GetSecurityType() const
	{
		if (BaseSize < offsetof(s_SymbolSearchRequest, SecurityType) + sizeof(SecurityType))
			return static_cast<DTC::SecurityTypeEnum>(0);

		return SecurityType;
	}

	/*==========================================================================*/
	DTC::SearchTypeEnum s_SymbolSearchRequest::GetSearchType() const
	{
		if (BaseSize < offsetof(s_SymbolSearchRequest, SearchType) + sizeof(SearchType))
			return static_cast<DTC::SearchTypeEnum>(0);

		return SearchType;
	}

	/****************************************************************************/
	// s_SecurityDefinitionForSymbolRequest

	/*==========================================================================*/
	uint16_t s_SecurityDefinitionForSymbolRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_SecurityDefinitionForSymbolRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_SecurityDefinitionForSymbolRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionForSymbolRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}


	/****************************************************************************/
	// s_SecurityDefinitionResponse

	/*==========================================================================*/
	uint16_t s_SecurityDefinitionResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_SecurityDefinitionResponse::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_SecurityDefinitionResponse::GetRequestID() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::SecurityTypeEnum s_SecurityDefinitionResponse::GetSecurityType() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, SecurityType) + sizeof(SecurityType))
			return DTC::SECURITY_TYPE_UNSET;

		return SecurityType;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetMinPriceIncrement() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, MinPriceIncrement) + sizeof(MinPriceIncrement))
			return 0.0;

		return MinPriceIncrement;
	}

	/*==========================================================================*/
	DTC::PriceDisplayFormatEnum s_SecurityDefinitionResponse::GetPriceDisplayFormat() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, PriceDisplayFormat) + sizeof(PriceDisplayFormat))
			return DTC::PRICE_DISPLAY_FORMAT_UNSET;

		return PriceDisplayFormat;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetCurrencyValuePerIncrement() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, CurrencyValuePerIncrement) + sizeof(CurrencyValuePerIncrement))
			return 0.0;

		return CurrencyValuePerIncrement;
	}

	/*==========================================================================*/
	uint8_t s_SecurityDefinitionResponse::GetIsFinalMessage() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, IsFinalMessage) + sizeof(IsFinalMessage))
			return 0;

		return IsFinalMessage;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetFloatToIntPriceMultiplier() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, FloatToIntPriceMultiplier) + sizeof(FloatToIntPriceMultiplier))
			return 1.0f;

		return FloatToIntPriceMultiplier;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetIntToFloatPriceDivisor() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, IntToFloatPriceDivisor) + sizeof(IntToFloatPriceDivisor))
			return 1.0f;

		return IntToFloatPriceDivisor;
	}

	/*==========================================================================*/
	uint8_t s_SecurityDefinitionResponse::GetUpdatesBidAskOnly() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, UpdatesBidAskOnly) + sizeof(UpdatesBidAskOnly))
			return 0;

		return UpdatesBidAskOnly;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetStrikePrice() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, StrikePrice) + sizeof(StrikePrice))
			return 0.0;

		return StrikePrice;
	}

	/*==========================================================================*/
	DTC::PutCallEnum s_SecurityDefinitionResponse::GetPutOrCall() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, PutOrCall) + sizeof(PutOrCall))
			return DTC::PC_UNSET;

		return PutOrCall;
	}

	/*==========================================================================*/
	uint32_t s_SecurityDefinitionResponse::GetShortInterest() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, ShortInterest) + sizeof(ShortInterest))
			return 0;

		return ShortInterest;
	}

	/*==========================================================================*/
	DTC::t_DateTime4Byte s_SecurityDefinitionResponse::GetSecurityExpirationDate() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, SecurityExpirationDate) + sizeof(SecurityExpirationDate))
			return 0;

		return SecurityExpirationDate;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetBuyRolloverInterest() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, BuyRolloverInterest) + sizeof(BuyRolloverInterest))
			return 0.0;

		return BuyRolloverInterest;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetSellRolloverInterest() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, SellRolloverInterest) + sizeof(SellRolloverInterest))
			return 0.0;

		return SellRolloverInterest;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetEarningsPerShare() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, EarningsPerShare) + sizeof(EarningsPerShare))
			return 0.0;

		return EarningsPerShare;
	}

	/*==========================================================================*/
	uint32_t s_SecurityDefinitionResponse::GetSharesOutstanding() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, SharesOutstanding) + sizeof(SharesOutstanding))
			return 0;

		return SharesOutstanding;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetIntToFloatQuantityDivisor() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, IntToFloatQuantityDivisor) + sizeof(IntToFloatQuantityDivisor))
			return 0.0;

		return IntToFloatQuantityDivisor;
	}

	/*==========================================================================*/
	uint8_t s_SecurityDefinitionResponse::GetHasMarketDepthData() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, HasMarketDepthData) + sizeof(HasMarketDepthData))
			return 1;

		return HasMarketDepthData;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetDisplayPriceMultiplier() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, DisplayPriceMultiplier) + sizeof(DisplayPriceMultiplier))
			return 1.0;

		return DisplayPriceMultiplier;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetInitialMarginRequirement() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, InitialMarginRequirement) + sizeof(InitialMarginRequirement))
			return 0.0;

		return InitialMarginRequirement;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetMaintenanceMarginRequirement() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, MaintenanceMarginRequirement) + sizeof(MaintenanceMarginRequirement))
			return 0.0;

		return MaintenanceMarginRequirement;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetContractSize() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, ContractSize) + sizeof(ContractSize))
			return 0.0;

		return ContractSize;
	}

	/*==========================================================================*/
	uint32_t s_SecurityDefinitionResponse::GetOpenInterest() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, OpenInterest) + sizeof(OpenInterest))
			return 0;

		return OpenInterest;
	}

	/*==========================================================================*/
	DTC::t_DateTime4Byte s_SecurityDefinitionResponse::GetRolloverDate() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, RolloverDate) + sizeof(RolloverDate))
			return 0;

		return RolloverDate;
	}

	/*==========================================================================*/
	uint8_t s_SecurityDefinitionResponse::GetIsDelayed() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, IsDelayed) + sizeof(IsDelayed))
			return 0;

		return IsDelayed;
	}

	/*==========================================================================*/
	int64_t s_SecurityDefinitionResponse::GetSecurityIdentifier() const
	{
		if (BaseSize < offsetof(s_SecurityDefinitionResponse, SecurityIdentifier) + sizeof(SecurityIdentifier))
			return 0;

		return SecurityIdentifier;
	}

	/****************************************************************************/
	// s_SecurityDefinitionReject

	/*==========================================================================*/
	uint16_t s_SecurityDefinitionReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_SecurityDefinitionReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_SecurityDefinitionReject::GetRequestID() const
	{

		if (BaseSize < offsetof(s_SecurityDefinitionReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/****************************************************************************/
	// s_AccountBalanceRequest

	/*==========================================================================*/
	uint16_t s_AccountBalanceRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_AccountBalanceRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceRequest::GetRequestID() const
	{

		if (BaseSize < offsetof(s_AccountBalanceRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/****************************************************************************/
	// s_AccountBalanceReject

	/*==========================================================================*/
	uint16_t s_AccountBalanceReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_AccountBalanceReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceReject::GetRequestID() const
	{

		if (BaseSize < offsetof(s_AccountBalanceReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}


	/****************************************************************************/
	// s_AccountBalanceUpdate

	/*==========================================================================*/
	uint16_t s_AccountBalanceUpdate::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_AccountBalanceUpdate::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceUpdate::GetRequestID() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetCashBalance() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, CashBalance) + sizeof(CashBalance))
			return 0;

		return CashBalance;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetBalanceAvailableForNewPositions() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, BalanceAvailableForNewPositions) + sizeof(BalanceAvailableForNewPositions))
			return 0;

		return BalanceAvailableForNewPositions;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetSecuritiesValue() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, SecuritiesValue) + sizeof(SecuritiesValue))
			return 0;

		return SecuritiesValue;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetMarginRequirement() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, MarginRequirement) + sizeof(MarginRequirement))
			return 0;

		return MarginRequirement;
	}

	
	/*==========================================================================*/
	int32_t s_AccountBalanceUpdate::GetTotalNumberMessages() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, TotalNumberMessages) + sizeof(TotalNumberMessages))
			return 0;

		return TotalNumberMessages;
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceUpdate::GetMessageNumber() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetNoAccountBalances() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, NoAccountBalances) + sizeof(NoAccountBalances))
			return 0;

		return NoAccountBalances;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetUnsolicited() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, Unsolicited) + sizeof(Unsolicited))
			return 0;

		return Unsolicited;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetOpenPositionsProfitLoss() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, OpenPositionsProfitLoss) + sizeof(OpenPositionsProfitLoss))
			return 0.0;

		return OpenPositionsProfitLoss;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetDailyProfitLoss() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, DailyProfitLoss) + sizeof(DailyProfitLoss))
			return 0.0;

		return DailyProfitLoss;
	}

	/*==========================================================================*/
	uint64_t s_AccountBalanceUpdate::GetTransactionIdentifier() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, TransactionIdentifier) + sizeof(TransactionIdentifier))
			return 0;

		return TransactionIdentifier;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetDailyNetLossLimit() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, DailyNetLossLimit) + sizeof(DailyNetLossLimit))
			return 0.0;

		return DailyNetLossLimit;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetTrailingAccountValueToLimitPositions() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, TrailingAccountValueToLimitPositions) + sizeof(TrailingAccountValueToLimitPositions))
			return 0.0;

		return TrailingAccountValueToLimitPositions;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetDailyNetLossLimitReached() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, DailyNetLossLimitReached) + sizeof(DailyNetLossLimitReached))
			return 0;

		return DailyNetLossLimitReached;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetIsUnderRequiredMargin() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, IsUnderRequiredMargin) + sizeof(IsUnderRequiredMargin))
			return 0;

		return IsUnderRequiredMargin;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetClosePositionsAtEndOfDay() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, ClosePositionsAtEndOfDay) + sizeof(ClosePositionsAtEndOfDay))
			return 0;

		return ClosePositionsAtEndOfDay;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetTradingIsDisabled() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, TradingIsDisabled) + sizeof(TradingIsDisabled))
			return 0;

		return TradingIsDisabled;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetIsUnderRequiredAccountValue() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, IsUnderRequiredAccountValue) + sizeof(IsUnderRequiredAccountValue))
			return 0;

		return IsUnderRequiredAccountValue;
	}

	/*==========================================================================*/
	DTC::t_DateTimeWithMicrosecondsInt s_AccountBalanceUpdate::GetTransactionDateTime() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, TransactionDateTime) + sizeof(TransactionDateTime))
			return 0;

		return TransactionDateTime;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetMarginRequirementFull() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, MarginRequirementFull) + sizeof(MarginRequirementFull))
			return 0.0;

		return MarginRequirementFull;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetMarginRequirementFullPositionsOnly() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, MarginRequirementFullPositionsOnly) + sizeof(MarginRequirementFullPositionsOnly))
			return 0.0;

		return MarginRequirementFullPositionsOnly;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetPeakMarginRequirement() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, PeakMarginRequirement) + sizeof(PeakMarginRequirement))
			return 0.0;

		return PeakMarginRequirement;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetEndOfDayAccountValue() const
	{
		if (BaseSize < offsetof(s_AccountBalanceUpdate, EndOfDayAccountValue) + sizeof(EndOfDayAccountValue))
			return 0.0;

		return EndOfDayAccountValue;
	}

	/****************************************************************************/
	// s_AccountBalanceAdjustment

	/*==========================================================================*/
	uint16_t s_AccountBalanceAdjustment::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_AccountBalanceAdjustment::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceAdjustment::GetRequestID() const
	{
		if (BaseSize < offsetof(s_AccountBalanceAdjustment, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	double s_AccountBalanceAdjustment::GetCreditAmount() const
	{
		if (BaseSize < offsetof(s_AccountBalanceAdjustment, CreditAmount) + sizeof(CreditAmount))
			return 0.0;

		return CreditAmount;
	}

	/*==========================================================================*/
	double s_AccountBalanceAdjustment::GetDebitAmount() const
	{
		if (BaseSize < offsetof(s_AccountBalanceAdjustment, DebitAmount) + sizeof(DebitAmount))
			return 0.0;

		return DebitAmount;
	}

	uint8_t s_AccountBalanceAdjustment::GetRecalculateDailyLossLimit() const
	{
		if (BaseSize < offsetof(s_AccountBalanceAdjustment, RecalculateDailyLossLimit) + sizeof(RecalculateDailyLossLimit))
		{
			return 0;
		}

		return RecalculateDailyLossLimit;
	}

	/****************************************************************************/
	// s_AccountBalanceAdjustmentReject

	/*==========================================================================*/
	uint16_t s_AccountBalanceAdjustmentReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_AccountBalanceAdjustmentReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceAdjustmentReject::GetRequestID() const
	{

		if (BaseSize < offsetof(s_AccountBalanceAdjustmentReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/****************************************************************************/
	// s_AccountBalanceAdjustmentComplete

	/*==========================================================================*/
	uint16_t s_AccountBalanceAdjustmentComplete::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_AccountBalanceAdjustmentComplete::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceAdjustmentComplete::GetRequestID() const
	{
		if (BaseSize < offsetof(s_AccountBalanceAdjustmentComplete, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	int64_t s_AccountBalanceAdjustmentComplete::GetTransactionID() const
	{
		if (BaseSize < offsetof(s_AccountBalanceAdjustmentComplete, TransactionID) + sizeof(TransactionID))
			return 0;

		return TransactionID;
	}

	/*==========================================================================*/
	double s_AccountBalanceAdjustmentComplete::GetNewBalance() const
	{
		if (BaseSize < offsetof(s_AccountBalanceAdjustmentComplete, NewBalance) + sizeof(NewBalance))
			return 0;

		return NewBalance;
	}

	/****************************************************************************/
	// s_HistoricalAccountBalancesRequest

	/*==========================================================================*/
	uint16_t s_HistoricalAccountBalancesRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalAccountBalancesRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_HistoricalAccountBalancesRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalAccountBalancesRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_HistoricalAccountBalancesRequest::GetStartDateTime() const
	{
		if (BaseSize < offsetof(s_HistoricalAccountBalancesRequest, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}

	/****************************************************************************/
	// s_HistoricalAccountBalancesReject

	/*==========================================================================*/
	uint16_t s_HistoricalAccountBalancesReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalAccountBalancesReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	uint32_t s_HistoricalAccountBalancesReject::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalAccountBalancesReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/****************************************************************************/
	// s_HistoricalAccountBalanceResponse

	/*==========================================================================*/
	uint16_t s_HistoricalAccountBalanceResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalAccountBalanceResponse::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_HistoricalAccountBalanceResponse::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalAccountBalanceResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::t_DateTimeWithMilliseconds s_HistoricalAccountBalanceResponse::GetDateTime() const
	{
		if (BaseSize < offsetof(s_HistoricalAccountBalanceResponse, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	double s_HistoricalAccountBalanceResponse::GetCashBalance() const
	{
		if (BaseSize < offsetof(s_HistoricalAccountBalanceResponse, CashBalance) + sizeof(CashBalance))
			return 0.0;

		return CashBalance;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalAccountBalanceResponse::GetIsFinalResponse() const
	{
		if (BaseSize < offsetof(s_HistoricalAccountBalanceResponse, IsFinalResponse) + sizeof(IsFinalResponse))
			return 0;

		return IsFinalResponse;
	}


	/*==========================================================================*/
	uint8_t s_HistoricalAccountBalanceResponse::GetNoAccountBalances() const
	{
		if (BaseSize < offsetof(s_HistoricalAccountBalanceResponse, NoAccountBalances) + sizeof(NoAccountBalances))
			return 0;

		return NoAccountBalances;
	}

	/****************************************************************************/
	// s_UserMessage

	/*==========================================================================*/
	uint16_t s_UserMessage::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_UserMessage::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	uint8_t s_UserMessage::GetIsPopupMessage() const
	{
		if (BaseSize < offsetof(s_UserMessage, IsPopupMessage) + sizeof(IsPopupMessage))
			return 0;

		return IsPopupMessage;
	}


	/****************************************************************************/
	// s_GeneralLogMessage

	/*==========================================================================*/
	uint16_t s_GeneralLogMessage::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_GeneralLogMessage::GetBaseSize() const
	{
		return BaseSize;
	}

	/****************************************************************************/
	// s_AlertMessage

	/*==========================================================================*/
	uint16_t s_AlertMessage::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_AlertMessage::GetBaseSize() const
	{
		return BaseSize;
	}

	/****************************************************************************/
	// s_JournalEntryAdd

	/*==========================================================================*/
	uint16_t s_JournalEntryAdd::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_JournalEntryAdd::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_JournalEntryAdd::GetDateTime() const
	{
		if (BaseSize < offsetof(s_JournalEntryAdd, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/****************************************************************************/
	// s_JournalEntriesReject

	/*==========================================================================*/
	uint16_t s_JournalEntriesReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_JournalEntriesReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_JournalEntriesReject::GetRequestID() const
	{
		if (BaseSize < offsetof(s_JournalEntriesReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/****************************************************************************/
	// s_JournalEntryResponse

	/*==========================================================================*/
	uint16_t s_JournalEntryResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_JournalEntryResponse::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_JournalEntryResponse::GetDateTime() const
	{
		if (BaseSize < offsetof(s_JournalEntryResponse, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	uint8_t s_JournalEntryResponse::GetIsFinalResponse() const
	{
		if (BaseSize < offsetof(s_JournalEntryResponse, IsFinalResponse) + sizeof(IsFinalResponse))
			return 0;

		return IsFinalResponse;
	}

	/****************************************************************************/
	// s_HistoricalPriceDataRequest

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	uint32_t s_HistoricalPriceDataRequest::GetMaxDaysToReturn() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataRequest, MaxDaysToReturn) + sizeof(MaxDaysToReturn))
			return 0;

		return MaxDaysToReturn;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_HistoricalPriceDataRequest::GetEndDateTime() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataRequest, EndDateTime) + sizeof(EndDateTime))
			return 0;

		return EndDateTime;
	}

	/*==========================================================================*/
	DTC::t_DateTime s_HistoricalPriceDataRequest::GetStartDateTime() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataRequest, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}

	/*==========================================================================*/
	DTC::HistoricalDataIntervalEnum s_HistoricalPriceDataRequest::GetRecordInterval() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataRequest, RecordInterval) + sizeof(RecordInterval))
			return static_cast<DTC::HistoricalDataIntervalEnum>(0);

		return RecordInterval;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataRequest::GetUseZLibCompression() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataRequest, UseZLibCompression) + sizeof(UseZLibCompression))
			return 0;

		return UseZLibCompression;
	}
	
	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataRequest::GetRequestDividendAdjustedStockData() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataRequest, RequestDividendAdjustedStockData) + sizeof(RequestDividendAdjustedStockData))
			return 0;

		return RequestDividendAdjustedStockData;
	}
	
	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataRequest::GetInteger_1() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataRequest, Integer_1) + sizeof(Integer_1))
			return 0;

		return Integer_1;
	}

	/****************************************************************************/
	// s_HistoricalPriceDataReject

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_HistoricalPriceDataReject::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::HistoricalPriceDataRejectReasonCodeEnum s_HistoricalPriceDataReject::GetRejectReasonCode() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataReject, RejectReasonCode) + sizeof(RejectReasonCode))
			return DTC::HPDR_UNSET;

		return RejectReasonCode;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataReject::GetRetryTimeInSeconds() const
	{
		if (BaseSize < offsetof(s_HistoricalPriceDataReject, RetryTimeInSeconds) + sizeof(RetryTimeInSeconds))
			return 0;

		return RetryTimeInSeconds;
	}

	/****************************************************************************/
	// s_HistoricalMarketDepthDataRequest

	/*==========================================================================*/
	uint16_t s_HistoricalMarketDepthDataRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalMarketDepthDataRequest::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_HistoricalMarketDepthDataRequest::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalMarketDepthDataRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::t_DateTimeWithMicrosecondsInt s_HistoricalMarketDepthDataRequest::GetStartDateTime() const
	{
		if (BaseSize < offsetof(s_HistoricalMarketDepthDataRequest, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}

	/*==========================================================================*/
	DTC::t_DateTimeWithMicrosecondsInt s_HistoricalMarketDepthDataRequest::GetEndDateTime() const

	{
		if (BaseSize < offsetof(s_HistoricalMarketDepthDataRequest, EndDateTime) + sizeof(EndDateTime))
			return 0;

		return EndDateTime;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalMarketDepthDataRequest::GetUseZLibCompression() const

	{
		if (BaseSize < offsetof(s_HistoricalMarketDepthDataRequest, UseZLibCompression) + sizeof(UseZLibCompression))
			return 0;

		return UseZLibCompression;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalMarketDepthDataRequest::GetInteger_1() const
	{
		if (BaseSize < offsetof(s_HistoricalMarketDepthDataRequest, Integer_1) + sizeof(Integer_1))
			return 0;

		return Integer_1;
	}

	/****************************************************************************/
	// s_HistoricalMarketDepthDataReject

	/*==========================================================================*/
	uint16_t s_HistoricalMarketDepthDataReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalMarketDepthDataReject::GetBaseSize() const
	{
		return BaseSize;
	}

	/*==========================================================================*/
	int32_t s_HistoricalMarketDepthDataReject::GetRequestID() const
	{
		if (BaseSize < offsetof(s_HistoricalMarketDepthDataReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	DTC::HistoricalPriceDataRejectReasonCodeEnum s_HistoricalMarketDepthDataReject::GetRejectReasonCode() const
	{
		if (BaseSize < offsetof(s_HistoricalMarketDepthDataReject, RejectReasonCode) + sizeof(RejectReasonCode))
			return DTC::HPDR_UNSET;

		return RejectReasonCode;
	}

	/*==========================================================================*/
}
