#include <bits/stdc++.h>
using namespace std;

class Node{
private:
    friend class BST;
    int data;
    Node *left, *right;
public:
    Node(){
        this->left = NULL;
        this->right = NULL;
        this->data = -1;
    }
    Node(int data){
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class BST{
private:
    Node* root;
public:
    BST(){
        root = NULL;
    }
    Node *getRoot()
	{
		return root;
	}
	void setRoot(Node *r)
	{
		root = r;
	}

    void insert(Node *, int);
    void BFS(Node*);
    void inorder_itr_DFS(Node*);
    void inorder_rec_DFS(Node*);
};

void BST::insert(Node *p, int val){
    if(val < p->data){
        if(p->left != NULL)
            insert(p->left, val);
        else 
            p->left = new Node(val);
    }
    else if(val > p->data){
        if(p->right != NULL)
            insert(p->right, val);
        else    
            p->right = new Node(val);
    } else {
        cout << "Entered value is already present\n";
    }
}

void BST::BFS(Node* root){
    if(!root)
        cout << "There are zero nodes present";
    queue<Node*>q;
    q.push(root);
    while(!q.empty()){
        for(int i=0, n=q.size(); i<n; i++){
            Node* itr = q.front();
            cout << itr->data << " "; 
            q.pop();
            if(itr->left)
                q.push(itr->left);
            if(itr->right)
                q.push(itr->right);
        }
    }
    cout << "\n";
}

void BST::inorder_rec_DFS(Node *root){
    if(root){
        inorder_rec_DFS(root->left);
        cout << root->data << " ";
        inorder_rec_DFS(root->right);
    }
}

void BST::inorder_itr_DFS(Node *root){
    if(!root)
        cout << "There are zero nodes present";
    stack<Node*>s;

    while(root || !s.empty()){
        while(root){
            s.push(root);
            root = root->left;
        }
        root = s.top();
        cout << root->data << " ";
        s.pop();
        root = root->right;
    }
    cout << "\n";
}


int main(){
    int choice, newVal, n;
    BST t;

    do
    {
        cout << "\n<<-----------MENU----------->>" << endl;
		cout << "1. Insert new values" << endl;
		cout << "2. Display inorder DFS iterative" << endl;
		cout << "3. Display inorder DFS recursive" << endl;
		cout << "4. Display BFS" << endl;
		cout << "5. EXIT" << endl;
		cout << "<<-------------------------->>" << endl;
		cout << "\nEnter your choice: ";
		cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nEnter number of values want to insert: ";
            cin >> n;
            for(int i=0; i<n; i++){
                cin >> newVal;
                if(!t.getRoot()){
                    Node *newNode = new Node(newVal);
                    t.setRoot(newNode);
                } else {
                    t.insert(t.getRoot(), newVal);
                }
            }
            cout << "Values inserted\n";
            break;
        case 2:
            cout << "\nInorder DFS iterative:\n";
            t.inorder_itr_DFS(t.getRoot());
            break;
        case 3:
            cout << "\nInorder DFS recursive:\n";
            t.inorder_rec_DFS(t.getRoot());
            break;
        case 4:
            cout << "\nBFS:\n";
            t.BFS(t.getRoot());
            break;
        default:
            break;
        }
    } while (choice!=5);
    return 0;
}