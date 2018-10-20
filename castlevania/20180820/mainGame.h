#pragma once
class titleScene;
class battleScene;
class scoreScene;
class selectScene;
class EndingScene;
class menuScene;
class GameOverScene;
class spaceShip;
class player;



class roomManager;
class hallwayRoom1;
class hallwayRoom2;
class hallwayRoom3;
class FountainRoom;
class gateRoom;
class SaveRoom;
class CastleHallway;
class BrickStaircaseroom;



class mainGame
{
private:
	// DC
	HDC hdc;

	// ¹é¹öÆÛ
	image * m_pBackBuffer;
	void setBackBuffer();

	char m_szText[128];

	int m_nscore;

	SYNTHESIZE( player*, m_pPlayer,Player);


	// save load test
	//std::vector<std::string> m_vecLoad;

	// scene test
	titleScene*		m_pTitleScene;
	battleScene*	m_pBattleScene;
	scoreScene*		m_pscoreScene;
	selectScene*	m_pselectScene;
	menuScene*		m_pmenuScene;
	GameOverScene*  m_pGameOverScene;
	EndingScene*	m_pEndingScene;

	hallwayRoom1*	m_phallwayRoom1;
	hallwayRoom2*	m_phallwayRoom2;
	hallwayRoom3*	m_phallwayRoom3;
	FountainRoom*	m_pFountainRoom;
	gateRoom*		m_gateroom;
	SaveRoom*		m_SaveRoom;
	roomManager*	m_RoomMgr;
	CastleHallway*  m_CastleHallway;
	BrickStaircaseroom* m_BrickStaircaseroom;

public:
	HRESULT init();
	void release();
	void update();
	void render();




	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame();
	~mainGame();
};

