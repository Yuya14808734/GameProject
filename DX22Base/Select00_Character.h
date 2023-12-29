#pragma once

class SelectCharacter
{
public:
	enum class CHARACTER : int
	{
		UNITYCHAN = 0,
		MAX
	};

public:
	SelectCharacter();
	~SelectCharacter();
	void Update();
	void Draw();

private:

};