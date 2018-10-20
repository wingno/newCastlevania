#pragma once

class image;
class player;




class SkeletonArcher
{

	image* m_Archer;
	RECT	m_rc;

	player* m_plyer;

	//¾Ö³Ê¹Ì 1
	float ArcherX, Archery;
	int  ArcherFX, ArcherFY;
	int ArcherIDX;
	int  Archercount;
	int BACKcount;
	bool  Archermove, Archerstand, Archerdead;
	bool ArcherAlive;


public:


	HRESULT init(int startX, int startY);
	void release();
	void update();
	void render(HDC hdc);
	void MOVE();
	SkeletonArcher();
	~SkeletonArcher();
};

