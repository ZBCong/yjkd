#include "stdafx.h"
#include "singleton.hpp"
#include "factory_method.hpp"
#include "facade.hpp"
#include "template_method.hpp"
#include "abstract_factory.hpp"
#include "proxy.hpp"

TEST(DESIGN_PATTERNS, SINGLETON)
{
    CSingletonClient::main();
}

TEST(DESIGN_PATTERNS, FACTORY_METHOD)
{
    CFactoryMethodClient::main();
}

TEST(DESIGN_PATTERNS, FACADE)
{
    CFacadeClient::main();
}

TEST(DESIGN_PATTERNS, TEMPLATE_METHOD)
{
    CTemplateMethodClient::main();
}

TEST(DESIGN_PATTERNS, ABSTRACT_FACTORY)
{
    CAbstractFactoryClient::main();
}

TEST(DESIGN_PATTERNS, PROXY)
{
    CProxyClient::main();
}