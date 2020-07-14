//
// Created by orzgg on 2020-06-30.
//

#include <exception>
#include <memory>
#include <mmu.h>

#ifndef TEST_IOREG_TYPE_H
#define TEST_IOREG_TYPE_H

namespace IO_Map {
    enum class AccessMode { R = 0, W = 1, RW = 2 };

    template <typename T, AccessMode M>
    struct IOReg_t {
        const unsigned addr ;
        using parentMemory = Components::Memory ;
        T Read(parentMemory &memory) const {
            if constexpr ( M == AccessMode::W )
                throw std::logic_error( "Attempted write to read only I/O register." ) ;
            else {
                if constexpr ( std::is_same_v<T, uint16_t> )
                    return memory.Read16( addr ) ;
                else if constexpr ( std::is_same_v<T, uint32_t> )
                    return memory.Read32( addr ) ;
            } // else
            return 0 ;
        } // Read()

        template<typename U>
        void Write( parentMemory &memory, U value ) const requires std::is_same_v<T, U> {
            if constexpr ( M == AccessMode::R )
                throw std::logic_error( "Attempted read from write only I/O register." ) ;
            else {
                if constexpr ( std::is_same_v<T, uint16_t> )
                    memory.Write16( addr, value ) ;
                else if constexpr ( std::is_same_v<T, uint32_t> )
                    memory.Write32( addr, value ) ;
            } // else
        } // Write()
    };
}

#endif //TEST_IOREG_TYPE_H
