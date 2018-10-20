#include "stdafx.h"
#include "item.h"


void item::init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr, int cInt, int cCon, int cLuc, int cHp, int cMp, string cName, string cExplanation)
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

	if (cIdx == 0)
	{
		m_imgIcon = NULL;

	}
	else
	{
		m_imgIcon = IMAGEMANAGER->addImage("image/item.bmp", "image/item.bmp", 360, 18, 20, 1, true, RGB(0, 64, 128));

	}

}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
}

item::item()
{
}


item::~item()
{
}
