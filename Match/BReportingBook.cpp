#include "StdAfx.h"
#include "BReportingBook.h"


CBReportingBook::CBReportingBook(void)
{
}


CBReportingBook::~CBReportingBook(void)
{
}



int CBReportingBook::Add(QUOTATION quotation)
{
	MAP_BUY_REPORTINGBOOK::iterator iter = m_mapBuyReportingBook.find(quotation.nPrice);
	if (iter == m_mapBuyReportingBook.end())
	{
		//不存在该价格.

		LIST_QUOTATION list_Quotation;
		list_Quotation.push_back(quotation);

		m_mapBuyReportingBook[quotation.nPrice] = list_Quotation;
	} 
	else
	{
		//存在该价格.

		iter->second.push_back(quotation);
	}

	return 0;
}


LPMAP_BUY_REPORTINGBOOK CBReportingBook::GetReportingBook()
{
	return &m_mapBuyReportingBook;
}

bool CBReportingBook::Exist(UINT nPrice)
{
	MAP_BUY_REPORTINGBOOK::iterator iter = m_mapBuyReportingBook.find(nPrice);

	if (iter != m_mapBuyReportingBook.end())
	{
		return true;
	}

	int nSize = m_mapBuyReportingBook.size();

	if (0 == nSize)
	{
		//压根就不存在数据.
		return false;
	}

	if (nSize > 0)
	{
		iter = m_mapBuyReportingBook.begin();

		if (nPrice <= iter->first)
		{
			//卖价 <= 买价.
			return true;
		}
	}

	return false;
}

int CBReportingBook::Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll)
{
	if ((NULL == pListQuotation || pListQuotation->empty()) && false == bDelAll)
	{
		return -1;
	}

	MAP_BUY_REPORTINGBOOK::iterator iter = m_mapBuyReportingBook.find(nKey);

	if (iter == m_mapBuyReportingBook.end())
	{
		return -1;
	}
	else
	{
		//删除全部.
		if (bDelAll)
		{
			iter->second.clear();
		}

		int nSize = iter->second.size();

		if (1 == nSize)
		{
			//只有一个.

			LIST_QUOTATION::iterator iter_begin = iter->second.begin();
			LIST_QUOTATION::iterator iter_param_begin = pListQuotation->begin();

			if (iter_begin->nCount == iter_param_begin->nCount)
			{
				//数量相等.全部成交.清空.
				iter->second.erase(iter_begin);
			}
			else if (iter_begin->nCount > iter_param_begin->nCount)
			{
				//报价板上队列第一个.持有量大于成交的量.修改.
				iter_begin->nCount = iter_begin->nCount - iter_param_begin->nCount;
			}
			else//iter_begin->nCount < iter_param_begin->nCount
			{
				//报价板上队列第一个.持有量小于成交的量.这是严重的bug.出现在撮合里.
			}
		}
		else
		{
			//多个.

			LIST_QUOTATION::iterator iter_begin = iter->second.begin();
			LIST_QUOTATION::iterator iter_end = iter->second.begin();

			//std::advance(iter_begin, 0);
			std::advance(iter_end, nSize-1);

			iter->second.erase(iter_begin,iter_end);

			LIST_QUOTATION::iterator iter_param_begin = pListQuotation->begin();
			--iter_param_begin;

			//比较最后一个.
			if (iter_begin->nCount == iter_param_begin->nCount)
			{
				//数量相等.全部成交.清空.
				iter->second.erase(iter_begin);
			}
			else if (iter_begin->nCount > iter_param_begin->nCount)
			{
				//报价板上队列第一个.持有量大于成交的量.修改.
				iter_begin->nCount = iter_begin->nCount - iter_param_begin->nCount;
			}
			else//iter_begin->nCount < iter_param_begin->nCount
			{
				//报价板上队列第一个.持有量小于成交的量.这是严重的bug.出现在撮合里.
			}
		}
	}

	return 0;
}

