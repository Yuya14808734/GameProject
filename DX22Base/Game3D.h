#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include "Model.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "BlendState.h"
#include "GAMEUI.h"
#include "Scene.h"

class Game3D
{
public:
	Game3D();
	~Game3D();
	void Update();
	void Draw();

private:
	ConstantBuffer* m_pWVP;
	BlendState* m_pBlend;
};

#endif // __GAME_3D_H__