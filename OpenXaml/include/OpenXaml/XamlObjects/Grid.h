#pragma once
#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/XamlObjects/RowDefinitionCollection.h"
#include "OpenXaml/XamlObjects/ColumnDefinitionCollection.h"
namespace OpenXaml {
	namespace Objects
	{
		///A grid for rendering xaml objects
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
			void SetBoundingBox(vec2<float> min, vec2<float> max);
		};
	}	
}
