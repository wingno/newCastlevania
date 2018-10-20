#include "stdafx.h"
#include "selectScene.h"
#include "spaceShip.h"


HRESULT selectScene::init()
{
	m_pBG = IMAGEMANAGER->addImage("mapselectBG", "image/titlebackground.bmp"
		, WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	m_pselect = IMAGEMANAGER->addImage("mapImageSelecter", "image/select.bmp"
		, 70, 84, true, RGB(0, 0, 255));

	m_imgRocketR= IMAGEMANAGER->addImage("spaceShipR", "image/rocket.bmp",52, 64, true, RGB(255, 0, 255));

	m_imgRocketY = IMAGEMANAGER->addImage("spaceShipY", "image/rocketY.bmp", 52, 64, true, RGB(255, 0, 255));

	selecterPos[0] = { WINSIZEX / 2 - 59,WINSIZEY / 2 - 64 };
	selecterPos[1] = {WINSIZEX / 2 + 41, WINSIZEY / 2 - 64};

	
	m_seletNum = 0;

	return S_OK;
}

void selectScene::release()
{

}

void selectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		m_seletNum = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		m_seletNum = 1;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

		SCENEMANAGER->changeScene("battle");
	}
}

void selectScene::render(HDC hdc)
{
	char str[128];

	sprintf_s(str, 128, "캐릭터를 골라주세요");

	m_pBG->render(hdc, 0, 0);

	m_imgRocketR->render(hdc, WINSIZEX / 2 - 50, WINSIZEY / 2 - 50);

	m_imgRocketY->render(hdc, WINSIZEX / 2 + 50, WINSIZEY / 2 - 50);
	
	m_pselect->render(hdc, selecterPos[m_seletNum].x, selecterPos[m_seletNum].y);


	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 0, 0));
	TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 2-150, str, strlen(str));
}


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}
