#include "stdafx.h"
#pragma warning(disable:4312)
#include "empty_class.h"
#include "virtual_base_class.h"
#include "child_class.h"

/**
 * ǳ����vs2005��32λ����Ķ�̬ʵ��ԭ��
 **/

TEST(POLYMORPHISM, EMPTY_CLASS)
{ CEmptyClassClient::main(); }

TEST(POLYMORPHISM, BASE_VIRTUAL_CLASS)
{ CVirtualBaseClassClient::main(); }

TEST(POLYMORPHISM, CHILD_VIRTUAL_CLASS)
{ CChildClassClient::main(); }
