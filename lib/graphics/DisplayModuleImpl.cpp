#include "IDisplayModule.hpp"
#include <iostream>

class DisplayModuleImpl : public arcade::IDisplayModule {
public:
    void init() override { std::cout << "DisplayModuleImpl init" << std::endl; }
    void stop() override { std::cout << "DisplayModuleImpl stop" << std::endl; }
    const arcade::IModule::LibName getName() const override {
        static arcade::IModule::LibName name = arcade::IModule::LibName::UNKNOWN;
        return name;
    }
};

extern "C" arcade::IDisplayModule* create() {
    return new DisplayModuleImpl();
}

extern "C" void destroy(arcade::IDisplayModule* p) {
    delete p;
}