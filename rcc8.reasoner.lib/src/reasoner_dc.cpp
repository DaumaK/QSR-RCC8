#include <QSR/rcc8.h>
#include "reasoner_internal.h"

using namespace qsr::rcc8::internal;

bool reasoner_utils::CheckDCRelations (std::vector<Relation> const& dcRelations, SolutionContext const& context)
    {
    for (auto const& world : context.GetWorlds ())
        {
        for (auto relation : dcRelations)
            {
            size_t p1 = context.GetPropVarFromCalcVar (relation.r1);
            size_t p2 = context.GetPropVarFromCalcVar (relation.r2);

            // there should not exist a world such that p1 and p2.
            if (world.trueValuations.count (p1) != 0 && world.trueValuations.count (p2) != 0)
                return false;
            }
        }

    return true;
    }