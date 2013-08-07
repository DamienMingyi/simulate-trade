#include "StdAfx.h"
#include "SZMatch.h"

#define SZ_MARKET_PRICE_OPTIMAL5 5	//�м�ί��.�����嵵.

CSZMatch::CSZMatch(void)
{
}


CSZMatch::~CSZMatch(void)
{
}


//���.
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



//�м۴��.
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
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://��.
		{

			UINT nPrice = m_sellReportingBook.GetOptimalPrice();
			
			if (nPrice > 0)
			{
				entrust.nPrice = nPrice;

				LimitPriceMatch(entrust);
			}

			//���������ż�.
			
		}
		break;
	case ENTRUST_SELL:
		{
			UINT nPrice = m_buyReportingBook.GetOptimalPrice();

			if (nPrice > 0)
			{
				entrust.nPrice = nPrice;

				LimitPriceMatch(entrust);
			}

			//���������ż�.
		}
		break;
	default:
		break;
	}

	return 0;
}

int CSZMatch::OurSideOptimalPrice(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://��.
		{
			UINT nPrice = m_buyReportingBook.GetOptimalPrice();

			if (nPrice > 0)
			{
				entrust.nPrice = nPrice;

				LimitPriceMatch(entrust);
			}

			//���������ż�.
		}
		break;
	case ENTRUST_SELL:
		{
			UINT nPrice = m_sellReportingBook.GetOptimalPrice();

			if (nPrice > 0)
			{
				entrust.nPrice = nPrice;

				LimitPriceMatch(entrust);
			}

			//���������ż�.
		}
		break;
	default:
		break;
	}

	return 0;
}

int CSZMatch::Optimal5TurnTOCancel(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://��.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5Buy(quotation);

			//ʣ��ĵ�����.
		}
		break;
	case ENTRUST_SELL://��.
		{
			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5Sell(quotation);

			//ʣ��ĵ�����.

		}
		break;
	default:
		break;
	}

	return 0;
}

int CSZMatch::ImmediateTurnTOCancel(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://��.
		{

		}
		break;
	case ENTRUST_SELL:
		{

		}
		break;
	default:
		break;
	}

	return 0;
}
int CSZMatch::AllTransactionsOrCancel(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://��.
		{

		}
		break;
	case ENTRUST_SELL:
		{

		}
		break;
	default:
		break;
	}

	return 0;
}



int CSZMatch::Optimal5Buy(QUOTATION &quotation)
{
	LPMAP_SELL_REPORTINGBOOK pSellReportingBook = m_sellReportingBook.GetReportingBook();

	MAP_SELL_REPORTINGBOOK::iterator map_iter = pSellReportingBook->begin();

	UINT nListCount = 0;//ÿ������ɽ����ļ���.
	UINT nOptimal5Count = 0;

	//�����嵵��ʱ�ɽ�ʣ�೷��.
	for ( ; map_iter != pSellReportingBook->end() && nOptimal5Count < SZ_MARKET_PRICE_OPTIMAL5; ++map_iter)
	{
		if (0 == (map_iter->second).size())
		{
			//����û��ί�е������嵵֮��.
			continue;
		}

		nOptimal5Count++;
		LIST_QUOTATION::const_iterator list_iter = (map_iter->second).begin();

		LIST_QUOTATION listQuotation;//�ɽ��б�.
		nListCount = 0;
		bool bLastCompleteTurnover = false;//���һ���Ƿ���ȫ�ɽ�.

		for ( ; list_iter != (map_iter->second).end(); ++list_iter)
		{
			nListCount += list_iter->nCount;

			//������Ҫ�ɽ�������.
			if (nListCount >= quotation.nCount)
			{
				//�ɽ��㹻.
				QUOTATION quotationTmp = (*list_iter);
				quotationTmp.nCount = quotationTmp.nCount - (nListCount - quotation.nCount);//�������һ���ɽ���.

				//���ȫ���ɽ�.
				if (list_iter->nCount == quotationTmp.nCount)
				{
					bLastCompleteTurnover = true;
				}

				//
				nListCount = quotation.nCount;

				listQuotation.push_back(quotationTmp);

				++list_iter;

				break;//for ( ; list_iter != (map_iter->second).end(); ++list_iter)

			}else
			{
				listQuotation.push_back((*list_iter));
			}
		}

		if (list_iter == (map_iter->second).end() && bLastCompleteTurnover)
		{
			//��ʣ��.
			quotation.nCount = 0;//quotation.nCount-nCount;
			m_sellReportingBook.Del(map_iter->first,&listQuotation,true);
		} 
		else
		{
			if (nListCount > 0)
			{
				//ʣ��ĳɽ���.
				quotation.nCount = quotation.nCount - nListCount;

				//���ݳɽ��б�.���걨����ɾ���Ѿ��ɽ���ί�е�.
				m_sellReportingBook.Del(map_iter->first, &listQuotation);
			}
		}

		listQuotation.clear();

		if (bLastCompleteTurnover)
		{
			break;//for ( ; map_iter != pSellReportingBook->end() && nOptimal5Count < SH_MARKET_PRICE_OPTIMAL5; ++map_iter)
		}

	}

	return 0;
}

int CSZMatch::Optimal5Sell(QUOTATION &quotation)
{
	LPMAP_BUY_REPORTINGBOOK pBuyReportingBook = m_buyReportingBook.GetReportingBook();

	MAP_BUY_REPORTINGBOOK::iterator map_iter = pBuyReportingBook->begin();

	UINT nListCount = 0;//ÿ������ɽ����ļ���.
	UINT nOptimal5Count = 0;

	//�����嵵��ʱ�ɽ�ʣ�೷��.
	for ( ; map_iter != pBuyReportingBook->end() && nOptimal5Count < SZ_MARKET_PRICE_OPTIMAL5; ++map_iter)
	{
		if (0 == (map_iter->second).size())
		{
			//����û��ί�е������嵵֮��.
			continue;
		}

		nOptimal5Count++;
		LIST_QUOTATION::const_iterator list_iter = (map_iter->second).begin();

		LIST_QUOTATION listQuotation;//�ɽ��б�.
		nListCount = 0;
		bool bLastCompleteTurnover = false;//���һ���Ƿ���ȫ�ɽ�.

		for ( ; list_iter != (map_iter->second).end(); ++list_iter)
		{
			nListCount += list_iter->nCount;

			//������Ҫ�ɽ�������.
			if (nListCount >= quotation.nCount)
			{
				//�ɽ��㹻.
				QUOTATION quotationTmp = (*list_iter);
				quotationTmp.nCount = quotationTmp.nCount - (nListCount - quotation.nCount);//�������һ���ɽ���.

				//���ȫ���ɽ�.
				if (list_iter->nCount == quotationTmp.nCount)
				{
					bLastCompleteTurnover = true;
				}

				//
				nListCount = quotation.nCount;

				listQuotation.push_back(quotationTmp);

				++list_iter;

				break;//for ( ; list_iter != (map_iter->second).end(); ++list_iter)

			}else
			{
				listQuotation.push_back((*list_iter));
			}
		}

		if (list_iter == (map_iter->second).end() && bLastCompleteTurnover)
		{
			//��ʣ��.
			quotation.nCount = 0;//quotation.nCount-nCount;
			m_sellReportingBook.Del(map_iter->first,&listQuotation,true);
		} 
		else
		{
			if (nListCount > 0)
			{
				//ʣ��ĳɽ���.
				quotation.nCount = quotation.nCount - nListCount;

				//���ݳɽ��б�.���걨����ɾ���Ѿ��ɽ���ί�е�.
				m_sellReportingBook.Del(map_iter->first, &listQuotation);
			}
		}

		listQuotation.clear();

		if (bLastCompleteTurnover)
		{
			break;//for ( ; map_iter != pSellReportingBook->end() && nOptimal5Count < SH_MARKET_PRICE_OPTIMAL5; ++map_iter)
		}

	}

	return 0;
}

