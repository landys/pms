// PMSView.cpp : CPMSView ���ʵ��
//

#include "stdafx.h"
#include "PMS.h"

#include "PMSDoc.h"
#include "PMSView.h"
#include ".\pmsview.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "StateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPMSView

IMPLEMENT_DYNCREATE(CPMSView, CListView)

BEGIN_MESSAGE_MAP(CPMSView, CListView)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnLvnColumnclick)
	ON_NOTIFY_REFLECT(NM_CLICK, OnNMClick)
END_MESSAGE_MAP()

// CPMSView ����/����


CPMSView::CPMSView() : m_RsPatient(&m_Db), m_nRow(0)
{
	// TODO: �ڴ˴���ӹ������

	m_dwDefaultStyle |= (LVS_REPORT);
}

CPMSView::~CPMSView()
{
}

BOOL CPMSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CListView::PreCreateWindow(cs);
}

void CPMSView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	// �Ӷ������������ ListView��

	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt =  LVCFMT_LEFT;
	
	lvc.iSubItem = 0;
	lvc.pszText = _T("���");
	lvc.cx = 60;
	GetListCtrl().InsertColumn(0,&lvc);
	lvc.iSubItem = 1;
	lvc.pszText = _T("����");
	lvc.cx = 75;
	GetListCtrl().InsertColumn(1,&lvc);
	lvc.iSubItem = 2;
	lvc.pszText = _T("�Ա�");
	lvc.cx = 50;
	GetListCtrl().InsertColumn(2,&lvc);
	lvc.iSubItem = 3;
	lvc.pszText = _T("����");
	lvc.cx = 50;
	GetListCtrl().InsertColumn(3,&lvc);
	lvc.iSubItem = 4;
	lvc.pszText = _T("����");
	lvc.cx = 50;
	GetListCtrl().InsertColumn(4,&lvc);
	lvc.iSubItem = 5;
	lvc.pszText = _T("����ҽ��");
	lvc.cx = 75;
	GetListCtrl().InsertColumn(5,&lvc);
	lvc.iSubItem = 6;
	lvc.pszText = _T("סԺ����");
	lvc.cx = 140;
	GetListCtrl().InsertColumn(6,&lvc);

	try
	{
		ShowAllData(TRUE);
	}
	catch(...)
	{
		::AfxMessageBox("�����ݿ������ȷ�����ݿ��Ƿ��������ռ��");
	}

}

// �������ݿ�,��������Ӧ�б���ʾ
void CPMSView::InsertDataBase(int patientID, CString name, int age, int sex, int state, CString timeIn, CString timeOut, CString doctor, 
	float stdBpHigh, float stdBpLow, float stdTempHigh, float stdTempLow, float stdCgHigh, float stdCgLow, int stdPulseHigh, int stdPulseLow)
{
	if (!m_Db.IsOpen())
	{
		m_Db.Open(CMainFrame::m_Path);
	}

	CString strSql = "";
	strSql.Format("INSERT INTO patient VALUES (%d, '%s', %d, %d, %d, '%s', '%s', '%s', %f, %f, %f, %f, %f, %f, %d, %d)", 
		patientID, name, age, sex, state, timeIn, timeOut, doctor, stdBpHigh, stdBpLow, stdTempHigh, stdTempLow, stdCgHigh, stdCgLow, stdPulseHigh, stdPulseLow);
	try
	{
		m_Db.Execute(strSql);
		InsertItem(0, patientID, name, age, sex, state, doctor, timeIn);
		m_nRow++;
	}
	catch (...) 
	{
		::AfxMessageBox("�ò��˱���Ѵ��ڣ������벻ͬ�ı��");
	}
}

// �������ݿ�,��������Ӧ�б���ʾ
void CPMSView::UpdateDataBase(int patientID, CString name, int age, int sex, int state, CString timeIn, CString timeOut, CString doctor, 
		float stdBpHigh, float stdBpLow, float stdTempHigh, float stdTempLow, float stdCgHigh, float stdCgLow, int stdPulseHigh, int stdPulseLow)
{
	if (!m_Db.IsOpen())
	{
		m_Db.Open(CMainFrame::m_Path);
	}

	CString strSql = "";
	strSql.Format("UPDATE patient set name='%s', age=%d, sex=%d, state=%d, timeIn='%s', timeOut='%s', doctor='%s', stdBpHigh=%f, stdBpLow=%f, stdTempHigh=%f, stdTempLow=%f, stdCgHigh=%f, stdCgLow=%f, stdPulseHigh=%d, stdPulseLow=%d WHERE patientID=%d", 
		name, age, sex, state, timeIn, timeOut, doctor, stdBpHigh, stdBpLow, stdTempHigh, stdTempLow, stdCgHigh, stdCgLow, stdPulseHigh, stdPulseLow, patientID);
	try
	{
		CString strTxt = "";
		LVFINDINFO info;
		int nIndex;
		info.flags = LVFI_PARTIAL | LVFI_STRING;
		strTxt.Format("%d", patientID);
		info.psz = (LPCTSTR)(strTxt);

		if ((nIndex = GetListCtrl().FindItem(&info)) == -1)
		{
			return;
		}
		m_Db.Execute(strSql);
		
		ModifyItem(nIndex, patientID, name, age, sex, state, doctor, timeIn);
	}
	catch (...) 
	{
		::AfxMessageBox("�������ݿ�����������ݿ��Ƿ��������ռ��");
	}
}

// ɾ�����ݿ���Ϣ,��������Ӧ�б���ʾ
void CPMSView::DeleteDataBase(int patientID)
{
	if (!m_Db.IsOpen())
	{
		m_Db.Open(CMainFrame::m_Path);
	}

	CString strSql = "";
	strSql.Format("DELETE FROM patient WHERE patientID=%d", patientID);
	try
	{
		CString strTxt = "";
		LVFINDINFO info;
		int nIndex;
		info.flags = LVFI_PARTIAL | LVFI_STRING;
		strTxt.Format("%d", patientID);
		info.psz = (LPCTSTR)(strTxt);

		if ((nIndex = GetListCtrl().FindItem(&info)) == -1)
		{
			return;
		}
		m_Db.Execute(strSql);

		GetListCtrl().DeleteItem(nIndex);
	}
	catch (...) 
	{
		::AfxMessageBox("�ò��˱���Ѵ��ڣ������벻ͬ�ı��");
	}
}

// ���б��в���һ����¼
void CPMSView::InsertItem(int nRow, int patientID, CString name, int age, int sex, int state, CString doctor, CString timeIn)
{
	CString strText;

	strText.Format(TEXT("%d"), patientID);
	GetListCtrl().InsertItem(LVIF_TEXT | LVIF_IMAGE, nRow, strText, 0, 0, 0, 0);	//������

	GetListCtrl().SetItemText(nRow, 1, name);

	if(sex == 1)
	{
		GetListCtrl().SetItemText(nRow, 2, "��");
	}
	else if (sex == 0)
	{
		GetListCtrl().SetItemText(nRow, 2, "Ů");
	}

	strText.Format(TEXT("%d"), age);
	GetListCtrl().SetItemText(nRow, 3, strText);

	if(state == 2)
	{
		GetListCtrl().SetItemText(nRow, 4, "Σ��");
	}
	else if (state == 1)
	{
		GetListCtrl().SetItemText(nRow, 4, "��");
	}
	else if(state == 0)
	{
		GetListCtrl().SetItemText(nRow, 4, "��ͨ");
	}

	GetListCtrl().SetItemText(nRow, 5, doctor);
	GetListCtrl().SetItemText(nRow, 6, timeIn);
}

// �޸��б��еļ�¼
void CPMSView::ModifyItem(int nRow, int patientID, CString name, int age, int sex, int state, CString doctor, CString timeIn)
{
	CString strText = "";
	
	GetListCtrl().SetItemText(nRow, 1, name);

	if(sex == 1)
	{
		GetListCtrl().SetItemText(nRow, 2, "��");
	}
	else if (sex == 0)
	{
		GetListCtrl().SetItemText(nRow, 2, "Ů");
	}

	strText.Format(TEXT("%d"), age);
	GetListCtrl().SetItemText(nRow, 3, strText);

	if(state == 2)
	{
		GetListCtrl().SetItemText(nRow, 4, "Σ��");
	}
	else if (state == 1)
	{
		GetListCtrl().SetItemText(nRow, 4, "��");
	}
	else if(state == 0)
	{
		GetListCtrl().SetItemText(nRow, 4, "��ͨ");
	}

	GetListCtrl().SetItemText(nRow, 5, doctor);
	GetListCtrl().SetItemText(nRow, 6, timeIn);
}

// ��ʼ���˶Ի��������
void CPMSView::SetPatientData(int patientID)
{
	COleVariant varStr;  // �ֶ�����
	varStr.ChangeType(VT_BSTR, NULL);
	COleVariant varInt;
	varInt.ChangeType(VT_I4, NULL);
	COleVariant varFloat;
	varFloat.ChangeType(VT_R4, NULL);
	CString strName = "";
	CString strDoctor = "";
	int iAge = 0;
	int iState = 0;
	int iSex = 0;
	CString strTimeIn = "";
	float stdBpHigh = 0;
	float stdBpLow = 0;
	float stdTempHigh = 0;
	float stdTempLow = 0;
	float stdCgHigh = 0;
	float stdCgLow = 0;
	int stdPulseHigh = 0;
	int stdPulseLow = 0;

	CString strSql = "";
	strSql.Format("SELECT * FROM patient Where patientId=%d", patientID);
	m_RsPatient.Close();
	if(!m_Db.IsOpen())
	{
		m_Db.Open(CMainFrame::m_Path);
	}
	if (!m_RsPatient.IsOpen())
	{
		m_RsPatient.Open(AFX_DAO_USE_DEFAULT_TYPE,strSql,NULL);
	}

	m_RsPatient.MoveFirst();
	if (!m_RsPatient.IsEOF()) // ��û�е����β
	{
		m_RsPatient.GetFieldValue("name",varStr);
		strName = (LPCSTR)varStr.pbstrVal;
		m_RsPatient.GetFieldValue("doctor",varStr);
		strDoctor = (LPCSTR)varStr.pbstrVal;
		m_RsPatient.GetFieldValue("age", varInt);
		iAge = (long)varInt.plVal;
		m_RsPatient.GetFieldValue("state", varInt);
		iState = (long)varInt.plVal;
		m_RsPatient.GetFieldValue("sex", varInt);
		iSex = (long)varInt.plVal;
		m_RsPatient.GetFieldValue("timeIn", varStr);
		strTimeIn = (LPCSTR)varStr.pbstrVal;

		m_RsPatient.GetFieldValue("stdBpHigh", varFloat);
		stdBpHigh = (float)varFloat.fltVal;
		m_RsPatient.GetFieldValue("stdBpLow", varFloat);
		stdBpLow = (float)varFloat.fltVal;
		m_RsPatient.GetFieldValue("stdTempHigh", varFloat);
		stdTempHigh = (float)varFloat.fltVal;
		m_RsPatient.GetFieldValue("stdTempLow", varFloat);
		stdTempLow = (float)varFloat.fltVal;
		m_RsPatient.GetFieldValue("stdCgHigh", varFloat);
		stdCgHigh = (float)varFloat.fltVal;
		m_RsPatient.GetFieldValue("stdCgLow", varFloat);
		stdCgLow = (float)varFloat.fltVal;
		
		m_RsPatient.GetFieldValue("stdPulseHigh", varInt);
		stdPulseHigh = (long)varInt.plVal;
		m_RsPatient.GetFieldValue("stdPulseLow", varInt);
		stdPulseLow = (long)varInt.plVal;

		CDlgPatient* dp = new CDlgPatient(patientID, strName, iAge, iSex, iState, strTimeIn, 
			strDoctor, stdBpHigh, stdBpLow, stdTempHigh, stdTempLow, stdCgHigh, stdCgLow, stdPulseHigh, stdPulseLow);

		if (!dp->Create(IDD_DLG_PATIENT))
		{
			return;
		}
		dp->ShowWindow(SW_RESTORE);
	}
	m_RsPatient.Close();
}

// ��ʾ���ݿ��в��˵����м�¼���б�,�����������Ϣ��������Ϣ����
void CPMSView::ShowAllData(BOOL isThread /*= FALSE*/)
{
	COleVariant varStr;  // �ֶ�����
	varStr.ChangeType(VT_BSTR, NULL);
	COleVariant varInt;
	varInt.ChangeType(VT_I4, NULL);
	CString strName = "";
	CString strDoctor = "";
	int iAge = 0;
	int iPatientID = 0;
	int iState = 0;
	int iSex = 0;
	CString strTimeIn = "";

	COleVariant varFloat;
	varFloat.ChangeType(VT_R4, NULL);

	if(!m_Db.IsOpen())
	{
		m_Db.Open(CMainFrame::m_Path);
	}
	if (!m_RsPatient.IsOpen())
	{
		m_RsPatient.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM patient",NULL);
	}

	if (m_RsPatient.IsEOF())
	{
		return;
	}

	m_RsPatient.MoveFirst();
	while(!m_RsPatient.IsEOF()) // ��û�е����β
	{
		m_RsPatient.GetFieldValue("name",varStr);
		strName = (LPCSTR)varStr.pbstrVal;
		m_RsPatient.GetFieldValue("doctor",varStr);
		strDoctor = (LPCSTR)varStr.pbstrVal;
		m_RsPatient.GetFieldValue("age", varInt);
		iAge = (long)varInt.plVal;
		m_RsPatient.GetFieldValue("state", varInt);
		iState = (long)varInt.plVal;
		m_RsPatient.GetFieldValue("sex", varInt);
		iSex = (long)varInt.plVal;
		m_RsPatient.GetFieldValue("patientID", varInt);
		iPatientID = (long)varInt.plVal;
		m_RsPatient.GetFieldValue("timeIn", varStr);
		strTimeIn = (LPCSTR)varStr.pbstrVal;
		InsertItem(m_nRow, iPatientID, strName, iAge, iSex, iState, strDoctor, strTimeIn);
		
		// ���²��˸�Ϣ����
		if (isThread)
		{
			PatientInfo* pPin = new PatientInfo;
			pPin->next = CMainFrame::m_pinHead;
			CMainFrame::m_pinHead = pPin;
			pPin->patientId = iPatientID;
			pPin->dlgWarning = NULL;
			pPin->flagBp = FALSE;
			pPin->flagCg = FALSE;
			pPin->flagPulse = FALSE;
			pPin->flagTemp = FALSE;

			m_RsPatient.GetFieldValue("stdBpHigh", varFloat);
			pPin->stdBpHigh = (float)varFloat.fltVal;
			m_RsPatient.GetFieldValue("stdBpLow", varFloat);
			pPin->stdBpLow = (float)varFloat.fltVal;
			m_RsPatient.GetFieldValue("stdTempHigh", varFloat);
			pPin->stdTempHigh = (float)varFloat.fltVal;
			m_RsPatient.GetFieldValue("stdTempLow", varFloat);
			pPin->stdTempLow = (float)varFloat.fltVal;
			m_RsPatient.GetFieldValue("stdCgHigh", varFloat);
			pPin->stdCgHigh = (float)varFloat.fltVal;
			m_RsPatient.GetFieldValue("stdCgLow", varFloat);
			pPin->stdCgLow = (float)varFloat.fltVal;

			m_RsPatient.GetFieldValue("stdPulseHigh", varInt);
			pPin->stdPulseHigh = (long)varInt.plVal;
			m_RsPatient.GetFieldValue("stdPulseLow", varInt);
			pPin->stdPulseLow = (long)varInt.plVal;
		}

		m_nRow++;
		m_RsPatient.MoveNext();
	}
}

// CPMSView ���

#ifdef _DEBUG
void CPMSView::AssertValid() const
{
	CListView::AssertValid();
}

void CPMSView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPMSDoc* CPMSView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPMSDoc)));
	return (CPMSDoc*)m_pDocument;
}
#endif //_DEBUG

// ʵ���б���ʾ��Ϣ����
void CPMSView::SetSort(LPCTSTR pszSortField)
{
	m_RsPatient.m_strSort = pszSortField;
	if(!m_Db.IsOpen())
	{
		m_Db.Open(CMainFrame::m_Path);
	}
	if (!m_RsPatient.IsOpen())
	{
		m_RsPatient.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM patient",NULL);
	}
	
	CWaitCursor wait;
	m_RsPatient.Requery();
}

// CPMSView ��Ϣ�������

void CPMSView::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	switch(reinterpret_cast<NMLISTVIEW*>(pNMHDR)->iSubItem)
	{
	// ʵ�ְ�������Ŀ����
	case 0:
		SetSort(_T("[patientId]"));
		break;
	case 1:
		SetSort(_T("[name]"));
		break;
	case 2:
		SetSort(_T("[sex]"));
		break;
	case 3:
		SetSort(_T("[age]"));
		break;
	case 4:
		SetSort(_T("[state]"));
		break;
	case 5:
		SetSort(_T("[doctor]"));
		break;
	case 6:
		SetSort(_T("[timeIn]"));
		break;
	default:
		break;
	}
	GetListCtrl().DeleteAllItems();
	m_nRow = 0;
	ShowAllData();
	
	*pResult = 0;
}

// ���ĳһ���б��¼ʱ��Ӧ����
void CPMSView::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CMainFrame* pFrame = static_cast<CMainFrame*>(::AfxGetMainWnd());
	CLeftView* pView = static_cast<CLeftView*>(pFrame->m_Splitter.GetPane(0, 0));

	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = GetListCtrl().GetNextSelectedItem(pos);
		CString ss = GetListCtrl().GetItemText(nIndex, 0);
		pView->m_txtPatientId.SetWindowText(ss);
		CMainFrame::m_iCGData = 0;
		for (int j=0; j<30; j++)
		{
			CMainFrame::m_CGData[j] = 0.0;
		}
		int ii = 0;
		for (int i=0; i<ss.GetLength(); i++)
		{
			ii = ii * 10 + (ss[i]-'0');
		}
		CMainFrame::m_curPatientId = ii;
	}
	else
	{
		pView->m_txtPatientId.SetWindowText("");
		CMainFrame::m_curPatientId = 0;
	}
	*pResult = 0;
}

