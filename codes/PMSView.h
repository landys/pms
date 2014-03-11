// PMSView.h : CPMSView 类的接口
//


#pragma once

#include "PMSDoc.h"
#include "StateView.h"

class CPMSView : public CListView
{
protected: // 仅从序列化创建
	CPMSView();
	DECLARE_DYNCREATE(CPMSView)

// 属性
public:
	CPMSDoc* GetDocument() const;
	
	CDaoRecordset m_RsPatient;
	CDaoDatabase m_Db;
	int m_nRow;
// 操作
public:
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
// 实现
public:
	virtual ~CPMSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// 在列表中插入一条记录
	void InsertItem(int nRow, int patientID, CString name, int age, int sex, int state, CString doctor, CString timeIn);
	// 修改列表中的记录
	void ModifyItem(int nRow, int patientID, CString name, int age, int sex, int state, CString doctor, CString timeIn);
	// 显示数据库中病人的所有记录到列表,并保存相关信息到病人信息链表
	void ShowAllData(BOOL isThread = FALSE);
	// 实现列表显示信息排序
	void SetSort(LPCTSTR pszSortField);
public:
	// 插入数据库,并更新相应列表显示
	void InsertDataBase(int patientID, CString name, int age, int sex, int state, CString timeIn, CString timeOut, CString doctor, 
		float stdBpHigh, float stdBpLow, float stdTempHigh, float stdTempLow, float stdCgHigh, float stdCgLow, int stdPulseHigh, int stdPulseLow);
	// 更新数据库,并更新相应列表显示
	void UpdateDataBase(int patientID, CString name, int age, int sex, int state, CString timeIn, CString timeOut, CString doctor, 
		float stdBpHigh, float stdBpLow, float stdTempHigh, float stdTempLow, float stdCgHigh, float stdCgLow, int stdPulseHigh, int stdPulseLow);
	// 删除数据库信息,并更新相应列表显示
	void DeleteDataBase(int patientID);
	// 初始病人对话框的数据
	void SetPatientData(int patientID);
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // PMSView.cpp 的调试版本
inline CPMSDoc* CPMSView::GetDocument() const
   { return reinterpret_cast<CPMSDoc*>(m_pDocument); }
#endif

