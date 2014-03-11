// StateView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PMS.h"
#include "StateView.h"
#include ".\stateview.h"


// CStateView

IMPLEMENT_DYNCREATE(CStateView, CListView)

CStateView::CStateView()
{
	m_dwDefaultStyle |= ( LVS_REPORT);	// ���ó�ʼ״̬
}

CStateView::~CStateView()
{
}

BEGIN_MESSAGE_MAP(CStateView, CListView)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnLvnColumnclick)
END_MESSAGE_MAP()


// CStateView ���

#ifdef _DEBUG
void CStateView::AssertValid() const
{
	CListView::AssertValid();
}

void CStateView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG


// CStateView ��Ϣ�������

void CStateView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// �ڹ��캯�������˳�ʼ״̬
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt =  LVCFMT_LEFT;

	lvc.iSubItem = 0;
	lvc.pszText = _T("���");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(0, &lvc);
	lvc.iSubItem = 1;
	lvc.pszText = _T("ʱ��");
	lvc.cx = 135;
	GetListCtrl().InsertColumn(1, &lvc);
	lvc.iSubItem = 2;
	lvc.pszText = _T("Ѫѹ");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(2, &lvc);
	lvc.iSubItem = 3;
	lvc.pszText = _T("����");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(3, &lvc);
	lvc.iSubItem = 4;
	lvc.pszText = _T("�ĵ�");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(4, &lvc);
	lvc.iSubItem = 5;
	lvc.pszText = _T("����");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(5, &lvc);
}

// �����¼
void CStateView::InsertItem(int nRow, int patientID, CString curTime, float bp, float temp, float cg, int pulse)
{
	CString strText;

	strText.Format(TEXT("%d"), patientID);
	GetListCtrl().InsertItem(LVIF_TEXT | LVIF_IMAGE, nRow, strText, 0, 0, 0, 0);	//������

	GetListCtrl().SetItemText(nRow, 1, curTime);

	strText.Format(TEXT("%.2f"), bp);
	GetListCtrl().SetItemText(nRow, 2, strText);

	strText.Format(TEXT("%.2f"), temp);
	GetListCtrl().SetItemText(nRow, 3, strText);

	strText.Format(TEXT("%.2f"), cg);
	GetListCtrl().SetItemText(nRow, 4, strText);

	strText.Format(TEXT("%d"), pulse);
	GetListCtrl().SetItemText(nRow, 5, strText);
}

void CStateView::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	InsertItem(0, 3, "2005-1-5", 34.34, 343.343, 534.45, 100);
	*pResult = 0;
}
