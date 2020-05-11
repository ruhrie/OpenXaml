#pragma once
namespace OpenXaml
{
    namespace Objects
    {
        ///A column definition for a column definition collection
        class ColumnDefinition
        {
        public:
            ColumnDefinition();
            ~ColumnDefinition() = default;
            void setWidth(int width);
            int getWidth() const;

        private:
            int Width;
        };
    } // namespace Objects
} // namespace OpenXaml