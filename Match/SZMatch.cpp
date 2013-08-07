#include "StdAfx.h"
#include "SZMatch.h"

#define SZ_MARKET_PRICE_OPTIMAL5 5	//市价委托.最优五档.

CSZMatch::CSZMatch(void)
{
}


CSZMatch::~CSZMatch(void)
{
}


//撮合.
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



//市价撮合.
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
	case ENTRUST_BUY://买.
		{

			UINT nPrice = m_sellReportingBook.GetOptimalPrice();
			
			if (nPrice > 0)
			{
				entrust.nPrice = nPrice;

				LimitPriceMatch(entrust);
			}

			//不存在最优价.
			
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

			//不存在最优价.
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
	case ENTRUST_BUY://买.
		{
			UINT nPrice = m_buyReportingBook.GetOptimalPrice();

			if (nPrice > 0)
			{
				entrust.nPrice = nPrice;

				LimitPriceMatch(entrust);
			}

			//不存在最优价.
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

			//不存在最优价.
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
	case ENTRUST_BUY://买.
		{

			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5Buy(quotation);

			//剩余的单撤销.
		}
		break;
	case ENTRUST_SELL://卖.
		{
			QUOTATION quotation;
			entrust.toQuotation(quotation);

			Optimal5Sell(quotation);

			//剩余的单撤销.

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
	case ENTRUST_BUY://买.
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
	case ENTRUST_BUY://买.
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

	UINT nListCount = 0;//每条链表成交量的计数.
	UINT nOptimal5Count = 0;

	//最优五档即时成交剩余撤销.
	for ( ; map_iter != pSellReportingBook->end() && nOptimal5Count < SZ_MARKET_PRICE_OPTIMAL5; ++map_iter)
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

int CSZMatch::Optimal5Sell(QUOTATION &quotation)
{
	LPMAP_BUY_REPORTINGBOOK pBuyReportingBook = m_buyReportingBook.GetReportingBook();

	MAP_BUY_REPORTINGBOOK::iterator map_iter = pBuyReportingBook->begin();

	UINT nListCount = 0;//每条链表成交量的计数.
	UINT nOptimal5Count = 0;

	//最优五档即时成交剩余撤销.
	for ( ; map_iter != pBuyReportingBook->end() && nOptimal5Count < SZ_MARKET_PRICE_OPTIMAL5; ++map_iter)
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

