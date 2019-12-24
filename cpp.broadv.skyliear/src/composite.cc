#include <iostream>
/*
 部分整体模式，使得用户对单个对象和组合对象的使用具有一致性
*/
class ICorp {
public:
    virtual std::string info() = 0;
};
class ILeaf : public ICorp {

};

