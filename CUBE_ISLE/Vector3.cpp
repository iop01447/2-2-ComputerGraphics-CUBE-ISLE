#include "stdafx.h"
#include "Vector3.h"

// 내적 계산
float Vector3::dot(const Vector3& other) const {
	return (x*other.x) + (y*other.y) + (z*other.z);
}

// 외적 계산
Vector3 Vector3::cross(const Vector3& other) const {
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

// 길이 계산
float Vector3::length() const {
	return std::sqrt(dot(*this));
}

// 정규화
Vector3 Vector3::normalize() const {
	const float len = length();
	if (len < FLT_EPSILON)
		return Vector3::ZERO;
	return *this / len;
}

// 제로 벡터인지 확인
bool Vector3::isZero() const {
	return *this == Vector3::ZERO;
}

Vector3 Vector3::flip() {
	return Vector3{ -x, -y, -z };
}

// 상수의 값(cpp 파일에 작성)
const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::LEFT(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::RIGHT(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UP(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::DOWN(0.0f, 1.0f, 0.0f);
