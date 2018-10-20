#include "stdafx.h"
#include "scoreScene.h"


HRESULT scoreScene::init()
{
	m_pBG = IMAGEMANAGER->addImage("mapImage", "image/mapImage.bmp"
		, WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	return S_OK;
}

void scoreScene::release()
{
}

void scoreScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->changeScene("title");

	}
}

void scoreScene::render(HDC hdc)
{
	char str[128];

	sprintf_s(str, 128, "score : %d",*m_pscore);

	m_pBG->render(hdc, 0, 0);


	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 0, 0));
	TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 2, str, strlen(str));
}


scoreScene::scoreScene()
{
}


scoreScene::~scoreScene()
{
}
