// StartGameForm.cpp : implementation file
//

#include "stdafx.h"
#include "LabyrinthGame.h"
#include "StartGameForm.h"
#include "afxdialogex.h"


// StartGameForm dialog

IMPLEMENT_DYNAMIC(StartGameForm, CDialogEx)

StartGameForm::StartGameForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_START_GAME, pParent),
	Level2(0)
{
	
	//CheckRadioButton(IDC_EASY, IDC_HARD, IDC_EASY);
}

StartGameForm::~StartGameForm()
{
}

void StartGameForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_EASY, Level2);
}


BEGIN_MESSAGE_MAP(StartGameForm, CDialogEx)
	ON_BN_CLICKED(IDC_START, &StartGameForm::OnBnClickedStart)
	ON_BN_CLICKED(IDC_EASY, &StartGameForm::OnBnClickedEasy)
	ON_BN_CLICKED(IDC_MEDIUM, &StartGameForm::OnBnClickedMedium)
	ON_BN_CLICKED(IDC_HARD, &StartGameForm::OnBnClickedHard)
END_MESSAGE_MAP()


// StartGameForm message handlers


void StartGameForm::OnBnClickedStart()
{
	DialogResult = true;
	EndDialog(0);
}


void StartGameForm::OnBnClickedEasy()
{
	Level2 = EASY;
}


void StartGameForm::OnBnClickedMedium()
{
	Level2 = MEDIUM;
}


void StartGameForm::OnBnClickedHard()
{
	Level2 = HARD;
}