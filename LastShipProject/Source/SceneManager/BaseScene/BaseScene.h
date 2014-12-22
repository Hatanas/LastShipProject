#pragma once

#include "NextSceneInfo.h"

//---------------------------------------------------------------------------------------
//�@�\, ����         : �V�[���N���X�̊�{�N���X�ł��B
//����               : ���G�ȏ������ƏI��������initialize()��finalize()�ōs���Ă��������B
//                   : �V�[���N���X��BaseScene����h�����Ă��������B
//                   : finalize, initialize, inputUpdateOutput�̓I�[�o�[���C�h���Ă��������B
//                   : inputUpdateOutput�̒���setNextSceneInfo���Ă�Ŏ��̃V�[����ݒ肵�Ă��������B
//---------------------------------------------------------------------------------------
//�h����


template<typename SceneID>
class BaseScene
{
	typedef NextSceneInfo<SceneID> NextInfo;
public:
	BaseScene(){}
	virtual ~BaseScene(){}

	virtual int finalize() = 0;           //�Ԃ�l : ���� 0 / ���s -1
	virtual NextInfo decideNextScene() = 0;
	virtual int initialize() = 0;         //�Ԃ�l : ���� 0 / ���s -1
	virtual int inputUpdateOutput() = 0;  //�Ԃ�l : ���� 0 / ���s -1
};
