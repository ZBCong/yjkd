# 浅析下vs2005下32位程序的多态实现原理

------
## 含有虚函数表的基类的内存结构
![base_class_with_vtbl](https://raw.githubusercontent.com/siren186/yjkd/master/demo/polymorphism/doc/001_%E5%90%AB%E6%9C%89%E8%99%9A%E5%87%BD%E6%95%B0%E8%A1%A8%E7%9A%84%E5%9F%BA%E7%B1%BB%E5%86%85%E5%AD%98%E7%BB%93%E6%9E%84.png)

## 继承但无覆盖情况的子类结构
![child_class_without_override](https://raw.githubusercontent.com/siren186/yjkd/master/demo/polymorphism/doc/002_%E7%BB%A7%E6%89%BF_%E6%97%A0%E8%A6%86%E7%9B%96.png)
