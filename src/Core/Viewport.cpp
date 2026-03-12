#include "Viewport.h"
#include <glad/glad.h>

Viewport::Viewport()
	:
	m_X(0), m_Y(0), m_W(640), m_H(480)
{}

Viewport::Viewport(int x, int y, int w, int h)
	:
	m_X(x), m_Y(y), m_W(w), m_H(h)
{}

void Viewport::Update(int x, int y, int w, int h)
{
	m_X = x;
	m_Y = y;
	m_W = w;
	m_H = h;

	glViewport(m_X, m_Y, m_W, m_H);
}

float Viewport::GetAspectRatio() const
{
	return static_cast<float>(m_W) / static_cast<float>(m_H);
}

int Viewport::GetX() const
{
	return m_X;
}

int Viewport::GetY() const
{
	return m_Y;
}

int Viewport::GetW() const
{
	return m_W;
}

int Viewport::GetH() const
{
	return m_H;
}
