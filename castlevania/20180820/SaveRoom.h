#pragma once
#include "room.h"


class image;


class SaveRoom : public room
{
private:

	RECT rectGate[3];
	RECT rectObj[2];

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void rectColider();
	void colliderMake();


	SaveRoom();
	~SaveRoom();
};

