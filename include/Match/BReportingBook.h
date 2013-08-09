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
	virtual int Add(QUOTATION quotation);//添加到报价板.撮合后调用.
	virtual LPMAP_BUY_REPORTINGBOOK GetReportingBook();

	virtual bool Exist(UINT	nPrice);
	//获取最优价格.
	virtual int GetOptimalPrice();
	virtual UINT GetEffectiveQuotationListCount();
	virtual int Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll = false);//从报价板中撤单.撮合后调用.

private:
	MAP_BUY_REPORTINGBOOK m_mapBuyReportingBook;//买档申报簿.

};

#endif
