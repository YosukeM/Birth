#ifdef _WIN32
#include <Windows.h>
#endif

#include <GL/glew.h>
#include <GL/glfw.h>
#include <iostream>

#include "Error.h"
#include "Application.h"

#include <functional>

namespace {

/**
 * グローバル変数
 */
Application *gApp = NULL;

/**
 * ウィンドウリサイズ時のコールバック
 * アスペクト比を4:3から16:9の間にし、それを超える場合はレターボックスをつける
 */
void onResize(int window_w, int window_h) {
	const f32 MAX_ASPECT = 16.0f / 9.0f;
	const f32 MIN_ASPECT = 4.0f / 3.0f;

	// viewportの大きさを決める
	float window_aspect = f32(window_w) / f32(window_h);
	uint2d viewport(window_w, window_h);
	if (window_aspect > MAX_ASPECT) {
		viewport.x = int(window_h * MAX_ASPECT);
	} else if (window_aspect < MIN_ASPECT) {
		viewport.y = int(window_w / MIN_ASPECT);
	}
	glViewport((window_w - viewport.x) / 2, (window_h - viewport.y) / 2, viewport.x, viewport.y);
	
	// プロジェクション行列を仮設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Applicationのコールバック関数を呼ぶ
	if (gApp) {
		gApp->onResize(viewport);
	}
}

/**
 * エラーメッセージを表示
 */
void showError(const char* str) {
	#ifdef _WIN32
		OutputDebugStringA(str);
		OutputDebugStringA("\n");
	#else
		std::cerr << str;
		std::cerr << std::endl;
	#endif
}

}

/**
 * main関数
 */
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR argv, int argc)
#else
int main(int argc, const char** argv)
#endif
{
	// GLFWを初期化
	if (!glfwInit()) {
		showError("Failed to initialize GLFW");
		return -1;
	}
	if (!glfwOpenWindow(800, 450, 8, 8, 8, 0, 0, 0, GLFW_WINDOW)) {
		showError("Failed to open a window");
		glfwTerminate();
		return -1;
	}

	// GLEWを初期化
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		showError("Failed to initialize GLEW");
		return -1;
	}

	// GLFWの設定
	glfwSetWindowTitle("Birth");
	glfwSetWindowSizeCallback(onResize);

	try {
		// Applicationのコンストラクタを呼ぶ
		Application app;

		// 一時変数に格納（GLFWのコールバック関数内で使う）
		gApp = &app;

		// メインループ
		double newTime, prevTime;
		newTime = prevTime = glfwGetTime();
		while (true) {
			newTime = glfwGetTime();
			app.update(f32(newTime - prevTime));
			prevTime = newTime;
			glfwSwapBuffers();
			if (!glfwGetWindowParam(GLFW_OPENED)) {
				if (app.onClose()) break;
			}
		}

		// 一時変数を破棄、Applicationのデストラクタが呼ばれる。
		gApp = NULL;

	} catch (Error& e) {
		gApp = NULL;
		showError(e.what());
	} catch (std::bad_alloc&) {
		gApp = NULL;
		showError("Memory shortage");
	} catch (std::runtime_error& e) {
		showError(e.what());
	} catch (...) {
		gApp = NULL;
		showError("Unknown Error");
	}

	// 終了処理
	glfwCloseWindow();
	glfwTerminate();

	return 0;
}
