#pragma once

class player;
class progressBar
{
private:
	RECT	m_rc;
	//ä�¹� ��ġ
	int  m_fX, m_fY;
	
	float	m_fWidth;
	float	m_fWidthMp;
	//ä�� 
	int m_nMyHp;
	//������
	int m_nFrameY;
	int m_nFrameY1;
	int m_nFrameY2;
	int m_nFrameY3;


	image*  m_imgeMenuProgress;
	image*	m_imgHp;
	image*  m_imgMp;

	//ü�� ������
	image*  m_imgNum;
	image*  m_imgNum1;
	image*  m_imgNum2;
	image*  m_imgNum3;

	player* m_pPlayer;

public:
	HRESULT init(float x, float y, float width, float height);
	void release();
	void update();
	void render(HDC hdc);
	void HpGauge(HDC hdc);
	void setGauge(float currGauge, float maxGauge
		,float currGaugemp, float maxGaugemp);



	progressBar();
	~progressBar();
};

