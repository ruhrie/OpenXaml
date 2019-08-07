#include "OpenXaml/XamlObjects/XamlObject.h"
#include "OpenXaml/XamlObjects/Rectangle.h"
#include "OpenXaml/XamlObjects/TextBlock.h"
#include "OpenXaml/XamlObjects/Button.h"
#include "OpenXaml/Properties/Alignment.h"
#include <algorithm>

using namespace std;

namespace OpenXaml
{
	void XamlObject::SetBoundingBox(coordinate min, coordinate max)
	{
		minCoord = min;
		maxCoord = max;
		for (auto child : Children)
		{
			child->SetBoundingBox(min, max);
		}
		for (auto der : DerivedElements)
		{
			der->SetBoundingBox(min, max);
		}
	}

	XamlObject::XamlObject()
	{
		this->Height = 0;
		this->Width = 0;
		this->VAO = 0;
		this->PixelScale = coordinate{ 0,0 };
		this->minCoord = coordinate{ 0,0 };
		this->maxCoord = coordinate{ 0,0 };
		maxRendered = { 0.0f, 0.0f };
		minRendered = { 0.0f, 0.0f };
	}

	XamlObject::~XamlObject()
	{
		for (auto child : Children)
		{
			delete child;
		}
		for (auto der : DerivedElements)
		{
			delete der;
		}
	}

	void XamlObject::setPixelScale(float x, float y)
	{
		PixelScale = coordinate{ x,y };
		for (int i = 0; i < Children.size(); i++)
		{
			Children[i]->setPixelScale(PixelScale);
		}
	}
	void XamlObject::setPixelScale(coordinate scale)
	{
		PixelScale = scale;
		for (int i = 0; i < Children.size(); i++)
		{
			Children[i]->setPixelScale(PixelScale);
		}
	}

	void XamlObject::setHorizontalAlignment(OpenXaml::HorizontalAlignment alignment)
	{
		this->HorizontalAlignment = alignment;
	}

	void XamlObject::setVerticalAlignment(OpenXaml::VerticalAlignment alignment)
	{
		this->VerticalAlignment = alignment;
	}

	HorizontalAlignment XamlObject::getHorizontalAlignment()
	{
		return this->HorizontalAlignment;
	}

	VerticalAlignment XamlObject::getVerticalAlignment()
	{
		return this->VerticalAlignment;
	}

	void XamlObject::setHeight(int height)
	{
		this->Height = height;
	}
	int XamlObject::getHeight()
	{
		return this->Height;
	}
	void XamlObject::setWidth(int width)
	{
		this->Width = width;
	}
	int XamlObject::getWidth()
	{
		return this->Width;
	}

	coordinate XamlObject::GetMaxRendered()
	{
		coordinate result = { -1.0f, -1.0f };
		for (auto der : DerivedElements)
		{
			result.x = std::max(result.x, der->maxRendered.x);
			result.y = std::max(result.y, der->maxRendered.y);
		}
		return result;
	}

	coordinate XamlObject::GetMinRendered()
	{
		coordinate result = { 1.0f, 1.0f };
		for (auto der : DerivedElements)
		{
			result.x = std::min(result.x, der->minRendered.x);
			result.y = std::min(result.y, der->minRendered.y);
		}
		return result;
	}

	int XamlObject::getColumn()
	{
		return Column;
	}

	int XamlObject::getRow()
	{
		return Row;
	}

	void XamlObject::setRow(int row)
	{
		Row = row;
	}

	void XamlObject::setColumn(int column)
	{
		Column = column;
	}
}

