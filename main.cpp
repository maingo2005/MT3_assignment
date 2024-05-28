#include <Novice.h>
#include <cassert>
#include <cstdint>
#include<cmath>
#include <imgui.h>

const char kWindowTitle[] = "GC2C_12_マインゴ_シズカ";
static const int kWindowWidth = 1280;
static const int kWindowHeight = 720;

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


struct Line {
	Vector3 origin;//!<始点
	Vector3 diff;//!<終点への差分ベクトル
};

struct Ray {
	Vector3 origin;//!<始点
	Vector3 diff;//!<終点への差分ベクトル
};

struct Segment {
	Vector3 origin;//!<始点
	Vector3 diff;//!<終点への差分ベクトル
};

Vector3 Project(const Vector3& v1, const Vector3& v2) {

}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {

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

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 addition;
	addition.x = v1.x + v2.x;
	addition.y = v1.y + v2.y;
	addition.z = v1.z + v2.z;
	return addition;
}

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 subtraction;
	subtraction.x = v1.x - v2.x;
	subtraction.y = v1.y - v2.y;
	subtraction.z = v1.z - v2.z;
	return subtraction;
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewPojectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 10;//分割数
	const float kLonEvery = 0.0f;
	const float kLatEvery = 0.0f;

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;
	}

	for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
		float lon = lonIndex * kLonEvery;

		Vector3 a, b, c;
		a.x = { std::cos(0) * std::sin(2 / 0) };
		a.y = { std::sin(0) };
		a.z = { std::cos(0 + 0) * std::sin(2 / 0) };
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };

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

		///
		/// ↓更新処理ここから
		///

		Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
		Vector3 closestPoint = ClosestPoint(point, segment);

		Sphere pointSphere{ point,0.0f };
		Sphere closestPointSphere{ closestPoint,0.01f };
		DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(closestPointSphere, viewProjectionMatrix, viewportMatrix, BLACK);

		Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);

		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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
