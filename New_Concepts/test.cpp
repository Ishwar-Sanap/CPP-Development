#include <bits/stdc++.h>
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

class LinkedList
{
private:
    Node *m_ptrHeadStNode{};

public:
    LinkedList() : m_ptrHeadStNode(nullptr)
    {
    }

    // Insert at first position
    void insertAtFirst(int val)
    {
        if (!m_ptrHeadStNode)
            m_ptrHeadStNode = new Node(val);
        else
        {
            Node *newNode = new Node(val);
            newNode->next = m_ptrHeadStNode;
            m_ptrHeadStNode = newNode;
        }
    }

    // Insert at last position
    void insertLast(int val)
    {
        Node *temp = m_ptrHeadStNode;
        if (!m_ptrHeadStNode)
            m_ptrHeadStNode = new Node(val);

        else
        {
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }

            Node *newNode = new Node(val);
            temp->next = newNode;
        }
    }
    // Display list
    void display()
    {
        Node *temp = m_ptrHeadStNode;
        while (temp != nullptr)
        {
            cout << temp->val << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~LinkedList()
    {
        while (m_ptrHeadStNode != nullptr)
        {
            Node *nextNode = m_ptrHeadStNode->next;
            delete m_ptrHeadStNode;
            m_ptrHeadStNode = nextNode;
        }
    }
};

void insertAtFirstPos(Node *head, int val)
{
    if (!head)
    {
        head = new Node(val);
    }
    else
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }
}
void insertAtLastPos(Node *head, int val)
{
    if (!head)
    {
        head = new Node(val);
    }
    else
    {
        while (head->next != nullptr)
        {
            head = head->next;
        }
        Node *newNode = new Node(val);
        head->next = newNode;
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

    // LinkedList ll;
    // ll.insertAtFirst(1);
    // ll.insertAtFirst(2);
    // ll.insertAtFirst(3);
    // ll.insertAtFirst(4);
    // ll.insertLast(6);
    // ll.display();

    Node *headNode = nullptr;

    insertAtFirstPos(headNode, 1);
    insertAtFirstPos(headNode, 2);
    insertAtFirstPos(headNode, 3);
    insertAtFirstPos(headNode, 4);
    insertAtLastPos(headNode, 6);

    displayList(headNode);

    while (headNode)
    {
        Node *nextNode = headNode->next;

        delete headNode;
        headNode = nextNode;
    }

    return 0;
}