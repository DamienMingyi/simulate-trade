#pragma once

#ifndef _MATCH_H_
#define _MATCH_H_

#include "SReportingBook.h"
#include "BReportingBook.h"

class STX_EXT_CLASS  CMatch
{
public:
	CMatch(void);
	virtual ~CMatch(void);

	//���.
	virtual int Match(ENTRUST entrust);

	//�޼۴��.
	virtual int LimitPriceMatch(ENTRUST entrust);
	virtual int LimitBuy(QUOTATION &quotation);
	virtual int LimitSell(QUOTATION &quotation);

	//�м۴��.
	virtual int MarketPriceMatch(ENTRUST entrust);
public:

	CSReportingBook m_sellReportingBook;		//�����걨��.
	CBReportingBook m_buyReportingBook;			//���걨��.
};

#endif
