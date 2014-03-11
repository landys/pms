// DlgLog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PMS.h"
#include "DlgLog.h"
#include ".\dlglog.h"

#include "MainFrm.h"

// CDlgLog �Ի���

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


// CDlgLog ��Ϣ�������

BOOL CDlgLog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString ss = "";
	ss.Format("��� %d ������־", m_PatientId);
	this->SetWindowText(ss);

	// �б�ͷ����Ϣ
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt =  LVCFMT_LEFT;

	lvc.iSubItem = 0;
	lvc.pszText = _T("ʱ��");
	lvc.cx = 132;
	m_lstLog.InsertColumn(0, &lvc);
	lvc.iSubItem = 1;
	lvc.pszText = _T("Ѫѹ");
	lvc.cx = 68;
	m_lstLog.InsertColumn(1, &lvc);
	lvc.iSubItem = 2;
	lvc.pszText = _T("����");
	lvc.cx = 68;
	m_lstLog.InsertColumn(2, &lvc);
	lvc.iSubItem = 3;
	lvc.pszText = _T("�ĵ�");
	lvc.cx = 68;
	m_lstLog.InsertColumn(3, &lvc);
	lvc.iSubItem = 4;
	lvc.pszText = _T("����");
	lvc.cx = 68;
	m_lstLog.InsertColumn(4, &lvc);

	// ��ʾ���иò�����־
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

	COleVariant varStr;  // �ֶ�����
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ���б��в���һ���б���־
void CDlgLog::InsertItem(int nRow, float bp, float temp, float cg, int pulse, CString curTime)
{
	CString strText;

	m_lstLog.InsertItem(LVIF_TEXT | LVIF_IMAGE, nRow, curTime, 0, 0, 0, 0);	//������

	strText.Format(TEXT("%.2f"), bp);
	m_lstLog.SetItemText(nRow, 1, strText);

	strText.Format(TEXT("%.2f"), temp);
	m_lstLog.SetItemText(nRow, 2, strText);

	strText.Format(TEXT("%.2f"), cg);
	m_lstLog.SetItemText(nRow, 3, strText);

	strText.Format(TEXT("%d"), pulse);
	m_lstLog.SetItemText(nRow, 4, strText);
}

// ��ʾ��ӡ�Ի���
void CDlgLog::OnPrint()
{
	// TODO: �ڴ���������������
	CPrintDialog dlg(TRUE);
	dlg.DoModal();
}
