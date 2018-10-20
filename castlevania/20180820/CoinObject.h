//#pragma once
//
//
//class player;
//class RoomObject;
//
//class CoinObject 
//{
//
//private:
//
//	//@@@@@@@@@@@@@@@@@@코인@@@@@@@@@@@@@@@@
//
//	//코인오브젝트 넘버
//	int CoinNum;
//	//코인이미지
//	image* m_coin;
//	image* m_imgcoin;
//	image* m_soulob;
//
//	int m_nimgcount;
//	//위치
//	int FX, FY;
//	float speed;
//	//프레임 
//	int FrameX, FrameY;
//	//인덱스
//	int MyIdx;
//	//카운트
//	int MYCount;
//	int m_angle;
//	bool Down;
//	bool m_bstand;
//	bool ;
//	RoomObject* m_RoomOBJ;
//	player* m_play;
//
//	SYNTHESIZE(bool, Alive, Alive);
//	SYNTHESIZE(bool, obAlive, obAlive);
//	SYNTHESIZE(bool, Destruction, Destruction);
//	SYNTHESIZE(RECT, m_rc, rc);
//
//public:
//
//		virtual HRESULT init(int XX, int XY);
//	virtual void release();
//	virtual void update();
//	virtual void render(HDC hdc);
//	void soulMove();
//
//
//	CoinObject();
//	~CoinObject();
//};
//
