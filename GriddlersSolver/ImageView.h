#pragma once
#include <vector>
using namespace std;

class ImageView
{
public:
    ImageView();
    virtual ~ImageView();
    
    // A handle to the window whose DC is to be released.
    HWND hwnd;

    CWnd* m_control;
    void SetImage(CImage& image);
};