#pragma once

class player;
class RoomObject;


class SubObject
{

	//서브오브잭트 코인이미지 
	image* m_imgCoin;
	//소울
	image* m_imgSoul;

	//습득시 나타나는 간판이미지
	//1원
	image* m_imgOneCoin;


	//카운트
	int m_nCount;
	//위치 X,Y Speed
	float m_fX, m_fY, m_fSpeed, m_fangle, m_fRange;
	//프레임, 인덱스
	int m_nFrameX, m_nFrameY, m_nIndex, m_nSoulIndex ;
	//행동변경
	bool m_bDown, m_bStand, m_bOneCoin, m_bSoulMove , m_bSoulStand;


	//오브잭트 넘버
	int SubObjectNum;
	//룸오브잭트 
	RoomObject* m_RoomObject;
	//플레이어
	player* m_Player;
	//오브잭트 살아있는경우
	SYNTHESIZE(bool, m_bAlive, Alive);
	//오브잭트 렉트
	SYNTHESIZE(RECT, m_rc, rc);
	



public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void checkCollision();
	void SetSubObjectNum(int Num);
	void SetSubObjectXY(int X, int Y);
	void soulMove();


	

	SubObject();
	~SubObject();
};

