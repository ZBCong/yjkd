#include "stdafx.h"
#include "singleton.hpp"

TEST(DESIGN_PATTERNS, SINGLETON)
{
    CLazyMan::Instance().DoSomething();
    y::Singleton<CHungryMan>::instance().DoSomething();
}
