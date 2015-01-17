#include "DxLib.h"

#include "Source\Animation\DerivedAnimation.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//--------------------------------�������珉����---------------------------
	ChangeWindowMode(TRUE);              //�E�B���h�E���[�h�ɂ���
	SetFullSceneAntiAliasingMode(4, 0);  //3D���f�������炩�ɂ���
	SetEnableXAudioFlag(FALSE);          //������VisualStudio���N���b�V�������Ȃ��΍�
	if (DxLib_Init() == -1){ return -1; }//dxlib�̏���������
	SetDrawScreen(DX_SCREEN_BACK);       //����ʂɕ`��
	SetUseZBuffer3D(TRUE);               //z��(���s)�𐳂����`��
	SetWriteZBuffer3D(TRUE);             //z��(���s)�𐳂����`��
	SetBackgroundColor(127, 127, 127);   //�w�i�𖾂邭����(�D�F)
	//--------------------------------�����܂ŏ�����---------------------------

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

	
	
	//--------------------------------�I������-------------------------------
	DxLib_End();// �c�w���C�u�����̏I������
	
	return 0;
}
