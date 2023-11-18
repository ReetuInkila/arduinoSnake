#include "../game/Pair.h"
#include "/usr/src/googletest/googletest/include/gtest/gtest.h"

TEST(PairTest, Constructor) {
    // Test the constructor of Pair
    Pair<int, double> myPair(42, 3.14);
    EXPECT_EQ(myPair.first, 42);
    EXPECT_EQ(myPair.second, 3.14);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}