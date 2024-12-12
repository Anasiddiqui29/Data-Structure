#include <iostream>
#include <string>

using namespace std ;

class Node
{
    public:
    int key ; 
    Node *right ; 
    Node *left ; 
    int height ; 

    Node(int key)
    {
        this->key = key ; 
        right = nullptr ; 
        left = nullptr ; 
        height = 1 ; 
    }
} ;

int getHeight(Node *N)
{
    if(N == nullptr)
    {
        return 0 ;
    }

    return N->height ; 
}

int getBalance(Node *N)
{
    if(N == nullptr)
    {
        return 0 ; 
    }

    return getHeight(N->left) - getHeight(N->right) ; //balance = height(left sub) - height(right sub)
}

int getmax(int a , int b)
{
    if(a>b)
    {
        return a ; 
    }
    else{
        return b ; 
    }
}

Node *rightRotate(Node *y)
{
    Node *x = y->left ; 
    Node *temp = x->right ; 

    //rotation
    x->right = y ; 
    y->left = temp ; 

    //update heights
    x->height = getmax(getHeight(x->left) , getHeight(x->right)) ;
    y->height = getmax(getHeight(y->left) , getHeight(y->right)) ; 

    return x ; 
}

Node *leftRotate(Node *x)
{
    Node *y = x->right ; 
    Node *temp = y->left ; 

    //rotation
    y->left = x ; 
    x->right = temp ; 

    //update heights
    x->height = getmax(getHeight(x->left) , getHeight(x->right)) ;
    y->height = getmax(getHeight(y->left) , getHeight(y->right)) ; 

    return y ; 
}

Node *insert(Node *node , int key)
{
    if(node == nullptr)
    {
        return new Node(key) ; 
    }

    if(key < node->key)
    {
        node->left = insert(node->left , key) ; 

    }
    else
    {
        if(key > node->key)
        {
            node->right = insert(node->right , key) ; 
        }
        else
        {
            return node ; 
        }
    }

    //update height
    node->height = 1+ getmax(getHeight(node->left) , getHeight(node->right)) ;

    //Now balancing
    //first calculate balance factor
    int balance = getBalance(node) ; 

    //left left subtree
    if(balance > 1 && key < node->left->key)
    {
        return rightRotate(node) ; 
    }

    //right right subtree
    if(balance < -1 && key > node->right->key)
    {
        return leftRotate(node) ; 
    }

    //left right subtree
    if(balance > 1 && key > node->left->key)
    {
        //double rotation
        node->left = leftRotate(node->left) ;
        return rightRotate(node) ; 
    }

    //right left subtree
    if(balance < -1 && key < node->right->key)
    {
        //double rotation
        node->right = rightRotate(node->right) ; 
        return leftRotate(node) ;
    }
    return node ; 
}

Node *findmin(Node *node)
{
    while(node->left !=nullptr) //since min will always be at the left side of the tree
    {
        node = node->left ; 
    }
    return node ; 
}

Node* deleteNode(Node* root, int key) 
{
    // standard bst delete
     if(root == nullptr)
        {
            return root ; 
        }
        else
        {
            // If node to delete is leaf node
            if(key < root->key) //Node to be delete in the left subtree
            {
                root->left = deleteNode(root->left , key) ;
            }
            else
            {
                if(key > root->key) //Node to be deleted in the right subtree
                {
                    root->right = deleteNode(root->right , key) ;
                }
                else
                {
                    //if the node that has to be deleted has one child
                    if(root->left == nullptr)
                    {
                        Node * temp = root->right ; 
                        delete root ; 
                        return temp ; 
                    }
                    else
                    {
                        Node * temp = root->left ; 
                        delete root ; 
                        return temp ;
                    }
                }

                //if the node that has to be deleted has two childs
                Node  * temp = findmin(root->right) ; //root->right add kiya hai abhi
                root->key = temp->key ;
                root->right = deleteNode(root->right , temp->key) ;
            }
        }

    // update height and check
    root->height = 1 + getmax(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key)
    {
        return rightRotate(root);
    }
    
    // Left Right Case
    if (balance > 1 && key > root->left->key) 
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && key > root->right->key)
    {
        return leftRotate(root);
    }
    
    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

//Inorder traversal
Node *findKthsmallest(Node *node , int &k)
{
    if(node == nullptr)
    {
        return nullptr ; 
    }
    
    Node *left = findKthsmallest(node->left , k) ; 

    if(left != nullptr)
    {
        return left ; 
    }

    k-- ; 

    if(k==0)
    {
        return node ; 
    }

    return findKthsmallest(node->right , k) ;
}

//Reverse Inorder traversal
Node *findkthlargest(Node *node , int& k)
{
    if(node == nullptr)
    {
        return nullptr ; 
    }

    Node *right = findkthlargest(node->right , k) ;

    if(right != nullptr)
    {
        return right ; 
    }

    k-- ;

    if(k == 0)
    {
        return node ; 
    }

    return  findkthlargest(node->left , k) ; 
}

void display(Node *node)
{
    if (node == nullptr)  // base case to stop recursion
    {
        return;
    }
    //preorder
    cout << node->key << "\t" ; 
    display(node->left) ; 
    display(node->right) ; 
}

void PrintleftrightHeight(Node *node)
{
    if(node == nullptr)
    {
        return ; 
    }

    cout << "Left height: " << getHeight(node->left) << endl ;
    cout << "Right height: " << getHeight(node->right) ; 
}


int main()
{
    Node *root = nullptr ; 
    root = insert(root , 1) ; 
    root = insert(root , 2) ; 
    root = insert(root , 3) ; 
    root = insert(root , 4) ; 
    root = insert(root , 5) ; 
    root = insert(root , 6) ;
    root = insert(root , 7) ;  

    int k = 3;
    Node* kthSmallest = findKthsmallest(root, k);
    if (kthSmallest) 
    {
        cout << "3rd Smallest Key: " << kthSmallest->key << endl;
    } 
    else 
    {
        cout << "Less than 3 elements in the tree." << endl;
    }

    k = 3;
    Node* kthLargest = findkthlargest(root, k);
    if (kthLargest) 
    {
        cout << "3rd Largest Key: " << kthLargest->key << endl;
    } else 
    {
        cout << "Less than 3 elements in the tree." << endl;
    } 

    PrintleftrightHeight(root) ; 
} 
