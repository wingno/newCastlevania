#pragma once
#include "room.h"
class image;
class RoomObject;

class gateRoom :public room
{
	
	RECT rectGate[1];
	RECT rectObj[6];
	//ø¿∫Í¿Ë∆Æ
	RoomObject* m_Object;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void colliderMake();
	void rectColider();
	void checkCollision();


	gateRoom();
	~gateRoom();
};

