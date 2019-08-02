#include "XamlObjects/XamlObject.h"

namespace OpenXaml {
	class Grid : public XamlObject
	{
	public:
		void Draw();
		Grid();
		void Initialize();
		void Update();
		~Grid();
	};
}
