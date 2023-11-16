
// LV3_18077.h : main header file for the LV3_18077 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLV318077App:
// See LV3_18077.cpp for the implementation of this class
//

class CLV318077App : public CWinApp
{
public:
	CLV318077App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLV318077App theApp;
