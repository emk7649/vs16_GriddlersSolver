#include "pch.h"
#include "ImageView.h"
#include <Algorithm>

ImageView::ImageView()
    : hwnd(NULL)
    , m_control(nullptr)
{
}

ImageView::~ImageView()
{
}

void ImageView::SetImage(CImage& image)
{
    //if (m_rect.IsRectEmpty() || m_rect.IsRectNull())
    //    return;
    if (hwnd == NULL)
        return;
    if (m_control == nullptr)
        return;

    m_control->GetWindowRect(m_rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.

    CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
    dc = m_control->GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
    //image.Load(_T("5.bmp"));//이미지 로드

    image.StretchBlt(dc->m_hDC, 0, 0, m_rect.Width(), m_rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
    ReleaseDC(hwnd, dc->m_hDC);//DC 해제
}