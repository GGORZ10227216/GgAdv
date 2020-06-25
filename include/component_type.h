//
// Created by orzgg on 2020-06-25.
//

#include <string>
#include <system_enum.h>
#include <system_literals.h>

#ifndef CPU_COMPONENT_TYPE_H
#define CPU_COMPONENT_TYPE_H

struct Component_t {
    virtual std::string ToString() = 0 ;
    virtual void ErrorHandler(ErrType type){
        unsigned code = static_cast<unsigned>(type);
        fmt::print(std::cerr, "An error has occurred({}), emulation stop!",
                   MsgString::errorMsg[code]
        );

        exit(code);
    } // ErrorHandler()
};

template<typename T>
struct ChildComponent_t : public Component_t {
    ChildComponent_t(Component_t* parent) : _parent(*static_cast<T*>(parent)) {}
    T& _parent ;
};

#endif //CPU_COMPONENT_TYPE_H
