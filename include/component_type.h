//
// Created by orzgg on 2020-06-25.
//

#include <string>
#include <iostream>
#include <memory>

#include <system_enum.h>
#include <system_literals.h>
#include <fmt/ostream.h>

#ifndef CPU_COMPONENT_TYPE_H
#define CPU_COMPONENT_TYPE_H

namespace Components {
    struct System ;

    template<typename T>
    struct Component_t {
        Component_t(T* parentPtr) :
            emuInstance(parentPtr) {}

        virtual std::string ToString() = 0 ;
        virtual void ErrorHandler(ErrType type){
            unsigned code = static_cast<unsigned>(type);
            fmt::print(std::cerr, "An error has occurred({}), emulation stop!",
                       MsgString::errorMsg[code]
            );

            exit(code);
        } // ErrorHandler()

    protected:
        T *const emuInstance ;
    };

    template<typename T>
    struct ClkDrivenComponent_t : public Component_t<T> {
        ClkDrivenComponent_t(T* parentPtr) :
                Component_t<T>(parentPtr) {}
        virtual void Tick() = 0 ;
    };
}

#endif //CPU_COMPONENT_TYPE_H
