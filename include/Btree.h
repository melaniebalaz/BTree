//
// What values are really in a tree? Are they keys? And if yes, where is their value?
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

#include "Container.h"
#include "Node.h"
#include "EmptyTreeException.h"

using namespace std;


template <typename E, int Degree = 2>
class Btree : public Container<E> {
private:
    //Keeps track of the rootNode
    Node<E,Degree> *rootNode;
//size_t counter;
    size_t elementsInTree = 0;

    //The smallest element in the tree
    E smallestElement;

    //The biggest element in the tree
    E biggestElement;


public:
    Btree();
    Btree(std::initializer_list<E> el);
    void changeRootNode(Node<E,Degree> *rootPointer);
    virtual std::ostream& print(std::ostream& output) const override;


    //[o] -> Already seems to work from Container.h!
    using Container<E>::add;
    virtual void add(const E element[], size_t sizeOfArray) override;
    //[o] -> Already seems to work from Container.h!
    virtual bool member(const E& e) const override;

    void increaseElementsInTree();
    virtual size_t size() const override;
    void setBiggestElement(E biggestElement);
    E getBiggestElement();
    void setSmallestElement(E smallestElement);
    E getSmallestElement();
    virtual E min() const override;
    virtual E max() const override;

    //Not implemented so far

    virtual bool empty() const override {
        return size() == 0;
    };

    virtual size_t apply(std::function<void(const E&)> f, Order order = dontcare) const override {
        return 10;
    };

    virtual void remove(const E e[], size_t s) override {
        return;
    };

};



//Constructor with no additional input, Calls the constructor with a parameter and hands over the default parameter
//DOESNT WORK!
// Btree() : Btree(defaultNodeDegree){}

//Empty Constructor!
template <typename E, int Degree>
Btree<E,Degree>::Btree() {
    Node<E,Degree> *rootNode = new Node<E,Degree>(Degree, this);
    this->rootNode = rootNode;
}

//Untested!
template <typename E, int Degree>
Btree<E,Degree>::Btree(std::initializer_list<E> el) {
    Node<E,Degree> *rootNode = new Node<E,Degree>(Degree, this);
    this->rootNode = rootNode;
    //first a default NodeDegree Tree is created
    /*
     * Then the elements from the list are added.
     * Yay a- range based loop!
     * This code prints the contents of a initializer list called el, with the variable element taking on the
     * value of each element of the list, in series, until the end of the list is reached.
     *
     * */
    for (auto element: el) {
        this->add(element);
    }
}


/*
 * change the root Node - called by the Node in case of rootNode split
 */
template <typename E, int Degree>
void Btree<E,Degree>::changeRootNode(Node<E,Degree> *rootPointer){
    this->rootNode = rootPointer;
}

/*
 * print method - calls the Node print Method
 */
template <typename E, int Degree>
ostream& Btree<E,Degree>::print(ostream& output) const {

    //call the print method for a Node on the root Node
    rootNode->print(output, 0);
    return output;
}


/*
 * add method
 */
template <typename E, int Degree>
void Btree<E,Degree>::add(const E element[], size_t sizeOfArray) {
    for (int i= 0; i < sizeOfArray;i++ ) {
        rootNode->add(element[i]);
    }
}


/*
 * checks whether an element exists in the tree, returns true or false,
 */
template <typename E, int Degree>
bool Btree<E,Degree>::member(const E& e) const {
    return (rootNode->isMember(e));
}

/*
* Every time this method is called, the elements in the tree are increased by one. This way the tree can keep track
 * of the elements in tree.
*/
template <typename E, int Degree>
void Btree<E,Degree>::increaseElementsInTree() {
    this->elementsInTree++;
}

template <typename E, int Degree>
size_t Btree<E,Degree>::size() const {
    return elementsInTree;
}

/*
 * Biggest element getter and setter
 */
template <typename E, int Degree>
void Btree<E,Degree>::setBiggestElement(E biggestElement) {
    this->biggestElement = biggestElement;
}

template <typename E, int Degree>
E Btree<E,Degree>::getBiggestElement(){
    return biggestElement;
}

/*
 * Smallest element getter and setter
 */

template <typename E, int Degree>
void Btree<E,Degree>::setSmallestElement(E smallestElement){
    this->smallestElement = smallestElement;
}

template <typename E, int Degree>
E Btree<E,Degree>::getSmallestElement(){
    return smallestElement;
}

/*
 * Min and max
 */

template <typename E, int Degree>
E Btree<E,Degree>::min() const{
    if (elementsInTree != 0){
        return smallestElement;
    }
    else throw EmptyTreeException();
}

template <typename E, int Degree>
E Btree<E,Degree>::max() const{
    if (elementsInTree != 0){
        return biggestElement;
    }
    else {
        throw EmptyTreeException();
    }
}

#endif //BTREE_BTREE_H
