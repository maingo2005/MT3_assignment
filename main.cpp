#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "GC2C_12_マインゴ_シズカ";

static const int kColumnWidth = 60;
static const int kRowHeight = 20;

struct Matrix4x4 {
	float m[4][4];
};

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

//２．正射行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 orthographic;
	orthographic.m[0][0] = 2.0f / (right - left);
	orthographic.m[0][1] = 0;
	orthographic.m[0][2] = 0;
	orthographic.m[0][3] = 0;

	orthographic.m[1][0] = 0;
	orthographic.m[1][1] = 2.0f / (top - bottom);
	orthographic.m[1][2] = 0;
	orthographic.m[1][3] = 0;

	orthographic.m[2][0] = 0;
	orthographic.m[2][1] = 0;
	orthographic.m[2][2] = 1.0f / (farClip - nearClip);
	orthographic.m[2][3] = 0;

	orthographic.m[3][0] = (left + right) / (left - right);
	orthographic.m[3][1] = (top + bottom) / (bottom - top);
	orthographic.m[3][2] = nearClip / (nearClip - farClip);
	orthographic.m[3][3] = 1;
	return orthographic;
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

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 20, "%6.02f", matrix.m[row][column]);
		}
	}
	Novice::ScreenPrintf(x, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Matrix4x4 orthographicMatrix = MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
	Matrix4x4 perspectiveFovMatrix = MakePerspectiveFovMatrix(0.63f, 1.33f, 0.0f, 1000.0f);
	Matrix4x4 viewportMatrix = MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, perspectiveFovMatrix, "perspectiveFovMatrix");
		MatrixScreenPrintf(0, kRowHeight * 10, viewportMatrix, "viewportMatrix");

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
