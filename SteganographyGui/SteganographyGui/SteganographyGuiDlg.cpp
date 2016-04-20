// SteganographyGuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteganographyGui.h"
#include "SteganographyGuiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSteganographyGuiDlg dialog




CSteganographyGuiDlg::CSteganographyGuiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSteganographyGuiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSteganographyGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ORIGINAL_BMP, m_cedit_ori_bmp);
	DDX_Control(pDX, IDC_ORIGINAL_FILE, m_cedit_ori_file);
	DDX_Control(pDX, IDC_ORIGINAL_BMPREV, m_cedit_bmprev);
}

BEGIN_MESSAGE_MAP(CSteganographyGuiDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_START, &CSteganographyGuiDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_REVSTART, &CSteganographyGuiDlg::OnBnClickedRevstart)
	ON_BN_CLICKED(IDOK, &CSteganographyGuiDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSteganographyGuiDlg message handlers

BOOL CSteganographyGuiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CString s="Drag file here.";
	m_cedit_ori_bmp.SetWindowTextA(s);
	m_cedit_ori_file.SetWindowTextA(s);
	m_cedit_bmprev.SetWindowTextA(s);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSteganographyGuiDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSteganographyGuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSteganographyGuiDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialog::OnDropFiles(hDropInfo);
}

void CSteganographyGuiDlg::OnBnClickedStart()
{
	char oribmpfile[255]={0};
	char orifile[255]={0};
	this->m_cedit_ori_bmp.GetWindowTextA(oribmpfile,250);
	this->m_cedit_ori_file.GetWindowTextA(orifile,250);
	if(steganography.SteganographyTo(orifile,oribmpfile,"test.bmp"))
	{
		this->MessageBox("OK","OK",MB_OK);
	}
	else
	{
		this->MessageBox("FAIL","FAIL",MB_OK);
	}
}

void CSteganographyGuiDlg::OnBnClickedRevstart()
{
	char bmpfile[255]={0};
	m_cedit_bmprev.GetWindowTextA(bmpfile,250);
	if(steganography.SteganographyFrom(bmpfile,"out.test"))
	{
		this->MessageBox("OK","OK",MB_OK);
	}
	else
	{
		this->MessageBox("FAIL","FAIL",MB_OK);
	}
}

void CSteganographyGuiDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
