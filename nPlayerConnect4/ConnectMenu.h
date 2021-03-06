#ifndef CONNECTMENU_H
#define CONNECTMENU_H

#include <freetype.h>
#include <Button.h>
#include "Fonts.h"
#include "ImageLoder.h"
#include "ScreenCoord.h"
#include "FontInfo.h"
#include <TextInput.h>

class ConnectMenu
{
private:
	GLuint m_menuTex;

	TextInfo connectText;
	TextInfo hostText;

	Game2D::Button backButton;
	Game2D::Button connectButton;

	//std::string address;
	//std::string port;

	Game2D::TextInput address;
	Game2D::TextInput port;

	bool isHost;
protected:
public:
	ConnectMenu();

	inline void setHost(bool host) { isHost = host; }

	void init();

	void resize();

	void update();
	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);
	void processCodepoint(unsigned int codepoint);
	void backspace() { address.backspace(); port.backspace(); };

	std::string getAddress() const { return address.getText(); }
	uint16_t getPort() const { return std::stoul(port.getText()); }
	bool getHost() const { return isHost; }


	void draw();
};


#endif //CONNECTMENU_H
