#pragma once

#include "mono_source.hh"
#include <string>

class WavExporter
{
  public:
    WavExporter(MonoSource* src);
    void MkWav(const std::string&, float duration);

  private:
    MonoSource* src_;
};
