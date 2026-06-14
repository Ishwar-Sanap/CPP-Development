#include <iostream>
using namespace std;

struct Node
{
    Node *next;
    int val;

    Node() : next(nullptr), val(0)
    {
    }
    Node(int data)
    {
        val = data;
        next = nullptr;
    }
};

void insertAtFirstPos(Node **head, int val)
{
    if (!*head)
    {
        *head = new Node(val);
    }
    else
    {
        Node *newNode = new Node(val);
        newNode->next = *head;
        *head = newNode;
    }
}
void insertAtLastPos(Node **head, int val)
{
    if (!*head)
    {
        *head = new Node(val);
    }
    else
    {
        Node *temp = *head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = new Node(val);
    }
}

void displayList(Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->val << " -> ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    Node *headNode = nullptr;

    insertAtFirstPos(&headNode, 1);
    insertAtFirstPos(&headNode, 2);
    insertAtFirstPos(&headNode, 3);
    insertAtFirstPos(&headNode, 4);
    insertAtLastPos(&headNode, 6);

    displayList(headNode);

    while (headNode)
    {
        Node *nextNode = headNode->next;

        delete headNode;
        headNode = nextNode;
    }

    return 0;
}