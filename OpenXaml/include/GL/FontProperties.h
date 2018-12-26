#ifndef FONTPROPERTIES_H
#define FONTPROPERTIES_H
#include <string>
struct FontProperties
{
	std::string name;
	float size = 0;
	bool bold = false;
	bool italic = false;

	bool operator<(const FontProperties& A) const
	{
		if (name < A.name)
		{
			return true;
		}
		else if (size < A.size)
		{
			return true;
		}
		else if (bold < A.bold)
		{
			return true;
		}
		else if (italic < A.italic)
		{
			return true;
		}
		return false;
	}
};

#endif