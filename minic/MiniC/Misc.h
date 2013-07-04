#ifndef __MISC_H__
#define __MISC_H__

#define _ENABLE_DEBUG_
#ifdef _ENABLE_DEBUG_
#include <stdlib.h>	/* abort() prototype */
#define ASSERT(p) \
{\
	if(!(p))\
	{\
		char _c_c_;\
		printf("Assertion failed: %s, file %s, line %d\n",\
		#p, __FILE__, __LINE__);\
		printf("'n' or 'N' to abort, other key continue\n");\
		_c_c_=getch();\
		if(_c_c_=='n' || _c_c_=='N') abort();\
	}\
}
#else
#define ASSERT(p)
#endif _ENABLE_DEBUG_

#define MAX_SYMBOL_NAME_LENGTH		15
#define MAX_SYMBOL					128
#define MAX_VARIABLE				1024
#define MAX_TRI_ELEM_EXPR			2048
#define MAX_CALL_NEST				256
#define MAX_FUNCTION_ARGS			256
#define MAX_BLOCK_NEST				64

typedef char	BOOL;
#define TRUE	1
#define FALSE	0
typedef unsigned char BYTE;
typedef unsigned int UINT;

/*��������*/
typedef enum
{
	DTNOUSE = 0,
	DTVOID,
	DTINT,
	DTFLOAT,
	DTLAST,
} DATATYPE;

/*���ʽ����*/
typedef enum
{
	ETFIRST = DTLAST-1,

	ETVARIABLE,		/*	����	*/

	ETASSIGN,		/*  =   */
	ETADDASSIGN,	/*  +=  */
	ETSUBASSIGN,	/*  -=  */
	ETMULASSIGN,	/*  *=  */
	ETDIVASSIGN,	/*  /=  */
	ETMODASSIGN,	/*  %=  */

	ETCOMMA,		/*  ,   */
	ETADD,			/*  +   */
	ETSUB,			/*  -   */
	ETMUL,			/*  *   */
	ETDIV,			/*  /   */
	ETMOD,			/*  %   */

	ETLARGE,		/*  >   */
	ETSMALL,		/*  <   */
	ETLARGEEQU,		/*  >=  */
	ETSMALLEQU,		/*  <=  */
	ETAND,			/*  &&  */
	ETOR,			/*  ||  */
	ETEQU,			/*  ==  */
	ETNOTEQU,		/*  !=  */

	ETSIN,			/*��ѧ����*/
	ETCOS,
	ETTAN,
	ETSQRT,
	ETEXP,
	ETLOG,

	ETNOT,			/*  !   */
	ETMINUS,		/*  ����	*/

	ETCONDITION,	/*	�������ʽ*/
	/*NOTE:don't change the following 4 operators' order*/
	ETINC,			/*  ++  */
	ETDEC,			/*  --  */
	ETPOSTINC,
	ETPOSTDEC,

	ETFUNCTION,		/*	����	*/

	ETLAST,
} EXPRTYPE;

/*����������*/
typedef enum
{
	OTFIRST = ETLAST-1,
	OTJMP,/*��������ת*/
	OTJNZ,/*������ת*/
	OTJZ,
	OTRETURN,
	OTADDVAR,
	OTREAD,
	OTREADLN,
	OTWRITE,
	OTWRITELN,
	OTCALL,
	OTINITGRAPH,
	OTCLOSEGRAPH,
	OTMOVETO,
	OTLINETO,
	OTSETCOLOR,
	OTLAST,
} OPTYPE;

/*�洢����*/
typedef enum
{
	CONST = 0,
	GLOBE,
	LOCAL,
	TEMP,
} STORETYPE;


#if ETLAST>256
typedef unsigned int EPCODE;
#else
typedef unsigned char EPCODE;
#endif

#if OTLAST>256
typedef unsigned int OPCODE;
#else
typedef unsigned char OPCODE;
#endif
	
/*��Ԫʽ*/

/*HERE*********************************************/
/*
typedef struct tagVARIABLE
{
	int nType;
	union
	{
		int nValue;
		double dValue;
		void vValue;
	}Content;
}VARIABLE;
typedef ETERAND*		PETERAND;
typedef VARIABLE*		PVARIABLE;
*/
extern void PrintError(const char *msg, const char* text);
extern void yyerror(const char *);

#endif  __MISC_H__