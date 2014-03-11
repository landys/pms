// DlgWarning.cpp : 实现文件
//

#include "stdafx.h"
#include "PMS.h"
#include "DlgWarning.h"
#include ".\dlgwarning.h"


// CDlgWarning 对话框

IMPLEMENT_DYNAMIC(CDlgWarning, CDialog)
CDlgWarning::CDlgWarning(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWarning::IDD, pParent)
{
}

CDlgWarning::~CDlgWarning()
{
}

void CDlgWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TXT_PATIENTID, m_txtPatientId);
	DDX_Control(pDX, IDC_TXT_WARNING, m_txtWarning);
}


BEGIN_MESSAGE_MAP(CDlgWarning, CDialog)
END_MESSAGE_MAP()

