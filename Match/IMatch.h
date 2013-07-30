#pragma once

#ifndef _MATCH_H_
#define _MATCH_H_

#include "SReportingBook.h"
#include "BReportingBook.h"

class CMatch
{
public:
	CMatch(void);
	virtual ~CMatch(void);

	virtual int Math(ENTRUST entrust);
public:

	CSReportingBook m_sellReportingBook;
	CBReportingBook m_buyReportingBook;
};

#endif

