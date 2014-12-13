#include "./../DxLibModelCalc.h"


const VECTOR DxLibModelCalc::ORIGIN = VGet(0.0f, 0.0f, 0.0f);
const VECTOR DxLibModelCalc::X_AXIS = VGet(1.0f, 0.0f, 0.0f);
const VECTOR DxLibModelCalc::Y_AXIS = VGet(0.0f, 1.0f, 0.0f);
const VECTOR DxLibModelCalc::Z_AXIS = VGet(0.0f, 0.0f, 1.0f);

float DxLibModelCalc::getScaleX(MATRIX m)
{
	return VSize(VGet(m.m[0][0], m.m[0][1], m.m[0][2]));
}

float DxLibModelCalc::getScaleY(MATRIX m)
{
	return VSize(VGet(m.m[1][0], m.m[1][1], m.m[1][2]));
}

float DxLibModelCalc::getScaleZ(MATRIX m)
{
	return VSize(VGet(m.m[2][0], m.m[2][1], m.m[2][2]));
}

VECTOR DxLibModelCalc::getPosition(MATRIX m)
{
	return VGet(m.m[3][0], m.m[3][1], m.m[3][2]);
}


