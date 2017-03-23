
// LazyImageDlg.h : header file
//

#pragma once


#define WM_NOTIFICATION_CALLBACK	(WM_USER + 1)


// CLazyImageDlg dialog
class CLazyImageDlg : public CDialogEx
{
// Construction
public:
	CLazyImageDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CLazyImageDlg();

	// œµÕ≥Õ–≈Ã
	NOTIFYICONDATA m_Notification;

// Dialog Data
	enum { IDD = IDD_LAZYIMAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnNotificationCallback(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnMenuItemExit();
};
