#pragma once
class image;
class SubObject;


class RoomObject 
{
private:
	
	//������ 
	int m_nObjFrameX, m_nObjFrameY;
	//�ε���
	int m_nObjIdx;
	//ī��Ʈ
	int m_nObjCount;
	//������Ʈ ��ȣ
	int m_nObjNum;

	SubObject* m_SubObject;

	//������Ʈ�̹���
	image* m_imgObj;
	image* m_imgObj1;
	image* m_imgObj2;
	//������Ʈ ��ġ
	SYNTHESIZE(int, m_nFX, FX);
	SYNTHESIZE(int, m_nFY, FY);

	//������Ʈ ���� �⺻����
	SYNTHESIZE(bool, m_bObjStand , ObjStand);
	SYNTHESIZE(bool, m_bObjDestruction, Destruction);

	//�ı� ���θ� äũ
	bool m_bObjDestructionMove;
// ��Ʈ
	SYNTHESIZE(RECT, m_rc, rc);


public:

	virtual HRESULT init(int nFX, int nFY, int ObjNum);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void ObjectCode();
	


	RoomObject();
	~RoomObject();
};

