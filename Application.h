#pragma once

#include "SyncResourceManager.h"

class Sequence;

/**
 * �쐬����A�v���P�[�V�����̖{�̂ƂȂ�N���X
 */
class Application
{
	core::vector<core::shared_ptr<Sequence> > _seqs;
	core::shared_ptr<Sequence> _seq;

	void _checkExtensions();

public:
	Application();
	~Application();

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
};
