#include "DxLib.h"



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





	//--------------------------------�I������-------------------------------
	DxLib_End();// �c�w���C�u�����̏I������
	
	return 0;
}
