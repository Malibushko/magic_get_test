# magic_get_test
Small repo for testing bug

## CI 
Travis CI [![Build Status](https://travis-ci.org/Malibushko/yatgbotlib.svg?branch=master)](https://travis-ci.org/Malibushko/magic_get_test)  
Appveyor  [![Build Status](https://img.shields.io/appveyor/ci/Malibushko/yatgbotlib/master.svg)](https://ci.appveyor.com/project/Malibushko/magic_get_test)

## Description

magic_get doesnt work with MSVC's implementation of `std::unique_ptr` but it does on GCC and CLang

See CI log for the following code: ```namespace inner {
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
    static_assert (boost::pfr::tuple_size_v<UniquePtr> == 1); // fail on MSVC 
    return 0;
}```

To be more precise, it triggers the following static_assert ```static_assert(
        is_aggregate_initializable_n<type, result>::value,
        "====================> Boost.PFR: Types with user specified constructors (non-aggregate initializable types) are not supported."
    );``` , even though `std::is_aggregate<UniquePtr>::value == true`
