#include "stdafx.h"
#include "mainGame.h"
#include "titleScene.h"
#include "battleScene.h"
#include "scoreScene.h"
#include "selectScene.h"
#include "spaceShip.h"
#include "menuScene.h"
#include "player.h"
#include"GameOverScene.h"
#include "EndingScene.h"

//��
#include "hallwayRoom1.h"
#include "hallwayRoom2.h"
#include "hallwayRoom3.h"
#include "FountainRoom.h"
#include"gateroom.h"
#include "SaveRoom.h"
#include "CastleHallway.h"
#include "BrickStaircaseroom.h"


/*
	���� window â���� (winmain () )

*/

void mainGame::setBackBuffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX, WINSIZEY);
}

HRESULT mainGame::init()
{
	hdc = GetDC(g_hWnd);

	//����
	m_nscore = 0;

	m_pPlayer = new player;
	m_pPlayer->init();

	ROOMMANAGER->setPlayer(m_pPlayer);

	//HANDLE hTimer = (HANDLE)SetTimer(g_hWnd, 1, 10, NULL);
	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	EFFECTMANAGER->init();
	ROOMMANAGER->init();

	setBackBuffer();

	EFFECTMANAGER->addEffect("explosion1", "image/explosion.bmp", 832, 62, 32, 62, 30, 10);

	// �� �̴ϼȶ�����
	m_phallwayRoom1 = new hallwayRoom1;
	ROOMMANAGER->addRoom("hallwayRoom1", m_phallwayRoom1);

	m_phallwayRoom2 = new hallwayRoom2;
	ROOMMANAGER->addRoom("hallwayRoom2", m_phallwayRoom2);

	m_phallwayRoom3 = new hallwayRoom3;
	ROOMMANAGER->addRoom("hallwayRoom3", m_phallwayRoom3);

	m_pFountainRoom = new FountainRoom;
	ROOMMANAGER->addRoom("FountainRoom", m_pFountainRoom);

	m_gateroom = new gateRoom;
	ROOMMANAGER->addRoom("gateroom", m_gateroom);

	m_SaveRoom = new SaveRoom;
	ROOMMANAGER->addRoom("saveroom", m_SaveRoom);

	m_CastleHallway = new CastleHallway;
	ROOMMANAGER->addRoom("CastleHallwayy", m_CastleHallway);


	m_BrickStaircaseroom = new BrickStaircaseroom;
	ROOMMANAGER->addRoom("BrickStaircaseroom", m_BrickStaircaseroom);

	ROOMMANAGER->changeRoom("gateroom");


	m_pBattleScene = new battleScene;
	SCENEMANAGER->addScene("battle", m_pBattleScene);


	m_pTitleScene = new titleScene;
	SCENEMANAGER->addScene("titleScene", m_pTitleScene);

	m_pmenuScene = new menuScene;
	SCENEMANAGER->addScene("menu", m_pmenuScene);

	m_pGameOverScene = new GameOverScene;
	SCENEMANAGER->addScene("GameOverScene", m_pGameOverScene);

	m_pEndingScene = new EndingScene;
	SCENEMANAGER->addScene("EndingScene", m_pEndingScene);


	SCENEMANAGER->changeScene("titleScene");
	

	m_phallwayRoom3->setBattleSceen(m_pBattleScene);

	//m_pBattleScene->setIsScore(&m_nscore);
	//m_pscoreScene->setIsScore(&m_nscore);
	//



	// ��Ÿ �ִϸ��̼� �׽�Ʈ


	// ���� ���� �׽�Ʈ
	//TXTDATA->txtSave("test.txt");
	//TXTDATA->txtLoad("test.txt");

	// 0 ) ���� ����
	// 1 )�츮�� �л� �̸� ���θ� ���� ���� ����
	//vector<string> vec;
	//vec.push_back("�̼���");
	//vec.push_back("������");
	//vec.push_back("���ο�");
	//vec.push_back("������");
	//TXTDATA->txtSave("test1.txt", vec);

	//// 2) ���̺� ���� �ε��ؼ� vector�� �ٽ� �־ ȭ�鿡 ���
	//m_vecLoad = TXTDATA->txtLoad("test1.txt");
	



	return S_OK;
}

void mainGame::release()
{


	if (m_pBackBuffer)	delete m_pBackBuffer;

	//KillTimer(g_hWnd, 1);
	ReleaseDC(g_hWnd, hdc);

	TXTDATA->release();
	KEYMANAGER->release();
	IMAGEMANAGER->release();
	TIMEMANAGER->release();
	EFFECTMANAGER->release();
	SCENEMANAGER->release();
	ROOMMANAGER->release();

	TXTDATA->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();

	SAFE_DELETE(m_pPlayer);
}

LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HDC hdc;
	//PAINTSTRUCT ps;

	switch (iMessage)
	{
	//case WM_TIMER:
	//	//this->update();
	//	break;
	//case WM_PAINT:
	//{
	//	hdc = BeginPaint(hWnd, &ps);
	//	this->render(hdc);
	//	EndPaint(hWnd, &ps);
	//}
	//break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void mainGame::update()
{
	InvalidateRect(g_hWnd, NULL, false);
	
	SCENEMANAGER->update();

}

void mainGame::render()
{
	HDC backDC = m_pBackBuffer->getMemDC();


	SCENEMANAGER->render(backDC);
	
	TIMEMANAGER->render(backDC);

	m_pBackBuffer->render(hdc, 0, 0);
}



mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
