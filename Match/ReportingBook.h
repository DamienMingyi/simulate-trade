#pragma once

#ifndef _REPORTINGBOOK_H_
#define _REPORTINGBOOK_H_
#include <list>
#include <map>

typedef std::list<QUOTATION> LIST_QUOTATION,*LPLIST_QUOTATION;//�걨����.

typedef struct tagCompare
{
	bool operator()(UINT s1, UINT s2)
	{
		return s1>s2;
	}
}COMPARE,*LPCOMPARE;

typedef std::map<UINT,LIST_QUOTATION> MAP_SELL_REPORTINGBOOK,*LPMAP_SELL_REPORTINGBOOK;//�۸��뱨�۵������ӳ��.SELL.
typedef std::map<UINT,LIST_QUOTATION,COMPARE> MAP_BUY_REPORTINGBOOK,*LPMAP_BUY_REPORTINGBOOK;//�۸��뱨�۵������ӳ��.BUY.



class CReportingBook
{
public:
	CReportingBook(void);
	virtual ~CReportingBook(void);


	virtual int Add(QUOTATION quotation);//��ӵ����۰�.��Ϻ����.
	
	
	virtual bool Exist(UINT	nPrice);

	//��ȡ���ż۸�.
	virtual int GetOptimalPrice();

	/**
	*	ɾ�������еı��۵�.��Ϻ����.
	*	@param nKey ���۰��еļ۸�.
	*	@param pListQuotation ��Ҫɾ��������.
	*	@param bDelAll ɾ��ȫ��.
	*
	*/
	virtual int Del(UINT nKey, LPLIST_QUOTATION pListQuotation, bool bDelAll = false);

};

#endif
