#pragma once

namespace OpenXaml {
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