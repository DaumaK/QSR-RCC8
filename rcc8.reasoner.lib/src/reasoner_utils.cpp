#include <queue>
#include <QSR/rcc8.h>
#include "reasoner_internal.h"

using namespace qsr::rcc8::internal;

//---------------------------------------------------------------------------------------------------------------------

void reasoner_utils::RegisterDCRelations (std::vector<Relation> const& dcRelations, SolutionContext& context)
    {
    for (auto relation : dcRelations)
        {
        size_t p1 = context.GetPropVarFromCalcVar(relation.r1);
        size_t p2 = context.GetPropVarFromCalcVar(relation.r2);

        auto& region1 = context.GetRegionFromPropVar (p1);
        auto& region2 = context.GetRegionFromPropVar (p2);

        region1.SetValuation (p2, Valuation::FALSE);
        region2.SetValuation (p1, Valuation::FALSE);
        }
    }

//---------------------------------------------------------------------------------------------------------------------

void reasoner_utils::RegisterECRelations (std::vector<Relation> const& ecRelations, SolutionContext& context)
    {
    for (auto relation : ecRelations)
        {
        size_t p1 = context.GetPropVarFromCalcVar(relation.r1);
        size_t p2 = context.GetPropVarFromCalcVar(relation.r2);

        auto& region1 = context.GetRegionFromPropVar (p1);
        auto& region2 = context.GetRegionFromPropVar (p2);

        region1.SetValuation (p2, Valuation::INTERIOR_FALSE);
        region2.SetValuation (p1, Valuation::INTERIOR_FALSE);

        context.AddWorld (ModalWorld ({ { p1, Valuation::TRUE }, { p2, Valuation::TRUE } }, {&region1, &region2 }));
        }
    }

//---------------------------------------------------------------------------------------------------------------------

struct GraphNode
    {
    bool visited;
    std::vector<size_t> adjacent;

    GraphNode (): visited (false), adjacent (std::vector<size_t> ()) { }
    };

SolutionContext reasoner_utils::RegisterEQRelations (std::vector<Relation> const& eqRelations, size_t variableCount)
    {
    // For convenience store cluster index in another vector
    auto graphNodes = std::vector<GraphNode> (variableCount);
    auto clusterIndices = std::vector<size_t> (variableCount); // i.e. our map from variable to world

    // Log EQ relation as graph transition
    for (auto const& eqRelation : eqRelations)
        {
        graphNodes[eqRelation.r1].adjacent.push_back (eqRelation.r2);
        graphNodes[eqRelation.r2].adjacent.push_back (eqRelation.r1);
        }

    // Mark clusters by using BFS
    size_t clusterCount = 0;
    auto queue = std::queue<size_t> ();
    for (size_t i = 0; i < variableCount; i++)
        {
        if (graphNodes[i].visited)
            continue;

        graphNodes[i].visited = true;
        clusterIndices[i] = clusterCount;

        queue.push (i);
        while (!queue.empty ())
            {
            size_t nodeIndex = queue.front ();
            queue.pop ();

            for (size_t adjNodeIndex : graphNodes[nodeIndex].adjacent)
                {
                auto& adjNode = graphNodes[adjNodeIndex];
                if (adjNode.visited)
                    continue;

                clusterIndices[adjNodeIndex] = clusterCount;
                adjNode.visited = true;

                if (adjNode.adjacent.size () > 1) // No need to check further if terminal node (i.e. only has rel with current node)
                    queue.push (adjNodeIndex);
                }
            }

        clusterCount++;
        }

    return SolutionContext (std::move (clusterIndices), clusterCount);
    }

//---------------------------------------------------------------------------------------------------------------------

void reasoner_utils::RegisterPORelations (std::vector<Relation> const& poRelations, SolutionContext& context)
    {
    for (auto relation : poRelations)
        {
        size_t p1 = context.GetPropVarFromCalcVar(relation.r1);
        size_t p2 = context.GetPropVarFromCalcVar(relation.r2);

        auto& region1 = context.GetRegionFromPropVar (p1);
        auto& region2 = context.GetRegionFromPropVar (p2);

        context.AddWorld (ModalWorld ({ { p1, Valuation::INTERIOR_TRUE }, { p2, Valuation::INTERIOR_TRUE } }, {&region1, &region2 }));
        context.AddWorld (ModalWorld ({ { p1, Valuation::FALSE }, { p2, Valuation::INTERIOR_TRUE } }, { &region2 }));
        context.AddWorld (ModalWorld ({ { p1, Valuation::INTERIOR_TRUE }, { p2, Valuation::FALSE } }, { &region1 }));
        }
    }

//---------------------------------------------------------------------------------------------------------------------

void reasoner_utils::RegisterTPPRelations (std::vector<Relation> const& tppRelations, SolutionContext& context)
    {
    for (auto relation : tppRelations)
        {
        size_t p1 = context.GetPropVarFromCalcVar(relation.r1);
        size_t p2 = context.GetPropVarFromCalcVar(relation.r2);

        auto& region1 = context.GetRegionFromPropVar (p1);
        auto& region2 = context.GetRegionFromPropVar (p2);

        context.AddWorld (ModalWorld ({ { p1, Valuation::FALSE }, { p2, Valuation::TRUE } }, { &region2 }));

        context.AddWorld (ModalWorld ({ { p1, Valuation::TRUE }, { p2, (Valuation) (Valuation::TRUE | Valuation::INTERIOR_FALSE) } }, {&region1, &region2 }));

        region2.AddTPPDependant (&region1);
        }
    }

//---------------------------------------------------------------------------------------------------------------------

void reasoner_utils::RegisterNTPPRelations (std::vector<Relation> const& ntppRelations, SolutionContext& context)
    {
    for (auto relation : ntppRelations)
        {
        size_t p1 = context.GetPropVarFromCalcVar(relation.r1);
        size_t p2 = context.GetPropVarFromCalcVar(relation.r2);

        auto& region1 = context.GetRegionFromPropVar (p1);
        auto& region2 = context.GetRegionFromPropVar (p2);

        context.AddWorld (ModalWorld ({ { p1, Valuation::FALSE }, { p2, Valuation::TRUE } }, { &region2 }));

        region2.AddNTPPDependant (&region1);
        }
    }

//---------------------------------------------------------------------------------------------------------------------

bool ResolvePPDependencies (SolutionContext& context)
    {
    auto queue = std::queue<Region*> ();
    for (auto& region : context.GetRegions ())
        {
        if (!region.HasDependencies ())
            queue.push (&region);
        }

    size_t iterations = 0;
    while (!queue.empty ())
        {
        auto* region = queue.front ();
        queue.pop ();

        for (auto* ntppDependant : region->GetNTPPDependants ())
            {
            ntppDependant->DecrementNTPPDependencyCount ();
            if (!ntppDependant->HasDependencies ())
                queue.push (ntppDependant);

            for (auto valuation : region->GetValuations ())
                ntppDependant->SetValuation (valuation.first, valuation.second);

            ntppDependant->SetValuation (region->GetPropVar (), Valuation::INTERIOR_TRUE);
            }

        for (auto* tppDependant : region->GetTPPDependants ())
            {
            tppDependant->DecrementTPPDependencyCount ();
            if (!tppDependant->HasDependencies ())
                queue.push (tppDependant);

            for (auto valuation : region->GetValuations ())
                tppDependant->SetValuation (valuation.first, valuation.second);

            }

        iterations++;
        }

    return iterations == context.GetRegions ().size ();
    }

//---------------------------------------------------------------------------------------------------------------------

bool reasoner_utils::PropagateValuationsToWorlds (SolutionContext &context)
    {
    if (!ResolvePPDependencies (context))
        return false;

    for (auto& world : context.GetWorlds ())
        {
        for (auto& owners : world.GetOwners ())
            {
            for (auto valuation : owners->GetValuations ())
                {
                if (!world.SetValuation (valuation.first, valuation.second))
                    return false;
                }
            }
        }

    return true;
    }