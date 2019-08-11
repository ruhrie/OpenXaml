#include "OpenXaml/XamlObjects/Grid.h"
#include <vector>
namespace OpenXaml
{
	namespace Objects
	{

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
			std::vector<float> rowHeights;
			std::vector<float> rowStarts;
			if (RowDefinitions != NULL)
			{
				float position = max.y;
				float yScale = PixelScale.y;
				for (auto row : RowDefinitions->Children)
				{
					float height = row->getHeight() * yScale;
					rowHeights.push_back(height);
					position -= height;
					rowStarts.push_back(position);
				}
			}
			else
			{
				rowHeights.push_back(max.y - min.y);
				rowStarts.push_back(min.y);
			}

			std::vector<float> columnWidths;
			std::vector<float> columnStarts;
			if (ColumnDefinitions != NULL)
			{
				float position = min.x;
				float xScale = PixelScale.x;
				for (auto col : ColumnDefinitions->Children)
				{
					float width = col->getWidth() * xScale;
					columnWidths.push_back(width);
					columnStarts.push_back(position);
					position += width;
				}
			}
			else
			{
				columnWidths.push_back(max.x - min.x);
				columnStarts.push_back(max.x);
			}


			for (auto child : Children)
			{
				int row = child->getRow();
				int col = child->getColumn();
				coordinate min = {
					columnStarts[col],
					rowStarts[row]
				};
				coordinate max = {
					min.x + columnWidths[col],
					min.y + rowHeights[row]
				};
				child->SetBoundingBox(min, max);
			}
		}
	}
}
