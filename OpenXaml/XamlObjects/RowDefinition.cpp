#pragma once
#include "XamlObjects/RowDefinition.h"

namespace OpenXaml
{
	RowDefinition::RowDefinition()
	{

	}
	RowDefinition::~RowDefinition()
	{

	}
	void RowDefinition::SetHeight(int height)
	{
		Height = height;
	}
	int RowDefinition::GetHeight()
	{
		return Height;
	}
}
