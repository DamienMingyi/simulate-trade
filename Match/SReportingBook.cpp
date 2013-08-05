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
	MAP_SELL_REPORTINGBOOK::iterator iter = m_mapReportingBook.find(quotation.nPrice);
	if (iter == m_mapReportingBook.end())
	{
		//�����ڸü۸�.

		LIST_QUOTATION list_Quotation;
		list_Quotation.push_back(quotation);

		m_mapReportingBook[quotation.nPrice] = list_Quotation;
	} 
	else
	{
		//���ڸü۸�.

		iter->second.push_back(quotation);
	}

	return 0;
}

int CSReportingBook::Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll)
{

	if ((NULL == pListQuotation || pListQuotation->empty()) && false == bDelAll)
	{
		return -1;
	}

	MAP_SELL_REPORTINGBOOK::iterator iter = m_mapReportingBook.find(nKey);

	if (iter == m_mapReportingBook.end())
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
