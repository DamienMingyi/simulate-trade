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

	//�޼۴��.
	virtual int LimitPriceMatch(ENTRUST entrust);

	//�м۴��.
	virtual int MarketPriceMatch(ENTRUST entrust);
};

