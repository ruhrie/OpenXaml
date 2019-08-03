#pragma once
#include "XamlObjects/ColumnDefinition.h"

namespace OpenXaml
{
	ColumnDefinition::ColumnDefinition()
	{

	}
	ColumnDefinition::~ColumnDefinition()
	{

	}
	int ColumnDefinition::GetWidth()
	{
		return Width;
	}
	void ColumnDefinition::SetWidth(int width)
	{
		Width = width;
	}
}