#include "OpenXaml/XamlObjects/ColumnDefinitionCollection.h"

namespace OpenXaml
{
	namespace Objects
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
}