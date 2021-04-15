#pragma once

#include <cstring>
#include <utility>
#include <vector>
#include <QSR/rcc8.h>

namespace qsr::rcc8::internal
    {
    /*******************************************************************************
     * Possible values for a valuation.
     *******************************************************************************/
    enum Valuation : unsigned short
        {
        UNSET          = 0,
        FALSE          = 1,
        TRUE           = 2,
        INTERIOR_FALSE = 4,
        INTERIOR_TRUE  = 8
        };

    /*******************************************************************************
     * Data structure for holding valuations
     *******************************************************************************/
    class ValuationSet
        {
        private:
            size_t m_setCount;
            Valuation* m_valuations;
            size_t* m_valuationsIterator;

        public:
            ValuationSet () = default;

            ~ValuationSet ()
                {
                delete [] m_valuations;
                delete [] m_valuationsIterator;
                }

        public:
            inline void Init (size_t propVarCount)
                {
                m_setCount = 0;
                m_valuations = new Valuation[propVarCount];
                m_valuationsIterator = new size_t[propVarCount];

                std::memset (m_valuations, Valuation::UNSET, sizeof (Valuation) * propVarCount);
                }

            inline void Init (size_t propVarCount, size_t regionPropVar)
                {
                Init (propVarCount);

                m_valuationsIterator[m_setCount++] = regionPropVar;
                m_valuations[regionPropVar] = Valuation::TRUE;
                }

            inline size_t GetSetCount () const { return m_setCount; }
            inline size_t const* GetIterator () const { return m_valuationsIterator; }
            inline Valuation GetValuation (size_t propVar) const { return m_valuations[propVar]; }
            inline Valuation SetValuation (size_t propVar, Valuation valuation)
                {
                if (m_valuations[propVar] == Valuation::UNSET)
                    m_valuationsIterator[m_setCount++] = propVar;

                m_valuations[propVar] = static_cast<Valuation>(m_valuations[propVar] | valuation);
                return m_valuations[propVar];
                }

        };

    /*******************************************************************************
     * Simple structure for accounting for dependant regions
     *******************************************************************************/
    class Region;
    class DependantList
        {
        private:
            Region** m_dependants;
            size_t m_dependantCount;

        public:
            DependantList () = default;

            ~DependantList () { delete [] m_dependants; }

        public:
            inline void Init (size_t expectedDependantCount)
                {
                m_dependants = expectedDependantCount == 0 ? nullptr : new Region*[expectedDependantCount];
                m_dependantCount = 0;
                }

            inline size_t GetCount () const { return m_dependantCount; }
            inline Region* const* GetDependants () const { return m_dependants; }
            inline void AddDependant (Region* dependant) { m_dependants[m_dependantCount++] = dependant; }

        };

    /*******************************************************************************
     * A region (modal world owner) that keeps track of common valuations for the worlds.
     *******************************************************************************/
    class Region
        {
        private:
            size_t m_assignedPropVar;

            ValuationSet m_valuations;

            DependantList m_ntppDependants;
            size_t m_ntppDependencyCount = 0;

            DependantList m_tppDependants;
            size_t m_tppDependencyCount = 0;

        public:
            Region () = default;

        public:
            inline void Init (size_t propVar, size_t propVarCount)
                {
                m_assignedPropVar = propVar;
                m_valuations.Init (propVarCount, propVar);
                }

            inline void InitTppDependants (size_t dependantCount) { m_tppDependants.Init (dependantCount); }
            inline void InitNtppDependants (size_t dependantCount) { m_ntppDependants.Init (dependantCount); }

            inline Valuation GetValuation (size_t propVar) const { return m_valuations.GetValuation (propVar); }
            inline void SetValuation (size_t propVar, Valuation valuation) { m_valuations.SetValuation (propVar, valuation); }
            inline ValuationSet const& GetValuationSet () { return m_valuations; }

            inline void AddTPPDependant (Region* dependant) { dependant->m_tppDependencyCount++; m_tppDependants.AddDependant (dependant); }
            inline void AddNTPPDependant (Region* dependant) { dependant->m_ntppDependencyCount++; m_ntppDependants.AddDependant (dependant); }

            inline DependantList const& GetTPPDependants () const { return m_tppDependants; }
            inline DependantList const& GetNTPPDependants () const { return m_ntppDependants; }

            inline void DecrementTPPDependencyCount () { m_tppDependencyCount--; }
            inline void DecrementNTPPDependencyCount () { m_ntppDependencyCount--; }

            inline bool HasDependencies () const { return m_tppDependencyCount || m_ntppDependencyCount; }

            inline size_t GetPropVar () const { return m_assignedPropVar; }
        };

    /*******************************************************************************
     * A modal logic world with region dependencies and individual valuations.
     *******************************************************************************/
    class ModalWorld
        {
        private:
            ValuationSet m_valuations;
            std::vector<Region*> m_owners;

        public:
            inline ModalWorld () = default;

        public:
            inline void Init (size_t totalPropVarCount, std::vector<Region*>&& owners)
                {
                m_valuations.Init (totalPropVarCount);
                m_owners = owners;
                }

            inline Valuation GetValuation (size_t propVar) const { return m_valuations.GetValuation (propVar); }
            inline Valuation SetValuation (size_t propVar, Valuation valuation) { return m_valuations.SetValuation (propVar, valuation); }
            inline std::vector<Region*> const& GetOwners () const { return m_owners; }
        };

    /*******************************************************************************
     * Class that holds all modal worlds, regions and mappings from calculus
     * variables to propositional variables (and, by extension, actual regions).
     *******************************************************************************/
    class SolutionContext
        {
        private:
            size_t m_propVarCount;
            size_t m_worldCount;
            Region* m_regions;
            ModalWorld* m_modalWorlds;
            size_t* m_calculusVariableToPropositionalVariable;

        public:
            inline SolutionContext (size_t* calculusVariableToPropositionalVariable, size_t minimalWorldCount, size_t expectedWorldCountFromRel)
                : m_propVarCount (minimalWorldCount)
                , m_worldCount (minimalWorldCount) // Starting value, will increase by 'expectedWorldCountFromRel'
                , m_regions (new Region[minimalWorldCount])
                , m_modalWorlds (new ModalWorld[minimalWorldCount + expectedWorldCountFromRel])
                , m_calculusVariableToPropositionalVariable (calculusVariableToPropositionalVariable)
                {
                // p_i must hold in every region r_i and its associated worlds
                for (size_t i = 0; i < minimalWorldCount; i++)
                    {
                    m_regions[i].Init (i, minimalWorldCount);
                    m_modalWorlds[i].Init (minimalWorldCount, { &m_regions[i] });
                    m_modalWorlds[i].SetValuation (i, Valuation::INTERIOR_TRUE);
                    }
                }

            ~SolutionContext ()
                {
                delete [] m_regions;
                delete [] m_modalWorlds;
                delete [] m_calculusVariableToPropositionalVariable;
                }

        public:
            inline size_t GetPropVarCount () const { return m_propVarCount; }
            inline size_t GetPropVarFromCalcVar (size_t variable) const { return m_calculusVariableToPropositionalVariable[variable]; }
            inline Region& GetRegionFromPropVar (size_t propVar) { return m_regions[propVar]; }
            inline Region* GetRegions () { return m_regions; }
            inline size_t GetWorldCount () const { return m_worldCount; }
            inline ModalWorld* GetWorlds () { return m_modalWorlds; }
            inline ModalWorld& AddWorld (std::vector<Region*>&& owners)
                {
                m_modalWorlds[m_worldCount].Init (m_propVarCount, std::move(owners));
                return m_modalWorlds[m_worldCount++];
                }

        };

    /*******************************************************************************
     * Namespace with static functions for rcc8 reasoning
     *******************************************************************************/
    namespace reasoner_utils
        {
        SolutionContext RegisterEQRelations (std::vector<Relation> const& eqRelations, size_t variableCount, size_t expectedWorldCountFromRel);
        void RegisterDCRelations (std::vector<Relation> const& dcRelations, SolutionContext& context);
        void RegisterECRelations (std::vector<Relation> const& ecRelations, SolutionContext& context);
        void RegisterPORelations (std::vector<Relation> const& poRelations, SolutionContext& context);
        void RegisterTPPRelations (std::vector<Relation> const& tppRelations, SolutionContext& context);
        void RegisterNTPPRelations (std::vector<Relation> const& ntppRelations, SolutionContext& context);

        bool PropagateValuationsToWorlds (SolutionContext& context);
        };
    }