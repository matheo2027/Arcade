#include "IDisplayModule.h"
#include <iostream>

class DisplayModuleImpl : public IDisplayModule {
public:
    void init() override { std::cout << "DisplayModuleImpl init" << std::endl; }
    void stop() override { std::cout << "DisplayModuleImpl stop" << std::endl; }
    const std::string& getName() const override {
        static std::string name = "DisplayModuleImpl";
        return name;
    }
};

extern "C" IDisplayModule* create() {
    return new DisplayModuleImpl();
}

extern "C" void destroy(IDisplayModule* p) {
    delete p;
}