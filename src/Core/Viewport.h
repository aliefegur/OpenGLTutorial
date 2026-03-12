#pragma once

class Viewport
{
public:
	Viewport();
	Viewport(int x, int y, int w, int h);

	void Update(int x, int y, int w, int h);

	float GetAspectRatio() const;

	int GetX() const;
	int GetY() const;
	int GetW() const;
	int GetH() const;

private:
	int	m_X,
		m_Y,
		m_W,
		m_H;
};
