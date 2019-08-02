#include "XamlObjects/Grid.h"

namespace OpenXaml {
	void Grid::Draw()
	{
		for (auto child : Children)
		{
			child->Draw();
		}
	}
	Grid::Grid()
	{

	}
	Grid::~Grid()
	{
		for (auto row : RowDefinitions)
		{
			delete row;
		}
		for (auto col : ColumnDefinitions)
		{
			delete col;
		}
	}
	void Grid::Initialize()
	{
		for (auto child : Children)
		{
			child->Initialize();
		}
	}
	void Grid::Update()
	{
		for (auto child : Children)
		{
			child->Update();
		}
	}
}
