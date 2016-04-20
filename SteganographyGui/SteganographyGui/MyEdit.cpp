#include "stdafx.h"
#include "MyEdit.h"
// CMyEdit
IMPLEMENT_DYNAMIC(CMyEdit, CEdit)
CMyEdit::CMyEdit()
{
}
CMyEdit::~CMyEdit()
{
}

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

void CMyEdit::OnDropFiles(HDROP hDropInfo)
{
	int DropCount = DragQueryFile(hDropInfo,-1,NULL,NULL);
	if(DropCount!=1) 
	{
		::MessageBox(NULL, "please drag one file!!", "ERROR", MB_OK);
		CEdit::OnDropFiles(hDropInfo);
		return;
	}
	char pName[255] = {0};
	DragQueryFile(hDropInfo,0,pName,255);
	if(GetFileAttributes(pName)==FILE_ATTRIBUTE_DIRECTORY)
	{
		::MessageBox(NULL, "please don't drag one directory!!", "ERROR", MB_OK);
		CEdit::OnDropFiles(hDropInfo);
		return;
	}
	SetWindowText(pName);
	CEdit::OnDropFiles(hDropInfo);
}