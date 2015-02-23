#pragma once

#include "DxLib.h"

template <typename T>
class Vector2
{
public:
	T x;
	T y;
};

template <typename T>
class Vector4
{
public:
	T x;
	T y;
	T z;
	T w;
};

template <typename T>
VECTOR vector2ToVector( Vector2<T> vector ) { return VGet( static_cast<float>(vector.x), static_cast<float>(vector.y), 0.0f ); }