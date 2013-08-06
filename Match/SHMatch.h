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

	//////////////////////////////////////////////////////////////////////////

	//限价撮合.
	//virtual int LimitPriceMatch(ENTRUST entrust);
	//virtual int LimitBuy(QUOTATION &quotation);
	//virtual int LimitSell(QUOTATION &quotation);

	//////////////////////////////////////////////////////////////////////////

	//市价撮合.
	virtual int MarketPriceMatch(ENTRUST entrust);
	//1：上海-最优五档即时成交剩余撤销.
	virtual int Optimal5TurnTOCancel(ENTRUST entrust);
	//2：上海-最优五档即时成交剩余转限价.
	virtual int Optimal5TurnTOLimit(ENTRUST entrust);

	virtual int Optimal5Buy(QUOTATION &quotation);
	virtual int Optimal5Sell(QUOTATION &quotation);

	
};

