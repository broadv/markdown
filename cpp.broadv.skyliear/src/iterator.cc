#include <iostream>
#include <stdlib.h>
#include <vector>

/*
    核心功能:
        a.提供一种特定的方法，顺序访问容器中的各个元素，但不会暴露容器的内部设计细
    节，又可以让外部的代码透明的访问集合内部的所有元素
*/

template<typename _Ty>
class iterator {
public:
    virtual bool hasNext() = 0;
    virtual _Ty& next() = 0;
};
template<typename _Ty>
class CArray {
public:
    void push(_Ty &&val) { vecs.push_back(val); }
    class ConcreteIterator : public iterator<_Ty> {
    public:
        ConcreteIterator(CArray<_Ty>& array) : _array(array) {}
        virtual bool hasNext() {
            return position < _array.vecs.size() ? true : false;
        }
        virtual _Ty& next() {
            _Ty& val = _array.vecs[position++];
            return val;
        }
    private:
        std::size_t position;
        CArray<_Ty> &_array;
    };
    iterator<_Ty>* begin() { return new ConcreteIterator(*this); }
private:
    std::vector<_Ty> vecs;
};

int main(int argc, char* argv[]) {
    CArray<int> users;
    users.push(1);
    users.push(2);
    users.push(3);
    iterator<int> *iter = users.begin();
    while (iter->hasNext())
    {
        int val = iter->next();
        std::cout << "val: " << val << " ";
    }
    std::cout << std::endl;    
    return 0;
}