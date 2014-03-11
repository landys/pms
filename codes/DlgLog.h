#pragma once
#include "afxcmn.h"


// CDlgLog �Ի���

class CDlgLog : public CDialog
{
	DECLARE_DYNAMIC(CDlgLog)

public:
	CDlgLog(int patientId, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLog();

// �Ի�������
	enum { IDD = IDD_DLG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	int nRow;
	int m_PatientId;	// ���˱��
	CDaoRecordset m_RsLogShow;	// ��־���ݼ�
	CDaoDatabase m_Db;	// ���ݿ�
	void InsertItem(int nRow, float bp, float temp, float cg, int pulse, CString curTime);	// ���б��в���һ���¼
public:
	CListCtrl m_lstLog;
	virtual BOOL OnInitDialog();
	afx_msg void OnPrint();
};
