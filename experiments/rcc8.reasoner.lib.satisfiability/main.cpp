#include <random>
#include <string>
#include <fstream>
#include <QSR/rcc8.h>

#define NO_ACTION 8
#define RUN_COUNT 1000
#define CON_PROB_STEP 1

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
    auto distribution = std::discrete_distribution<short> { dcProb, ecProb, poProb, eqProb, tppProb, ntppProb, 0, 0, noneProb };

    auto relations = std::vector<qsr::rcc8::Relation>();

    for (size_t i = 0; i < variableCount; i++)
        {
        for (size_t j = i + 1; j < variableCount; j++)
            {
            short action = distribution (generator);
            if (action == NO_ACTION)
                continue;

            auto relationType = static_cast<qsr::rcc8::RelationType> (action);
            relations.push_back ({ i, j, relationType });
            }
        }

    return relations;
    }

void RunExperiment
(
std::string const& outputFile,
size_t variableCount,
size_t step,
double dcProb,
double ecProb,
double poProb,
double eqProb,
double tppProb,
double ntppProb,
double noneProb
)
    {
    std::ofstream fout (outputFile);
//    fout.precision (2);
//    fout << " p(dc)=" << dcProb
//         << " p(ec)=" << ecProb
//         << " p(po)=" << poProb
//         << " p(eq)=" << eqProb
//         << " p(tpp)=" << tppProb
//         << " p(ntpp)=" << ntppProb
//         << " p(none)=" << noneProb
//         << " runs=" << RUN_COUNT
//         << '\n';
//
//    fout.precision (32);
    for (size_t i = step; i <= variableCount; i += step)
        {
        size_t satisfiableCount = 0;
        for (size_t run = 0; run < RUN_COUNT; run++)
            {
            auto network = qsr::rcc8::ConstraintNetwork (i, GenerateRelations (i, dcProb, ecProb, poProb, eqProb, tppProb, ntppProb, noneProb));
            bool isSat = network.IsSatisfiable();
            if (isSat)
                satisfiableCount++;
            }

        double satProb = (double)satisfiableCount / RUN_COUNT;
        fout << i << " " << satProb << '\n';
        }

    fout.close ();
    }

void RunExtensiveExperiment (std::string const& outputFile, size_t step)
    {
    std::ofstream fout (outputFile);
    fout << "# runs: " << RUN_COUNT << '\n';

    for (size_t probConnected = 0; probConnected <= 100; probConnected += CON_PROB_STEP)
        {
        size_t zeroCount = 0;
        for (size_t i = step; i <= 100; i += step)
            {
            if (zeroCount >= 3)
                {
                fout << (double)probConnected / 100 << " " << i << " " << 0 << '\n';
                continue;
                }

            size_t satisfiableCount = 0;
            for (size_t run = 0; run < RUN_COUNT; run++)
                {
                double relProb = (double)probConnected / 2;
                auto network = qsr::rcc8::ConstraintNetwork (i, GenerateRelations (i, 0, 0, 0, 0, relProb, relProb, (double)100 - probConnected));
                bool isSat = network.IsSatisfiable();
                if (isSat)
                    satisfiableCount++;
                }

            double satProb = (double)satisfiableCount / RUN_COUNT;
            fout << (double)probConnected / 100 << " " << i << " " << satProb << '\n';

            if (satisfiableCount == 0)
                zeroCount++;
            }

        fout << '\n';
        }

    fout.close ();
    }

int main (int argc, char* argv[])
    {
    //RunExperiment ("equal_prob_none_half_no_inv.txt", 50, 1, (double)1/12, (double)1/12, (double)1/12, (double)1/12, (double)1/12, (double)1/12, (double)1/2);
    //RunExperiment ("equal_prob_no_eq_none_half_no_inv.txt", 50, 1, (double)1/10, (double)1/10, (double)1/10, 0, (double)1/10, (double)1/10, (double)1/2);
    //RunExperiment ("equal_prob_no_pp_none_half.txt", 50, 1, (double)1/8, (double)1/8, (double)1/8, (double)1/8, 0, 0, (double)1/2);
    RunExtensiveExperiment ("03_26_only_pp_no_inv.dat", 1);
    return 0;
    }