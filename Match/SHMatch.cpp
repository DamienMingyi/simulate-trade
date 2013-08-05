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
		//�޼�ί��.
		LimitPriceMatch(entrust);
	}
	else
	{
		//�м�ί��.
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


//�޼۴��.
int CSHMatch::LimitPriceMatch(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://��.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);
			m_buyReportingBook.Add(quotation);
		}
		break;
	case ENTRUST_SELL://��.
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

//�м۴��.
int CSHMatch::MarketPriceMatch(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://��.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);
			m_buyReportingBook.Add(quotation);
		}
		break;
	case ENTRUST_SELL://��.
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

