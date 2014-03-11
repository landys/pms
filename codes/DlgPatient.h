#pragma once
#include "atlcomtime.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CDlgPatient �Ի���

class CDlgPatient : public CDialog
{
	DECLARE_DYNAMIC(CDlgPatient)

public:
	CDlgPatient(CWnd* pParent = NULL);   // ��׼���캯��
	CDlgPatient(int patientID, CString name, int age, int sex, int state, CString timeIn, CString doctor, 
		float stdBpHigh, float stdBpLow, float stdTempHigh, float stdTempLow, float stdCgHigh, float stdCgLow, int stdPulseHigh, int stdPulseLow, CWnd* pParent = NULL);
	virtual ~CDlgPatient();

// �Ի�������
	enum { IDD = IDD_DLG_PATIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_PatientId;	// ���
	CString m_Name;	// ����
	CString m_Doctor;	// ����ҽ������
	int m_Age;	// ����
	float m_CGHigh;	// �ĵ�����
	float m_CGLow;	// �ĵ�����
	float m_TempHigh;	// ��������
	float m_TempLow;	// ��������
	float m_BPHigh;	// Ѫѹ����
	float m_BPLow;	// Ѫѹ����
	int m_PulseHigh;	// ��������
	int m_PulseLow;	// ��������
	afx_msg void OnBnClickedOk();
	COleDateTime m_TimeIn;	// ʱ��
	virtual BOOL OnInitDialog();
	CButton m_rbtnMale;	// ���Ե�ѡ��
	CButton m_rbtnFemale;	// Ů�Ե�ѡ��
	CButton m_rbtnDanger;	// ��Σ��ѡ��
	CButton m_rbtnBad;	// ���ص�ѡ��
	CButton m_rbtnNormal;	// ������ѡ��

	int m_Sex;	// �Ա�
	int m_State;	// ����״̬
	CString m_strTimeIn;	// ʱ��

	BOOL m_isAdd;	// �Ƿ�����Ӳ���
	CEdit m_txtPatientId;
	CDateTimeCtrl m_dtTimeIn;
};
