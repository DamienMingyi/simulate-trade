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

	//深圳-对手最优价格.
	virtual int OtherSideOptimalPrice(ENTRUST entrust);
	//深圳-本方最优价格.
	virtual int OurSideOptimalPrice(ENTRUST entrust);
	//深圳-最优五档即时成交剩余撤销.
	virtual int Optimal5TurnTOCancel(ENTRUST entrust);
	//深圳-即时成交剩余撤销(FAK).
	virtual int ImmediateTurnTOCancel(ENTRUST entrust);
	//深圳-全额成交或撤销委托(FOK).
	virtual int AllTransactionsOrCancel(ENTRUST entrust);

	//最优五档买卖.
	virtual int Optimal5Buy(QUOTATION &quotation);
	virtual int Optimal5Sell(QUOTATION &quotation);

	//即时买卖.
	virtual int ImmediateBuy(QUOTATION &quotation);
	virtual int ImmediateSell(QUOTATION &quotation);

	//全额成交
	virtual int AllTransactionsBuy(QUOTATION &quotation);
	virtual int AllTransactionsSell(QUOTATION &quotation);

};

