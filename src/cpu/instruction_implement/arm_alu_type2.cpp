//
// Created by orzgg on 2020-07-11.
//

//void ArmHandler::CMP(Components::System& system) {
//    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::TEST> (
//            system,
//            [](unsigned Rn, unsigned op2) {
//                return static_cast<uint64_t>(Rn) - op2 ;
//            }
//    );
//}
//
//void ArmHandler::CMN(Components::System& system) {
//    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::TEST> (
//            system,
//            [](unsigned Rn, unsigned op2) {
//                return static_cast<uint64_t>(Rn) + op2 ;
//            }
//    );
//}
//
//void ArmHandler::TST(Components::System& system) {
//    ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::TEST> (
//            system,
//            [](unsigned Rn, unsigned op2) {
//                return static_cast<uint64_t>(Rn) & op2 ;
//            }
//    );
//}
//
//void ArmHandler::TEQ(Components::System& system) {
//    ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::TEST> (
//            system,
//            [](unsigned Rn, unsigned op2) {
//                return static_cast<uint64_t>(Rn) ^ op2 ;
//            }
//    );
//}