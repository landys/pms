#pragma once

// CStateView 视图

class CStateView : public CListView
{
	DECLARE_DYNCREATE(CStateView)

protected:
	CStateView();           // 动态创建所使用的受保护的构造函数
	virtual ~CStateView();

public:
	// 插入记录
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


