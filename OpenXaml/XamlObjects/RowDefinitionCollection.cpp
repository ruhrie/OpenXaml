#include "OpenXaml/XamlObjects/RowDefinitionCollection.h"

namespace OpenXaml
{
	namespace Objects
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
		void RowDefinitionCollection::Draw()
		{

		}
		void RowDefinitionCollection::Initialize()
		{

		}
		void RowDefinitionCollection::Update()
		{

		}
	}
}