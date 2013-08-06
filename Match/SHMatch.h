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
	//virtual int LimitPriceMatch(ENTRUST entrust);
	//virtual int LimitBuy(QUOTATION &quotation);
	//virtual int LimitSell(QUOTATION &quotation);

	//////////////////////////////////////////////////////////////////////////

	//�м۴��.
	virtual int MarketPriceMatch(ENTRUST entrust);
	//1���Ϻ�-�����嵵��ʱ�ɽ�ʣ�೷��.
	virtual int Optimal5TurnTOCancel(ENTRUST entrust);
	//2���Ϻ�-�����嵵��ʱ�ɽ�ʣ��ת�޼�.
	virtual int Optimal5TurnTOLimit(ENTRUST entrust);

	virtual int Optimal5Buy(QUOTATION &quotation);
	virtual int Optimal5Sell(QUOTATION &quotation);

	
};

