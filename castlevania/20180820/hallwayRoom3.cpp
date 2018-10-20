#include "stdafx.h"
#include "hallwayRoom3.h"
#include "player.h"
#include "battleScene.h"
HRESULT hallwayRoom3::init()
{
	m_imgBg = IMAGEMANAGER->addImage("image/bossRoom.bmp", "image/bossRoom.bmp", 512, 160, true, RGB(0, 88, 24));
	m_imgMap= IMAGEMANAGER->addImage("image/bossRoomMa.bmp", "image/bossRoomMa.bmp", 512, 160, true, RGB(255, 0, 255));

	colliderMake();


	m_posMap = PointMake(0, 0);
	m_posBG = PointMake(0, 0);


	m_nBalore.init();


	//m_rectGate = rectGate;
	//m_rectObj = rectObj;


	return S_OK;
}

void hallwayRoom3::release()
{
	if (m_pMemDCInfo)
	{
		SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hOldBitmap);
		DeleteObject(m_pMemDCInfo->hBitmap);
		DeleteDC(m_pMemDCInfo->hMemDC);

		delete m_pMemDCInfo;
	}
}

void hallwayRoom3::update()
{



	if (m_posMap.x < 0)
	{
		m_posMap.x = 0;
		m_pPlayer->setXCameraOn(false);


	}
	else if (m_posMap.x > 512 * 3 - WINSIZEX)
	{
		m_posMap.x = 512 * 3 - WINSIZEX;
		m_pPlayer->setXCameraOn(false);
	}

	if (m_posMap.y < 0)
	{
		m_posMap.y = 0;
		m_pPlayer->setYCameraOn(false);
	}
	else if (m_posMap.y > 160 * 3 - WINSIZEY)
	{
		m_posMap.y = 160 * 3 - WINSIZEY;
		m_pPlayer->setYCameraOn(false);
	}

		if (m_posMap.x == 0 && m_pPlayer->getFx() > WINSIZEX / 2)
	{

		m_pPlayer->setXCameraOn(true);
	}

	if (m_posMap.x == 512 * 3 - WINSIZEX && m_pPlayer->getFx() < WINSIZEX / 2)
	{

		m_pPlayer->setXCameraOn(true);
	}

	m_nBalore.update();


	if (m_nBalore.m_bIsAlive == false)
	{
		m_pBattleSceen->setGameEnd(true);
	}
	//m_rectGate[0] = RectMake(-20 - m_posMap.x, 193, 30, 144);
	//m_rectGate[1] = RectMake(1525 - m_posMap.x, 193 - m_posMap.y, 30, 144);

	//rectColider();
}

void hallwayRoom3::render(HDC hdc)
{




	m_imgBg->render(hdc, 0 - m_posMap.x, 0 - m_posMap.y, 0, 0 , 512,160, 3);
	m_nBalore.headRender(hdc);
	m_imgMap->render(hdc, 0 - m_posMap.x, 0 - m_posMap.y, 0, 0, 512, 160, 3);
	m_nBalore.armRender(hdc);

	//for (int i = 0; i < 2; i++)
	//{
	//	//Rectangle(hdc, m_rectGate[i].left, m_rectGate[i].top, m_rectGate[i].right, m_rectGate[i].bottom);
	//}

}

void hallwayRoom3::rectColider()
{
	//for (int i = 0; i < 2; i++)
	//{
	//	POINT point;
	//	RECT rc;
	//	if (IntersectRect(&rc, &(m_pPlayer->getRc()), &(m_rectGate[i])))
	//	{
	//		switch (i)
	//		{
	//		case 0:


	//			m_pPlayer->setFY(300);
	//			m_pPlayer->setFx(640 - (30 * 3));
	//			m_pPlayer->PlayerRect();
	//			ROOMMANAGER->changeRoom("CastleHallwayy");


	//			point.x = 540 * 3 - WINSIZEX;
	//			point.y = 3850;

	//			ROOMMANAGER->getCurrRoom()->setPosMap(point);

	//			break;
	//		case 1:

	//			m_pPlayer->setFY(300);
	//			m_pPlayer->setFx(30 * 3);
	//			m_pPlayer->PlayerRect();
	//			ROOMMANAGER->changeRoom("BrickStaircaseroom");
	//			
	//			break;
	//		case 2:


	//			break;


	//		default:
	//			break;
	//		}
	//	}
	//}
}

void hallwayRoom3::colliderMake()
{
	HDC hdc = GetDC(g_hWnd);

	tagMemDCInfo tempInfo;

	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	tempInfo.hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	tempInfo.hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		"image/bossRoomPIX.bmp",
		IMAGE_BITMAP,
		512, 160,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	tempInfo.hOldBitmap = (HBITMAP)SelectObject(tempInfo.hMemDC, tempInfo.hBitmap);

	tempInfo.nWidth = 512;
	tempInfo.nHeight = 160;


	m_pMemDCInfo = new tagMemDCInfo;
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pMemDCInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, 512 * 3, 160 * 3);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	m_pMemDCInfo->nWidth = 512 * 3;
	m_pMemDCInfo->nHeight = 160 * 3;


	GdiTransparentBlt(
		// 목적지
		m_pMemDCInfo->hMemDC,					// 복사될 목적지 DC
		0, 0,			// 복사될 좌표 시작점
		512 * 3, 160 * 3,	// 복사될 크기

						// 대상
		tempInfo.hMemDC,	// 복사할 대상 DC
		0, 0,			// 복사될 영역 시작좌표
		512, 160,	// 복사될 영역지정 좌표

		RGB(255, 0, 255));			// 복사에서 제외할 색상

	SelectObject(tempInfo.hMemDC, tempInfo.hOldBitmap);
	DeleteObject(tempInfo.hBitmap);
	DeleteDC(tempInfo.hMemDC);
}

hallwayRoom3::hallwayRoom3()
{
}


hallwayRoom3::~hallwayRoom3()
{
}
