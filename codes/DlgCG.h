#pragma once


// CDlgCG �Ի���

class CDlgCG : public CDialog
{
	DECLARE_DYNAMIC(CDlgCG)

private:
	CBitmap m_bmpBuf;	// �ڴ�
	CRect m_Rect;	// ����
public:
	CDlgCG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCG();

// �Ի�������
	enum { IDD = IDD_DLG_CG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
