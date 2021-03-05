#include "reasoner_internal.h"

using namespace qsr::rcc8::internal;

Valuation ModalWorld::GetValuation (size_t propVar)
    {
    auto it = m_valuations.find (propVar);
    return it == m_valuations.end () ? Valuation::UNSET : it->second;
    }

bool ModalWorld::SetValuation (size_t propVar, Valuation valuation)
    {
    valuation = static_cast<Valuation> (static_cast<unsigned short> (valuation) | static_cast<unsigned short> (GetValuation (propVar)));
    m_valuations.insert_or_assign (propVar, valuation);
    switch (valuation)
        {
        case Valuation::TRUE:
        case Valuation::FALSE:
        case Valuation::INTERIOR_TRUE:
        case Valuation::INTERIOR_FALSE:
        case Valuation::TRUE | Valuation::INTERIOR_TRUE:
        case Valuation::TRUE | Valuation::INTERIOR_FALSE:
        case Valuation::FALSE | Valuation::INTERIOR_FALSE:
            return true;
        default:
            return false;
        }
    }