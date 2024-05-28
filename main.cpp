#include <Novice.h>
#include <cstdint>
#include <imgui.h>
#include<cmath>

const char kWindowTitle[] = "GC2C_12_マインゴ_シズカ";

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

void DrawGrid(const Matrix4x4& viewPojectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const uint32_t kSubdivision = 10;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);//1つ分の長さ

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

	}
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {

	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

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

		Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
		Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat3("SphereRotate", &sphere.radius, 0.01f);
		ImGui::End();

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
