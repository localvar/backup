#ifndef __TRIELEM_H__
#define __TRIELEM_H__

#include"d:\zbmprj\minic\variable.h"

typedef struct tagTRIELEMEXPR
{
	OPCODE op;
	unsigned LsType: 2;/*��������洢����*/
	unsigned LdType: 6;/*���������������*/
	unsigned RsType: 2;
	unsigned RdType: 6;
	union tagVARIABLE left;
	union tagVARIABLE right;
}TRIELEMEXPR;

typedef struct tagSTACK
{
	UINT ip;
	UINT nLocalVar;
}STACK;

typedef TRIELEMEXPR*	PTRIELEMEXPR;
typedef STACK*			PSTACK;

extern TRIELEMEXPR TriElemExprTbl[MAX_TRI_ELEM_EXPR];
extern UINT ip;/*��Ԫʽָ��*/
extern STACK		CallStack[MAX_CALL_NEST];
extern UINT	sp;

extern void IncreaseIp();

#endif __TRIELEM_H__