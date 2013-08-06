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

	//����-�������ż۸�.
	virtual int OtherSideOptimalPrice(ENTRUST entrust);
	//����-�������ż۸�.
	virtual int OurSideOptimalPrice(ENTRUST entrust);
	//����-�����嵵��ʱ�ɽ�ʣ�೷��.
	virtual int Optimal5TurnTOCancel(ENTRUST entrust);
	//����-��ʱ�ɽ�ʣ�೷��(FAK).
	virtual int ImmediateTurnTOCancel(ENTRUST entrust);
	//����-ȫ��ɽ�����ί��(FOK).
	virtual int AllTransactionsOrCancel(ENTRUST entrust);
};

