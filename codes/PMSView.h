// PMSView.h : CPMSView ��Ľӿ�
//


#pragma once

#include "PMSDoc.h"
#include "StateView.h"

class CPMSView : public CListView
{
protected: // �������л�����
	CPMSView();
	DECLARE_DYNCREATE(CPMSView)

// ����
public:
	CPMSDoc* GetDocument() const;
	
	CDaoRecordset m_RsPatient;
	CDaoDatabase m_Db;
	int m_nRow;
// ����
public:
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
// ʵ��
public:
	virtual ~CPMSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// ���б��в���һ����¼
	void InsertItem(int nRow, int patientID, CString name, int age, int sex, int state, CString doctor, CString timeIn);
	// �޸��б��еļ�¼
	void ModifyItem(int nRow, int patientID, CString name, int age, int sex, int state, CString doctor, CString timeIn);
	// ��ʾ���ݿ��в��˵����м�¼���б�,�����������Ϣ��������Ϣ����
	void ShowAllData(BOOL isThread = FALSE);
	// ʵ���б���ʾ��Ϣ����
	void SetSort(LPCTSTR pszSortField);
public:
	// �������ݿ�,��������Ӧ�б���ʾ
	void InsertDataBase(int patientID, CString name, int age, int sex, int state, CString timeIn, CString timeOut, CString doctor, 
		float stdBpHigh, float stdBpLow, float stdTempHigh, float stdTempLow, float stdCgHigh, float stdCgLow, int stdPulseHigh, int stdPulseLow);
	// �������ݿ�,��������Ӧ�б���ʾ
	void UpdateDataBase(int patientID, CString name, int age, int sex, int state, CString timeIn, CString timeOut, CString doctor, 
		float stdBpHigh, float stdBpLow, float stdTempHigh, float stdTempLow, float stdCgHigh, float stdCgLow, int stdPulseHigh, int stdPulseLow);
	// ɾ�����ݿ���Ϣ,��������Ӧ�б���ʾ
	void DeleteDataBase(int patientID);
	// ��ʼ���˶Ի��������
	void SetPatientData(int patientID);
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // PMSView.cpp �ĵ��԰汾
inline CPMSDoc* CPMSView::GetDocument() const
   { return reinterpret_cast<CPMSDoc*>(m_pDocument); }
#endif

