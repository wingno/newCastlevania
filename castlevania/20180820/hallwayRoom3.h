#pragma once
#include "room.h"
#include "balore.h"

class battleScene;
class image;


class hallwayRoom3: public room
{


private:

	RECT rectGate[3];
	RECT rectObj[2];
	balore  m_nBalore;
	SYNTHESIZE(battleScene*, m_pBattleSceen,BattleSceen);

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void rectColider();
	void colliderMake();

	hallwayRoom3();
	~hallwayRoom3();
};

