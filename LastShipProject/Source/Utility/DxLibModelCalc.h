#pragma once

#include "DxLib.h"

//３Dのワールド変換行列から分かる情報を計算する


class DxLibModelCalc
{
public:
	static const VECTOR ORIGIN;//原点
	static const VECTOR X_AXIS;//x軸
	static const VECTOR Y_AXIS;//y軸
	static const VECTOR Z_AXIS;//z軸

	//行列からx方向の拡大率を得る
	static float getScaleX(MATRIX m);

	//行列からy方向の拡大率を得る
	static float getScaleY(MATRIX m);

	//行列からz方向の拡大率を得る
	static float getScaleZ(MATRIX m);

	//行列から位置ベクトルを得る
	static VECTOR getPosition(MATRIX m);
};
