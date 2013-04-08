#include <utility>

template <class Param = SInt16, int SR = 44100>
struct StereoSource
{
    typedef typename Param::data_type data_type;

    virtual std::pair<data_type, data_type> Gen() = 0;
};

template <class Param = SInt16, int SR = 44100>
class StereoMerge : public StereoSource<Param, SR>
{
    public:
        typedef MonoSource<Param, SR> MonoSrc;
        typedef typename Param::data_type data_type;
        StereoMerge(MonoSrc* l, MonoSrc* r);

        MonoSrc* left() { return left_; }
        void left(MonoSrc* src) { left_ = src; }

        MonoSrc* right() { return right_; }
        void right(MonoSrc* src) { right_ = src; }

        virtual std::pair<data_type, data_type> Gen();
    private:
        MonoSrc* left_;
        MonoSrc* right_;
};

template <class Param, int SR>
std::pair<typename Param::data_type, typename Param::data_type>
StereoMerge<Param, SR>::Gen()
{
    return std::make_pair(left_->Gen(), right_->Gen());
}

template <class Param, int SR>
StereoMerge<Param, SR>::StereoMerge(MonoSrc* l, MonoSrc* r)
    : left_(l),
    right_(r)
{
}
