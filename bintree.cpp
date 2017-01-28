#include "bintree.h"
// :g/.\{81,\}/p
/*
 //|===========================================================================|
 //|                                                                           |
 //|  Assignment2 Binary Search Tree                                           |
 //|                                                                           |
 //|  Created by Danny Ly on 1/15/17.                                          |
 //|  Copyright © 2017 Red Klouds. All rights reserved.                        |
 //|===========================================================================|
 
 //============================================================================|
 
 Program_Description:
 --File Name: bintree.h
 -- A program demonstrating the understanding of implmenting a Binary Search 
 	Tree This program also shows understanding of pointers, memory leaks, and 
	object references.
 
 The Running time for Program, for:
 	-- Searching: O(long(n))
 	-- inserting: O(log(n))
 	--	Reconstructing from array/binary tree: O(n)

	-> Abstract:
		This program is implemented using the NodeData class, each node within
		the tree structure is a tree node which contains a NodeData pointer.
 
 Program_Features:
 -- Defaults constructor of 1 parameter.
 -- Copy Constructor,initalizes this with a deep copy of rhs.
 -- operator=, 		assignment operator copyies(deep-copy) RHS to THIS.
 -- operator==, 	checks wether the two objects are the same.
 -- operator!=, 	check wether the two object are not the same.
 -- operator>>, 	output the current object in order traversal.
 -- insert, 		Inserts a NodeData pointer into the binary tree.
 -- isEmpty, 		checks if the Object is empty.
 --	retrieve,		searchs for specific NodeData target.
 -- bstreeToArray,	turns binary tree into an array.
 --	arrayToBstree,	turns array into binary tree.
 -- makeEmpty,		makes the object empty, deallocates all nodes
 -- displaysSideways,	displays the tree repersentation side ways.
 --	getHeight,		return the most-depth of a given NodeData.
 
 Assumptions:
 -- iostream library's are visable and included packages for
 output functionalities.
 -- NodeData is included within the program, to fufill the dependency this
 program has for NodeData.
 -- NodeData has correct implmentations of operator ==,!=, >, <, copy
 Constructor.

 
 
 //------------========================================================---------
 //------------========================================================---------
 */



/*
 |=============================< DEFAULTCONSTRUCTOR >==========================|
 |	Function Name:
 |		-> Default constructor
 |	Description:
 |		-> sets the binary tree's root to nullptr, default no parameter
 |		constructor
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> BinaryTree is constructed/ and/or initalized
 |	ASSUMPTIONS:
 |		-> None
 |=============================================================================|
 */

BinTree::BinTree(){
    //default root to null
    //set the root to nullptr.
    root = nullptr;
}

/*
 |===============================< DESTRUCTOR >================================|
 |	Function Name:
 |		-> default destructor
 |	Description:
 |		-> called when the main tread stack ends the delete all objects
 |		allocated in main.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> Deallocates all tree nodes and NodeData contained to prevent
 |		Memory leaks.
 |	ASSUMPTIONS:
 |		-> None.
 |=============================================================================|
 */
BinTree::~BinTree(){
    //call clear helper method
    clear(root);
    //set root to nullptr
    root = nullptr;
}


/*
 |============================< COPY CONSTRUCTOR >=============================|
 |	Function Name: Copy constructor
 |		-> Makes a deep copy of rhs
 |	Description:
 |		-> This function makes a deept copy and initalizes an object
 |		with the rhs object.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> This Object is intalized with a deep copy of rhs object
 |	ASSUMPTIONS:
 |		-> None.
 |
 |=============================================================================|
 */
BinTree::BinTree(const BinTree &rhs){
    if(rhs.isEmpty()){
        //if the rhs is empty, quickly set this root to nullptr, and do not
        //continue, a small optimization.
        root = nullptr;
    }else{
        //make a call to the helper function.
        root = copyTreeHelper(root, rhs.root);
    }
}


/*
 |================================< COPY HELPER >==============================|
 |	Function Name:
 |		-> Copy constructor helper function( facade )
 |	Description:
 |		->  Facade helper function to make deep copies f rhs object
 |		-> This function works by making a new tree Node and NodeData.
 |		this recursive function says make the current node's child left and
 |		right, to a recursive sack call, each stack call check if the current
 |		child is nullptr( signafying we are at a child without a currrent node)
 |		when we foun the parking spot, we make a new node and return that node
 |		To the calling stack.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> this is initalized, with data from rhs.
 |	ASSUMPTIONS:
 |		-> None.
 |
 |=============================================================================|
 */
//IM A GOD
typename BinTree::Node* BinTree::copyTreeHelper(Node *thisCurrent,
                                                Node *rhsCurrent){
    if(rhsCurrent == nullptr){
        thisCurrent = nullptr;
    }else{
        //make a new node
        Node *newNode = new Node;
        //copy over the rhs data to a newData Node
        NodeData *newNodeData = new NodeData(*rhsCurrent->data);
        newNode->data = newNodeData;
        //link the current leaf with the new node.
        thisCurrent = newNode;
        //make a recursive stack call for the current nodes left,
        thisCurrent->left = copyTreeHelper(thisCurrent->left, 
		rhsCurrent->left);
        //make a recursive stack call for the current node right child node
        thisCurrent->right = copyTreeHelper(thisCurrent->right, 
		rhsCurrent->right);
    }
    
    //return the current subtree node.
    return thisCurrent;
}
/*
 |=============================< ASSIGNMENT OPERATOR >=========================|
 |	Function Name:
 |		-> Assignment operator overload
 |	Description:
 |		-> Assignment operator called to already instatiated object. This
 |		Method, clears the current Binary tree of existing objects and makes
 |		deep copies of the data from rhs to this(itself).
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> This is reconstructed with a deep copy of rhs NodeData elements.
 |		-> This function allocates new NodeData objects
 |	ASSUMPTIONS:
 |		-> NodeData default constructor is properly implemented.
 |=============================================================================|
 */
BinTree& BinTree::operator=(const BinTree &rhs){
    if(*this != rhs){//if its not the same object, reconstruct this as a copy of
        //RHS(deep copy)
        clear(root);//delete all things currently in this tree
    
        root = copyTreeHelper(root, rhs.root);
    }
    return *this;
}




/*
|==================================< INSERT >==================================|
|	Function Name:
|		-> insert 
|	Description:
|		-> insert a NodeData pointer into the current binary tree
|	Pre-Conditions:
|		-> None
|	Post-Conditions:
|		-> dataPtr (NodeData) is inserted into the binary tree
|		-> Returns  true if inserted, false if we have a duplicate
|	ASSUMPTIONS:
|		-> None.
|==============================================================================|
*/
bool BinTree::insert( NodeData *dataPtr){
	//the recursive stack call will return a root(subtree)
	//we want to retain the entire structure and its changes 
	//inserted so we need to 'save it'.
	//need to make a reference to isInserted boolean such that we are not making
	//a copy of the value instead we are changing the ACTUAL value of isInserted
	bool isInserted = false; //defaulted to false, because initally the item is
    //not inserted, once it is inserted we can change to assume it has correctly
    //inserted.
    
    //the parameters are Node * root, NodeData* dataPtr, and bool &reference
	root = insert(root, dataPtr, isInserted);
    
	return isInserted;
}

/*
|===============================< INSERT HELPER >==============================|
|	Function Name:
|		-> Insert facade method,
|	Description:
|		-> This method is a redirection of the original insert method.
|		-> This method works by checking wether the current root is nullptr.
|		If it is not, we then check wether the current data to insert is less
|		than or greater than the current Node's data(NodeData) if it is less
|		make a recursive call to the left of the current nodes left child 
|		pointer, otherwise make a recursive call to the right of current node
|		child, Once one of the current sub Nodes have found a child's pointer
|		be nullptr, make a new node, populate that node, and set the current 
|		pointer to the new node.
|		-> Each recursive call returns the newNode, when 'unwinding' the
|		recursive stack calls, each return links all calls, up to the very
|		top making it possible for the calling function to make root = function
|       -> Notice in this function we check if 2 and only 2 cases:
|               -> If the newData is less than current subtree Node.
|               -> If the newData is greater than current subtree Node.
|           This allows us to ommit the third case, if the target equals the
|           current node.
|	Pre-Conditions:
|		-> dataPtr is not nullptr
|	Post-Conditions:
|		-> Inserts the newNode data into the binary tree structure
|	ASSUMPTIONS:
|		-> DataPtr is not nulllptr, or NULL
|		-> operator ==,!=,>,< are implmented correctly in NodeData Object.
|==============================================================================|
*/
typename BinTree::Node* BinTree::insert(Node *subtree, NodeData *dataPtr, bool
&isInserted){
	if(subtree == nullptr){
		//found a parking spot park it.
		Node *newNode = new Node;
		//NodeData *nodeData = new NodeData(*dataPtr);
		newNode->data = dataPtr;
		//link the current previous calling stack 
		subtree = newNode;
        //switch the referenced parameter to true, signifying we have correctly
        //inserted the new Node.
		isInserted = true;
		//keep in mind, dataPtr is a NODEDATA
		//subtree is a NODE that CONTAINS(data field) a NODEDATA
		//NodeDATA has overloaded comparision operators to use here.
		//comparing two node data.

    //compare the current subtree->data object with the newData Item.
	}else if(*dataPtr < *subtree->data){
		//new Node Data is less than current Node, move left
		subtree->left = insert(subtree->left, dataPtr, isInserted);
	//To AVOID Duplicates, we have two conditional else if statments that will
	//check if the current pointer is GREATER and LESS than the current node,
	//BUT NEVER if its equal, 
	//in the event the dataPtr is equal the the current Node, we just return the
	//current node(base case) and unwinde the recursive stack back to root.
	}else if(*dataPtr > *subtree->data){
		//go to the right, of the current subtree->right
		subtree->right = insert(subtree->right, dataPtr, isInserted);
	}
    //last case is IF THE NEWDATA EQUALS the current node, we just ommit the
    //comparision and return the subtree without making more recursive stack
    //calls which will create new nodes.
    //we also keep the default false, boolean parameter passed in.
    
	//return the populated subtree from the above if statment
	return subtree;
}

/*
|================================< OPERATOR == >===============================|
|	Function Name:
|		-> Operator == 
|	Description:
|		-> Tell if two binary trees are the same
|	Pre-Conditions:
|		-> None
|	Post-Conditions:
|		-> Return a boolean reguarding if two binary tree are equals
|	ASSUMPTIONS:
|		-> NodeData operator == is correctly implmented.
|	
|==============================================================================|
*/
bool BinTree::operator==(const BinTree &rhs) const{
	//call the facade/Helper function equalsHelper
    return equalsHelper(root, rhs.root);
}

/*
|===============================< EQUALS HELPER >==============================|
|	Function Name:
|		-> Equals Helper
|	Description:
|		-> Helper/facade for the equals operator, to make a recursive call
|	Pre-Conditions:
|		-> None;
|	Post-Conditions:
|		-> Returns a boolean reguarding if two binary trees are equal.
|	ASSUMPTIONS:
|		-> NodeData operator == is correctly implemented
|==============================================================================|
*/
bool BinTree::equalsHelper( const Node *thisCurrent,const  Node *rhsCurrent)
const{
	//i want to check each node to see if they are the same 
	//recursivly calling this function on each,
	//check if the current node are the same
    //also handles if THIS and RHS root's are nullptr intally, return true.
	if(thisCurrent == nullptr && rhsCurrent == nullptr){
		return true;//once we encount a nullptr on return false
	}
	//checking the nodes
    // handles the case:
    //  we recursve into the current nodes children and one side has a children
    //  while the other sides does not,
    //  signifying a un even compare, not the same size, return false.
	else if(thisCurrent == nullptr || rhsCurrent == nullptr){
		return false;
	}
	//checking the data of th current and rhs current data, returning a boolean
	//and appending that boolean to the next recursive stack calls.
	return (*thisCurrent->data == *rhsCurrent->data) &&
	equalsHelper(thisCurrent->left, rhsCurrent->left) &&
	equalsHelper(thisCurrent->right, rhsCurrent->right);
}

/*
 |===============================< OPERATOR!= >================================|
 |	Function Name:
 |		-> Operator !=
 |	Description:
 |		-> Tells if two trees are not equal, same nodes contained
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> Returns a boolean regurading wether two trees are the same.
 |	ASSUMPTIONS:
 |		-> Operator == is correctly implemented and inintalized.
 |
 |=============================================================================|
 */
bool BinTree::operator!=(const BinTree &rhs) const{
    return !(*this == rhs);
}

/*
 |=================================< RETRIEVE >================================|
 |	Function Name:
 |		-> Retrieve function
 |	Description:
 |		-> given a pointer as a second parameter, retrieve will look for the
 |		target object, if found link/point the second parameter to the found
 |		NodeData in the binary tree, and return true, else the second
 |		pointer will equal nullptr
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> Returns true if item is found, false otherwise. The second parameter
 |		is a reference to a pointer will equal nullptr if returned false.
 |		otherwise will point to the corresponding targeted NodeData within
 |		the binary tree.
 |	ASSUMPTIONS:
 |		-> second parameter pointerToResult is not pointing to anything prior
 |		to prevent memory leaks.
 |=============================================================================|
 */

bool BinTree::retrieve(const NodeData &target, NodeData *&pointerToResult)
 const{
    //redirect to facade method.
    return retrieveHelper(target, pointerToResult, root);
}
/*
 |================================< RETRIEVE HELPER >==========================|
 |	Function Name:
 |		-> Retrieve helper function (facade)
 |	Description:
 |		-> Performs a binary search for the target node, the second parameter
 |		is referenced to the NodeData if the target has been located within
 |		The structure.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> None
 |	ASSUMPTIONS:
 |		-> pointerToResult has been freed, such that iff it had reference
 |		to data it was freed, to prevent memory leaks.
 |		-> NodeData operator >, <, ==, !=, have all been correctly implemented
 |		and check and return if the data contained are respective to their
 |		definitions.
 |      -> User does not delete the NodeData of the second parameter if the 
 |      NodeData was found,
 |=============================================================================|
 */
bool BinTree::retrieveHelper(const NodeData &target, NodeData *&pointerToResult,
                             Node *current) const{
    if(current == nullptr){
        //base case
        //item was not found
        //make the pointerToResult nullptr
        pointerToResult = nullptr;
        //return false, item not found
        return false;
        //if the item is found within the structure, point pointerToResult to
// the
        //NodeData object, and return true, signifying item found.
    }else if(*current->data == target){
        pointerToResult = current->data;
        return true;
        //make a recursive call to the left of the current node, if the target
// is
        //less than the current node.
    }else if(target < *current->data){
        retrieveHelper(target, pointerToResult, current->left);
        
        //make a recursive call to the right of the current node, if the target
		//is larger than the current node.
    }else{
        retrieveHelper(target, pointerToResult, current->right);
    }
}



/*
 |================================< BSTREETOARRAY >============================|
 |	Function Name:
 |		-> bstTree to Array
 |	Description:
 |		-> This function transfers the current bstTree to an array of NodeData
 |		Pointers, using an inorder walk/traversal to popualte the array.
 |		-> this function also NUll's the current tree after execution.
 |		-> Things to keep in mind are, when nulling the tree we do not want to
 |		call clear/make empty, for these functions will destroy the Tree node
 |		AND the NodeData associated with them. we also need to delete the
 |		tree nodes in an event where after transfering our node data we want
 |		to resuse this tree, our insert method would over-write/loss reference
 |		to the old exising Node's so to be safe its better to delete the
 |		current node's
 |		-> Thus calling a helper function deleteTreeNodesHelper does the job
 |		to deallocate exisiting tree nodes.
 |	Pre-Conditions:
 |		-> array of NodeData Pointers
 |	Post-Conditions:
 |		-> Binary tree is empty, root is set to null, and array given is
 |		now populated with a sorted repersentation of the bstree.
 |	ASSUMPTIONS:
 |		-> None.
 |=============================================================================|
 */
void BinTree::bstreeToArray(NodeData* array[]){
    //Parameter: array of NodeData Ptrs
    bstreeToArrayHelper(root, array, 0);
    //because we are transfering the nodes from bstree to array and we need to
    //null out the exising nodes, we need to transfer the NodeData safely
    //WITHOUT deleting the NodeData,s so calling a function that will just
    //delete/de-allocate the tree nodes, and not the NodeData, so we wont have
    //leaks
    deleteTreeNodesHelper(root);
    //set the tree to nullptr, or empty it out.
    root = nullptr;
}


/*
 |============================< BSTREETOARRAY HELPER >=========================|
 |	Function Name:
 |		-> bstTree to array helper function(facade)
 |	Description:
 |		-> This function transfers the current bstTree to an array of NodeData
 |		Pointers, using an inorder walk/traversal to popualte the array.
 |		-> this function also NUll's the current tree after execution.
 |		-> Things to keep in mind are, when nulling the tree we do not want to
 |		call clear/make empty, for these functions will destroy the Tree node
 |		AND the NodeData associated with them. we also need to delete the
 |		tree nodes in an event where after transfering our node data we want
 |		to resuse this tree, our insert method would over-write/loss reference
 |		to the old exising Node's so to be safe its better to delete the
 |		current node's
 |		-> Thus calling a helper function deleteTreeNodesHelper does the job
 |		to deallocate exisiting tree nodes.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> Binary tree is empty, root is set to null, and array given is
 |		now populated with a sorted repersentation of the bstree.
 |	ASSUMPTIONS:
 |		-> index is not changed from zero, array passed in has been initalized
 |		to all NULL values to prevent memory leaks.
 |=============================================================================|
 */
int BinTree::bstreeToArrayHelper(Node *current, NodeData *array[], int index){
    //out base case if the current node is nullptr, signifying we reached a node
    //whose child are nullptr, return the current counting index
    if(current == nullptr){
        return index;
    }
    //check if the current does exist make a recursive call, to its left.
    //giving it the current index to increment.
    if(current->left != nullptr){
        //the way this works is each recursive stack call will have a value of
        //the current index and incremented that index each recursive call each
        //time it is called, this recursive index is returned such that we have
        //a running total of the current index, and no over run index.
        index = bstreeToArrayHelper(current->left, array, index);
    }
    //used in an INORDER traversal where the index is kept and returned from the
    //two recursive calls,
    //set the arrays current index to the current nodes's NodeData Pointer
    array[index++] = current->data;
    if(current->right != nullptr){
        index = bstreeToArrayHelper(current->right, array, index);
    }
    //return the running index each recursive call.
    return index;
}
/*
 |===============================< ARRAYTOBSTREE >=============================|
 |	Function Name:
 |		-> array to bstree
 |	Description:
 |		-> populates this binary tree from the given array NodeData elements
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> This binary tree is constructed with items inorder
 |	ASSUMPTIONS:
 |		-> getSizeOFArrayHelper correctly initalized.
 |
 |=============================================================================|
 */
void BinTree::arrayToBSTree(NodeData *array[]){
    //cout << "SIZE FUNCTON: " <<getSizeOfArrayHelper(array) <<endl;
    root = arrayToBSTreeHelper(array,0,(getSizeOfArrayHelper(array) -1));
}
/*
 |=======================< ARRAYTOBSTREE HELPER >==============================|
 |	Function Name: array to bstree helper (facade helper function)
 |		->
 |	Description:
 |		-> This function is a facade helper which main functionality is to take
 |		Nodes from an array starting from the center and populate an binary
 |		Search tree from it.
 |		-> The way this function works, is first construct a tree node
 |		Then get the current array's middle data and assign it to the new node
 |		Next we make a recursive call, giving the left of the new Node
 |		The current array's sub-parition of the first half, Then doing the
 |		Same for the newNode's right child, giving the right child a recursive
 |		Call to the other "above mid/second" partition.
 |		->Each recursive stack call returns a newNode corresponding to that
 |		Stack calls sub-array middle index.
 |	Pre-Conditions:
 |		-> High and Low need to be correctly adjusted
 |	Post-Conditions:
 |		-> nulls the given array, and populates THIS binary tree with the
 |		respective nodeData elements from the array.
 |	ASSUMPTIONS:
 |		-> getSozeOFArray is correctly implmented.
 |
 |=============================================================================|
 */

typename BinTree::Node* BinTree::arrayToBSTreeHelper(NodeData *array[],
                                                     int low, int high){
    if(low > high){
        //eventually the middle tracker will minus 1 until mid is less than low
        //meaning for left parition is -1 is less than 0, -1 being mid and 0
        //being low.
        //at this point we return a nullptr signifying that we have reached the
        //end of the current array parition, and return a nullptr for the
        //previous recursive stack call's LEFT or RIGHT pointer.
        return nullptr;
    }
    //get the current mid of the array
    int mid = (low + high)/2;
    //get the NodeData pointer at the center of THIS sub array
    NodeData *dataPtr = array[mid];
    //construct the tree Node.
    Node *newNode = new Node;
    //reference/link the new tree node to the data pointer taken from the sub
    //array
    newNode->data = dataPtr;
    
    //empty the current index of this subarray's index to NULL
    array[mid] = NULL;
    
    //make a recursive call, to split the current array to subarray's
    //this call will split the current sub-array's left partition for the nodes
    //left children.
    newNode->left = arrayToBSTreeHelper(array,low, mid-1);
    //this recursive call will split the current subarray right partition for
    //the nodes, and pass that parition to the next recursive call to get the
    //middle node for insertion.
    newNode->right = arrayToBSTreeHelper(array,mid+1,high);
    //if we haven't hit out base-case meaning there is still more item in the
    //array, simply return the current constructed node to the previous
    //recursive call
    //-> this either be previous->right = THISnewNode ~OR~
    //-->previous->left = THISnewNode;
    return newNode;
    
}

/*
 |================================< MAKEEMPTY >================================|
 |	Function Name:
 |		-> MakeEmpty
 |	Description:
 |		-> This function calls clear, functon to remove,deallocate all tree
 |		Tree nodes and NodeData associated with the treeNode.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> Binary tree root is et to nullptr, all data/memory will be
 |		deallocated.
 |	ASSUMPTIONS:
 |		-> None.
 |=============================================================================|
 */

void BinTree::makeEmpty(){
    clear(root);
    root = nullptr;
}
/*
 |=============================< DISPLAYSIDEWAYS >=============================|
 |	Function Name:
 |		->i Display sideways
 |	Description:
 |		-> Displays the binary tree sideways, calls the helper method.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> prints to console the binary tree sideways
 |	ASSUMPTIONS:
 |		-> the second parameter does not change and is set to zero.
 |
 |=============================================================================|
 */
void BinTree::displaySideways() const{
    displaySidewaysHelper(root, 0);
}
/*
 |===============================< DISPLAYHELPER >=============================|
 |	Function Name:
 |		-> display side ways Helper
 |	Description:
 |		-> This functon displays the binary tree side ways,
 |		The way this function works is, we make an inorder walk/traversale
 |		However starting at the right side, or the right subtree, then to the
 |		left subtree. too get the tab effect printed out, we first start with
 |		zero depth, then for each recursive stack, or recursive call/ move
 |		to further to the right, we iterate our depth variable to know
 |		how much tabs we should have, once the stack call is over, that stack
 |		call will have the dept variable associated with the number or tabs
 |		we then print the number of tabs with a for-loop, in this instance
 |		we also have the current number of tabs for the left child in an
 |		event where the left chil exceeds the right, we can start for example
 |		current right child is 8 depth then the left is 9, the current stack
 |		holds a depth variable of 8, iterating the left stack call by one
 |		solves this little problem.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> Prints the binary tree sideways to the console.
 |	ASSUMPTIONS:
 |		-> Depth paramter is not changed from zero.
 |
 |=============================================================================|
 */

void BinTree::displaySidewaysHelper(Node *current, int depth) const{
    if(current != nullptr){
        
        displaySidewaysHelper(current->right, depth + 1);
        for(int i =0; i <= depth; ++i){
            std::cout << "\t";
        }
        std::cout <<  *current->data << endl;
        //each recursive call will take the CURRENT recursive stack calls depth
        //value and add too it, to make it even
        displaySidewaysHelper(current->left, depth + 1);
    }
}

/*
 |================================< GETHEIGHT >================================|
 |	Function Name:
 |		-> Get height
 |	Description:
 |		-> get the height starting from the current target node to the child
 |		with the most depth.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> Returns an integer associated with the depth of the current Node
 |		-> the number returned is the target node starting at 1
 |			-> IF THE node is Found, returns a depth starting at 1.
 |			-> IF THE node is NOT Found, returns a depth of zero(0).
 |	ASSUMPTIONS:
 |		-> operator == has been implemened in NodeData.
 |
 |=============================================================================|
 */

int BinTree::getHeight(const NodeData &target) const{
    return getNode(target, root);
}

/*
 |==================================< GETNODE >================================|
 |	Function Name:
 |		-> Get Node Helper
 |	Description:
 |		-> Helper function to search for the current target Node given by
 |		getHeight,if the target is found, make a recursive call to
 |		getHeightHelper function.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> None
 |	ASSUMPTIONS:
 |		-> getHeightHelper is implemented.
 |
 |=============================================================================|
 */

int BinTree::getNode(const NodeData &target, Node *current) const{
    if(current == nullptr){
        return 0;
        //if the current NodeData matches our target to look for..
    }else if(*current->data == target){
        // ... Make a recursive call to the getHeightHelper passing in the
        // pointer of the node that matches the target.
        return getHeightHelper(current);
    }else{
        //if the target still has not ben found, make a recursive call go into
        //sub children of the current node.
        return getNode(target, current->right) + getNode(target, current->left);
    }
}

/*
 |===============================< GETHEIGHTHELPER >===========================|
 |	Function Name:
 |		-> getHeight helper (facade)
 |	Description:
 |		-> a helper fuction called in a chain with getNode and getHeight, this
 |		function, is ONLY CALLED when getNode finds a matching node to its
 |		target.
 |		-> This function starts at given node as level 1, and makes a recursive
 |		call to itself, give it the current node's left and right children
 |		at the end of the base case, when each sub children reach the a nullptr
 |		and returns their respective integer values, std::max() built in
 |		library is called to compare the results and return the largest value
 |		between left and right subchildren.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> returns an integer pertaining to the current given node's lowest
 |		deepest most depth.
 |	ASSUMPTIONS:
 |		-> None.
 |
 |=============================================================================|
 */
int BinTree::getHeightHelper(Node *target) const{
    if(target == nullptr){
        return 0;
    }
    //each recursive call will append/increment 1 to the current stack
    //recursive call, each call adds 1 when we reach a nullptr, signifying
    //that current node has no children, we return zero, the stack unwinds
    //returning all the total number of stack calls was made.
    //the standard max function is called to compare the left and right
    //children depths, which is then returned to the calling function.
    return 1 + std::max( getHeightHelper(target->right), 
                        getHeightHelper(target->left));
}


/*
|==============================< OUTPUT OPERATOR >=============================|
|	Function Name:
|		->Operator <<
|	Description:
|		-> Outputs to the console, overloading the output operator
|	Pre-Conditions:
|		->
|	Post-Conditions:
|		->
|	ASSUMPTIONS:
|		->
|	
|==============================================================================|
*/
std::ostream& operator<<(std::ostream& output, const BinTree &rhs){
	//needs fixing i do not use ht ouput stream at all NOT sure how it works..
	//right now the helper is printing straight to the console using cout.
	rhs.outputHelper(output, rhs.root);
	return output;
}
/*
|===============================< OUTPUT HELPER >==============================|
|	Function Name:
|		-> print helper function(facade)
|	Description:
|		-> helper function for the output operator,
|	Pre-Conditions:
|		-> None
|	Post-Conditions:
|		-> print to the console the  inital items in the binary tree
|	ASSUMPTIONS:
|		-> None
|	
|==============================================================================|
*/

std::ostream& BinTree::outputHelper(std::ostream &output, Node *current) const{
	if(current != nullptr){
		outputHelper(output,current->left);
		output << " " << *current->data  << " ";
		outputHelper(output,current->right);
	}
	return output;
}

/*
Topics will be included by a week before test date, (topics will)
1st test 1 page front.
*/

/*
 |===============================< CLEAR HELPER  >=============================|
 |	Function Name:
 |		-> clear function helper
 |	Description:
 |		-> clear is called to empty the current binary tree, by deallocating
 |		all tree nodes and treeNodes NodeData objects held.
 |	Pre-Conditions:
 |		-> None;
 |	Post-Conditions:
 |		-> All tree Nodes and NodeData contained are deallocated/deleted.
 |	ASSUMPTIONS:
 |		-> The User must make the root nullptr, after calling clear.
 |=============================================================================|
 */
void BinTree::clear(Node *subtree){
    if(subtree != nullptr){
        //as long as subtree doens't equal nullptr there is something
        //to delete
        //make a recursive call the current subtree's right child
        clear(subtree->right);
        //make a recursive call to the current subtree's left child
        clear(subtree->left);
        //need not only delete the Node but also the NodeData
        //first delete/dealllocate the subtree's NodeDat
        delete subtree->data;
        //now delete the tree's Node.
        delete subtree;
    }
}


/*
 |=================================< IsEMPTY >=================================|
 |	Function Name:
 |		-> IsEmpty
 |	Description:
 |		-> Checks if the current tree is empty, by checking wether the root
 |		node pointer is pointing to a nullptr.
 |	Pre-Conditions:
 |		-> None
 |	Post-Conditions:
 |		-> returns a boolean signifying if the tree is empty, returns true
 |		if empty and false otherwise.
 |	ASSUMPTIONS:
 |		-> default constructor is called, which properly intalizes root pointer
 |
 |=============================================================================|
 */
bool BinTree::isEmpty() const{
    return root == nullptr;
}
/*
|===============================< GETSIZEHELPER >==============================|
|	Function Name:
|		-> GetSizeArray
|	Description:
|		-> return the number of elements in an given array, used in 
|		conjuncture with arrayToBSTreeHelper() function, to help get the
|		higher bound of the array
|	Pre-Conditions:
|		-> array properly initalized with NULL elements/ or ZERO
|	Post-Conditions:
|		-> Returns an integer pertaining to the number of elements in the 
|		given array.
|	ASSUMPTIONS:
|		-> array has perviously initalized with NULL elements or ZERO
|	
|==============================================================================|
*/

int BinTree::getSizeOfArrayHelper(NodeData *array[]){
	
	int numElements = 0;
	int index = 0;	
	while(true){
		//check if the current index is null/0
		//if so break from the loop
		if(array[index] == NULL)break;
		//increment variables
		numElements++;
		index++;
	}
	return numElements;
}



/*
|=========================< DELETETREENODEHELPER >=============================|
|	Function Name:
|		-> delete tree helper function
|	Description:
|		-> used to deallocate all tree nodes, mainly used for bstreetoarray
|		when we need to remove just the treenodes and not the NodeData 
|		associated with them.
|	Pre-Conditions:
|		-> None.
|	Post-Conditions:
|		-> Deallocates all Tree Node's within the binary tree
|	ASSUMPTIONS:
|		-> None.
|==============================================================================|
*/

void BinTree::deleteTreeNodesHelper(Node *current){
	if(current != nullptr){
		//as long as the current node is not nullptr,
		//recursivly call deleteTreeNodeHelper to its children
		deleteTreeNodesHelper(current->left);
		deleteTreeNodesHelper(current->right);
		//set the current node's data to nullptr
		current->data = nullptr;

		//deallocate the current tree node
		delete current;

	}
}


