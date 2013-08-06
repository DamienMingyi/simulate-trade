#include "StdAfx.h"
#include "SHMatch.h"

#define SH_MARKET_PRICE_OPTIMAL5 5	//�м�ί��.�����嵵.

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
			Optimal5TurnTOCancel(entrust);
		}
		break;
	case ENTRUST_MARKET_PRICE_SH_2:
		{
			Optimal5TurnTOLimit(entrust);
		}
		break;
	default:
		break;
	}

	return 0;
}



int CSHMatch::Optimal5TurnTOCancel(ENTRUST entrust)
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


int CSHMatch::Optimal5TurnTOLimit(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://��.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5Buy(quotation);

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

			Optimal5Sell(quotation);

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


int CSHMatch::Optimal5Buy(QUOTATION &quotation)
{
	LPMAP_SELL_REPORTINGBOOK pSellReportingBook = m_sellReportingBook.GetReportingBook();

	MAP_SELL_REPORTINGBOOK::iterator map_iter = pSellReportingBook->begin();

	UINT nListCount = 0;//ÿ������ɽ����ļ���.
	UINT nOptimal5Count = 0;

	//�����嵵��ʱ�ɽ�ʣ�೷��.
	for ( ; map_iter != pSellReportingBook->end() && nOptimal5Count < SH_MARKET_PRICE_OPTIMAL5; ++map_iter)
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

int CSHMatch::Optimal5Sell(QUOTATION &quotation)
{
	LPMAP_BUY_REPORTINGBOOK pBuyReportingBook = m_buyReportingBook.GetReportingBook();

	MAP_BUY_REPORTINGBOOK::iterator map_iter = pBuyReportingBook->begin();

	UINT nListCount = 0;//ÿ������ɽ����ļ���.
	UINT nOptimal5Count = 0;

	//�����嵵��ʱ�ɽ�ʣ�೷��.
	for ( ; map_iter != pBuyReportingBook->end() && nOptimal5Count < SH_MARKET_PRICE_OPTIMAL5; ++map_iter)
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
