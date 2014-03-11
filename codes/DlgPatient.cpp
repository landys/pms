// DlgPatient.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PMS.h"
#include "DlgPatient.h"
#include ".\dlgpatient.h"

#include "MainFrm.h"
#include "PMSView.h"


// CDlgPatient �Ի���

IMPLEMENT_DYNAMIC(CDlgPatient, CDialog)
CDlgPatient::CDlgPatient(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPatient::IDD, pParent)
	, m_PatientId(0)
	, m_Name(_T(""))
	, m_Doctor(_T(""))
	, m_Age(0)
	, m_CGHigh(0)
	, m_CGLow(0)
	, m_TempHigh(0)
	, m_TempLow(0)
	, m_BPHigh(0)
	, m_BPLow(0)
	, m_PulseHigh(0)
	, m_PulseLow(0)
	, m_TimeIn(COleDateTime::GetCurrentTime())
	, m_isAdd(TRUE)
	, m_Sex(1)
	, m_State(0)
	, m_strTimeIn("")
{
}

CDlgPatient::CDlgPatient(int patientID, CString name, int age, int sex, int state, CString timeIn, CString doctor, 
			float stdBpHigh, float stdBpLow, float stdTempHigh, float stdTempLow, float stdCgHigh, float stdCgLow, int stdPulseHigh, int stdPulseLow, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPatient::IDD, pParent)
		, m_PatientId(patientID)
		, m_Name(name)
		, m_Doctor(doctor)
		, m_Age(age)
		, m_CGHigh(stdCgHigh)
		, m_CGLow(stdCgLow)
		, m_TempHigh(stdTempHigh)
		, m_TempLow(stdTempLow)
		, m_BPHigh(stdBpHigh)
		, m_BPLow(stdBpLow)
		, m_PulseHigh(stdPulseHigh)
		, m_PulseLow(stdPulseLow)
		, m_isAdd(FALSE)
		, m_Sex(sex)
		, m_State(state)
		, m_strTimeIn(timeIn)
{
}

CDlgPatient::~CDlgPatient()
{
}

void CDlgPatient::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATIENTID, m_PatientId);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_DOCTOR, m_Doctor);
	DDX_Text(pDX, IDC_AGE, m_Age);
	DDX_Text(pDX, IDC_CG_HIGH, m_CGHigh);
	DDX_Text(pDX, IDC_CG_LOW, m_CGLow);
	DDX_Text(pDX, IDC_TEMP_HIGH, m_TempHigh);
	DDX_Text(pDX, IDC_TEMP_LOW, m_TempLow);
	DDX_Text(pDX, IDC_BP_HIGH, m_BPHigh);
	DDX_Text(pDX, IDC_BP_LOW, m_BPLow);
	DDX_Text(pDX, IDC_PULSE_HIGH, m_PulseHigh);
	DDX_Text(pDX, IDC_PULSE_LOW, m_PulseLow);
	DDX_DateTimeCtrl(pDX, IDC_TIMEIN, m_TimeIn);
	DDX_Control(pDX, IDC_MALE, m_rbtnMale);
	DDX_Control(pDX, IDC_FEMALE, m_rbtnFemale);
	DDX_Control(pDX, IDC_DANGER, m_rbtnDanger);
	DDX_Control(pDX, IDC_BAD, m_rbtnBad);
	DDX_Control(pDX, IDC_NORMAL, m_rbtnNormal);
	DDX_Control(pDX, IDC_PATIENTID, m_txtPatientId);
	DDX_Control(pDX, IDC_TIMEIN, m_dtTimeIn);
}

BEGIN_MESSAGE_MAP(CDlgPatient, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// ���벡����Ϣ���޸Ĳ�����Ϣ
void CDlgPatient::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);

	if(m_PatientId == 0)
	{
		::AfxMessageBox("����������");
		return;
	}
	if(m_Name.Trim() == "")
	{
		::AfxMessageBox("�����벡������");
		return;
	}
	if(m_Age <= 0)
	{
		::AfxMessageBox("����ȷ���벡������");
		return;
	}
	if (m_Doctor.Trim() == "")
	{
		::AfxMessageBox("����������ҽ������");
		return;
	}

	int sex = 1;
	int state = 0;
	CString timeIn = "";
	if (this->m_rbtnFemale.GetCheck() == TRUE)
	{
		sex = 0;
	}

	if (this->m_rbtnBad.GetCheck() == TRUE)
	{
		state = 1;
	}
	else if (this->m_rbtnDanger.GetCheck() == TRUE)
	{
		state = 2;
	}

	timeIn = m_TimeIn.Format(_T("%Y-%m-%d %H:%M:%S"));
	CMainFrame* pFrame=static_cast<CMainFrame*>(::AfxGetMainWnd());
	CPMSView* pView=static_cast<CPMSView*>(pFrame->m_SplitterUpDown.GetPane(0, 0));

	if (m_isAdd)
	{
		// �������в���һ����¼
		pView->InsertDataBase(m_PatientId, m_Name.Trim(), m_Age, sex, state, timeIn, "", m_Doctor.Trim(), 
			m_BPHigh, m_BPLow, m_TempHigh, m_TempLow, m_CGHigh, m_CGLow, m_PulseHigh, m_PulseLow);
	}
	else
	{
		// �޸����ݿ��¼
		pView->UpdateDataBase(m_PatientId, m_Name.Trim(), m_Age, sex, state, timeIn, "", m_Doctor.Trim(), 
			m_BPHigh, m_BPLow, m_TempHigh, m_TempLow, m_CGHigh, m_CGLow, m_PulseHigh, m_PulseLow);
	}

	// �ڲ�������������һ���б�
	PatientInfo* pIn = new PatientInfo;
	pIn->patientId = m_PatientId;
	pIn->stdCgHigh = m_CGHigh;
	pIn->stdCgLow = m_CGLow;
	pIn->stdBpHigh = m_BPHigh;
	pIn->stdBpLow = m_BPLow;
	pIn->stdTempHigh = m_TempHigh;
	pIn->stdTempLow = m_TempLow;
	pIn->stdPulseHigh = m_PulseHigh;
	pIn->stdPulseLow = m_PulseLow;
	pIn->dlgWarning = NULL;
	pIn->flagBp = FALSE;
	pIn->flagCg = FALSE;
	pIn->flagTemp = FALSE;
	pIn->flagPulse = FALSE;

	pIn->next = CMainFrame::m_pinHead;
	CMainFrame::m_pinHead = pIn;

	OnOK();
}

BOOL CDlgPatient::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	if (m_isAdd)
	{
		// ��Ӳ�����Ϣ
		m_BPHigh = 120;
		m_BPLow = 100;
		m_TempHigh = 37.5;
		m_TempLow = 36.5;
		m_CGHigh = 150;
		m_CGLow = -90;
		m_PulseHigh = 80;
		m_PulseLow = 60;
		this->m_rbtnNormal.SetCheck(TRUE);
		this->m_rbtnMale.SetCheck(TRUE);
	}
	else
	{
		// �޸Ĳ�����Ϣ
		if (m_Sex == 1)
		{
			this->m_rbtnMale.SetCheck(TRUE);
		}
		else
		{
			this->m_rbtnFemale.SetCheck(TRUE);
		}

		if (m_State == 0)
		{
			this->m_rbtnNormal.SetCheck(TRUE);
		}
		else if (m_State == 1)
		{
			this->m_rbtnBad.SetCheck(TRUE);
		}
		else
		{
			this->m_rbtnDanger.SetCheck(TRUE);
		}
		this->SetWindowText("�޸Ĳ�����Ϣ");
		this->m_txtPatientId.SetReadOnly(TRUE);
		this->m_dtTimeIn.SetWindowText(m_strTimeIn);
	}
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

