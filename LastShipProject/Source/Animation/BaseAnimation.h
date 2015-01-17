#pragma once

#include <cassert>

//indexの範囲 : 0.0f <= index < max
class BaseAnimation
{
private:
	bool isValid_m = false;
	const float interval_m;
	const float max_m;
	float index_m = 0.0f;
protected:
	//派生先のクラス内で現在のindexを取得する
	float getIndex()const;
public:
	//アニメーションを有効にして最初から開始する
	void start();
	//アニメーションを無効にして初期状態にリセットする
	void stop();
	//アニメーションをが有効な時1フレームに1回この関数を呼んでindexを更新する
	void update();
	//アニメーションが有効なら真を返す
	bool isValid()const;
	//1フレーム当たりのindexの更新量(interval)とindexの最大値(max)を設定する
	BaseAnimation(float interval, float max);
	virtual ~BaseAnimation();
};

