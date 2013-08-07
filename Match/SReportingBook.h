#pragma once

#ifndef _SREPORTINGBOOK_H_
#define _SREPORTINGBOOK_H_

#include "ReportingBook.h"


class CSReportingBook :
	public CReportingBook
{
public:
	CSReportingBook(void);
	virtual ~CSReportingBook(void);

public:
	virtual int Add(QUOTATION quotation);//��ӵ����۰�.��Ϻ����.

	virtual LPMAP_SELL_REPORTINGBOOK GetReportingBook();

	virtual bool Exist(UINT	nPrice);
	//��ȡ���ż۸�.
	virtual int GetOptimalPrice();

	virtual int Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll = false);//�ӱ��۰��г���.��Ϻ����.

private:
	MAP_SELL_REPORTINGBOOK m_mapSellReportingBook;//�����걨��.
};

#endif

