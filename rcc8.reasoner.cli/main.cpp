#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <QSR/rcc8.h>

using namespace qsr;
qsr::rcc8::RelationType RelationStringToRelationType (std::string& relationStr);

int main (int argc, char* argv[])
    {
    if (argc <= 1)
        {
        std::cout << "No parameters specified. Use -h flag for help.\n";
        return -1;
        }

    std::string flag = argv[1];
    if (flag == "-h" || flag == "--help")
        {
        std::cout << "Usage: <executable> <optional_flag> <path_to_file>\n"
                     "\n"
                     "  A simple RCC-8 satisfiability checker.\n"
                     "  The result will be given to stdout."
                     "  The first line of the file should contain a single number n: the number of regions.\n"
                     "  Following lines should be of the following form: i <relation> j\n"
                     "  where 0 <= i, j < n, and relation is one of the following:\n"
                     "  DC (for disconnected),\n"
                     "  EC (for externally connected),\n"
                     "  EQ (for equal),\n"
                     "  PO (for partially overlapping),\n"
                     "  TPP (for tangential proper part),\n"
                     "  NTPP (for non-tangential proper part),\n"
                     "  TPPi (for tangential proper part inverse),\n"
                     "  NTPPi (for non-tangential proper part inverse).\n"
                     "\n"
                     "Options:\n"
                     "  -h, --help : shows this message\n"
                     "  -b, --binary : outputs the result as a binary digit 1 for 'true' or 0 for 'false' (default).\n"
                     "  -s, --string : outputs the result as an uncapitalised string 'true' or 'false'.\n"
                     "  -S, --String : outputs the result as a capitalised string 'True' or 'False'.\n";

        return 0;
        }


    std::string fileName = flag[0] == '-' ? argv[2] : flag;
    std::ifstream fin (fileName, std::ios::in);
    if (!fin.is_open ())
        {
        std::cout << "Failed to open file: " << argv[2] << '\n';
        return -1;
        }

    size_t regionCount;
    fin >> regionCount;

    auto network = qsr::rcc8::ConstraintNetwork (regionCount);

    size_t r1, r2;
    std::string relationStr;

    while (fin >> r1 >> relationStr >> r2)
        network.AddRelation ({ r1, r2, RelationStringToRelationType (relationStr) });

    fin.close ();

    bool isSatisfiable = network.IsSatisfiable ();
    if ("-s" == flag || "--string" == flag)
        std::cout << (isSatisfiable ? "true\n" : "false\n");
    else if ("-S" == flag || "--String" == flag)
        std::cout << (isSatisfiable ? "True\n" : "False\n");
    else
        std::cout << static_cast<int> (isSatisfiable) << "\n";

    return 0;
    }

qsr::rcc8::RelationType RelationStringToRelationType (std::string& relationStr)
    {
    for (char& character : relationStr)
        character = std::toupper (character);

    if ("DC" == relationStr)
        return qsr::rcc8::RelationType::DC;

    if ("EC" == relationStr)
        return qsr::rcc8::RelationType::EC;

    if ("EQ" == relationStr)
        return qsr::rcc8::RelationType::EQ;

    if ("PO" == relationStr)
        return qsr::rcc8::RelationType::PO;

    if ("TPP" == relationStr)
        return qsr::rcc8::RelationType::TPP;

    if ("NTPP" == relationStr)
        return qsr::rcc8::RelationType::NTPP;

    if ("TPPi" == relationStr)
        return qsr::rcc8::RelationType::TPPi;

    if ("NTPPi" == relationStr)
        return qsr::rcc8::RelationType::NTPPi;

    std::cout << "Failed to parse input file, unknown relation: " << relationStr << "\n";
    exit (-1);
    }