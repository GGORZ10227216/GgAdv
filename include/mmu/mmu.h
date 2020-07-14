//
// Created by orzgg on 2020-06-28.
//

#include <unordered_map>
#include <memory>

#include <component_type.h>
#include <system_enum.h>
#include <array_tool.h>

#include <general_memory.h>
#include <display_memory.h>
#include <gamepak_memory.h>

#ifndef CPU_MMU_H
#define CPU_MMU_H

namespace Components {
    using ReadHandlerList = std::unordered_map<unsigned, std::unordered_map<std::string, MMU::ReadEventHandler>>;
    using WriteHandlerList = std::unordered_map<unsigned, std::unordered_map<std::string, MMU::WriteEventHandler>>;

    enum class AccessMode {
        Read, Write
    };

    struct Memory final : public ClkDrivenComponent_t<Components::System>, public MMU::RegionBase {
        Memory(Components::System* parentPtr) ;

        std::string ToString() override ;

        void Tick() override ;

        void Reset() override ;

        // TODO: Implement a safe_read() and safe_write() to emulate not aligned memory access behavior on ARM CPU.
        uint8_t Read8(unsigned addr) ;

        uint16_t Read16(unsigned addr) ;

        uint32_t Read32(unsigned addr) ;

        template<typename T>
        void Write8(unsigned addr, T value) requires std::is_same_v<T, uint8_t> {
            using WIDTH = MMU_Enum::WIDTH ;
            CheckEvents(_writeEventHandler, addr, value);
            Access(addr, WIDTH::BYTE) = value;
        } // Write()

        template<typename T>
        void Write16(unsigned addr, T value) requires std::is_same_v<T, uint16_t> {
            using WIDTH = MMU_Enum::WIDTH ;
            if (addr % 2 != 0)
                throw std::logic_error("Attempt to write a 16bit data to a not 2 aligned address");
            CheckEvents(_writeEventHandler, addr, value);
            reinterpret_cast<uint16_t &> (Access(addr, WIDTH::HALFWORD)) = value;
        } // Write()

        template<typename T>
        void Write32(unsigned addr, T value) requires std::is_same_v<T, uint32_t> {
            using WIDTH = MMU_Enum::WIDTH ;
            if (addr % 4 != 0)
                throw std::logic_error("Attempt to write a 32bit data to a not 4 aligned address");
            CheckEvents(_writeEventHandler, addr, value);
            reinterpret_cast<uint32_t &> (Access(addr, WIDTH::WORD)) = value;
        } // Write()

    private :
        template<typename T, typename... Args>
        void CheckEvents(const T &target, unsigned addr, Args... args) {
            if (!target.empty()) {
                auto it = target.find(addr);
                if (it != target.end()) {
                    for (auto &handlerPair : it->second) {
                        handlerPair.second(addr, args...);
                    } // for
                } // if
                else {
                    int i = 0;
                    if constexpr (std::is_same_v<T, WriteHandlerList>)
                        i = 1;
                    throw std::logic_error(
                            fmt::format("There are no {} handler binded at {:#x}",
                                        AccessModeName[i],
                                        addr
                            ));
                } // else
            } // if
        } // CheckEvents()

        uint8_t &Access(unsigned addr, MMU_Enum::WIDTH width) override ;

        MMU::Region<Region_t::General> generalMemory;
        MMU::Region<Region_t::Display> displayMemory;
        MMU::Region<Region_t::GamePak> gamepakMemory;

        // TODO: implement the read&write event mechanism. (insert, delete)
        constexpr static auto AccessModeName = Utility::MakeArray("READ", "WRITE");
        ReadHandlerList _readEventHandler;
        WriteHandlerList _writeEventHandler;
    };
}

#endif //CPU_MMU_H
