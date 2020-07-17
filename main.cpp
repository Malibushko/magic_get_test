#include <iostream>
#include <memory>
#include <boost/pfr.hpp>
#include <boost/move/unique_ptr.hpp>

namespace inner {
class MoveOnly {
public:
    MoveOnly() = default;
    MoveOnly(MoveOnly&&) = default;
    MoveOnly& operator=(MoveOnly&&) = default;
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;
};
}

struct UniquePtr {
    std::unique_ptr<int> a;
};
struct BoostUniquePtr {
    boost::movelib::unique_ptr<int> a;
};

struct MoveWrapper {
    inner::MoveOnly v;
};

int main()
{
    static_assert (boost::pfr::tuple_size_v<BoostUniquePtr> == 1);
    static_assert (boost::pfr::tuple_size_v<MoveWrapper> == 1);
    static_assert (boost::pfr::tuple_size_v<UniquePtr> == 1);
    return 0;
}
