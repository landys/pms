#pragma once


// CDlgCG 对话框

class CDlgCG : public CDialog
{
	DECLARE_DYNAMIC(CDlgCG)

private:
	CBitmap m_bmpBuf;	// 内存
	CRect m_Rect;	// 区域
public:
	CDlgCG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCG();

// 对话框数据
	enum { IDD = IDD_DLG_CG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
