#include "DxLib.h"

#include "Source\Animation\DerivedAnimation.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//--------------------------------ここから初期化---------------------------
	ChangeWindowMode(TRUE);              //ウィンドウモードにする
	SetFullSceneAntiAliasingMode(4, 0);  //3Dモデルを滑らかにする
	SetEnableXAudioFlag(FALSE);          //藤原のVisualStudioをクラッシュさせない対策
	if (DxLib_Init() == -1){ return -1; }//dxlibの初期化処理
	SetDrawScreen(DX_SCREEN_BACK);       //裏画面に描画
	SetUseZBuffer3D(TRUE);               //z軸(奥行)を正しく描画
	SetWriteZBuffer3D(TRUE);             //z軸(奥行)を正しく描画
	SetBackgroundColor(127, 127, 127);   //背景を明るくする(灰色)
	//--------------------------------ここまで初期化---------------------------

	DerivedAnimation a(1.0f/60.0f, 10);
	
	while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		if(CheckHitKey(KEY_INPUT_ESCAPE) != 0) { break; }

		if(CheckHitKey(KEY_INPUT_SPACE)) { a.start(); }
		if(a.isValid()) {
			a.update();
			DrawFormatString(0, 0, 0xffffff, "%f", a.getTime());
		}
		if(CheckHitKey(KEY_INPUT_RETURN)) { a.stop(); }
	}	

	
	
	//--------------------------------終了処理-------------------------------
	DxLib_End();// ＤＸライブラリの終了処理
	
	return 0;
}
