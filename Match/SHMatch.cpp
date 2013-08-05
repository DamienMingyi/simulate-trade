#include "StdAfx.h"
#include "SHMatch.h"


CSHMatch::CSHMatch(void)
{
}


CSHMatch::~CSHMatch(void)
{
}


int CSHMatch::Match(ENTRUST entrust)
{
	if (ENTRUST_LIMIT_PRICE == entrust.nDeclareType)
	{
		//限价委托.
		LimitPriceMatch(entrust);
	}
	else
	{
		//市价委托.
		switch(entrust.nDeclareType)
		{
		case ENTRUST_MARKET_PRICE_SH_1:
		case ENTRUST_MARKET_PRICE_SH_2:
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


//限价撮合.
int CSHMatch::LimitPriceMatch(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://买.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);
			m_buyReportingBook.Add(quotation);
		}
		break;
	case ENTRUST_SELL://卖.
		{
			QUOTATION quotation;
			entrust.toQuotation(quotation);
			m_sellReportingBook.Add(quotation);
		}
		break;
	default:
		break;
	}


	return 0;
}

//市价撮合.
int CSHMatch::MarketPriceMatch(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://买.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);
			m_buyReportingBook.Add(quotation);
		}
		break;
	case ENTRUST_SELL://卖.
		{
			QUOTATION quotation;
			entrust.toQuotation(quotation);
			m_sellReportingBook.Add(quotation);
		}
		break;
	default:
		break;
	}


	return 0;
}

