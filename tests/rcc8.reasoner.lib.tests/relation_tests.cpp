#include <gtest/gtest.h>
#include <QSR/rcc8.h>

using namespace qsr;

TEST (rcc8_relation, Ctor_Values_ValuesSet)
    {
    // Arrange, Act
    auto relation = rcc8::Relation (0, 12, rcc8::RelationType::TPP);

    // Assert
    ASSERT_EQ (0, relation.GetR1 ());
    ASSERT_EQ (12, relation.GetR2 ());
    ASSERT_EQ (rcc8::RelationType::TPP, relation.GetRelationType ());
    }