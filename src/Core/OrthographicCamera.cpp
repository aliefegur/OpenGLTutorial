#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera()
	:
	m_ViewProjectionMatrix(glm::mat4(1.0f)),
	m_Position(glm::vec3(0.0f)),
	m_Rotation(0.0f),
	m_Near(0.1f),
	m_Far(100.0f),
	m_Size(5.0f)
{}

void OrthographicCamera::Update(float aspectRatio)
{
	glm::mat4 viewMatrix = glm::translate(glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), { 0.0f, 0.0f, -1.0f }), -m_Position);
	glm::mat4 projectionMatrix = glm::ortho(
		-m_Size * aspectRatio / 2.0f,
		 m_Size * aspectRatio / 2.0f,
		-m_Size,
		 m_Size
	);
	
	m_ViewProjectionMatrix = projectionMatrix * viewMatrix;
}

const glm::mat4& OrthographicCamera::GetCombinedMatrix() const
{
	return m_ViewProjectionMatrix;
}

const glm::vec3& OrthographicCamera::GetPosition() const
{
	return m_Position;
}

float OrthographicCamera::GetRotation() const
{
	return m_Rotation;
}

float OrthographicCamera::GetNear() const
{
	return m_Near;
}

float OrthographicCamera::GetFar() const
{
	return m_Far;
}

void OrthographicCamera::Translate(const glm::vec3& translation)
{
	m_Position += translation;
}

void OrthographicCamera::Rotate(float angle)
{
	m_Rotation += angle;
}

void OrthographicCamera::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void OrthographicCamera::SetRotation(float rotation)
{
	m_Rotation = rotation;
}

void OrthographicCamera::SetNear(float near)
{
	m_Near = near;
}

void OrthographicCamera::SetFar(float far)
{
	m_Far = far;
}
