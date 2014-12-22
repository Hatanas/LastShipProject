#pragma once

#include "../BaseScene/BaseScene.h"

//---------------------------------------------------------------------------------------
//機能, 役割         : テンプレート引数のシーンクラスを生成します。
//注意               : SceneID   シーン識別列挙体
//                   : Scene     BaseSceneの派生クラス
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
