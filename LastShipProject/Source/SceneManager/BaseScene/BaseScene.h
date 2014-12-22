#pragma once

#include "NextSceneInfo.h"

//---------------------------------------------------------------------------------------
//機能, 役割         : シーンクラスの基本クラスです。
//注意               : 複雑な初期化と終了処理はinitialize()とfinalize()で行ってください。
//                   : シーンクラスはBaseSceneから派生してください。
//                   : finalize, initialize, inputUpdateOutputはオーバーライドしてください。
//                   : inputUpdateOutputの中でsetNextSceneInfoを呼んで次のシーンを設定してください。
//---------------------------------------------------------------------------------------
//派生例


template<typename SceneID>
class BaseScene
{
	typedef NextSceneInfo<SceneID> NextInfo;
public:
	BaseScene(){}
	virtual ~BaseScene(){}

	virtual int finalize() = 0;           //返り値 : 成功 0 / 失敗 -1
	virtual NextInfo decideNextScene() = 0;
	virtual int initialize() = 0;         //返り値 : 成功 0 / 失敗 -1
	virtual int inputUpdateOutput() = 0;  //返り値 : 成功 0 / 失敗 -1
};
