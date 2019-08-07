#include "OpenXaml/XamlObjects/ColumnDefinitionCollection.h"

namespace OpenXaml
{
	ColumnDefinitionCollection::ColumnDefinitionCollection()
	{

	}
	ColumnDefinitionCollection::~ColumnDefinitionCollection()
	{
		for (auto child : Children)
		{
			delete child;
		}
	}

	void ColumnDefinitionCollection::Draw()
	{

	}
	void ColumnDefinitionCollection::Initialize()
	{

	}
	void ColumnDefinitionCollection::Update()
	{

	}
}