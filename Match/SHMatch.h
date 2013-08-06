#pragma once
#include "imatch.h"
class CSHMatch :
	public CMatch
{
public:
	CSHMatch(void);
	virtual ~CSHMatch(void);

	//���.
	virtual int Match(ENTRUST entrust);

	//////////////////////////////////////////////////////////////////////////

	//�޼۴��.
	virtual int LimitPriceMatch(ENTRUST entrust);
	virtual int LinitBuy(QUOTATION &quotation);
	virtual int LinitSell(QUOTATION &quotation);

	//////////////////////////////////////////////////////////////////////////

	//�м۴��.
	virtual int MarketPriceMatch(ENTRUST entrust);
	virtual int MarketBuy(ENTRUST &entrust);
	virtual int MarketSell(ENTRUST &entrust);
};

