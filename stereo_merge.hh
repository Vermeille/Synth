#include <utility>

struct StereoSource
{
    virtual std::pair<float, float> Gen() = 0;
};

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

std::pair<float, float> StereoMerge::Gen()
{
    return std::make_pair(left_->Gen(), right_->Gen());
}

StereoMerge::StereoMerge(MonoSource* l, MonoSource* r)
    : left_(l),
    right_(r)
{
}
