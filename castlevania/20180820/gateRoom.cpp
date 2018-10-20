#include "stdafx.h"
#include "gateRoom.h"
#include "player.h"
#include "RoomObject.h"

HRESULT gateRoom::init()
{
	m_imgBg = IMAGEMANAGER->addImage("image/MAP1.bmp", "image/MAP1.bmp", 5784, 2012, true, RGB(0, 88, 24));
	//m_imgMap= IMAGEMANAGER->addImage("image/MAP1PIX.bmp", "image/MAP1PIX.bmp", 5784, 2012, true, RGB(255, 0, 255));

	colliderMake();

	m_posMap = PointMake(0, 0);
	m_posBG = PointMake(0, 0);



	m_rectGate = rectGate;
	m_rectObj = rectObj;

	m_Object = new RoomObject[4];
	m_nRectNum = 6;


	//������
	m_Object[0].init(334, 1137, 1);
	m_Object[1].init(334, 890, 1);
	m_Object[2].init(867, 800, 1);
	m_Object[3].init(1343, 224, 1);




	return S_OK;
}

void gateRoom::release()
{
	if (m_pMemDCInfo)
	{

		SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hOldBitmap);
		DeleteObject(m_pMemDCInfo->hBitmap);
		DeleteDC(m_pMemDCInfo->hMemDC);

		delete m_pMemDCInfo;
	}
}

void gateRoom::update()
{
	//������
	for (int i = 0; i < 4; i++)
	{
		m_Object[i].update();
	}
	if (m_posMap.x < 0)
	{
		m_posMap.x = 0;
		m_pPlayer->setXCameraOn(false);

		
	}
	else if (m_posMap.x > 510 * 3 - WINSIZEX)
	{
		m_posMap.x = 510 * 3 - WINSIZEX;
		m_pPlayer->setXCameraOn(false);
	}

	if (m_posMap.y < -10)
	{
		m_posMap.y = 0;
		m_pPlayer->setYCameraOn(false);
	}
	else if (m_posMap.y > 666 * 3 - WINSIZEY)
	{
		m_posMap.y = 666 * 3 - WINSIZEY;
		m_pPlayer->setYCameraOn(false);
	}

	if (m_posMap.x == 0 && m_pPlayer->getFx() > WINSIZEX / 2)
	{

		m_pPlayer->setXCameraOn(true);
	}

	if (m_posMap.x == 510 * 3 - WINSIZEX && m_pPlayer->getFx() < WINSIZEX / 2)
	{

		m_pPlayer->setXCameraOn(true);
	}

	if (m_posMap.y == 0 && m_pPlayer->getFY() > WINSIZEY / 2 + 75)
	{

		m_pPlayer->setYCameraOn(true);
	}

	if (m_posMap.y == 666 * 3 - WINSIZEY && m_pPlayer->getFY() < WINSIZEY / 2 + 75)
	{

		m_pPlayer->setYCameraOn(true);
	}


	//����Ʈ
	m_rectGate[0] = RectMake(1530- m_posMap.x, 1714 - m_posMap.y, 30, 150 );
	//���ӷ�Ʈ
	//������ �� ���� ��Ʈ ���������� �Ʒ��� 
	m_rectObj[0] = RectMake(1340 - m_posMap.x, 465- m_posMap.y, 100, 30);
	m_rectObj[1] = RectMake(1340 - m_posMap.x, 605 - m_posMap.y, 100, 30);
	m_rectObj[2] = RectMake(1340 - m_posMap.x, 795 - m_posMap.y, 100, 30);
	
	m_rectObj[3] = RectMake(1340 - m_posMap.x, 1470 - m_posMap.y, 100, 30);
	m_rectObj[4] = RectMake(1200 - m_posMap.x, 1665 - m_posMap.y, 240, 30);

	m_rectObj[5] = RectMake(1055 - m_posMap.x, 700 - m_posMap.y, 290, 30);


	rectColider();
}

void gateRoom::render(HDC hdc)
{
	m_imgBg->render(hdc, 0, 0, 174, 1796, 240, 160, 3);

	m_imgBg->render(hdc, 0, 0, 10+ m_posMap.x / 3, 1044 + m_posMap.y / 3, 300, 160, 3);
	
	//Rectangle(hdc, m_rectGate[0].left, m_rectGate[0].top, m_rectGate[0].right, m_rectGate[0].bottom);


	for (int i = 0; i < 6; i++)
	{
		//Rectangle(hdc, m_rectObj[i].left, m_rectObj[i].top, m_rectObj[i].right, m_rectObj[i].bottom);
	}

	for (int i = 0; i < 4; i++)
	{
		m_Object[i].render(hdc);
	}

}
void gateRoom::colliderMake()
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
	m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, 509 * 3, 666 * 3);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	m_pMemDCInfo->nWidth = 509 * 3;
	m_pMemDCInfo->nHeight = 666 * 3;


	GdiTransparentBlt(
		// ������
		m_pMemDCInfo->hMemDC,					// ����� ������ DC
		0, 0,			// ����� ��ǥ ������
		509 * 3, 666 * 3,	// ����� ũ��

						// ���
		tempInfo.hMemDC,	// ������ ��� DC
		10, 1044,			// ����� ���� ������ǥ
		509, 666,	// ����� �������� ��ǥ

		RGB(255, 0, 255));			// ���翡�� ������ ����

	SelectObject(tempInfo.hMemDC, tempInfo.hOldBitmap);
	DeleteObject(tempInfo.hBitmap);
	DeleteDC(tempInfo.hMemDC);
}

void gateRoom::rectColider()
{
	for (int i = 0; i < 1; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &(m_pPlayer->getRc()), &(m_rectGate[i])))
		{
			switch (i)
			{
			case 0:
				

				m_pPlayer->setFY(300); //�÷��̾��ǽ�����ġ
				m_pPlayer->setFx(50);
				m_pPlayer->PlayerRect();
				ROOMMANAGER->changeRoom("hallwayRoom1");

				POINT point;
				point.x = 10 * 3 - WINSIZEX; //���� ������ġ
				point.y = 0;
				ROOMMANAGER->getCurrRoom()->setPosMap(point);
				break;
			case 1:

				break;
			case 2:


				break;


			default:
				break;
			}
		}
	}




	for (int i = 0; i < 6; i++)
	{
		if (m_rectObj[i].top + 13 > m_pPlayer->getRc().bottom && m_rectObj[i].top - 7 < m_pPlayer->getRc().bottom
			&& (m_pPlayer->getRc().right > m_rectObj[i].left && m_pPlayer->getRc().left < m_rectObj[i].right))
		{

			m_pPlayer->setFY(m_rectObj[i].top - 50);


			//�ʿ��ɸ���� �������°� �ӽù��� ���߿� �����ؾ��� !!!
			if(m_rectObj[i].top - 50)
			{
				if (KEYMANAGER->isOnceKeyDown('C'))
				{
					m_pPlayer->setFY(m_rectObj[i].top-10);
				}
			}

		}
	}
}

void gateRoom::checkCollision()
{
}



gateRoom::gateRoom()
{
}


gateRoom::~gateRoom()
{
}
