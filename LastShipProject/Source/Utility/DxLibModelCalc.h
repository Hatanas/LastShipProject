#pragma once

#include "DxLib.h"

//�RD�̃��[���h�ϊ��s�񂩂番��������v�Z����


class DxLibModelCalc
{
public:
	static const VECTOR ORIGIN;//���_
	static const VECTOR X_AXIS;//x��
	static const VECTOR Y_AXIS;//y��
	static const VECTOR Z_AXIS;//z��

	//�s�񂩂�x�����̊g�嗦�𓾂�
	static float getScaleX(MATRIX m);

	//�s�񂩂�y�����̊g�嗦�𓾂�
	static float getScaleY(MATRIX m);

	//�s�񂩂�z�����̊g�嗦�𓾂�
	static float getScaleZ(MATRIX m);

	//�s�񂩂�ʒu�x�N�g���𓾂�
	static VECTOR getPosition(MATRIX m);
};
