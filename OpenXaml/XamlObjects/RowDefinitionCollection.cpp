#include "XamlObjects/RowDefinitionCollection.h"

namespace OpenXaml
{
	RowDefinitionCollection::RowDefinitionCollection()
	{

	}
	RowDefinitionCollection::~RowDefinitionCollection()
	{
		for (auto child : Children)
		{
			delete child;
		}
	}
}