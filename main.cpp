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
 * �O���[�o���ϐ�
 */
Application *gApp = NULL;

/**
 * �E�B���h�E���T�C�Y���̃R�[���o�b�N
 * �A�X�y�N�g���4:3����16:9�̊Ԃɂ��A����𒴂���ꍇ�̓��^�[�{�b�N�X������
 */
void onResize(int window_w, int window_h) {
	const f32 MAX_ASPECT = 16.0f / 9.0f;
	const f32 MIN_ASPECT = 4.0f / 3.0f;

	// viewport�̑傫�������߂�
	float window_aspect = f32(window_w) / f32(window_h);
	uint2d viewport(window_w, window_h);
	if (window_aspect > MAX_ASPECT) {
		viewport.x = int(window_h * MAX_ASPECT);
	} else if (window_aspect < MIN_ASPECT) {
		viewport.y = int(window_w / MIN_ASPECT);
	}
	glViewport((window_w - viewport.x) / 2, (window_h - viewport.y) / 2, viewport.x, viewport.y);
	
	// �v���W�F�N�V�����s������ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Application�̃R�[���o�b�N�֐����Ă�
	if (gApp) {
		gApp->onResize(viewport);
	}
}

/**
 * �G���[���b�Z�[�W��\��
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
 * main�֐�
 */
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR argv, int argc)
#else
int main(int argc, const char** argv)
#endif
{
	// GLFW��������
	if (!glfwInit()) {
		showError("Failed to initialize GLFW");
		return -1;
	}
	if (!glfwOpenWindow(800, 450, 8, 8, 8, 0, 0, 0, GLFW_WINDOW)) {
		showError("Failed to open a window");
		glfwTerminate();
		return -1;
	}

	// GLEW��������
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		showError("Failed to initialize GLEW");
		return -1;
	}

	// GLFW�̐ݒ�
	glfwSetWindowTitle("Birth");
	glfwSetWindowSizeCallback(onResize);

	try {
		// Application�̃R���X�g���N�^���Ă�
		Application app;

		// �ꎞ�ϐ��Ɋi�[�iGLFW�̃R�[���o�b�N�֐����Ŏg���j
		gApp = &app;

		// ���C�����[�v
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

		// �ꎞ�ϐ���j���AApplication�̃f�X�g���N�^���Ă΂��B
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

	// �I������
	glfwCloseWindow();
	glfwTerminate();

	return 0;
}
