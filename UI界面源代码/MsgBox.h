#pragma once
#include "BasicWidget.h"
#include "PushButton.h"
#include <string>
#include"Timer.h"
class MsgBox : public BasicWidget
{
public:
	MsgBox(int x = 300, int y = 200, int w = 400, int h = 200);
	void setMessage(const std::string& msg);
	void show() override;
	void eventLoop(const ExMessage& msg);
	bool isVisible() const;
	void hide();
	PushButton m_okBtn;

private:
	std::string m_message;
	bool m_visible;
};
