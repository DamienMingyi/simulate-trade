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
		//�����ڸü۸�.

		LIST_QUOTATION list_Quotation;
		list_Quotation.push_back(quotation);

		m_mapBuyReportingBook[quotation.nPrice] = list_Quotation;
	} 
	else
	{
		//���ڸü۸�.

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
		//ѹ���Ͳ���������.
		return false;
	}

	if (nSize > 0)
	{
		iter = m_mapBuyReportingBook.begin();

		if (nPrice <= iter->first)
		{
			//���� <= ���.
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

