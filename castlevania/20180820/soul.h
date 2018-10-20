#pragma once
class soul
{
protected:
	SYNTHESIZE( image*, m_imgIcon,ImgIcon);
	string m_sName;
	string	m_sExplanation;

	int m_nType;
	int	m_nCount;
	int m_nIdx;

	int m_nChangeAtt;
	int m_nChangeDef;
	int m_nChangeStr;
	int m_nChangeInt;
	int m_nChangeCon;
	int m_nChangeLck;

	int m_nChangeMP;
	int m_nChangeHP;

	int m_nUseMp;



public:
	virtual void init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr,
		int cInt, int cCon, int cLuc, int cHp, int cMp,int useMp,string cName,string cExplanation);
	virtual void release();
	virtual void update();
	virtual void render();
	soul();
	~soul();
};

