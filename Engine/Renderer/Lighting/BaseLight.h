// FILE:
//		Source/Scene/Lights/Light.h
//
// DESCRIPTION:
//
//
// Functions:
// 
//
// ERRORS:
//
//
// NOTES: 
//
//
// Copyright (C) 2016, Haval Ahmed


#include "Linker/Header_File_Linker.h"

#ifndef LIGHT_H
#define LIGHT_H

class Light
{
public:
	// Constructors
	Light() { ZeroMemory(this, sizeof(this)); };
	virtual ~Light() {};

	// Base variables
	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 specular;
	float lightPadding;
};









#endif // !LIGHT_H