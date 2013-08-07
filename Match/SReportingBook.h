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
	virtual int Add(QUOTATION quotation);//添加到报价板.撮合后调用.

	virtual LPMAP_SELL_REPORTINGBOOK GetReportingBook();

	virtual bool Exist(UINT	nPrice);
	//获取最优价格.
	virtual int GetOptimalPrice();

	virtual int Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll = false);//从报价板中撤单.撮合后调用.

private:
	MAP_SELL_REPORTINGBOOK m_mapSellReportingBook;//卖档申报簿.
};

#endif

