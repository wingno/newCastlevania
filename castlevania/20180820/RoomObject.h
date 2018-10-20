#pragma once
class image;
class SubObject;


class RoomObject 
{
private:
	
	//프레임 
	int m_nObjFrameX, m_nObjFrameY;
	//인덱스
	int m_nObjIdx;
	//카운트
	int m_nObjCount;
	//오브잭트 번호
	int m_nObjNum;

	SubObject* m_SubObject;

	//오브잭트이미지
	image* m_imgObj;
	image* m_imgObj1;
	image* m_imgObj2;
	//오브잭트 위치
	SYNTHESIZE(int, m_nFX, FX);
	SYNTHESIZE(int, m_nFY, FY);

	//오브잭트 생성 기본상태
	SYNTHESIZE(bool, m_bObjStand , ObjStand);
	SYNTHESIZE(bool, m_bObjDestruction, Destruction);

	//파괴 여부를 채크
	bool m_bObjDestructionMove;
// 랙트
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

