#include "XamlObjects/ColumnDefinitionCollection.h"

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
}