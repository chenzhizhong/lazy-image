
// LazyImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LazyImage.h"
#include "LazyImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLazyImageDlg dialog

CLazyImageDlg::CLazyImageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLazyImageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CLazyImageDlg::~CLazyImageDlg()
{
	Shell_NotifyIcon(NIM_DELETE, &m_Notification);
}

void CLazyImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLazyImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_NOTIFICATION_CALLBACK, &CLazyImageDlg::OnNotificationCallback)
	ON_COMMAND(ID_MENU_ITEM_EXIT, &CLazyImageDlg::OnMenuItemExit)
END_MESSAGE_MAP()


// CLazyImageDlg message handlers

BOOL CLazyImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// 显示系统托盘
	m_Notification.cbSize = sizeof(NOTIFYICONDATA);
	m_Notification.hWnd = m_hWnd;
	m_Notification.uID = IDR_MAINFRAME;
	m_Notification.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
	m_Notification.uCallbackMessage = WM_NOTIFICATION_CALLBACK;
	m_Notification.hIcon = m_hIcon;
	LoadString(GetModuleHandle(NULL), IDS_LAZYIMAGE, m_Notification.szTip, sizeof(m_Notification.szTip) / sizeof(WCHAR)); 
	::Shell_NotifyIcon(NIM_ADD, &m_Notification);

	// 从任务栏中去掉
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	// 隐藏窗口
	WINDOWPLACEMENT wp;
	wp.length=sizeof(WINDOWPLACEMENT);
	wp.flags = WPF_RESTORETOMAXIMIZED;
	wp.showCmd = SW_HIDE;
	SetWindowPlacement(&wp);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLazyImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLazyImageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLazyImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CLazyImageDlg::OnNotificationCallback(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
	{
		return 1;
	}

	if (lParam == WM_RBUTTONDOWN)
	{
		CMenu menu;
		menu.LoadMenu(IDR_MENU_RCLICK_NOTIFICATION);

		CMenu *pMenu = menu.GetSubMenu(0);
        CPoint pt;
        GetCursorPos(&pt);
		SetForegroundWindow();
        pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	return 0;
}

void CLazyImageDlg::OnMenuItemExit()
{
	// TODO: Add your command handler code here

	// 关闭对话框
	OnCancel();
}
