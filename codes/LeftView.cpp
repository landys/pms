// LeftView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PMS.h"
#include "LeftView.h"
#include ".\leftview.h"

#include "DlgPatient.h"
#include "MainFrm.h"
#include "PMSView.h"
#include "DlgCG.h"

// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(CLeftView::IDD)
	, m_PatientId(0)
	, m_Interval(0)
	, m_RecInterval(0)
	, m_dlgLog(NULL)
{
}

CLeftView::~CLeftView()
{
}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATIENTID, m_PatientId);
	DDX_Control(pDX, IDC_PATIENTID, m_txtPatientId);
	DDX_Control(pDX, IDC_Modify, m_btnModify);
	DDX_Control(pDX, IDC_Delete, m_btnDelete);
	DDX_Control(pDX, IDC_SEE_CG, m_btnSeeCg);
	DDX_Text(pDX, IDC_TXT_INTERVAL, m_Interval);
	DDX_Text(pDX, IDC_TXT_REC_INTERVAL, m_RecInterval);
	DDX_Control(pDX, IDC_SEE_LOG, m_btnSeeLog);
}

BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_WM_CREATE()
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TABCTRL, OnTcnSelchangeTabctrl)
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_Modify, OnBnClickedModify)
	ON_BN_CLICKED(IDC_Delete, OnBnClickedDelete)
	ON_BN_CLICKED(IDC_SEE_CG, OnBnClickedSeeCg)
	ON_EN_CHANGE(IDC_PATIENTID, OnEnChangePatientid)
	ON_BN_CLICKED(IDC_YES, OnBnClickedYes)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SEE_LOG, OnBnClickedSeeLog)
END_MESSAGE_MAP()


// CLeftView ���

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CLeftView ��Ϣ�������

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CLeftView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


	// TODO: �ڴ����ר�ô����/����û���

	// �ڶԻ����ʼʱDisableһЩ��ť
	m_btnSeeCg.EnableWindow(FALSE);
	m_btnDelete.EnableWindow(FALSE);
	m_btnModify.EnableWindow(FALSE);
	m_btnSeeLog.EnableWindow(FALSE);
	m_Interval = CMainFrame::m_Interval;
	m_RecInterval = CMainFrame::m_RecordInterval;
	UpdateData(FALSE);
}

// ��ʾ��ӶԻ���
void CLeftView::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDlgPatient* dp = new CDlgPatient();

	if (!dp->Create(IDD_DLG_PATIENT))
	{
		return;
	}
	dp->ShowWindow(SW_RESTORE);
}

// ��ʾ�޸ĶԻ���
void CLeftView::OnBnClickedModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	
	CMainFrame* pFrame=static_cast<CMainFrame*>(::AfxGetMainWnd());
	CPMSView* pView=static_cast<CPMSView*>(pFrame->m_SplitterUpDown.GetPane(0, 0));

	pView->SetPatientData(m_PatientId);
}

// ɾ�����˼�¼
void CLeftView::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pFrame=static_cast<CMainFrame*>(::AfxGetMainWnd());
	CPMSView* pView=static_cast<CPMSView*>(pFrame->m_SplitterUpDown.GetPane(0, 0));
	
	UpdateData(TRUE);
	pView->DeleteDataBase(m_PatientId);
	this->m_txtPatientId.SetWindowText("");
	
	// ������Ӧ������Ϣ����
	CMainFrame::m_curPatientId = 0;
	PatientInfo* pIn = CMainFrame::m_pinHead;
	if (CMainFrame::m_pinHead->patientId == m_PatientId)
	{
		CMainFrame::m_pinHead = CMainFrame::m_pinHead->next;
		delete pIn;
		return;
	}
	
	PatientInfo* pNext = CMainFrame::m_pinHead->next;
	while (pNext != NULL)
	{
		if (pNext->patientId == m_PatientId)
		{
			pIn->next = pNext->next;
			delete pNext;
			return;
		}
		pIn = pNext;
		pNext = pNext->next;
	}
}

// ��ʾ�ĵ�ͼ�Ի���
void CLeftView::OnBnClickedSeeCg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (CMainFrame::m_dlgCG == NULL)
	{
		CMainFrame::m_dlgCG = new CDlgCG();
	}

	if (!CMainFrame::m_dlgCG->Create(IDD_DLG_CG))
	{
		return;
	}
	CMainFrame::m_dlgCG->ShowWindow(SW_RESTORE);
}

// ���˱���ı������ı��ı�ʱ����Ӧ����
void CLeftView::OnEnChangePatientid()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CString ss = "";
	m_txtPatientId.GetWindowText(ss);
	if (ss != "")
	{
		UpdateData(TRUE);
	
		if (m_PatientId == 0)
		{
			m_btnSeeCg.EnableWindow(FALSE);
			m_btnDelete.EnableWindow(FALSE);
			m_btnModify.EnableWindow(FALSE);
			m_btnSeeLog.EnableWindow(FALSE);
		}
		else
		{
			m_btnSeeCg.EnableWindow(TRUE);
			m_btnDelete.EnableWindow(TRUE);
			m_btnModify.EnableWindow(TRUE);
			m_btnSeeLog.EnableWindow(TRUE);
		}
	}
	else
	{
		m_btnSeeCg.EnableWindow(FALSE);
		m_btnDelete.EnableWindow(FALSE);
		m_btnModify.EnableWindow(FALSE);
		m_btnSeeLog.EnableWindow(FALSE);
	}
}

// ȷ���޸�����ʱ����
void CLeftView::OnBnClickedYes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if (m_Interval == 0)
	{
		m_Interval = CMainFrame::m_Interval;
	}
	else
	{
		CMainFrame::m_Interval = m_Interval;
		CMainFrame* pFrame = static_cast<CMainFrame*>(::AfxGetMainWnd());
		pFrame->KillTimer(CMainFrame::m_Timer);
		CMainFrame::m_Timer = pFrame->SetTimer(5, m_Interval, NULL);
	}
	if (m_RecInterval == 0)
	{
		m_RecInterval = CMainFrame::m_RecordInterval;
	}
	else
	{
		CMainFrame::m_RecordInterval = m_RecInterval;
	}

	UpdateData(FALSE);
}

// �����޸�����ʱ����
void CLeftView::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Interval = CMainFrame::m_Interval;
	m_RecInterval = CMainFrame::m_RecordInterval;
	UpdateData(FALSE);
}

// ��ʾ������־�Ի���
void CLeftView::OnBnClickedSeeLog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if (m_dlgLog != NULL)
	{
		delete m_dlgLog;	
	}
	m_dlgLog = new CDlgLog(m_PatientId);
	m_dlgLog->Create(IDD_DLG_LOG);
	m_dlgLog->ShowWindow(SW_RESTORE);
}
