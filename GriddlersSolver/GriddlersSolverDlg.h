
#pragma once

#include <vector>
using namespace std;


// CGriddlersSolverDlg 대화 상자
class CGriddlersSolverDlg : public CDialogEx
{
// 생성입니다.
public:
	CGriddlersSolverDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	virtual ~CGriddlersSolverDlg();

	vector<vector<int>> m_vvRow;
	vector<vector<int>> m_vvColumn;

	void ConvertRowColumn(CString strValue, vector<vector<int>>& o_vvValue);
	void InitView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRIDDLERSSOLVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_edit_rows;
	CString m_edit_columns;
	CString m_static_columnrow;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnMakeplate();
	afx_msg void OnBnClickedBtnSolveproblem();
};
