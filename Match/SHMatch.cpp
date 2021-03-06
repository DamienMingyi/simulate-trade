#include "StdAfx.h"
#include "SHMatch.h"

#define SH_MARKET_PRICE_OPTIMAL5 5	//市价委托.最优五档.

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
	QUOTATION quotation;
	entrust.toQuotation(quotation);

	switch(entrust.nBS)
	{
	case ENTRUST_BUY://买.
		{
			Optimal5Buy(quotation);

			//剩余的单撤销.
		}
		break;
	case ENTRUST_SELL://卖.
		{
			Optimal5Sell(quotation);

			//剩余的单撤销.

		}
		break;
	default:
		break;
	}

	return 0;
}


int CSHMatch::Optimal5TurnTOLimit(ENTRUST entrust)
{
	QUOTATION quotation;
	entrust.toQuotation(quotation);

	switch(entrust.nBS)
	{
	case ENTRUST_BUY://买.
		{
			Optimal5Buy(quotation);

			//市价撮合后剩余的单.转入限价单.
			LPMAP_BUY_REPORTINGBOOK pBuyReportingBook = m_buyReportingBook.GetReportingBook();
			MAP_BUY_REPORTINGBOOK::iterator iter = pBuyReportingBook->begin();

			if (quotation.nCount > 0)
			{
				for ( ; iter != pBuyReportingBook->end(); ++iter)
				{
					if ((iter->second).size() > 0)
					{
						//剩余转入限价单.价格为本分最优价.
						quotation.nPrice = iter->first;
						m_buyReportingBook.Add(quotation);
					}
				}

				//本分没有委托.撤销.
				
			}

		}
		break;
	case ENTRUST_SELL://卖.
		{
			Optimal5Sell(quotation);

			//市价撮合后剩余的单.转入限价单.
			LPMAP_SELL_REPORTINGBOOK pSellReportingBook = m_sellReportingBook.GetReportingBook();
			MAP_SELL_REPORTINGBOOK::iterator iter = pSellReportingBook->begin();
			if (quotation.nCount > 0)
			{				
				for ( ; iter != pSellReportingBook->end(); ++iter)
				{
					if ((iter->second).size() > 0)
					{
						//剩余转入限价单.价格为本分最优价.
						quotation.nPrice = iter->first;
						m_sellReportingBook.Add(quotation);
					}
				}

				//本分没有委托.撤销.
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

	UINT nListCount = 0;//每条链表成交量的计数.
	UINT nOptimal5Count = 0;

	//最优五档即时成交剩余撤销.
	for ( ; map_iter != pSellReportingBook->end() && nOptimal5Count < SH_MARKET_PRICE_OPTIMAL5; ++map_iter)
	{
		if (0 == (map_iter->second).size())
		{
			//链表没有委托单不在五档之中.
			continue;
		}

		nOptimal5Count++;
		LIST_QUOTATION::const_iterator list_iter = (map_iter->second).begin();

		LIST_QUOTATION listQuotation;//成交列表.
		nListCount = 0;
		bool bLastCompleteTurnover = false;//最后一单是否完全成交.

		for ( ; list_iter != (map_iter->second).end(); ++list_iter)
		{
			nListCount += list_iter->nCount;

			//超出需要成交的数量.
			if (nListCount >= quotation.nCount)
			{
				//成交足够.
				QUOTATION quotationTmp = (*list_iter);
				quotationTmp.nCount = quotationTmp.nCount - (nListCount - quotation.nCount);//计算最后一单成交量.

				//最后全部成交.
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
			//无剩余.
			quotation.nCount = 0;//quotation.nCount-nCount;
			m_sellReportingBook.Del(map_iter->first,&listQuotation,true);
		} 
		else
		{
			if (nListCount > 0)
			{
				//剩余的成交量.
				quotation.nCount = quotation.nCount - nListCount;

				//根据成交列表.从申报薄中删除已经成交的委托单.
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

	UINT nListCount = 0;//每条链表成交量的计数.
	UINT nOptimal5Count = 0;

	//最优五档即时成交剩余撤销.
	for ( ; map_iter != pBuyReportingBook->end() && nOptimal5Count < SH_MARKET_PRICE_OPTIMAL5; ++map_iter)
	{
		if (0 == (map_iter->second).size())
		{
			//链表没有委托单不在五档之中.
			continue;
		}

		nOptimal5Count++;
		LIST_QUOTATION::const_iterator list_iter = (map_iter->second).begin();

		LIST_QUOTATION listQuotation;//成交列表.
		nListCount = 0;
		bool bLastCompleteTurnover = false;//最后一单是否完全成交.

		for ( ; list_iter != (map_iter->second).end(); ++list_iter)
		{
			nListCount += list_iter->nCount;

			//超出需要成交的数量.
			if (nListCount >= quotation.nCount)
			{
				//成交足够.
				QUOTATION quotationTmp = (*list_iter);
				quotationTmp.nCount = quotationTmp.nCount - (nListCount - quotation.nCount);//计算最后一单成交量.

				//最后全部成交.
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
			//无剩余.
			quotation.nCount = 0;//quotation.nCount-nCount;
			m_sellReportingBook.Del(map_iter->first,&listQuotation,true);
		} 
		else
		{
			if (nListCount > 0)
			{
				//剩余的成交量.
				quotation.nCount = quotation.nCount - nListCount;

				//根据成交列表.从申报薄中删除已经成交的委托单.
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
