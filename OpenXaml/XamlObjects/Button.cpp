#include "OpenXaml/XamlObjects/Button.h"
#include "OpenXaml/Environment/Environment.h"
#include "OpenXaml/Environment/Window.h"
#include "OpenXaml/XamlEvents/XamlEvent.h"
#include <sstream>

using namespace std;

namespace OpenXaml
{
    namespace Objects
    {
        void Button::Draw()
        {
            Frame->Draw();
            Label->Draw();
        }
        void Button::Initialize()
        {
            Frame->Initialize();
            Label->Initialize();
            Update();
        }

        void Button::Update()
        {
            Label->setText(Text);
            auto desiredDimensions = Label->getDesiredDimensions();
            if (Width == 0)
            {
                int w = desiredDimensions.x;
                Frame->setWidth(w);
                Label->setWidth(w);
            }
            if (Height == 0)
            {
                int h = desiredDimensions.y;
                Frame->setHeight(h);
                Label->setHeight(h);
            }
            Label->setVerticalAlignment(VerticalAlignment);
            Label->setHorizontalAlignment(HorizontalAlignment);
            Label->setTextAlignment(TextAlignment::Center);
            Label->Update();
            Frame->setHorizontalAlignment(HorizontalAlignment);
            Frame->setVerticalAlignment(VerticalAlignment);
            Frame->setFill(Fill);
            Frame->Update();
            maxRendered = GetMaxRendered();
            minRendered = GetMinRendered();
        }
        Button::Button()
        {
            Label = new TextBlock();
            Frame = new Rectangle();
            DerivedElements.push_back(Label);
            DerivedElements.push_back(Frame);
        }
        Button::~Button()
        {
            XamlObject::~XamlObject();
        }

        void Button::setFill(unsigned int fill)
        {
            this->Fill = fill;
        }
        unsigned int Button::getFill()
        {
            return this->Fill;
        }
        void Button::setText(std::string content)
        {
            this->Text = content;
        }
        std::string Button::getText()
        {
            return this->Text;
        }
    } // namespace Objects
} // namespace OpenXaml
