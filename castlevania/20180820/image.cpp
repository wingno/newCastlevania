#include "stdafx.h"
#include "image.h"
#include "animation.h"

#pragma comment (lib, "msimg32.lib")

image::image()
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pImageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// ���� ����
	// �ɼ�
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// ���� ���� ����� ���� �߰� �̹���
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, 
		WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;


	// ���� ���� ����� ���� �߰� �̹���
	m_ptempImage = new IMAGE_INFO;
	m_ptempImage->hMemDC = CreateCompatibleDC(hdc);
	m_ptempImage->hBitmap = CreateCompatibleBitmap(hdc,
		WINSIZEX, WINSIZEY);
	m_ptempImage->hOldBitmap = (HBITMAP)SelectObject(
		m_ptempImage->hMemDC, m_ptempImage->hBitmap);
	m_ptempImage->nWidth = WINSIZEX;
	m_ptempImage->nHeight = WINSIZEY;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//HRESULT image::init(const char * szFileName, int width, int height)
//{
//	if (szFileName == NULL) return E_FAIL;
//
//	HDC hdc = GetDC(g_hWnd);
//
//	m_pImageInfo = new IMAGE_INFO;
//	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
//	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
//	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
//	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
//		g_hInstance, 
//		szFileName,
//		IMAGE_BITMAP,
//		width, height,
//		LR_LOADFROMFILE);
//	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
//	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);
//
//	m_pImageInfo->nWidth = width;
//	m_pImageInfo->nHeight = height;
//
//	ReleaseDC(g_hWnd, hdc);
//
//	if (m_pImageInfo->hBitmap == NULL)
//	{
//		release();
//		return E_FAIL;
//	}
//
//	return S_OK;
//}

HRESULT image::init(const char * szFileName, int width, int height, bool trans /*= false*/, COLORREF transColor)
{
	if (szFileName == NULL) return E_FAIL;

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// ���� ����
	// �ɼ�
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// ���� ���� ����� ���� �߰� �̹���
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// ���� �÷� ����
	m_isTransparent = trans;
	m_transColor = transColor;


	// ���� ���� ����� ���� �߰� �̹���
	m_ptempImage = new IMAGE_INFO;
	m_ptempImage->hMemDC = CreateCompatibleDC(hdc);
	m_ptempImage->hBitmap = CreateCompatibleBitmap(hdc,
		WINSIZEX, WINSIZEY);
	m_ptempImage->hOldBitmap = (HBITMAP)SelectObject(
		m_ptempImage->hMemDC, m_ptempImage->hBitmap);
	m_ptempImage->nWidth = WINSIZEX;
	m_ptempImage->nHeight = WINSIZEY;


	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char * szFileName, float x, float y,
	int width, int height, int frameX, int frameY,
	bool trans, COLORREF transColor)
{
	if (szFileName == NULL) return E_FAIL;

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->fX = x;
	m_pImageInfo->fY = y;
	m_pImageInfo->nCurrFrameX = 0;
	m_pImageInfo->nCurrFrameY = 0;
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nFrameWidth = width / frameX;
	m_pImageInfo->nFrameHeight = height / frameY;
	m_pImageInfo->nMaxFrameX = frameX - 1;
	m_pImageInfo->nMaxFrameY = frameY - 1;

	// ���� ����
	// �ɼ�
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// ���� ���� ����� ���� �߰� �̹���
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;


	// ���� ���� ����� ���� �߰� �̹���
	m_ptempImage = new IMAGE_INFO;
	m_ptempImage->hMemDC = CreateCompatibleDC(hdc);
	m_ptempImage->hBitmap = CreateCompatibleBitmap(hdc,
		WINSIZEX, WINSIZEY);
	m_ptempImage->hOldBitmap = (HBITMAP)SelectObject(
		m_ptempImage->hMemDC, m_ptempImage->hBitmap);
	m_ptempImage->nWidth = WINSIZEX;
	m_ptempImage->nHeight = WINSIZEY;

	// ���� �÷� ����
	m_isTransparent = trans;
	m_transColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

void image::release()
{
	if (m_pBlendImage)
	{
		SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hOldBitmap);
		DeleteObject(m_pBlendImage->hBitmap);
		DeleteDC(m_pBlendImage->hMemDC);

		delete m_pBlendImage;
	}

	if (m_pImageInfo)
	{
		SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hOldBitmap);
		DeleteObject(m_pImageInfo->hBitmap);
		DeleteDC(m_pImageInfo->hMemDC);

		delete m_pImageInfo;
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// ������
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// ����� ũ��
			
			// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			0, 0,					// ����� ���� ������ǥ
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		// hdc : ����� ������ DC
		// destX : ����� ������ x ��ǥ
		// destY : ����� ������ y ��ǥ
		// cx : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// cy : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// hdcSrc : ������ ������ �����ϴ� DC
		// x1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// y1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// rop : �����ϴ� �ɼ� (SRCCOPY)
		BitBlt(
			hdc, 
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int scalar)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// ������
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			m_pImageInfo->nWidth*scalar,
			m_pImageInfo->nHeight*scalar,	// ����� ũ��

			// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			0, 0,					// ����� ���� ������ǥ
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		// hdc : ����� ������ DC
		// destX : ����� ������ x ��ǥ
		// destY : ����� ������ y ��ǥ
		// cx : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// cy : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// hdcSrc : ������ ������ �����ϴ� DC
		// x1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// y1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// rop : �����ϴ� �ɼ� (SRCCOPY)
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, 
	int sourX, int sourY, int sourWidth, int sourHeight, int scalar)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// ������
			hdc,					// ����� ������ DC
			destX, destY,			// ����� ��ǥ ������
			sourWidth * scalar, sourHeight * scalar,	// ����� ũ��

			// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			sourX, sourY,			// ����� ���� ������ǥ
			sourWidth, sourHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			sourX, sourY,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY)
{
	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;

	if (m_isTransparent)
	{
		GdiTransparentBlt(
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� ũ��

									// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// ����� ���� ������ǥ
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, int sourWidth, int sourHeight)
{
	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;

	if (m_isTransparent)
	{
		GdiTransparentBlt(
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			sourWidth,
			sourHeight,	// ����� ũ��

									// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// ����� ���� ������ǥ
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, float scale)
{
	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;

	if (m_isTransparent)
	{
		GdiTransparentBlt(
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			m_pImageInfo->nFrameWidth*scale,
			m_pImageInfo->nFrameHeight*scale,	// ����� ũ��

									// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// ����� ���� ������ǥ
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}


void image::alphaRender(HDC hdc, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. ����ؾߵǴ� DC�� �׷����ִ� ������ blendImage�� ����
		BitBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			SRCCOPY);

		// 2. ����� �̹����� blendImage�� ����
		GdiTransparentBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC�� ����ؾߵǴ� DC�� ����
		AlphaBlend(hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// ������ ��ǥ
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// ������ ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. ����ؾߵǴ� DC�� �׷����ִ� ������ blendImage�� ����
		BitBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. ����� �̹����� blendImage�� ����
		GdiTransparentBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC�� ����ؾߵǴ� DC�� ����
		AlphaBlend(hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// ������ ��ǥ
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// ������ ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha, float scale)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. ����ؾߵǴ� DC�� �׷����ִ� ������ blendImage�� ����
		BitBlt(
			// ������
			m_pBlendImage->hMemDC,
			0, 0,
			sourWidth , sourHeight ,

			// ���
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. ����� �̹����� blendImage�� ����
		GdiTransparentBlt(
			// ������
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC�� ����ؾߵǴ� DC�� ����
		AlphaBlend(
			// ������
			hdc,
			destX, destY,
			sourWidth , sourHeight,

			// ���
			m_pBlendImage->hMemDC,
			sourX, sourY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// ������ ��ǥ
			hdc,
			destX, destY,
			sourWidth  , sourHeight,
			// ������ ���
			m_pImageInfo->hMemDC,
			sourX, sourY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::rotateRender(HDC hdc, float rotateAngle, float fX, float fY, float anchorX/*0.5*/, float anchorY/*0.5*/, int scalar/*=1*/)
{

	// ���� ������ ���Ȱ����� ��ȯ
	float theta = rotateAngle * PI / 180.0f;

	// sin, cos�� ���ϱ�
	float s = sinf(theta);
	float c = cosf(theta);

	float fAncherX = anchorX; // ��Ŀ���� ȸ���� ������ �� �׷��� �̹� ������Ʈ���� ����� �������� ȸ���� �ϱ� ������ 0.5�� �������� �س���
	float fAncherY = anchorY;

	float posXSrcL = m_pImageInfo->nWidth * fAncherX;
	float posYSrcL = m_pImageInfo->nHeight * fAncherY;
	float posXSrcR = m_pImageInfo->nWidth * (1.0f - fAncherX);
	float posYSrcR = m_pImageInfo->nHeight * (1.0f - fAncherY);

	POINT m_vertices[3];


	if (m_isTransparent)
	{

		// Upper-Left
		m_vertices[0].x = (LONG)((-posXSrcL * c + posYSrcL * s) + m_pImageInfo->nWidth / 2);
		m_vertices[0].y = (LONG)((-posXSrcL * s - posYSrcL * c) + m_pImageInfo->nHeight / 2);
		// Upper-Right
		m_vertices[1].x = (LONG)((posXSrcR * c + posYSrcL * s) + m_pImageInfo->nWidth / 2);
		m_vertices[1].y = (LONG)((posXSrcR * s - posYSrcL * c) + m_pImageInfo->nHeight / 2);
		// Lower-Right
		m_vertices[2].x = (LONG)((-posXSrcL * c - posYSrcR * s) + m_pImageInfo->nWidth / 2);
		m_vertices[2].y = (LONG)((-posXSrcL * s + posYSrcR * c) + m_pImageInfo->nHeight / 2);

		HBRUSH brush = CreateSolidBrush(m_transColor);

		RECT rc;
		rc = RectMake(0, 0, m_pImageInfo->nWidth + (m_pImageInfo->nWidth / 2), m_pImageInfo->nHeight + (m_pImageInfo->nHeight / 2));

		FillRect(m_ptempImage->hMemDC, &rc, brush);
		DeleteObject(brush);




		PlgBlt(m_ptempImage->hMemDC, m_vertices, m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, NULL, 0, 0);



		// 2. ����� �̹����� blendImage�� ����
		GdiTransparentBlt(hdc,
			fX - m_pImageInfo->nWidth / 2, fY - m_pImageInfo->nHeight / 2,
			(m_pImageInfo->nWidth)*scalar, (m_pImageInfo->nHeight)*scalar,
			m_ptempImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
	}
	else
	{
		// Upper-Left
		m_vertices[0].x = (LONG)((-posXSrcL * c + posYSrcL * s) + fX);
		m_vertices[0].y = (LONG)((-posXSrcL * s - posYSrcL * c) + fY);
		// Upper-Right
		m_vertices[1].x = (LONG)((posXSrcR * c + posYSrcL * s) + fX);
		m_vertices[1].y = (LONG)((posXSrcR * s - posYSrcL * c) + fY);
		// Lower-Right
		m_vertices[2].x = (LONG)((-posXSrcL * c - posYSrcR * s) + fX);
		m_vertices[2].y = (LONG)((-posXSrcL * s + posYSrcR * c) + fY);

		PlgBlt(hdc, m_vertices, m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth + 20, m_pImageInfo->nHeight + 20, NULL, 0, 0);

	}

}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani, int scalar)
{
	render(hdc, destX, destY,
		ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight(), scalar);
}

void image::aniReversRender(HDC hdc, int destX, int destY, animation * ani, int scalar)
{
	render(hdc, destX, destY,
		ani->getReversFramePos().x, ani->getReversFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight(), scalar);
}

void image::setTransColor(bool trans, COLORREF transColor)
{
	m_isTransparent = trans;
	m_transColor = transColor;
}
