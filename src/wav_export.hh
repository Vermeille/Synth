#pragma once

#include <string>
#include "mono_source.hh"

class WavExporter
{
    public:
        WavExporter(MonoSource* src);
        void MkWav(const std::string&, float duration);

    private:
        MonoSource* src_;
};
