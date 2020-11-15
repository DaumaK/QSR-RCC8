#include <iostream>
#include <QSR/rcc8.h>

using namespace qsr;

int main ()
    {
    auto rel = rcc8::Relation {0, 1, rcc8::RelationType::EC};

    std:: cout << rel.r1 << " " << static_cast<int> (rel.relationType) << " " << rel.r2 << std::endl;
    return 0;
    }