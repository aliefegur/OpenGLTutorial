#pragma once

#include <glm/mat4x4.hpp>

class OrthographicCamera
{
public:
	OrthographicCamera();

	void Update(float aspectRatio);

	const glm::mat4& GetCombinedMatrix() const;
	const glm::vec3& GetPosition() const;
	float GetRotation() const;
	float GetNear() const;
	float GetFar() const;

	void Translate(const glm::vec3& translation);
	void Rotate(float angle);
	void SetPosition(const glm::vec3& position);
	void SetRotation(float rotation);
	void SetNear(float near);
	void SetFar(float far);

private:
	glm::mat4 m_ViewProjectionMatrix;
	glm::vec3 m_Position;
	float m_Rotation;
	float m_Near;
	float m_Far;
	float m_Size;
};
