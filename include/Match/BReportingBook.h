#pragma once

#ifndef _BREPORTINGBOOK_H_
#define _BREPORTINGBOOK_H_

#include "ReportingBook.h"



class STX_EXT_CLASS  CBReportingBook :
	public CReportingBook
{
public:
	CBReportingBook(void);
	virtual ~CBReportingBook(void);

public:
	virtual int Add(QUOTATION quotation);//��ӵ����۰�.��Ϻ����.
	virtual LPMAP_BUY_REPORTINGBOOK GetReportingBook();

	virtual bool Exist(UINT	nPrice);
	//��ȡ���ż۸�.
	virtual int GetOptimalPrice();
	virtual UINT GetEffectiveQuotationListCount();
	virtual int Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll = false);//�ӱ��۰��г���.��Ϻ����.

private:
	MAP_BUY_REPORTINGBOOK m_mapBuyReportingBook;//���걨��.

};

#endif
