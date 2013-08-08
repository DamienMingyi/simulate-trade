#include "StdAfx.h"
#include "IMatch.h"


CMatch::CMatch(void)
{
}


CMatch::~CMatch(void)
{
}



//���.
int CMatch::Match(ENTRUST entrust)
{
	return 0;
}

//�޼۴��.
int CMatch::LimitPriceMatch(ENTRUST entrust)
{
	QUOTATION quotation;
	entrust.toQuotation(quotation);

	switch(entrust.nBS)
	{
	case ENTRUST_BUY://��.
		{
			if (m_sellReportingBook.Exist(quotation.nPrice))
			{
				//���걨���д��ڿɴ������.
				//���.
				LimitBuy(quotation);
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
			if (m_buyReportingBook.Exist(quotation.nPrice))
			{
				//���걨���д��ڿɴ������.
				//���.
				LimitSell(quotation);
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

int CMatch::LimitBuy(QUOTATION &quotation)
{
	LPMAP_SELL_REPORTINGBOOK pSellReportingBook = m_sellReportingBook.GetReportingBook();

	MAP_SELL_REPORTINGBOOK::iterator map_iter = pSellReportingBook->begin();

	UINT nListCount = 0;//ÿ������ɽ����ļ���.

	for ( ; map_iter != pSellReportingBook->end(); ++map_iter)
	{
		//�۸��޷��ɽ�.
		if (quotation.nPrice >= map_iter->first)
		{
			if (0 == (map_iter->second).size())
			{
				continue;
			}

			LIST_QUOTATION::const_iterator list_iter = (map_iter->second).begin();

			LIST_QUOTATION listQuotation;//�ɽ��б�.
			nListCount = 0;
			bool bLastCompleteTurnover = false;//���һ���Ƿ���ȫ�ɽ�.

			for ( ; list_iter != (map_iter->second).end(); ++list_iter)
			{
				nListCount += list_iter->nCount;

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

					nListCount = quotation.nCount;

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
				break;//for ( ; map_iter != pSellReportingBook->end(); ++map_iter)
			}
		}
		{
			break;//for ( ; map_iter != pSellReportingBook->end(); ++map_iter)
		}
	}

	return 0;
}

int CMatch::LimitSell(QUOTATION &quotation)
{
	LPMAP_BUY_REPORTINGBOOK pBuyReportingBook = m_buyReportingBook.GetReportingBook();

	MAP_BUY_REPORTINGBOOK::iterator map_iter = pBuyReportingBook->begin();

	UINT nCount = 0;//ÿ������ɽ����ļ���.

	for ( ; map_iter != pBuyReportingBook->end(); ++map_iter)
	{
		if (quotation.nPrice <= map_iter->first)
		{
			if (0 == (map_iter->second).size())
			{
				continue;
			}

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
		else
		{
			break;
		}
	}

	return 0;
}

//�м۴��.
int CMatch::MarketPriceMatch(ENTRUST entrust)
{
	return 0;
}

