#pragma once

#include "WaySceneChange.h"
#include "../../Scenes/SceneID/SceneID.h"

//---------------------------------------------------------------------------------------
//機能, 役割         : 次のシーンの情報を保持します。
//使用例             : NextSceneInfo<projectj::SceneID> *info = new NextSceneInfo<projectj::SceneID>;
//                   : info->sceneID_m = NEXT_SCENE;
//                   : info->wayToChange_m = JUMP;
//                   : *NextSceneInfo_m = *info;
//                   : delete info;
//---------------------------------------------------------------------------------------
//メンバ変数と動作の対応表---------------------------------------------------------------
//wayToChange_m : sceneID_m : 動作
//  CLEAR            : NOTHING       : ゲームを終了
//  CLEAR            : others        : ゲームを終了
//  KEEP             : NOTHING       : シーン変更無し
//  KEEP             : others        : シーン変更無し
//  others           : NOTHING       : ゲームを終了
//  others           : others        : シーンを変更
//----------------------------------------------------------------------------------------

template<typename SceneID>
struct NextSceneInfo
{
	SceneID nextID_m;           //変更先のシーンの識別列挙定数を代入します。
	WaySceneChange wayToChange_m; //シーン移行の方法を代入します。

	NextSceneInfo(){}
	NextSceneInfo(SceneID id, WaySceneChange way)
		: nextID_m(id), wayToChange_m(way){}
	~NextSceneInfo(){}
};
