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
//	//@@@@@@@@@@@@@@@@@@����@@@@@@@@@@@@@@@@
//
//	//���ο�����Ʈ �ѹ�
//	int CoinNum;
//	//�����̹���
//	image* m_coin;
//	image* m_imgcoin;
//	image* m_soulob;
//
//	int m_nimgcount;
//	//��ġ
//	int FX, FY;
//	float speed;
//	//������ 
//	int FrameX, FrameY;
//	//�ε���
//	int MyIdx;
//	//ī��Ʈ
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
