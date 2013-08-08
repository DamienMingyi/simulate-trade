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

	//�����嵵����.
	virtual int Optimal5Buy(QUOTATION &quotation);
	virtual int Optimal5Sell(QUOTATION &quotation);

	//��ʱ����.
	virtual int ImmediateBuy(QUOTATION &quotation);
	virtual int ImmediateSell(QUOTATION &quotation);

	//ȫ��ɽ�
	virtual int AllTransactionsBuy(QUOTATION &quotation);
	virtual int AllTransactionsSell(QUOTATION &quotation);

};

