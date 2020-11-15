#include <queue>
#include <QSR/rcc8.h>
#include "reasoner_internal.h"

using namespace qsr::rcc8::internal;

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

    return SolutionContext (clusterIndices, clusterCount);
    }