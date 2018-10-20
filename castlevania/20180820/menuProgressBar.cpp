#include "stdafx.h"
#include "menuProgressBar.h"


HRESULT menuProgressBar::init(float x, float y, float width, float height, bool isHp)
{
	m_fX = x;
	m_fY = y;
	m_fWidth = width-10;

	m_rc = RectMake(m_fX, m_fY, m_fWidth, height);


	if (isHp)
	{
		m_imgTop = IMAGEMANAGER->addImage("image/progesshptop.bmp","image/progesshptop.bmp", m_fWidth, height-8, true, RGB(255, 0, 255));
	}
	else
	{
		m_imgTop = IMAGEMANAGER->addImage("image/progessmptop.bmp", "image/progessmptop.bmp", m_fWidth, height-8, true, RGB(255, 0, 255));
	}
	m_imgBottom = IMAGEMANAGER->addImage("barBottom","image/progressbottom.bmp", width, height, true, RGB(255, 0, 255));

	return S_OK;
}

void menuProgressBar::release()
{
}

void menuProgressBar::update()
{
}

void menuProgressBar::render(HDC hdc)
{
	m_imgBottom->render(hdc, m_fX, m_fY);
	m_imgTop->render(hdc, m_fX+5, m_fY+4,
		0, 0, m_fWidth, m_imgTop->getHeight());
}

void menuProgressBar::render(HDC hdc, int x, int y)
{
	m_imgBottom->render(hdc, x, y);
	m_imgTop->render(hdc, x + 5, y + 4,
		0, 0, m_fWidth, m_imgTop->getHeight());
}


void menuProgressBar::setGauge(float currGauge, float maxGauge)
{
	m_fWidth = (currGauge / maxGauge) * m_imgTop->getWidth();
}

menuProgressBar::menuProgressBar()
{
}


menuProgressBar::~menuProgressBar()
{
}
