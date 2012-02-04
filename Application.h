#pragma once

class Sequence;

namespace gameaudio {
	class ISound;
}

namespace rsc {
	class SyncManager;
}

/**
 * �쐬����A�v���P�[�V�����̖{�̂ƂȂ�N���X
 */
class Application
{
	gameaudio::ISound* _bgm;
	core::shared_ptr<rsc::SyncManager> _rm;
	core::shared_ptr<Sequence> _seq;

	void _checkExtensions();
	
	Application();

public:
	static bool hasInstance();
	static Application* instance();
	static void deleteInstance();

	~Application();

	/**
	 * ������
	 * Application::instance()����Ă΂��̂ŁA���ʂ͈ӎ����Ȃ��Ă��悢
	 */
	void init();

	/** ���t���[���Ă΂��֐�
	 * \param delta_time ���O�̃t���[������̌o�ߎ��ԁi�b�j
	 */
	void update(f32 delta_time);
	
	/** �E�B���h�E�̑傫�����ς�����Ƃ��ɌĂ΂��֐�
	 * \param size 
	 */
	void onResize(const uint2d& size);
	
	/** �E�B���h�E�������悤�Ƃ��Ă���Ƃ��ɌĂ΂��֐�
	 * \return ���Ă��悯���true�A�����łȂ��Ƃ���false
	 */
	bool onClose();

	// �S�V�[�P���X���ʂ�BGM
	gameaudio::ISound* getBGM() const;

	// ���\�[�X�}�l�[�W��
	core::shared_ptr<rsc::SyncManager> getResourceManager() const;
};
