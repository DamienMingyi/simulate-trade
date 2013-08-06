#pragma once

#ifndef _MATCH_H_
#define _MATCH_H_

#include "SReportingBook.h"
#include "BReportingBook.h"

class CMatch
{
public:
	CMatch(void);
	virtual ~CMatch(void);

	//���.
	virtual int Match(ENTRUST entrust);

	//�޼۴��.
	virtual int LimitPriceMatch(ENTRUST entrust);
	virtual int LinitBuy(QUOTATION &quotation);
	virtual int LinitSell(QUOTATION &quotation);

	//�м۴��.
	virtual int MarketPriceMatch(ENTRUST entrust);
public:

	CSReportingBook m_sellReportingBook;		//�����걨��.
	CBReportingBook m_buyReportingBook;			//���걨��.
};

#endif

