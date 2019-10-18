#pragma once
namespace OpenXaml {
	namespace Objects
	{
		///A row definition for a row definition collection
		class RowDefinition
		{
		public:
			RowDefinition();
			~RowDefinition();
			int getHeight();
			void setHeight(int height);
		private:
			int Height;
		};
	}
}