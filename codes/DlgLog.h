#pragma once
#include "afxcmn.h"


// CDlgLog 对话框

class CDlgLog : public CDialog
{
	DECLARE_DYNAMIC(CDlgLog)

public:
	CDlgLog(int patientId, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLog();

// 对话框数据
	enum { IDD = IDD_DLG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int nRow;
	int m_PatientId;	// 病人编号
	CDaoRecordset m_RsLogShow;	// 日志数据集
	CDaoDatabase m_Db;	// 数据库
	void InsertItem(int nRow, float bp, float temp, float cg, int pulse, CString curTime);	// 在列表中插入一务记录
public:
	CListCtrl m_lstLog;
	virtual BOOL OnInitDialog();
	afx_msg void OnPrint();
};
