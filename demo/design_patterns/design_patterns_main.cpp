#include "stdafx.h"
#include "singleton.hpp"
#include "factory_method.hpp"
#include "facade.hpp"
#include "template_method.hpp"
#include "abstract_factory.hpp"
#include "proxy.hpp"
#include "composite.hpp"
#include "adapter.hpp"
#include "prototype.hpp"
#include "command.hpp"

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

TEST(DESIGN_PATTERNS, COMPOSITE)
{
    CCompositeClient::main();
}

TEST(DESIGN_PATTERNS, ADAPTOR)
{
    CAdapterClient::main();
}

TEST(DESIGN_PATTERNS, PROTOTYPE)
{
    CPrototypeClient::main();
}

TEST(DESIGN_PATTERNS, COMMAND)
{
    CCommandClient::main();
}
