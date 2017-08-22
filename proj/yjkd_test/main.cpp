#include "stdafx.h"
#include "interpreter.hpp"

int main(int argc, char **argv)
{
    CInterpreterClient::main();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
