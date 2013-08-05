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

	//限价撮合.
	virtual int LimitPriceMatch(ENTRUST entrust);

	//市价撮合.
	virtual int MarketPriceMatch(ENTRUST entrust);
};

