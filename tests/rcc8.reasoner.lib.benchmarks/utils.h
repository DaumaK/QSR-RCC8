#pragma once
#include <string>
#include <QSR/rcc8.h>

namespace utils
    {
    std::string RelationToString (qsr::rcc8::RelationType relation)
        {
        switch (relation)
            {
            case qsr::rcc8::RelationType::DC: return "( DC )";
            case qsr::rcc8::RelationType::EC: return "( EC )";
            case qsr::rcc8::RelationType::EQ: return "( EQ )";
            case qsr::rcc8::RelationType::PO: return "( PO )";
            case qsr::rcc8::RelationType::TPP: return "( TPP )";
            case qsr::rcc8::RelationType::NTPP: return "( NTPP )";
            case qsr::rcc8::RelationType::TPPi: return "( TPPI )";
            case qsr::rcc8::RelationType::NTPPi: return "( NTPPI )";
            }
        }
    }