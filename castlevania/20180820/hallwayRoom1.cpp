#include "stdafx.h"
#include "hallwayRoom1.h"
#include "player.h"
#include "zombie.h"
#include "SkeletonArcher.h"
#include "RoomObject.h"
#include "enemyManager.h"

HRESULT hallwayRoom1::init()
{

	m_imgBg = IMAGEMANAGER->addImage("image/MAP1.bmp", "image/MAP1.bmp", 5784, 2012, true, RGB(0, 88, 24));
	//m_imgMap= IMAGEMANAGER->addImage("image/MAP1PIX.bmp", "image/MAP1PIX.bmp", 5784, 2012, true, RGB(255, 0, 255));

	colliderMake();

	m_posMap = PointMake(0, 0);
	m_posBG = PointMake(0, 0);

	//m_pEnemyMgr->setEnemy(500, 300, LIZARDMAN);

	m_Zombie = new zombie[10];
	m_Zombie->init(500, 350);




	for (int i = 1; i < 10; i++)
	{
		m_Zombie[i].init(700 + (i * 200), 350);
	}

	m_Object = new RoomObject[5];


	//촛불
	m_Object[0].init(742, 300, 0);
	m_Object[1].init(1513, 300, 0);
	m_Object[2].init(2279, 300, 0);
	m_Object[3].init(3045, 300, 0);
	m_Object[4].init(500, 300, 2);


	m_rectGate =rectGate;
	m_rectObj = rectObj;
	m_nRectNum = 1;

	m_rectGate[0] = RectMake(0, 195, 30, 144);
	m_rectGate[1] = RectMake(1273 * 3 -30, 195, 30, 144);

	m_rectObj[0] = RectMake(386 * 3, 88 * 3, 32 * 3, 7 * 3);





	return S_OK;
}

void hallwayRoom1::release()
{
	
	if (m_pMemDCInfo)
	{
		SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hOldBitmap);
		DeleteObject(m_pMemDCInfo->hBitmap);
		DeleteDC(m_pMemDCInfo->hMemDC);

		delete m_pMemDCInfo;
	}

	for (int i = 0; i < 10; i++)
	{
		//delete &m_Zombie[i];
	}
	

}

void hallwayRoom1::update()
{
	m_Zombie->update();
	//촛불
	for (int i = 0; i < 5; i++)
	{
		m_Object[i].update();
	}
		
	for (int i = 1; i < 10; i++)
	{
		m_Zombie[i].update();
	}

	if (m_posBG.x >= (2280))
	{
		m_posBG.x = 0;
	}
	else if(m_posBG.x<=0)
	{
		m_posBG.x = 2280;
	}

	if (m_posMap.x <0 )
	{
		m_posMap.x = 0;
		m_pPlayer->setXCameraOn(false);
	}
	else if (m_posMap.x > 3200)
	{
		m_posMap.x = 3200;
		m_pPlayer->setXCameraOn(false);
	}

	if (m_posBG.x == 0 && m_pPlayer->getFx()>WINSIZEX/2 )
	{

		m_pPlayer->setXCameraOn(true);
	}

	if (m_posBG.x == 3200 && m_pPlayer->getFx() < WINSIZEX / 2)
	{

		m_pPlayer->setXCameraOn(true);
	}

	m_posMap.y = 0;
	m_posBG.y = 0;
	m_pPlayer->setYCameraOn(false);


	m_rectGate[0] = RectMake(0 - m_posMap.x, 195, 30, 144);
	m_rectGate[1] = RectMake(1273*3 - m_posMap.x, 195, 25, 144);
	

	m_rectObj[0] = RectMake(384 * 3 - m_posMap.x, 80 * 3, 32 * 3, 7 * 3);
	

	checkCollision();
	rectColider();


}

void hallwayRoom1::render(HDC hdc)
{

	
	//배경
	m_imgBg->render(hdc, 0, 0, 542, 1839, 240, 160, 3);


	m_imgBg->render(hdc, 0, 140, 542 + m_posBG.x / 3, 1725, 240, 100,3);
	
	m_imgBg->render(hdc, 2280-m_posBG.x, 140, 542, 1725, 240, 100, 3);
	

	m_imgBg->render(hdc, 0,  0, 521+ m_posMap.x/3, 1551 + m_posMap.y / 3, 400, 160,3);

	//랙트

	for (int i = 0; i < 2; i++)
	{
		//Rectangle(hdc, m_rectGate[i].left, m_rectGate[i].top, m_rectGate[i].right, m_rectGate[i].bottom);
	}
	for (int i = 0; i < 1; i++)
	{
		//Rectangle(hdc, m_rectObj[i].left, m_rectObj[i].top, m_rectObj[i].right, m_rectObj[i].bottom);
	}
	
	m_Zombie->render(hdc);
	for (int i = 1; i < 10; i++)
	{
		m_Zombie[i].render(hdc);
	}
	for (int i = 0; i < 5; i++)
	{
		m_Object[i].render(hdc);
	}

}

void hallwayRoom1::colliderMake()
{

	//HDC hdc = GetDC(g_hWnd);

	//m_pMemDCInfo = new MEM_INFO;
	//m_pMemDCInfo->hMemDC = CreateCompatibleDC(hdc);
	//m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	//m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	//m_pMemDCInfo->nWidth = width;
	//m_pMemDCInfo->nHeight = height;

	HDC hdc = GetDC(g_hWnd);

	tagMemDCInfo tempInfo;

	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	tempInfo.hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	tempInfo.hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		"image/MAP1PIX.bmp",
		IMAGE_BITMAP,
		5784, 2012,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	tempInfo.hOldBitmap = (HBITMAP)SelectObject(tempInfo.hMemDC, tempInfo.hBitmap);

	tempInfo.nWidth = 5784;
	tempInfo.nHeight = 2012;


	m_pMemDCInfo = new tagMemDCInfo;
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pMemDCInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, 1276 * 3, 160 * 3);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	m_pMemDCInfo->nWidth = 1276 * 3;
	m_pMemDCInfo->nHeight = 160 * 3;


	GdiTransparentBlt(
		// 목적지
		m_pMemDCInfo->hMemDC,					// 복사될 목적지 DC
		0, 0,			// 복사될 좌표 시작점
		1276*3, 160*3,	// 복사될 크기

						// 대상
		tempInfo.hMemDC,	// 복사할 대상 DC
		521, 1551,			// 복사될 영역 시작좌표
		1276, 160,	// 복사될 영역지정 좌표

		RGB(255, 0, 255));			// 복사에서 제외할 색상

	SelectObject(tempInfo.hMemDC, tempInfo.hOldBitmap);
	DeleteObject(tempInfo.hBitmap);
	DeleteDC(tempInfo.hMemDC);
}

void hallwayRoom1::rectColider()
{
	for (int i = 0; i < 3; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &(m_pPlayer->getRc()), &(m_rectGate[i])))
		{
			POINT point;
			switch (i)
			{
			case 0:
				m_pPlayer->setFY(293);
				m_pPlayer->setFx(200 * 3);

				ROOMMANAGER->changeRoom("gateroom");

				
				point.x = 500 * 3 - WINSIZEX; //맵의 시작위치
				point.y = 1500;

				ROOMMANAGER->getCurrRoom()->setPosMap(point);
				break;
			case 1:

				m_pPlayer->setFY(293);
				m_pPlayer->setFx(50 * 3);
				ROOMMANAGER->changeRoom("FountainRoom");//원본
				break;
			
			default:
				break;
			}
		}

	}


}

void hallwayRoom1::checkCollision()
{
	RECT rc;

	for (int i = 0; i < 10; i++)
	{
	

		if (m_Zombie[i].getAlive() && IntersectRect(&rc, &m_pPlayer->getIRC(), &m_Zombie[i].getrc()))
		{
			m_Zombie[i].setAlive(false);
		}

	}
	for (int i = 0; i < 5; i++)
	{


		if (m_Object[i].getObjStand() && IntersectRect(&rc, &m_pPlayer->getIRC(), &m_Object[i].getrc()))
		{
			m_Object[i].setObjStand(false);
		
			m_Object[i].setDestruction(true);
		}

	}


}




hallwayRoom1::hallwayRoom1()
{
}


hallwayRoom1::~hallwayRoom1()
{
}
