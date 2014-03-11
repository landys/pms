#pragma once

#include "DlgPatient.h"
#include "DlgLog.h"
#include "afxwin.h"


// CLeftView ������ͼ

class CLeftView : public CFormView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLeftView();

public:
	enum { IDD = IDD_LEFTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	int m_PatientId;	// ���˱��
	CEdit m_txtPatientId;
	CButton m_btnModify;
	CButton m_btnDelete;
	CButton m_btnSeeCg;
	int m_Interval;	// �����ź�ʱ����
	int m_RecInterval;	// ��¼�����ݿ���
	afx_msg void OnBnClickedYes();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSeeLog();
	CButton m_btnSeeLog;
};


