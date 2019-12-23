#include <stdio.h>
#include <iostream>
#include <memory>

class Human {
public:
    virtual void talk() = 0;
    virtual void color() = 0;
};

class BlackHuman : public Human {
public:
    virtual void talk() {
        std::cout << "black man talk english ..." << std::endl;
    }
    virtual void color() {
        std::cout << "black man`s color is black ..." << std::endl;
    }
};

class YellowHuman : public Human {
virtual void talk() {
        std::cout << "yellow man talk chinese ..." << std::endl;
    }
    virtual void color() {
        std::cout << "yellow man`s color is yellow ..." << std::endl;
    }
};

class WhiteHuman : public Human {
virtual void talk() {
        std::cout << "white man talk english ..." << std::endl;
    }
    virtual void color() {
        std::cout << "white man`s color is white ..." << std::endl;
    }
};

template <typename T>
class HumanFactory {
public:
    std::shared_ptr<Human> CreateHuman() {
        T man;
        if(typeid(BlackHuman) == typeid(man)) {
            return std::make_shared<BlackHuman>();
        } else if(typeid(YellowHuman) == typeid(man)) {
            return std::make_shared<YellowHuman>();
        } else {
            return std::make_shared<WhiteHuman>();
        }
        return nullptr;
    }
};

int main(int argc, char* argv[]) {
    std::shared_ptr<Human> man = HumanFactory<BlackHuman>().CreateHuman();
    man->color();
    man->talk();
}