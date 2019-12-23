#include <iostream>

class Singleton {
private:
    Singleton() = default;
    Singleton(const Singleton& other) = delete;
    Singleton& operator = (const Singleton& other) = delete;
public:
    static Singleton* instance() {
        if(m_instance == nullptr) {
            m_instance = new Singleton();
        }
        return m_instance;
    }
    void show() {
        std::cout << "this is a singleton..." << std::endl;
    }
private:
    static Singleton* m_instance;
};

Singleton* Singleton::m_instance = nullptr;

class msingleton {
public:
    static msingleton& instance() {
        static msingleton ms;
        return ms;
    }
    void show() { std::cout << "msingleton ......" << std::endl; }
private:
    msingleton() = default;
    msingleton(const msingleton&) = delete;
    msingleton& operator = (const msingleton&) = delete;
};

template<typename T>
class singletons {
public:
    static T& instance() noexcept(std::is_nothrow_constructible<T>::value) {
        static T inst{token()};
        return inst;
    }
protected:
    singletons() noexcept = default;
    singletons(const singletons&) = delete;
    singletons& operator = (const singletons&) = delete;
    struct token {};
/*
public:
    singletons(token) {}
*/    
};

class DerivedInstance : public singletons<DerivedInstance> {
// 需要将基类定义为友元，才能调用子类的私有构造函数
//friend class singletons;
public:
    // 引入token,这样不需要引入友元
    DerivedInstance(token) {};
private:
    DerivedInstance(const DerivedInstance&) = delete;
    DerivedInstance& operator = (DerivedInstance&) = delete;
public:
    void show() { std::cout << "derived instance ..." << std::endl; }
};

int main(int argc, char* argv[]) {
    Singleton::instance()->show();
    msingleton::instance().show();
    DerivedInstance::instance().show();
    return 0;
}