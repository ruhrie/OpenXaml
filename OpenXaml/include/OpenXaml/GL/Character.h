#pragma once
namespace OpenXaml
{
    ///A generic wrapper for the opengl properties of a character
    struct Character
    {
        unsigned int TextureID;
        unsigned int Width;
        unsigned int Height;
        int BearingX;
        int BearingY;
        long AdvanceX;
        long AdvanceY;
    };
} // namespace OpenXaml