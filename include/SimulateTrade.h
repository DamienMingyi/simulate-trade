#pragma once

#ifndef _SIMULATETRADE_H_
#define _SIMULATETRADE_H_

#pragma pack(push)
#pragma pack(push,1)

#define ENTRUST_BUY			1
#define ENTRUST_SELL		2

//����.
typedef struct tagQuotation
{
	UINT64	ID;				//ί��ID.
	UINT	nPrice;			//�۸�.0���м۵�.*10000.
	UINT	nCount;			//����.��100�ı���.��100�ı�����С��100��һ����ȫ������.���ø���100���(��.����.Ȩ֤).
	UINT	nBS;			//��������.1����  2����.

}QUOTATION,*LPQUOTATION;



//ί��.
typedef struct tagEntrust
{
	UINT64	ID;				//ί��ID.
	UINT	nDeclareType;	//�걨����.0���޼�. 
							//�������м�.
							//1���Ϻ�-�����嵵��ʱ�ɽ�ʣ��ɽ�.
							//2���Ϻ�-�����嵵��ʱ�ɽ�ʣ��ת�޼�.
							//11������-�������ż۸�.
							//12������-�������ż۸�.
							//13������-�����嵵��ʱ�ɽ�ʣ�೷��.
							//14������-��ʱ�ɽ�ʣ�೷��(FAK).
							//15������-ȫ��ɽ�����ί��(FOK).
	char	szMarket[4];	//�г�.SH:�Ϻ�.SZ:����.
	char	szSeatCode[8];	//����.����ϯλ����.
	char	szCode[8];		//����.��Ʊ����.
	UINT	nPrice;			//�۸�.0���м۵�.*10000.
							// A�ɡ�ծȯ��ծȯ��Ѻʽ�ع����׵��걨�۸���С�䶯��λΪ0.01Ԫ����ң�
							//������Ϊ0.001Ԫ����ң�B�ɽ���Ϊ0.01��Ԫ��
	UINT	nCount;			//����.��100�ı���.��100�ı�����С��100��һ����ȫ������.���ø���100���(��.����.Ȩ֤).
							//ծȯ��Ϊ10�ı���.���ø���10����.
	UINT	nBS;			//��������.1����  2����.

	void toQUOTATION(QUOTATION &quotation)
	{
		quotation.ID		= ID;
		quotation.nPrice	= nPrice;
		quotation.nCount	= nCount;
		quotation.nBS		= nBS;
	}

}ENTRUST,*LPENTRUST;



//�ɽ�.
typedef struct tagTraded 
{
	UINT64	Buy_ID;			//ί��ID.��.
	//char	szMarket[4];	//�г�.
	char	szBuy_SeatCode[8];	//��ϯλ����.
	char	szCode[8];		//����.
	UINT	nPrice;			//�۸�.
	UINT	nCount;			//����.
	char	szSell_SeatCode[8];	//����ϯλ����.
	UINT64	Sell_ID;		//ί��ID.����.

}TRADED,*LPTRADED;

//�ɽ�.��ϯλ����.
typedef struct tagTraded2 
{
	UINT64	Buy_ID;			//ί��ID.��.
	char	szCode[8];		//����.
	UINT	nPrice;			//�۸�.
	UINT	nCount;			//����.
	UINT64	Sell_ID;		//ί��ID.����.

}TRADED2,*LPTRADED2;

//�ɽ�.��ϯλ����.�޶Է�ID.
typedef struct tagTraded3 
{
	UINT64	ID;				//ί��ID.
	char	szCode[8];		//����.
	UINT	nPrice;			//�۸�.
	UINT	nCount;			//����.

}TRADED3,*LPTRADED3;

#pragma pack(pop)

#endif
