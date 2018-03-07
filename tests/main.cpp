#include "gtest/gtest.h"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*
#include "../include/Container.h"
#include "../upload/Btree.h"
using namespace std;

void testPrinter(const int& element){
    cout << element << " ";
}



int main () {



    Btree<int> testBtree;
    testBtree.add(11);
    testBtree.add(12);
    testBtree.add(15);
    testBtree.add(17);
    testBtree.add(9);
    testBtree.add(6);
    testBtree.add(2);
    cout << endl;
    testBtree.apply(testPrinter, dontcare);
    cout << endl;
    testBtree.apply(testPrinter, ascending);

    testBtree.add(1);
    testBtree.add(2);
    testBtree.add(3);
    testBtree.add(4);
    testBtree.add(5);
    testBtree.add(6);
    testBtree.add(7);
    testBtree.add(8);
    testBtree.add(20);
    testBtree.add(50);
    testBtree.add(102);
    testBtree.add(33);
    testBtree.add(80);
    testBtree.add(1024);
    testBtree.add(1024);
    testBtree.add(500);
    testBtree.add(11056);
    testBtree.add(512);
    testBtree.add(42);
    cout << testBtree.getBiggestElement() << endl;
    cout << testBtree.getSmallestElement() << endl;
    testBtree.apply(testPrinter, descending);
    cout << "\n";
    testBtree.apply(testPrinter, ascending);
    cout << endl << testBtree.getBiggestElement() << endl;
    cout << endl << testBtree.getSmallestElement() << endl;
    testBtree.apply(testPrinter, descending);
    cout << "\n";
    testBtree.apply(testPrinter, ascending);
    cout << "\n";
    testBtree.apply(testPrinter, dontcare);

}
*/
