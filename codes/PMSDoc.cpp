// PMSDoc.cpp :  CPMSDoc ���ʵ��
//

#include "stdafx.h"
#include "PMS.h"

#include "PMSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPMSDoc

IMPLEMENT_DYNCREATE(CPMSDoc, CDocument)

BEGIN_MESSAGE_MAP(CPMSDoc, CDocument)
END_MESSAGE_MAP()


// CPMSDoc ����/����

CPMSDoc::CPMSDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPMSDoc::~CPMSDoc()
{
}

BOOL CPMSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPMSDoc ���л�

void CPMSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CPMSDoc ���

#ifdef _DEBUG
void CPMSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPMSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPMSDoc ����
