#include <Novice.h>
#include <corecrt_math.h>

const char kWindowTitle[] = "GC2C_12_マインゴ_シズカ";

static const int kColumnWidth = 60;
static const int kRowHeight = 20;

struct Vector3 {
	float x;
	float y;
	float z;
};

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

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 multiplication;
	multiplication.x = scalar * v.x;
	multiplication.y = scalar * v.y;
	multiplication.z = scalar * v.z;
	return multiplication;
}

//内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float innerproduct;
	innerproduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return innerproduct;
}

//長さ(ノルム)
float Length(const Vector3& v) {
	float norm;
	norm = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return norm;
}

//正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result{ 0.0f,0.0f,0.0f };
	float X = 4, Y = -1, Z = 2;
	float norm = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (norm != 0.0f) {
		result.x = X / norm;
		result.y = Y / norm;
		result.z = Z / norm;
	}
	return result;
}

void VetorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
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

		Vector3 v1{ 1.0f,3.0f,-5.0f };
		Vector3 v2{ 4.0f,-1.0f,2.0f };
		float k = { 4.0f };

		Vector3 resultAdd = Add(v1, v2);
		Vector3 resultSudtract = Subtract(v1, v2);
		Vector3 resultMtiply = Multiply(k, v1);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vector3 resultNormalize = Normalize(v2);

		VetorScreenPrintf(0, 0, resultAdd, " : Add");
		VetorScreenPrintf(0, kRowHeight, resultSudtract, " : Sudtract");
		VetorScreenPrintf(0, kRowHeight * 2, resultMtiply, " : Mtiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", resultLength);
		VetorScreenPrintf(0, kRowHeight * 5, resultNormalize, " : Normalize");

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
