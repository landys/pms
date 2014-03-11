// StateView.cpp : 实现文件
//

#include "stdafx.h"
#include "PMS.h"
#include "StateView.h"
#include ".\stateview.h"


// CStateView

IMPLEMENT_DYNCREATE(CStateView, CListView)

CStateView::CStateView()
{
	m_dwDefaultStyle |= ( LVS_REPORT);	// 设置初始状态
}

CStateView::~CStateView()
{
}

BEGIN_MESSAGE_MAP(CStateView, CListView)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnLvnColumnclick)
END_MESSAGE_MAP()


// CStateView 诊断

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


// CStateView 消息处理程序

void CStateView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// 在构造函数中设了初始状态
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt =  LVCFMT_LEFT;

	lvc.iSubItem = 0;
	lvc.pszText = _T("编号");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(0, &lvc);
	lvc.iSubItem = 1;
	lvc.pszText = _T("时间");
	lvc.cx = 135;
	GetListCtrl().InsertColumn(1, &lvc);
	lvc.iSubItem = 2;
	lvc.pszText = _T("血压");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(2, &lvc);
	lvc.iSubItem = 3;
	lvc.pszText = _T("体温");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(3, &lvc);
	lvc.iSubItem = 4;
	lvc.pszText = _T("心电");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(4, &lvc);
	lvc.iSubItem = 5;
	lvc.pszText = _T("脉搏");
	lvc.cx = 68;
	GetListCtrl().InsertColumn(5, &lvc);
}

// 插入记录
void CStateView::InsertItem(int nRow, int patientID, CString curTime, float bp, float temp, float cg, int pulse)
{
	CString strText;

	strText.Format(TEXT("%d"), patientID);
	GetListCtrl().InsertItem(LVIF_TEXT | LVIF_IMAGE, nRow, strText, 0, 0, 0, 0);	//插入编号

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
	// TODO: 在此添加控件通知处理程序代码

	InsertItem(0, 3, "2005-1-5", 34.34, 343.343, 534.45, 100);
	*pResult = 0;
}
