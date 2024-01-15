#pragma once


class SceneGame_EndState
{
public:
	SceneGame_EndState() {};
	~SceneGame_EndState() override {};

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};