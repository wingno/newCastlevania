#pragma once
#include "room.h"

class image;
class SkeletonArcher;
class zombie;
class RoomObject;

class hallwayRoom1:public room
{
private:

	RECT rectGate[3];
	RECT rectObj[2];
	SkeletonArcher* m_Archer;
	RoomObject* m_Object;



	zombie* m_Zombie;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);



	void colliderMake();
	void rectColider();
	void checkCollision();

	hallwayRoom1();
	~hallwayRoom1();
};

