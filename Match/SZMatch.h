#pragma once
#include "imatch.h"
class CSZMatch :
	public CMatch
{
public:
	CSZMatch(void);
	virtual ~CSZMatch(void);

public:
	//���.
	virtual int Match(ENTRUST entrust);

	//////////////////////////////////////////////////////////////////////////

	//�޼۴��.
	//virtual int LimitPriceMatch(ENTRUST entrust);
	//virtual int LinitBuy(QUOTATION &quotation);
	//virtual int LinitSell(QUOTATION &quotation);

	//////////////////////////////////////////////////////////////////////////

	//�м۴��.
	virtual int MarketPriceMatch(ENTRUST entrust);
	virtual int MarketBuy(ENTRUST &entrust);
	virtual int MarketSell(ENTRUST &entrust);
};

