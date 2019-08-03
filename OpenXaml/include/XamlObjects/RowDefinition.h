#pragma once

namespace OpenXaml {
	class RowDefinition
	{
	public:
		RowDefinition();
		~RowDefinition();
		int GetHeight();
		void SetHeight(int height);
	private:
		int Height;
	};
}