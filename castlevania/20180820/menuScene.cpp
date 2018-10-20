#include "stdafx.h"
#include "menuScene.h"
#include "player.h"
#include "menuProgressBar.h"
#include "bulletSoul.h"
#include "enchantSoul.h"
#include "guardianSoul.h"
#include "accessoryItem.h"
#include "handItem.h"
#include "bodyItem.h"
#include "ItemUse.h"
#include "animation.h"



HRESULT menuScene::init()
{
	m_imgMenu = IMAGEMANAGER->addImage("image/menu.bmp", "image/menu.bmp", WINSIZEX, WINSIZEY, false, 0);

	m_imgSoulSet = IMAGEMANAGER->addImage("image/soul.bmp", "image/soul.bmp", WINSIZEX, WINSIZEY, false, 0);

	m_imgEquit= IMAGEMANAGER->addImage("image/arms.bmp", "image/arms.bmp", WINSIZEX, WINSIZEY, false, 0);

	m_imgUseItem = IMAGEMANAGER->addImage("image/itemUse.bmp", "image/itemUse.bmp", WINSIZEX, WINSIZEY, false, 0);

	m_imgSeleter = IMAGEMANAGER->addImage("image/seleter.bmp", "image/seleter.bmp", 16, 16, true, RGB(255,0,255));

	m_imgLArrow = IMAGEMANAGER->addImage("image/leftArrow.bmp", "image/leftArrow.bmp", 17, 21, true, RGB(255, 0, 255));
	
	m_imgRArrow = IMAGEMANAGER->addImage("image/rightArrow.bmp", "image/rightArrow.bmp", 17, 21, true, RGB(255, 0, 255));

	m_imgEmptySoul= IMAGEMANAGER->addImage("image/4303.bmp", "image/4303.bmp", 222, 439, true, RGB(84, 109, 142));



	m_pPlayer = g_mainGame.getPlayer();

	m_pHpBar = new menuProgressBar;

	m_pMpBar = new menuProgressBar;

	m_pHpBar->init(WINSIZEX / 2 + 100, 50, 190, 24, true);

	m_pMpBar->init(WINSIZEX / 2 + 100, 80, 190, 24, false);

	m_pHpBar->setGauge(m_pPlayer->getState().curHP, m_pPlayer->getState().fullHP);
	m_pMpBar->setGauge(m_pPlayer->getState().curMP, m_pPlayer->getState().fullMP);

	m_seleter = {0,0,true,2.5f};

	m_state = MENU;

	m_bIsChangeScene = false;

	m_nAlphaNum = 0;

	m_nSetStep = 0;

	m_nTypeSelcet = 0;

	m_nFinalSelectNum = 0;

	m_nShowStartNum = 0;

	m_nShowEndChacker = 0;


	m_ChangeStatus = m_pPlayer->getState();

	m_imgBSoul = IMAGEMANAGER->addImage("image/bSoul.bmp", "image/bSoul.bmp", 144, 18, 18, 18, true, RGB(84, 109, 142));
	m_imgGSoul = IMAGEMANAGER->addImage("image/gSoul.bmp", "image/gSoul.bmp", 144, 18, 18, 18, true, RGB(84, 109, 142));
	m_imgESoul = IMAGEMANAGER->addImage("image/eSoul.bmp", "image/eSoul.bmp", 144, 18, 18, 18, true, RGB(84, 109, 142));



	m_pBSoulAni = new animation;
	m_pBSoulAni->init(m_imgBSoul->getWidth(), m_imgBSoul->getHeight(),18,18);
	m_pBSoulAni->setPlayFrame(0, 7,false,true);
	m_pBSoulAni->setFPS(10);

	m_pGSoulAni = new animation;
	m_pGSoulAni->init(m_imgGSoul->getWidth(), m_imgGSoul->getHeight(), 18, 18);
	m_pGSoulAni->setPlayFrame(0, 7, false, true);
	m_pGSoulAni->setFPS(10);

	m_pESoulAni = new animation;
	m_pESoulAni->init(m_imgESoul->getWidth(), m_imgESoul->getHeight(), 18, 18);
	m_pESoulAni->setPlayFrame(0, 7, false, true);
	m_pESoulAni->setFPS(10);

	clearInven();

	return S_OK;
}

void menuScene::release()
{

	SAFE_DELETE(m_pHpBar);
	SAFE_DELETE(m_pMpBar);
	SAFE_DELETE(m_pBSoulAni);
	SAFE_DELETE(m_pGSoulAni);
	SAFE_DELETE(m_pESoulAni);
}

void menuScene::update()
{
	switch (m_state)
	{
	case MENU:
		menuUpdate();
		break;
	case SOUL_SET:
		sourSetupdate();
		break;
	case EQUIT:
		equitupdate();
		break;
	case ITEM:
		useItemupdate();
		break;

	default:
		break;
	}

	if (m_state != MENU)
	{
		if (KEYMANAGER->isOnceKeyDown('X')&& m_nSetStep==0)
		{
			m_state = MENU;
			m_nTypeSelcet = 0;
		}

		
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			m_bIsChangeScene = true;
		}
	}



	if (m_bIsChangeScene)
	{
		
		
		if (m_nAlphaNum < 255)
		{
			
			m_nAlphaNum+=50;
		}
		else
		{
			m_pPlayer->setIsJump(false);
			SCENEMANAGER->changeScene("battle");
		}

	}
}

void menuScene::render(HDC hdc)
{
	AddFontResourceA("font/Slabberton.ttf");

	HFONT hFont= CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);


	switch (m_state)
	{
	case MENU:
		menuRander(hdc);
		break;
	case SOUL_SET:
		sourSetRander(hdc);
		break;
	case EQUIT:
		equitRander(hdc);
		break;
	case ITEM:
		useItemRander(hdc);
		break;

	default:
		break;
	}

	if (m_seleter.SelectMover <= 0)
	{
		m_seleter.isLeft = true;
	}
	else if (m_seleter.SelectMover >= 30)
	{
		m_seleter.isLeft = false;
	}

	if (m_seleter.isLeft)
		m_seleter.SelectMover += m_seleter.speed;
	else
		m_seleter.SelectMover -= m_seleter.speed;

	

	if (m_bIsChangeScene)
	{
		IMAGEMANAGER->findImage("background")->alphaRender(hdc, m_nAlphaNum);

	}

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void menuScene::menuRander(HDC hdc)
{


	char str[300];

	m_imgMenu->render(hdc, 0, 0);



	// 1. 폰트 추가하기. 



	SetTextColor(hdc, RGB(243, 122, 40));
	sprintf_s(str, "HP   ");
	TextOut(hdc, WINSIZEX / 2 - 120, 50, str, lstrlen(str));

	sprintf_s(str, "ATT   %d", m_pPlayer->getState().curAtt);
	TextOut(hdc, WINSIZEX / 2 + 80, 120, str, lstrlen(str));

	SetTextColor(hdc, RGB(126, 117, 255));

	sprintf_s(str, "MP   ");
	TextOut(hdc, WINSIZEX / 2 - 120, 80, str, lstrlen(str));

	sprintf_s(str, "DEF   %d", m_pPlayer->getState().curDef);
	TextOut(hdc, WINSIZEX / 2 + 80, 150, str, lstrlen(str));




	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf_s(str, " %d", m_pPlayer->getState().curHP);
	TextOut(hdc, WINSIZEX / 2 - 60, 50, str, lstrlen(str));

	sprintf_s(str, "/  %d", m_pPlayer->getState().fullHP);
	TextOut(hdc, WINSIZEX / 2 + 15, 50, str, lstrlen(str));

	sprintf_s(str, " %d", m_pPlayer->getState().curMP);
	TextOut(hdc, WINSIZEX / 2 - 60, 80, str, lstrlen(str));

	sprintf_s(str, "/  %d", m_pPlayer->getState().fullMP);
	TextOut(hdc, WINSIZEX / 2 + 15, 80, str, lstrlen(str));




	sprintf_s(str, "STR   %d", m_pPlayer->getState().curStr);
	TextOut(hdc, WINSIZEX / 2 - 120, 120, str, lstrlen(str));

	sprintf_s(str, "CON   %d", m_pPlayer->getState().curCon);
	TextOut(hdc, WINSIZEX / 2 - 120, 150, str, lstrlen(str));

	sprintf_s(str, "INT   %d", m_pPlayer->getState().curCon);
	TextOut(hdc, WINSIZEX / 2 - 120, 180, str, lstrlen(str));

	sprintf_s(str, "LCK   %d", m_pPlayer->getState().curLck);
	TextOut(hdc, WINSIZEX / 2 - 120, 210, str, lstrlen(str));


	//경험치
	sprintf_s(str, "EXP           %d", m_pPlayer->getState().exp);
	TextOut(hdc, WINSIZEX / 2 - 40, 290, str, lstrlen(str));

	sprintf_s(str, "NEXT         %d", m_pPlayer->getState().nextExp- m_pPlayer->getState().exp);
	TextOut(hdc, WINSIZEX / 2 - 40, 310, str, lstrlen(str));

	//돈
	SetTextColor(hdc, RGB(243, 206, 91));
	sprintf_s(str, "GOLD : %d   ",m_pPlayer->getGold());
	TextOut(hdc, WINSIZEX / 2+50, 210, str, lstrlen(str));


	//메뉴바
	SetTextColor(hdc, RGB(158, 159, 153));

	sprintf_s(str, "SOUL SET");
	TextOut(hdc, 40, 290, str, lstrlen(str));

	sprintf_s(str, "EQUIP");
	TextOut(hdc, 40, 330, str, lstrlen(str));

	sprintf_s(str, "ITEM USE");
	TextOut(hdc, 40, 370, str, lstrlen(str));

	sprintf_s(str, "EXIT");
	TextOut(hdc, 40, 410, str, lstrlen(str));




	SetTextColor(hdc, RGB(255, 255, 255));
	switch (m_seleter.Select)
	{
		case 0:
			sprintf_s(str, "SOUL SET");
			TextOut(hdc, 40, 290, str, lstrlen(str));
			break;
		case 1:
			sprintf_s(str, "EQUIP");
			TextOut(hdc, 40, 330, str, lstrlen(str));
			break;
		case 2:
			sprintf_s(str, "ITEM USE");
			TextOut(hdc, 40, 370, str, lstrlen(str));
			break;
		case 3:
			sprintf_s(str, "EXIT");
			TextOut(hdc, 40, 410, str, lstrlen(str));
			break;
		default:
			break;
	}


	m_imgSeleter->render(hdc, -5- m_seleter.SelectMover, 270 + (40*m_seleter.Select), 3);


	m_pHpBar->render(hdc);
	m_pMpBar->render(hdc);



}

void menuScene::menuUpdate()
{
	m_nFinalSelectNum = 0;
	m_nShowStartNum = 0;
	m_nShowEndChacker = 0;

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (m_seleter.Select > 0)
		{
			m_seleter.Select--;

		}
		else
		{
			m_seleter.Select = 3;
		}

	}
	else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{

		if (m_seleter.Select < 3)
		{
			m_seleter.Select++;

		}
		else
		{
			m_seleter.Select = 0;
		}
		
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		switch (m_seleter.Select)
		{
		case 0:
			m_state = SOUL_SET;
			break;
		case 1:
			m_state = EQUIT;
			break;
		case 2:

			m_state = ITEM;
			m_seleter.Select=0;
			break;
		case 3:
			m_bIsChangeScene = true;
			break;
		default:
			break;
		}
	}



}

void menuScene::sourSetRander(HDC hdc)
{



	m_imgSoulSet->render(hdc, 0, 0);

	m_imgSeleter->render(hdc, m_nSetStep==0? - m_seleter.SelectMover:0, 80 + (40 * m_nTypeSelcet), 3);

	//m_imgSeleter->render(hdc, 0 , 80 + (40 * m_TypeSelet), 3);
	if (m_nSetStep == 0)
	{
		m_imgLArrow->render(hdc, 20 - m_seleter.SelectMover/3, 60);
		m_imgRArrow->render(hdc, 325 + m_seleter.SelectMover/3, 60);

	}

	if (m_nSetStep == 1)
		m_imgSeleter->render(hdc, -m_seleter.SelectMover/3 +
		(m_nFinalSelectNum % 2 == 0 ? 10:330), WINSIZEY / 2-20 +(20* (m_nFinalSelectNum/2)), 3);

	if (m_pPlayer->m_soulSet.bS->m_nIdx!=0)
	{
		m_imgBSoul->aniRender(hdc, 40, 80,m_pBSoulAni,3);
		//m_imgBSoul->aniRender(hdc, m_fX - m_img->getWidth() / 2, m_fY - m_img->getHeight() / 2, m_pAni_1);
	}
	else
	{
		m_imgEmptySoul->render(hdc, 50, 90, 116, 40, 13, 13, 3);
	}

	if (m_pPlayer->m_soulSet.gS->m_nIdx != 0)
	{
		m_imgGSoul->aniRender(hdc, 40, 120, m_pGSoulAni, 3);
	}
	else
	{
		m_imgEmptySoul->render(hdc, 50, 130, 116, 4, 13, 13, 3);
	}

	if (m_pPlayer->m_soulSet.eS-> m_nIdx != 0)
	{
		m_imgESoul->aniRender(hdc, 40, 160, m_pESoulAni, 3);
	}
	else
	{
		m_imgEmptySoul->render(hdc, 50, 170, 116, 76, 13, 13, 3);
	}

	fontPrint(hdc);


}

void menuScene::sourSetupdate()
{
	m_pBSoulAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pGSoulAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	m_pESoulAni->frameUpdate(TIMEMANAGER->getElapsedTime());

	switch (m_nTypeSelcet)
	{
	case 0:
		if(!m_pBSoulAni->getIsPlaying())
			m_pBSoulAni->start();
		m_pGSoulAni->stop();
		m_pESoulAni->stop();
		break;
	case 1:
		m_pBSoulAni->stop();
		if (!m_pGSoulAni->getIsPlaying())
			m_pGSoulAni->start();
		m_pESoulAni->stop();
		break;
	case 2:
		m_pBSoulAni->stop();
		m_pGSoulAni->stop();
		if (!m_pESoulAni->getIsPlaying())
			m_pESoulAni->start();
		break;
	default:
		break;
	}




	switch (m_nSetStep)
	{
	case 0:

		if (m_nSetStep == 0 && (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT)))
		{
			m_state = EQUIT;
			m_seleter.Select = 1;
			m_nTypeSelcet = 0;

			m_nFinalSelectNum = 0;
			m_nShowStartNum = 0;
			m_nShowEndChacker = 0;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (m_nTypeSelcet > 0)
			{
				m_nTypeSelcet--;

			}
			else
			{
				m_nTypeSelcet = 2;
			}
			m_nFinalSelectNum = 0;
			m_nShowStartNum = 0;
			m_nShowEndChacker = 0;

		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{

			if (m_nTypeSelcet < 2)
			{
				m_nTypeSelcet++;

			}
			else
			{
				m_nTypeSelcet = 0;
			}
			m_nFinalSelectNum = 0;
			m_nShowStartNum = 0;
			m_nShowEndChacker = 0;
		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			m_nSetStep++;
		}
		break;
	case 1:

		switch (m_nTypeSelcet)
		{
		case 0:
			bsUpDate();
			break;
		case 1:
			gsUpDate();
			break;
		case 2:
			esUpDate();
			break;

		default:
			break;
		}


		break;
	default:
		break;
	}



}

void menuScene::equitRander(HDC hdc)
{
	m_imgEquit->render(hdc, 0, 0);

	m_imgSeleter->render(hdc, m_nSetStep == 0 ? -m_seleter.SelectMover : 0, 80 + (40 * m_nTypeSelcet), 3);


	if (m_nSetStep == 0)
	{
		m_imgLArrow->render(hdc, 20 - m_seleter.SelectMover / 3, 60);
		m_imgRArrow->render(hdc, 325 + m_seleter.SelectMover / 3, 60);

		switch (m_nTypeSelcet)
		{
		case 0:
			if (m_pPlayer->m_ItemSet.hI->m_nIdx != 0)
			{

				m_pPlayer->m_ItemSet.hI->getImgIcon()->frameRender(hdc, 60, 365, m_pPlayer->m_ItemSet.hI->m_nIdx - 1, 0, 3);
			}


			break;
		case 1:
			if (m_pPlayer->m_ItemSet.bI->m_nIdx != 0)
			{

				m_pPlayer->m_ItemSet.bI->getImgIcon()->frameRender(hdc, 60, 365, m_pPlayer->m_ItemSet.bI->m_nIdx + 2, 0, 3);
			}
			break;
		case 2:
			if (m_pPlayer->m_ItemSet.aI->m_nIdx != 0)
			{

				m_pPlayer->m_ItemSet.aI->getImgIcon()->frameRender(hdc, 60, 365, m_pPlayer->m_ItemSet.aI->m_nIdx + 7, 0, 3);
			}
			break;

		default:
			break;
		}

	}

	if (m_nSetStep == 1)
	{
		m_imgSeleter->render(hdc, -m_seleter.SelectMover / 3 +
			(m_nFinalSelectNum % 2 == 0 ? 10 : 330), WINSIZEY / 2 - 20 + (20 * (m_nFinalSelectNum / 2)), 3);

		switch (m_nTypeSelcet)
		{
		case 0:
			if (m_pPlayer->m_ItemInven.vecHandItem[m_nShowStartNum + m_nFinalSelectNum]->m_nIdx != 0)
			{

				m_pPlayer->m_ItemInven.vecHandItem[m_nShowStartNum + m_nFinalSelectNum]->getImgIcon()->frameRender(hdc, 60, 365, m_pPlayer->m_ItemInven.vecHandItem[m_nShowStartNum + m_nFinalSelectNum]->m_nIdx - 1, 0, 3);

				
			}
			break;
		case 1:
			if (m_pPlayer->m_ItemInven.vecBodyItem[m_nShowStartNum + m_nFinalSelectNum]->m_nIdx != 0)
			{

				m_pPlayer->m_ItemInven.vecBodyItem[m_nShowStartNum + m_nFinalSelectNum]->getImgIcon()->frameRender(hdc, 60, 365, m_pPlayer->m_ItemInven.vecBodyItem[m_nShowStartNum + m_nFinalSelectNum]->m_nIdx + 2, 0, 3);
			}
			break;
		case 2:
			if (m_pPlayer->m_ItemInven.vecAccessoryItem[m_nShowStartNum + m_nFinalSelectNum]->m_nIdx != 0)
			{

				m_pPlayer->m_ItemInven.vecAccessoryItem[m_nShowStartNum + m_nFinalSelectNum]->getImgIcon()->frameRender(hdc, 60, 365, m_pPlayer->m_ItemInven.vecAccessoryItem[m_nShowStartNum + m_nFinalSelectNum]->m_nIdx + 7, 0, 3);
			}
			break;

		default:
			break;
		}

	}


	if (m_pPlayer->m_ItemSet.hI->m_nIdx != 0)
	{

		m_pPlayer->m_ItemSet.hI->getImgIcon()->frameRender(hdc, 60, 90, m_pPlayer->m_ItemSet.hI->m_nIdx - 1, 0, 2);
	}

	if (m_pPlayer->m_ItemSet.bI->m_nIdx != 0)
	{

		m_pPlayer->m_ItemSet.bI->getImgIcon()->frameRender(hdc, 60, 130, m_pPlayer->m_ItemSet.bI->m_nIdx +2, 0, 2);
	}

	if (m_pPlayer->m_ItemSet.aI->m_nIdx != 0)
	{

		m_pPlayer->m_ItemSet.aI->getImgIcon()->frameRender(hdc, 60, 170, m_pPlayer->m_ItemSet.aI->m_nIdx +7, 0, 2);
	}



	fontPrint(hdc);









}

void menuScene::equitupdate()
{




	if (m_nSetStep == 0 && (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT)))
	{
		m_state = SOUL_SET;
		m_seleter.Select = 0;
		m_nTypeSelcet = 0;

		m_nFinalSelectNum = 0;
		m_nShowStartNum = 0;
		m_nShowEndChacker = 0;
	}

	switch (m_nSetStep)
	{
	case 0:
		if (m_nSetStep == 0 && (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT)))
		{
			m_state = EQUIT;
			m_seleter.Select = 1;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (m_nTypeSelcet > 0)
			{
				m_nTypeSelcet--;

			}
			else
			{
				m_nTypeSelcet = 2;
			}
			m_nFinalSelectNum = 0;
			m_nShowStartNum = 0;
			m_nShowEndChacker = 0;

		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{

			if (m_nTypeSelcet < 2)
			{
				m_nTypeSelcet++;

			}
			else
			{
				m_nTypeSelcet = 0;
			}
			m_nFinalSelectNum = 0;
			m_nShowStartNum = 0;
			m_nShowEndChacker = 0;

		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			m_nSetStep++;
		}
		break;
	case 1:
		switch (m_nTypeSelcet)
		{
		case 0:
			hiUpDate();
			break;
		case 1:
			biUpDate();
			break;
		case 2:
			aiUpDate();
			break;

		default:
			break;
		}

		break;
	default:
		break;
	}
}

void menuScene::useItemRander(HDC hdc)
{
	m_imgUseItem->render(hdc, 0, 0);

	m_imgSeleter->render(hdc, 30 -m_seleter.SelectMover  +(m_seleter.Select%2)*300, 245 + (m_seleter.Select / 2) * 25, 3);

	m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select]->getImgIcon()->frameRender(hdc, 60, 390,
		m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select]->m_nIdx+13 , 0, 3);


	m_pHpBar->render(hdc,330,110);
	m_pMpBar->render(hdc,330,140);
	


	useItemFontPrint(hdc);



}

void menuScene::useItemupdate()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		m_state = MENU;

		m_seleter.Select = 2;

	}

	if (m_pPlayer->m_ItemInven.vecItemUse.size() <= 0)
	{
		return;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (m_seleter.Select % 2 == 0)
		{
			if (m_seleter.Select < m_pPlayer->m_ItemInven.vecItemUse.size())
				m_seleter.Select++;

			if (m_nShowStartNum + m_seleter.Select >= m_pPlayer->m_ItemInven.vecItemUse.size())
			{

				m_seleter.Select--;

			}


		}
		else
		{
			m_seleter.Select--;

		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (m_seleter.Select % 2 == 1)
		{
			m_seleter.Select--;
		}
		else
		{
			if (m_seleter.Select == 0)
				m_seleter.Select = 0;
			m_seleter.Select++;

			if (m_nShowStartNum + m_seleter.Select >= m_pPlayer->m_ItemInven.vecItemUse.size())
			{

				m_seleter.Select--;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (m_seleter.Select >= 2)
		{
			m_seleter.Select -= 2;
		}
		else
		{
			if (m_nShowStartNum >= 2)
			{
				m_nShowStartNum -= 2;
				if (m_nShowStartNum < 0)
				{
					m_nShowStartNum = 0;
				}
				m_nShowEndChacker = 0;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (m_seleter.Select + 2 < 8)
		{
			m_seleter.Select += 2;
			if (m_seleter.Select + m_nShowStartNum + 2 > m_pPlayer->m_ItemInven.vecItemUse.size() && m_pPlayer->m_ItemInven.vecItemUse.size() >= 8)
				m_seleter.Select = 6;
		}
		else
		{
			if (m_nShowStartNum + 8 < m_pPlayer->m_ItemInven.vecItemUse.size())
				m_nShowStartNum += 2;

			if (m_nShowStartNum + 8 > m_pPlayer->m_ItemInven.vecItemUse.size() && m_pPlayer->m_ItemInven.vecItemUse.size() >= 8)
			{
				m_nShowEndChacker = 1;

				m_seleter.Select = 6;

			}

		}

		if (m_pPlayer->m_ItemInven.vecItemUse.size() > 2)
		{

			if (m_seleter.Select >= m_pPlayer->m_ItemInven.vecItemUse.size())
			{
				if (m_pPlayer->m_ItemInven.vecHandItem.size() % 2 == 0)
				{
					if (m_seleter.Select % 2 == 0)
					{
						m_seleter.Select = m_pPlayer->m_ItemInven.vecItemUse.size() - 2;
					}
					else
					{
						m_seleter.Select = m_pPlayer->m_ItemInven.vecItemUse.size() - 1;
					}
				}
				else
				{
					if (m_seleter.Select % 2 == 1)
					{
						m_seleter.Select = m_pPlayer->m_ItemInven.vecItemUse.size() - 2;
					}
					else
					{
						m_seleter.Select = m_pPlayer->m_ItemInven.vecItemUse.size() - 1;
					}
				}


			}
		}
		else
		{
			m_seleter.Select -= 2;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nIdx < 3 ||
			m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nIdx == 6)
		{

			if (m_pPlayer->getPState()->curHP >= m_pPlayer->getPState()->fullHP&&m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nIdx < 3)
				return;

			m_pPlayer->getPState()->curHP += m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nChangeHP;
			if (m_pPlayer->getPState()->curHP > m_pPlayer->getPState()->fullHP)
			{
				m_pPlayer->getPState()->curHP = m_pPlayer->getPState()->fullHP;
			}

			if (m_pPlayer->getPState()->curHP <= 0)
				m_pPlayer->getPState()->curHP = 1;

			
			m_pHpBar->setGauge(m_pPlayer->getPState()->curHP, m_pPlayer->getPState()->fullHP);

			m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nCount--;
		}


		if (m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nIdx >=3 &&
			m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nIdx < 6)
		{

			if (m_pPlayer->getPState()->curMP >= m_pPlayer->getPState()->fullMP)
				return;

			m_pPlayer->getPState()->curMP += m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nChangeMP;
			if (m_pPlayer->getPState()->curMP > m_pPlayer->getPState()->fullMP)
			{
				m_pPlayer->getPState()->curMP = m_pPlayer->getPState()->fullMP;
			}



			m_pMpBar->setGauge(m_pPlayer->getPState()->curMP, m_pPlayer->getPState()->fullMP);

			m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nCount--;
		}





		if (m_pPlayer->m_ItemInven.vecItemUse[m_seleter.Select + m_nShowStartNum]->m_nCount >= 0)
		{
			clearInven();

			if (m_pPlayer->m_ItemInven.vecItemUse.size() <= m_seleter.Select)
			{
				m_seleter.Select = m_pPlayer->m_ItemInven.vecItemUse.size() - 1;
			}

		}

		if (m_seleter.Select < 0)
		{
			m_seleter.Select = 0;
		}
		 
	}


}

void menuScene::bsUpDate()
{

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (m_nFinalSelectNum % 2 == 0)
		{
			if (m_nFinalSelectNum < m_pPlayer->m_soulInven.vecBulletSoul.size())
				m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_soulInven.vecBulletSoul.size())
			{

				m_nFinalSelectNum--;

			}


		}
		else
		{
			m_nFinalSelectNum--;

		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (m_nFinalSelectNum % 2 == 1)
		{
			m_nFinalSelectNum--;
		}
		else
		{
			if (m_nFinalSelectNum == 0)
				m_nFinalSelectNum = 0;
			m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_soulInven.vecBulletSoul.size())
			{

				m_nFinalSelectNum--;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (m_nFinalSelectNum >= 2)
		{
			m_nFinalSelectNum -= 2;
		}
		else
		{
			if (m_nShowStartNum >= 2)
			{
				m_nShowStartNum -= 2;
				if (m_nShowStartNum < 0)
				{
					m_nShowStartNum = 0;
				}
				m_nShowEndChacker = 0;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (m_nFinalSelectNum + 2 < 8)
		{
			m_nFinalSelectNum += 2;
			if (m_nFinalSelectNum + m_nShowStartNum + 2 > m_pPlayer->m_soulInven.vecBulletSoul.size() && m_pPlayer->m_soulInven.vecBulletSoul.size() >= 8)
				m_nFinalSelectNum = 6;
		}
		else
		{
			if (m_nShowStartNum + 8 < m_pPlayer->m_soulInven.vecBulletSoul.size())
				m_nShowStartNum += 2;

			if (m_nShowStartNum + 8 > m_pPlayer->m_soulInven.vecBulletSoul.size() && m_pPlayer->m_soulInven.vecBulletSoul.size() >= 8)
			{
				m_nShowEndChacker = 1;

				m_nFinalSelectNum = 6;

			}

		}

		if (m_pPlayer->m_soulInven.vecBulletSoul.size() > 2)
		{



			if (m_nFinalSelectNum >= m_pPlayer->m_soulInven.vecBulletSoul.size())
			{
				if (m_pPlayer->m_soulInven.vecBulletSoul.size() % 2 == 0)
				{
					if (m_nFinalSelectNum % 2 == 0)
					{
						m_nFinalSelectNum = m_pPlayer->m_soulInven.vecBulletSoul.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_soulInven.vecBulletSoul.size() - 1;
					}
				}
				else
				{
					if (m_nFinalSelectNum % 2 == 1)
					{
						m_nFinalSelectNum = m_pPlayer->m_soulInven.vecBulletSoul.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_soulInven.vecBulletSoul.size() - 1;
					}
				}


			}
		}
		else
		{
			m_nFinalSelectNum -= 2;
		}



	}
	SoulSet tempSoulSet = { m_pPlayer->m_soulInven.vecBulletSoul[m_nFinalSelectNum + m_nShowStartNum] ,
							m_pPlayer->m_soulSet.gS,m_pPlayer->m_soulSet.eS};

	m_ChangeStatus=changeStatus(m_ChangeStatus, tempSoulSet,m_pPlayer->m_ItemSet);

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		m_pPlayer->m_soulSet.bS = m_pPlayer->m_soulInven.vecBulletSoul[m_nFinalSelectNum + m_nShowStartNum];
		m_pPlayer->setState(changeStatus(m_pPlayer->getState(), m_pPlayer->m_soulSet, m_pPlayer->m_ItemSet));
		m_nSetStep--;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		m_nSetStep--;
	}

}

void menuScene::gsUpDate()
{

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (m_nFinalSelectNum % 2 == 0)
		{
			if (m_nFinalSelectNum < m_pPlayer->m_soulInven.vecGuardianSoul.size())
				m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_soulInven.vecGuardianSoul.size())
			{

				m_nFinalSelectNum--;

			}


		}
		else
		{
			m_nFinalSelectNum--;

		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (m_nFinalSelectNum % 2 == 1)
		{
			m_nFinalSelectNum--;
		}
		else
		{
			if (m_nFinalSelectNum == 0)
				m_nFinalSelectNum = 0;
			m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_soulInven.vecGuardianSoul.size())
			{

				m_nFinalSelectNum--;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (m_nFinalSelectNum >= 2)
		{
			m_nFinalSelectNum -= 2;
		}
		else
		{
			if (m_nShowStartNum >= 2)
			{
				m_nShowStartNum -= 2;
				if (m_nShowStartNum < 0)
				{
					m_nShowStartNum = 0;
				}
				m_nShowEndChacker = 0;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (m_nFinalSelectNum + 2 < 8)
		{
			m_nFinalSelectNum += 2;
			if (m_nFinalSelectNum + m_nShowStartNum + 2 > m_pPlayer->m_soulInven.vecGuardianSoul.size() && m_pPlayer->m_soulInven.vecGuardianSoul.size() >= 8)
				m_nFinalSelectNum = 6;
		}
		else
		{
			if (m_nShowStartNum + 8 < m_pPlayer->m_soulInven.vecGuardianSoul.size())
				m_nShowStartNum += 2;

			if (m_nShowStartNum + 8 > m_pPlayer->m_soulInven.vecGuardianSoul.size() && m_pPlayer->m_soulInven.vecGuardianSoul.size() >= 8)
			{
				m_nShowEndChacker = 1;

				m_nFinalSelectNum = 6;

			}

		}

		if (m_pPlayer->m_soulInven.vecGuardianSoul.size() > 2)
		{
			if (m_nFinalSelectNum >= m_pPlayer->m_soulInven.vecGuardianSoul.size())
			{
				if (m_pPlayer->m_soulInven.vecGuardianSoul.size() % 2 == 0)
				{
					if (m_nFinalSelectNum % 2 == 0)
					{
						m_nFinalSelectNum = m_pPlayer->m_soulInven.vecGuardianSoul.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_soulInven.vecGuardianSoul.size() - 1;
					}
				}
				else
				{
					if (m_nFinalSelectNum % 2 == 1)
					{
						m_nFinalSelectNum = m_pPlayer->m_soulInven.vecGuardianSoul.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_soulInven.vecGuardianSoul.size() - 1;
					}
				}


			}
		}
		else
		{
			m_nFinalSelectNum -= 2;
		}



	}
	SoulSet tempSoulSet = { m_pPlayer->m_soulSet.bS ,
							m_pPlayer->m_soulInven.vecGuardianSoul[m_nFinalSelectNum + m_nShowStartNum],m_pPlayer->m_soulSet.eS };

	m_ChangeStatus = changeStatus(m_ChangeStatus, tempSoulSet, m_pPlayer->m_ItemSet);


	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		m_pPlayer->m_soulSet.gS = m_pPlayer->m_soulInven.vecGuardianSoul[m_nFinalSelectNum + m_nShowStartNum];
		m_pPlayer->setState(changeStatus(m_pPlayer->getState(), m_pPlayer->m_soulSet, m_pPlayer->m_ItemSet));
		m_nSetStep--;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		m_nSetStep--;
	}
}

void menuScene::esUpDate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (m_nFinalSelectNum % 2 == 0)
		{
			if (m_nFinalSelectNum < m_pPlayer->m_soulInven.vecEnchantSoul.size())
				m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_soulInven.vecEnchantSoul.size())
			{

				m_nFinalSelectNum--;

			}


		}
		else
		{
			m_nFinalSelectNum--;

		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (m_nFinalSelectNum % 2 == 1)
		{
			m_nFinalSelectNum--;
		}
		else
		{
			if (m_nFinalSelectNum == 0)
				m_nFinalSelectNum = 0;
			m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_soulInven.vecEnchantSoul.size())
			{

				m_nFinalSelectNum--;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (m_nFinalSelectNum >= 2)
		{
			m_nFinalSelectNum -= 2;
		}
		else
		{
			if (m_nShowStartNum >= 2)
			{
				m_nShowStartNum -= 2;
				if (m_nShowStartNum < 0)
				{
					m_nShowStartNum = 0;
				}
				m_nShowEndChacker = 0;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (m_nFinalSelectNum + 2 < 8)
		{
			m_nFinalSelectNum += 2;
			if (m_nFinalSelectNum + m_nShowStartNum + 2 > m_pPlayer->m_soulInven.vecEnchantSoul.size() && m_pPlayer->m_soulInven.vecEnchantSoul.size() >= 8)
				m_nFinalSelectNum = 6;
		}
		else
		{
			if (m_nShowStartNum + 8 < m_pPlayer->m_soulInven.vecEnchantSoul.size())
				m_nShowStartNum += 2;

			if (m_nShowStartNum + 8 > m_pPlayer->m_soulInven.vecEnchantSoul.size()&& m_pPlayer->m_soulInven.vecEnchantSoul.size()>=8)
			{
				m_nShowEndChacker = 1;

				m_nFinalSelectNum = 6;

			}

		}

		if (m_pPlayer->m_soulInven.vecEnchantSoul.size() > 2)
		{
			if (m_nFinalSelectNum == m_pPlayer->m_soulInven.vecEnchantSoul.size())
			{
				if (m_nFinalSelectNum % 2 == 0)
				{
					m_nFinalSelectNum = m_pPlayer->m_soulInven.vecEnchantSoul.size() - 2;
				}
				else
				{
					m_nFinalSelectNum = m_pPlayer->m_soulInven.vecEnchantSoul.size() - 1;
				}
			}


			if (m_nFinalSelectNum > m_pPlayer->m_soulInven.vecEnchantSoul.size())
			{
				if (m_nFinalSelectNum % 2 == 1)
				{
					m_nFinalSelectNum = m_pPlayer->m_soulInven.vecEnchantSoul.size() - 2;
				}
				else
				{
					m_nFinalSelectNum = m_pPlayer->m_soulInven.vecEnchantSoul.size() - 1;
				}
			}
		}
		else
		{
			m_nFinalSelectNum -= 2;
		}



	}
	SoulSet tempSoulSet = { m_pPlayer->m_soulSet.bS ,m_pPlayer->m_soulSet.gS,
		 m_pPlayer->m_soulInven.vecEnchantSoul[m_nFinalSelectNum + m_nShowStartNum] };

	m_ChangeStatus = changeStatus(m_ChangeStatus, tempSoulSet, m_pPlayer->m_ItemSet);

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		m_pPlayer->m_soulSet.eS = m_pPlayer->m_soulInven.vecEnchantSoul[m_nFinalSelectNum + m_nShowStartNum];
		m_pPlayer->setState(changeStatus(m_pPlayer->getState(), m_pPlayer->m_soulSet, m_pPlayer->m_ItemSet));
		m_nSetStep--;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		m_nSetStep--;
	}
}


void menuScene::hiUpDate()
{

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (m_nFinalSelectNum % 2 == 0)
		{
			if (m_nFinalSelectNum < m_pPlayer->m_ItemInven.vecHandItem.size())
				m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_ItemInven.vecHandItem.size())
			{

				m_nFinalSelectNum--;

			}


		}
		else
		{
			m_nFinalSelectNum--;

		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (m_nFinalSelectNum % 2 == 1)
		{
			m_nFinalSelectNum--;
		}
		else
		{
			if (m_nFinalSelectNum == 0)
				m_nFinalSelectNum = 0;
			m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_ItemInven.vecHandItem.size())
			{

				m_nFinalSelectNum--;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (m_nFinalSelectNum >= 2)
		{
			m_nFinalSelectNum -= 2;
		}
		else
		{
			if (m_nShowStartNum >= 2)
			{
				m_nShowStartNum -= 2;
				if (m_nShowStartNum < 0)
				{
					m_nShowStartNum = 0;
				}
				m_nShowEndChacker = 0;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (m_nFinalSelectNum + 2 < 8)
		{
			m_nFinalSelectNum += 2;
			if (m_nFinalSelectNum + m_nShowStartNum + 2 > m_pPlayer->m_ItemInven.vecHandItem.size() && m_pPlayer->m_ItemInven.vecHandItem.size() >= 8)
				m_nFinalSelectNum = 6;
		}
		else
		{
			if (m_nShowStartNum + 8 < m_pPlayer->m_ItemInven.vecHandItem.size())
				m_nShowStartNum += 2;

			if (m_nShowStartNum + 8 > m_pPlayer->m_ItemInven.vecHandItem.size() && m_pPlayer->m_ItemInven.vecHandItem.size() >= 8)
			{
				m_nShowEndChacker = 1;

				m_nFinalSelectNum = 6;

			}

		}

		if (m_pPlayer->m_ItemInven.vecHandItem.size() > 2)
		{

			if (m_nFinalSelectNum >= m_pPlayer->m_ItemInven.vecHandItem.size())
			{
				if (m_pPlayer->m_ItemInven.vecHandItem.size() % 2 == 0)
				{
					if (m_nFinalSelectNum % 2 == 0)
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecHandItem.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecHandItem.size() - 1;
					}
				}
				else
				{
					if (m_nFinalSelectNum % 2 == 1)
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecHandItem.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecHandItem.size() - 1;
					}
				}


			}
		}
		else
		{
			m_nFinalSelectNum -= 2;
		}



	}

	ItemSet tempItemSet = { m_pPlayer->m_ItemInven.vecHandItem[m_nFinalSelectNum + m_nShowStartNum] ,
							m_pPlayer->m_ItemSet.bI,m_pPlayer->m_ItemSet.aI };

	m_ChangeStatus = changeStatus(m_ChangeStatus, m_pPlayer->m_soulSet, tempItemSet);

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		m_pPlayer->m_ItemSet.hI = m_pPlayer->m_ItemInven.vecHandItem[m_nFinalSelectNum + m_nShowStartNum];
		m_pPlayer->setState(changeStatus(m_pPlayer->getState(), m_pPlayer->m_soulSet, tempItemSet));
		m_nSetStep--;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		m_nSetStep--;
	}

}

void menuScene::biUpDate()
{

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (m_nFinalSelectNum % 2 == 0)
		{
			if (m_nFinalSelectNum < m_pPlayer->m_ItemInven.vecBodyItem.size())
				m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_ItemInven.vecBodyItem.size())
			{

				m_nFinalSelectNum--;

			}


		}
		else
		{
			m_nFinalSelectNum--;

		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (m_nFinalSelectNum % 2 == 1)
		{
			m_nFinalSelectNum--;
		}
		else
		{
			if (m_nFinalSelectNum == 0)
				m_nFinalSelectNum = 0;
			m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_ItemInven.vecBodyItem.size())
			{

				m_nFinalSelectNum--;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (m_nFinalSelectNum >= 2)
		{
			m_nFinalSelectNum -= 2;
		}
		else
		{
			if (m_nShowStartNum >= 2)
			{
				m_nShowStartNum -= 2;
				if (m_nShowStartNum < 0)
				{
					m_nShowStartNum = 0;
				}
				m_nShowEndChacker = 0;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (m_nFinalSelectNum + 2 < 8)
		{
			m_nFinalSelectNum += 2;
			if (m_nFinalSelectNum + m_nShowStartNum + 2 > m_pPlayer->m_ItemInven.vecBodyItem.size() && m_pPlayer->m_ItemInven.vecBodyItem.size() >= 8)
				m_nFinalSelectNum = 6;
		}
		else
		{
			if (m_nShowStartNum + 8 < m_pPlayer->m_ItemInven.vecBodyItem.size())
				m_nShowStartNum += 2;

			if (m_nShowStartNum + 8 > m_pPlayer->m_ItemInven.vecBodyItem.size() && m_pPlayer->m_ItemInven.vecBodyItem.size() >= 8)
			{
				m_nShowEndChacker = 1;

				m_nFinalSelectNum = 6;

			}

		}

		if (m_pPlayer->m_ItemInven.vecBodyItem.size() > 2)
		{

			if (m_nFinalSelectNum >= m_pPlayer->m_ItemInven.vecBodyItem.size())
			{
				if (m_pPlayer->m_ItemInven.vecBodyItem.size() % 2 == 0)
				{
					if (m_nFinalSelectNum % 2 == 0)
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecBodyItem.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecBodyItem.size() - 1;
					}
				}
				else
				{
					if (m_nFinalSelectNum % 2 == 1)
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecBodyItem.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecBodyItem.size() - 1;
					}
				}


			}
		}
		else
		{
			m_nFinalSelectNum -= 2;
		}



	}

	ItemSet tempItemSet = { m_pPlayer->m_ItemSet.hI ,
							m_pPlayer->m_ItemInven.vecBodyItem[m_nFinalSelectNum + m_nShowStartNum],m_pPlayer->m_ItemSet.aI };

	m_ChangeStatus = changeStatus(m_ChangeStatus, m_pPlayer->m_soulSet, tempItemSet);

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		m_pPlayer->m_ItemSet.bI = m_pPlayer->m_ItemInven.vecBodyItem[m_nFinalSelectNum + m_nShowStartNum];
		m_pPlayer->setState(changeStatus(m_pPlayer->getState(), m_pPlayer->m_soulSet, tempItemSet));
		m_nSetStep--;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		m_nSetStep--;
	}

}


void menuScene::aiUpDate()
{

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (m_nFinalSelectNum % 2 == 0)
		{
			if (m_nFinalSelectNum < m_pPlayer->m_ItemInven.vecAccessoryItem.size())
				m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_ItemInven.vecAccessoryItem.size())
			{

				m_nFinalSelectNum--;

			}


		}
		else
		{
			m_nFinalSelectNum--;

		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (m_nFinalSelectNum % 2 == 1)
		{
			m_nFinalSelectNum--;
		}
		else
		{
			if (m_nFinalSelectNum == 0)
				m_nFinalSelectNum = 0;
			m_nFinalSelectNum++;

			if (m_nShowStartNum + m_nFinalSelectNum >= m_pPlayer->m_ItemInven.vecAccessoryItem.size())
			{

				m_nFinalSelectNum--;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (m_nFinalSelectNum >= 2)
		{
			m_nFinalSelectNum -= 2;
		}
		else
		{
			if (m_nShowStartNum >= 2)
			{
				m_nShowStartNum -= 2;
				if (m_nShowStartNum < 0)
				{
					m_nShowStartNum = 0;
				}
				m_nShowEndChacker = 0;

			}
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (m_nFinalSelectNum + 2 < 8)
		{
			m_nFinalSelectNum += 2;
			if (m_nFinalSelectNum + m_nShowStartNum + 2 > m_pPlayer->m_ItemInven.vecAccessoryItem.size() && m_pPlayer->m_ItemInven.vecAccessoryItem.size() >= 8)
				m_nFinalSelectNum = 6;
		}
		else
		{
			if (m_nShowStartNum + 8 < m_pPlayer->m_ItemInven.vecAccessoryItem.size())
				m_nShowStartNum += 2;

			if (m_nShowStartNum + 8 > m_pPlayer->m_ItemInven.vecAccessoryItem.size() && m_pPlayer->m_ItemInven.vecAccessoryItem.size() >= 8)
			{
				m_nShowEndChacker = 1;

				m_nFinalSelectNum = 6;

			}

		}

		if (m_pPlayer->m_ItemInven.vecAccessoryItem.size() > 2)
		{

			if (m_nFinalSelectNum >= m_pPlayer->m_ItemInven.vecAccessoryItem.size())
			{
				if (m_pPlayer->m_ItemInven.vecAccessoryItem.size() % 2 == 0)
				{
					if (m_nFinalSelectNum % 2 == 0)
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecAccessoryItem.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecAccessoryItem.size() - 1;
					}
				}
				else
				{
					if (m_nFinalSelectNum % 2 == 1)
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecAccessoryItem.size() - 2;
					}
					else
					{
						m_nFinalSelectNum = m_pPlayer->m_ItemInven.vecAccessoryItem.size() - 1;
					}
				}


			}
		}
		else
		{
			m_nFinalSelectNum -= 2;
		}



	}

	ItemSet tempItemSet = { m_pPlayer->m_ItemSet.hI ,m_pPlayer->m_ItemSet.bI,
							m_pPlayer->m_ItemInven.vecAccessoryItem[m_nFinalSelectNum + m_nShowStartNum] };

	m_ChangeStatus = changeStatus(m_ChangeStatus, m_pPlayer->m_soulSet, tempItemSet);

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		m_pPlayer->m_ItemSet.aI = m_pPlayer->m_ItemInven.vecAccessoryItem[m_nFinalSelectNum + m_nShowStartNum];
		m_pPlayer->setState(changeStatus(m_pPlayer->getState(), m_pPlayer->m_soulSet, tempItemSet));
		m_nSetStep--;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		m_nSetStep--;
	}

}



void menuScene::fontPrint(HDC hdc)
{


	char str[300];
	

	SetTextColor(hdc, RGB(243, 122, 40));


	sprintf_s(str, "ATT    %d", m_pPlayer->getState().curAtt);
	TextOut(hdc, WINSIZEX / 2 + 60, 80, str, lstrlen(str));

	if (m_nSetStep == 1)
	{
		if (m_pPlayer->getState().curAtt < m_ChangeStatus.curAtt)
		{
			SetTextColor(hdc, RGB(0, 216, 248));
			sprintf_s(str, "↗   %d", m_ChangeStatus.curAtt);
			TextOut(hdc, WINSIZEX / 2 + 200, 80, str, lstrlen(str));
		}
		else if (m_pPlayer->getState().curAtt == m_ChangeStatus.curAtt)
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			sprintf_s(str, "→   %d", m_ChangeStatus.curAtt);
			TextOut(hdc, WINSIZEX / 2 + 200, 80, str, lstrlen(str));
		}
		else
		{
			SetTextColor(hdc, RGB(230, 37, 74));
			sprintf_s(str, "↘   %d", m_ChangeStatus.curAtt);
			TextOut(hdc, WINSIZEX / 2 + 200, 80, str, lstrlen(str));
		}


	}

	SetTextColor(hdc, RGB(126, 117, 255));

	sprintf_s(str, "DEF    %d", m_pPlayer->getState().curDef);
	TextOut(hdc, WINSIZEX / 2 + 60, 100, str, lstrlen(str));

	if (m_nSetStep == 1)
	{

		if (m_pPlayer->getState().curDef < m_ChangeStatus.curDef)
		{
			SetTextColor(hdc, RGB(0, 216, 248));
			sprintf_s(str, "↗   %d", m_ChangeStatus.curDef);
			TextOut(hdc, WINSIZEX / 2 + 200, 100, str, lstrlen(str));
		}
		else if (m_pPlayer->getState().curDef == m_ChangeStatus.curDef)
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			sprintf_s(str, "→   %d", m_ChangeStatus.curDef);
			TextOut(hdc, WINSIZEX / 2 + 200, 100, str, lstrlen(str));
		}
		else
		{
			SetTextColor(hdc, RGB(230, 37, 74));
			sprintf_s(str, "↘   %d", m_ChangeStatus.curDef);
			TextOut(hdc, WINSIZEX / 2 + 200, 100, str, lstrlen(str));
		}

	}



	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf_s(str, "STR    %d", m_pPlayer->getState().curStr);
	TextOut(hdc, WINSIZEX / 2 + 60, 120, str, lstrlen(str));

	sprintf_s(str, "CON    %d", m_pPlayer->getState().curCon);
	TextOut(hdc, WINSIZEX / 2 + 60, 140, str, lstrlen(str));

	sprintf_s(str, "INT    %d", m_pPlayer->getState().curInt);
	TextOut(hdc, WINSIZEX / 2 + 60, 160, str, lstrlen(str));

	sprintf_s(str, "LCK    %d", m_pPlayer->getState().curLck);
	TextOut(hdc, WINSIZEX / 2 + 60, 180, str, lstrlen(str));


	if (m_nSetStep == 1)
	{
		if (m_pPlayer->getState().curStr < m_ChangeStatus.curStr)
		{
			SetTextColor(hdc, RGB(0, 216, 248));
			sprintf_s(str, "↗   %d", m_ChangeStatus.curStr);
			TextOut(hdc, WINSIZEX / 2 + 200, 120, str, lstrlen(str));
		}
		else if (m_pPlayer->getState().curStr == m_ChangeStatus.curStr)
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			sprintf_s(str, "→   %d", m_ChangeStatus.curStr);
			TextOut(hdc, WINSIZEX / 2 + 200, 120, str, lstrlen(str));
		}
		else
		{
			SetTextColor(hdc, RGB(230, 37, 74));
			sprintf_s(str, "↘   %d", m_ChangeStatus.curStr);
			TextOut(hdc, WINSIZEX / 2 + 200, 120, str, lstrlen(str));
		}

		if (m_pPlayer->getState().curCon < m_ChangeStatus.curCon)
		{
			SetTextColor(hdc, RGB(0, 216, 248));
			sprintf_s(str, "↗   %d", m_ChangeStatus.curCon);
			TextOut(hdc, WINSIZEX / 2 + 200, 140, str, lstrlen(str));
		}
		else if (m_pPlayer->getState().curCon == m_ChangeStatus.curCon)
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			sprintf_s(str, "→   %d", m_ChangeStatus.curCon);
			TextOut(hdc, WINSIZEX / 2 + 200, 140, str, lstrlen(str));
		}
		else
		{
			SetTextColor(hdc, RGB(230, 37, 74));
			sprintf_s(str, "↘   %d", m_ChangeStatus.curCon);
			TextOut(hdc, WINSIZEX / 2 + 200, 140, str, lstrlen(str));
		}

		if (m_pPlayer->getState().curInt < m_ChangeStatus.curInt)
		{
			SetTextColor(hdc, RGB(0, 216, 248));
			sprintf_s(str, "↗   %d", m_ChangeStatus.curInt);
			TextOut(hdc, WINSIZEX / 2 + 200, 160, str, lstrlen(str));
		}
		else if (m_pPlayer->getState().curInt == m_ChangeStatus.curInt)
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			sprintf_s(str, "→   %d", m_ChangeStatus.curInt);
			TextOut(hdc, WINSIZEX / 2 + 200, 160, str, lstrlen(str));
		}
		else
		{
			SetTextColor(hdc, RGB(230, 37, 74));
			sprintf_s(str, "↘   %d", m_ChangeStatus.curInt);
			TextOut(hdc, WINSIZEX / 2 + 200, 160, str, lstrlen(str));
		}

		if (m_pPlayer->getState().curLck < m_ChangeStatus.curLck)
		{
			SetTextColor(hdc, RGB(0, 216, 248));
			sprintf_s(str, "↗   %d", m_ChangeStatus.curLck);
			TextOut(hdc, WINSIZEX / 2 + 200, 180, str, lstrlen(str));
		}
		else if (m_pPlayer->getState().curLck == m_ChangeStatus.curLck)
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			sprintf_s(str, "→   %d", m_ChangeStatus.curLck);
			TextOut(hdc, WINSIZEX / 2 + 200, 180, str, lstrlen(str));
		}
		else
		{
			SetTextColor(hdc, RGB(230, 37, 74));
			sprintf_s(str, "↘   %d", m_ChangeStatus.curLck);
			TextOut(hdc, WINSIZEX / 2 + 200, 180, str, lstrlen(str));
		}


	}




	if (m_state == EQUIT)
	{
		//메뉴바
		SetTextColor(hdc, RGB(158, 159, 153));

		sprintf_s(str, "%s", m_pPlayer->m_ItemSet.hI->m_sName.c_str());
		TextOut(hdc, 120, 95, str, lstrlen(str));

		sprintf_s(str, "%s", m_pPlayer->m_ItemSet.bI->m_sName.c_str());
		TextOut(hdc, 120, 135, str, lstrlen(str));

		sprintf_s(str, "%s", m_pPlayer->m_ItemSet.aI->m_sName.c_str());
		TextOut(hdc, 120, 175, str, lstrlen(str));


		HFONT hFont;
		HFONT oldFont;

		SetTextColor(hdc, RGB(255, 255, 255));

		switch (m_nTypeSelcet)
		{
		case 0:
			sprintf_s(str, "%s", m_pPlayer->m_ItemSet.hI->m_sName.c_str());
			TextOut(hdc, 120, 95, str, lstrlen(str));

			if (m_nSetStep < 1)
			{
				sprintf_s(str, "%s", m_pPlayer->m_ItemSet.hI->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));
			}
			else
			{
				sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecHandItem[m_nShowStartNum + m_nFinalSelectNum]->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));
			}

			sprintf_s(str, "HAND");
			TextOut(hdc, WINSIZEX / 2 -180,WINSIZEY/2-33, str, lstrlen(str));

			hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
			oldFont = (HFONT)SelectObject(hdc, hFont);
		
			for (int i = m_nShowStartNum;
				i < (m_pPlayer->m_ItemInven.vecHandItem.size() < 9
					? m_pPlayer->m_ItemInven.vecHandItem.size() : 8 + m_nShowStartNum - m_nShowEndChacker); i++)

			{


				if (i % 2 == 0)
				{
					sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecHandItem[i]->m_sName.c_str());
					TextOut(hdc, 60, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}
				else
				{
					sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecHandItem[i]->m_sName.c_str());
					TextOut(hdc, 380, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}

			}
			SelectObject(hdc, oldFont);
			DeleteObject(hFont);

			break;
		case 1:

			sprintf_s(str, "%s", m_pPlayer->m_ItemSet.bI->m_sName.c_str());
			TextOut(hdc, 120, 135, str, lstrlen(str));

			if (m_nSetStep < 1)
			{
				sprintf_s(str, "%s", m_pPlayer->m_ItemSet.bI->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));
			}
			else
			{
				sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecBodyItem[m_nShowStartNum + m_nFinalSelectNum]->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));
			}
			sprintf_s(str, "BODY");
			TextOut(hdc, WINSIZEX / 2 - 180, WINSIZEY / 2 - 33, str, lstrlen(str));

			hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
			oldFont = (HFONT)SelectObject(hdc, hFont);
			for (int i = m_nShowStartNum;
				i < (m_pPlayer->m_ItemInven.vecBodyItem.size() < 9
					? m_pPlayer->m_ItemInven.vecBodyItem.size() : 8 + m_nShowStartNum - m_nShowEndChacker); i++)
			{
				if (i % 2 == 0)
				{
					sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecBodyItem[i]->m_sName.c_str());
					TextOut(hdc, 60, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}
				else
				{
					sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecBodyItem[i]->m_sName.c_str());
					TextOut(hdc, 380, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}

			}
			SelectObject(hdc, oldFont);
			DeleteObject(hFont);

			break;
		case 2:
			sprintf_s(str, "%s", m_pPlayer->m_ItemSet.aI->m_sName.c_str());
			TextOut(hdc, 120, 175, str, lstrlen(str));

			if (m_nSetStep < 1)
			{
				sprintf_s(str, "%s", m_pPlayer->m_ItemSet.aI->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));
			}
			else
			{
				sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecAccessoryItem[m_nShowStartNum + m_nFinalSelectNum]->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));
			}

			sprintf_s(str, "ACCESSORY");
			TextOut(hdc, WINSIZEX / 2 - 210, WINSIZEY / 2 - 33, str, lstrlen(str));


			hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
			oldFont = (HFONT)SelectObject(hdc, hFont);
			for (int i = m_nShowStartNum;
				i < (m_pPlayer->m_ItemInven.vecAccessoryItem.size() < 9
					? m_pPlayer->m_ItemInven.vecAccessoryItem.size() : 8 + m_nShowStartNum - m_nShowEndChacker); i++)
			{
				if (i % 2 == 0)
				{
					sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecAccessoryItem[i]->m_sName.c_str());
					TextOut(hdc, 60, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}
				else
				{
					sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecAccessoryItem[i]->m_sName.c_str());
					TextOut(hdc, 380, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}

			}
			SelectObject(hdc, oldFont);
			DeleteObject(hFont);

			break;
		default:
			break;
		}
	}
	else if (m_state == SOUL_SET)
	{
		//메뉴바
		SetTextColor(hdc, RGB(158, 159, 153));

		sprintf_s(str, "%s", m_pPlayer->m_soulSet.bS->m_sName.c_str());
		TextOut(hdc, 120, 95, str, lstrlen(str));

		sprintf_s(str, "%s", m_pPlayer->m_soulSet.gS->m_sName.c_str());
		TextOut(hdc, 120, 135, str, lstrlen(str));

		sprintf_s(str, "%s", m_pPlayer->m_soulSet.eS->m_sName.c_str());
		TextOut(hdc, 120, 175, str, lstrlen(str));



		HFONT hFont;
		HFONT oldFont;


		SetTextColor(hdc, RGB(255, 255, 255));

		switch (m_nTypeSelcet)
		{
		case 0:
			sprintf_s(str, "%s", m_pPlayer->m_soulSet.bS->m_sName.c_str());
			TextOut(hdc, 120, 95, str, lstrlen(str));

			if (m_nSetStep < 1)
			{
				sprintf_s(str, "%s", m_pPlayer->m_soulSet.bS->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));


				if (m_pPlayer->m_soulSet.bS->m_nIdx != 0)
				{
					hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
					oldFont = (HFONT)SelectObject(hdc, hFont);

					sprintf_s(str, "%d / use", m_pPlayer->m_soulSet.bS->m_nUseMp);
					TextOut(hdc, 520, 410 , str, lstrlen(str));

					SelectObject(hdc, oldFont);
					DeleteObject(hFont);


				}
			}
			else
			{
				sprintf_s(str, "%s", m_pPlayer->m_soulInven.vecBulletSoul[m_nShowStartNum+ m_nFinalSelectNum]->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));

				if (m_pPlayer->m_soulInven.vecBulletSoul[m_nShowStartNum + m_nFinalSelectNum]->m_nIdx != 0)
				{
					hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
					oldFont = (HFONT)SelectObject(hdc, hFont);

					sprintf_s(str, "%d / use", m_pPlayer->m_soulInven.vecBulletSoul[m_nShowStartNum + m_nFinalSelectNum]->m_nUseMp);
					TextOut(hdc, 520, 410, str, lstrlen(str));

					SelectObject(hdc, oldFont);
					DeleteObject(hFont);


				}
			}

			sprintf_s(str, "BULLET");
			TextOut(hdc, WINSIZEX / 2 - 190, WINSIZEY / 2 - 33, str, lstrlen(str));

			hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
			oldFont = (HFONT)SelectObject(hdc, hFont);
			for (int i = m_nShowStartNum;
				i <( m_pPlayer->m_soulInven.vecBulletSoul.size() < 9
				? m_pPlayer->m_soulInven.vecBulletSoul.size() : 8+ m_nShowStartNum- m_nShowEndChacker); i++)
			
			{

				if (i % 2==0)
				{
					sprintf_s(str, "%s", m_pPlayer->m_soulInven.vecBulletSoul[i]->m_sName.c_str());
					TextOut(hdc, 60, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}
				else
				{
					sprintf_s(str, "%s", m_pPlayer->m_soulInven.vecBulletSoul[i]->m_sName.c_str());
					TextOut(hdc, 380, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}

			}
			SelectObject(hdc, oldFont);
			DeleteObject(hFont);




			break;
		case 1:

			sprintf_s(str, "%s", m_pPlayer->m_soulSet.gS->m_sName.c_str());
			TextOut(hdc, 120, 135, str, lstrlen(str));

			if (m_nSetStep < 1)
			{
				sprintf_s(str, "%s", m_pPlayer->m_soulSet.gS->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));

				if (m_pPlayer->m_soulSet.gS->m_nIdx != 0)
				{
					hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
					oldFont = (HFONT)SelectObject(hdc, hFont);

					sprintf_s(str, "%d / time", m_pPlayer->m_soulSet.gS->m_nUseMp);
					TextOut(hdc, 520, 410, str, lstrlen(str));

					SelectObject(hdc, oldFont);
					DeleteObject(hFont);


				}
			}
			else
			{
				sprintf_s(str, "%s", m_pPlayer->m_soulInven.vecGuardianSoul[m_nShowStartNum + m_nFinalSelectNum]->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));

				if (m_pPlayer->m_soulInven.vecGuardianSoul[m_nShowStartNum + m_nFinalSelectNum]->m_nIdx != 0)
				{
					hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
					oldFont = (HFONT)SelectObject(hdc, hFont);

					sprintf_s(str, "%d / time", m_pPlayer->m_soulInven.vecGuardianSoul[m_nShowStartNum + m_nFinalSelectNum]->m_nUseMp);
					TextOut(hdc, 520, 410, str, lstrlen(str));

					SelectObject(hdc, oldFont);
					DeleteObject(hFont);


				}
			}

			sprintf_s(str, "GUARDIAN");
			TextOut(hdc, WINSIZEX / 2 - 210, WINSIZEY / 2 - 33, str, lstrlen(str));
			hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
			oldFont = (HFONT)SelectObject(hdc, hFont);
			for (int i = m_nShowStartNum;
				i < (m_pPlayer->m_soulInven.vecGuardianSoul.size() < 9
				? m_pPlayer->m_soulInven.vecGuardianSoul.size() : 8+ m_nShowStartNum- m_nShowEndChacker); i++)
			{
				if (i % 2 == 0)
				{
					sprintf_s(str, "%s", m_pPlayer->m_soulInven.vecGuardianSoul[i]->m_sName.c_str());
					TextOut(hdc, 60, 240 + (((i- m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}
				else
				{
					sprintf_s(str, "%s", m_pPlayer->m_soulInven.vecGuardianSoul[i]->m_sName.c_str());
					TextOut(hdc, 380, 240 + (((i-m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}

			}
			SelectObject(hdc, oldFont);
			DeleteObject(hFont);
			break;
		case 2:

			sprintf_s(str, "%s", m_pPlayer->m_soulSet.eS->m_sName.c_str());
			TextOut(hdc, 120, 175, str, lstrlen(str));

			if (m_nSetStep < 1)
			{
				sprintf_s(str, "%s", m_pPlayer->m_soulSet.eS->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));
			}
			else
			{
				sprintf_s(str, "%s", m_pPlayer->m_soulInven.vecEnchantSoul[m_nShowStartNum + m_nFinalSelectNum]->m_sExplanation.c_str());
				TextOut(hdc, 140, 370, str, lstrlen(str));
			}

			sprintf_s(str, "ENCHANT");
			TextOut(hdc, WINSIZEX / 2 - 200, WINSIZEY / 2 - 33, str, lstrlen(str));
			hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
			oldFont = (HFONT)SelectObject(hdc, hFont);
			for (int i = m_nShowStartNum;
				i < (m_pPlayer->m_soulInven.vecEnchantSoul.size()<9
				? m_pPlayer->m_soulInven.vecEnchantSoul.size():8+ m_nShowStartNum- m_nShowEndChacker); i++)
			{
				if (i % 2 == 0)
				{
					sprintf_s(str, "%s", m_pPlayer->m_soulInven.vecEnchantSoul[i]->m_sName.c_str());
					TextOut(hdc, 60, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}
				else
				{
					sprintf_s(str, "%s", m_pPlayer->m_soulInven.vecEnchantSoul[i]->m_sName.c_str());
					TextOut(hdc, 380, 240 + (((i - m_nShowStartNum) / 2) * 20), str, lstrlen(str));
				}

			}
			SelectObject(hdc, oldFont);
			DeleteObject(hFont);
			break;
		default:
			break;
		}



	}

	


}

void menuScene::useItemFontPrint(HDC hdc)
{




	char str[300];
	SetTextColor(hdc, RGB(255, 255, 255));

	HFONT hFont;
	HFONT oldFont;

	hFont = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");
	oldFont = (HFONT)SelectObject(hdc, hFont);

	if (m_pPlayer->m_ItemInven.vecItemUse.size() == 0)
	{
		sprintf_s(str, "-------");
		TextOut(hdc, 80, 260 , str, lstrlen(str));


		sprintf_s(str, "-------");
		TextOut(hdc, 140, 400, str, lstrlen(str));


		return;
	}


	for (int i = m_nShowStartNum;
		i < (m_pPlayer->m_ItemInven.vecItemUse.size() < 9
			? m_pPlayer->m_ItemInven.vecItemUse.size() : 8 + m_nShowStartNum - m_nShowEndChacker); i++)
	{
		if (i % 2 == 0)
		{
			sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecItemUse[i]->m_sName.c_str());
			TextOut(hdc, 80, 260 + (((i - m_nShowStartNum) / 2) * 25), str, lstrlen(str));
		}
		else
		{
			sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecItemUse[i]->m_sName.c_str());
			TextOut(hdc, 380, 260 + (((i - m_nShowStartNum) / 2) * 25), str, lstrlen(str));
		}

	}

	sprintf_s(str, "%d", m_pPlayer->getPState()->curHP);
	TextOut(hdc, 150, 110, str, lstrlen(str));

	sprintf_s(str, "/ %d",m_pPlayer->getPState()->fullHP);
	TextOut(hdc, 225, 110, str, lstrlen(str));


	sprintf_s(str, "%d", m_pPlayer->getPState()->curMP);
	TextOut(hdc, 150, 140, str, lstrlen(str));

	sprintf_s(str, "/ %d",  m_pPlayer->getPState()->fullMP);
	TextOut(hdc, 225, 140, str, lstrlen(str));



	sprintf_s(str, "%s", m_pPlayer->m_ItemInven.vecItemUse[m_nShowStartNum+m_seleter.Select]->m_sExplanation.c_str());
	TextOut(hdc, 140, 400, str, lstrlen(str));

	SetTextColor(hdc, RGB(243, 122, 40));
	sprintf_s(str, "HP");
	TextOut(hdc, 100, 110, str, lstrlen(str));


	SetTextColor(hdc, RGB(126, 117, 255));

	sprintf_s(str, "MP");
	TextOut(hdc, 100, 140, str, lstrlen(str));



	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void menuScene::clearInven()
{

	for (m_pPlayer->m_ItemInven.hiter= m_pPlayer->m_ItemInven.vecHandItem.begin();
		m_pPlayer->m_ItemInven.hiter != m_pPlayer->m_ItemInven.vecHandItem.end();)
	{
		

		if ((*(m_pPlayer->m_ItemInven.hiter))->m_nCount==0 )
		{
			m_pPlayer->m_ItemInven.hiter=m_pPlayer->m_ItemInven.vecHandItem.erase(m_pPlayer->m_ItemInven.hiter);
		}
		else
		{
			m_pPlayer->m_ItemInven.hiter++;
		}

		if (m_pPlayer->m_ItemInven.hiter == m_pPlayer->m_ItemInven.vecHandItem.end())
		{
			break;
		}
	}

	for (m_pPlayer->m_ItemInven.biter = m_pPlayer->m_ItemInven.vecBodyItem.begin();
		m_pPlayer->m_ItemInven.biter != m_pPlayer->m_ItemInven.vecBodyItem.end();)
	{
		if ((*(m_pPlayer->m_ItemInven.biter))->m_nCount == 0)
		{
			m_pPlayer->m_ItemInven.biter = m_pPlayer->m_ItemInven.vecBodyItem.erase(m_pPlayer->m_ItemInven.biter);
		}
		else
		{
			m_pPlayer->m_ItemInven.biter++;
		}

		if (m_pPlayer->m_ItemInven.biter == m_pPlayer->m_ItemInven.vecBodyItem.end())
		{
			break;
		}
	}	
	
	
	for (m_pPlayer->m_ItemInven.aiter = m_pPlayer->m_ItemInven.vecAccessoryItem.begin();
		m_pPlayer->m_ItemInven.aiter != m_pPlayer->m_ItemInven.vecAccessoryItem.end();)
	{
		if ((*(m_pPlayer->m_ItemInven.aiter))->m_nCount == 0)
		{
			m_pPlayer->m_ItemInven.aiter = m_pPlayer->m_ItemInven.vecAccessoryItem.erase(m_pPlayer->m_ItemInven.aiter);
		}
		else
		{
			m_pPlayer->m_ItemInven.aiter++;
		}

		if (m_pPlayer->m_ItemInven.aiter == m_pPlayer->m_ItemInven.vecAccessoryItem.end())
		{
			break;
		}
	}



	for (m_pPlayer->m_ItemInven.iiter = m_pPlayer->m_ItemInven.vecItemUse.begin();
		m_pPlayer->m_ItemInven.iiter != m_pPlayer->m_ItemInven.vecItemUse.end();)
	{

		if ((*(m_pPlayer->m_ItemInven.iiter))->m_nCount==0)
		{
			m_pPlayer->m_ItemInven.iiter = m_pPlayer->m_ItemInven.vecItemUse.erase(m_pPlayer->m_ItemInven.iiter);
		}
		else
		{
			m_pPlayer->m_ItemInven.iiter++;
		}


		if (m_pPlayer->m_ItemInven.iiter == m_pPlayer->m_ItemInven.vecItemUse.end())
		{
			break;
		}
	}

}






Status menuScene::changeStatus(Status status , SoulSet soulSet, ItemSet itemSet)
{
	status.curStr = status.originStr + soulSet.eS->m_nChangeStr + soulSet.gS->m_nChangeStr+ soulSet.bS->m_nChangeStr+ itemSet.hI->m_nChangeStr+ itemSet.bI->m_nChangeStr+ itemSet.aI->m_nChangeStr;
	status.curCon = status.originCon + soulSet.eS->m_nChangeCon + soulSet.gS->m_nChangeCon + soulSet.bS->m_nChangeCon + itemSet.hI->m_nChangeCon + itemSet.bI->m_nChangeCon + itemSet.aI->m_nChangeCon;
	status.curInt = status.originInt + soulSet.eS->m_nChangeInt + soulSet.gS->m_nChangeInt + soulSet.bS->m_nChangeInt + itemSet.hI->m_nChangeInt + itemSet.bI->m_nChangeInt + itemSet.aI->m_nChangeInt;
	status.curLck = status.originLck + soulSet.eS->m_nChangeLck + soulSet.gS->m_nChangeLck + soulSet.bS->m_nChangeLck + itemSet.hI->m_nChangeLck + itemSet.bI->m_nChangeLck + itemSet.aI->m_nChangeLck;

	status.originAtt = status.curStr ;
	status.originDef = status.curCon/2;

	status.curAtt = status.originAtt + soulSet.eS->m_nChangeAtt + soulSet.gS->m_nChangeAtt + soulSet.bS->m_nChangeAtt + itemSet.hI->m_nChangeAtt + itemSet.bI->m_nChangeAtt + itemSet.aI->m_nChangeAtt;
	status.curDef = status.originDef + soulSet.eS->m_nChangeDef + soulSet.gS->m_nChangeDef + soulSet.bS->m_nChangeDef + itemSet.hI->m_nChangeDef + itemSet.bI->m_nChangeDef + itemSet.aI->m_nChangeDef;

	return status;
}

menuScene::menuScene()
{
}


menuScene::~menuScene()
{
}
