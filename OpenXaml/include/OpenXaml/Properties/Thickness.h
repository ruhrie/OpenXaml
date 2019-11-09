#pragma once

struct Thickness
{
    int Left;
    int Top;
    int Right;
    int Bottom;
    Thickness()
    {
        Left = 0;
        Right = 0;
        Top = 0;
        Bottom = 0;
    }
    Thickness(int param)
    {
        Left = param;
        Right = param;
        Top = param;
        Bottom = param;
    }
    Thickness(int left, int top, int right, int bottom)
    {
        Left = left;
        Top = top;
        Right = right;
        Bottom = bottom;
    }
};