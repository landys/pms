#pragma once
#include "afxwin.h"


// CDlgWarning 对话框

class CDlgWarning : public CDialog
{
	DECLARE_DYNAMIC(CDlgWarning)

public:
	CDlgWarning(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWarning();

// 对话框数据
	enum { IDD = IDD_DLG_WARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_txtPatientId;	// 病人编号
	CEdit m_txtWarning;	// 警告内容
};
