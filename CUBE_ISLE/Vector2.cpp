#include "stdafx.h"
#include "Vector2.h"

// ���� ���
float Vector2::dot(const Vector2& other) const {
	return (x*other.x) + (y*other.y);
}

// ���� ���
// ������ ���ʹ� z��ǥ�� 0�� 3���� ���ͷ� ������ �� �ֱ� ������ 2���� ���Ϳ� ���ؼ��� ������ ������ �� �ֽ��ϴ�.
float Vector2::cross(const Vector2& other) const {
	return(x*other.y) - (y*other.x);
}

//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
float Vector2::ccw(const Vector2& b) {
	return this->cross(b);
}

// ���� ���
float Vector2::length() const {
	return std::sqrt(dot(*this));
}

// �Ÿ� ���
float Vector2::distance(const Vector2& other) const {
	return std::sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

// ����ȭ
Vector2 Vector2::normalize() const {
	const float len = length();
	if (len < FLT_EPSILON)
		return Vector2::ZERO;
	return *this / len;
}

// ���� �������� Ȯ��
bool Vector2::isZero() const {
	return *this == Vector2::ZERO;
}

// ����� ��(cpp ���Ͽ� �ۼ�)
const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::LEFT(-1.0f, 0.0f);
const Vector2 Vector2::RIGHT(1.0f, 0.0f);
const Vector2 Vector2::UP(0.0f, -1.0f);
const Vector2 Vector2::DOWN(0.0f, 1.0f);
