#pragma once
#include <vector>
#include <functional>
#include <string>
#include "OpenXaml/Properties/Alignment.h"
#include "OpenXaml/Properties/TextWrapping.h"
#include "OpenXaml/Properties/Visibility.h"
#include "OpenXaml/XamlObjects/Coordinate.h"

namespace OpenXaml
{
	namespace Objects
	{
		/// An abstract base class for all Xaml Objects
		class XamlObject
		{
		public:
			virtual void Draw() = 0; ///The draw call which actually renders the object.
			std::vector<XamlObject*> Children; ///The child objects to the current xaml element.
			virtual void Initialize() = 0; ///Currently responsible for initializing the OpenGL attributes. Due to be removed soon.
			virtual void Update();
			XamlObject();
			~XamlObject();
			void setHorizontalAlignment(HorizontalAlignment alignment);
			void setVerticalAlignment(VerticalAlignment alignment);
			HorizontalAlignment getHorizontalAlignment();
			VerticalAlignment getVerticalAlignment();
			void setHeight(int height);
			int getHeight();
			void setWidth(int width);
			int getWidth();
			int getColumn();
			int getRow();
			void setRow(int row);
			void setColumn(int column);
			void setVisibility(OpenXaml::Visibliity visibility);
			OpenXaml::Visibliity getVisibility();
			virtual void SetBoundingBox(coordinate min, coordinate max); ///Sets the bounding box for rendering the object (not where it actually renders).
		protected:
			coordinate minCoord;
			coordinate maxCoord;
			coordinate minRendered;
			coordinate maxRendered;
			int Height;
			int Width;
			OpenXaml::Visibliity Visibility;
			HorizontalAlignment HorizontalAlignment = HorizontalAlignment::Stretch;
			VerticalAlignment VerticalAlignment = VerticalAlignment::Stretch;
			unsigned int VAO;
			std::vector<XamlObject*> DerivedElements;
			coordinate GetMaxRendered(); ///Gets the upper right corner of the actually rendered object
			coordinate GetMinRendered(); ///Gets the lower left corner of the actually rendered object
		private:
			XamlObject& operator=(const XamlObject&);
			int Column = 0;
			int Row = 0;
		};
	}	
} // namespace OpenXaml
