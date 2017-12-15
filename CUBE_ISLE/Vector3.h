#pragma once

// 3D ���� Ŭ����
class Vector3 {
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float arr[3];
	};
	float* operator&()
	{
		return arr;
	}

	// ������
	Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

	// ���� ���
	float dot(const Vector3& other) const;

	// ���� ���
	Vector3 cross(const Vector3& other) const;

	// ���� ���
	float length() const;

	// ����ȭ
	Vector3 normalize() const;

	// ���� �������� Ȯ��
	bool isZero() const;

	// �ݴ���⺤��
	Vector3 flip();

	// ������ �����ε�
	Vector3& operator += (const Vector3& other) {
		return *this = *this + other;
	}

	Vector3& operator -= (const Vector3& other) {
		return *this = *this - other;
	}

	Vector3& operator *= (float scalar) {
		return *this = *this * scalar;
	}

	Vector3& operator /= (float scalar) {
		return *this = *this / scalar;
	}

	const Vector3 operator + (const Vector3& other) const {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	const Vector3 operator - (const Vector3& other) const {
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	const Vector3 operator + (float scalar) const {
		return Vector3(x + scalar, y + scalar, z + scalar);
	}

	const Vector3 operator - (float scalar) const {
		return Vector3(x - scalar, y - scalar, z - scalar);
	}

	const Vector3 operator * (float scalar) const {
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	const Vector3 operator / (float scalar) const {
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	const Vector3 operator - () const {
		return Vector3(-x, -y, -z);
	}

	bool operator == (const Vector3& other) const {
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool operator != (const Vector3& other) const {
		return !(*this == other);
	}

	bool operator < (const Vector3& other) const {
		if (x != other.x) return x < other.x;
		if (y != other.y) return y < other.y;
		if (z != other.z) return z < other.z;
		return false;
	}

	// ���
	static const Vector3 ZERO;
	static const Vector3 LEFT;
	static const Vector3 RIGHT;
	static const Vector3 DOWN;
	static const Vector3 UP;
};
