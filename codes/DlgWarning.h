#pragma once
#include "afxwin.h"


// CDlgWarning �Ի���

class CDlgWarning : public CDialog
{
	DECLARE_DYNAMIC(CDlgWarning)

public:
	CDlgWarning(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWarning();

// �Ի�������
	enum { IDD = IDD_DLG_WARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_txtPatientId;	// ���˱��
	CEdit m_txtWarning;	// ��������
};
