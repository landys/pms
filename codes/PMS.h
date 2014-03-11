// PMS.h : PMS 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h” 
#endif

#include "resource.h"       // 主符号
#include "DlgWarning.h"

// 病人信息
typedef struct tag_PatientInfo
{
	int patientId;	// 编号

	CString curTime;	// 时间	
	float bp;	// 血压
	float temp;	// 体温
	float cg;	// 心电
	int pulse;	// 脉搏
	float stdBpHigh;	// 标准血压上限
	float stdBpLow;	// 标准血压下限
	float stdTempHigh;
	float stdTempLow;
	float stdCgHigh;
	float stdCgLow;
	int stdPulseHigh;
	int stdPulseLow;

	BOOL flagBp;	// 血压是否超标标志
	BOOL flagTemp;
	BOOL flagCg;
	BOOL flagPulse;
	CDlgWarning* dlgWarning;	// 警告对话框
	struct tag_PatientInfo* next;	// 指向下一个该结构
} PatientInfo;

// CPMSApp:
// 有关此类的实现，请参阅 PMS.cpp
//

class CPMSApp : public CWinApp
{
public:
	CPMSApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPMSApp theApp;
