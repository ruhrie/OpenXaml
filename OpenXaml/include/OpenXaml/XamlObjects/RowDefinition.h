#pragma once
namespace OpenXaml
{
    namespace Objects
    {
        ///A row definition for a row definition collection
        class RowDefinition
        {
        public:
            RowDefinition();
            ~RowDefinition() = default;
            int getHeight() const;
            void setHeight(int height);

        private:
            int Height;
        };
    } // namespace Objects
} // namespace OpenXaml