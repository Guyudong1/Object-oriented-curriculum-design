#pragma once
#include "BasicWidget.h"
#include"configure.h"
class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string& text="Button",int x = 0, int y = 0, int w = 100, int h = 30);
    void show() override;
    bool isin();        //�ж�����Ƿ��ڵ�ǰ��ť��
    bool isClicked();
    void hide();

    void eventLoop(const ExMessage& msg);       //���m_msg��
    void setBackgroundColor(COLORREF c);
    void setHoverColor(COLORREF c);


private:
    std::string m_text;
    ExMessage m_msg;
    bool m_visible = true;
    COLORREF normal_c = RGB(232, 232, 236);
    COLORREF hover_c = RGB(250, 174, 201);
    COLORREF cur_c = RGB(232, 232, 236);
};

