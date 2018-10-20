#include "stdafx.h"
#include "soul.h"


void soul::init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr,
	int cInt, int cCon, int cLuc, int cHp, int cMp,int UseMp, string cName, string cExplanation)
{
	m_sName = cName;
	m_sExplanation = cExplanation;
	m_nType = cType;
	m_nCount = cCount;
	m_nIdx = cIdx;
	m_nChangeAtt = cAtt;
	m_nChangeDef = cDef;
	m_nChangeStr = cStr;
	m_nChangeInt = cInt;
	m_nChangeCon = cCon;
	m_nChangeLck = cLuc;
	m_nChangeMP = cMp;
	m_nChangeHP = cHp;
	m_nUseMp = UseMp;


	m_imgIcon = NULL;

}

void soul::release()
{
}

void soul::update()
{
}

void soul::render()
{
}

soul::soul()
{
}


soul::~soul()
{
}
