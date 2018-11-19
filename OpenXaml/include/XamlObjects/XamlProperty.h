#ifndef XAMLPROPERTY_H
#define XAMLPROPERTY_H
#include <functional>
template<typename T>
class XamlProperty
{
public: 
	void operator=(T value)
	{
		if (Value != value)
		{
			Value = value;
			if (onPropertyChanged != 0)
			{
				onPropertyChanged();
			}
		}
	}
	XamlProperty<T>(T value)
	{
		Value = value;
	}
	
	operator T()
	{
		return Value;
	}


	XamlProperty<T>()
	{

	}
	std::function<void(void)> onPropertyChanged = 0;
private:
	T Value;
};
#endif