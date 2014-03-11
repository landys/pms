#pragma once

#include "DlgPatient.h"
#include "DlgLog.h"
#include "afxwin.h"


// CLeftView 窗体视图

class CLeftView : public CFormView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftView();

public:
	enum { IDD = IDD_LEFTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	CDlgLog* m_dlgLog;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSeeCg();
	afx_msg void OnEnChangePatientid();
	int m_PatientId;	// 病人编号
	CEdit m_txtPatientId;
	CButton m_btnModify;
	CButton m_btnDelete;
	CButton m_btnSeeCg;
	int m_Interval;	// 接收信号时间间隔
	int m_RecInterval;	// 记录到数据库间隔
	afx_msg void OnBnClickedYes();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSeeLog();
	CButton m_btnSeeLog;
};


