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
#include "observer.hpp"
#include "strategy.hpp"
#include "iterator.hpp"
#include "builder.hpp"
#include "bridge.hpp"
#include "decorator.hpp"
#include "mediator.hpp"

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

TEST(DESIGN_PATTERNS, OBSERVER)
{
    CObserverClient::main();
}

TEST(DESIGN_PATTERNS, STRATEGY)
{
    CStrategyClient::main();
}

TEST(DESIGN_PATTERNS, ITERATOR)
{
    CIteratorClient::main();
}

TEST(DESIGN_PATTERNS, BUILDER)
{
    CBuilderClient::main();
}

TEST(DESIGN_PATTERNS, BRIDGE)
{
    CBridgeClient::main();
}

TEST(DESIGN_PATTERNS, DECORATOR)
{
    CDecoratorClient::main();
}

TEST(DESIGN_PATTERNS, MEDIATOR)
{
    CMediatorClient::main();
}
