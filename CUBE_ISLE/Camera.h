#pragma once
#include "stdafx.h"

class Camera
{
public:
	Vector3 m_pos{ 0.f, 0.f, 1.0f }; // 카메라 위치 
	Vector3 m_at{ 0.f, 0.f, 0.f }; // at
	Vector3 m_up{ 0.f, 1.f, 0.f };

	float m_distance{ 0 };	// zoom

	float m_vertical{ 0 };	// ↕ 회전각
	float m_horizontal{ 0 };	// ↔ 회전각

	float m_aspect{ 0 };
	float m_near{ 0.f };
	float m_far{ 1.f };
	float m_fovy{ 0 };

public:
	Camera()
		// 카메라 생성 시 최초 1회는 aspect를 자동으로 설정한다.
		: m_aspect{ (float)WIDTH / (float)HEIGHT }
	{
	}

	~Camera() = default;

	void Initialize()
	{
		m_distance = 610.f;
		m_at = { 0.f, 0.f, 0.f };
		m_vertical = 0;
		m_horizontal = 0;
		m_pos = eye();
		m_up = { 0.f, 1.f, 0.f };

		LookAt();
	}

	void Initialize(const Vector3 & at, float distance, float zNear, float zFar, float fov)
	{
		m_fovy = fov;
		m_near = zNear;
		m_far = zFar;
		m_distance = distance;
		m_at = at;
		m_pos = eye();
		m_up = { 0.f, 1.f, 0.f };

		LookAt();
	}

	void SetAspect(float aspect) { m_aspect = aspect; }
	Vector3 GetAtPos()	const { return m_at; }

	void SetAtPos(const Vector3& pos) { m_at = pos; LookAt(); }
	void SetAtPos(Vector3&& pos)	noexcept { m_at = std::move(pos); LookAt(); }

	void Move(const Vector3& pos)	noexcept { SetAtPos(m_at + pos); }
	void Move(Vector3&& pos)		noexcept { SetAtPos(m_at + std::move(pos)); }

	void SetDistance(const float& d) { m_distance = fmax(d, m_near); }
	float GetDistance() const { return m_distance; }

	void zoom(float distance) {
		//m_distance = m_distance * per;
		m_distance = m_distance + distance;
		m_pos = eye();
		LookAt();
	}

	void Rotate(float v, float h)
	{
		m_vertical += v;
		if (-PIE * 0.5f < m_horizontal + h && m_horizontal + h < PIE * 0.5f)
			m_horizontal += h;
		m_pos = eye();

		LookAt();
	}

	// projection 설정
	void LookAt() const
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(m_fovy, m_aspect, m_near, m_far);

		gluLookAt(
			m_pos.x, m_pos.y, m_pos.z,
			m_at.x, m_at.y, m_at.z,
			m_up.x, m_up.y, m_up.z
		);

		glMatrixMode(GL_MODELVIEW);
	}

	// at에서 카메라 위치를 보는 방향
	Vector3 GetBackLookVector() const
	{
		// 초기값이 0,0,1인데?
		return Vector3
		{
			cos(m_horizontal) * sin(m_vertical),
			sin(m_horizontal),
			cos(m_horizontal) * cos(m_vertical)
		}.normalize();
	}

	void SetFpvPosition(const Vector3& at, const Vector3& up = {0,1,0}) {
		m_distance = 50;
		m_at = at;
		m_up = up;

		m_pos = eye();

		LookAt();
	}

	Vector3 eye() const { return GetBackLookVector() * m_distance + GetAtPos(); }
};
