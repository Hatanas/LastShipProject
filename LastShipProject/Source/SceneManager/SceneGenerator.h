#pragma once

template<typename SceneID>
class BaseScene;

#include "BaseScene.h"
#include <memory>
//---------------------------------------------------------------------------------------
//機能, 役割         : テンプレート引数のシーンクラスを生成します。
//注意               : SceneID   シーン識別列挙体
//                   : Scene     BaseSceneの派生クラス
//---------------------------------------------------------------------------------------

namespace projectj {
namespace scenemanager {

template<typename SceneID>
class BaseSceneGenerator
{
protected:
	typedef BaseScene<SceneID> Scene;
public:
	typedef std::shared_ptr<BaseScene<SceneID>> SharedScene;
public:
	BaseSceneGenerator() {};
	virtual ~BaseSceneGenerator() {};
	virtual SharedScene generateScene() const = 0;
};


template<typename SceneID, class DerivedScene>
class SceneGenerator : public BaseSceneGenerator < SceneID >
{
public:
	SceneGenerator() {};
	~SceneGenerator() {};
	SharedScene generateScene() const;
};

template<typename SceneID, class DerivedScene>
typename SceneGenerator<SceneID, DerivedScene>::SharedScene
	SceneGenerator<SceneID, DerivedScene>::generateScene() const
{
	return std::make_shared<DerivedScene>();
}

}
}
