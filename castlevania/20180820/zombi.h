#pragma once

class image;
class room;

class zombi
{

	image* m_zombi;
	RECT	m_rc;
	
	room* m_rom;

	//¾Ö³Ê¹Ì 1
	float zombiX, zombiy;
	int zombiFX, zombiFY;
	int zombiIDX;
	int  zombicount;
	bool  zombimove, zombistand, zombidead;
	bool Alive;

public:
	
	HRESULT init(int startX, int startY);
	void release();
	void update();
	void render(HDC hdc);
	void MOVE();

	inline bool getlive() { return Alive; }
	inline void setlive(bool live) { Alive = live; }
	
	zombi();
	~zombi();


};

