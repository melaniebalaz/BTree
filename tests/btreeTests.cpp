#include "gtest/gtest.h"
#include "../upload/Btree.h"
#include <stdlib.h>
#include "string.h"
//#include "../include/Btree.h"
//#include "../include/EmptyTreeException.h"
//#include "../include/Container.h"
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


template <typename E, int Degree = 31>
void debugTree(Btree<E,Degree> debugBtree) {
    std::ostringstream stdoutput;
    debugBtree.print(stdoutput);
    std::cout << '\n';
    std::cout << "_______________";
    std::cout << '\n';
    std::cout << '\n';
    std::cout << stdoutput.str();
};


#ifdef DEBUG_TESTS
#define DEBUG_TREE(Btree) debugTree<int>(Btree);
//#define DEBUG_TREE(Btree) debugTree<string>(Btree);
#else
#define DEBUG_TREE(Btree)
#endif

TEST(BtreeTest, TestEmpty){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.print(output);
    EXPECT_EQ(output.str(),"");
};

TEST(BtreeTest, TestOneElement){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n");
};

TEST(BtreeTest, TestTwoElementsInOrder){
    Btree<int, 2> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n");
};

TEST(BtreeTest, TestTwoElementsOutOfOrder){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(2);
    testBtree.add(1);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n");
};


TEST(BtreeTest, TestThreeElementsInOrder){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n3\n");
};

TEST(BtreeTest, TestThreeElementsOutOfOrder){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(2);
    testBtree.add(1);
    testBtree.add(3);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n3\n");
};

TEST(BtreeTest, TestThreeElements){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(2);
    testBtree.add(1);
    testBtree.add(4);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n4\n");
};

TEST(BtreeTest, TestFourElementsOutOfOrder){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(2);
    testBtree.add(4);
    testBtree.add(3);
    testBtree.add(1);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n3\n4\n");
};

/**
 *               [  4  ]
 *    [  1  |  2  | 3 ] [  4  |  5   ]
 *
 */


TEST(BtreeTest, TestFiveElementsInOrder){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n 3\n4\n 4\n 5\n");
};

/**
 *               [  4  ]
 *    [  1  |  2  | 3 ] [  4  |  5   ]
 *
 */

TEST(BtreeTest, TestFiveElementsOutOfOrder){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(2);
    testBtree.add(4);
    testBtree.add(1);
    testBtree.add(5);
    testBtree.add(3);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n 3\n4\n 4\n 5\n");
};

/**
 *               [  4  ]
 *    [  1  |  2  | 3 ] [  4  |  5  | 6 ]
 *
 */

TEST(BtreeTest, TestSixElementsInOrder){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n 3\n4\n 4\n 5\n 6\n");
};



TEST(BtreeTest, Test4ElementsDegree3){
    Btree<int,3> testBtree; // 3
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n3\n4\n");
};



TEST(BtreeTest, Test6ElementsDegree3){
    Btree<int,3> testBtree; //3
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(6);
    testBtree.add(5);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n3\n4\n5\n6\n");
};


/**
 *               [  5 ]
 *    [  1 | 2 | 3 | 4 ] [ 5 | 6 | 7 ]
 *
 */

TEST(BtreeTest, Test7ElementsDegree3){
    Btree<int,3> testBtree; //3
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(6);
    testBtree.add(5);
    testBtree.add(7);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n 3\n 4\n5\n 5\n 6\n 7\n");
};



/**
 *               [  9  ]
 *    [  1  |  2  | 3] [  9  |  10   ]
 *
 */



TEST(BtreeTest, TestPromotionOutofOrder){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(9);
    testBtree.add(10);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n 3\n9\n 9\n 10\n");
};


/**
 *         [ 4 7 ]
 *  [ 1 2 3 ] [ 4 5 6 ] [ 7 8 ]
 */



TEST(BtreeTest, TestPromotionInOrder){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8); //Promotion should happen here
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n 3\n4\n 4\n 5\n 6\n7\n 7\n 8\n");
};


/**
 *                                [  4 7 9 ]
 *               [ 1 2 3 ] [ 4 5 6 ] [ 7 8 ]  [ 9 10 11 ]
 *
 */


TEST(BtreeTest, TestSubBtreeShift){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(9);
    testBtree.add(10);
    testBtree.add(11);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n 3\n4\n 4\n 5\n 6\n7\n 7\n 8\n9\n 9\n 10\n 11\n");
};

TEST(BtreeTest, TestDuplicates){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n 3\n4\n 4\n 5\n");
};


TEST(BtreeTest, TestMemberTrue){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    EXPECT_EQ(true,testBtree.member(5));
};

TEST(BtreeTest, TestMemberTrue2){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    testBtree.print(output);
    EXPECT_EQ(true,testBtree.member(6));
};


/*
 * MAX and MIN Tests
 */

/**
 *         [ 4 7 ]
 *  [ 1 2 3 ] [ 4 5 6 ] [ 7 8 ]
 */

TEST(BtreeTest, TestMin){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    EXPECT_EQ(1,testBtree.min());
};


TEST(BtreeTest, TestMax){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    EXPECT_EQ(8,testBtree.max());
};

TEST(BtreeTest, TestEmptyTreeMaxException){
    Btree<int> testBtree;
    ASSERT_THROW(testBtree.max(), EmptyTreeException);
}

TEST(BtreeTest, TestEmptyTreeMinException){
    Btree<int> testBtree;
    ASSERT_THROW(testBtree.min(), EmptyTreeException);
}



TEST(BtreeTest, TestDefaultTreeConstructor){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(2);
    testBtree.add(1);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n");
};


TEST(BtreeTest, TestSizeMethod){
    Btree<int> testBtree;
    testBtree.add(4);
    testBtree.add(3);
    testBtree.add(2);
    testBtree.add(1);
    EXPECT_EQ(4,testBtree.size());
};



TEST(BtreeTest, TestSizeMethodAfterSplit){
    Btree<int> testBtree;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(9);
    testBtree.add(10);
    testBtree.add(11);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    EXPECT_EQ(11,testBtree.size());
    EXPECT_EQ(true, testBtree.member(7));
};


/**
 *                            [ 4 7 10 13 ]
 *                      [ 1 2 3 ] [ 4 5 6 ] [ 7 8 9 ] [ 10 11 12 ] [ 13 14 15 16]
 */

TEST(BtreeTest, LotsofElementsTest1){
    Btree<int> testBtree;
    for (int i = 1; i <= 16; i++){
        testBtree.add(i);
    }
    EXPECT_EQ(true, testBtree.member(10));
    EXPECT_EQ(true, testBtree.member(15));
    EXPECT_EQ(true, testBtree.member(16));
    EXPECT_EQ(true, testBtree.member(7));

    //Works fine until the root splits the second time!
}

/**                                  [10]
 *                                    [ 4 7 ]              [ 13 16 ]
 *                      [ 1 2 3 ] [ 4 5 6 ] [ 7 8 9 ] [ 10 11 12 ] [ 13 14 15 ] [ 16 17]
 */

TEST(BtreeTest, LotsofElementsTest2){
    Btree<int> testBtree;
    for (int i = 1; i <= 100; i++){
        testBtree.add(i);
    }

    EXPECT_EQ(true, testBtree.member(16));
    EXPECT_EQ(true, testBtree.member(18));
    EXPECT_EQ(100, testBtree.size());

    //Works fine until the root splits the second time!
}


TEST(BtreeTest, LotsofElementsTest4){
    Btree<int> testBtree;
    testBtree.add(1985);
    //DEBUG_TREE(testBtree);
    EXPECT_EQ(true,testBtree.member(1985));
    testBtree.add(1987);
    EXPECT_EQ(true,testBtree.member(1987));
    //DEBUG_TREE(testBtree);
    testBtree.add(1988);
    EXPECT_EQ(true,testBtree.member(1988));
    //DEBUG_TREE(testBtree);
    testBtree.add(1990);
    EXPECT_EQ(true,testBtree.member(1990));
    //DEBUG_TREE(testBtree);
    testBtree.add(1992);
    EXPECT_EQ(true,testBtree.member(1992));
    //DEBUG_TREE(testBtree);
    testBtree.add(1993);
    EXPECT_EQ(true,testBtree.member(1993));
    //DEBUG_TREE(testBtree);
    testBtree.add(1994);
    EXPECT_EQ(true,testBtree.member(1994));
    //DEBUG_TREE(testBtree);
    testBtree.add(1997);
    EXPECT_EQ(true,testBtree.member(1997));
    //DEBUG_TREE(testBtree);
    testBtree.add(1995);
    EXPECT_EQ(true,testBtree.member(1995));
    //DEBUG_TREE(testBtree);
    testBtree.add(1985);
    EXPECT_EQ(true,testBtree.member(1985));
    //DEBUG_TREE(testBtree);
    testBtree.add(2004);
    EXPECT_EQ(true,testBtree.member(2004));
    //DEBUG_TREE(testBtree);
    testBtree.add(2007);
    EXPECT_EQ(true,testBtree.member(2007));
    //DEBUG_TREE(testBtree);
    testBtree.add(2008);
    EXPECT_EQ(true,testBtree.member(2008));
    //DEBUG_TREE(testBtree);
    testBtree.add(2009);
    EXPECT_EQ(true,testBtree.member(2009));
    //DEBUG_TREE(testBtree);
    testBtree.add(2009);
    EXPECT_EQ(true,testBtree.member(2009));
    //DEBUG_TREE(testBtree);
    testBtree.add(2012);
    EXPECT_EQ(true,testBtree.member(2012));
    //DEBUG_TREE(testBtree);
    testBtree.add(1995);
    EXPECT_EQ(true,testBtree.member(1995));
    //DEBUG_TREE(testBtree);
    testBtree.add(4);
    EXPECT_EQ(true,testBtree.member(4));
    //DEBUG_TREE(testBtree);

    //this is what kills it!
    testBtree.add(14);
    EXPECT_EQ(true,testBtree.member(14));
    EXPECT_EQ(true,testBtree.member(2012));

    //Works fine until the root splits the second time!
}


TEST(BtreeTest, TestDuplicates2){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(1);
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(5);
    testBtree.add(4);
    testBtree.add(12);
    testBtree.add(4);
    testBtree.add(45);
    testBtree.add(45);
    testBtree.print(output);
    EXPECT_EQ(7, testBtree.size());
};




TEST(BtreeTest, RemoveElementfromRoot){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(9);
    testBtree.remove(9);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n3\n");
};

TEST(BtreeTest, RemoveElementfromRootAndShift){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(9);
    testBtree.remove(3);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n2\n9\n");
};


/**
 *               [  9  ]
 *    [  1  |  2  | 3] [  9  |  10   ]
 *
 */

TEST(BtreeTest, RemoveElementfromLeaf){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(9);
    testBtree.add(10);
    testBtree.remove(3);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n9\n 9\n 10\n");
};


/**
 *                            [ 4 7 10 13 ]
 *                      [ 1 2 3 ] [ 4 5 6 ] [ 7 8 9 ] [ 10 11 12 ] [ 13 14 15 16]
 */

TEST(BtreeTest, RemoveSeveralElements){
    Btree<int> testBtree;
    for (int i = 1; i <= 16; i++){
        testBtree.add(i);
    }
    testBtree.remove(10);
    testBtree.remove(15);
    testBtree.remove(16);
    testBtree.remove(7);
    EXPECT_EQ(false, testBtree.member(10));
    EXPECT_EQ(false, testBtree.member(15));
    EXPECT_EQ(false, testBtree.member(16));
    EXPECT_EQ(false, testBtree.member(7));

}


/**
 *              3
 *          1 2   10
 *
 */

TEST(BtreeTest, RemoveElementAndMergeLeft){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(9);
    testBtree.add(10);
    testBtree.remove(9);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 1\n 2\n3\n 3\n 10\n");
};

/*
 *           3
*      1 3     10
 */


TEST(BtreeTest, RemoveElementAndMerge){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(9);
    testBtree.add(10);
    testBtree.remove(2);
    testBtree.remove(9);
    testBtree.print(output);
    EXPECT_EQ(output.str(),"1\n3\n10\n");
};

/*
*         3
*   3  9 10 11
*/

TEST(BtreeTest, TestMergeRight){
    Btree<int> testBtree;
    std::ostringstream output;
    //overwrites the original output Object -> passed by reference
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(9);
    testBtree.add(10);
    testBtree.add(11);
    testBtree.remove(2);
    testBtree.remove(1);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 3\n 9\n10\n 10\n 11\n");
};



TEST(BtreeTest, TestMaxAfterRemove){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    testBtree.remove(8);
    EXPECT_EQ(7,testBtree.max());
};


TEST(BtreeTest, TesMinAfterRemove){
    Btree<int> testBtree;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    testBtree.remove(1);
    EXPECT_EQ(2,testBtree.min());
};


/*        4       6
 *  1 2 3   4 5 6   7 8 9 10
 */

TEST(BtreeTest, TestSplitAfterMerge){
    Btree<int> testBtree;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    testBtree.remove(1);
    EXPECT_EQ(2,testBtree.min());
    EXPECT_EQ(7,testBtree.size());
};


void testPrinter(const int& element){

}


TEST(BtreeTest, TesApplyEmpty){
    Btree<int> testBtree;
    size_t n;
    n = testBtree.apply(testPrinter, ascending);
    EXPECT_EQ(0,n);
};

/*TEST(BtreeTest, TesApplyAsc){
    Btree<int> testBtree;
    testBtree.add(11);
    testBtree.add(12);
    testBtree.add(15);
    testBtree.add(17);
    testBtree.add(9);
    testBtree.add(6);
    testBtree.add(2);
    size_t n;
    n = testBtree.apply(testPrinter, ascending);
    EXPECT_EQ(7,n);
};*/

TEST(BtreeTest, TesApplyDesc){
    Btree<int> testBtree;
    testBtree.add(11);
    testBtree.add(12);
    testBtree.add(15);
    testBtree.add(17);
    testBtree.add(9);
    testBtree.add(6);
    testBtree.add(2);
    int expectedResult[7] = {17, 15, 12, 11, 9, 6, 2};
    int actualResult[7];
    int actualResultCounter = 0;
    std::function<void(const int & element)> resultCollector(
        [&actualResult, &actualResultCounter](const int & element){
            actualResult[actualResultCounter++] = element;
        }
    );
    testBtree.apply(resultCollector, descending);
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(expectedResult[i], actualResult[i]);
    }
};


TEST(BtreeTest, TesApplyAsc2){
    Btree<string> testBtree;
    testBtree.add(string("d-4711"));
    testBtree.add(string("d-4294967295"));
    testBtree.add(string("c-666"));

    string actualResult[3];
    int actualResultCounter = 0;
    std::function<void(const string & element)> resultCollector(
            [&actualResult, &actualResultCounter](const string & element){
                actualResult[actualResultCounter++] = element;
            }
    );
    string expectedResult[3] = {string("c-666"), string("d-4294967295"), string("d-4711")};

    testBtree.apply(resultCollector, ascending);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(expectedResult[i], actualResult[i]);
    }
};

/*
Removing 1 elements...
Removing c-666
Tree is empty!
Removing 3 elements...
Removing c-666
Removing d-4711
Removing a-0
Tree is empty!
Adding 0 elements...
Adding 3 elements...
Adding d-4294967295
Adding d-4711
Adding c-666
Adding 0 elements...
Removing 1 elements...
Removing d-123
 */
TEST(BtreeTest, TestRandomEmptyRemoval) {
    Btree<string> testBtree;
    string * threeData2 = new string[3];
    threeData2[0] = string("d-4294967295");
    threeData2[1] = string("d-4711");
    threeData2[2] = string("c-666");
    testBtree.add(threeData2, 3);

    testBtree.add(nullptr, 0);
    testBtree.remove(string("d-123"));

    string actualResult[3];
    int actualResultCounter = 0;
    std::function<void(const string & element)> resultCollector(
            [&actualResult, &actualResultCounter](const string & element){
                actualResult[actualResultCounter++] = element;
            }
    );
    string expectedResult[3] = {string("c-666"), string("d-4294967295"), string("d-4711")};

    testBtree.apply(resultCollector, ascending);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(expectedResult[i], actualResult[i]);
    }

};



TEST(BtreeTest, RemoveRandomElementsTest){
    Btree<int> testBtree;
    testBtree.add(1985);
    //DEBUG_TREE(testBtree);
    testBtree.add(1987);
    //DEBUG_TREE(testBtree);
    testBtree.add(1988);
    //DEBUG_TREE(testBtree);
    testBtree.add(1990);
    //DEBUG_TREE(testBtree);
    testBtree.add(1992);
    //DEBUG_TREE(testBtree);
    testBtree.add(1993);
    //DEBUG_TREE(testBtree);
    testBtree.add(1994);
    //DEBUG_TREE(testBtree);
    testBtree.add(1997);
    //DEBUG_TREE(testBtree);
    testBtree.add(1995);
    //DEBUG_TREE(testBtree);
    testBtree.add(1985);
    //DEBUG_TREE(testBtree);
    testBtree.add(2004);
    //DEBUG_TREE(testBtree);
    testBtree.add(2007);
    //DEBUG_TREE(testBtree);
    testBtree.add(2008);
    //DEBUG_TREE(testBtree);
    testBtree.add(2009);
    //DEBUG_TREE(testBtree);
    testBtree.add(2009);
    //DEBUG_TREE(testBtree);
    testBtree.add(2012);
    //DEBUG_TREE(testBtree);
    testBtree.add(1995);
    //DEBUG_TREE(testBtree);
    testBtree.add(4);
    testBtree.add(14);
    testBtree.remove(1985);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1987);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1988);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1990);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1992);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1993);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1994);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1997);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1995);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1985);
    //DEBUG_TREE(testBtree);
    testBtree.remove(2004);
    //DEBUG_TREE(testBtree);
    testBtree.remove(2007);
    //DEBUG_TREE(testBtree);
    testBtree.remove(2008);
    //DEBUG_TREE(testBtree);
    testBtree.remove(2009);
    //DEBUG_TREE(testBtree);
    testBtree.remove(2009);
    //DEBUG_TREE(testBtree);
    testBtree.remove(2012);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1995);
    EXPECT_EQ(false, testBtree.member(1995));
    //DEBUG_TREE(testBtree);
    testBtree.remove(4);
    testBtree.remove(14);
}


/*
 *        4      7
 *  1 2 3  4 5 6  7 8
 */



TEST(BtreeTest, RemoveAndAdd30Elements) {
    Btree<int> testBtree;
    std::ostringstream output;
    for (int i=1; i <= 30; i++){
        testBtree.add(i);
    }
    //DEBUG_TREE(testBtree);
    testBtree.print(output);
    EXPECT_EQ(output.str(), "  1\n"
            "  2\n"
            "  3\n"
            " 4\n"
            "  4\n"
            "  5\n"
            "  6\n"
            " 7\n"
            "  7\n"
            "  8\n"
            "  9\n"
            "10\n"
            "  10\n"
            "  11\n"
            "  12\n"
            " 13\n"
            "  13\n"
            "  14\n"
            "  15\n"
            " 16\n"
            "  16\n"
            "  17\n"
            "  18\n"
            "19\n"
            "  19\n"
            "  20\n"
            "  21\n"
            " 22\n"
            "  22\n"
            "  23\n"
            "  24\n"
            " 25\n"
            "  25\n"
            "  26\n"
            "  27\n"
            " 28\n"
            "  28\n"
            "  29\n"
            "  30\n"
);


testBtree.remove(1);
    std::ostringstream output1;
    testBtree.print(output1);
    EXPECT_EQ(output1.str(), "  2\n"
            "  3\n"
            " 4\n"
            "  4\n"
            "  5\n"
            "  6\n"
            " 7\n"
            "  7\n"
            "  8\n"
            "  9\n"
            "10\n"
            "  10\n"
            "  11\n"
            "  12\n"
            " 13\n"
            "  13\n"
            "  14\n"
            "  15\n"
            " 16\n"
            "  16\n"
            "  17\n"
            "  18\n"
            "19\n"
            "  19\n"
            "  20\n"
            "  21\n"
            " 22\n"
            "  22\n"
            "  23\n"
            "  24\n"
            " 25\n"
            "  25\n"
            "  26\n"
            "  27\n"
            " 28\n"
            "  28\n"
            "  29\n"
            "  30\n"
    );



testBtree.remove(2);



testBtree.remove(3);

     {
        std::ostringstream output2;
        testBtree.print(output2);
        string expectedResult = (
                "  4\n"
                "  5\n"
                "  6\n"
                " 7\n"
                "  7\n"
                "  8\n"
                "  9\n"
                " 10\n"
                "  10\n"
                "  11\n"
                "  12\n"
                " 13\n"
                "  13\n"
                "  14\n"
                "  15\n"
                " 16\n"
                "  16\n"
                "  17\n"
                "  18\n"
                "19\n"
                "  19\n"
                "  20\n"
                "  21\n"
                " 22\n"
                "  22\n"
                "  23\n"
                "  24\n"
                " 25\n"
                "  25\n"
                "  26\n"
                "  27\n"
                " 28\n"
                "  28\n"
                "  29\n"
                "  30\n");
        EXPECT_EQ(output2.str(), expectedResult);
    }




testBtree.remove(4);

      {
        std::ostringstream output2;
        testBtree.print(output2);
        string expectedResult = (
                "  5\n"
                "  6\n"
                " 7\n"
                "  7\n"
                "  8\n"
                "  9\n"
                " 10\n"
                "  10\n"
                "  11\n"
                "  12\n"
                " 13\n"
                "  13\n"
                "  14\n"
                "  15\n"
                " 16\n"
                "  16\n"
                "  17\n"
                "  18\n"
                "19\n"
                "  19\n"
                "  20\n"
                "  21\n"
                " 22\n"
                "  22\n"
                "  23\n"
                "  24\n"
                " 25\n"
                "  25\n"
                "  26\n"
                "  27\n"
                " 28\n"
                "  28\n"
                "  29\n"
                "  30\n");
        EXPECT_EQ(output2.str(), expectedResult);
    }




testBtree.remove(5);

testBtree.remove(6);
testBtree.remove(7);

        {
        std::ostringstream output2;
        testBtree.print(output2);
        string expectedResult = (
                "  8\n"
                "  9\n"
                " 10\n"
                "  10\n"
                "  11\n"
                "  12\n"
                " 13\n"
                "  13\n"
                "  14\n"
                "  15\n"
                " 16\n"
                "  16\n"
                "  17\n"
                "  18\n"
                "19\n"
                "  19\n"
                "  20\n"
                "  21\n"
                " 22\n"
                "  22\n"
                "  23\n"
                "  24\n"
                " 25\n"
                "  25\n"
                "  26\n"
                "  27\n"
                " 28\n"
                "  28\n"
                "  29\n"
                "  30\n");
        EXPECT_EQ(output2.str(), expectedResult);
    }


  testBtree.remove(8);


  testBtree.remove(9);
  testBtree.remove(10);

      testBtree.remove(8);

 //DEBUG_TREE(testBtree);
 testBtree.remove(11);
 testBtree.remove(13);
 testBtree.remove(12);
 testBtree.remove(14);
 testBtree.remove(15);
 testBtree.remove(17);
 testBtree.remove(16);
 testBtree.remove(18);
 for (int i= 19; i <= 30; i++){
 testBtree.remove(i);
 }
 EXPECT_EQ(0, testBtree.size());



}

TEST(BtreeTest, RemoveAllAddeddElements){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    testBtree.add(9);
    testBtree.add(10);
    testBtree.add(11);
    testBtree.add(12);
    testBtree.add(13);
    testBtree.add(14);
    testBtree.add(15);
    testBtree.add(16);
    testBtree.add(17);
    //DEBUG_TREE(testBtree);
    testBtree.remove(1);
    testBtree.remove(2);
    testBtree.remove(3);
    testBtree.print(output);
    EXPECT_EQ(output.str()," 4\n 5\n 6\n7\n 7\n 8\n 9\n10\n 10\n 11\n 12\n13\n 13\n 14\n 15\n16\n 16\n 17\n");
    testBtree.remove(4);
    testBtree.remove(5);
    testBtree.remove(6);
    testBtree.remove(7);
    testBtree.remove(8);
    testBtree.remove(9);
    testBtree.remove(10);
    testBtree.remove(11);
    testBtree.remove(13);
    testBtree.remove(12);
    testBtree.remove(14);
    testBtree.remove(15);
    testBtree.remove(17);
    testBtree.remove(16);

    EXPECT_EQ(0,testBtree.size());
};

TEST(BtreeTest, RemoveAllAddedElements2) {
    Btree<int> testBtree;
    std::ostringstream output;

    testBtree.add(29);
    testBtree.add(9);
    testBtree.add(4);
    testBtree.add(22);
    testBtree.add(30);
    testBtree.add(19);
    testBtree.add(21);
    testBtree.add(13);
    testBtree.add(23);
    testBtree.add(14);
    testBtree.add(3);
    testBtree.add(17);
    testBtree.add(1);
    testBtree.add(8);
    testBtree.add(11);
    testBtree.add(10);
    testBtree.add(2);
    testBtree.add(7);
    testBtree.add(20);
    testBtree.add(16);
    testBtree.add(24);
    testBtree.add(6);
    testBtree.add(5);
    testBtree.add(26);
    testBtree.add(25);
    testBtree.add(28);
    testBtree.add(18);
    testBtree.add(15);
    testBtree.add(27);
    testBtree.add(12);

    testBtree.remove(29);
    {
        testBtree.print(output);
        EXPECT_EQ(output.str(), "  1\n"
                "  2\n"
                "  3\n"
                " 4\n"
                "  4\n"
                "  5\n"
                "  6\n"
                " 7\n"
                "  7\n"
                "  8\n"
                " 9\n"
                "  9\n"
                "  10\n"
                "  11\n"
                " 12\n"
                "  12\n"
                "  13\n"
                "14\n"
                "  14\n"
                "  15\n"
                "  16\n"
                " 17\n"
                "  17\n"
                "  18\n"
                " 19\n"
                "  19\n"
                "  20\n"
                "21\n"
                "  21\n"
                "  22\n"
                "  23\n"
                " 24\n"
                "  24\n"
                "  25\n"
                "  26\n"
                " 27\n"
                "  27\n"
                "  28\n"
                "  30\n"
        );
    }


    testBtree.remove(9);

     {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             "  3\n"
             " 4\n"
             "  4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             " 12\n"
             "  12\n"
             "  13\n"
             "14\n"
             "  14\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             " 19\n"
             "  19\n"
             "  20\n"
             "21\n"
             "  21\n"
             "  22\n"
             "  23\n"
             " 24\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n"
             "  30\n");
    EXPECT_EQ(output.str(), expectedResult);
    }


    testBtree.remove(4);
      {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             "  3\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             " 12\n"
             "  12\n"
             "  13\n"
             "14\n"
             "  14\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             " 19\n"
             "  19\n"
             "  20\n"
             "21\n"
             "  21\n"
             "  22\n"
             "  23\n"
             " 24\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n"
             "  30\n");
    EXPECT_EQ(output.str(), expectedResult);
    }



    testBtree.remove(22);

     {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             "  3\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             " 12\n"
             "  12\n"
             "  13\n"
             "14\n"
             "  14\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             " 19\n"
             "  19\n"
             "  20\n"
             "21\n"
             "  21\n"
             "  23\n"
             " 24\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n"
             "  30\n");
    EXPECT_EQ(output.str(), expectedResult);
    }



   testBtree.remove(30);

     {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             "  3\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             " 12\n"
             "  12\n"
             "  13\n"
             "14\n"
             "  14\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             " 19\n"
             "  19\n"
             "  20\n"
             "21\n"
             "  21\n"
             "  23\n"
             " 24\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n");
    EXPECT_EQ(output.str(), expectedResult);
    }



   testBtree.remove(19);

      {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             "  3\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             "12\n"
             "  12\n"
             "  13\n"
             " 14\n"
             "  14\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             "  20\n"
             "21\n"
             "  21\n"
             "  23\n"
             " 24\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n");
    EXPECT_EQ(output.str(), expectedResult);
    }


  testBtree.remove(21);

      {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             "  3\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             "12\n"
             "  12\n"
             "  13\n"
             " 14\n"
             "  14\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             "  20\n"
             "21\n"
             "  23\n"
             "  24\n"
             " 25\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n");
    EXPECT_EQ(output.str(), expectedResult);
    }


  testBtree.remove(13);

     {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             "  3\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             "12\n"
             "  12\n"
             "  14\n"
             " 15\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             "  20\n"
             "21\n"
             "  23\n"
             "  24\n"
             " 25\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n");
    EXPECT_EQ(output.str(), expectedResult);
    }


   testBtree.remove(23);

     {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             "  3\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             "12\n"
             "  12\n"
             "  14\n"
             " 15\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             "  20\n"
             " 21\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n");
    EXPECT_EQ(output.str(), expectedResult);
    }


  testBtree.remove(14);

     {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             "  3\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             "12\n"
             "  12\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             "  20\n"
             " 21\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n");
    EXPECT_EQ(output.str(), expectedResult);
    }


  testBtree.remove(3);

       {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             "12\n"
             "  12\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  17\n"
             "  18\n"
             "  20\n"
             " 21\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n");
    EXPECT_EQ(output.str(), expectedResult);
    }

 testBtree.remove(17);

        {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =("  1\n"
             "  2\n"
             " 4\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             "12\n"
             "  12\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  18\n"
             "  20\n"
             " 21\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n");
    EXPECT_EQ(output.str(), expectedResult);
    }

    testBtree.remove(1);

         {
    std::ostringstream output;
    testBtree.print(output);
     string expectedResult =(
             "  2\n"
             "  5\n"
             "  6\n"
             " 7\n"
             "  7\n"
             "  8\n"
             " 9\n"
             "  10\n"
             "  11\n"
             "12\n"
             "  12\n"
             "  15\n"
             "  16\n"
             " 17\n"
             "  18\n"
             "  20\n"
             " 21\n"
             "  24\n"
             "  25\n"
             "  26\n"
             " 27\n"
             "  27\n"
             "  28\n");
    EXPECT_EQ(output.str(), expectedResult);
    }

   testBtree.remove(8);

    {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                "  2\n"
                "  5\n"
                " 6\n"
                "  6\n"
                "  7\n"
                " 9\n"
                "  10\n"
                "  11\n"
                "12\n"
                "  12\n"
                "  15\n"
                "  16\n"
                " 17\n"
                "  18\n"
                "  20\n"
                " 21\n"
                "  24\n"
                "  25\n"
                "  26\n"
                " 27\n"
                "  27\n"
                "  28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }

   testBtree.remove(11);

     {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                "  2\n"
                "  5\n"
                " 6\n"
                "  6\n"
                "  7\n"
                "  10\n"
                " 12\n"
                "  12\n"
                "  15\n"
                "  16\n"
                "17\n"
                "  18\n"
                "  20\n"
                " 21\n"
                "  24\n"
                "  25\n"
                "  26\n"
                " 27\n"
                "  27\n"
                "  28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }

   testBtree.remove(10);
      {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                "  2\n"
                "  5\n"
                " 6\n"
                "  6\n"
                "  7\n"
                " 12\n"
                "  12\n"
                "  15\n"
                "  16\n"
                "17\n"
                "  18\n"
                "  20\n"
                " 21\n"
                "  24\n"
                "  25\n"
                "  26\n"
                " 27\n"
                "  27\n"
                "  28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }

    testBtree.remove(2);
    {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                " 5\n"
                " 6\n"
                " 7\n"
                "12\n"
                " 12\n"
                " 15\n"
                " 16\n"
                "17\n"
                " 18\n"
                " 20\n"
                "21\n"
                " 24\n"
                " 25\n"
                " 26\n"
                "27\n"
                " 27\n"
                " 28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }


    testBtree.remove(7);
    {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                " 5\n"
                " 6\n"
                "12\n"
                " 12\n"
                " 15\n"
                " 16\n"
                "17\n"
                " 18\n"
                " 20\n"
                "21\n"
                " 24\n"
                " 25\n"
                " 26\n"
                "27\n"
                " 27\n"
                " 28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }

   testBtree.remove(20);

    {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                " 5\n"
                        " 6\n"
                        "12\n"
                        " 12\n"
                        " 15\n"
                        "16\n"
                        " 16\n"
                        " 18\n"
                        "21\n"
                        " 24\n"
                        " 25\n"
                        " 26\n"
                        "27\n"
                        " 27\n"
                        " 28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }


   testBtree.remove(16);

    {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                " 5\n"
                " 6\n"
                "12\n"
                " 12\n"
                " 15\n"
                " 18\n"
                "21\n"
                " 24\n"
                " 25\n"
                " 26\n"
                "27\n"
                " 27\n"
                " 28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }

   testBtree.remove(24);
    {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                " 5\n"
                " 6\n"
                "12\n"
                " 12\n"
                " 15\n"
                " 18\n"
                "21\n"
                " 25\n"
                " 26\n"
                "27\n"
                " 27\n"
                " 28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }

   testBtree.remove(6);

    {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                " 5\n"
                " 12\n"
                "15\n"
                " 15\n"
                " 18\n"
                "21\n"
                " 25\n"
                " 26\n"
                "27\n"
                " 27\n"
                " 28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }
   testBtree.remove(5);

    {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                " 12\n"
                " 15\n"
                " 18\n"
                "21\n"
                " 25\n"
                " 26\n"
                "27\n"
                " 27\n"
                " 28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }


    testBtree.remove(26);

     {
        std::ostringstream output;
        testBtree.print(output);
        string expectedResult =(
                " 12\n"
                " 15\n"
                "18\n"
                " 18\n"
                " 25\n"
                "27\n"
                " 27\n"
                " 28\n");
        EXPECT_EQ(output.str(), expectedResult);
    }

   testBtree.remove(25);
   testBtree.remove(28);
   testBtree.remove(18);
   testBtree.remove(15);
   testBtree.remove(27);
   testBtree.remove(12);

    //DEBUG_TREE(testBtree);

   EXPECT_EQ(0,testBtree.size());

}


TEST(BtreeTest, RemoveAndAddAndthenApplyMixture){
    Btree<int> testBtree;
    std::ostringstream output;
    testBtree.add(66);
     testBtree.remove(43);
     testBtree.add(67);
     testBtree.add(63);
     testBtree.remove(47);
     testBtree.add(61);
     testBtree.remove(8);
     testBtree.add(29);
     testBtree.add(50);
     testBtree.add(2);
     testBtree.add(58);
     testBtree.remove(70);
     testBtree.remove(23);
     testBtree.remove(12);
     testBtree.add(5);
     testBtree.add(25);
     testBtree.add(12);
     testBtree.add(62);
     testBtree.add(54);
     testBtree.add(14);
    testBtree.add(7);
    testBtree.remove(66);
    //DEBUG_TREE(testBtree);

    int expectedResult[14] = {67, 63, 62, 61, 58, 54, 50, 29, 25, 14, 12, 7, 5, 2};
    int actualResult[14];
    int actualResultCounter = 0;
    std::function<void(const int & element)> resultCollector(
            [&actualResult, &actualResultCounter](const int & element){
                actualResult[actualResultCounter++] = element;
            }
    );
    testBtree.apply(resultCollector, descending);
    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(expectedResult[i], actualResult[i]);
    }
};


TEST(BtreeTest, TestDegree31){
    Btree<int, 31> testBtree;
    testBtree.add(19932546);
    testBtree.add(27706653);
    testBtree.add(28925691);
    testBtree.add(52107318);
    testBtree.add(57271926);
    testBtree.add(66433441);
    testBtree.add(68362598);
    testBtree.add(77268269);
    testBtree.add(115120654);
    testBtree.add(145532761);
    testBtree.add(158379552);
    testBtree.add(205711490);
    testBtree.add(210367714);
    testBtree.add(247074805);
    testBtree.add(250591794);
    testBtree.add(309696691);
    testBtree.add(393860762);
    testBtree.add(400151788);
    testBtree.add(422527594);
    testBtree.add(428300259);
    testBtree.add(480849991);
    testBtree.add(496586426);
    testBtree.add(496586426);
    testBtree.add(515529753);
    testBtree.add(520932930);
    testBtree.add(525706991);
    testBtree.add(569022154);
    testBtree.add(590294128);
    testBtree.add(608455363);
    testBtree.add(631361083);
    testBtree.add(664835076);
    testBtree.add(675891343);
    testBtree.add(679469414);
    testBtree.add(763654014);
    testBtree.add(764058775);
    testBtree.add(792526220);
    testBtree.add(809673979);
    testBtree.add(810662187);
    testBtree.add(810662187);
    testBtree.add(819516268);
    testBtree.add(822784415);
    testBtree.add(838023412);
    testBtree.add(890459872);
    testBtree.add(892086236);
    testBtree.add(897787792);
    testBtree.add(899316322);
    testBtree.add(926881476);
    testBtree.add(968021766);
    testBtree.add(1002898451);
    testBtree.add(1006609540);
    testBtree.add(1009021007);
    testBtree.add(1028169396);
    testBtree.add(1028169396);
    testBtree.add(1040043610);
    testBtree.add(1046126087);
    testBtree.add(1073226880);
    testBtree.add(1094100450);
    testBtree.add(1152891831);
    testBtree.add(1163120341);
    testBtree.add(1269870926);
    testBtree.add(1290446329);
    testBtree.add(1294600846);
    testBtree.add(1359072203);
    testBtree.add(1370738826);
    testBtree.add(1461728458);
    testBtree.add(1462087311);
    testBtree.add(1500357984);
    testBtree.add(1514888112);
    testBtree.add(1559526673);
    testBtree.add(1559526673);
    testBtree.add(1566369460);
    testBtree.add(1567674295);
    testBtree.add(1579802159);
    testBtree.add(1643550337);
    testBtree.add(1664792818);
    testBtree.add(1669187896);
    testBtree.add(1671889999);
    testBtree.add(1710028745);
    testBtree.add(1719408956);
    testBtree.add(1731106012);
    testBtree.add(1734177661);
    testBtree.add(1741849297);
    testBtree.add(1779175845);
    testBtree.add(1789614810);
    testBtree.add(1789614810);
    testBtree.add(1791277536);
    testBtree.add(1793547003);
    testBtree.add(1797288065);
    testBtree.add(1809249219);
    testBtree.add(1830665860);
    testBtree.add(1840335376);
    testBtree.add(1846443803);
    testBtree.add(1906706780);
    testBtree.add(1950367213);
    testBtree.add(2002830094);
    testBtree.add(2042297871);
    testBtree.add(2055540383);
    testBtree.add(2064010129);
    testBtree.add(2085187937);
    testBtree.add(2091824407);
    testBtree.add(2097549478);
    testBtree.add(2116969294);
    testBtree.add(2132723841);
    testBtree.add(2139642574);
    testBtree.add(2146335337);

    testBtree.remove(2002830094);
    testBtree.remove(763654014);
    testBtree.remove(810662187);
    testBtree.remove(1269870926);
    testBtree.remove(1731106012);
    testBtree.remove(926881476);
    testBtree.remove(897787792);
    testBtree.remove(1009021007);
    testBtree.remove(205711490);
    testBtree.remove(2064010129);
    testBtree.remove(57271926);
    testBtree.remove(19932546);
    testBtree.remove(1290446329);
    testBtree.remove(1163120341);
    testBtree.remove(1906706780);
    testBtree.remove(2055540383);
    testBtree.remove(1840335376);
    testBtree.remove(1789614810);
    testBtree.remove(1579802159);
    testBtree.remove(68362598);
    testBtree.remove(1791277536);
    testBtree.remove(247074805);
    testBtree.remove(664835076);
    testBtree.remove(631361083);
    testBtree.remove(764058775);
    testBtree.remove(145532761);
    testBtree.remove(1950367213);
    testBtree.remove(1664792818);
    testBtree.remove(496586426);
    testBtree.remove(1643550337);
    testBtree.remove(2116969294);
    testBtree.remove(515529753);
    testBtree.remove(496586426);
    testBtree.remove(679469414);
    testBtree.remove(250591794);
    testBtree.remove(1797288065);
    testBtree.remove(2091824407);
    testBtree.remove(890459872);
    testBtree.remove(77268269);
    testBtree.remove(66433441);
    testBtree.remove(1710028745);
    testBtree.remove(1559526673);
    testBtree.remove(520932930);
    testBtree.remove(1809249219);
    testBtree.remove(1462087311);
    testBtree.remove(809673979);
    testBtree.remove(1719408956);
    testBtree.remove(1789614810);
    testBtree.remove(480849991);
    testBtree.remove(1002898451);
    testBtree.remove(1830665860);
    testBtree.remove(1028169396);
    testBtree.remove(115120654);
    testBtree.remove(1500357984);
    testBtree.remove(1567674295);
    testBtree.remove(810662187);
    testBtree.remove(1793547003);
    testBtree.remove(28925691);
    testBtree.remove(2146335337);
    testBtree.remove(2085187937);
    testBtree.remove(1028169396);
    testBtree.remove(1671889999);
    testBtree.remove(210367714);
    testBtree.remove(1294600846);
    testBtree.remove(968021766);
    testBtree.remove(899316322);
    testBtree.remove(1040043610);
    testBtree.remove(309696691);
    testBtree.remove(1734177661);
    testBtree.remove(2042297871);
    testBtree.remove(569022154);
    testBtree.remove(428300259);
    testBtree.remove(892086236);
    testBtree.remove(1094100450);
    testBtree.remove(27706653);
    testBtree.remove(1566369460);
    testBtree.remove(1559526673);
    testBtree.remove(1669187896);
    testBtree.remove(422527594);
    testBtree.remove(2097549478);
    testBtree.remove(590294128);
    testBtree.remove(1359072203);
    testBtree.remove(525706991);
    testBtree.remove(1741849297);
    testBtree.remove(1846443803);
    testBtree.remove(1779175845);
    testBtree.remove(52107318);
    testBtree.remove(675891343);
    testBtree.remove(608455363);
    testBtree.remove(1514888112);
    testBtree.remove(1152891831);
    testBtree.remove(2139642574);
    testBtree.remove(1006609540);
    testBtree.remove(393860762);
    testBtree.remove(400151788);
    testBtree.remove(838023412);
    testBtree.remove(792526220);
    testBtree.remove(1073226880);
    testBtree.remove(1461728458);
    testBtree.remove(819516268);
    testBtree.remove(1370738826);
    testBtree.remove(822784415);
    testBtree.remove(158379552);
    testBtree.remove(1046126087);
    testBtree.remove(2132723841);
    EXPECT_EQ(0,testBtree.size());
}

TEST(BtreeTest, TestDegree33){
    Btree<string, 33> testBtree;
    testBtree.add("19932546");
    testBtree.add("27706653");
    testBtree.add("28925691");
    testBtree.add("52107318");
    testBtree.add("57271926");
    testBtree.add("66433441");
    testBtree.add("68362598");
    testBtree.add("77268269");
    testBtree.add("115120654");
    testBtree.add("145532761");
    testBtree.add("158379552");
    testBtree.add("205711490");
    testBtree.add("210367714");
    testBtree.add("247074805");
    testBtree.add("250591794");
    testBtree.add("309696691");
    testBtree.add("393860762");
    testBtree.add("400151788");
    testBtree.add("422527594");
    testBtree.add("428300259");
    testBtree.add("480849991");
    testBtree.add("496586426");
    testBtree.add("496586426");
    testBtree.add("515529753");
    testBtree.add("520932930");
    testBtree.add("525706991");
    testBtree.add("569022154");
    testBtree.add("590294128");
    testBtree.add("608455363");
    testBtree.add("631361083");
    testBtree.add("664835076");
    testBtree.add("675891343");
    testBtree.add("679469414");
    testBtree.add("763654014");
    testBtree.add("764058775");
    testBtree.add("792526220");
    testBtree.add("809673979");
    testBtree.add("810662187");
    testBtree.add("810662187");
    testBtree.add("819516268");
    testBtree.add("822784415");
    testBtree.add("838023412");
    testBtree.add("890459872");
    testBtree.add("892086236");
    testBtree.add("897787792");
    testBtree.add("899316322");
    testBtree.add("926881476");
    testBtree.add("968021766");
    testBtree.add("1002898451");
    testBtree.add("1006609540");
    testBtree.add("1009021007");
    testBtree.add("1028169396");
    testBtree.add("1028169396");
    testBtree.add("1040043610");
    testBtree.add("1046126087");
    testBtree.add("1073226880");
    testBtree.add("1094100450");
    testBtree.add("1152891831");
    testBtree.add("1163120341");
    testBtree.add("1269870926");
    testBtree.add("1290446329");
    testBtree.add("1294600846");
    testBtree.add("1359072203");
    testBtree.add("1370738826");
    testBtree.add("1461728458");
    testBtree.add("1462087311");
    testBtree.add("1500357984");
    testBtree.add("1514888112");
    testBtree.add("1559526673");
    testBtree.add("1559526673");
    testBtree.add("1566369460");
    testBtree.add("1567674295");
    testBtree.add("1579802159");
    testBtree.add("1643550337");
    testBtree.add("1664792818");
    testBtree.add("1669187896");
    testBtree.add("1671889999");
    testBtree.add("1710028745");
    testBtree.add("1719408956");
    testBtree.add("1731106012");
    testBtree.add("1734177661");
    testBtree.add("1741849297");
    testBtree.add("1779175845");
    testBtree.add("1789614810");
    testBtree.add("1789614810");
    testBtree.add("1791277536");
    testBtree.add("1793547003");
    testBtree.add("1797288065");
    testBtree.add("1809249219");
    testBtree.add("1830665860");
    testBtree.add("1840335376");
    testBtree.add("1846443803");
    testBtree.add("1906706780");
    testBtree.add("1950367213");
    testBtree.add("2002830094");
    testBtree.add("2042297871");
    testBtree.add("2055540383");
    testBtree.add("2064010129");
    testBtree.add("2085187937");
    testBtree.add("2091824407");
    testBtree.add("2097549478");
    testBtree.add("2116969294");
    testBtree.add("2132723841");
    testBtree.add("2139642574");
    testBtree.add("2146335337");

    testBtree.remove("2002830094");
    testBtree.remove("763654014");
    testBtree.remove("810662187");
    testBtree.remove("1269870926");
    testBtree.remove("1731106012");
    testBtree.remove("926881476");
    testBtree.remove("897787792");
    testBtree.remove("1009021007");
    testBtree.remove("205711490");
    testBtree.remove("2064010129");
    testBtree.remove("57271926");
    testBtree.remove("19932546");
    testBtree.remove("1290446329");
    testBtree.remove("1163120341");
    testBtree.remove("1906706780");
    testBtree.remove("2055540383");
    testBtree.remove("1840335376");
    testBtree.remove("1789614810");
    testBtree.remove("1579802159");
    testBtree.remove("68362598");
    testBtree.remove("1791277536");
    testBtree.remove("247074805");
    testBtree.remove("664835076");
    testBtree.remove("631361083");
    testBtree.remove("764058775");
    testBtree.remove("145532761");
    testBtree.remove("1950367213");
    testBtree.remove("1664792818");
    testBtree.remove("496586426");
    testBtree.remove("1643550337");
    testBtree.remove("2116969294");
    testBtree.remove("515529753");
    testBtree.remove("496586426");
    testBtree.remove("679469414");
    testBtree.remove("250591794");
    testBtree.remove("1797288065");
    testBtree.remove("2091824407");
    testBtree.remove("890459872");
    testBtree.remove("77268269");
    testBtree.remove("66433441");
    testBtree.remove("1710028745");
    testBtree.remove("1559526673");
    testBtree.remove("520932930");
    testBtree.remove("1809249219");
    testBtree.remove("1462087311");
    testBtree.remove("809673979");
    testBtree.remove("1719408956");
    testBtree.remove("1789614810");
    testBtree.remove("480849991");
    testBtree.remove("1002898451");
    testBtree.remove("1830665860");
    testBtree.remove("1028169396");
    testBtree.remove("115120654");
    testBtree.remove("1500357984");
    testBtree.remove("1567674295");
    testBtree.remove("810662187");
    testBtree.remove("1793547003");
    testBtree.remove("28925691");
    testBtree.remove("2146335337");
    testBtree.remove("2085187937");
    testBtree.remove("1028169396");
    testBtree.remove("1671889999");
    testBtree.remove("210367714");
    testBtree.remove("1294600846");
    testBtree.remove("968021766");
    testBtree.remove("899316322");
    testBtree.remove("1040043610");
    testBtree.remove("309696691");
    testBtree.remove("1734177661");
    testBtree.remove("2042297871");
    testBtree.remove("569022154");
    testBtree.remove("428300259");
    testBtree.remove("892086236");
    testBtree.remove("1094100450");
    testBtree.remove("27706653");
    testBtree.remove("1566369460");
    testBtree.remove("1559526673");
    testBtree.remove("1669187896");
    testBtree.remove("422527594");
    testBtree.remove("2097549478");
    testBtree.remove("590294128");
    testBtree.remove("1359072203");
    testBtree.remove("525706991");
    testBtree.remove("1741849297");
    testBtree.remove("1846443803");
    testBtree.remove("1779175845");
    testBtree.remove("52107318");
    testBtree.remove("675891343");
    testBtree.remove("608455363");
    testBtree.remove("1514888112");
    testBtree.remove("1152891831");
    testBtree.remove("2139642574");
    testBtree.remove("1006609540");
    testBtree.remove("393860762");
    testBtree.remove("400151788");
    testBtree.remove("838023412");
    testBtree.remove("792526220");
    testBtree.remove("1073226880");
    testBtree.remove("1461728458");
    testBtree.remove("819516268");
    testBtree.remove("1370738826");
    testBtree.remove("822784415");
    testBtree.remove("158379552");
    testBtree.remove("1046126087");
    testBtree.remove("2132723841");
    EXPECT_EQ(0,testBtree.size());
}

TEST(BtreeTest, TestDegree33Numbers){
    Btree<int, 33> testBtree;
    for (int i = 0; i < 10000; i++) {
        testBtree.add(i);
    }
    for (int i = 0; i < 10000; i++) {
        testBtree.remove(i);
    }
    EXPECT_EQ(0,testBtree.size());
    for (int i = 0; i < 10000; i++) {
        testBtree.add(i);
    }
    for (int i = 9999; i >= 0; i--) {
        testBtree.remove(i);
    }
    EXPECT_EQ(0,testBtree.size());
}

TEST(BtreeTest, TestDegree33Files){
    Btree<string, 33> testBtree;
    std::ifstream infile("massivedatasource.txt");
    string buf;
    while (infile >> buf) {
        testBtree.add(buf);
    }

    std::ifstream infile2("massivedataremove.txt");
    while (infile2 >> buf) {
        testBtree.remove(buf);

    }
}

