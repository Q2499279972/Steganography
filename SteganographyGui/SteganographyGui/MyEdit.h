#ifndef _MYEDIT_H_
#define _MYEDIT_H_
class CMyEdit : public CEdit
{
 DECLARE_DYNAMIC(CMyEdit)
public:
 CMyEdit();
 virtual ~CMyEdit();
protected:
 DECLARE_MESSAGE_MAP()
public:
 afx_msg void OnDropFiles(HDROP hDropInfo);
};

#endif

