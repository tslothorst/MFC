#pragma once


// CPathComboBox

class CPathComboBox : public CComboBoxEx
{

public:
	CPathComboBox();
	virtual ~CPathComboBox();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CString GetPath();
	BOOL SetPath(LPCTSTR pszPath);

protected:
	void GetSubstring(int& nStart, CString& string, CString& result);
	int m_nIndexEnd;
	int m_nIndexStart;
	BOOL m_bFirstCall;
	CImageList m_il;
};


