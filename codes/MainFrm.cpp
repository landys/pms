// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PMS.h"

#include "MainFrm.h"
#include ".\mainfrm.h"

#include "LeftView.h"
#include "StateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	// 全局帮助命令
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// 初始化静态变量
float CMainFrame::m_CGData[30] = {0.0f};
int CMainFrame::m_iCGData = 0;
PatientInfo* CMainFrame::m_pinHead = NULL;
int CMainFrame::m_curPatientId = 0;
int CMainFrame::m_Interval = 1000;
int CMainFrame::m_RecordInterval = 10;
CDlgCG* CMainFrame::m_dlgCG = NULL;
CString CMainFrame::m_Path = "PMS.mdb";
int CMainFrame::m_Timer = 0;

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame() : m_RsLog(&m_Db), m_iRecord(0)
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	/*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}*/

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建 
	}
	// TODO: 如果不需要工具栏可停靠，则删除这三行
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
	
	m_Timer = SetTimer(5, m_Interval, 0);
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	// create a splitter with 1 row, 2 columns
	if (!m_Splitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// add the first splitter pane - the default view in column 0
	if (!m_Splitter.CreateView(0, 0,
		RUNTIME_CLASS(CLeftView), CSize(191, 0), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	// add the second splitter pane - which is a nested splitter with 2 rows
	if (!m_SplitterUpDown.CreateStatic(
		&m_Splitter,     // our parent window is the first splitter
		2, 1,               // the new splitter is 2 rows, 1 column
		WS_CHILD | WS_VISIBLE | WS_BORDER,  // style, WS_BORDER is needed
		m_Splitter.IdFromRowCol(0, 1)
		// new splitter is in the first row, 2nd column of first splitter
		))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}

	if (!m_SplitterUpDown.CreateView(0, 0,
		pContext->m_pNewViewClass, CSize(0, 200), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
	
	if (!m_SplitterUpDown.CreateView(1, 0,
		RUNTIME_CLASS(CStateView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}

	// activate the input view
	SetActiveView((CView*)m_Splitter.GetPane(0,0));

	return TRUE;
}


void CMainFrame::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	if (nIDEvent == 5)
	{
		CatchPatientInfo();

		CFrameWnd::OnTimer(nIDEvent);
	}
}

// 在数据库中插入一条日志记录
void CMainFrame::InsertDataBase(int patientID, float bp, float temp, float cg, int pulse, CString curTime)
{
	if (!m_Db.IsOpen())
	{
		m_Db.Open(m_Path);
	}

	CString strSql = "";
	strSql.Format("INSERT INTO illstate VALUES (%d, %f, %f, %f, %d, '%s')", patientID, bp, temp, cg, pulse, curTime);
	try
	{
		m_Db.Execute(strSql);
	}
	catch (...) 
	{
		::AfxMessageBox("记录病人情况出错，请检查数据库");
	}
}

// 随时接收病人信息
void CMainFrame::CatchPatientInfo()
{
	srand((unsigned int)time(NULL));

	PatientInfo* pIn = m_pinHead;
	CTime tt;
	CStateView* pView = static_cast<CStateView*>(m_SplitterUpDown.GetPane(1,0));
	CString strTxt = "";
	m_iRecord++;
	while (pIn != NULL)
	{
		// 随机产生病人信号
		pIn->bp = (float)(rand() % 26 + 97);	// 100--120
		pIn->cg = (float)(rand() % 260 - 100);	// -90--150
		pIn->temp = (float)(rand() % 16 + 362) / 10;	// 36.5--37.5
		pIn->pulse = rand() % 28 + 56;	 // 60--80
		tt = CTime::GetCurrentTime();
		pIn->curTime = tt.Format("%Y-%m-%d %H:%M:%S");

		if (m_iRecord == m_RecordInterval)
		{
			InsertDataBase(pIn->patientId, pIn->bp, pIn->temp, pIn->cg, pIn->pulse, pIn->curTime);
		}
		

		if (m_curPatientId == 0 || m_curPatientId == pIn->patientId)
		{
			if (m_curPatientId == pIn->patientId)
			{
				if (m_iCGData == 30)
				{
					m_iCGData = 0;
				}
				m_CGData[m_iCGData++] = pIn->cg;
				if (m_dlgCG != NULL)
				{
					m_dlgCG->Invalidate();
				}
			}
			
			pView->InsertItem(0, pIn->patientId, pIn->curTime, pIn->bp, pIn->temp, pIn->cg, pIn->pulse);
		}
		// 判断病人是否危险
		// 血压
		if (pIn->bp > pIn->stdBpHigh || pIn->bp < pIn->stdBpLow)
		{
			if (pIn->dlgWarning == NULL)
			{
				pIn->dlgWarning = new CDlgWarning;
				pIn->dlgWarning->Create(IDD_DLG_WARNING);
			}
			strTxt.Format("%d", pIn->patientId);
			pIn->dlgWarning->m_txtPatientId.SetWindowText(strTxt);
			if (pIn->bp > pIn->stdBpHigh)
			{
				strTxt = "血压过高";
			}
			else
			{
				strTxt = "血压过低";
			}
			pIn->dlgWarning->m_txtWarning.SetWindowText(strTxt);
			pIn->dlgWarning->ShowWindow(SW_RESTORE);
			pIn->flagBp = TRUE;
		}

		// 心电
		if(pIn->cg > pIn->stdCgHigh || pIn->cg < pIn->stdCgLow)
		{
			if (pIn->dlgWarning == NULL)
			{
				pIn->dlgWarning = new CDlgWarning;
				pIn->dlgWarning->Create(IDD_DLG_WARNING);
			}
			strTxt.Format("%d", pIn->patientId);
			pIn->dlgWarning->m_txtPatientId.SetWindowText(strTxt);
			if (pIn->cg > pIn->stdCgHigh)
			{
				strTxt = "心电紊乱";
			}
			else
			{
				strTxt = "心电紊乱";
			}
			pIn->dlgWarning->m_txtWarning.SetWindowText(strTxt);
			pIn->dlgWarning->ShowWindow(SW_RESTORE);
			pIn->flagCg = TRUE;
		}

		// 脉搏
		if(pIn->pulse > pIn->stdPulseHigh || pIn->pulse < pIn->stdPulseLow)
		{
			if (pIn->dlgWarning == NULL)
			{
				pIn->dlgWarning = new CDlgWarning;
				pIn->dlgWarning->Create(IDD_DLG_WARNING);
			}
			strTxt.Format("%d", pIn->patientId);
			pIn->dlgWarning->m_txtPatientId.SetWindowText(strTxt);
			if (pIn->pulse > pIn->stdPulseHigh)
			{
				strTxt = "脉搏过快";
			}
			else
			{
				strTxt = "脉搏过慢";
			}
			pIn->dlgWarning->m_txtWarning.SetWindowText(strTxt);
			pIn->dlgWarning->ShowWindow(SW_RESTORE);
			pIn->flagPulse = TRUE;
		}

		// 体温
		if(pIn->temp > pIn->stdTempHigh || pIn->temp < pIn->stdTempLow)
		{
			if (pIn->dlgWarning == NULL)
			{
				pIn->dlgWarning = new CDlgWarning;
				pIn->dlgWarning->Create(IDD_DLG_WARNING);
			}
			strTxt.Format("%d", pIn->patientId);
			pIn->dlgWarning->m_txtPatientId.SetWindowText(strTxt);
			if (pIn->temp > pIn->stdTempHigh)
			{
				strTxt = "体温过高";
			}
			else
			{
				strTxt = "体温过低";
			}
			pIn->dlgWarning->m_txtWarning.SetWindowText(strTxt);
			pIn->dlgWarning->ShowWindow(SW_RESTORE);
			pIn->flagTemp = TRUE;
		}
		pIn = pIn->next;

	}

	if (m_iRecord == m_RecordInterval)
	{
		m_iRecord = 0;
	}
}