#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <sys\stat.h>

#define  Assert( _exp )										((void)0)

typedef float vec_t;
typedef float vec2_t[2];
typedef float vec3_t[3];

class Matrix3x4
{
public:
	float* operator[](int i)
	{
		return m[i];
	}

	const float* operator[](int i) const
	{
		return m[i];
	}

public:
	float m[3][4];
};

class Matrix4x4
{
public:
	float* operator[](int i)
	{
		return m[i];
	}

	const float* operator[](int i) const
	{
		return m[i];
	}

public:
	float m[4][4];
};

struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}

	float *operator[](int i) { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	const float *operator[](int i) const { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	float *Base() { return &m_flMatVal[0][0]; }
	const float *Base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};

class QAngleByValue;

class QAngle
{
public:
	vec_t x, y, z;

	QAngle(void);
	QAngle(vec_t X, vec_t Y, vec_t Z);

	operator QAngleByValue &() { return *((QAngleByValue *)(this)); }
	operator const QAngleByValue &() const { return *((const QAngleByValue *)(this)); }

	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);
	void Random(vec_t minVal, vec_t maxVal);

	bool IsValid() const;

	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	vec_t* Base();
	vec_t const* Base() const;

	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;

	QAngle&	operator+=(const QAngle &v);
	QAngle&	operator-=(const QAngle &v);
	QAngle&	operator*=(float s);
	QAngle&	operator/=(float s);

	vec_t	Length() const;
	vec_t	LengthSqr() const;

	QAngle& operator=(const QAngle& src);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	QAngle	operator-(void) const;

	QAngle	operator+(const QAngle& v) const;
	QAngle	operator-(const QAngle& v) const;
	QAngle	operator*(float fl) const;
	QAngle	operator/(float fl) const;
#else

private:
	QAngle(const QAngle& vOther);

#endif
};

class QAngleByValue : public QAngle
{
public:
	QAngleByValue(void) : QAngle() {}
	QAngleByValue(vec_t X, vec_t Y, vec_t Z) : QAngle(X, Y, Z) {}
	QAngleByValue(const QAngleByValue& vOther) { *this = vOther; }
};

class Vector2
{
public:
	Vector2(void)
	{
		x = y = 0.0f;
	}

	Vector2(float X, float Y)
	{
		x = X; y = Y;
	}

	Vector2(float* v)
	{
		x = v[0]; y = v[1];
	}

	Vector2(const float* v)
	{
		x = v[0]; y = v[1];
	}

	Vector2(const Vector2& v)
	{
		x = v.x; y = v.y;
	}

	Vector2& operator=(const Vector2& v)
	{
		x = v.x; y = v.y; return *this;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	Vector2& operator+=(const Vector2& v)
	{
		x += v.x; y += v.y; return *this;
	}

	Vector2& operator-=(const Vector2& v)
	{
		x -= v.x; y -= v.y; return *this;
	}

	Vector2& operator*=(const Vector2& v)
	{
		x *= v.x; y *= v.y; return *this;
	}

	Vector2& operator/=(const Vector2& v)
	{
		x /= v.x; y /= v.y; return *this;
	}

	Vector2& operator+=(float v)
	{
		x += v; y += v; return *this;
	}

	Vector2& operator-=(float v)
	{
		x -= v; y -= v; return *this;
	}

	Vector2& operator*=(float v)
	{
		x *= v; y *= v; return *this;
	}

	Vector2& operator/=(float v)
	{
		x /= v; y /= v; return *this;
	}

	Vector2 operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 operator*(const Vector2& v) const
	{
		return Vector2(x * v.x, y * v.y);
	}

	Vector2 operator/(const Vector2& v) const
	{
		return Vector2(x / v.x, y / v.y);
	}

	Vector2 operator+(float v) const
	{
		return Vector2(x + v, y + v);
	}

	Vector2 operator-(float v) const
	{
		return Vector2(x - v, y - v);
	}

	Vector2 operator*(float v) const
	{
		return Vector2(x * v, y * v);
	}

	Vector2 operator/(float v) const
	{
		return Vector2(x / v, y / v);
	}

	void Set(float X = 0.0f, float Y = 0.0f)
	{
		x = X; y = Y;
	}

	float Length(void) const
	{
		return sqrtf(x * x + y * y);
	}

	float LengthSqr(void) const
	{
		return (x * x + y * y);
	}


	float DistTo(const Vector2& v) const
	{
		return (*this - v).Length();
	}

	float DistToSqr(const Vector2& v) const
	{
		return (*this - v).LengthSqr();
	}

	float Dot(const Vector2& v) const
	{
		return (x * v.x + y * v.y);
	}

	bool IsZero(void) const
	{
		return (x > -0.01f && x < 0.01f &&
			y > -0.01f && y < 0.01f);
	}

public:
	float x, y;
};


class Vector
{
public:
	vec_t x, y, z;

	Vector(void);
	Vector(vec_t X, vec_t Y, vec_t Z);
	explicit Vector(vec_t XYZ);

	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);

	bool IsValid() const;
	void Invalidate();

	vec_t   operator[](int i) const;
	vec_t&  operator[](int i);

	vec_t* Base();
	vec_t const* Base() const;

	inline void Zero();

	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	FORCEINLINE Vector& operator+=(const Vector& v);
	FORCEINLINE Vector& operator-=(const Vector& v);
	FORCEINLINE Vector& operator*=(const Vector& v);
	FORCEINLINE Vector& operator*=(float s);
	FORCEINLINE Vector& operator/=(const Vector& v);
	FORCEINLINE Vector& operator/=(float s);
	FORCEINLINE Vector& operator+=(float fl);
	FORCEINLINE Vector& operator-=(float fl);

	operator float *() { return &x; }
	operator const float *() const { return &x; }

	void Negate();

	inline vec_t Length() const;

	FORCEINLINE vec_t LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	vec_t NormalizeInPlace();
	float NormalizeInPlace1();
	Vector Normalized() const;

	bool IsLengthGreaterThan(float val) const;
	bool IsLengthLessThan(float val) const;

	FORCEINLINE bool WithinAABox(Vector const &boxmin, Vector const &boxmax);

	vec_t DistTo(const Vector& vOther) const;

	FORCEINLINE vec_t DistToSqr(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}

	void CopyToArray(float* rgfl) const;
	void MulAdd(const Vector& a, const Vector& b, float scalar);

	vec_t Dot(const Vector& vOther) const;

	Vector& operator=(const Vector& vOther);

	vec_t Length2D(void) const;
	vec_t Length2DSqr(void) const;

	Vector operator-(void) const;
	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector operator*(const Vector& v) const;
	Vector operator/(const Vector& v) const;
	Vector operator*(float fl) const;
	Vector operator/(float fl) const;

	Vector Cross(const Vector& vOther) const;

	Vector Min(const Vector& vOther) const;
	Vector Max(const Vector& vOther) const;

	void Set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
	{
		x = X; y = Y; z = Z;
	}
};

class Vector3
{
public:
	Vector3(void)
	{
		x = y = z = 0.0f;
	}

	Vector3(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	Vector3(float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vector3(const float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vector3(const Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}

	Vector3(const Vector2& v)
	{
		x = v.x; y = v.y; z = 0.0f;
	}

	Vector3& operator=(const Vector3& v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	Vector3& operator=(const Vector2& v)
	{
		x = v.x; y = v.y; z = 0.0f; return *this;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	Vector3& operator+=(const Vector3& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	Vector3& operator*=(const Vector3& v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	Vector3& operator/=(const Vector3& v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	Vector3& operator+=(float v)
	{
		x += v; y += v; z += v; return *this;
	}

	Vector3& operator-=(float v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	Vector3& operator*=(float v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	Vector3& operator/=(float v)
	{
		x /= v; y /= v; z /= v; return *this;
	}

	Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(const Vector3& v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	Vector3 operator/(const Vector3& v) const
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}

	Vector3 operator+(float v) const
	{
		return Vector3(x + v, y + v, z + v);
	}

	Vector3 operator-(float v) const
	{
		return Vector3(x - v, y - v, z - v);
	}

	Vector3 operator*(float v) const
	{
		return Vector3(x * v, y * v, z * v);
	}

	Vector3 operator/(float v) const
	{
		return Vector3(x / v, y / v, z / v);
	}

	void Set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
	{
		x = X; y = Y; z = Z;
	}

	float Length(void) const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	float Length2d(void) const
	{
		return sqrtf(x * x + y * y);
	}

	float Length2dSqr(void) const
	{
		return (x * x + y * y);
	}

	float DistTo(const Vector3& v) const
	{
		return (*this - v).Length();
	}

	float DistToSqr(const Vector3& v) const
	{
		return (*this - v).LengthSqr();
	}

	float Dot(const Vector3& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	Vector3 Cross(const Vector3& v) const
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	bool IsZero(void) const
	{
		return (x > -0.01f && x < 0.01f &&
			y > -0.01f && y < 0.01f &&
			z > -0.01f && z < 0.01f);
	}

public:
	float x, y, z;
};

FORCEINLINE Vector3 operator*(float f, const Vector3& v)
{
	return v * f;
}