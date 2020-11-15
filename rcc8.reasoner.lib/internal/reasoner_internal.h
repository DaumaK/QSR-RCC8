#pragma once

#include <vector>
#include <unordered_set>

namespace qsr::rcc8::internal
    {
    /*******************************************************************************
     * A modal logic world.
     * p_i is said to be true if it is in trueValuations, false otherwise
     *******************************************************************************/
    struct ModalWorld
        {
        std::unordered_set<size_t> trueValuations;
        std::vector<ModalWorld*> RelationsTo;

        ModalWorld ()
            : trueValuations (std::unordered_set<size_t> ())
            , RelationsTo (std::vector<ModalWorld*> ())
            { }
        };

    /*******************************************************************************
     * Class that holds all modal worlds and mappings from region variables to
     * the worlds
     *******************************************************************************/
    class SolutionContext
        {
        private:
            std::vector<ModalWorld> m_modalWorlds;
            std::vector<size_t> m_calculusVariableToPropositionalVariable;

        public:
            SolutionContext (std::vector<size_t> calculusVariableToPropositionalVariable, size_t minimalWorldCount)
                : m_modalWorlds (std::vector<ModalWorld> (minimalWorldCount))
                , m_calculusVariableToPropositionalVariable (calculusVariableToPropositionalVariable)
                {
                // p_i must hold in every world w_i (i.e. construct regular closed region r_1)
                for (size_t i = 0; i < minimalWorldCount; i++)
                    m_modalWorlds[i].trueValuations.insert (i);
                }

        public:
            inline size_t GetPropVarFromCalcVar (size_t variable) const { return m_calculusVariableToPropositionalVariable[variable]; }
            inline ModalWorld& GetWorldFromVariable (size_t variable) { return m_modalWorlds[m_calculusVariableToPropositionalVariable[variable]]; }
            inline std::vector<ModalWorld> const& GetWorlds () const { return m_modalWorlds; }
            inline ModalWorld& CreateWorld () { m_modalWorlds.emplace_back (); return m_modalWorlds.back (); }
        };

    /*******************************************************************************
     * Namespace with static functions for rcc8 reasoning
     * Register EQ = CreateSolutionContext
     *******************************************************************************/
    namespace reasoner_utils
        {
        // Register functions
        /*******************************************************************************
         * Register EQ relation:
         * r_i EQ r_j -> for all worlds: (p_i <-> p_j)
         * NOTE: this function should always be called first before any other reasoning
         * takes place as it constructs the initial worlds
         *******************************************************************************/
        SolutionContext RegisterEQRelations (std::vector<Relation> const& eqRelations, size_t variableCount);
        void RegisterECRelations (std::vector<Relation> const& ecRelations, SolutionContext& context);

        // Check functions
        bool CheckDCRelations (std::vector<Relation> const& dcRelations, SolutionContext const& context);
        bool CheckECRelations (std::vector<Relation> const& ecRelations, SolutionContext const& context);
        };
    }