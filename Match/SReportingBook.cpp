#include "StdAfx.h"
#include "SReportingBook.h"


CSReportingBook::CSReportingBook(void)
{
}


CSReportingBook::~CSReportingBook(void)
{
}



int CSReportingBook::Add(QUOTATION quotation)
{
	MAP_SELL_REPORTINGBOOK::iterator iter = m_mapSellReportingBook.find(quotation.nPrice);
	if (iter == m_mapSellReportingBook.end())
	{
		//�����ڸü۸�.

		LIST_QUOTATION list_Quotation;
		list_Quotation.push_back(quotation);

		m_mapSellReportingBook[quotation.nPrice] = list_Quotation;
	} 
	else
	{
		//���ڸü۸�.

		iter->second.push_back(quotation);
	}

	return 0;
}

LPMAP_SELL_REPORTINGBOOK CSReportingBook::GetReportingBook()
{
	return &m_mapSellReportingBook;
}

bool CSReportingBook::Exist(UINT nPrice)
{
	int nSize = m_mapSellReportingBook.size();

	if (0 == nSize)
	{
		//ѹ���Ͳ���������.
		return false;
	}
	
	MAP_SELL_REPORTINGBOOK::iterator iter = m_mapSellReportingBook.find(nPrice);

	//���ڸü۸�.����ί������.
	if (iter != m_mapSellReportingBook.end() && (iter->second).size() > 0)
	{
		return true;
	}

	iter = m_mapSellReportingBook.begin();
	for ( ; iter != m_mapSellReportingBook.end(); ++iter)
	{
		if (nPrice >= iter->first && (iter->second).size() > 0)
		{
			//��� >= ����.
			return true;
		}
	}
	
	return false;
}

int CSReportingBook::GetOptimalPrice()
{
	UINT nPrice = 0;
	MAP_SELL_REPORTINGBOOK::const_iterator iter = m_mapSellReportingBook.begin();
	for ( ; iter != m_mapSellReportingBook.end(); ++iter)
	{
		if (iter->second.size() > 0)
		{
			nPrice = iter->first;
			break;
		}
	}

	return nPrice;
}

UINT CSReportingBook::GetEffectiveQuotationListCount()
{
	MAP_SELL_REPORTINGBOOK::const_iterator iter = m_mapSellReportingBook.begin();
	UINT nCount = 0;

	for ( ; iter != m_mapSellReportingBook.end(); ++iter)
	{
		if ((iter->second).size() > 0)
		{
			nCount++;
		}
	}

	return nCount;
}

int CSReportingBook::Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll)
{

	if ((NULL == pListQuotation || pListQuotation->empty()) && false == bDelAll)
	{
		return -1;
	}

	MAP_SELL_REPORTINGBOOK::iterator iter = m_mapSellReportingBook.find(nKey);

	if (iter == m_mapSellReportingBook.end())
	{
		return -1;
	}
	else
	{
		//ɾ��ȫ��.
		if (bDelAll)
		{
			iter->second.clear();
		}

		int nSize = iter->second.size();

		if (1 == nSize)
		{
			//ֻ��һ��.

			LIST_QUOTATION::iterator iter_begin = iter->second.begin();
			LIST_QUOTATION::iterator iter_param_begin = pListQuotation->begin();

			if (iter_begin->nCount == iter_param_begin->nCount)
			{
				//�������.ȫ���ɽ�.���.
				iter->second.erase(iter_begin);
			}
			else if (iter_begin->nCount > iter_param_begin->nCount)
			{
				//���۰��϶��е�һ��.���������ڳɽ�����.�޸�.
				iter_begin->nCount = iter_begin->nCount - iter_param_begin->nCount;
			}
			else//iter_begin->nCount < iter_param_begin->nCount
			{
				//���۰��϶��е�һ��.������С�ڳɽ�����.�������ص�bug.�����ڴ����.
			}
		}
		else
		{
			//���.

			LIST_QUOTATION::iterator iter_begin = iter->second.begin();
			LIST_QUOTATION::iterator iter_end = iter->second.begin();

			//std::advance(iter_begin, 0);
			std::advance(iter_end, nSize-1);

			iter->second.erase(iter_begin,iter_end);

			LIST_QUOTATION::iterator iter_param_begin = pListQuotation->begin();
			--iter_param_begin;

			//�Ƚ����һ��.
			if (iter_begin->nCount == iter_param_begin->nCount)
			{
				//�������.ȫ���ɽ�.���.
				iter->second.erase(iter_begin);
			}
			else if (iter_begin->nCount > iter_param_begin->nCount)
			{
				//���۰��϶��е�һ��.���������ڳɽ�����.�޸�.
				iter_begin->nCount = iter_begin->nCount - iter_param_begin->nCount;
			}
			else//iter_begin->nCount < iter_param_begin->nCount
			{
				//���۰��϶��е�һ��.������С�ڳɽ�����.�������ص�bug.�����ڴ����.
			}
		}
	}

	return 0;
}

