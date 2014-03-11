// DlgLog.cpp : 实现文件
//

#include "stdafx.h"
#include "PMS.h"
#include "DlgLog.h"
#include ".\dlglog.h"

#include "MainFrm.h"

// CDlgLog 对话框

IMPLEMENT_DYNAMIC(CDlgLog, CDialog)
CDlgLog::CDlgLog(int patientId, CWnd* pParent /*=NULL*/)
: CDialog(CDlgLog::IDD, pParent), m_PatientId(patientId), 
	m_RsLogShow(&m_Db), nRow(0)
{
}

CDlgLog::~CDlgLog()
{
}

void CDlgLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_LOG, m_lstLog);
}


BEGIN_MESSAGE_MAP(CDlgLog, CDialog)
	ON_COMMAND(ID_PRINT, OnPrint)
END_MESSAGE_MAP()


// CDlgLog 消息处理程序

BOOL CDlgLog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CString ss = "";
	ss.Format("编号 %d 患者日志", m_PatientId);
	this->SetWindowText(ss);

	// 列表头部信息
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt =  LVCFMT_LEFT;

	lvc.iSubItem = 0;
	lvc.pszText = _T("时间");
	lvc.cx = 132;
	m_lstLog.InsertColumn(0, &lvc);
	lvc.iSubItem = 1;
	lvc.pszText = _T("血压");
	lvc.cx = 68;
	m_lstLog.InsertColumn(1, &lvc);
	lvc.iSubItem = 2;
	lvc.pszText = _T("体温");
	lvc.cx = 68;
	m_lstLog.InsertColumn(2, &lvc);
	lvc.iSubItem = 3;
	lvc.pszText = _T("心电");
	lvc.cx = 68;
	m_lstLog.InsertColumn(3, &lvc);
	lvc.iSubItem = 4;
	lvc.pszText = _T("脉搏");
	lvc.cx = 68;
	m_lstLog.InsertColumn(4, &lvc);

	// 显示所有该病人日志
	ss.Format("SELECT * FROM illstate where patientId=%d order by time asc", m_PatientId);
	if (!m_Db.IsOpen())
	{
		m_Db.Open(CMainFrame::m_Path);
	}
	if (!m_RsLogShow.IsOpen())
	{
		m_RsLogShow.Open(AFX_DAO_USE_DEFAULT_TYPE, ss);
	}
	if (m_RsLogShow.IsEOF())
	{
		return TRUE;
	}

	COleVariant varStr;  // 字段类型
	varStr.ChangeType(VT_BSTR, NULL);
	COleVariant varInt;
	varInt.ChangeType(VT_I4, NULL);
	COleVariant varFloat;
	varFloat.ChangeType(VT_R4, NULL);

	float bp = 0;
	float temp = 0;
	float cg = 0;
	int pulse = 0;
	CString curTime = "";

	m_RsLogShow.MoveFirst();
	while (!m_RsLogShow.IsEOF())
	{
		m_RsLogShow.GetFieldValue("bloodPressure", varFloat);
		bp = (float)varFloat.fltVal;
		m_RsLogShow.GetFieldValue("temperature", varFloat);
		temp = (float)varFloat.fltVal;
		m_RsLogShow.GetFieldValue("cardiogram", varFloat);
		cg = (float)varFloat.fltVal;
		m_RsLogShow.GetFieldValue("pulse", varInt);
		pulse = (long)varInt.plVal;
		m_RsLogShow.GetFieldValue("time", varStr);
		curTime = (LPCSTR)varStr.pbstrVal;
		InsertItem(0, bp, temp, cg, pulse, curTime);
		m_RsLogShow.MoveNext();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 在列表中插入一条列表日志
void CDlgLog::InsertItem(int nRow, float bp, float temp, float cg, int pulse, CString curTime)
{
	CString strText;

	m_lstLog.InsertItem(LVIF_TEXT | LVIF_IMAGE, nRow, curTime, 0, 0, 0, 0);	//插入编号

	strText.Format(TEXT("%.2f"), bp);
	m_lstLog.SetItemText(nRow, 1, strText);

	strText.Format(TEXT("%.2f"), temp);
	m_lstLog.SetItemText(nRow, 2, strText);

	strText.Format(TEXT("%.2f"), cg);
	m_lstLog.SetItemText(nRow, 3, strText);

	strText.Format(TEXT("%d"), pulse);
	m_lstLog.SetItemText(nRow, 4, strText);
}

// 显示打印对话框
void CDlgLog::OnPrint()
{
	// TODO: 在此添加命令处理程序代码
	CPrintDialog dlg(TRUE);
	dlg.DoModal();
}
