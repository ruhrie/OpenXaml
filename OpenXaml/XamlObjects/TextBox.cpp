#include "OpenXaml/XamlObjects/TextBox.h"
#include "OpenXaml/Environment/Environment.h"
#include "OpenXaml/XamlEvents/XamlEvents.h"
#include "OpenXaml\Environment\Window.h"
namespace OpenXaml
{
    namespace Objects
    {
        TextBox::TextBox()
        {
            Frame = new Rectangle();
            PlaceholderTextTextBlock = new TextBlock();
            TextTextBlock = new TextBlock();
            TextTextBlock->setText(Text);
            TextTextBlock->setTextAlignment(TextAlignment::Start);
            TextTextBlock->setHorizontalAlignment(HorizontalAlignment::Left);
            PlaceholderTextTextBlock->setTextAlignment(TextAlignment::Start);
            PlaceholderTextTextBlock->setText(PlaceholderText);
            PlaceholderTextTextBlock->setHorizontalAlignment(HorizontalAlignment::Left);
            DerivedElements.push_back(PlaceholderTextTextBlock);
            DerivedElements.push_back(TextTextBlock);
            DerivedElements.push_back(Frame);
            Events::AddEvent(Events::XamlEvent::TextEvent, this);
            Events::AddEvent(Events::XamlEvent::ClickEvent, this);
        }
        TextBox::~TextBox()
        {
            Events::RemoveEvent(Events::XamlEvent::TextEvent, this);
            Events::RemoveEvent(Events::XamlEvent::ClickEvent, this);
            delete Frame;
            delete PlaceholderTextTextBlock;
            delete TextTextBlock;
            XamlObject::~XamlObject();
        }

        void TextBox::setOnClick(std::function<void(XamlObject *)> func)
        {
            OnClick = func;
        }

        void TextBox::Initialize()
        {
            Frame->Initialize();
            PlaceholderTextTextBlock->Initialize();
            TextTextBlock->Initialize();
            Update();
        }
        void TextBox::Draw()
        {
            Frame->Draw();
            if (Text.empty())
            {
                PlaceholderTextTextBlock->Draw();
            }
            else
            {
                TextTextBlock->setText(Text);
                TextTextBlock->Draw();
            }
        }
        void TextBox::Update()
        {
            auto desiredDimensions = PlaceholderTextTextBlock->getDesiredDimensions();
            if (Width == 0)
            {
                int w = desiredDimensions.x / OpenXaml::Environment::window->xScale;
                Frame->setWidth(w);
                PlaceholderTextTextBlock->setWidth(w);
                TextTextBlock->setWidth(w);
            }
            if (Height == 0)
            {
                int h = desiredDimensions.y / OpenXaml::Environment::window->yScale;
                Frame->setHeight(h);
                PlaceholderTextTextBlock->setHeight(h);
                TextTextBlock->setHeight(h);
            }
            Frame->setFill(0xFFFFFFFF);
            Frame->setHorizontalAlignment(HorizontalAlignment);
            Frame->setVerticalAlignment(VerticalAlignment);
            Frame->Update();
            auto min = Frame->GetMinRendered();
            auto max = Frame->GetMaxRendered();
            PlaceholderTextTextBlock->SetBoundingBox(min, max);
            PlaceholderTextTextBlock->Update();
            TextTextBlock->setText(Text);
            TextTextBlock->SetBoundingBox(min, max);
            TextTextBlock->Update();
            XamlObject::Update();
        }
        void TextBox::setPlaceholderText(std::string placeholderText)
        {
            PlaceholderText = placeholderText;
            PlaceholderTextTextBlock->setText(placeholderText);
        }
        std::string TextBox::getPlaceholderText()
        {
            return PlaceholderText;
        }
        void TextBox::setText(std::string text)
        {
            Text = text;
            Update();
        }
        std::string TextBox::getText()
        {
            return Text;
        }

        void TextBox::TextUpdate(std::string text)
        {
            if (Environment::ActiveElement == this)
            {
                Text += text;
                Update();
            }
        }
    } // namespace Objects
} // namespace OpenXaml