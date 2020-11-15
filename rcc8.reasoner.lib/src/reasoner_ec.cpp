#include <queue>
#include <QSR/rcc8.h>
#include "reasoner_internal.h"

using namespace qsr::rcc8::internal;

void reasoner_utils::RegisterECRelations (std::vector<Relation> const& ecRelations, SolutionContext& context)
    {
    for (auto relation : ecRelations)
        {
        size_t p1 = context.GetPropVarFromCalcVar(relation.r1);
        size_t p2 = context.GetPropVarFromCalcVar(relation.r2);

        auto& world1 = context.GetWorldFromVariable (relation.r1);
        auto& world2 = context.GetWorldFromVariable (relation.r2);

        auto& newWorld = context.CreateWorld ();
        newWorld.trueValuations.insert (p1);
        newWorld.trueValuations.insert (p2);

        newWorld.RelationsTo.push_back(&world1);
        newWorld.RelationsTo.push_back(&world2);
        }
    }

bool reasoner_utils::CheckECRelations (std::vector<Relation> const& ecRelations, SolutionContext const& context)
    {
    auto queue = std::queue<ModalWorld*> ();
    for (auto const& world : context.GetWorlds ())
        {
        for (auto relation : ecRelations)
            {
            size_t p1 = context.GetPropVarFromCalcVar (relation.r1);
            size_t p2 = context.GetPropVarFromCalcVar (relation.r2);

            // There should not exist a world where both Ip1 and Ip2 hold.
            // The idea here is that if Ip1 and Ip2, there will be a terminal world with 0 relations to where that holds
            if (world.trueValuations.count (p1) && world.trueValuations.count (p2) && world.RelationsTo.empty ())
                return false;
            }
        }

    return true;
    }