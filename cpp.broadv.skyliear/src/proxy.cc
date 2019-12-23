#include <iostream>
#include <string>
#include <memory>

/*
    普通代理
    强制代理
    动态代理
*/
class IGamePlayer {
public:
    virtual void login(const std::string & user, const std::string & password) = 0;
    virtual void kill(const std::string & user, const std::string & password) = 0;
    virtual void upgrade(const std::string & user, const std::string & password) = 0;
};

class GamePlayer : public IGamePlayer {
public:
    GamePlayer(const std::string& n) : name(n) {}
    virtual void login(const std::string & user, const std::string & password) override {
        std::cout << "user:" + user << " player" << name << " login success" << std::endl;
    }
    
    virtual void kill(const std::string & user, const std::string & password) override {
        std::cout << this->name << " kill boss" << std::endl;
    }

    virtual void upgrade(const std::string & user, const std::string & password) override {
        std::cout << "user:" + user << " player:" << name << " upgrade" << std::endl;
    }
private:
    std::string name;
};

class GamePlayerProxy : public IGamePlayer {
public:
    GamePlayerProxy(const std::string& name) {
        try {
            if(nullptr == player) {
                player = std::make_shared<GamePlayer>(name);
            }
        }
        catch(std::bad_alloc) {
            std::cerr << "bad alloc memory ......" << std::endl;
        }
    }
    virtual void login(const std::string & user, const std::string & password) {
        if(nullptr != player) {
            player->login(user, password);
        }
    }
    virtual void kill(const std::string & user, const std::string & password) {
        if(nullptr != player) {
            player->kill(user, password);
        }
    }
    virtual void upgrade(const std::string & user, const std::string & password) {
        if(nullptr != player) {
            player->upgrade(user, password);
        }
    }
protected:
    std::shared_ptr<IGamePlayer> player;
};

// 强制代理
class CoerceProxy : public IGamePlayer {
public:
    CoerceProxy(IGamePlayer* p) : player(p) { }
    virtual void login(const std::string & user, const std::string & password) {
        if(nullptr != player) {
            player->login(user, password);
        }
    }
    virtual void kill(const std::string & user, const std::string & password) {
        if(nullptr != player) {
            player->kill(user, password);
        }
    }
    virtual void upgrade(const std::string & user, const std::string & password) {
        if(nullptr != player) {
            player->upgrade(user, password);
        }
    }
private:
    IGamePlayer* player;
};

class CoercePlayer : public IGamePlayer {
public:
    CoercePlayer(const std::string& n) : name(n) {}
    std::shared_ptr<IGamePlayer> const_proxy() {
        if(nullptr == proxy) {
            this->proxy = std::make_shared<CoerceProxy>(this);
        }
        return proxy;
    }
    bool is_proxy() {
        if(nullptr == proxy) {
            return false;
        } else {
            return true;
        }
    }
    virtual void login(const std::string & user, const std::string & password) {
        if(is_proxy()) {
            std::cout << "user:" + user << " player" << name << " login success" << std::endl;
        } else {
            std::cout << "please use proxy ......" << std::endl;
        }
    }
    virtual void kill(const std::string & user, const std::string & password) {
        if(is_proxy()) {
            std::cout << "user:" + user << " player" << name << " kill success" << std::endl;
        } else {
            std::cout << "please use proxy ......" << std::endl;
        }
    }
    virtual void upgrade(const std::string & user, const std::string & password) {
        if(is_proxy()) {
            std::cout << "user:" + user << " player" << name << " upgrade success" << std::endl;
        } else {
            std::cout << "please use proxy ......" << std::endl;
        }
    }
private:
    std::string name;
    std::shared_ptr<IGamePlayer> proxy;
};

int main(int argc, char* argv[]) {
    std::shared_ptr<CoercePlayer> player = std::make_shared<CoercePlayer>("john");
    /* 强制使用代理才能访问 */
    player->const_proxy()->login("john", "123456");
    player->const_proxy()->kill("john", "123456");
    player->const_proxy()->upgrade("john", "123456");
    return 0;
}