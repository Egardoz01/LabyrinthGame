#pragma once


// ggg dialog

class GameMenu : public CDialogEx
{
	DECLARE_DYNAMIC(GameMenu)

public:
	GameMenu(CWnd* pParent = nullptr);   // standard constructor
	virtual ~GameMenu();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDC_GAMEMENU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
