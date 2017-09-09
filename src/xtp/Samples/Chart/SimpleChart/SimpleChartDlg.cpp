// SimpleChartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleChart.h"
#include "SimpleChartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSimpleChartDlg dialog

CSimpleChartDlg::CSimpleChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimpleChartDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleChartDlg)
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimpleChartDlg, CDialog)
	//{{AFX_MSG_MAP(CSimpleChartDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// NOTE: user control styles used.
//#define WS_CHART (WS_CHILD|WS_BORDER|WS_VISIBLE|WS_TABSTOP)

/////////////////////////////////////////////////////////////////////////////
// CSimpleChartDlg message handlers

BOOL CSimpleChartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize the chart control.
	InitChart();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CSimpleChartDlg::InitChart()
{
	// ----------------------------------------------------------------------
	// INITIALIZE CHART
	// ----------------------------------------------------------------------
	// Get a pointer to the chart's CXTPChartContent object. We can use this 
	// object to access the elements necessary to initialize the chart such 
	// as chart titles, series and legends.

	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	if (pContent)
	{
		// ------------------------------------------------------------------
		// ADD A TITLE TO THE CHART
		// ------------------------------------------------------------------
		// Get a pointer to the chart's CXTPChartTitleCollection object. We use
		// this add a title to the chart.
		
		CXTPChartTitleCollection* pTitles = pContent->GetTitles();
		if (pTitles)
		{
			CXTPChartTitle* pTitle = pTitles->Add(new CXTPChartTitle());
			if (pTitle)
			{
				pTitle->SetText(_T("My Chart"));
			}
		}
		
		// ------------------------------------------------------------------
		// ADD A SERIES OF POINTS TO THE CHART
		// ------------------------------------------------------------------
		// Get a pointer to the chart's CXTPChartSeriesCollection object. We use
		// this to add a series to the chart, then plot points along the chart 
		// accordingly. A chart can contain any number of series, we are just 
		// adding one here to keep it simple.
		
		CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
		if (pCollection)
		{
			CXTPChartSeries* pSeries = pCollection->Add(new CXTPChartSeries());
			if (pSeries)
			{
				CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();
				if (pPoints)
				{
					pPoints->Add(new CXTPChartSeriesPoint(0, 0.5));
					pPoints->Add(new CXTPChartSeriesPoint(1, 2));
					pPoints->Add(new CXTPChartSeriesPoint(2, 1));
					pPoints->Add(new CXTPChartSeriesPoint(3, 1.5));
				}

				// ----------------------------------------------------------
				// SET THE CHART SERIES STYLE
				// ----------------------------------------------------------
				// You can call SetStyle to set the chart style such as bar, 
				// line or area chart. Here we set the style to line chart by 
				// instantiating a CXTPChartLineSeriesStyle object.

				pSeries->SetStyle(new CXTPChartLineSeriesStyle());
			}
		}
		
		// ------------------------------------------------------------------
		// SET THE CHART APPEARANCE
		// ------------------------------------------------------------------
		// Get a pointer to the chart's CXTPChartAppearance object. We use this
		// to set the colors for the chart's background, grid and text by using 
		// the LoadAppearance function. The colors are stored in an XML file 
		// that can be added to your project's resources as HTML. There are 
		// several predefined color schemes available such as CHART_APPEARANCE_NATURE (default), 
		// CHART_APPEARANCE_GRAY and CHART_APPEARANCE_DARK that are part of the chart's resources.
 
		CXTPChartAppearance* pAppearance = pContent->GetAppearance();
		if (pAppearance)
		{
			if (!pAppearance->LoadAppearance(_T("CHART_APPEARANCE_GRAY")))
			{
				TRACE0("Error loading color data.\n");
				return FALSE;
			}

			// --------------------------------------------------------------
			// SET THE CHART SERIES APPEARANCE
			// --------------------------------------------------------------
			// Similar to LoadAppearance, LoadPalette loads a set of predefined
			// colors for the chart series. Typically a set of colors is defined
			// for example red, blue and green in an external XML file. The chart
			// will use the first defined color to draw the first series for
			// example red, then the next color in the list to draw the second
			// series of points and so on. Once the end of the list is reached,
			// the chart will start from the top of the list and start over again.
			// As with LoadAppearance there are several predefined color schemes
			// available, the default is CHART_PALETTE_NATURE.

			if (!pAppearance->LoadPalette(_T("CHART_PALETTE_GRAY")))
			{
				TRACE0("Error loading color palette.\n");
				return FALSE;
			}
		}
		
		return TRUE;
	}

	return FALSE;
}

void CSimpleChartDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSimpleChartDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimpleChartDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
