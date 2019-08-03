#include "XamlObjects/Grid.h"
#include <vector>
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
	void Grid::SetBoundingBox(coordinate min, coordinate max)
	{
		std::vector<int> rowHeights;
		int position = 0;
		for (auto row : RowDefinitions->Children)
		{
			rowHeights.push_back(row->getHeight());
		}
		std::vector<int> columnWidths;
		for (auto col : ColumnDefinitions->Children)
		{
			columnWidths.push_back(col->getWidth());
		}

		for (auto child : Children)
		{
			int row = child->getRow();
			int col = child->getColumn();

		}
	}
}
