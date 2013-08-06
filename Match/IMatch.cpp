#include "StdAfx.h"
#include "IMatch.h"


CMatch::CMatch(void)
{
}


CMatch::~CMatch(void)
{
}



//撮合.
int CMatch::Match(ENTRUST entrust)
{
	return 0;
}

//限价撮合.
int CMatch::LimitPriceMatch(ENTRUST entrust)
{
	switch(entrust.nBS)
	{
	case ENTRUST_BUY://买.
		{
			QUOTATION quotation;
			entrust.toQuotation(quotation);

			if (m_sellReportingBook.Exist(quotation.nPrice))
			{
				//卖申报薄中存在可撮合数据.
				//撮合.
				LinitBuy(quotation);
			}

			//撮合之后还有剩余.添加到申报薄中.
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

			if (m_buyReportingBook.Exist(quotation.nPrice))
			{
				//买申报薄中存在可撮合数据.
				//撮合.
				LinitSell(quotation);
			}

			//撮合之后还有剩余.添加到申报薄中.
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

int CMatch::LinitBuy(QUOTATION &quotation)
{
	LPMAP_SELL_REPORTINGBOOK pSellReportingBook = m_sellReportingBook.GetReportingBook();

	MAP_SELL_REPORTINGBOOK::iterator map_iter = pSellReportingBook->begin();

	UINT nCount = 0;//每条链表成交量的计数.

	for ( ; map_iter != pSellReportingBook->end(); ++map_iter)
	{
		if (quotation.nPrice >= map_iter->first)
		{
			LIST_QUOTATION::const_iterator list_iter = (map_iter->second).begin();

			LIST_QUOTATION listQuotation;//成交列表.
			nCount = 0;
			bool bLastCompleteTurnover = false;//最后一般是否完全成交.

			for ( ; list_iter != (map_iter->second).end(); ++list_iter)
			{
				nCount += list_iter->nCount;

				if (nCount >= quotation.nCount)
				{
					//成交足够.
					QUOTATION quotationTmp = (*list_iter);
					quotationTmp.nCount = quotationTmp.nCount - (nCount - quotation.nCount);//计算剩余.

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
				//无剩余.
				quotation.nCount = 0;//quotation.nCount-nCount;
				m_sellReportingBook.Del(map_iter->first,&listQuotation,true);
			} 
			else
			{
				//有剩余.
				if (nCount > 0)
				{
					quotation.nCount = quotation.nCount - nCount;
					m_sellReportingBook.Del(map_iter->first, &listQuotation);
				}
			}

			listQuotation.clear();
		}
		{
			break;
		}
	}

	return 0;
}

int CMatch::LinitSell(QUOTATION &quotation)
{
	LPMAP_BUY_REPORTINGBOOK pBuyReportingBook = m_buyReportingBook.GetReportingBook();

	MAP_BUY_REPORTINGBOOK::iterator map_iter = pBuyReportingBook->begin();

	UINT nCount = 0;//每条链表成交量的计数.

	for ( ; map_iter != pBuyReportingBook->end(); ++map_iter)
	{
		if (quotation.nPrice <= map_iter->first)
		{
			LIST_QUOTATION::const_iterator list_iter = (map_iter->second).begin();

			LIST_QUOTATION listQuotation;//成交列表.
			nCount = 0;
			bool bLastCompleteTurnover = false;//最后一般是否完全成交.

			for ( ; list_iter != (map_iter->second).end(); ++list_iter)
			{
				nCount += list_iter->nCount;

				if (nCount >= quotation.nCount)
				{
					//成交足够.
					QUOTATION quotationTmp = (*list_iter);
					quotationTmp.nCount = quotationTmp.nCount - (nCount - quotation.nCount);//计算剩余.

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
				//无剩余.
				quotation.nCount = 0;//quotation.nCount-nCount;
				m_sellReportingBook.Del(map_iter->first,&listQuotation,true);
			} 
			else
			{
				//有剩余.
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

//市价撮合.
int CMatch::MarketPriceMatch(ENTRUST entrust)
{
	return 0;
}

