#pragma once

#include <memory>

//---------------------------------------------------------------------------------------
//�@�\, ����		: �V�[���N���X�̊�{�N���X�ł��B
//����			: ���G�ȏ������ƏI��������initialize()��finalize()�ōs���Ă��������B
//				: �V�[���N���X��BaseScene����h�����Ă��������B
//				: finalize, initialize, inputUpdateOutput�̓I�[�o�[���C�h���Ă��������B
//				: inputUpdateOutput�̒���setNextSceneInfo���Ă�Ŏ��̃V�[����ݒ肵�Ă��������B
//---------------------------------------------------------------------------------------

namespace projectj {
namespace scenemanager {
template<typename SceneID>
class BaseSceneChangeMethod;
template<typename SceneID>
class SceneChangeMethodFactory;

template<typename SceneID>
class BaseScene
{
public:
	typedef std::unique_ptr<BaseSceneChangeMethod<SceneID>> SceneChangeMethod;
	typedef SceneChangeMethodFactory<SceneID> SceneChangeMethodSet;

	BaseScene() {}
	virtual ~BaseScene() {}

	virtual int finalize() = 0;           //�Ԃ�l : ���� 0 / ���s -1
	virtual SceneChangeMethod decideNext() = 0;
	virtual int initialize() = 0;         //�Ԃ�l : ���� 0 / ���s -1
	virtual int execute() = 0;  //�Ԃ�l : ���� 0 / ���s -1
};

}
}
