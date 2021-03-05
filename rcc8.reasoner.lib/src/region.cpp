#include "reasoner_internal.h"

using namespace qsr::rcc8::internal;

Valuation Region::GetValuation (size_t propVar)
    {
    auto it = m_valuations.find (propVar);
    return it == m_valuations.end () ? Valuation::UNSET : it->second;
    }

void Region::SetValuation (size_t propVar, Valuation valuation)
    {
    valuation = static_cast<Valuation> (static_cast<unsigned short> (valuation) | static_cast<unsigned short> (GetValuation (propVar)));
    m_valuations.insert_or_assign (propVar, valuation);
    }
