#pragma once
#include "atlcomtime.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CDlgPatient 对话框

class CDlgPatient : public CDialog
{
	DECLARE_DYNAMIC(CDlgPatient)

public:
	CDlgPatient(CWnd* pParent = NULL);   // 标准构造函数
	CDlgPatient(int patientID, CString name, int age, int sex, int state, CString timeIn, CString doctor, 
		float stdBpHigh, float stdBpLow, float stdTempHigh, float stdTempLow, float stdCgHigh, float stdCgLow, int stdPulseHigh, int stdPulseLow, CWnd* pParent = NULL);
	virtual ~CDlgPatient();

// 对话框数据
	enum { IDD = IDD_DLG_PATIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_PatientId;	// 编号
	CString m_Name;	// 姓名
	CString m_Doctor;	// 主治医生姓名
	int m_Age;	// 年龄
	float m_CGHigh;	// 心电上限
	float m_CGLow;	// 心电下限
	float m_TempHigh;	// 体温上限
	float m_TempLow;	// 体温下限
	float m_BPHigh;	// 血压上限
	float m_BPLow;	// 血压下限
	int m_PulseHigh;	// 脉搏上限
	int m_PulseLow;	// 脉搏下限
	afx_msg void OnBnClickedOk();
	COleDateTime m_TimeIn;	// 时间
	virtual BOOL OnInitDialog();
	CButton m_rbtnMale;	// 男性单选框
	CButton m_rbtnFemale;	// 女性单选框
	CButton m_rbtnDanger;	// 病危单选框
	CButton m_rbtnBad;	// 病重单选框
	CButton m_rbtnNormal;	// 正常单选框

	int m_Sex;	// 性别
	int m_State;	// 病性状态
	CString m_strTimeIn;	// 时间

	BOOL m_isAdd;	// 是否是添加病人
	CEdit m_txtPatientId;
	CDateTimeCtrl m_dtTimeIn;
};
