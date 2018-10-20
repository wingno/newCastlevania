#pragma once

class player;
class RoomObject;


class SubObject
{

	//���������Ʈ �����̹��� 
	image* m_imgCoin;
	//�ҿ�
	image* m_imgSoul;

	//����� ��Ÿ���� �����̹���
	//1��
	image* m_imgOneCoin;


	//ī��Ʈ
	int m_nCount;
	//��ġ X,Y Speed
	float m_fX, m_fY, m_fSpeed, m_fangle, m_fRange;
	//������, �ε���
	int m_nFrameX, m_nFrameY, m_nIndex, m_nSoulIndex ;
	//�ൿ����
	bool m_bDown, m_bStand, m_bOneCoin, m_bSoulMove , m_bSoulStand;


	//������Ʈ �ѹ�
	int SubObjectNum;
	//�������Ʈ 
	RoomObject* m_RoomObject;
	//�÷��̾�
	player* m_Player;
	//������Ʈ ����ִ°��
	SYNTHESIZE(bool, m_bAlive, Alive);
	//������Ʈ ��Ʈ
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

