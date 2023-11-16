
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

bool CreateCImage(CImage& cimage, long width, long height, long nPixelCount)
{
	cimage.Destroy();
	BYTE tmp[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
	void* pBits;
	LPBITMAPINFO pbmi((BITMAPINFO*)tmp);
	memset(&pbmi->bmiHeader, 0, sizeof(pbmi->bmiHeader));
	pbmi->bmiHeader.biSize = sizeof(pbmi->bmiHeader);
	pbmi->bmiHeader.biWidth = width;
	pbmi->bmiHeader.biHeight = height;
	pbmi->bmiHeader.biPlanes = 1;
	pbmi->bmiHeader.biBitCount = USHORT(nPixelCount);
	pbmi->bmiHeader.biCompression = BI_RGB;
	if (pbmi->bmiHeader.biBitCount <= 8)
		memset(pbmi->bmiColors, 0, 256 * sizeof(RGBQUAD));
	WORD& bpp = pbmi->bmiHeader.biBitCount;
	switch (bpp)
	{
	case 8:
		for (long i = 0; i < 256; i++)
		{
			pbmi->bmiColors[i].rgbBlue = (BYTE)i;
			pbmi->bmiColors[i].rgbGreen = (BYTE)i;
			pbmi->bmiColors[i].rgbRed = (BYTE)i;
		}
		break;
	case 32:
	case 24:
		((DWORD*)pbmi->bmiColors)[0] = 0x00FF0000; /* red mask  */
		((DWORD*)pbmi->bmiColors)[1] = 0x0000FF00; /* green mask */
		((DWORD*)pbmi->bmiColors)[2] = 0x000000FF; /* blue mask  */
		break;
	}
	HBITMAP hBitmap = ::CreateDIBSection(NULL, pbmi, DIB_RGB_COLORS, &pBits, NULL, 0);
	ASSERT(hBitmap != NULL);
	cimage.Attach(hBitmap, (pbmi->bmiHeader.biHeight < 0) ? CImage::DIBOR_TOPDOWN : CImage::DIBOR_BOTTOMUP);
	return true;
}

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

	m_edit_rows = _T("3\r\n2,2,\r\n1,1,\r\n2,2,\r\n3,");
	m_edit_columns = _T("3,\r\n2,2,\r\n1,1,\r\n2,2,\r\n3,");
	UpdateData(false);

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

int CGriddlersSolverDlg::ConvertRowColumn(CString strValue, vector<vector<int>>& o_vvValue)
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

    int sum, sum_line;
    sum = 0;

    // 몇 개나 되겠어, push_back 써라
    while (true) // while (!line.IsEmpty());
    {
        // Get next token.
        line = strValue.Tokenize(SeperatorLine, PositionLine);
        if (PositionLine == -1)
            break;

        vector<int> o_line;
        PositionWord = 0;
        sum_line = 0;
        while (true)
        {
			// Get next token.
            word = line.Tokenize(SeperatorWord, PositionWord);
            if (PositionWord == -1)
                break;

            int value = _ttol(word);
            o_line.push_back(value);
            sum_line += value;
        }

        o_vvValue.push_back(o_line);
        sum += sum_line;
    }

    return sum;
}

void CGriddlersSolverDlg::MakeSquareMonochrome(CImage& plate, CPoint pos, BYTE gray_value)
{
	if (plate.GetBPP() != 8)
		return;

	BYTE* Dst = (BYTE*)plate.GetPixelAddress(pos.x, pos.y);
	*Dst = gray_value;
}

void CGriddlersSolverDlg::MakeSquareColor(CImage& plate, CPoint pos, COLORREF color)
{
	if (plate.GetBPP() != 24)
		return;

	BYTE* Dst = (BYTE*)plate.GetPixelAddress(pos.x, pos.y);

	BYTE red = (BYTE)(color >> 0);
	BYTE green = (BYTE)(color >> 8);
	BYTE blue = (BYTE)(color >> 16);

	Dst[0] = blue;
	Dst[1] = green;
	Dst[2] = red;
}

void CGriddlersSolverDlg::MakeDrawPlate(CImage& plateData, CImage& plateDraw)
{
	long widthSrc = plateData.GetWidth();
	long heightSrc = plateData.GetHeight();

	for (long y = 0; y < heightSrc; y++)
	{
		BYTE* Src = (BYTE*)plateData.GetPixelAddress(0, y);
		BYTE* Dst = (BYTE*)plateDraw.GetPixelAddress(0, y);
		for (long x = 0; x < widthSrc; x++)
		{
			switch (Src[x])
			{
			case 0:    // 未定, make chess pattern (gray & white)
			{
				if ((x + y) % 2 == 1)
				{
					Dst[x * plateDraw.GetBPP() / 8 + 0] = 192;
					Dst[x * plateDraw.GetBPP() / 8 + 1] = 192;
					Dst[x * plateDraw.GetBPP() / 8 + 2] = 192;
				}
				else
				{
					Dst[x * plateDraw.GetBPP() / 8 + 0] = 255;
					Dst[x * plateDraw.GetBPP() / 8 + 1] = 255;
					Dst[x * plateDraw.GetBPP() / 8 + 2] = 255;
				}
				break;
			}
			case 1:    // 有, make black
			{
				Dst[x * plateDraw.GetBPP() / 8 + 0] = 0;
				Dst[x * plateDraw.GetBPP() / 8 + 1] = 0;
				Dst[x * plateDraw.GetBPP() / 8 + 2] = 0;
				break;
			}
			case 2:    // 無, make red
			{
				Dst[x * plateDraw.GetBPP() / 8 + 0] = 0;
				Dst[x * plateDraw.GetBPP() / 8 + 1] = 0;
				Dst[x * plateDraw.GetBPP() / 8 + 2] = 255;
				break;
			}
			default:;
			}
		}
	}
}

void CGriddlersSolverDlg::InitView()
{
	//CRect viewRect;
	//GetDlgItem(IDC_VIEW)->GetWindowRect(viewRect);
	//ScreenToClient(viewRect);

	m_view.hwnd = GetSafeHwnd();
	m_view.m_control = GetDlgItem(IDC_VIEW);
}

void CGriddlersSolverDlg::FillZero(CImage& image)
{
	int width = image.GetWidth();
	int height = image.GetHeight();
	if (width == 0 || height == 0)
		return;

	int pitch = std::abs(image.GetPitch());
	BYTE* zeros = new BYTE[pitch];
	memset(zeros, 0, pitch);
	for (long y = 0; y < height; y++)
	{
		BYTE* Dst = (BYTE*)image.GetPixelAddress(0, y);
		memcpy(Dst, zeros, pitch);
	}
	delete[] zeros;
}

// Get LineVector from PlateDatas
bool CGriddlersSolverDlg::GetLineVector(CImage& plateData, GridElement grid_element, int line_index, vector<BYTE>& o_line)
{
	if (plateData.GetWidth() == 0)
		return false;

	vector<BYTE>& result = o_line;

	long width = plateData.GetWidth();
	long height = plateData.GetHeight();

	if (grid_element == GridElement::ROW)
	{
		result.resize(plateData.GetWidth());
		for (long x = 0; x < width; x++)
		{
			BYTE* byte = (BYTE*)plateData.GetPixelAddress(x, line_index);
			result[x] = *byte;
		}
	}
	else if (grid_element == GridElement::COLUMN)
	{
		result.resize(plateData.GetHeight());
		for (long y = 0; y < height; y++)
		{
			BYTE* byte = (BYTE*)plateData.GetPixelAddress(line_index, y);
			result[y] = *byte;
		}
	}

	return true;
}

// Set LineVector to PlateDatas
bool CGriddlersSolverDlg::SetLineVector(CImage& plateData, GridElement grid_element, int line_index, const vector<BYTE>& i_line)
{
	if (plateData.GetWidth() == 0)
		return false;

	long width = plateData.GetWidth();
	long height = plateData.GetHeight();

	if (grid_element == GridElement::ROW)
	{
		if (i_line.size() != width)
			return false;
		for (long x = 0; x < width; x++)
		{
			BYTE* dst = (BYTE*)plateData.GetPixelAddress(x, line_index);
			*dst = i_line[x];
		}
	}
	else if (grid_element == GridElement::COLUMN)
	{
		if (i_line.size() != height)
			return false;
		for (long y = 0; y < height; y++)
		{
			BYTE* dst = (BYTE*)plateData.GetPixelAddress(line_index, y);
			*dst = i_line[y];
		}
	}
	return false;
}

bool CGriddlersSolverDlg::SolveLineSolve1(CImage& io_plateData, sLineSolve lineSolve)
{
	GridElement& grid_element = lineSolve.grid_element;
	int& line_index = lineSolve.line_index;

	vector<int> blocks;
	if (grid_element == GridElement::ROW)
		blocks = m_blocks_row[line_index];
	else if (grid_element == GridElement::COLUMN)
		blocks = m_blocks_column[line_index];

	CImage& plateData = io_plateData;
	vector<BYTE> line;
	if (!GetLineVector(plateData, grid_element, line_index, line))
		return false;

	int nOccupy = 0;
	for (long cnt = 0; cnt < blocks.size(); cnt++)
	{
		nOccupy += blocks[cnt];
	}
	int nMargin = line.size() - nOccupy - blocks.size() + 1;

	// Algorithm
	// do solve line
	// do solve line
	// do solve line
	// if, 하나도 안 채워졌을 때
	int sumLine = 0;
	for (long cnt = 0; cnt < line.size(); cnt++)
	{
		sumLine += line[cnt];
	}
	if (sumLine == 0)
	{
		// if nMargin + each block > line.size()
		// 해당 블록 이전 숫자 합 + cnt = first block pos
		// first block pos + margin = occupy square start pos
		int sumBlock = 0;
		for (long cnt = 0; cnt < blocks.size(); cnt++)
		{
			if (blocks[cnt] - nMargin > 0)
			{
				int startPos_occupy = sumBlock + cnt + nMargin;
				int size_occupy = blocks[cnt] - nMargin;
				for (long blockPos = startPos_occupy; blockPos < startPos_occupy + size_occupy; blockPos++)
				{
					line[blockPos] = 1;
				}
			}
			sumBlock += blocks[cnt];
		}
	}
	// if not, Normal Algorithm
	// 모든 경우의 수를 구하고 &
	// 중복 combination, nNCr = n^r / r!
	// n = b + 1, block 사이 또는 양 끝
	// r = m, nMargin
	else
	{

	}

	if (!SetLineVector(plateData, grid_element, line_index, line))
		return false;
}

void CGriddlersSolverDlg::OnBnClickedBtnMakeplate()
{
	UpdateData(true);
	m_blocks_row.clear();
	m_blocks_column.clear();

	int sum_row = ConvertRowColumn(m_edit_rows, m_blocks_row);
	int sum_column = ConvertRowColumn(m_edit_columns, m_blocks_column);

	// check sum_row == sum_column
	if (sum_row != sum_column)
	{
		AfxMessageBox(_T("error {5CA8658B-9447-4178-B71E-8335E70AFC0D}, sum_row != sum_column"));
		return;
	}

	int size_row = (int)m_blocks_row.size();
	int size_column = (int)m_blocks_column.size();

	m_static_columnrow.Format(_T("%d * %d"), size_column, size_row);
	UpdateData(false);

	// make plate
	CreateCImage(m_plateData, size_row, size_column, 8);
	CreateCImage(m_plateDraw, size_row, size_column, 24);
	MakeDrawPlate(m_plateData, m_plateDraw);
	m_view.SetImage(m_plateDraw);
}

void CGriddlersSolverDlg::OnBnClickedBtnSolveproblem()
{
	int width = m_plateData.GetWidth();
	int height = m_plateData.GetHeight();
	if (width == 0 || height == 0)
		return;

	// init queue
	m_completionChecker.SetSize(width, height);
	for (int cnt = 0; cnt < height; cnt++)
	{
		m_queueLineSolve.push_back(GridElement::ROW, cnt);
	}
	for (int cnt = 0; cnt < width; cnt++)
	{
		m_queueLineSolve.push_back(GridElement::COLUMN, cnt);
	}

	// while queue
	while (!m_queueLineSolve.empty())
	{
		SolveLineSolve1(m_plateData, *m_queueLineSolve.pop_front());
		long x = 10;

	}
	MakeDrawPlate(m_plateData, m_plateDraw);
	m_view.SetImage(m_plateDraw);
}