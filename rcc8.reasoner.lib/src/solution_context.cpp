#include "reasoner_internal.h"

using namespace qsr::rcc8::internal;

SolutionContext::SolutionContext (size_t* calculusVariableToPropositionalVariable, size_t regionCount, size_t modalWorldCount)
    : m_regionCount (regionCount)
    , m_regions (new Region[regionCount])
    , m_modalWorldCount (regionCount) // we will start of with a small size first, and add more later.
    , m_modalWorlds (new ModalWorld[modalWorldCount])
    , m_calculusVariableToPropositionalVariable (calculusVariableToPropositionalVariable)
    , m_nextPropVar (regionCount)
    {
    // p_i must hold in every region r_i and its associated worlds
    for (size_t i = 0; i < regionCount; i++)
        {
        m_regions[i].SetValuation (i, Valuation::TRUE);
        m_modalWorlds[i] = ModalWorld ({ { i, Valuation::TRUE } }, { }, { &m_regions[i] });
        }
    }

SolutionContext::~SolutionContext ()
    {
    delete [] m_regions;
    delete [] m_modalWorlds;
    delete [] m_calculusVariableToPropositionalVariable;
    }