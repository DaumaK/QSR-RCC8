#include <QSR/rcc8.h>
#include "reasoner_internal.h"

using namespace qsr::rcc8;

ConstraintNetwork::ConstraintNetwork (size_t variableCount)
    : m_variableCount (variableCount)
    , m_dcRelations (std::vector<Relation> ())
    , m_ecRelations (std::vector<Relation> ())
    , m_poRelations (std::vector<Relation> ())
    , m_eqRelations (std::vector<Relation> ())
    , m_tppRelations (std::vector<Relation> ())
    , m_ntppRelations (std::vector<Relation> ())
    { }

ConstraintNetwork::ConstraintNetwork (size_t variableCount, std::vector<Relation> const& relations)
    : ConstraintNetwork (variableCount)
    {
    for (auto const& relation : relations)
        AddRelation (relation);
    }

void ConstraintNetwork::AddRelation (Relation relation)
    {
    switch (relation.relationType)
        {
        case RelationType::DC:    m_dcRelations.push_back (relation); break;
        case RelationType::EC:    m_ecRelations.push_back (relation); break;
        case RelationType::PO:    m_poRelations.push_back (relation); break;
        case RelationType::EQ:    m_eqRelations.push_back (relation); break;
        case RelationType::TPP:   m_tppRelations.push_back (relation); break;
        case RelationType::NTPP:  m_ntppRelations.push_back (relation); break;
        case RelationType::TPPi:  m_tppRelations.push_back (Relation { .r1 = relation.r2, .r2 = relation.r1, .relationType = RelationType::TPP }); break;
        case RelationType::NTPPi: m_ntppRelations.push_back (Relation { .r1 = relation.r2, .r2 = relation.r1, .relationType = RelationType::NTPP }); break;
        }
    }

bool ConstraintNetwork::IsSatisfiable ()
    {
    size_t expectedWorldCountFromRel = m_ecRelations.size ()
        + 3 * m_poRelations.size ()
        + 2 * m_tppRelations.size ()
        + m_ntppRelations.size ();

    // Register EQ relations first
    auto context = internal::reasoner_utils::RegisterEQRelations (m_eqRelations, m_variableCount, expectedWorldCountFromRel);

    internal::reasoner_utils::RegisterDCRelations (m_dcRelations, context);
    internal::reasoner_utils::RegisterECRelations (m_ecRelations, context);
    internal::reasoner_utils::RegisterPORelations (m_poRelations, context);
    internal::reasoner_utils::RegisterTPPRelations (m_tppRelations, context);
    internal::reasoner_utils::RegisterNTPPRelations (m_ntppRelations, context);

    return internal::reasoner_utils::PropagateValuationsToWorlds (context);
    }