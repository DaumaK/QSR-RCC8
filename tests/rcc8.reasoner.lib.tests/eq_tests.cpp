#include <gtest/gtest.h>
#include <QSR/rcc8.h>

using namespace qsr;

TEST (IsSatisfiable_EQ, IsSatisfiable_EQRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 1, 3, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 0, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable_EQ, IsSatisfiable_EQAndSatisfiableDCRelations_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 2, 3, rcc8::RelationType::DC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable_EQ, IsSatisfiable_EQAndUnsatisfiableDCRelations_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::DC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

TEST (IsSatisfiable_EQ, IsSatisfiable_EQAndSatisfiableECRelations_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 2, 3, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable_EQ, IsSatisfiable_EQAndUnsatisfiableECRelations_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }