// FILE:
//		Source/Scene/Lights/DirectionalLight.h
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

#include "Scene/Lights/Light.h"

#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

class directionalLight : public Light
{
	directionalLight() {};
	virtual ~directionalLight() {};

	// Just need direction for light
	DirectX::XMFLOAT3 lightDirection;
};


#endif // !DIRECTIONLIGHT_H