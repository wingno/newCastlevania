#pragma once
#include "room.h"
class image;
class RoomObject;


class hallwayRoom2: public room
{
private:

	RECT rectGate[3];
	RECT rectObj[2];
	RoomObject* m_Object;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void rectColider();
	void colliderMake();
	void checkCollision();


	hallwayRoom2();
	~hallwayRoom2();
};

