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

	Game2D::TextInput address;
	Game2D::TextInput port;

	bool isHost;
	std::string errorMessage;
	float errorMessageWidth;
protected:
public:
	ConnectMenu();

	void setHost(bool host);

	void init();

	void resize();

	void update();
	int processMouse(Game2D::Pos2 mousePos, Game2D::KeyState::State mouseState);
	void processCodepoint(unsigned int codepoint);
	void backspace() { address.backspace(); port.backspace(); };

	std::string getAddress() const { return address.getText(); }
	uint16_t getPort() const { return std::stoul(port.getText()); }
	bool getHost() const { return isHost; }

	void setErrorMessage(std::string message);
	inline void clearErrorMessage() { errorMessage.clear(); errorMessageWidth = 0; }


	void draw();
};


#endif //CONNECTMENU_H
