#include "Container.h"
#include <signal.h>
//
// EXCEPTION CLASS STARTS HERE
//
#include <vector>
#include <fstream>

using namespace std;


//Exception work this way, that I throw the constructor of an object of the type myException
class EmptyTreeException : public ContainerException {
public:
    const char* what() const throw(){
        return "Tree is empty!";
    }
};

class DuplicateElementException : public ContainerException {
public:
    const char* what() const throw(){
        return "Value already exists!";
    }
};

class ElementNotFoundException : public ContainerException {
public:
    const char* what() const throw(){
        return "Value not found!";
    }
};


template <typename E, int Degree = 2> class Node;


template <typename E, int Degree = 2>
class Btree : public Container<E>{
private:
    //Keeps track of the rootNode
    Node<E,Degree> *rootNode = nullptr;
    //size_t counter;
    size_t elementsInTree = 0;

    //THe Nodes on both sides
    Node<E,Degree> *leftMostNode = nullptr;
    Node<E,Degree> *rightMostNode = nullptr;

    
    //The smallest element in the tree
    E smallestElement;
    
    //The biggest element in the tree
    E biggestElement;


public:

    Btree();
    Btree(std::initializer_list<E> el);
    ~Btree();
    void changeRootNode(Node<E,Degree> *rootPointer);
    virtual std::ostream& print(std::ostream& output) const override;
    
    
    //[o] -> Already seems to work from Container.h!
    using Container<E>::add;
    virtual void add(const E element[], size_t sizeOfArray) override;
    virtual void remove(const E element[], size_t sizeOfArray) override;
    virtual void remove(const E& e) override {
        remove(&e, 1);
    }
    virtual bool member(const E& e) const override;
    
    virtual size_t size() const override;
    void setBiggestElement(E biggestElement);
    E getBiggestElement();
    void setSmallestElement(E smallestElement);
    E getSmallestElement();
    void setLeftMostNode(Node<E,Degree> *leftMostNode);
    void setRightMostNode(Node<E,Degree> *rightMostNode);
    virtual E min() const override;
    virtual E max() const override;


    virtual bool empty() const override {
        return size() == 0;
    };
    
    virtual size_t apply(std::function<void(const E&)> function, Order order = dontcare) const override;

};


//Empty Constructor!
template <typename E, int Degree>
Btree<E,Degree>::Btree() {
    Node<E,Degree> *rootNode = new Node<E,Degree>(Degree, this);
    this->rootNode = rootNode;
}


template <typename E, int Degree>
Btree<E,Degree>::~Btree() {
    rootNode->deleteNodes();
}

/*
 * The Apply Method
 */

template <typename E, int Degree>
size_t Btree<E,Degree>::apply(std::function<void(const E&)> function, Order order) const {
    size_t n = 0;
    if (elementsInTree == 0){
        return n;
    }
    try {
        if (order == ascending){
            leftMostNode->applyAsc(function,n);
        }
        else {
            rightMostNode->applyDesc(function,n);
        }
        //Catches all sorts of exceptions that might be thrown about
    } catch (...){

    };

    return n;
}



/*
 * Setters for the left and right most Nodes
 */
template <typename E, int Degree>
void Btree<E,Degree>::setLeftMostNode(Node<E,Degree> *leftMostNode){
    this->leftMostNode = leftMostNode;
}

template <typename E, int Degree>
void Btree<E,Degree>::setRightMostNode(Node<E,Degree> *rightMostNode){
    this->rightMostNode = rightMostNode;
}

/*
 * The Add Initializer List Method
 */

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
 * add method
 */
template <typename E, int Degree>
void Btree<E,Degree>::add(const E element[], size_t sizeOfArray) {
    for (int i = 0; i < sizeOfArray;i++ ) {
        try {
            //If add throws an Exception, the elementsInTree are not incremented
            rootNode->add(element[i]);
            elementsInTree++;
            //rootNode->sanityCheck(0);
        }
        catch (DuplicateElementException e) {
            //Btree<E,Degree>::actionLog.push_back(LogEntry<E>("DPL", element[i]));
        }
    }
}


/*
 * Removes elements
 */
template <typename E, int Degree>
void Btree<E,Degree>::remove(const E element[], size_t sizeOfArray) {
    if (elementsInTree == 0){
        return;
    }
    for (int i = 0; i < sizeOfArray;i++ ) {
        try {
            rootNode->remove(element[i]);
            elementsInTree--;
            //rootNode->sanityCheck(0);
        } catch (ElementNotFoundException e) {
            //pass
        }
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
    rootNode->print(output, 0);
    return output;
}


/*
 * checks whether an element exists in the tree, returns true or false,
 */
template <typename E, int Degree>
bool Btree<E,Degree>::member(const E& e) const {
    return (rootNode->isMember(e));
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




//
// NODE CLASS STARTS HERE
//


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
    Node<E,Degree> *leftSideNode = nullptr;
    Node<E,Degree> *rightSideNode = nullptr;
    
    void promoteElement(E element, Node<E,Degree> *rightNode);
    void insertElement(E element, int insertionIndex);
    void deleteElement(const E& element);
    void executeMerge();
    void leafMerge();
    void mergeLeafLeft(int thisPointerIndex);
    void mergeLeafRight(int thisPointerIndex);
    void mergeIndexRight(int thisPointerIndex);
    void mergeIndexLeft(int thisPointerIndex);
    void indexMerge();
    void safeDelete();

public:
    Node(int degree, Btree<E,Degree> *owningTree);
    ~Node();
    void add(const E& element);
    void remove(const E& element);
    void split();
    bool isMember(const E& element);
    ostream& print(ostream& output, int indentation);
    void applyAsc(std::function<void(const E&)> function, size_t& n);
    void applyDesc(std::function<void(const E&)> function, size_t& n);
    void deleteNodes();

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
    this->elements = new E[maxElements+2];
    
    //A Node can have the amount of maxElements + 2 extra subNodes for shifting
    this->subNodes = new Node<E,Degree>*[maxElements+3];
    for (int i=0; i < maxElements+3; i++ ){
        this->subNodes[i] = nullptr;
    }
}


template <typename E, int Degree >
Node<E,Degree>::~Node(){
    delete[] elements;
    for (int i= 0; i < maxElements+3; i++){
        if (subNodes[i]!= nullptr){
            subNodes[i] = nullptr;
        }
    }

    //delete[] subNodes;
}

template <typename E, int Degree >
void Node<E,Degree>::deleteNodes(){
    //cout << "deleteNodes" << endl;
    for (int i = 0; i < maxElements+3; i++){
        if (subNodes[i] != nullptr){
            subNodes[i]->deleteNodes();
        }
    }

    delete this;

    for (int i = 0; i < maxElements+3; i++){
        delete subNodes[i];
    }

    delete[] subNodes;
}

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
            //as well as the left most node and the right most Node set
            owningTree->setSmallestElement(element);
            owningTree->setLeftMostNode(this);
            owningTree->setBiggestElement(element);
            owningTree->setRightMostNode(this);
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
                    throw DuplicateElementException();
                }
                else if (element > elements[i]){
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
            /*
             * Check whether the elements in the Node are more than they should be, if yes the Node needs to be split.
             * It is easier to split if the one element too many is already in the Node.
             */
            if (usedElements > maxElements) {
                split(); //split and redistribute
            }
        }
        
    }
    
    /*
     * Recursively look for a leaf, where the value can be inserted
     */
    else {
        //If the value is greater (or equal - could be) then the biggest value in this Node, go right
        if (element > elements[usedElements-1] || element == elements[usedElements-1] ){
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
    Node<E,Degree> *rightNode = new Node<E,Degree>(this->degree, owningTree);


    rightNode->parentNode = this->parentNode;


    /*
     * Copy half the elements into the new Node (Everything what is bigger than the half goes right) -> CAREFUL: Will
     * depend on whether the degree of the Tree is a even or uneven number. This will leave a greater number of elements
     * in the this-Node than in the right Node. Also shoving the pointers over
     */
    int j = 0;
    for (int i = (maxElements/2)+1; i < this->usedElements; i++){
        rightNode->elements[j] = this->elements[i];
        rightNode->usedElements++;
        j++;
    }

    j = 0;
    for (int k = (maxElements/2)+1; k <= this->usedElements; k++){
        rightNode->subNodes[j] = this->subNodes[k];
        if (rightNode->subNodes[j] != nullptr) {
            rightNode->subNodes[j]->parentNode = rightNode;
        }

        this->subNodes[k] = nullptr;
        /*
        if (k > (maxElements/2)+1) {
            this->subNodes[k] = nullptr;
        }
         */
        j++;
    }


    
    //Subtract the amount of elements from this Node that are copied into the other Node
    this->usedElements = this->usedElements - rightNode->usedElements;
    

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
void Node<E,Degree>::promoteElement(E element, Node<E,Degree> *rightNode) {
    
    /*
     * This method must handle three cases:
     * 1.  ROOT NODE : There is no parentNode to insert the value to, because it is the root. Make a new parentroot
     */
    
    if (this->parentNode == nullptr) {
        

        //Create a new RootNode
        Node<E,Degree> *rootNode = new Node(this->degree, owningTree);
        //Insert the promoted element£
        rootNode->elements[0] = element;
        

        rootNode->usedElements++;
        
        //Set the pointers straight
        rootNode->subNodes[0] = this;
        

        rootNode->subNodes[1] = rightNode;
        
        this->parentNode = rootNode;
        
        rightNode->parentNode = rootNode;


        this->rightSideNode = rightNode;
        rightNode->leftSideNode = this;


        //Now the root Node has changed, so let the Tree know
        
        owningTree->changeRootNode(rootNode);

        //If its a root which has no children and splits for the first time
        if (this->subNodes[0] == nullptr){
            //The most left and the most right Nodes are set anew
            //as well as the direct neighbors
            owningTree->setLeftMostNode(this);
            owningTree->setRightMostNode(rightNode);
        }
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
    for (int i = 0; i <= parentNode->usedElements; i++) {
        if (parentNode->subNodes[i] == this) {
            promotePointerIndex = i;
            break;
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
    rightNode->leftSideNode = this;
    if (this->rightSideNode != nullptr) {
        this->rightSideNode->leftSideNode = rightNode;
        rightNode->rightSideNode = this->rightSideNode;
    }
    this->rightSideNode = rightNode;

    /*
     *
     */
    if (owningTree->getSmallestElement() == this->elements[0]){
        owningTree->setLeftMostNode(this);
    }
    else if (owningTree->getBiggestElement() == rightNode->elements[rightNode->usedElements-1]){
        owningTree->setRightMostNode(rightNode);
    }

    /*
     * Check whether the elements in the parent Node are more than they should be, if yes the Node needs to be split.
     * It is easier to split if the one element too many is already in the Node.
     */
    if (this->parentNode->usedElements > this->parentNode->maxElements) {
        
        this->parentNode->split(); //split and redistribute
    }
}

/*
 * REMOVE ELEMENT METHOD
 *
 * WIKI:
 *     If L has fewer entries than it should,
 *      If sibling (adjacent node with same parent as L) is more than half-full, re-distribute, borrowing an entry from it.
 *        Otherwise, sibling is exactly half-full, so we can merge L and sibling.
 *
 *  If merge occurred, must delete entry (pointing to L or sibling) from parent of L.
 */
template <typename E, int Degree >
void Node<E,Degree>::remove(const E& element) {

    if (subNodes[0] == nullptr){

        deleteElement(element);
        if (usedElements == 0){
            return;
        }
        //If the biggest element has just been deleted, set it again new with the element that was on it´s left
        if (owningTree->getBiggestElement() == element){
            owningTree->setBiggestElement(this->elements[usedElements-1]);
        }
        else if (owningTree->getSmallestElement() == element){
            owningTree->setSmallestElement(this->elements[0]);
        }

        /*
         * Check whether there is the need for merging (if its a root there is no need)
         */

        if (usedElements < minElements && parentNode != nullptr){
            this->executeMerge();
        }
    }
    else if (element > elements[usedElements-1] || element == elements[usedElements-1]){
        subNodes[usedElements]->remove(element);
    }

    else {
        for (int i = 0; i < usedElements; i++){
            if (elements[i] > element){
                subNodes[i]->remove(element);
                //Break out of the recursion!
                break;
            }
        }
    }
}

/*
 * All this method does is be called on a Node in which it should delete an element
 */
template <typename E, int Degree >
void Node<E,Degree>::deleteElement(const E& element){
    int removeIndex = -1;
    for (int i=0; i < usedElements; i++){
        if (elements[i] == element){
            removeIndex = i;
            break;
        }
    }
    if (removeIndex == -1) {
        throw ElementNotFoundException();
    }

    for (int j = removeIndex; j < usedElements; j++){
        elements[j] = elements[j+1];
        //Move the pointers as well in case something gets deleted in not a leaf
        subNodes[j+1] = subNodes[j+2];
    }
    usedElements--;
    for (int k = usedElements+1; k < maxElements+3; k++){
        this->subNodes[k] = nullptr;
    }
}

/*
 * ALL THE MERGE LOGIC METHODS
 */
template <typename E, int Degree >
void Node<E,Degree>::executeMerge(){
    if (this->subNodes[0] == nullptr){
        leafMerge();
    }
    else {
        indexMerge();
    }
}

template <typename E, int Degree >
void Node<E,Degree>::leafMerge(){
    int thisPointerIndex = -1;
    for (int i = 0; i <= parentNode->usedElements; i++){
        if (parentNode->subNodes[i] == this){
            thisPointerIndex = i;
        }
    }

    if (thisPointerIndex == -1){
        throw "This node has not been found";
    }
    //merge left preference
    if (thisPointerIndex == 0){
        mergeLeafRight(thisPointerIndex);

    }
    else if (parentNode->subNodes[thisPointerIndex-1] != nullptr) {
        mergeLeafLeft(thisPointerIndex);
    }
}


template <typename E, int Degree >
void Node<E,Degree>::mergeLeafLeft(int thisPointerIndex){

    Node<E,Degree>* leftNode = parentNode->subNodes[thisPointerIndex-1];

    if (leftNode->usedElements <= leftNode->maxElements/2){

        for (int i = 0; i < this->usedElements; i++){
            leftNode->elements[leftNode->usedElements] = this->elements[i];
            leftNode->usedElements++;
        }
        this->usedElements = 0;
        if (this->rightSideNode != nullptr){
            leftNode->rightSideNode = this->rightSideNode;
            leftNode->rightSideNode->leftSideNode = leftNode;
        }
        else {
            leftNode->rightSideNode = nullptr;
        }

        this->leftSideNode = nullptr;
        this->rightSideNode = nullptr;

        this->parentNode->deleteElement(this->parentNode->elements[thisPointerIndex-1]);

        //get biggest element replacement here

        if (leftNode->owningTree->getBiggestElement() == leftNode->elements[leftNode->usedElements-1]){
            leftNode->owningTree->setRightMostNode(leftNode);
        }

        if (leftNode->parentNode->usedElements == 0){
            leftNode->owningTree->changeRootNode(leftNode);
            leftNode->owningTree->setRightMostNode(leftNode);
            leftNode->owningTree->setLeftMostNode(leftNode);
            auto originalLeftParentNode = leftNode->parentNode;
            leftNode->parentNode = nullptr;
            originalLeftParentNode->subNodes[0] = nullptr;
            originalLeftParentNode->safeDelete();
            this->safeDelete();
            return;
        }

        this->safeDelete();

        if (leftNode->parentNode != nullptr && leftNode->parentNode->parentNode != nullptr && leftNode->parentNode->usedElements < leftNode->minElements){
            leftNode->parentNode->executeMerge();
        }
        return;
    }

    else if (leftNode->usedElements > leftNode->maxElements/2){
//Add the biggest element from the left Node to the this Node
        //Add the smallest element from the right Node to the this Node
        this->insertElement(leftNode->elements[leftNode->usedElements-1], 0);
        //Remove this element from the right Node
        leftNode->deleteElement(leftNode->elements[leftNode->usedElements-1]);
        //Set the index Key in the parent Node correctly
        parentNode->elements[thisPointerIndex-1] = this->elements[0];
        return;
    }
}


template <typename E, int Degree >
void Node<E,Degree>::mergeLeafRight(int thisPointerIndex){

    Node<E,Degree>* rightNode = parentNode->subNodes[thisPointerIndex+1];

    if (rightNode->usedElements <= rightNode->maxElements/2){

        for (int i = 0; i < rightNode->usedElements; i++){
            this->elements[this->usedElements] = rightNode->elements[i];
            this->usedElements++;
        }
        rightNode->usedElements = 0;

        if (rightNode->rightSideNode != nullptr){
            this->rightSideNode = rightNode->rightSideNode;
            this->rightSideNode->leftSideNode = this;
        }
        else {
            this->rightSideNode = nullptr;
        }

        this->parentNode->deleteElement(this->parentNode->elements[thisPointerIndex]);

        //get biggest element replacement here

        if (this->parentNode->usedElements == 0){
            this->owningTree->changeRootNode(this);
            this->owningTree->setRightMostNode(this);
            this->owningTree->setLeftMostNode(this);
            auto originalParentNode = this->parentNode;
            this->parentNode = nullptr;
            originalParentNode->subNodes[0] = nullptr;
            originalParentNode->safeDelete();
            rightNode->safeDelete();
            return;
        }
        rightNode->safeDelete();

        if (this->parentNode != nullptr && this->parentNode->parentNode != nullptr && this->parentNode->usedElements < this->minElements){
            this->parentNode->executeMerge();
        }
    }

        //REDISTRIBUTE
    else if (rightNode->usedElements > maxElements/2){
        //Add the smallest element from the right Node to the this Node
        this->insertElement(rightNode->elements[0], this->usedElements);
        //Remove this element from the right Node
        rightNode->deleteElement(rightNode->elements[0]);
        //Set the index Key in the parent Node correctly
        parentNode->elements[thisPointerIndex] = rightNode->elements[0];
        return;
    }
}

template <typename E, int Degree >
void Node<E,Degree>::indexMerge(){
    int thisPointerIndex = -1;
    for (int i = 0; i <= parentNode->usedElements; i++){
        if (parentNode->subNodes[i] == this){
            thisPointerIndex = i;
        }
    }

    if(thisPointerIndex == -1 ) {
        throw "This node has not been found";
    }

    //merge left preference
    if (thisPointerIndex == 0){
        mergeIndexRight(thisPointerIndex);

    }
    else if (parentNode->subNodes[thisPointerIndex-1] != nullptr) {
        mergeIndexLeft(thisPointerIndex);
    }
}


template <typename E, int Degree >
void Node<E,Degree>::mergeIndexRight(int thisPointerIndex){
    //most left Node -> merge right into this
    Node<E,Degree>* rightNode = parentNode->subNodes[thisPointerIndex+1];

    if (rightNode->usedElements <= rightNode->maxElements/2){

        //pulldown
        this->insertElement(this->parentNode->elements[thisPointerIndex], this->usedElements);

        int elementsLeftToMerge = rightNode->usedElements;
        int nodesLeftToMerge = rightNode->usedElements +1;
        for (int i = 0; i <= rightNode->usedElements; i++){
            this->subNodes[usedElements] = rightNode->subNodes[i];
            rightNode->subNodes[i] = nullptr;
            nodesLeftToMerge--;
            if (elementsLeftToMerge != 0){
                this->elements[this->usedElements] = rightNode->elements[i];
                this->usedElements++;
                elementsLeftToMerge--;
            }
        }
        rightNode->usedElements = 0;

        if (rightNode->rightSideNode != nullptr){
            this->rightSideNode = rightNode->rightSideNode;
            this->rightSideNode->leftSideNode = this;
        }
        else {
            this->rightSideNode = nullptr;
        }

        rightNode->leftSideNode = nullptr;
        rightNode->rightSideNode = nullptr;

        for (int i = 0; i <= this->usedElements; i++){
            this->subNodes[i]->parentNode = this;
        }


        this->parentNode->deleteElement(this->parentNode->elements[thisPointerIndex]);

        if (this->parentNode->usedElements == 0 && this->parentNode->parentNode == nullptr){
            auto originalParentNode = parentNode;
            this->parentNode = nullptr;
            originalParentNode->subNodes[0] = nullptr;
            originalParentNode->safeDelete();
            this->owningTree->changeRootNode(this);
            rightNode->safeDelete();
            return;
        }

        rightNode->safeDelete();


        if (this->parentNode != nullptr && this->parentNode->parentNode != nullptr && this->parentNode->usedElements < this->minElements){
            this->parentNode->executeMerge();
        }
    }

    else if (rightNode->usedElements > maxElements/2){
        this->elements[this->usedElements] = rightNode->parentNode->elements[thisPointerIndex];
        this->usedElements++;
        this->subNodes[this->usedElements] = rightNode->subNodes[0];
        if (this->subNodes[this->usedElements] != nullptr) {
            this->subNodes[this->usedElements]->parentNode = this;
            rightNode->subNodes[0] = nullptr;
        }
        rightNode->parentNode->elements[thisPointerIndex] = rightNode->elements[0];
        for (int i = 0; i < rightNode->usedElements - 1; i++) {
            rightNode->elements[i] = rightNode->elements[i+1];
        }
        for (int i = 0; i < rightNode->usedElements; i++) {
            rightNode->subNodes[i] = rightNode->subNodes[i+1];
        }
        rightNode->usedElements--;
    }
}

template <typename E, int Degree >
void Node<E,Degree>::mergeIndexLeft(int thisPointerIndex){
    Node<E,Degree>* leftNode = parentNode->subNodes[thisPointerIndex-1];

    if (leftNode->usedElements <= leftNode->maxElements/2) {
        leftNode->insertElement(leftNode->parentNode->elements[thisPointerIndex - 1], leftNode->usedElements);

        int elementsLeftToMerge = this->usedElements;
        int nodesLeftToMerge = this->usedElements + 1;
        for (int i = 0; i <= this->usedElements; i++) {
            leftNode->subNodes[leftNode->usedElements] = this->subNodes[i];
            this->subNodes[i] = nullptr;
            nodesLeftToMerge--;
            if (elementsLeftToMerge != 0) {
                leftNode->elements[leftNode->usedElements] = this->elements[i];
                leftNode->usedElements++;
                elementsLeftToMerge--;
            }
        }
        this->usedElements = 0;

        if (this->rightSideNode != nullptr) {
            leftNode->rightSideNode = this->rightSideNode;
            leftNode->rightSideNode->leftSideNode = leftNode;
        }
        else {
            leftNode->rightSideNode = nullptr;
        }

        for (int i = 0; i <= leftNode->usedElements; i++) {
            leftNode->subNodes[i]->parentNode = leftNode;
        }

        //RightSideNode Left Node Logic still missing

        leftNode->parentNode->deleteElement(leftNode->parentNode->elements[thisPointerIndex - 1]);

        if (leftNode->parentNode->usedElements == 0 && this->parentNode->parentNode == nullptr) {
            auto originalParentNode = parentNode;
            leftNode->parentNode = nullptr;
            originalParentNode->subNodes[0] = nullptr;
            originalParentNode->safeDelete();
            leftNode->owningTree->changeRootNode(leftNode);
            this->safeDelete();
            return;
        }

        this->safeDelete();

        if (leftNode->parentNode != nullptr && leftNode->parentNode->parentNode != nullptr &&
            leftNode->parentNode->usedElements < leftNode->minElements) {
            leftNode->parentNode->executeMerge();
        }
    }

    else if (leftNode->usedElements > leftNode->maxElements/2){

        for (int i = this->usedElements; i > 0; i--) {
            this->elements[i] = this->elements[i-1];
        }
        for (int i = this->usedElements+1; i > 0; i--){
            this->subNodes[i] = this->subNodes[i-1];
        }
        this->elements[0] = this->parentNode->elements[thisPointerIndex-1];
        this->usedElements++;
        this->subNodes[0] = leftNode->subNodes[leftNode->usedElements];
        if (this->subNodes[0] != nullptr) {
            this->subNodes[0]->parentNode = this;
        }
        this->parentNode->elements[thisPointerIndex-1] = leftNode->elements[leftNode->usedElements-1];
        leftNode->subNodes[leftNode->usedElements] = nullptr;
        leftNode->usedElements--;
    }
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
     * Insert the new Element in the Insertion place found above, increase the usedElements in this Node
     * and tell the tree there is one more element in the tree
     */
    elements[insertionIndex] = element;
    usedElements++;

    for (int k = usedElements+1; k < maxElements+3; k++){
        this->subNodes[k] = nullptr;
    }

    //If the variables already have been set, just do a comparison between what is set and what is being newly added
    if (owningTree->getSmallestElement() > element ) {
        owningTree->setSmallestElement(element);
    }
    else if (element > owningTree->getBiggestElement()) {
        owningTree->setBiggestElement(element);
    };
}

template <typename E, int Degree >
void Node<E,Degree>::applyAsc(std::function<void(const E&)> function, size_t& n){
    //passes all the elements of one Node to the function
    for (int i=0; i < usedElements; i++){
        function(elements[i]);
        ++n;
    }
    //recursively calls itself until the pointer on the left side points to null
    while (this->rightSideNode!= nullptr){
        this->rightSideNode->applyAsc(function,n);
        return;
    }
}

template <typename E, int Degree >
void Node<E,Degree>::applyDesc(std::function<void(const E&)> function, size_t& n){
    //passes all the elements of one Node to the function
    for (int i=usedElements-1; i >= 0; i--){
        function(elements[i]);
        ++n;
    }
    //recursively calls itself until the pointer on the right side points to null
    while (this->leftSideNode!= nullptr){
        this->leftSideNode->applyDesc(function,n);
        return;
    }
}


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
        for (int i = 0; i < usedElements; i++){
            if (elements[i] > element){
                return subNodes[i]->isMember(element);
            }
        }
        return subNodes[usedElements]->isMember(element);
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
}


template <typename E, int Degree >
void Node<E,Degree>::safeDelete() {
    if (parentNode != nullptr) {
        for (int i = 0; i < parentNode->usedElements + 1; i++) {
            if (parentNode->subNodes[i] == this) {
                cout << "Tried to delete non-unlinked element, parentNode still has element!";
                throw "Tried to delete non-unlinked element!";
            }
        }
    }
    if (leftSideNode != nullptr && leftSideNode->rightSideNode == this) {
        cout << "Tried to delete non-unlinked element, the leftSideNode right Side Node points to this!";
        throw "Tried to delete non-unlinked element!";
    }
    if (rightSideNode != nullptr && rightSideNode->leftSideNode == this) {
        cout << "Tried to delete non-unlinked element, the rightside Node left Side Node points to this!";
        throw "Tried to delete non-unlinked element!";
    }
    for (int i = 0; i < usedElements + 1; i++) {
        if (subNodes[i] != nullptr) {
            if (subNodes[i]->parentNode == this) {
                cout << "Tried to delete non-unlinked element, we still have subNodes pointing to this!";
                throw "Tried to delete non-unlinked element!";
            }
        }
    }
    delete this;

    for (int i = 0; i < maxElements+3; i++){
        delete subNodes[i];
    }

    delete[] subNodes;
}



//
// UNIT TESTS ARE HERE
//

/*

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

TEST(BtreeTest, TesApplyAsc){
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
};

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


*/