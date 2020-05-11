#pragma once
#include <string>
#include <xercesc/dom/DOMAttr.hpp>

/// This file contains helper methods that convert xml to cpp strings
std::string GetNameString(xercesc::DOMAttr *input);
std::string GetName(xercesc::DOMAttr *input, bool root = false);
std::string GetHeight(xercesc::DOMAttr *, bool root = false);
std::string GetFill(xercesc::DOMAttr *, bool root = false);
std::string GetWidth(xercesc::DOMAttr *, bool root = false);
std::string GetHorizontalAlignment(xercesc::DOMAttr *);
std::string GetVerticalAlignment(xercesc::DOMAttr *);
std::string GetTextWrapping(xercesc::DOMAttr *);
std::string GetTextAlignment(xercesc::DOMAttr *);
std::string GetFontFamily(xercesc::DOMAttr *);
std::string GetFontSize(xercesc::DOMAttr *);
std::string GetText(const std::string &input);
std::string GetText(xercesc::DOMAttr *input);
std::string GetPlaceholderText(xercesc::DOMAttr *input);
std::string GetClickSigniture(xercesc::DOMAttr *input);
std::string GetClickCall(xercesc::DOMAttr *input);
std::string FormatString(const std::string &input);
std::string GetGridRow(xercesc::DOMAttr *input);
std::string GetGridColumn(xercesc::DOMAttr *input);
std::string GetVisibility(xercesc::DOMAttr *input);
std::string GetMargin(xercesc::DOMAttr *input);