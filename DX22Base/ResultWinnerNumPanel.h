#pragma once
#include "Image2D.h"
#include "Calculation.h"

class ResultWinnerNumPanel : public Image2D
{
private:
	const CVector2 m_DefaultSize = CVector2(400.0f, 151.0f);
	const CVector2 m_StartSize = m_DefaultSize * 1.3f;

public:
	ResultWinnerNumPanel();
	~ResultWinnerNumPanel() override;
	void Update() override;

	void SetPanelImage(int PlayerNum);
	void DrawStart(float MoveEndTime);

private:
	bool		m_isDrawStart = false;
	float		m_CountTime = 0.0f;
	float		m_MoveEndTime = 0.0f;
};
