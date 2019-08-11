#pragma once
#include <vector>
#include "OpenXaml/XamlObjects/RowDefinition.h"
#include "OpenXaml/XamlObjects/XamlObject.h"
namespace OpenXaml
{
	namespace Objects
	{
		///A renderable wrapper for row definitions
		class RowDefinitionCollection : public XamlObject
		{
		public:
			RowDefinitionCollection();
			~RowDefinitionCollection();
			std::vector<RowDefinition*> Children;
			void Draw();
			void Initialize();
			void Update();
		};
	}
}