#include "stdafx.h"
//#include "CoinObject.h"
//#include "room.h"
//#include "RoomObject.h"
//#include "CoinObject.h"
//#include "player.h"
//
//
//HRESULT CoinObject::init(int XX, int XY)
//{
//
//	m_coin = IMAGEMANAGER->addImage("1coin", "image/object/onecoin.bmp", 33, 10, 3, 1, true, RGB(0, 64, 128));
//	m_imgcoin = IMAGEMANAGER->addImage("1won", "image/object/1won.bmp", 143/1.2, 75/1.2, 1, 1, true, RGB(255, 0, 255));
//	m_soulob = IMAGEMANAGER->addImage("soul", "image/object/soulob.bmp", 80, 20, 4, 1, true, RGB(0, 64, 128));
//	//오브잭트
//	Alive = false;
//	//파괴 여부를 채크
//	m_b1won = false;
//	Destruction = false;
//	Down = false;
//	m_bstand = false;
//	m_nimgcount = 0;
//	obAlive = false;
//	//위치
//	FX = XX ;
//	FY = XY;
//	m_angle = 0;
//	//프레임 
//	FrameX = 0;
//	FrameY = 0;
//	speed = 0;
//	MyIdx = 0;
//	MYCount = 0;
//
//	m_rc = RectMakeCenter(FX , FY,
//		m_coin->getWidth() / 2, m_coin->getHeight() * 2);
//	
//	return S_OK;
//
//}
//
//void CoinObject::release()
//{
//}
//
//void CoinObject::update()
//{
//	/*if (m_b1won)
//	{
//		m_nimgcount++;
//
//
//		if (m_nimgcount == 100)
//		{
//			m_b1won = false;
//			m_nimgcount = 0;
//		}
//	}
//		if (Alive)
//		{
//			speed+=0.2;
//			FY -= 1 * speed;
//			MyIdx++;
//			MYCount++;
//			if (MyIdx % 3 == 0)
//			{
//				FrameX++;
//				
//				if (FrameX > 3)
//				{
//
//					FrameX = 0;
//				}
//
//			}
//
//			if (MYCount == 10)
//			{
//
//				Down = true;
//				Alive = false;
//			}
//
//		}
//
//
//		if (Down)
//		{
//			speed += 0.4f;
//			FY += 0.8f * speed;
//			MyIdx++;
//			if (MyIdx % 3 == 0)
//			{
//				FrameX++;
//
//				if (FrameX > 3)
//				{
//					FrameX = 0;
//				}
//
//			}
//		}
//
//
//		if (m_bstand)
//		{
//			FY = FY;
//						MyIdx++;
//			if (MyIdx % 3 == 0)
//			{
//				FrameX++;
//
//				if (FrameX > 3)
//				{
//					FrameX = 0;
//				}
//
//			}
//
//		}
//*/
//
//		if (obAlive)
//		{
//			
//			MyIdx++;
//			soulMove();
//			if (MyIdx % 3 == 0)
//			{
//				FrameX++;
//				
//				if (FrameX > 3)
//				{
//					m_angle += 2;
//					FrameX = 0;
//				}
//
//			}
//
//		}
//
//
//
//	m_rc = RectMakeCenter(FX+ 18 - ROOMMANAGER->getCurrRoom()->getPosMap().x , FY +17  - ROOMMANAGER->getCurrRoom()->getPosMap().y,
//		m_coin->getWidth() /2, m_coin->getHeight() * 2);
//
//	//for (int y = m_rc.top; y <= m_rc.bottom; y++)
//	//{
//	//	COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
//	//		FX, FY + 20);
//
//	//	int r = GetRValue(color);
//	//	int g = GetGValue(color);
//	//	int b = GetBValue(color);
//
//
//
//	//	if (y == m_rc.bottom)
//	//	{
//	//		color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
//	//			FX, FY +20 );
//
//	//		r = GetRValue(color);
//	//		g = GetGValue(color);
//	//		b = GetBValue(color);
//
//
//
//	//		if (!(r == 0 && g == 88 && b == 24))
//	//		{
//	//			Down = false;
//	//			m_bstand = true;
//	//			FY = FY - 10;
//	//		}
//	//	}
//	//}
//
//	//수정해야함
//	
//		RECT rc;
//
//		if (IntersectRect(&rc, &m_rc, &ROOMMANAGER->getPlayer()->getRc()))
//		{
//			m_bstand = false;
//           Alive = false;
//			Down = false;
//			
//			m_b1won = true;
//	
//		}
//
//
//
//
//
//}
//
//void CoinObject::render(HDC hdc)
//{
//
//
//	if (Alive || m_bstand||
//		 Down
//		)
//	{
//
//
//		Rectangle(hdc, m_rc.left, m_rc.top,
//
//			m_rc.right, m_rc.bottom);
//
//		m_coin->frameRender(hdc, FX - ROOMMANAGER->getCurrRoom()->getPosMap().x ,FY - ROOMMANAGER->getCurrRoom()->getPosMap().y
//			, FrameX, FrameY, 3);
//
//	}
//
//	if (obAlive)
//	{
//		m_soulob->frameRender(hdc, FX - ROOMMANAGER->getCurrRoom()->getPosMap().x, FY - ROOMMANAGER->getCurrRoom()->getPosMap().y
//			, FrameX, FrameY, 3);
//	}
//	if (m_b1won)
//	{
//		m_imgcoin->render(hdc, 0, 420);
//	
//	}
//
//}
//
//void CoinObject::soulMove()
//{
//	
//	FX += cosf(m_angle ) * 2;
//	FY += -sinf(m_angle ) * 2;
//}
//
//
//CoinObject::CoinObject()
//{
//}
//
//
//CoinObject::~CoinObject()
//{
//}