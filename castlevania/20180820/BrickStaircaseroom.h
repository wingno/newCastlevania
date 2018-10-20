#pragma once
#include "room.h"
class image;

class BrickStaircaseroom : public room
{
	RECT rectGate[3];
	RECT rectObj[2];

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void rectColider();
	void colliderMake();


	BrickStaircaseroom();
	~BrickStaircaseroom();
};

