#include <iostream>

class Prototype {
public:
    Prototype(std::string s) : name(s) {}
    Prototype() {}
    void show() { std::cout << "name:" << name << std::endl; }
    virtual Prototype* clone() = 0;
protected:
    std::string name;
};

class Manager : public Prototype {
public:
    Manager(std::string & s) : Prototype(s) {}
    Manager() {}
    virtual Prototype* clone() {
        Manager* manager = new Manager();
        *manager = *this;
        return manager;
    }
};

int main(int argc, char* argv[]) {
    Manager* websoft = new Manager(std::string("web teecher soft"));
    Manager* osssoft = (Manager*)websoft->clone();
    websoft->show();
    osssoft->show();
    return 0;
}