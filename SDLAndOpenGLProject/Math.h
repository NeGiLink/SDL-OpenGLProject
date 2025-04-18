#pragma once
#include "STD.h"

namespace Math
{
	const float Pi = 3.1415926535f;
	const float TwoPi = Pi * 2.0f;
	const float PiOver2 = Pi / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Acos(float value)
	{
		return acosf(value);
	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float Fmod(float numer, float denom)
	{
		return fmod(numer, denom);
	}
}

// 2D Vector
class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		, y(0.0f)
	{
	}

	explicit Vector2(float inX, float inY)
		:x(inX)
		, y(inY)
	{
	}

	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// 両方のコンポーネントを1行に設定
	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	// ベクトル加算（a + b）
	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	// ベクトル減算（a - b）
	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	// 要素ごとの乗算
	// (a.x * b.x, ...)
	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	// スカラー乗算
	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	// スカラー乗算
	friend Vector2 operator*(float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	// Scalar *=
	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	// Vector +=
	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	// Vector -=
	Vector2& operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	// ベクトルの長さの二乗
	float LengthSq() const
	{
		return (x * x + y * y);
	}

	// ベクトルの長さ
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// ベクトルを正規化
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	// 渡されたベクトルを正規化
	static Vector2 Normalize(const Vector2& vec)
	{
		Vector2 temp = vec;
		temp.Normalize();
		return temp;
	}

	// 二つのベクトル間のドット積（a・b）
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x + a.y * b.y);
	}

	// AからBへfによって線形補間
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
	{
		return Vector2(a + f * (b - a));
	}

	// N（正規化された）について反射
	static Vector2 Reflect(const Vector2& v, const Vector2& n)
	{
		return v - 2.0f * Vector2::Dot(v, n) * n;
	}

	// 行列によってベクトルを変換する
	static Vector2 Transform(const Vector2& vec, const class Matrix3& mat, float w = 1.0f);

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};

// 3D Vector
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
		:x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{
	}

	explicit Vector3(float inX, float inY, float inZ)
		:x(inX)
		, y(inY)
		, z(inZ)
	{
	}

	// const float ポインタにキャスト
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// すべての三つのコンポーネントを1行に設定
	void Set(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}

	// ベクトル加算（a + b）
	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	// ベクトル減算（a - b）
	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	// 要素ごとの乗算
	friend Vector3 operator*(const Vector3& left, const Vector3& right)
	{
		return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	// スカラー乗算
	friend Vector3 operator*(const Vector3& vec, float scalar)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	friend Vector3 operator/(const Vector3& vec, float scalar)
	{
		return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
	}

	// スカラー乗算
	friend Vector3 operator*(float scalar, const Vector3& vec)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Scalar *=
	Vector3& operator*=(Vector3 scalar)
	{
		x *= scalar.x;
		y *= scalar.y;
		z *= scalar.z;
		return *this;
	}

	Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// Vector +=
	Vector3& operator+=(const Vector3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	// Vector -=
	Vector3& operator-=(const Vector3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	// ベクトルの長さの二乗
	float LengthSq() const
	{
		return (x * x + y * y + z * z);
	}

	// ベクトルの長さ
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// ベクトルの正規化
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	// 渡されたベクトルを正規化
	static Vector3 Normalize(const Vector3& vec)
	{
		Vector3 temp = vec;
		temp.Normalize();
		return temp;
	}

	// 二つのベクトル間のドット積（a・b）
	static float Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	// 二つのベクトルのクロス積（a × b）
	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		Vector3 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		return temp;
	}

	// AからBへfによって線形補間
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
	{
		return Vector3(a + f * (b - a));
	}

	// N（正規化された）について反射する
	static Vector3 Reflect(const Vector3& v, const Vector3& n)
	{
		return v - 2.0f * Vector3::Dot(v, n) * n;
	}

	// 成分ごとのMin
	static Vector3 Min(const Vector3& a, const Vector3& b)
	{
		return Vector3(
			std::min(a.x, b.x),
			std::min(a.y, b.y),
			std::min(a.z, b.z)
		);
	}

	// 成分ごとのMax
	static Vector3 Max(const Vector3& a, const Vector3& b)
	{
		return Vector3(
			std::max(a.x, b.x),
			std::max(a.y, b.y),
			std::max(a.z, b.z)
		);
	}

	static Vector3 Transform(const Vector3& vec, const class Matrix4& mat, float w = 1.0f);
	// ベクトルを変換、w成分が再正規化
	static Vector3 TransformWithPerspDiv(const Vector3& vec, const class Matrix4& mat, float w = 1.0f);

	// クォータニオンでベクトル3を変換
	static Vector3 Transform(const Vector3& v, const class Quaternion& q);

	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 UnitXYZ;
	static const Vector3 NegUnitX;
	static const Vector3 NegUnitY;
	static const Vector3 NegUnitZ;
	static const Vector3 Infinity;
	static const Vector3 NegInfinity;
};

// 4D Vector
class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4()
		:x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{
	}

	explicit Vector4(float inX, float inY, float inZ, float inW)
		:x(inX)
		, y(inY)
		, z(inZ)
		, w(inZ)
	{
	}

	// const float ポインタにキャスト
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// すべての三つのコンポーネントを1行に設定
	void Set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}

	// ベクトル加算（a + b）
	friend Vector4 operator+(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x + b.x, a.y + b.y, a.z + b.z,a.w + b.w);
	}

	// ベクトル減算 (a - b)
	friend Vector4 operator-(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	// 要素ごとの乗算
	friend Vector4 operator*(const Vector4& left, const Vector4& right)
	{
		return Vector4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
	}

	// スカラー乗算
	friend Vector4 operator*(const Vector4& vec, float scalar)
	{
		return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
	}

	// スカラー乗算
	friend Vector4 operator*(float scalar, const Vector4& vec)
	{
		return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
	}

	// Scalar *=
	Vector4& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	// Vector +=
	Vector4& operator+=(const Vector4& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	}

	// Vector -=
	Vector4& operator-=(const Vector4& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	}

	// ベクトルの長さの二乗
	float LengthSq() const
	{
		return (x * x + y * y + z * z + w * w);
	}

	// ベクトルの長さ
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// ベクトルを正規化
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	// 渡されたベクトルを正規化
	static Vector4 Normalize(const Vector4& vec)
	{
		Vector4 temp = vec;
		temp.Normalize();
		return temp;
	}

	// 二つのベクトル間のドット積（a・b）
	static float Dot(const Vector4& a, const Vector4& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
	}

	// AからBへfによって線形補間
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float f)
	{
		return Vector4(a + f * (b - a));
	}

	// N（正規化された）について反射
	static Vector4 Reflect(const Vector4& v, const Vector4& n)
	{
		return v - 2.0f * Vector4::Dot(v, n) * n;
	}

	static const Vector4 Zero;
	static const Vector4 UnitX;
	static const Vector4 UnitY;
	static const Vector4 UnitZ;
	static const Vector4 NegUnitX;
	static const Vector4 NegUnitY;
	static const Vector4 NegUnitZ;
	static const Vector4 Infinity;
	static const Vector4 NegInfinity;
};

// 3x3 Matrix
class Matrix3
{
public:
	float mat[3][3];

	Matrix3()
	{
		*this = Matrix3::Identity;
	}

	explicit Matrix3(float inMat[3][3])
	{
		memcpy(mat, inMat, 9 * sizeof(float));
	}

	// const floatポインタにキャスト
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// 行列の乗算
	friend Matrix3 operator*(const Matrix3& left, const Matrix3& right)
	{
		Matrix3 retVal;
		// row 0
		retVal.mat[0][0] =
			left.mat[0][0] * right.mat[0][0] +
			left.mat[0][1] * right.mat[1][0] +
			left.mat[0][2] * right.mat[2][0];

		retVal.mat[0][1] =
			left.mat[0][0] * right.mat[0][1] +
			left.mat[0][1] * right.mat[1][1] +
			left.mat[0][2] * right.mat[2][1];

		retVal.mat[0][2] =
			left.mat[0][0] * right.mat[0][2] +
			left.mat[0][1] * right.mat[1][2] +
			left.mat[0][2] * right.mat[2][2];

		// row 1
		retVal.mat[1][0] =
			left.mat[1][0] * right.mat[0][0] +
			left.mat[1][1] * right.mat[1][0] +
			left.mat[1][2] * right.mat[2][0];

		retVal.mat[1][1] =
			left.mat[1][0] * right.mat[0][1] +
			left.mat[1][1] * right.mat[1][1] +
			left.mat[1][2] * right.mat[2][1];

		retVal.mat[1][2] =
			left.mat[1][0] * right.mat[0][2] +
			left.mat[1][1] * right.mat[1][2] +
			left.mat[1][2] * right.mat[2][2];

		// row 2
		retVal.mat[2][0] =
			left.mat[2][0] * right.mat[0][0] +
			left.mat[2][1] * right.mat[1][0] +
			left.mat[2][2] * right.mat[2][0];

		retVal.mat[2][1] =
			left.mat[2][0] * right.mat[0][1] +
			left.mat[2][1] * right.mat[1][1] +
			left.mat[2][2] * right.mat[2][1];

		retVal.mat[2][2] =
			left.mat[2][0] * right.mat[0][2] +
			left.mat[2][1] * right.mat[1][2] +
			left.mat[2][2] * right.mat[2][2];

		return retVal;
	}

	Matrix3& operator*=(const Matrix3& right)
	{
		*this = *this * right;
		return *this;
	}

	// xおよびyスケールを持つスケール行列を作成
	static Matrix3 CreateScale(float xScale, float yScale)
	{
		float temp[3][3] =
		{
			{ xScale, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

	static Matrix3 CreateScale(const Vector2& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y);
	}

	// 均一な因子でスケール行列を作成
	static Matrix3 CreateScale(float scale)
	{
		return CreateScale(scale, scale);
	}

	// Z軸回りの回転行列を作成
	// シータはラジアンで表されます
	static Matrix3 CreateRotation(float theta)
	{
		float temp[3][3] =
		{
			{ Math::Cos(theta), Math::Sin(theta), 0.0f },
			{ -Math::Sin(theta), Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

	// xy平面上に翻訳行列を作成
	static Matrix3 CreateTranslation(const Vector2& trans)
	{
		float temp[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ trans.x, trans.y, 1.0f },
		};
		return Matrix3(temp);
	}

	static const Matrix3 Identity;
};

// (Unit) Quaternion
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		*this = Quaternion::Identity;
	}

	// これは四元数の成分を直接設定します -- 軸/角度には使用しない
	explicit Quaternion(float inX, float inY, float inZ, float inW)
	{
		Set(inX, inY, inZ, inW);
	}

	void Rotate(const Vector3& axis, float angle) 
	{
		float scalar = Math::Sin(angle / 2.0f);
		x = axis.x * scalar;
		y = axis.y * scalar;
		z = axis.z * scalar;
		w = Math::Cos(angle / 2.0f);
	}

	Vector3 Rotate(const Vector3& v) const
	{
		// q * v * q^-1 を使う方法
		Quaternion qv(v.x, v.y, v.z, 0.0f);
		Quaternion result = (*this) * qv * Inverse();
		return Vector3(result.x, result.y, result.z);
	}


	// 軸と角度からクォータニオンを構築します。
	// 軸はすでに正規化されていると仮定し、
	// 角度はラジアンで表されます。
	explicit Quaternion(const Vector3& axis, float angle)
	{
		Rotate(axis, angle);
	}

	// 内部コンポーネントを直接設定する
	void Set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}

	void Conjugate()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
	}

	float LengthSq() const
	{
		return (x * x + y * y + z * z + w * w);
	}

	float Length() const
	{
		return Math::Sqrt(LengthSq());
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	// 提供された四元数を正規化
	static Quaternion Normalize(const Quaternion& q)
	{
		Quaternion retVal = q;
		retVal.Normalize();
		return retVal;
	}

	// 線形補間
	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f)
	{
		Quaternion retVal;
		retVal.x = Math::Lerp(a.x, b.x, f);
		retVal.y = Math::Lerp(a.y, b.y, f);
		retVal.z = Math::Lerp(a.z, b.z, f);
		retVal.w = Math::Lerp(a.w, b.w, f);
		retVal.Normalize();
		return retVal;
	}

	static float Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	// 球面線形補間
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f)
	{
		float rawCosm = Quaternion::Dot(a, b);

		float cosom = -rawCosm;
		if (rawCosm >= 0.0f)
		{
			cosom = rawCosm;
		}

		float scale0, scale1;

		if (cosom < 0.9999f)
		{
			const float omega = Math::Acos(cosom);
			const float invSin = 1.f / Math::Sin(omega);
			scale0 = Math::Sin((1.f - f) * omega) * invSin;
			scale1 = Math::Sin(f * omega) * invSin;
		}
		else
		{
			// クォータニオンが共線である場合は、線形補間を使用。
			scale0 = 1.0f - f;
			scale1 = f;
		}

		if (rawCosm < 0.0f)
		{
			scale1 = -scale1;
		}

		Quaternion retVal;
		retVal.x = scale0 * a.x + scale1 * b.x;
		retVal.y = scale0 * a.y + scale1 * b.y;
		retVal.z = scale0 * a.z + scale1 * b.z;
		retVal.w = scale0 * a.w + scale1 * b.w;
		retVal.Normalize();
		return retVal;
	}

	// 連結
	// qで回転した後にpを続ける
	static Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
	{
		Quaternion retVal;

		// ベクトル成分:
		// ps * qv + qs * pv + pv x qv
		Vector3 qv(q.x, q.y, q.z);
		Vector3 pv(p.x, p.y, p.z);
		Vector3 newVec = p.w * qv + q.w * pv + Vector3::Cross(pv, qv);
		retVal.x = newVec.x;
		retVal.y = newVec.y;
		retVal.z = newVec.z;

		// スカラー成分:
		// ps * qs - pv . qv
		retVal.w = p.w * q.w - Vector3::Dot(pv, qv);

		return retVal;
	}

	// 四元数の逆行列を計算するメソッド
	Quaternion Inverse() const {
		// ノルムの2乗
		float normSquared = x * x + y * y + z * z + w * w;
		if (normSquared == 0) 
		{
			// ゼロ除算を防ぐため、逆行列は存在しないとする場合
			// もしくは例外を投げる等
			return Quaternion(0, 0, 0, 0);  
		}

		// 共役を取る（虚部を反転させる）
		return Quaternion(-x / normSquared, -y / normSquared, -z / normSquared, w / normSquared);
	}

	static Vector3 RotateVector(const Vector3 scale,const Quaternion& parent)
	{
		// ベクトルをクォータニオン形式に変換
		Quaternion qv = Quaternion(0, scale.x, scale.y, scale.z);
		// 回転を適用
		qv = parent * qv * parent.Inverse();
		// 回転後のベクトルを返す
		return Vector3(qv.x, qv.y, qv.z);
	}

	Vector3 RotateVector(const Vector3& v) const
	{
		// q * v * q^-1 を実装している
		Quaternion qv(v.x, v.y, v.z, 1.0f);
		Quaternion result = (*this) * qv * Inverse();
		return Vector3(result.x, result.y, result.z);
	}


	// 指定軸と角度で回転クォータニオンを作成して返す関数（角度は度数）
	static Quaternion CreateFromAxisAngle(const Vector3& axis, float angleDegrees)
	{
		// 角度をラジアンに変換
		float angleRadians = Math::ToRadians(angleDegrees);
		// axisが正規化されていることを前提にしているが、念のためNormalizeしてもOK
		Vector3 normAxis = Vector3::Normalize(axis);
		return Quaternion(normAxis, angleRadians);
	}

	// 自身の回転に、指定軸と角度の回転を追加する（角度は度数）
	void RotateByAxisAngle(const Vector3& axis, float angleDegrees)
	{
		float angleRadians = Math::ToRadians(angleDegrees);
		Quaternion deltaRot(axis, angleRadians); // 追加回転を生成
		*this = deltaRot * (*this);              // deltaRotを先に掛ける（後から回転）
	}

	static const Quaternion Identity;

	Quaternion& operator*=(const Quaternion& q)
	{
		float newX = w * q.x + x * q.w + y * q.z - z * q.y;
		float newY = w * q.y - x * q.z + y * q.w + z * q.x;
		float newZ = w * q.z + x * q.y - y * q.x + z * q.w;
		float newW = w * q.w - x * q.x - y * q.y - z * q.z;

		x = newX;
		y = newY;
		z = newZ;
		w = newW;

		return *this;
	}

	

	friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
	{
		return Quaternion(
			q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
			q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
			q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z
		);
	}
};
// 4x4 Matrix
class Matrix4
{
public:
	float mat[4][4];

	Matrix4()
	{
		*this = Matrix4::Identity;
	}

	explicit Matrix4(float inMat[4][4])
	{
		memcpy(mat, inMat, 16 * sizeof(float));
	}

	// const float ポインタにキャスト
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// 行列の掛け算 (a * b)
	friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
	{
		Matrix4 retVal;
		// row 0
		retVal.mat[0][0] =
			a.mat[0][0] * b.mat[0][0] +
			a.mat[0][1] * b.mat[1][0] +
			a.mat[0][2] * b.mat[2][0] +
			a.mat[0][3] * b.mat[3][0];

		retVal.mat[0][1] =
			a.mat[0][0] * b.mat[0][1] +
			a.mat[0][1] * b.mat[1][1] +
			a.mat[0][2] * b.mat[2][1] +
			a.mat[0][3] * b.mat[3][1];

		retVal.mat[0][2] =
			a.mat[0][0] * b.mat[0][2] +
			a.mat[0][1] * b.mat[1][2] +
			a.mat[0][2] * b.mat[2][2] +
			a.mat[0][3] * b.mat[3][2];

		retVal.mat[0][3] =
			a.mat[0][0] * b.mat[0][3] +
			a.mat[0][1] * b.mat[1][3] +
			a.mat[0][2] * b.mat[2][3] +
			a.mat[0][3] * b.mat[3][3];

		// row 1
		retVal.mat[1][0] =
			a.mat[1][0] * b.mat[0][0] +
			a.mat[1][1] * b.mat[1][0] +
			a.mat[1][2] * b.mat[2][0] +
			a.mat[1][3] * b.mat[3][0];

		retVal.mat[1][1] =
			a.mat[1][0] * b.mat[0][1] +
			a.mat[1][1] * b.mat[1][1] +
			a.mat[1][2] * b.mat[2][1] +
			a.mat[1][3] * b.mat[3][1];

		retVal.mat[1][2] =
			a.mat[1][0] * b.mat[0][2] +
			a.mat[1][1] * b.mat[1][2] +
			a.mat[1][2] * b.mat[2][2] +
			a.mat[1][3] * b.mat[3][2];

		retVal.mat[1][3] =
			a.mat[1][0] * b.mat[0][3] +
			a.mat[1][1] * b.mat[1][3] +
			a.mat[1][2] * b.mat[2][3] +
			a.mat[1][3] * b.mat[3][3];

		// row 2
		retVal.mat[2][0] =
			a.mat[2][0] * b.mat[0][0] +
			a.mat[2][1] * b.mat[1][0] +
			a.mat[2][2] * b.mat[2][0] +
			a.mat[2][3] * b.mat[3][0];

		retVal.mat[2][1] =
			a.mat[2][0] * b.mat[0][1] +
			a.mat[2][1] * b.mat[1][1] +
			a.mat[2][2] * b.mat[2][1] +
			a.mat[2][3] * b.mat[3][1];

		retVal.mat[2][2] =
			a.mat[2][0] * b.mat[0][2] +
			a.mat[2][1] * b.mat[1][2] +
			a.mat[2][2] * b.mat[2][2] +
			a.mat[2][3] * b.mat[3][2];

		retVal.mat[2][3] =
			a.mat[2][0] * b.mat[0][3] +
			a.mat[2][1] * b.mat[1][3] +
			a.mat[2][2] * b.mat[2][3] +
			a.mat[2][3] * b.mat[3][3];

		// row 3
		retVal.mat[3][0] =
			a.mat[3][0] * b.mat[0][0] +
			a.mat[3][1] * b.mat[1][0] +
			a.mat[3][2] * b.mat[2][0] +
			a.mat[3][3] * b.mat[3][0];

		retVal.mat[3][1] =
			a.mat[3][0] * b.mat[0][1] +
			a.mat[3][1] * b.mat[1][1] +
			a.mat[3][2] * b.mat[2][1] +
			a.mat[3][3] * b.mat[3][1];

		retVal.mat[3][2] =
			a.mat[3][0] * b.mat[0][2] +
			a.mat[3][1] * b.mat[1][2] +
			a.mat[3][2] * b.mat[2][2] +
			a.mat[3][3] * b.mat[3][2];

		retVal.mat[3][3] =
			a.mat[3][0] * b.mat[0][3] +
			a.mat[3][1] * b.mat[1][3] +
			a.mat[3][2] * b.mat[2][3] +
			a.mat[3][3] * b.mat[3][3];

		return retVal;
	}

	Matrix4& operator*=(const Matrix4& right)
	{
		*this = *this * right;
		return *this;
	}

	// 行列を反転させる
	void Invert();

	// 行列の翻訳成分を取得する
	Vector3 GetTranslation() const
	{
		return Vector3(mat[3][0], mat[3][1], mat[3][2]);
	}

	// 行列のX軸を取得する（前方）
	Vector3 GetXAxis() const
	{
		return Vector3::Normalize(Vector3(mat[0][0], mat[0][1], mat[0][2]));
	}

	// 行列のY軸を取得してください（左）
	Vector3 GetYAxis() const
	{
		return Vector3::Normalize(Vector3(mat[1][0], mat[1][1], mat[1][2]));
	}

	// 行列のZ軸を取得する（上）
	Vector3 GetZAxis() const
	{
		return Vector3::Normalize(Vector3(mat[2][0], mat[2][1], mat[2][2]));
	}

	// 行列からスケール成分を抽出
	Vector3 GetScale() const
	{
		Vector3 retVal;
		retVal.x = Vector3(mat[0][0], mat[0][1], mat[0][2]).Length();
		retVal.y = Vector3(mat[1][0], mat[1][1], mat[1][2]).Length();
		retVal.z = Vector3(mat[2][0], mat[2][1], mat[2][2]).Length();
		return retVal;
	}

	Quaternion GetRotation() const
	{
		Quaternion q;
		float trace = mat[0][0] + mat[1][1] + mat[2][2];

		if (trace > 0.0f)
		{
			float s = sqrtf(trace + 1.0f) * 2.0f;
			q.w = 0.25f * s;
			q.x = (mat[1][2] - mat[2][1]) / s;
			q.y = (mat[2][0] - mat[0][2]) / s;
			q.z = (mat[0][1] - mat[1][0]) / s;
		}
		else
		{
			if (mat[0][0] > mat[1][1] && mat[0][0] > mat[2][2])
			{
				float s = sqrtf(1.0f + mat[0][0] - mat[1][1] - mat[2][2]) * 2.0f;
				q.w = (mat[1][2] - mat[2][1]) / s;
				q.x = 0.25f * s;
				q.y = (mat[1][0] + mat[0][1]) / s;
				q.z = (mat[2][0] + mat[0][2]) / s;
			}
			else if (mat[1][1] > mat[2][2])
			{
				float s = sqrtf(1.0f + mat[1][1] - mat[0][0] - mat[2][2]) * 2.0f;
				q.w = (mat[2][0] - mat[0][2]) / s;
				q.x = (mat[1][0] + mat[0][1]) / s;
				q.y = 0.25f * s;
				q.z = (mat[2][1] + mat[1][2]) / s;
			}
			else
			{
				float s = sqrtf(1.0f + mat[2][2] - mat[0][0] - mat[1][1]) * 2.0f;
				q.w = (mat[0][1] - mat[1][0]) / s;
				q.x = (mat[2][0] + mat[0][2]) / s;
				q.y = (mat[2][1] + mat[1][2]) / s;
				q.z = 0.25f * s;
			}
		}

		return q;
	}


	// x、y、zのスケールを持つスケール行列を作成
	static Matrix4 CreateScale(float xScale, float yScale, float zScale)
	{
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, zScale, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateScale(const Vector3& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
	}

	// 均一な因子でスケール行列を作成
	static Matrix4 CreateScale(float scale)
	{
		return CreateScale(scale, scale, scale);
	}

	// x軸回転
	static Matrix4 CreateRotationX(float theta)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f , 0.0f },
			{ 0.0f, Math::Cos(theta), Math::Sin(theta), 0.0f },
			{ 0.0f, -Math::Sin(theta), Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// y軸回転
	static Matrix4 CreateRotationY(float theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(theta), 0.0f, -Math::Sin(theta), 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ Math::Sin(theta), 0.0f, Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// z軸回転
	static Matrix4 CreateRotationZ(float theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(theta), Math::Sin(theta), 0.0f, 0.0f },
			{ -Math::Sin(theta), Math::Cos(theta), 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// クォータニオンから回転行列を作成
	static Matrix4 CreateFromQuaternion(const class Quaternion& q);

	static Matrix4 CreateTranslation(const Vector3& trans)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{

		Vector3 forward = Vector3::Normalize(target - eye);
		Vector3 right = Vector3::Normalize(Vector3::Cross(up, forward));
		Vector3 newUp = Vector3::Normalize(Vector3::Cross(forward, right));
		Vector3 trans;
		trans.x = -Vector3::Dot(right, eye);
		trans.y = -Vector3::Dot(up, eye);
		trans.z = -Vector3::Dot(forward, eye);

		float temp[4][4] =
		{
			{ right.x, newUp.x, forward.x, 0.0f },
			{ right.y, newUp.y, forward.y, 0.0f },
			{ right.z, newUp.z, forward.z, 0.0f },
			{ trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateOrtho(float width, float height, float near, float far)
	{
		float temp[4][4] =
		{
			{ 2.0f / width, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 2.0f / height, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f / (far - near), 0.0f },
			{ 0.0f, 0.0f, near / (near - far), 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float near, float far)
	{
		float yScale = Math::Cot(fovY / 2.0f);
		float xScale = yScale * height / width;
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, far / (far - near), 1.0f },
			{ 0.0f, 0.0f, -near * far / (far - near), 0.0f }
		};
		return Matrix4(temp);
	}

	// シンプルビュー投影行列を作成する
	static Matrix4 CreateSimpleViewProj(float width, float height)
	{
		float temp[4][4] =
		{
			{ 2.0f / width, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 2.0f / height, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Quaternion FromMatrix(const Matrix4& mat)
	{
		Quaternion q;
		float trace = mat.mat[0][0] + mat.mat[1][1] + mat.mat[2][2];

		if (trace > 0.0f)
		{
			float s = Math::Sqrt(trace + 1.0f) * 2.0f;
			q.w = 0.25f * s;
			q.x = (mat.mat[2][1] - mat.mat[1][2]) / s;
			q.y = (mat.mat[0][2] - mat.mat[2][0]) / s;
			q.z = (mat.mat[1][0] - mat.mat[0][1]) / s;
		}
		else
		{
			if (mat.mat[0][0] > mat.mat[1][1] && mat.mat[0][0] > mat.mat[2][2])
			{
				float s = Math::Sqrt(1.0f + mat.mat[0][0] - mat.mat[1][1] - mat.mat[2][2]) * 2.0f;
				q.w = (mat.mat[2][1] - mat.mat[1][2]) / s;
				q.x = 0.25f * s;
				q.y = (mat.mat[0][1] + mat.mat[1][0]) / s;
				q.z = (mat.mat[0][2] + mat.mat[2][0]) / s;
			}
			else if (mat.mat[1][1] > mat.mat[2][2])
			{
				float s = Math::Sqrt(1.0f + mat.mat[1][1] - mat.mat[0][0] - mat.mat[2][2]) * 2.0f;
				q.w = (mat.mat[0][2] - mat.mat[2][0]) / s;
				q.x = (mat.mat[0][1] + mat.mat[1][0]) / s;
				q.y = 0.25f * s;
				q.z = (mat.mat[1][2] + mat.mat[2][1]) / s;
			}
			else
			{
				float s = Math::Sqrt(1.0f + mat.mat[2][2] - mat.mat[0][0] - mat.mat[1][1]) * 2.0f;
				q.w = (mat.mat[1][0] - mat.mat[0][1]) / s;
				q.x = (mat.mat[0][2] + mat.mat[2][0]) / s;
				q.y = (mat.mat[1][2] + mat.mat[2][1]) / s;
				q.z = 0.25f * s;
			}
		}

		return q;
	}

	static const Matrix4 Identity;
};


namespace Color
{
	static const Vector3 Black(0.0f, 0.0f, 0.0f);
	static const Vector3 White(1.0f, 1.0f, 1.0f);
	static const Vector3 Red(1.0f, 0.0f, 0.0f);
	static const Vector3 Green(0.0f, 1.0f, 0.0f);
	static const Vector3 Blue(0.0f, 0.0f, 1.0f);
	static const Vector3 Yellow(1.0f, 1.0f, 0.0f);
	static const Vector3 LightYellow(1.0f, 1.0f, 0.88f);
	static const Vector3 LightBlue(0.68f, 0.85f, 0.9f);
	static const Vector3 LightPink(1.0f, 0.71f, 0.76f);
	static const Vector3 LightGreen(0.56f, 0.93f, 0.56f);
}
