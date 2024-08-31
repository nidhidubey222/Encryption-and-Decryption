#include <bits/stdc++.h>
using namespace std;

string cypher_text;
string decipher;
vector<int> v1;
vector<int> input;
vector<vector<int>> pd;
int indexx;
int pindex;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node *root;
    vector<int> in;
    vector<int> pre;
    vector<int> post;
    // Function to create a new node
Node* CreateNode(int data)
{
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
 
// Function to insert element in binary tree
void insert(Node*&root, int data)
{
    // If the tree is empty, assign new node addcypher_texts to root
    if (root == NULL) {
        root = CreateNode(data);
        return ;
    }
 
    // Else, do level order traversal until we find an empty
    // place, i.e. either left child or right child of some
    // node is pointing to NULL.
    queue<Node*> q;
    q.push(root);
 
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
 
        if (temp->left != NULL)
            q.push(temp->left);
        else {
            temp->left = CreateNode(data);
           return ;
        }
 
        if (temp->right != NULL)
            q.push(temp->right);
        else {
            temp->right = CreateNode(data);
            return;
        }
    }
}

 void inorderr(Node* temp)
{
    if (temp == NULL)
        return;
 
    inorder(temp->left);
    cout<<temp->data<<" ";
    
    inorder(temp->right);
}
/* Inorder traversal of a binary tree */
void inorder(Node* temp)
{
    if (temp == NULL)
        return;
 
    inorder(temp->left);
    v1.push_back(temp->data);
    inorder(temp->right);
}
void preorder(Node* temp)
{
    if (temp == NULL)
        return;
    v1.push_back(temp->data);
    preorder(temp->left);
    preorder(temp->right);
}
void postorderr(Node* temp)
{
    if (temp == NULL)
        return;
    postorderr(temp->left);
    postorderr(temp->right);
    pd[indexx].push_back(temp->data);
}
Node* buildTree(vector<int> preorder,vector<int> inorder,int n)
{
    set<Node*> s;
    stack<Node*> st;
    Node* root = NULL;
    for (int pre = 0, in = 0; pre < n;)
    {
 
        Node* node = NULL;
        do
        {
            node = CreateNode(preorder[pre]);
            if (root == NULL)
            {
                root = node;
            }
            if (st.size() > 0)
            {
                if (s.find(st.top()) != s.end())
                {
                    s.erase(st.top());
                    st.top()->right = node;
                    st.pop();
                }
                else
                {
                    st.top()->left = node;
                }
            }
            st.push(node);
        } while (preorder[pre++] != inorder[in] && pre < n);
 
        node = NULL;
        while (st.size() > 0 && in < n &&
                st.top()->data == inorder[in])
        {
            node = st.top();
            st.pop();
            in++;
        }
 
        if (node != NULL)
        {
            s.insert(node);
            st.push(node);
        }
    }
 
    return root;
}
 Node* buildTree_pd(vector<int> inorder, vector<int> postorder, int n)
{
 
    // Create Stack of type Node*
    stack<Node*> st;
 
    // Create Set of type Node*
    set<Node*> s;
 
    // Initialise postIndex with n - 1
    int postIndex = n - 1;
 
    // Initialise root with NULL
    Node* root = NULL;
 
    for (int p = n - 1, i = n - 1; p >= 0;) {
 
        // Initialise node with NULL
        Node* node = NULL;
 
        // Run do-while loop
        do {
 
            // Initialise node with
            // new Node(post[p]);
            node = CreateNode(postorder[p]);
 
            // Check is root is
            // equal to NULL
            if (root == NULL) {
                root = node;
            }
 
            // If size of set
            // is greater than 0
            if (st.size() > 0) {
 
                // If st.top() is present in the
                // set s
                if (s.find(st.top()) != s.end()) {
                    s.erase(st.top());
                    st.top()->left = node;
                    st.pop();
                }
                else {
                    st.top()->right = node;
                }
            }
 
            st.push(node);
 
        } while (postorder[p--] != inorder[i] && p >= 0);
 
        node = NULL;
 
        // If the stack is not empty and
        // st.top()->data is equal to in[i]
        while (st.size() > 0 && i >= 0
               && st.top()->data == inorder[i]) {
            node = st.top();
 
            // Pop elements from stack
            st.pop();
            i--;
        }
 
        // if node not equal to NULL
        if (node != NULL) {
            s.insert(node);
            st.push(node);
        }
    }
 
    // Return root
    return root;
}
void levelorder(vector<int> keyt)
{
    if (root == NULL)
        return;
 
    // Create an empty queue for level order traversal
    queue<Node*> q;
    vector<int> Y;
    // Enqueue Root and initialize height
    q.push(root);
 
    while (q.empty() == false) {
        // Print front of queue and remove it from queue
        Node* node = q.front();
        //cout<<node->data;
        Y.push_back(node->data);
        q.pop();
 
        /* Enqueue left child */
        if (node->left != NULL)
            q.push(node->left);
 
        /*Enqueue right child */
        if (node->right != NULL)
            q.push(node->right);

        
    }
    int result = 0;
    for (int i=0;i<Y.size();i++)  
    {
        result = result * 10 + Y[i];
    }
    int pidd=keyt[0];
    int p=0;
    while(pidd>0)
    {
        p+=(pidd%10);
        pidd/=10;
    }
    int asc=(result-keyt[1])/p;
    char c=(char)asc;
    decipher.push_back(c);
}

};

void encryption(char c, vector<int> keyt)
{
    
    Node e;
    e.root=NULL;
    int ascii=int(c);
    int pidd=keyt[0];
    int p=0;
    while(pidd>0)
    {
        p+=(pidd%10);
        pidd/=10;
    }
    int y=ascii*p+keyt[1];
    int reversed_number=0;
    int f=0;
    if(y%10==0)
        f++;
    if(y%100==0)
        f++;
    if(y%1000==0)
        f++;
    while(y > 0) 
    {
        reversed_number = reversed_number * 10 + y % 10;
        y/=10;
    }
    while(reversed_number>0)
    {
        
        e.insert(e.root,reversed_number%10);
        reversed_number/=10;
    }
    if(f>0)
    {
        for(int i=0;i<f;i++)
            e.insert(e.root,0);
    }
        
    e.inorder(e.root);
    
    e.preorder(e.root);
    e.postorderr(e.root);
    reverse(pd[indexx].begin(),pd[indexx].end());
    indexx++;
    for(int i=0;i<v1.size();)
    {
        int t=v1[i]*10+v1[i+1];
        if(t<33)
            t+=100;
        //cout<<t<<endl;
        char re=char(t);
        cypher_text.push_back(re);
        i+=2;
    }
}
//deccypher_text function
void decryption(int a, vector<int> keyt)
{
   
    Node e;
    for(int i=0;i<input.size()/2;i++)
    {
            e.in.push_back(input[i]);
    }
    for(int i=input.size()/2;i<input.size();i++)
    {
            e.pre.push_back(input[i]);
    }
    for(int i=0;i<e.in.size();i++)
        e.post.push_back(pd[a][i]);
    int f=0;
    for(int i=0;i<e.in.size();i++)
    {
        if(e.in[i]!=e.pre[i])
        {
            f=1;
            break;
        }   
    }
    if(f==0)
    {
         e.root=e.buildTree_pd(e.in,e.post,e.in.size());
    }
    else
    {
        e.root=e.buildTree(e.pre,e.in,e.in.size());
    }
    
    e.levelorder(keyt);
}

string tree_prep(string s, vector<int> keyt)
{
    pd.resize(s.length(),vector<int>(6,0));
    indexx=0;
    for(int i=0;i<s.length();i++)
    {
        
        encryption(s[i],keyt);
        v1.clear();
        cypher_text.push_back(' ');
       
    }
    return cypher_text;
}

string tree_end(string text, vector<int> keyt)
{
    int count=0;
    int f=0;
    int j=0;
    map<int,int> m;
    for(int i=0;i<text.length();i++)
    {
        if(text[i]!=' ')
            f++;
        else
        {
            m[j++]=f;
            f=0;
        }
    }
    int limit=0,i=0;
   for(auto x:m)
   {
        while(i<limit+x.second)
        {
            int y;
            int reversed_number=0,t,w,g=0;
            // if(i==0)
            // {
            //     t=(int)cypher_text[0];
            //     if(t==(-128))
            //         t=128;
            //     if(t==(-127))
            //         t=129;
            //     if(t==(-126))
            //         t=130;
            //     if(t==(-125))
            //         t=131;
            //     if(t==(-124))
            //         t=132;
            //     if(t>=100)
            //         t-=100;
            //     if(t<10)
            //         g=1;
            //     w=0;
            //     if(t%1000==0)
            //         w+=3;
            //     else
            //     {
            //         if(t%100==0)
            //             w+=2;
            //         else
            //         {
            //             if(t%10==0)
            //                 w++;
            //         }
            //     }
            //     y=t;
            // }
                
            // else
            //{
                int h=0;
                t=(int)text[i];
                //cout<<"ascii:"<<text[i]<<t<<endl;
                if(text[i]=='d')
                    h=1;
                if(t==(-128))
                    t=128;
                if(t==(-127))
                    t=129;
                if(t==(-126))
                    t=130;
                if(t==(-125))
                    t=131;
                if(t==(-124))
                    t=132;
                if(t>=100)
                    t-=100;
                if(t<10)
                    g=1;
                w=0;
                if(h==1)
                {
                    w+=1;
                }
                else
                {
                    if(t%10==0)
                        w++;
                    if(t%100==0)
                        w++;
                    if(t%1000==0)
                        w++;
                }
            //}   
            //cout<<t<<" ";
            while(t > 0) 
            {
                reversed_number = reversed_number * 10 + t % 10;
               // cout<<reversed_number<<" ";
                t/=10;
            }
            // if(i==0)
            //     reversed_number-=300;
           // cout<<reversed_number<<endl;
            if(g==1)
                input.push_back(0);
            while(reversed_number>0)
            {
                input.push_back(reversed_number%10);
                
                reversed_number/=10;
            }
            
            if(w>0)
            {
                for(int l=0;l<w;l++)
                    input.push_back(0);
                w=0;
            }
            i++;
                
        }
        int g=x.first;
        decryption(g,keyt);
        input.clear();
        i++;
        limit=i;
   }
    return decipher;
}