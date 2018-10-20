#pragma once
#include "room.h"

class image;
class RoomObject;

class CastleHallway : public room
{
private:
	//��
	RECT rectGate[3];
	//����
	RECT rectObj[12];
	RoomObject* m_Object;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void colliderMake();
	void rectColider();
	void checkCollision();
	
	CastleHallway();
	~CastleHallway();
};

