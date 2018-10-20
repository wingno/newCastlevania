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
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pImageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// 알파 블렌드
	// 옵션
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// 알파 블렌드 사용을 위한 중간 이미지
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, 
		WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;


	// 알파 블렌드 사용을 위한 중간 이미지
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
//	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
//	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
//	// 원본 DC와 호환되는 비트맵 생성
//	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
//		g_hInstance, 
//		szFileName,
//		IMAGE_BITMAP,
//		width, height,
//		LR_LOADFROMFILE);
//	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
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
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// 알파 블렌드
	// 옵션
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// 알파 블렌드 사용을 위한 중간 이미지
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// 투명 컬러 셋팅
	m_isTransparent = trans;
	m_transColor = transColor;


	// 알파 블렌드 사용을 위한 중간 이미지
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
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
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

	// 알파 블렌드
	// 옵션
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// 알파 블렌드 사용을 위한 중간 이미지
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;


	// 알파 블렌드 사용을 위한 중간 이미지
	m_ptempImage = new IMAGE_INFO;
	m_ptempImage->hMemDC = CreateCompatibleDC(hdc);
	m_ptempImage->hBitmap = CreateCompatibleBitmap(hdc,
		WINSIZEX, WINSIZEY);
	m_ptempImage->hOldBitmap = (HBITMAP)SelectObject(
		m_ptempImage->hMemDC, m_ptempImage->hBitmap);
	m_ptempImage->nWidth = WINSIZEX;
	m_ptempImage->nHeight = WINSIZEY;

	// 투명 컬러 셋팅
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
			// 목적지
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// 복사될 크기
			
			// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			0, 0,					// 복사될 영역 시작좌표
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
	}
	else
	{
		// hdc : 복사될 목적지 DC
		// destX : 출력을 시작할 x 좌표
		// destY : 출력을 시작할 y 좌표
		// cx : 출력할 이미지를 어느정도까지 출력할 것인가의 가로값
		// cy : 출력할 이미지를 어느정도까지 출력할 것인가의 세로값
		// hdcSrc : 복사할 정보를 제공하는 DC
		// x1 : 이미지의 시작점을 잘라낼 것인가의 가로값
		// y1 : 이미지의 시작점을 잘라낼 것인가의 세로값
		// rop : 복사하는 옵션 (SRCCOPY)
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
			// 목적지
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nWidth*scalar,
			m_pImageInfo->nHeight*scalar,	// 복사될 크기

			// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			0, 0,					// 복사될 영역 시작좌표
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
	}
	else
	{
		// hdc : 복사될 목적지 DC
		// destX : 출력을 시작할 x 좌표
		// destY : 출력을 시작할 y 좌표
		// cx : 출력할 이미지를 어느정도까지 출력할 것인가의 가로값
		// cy : 출력할 이미지를 어느정도까지 출력할 것인가의 세로값
		// hdcSrc : 복사할 정보를 제공하는 DC
		// x1 : 이미지의 시작점을 잘라낼 것인가의 가로값
		// y1 : 이미지의 시작점을 잘라낼 것인가의 세로값
		// rop : 복사하는 옵션 (SRCCOPY)
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
			// 목적지
			hdc,					// 복사될 목적지 DC
			destX, destY,			// 복사될 좌표 시작점
			sourWidth * scalar, sourHeight * scalar,	// 복사될 크기

			// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			sourX, sourY,			// 복사될 영역 시작좌표
			sourWidth, sourHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
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
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 크기

									// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// 복사될 영역 시작좌표
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
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
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			sourWidth,
			sourHeight,	// 복사될 크기

									// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// 복사될 영역 시작좌표
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
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
			hdc,	// 복사될 목적지 DC
			destX, destY,		// 복사될 좌표 시작점
			m_pImageInfo->nFrameWidth*scale,
			m_pImageInfo->nFrameHeight*scale,	// 복사될 크기

									// 대상
			m_pImageInfo->hMemDC,	// 복사할 대상 DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// 복사될 영역 시작좌표
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// 복사될 영역지정 좌표

			m_transColor);			// 복사에서 제외할 색상
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
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			SRCCOPY);

		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC를 출력해야되는 DC에 복사
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
			// 복사할 목표
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 복사할 대상
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
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC를 출력해야되는 DC에 복사
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
			// 복사할 목표
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// 복사할 대상
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
		// 1. 출력해야되는 DC에 그려져있는 내용을 blendImage에 복사
		BitBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			sourWidth , sourHeight ,

			// 대상
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. 출력할 이미지를 blendImage에 복사
		GdiTransparentBlt(
			// 목적지
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// 대상
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC를 출력해야되는 DC에 복사
		AlphaBlend(
			// 목적지
			hdc,
			destX, destY,
			sourWidth , sourHeight,

			// 대상
			m_pBlendImage->hMemDC,
			sourX, sourY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// 복사할 목표
			hdc,
			destX, destY,
			sourWidth  , sourHeight,
			// 복사할 대상
			m_pImageInfo->hMemDC,
			sourX, sourY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::rotateRender(HDC hdc, float rotateAngle, float fX, float fY, float anchorX/*0.5*/, float anchorY/*0.5*/, int scalar/*=1*/)
{

	// 현재 각도를 라디안값으로 변환
	float theta = rotateAngle * PI / 180.0f;

	// sin, cos값 구하기
	float s = sinf(theta);
	float c = cosf(theta);

	float fAncherX = anchorX; // 앵커들은 회전의 기준이 됨 그러나 이번 프로젝트에선 가운데를 기준으로 회전만 하기 떄문에 0.5로 고정값을 해놓음
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



		// 2. 출력할 이미지를 blendImage에 복사
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
