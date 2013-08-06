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


//�м۴��.
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
	case ENTRUST_BUY://��.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5_Cancel_Buy(quotation);

			//�м۴�Ϻ�ʣ��ĵ�.ת���޼۵�.
			if (quotation.nCount > 0)
			{
				m_buyReportingBook.Add(quotation);
			}

		}
		break;
	case ENTRUST_SELL://��.
		{
			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5_Cancel_Sell(quotation);

			//�м۴�Ϻ�ʣ��ĵ�.ת���޼۵�.
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
	case ENTRUST_BUY://��.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5_Limit_Buy(quotation);

			//�м۴�Ϻ�ʣ��ĵ�.ת���޼۵�.
			if (quotation.nCount > 0)
			{
				m_buyReportingBook.Add(quotation);
			}

		}
		break;
	case ENTRUST_SELL://��.
		{
			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5_Limit_Sell(quotation);

			//�м۴�Ϻ�ʣ��ĵ�.ת���޼۵�.
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
