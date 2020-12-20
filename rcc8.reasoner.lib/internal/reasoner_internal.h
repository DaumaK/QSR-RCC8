#pragma once

#include <utility>
#include <vector>
#include <unordered_map>
#include <QSR/rcc8.h>

namespace qsr::rcc8::internal
    {
    /*******************************************************************************
     * Possible values for a valuation.
     *******************************************************************************/
    enum class Valuation
        {
        UNSET         = 0,
        FALSE         = 1,
        TRUE          = 2,
        CONTRADICTION = FALSE | TRUE
        };

    /*******************************************************************************
     * A region (modal world owner) that keeps track of common valuations for the worlds.
     *******************************************************************************/
    class Region
        {
        private:
            std::unordered_map<size_t, Valuation> m_interiorValuations;
            std::unordered_map<size_t, Valuation> m_valuations;

            std::vector<Region*> m_ntppDependants;
            size_t m_ntppDependencyCount = 0;

            std::vector<Region*> m_tppDependants;
            size_t m_tppDependencyCount = 0;

        public:
            Valuation GetValuation (size_t propVar);
            bool SetValuation (size_t propVar, Valuation valuation);
            Valuation GetInteriorValuation (size_t propVar);
            bool SetInteriorValuation (size_t propVar, Valuation valuation);

            inline std::unordered_map<size_t, Valuation>& GetInteriorValuations () { return m_interiorValuations; }
            inline std::unordered_map<size_t, Valuation>& GetValuations () { return m_valuations; }

            void AddTPPDependant (Region* dependant) { dependant->m_tppDependencyCount++; m_tppDependants.push_back (dependant); }
            void AddNTPPDependant (Region* dependant) { dependant->m_ntppDependencyCount++; m_ntppDependants.push_back (dependant); }

            inline std::vector<Region*>& GetTPPDependants () { return m_tppDependants; }
            inline std::vector<Region*>& GetNTPPDependants () { return m_ntppDependants; }

            inline void DecrementTPPDependencyCount () { m_tppDependencyCount--; }
            inline void DecrementNTPPDependencyCount () { m_ntppDependencyCount--; }

            inline bool HasDependencies () { return m_tppDependencyCount || m_ntppDependencyCount; }
        };

    /*******************************************************************************
     * A modal logic world with region dependencies and individual valuations.
     *******************************************************************************/
    class ModalWorld
        {
        private:
            std::unordered_map<size_t, Valuation> m_valuations;
            std::vector<Region*> m_ownersAsExterior;
            std::vector<Region*> m_ownersAsInterior;

        public:
            ModalWorld (std::unordered_map<size_t, Valuation>&& valuations, std::vector<Region*>&& ownersAsExterior, std::vector<Region*>&& ownersAsInterior)
                : m_valuations (valuations)
                , m_ownersAsExterior (ownersAsExterior)
                , m_ownersAsInterior (ownersAsInterior)
                { }

        public:
            Valuation GetValuation (size_t propVar);
            bool SetValuation (size_t propVar, Valuation valuation);

            std::vector<Region*> GetInteriorRegions () { return m_ownersAsInterior; }
            std::vector<Region*> GetExteriorRegions () { return m_ownersAsExterior; }

        };

    /*******************************************************************************
     * Class that holds all modal worlds, regions and mappings from calculus
     * variables to propositional variables (and, by extension, actual regions).
     *******************************************************************************/
    class SolutionContext
        {
        private:
            std::vector<Region> m_regions;
            std::vector<ModalWorld> m_modalWorlds;
            std::vector<size_t> m_calculusVariableToPropositionalVariable;
            size_t m_nextPropVar;

        public:
            SolutionContext (std::vector<size_t>&& calculusVariableToPropositionalVariable, size_t minimalWorldCount);

        public:
            inline size_t GetPropVarFromCalcVar (size_t variable) const { return m_calculusVariableToPropositionalVariable[variable]; }
            inline Region& GetRegionFromPropVar (size_t propVar) { return m_regions[propVar]; }
            inline std::vector<Region>& GetRegions () { return m_regions; }
            inline std::vector<ModalWorld>& GetWorlds () { return m_modalWorlds; }
            inline ModalWorld& AddWorld (ModalWorld&& world) { return m_modalWorlds.emplace_back (world); }
            inline size_t CreateNewPropVar () { return m_nextPropVar++; }

        };

    /*******************************************************************************
     * Namespace with static functions for rcc8 reasoning
     *******************************************************************************/
    namespace reasoner_utils
        {
        SolutionContext RegisterEQRelations (std::vector<Relation> const& eqRelations, size_t variableCount);
        void RegisterDCRelations (std::vector<Relation> const& dcRelations, SolutionContext& context);
        void RegisterECRelations (std::vector<Relation> const& ecRelations, SolutionContext& context);
        void RegisterPORelations (std::vector<Relation> const& poRelations, SolutionContext& context);
        void RegisterTPPRelations (std::vector<Relation> const& tppRelations, SolutionContext& context);
        void RegisterNTPPRelations (std::vector<Relation> const& ntppRelations, SolutionContext& context);

        bool PropagateValuationsToWorlds (SolutionContext& context);
        };
    }