#pragma once
#include <vector>

namespace qsr::rcc8
    {
    /*******************************************************************************
     * Enumerator of all possible RCC8 relation types:
     * DC    - disconnected
     * EC    - externally connected
     * PO    - partially overlapping
     * EQ    - equal
     * TPP   - tangential proper part
     * NTPP  - non-tangential proper part
     * TPPi  - TPP^-1
     * NTPPi - NTPP^-1
     *******************************************************************************/
    enum class RelationType
        {
        DC = 0,
        EC,
        PO,
        EQ,
        TPP,
        NTPP,
        TPPi,
        NTPPi
        };

    /*******************************************************************************
     * Struct that holds two variable indices (r1, r2) and a relation between them.
     * Should be interpreted as r1 relation r2
     * (e.g. r1 TPP r2 means that r1 is a tangential proper part of r2)
     *******************************************************************************/
    struct Relation
        {
        size_t r1;
        size_t r2;
        RelationType relationType;
        };

    /*******************************************************************************
     * A class that reasons with a given rcc8 constraint network
     *******************************************************************************/
    class ConstraintNetwork
        {
        private:
            size_t m_variableCount;
            std::vector<Relation> m_dcRelations;
            std::vector<Relation> m_ecRelations;
            std::vector<Relation> m_poRelations;
            std::vector<Relation> m_eqRelations;
            std::vector<Relation> m_tppRelations;
            std::vector<Relation> m_ntppRelations;

        public:
            ConstraintNetwork (size_t variableCount);
            ConstraintNetwork (size_t variableCount, std::vector<Relation> relations);

        public:
            bool IsSatisfiable ();
            void AddRelation (Relation const relation);
        };
    }
