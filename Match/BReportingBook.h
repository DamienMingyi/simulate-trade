#pragma once

#ifndef _BREPORTINGBOOK_H_
#define _BREPORTINGBOOK_H_

#include "ReportingBook.h"



class CBReportingBook :
	public CReportingBook
{
public:
	CBReportingBook(void);
	virtual ~CBReportingBook(void);

public:
	virtual int Add(QUOTATION quotation);//��ӵ����۰�.��Ϻ����.
	virtual int Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll = false);//�ӱ��۰��г���.��Ϻ����.

private:
	MAP_BUY_REPORTINGBOOK m_mapBuyReportingBook;//���걨��.

};

#endif
