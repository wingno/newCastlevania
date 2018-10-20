#pragma once
#include "scene.h"

class spaceShip;
class enemyManager;
class camel;
class player;
class progressBar;
//��





class battleScene : public scene
{
private:
	image *			m_imgMap;
	spaceShip*		m_pSpaceShip;
	enemyManager*	m_pEnemyMgr;
	camel*			m_pCamel;

	//ä�¹�
	progressBar*	m_progressBar;
	


	//��


	player*			m_pPlayer;

	int m_nstage;

	int* m_pscore;

	int m_nselectNum;

	bool m_benemyIsSetting;

	bool m_bIsChangeScene;

	bool m_bPlayerDieChangeScene;

	SYNTHESIZE(bool, m_bGameEnd, GameEnd);


	int m_nAlphaNum;

	

	// save load test
	std::vector<std::string> m_vecLoad;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void checkCollision();

	inline void setIsScore(int* score) { m_pscore = score; }



	inline void setISpaceShip(spaceShip* SpaceShip) { m_pSpaceShip = SpaceShip; }

	battleScene();
	~battleScene();
};

