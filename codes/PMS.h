// PMS.h : PMS Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������
#include "DlgWarning.h"

// ������Ϣ
typedef struct tag_PatientInfo
{
	int patientId;	// ���

	CString curTime;	// ʱ��	
	float bp;	// Ѫѹ
	float temp;	// ����
	float cg;	// �ĵ�
	int pulse;	// ����
	float stdBpHigh;	// ��׼Ѫѹ����
	float stdBpLow;	// ��׼Ѫѹ����
	float stdTempHigh;
	float stdTempLow;
	float stdCgHigh;
	float stdCgLow;
	int stdPulseHigh;
	int stdPulseLow;

	BOOL flagBp;	// Ѫѹ�Ƿ񳬱��־
	BOOL flagTemp;
	BOOL flagCg;
	BOOL flagPulse;
	CDlgWarning* dlgWarning;	// ����Ի���
	struct tag_PatientInfo* next;	// ָ����һ���ýṹ
} PatientInfo;

// CPMSApp:
// �йش����ʵ�֣������ PMS.cpp
//

class CPMSApp : public CWinApp
{
public:
	CPMSApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPMSApp theApp;
