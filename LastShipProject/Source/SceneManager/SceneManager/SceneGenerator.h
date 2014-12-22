#pragma once

#include "../BaseScene/BaseScene.h"

//---------------------------------------------------------------------------------------
//�@�\, ����         : �e���v���[�g�����̃V�[���N���X�𐶐����܂��B
//����               : SceneID   �V�[�����ʗ񋓑�
//                   : Scene     BaseScene�̔h���N���X
//---------------------------------------------------------------------------------------

template<typename SceneID>
class BaseSceneGenerator
{
protected:
	typedef BaseScene<SceneID> Scene;
public:
	BaseSceneGenerator(){};
	virtual ~BaseSceneGenerator(){};
	virtual Scene *generateScene() = 0;
};


template<typename SceneID, class DerivedScene>
class SceneGenerator : public BaseSceneGenerator<SceneID>
{
public:
	SceneGenerator(){};
	~SceneGenerator(){};
	Scene *generateScene();
};

template<typename SceneID, class DerivedScene>
typename SceneGenerator<SceneID, DerivedScene>::Scene *SceneGenerator<SceneID, DerivedScene>::generateScene()
{
	return new DerivedScene();
}
