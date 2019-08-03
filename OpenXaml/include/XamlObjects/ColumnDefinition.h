#pragma once

namespace OpenXaml {
	class ColumnDefinition
	{
	public:
		ColumnDefinition();
		~ColumnDefinition();
		void SetWidth(int width);
		int GetWidth();
	private:
		int Width;
	};
}