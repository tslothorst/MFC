#pragma once
#define WM_USER_APPLY WM_USER+0x100
#define WM_USER_DIALOG_DESTROYED WM_USER+0x101

typedef struct tagELLPROP
{
	int nWidth;
	int nHeight;
	int nUnits;
	int nColor;
} ELLPROP;

class stdafx
{
};

