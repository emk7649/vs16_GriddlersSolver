
// GriddlersSolverDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GriddlersSolver.h"
#include "GriddlersSolverDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGriddlersSolverDlg 대화 상자



CGriddlersSolverDlg::CGriddlersSolverDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRIDDLERSSOLVER_DIALOG, pParent)
	, m_edit_rows(_T(""))
	, m_edit_columns(_T(""))
	, m_static_columnrow(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGriddlersSolverDlg::~CGriddlersSolverDlg()
{
}

void CGriddlersSolverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROW, m_edit_rows);
	DDX_Text(pDX, IDC_EDIT_COLUMN, m_edit_columns);
	DDX_Text(pDX, IDC_STATIC_COLUMNROW, m_static_columnrow);
}

BEGIN_MESSAGE_MAP(CGriddlersSolverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MakePlate, &CGriddlersSolverDlg::OnBnClickedBtnMakeplate)
	ON_BN_CLICKED(IDC_BTN_SolveProblem, &CGriddlersSolverDlg::OnBnClickedBtnSolveproblem)
END_MESSAGE_MAP()


// CGriddlersSolverDlg 메시지 처리기

BOOL CGriddlersSolverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitView();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGriddlersSolverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGriddlersSolverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGriddlersSolverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CGriddlersSolverDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (GetDlgItem(IDC_EDIT_ROW) == GetFocus() || GetDlgItem(IDC_EDIT_COLUMN) == GetFocus())
			{
				CEdit* edit = (CEdit*)GetFocus();
				int nLen = edit->GetWindowTextLength();
				edit->SetSel(nLen, nLen);
				edit->ReplaceSel(_T("\r\n"));
			}
			else
				return TRUE;
		}
		else if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CGriddlersSolverDlg::ConvertRowColumn(CString strValue, vector<vector<int>>& o_vvValue)
{
	// line to line seperator : '\n', '\r\n'
	// word to word seperator : ' ', ',', '.'

	strValue.Replace(_T("\r"), _T(""));
	strValue.Replace(_T(" "), _T(","));
	strValue.Replace(_T("."), _T(","));

	CString SeperatorLine = _T("\n");
	CString SeperatorWord = _T(",");
	int PositionLine = 0;
	int PositionWord = 0;
	CString line, word;

	// 몇 개나 되겠어, push_back 써라
	while (true) // while (!line.IsEmpty());
	{
		// Get next token.
		line = strValue.Tokenize(SeperatorLine, PositionLine);
		if (PositionLine == -1)
			break;

		vector<int> o_line;
		PositionWord = 0;
		while (true)
		{
			// Get next token.
			word = line.Tokenize(SeperatorWord, PositionWord);
			if (PositionWord == -1)
				break;

			o_line.push_back(_ttol(word));
		}
		o_vvValue.push_back(o_line);
	}
}

void CGriddlersSolverDlg::InitView()
{
	CRect viewRect;
	GetDlgItem(IDC_VIEW)->GetWindowRect(viewRect);
	ScreenToClient(viewRect);

	// assign view
}

void CGriddlersSolverDlg::OnBnClickedBtnMakeplate()
{
	UpdateData(true);
	m_vvRow.clear();
	m_vvRow.clear();

	ConvertRowColumn(m_edit_rows, m_vvRow);
	ConvertRowColumn(m_edit_columns, m_vvColumn);

	int size_row = m_vvRow.size();
	int size_column = m_vvColumn.size();

	CString RowColumn;
	RowColumn.Format(_T(""));
}

void CGriddlersSolverDlg::OnBnClickedBtnSolveproblem()
{

}
