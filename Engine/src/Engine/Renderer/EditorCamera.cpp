#include "wbpch.h"
#include "EditorCamera.h"

#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCode.h"

#include "Engine/Event/KeyEvent.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Workbench
{
	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip),
		 ProjectionCamera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip), ProjectionType::Perspective)
	{
		UpdateView();
	}
	
	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		
		SetProjection(glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip));
	}
	
	void EditorCamera::UpdateView()
	{
		m_Position = CalculatePosition();
		
		glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	void EditorCamera::OnUpdate(Timestep ts)
	{
		if (Input::KeyPressed(WB_KEY_LEFT_ALT))
		{
			const glm::vec2& position { Input::GetMouseX(), Input::GetMouseY() };
			glm::vec2 delta = (position - m_MousePosition) * 0.003f;
			m_MousePosition = position;

			if (Input::MouseButtonPressed(WB_MOUSE_BUTTON_3))
				MousePan(delta);
			else if (Input::MouseButtonPressed(WB_MOUSE_BUTTON_LEFT))
				MouseRotate(delta);
			else if (Input::MouseButtonPressed(WB_MOUSE_BUTTON_RIGHT))
				MouseZoom(delta.y);
		}

		UpdateView();
	}

	void EditorCamera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrollEvent>(WB_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	bool EditorCamera::OnMouseScroll(MouseScrollEvent& event)
	{
		float delta = event.GetScrollYOffset() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}

	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += -GetRightDirection() * delta.x * xSpeed, m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
	}

	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * RotationSpeed();
		m_Pitch += delta.y * RotationSpeed();
	}

	void EditorCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.0f) // TODO: Clamp m_Distance minimum to 1.0f
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.f);
		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f

		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return std::pair(xFactor, yFactor);
	}

	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f);
		return speed;
	}

	glm::vec3 EditorCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

	glm::vec3 EditorCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	
	glm::vec3 EditorCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}
}