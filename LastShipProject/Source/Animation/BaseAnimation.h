#pragma once

#include <cassert>

//index�͈̔� : 0.0f <= index < max
class BaseAnimation
{
private:
	bool isValid_m = false;
	const float interval_m;
	const float max_m;
	float index_m = 0.0f;
protected:
	//�h����̃N���X���Ō��݂�index���擾����
	float getIndex()const;
public:
	//�A�j���[�V������L���ɂ��čŏ�����J�n����
	void start();
	//�A�j���[�V�����𖳌��ɂ��ď�����ԂɃ��Z�b�g����
	void stop();
	//�A�j���[�V���������L���Ȏ�1�t���[����1�񂱂̊֐����Ă��index���X�V����
	void update();
	//�A�j���[�V�������L���Ȃ�^��Ԃ�
	bool isValid()const;
	//1�t���[���������index�̍X�V��(interval)��index�̍ő�l(max)��ݒ肷��
	BaseAnimation(float interval, float max);
	virtual ~BaseAnimation();
};

