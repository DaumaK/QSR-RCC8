#include <gtest/gtest.h>
#include <QSR/rcc8.h>

using namespace qsr;

#pragma region STANDALONE RELATION TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableEQRelatons_True)
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

TEST (IsSatisfiable, IsSatisfiable_SatisfiableDCRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 1, 3, rcc8::RelationType::DC };
    auto relation2 = rcc8::Relation { 0, 2, rcc8::RelationType::DC };
    auto relation3 = rcc8::Relation { 0, 1, rcc8::RelationType::DC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_SatisfiableECRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 1, 3, rcc8::RelationType::EC };
    auto relation2 = rcc8::Relation { 0, 2, rcc8::RelationType::EC };
    auto relation3 = rcc8::Relation { 0, 1, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_SatisfiablePORelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 1, 3, rcc8::RelationType::PO };
    auto relation2 = rcc8::Relation { 0, 2, rcc8::RelationType::PO };
    auto relation3 = rcc8::Relation { 0, 1, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_SatisfiableTPPRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 1, 2, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 0, 2, rcc8::RelationType::TPP };
    auto relation3 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableTPPRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::TPP };
    auto relation3 = rcc8::Relation { 2, 0, rcc8::RelationType::TPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_SatisfiableNTPPRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 1, 2, rcc8::RelationType::NTPP };
    auto relation2 = rcc8::Relation { 0, 2, rcc8::RelationType::NTPP };
    auto relation3 = rcc8::Relation { 0, 1, rcc8::RelationType::NTPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableNTPPRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::NTPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::NTPP };
    auto relation3 = rcc8::Relation { 2, 0, rcc8::RelationType::NTPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region EQ, DC RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableEQAndDCRelations_True)
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

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableEQAndDCRelations_False)
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

#pragma endregion

#pragma region EQ, EC RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableEQAndECRelations_True)
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

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableEQAndECRelations_False)
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

#pragma endregion

#pragma region EQ, PO RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableEQAndPORelations_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 2, 3, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableEQAndPORelations_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region EQ, TPP RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableEQAndTPPRelations_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 2, 3, rcc8::RelationType::TPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableEQAndTPPRelations_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::TPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region EQ, NTPP RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableEQAndNTPPRelations_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 2, 3, rcc8::RelationType::NTPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableEQAndNTPPRelations_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EQ };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EQ };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::NTPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region DC, EC RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableDCAndECRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::DC };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EC };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableDCAndECRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::DC };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EC };
    auto relation3 = rcc8::Relation { 0, 1, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region DC, PO RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableDCAndPORelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::DC };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::PO };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableDCAndPORelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::DC };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::PO };
    auto relation3 = rcc8::Relation { 0, 1, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region DC, TPP RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableDCAndTPPRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::DC };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::TPP };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::TPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableDCAndTPPRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 2, rcc8::RelationType::DC };
    auto relation2 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation3 = rcc8::Relation { 1, 2, rcc8::RelationType::TPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region DC, NTPP RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableDCAndNTPPRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::DC };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::NTPP };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::NTPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableDCAndNTPPRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::DC };
    auto relation2 = rcc8::Relation { 2, 0, rcc8::RelationType::NTPP };
    auto relation3 = rcc8::Relation { 2, 1, rcc8::RelationType::NTPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region EC, PO RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableECAndPORelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 2, rcc8::RelationType::EC };
    auto relation2 = rcc8::Relation { 0, 1, rcc8::RelationType::PO };
    auto relation3 = rcc8::Relation { 1, 2, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableECAndPORelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 2, rcc8::RelationType::EC };
    auto relation2 = rcc8::Relation { 0, 1, rcc8::RelationType::PO };
    auto relation3 = rcc8::Relation { 1, 0, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region EC, TPP (and DC) RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableECAndTPPRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::TPP };
    auto relation3 = rcc8::Relation { 0, 3, rcc8::RelationType::EC };
    auto relation4 = rcc8::Relation { 1, 3, rcc8::RelationType::EC };
    auto relation5 = rcc8::Relation { 2, 3, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3, relation4, relation5 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableECAndTPPRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::EC };
    auto relation2 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_SatisfiableECAndTPPAndDCRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 1, 2, rcc8::RelationType::EC };
    auto relation2 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::DC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }


TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableECAndTPPAndDCRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 0, 2, rcc8::RelationType::EC };
    auto relation3 = rcc8::Relation { 1, 2, rcc8::RelationType::DC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region EC, NTPP RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableECAndNTPPRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 2, rcc8::RelationType::NTPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::NTPP };
    auto relation3 = rcc8::Relation { 3, 0, rcc8::RelationType::EC };
    auto relation4 = rcc8::Relation { 3, 1, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3, relation4 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableECAndNTPPRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::NTPP };
    auto relation2 = rcc8::Relation { 2, 1, rcc8::RelationType::EC };
    auto relation3 = rcc8::Relation { 2, 0, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region PO, TPP (and EC) RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiablePOAndTPPRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::PO };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiablePOAndTPPRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::PO };
    auto relation2 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_SatisfiablePOAndTPPAndECRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::PO };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }


TEST (IsSatisfiable, IsSatisfiable_UnsatisfiablePOAndTPPAndDCRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EC };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region PO, NTPP (and EC) RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiablePOAndNTPPRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::NTPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::PO };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiablePOAndNTPPRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::PO };
    auto relation2 = rcc8::Relation { 0, 1, rcc8::RelationType::NTPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_SatisfiablePOAndNTPPAndECRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::NTPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::PO };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }


TEST (IsSatisfiable, IsSatisfiable_UnsatisfiablePOAndNTPPAndDCRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::NTPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::EC };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion

#pragma region TPP, NTPP (and EC, PO) RELATIONS TESTS

TEST (IsSatisfiable, IsSatisfiable_SatisfiableTPPAndNTPPRelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::NTPP };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::NTPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableTPPAndNTPPRelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::NTPP };
    auto relation3 = rcc8::Relation { 0, 2, rcc8::RelationType::TPP };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_SatisfiableTPPAndNTPPAndECAndPORelatons_True)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::NTPP };
    auto relation3 = rcc8::Relation { 3, 2, rcc8::RelationType::PO };
    auto relation4 = rcc8::Relation { 3, 1, rcc8::RelationType::PO };
    auto relation5 = rcc8::Relation { 3, 0, rcc8::RelationType::EC };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3, relation4, relation5 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_TRUE (isSatisfiable);
    }

TEST (IsSatisfiable, IsSatisfiable_UnsatisfiableTPPAndNTPPAndECAndPORelatons_False)
    {
    // Arrange
    auto relation1 = rcc8::Relation { 0, 1, rcc8::RelationType::TPP };
    auto relation2 = rcc8::Relation { 1, 2, rcc8::RelationType::NTPP };
    auto relation3 = rcc8::Relation { 3, 2, rcc8::RelationType::PO };
    auto relation4 = rcc8::Relation { 3, 1, rcc8::RelationType::EC };
    auto relation5 = rcc8::Relation { 3, 0, rcc8::RelationType::PO };

    auto network = rcc8::ConstraintNetwork (5, { relation1, relation2, relation3, relation4, relation5 });

    // Act
    bool isSatisfiable = network.IsSatisfiable ();

    // Assert
    ASSERT_FALSE (isSatisfiable);
    }

#pragma endregion
