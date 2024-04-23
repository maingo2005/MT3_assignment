#include <Novice.h>
#include <corecrt_math.h>
#include <corecrt_math_defines.h>

const char kWindowTitle[] = "GC2C_12_マインゴ_シズカ";

static const int kColumnWidth = 60;
static const int kRowHeight = 20;

struct Vector3 {
	float x;
	float y;
	float z;
};
struct Matrix4x4 {
	float m[4][4];
};

//１.X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 M;
	M.m[0][0] = 1;
	M.m[0][1] = 0;
	M.m[0][2] = 0;
	M.m[0][3] = 0;

	M.m[1][0] = 0;
	M.m[1][1] = cosf(radian);
	M.m[1][2] = sinf(radian);
	M.m[1][3] = 0;

	M.m[2][0] = 0;
	M.m[2][1] = -1 * sinf(radian);
	M.m[2][2] = cosf(radian);
	M.m[2][3] = 0;

	M.m[3][0] = 0;
	M.m[3][1] = 0;
	M.m[3][2] = 0;
	M.m[3][3] = 1;

	return M;
}
//2.X軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 M;
	M.m[0][0] = cosf(radian);
	M.m[0][1] = 0;
	M.m[0][2] = -1 * sinf(radian);
	M.m[0][3] = 0;

	M.m[1][0] = 0;
	M.m[1][1] = 1;
	M.m[1][2] = 0;
	M.m[1][3] = 0;

	M.m[2][0] = sinf(radian);
	M.m[2][1] = 0;
	M.m[2][2] = cosf(radian);
	M.m[2][3] = 0;

	M.m[3][0] = 0;
	M.m[3][1] = 0;
	M.m[3][2] = 0;
	M.m[3][3] = 1;

	return M;
}
//3.X軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 M;
	M.m[0][0] = cosf(radian);
	M.m[0][1] = sinf(radian);
	M.m[0][2] = 0;
	M.m[0][3] = 0;

	M.m[1][0] = -1 * sinf(radian);
	M.m[1][1] = cosf(radian);
	M.m[1][2] = 0;
	M.m[1][3] = 0;

	M.m[2][0] = 0;
	M.m[2][1] = 0;
	M.m[2][2] = 1;
	M.m[2][3] = 0;

	M.m[3][0] = 0;
	M.m[3][1] = 0;
	M.m[3][2] = 0;
	M.m[3][3] = 1;

	return M;
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

	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

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

		MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");

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
