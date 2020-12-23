#pragma once
#include <vector>
#include <sstream>
#include <random>
#include <QSR/rcc8.h>
#include "utils.h"

#define NO_ACTION 8

class BenchmarkAdministrator
    {
    private:
        size_t m_generationCount = 0;
        size_t m_variableCount;
        std::vector<qsr::rcc8::Relation> m_relations;
        bool m_result;

    private:
        std::vector<qsr::rcc8::Relation> GenerateRelations
        (
        size_t variableCount,
        double dcProb,
        double ecProb,
        double poProb,
        double eqProb,
        double tppProb,
        double ntppProb,
        double noneProb
        )
            {
            auto generator = std::random_device ();
            auto distribution = std::discrete_distribution<short> { dcProb, ecProb, poProb, eqProb, tppProb / 2, ntppProb / 2, tppProb / 2, ntppProb / 2, noneProb };

            m_relations.clear ();
            m_variableCount = variableCount;

            for (size_t i = 0; i < variableCount; i++)
                {
                for (size_t j = i + 1; j < variableCount; j++)
                    {
                    short action = distribution (generator);
                    if (action == NO_ACTION)
                        continue;

                    auto relationType = static_cast<qsr::rcc8::RelationType> (action);
                    m_relations.push_back ({ i, j, relationType });
                    }
                }

            return m_relations;
            }

    public:
        std::vector<qsr::rcc8::Relation> GetOrGenerateRelations
        (
        size_t variableCount,
        double dcProb,
        double ecProb,
        double poProb,
        double eqProb,
        double tppProb,
        double ntppProb,
        double noneProb
        )
            {
            if (m_generationCount % 2 == 0)
                return GenerateRelations (variableCount, dcProb, ecProb, poProb, eqProb, tppProb, ntppProb, noneProb);

            return m_relations;
            }

        void RegisterResult (benchmark::State& state, bool result)
            {
            if (m_generationCount++ % 2 == 0)
                {
                m_result = result;
                return;
                }

            if (result == m_result)
                return;

            std::stringstream stream;
            stream << "Result mismatch:\n";
            stream << " " << m_variableCount << "\n";

            for (auto relation : m_relations)
                stream << "  " << relation.r1 << " " << relation.r2 << " " << utils::RelationToString (relation.relationType) << "\n";

            state.SkipWithError (stream.str ().c_str ());
            }
    };