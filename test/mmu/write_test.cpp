//
// Created by orzgg on 2020-06-29.
//
#define CATCH_CONFIG_MAIN

#include <test_mmu.h>

#include <array>

TEST_CASE_METHOD(MMU_Test, "BIOS Access", "[mmu]") {
    std::fstream fs( "/home/orzgg/gba_bios.bin", std::ios::in | std::ios::binary ) ;
    std::array<char, 16384> bios {} ;

    Components::Memory &memUnderTest = Components::emulator.memory ;
    if ( fs.good() ) {
        fs.read( bios.data(), 16384 ) ;
        SECTION( "8 bit read and write" ) ;
        for ( int i =  0 ; i < 16384 ; ++i ) {
            memUnderTest.Write8( 0x0 + i, bios[ i ] ) ;
            CAPTURE( i ) ;
            REQUIRE( memUnderTest.Read8( 0x0 + i ) == static_cast<uint8_t>( bios[ i ] ) ) ;
        } // for

        SECTION( "16 bit read and write" ) ;
        memUnderTest.Reset() ;
        for ( int i =  0 ; i < 16384 ; i += 2 ) {
            uint16_t &halfWordRef = reinterpret_cast<uint16_t&>( bios.data()[ i ] ) ;
            memUnderTest.Write16( 0x0 + i, halfWordRef ) ;
            CAPTURE( i ) ;
            REQUIRE( memUnderTest.Read16( 0x0 + i ) == halfWordRef ) ;
        } // for

        SECTION( "32 bit read and write" ) ;
        memUnderTest.Reset() ;
        for ( int i =  0 ; i < 16384 ; i += 4 ) {
            uint32_t &wordRef = reinterpret_cast<uint32_t&>( bios.data()[ i ] ) ;
            memUnderTest.Write32( 0x0 + i, wordRef ) ;
            CAPTURE( i ) ;
            REQUIRE( memUnderTest.Read32( 0x0 + i ) == wordRef ) ;
        } // for
    } // if
    else
        fmt::print( "read bios failed." ) ;
}