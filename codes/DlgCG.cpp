// DlgCG.cpp : 实现文件
//

#include "stdafx.h"
#include "PMS.h"
#include "DlgCG.h"
#include ".\dlgcg.h"
#include "MainFrm.h"


// CDlgCG 对话框

IMPLEMENT_DYNAMIC(CDlgCG, CDialog)
CDlgCG::CDlgCG(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCG::IDD, pParent)
{
}

CDlgCG::~CDlgCG()
{
}

void CDlgCG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCG, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgCG 消息处理程序

void CDlgCG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()


	// 先在内存中画图,再画到屏幕上,不闪
	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);
	dcMem.SelectObject(&m_bmpBuf);

	CString strTxt;

	dcMem.Rectangle(0, 0, m_Rect.Width(), m_Rect.Height());
	dcMem.MoveTo(30, 0);
	dcMem.LineTo(30, m_Rect.Height());	//垂直轴

	dcMem.MoveTo(30, 200);
	dcMem.LineTo(m_Rect.Width(), 200);	//水平轴

	int i = 0;
	// Y轴刻度
	for(i=300; i>=50;)
	{
		strTxt.Format("%d", 200 - i);
		dcMem.TextOut(0, i, strTxt);
		i -= 50;
	}

	CPen* pPenRed = new CPen;
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	// 红色

	CGdiObject* pOldPen = dcMem.SelectObject(pPenRed);

	CMainFrame::m_CGData[0] = CMainFrame::m_CGData[0] + 150;
	// 处理数据模拟心电图
	for(i = 1; i < 30; i++)
	{
		if (CMainFrame::m_CGData[i] <= -120)
		{
			CMainFrame::m_CGData[i] = -120;
		}
		else if (CMainFrame::m_CGData[i] >= 180)
		{
			CMainFrame::m_CGData[i] = 180;
		}
		else if (CMainFrame::m_CGData[i] < 50 && CMainFrame::m_CGData[i] >=0)
		{
			CMainFrame::m_CGData[i] += 70;
		}
		else if (CMainFrame::m_CGData[i] > -50 && CMainFrame::m_CGData[i] <0)
		{
			CMainFrame::m_CGData[i] -= 50;
		}

		if (CMainFrame::m_CGData[i] * CMainFrame::m_CGData[i] > 0)
		{
			CMainFrame::m_CGData[i] = -CMainFrame::m_CGData[i];
		}

		CMainFrame::m_CGData[i] = CMainFrame::m_CGData[i] + 150;
	}

	int j = 30;
	dcMem.MoveTo(j, (int)CMainFrame::m_CGData[0]);
	for(i = 1; i < 30; i++)
	{
		j = j + 12;
		dcMem.LineTo(j, (int)CMainFrame::m_CGData[i]);
	}

	// 把内存中图画到屏幕上
	CWnd* pWnd = GetDlgItem(IDC_CG);
	CDC *pDC = pWnd->GetDC();
	pDC->BitBlt(0, 0, m_Rect.Width(), m_Rect.Height(), &dcMem, 0, 0, SRCCOPY);
}

BOOL CDlgCG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CWnd* pWnd = GetDlgItem(IDC_CG);
	CDC *pDC = pWnd->GetDC();

	
	pWnd->GetClientRect(&m_Rect);
	m_bmpBuf.CreateCompatibleBitmap(pDC, m_Rect.Width(), m_Rect.Height());

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 重写不擦除背景, 从而实现屏幕不闪
BOOL CDlgCG::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CDialog::OnEraseBkgnd(pDC);
	return TRUE;
}
