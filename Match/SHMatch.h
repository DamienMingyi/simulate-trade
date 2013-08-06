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
	//virtual int LinitBuy(QUOTATION &quotation);
	//virtual int LinitSell(QUOTATION &quotation);

	//////////////////////////////////////////////////////////////////////////

	//�м۴��.
	virtual int MarketPriceMatch(ENTRUST entrust);
	//1���Ϻ�-�����嵵��ʱ�ɽ�ʣ�೷��.
	virtual int Optimal5_Cancel(ENTRUST entrust);
	virtual int Optimal5_Cancel_Buy(QUOTATION &quotation);
	virtual int Optimal5_Cancel_Sell(QUOTATION &quotation);
	//2���Ϻ�-�����嵵��ʱ�ɽ�ʣ��ת�޼�.
	virtual int Optimal5_Limit(ENTRUST entrust);
	virtual int Optimal5_Limit_Buy(QUOTATION &quotation);
	virtual int Optimal5_Limit_Sell(QUOTATION &quotation);

	
};

