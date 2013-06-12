#ifndef ED_VER_H_INCLUDED
#define ED_VER_H_INCLUDED

#pragma once

#define ED_VER_MAJOR		1			// ���汾��
#define ED_VER_MINOR		0			// �ΰ汾��
#define ED_VER_RELEASE		0			// ������
#define ED_VER_REV			11			// �޶���

#define ED_STRINGLISE( v )			#v
#define ED_VER_JOIN(a, b, c, d)		ED_STRINGLISE(a.b.c.d)

#define ED_VERSION		((ED_VER_MAJOR << 24) + (ED_VER_MINOR << 16) + ED_VER_RELEASE)
#define ED_VER_STR		ED_VER_JOIN(ED_VER_MAJOR, ED_VER_MINOR, ED_VER_RELEASE, ED_VER_REV)

//#define ED_BUILD_TIME	"$WCNOW$"


// �汾��Ϣ����ʾ������
#define ED_PRODUCT_NAME	 "EasyTools"


#endif // ED_VER_H_INCLUDED
