// MainFrm.h : CMainFrame 类的接口
//


#pragma once

#include "DlgCG.h"

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:
	static float m_CGData[30];	// 最近30次心电信息
	static int m_iCGData;	// 心电信息数据当前下标
	static PatientInfo* m_pinHead;	// 病人信息链表头
	static int m_curPatientId;	// 当前选中病人编号
	static int m_Interval;	// 随时接收病人信号间隔
	static int m_RecordInterval;	// 记录病人信息到数据库间隔
	static CDlgCG* m_dlgCG;	// 心电图
	static CString m_Path;	// 数据库路径
	static int m_Timer;	// 定时器

	int m_iRecord;	// 统计接收了几条信息,以定时在数据库记录信息
	CDaoDatabase m_Db;	// 数据库
	CDaoRecordset m_RsLog;	// 日志数据集
// 操作
public:
	// 插入数据库信息
	void InsertDataBase(int patientID, float bp, float temp, float cg, int pulse, CString curTime);
	// 接收病人信息
	void CatchPatientInfo();
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar  m_wndStatusBar;
	//CToolBar    m_wndToolBar;
public:
	CSplitterWnd m_Splitter;	// 左右分隔条
	CSplitterWnd m_SplitterUpDown;	// 上下分隔条

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnTimer(UINT nIDEvent);
};


