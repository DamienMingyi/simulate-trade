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

	//撮合.
	virtual int Match(ENTRUST entrust);

	//限价撮合.
	virtual int LimitPriceMatch(ENTRUST entrust);
	virtual int LinitBuy(QUOTATION &quotation);
	virtual int LinitSell(QUOTATION &quotation);

	//市价撮合.
	virtual int MarketPriceMatch(ENTRUST entrust);
public:

	CSReportingBook m_sellReportingBook;		//卖方申报簿.
	CBReportingBook m_buyReportingBook;			//买方申报簿.
};

#endif

