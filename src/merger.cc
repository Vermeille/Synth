#include "merger.hh"

float Merger::Gen()
{
    float x = 0;
    for (auto src : src_)
    {
        x += src->Gen();
    }
    return x;
}
