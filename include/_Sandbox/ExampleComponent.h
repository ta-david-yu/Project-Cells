#pragma once

#include "Core/EditorComponent.h"

namespace DYE::DYEditor::Template
{
	DYE_COMPONENT("Example Component", DYE::DYEditor::Template::ExampleComponent)
	struct ExampleComponent
	{
		DYE_PROPERTY()
		DYE::Int32 IntegerVariable;
	};


	DYE_COMPONENT("ComponentWithAllPrimitiveProperties", DYE::DYEditor::Template::ComponentWithAllPrimitiveProperties)
	struct ComponentWithAllPrimitiveProperties
	{
		DYE_PROPERTY()
		DYE::Char CharVar = 'a';

		DYE_PROPERTY()
		DYE::Bool BoolVar = false;

		DYE_PROPERTY()
		DYE::Int32 Int32Var;

//	DYE_PROPERTY()
//	DYE::Int64 Int64Var;
//
//	DYE_PROPERTY()
//	DYE::Uint8 Uint8Var;
//
//	DYE_PROPERTY()
//	DYE::Uint16 Uint16Var;
//
//	DYE_PROPERTY()
//	DYE::Uint32 Uint32Var;
//
//	DYE_PROPERTY()
//	DYE::Uint64 Uint64Var;

		DYE_PROPERTY()
		DYE::Float FloatVar;

//	DYE_PROPERTY()
//	DYE::Double DoubleVar;

		DYE_PROPERTY()
		DYE::Vector2 Vector2Var;

		DYE_PROPERTY()
		DYE::Vector3 Vector3Var;

		DYE_PROPERTY()
		DYE::Vector4 Vector4Var;

		DYE_PROPERTY()
		DYE::Color4 Color4Var;

		DYE_PROPERTY()
		DYE::String StringVar;

		DYE_PROPERTY()
		DYE::Quaternion QuaternionVar;
	};
}