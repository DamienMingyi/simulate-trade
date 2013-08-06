#pragma once
#include "imatch.h"
class CSZMatch :
	public CMatch
{
public:
	CSZMatch(void);
	virtual ~CSZMatch(void);

public:
	//撮合.
	virtual int Match(ENTRUST entrust);

	//////////////////////////////////////////////////////////////////////////

	//限价撮合.
	//virtual int LimitPriceMatch(ENTRUST entrust);
	//virtual int LinitBuy(QUOTATION &quotation);
	//virtual int LinitSell(QUOTATION &quotation);

	//////////////////////////////////////////////////////////////////////////

	//市价撮合.
	virtual int MarketPriceMatch(ENTRUST entrust);
	virtual int MarketBuy(ENTRUST &entrust);
	virtual int MarketSell(ENTRUST &entrust);
};

