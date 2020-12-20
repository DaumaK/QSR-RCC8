#include "reasoner_internal.h"

using namespace qsr::rcc8::internal;

SolutionContext::SolutionContext (std::vector<size_t>&& calculusVariableToPropositionalVariable, size_t minimalWorldCount)
    : m_regions (minimalWorldCount)
    , m_modalWorlds ()
    , m_calculusVariableToPropositionalVariable (calculusVariableToPropositionalVariable)
    , m_nextPropVar (minimalWorldCount)
    {
    // p_i must hold in every region r_i and its associated worlds
    for (size_t i = 0; i < minimalWorldCount; i++)
        {
        m_regions[i].SetValuation (i, Valuation::TRUE);
        m_modalWorlds.push_back (ModalWorld ({ { i, Valuation::TRUE } }, { }, { &m_regions[i] }) );
        }
    }