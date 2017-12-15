#include "stdafx.h"
#include "Vector3.h"

// ���� ���
float Vector3::dot(const Vector3& other) const {
	return (x*other.x) + (y*other.y) + (z*other.z);
}

// ���� ���
Vector3 Vector3::cross(const Vector3& other) const {
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

// ���� ���
float Vector3::length() const {
	return std::sqrt(dot(*this));
}

// ����ȭ
Vector3 Vector3::normalize() const {
	const float len = length();
	if (len < FLT_EPSILON)
		return Vector3::ZERO;
	return *this / len;
}

// ���� �������� Ȯ��
bool Vector3::isZero() const {
	return *this == Vector3::ZERO;
}

Vector3 Vector3::flip() {
	return Vector3{ -x, -y, -z };
}

// ����� ��(cpp ���Ͽ� �ۼ�)
const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::LEFT(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::RIGHT(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UP(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::DOWN(0.0f, 1.0f, 0.0f);
