#pragma once

#include "Color.h"

/**
 * ��ʑJ�ڂ���邽�߂̊�{�N���X�B
 * �T�u�N���X�̂��߂ɂ������֗̕��@�\��񋟂��Ă���B
 */
class Sequence {
private:
	f32 _fadeTimer, _fadeDuration;
	Color _fadeColor;
public:
	typedef enum {
		EFS_NONE,
		EFS_FADEIN,
		EFS_FADEOUT
	} EFadeState;
private:
	EFadeState _fadeState;

	void _drawFading(f32);

protected:
	Sequence();

	// �t�F�[�h�C�����J�n����B
	// \param duration �t�F�[�h�C������������܂ł̎���
	// \param from �J�n���̃t�F�[�h�C���̐F
	void _fadein(f32 duration = 1.0f, const Color& from = Color(0x000000FF));

	// �t�F�[�h�A�E�g���J�n���A�V�[�P���X���I��������
	// \param duration �t�F�[�h�A�E�g����������܂ł̎���
	// \param to �I�����̉�ʂ̐F
	void _fadeout(f32 duration = 1.0f, const Color& to = Color(0x000000FF));

	// ���ǂ̂悤�Ƀt�F�[�h���Ă��邩�擾����B
	// \return EFS_NONE | EFS_FADEIN | EFS_FADEOUT
	EFadeState _getFadeState() const;

	// �t�F�[�f�B���O�̐i�s�󋵂��擾����B
	// FADEIN����1����0�ցAFADEOUT����0����1�֐��ڂ���l��������B
	float _getFadeLevel() const;

	// �T�u�N���X���������ׂ��֐�
	virtual void _draw() = 0;
	virtual void _update(f32) = 0;
	virtual core::shared_ptr<Sequence> _getNextSequence() = 0;

public:
	virtual ~Sequence();

	// ���t���[���ĂԍX�V�֐�
	// \param delta_time ���O�̃t���[������̌o�ߎ���
	// \return ���̃V�[�P���X�i�J�ڂ��Ȃ����null�j
	core::shared_ptr<Sequence> update(f32 delta_time);

	// ���t���[���Ăԕ`��֐�
	void draw();

	// ��ʃT�C�Y�ύX���ɌĂԊ֐�
	virtual void onResize(const uint2d& size) {};
};