#pragma once

#include <vector>

#include "mono_source.hh"

class Merger : public MonoSource
{
  public:
    virtual float Gen() override;

    void AddSource(MonoSource* src) { src_.push_back(src); }

  private:
    std::vector<MonoSource*> src_;
};
