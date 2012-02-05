#ifdef _WIN32
#include <Windows.h>
#else
#include <boost/filesystem/operations.hpp>
#endif

#include <GL/glew.h>
#include <GL/glfw.h>

#include "Error.h"
#include "Application.h"
#include "inputManager.h"

#include <gameaudio/gameaudio.h>

namespace {
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
	if (Application::hasInstance()) {
		Application::instance()->onResize(viewport);
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
	int window_mode = GLFW_WINDOW;
	int2d window_size(800, 450);
#ifdef _WIN32
#ifndef _DEBUG
	if (MessageBox(NULL, TEXT("�t���X�N���[�����[�h�ŋN�����Ă�\n��낵���ł����H"), TEXT("�m�F"), MB_YESNO) == IDYES) {
		window_mode = GLFW_FULLSCREEN;
		window_size.x = GetSystemMetrics(SM_CXSCREEN);
		window_size.y = GetSystemMetrics(SM_CYSCREEN);
	}
#endif
#endif

	// GLFW��������
	if (!glfwInit()) {
		showError("Failed to initialize GLFW");
		return -1;
	}
	if (!glfwOpenWindow(window_size.x, window_size.y, 8, 8, 8, 0, 0, 0, window_mode)) {
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

	// GameAudio��������
	gameaudio::getSoundManager();

	// GLFW�̐ݒ�
	glfwSetWindowTitle("Birth");
	glfwSetWindowSizeCallback(onResize);

#ifndef _WIN32
#ifdef _DEBUG
	boost::filesystem::current_path("../../../../Birth");
#endif
#endif

	try {
		// Application�̃R���X�g���N�^���Ă�
		Application::instance();

		// ���C�����[�v
		double newTime, prevTime;
		newTime = prevTime = glfwGetTime();
		while (true) {
			newTime = glfwGetTime();
			input::Manager::instance()->update(f32(newTime - prevTime));
			Application::instance()->update(f32(newTime - prevTime));
			prevTime = newTime;
			glfwSwapBuffers();
			if (!glfwGetWindowParam(GLFW_OPENED) || glfwGetKey(GLFW_KEY_ESC)) {
				if (Application::instance()->onClose()) break;
			}
		}

	} catch (Error& e) {
		showError(e.what());
	} catch (std::bad_alloc&) {
		showError("Memory shortage");
	} catch (std::runtime_error& e) {
		showError(e.what());
	} catch (...) {
		showError("Unknown Error");
	}
	
	// Application�̃f�X�g���N�^���ĂԁB
	Application::deleteInstance();

	// �I������
	glfwCloseWindow();
	glfwTerminate();

	return 0;
}
