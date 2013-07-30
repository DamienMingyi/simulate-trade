#pragma once

#ifndef _SIMULATETRADE_H_
#define _SIMULATETRADE_H_

#pragma pack(push)
#pragma pack(push,1)

#define ENTRUST_BUY			1
#define ENTRUST_SELL		2

//报价.
typedef struct tagQuotation
{
	UINT64	ID;				//委托ID.
	UINT	nPrice;			//价格.0则市价单.*10000.
	UINT	nCount;			//数量.买100的倍数.卖100的倍数或小于100的一次性全部卖出.不得高于100万股(份.基金.权证).
	UINT	nBS;			//买卖方向.1：买  2：卖.

}QUOTATION,*LPQUOTATION;



//委托.
typedef struct tagEntrust
{
	UINT64	ID;				//委托ID.
	UINT	nDeclareType;	//申报类型.0：限价. 
							//其他：市价.
							//1：上海-最优五档即时成交剩余成交.
							//2：上海-最优五档即时成交剩余转限价.
							//11：深圳-对手最优价格.
							//12：深圳-本方最优价格.
							//13：深圳-最优五档即时成交剩余撤销.
							//14：深圳-即时成交剩余撤销(FAK).
							//15：深圳-全额成交或撤销委托(FOK).
	char	szMarket[4];	//市场.SH:上海.SZ:深圳.
	char	szSeatCode[8];	//劵商.机构席位代码.
	char	szCode[8];		//代码.股票代码.
	UINT	nPrice;			//价格.0则市价单.*10000.
							// A股、债券、债券质押式回购交易的申报价格最小变动单位为0.01元人民币；
							//基金交易为0.001元人民币；B股交易为0.01港元。
	UINT	nCount;			//数量.买100的倍数.卖100的倍数或小于100的一次性全部卖出.不得高于100万股(份.基金.权证).
							//债券则为10的倍数.不得高于10万张.
	UINT	nBS;			//买卖方向.1：买  2：卖.

	void toQUOTATION(QUOTATION &quotation)
	{
		quotation.ID		= ID;
		quotation.nPrice	= nPrice;
		quotation.nCount	= nCount;
		quotation.nBS		= nBS;
	}

}ENTRUST,*LPENTRUST;



//成交.
typedef struct tagTraded 
{
	UINT64	Buy_ID;			//委托ID.买方.
	//char	szMarket[4];	//市场.
	char	szBuy_SeatCode[8];	//买方席位代码.
	char	szCode[8];		//代码.
	UINT	nPrice;			//价格.
	UINT	nCount;			//数量.
	char	szSell_SeatCode[8];	//卖方席位代码.
	UINT64	Sell_ID;		//委托ID.卖方.

}TRADED,*LPTRADED;

//成交.无席位代码.
typedef struct tagTraded2 
{
	UINT64	Buy_ID;			//委托ID.买方.
	char	szCode[8];		//代码.
	UINT	nPrice;			//价格.
	UINT	nCount;			//数量.
	UINT64	Sell_ID;		//委托ID.卖方.

}TRADED2,*LPTRADED2;

//成交.无席位代码.无对方ID.
typedef struct tagTraded3 
{
	UINT64	ID;				//委托ID.
	char	szCode[8];		//代码.
	UINT	nPrice;			//价格.
	UINT	nCount;			//数量.

}TRADED3,*LPTRADED3;

#pragma pack(pop)

#endif
