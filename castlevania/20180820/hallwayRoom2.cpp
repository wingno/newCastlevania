#include "stdafx.h"
#include "hallwayRoom2.h"
#include "player.h"
#include"RoomObject.h"

HRESULT hallwayRoom2::init()
{
	m_imgBg = IMAGEMANAGER->addImage("image/MAP1.bmp", "image/MAP1.bmp", 5784, 2012, true, RGB(0, 88, 24));
	//m_imgMap= IMAGEMANAGER->addImage("image/MAP1PIX.bmp", "image/MAP1PIX.bmp", 5784, 2012, true, RGB(255, 0, 255));

	colliderMake();


	m_posMap = PointMake(0, 0);
	m_posBG = PointMake(0, 0);



	m_rectGate = rectGate;
	m_rectObj = rectObj;


	//������Ʈ
	m_Object = new RoomObject[2];

	
	m_Object[0].init(740, 190, 0);
	m_Object[1].init(1510, 190, 0);
	
	m_pEnemyMgr->setEnemy(500, 425, RIPPER);
	m_pEnemyMgr->setEnemy(900, 425, RIPPER);
	m_pEnemyMgr->setEnemy(1300, 425, RIPPER);
	m_pEnemyMgr->setEnemy(2000, 425, RIPPER);
	m_pEnemyMgr->setEnemy(3000, 425, RIPPER);


	return S_OK;

}

void hallwayRoom2::release()
{
	if (m_pMemDCInfo)
	{
		SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hOldBitmap);
		DeleteObject(m_pMemDCInfo->hBitmap);
		DeleteDC(m_pMemDCInfo->hMemDC);

		delete m_pMemDCInfo;
	}

}

void hallwayRoom2::update()
{
	//������Ʈ
	for (int i = 0; i < 2; i++)
	{
		m_Object[i].update();

	}

	if (m_posMap.x < 0)
	{
		m_posMap.x = 0;
		m_pPlayer->setXCameraOn(false);


	}
	else if (m_posMap.x > 765 * 3 - WINSIZEX)
	{
		m_posMap.x = 765 * 3 - WINSIZEX;
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


	m_rectGate[0] = RectMake( 0 - m_posMap.x, 193, 30, 144);
	m_rectGate[1] = RectMake(2280 - m_posMap.x, 193 - m_posMap.y, 30, 144);

	rectColider();


}

void hallwayRoom2::render(HDC hdc)
{


	m_imgBg->render(hdc, 0, 0, 542, 1839, 300, 160, 3);

	m_imgBg->render(hdc, 0, 140, 542 + m_posBG.x / 3, 1725, 300, 100, 3);


	m_imgBg->render(hdc, 0, 0, 2314 + m_posMap.x / 3, 1551 + m_posMap.y / 3, 300, 160, 3);

	for (int i = 0; i < 2; i++)
	{
		//Rectangle(hdc, m_rectGate[i].left, m_rectGate[i].top, m_rectGate[i].right, m_rectGate[i].bottom);
	}
	//������Ʈ
	for (int i = 0; i < 2; i++)
	{
		m_Object[i].render(hdc);
	}

}



void hallwayRoom2::rectColider()
{
	for (int i = 0; i < 2; i++)
	{
		POINT point;
		RECT rc;
		if (IntersectRect(&rc, &(m_pPlayer->getRc()), &(m_rectGate[i])))
		{
			switch (i)
			{
			case 0:

				m_pPlayer->setFY(300);
				m_pPlayer->setFx(590 - (30 * 3));
				m_pPlayer->PlayerRect();
				ROOMMANAGER->changeRoom("FountainRoom");


				point.x = 520 * 3 - WINSIZEX;
				point.y = 0;
				m_pPlayer->PlayerRect();
				ROOMMANAGER->getCurrRoom()->setPosMap(point);
				break;
			case 1:

				m_pPlayer->setFY(300);
				m_pPlayer->setFx(20 * 3);
				m_pPlayer->PlayerRect();
				ROOMMANAGER->changeRoom("CastleHallwayy");

				point.x = 0;
				point.y = 3850;
				m_pPlayer->PlayerRect();
				ROOMMANAGER->getCurrRoom()->setPosMap(point);
				break;
			case 2:


				break;


			default:
				break;
			}
		}
	}


}
void hallwayRoom2::colliderMake()
{
	HDC hdc = GetDC(g_hWnd);

	tagMemDCInfo tempInfo;

	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	tempInfo.hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	tempInfo.hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		"image/MAP1PIX.bmp",
		IMAGE_BITMAP,
		5784, 2012,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	tempInfo.hOldBitmap = (HBITMAP)SelectObject(tempInfo.hMemDC, tempInfo.hBitmap);

	tempInfo.nWidth = 5784;
	tempInfo.nHeight = 2012;


	m_pMemDCInfo = new tagMemDCInfo;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pMemDCInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, 765 * 3, 160 * 3);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	m_pMemDCInfo->nWidth = 768 * 3;
	m_pMemDCInfo->nHeight = 160 * 3;


	GdiTransparentBlt(
		// ������
		m_pMemDCInfo->hMemDC,					// ����� ������ DC
		0, 0,			// ����� ��ǥ ������
		765 * 3, 160 * 3,	// ����� ũ��

						// ���
		tempInfo.hMemDC,	// ������ ��� DC
		2313, 1551,			// ����� ���� ������ǥ
		765, 160,	// ����� �������� ��ǥ

		RGB(255, 0, 255));			// ���翡�� ������ ����

	SelectObject(tempInfo.hMemDC, tempInfo.hOldBitmap);
	DeleteObject(tempInfo.hBitmap);
	DeleteDC(tempInfo.hMemDC);
}
void hallwayRoom2::checkCollision()
{
	RECT rc;
	for (int i = 0; i < 4; i++)
	{


		if (m_Object[i].getObjStand() && IntersectRect(&rc, &m_pPlayer->getIRC(), &m_Object[i].getrc()))
		{
			m_Object[i].setObjStand(false);

			m_Object[i].setDestruction(true);
		}

	}
}
hallwayRoom2::hallwayRoom2()
{
}


hallwayRoom2::~hallwayRoom2()
{
}
