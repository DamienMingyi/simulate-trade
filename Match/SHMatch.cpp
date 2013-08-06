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


//市价撮合.
int CSHMatch::MarketPriceMatch(ENTRUST entrust)
{
	switch(entrust.nDeclareType)
	{
	case ENTRUST_MARKET_PRICE_SH_1:
		{
			Optimal5_Cancel(entrust);
		}
		break;
	case ENTRUST_MARKET_PRICE_SH_2:
		{
			Optimal5_Limit(entrust);
		}
		break;
	default:
		break;
	}

	return 0;
}



int CSHMatch::Optimal5_Cancel(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://买.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5_Cancel_Buy(quotation);

			//市价撮合后剩余的单.转入限价单.
			if (quotation.nCount > 0)
			{
				m_buyReportingBook.Add(quotation);
			}

		}
		break;
	case ENTRUST_SELL://卖.
		{
			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5_Cancel_Sell(quotation);

			//市价撮合后剩余的单.转入限价单.
			if (quotation.nCount)
			{
				m_sellReportingBook.Add(quotation);
			}

		}
		break;
	default:
		break;
	}

	return 0;
}

int CSHMatch::Optimal5_Cancel_Buy(QUOTATION &quotation)
{
	return 0;
}

int CSHMatch::Optimal5_Cancel_Sell(QUOTATION &quotation)
{
	return 0;
}

int CSHMatch::Optimal5_Limit(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://买.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5_Limit_Buy(quotation);

			//市价撮合后剩余的单.转入限价单.
			if (quotation.nCount > 0)
			{
				m_buyReportingBook.Add(quotation);
			}

		}
		break;
	case ENTRUST_SELL://卖.
		{
			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5_Limit_Sell(quotation);

			//市价撮合后剩余的单.转入限价单.
			if (quotation.nCount)
			{
				m_sellReportingBook.Add(quotation);
			}

		}
		break;
	default:
		break;
	}

	return 0;
}


int CSHMatch::Optimal5_Limit_Buy(QUOTATION &quotation)
{
	return 0;
}

int CSHMatch::Optimal5_Limit_Sell(QUOTATION &quotation)
{
	return 0;
}
