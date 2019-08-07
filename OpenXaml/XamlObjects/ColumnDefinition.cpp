#pragma once
#include "OpenXaml/XamlObjects/ColumnDefinition.h"

namespace OpenXaml
{
	ColumnDefinition::ColumnDefinition()
	{

	}
	ColumnDefinition::~ColumnDefinition()
	{

	}
	int ColumnDefinition::getWidth()
	{
		return Width;
	}
	void ColumnDefinition::setWidth(int width)
	{
		Width = width;
	}
}