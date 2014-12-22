#pragma once

#include "WaySceneChange.h"
#include "../../Scenes/SceneID/SceneID.h"

//---------------------------------------------------------------------------------------
//�@�\, ����         : ���̃V�[���̏���ێ����܂��B
//�g�p��             : NextSceneInfo<projectj::SceneID> *info = new NextSceneInfo<projectj::SceneID>;
//                   : info->sceneID_m = NEXT_SCENE;
//                   : info->wayToChange_m = JUMP;
//                   : *NextSceneInfo_m = *info;
//                   : delete info;
//---------------------------------------------------------------------------------------
//�����o�ϐ��Ɠ���̑Ή��\---------------------------------------------------------------
//wayToChange_m : sceneID_m : ����
//  CLEAR            : NOTHING       : �Q�[�����I��
//  CLEAR            : others        : �Q�[�����I��
//  KEEP             : NOTHING       : �V�[���ύX����
//  KEEP             : others        : �V�[���ύX����
//  others           : NOTHING       : �Q�[�����I��
//  others           : others        : �V�[����ύX
//----------------------------------------------------------------------------------------

template<typename SceneID>
struct NextSceneInfo
{
	SceneID nextID_m;           //�ύX��̃V�[���̎��ʗ񋓒萔�������܂��B
	WaySceneChange wayToChange_m; //�V�[���ڍs�̕��@�������܂��B

	NextSceneInfo(){}
	NextSceneInfo(SceneID id, WaySceneChange way)
		: nextID_m(id), wayToChange_m(way){}
	~NextSceneInfo(){}
};
