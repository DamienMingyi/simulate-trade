#include "StdAfx.h"
#include "SZMatch.h"


CSZMatch::CSZMatch(void)
{
}


CSZMatch::~CSZMatch(void)
{
}


//撮合.
int CSZMatch::Match(ENTRUST entrust)
{
	if (ENTRUST_LIMIT_PRICE == entrust.nDeclareType)
	{
		LimitPriceMatch(entrust);
	}
	else
	{
		switch(entrust.nDeclareType)
		{
		case ENTRUST_MARKET_PRICE_SZ_1:
		case ENTRUST_MARKET_PRICE_SZ_2:
		case ENTRUST_MARKET_PRICE_SZ_3:
		case ENTRUST_MARKET_PRICE_SZ_4:
		case ENTRUST_MARKET_PRICE_SZ_5:
			{
				MarketPriceMatch(entrust);
			}
			break;
		default:
			break;
		}
	}


	return 0;
}



//市价撮合.
int CSZMatch::MarketPriceMatch(ENTRUST entrust)
{
	switch(entrust.nDeclareType)
	{
	case ENTRUST_MARKET_PRICE_SZ_1:
		{
			OtherSideOptimalPrice(entrust);
		}
		break;
	case ENTRUST_MARKET_PRICE_SZ_2:
		{
			OurSideOptimalPrice(entrust);
		}
		break;
	case ENTRUST_MARKET_PRICE_SZ_3:
		{
			Optimal5TurnTOCancel(entrust);
		}
		break;
	case ENTRUST_MARKET_PRICE_SZ_4:
		{
			ImmediateTurnTOCancel(entrust);
		}
		break;
	case ENTRUST_MARKET_PRICE_SZ_5:
		{
			AllTransactionsOrCancel(entrust);
		}
		break;
	default:
		break;
	}

	return 0;
}

int CSZMatch::OtherSideOptimalPrice(ENTRUST entrust)
{
	return 0;
}

int CSZMatch::OurSideOptimalPrice(ENTRUST entrust)
{
	return 0;
}

int CSZMatch::Optimal5TurnTOCancel(ENTRUST entrust)
{
	return 0;
}

int CSZMatch::ImmediateTurnTOCancel(ENTRUST entrust)
{
	return 0;
}
int CSZMatch::AllTransactionsOrCancel(ENTRUST entrust)
{
	return 0;
}

