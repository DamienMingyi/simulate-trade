// Match.h : Match DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMatchApp
// �йش���ʵ�ֵ���Ϣ������� Match.cpp
//

class CMatchApp : public CWinApp
{
public:
	CMatchApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
