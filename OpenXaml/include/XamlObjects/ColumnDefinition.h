#pragma once

namespace OpenXaml {
	class ColumnDefinition
	{
	public:
		ColumnDefinition();
		~ColumnDefinition();
		void setWidth(int width);
		int getWidth();
	private:
		int Width;
	};
}