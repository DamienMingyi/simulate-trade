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

			if (m_sellReportingBook.Exist(quotation.nPrice))
			{
				//���걨���д��ڿɴ������.
				//���.
				LinitBuy(quotation);
			}

			//���֮����ʣ��.��ӵ��걨����.
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

			if (m_buyReportingBook.Exist(quotation.nPrice))
			{
				//���걨���д��ڿɴ������.
				//���.
				LinitSell(quotation);
			}

			//���֮����ʣ��.��ӵ��걨����.
			if (quotation.nCount > 0)
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


int CSHMatch::LinitBuy(QUOTATION &quotation)
{
	LPMAP_SELL_REPORTINGBOOK pSellReportingBook = m_sellReportingBook.GetReportingBook();

	MAP_SELL_REPORTINGBOOK::iterator map_iter = pSellReportingBook->begin();

	UINT nCount = 0;//ÿ������ɽ����ļ���.

	for ( ; map_iter != pSellReportingBook->end(); ++map_iter)
	{
		if (quotation.nPrice >= map_iter->first)
		{
			LIST_QUOTATION::const_iterator list_iter = (map_iter->second).begin();

			LIST_QUOTATION listQuotation;//�ɽ��б�.
			nCount = 0;
			bool bLastCompleteTurnover = false;//���һ���Ƿ���ȫ�ɽ�.

			for ( ; list_iter != (map_iter->second).end(); ++list_iter)
			{
				nCount += list_iter->nCount;

				if (nCount >= quotation.nCount)
				{
					//�ɽ��㹻.
					QUOTATION quotationTmp = (*list_iter);
					quotationTmp.nCount = quotationTmp.nCount - (nCount - quotation.nCount);//����ʣ��.

					if (0 == quotationTmp.nCount)
					{
						bLastCompleteTurnover = true;
					}

					nCount = quotation.nCount;
					
					listQuotation.push_back(quotationTmp);

					++list_iter;
					break;
					
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
				//��ʣ��.
				if (nCount > 0)
				{
					quotation.nCount = quotation.nCount - nCount;
					m_sellReportingBook.Del(map_iter->first, &listQuotation);
				}
			}

			listQuotation.clear();
		}
	}


	return 0;
}


int CSHMatch::LinitSell(QUOTATION &quotation)
{
	LPMAP_BUY_REPORTINGBOOK buyReportingBook = m_buyReportingBook.GetReportingBook();

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

			//MarketBuy(ENTRUST &entrust)

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

			//MarketSell(ENTRUST &entrust)

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

int CSHMatch::MarketBuy(ENTRUST &entrust)
{
	return 0;
}

int CSHMatch::MarketSell(ENTRUST &entrust)
{
	return 0;
}

