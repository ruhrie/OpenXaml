#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/XamlObjects/RowDefinitionCollection.h"
#include "OpenXaml/XamlObjects/ColumnDefinitionCollection.h"
namespace OpenXaml {
	class Grid : public XamlObject
	{
	public:
		void Draw();
		Grid();
		void Initialize();
		void Update();
		~Grid();
		ColumnDefinitionCollection* ColumnDefinitions = NULL;
		RowDefinitionCollection* RowDefinitions = NULL;
	protected:
		void SetBoundingBox(coordinate min, coordinate max);
	};
}
