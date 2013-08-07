#pragma once

#ifndef _REPORTINGBOOK_H_
#define _REPORTINGBOOK_H_
#include <list>
#include <map>

typedef std::list<QUOTATION> LIST_QUOTATION,*LPLIST_QUOTATION;//申报队列.

typedef struct tagCompare
{
	bool operator()(UINT s1, UINT s2)
	{
		return s1>s2;
	}
}COMPARE,*LPCOMPARE;

typedef std::map<UINT,LIST_QUOTATION> MAP_SELL_REPORTINGBOOK,*LPMAP_SELL_REPORTINGBOOK;//价格与报价单链表的映射.SELL.
typedef std::map<UINT,LIST_QUOTATION,COMPARE> MAP_BUY_REPORTINGBOOK,*LPMAP_BUY_REPORTINGBOOK;//价格与报价单链表的映射.BUY.



class CReportingBook
{
public:
	CReportingBook(void);
	virtual ~CReportingBook(void);


	virtual int Add(QUOTATION quotation);//添加到报价板.撮合后调用.
	
	
	virtual bool Exist(UINT	nPrice);

	//获取最优价格.
	virtual int GetOptimalPrice();

	/**
	*	删除链表中的报价单.撮合后调用.
	*	@param nKey 报价板中的价格.
	*	@param pListQuotation 需要删除的内容.
	*	@param bDelAll 删除全部.
	*
	*/
	virtual int Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll = false);

};

#endif
