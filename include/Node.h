//
// Created by Melanie Balaz on 30.04.16.
//

#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include "Container.h"
template <typename E, int Degree> class Btree;
using namespace std;


/*
 * When not a leaf Node is split, distribute the values unto two Nodes and then copy the smallest value from the right Node, up
 * into the higher Node
 *
*/

template <typename E, int Degree>
class Node {
private:
    //The degree of each Node
    int degree;

    /*
     * A Node can have at most maxElements = 2d Elements, if there are more, split
     */
    int maxElements;

    /*
     * A Node must have at least minElements = degree Elements, if there are less, merge
     */
    int minElements;

    //Pointers to the elements which are stored in each Node (The actual values, or keys,..)
    E *elements;

    /*
     * Counts how many elements there are in each Node (from the available maxElements)
    */
    int usedElements = 0;


    Btree<E,Degree> *owningTree;

    /*
     * A pointer to pointers, pointing to Nodes -
     * so that in the constructor the memory is not actually allocated for degree subNodes, but just for the
     * pointers that could potentially point to the Nodes, when they are actually needed (no unecessary waste of memory)
     * */
    Node<E,Degree> **subNodes = nullptr;
    Node<E,Degree> *parentNode = nullptr;

    void promoteElement(E element, Node *rightNode);
    void insertElement(E element, int insertionIndex);

public:
    Node(int degree, Btree<E,Degree> *owningTree);
    void add(const E& element);
    void split();
    bool isMember(const E& element);
    ostream& print(ostream& output, int indentation);

};


//Constructor
template <typename E, int Degree >
Node<E,Degree>::Node(int degree, Btree<E,Degree> *owningTree){
    this->degree = degree;
    this->maxElements = 2*degree;
    this->minElements = degree;
    this->owningTree = owningTree;

    /*
     * A node can at maximum have the amount of 2*degree elements, but the pointer to 1 extra element can be kept for adding
     * an element before a split
    */
    this->elements = new E[maxElements+1];

    //A Node can have the amount of maxElements + 2 extra subNodes for shifting
    this->subNodes = new Node<E,Degree>*[maxElements+2];
    for (int i=0; i < maxElements+2; i++ ){
        this->subNodes[i] = nullptr;
    }
}

/*
 * I will need a destructor to clean up all the dynamically allocated Nodes
 */


/*
 *
 * ADD METHOD
 */
template <typename E, int Degree >
void Node<E,Degree>::add(const E& element) {

    /*
     * If the Node is a leaf Node (has no children), the element can be inserted. Only insert Elements into leaf Nodes!
     */
    if (this->subNodes[0] == nullptr){

    /*
     * If the Node is completely empty which only happens in the case of the very first element
     * being inserted into the tree into the rootNode, the element is added to the spot with index 0
     */
        if (usedElements == 0 && this->parentNode == nullptr){
            this->elements[0] = element;
            usedElements ++;

            //Since it is the first element in the tree, the biggest and smallest variables need to be initialized
            owningTree->setSmallestElement(element);
            owningTree->setBiggestElement(element);
            owningTree->increaseElementsInTree();
            return;
        }
        else {

            int insertionIndex = 0;
            //loop over all the documented elements within a Node to find the place to put the new Element
            for (int i=0;i < usedElements ; i++){
                /*
                 * Find the place where the new element should go, duplicates just get ignored
                */
                if (element == elements[i]){
                    return;
                }
                if (element > elements[i]){
                    insertionIndex = i+1;
                }
                else {
                    /*
                     * Once the right place has been found (can´ be moved anymore to the right), break out of the for loop
                    */
                    break;
                }
            }
            //Call the method for actually inserting the element and splitting if necessary
            insertElement(element, insertionIndex);
        }

    }

    /*
     * Recursively look for a leaf, where the value can be inserted
     */
    else {
        //If the value is greater then the biggest value in this Node, go right
        if (element > elements[usedElements-1]){
            subNodes[usedElements]->add(element);
        }

        else {
            for (int i = 0; i < usedElements; i++){
                if (elements[i] > element){
                    subNodes[i]->add(element);
                    //Break out of the recursion!
                    break;
                }
            }
        }

    }
}

/*
 * The Split Method
 */
template <typename E, int Degree >
void Node<E,Degree>::split(){


    /*
     *
     * WHEN A SPLIT HAPPENS...
     * TWO CASES:
     */


    //Allocate only one new Node, which in both cases will be the right Node
    Node<E,Degree> *rightNode = new Node(this->degree, owningTree);

    /*
     * Copy half the elements into the new Node (Everything what is bigger than the half goes right) -> CAREFUL: Will
     * depend on whether the degree of the Tree is a even or uneven number. This will leave a greater number of elements
     * in the this-Node than in the right Node.
    */
    int j = 0;
    int i = (maxElements/2)+1;
    for ( i ; i < this->usedElements; i++){
        rightNode->elements[j] = this->elements[i];
        j++;
        rightNode->usedElements++;
    }

    //Subtract the amount of elements from this Node that are copied into the other Node
    this-> usedElements = this-> usedElements-j;

    /*
     *
     * 1st CASE: A ROOT/INDEX NODE IS SPLITTING: (The value only needs to be moved up and not copied)
     */

    //AN Index Node (One that has children) is splitting -> NO INDEX COPYING
    if (subNodes[0] != nullptr){

        /*
         * Pass the value which needs to be moved up to be promoted. The value in question is the one that sits exactly in the middle.
         * Again: Differenciate between even or uneven degree.
         */
        promoteElement(this->elements[maxElements/2],rightNode);
        //After the element has been moved up, it can be "removed" from the original Node, by simply subtracting from the usedElements
        this->usedElements--;

    }
        /*
        * 2nd CASE: A LEAF NODE OR A ROOT NODE with no children IS SPLITTING..
        */
    else {
        /*
         * Pass the Value that needs to be copied into its parent, which is the smallest value in the rightNode and
         * pass the right Node so it can be linked to the parentNode as well.
         * After copying the value into the parents, the left and right pointers of this value need to be set to this and rightNode
        */
        promoteElement(rightNode->elements[0],rightNode);
    }
}


/*
     * PROMOTE METHOD:
     * This method has the task to promote an element after a split and integrate it into its parentNode.
     * This works by taking the Node with the element in question and all its SubNodes and integrating this element into the
     * parentNode, and removing the pointer which pointed to the Node where it was originally stored (Keeping all the subNode pointers)
     */
template <typename E, int Degree >
void Node<E,Degree>::promoteElement(E element, Node *rightNode) {

    /*
     * This method must handle three cases:
     * 1.  ROOT NODE : There is no parentNode to insert the value to, because it is the root. Make a new parentroot
     */

    if (this->parentNode == nullptr) {

        //Create a new RootNode
        Node<E,Degree> *rootNode = new Node(this->degree, owningTree);
        //Insert the promoted element (A copy)
        rootNode->elements[0] = element;
        rootNode->usedElements++;
        //Set the pointers straight
        rootNode->subNodes[0] = this;
        rootNode->subNodes[1] = rightNode;
        this->parentNode = rootNode;
        rightNode->parentNode = rootNode;

        //Now the root Node has changed, so let the Tree know

        owningTree->changeRootNode(rootNode);
        return;

    }

    /*
     * Case 2 and 3 have the same procedure:
     * The element needs to be inserted into their ParentNode at a certain index and the pointers need to point
     * to this and the rightNode
     * After returning in the case of an Index Node in comparison to a leaf Node, the value will be deleted from where it was promoted.
     */

    int promotePointerIndex = 0;

    //look for the pointer to our this Node, right of which our value will need to be inserted
    for (int i = 0; i <= usedElements; i++) {
        if (parentNode->subNodes[i] == this) {
            promotePointerIndex = i;
        }
    }

    //Call the insert Element method with the chosen index from above and pass it the element from our Node.
    this->parentNode->insertElement(element, promotePointerIndex);

    /*
     * Once we inserted the element in the correct place, we need to to correctly place the pointers.
     * The correct pointer is still pointing towards our this Node, but the pointer on the right side of it, needs to
     * point to the right Node. And our right Node needs a parentNode!
    */
    this->parentNode->subNodes[promotePointerIndex + 1] = rightNode;
    rightNode->parentNode = this->parentNode;
}



/*
* INSERT ELEMENT METHOD
*/
template <typename E, int Degree >
void Node<E,Degree>::insertElement(E element, int insertionIndex) {
    /*
            * Loop over the (used) elements from the back and shift them to the right until the spot for the new element is cleared.
            */
    for (int i = usedElements; i > insertionIndex; i--) {
        elements[i] = elements[i - 1];
        subNodes[i + 1] = subNodes[i];
    }

    /*
     * Insert the new Element in the Insertion place found above, increase the usedElements in this Node.
     */
    elements[insertionIndex] = element;
    usedElements++;

    //If the variables already have been set, just do a comparison between what is set and what is being newly added
    if (element < owningTree->getSmallestElement()) {
        owningTree->setSmallestElement(element);
    }
    else if (element > owningTree->getBiggestElement()) {
        owningTree->setBiggestElement(element);
    };

    /*
    * Check whether the elements in the Node are more than they should be, if yes the Node needs to be split.
    * It is easier to split if the one element too many is already in the Node.
   */
    if (usedElements > maxElements) {
        split(); //split and redistribute
    }
}


/*
 * The root of a B+ Tree represents the whole range of values in the tree, where every internal node is a subinterval.
 *  We are looking for a value k in the B+ Tree.
 *  Starting from the root, we are looking for the leaf which may contain the value k.
 *  At each node, we figure out which internal pointer we should follow.
 *  An internal B+ Tree node has at most d ≤ b children,
 *  where every one of them represents a different sub-interval.
 *  We select the corresponding node by searching on the key values of the node.
 *
 */
template <typename E, int Degree >
bool Node<E,Degree>::isMember(const E& element){

    /*
    * The values are stored in a leaf
    */
    if (this->subNodes[0] == nullptr){

        //loop over all the documented elements within a Node to find the element
        for (int i=0;i < usedElements ; i++){
            if (element == elements[i]){
                return true;
            }
        }
        return false;
    }
        /*
         * Recursively look for a leaf, where the value could be
         */
    else {
        //If the value is greater then the biggest value in this Node, go right
        if (element > elements[usedElements-1]){
            return subNodes[usedElements]->isMember(element);
        }

        else {
            for (int i = 0; i < usedElements; i++){
                if (elements[i] > element){
                    return subNodes[i]->isMember(element);
                    //Break out of the recursion!
                    break;
                }
            }
        }

    }
}

/*
 * The print method
 */
template <typename E, int Degree >
ostream& Node<E,Degree>::print(ostream& output, int indentation) {


        /*
         * Loop over all the SubNodes left and right of the usedElements. Keep in mind: The last SubNode
         * on the right is not included in this for loop (because it only goes so far as the used elements on the first level
         */
        for (int i = 0; i<usedElements; i++){

            /*
             * If a subNode exists, follow it down to its depths recursively,
             * for each level going deeper add indentation
             */
            if (this->subNodes[i] != nullptr){
                this->subNodes[i]->print(output,indentation+1);
                /*
                 * After the deepest point has been reached this if Block will not be entered anymore - instead the
                 * printing out below will start. Once that is done the return statement brings us back to exactly this point here.
                 */
            }


            /*
             * Print out the stuff on the screen
             */
            for (int j = 0; j<indentation; j++){
                output << " ";
            }
            output << this->elements[i];
            output << "\n";
        }

        /*
         * This part here is for the last SubNode on the right.
         */
    if (this->subNodes[usedElements] != nullptr){
        this->subNodes[usedElements]->print(output,indentation+1);
    }

    return output;
};


#endif //BTREE_NODE_H
