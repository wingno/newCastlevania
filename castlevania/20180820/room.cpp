#include "stdafx.h"
#include "room.h"


HRESULT room::init()
{
	return S_OK;
}

void room::release()
{
	
}

void room::update()
{
	
}

void room::render(HDC hdc)
{
	

}

void room::MapMove(float fx, float fy)
{
	m_posMap.x += fx;
	m_posMap.y += fy;
	m_posBG.x += fx;
	m_posBG.y += fy;



}

room::room()
{
}


room::~room()
{
}
