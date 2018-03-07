//
// Created by Melanie Balaz on 14.05.16.
//

#ifndef BTREE_EMPTYTREEEXCEPTION_H
#define BTREE_EMPTYTREEEXCEPTION_H


//Exception work this way, that I throw the constructor of an object of the type myException
class EmptyTreeException : public ContainerException {
public:
    const char* what() const throw(){
        return "Tree is empty!";
    }
};


#endif //BTREE_EMPTYTREEEXCEPTION_H
