# C++11 之 delete 和 default
在C++11中，新的关键字"delete"被引入，用于禁用不想被调用的方法
```bash
void function() = delete
```
## 使用场景
+ 删除编译器自动生成的方法,如拷贝构造，赋值构造，Move Constructor、move assignment operator和缺省构造函数
+ 删除成员函数以防止类型转换
+ 删除特定的模板
+ Restrict Object creation on Heap by deleting new operator for class
### 删除拷贝构造和赋值操作符
```C++
class User {
public:
    User(int id, std::string name) : userId(id), userName(name) {}
    User(const User& other) = delete;
    User & operator = (const User & other) = delete;
private:
    int userId;
    std::string userName;
};
```
在上面的类User中，拷贝构造和赋值构造方法被删除，如果尝试调用删除的方法，它将生成编译时错误
```
User john(3, "John");
User bjohn = john;
```