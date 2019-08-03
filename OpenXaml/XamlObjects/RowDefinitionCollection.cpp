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