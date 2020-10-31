#include <iostream>
#include <QSR/rcc8.h>

using namespace qsr;

int main ()
    {
    auto rel = rcc8::Relation (0, 1, rcc8::RelationType::EC);

    std:: cout << rel.GetR1 () << " " << static_cast<int> (rel.GetRelationType ()) << " " << rel.GetR2 () << std::endl;
    return 0;
    }