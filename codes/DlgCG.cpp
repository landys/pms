// DlgCG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PMS.h"
#include "DlgCG.h"
#include ".\dlgcg.h"
#include "MainFrm.h"


// CDlgCG �Ի���

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


// CDlgCG ��Ϣ�������

void CDlgCG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()


	// �����ڴ��л�ͼ,�ٻ�����Ļ��,����
	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);
	dcMem.SelectObject(&m_bmpBuf);

	CString strTxt;

	dcMem.Rectangle(0, 0, m_Rect.Width(), m_Rect.Height());
	dcMem.MoveTo(30, 0);
	dcMem.LineTo(30, m_Rect.Height());	//��ֱ��

	dcMem.MoveTo(30, 200);
	dcMem.LineTo(m_Rect.Width(), 200);	//ˮƽ��

	int i = 0;
	// Y��̶�
	for(i=300; i>=50;)
	{
		strTxt.Format("%d", 200 - i);
		dcMem.TextOut(0, i, strTxt);
		i -= 50;
	}

	CPen* pPenRed = new CPen;
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	// ��ɫ

	CGdiObject* pOldPen = dcMem.SelectObject(pPenRed);

	CMainFrame::m_CGData[0] = CMainFrame::m_CGData[0] + 150;
	// ��������ģ���ĵ�ͼ
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

	// ���ڴ���ͼ������Ļ��
	CWnd* pWnd = GetDlgItem(IDC_CG);
	CDC *pDC = pWnd->GetDC();
	pDC->BitBlt(0, 0, m_Rect.Width(), m_Rect.Height(), &dcMem, 0, 0, SRCCOPY);
}

BOOL CDlgCG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CWnd* pWnd = GetDlgItem(IDC_CG);
	CDC *pDC = pWnd->GetDC();

	
	pWnd->GetClientRect(&m_Rect);
	m_bmpBuf.CreateCompatibleBitmap(pDC, m_Rect.Width(), m_Rect.Height());

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ��д����������, �Ӷ�ʵ����Ļ����
BOOL CDlgCG::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CDialog::OnEraseBkgnd(pDC);
	return TRUE;
}
