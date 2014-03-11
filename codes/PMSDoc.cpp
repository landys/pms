// PMSDoc.cpp :  CPMSDoc 类的实现
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


// CPMSDoc 构造/析构

CPMSDoc::CPMSDoc()
{
	// TODO: 在此添加一次性构造代码

}

CPMSDoc::~CPMSDoc()
{
}

BOOL CPMSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPMSDoc 序列化

void CPMSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CPMSDoc 诊断

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


// CPMSDoc 命令
