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
            ~ColumnDefinition();
            void setWidth(int width);
            int getWidth();

        private:
            int Width;
        };
    } // namespace Objects
} // namespace OpenXaml