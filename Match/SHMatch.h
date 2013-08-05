#pragma once
#include "imatch.h"
class CSHMatch :
	public CMatch
{
public:
	CSHMatch(void);
	virtual ~CSHMatch(void);

	//撮合.
	virtual int Match(ENTRUST entrust);

	//限价撮合.
	virtual int LimitPriceMatch(ENTRUST entrust);

	//市价撮合.
	virtual int MarketPriceMatch(ENTRUST entrust);
	
};

