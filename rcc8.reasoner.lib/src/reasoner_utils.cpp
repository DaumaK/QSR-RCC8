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

        auto& world = context.AddWorld ({ &region1, &region2 });
        world.SetValuation (p1, Valuation::TRUE);
        world.SetValuation (p2, Valuation::TRUE);
        }
    }

//---------------------------------------------------------------------------------------------------------------------

struct Component
    {
    Component* parent = nullptr;
    size_t size = 1;
    size_t componentIndex;
    };

inline Component* Find (Component* component)
    {
    if (component->parent == nullptr)
        return component;

    component->parent = Find (component->parent);

    return component->parent;
    }

inline void Union (Component* root1, Component* root2)
    {
    if (root1->size < root2->size)
        {
        root1->parent = root2;
        root2->size += root1->size;
        }
    else
        {
        root2->parent = root1;
        root1->size += root2->size;
        }
    }

SolutionContext reasoner_utils::RegisterEQRelations (std::vector<Relation> const& eqRelations, size_t variableCount, size_t expectedWorldCountFromRel)
    {
    auto* components = new Component[variableCount];

    for (auto relation : eqRelations)
        {
        auto* root1 = Find (&components[relation.r1]);
        auto* root2 = Find (&components[relation.r2]);

        if (root1 != root2)
            Union (root1, root2);
        }

    size_t sscCount = 0;
    for (size_t i = 0; i < variableCount; i++)
        {
        if (components[i].parent != nullptr)
            continue;

        components[i].componentIndex = sscCount;
        sscCount++;
        }

    auto* strongConComp = new size_t[variableCount];
    for (size_t i = 0; i < variableCount; i++)
        {
        auto* root = Find (&components[i]);
        strongConComp[i] = root->componentIndex;
        }

    delete [] components;
    return SolutionContext (strongConComp, sscCount, expectedWorldCountFromRel);
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

        auto& world1 = context.AddWorld ({ &region1, &region2 });
        world1.SetValuation (p1, Valuation::INTERIOR_TRUE);
        world1.SetValuation (p2, Valuation::INTERIOR_TRUE);

        auto& world2 = context.AddWorld ({ &region2 });
        world2.SetValuation (p1, Valuation::FALSE);
        world2.SetValuation (p2, Valuation::INTERIOR_TRUE);

        auto& world3 = context.AddWorld ({ &region1 });
        world3.SetValuation (p1, Valuation::INTERIOR_TRUE);
        world3.SetValuation (p2, Valuation::FALSE);
        }
    }

//---------------------------------------------------------------------------------------------------------------------

void reasoner_utils::RegisterTPPRelations (std::vector<Relation> const& tppRelations, SolutionContext& context)
    {
    // Count needed sizes
    size_t regionCount = context.GetPropVarCount ();
    size_t* tppDependantCounts = new size_t[regionCount];
    std::memset (tppDependantCounts, 0, sizeof (tppDependantCounts) * regionCount);
    for (auto relation : tppRelations)
        {
        size_t p = context.GetPropVarFromCalcVar (relation.r2);
        tppDependantCounts[p]++;
        }

    auto* regions = context.GetRegions ();
    for (int i = 0; i < regionCount; i++)
        regions[i].InitTppDependants (tppDependantCounts[i]);

    delete [] tppDependantCounts;

    for (auto relation : tppRelations)
        {
        size_t p1 = context.GetPropVarFromCalcVar(relation.r1);
        size_t p2 = context.GetPropVarFromCalcVar(relation.r2);

        auto& region1 = context.GetRegionFromPropVar (p1);
        auto& region2 = context.GetRegionFromPropVar (p2);

        auto& world1 = context.AddWorld ({ &region2 });
        world1.SetValuation (p1, Valuation::FALSE);
        world1.SetValuation (p2, Valuation::TRUE);

        auto& world2 = context.AddWorld ({ &region1, &region2 });
        world2.SetValuation (p1, Valuation::TRUE);
        world2.SetValuation (p2, static_cast<Valuation>(Valuation::TRUE | Valuation::INTERIOR_FALSE));

        region2.AddTPPDependant (&region1);
        }
    }

//---------------------------------------------------------------------------------------------------------------------

void reasoner_utils::RegisterNTPPRelations (std::vector<Relation> const& ntppRelations, SolutionContext& context)
    {
    // Count needed sizes
    size_t regionCount = context.GetPropVarCount ();
    size_t* ntppDependantCounts = new size_t[regionCount];
    std::memset (ntppDependantCounts, 0, sizeof (ntppDependantCounts) * regionCount);
    for (auto relation : ntppRelations)
        {
        size_t p = context.GetPropVarFromCalcVar (relation.r2);
        ntppDependantCounts[p]++;
        }

    auto* regions = context.GetRegions ();
    for (int i = 0; i < regionCount; i++)
        regions[i].InitNtppDependants (ntppDependantCounts[i]);

    delete [] ntppDependantCounts;

    for (auto relation : ntppRelations)
        {
        size_t p1 = context.GetPropVarFromCalcVar(relation.r1);
        size_t p2 = context.GetPropVarFromCalcVar(relation.r2);

        auto& region1 = context.GetRegionFromPropVar (p1);
        auto& region2 = context.GetRegionFromPropVar (p2);

        auto& world = context.AddWorld ({ &region2 });
        world.SetValuation (p1, Valuation::FALSE);
        world.SetValuation (p2, Valuation::TRUE);

        region2.AddNTPPDependant (&region1);
        }
    }

//---------------------------------------------------------------------------------------------------------------------

bool ResolvePPDependencies (SolutionContext& context)
    {
    size_t regionCount = context.GetPropVarCount ();
    auto* queue = new Region*[regionCount];
    size_t queueCounter = 0;

    auto* regions = context.GetRegions();
    for (size_t i = 0; i < context.GetPropVarCount (); i++)
        {
        auto& region = regions[i];

        if (!region.HasDependencies ())
            queue[queueCounter++] = &region;
        }

    size_t iterations = 0;
    for (size_t queuePosition = 0; queuePosition < queueCounter; queuePosition++)
        {
        auto* region = queue[queuePosition];

        auto& valuationSet = region->GetValuationSet ();
        auto* valuationIterator = valuationSet.GetIterator ();
        size_t setCount = valuationSet.GetSetCount ();

        {
            auto& ntppDependantList = region->GetNTPPDependants ();
            auto* nttpDependants = ntppDependantList.GetDependants ();
            for (size_t i = 0; i < ntppDependantList.GetCount (); i++)
                {
                auto* ntppDependant = nttpDependants[i];

                ntppDependant->DecrementNTPPDependencyCount ();
                if (!ntppDependant->HasDependencies ())
                    queue[queueCounter++] = ntppDependant;

                for (size_t j = 0; j < setCount; j++)
                    {
                    size_t propVar = valuationIterator[j];
                    ntppDependant->SetValuation (propVar, valuationSet.GetValuation (propVar));
                    }

                ntppDependant->SetValuation (region->GetPropVar (), Valuation::INTERIOR_TRUE);
                }
        }
        {
            auto& tppDependantList = region->GetTPPDependants ();
            auto* ttpDependants = tppDependantList.GetDependants ();
            for (size_t i = 0; i < tppDependantList.GetCount (); i++)
                {
                auto* tppDependant = ttpDependants[i];

                tppDependant->DecrementTPPDependencyCount ();
                if (!tppDependant->HasDependencies ())
                    queue[queueCounter++] = tppDependant;

                for (size_t j = 0; j < setCount; j++)
                    {
                    size_t propVar = valuationIterator[j];
                    tppDependant->SetValuation (propVar, valuationSet.GetValuation (propVar));
                    }
                }
        }

        iterations++;
        }

    delete [] queue;
    return iterations == regionCount;
    }

//---------------------------------------------------------------------------------------------------------------------

bool reasoner_utils::PropagateValuationsToWorlds (SolutionContext &context)
    {
    if (!ResolvePPDependencies (context))
        return false;

    auto* worlds = context.GetWorlds ();
    for (size_t i = 0; i < context.GetWorldCount (); i++)
        {
        auto& world = worlds[i];

        for (auto& owner : world.GetOwners ())
            {
            auto& valuationSet = owner->GetValuationSet ();
            auto* valuationIterator = valuationSet.GetIterator ();
            size_t setCount = valuationSet.GetSetCount ();

            for (size_t j = 0; j < setCount; j++)
                {
                size_t propVar = valuationIterator[j];
                auto valuation = world.SetValuation (propVar, valuationSet.GetValuation (propVar));
                switch (valuation)
                    {
                    case Valuation::TRUE:
                    case Valuation::FALSE:
                    case Valuation::INTERIOR_TRUE:
                    case Valuation::INTERIOR_FALSE:
                    case Valuation::TRUE | Valuation::INTERIOR_TRUE:
                    case Valuation::TRUE | Valuation::INTERIOR_FALSE:
                    case Valuation::FALSE | Valuation::INTERIOR_FALSE:
                        continue;
                    default:
                        return false;
                    }
                }
            }
        }

    return true;
    }