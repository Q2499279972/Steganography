// SteganographyGuiDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "MyEdit.h"
#include "Steganography.h"
// CSteganographyGuiDlg dialog
class CSteganographyGuiDlg : public CDialog
{
// Construction
public:
	CSteganographyGuiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_STEGANOGRAPHYGUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
public:
	CMyEdit m_cedit_ori_bmp;
	CMyEdit m_cedit_ori_file;
	CMyEdit m_cedit_bmprev;
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedRevstart();

public:
	Steganography steganography;
public:
	afx_msg void OnBnClickedOk();
};
