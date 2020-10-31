#pragma once

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
     * Class that holds two variable indices (r1, r2) and a relation between them.
     * Should be interpreted as r1 relation r2
     * (e.g. r1 TPP r2 means that r1 is a tangential proper part of r2)
     *******************************************************************************/
    class Relation
        {
        private:
            unsigned long long m_r1;
            unsigned long long m_r2;
            RelationType m_relationType;

        public:
            /*******************************************************************************
             * Contructs a relation that reads as r1 relationType r2
             * (e.g. given r1, r2 TPP it would mean that r1 is a tangential proper part of r2)
             *******************************************************************************/
            Relation (unsigned long long r1, unsigned long long r2, RelationType relationType)
                : m_r1 (r1), m_r2 (r2), m_relationType (relationType) { }

        public:
            unsigned long long GetR1 () { return m_r1; }
            unsigned long long GetR2 () { return m_r2; }
            RelationType GetRelationType () { return m_relationType; }

        };
    }