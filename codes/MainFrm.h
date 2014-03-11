// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once

#include "DlgCG.h"

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	static float m_CGData[30];	// ���30���ĵ���Ϣ
	static int m_iCGData;	// �ĵ���Ϣ���ݵ�ǰ�±�
	static PatientInfo* m_pinHead;	// ������Ϣ����ͷ
	static int m_curPatientId;	// ��ǰѡ�в��˱��
	static int m_Interval;	// ��ʱ���ղ����źż��
	static int m_RecordInterval;	// ��¼������Ϣ�����ݿ���
	static CDlgCG* m_dlgCG;	// �ĵ�ͼ
	static CString m_Path;	// ���ݿ�·��
	static int m_Timer;	// ��ʱ��

	int m_iRecord;	// ͳ�ƽ����˼�����Ϣ,�Զ�ʱ�����ݿ��¼��Ϣ
	CDaoDatabase m_Db;	// ���ݿ�
	CDaoRecordset m_RsLog;	// ��־���ݼ�
// ����
public:
	// �������ݿ���Ϣ
	void InsertDataBase(int patientID, float bp, float temp, float cg, int pulse, CString curTime);
	// ���ղ�����Ϣ
	void CatchPatientInfo();
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	//CToolBar    m_wndToolBar;
public:
	CSplitterWnd m_Splitter;	// ���ҷָ���
	CSplitterWnd m_SplitterUpDown;	// ���·ָ���

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnTimer(UINT nIDEvent);
};


