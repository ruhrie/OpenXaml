#include "OpenXaml/XamlObjects/Grid.h"
#include "OpenXaml/Environment/Window.h"
#include <vector>
using namespace std;
namespace OpenXaml::Objects
{

    void Grid::Draw()
    {
        for (const auto &child : Children)
        {
            child->Draw();
        }
    }
    Grid::Grid()
    {
        ColumnDefinitions = make_shared<ColumnDefinitionCollection>();
        RowDefinitions = make_shared<RowDefinitionCollection>();
    }
    Grid::~Grid()
    {
        XamlObject::~XamlObject();
    }
    void Grid::Initialize()
    {
        for (const auto &child : Children)
        {
            child->Initialize();
        }
    }
    void Grid::Update()
    {
        for (const auto &child : Children)
        {
            child->Update();
        }
    }
    void Grid::SetBoundingBox(vec2<float> min, vec2<float> max)
    {
        std::vector<float> rowHeights;
        std::vector<float> rowStarts;
        if (RowDefinitions != nullptr)
        {
            float position = max.y;
            for (const auto &row : RowDefinitions->Children)
            {
                auto height = (float)row->getHeight();
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
        if (ColumnDefinitions != nullptr)
        {
            float position = min.x;
            for (const auto &col : ColumnDefinitions->Children)
            {
                float width = col->getWidth();
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

        for (const auto &child : Children)
        {
            int row = child->getRow();
            int col = child->getColumn();
            vec2<float> min = {
                columnStarts[col],
                rowStarts[row]};
            vec2<float> max = {
                min.x + columnWidths[col],
                min.y + rowHeights[row]};
            child->SetBoundingBox(min, max);
        }
    }
} // namespace OpenXaml::Objects
