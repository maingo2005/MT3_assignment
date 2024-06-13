#include <Novice.h>
#include <cstdint>
#include <imgui.h>
#include<cmath>

const char kWindowTitle[] = "GC2C_12_マインゴ_シズカ";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

struct Vector3 {
	float x, y, z;
};

struct Matrix4x4 {
	float m[4][4];
};

struct Sphere {
	Vector3 center; //!<中心点
	float radius; //!<半径
};

//3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 affine;

	affine.m[0][0] = scale.x * (((1 * std::cos(rotate.y) + 0 * 0 + 0 * std::sin(rotate.y) + 0 * 0) * std::cos(rotate.z)) + ((1 * 0 + 0 * 1 + 0 * 0 + 0 * 0) * std::sin(rotate.z)) + ((1 * std::sin(-rotate.y) + 0 * 0 + 0 * std::cos(rotate.y) + 0 * 0) * 0) + ((1 * 0 + 0 * 0 + 0 * 0 + 0 * 1) * 0));
	affine.m[0][1] = scale.x * (((1 * std::cos(rotate.y) + 0 * 0 + 0 * std::sin(rotate.y) + 0 * 0) * std::sin(rotate.z)) + ((1 * 0 + 0 * 1 + 0 * 0 + 0 * 0) * std::cos(rotate.z)) + ((1 * std::sin(-rotate.y) + 0 * 0 + 0 * std::cos(rotate.y) + 0 * 0) * 0) + ((1 * 0 + 0 * 0 + 0 * 0 + 0 * 1) * 0));
	affine.m[0][2] = scale.x * (((1 * std::cos(rotate.y) + 0 * 0 + 0 * std::sin(rotate.y) + 0 * 0) * 0) + ((1 * 0 + 0 * 1 + 0 * 0 + 0 * 0) * 0) + ((1 * std::sin(-rotate.y) + 0 * 0 + 0 * std::cos(rotate.y) + 0 * 0) * 1) + ((1 * 0 + 0 * 0 + 0 * 0 + 0 * 1) * 0));
	affine.m[0][3] = 0;

	affine.m[1][0] = scale.y * (((0 * std::cos(rotate.y) + std::cos(rotate.x) * 0 + std::sin(rotate.x) * std::sin(rotate.y) + 0 * 0) * std::cos(rotate.z)) + ((0 * 0 + std::cos(rotate.x) * 1 + std::sin(rotate.x) * 0 + 0 * 0) * std::sin(-rotate.z) + ((0 * std::sin(-rotate.y) + std::cos(rotate.x) * 0 + std::sin(rotate.x) * std::cos(rotate.y) + 0 * 0) * 0) + ((0 * 0 + std::cos(rotate.x) * 0 + std::sin(rotate.x) * 0 + 0 * 1) * 0)));
	affine.m[1][1] = scale.y * (((0 * std::cos(rotate.y) + std::cos(rotate.x) * 0 + std::sin(rotate.x) * std::sin(rotate.y) + 0 * 0) * std::sin(rotate.z)) + ((0 * 0 + std::cos(rotate.x) * 1 + std::sin(rotate.x) * 0 + 0 * 0) * std::cos(rotate.z) + ((0 * std::sin(-rotate.y) + std::cos(rotate.x) * 0 + std::sin(rotate.x) * std::cos(rotate.y) + 0 * 0) * 0) + ((0 * 0 + std::cos(rotate.x) * 0 + std::sin(rotate.x) * 0 + 0 * 1) * 0)));
	affine.m[1][2] = scale.y * (((0 * std::cos(rotate.y) + std::cos(rotate.x) * 0 + std::sin(rotate.x) * std::sin(rotate.y) + 0 * 0) * 0) + ((0 * 0 + std::cos(rotate.x) * 1 + std::sin(rotate.x) * 0 + 0 * 0) * 0) + ((0 * std::sin(-rotate.y) + std::cos(rotate.x) * 0 + std::sin(rotate.x) * std::cos(rotate.y) + 0 * 0) * 1) + ((0 * 0 + std::cos(rotate.x) * 0 + std::sin(rotate.x) * 0 + 0 * 1) * 0));
	affine.m[1][3] = 0;

	affine.m[2][0] = scale.z * (((0 * std::cos(rotate.y) + std::sin(-rotate.x) * 0 + std::cos(rotate.x) * std::sin(rotate.y) + 0 * 0) * std::cos(rotate.z) + ((0 * 0 + std::sin(-rotate.x) * 1 + std::cos(rotate.x) * 0 + 0 * 0) * std::sin(-rotate.z)) + ((0 * std::sin(-rotate.y) + std::sin(-rotate.x) * 0 + std::cos(rotate.x) * std::cos(rotate.y) + 0 * 0) * 0) + ((0 * 0 + std::sin(-rotate.x) * 0 + std::cos(rotate.x) * 0 + 0 * 1) * 0)));
	affine.m[2][1] = scale.z * (((0 * std::cos(rotate.y) + std::sin(-rotate.x) * 0 + std::cos(rotate.x) * std::sin(rotate.y) + 0 * 0) * std::sin(rotate.z) + ((0 * 0 + std::sin(-rotate.x) * 1 + std::cos(rotate.x) * 0 + 0 * 0) * std::cos(-rotate.z)) + ((0 * std::sin(-rotate.y) + std::sin(-rotate.x) * 0 + std::cos(rotate.x) * std::cos(rotate.y) + 0 * 0) * 0) + ((0 * 0 + std::sin(-rotate.x) * 0 + std::cos(rotate.x) * 0 + 0 * 1) * 0)));
	affine.m[2][2] = scale.z * (((0 * std::cos(rotate.y) + std::sin(-rotate.x) * 0 + std::cos(rotate.x) * std::sin(rotate.y) + 0 * 0) * 0) + ((0 * 0 + std::sin(-rotate.x) * 1 + std::cos(rotate.x) * 0 + 0 * 0) * 0) + ((0 * std::sin(-rotate.y) + std::sin(-rotate.x) * 0 + std::cos(rotate.x) * std::cos(rotate.y) + 0 * 0) * 1) + ((0 * 0 + std::sin(-rotate.x) * 0 + std::cos(rotate.x) * 0 + 0 * 1) * 0));
	affine.m[2][3] = 0;

	affine.m[3][0] = translate.x;
	affine.m[3][1] = translate.y;
	affine.m[3][2] = translate.z;
	affine.m[3][3] = 1;
	return affine;
}


//１．透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 perspectiveFov;
	perspectiveFov.m[0][0] = 1.0f / aspectRatio * cosf(fovY / 2) / sinf(fovY / 2);
	perspectiveFov.m[0][1] = 0;
	perspectiveFov.m[0][2] = 0;
	perspectiveFov.m[0][3] = 0;

	perspectiveFov.m[1][0] = 0;
	perspectiveFov.m[1][1] = cosf(fovY / 2) / sinf(fovY / 2);
	perspectiveFov.m[1][2] = 0;
	perspectiveFov.m[1][3] = 0;

	perspectiveFov.m[2][0] = 0;
	perspectiveFov.m[2][1] = 0;
	perspectiveFov.m[2][2] = farClip / (farClip - nearClip);
	perspectiveFov.m[2][3] = 1;

	perspectiveFov.m[3][0] = 0;
	perspectiveFov.m[3][1] = 0;
	perspectiveFov.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	perspectiveFov.m[3][3] = 0;
	return perspectiveFov;
}

//３．ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 viewport;
	viewport.m[0][0] = width / 2.0f;
	viewport.m[0][1] = 0;
	viewport.m[0][2] = 0;
	viewport.m[0][3] = 0;

	viewport.m[1][0] = 0;
	viewport.m[1][1] = -1 * (height / 2.0f);
	viewport.m[1][2] = 0;
	viewport.m[1][3] = 0;

	viewport.m[2][0] = 0;
	viewport.m[2][1] = 0;
	viewport.m[2][2] = (maxDepth - minDepth);
	viewport.m[2][3] = 0;

	viewport.m[3][0] = left + (width / 2);
	viewport.m[3][1] = top + (height / 2);
	viewport.m[3][2] = minDepth;
	viewport.m[3][3] = 1;
	return viewport;
}

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 reciprocal{ 0.0f };
	reciprocal.m[0][0] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((m.m[1][1] * m.m[2][2] * m.m[3][3]) +
			(m.m[1][2] * m.m[2][3] * m.m[3][1]) +
			(m.m[1][3] * m.m[2][1] * m.m[3][2]) -
			(m.m[1][3] * m.m[2][2] * m.m[3][1]) -
			(m.m[1][2] * m.m[2][1] * m.m[3][3]) -
			(m.m[1][1] * m.m[2][3] * m.m[3][2]));


	reciprocal.m[0][1] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((-m.m[0][1] * m.m[2][2] * m.m[3][3]) -
			(m.m[0][2] * m.m[2][3] * m.m[3][1]) -
			(m.m[0][3] * m.m[2][1] * m.m[3][2]) +
			(m.m[0][3] * m.m[2][2] * m.m[3][1]) +
			(m.m[0][2] * m.m[2][1] * m.m[3][3]) +
			(m.m[0][1] * m.m[2][3] * m.m[3][2]));


	reciprocal.m[0][2] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((+m.m[0][1] * m.m[1][2] * m.m[3][3]) +
			(m.m[0][2] * m.m[1][3] * m.m[3][1]) +
			(m.m[0][3] * m.m[1][1] * m.m[3][2]) -
			(m.m[0][3] * m.m[1][2] * m.m[3][1]) -
			(m.m[0][2] * m.m[1][1] * m.m[3][3]) -
			(m.m[0][1] * m.m[1][3] * m.m[3][2]));


	reciprocal.m[0][3] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((-m.m[0][1] * m.m[1][2] * m.m[2][3]) -
			(m.m[0][2] * m.m[1][3] * m.m[2][1]) -
			(m.m[0][3] * m.m[1][1] * m.m[2][2]) +
			(m.m[0][3] * m.m[1][2] * m.m[2][1]) +
			(m.m[0][2] * m.m[1][1] * m.m[2][3]) +
			(m.m[0][1] * m.m[1][3] * m.m[2][2]));

	reciprocal.m[1][0] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((+m.m[0][0] * m.m[2][2] * m.m[3][3]) +
			(m.m[0][2] * m.m[2][3] * m.m[3][0]) +
			(m.m[0][3] * m.m[2][0] * m.m[3][2]) -
			(m.m[0][3] * m.m[2][2] * m.m[3][0]) -
			(m.m[0][2] * m.m[2][0] * m.m[3][3]) -
			(m.m[0][0] * m.m[2][3] * m.m[3][2]));

	reciprocal.m[1][1] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((-m.m[1][0] * m.m[2][2] * m.m[3][3]) -
			(m.m[1][2] * m.m[2][3] * m.m[3][0]) -
			(m.m[1][3] * m.m[2][0] * m.m[3][2]) +
			(m.m[1][3] * m.m[2][2] * m.m[3][0]) +
			(m.m[1][2] * m.m[2][0] * m.m[3][3]) +
			(m.m[1][0] * m.m[2][3] * m.m[3][2]));



	reciprocal.m[1][2] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((-m.m[0][0] * m.m[1][2] * m.m[3][3]) -
			(m.m[0][2] * m.m[1][3] * m.m[3][0]) -
			(m.m[0][3] * m.m[1][0] * m.m[3][2]) +
			(m.m[0][3] * m.m[1][2] * m.m[3][0]) +
			(m.m[0][2] * m.m[1][0] * m.m[3][3]) +
			(m.m[0][0] * m.m[1][3] * m.m[3][2]));


	reciprocal.m[1][3] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((+m.m[0][0] * m.m[1][2] * m.m[2][3]) +
			(m.m[0][2] * m.m[1][3] * m.m[2][0]) +
			(m.m[0][3] * m.m[1][0] * m.m[2][2]) -
			(m.m[0][3] * m.m[1][2] * m.m[2][0]) -
			(m.m[0][2] * m.m[1][0] * m.m[2][3]) -
			(m.m[0][0] * m.m[1][3] * m.m[2][2]));


	reciprocal.m[2][0] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((+m.m[1][0] * m.m[2][1] * m.m[3][3]) +
			(m.m[1][1] * m.m[2][3] * m.m[3][0]) +
			(m.m[1][3] * m.m[2][0] * m.m[3][1]) -
			(m.m[1][3] * m.m[2][1] * m.m[3][0]) -
			(m.m[1][1] * m.m[2][0] * m.m[3][3]) -
			(m.m[1][0] * m.m[2][3] * m.m[3][1]));


	reciprocal.m[2][1] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((-m.m[0][0] * m.m[2][1] * m.m[3][3]) -
			(m.m[0][1] * m.m[2][3] * m.m[3][0]) -
			(m.m[0][3] * m.m[2][0] * m.m[3][1]) +
			(m.m[0][3] * m.m[2][1] * m.m[3][0]) +
			(m.m[0][1] * m.m[2][0] * m.m[3][3]) +
			(m.m[0][0] * m.m[2][3] * m.m[3][1]));

	reciprocal.m[2][2] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((m.m[0][0] * m.m[1][1] * m.m[3][3]) +
			(m.m[0][1] * m.m[1][3] * m.m[3][0]) +
			(m.m[0][3] * m.m[1][0] * m.m[3][1]) -
			(m.m[0][3] * m.m[1][1] * m.m[3][0]) -
			(m.m[0][1] * m.m[1][0] * m.m[3][3]) -
			(m.m[0][0] * m.m[1][3] * m.m[3][1]));


	reciprocal.m[2][3] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((-m.m[0][0] * m.m[1][1] * m.m[2][3]) -
			(m.m[0][1] * m.m[1][3] * m.m[2][0]) -
			(m.m[0][3] * m.m[1][0] * m.m[2][1]) +
			(m.m[0][3] * m.m[1][1] * m.m[2][0]) +
			(m.m[0][1] * m.m[1][0] * m.m[2][3]) +
			(m.m[0][0] * m.m[1][3] * m.m[2][1]));

	reciprocal.m[3][0] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((-m.m[1][0] * m.m[2][1] * m.m[3][2]) -
			(m.m[1][1] * m.m[2][2] * m.m[3][0]) -
			(m.m[1][2] * m.m[2][0] * m.m[3][1]) +
			(m.m[1][2] * m.m[2][1] * m.m[3][0]) +
			(m.m[1][1] * m.m[2][0] * m.m[3][2]) +
			(m.m[1][0] * m.m[2][2] * m.m[3][1]));

	reciprocal.m[3][1] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((+m.m[0][0] * m.m[2][1] * m.m[3][2]) +
			(m.m[0][1] * m.m[2][2] * m.m[3][0]) +
			(m.m[0][2] * m.m[2][0] * m.m[3][1]) -
			(m.m[0][2] * m.m[2][1] * m.m[3][0]) -
			(m.m[0][1] * m.m[2][0] * m.m[3][2]) -
			(m.m[0][0] * m.m[2][2] * m.m[3][1]));


	reciprocal.m[3][2] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((-m.m[0][0] * m.m[1][1] * m.m[3][2]) -
			(m.m[0][1] * m.m[1][2] * m.m[3][0]) -
			(m.m[0][2] * m.m[1][0] * m.m[3][1]) +
			(m.m[0][2] * m.m[1][1] * m.m[3][0]) +
			(m.m[0][1] * m.m[1][0] * m.m[3][2]) +
			(m.m[0][0] * m.m[1][2] * m.m[3][1]));

	reciprocal.m[3][3] = (1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]))) *
		((+m.m[0][0] * m.m[1][1] * m.m[2][2]) +
			(m.m[0][1] * m.m[1][2] * m.m[2][0]) +
			(m.m[0][2] * m.m[1][0] * m.m[2][1]) -
			(m.m[0][2] * m.m[1][1] * m.m[2][0]) -
			(m.m[0][1] * m.m[1][0] * m.m[2][2]) -
			(m.m[0][0] * m.m[1][2] * m.m[2][1]));

	return reciprocal;
}

Matrix4x4 Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2)
{
	Matrix4x4 multiplication;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			multiplication.m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				multiplication.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return multiplication;
}

//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

void DrawGrid(const Matrix4x4& viewPojectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const uint32_t kSubdivision = 10;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);//1つ分の長さ

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float x = -kGridHalfWidth + xIndex * kGridEvery;

		Vector3 start = { x,0,-kGridHalfWidth };
		Vector3 end = { x,0,kGridHalfWidth };

		Vector3 tS = Transform(start, viewPojectionMatrix);
		tS = Transform(tS, viewportMatrix);
		Vector3 tE = Transform(end, viewPojectionMatrix);
		tE = Transform(tE, viewportMatrix);

		Novice::DrawLine((int)tS.x, (int)tS.y, (int)tE.x, (int)tE.y, 0xAAAAAAFF);

	}
	
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float z = -kGridHalfWidth + zIndex * kGridEvery;

		Vector3 start = { -kGridHalfWidth,0,z };
		Vector3 end = { kGridHalfWidth,0,z };

		Vector3 tS = Transform(start, viewPojectionMatrix);
		tS = Transform(tS, viewportMatrix);
		Vector3 tE = Transform(end, viewPojectionMatrix);
		tE = Transform(tE, viewportMatrix);

		Novice::DrawLine((int)tS.x, (int)tS.y, (int)tE.x, (int)tE.y, 0xAAAAAAFF);

	}
}

const float pi = 3.14f;
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewPojectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 20;//分割数
	const float kLonEvery = 2 * pi / kSubdivision;
	const float kLatEvery = pi / kSubdivision;

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;
		float latNext = -pi / 2.0f + kLatEvery * (latIndex + 1);

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			float lonNext = (lonIndex + 1) * kLonEvery;

			Vector3 a = { sphere.radius * cosf(lat) * cosf(lon),sphere.radius * sinf(lat),sphere.radius * cosf(lat) * sinf(lon) };
			Vector3 b = { sphere.radius * cosf(latNext) * cosf(lon),sphere.radius * sinf(latNext),sphere.radius * cosf(latNext) * sinf(lon) };
			Vector3 c = { sphere.radius * cosf(lat) * cosf(lonNext),sphere.radius * sinf(lat),sphere.radius * cosf(lat) * sinf(lonNext) };

			Vector3 t = Transform(a, viewPojectionMatrix);
			t = Transform(t, viewportMatrix);

			Vector3 t2 = Transform(b, viewPojectionMatrix);
			t2 = Transform(t2, viewportMatrix);

			Vector3 t3 = Transform(c, viewPojectionMatrix);
			t3 = Transform(t3, viewportMatrix);

			Novice::DrawLine((int)t.x, (int)t.y, (int)t2.x, (int)t2.y, color);
			Novice::DrawLine((int)t.x, (int)t.y, (int)t3.x, (int)t3.y, color);
		}
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };
	Vector3 rotate{};
	Vector3 translate{};

	Sphere sphere{};
	sphere.radius = 0.5f;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);


		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::End();

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);

		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, BLACK);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
