// PMSDoc.h :  CPMSDoc ��Ľӿ�
//


#pragma once

class CPMSDoc : public CDocument
{
protected: // �������л�����
	CPMSDoc();
	DECLARE_DYNCREATE(CPMSDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPMSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


