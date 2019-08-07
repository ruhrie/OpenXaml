#pragma once
#include "OpenXaml/XamlObjects/RowDefinition.h"

namespace OpenXaml
{
	RowDefinition::RowDefinition()
	{

	}
	RowDefinition::~RowDefinition()
	{

	}
	void RowDefinition::setHeight(int height)
	{
		Height = height;
	}
	int RowDefinition::getHeight()
	{
		return Height;
	}
}
