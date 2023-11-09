//#pragma once
#ifndef _GAMEUI_H_
#define _GAMEUI_H_
#include "DirectX.h"

class GameUI
{
public :
	GameUI();
	~GameUI();
	void Draw();

private:
	ID3D11ShaderResourceView* m_pNazoBar;
};

#endif // !_GAMEUI_H_
