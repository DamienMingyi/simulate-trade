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

	//�޼۴��.
	virtual int LimitPriceMatch(ENTRUST entrust);

	//�м۴��.
	virtual int MarketPriceMatch(ENTRUST entrust);
	
};

