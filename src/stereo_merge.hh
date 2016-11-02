#include <utility>

#include "mono_source.hh"
#include "stereo_source.hh"

class StereoMerge : public StereoSource
{
  public:
    StereoMerge(MonoSource* l, MonoSource* r);

    MonoSource* left() { return left_; }
    void left(MonoSource* src) { left_ = src; }

    MonoSource* right() { return right_; }
    void right(MonoSource* src) { right_ = src; }

    virtual std::pair<float, float> Gen();

  private:
    MonoSource* left_;
    MonoSource* right_;
};
