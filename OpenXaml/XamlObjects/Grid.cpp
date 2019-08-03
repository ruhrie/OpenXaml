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
		delete RowDefinitions;
		delete ColumnDefinitions;
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
