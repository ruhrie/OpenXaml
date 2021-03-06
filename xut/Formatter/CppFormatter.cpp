#include "Formatter/CppFormatter.h"
#include <sstream>
#include <utility>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
using namespace std;
using namespace xercesc;

string GetName(DOMAttr *input, bool root)
{
    string value = XMLString::transcode(input->getNodeValue());
    if (root)
    {
        return "setName(" + value + ");\n";
    }

    return "%name%->setName(\"" + value + "\");\n";
}

string GetNameString(DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    return value;
}

string GetHeight(DOMAttr *input, bool root)
{
    string value = XMLString::transcode(input->getNodeValue());
    if (root)
    {
        return "setHeight(" + to_string(stoi(value)) + ");\n";
    }

    return "%name%->setHeight(" + to_string(stoi(value)) + ");\n";
}

std::string GetFill(DOMAttr *input, bool root)
{
    string value = XMLString::transcode(input->getNodeValue());
    std::istringstream iss(value.substr(1, value.size()));
    unsigned int val;
    iss >> std::hex >> val;
    string result;
    if (root)
    {
        result += "setFill(" + to_string(val) + ");\n";
    }
    else
    {
        result += "%name%->setFill(" + to_string(val) + ");\n";
    }
    return result;
}

string GetWidth(DOMAttr *input, bool root)
{
    string value = XMLString::transcode(input->getNodeValue());
    if (root)
    {
        return "setWidth(" + to_string(stoi(value)) + ");\n";
    }

    return "%name%->setWidth(" + to_string(stoi(value)) + ");\n";
}

string GetHorizontalAlignment(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    if (value == "Right")
    {
        return "%name%->setHorizontalAlignment(OpenXaml::HorizontalAlignment::Right);\n";
    }
    if (value == "Left")
    {
        return "%name%->setHorizontalAlignment(OpenXaml::HorizontalAlignment::Left);\n";
    }
    if (value == "Center")
    {
        return "%name%->setHorizontalAlignment(OpenXaml::HorizontalAlignment::Center);\n";
    }
    if (value == "Stretch")
    {
        return "%name%->setHorizontalAlignment(OpenXaml::HorizontalAlignment::Stretch);\n";
    }

    throw 2;
}

string GetVerticalAlignment(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    if (value == "Top")
    {
        return "%name%->setVerticalAlignment(OpenXaml::VerticalAlignment::Top);\n";
    }
    if (value == "Bottom")
    {
        return "%name%->setVerticalAlignment(OpenXaml::VerticalAlignment::Bottom);\n";
    }
    if (value == "Center")
    {
        return "%name%->setVerticalAlignment(OpenXaml::VerticalAlignment::Center);\n";
    }
    if (value == "Stretch")
    {
        return "%name%->setVerticalAlignment(OpenXaml::VerticalAlignment::Stretch);\n";
    }

    throw 2;
}

std::string GetText(const std::string &input)
{
    return "%name%->setText(\"" + FormatString(input) + "\");\n";
}

std::string GetPlaceholderText(const std::string &input)
{
    return "%name%->setPlaceholderText(\"" + FormatString(input) + "\");\n";
}

std::string GetClickSigniture(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    std::string result = "void " + value + "(std::shared_ptr<OpenXaml::Objects::XamlObject> sender);\n";
    return result;
}

std::string GetClickCall(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    std::string result = "%name%->setOnClick(std::bind(&%master%::" + value + ", this, %name%));\n";
    return result;
}

std::string GetFontFamily(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    return "%name%->setFontFamily(\"" + value + "\");\n";
}
std::string GetFontSize(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    return "%name%->setFontSize(" + value + ");\n";
}

std::string GetTextAlignment(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    if (value == "Left")
    {
        return "%name%->setTextAlignment(TextAlignment::Left);\n";
    }
    if (value == "Right")
    {
        return "%name%->setTextAlignment(TextAlignment::Right);\n";
    }
    if (value == "Center")
    {
        return "%name%->setTextAlignment(TextAlignment::Center);\n";
    }

    throw 2;
}

std::string GetText(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    return GetText(value);
}

std::string GetPlaceholderText(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    return GetPlaceholderText(value);
}

std::string GetTextWrapping(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    if (value == "None")
    {
        return "%name%->setTextWrapping(OpenXaml::TextWrapping::None);\n";
    }
    if (value == "Wrap")
    {
        return "%name%->setTextWrapping(OpenXaml::TextWrapping::Wrap);\n";
    }
    if (value == "WrapWholeWords")
    {
        return "%name%->setTextWrapping(OpenXaml::TextWrapping::WrapWholeWords);\n";
    }

    throw 2;
}

std::string FormatString(const std::string &input)
{
    std::string result;
    for (auto ch : input)
    {
        switch (ch)
        {
            case '\'':
                result += "\\'";
                break;

            case '\"':
                result += "\\\"";
                break;

            case '\?':
                result += "\\?";
                break;

            case '\\':
                result += "\\\\";
                break;

            case '\a':
                result += "\\a";
                break;

            case '\b':
                result += "\\b";
                break;

            case '\f':
                result += "\\f";
                break;

            case '\n':
                result += "\\n";
                break;

            case '\r':
                result += "\\r";
                break;

            case '\t':
                result += "\\t";
                break;

            case '\v':
                result += "\\v";
                break;

            default:
                result += ch;
        }
    }
    return result;
}

std::string GetGridRow(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    return "%name%->setRow(" + value + ");\n";
}

std::string GetGridColumn(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    return "%name%->setColumn(" + value + ");\n";
}

std::string GetVisibility(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    return "%name%->setVisibility(OpenXaml::Visibility::" + value + ");\n";
}

std::string GetMargin(xercesc::DOMAttr *input)
{
    string value = XMLString::transcode(input->getNodeValue());
    if (value.find(',') == string::npos)
    {
        return "%name%->Margin = Thickness(" + value + ");\n";
    }

    return "%name%->Margin = Thickness(" + value + ");\n";
}