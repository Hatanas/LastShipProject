#pragma once

#include <memory>

//---------------------------------------------------------------------------------------
//機能, 役割		: シーンクラスの基本クラスです。
//注意			: 複雑な初期化と終了処理はinitialize()とfinalize()で行ってください。
//				: シーンクラスはBaseSceneから派生してください。
//				: finalize, initialize, inputUpdateOutputはオーバーライドしてください。
//				: inputUpdateOutputの中でsetNextSceneInfoを呼んで次のシーンを設定してください。
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

	virtual int finalize() = 0;           //返り値 : 成功 0 / 失敗 -1
	virtual SceneChangeMethod decideNext() = 0;
	virtual int initialize() = 0;         //返り値 : 成功 0 / 失敗 -1
	virtual int execute() = 0;  //返り値 : 成功 0 / 失敗 -1
};

}
}
