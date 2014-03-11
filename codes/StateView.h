#pragma once

// CStateView ��ͼ

class CStateView : public CListView
{
	DECLARE_DYNCREATE(CStateView)

protected:
	CStateView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CStateView();

public:
	// �����¼
	void InsertItem(int nRow, int patientID, CString curTime, float bp, float temp, float cg, int pulse);
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
};


