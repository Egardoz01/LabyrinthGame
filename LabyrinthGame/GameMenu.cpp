// ggg.cpp : implementation file
//

#include "stdafx.h"
#include "LabyrinthGame.h"
#include "GameMenu.h"
#include "afxdialogex.h"


// ggg dialog

IMPLEMENT_DYNAMIC(GameMenu, CDialogEx)

GameMenu::GameMenu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDC_GAMEMENU, pParent)
{

}

GameMenu::~GameMenu()
{
}

void GameMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameMenu, CDialogEx)
END_MESSAGE_MAP()


// ggg message handlers
