#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int data{};
    Node *left{};
    Node *right{};

    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

// T.C --> O(H)
Node *insertNode(Node *root, int val)
{
    if (!root)
    {
        return new Node(val);
    }

    if (val < root->data)
    {
        root->left = insertNode(root->left, val);
    }
    else
    {
        root->right = insertNode(root->right, val);
    }

    return root;
}

Node *insertNodeIterative(Node *root, int val)
{
    if (!root)
        return new Node(val);

    Node *temp = root;
    while (temp)
    {
        if (val < temp->data)
        {
            if (!temp->left)
            {
                temp->left = new Node(val);
                break;
            }

            temp = temp->left;
        }
        else
        {
            if (!temp->right)
            {
                temp->right = new Node(val);
                break;
            }

            temp = temp->right;
        }
    }

    return root;
}

// T.C O(H)
bool findNode(Node *root, int val)
{
    if (!root)
        return false;

    Node *temp = root;
    while (temp)
    {
        if (temp->data == val)
            return true;
        else if (val < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    return false;
}
void inorder(Node *root, vector<int> &ans)
{
    if (!root)
        return;

    inorder(root->left, ans);
    ans.push_back(root->data);
    inorder(root->right, ans);
}

Node *deleteNode(Node *root, int key)
{

    if (!root)
        return root;

    Node *delNodeParent = nullptr;
    Node *delNode = root;

    // Finding node to delete
    while (delNode)
    {
        if (key == delNode->data)
        {
            break;
        }

        delNodeParent = delNode;

        if (key < delNode->data)
        {
            delNode = delNode->left;
        }
        else
        {
            delNode = delNode->right;
        }
    }

    if (!delNode)
        return root;

    // Deleted node have either 1 (left/right) or 0 child
    if (!delNode->left || !delNode->right)
    {
        Node *childs = delNode->left ? delNode->left : delNode->right;

        // delete root node
        if (delNodeParent == nullptr)
            root = childs;
        else if (delNodeParent->left == delNode)
            delNodeParent->left = childs;
        else if (delNodeParent->right == delNode)
            delNodeParent->right = childs;
    }
    else
    {
        // Deleted node have 2 childs (left and right)

        // get smallest node from right subtree
        Node *curr = delNode->right;
        while (curr->left)
        {
            curr = curr->left;
        }
        curr->left = delNode->left;

        // delete root node
        if (delNodeParent == nullptr)
            root = delNode->right;
        else if (delNodeParent->left == delNode)
            delNodeParent->left = delNode->right;
        else if (delNodeParent->right == delNode)
            delNodeParent->right = delNode->right;
        ;
    }

    delete delNode;
    return root;
}

void levelOrderTravelsal(Node *root)
{
    if (!root)
        return;

    queue<Node *> qNodes;

    qNodes.push(root);

    while (!qNodes.empty())
    {
        int n = qNodes.size();
        for (int i = 0; i < n; i++)
        {
            Node *frt = qNodes.front();
            qNodes.pop();

            cout << frt->data << " ";

            if (frt->left)
                qNodes.push(frt->left);
            if (frt->right)
                qNodes.push(frt->right);
        }

        cout << endl;
    }
}
int main()
{
    vector<int> arr = {4, 5, 12, 3, 1, 18, 6, 2};
    Node *root = nullptr;

    for (int i = 0; i < arr.size(); i++)
    {
        // root = insertNode(root, arr[i]);  recursive

        root = insertNodeIterative(root, arr[i]);
    }

    // inodrder traversal print BST values in Sorted order : 1 2 3 4 5 6 12 18

    int target = 12;

    if (findNode(root, target))
    {
        cout << "Target node " << target << " found\n";
    }
    else
    {
        cout << "Target node " << target << " not found\n";
    }

    vector<int> ans;

    root = deleteNode(root, 18);
    inorder(root, ans);
    for (int &ele : ans)
    {
        cout << ele << " ";
    }

    cout<<endl;
    
    levelOrderTravelsal(root);
    return 0;
}