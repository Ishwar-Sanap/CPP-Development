#include <bits/stdc++.h>
using namespace std;
/*
Design LRU Cache:

Requirements:
- Support get(key) operation: returns the value if the key exists, otherwise returns null or -1
- Support put(key, value) operation: inserts a new key-value pair or updates the value of an existing key
- If the cache exceeds its capacity, it should automatically evict the least recently used item.
- Both get and put operations should update the recency of the accessed or inserted item.
- Keys and values should be generic (e.g., <K, V>), provided the keys are hashable.
- Time Complexity: Both get and put operations must run in O(1) time on average.
- Thread Safety: The implementation must be thread-safe for use in concurrent environments.

*/

template <typename K, typename V>
class Node
{
public:
    V data;
    K key;
    Node *prev{};
    Node *next{};

    Node(const K &key, const V &val) : key(key), data(val)
    {
        prev = nullptr;
        next = nullptr;
    }
};

template <typename K, typename V>
class DoublyLinkedList
{
private:
    Node<K, V> *head;
    Node<K, V> *tail;
    int size;

public:
    Node<K, V> *getHead() const { return head; }
    Node<K, V> *getTail() const { return tail; }
    int getSize() const { return size; }
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0)
    {
    }

    ~DoublyLinkedList()
    {
        while (head)
        {
            Node<K, V> *delNode = head;
            head = head->next;
            delete delNode;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void insertAtFirst(const K &key, const V &val)
    {
        if (head == nullptr && tail == nullptr)
        {
            head = new Node<K, V>(key, val);
            tail = head;
        }
        else
        {

            Node<K, V> *newNode = new Node<K, V>(key, val);
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        size++;
    }

    void deleteGivenNode(Node<K, V> *ptr)
    {
        if (!ptr)
        {
            throw invalid_argument("Can't delete Invalid node");
        }

        if (ptr == tail && ptr == head)
        {
            tail = nullptr;
            head = nullptr;
        }
        else if (ptr == tail)
        {
            tail = ptr->prev;
            tail->next = nullptr;
        }
        else if (ptr == head)
        {
            head = ptr->next;
            head->prev = nullptr;
        }
        else
        {
            // In between node
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
        }

        size--;

        ptr->next = nullptr;
        ptr->prev = nullptr;
        delete ptr;
    }
    void deleteLast()
    {
        if (!head || !tail)
        {
            throw logic_error("Can't delete Invalid node");
        }

        Node<K, V> *delNode = tail;
        // Single node in list
        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        { // more than 1 nodes in list
            tail = tail->prev;
            tail->next = nullptr;
        }

        size--;
        delete delNode;
    }

    void printList()
    {
        Node<K, V> *temp = head;
        while (temp)
        {
            cout << "{ " << temp->key << " : " << temp->data << " } ";
            temp = temp->next;
        }
        cout << endl;
    }
};

template <typename K, typename V>
class LRUCache
{
private:
    int capacity{};
    unordered_map<K, Node<K, V> *> mpKeyToNode;
    DoublyLinkedList<K, V> dll;
    mutex mtx;

public:
    LRUCache(int cap) : capacity(cap)
    {
    }

    void put(const K &key, const V &val)
    {
        lock_guard<mutex> lg(mtx);

        // key not found
        if (mpKeyToNode.find(key) == mpKeyToNode.end())
        {
            if (dll.getSize() >= capacity)
            {
                // Evict the least recently used key (i.e last node from dll)
                Node<K, V> *node = dll.getTail();
                K oldKey = node->key;
                dll.deleteGivenNode(node);
                mpKeyToNode.erase(oldKey);
            }

            // Insert new key
            dll.insertAtFirst(key, val);
            mpKeyToNode[key] = dll.getHead();
        }
        else
        {
            // key found
            Node<K, V> *node = mpKeyToNode[key];
            dll.deleteGivenNode(node);
            dll.insertAtFirst(key, val);
            mpKeyToNode[key] = dll.getHead();
        }
    }

    std::optional<V> get(const K &key)
    {
        lock_guard<mutex> lg(mtx);

        if (mpKeyToNode.find(key) == mpKeyToNode.end())
            return std::nullopt;

        Node<K, V> *node = mpKeyToNode[key];
        V val = node->data;

        dll.deleteGivenNode(node);
        dll.insertAtFirst(key, val);
        mpKeyToNode[key] = dll.getHead();
        return val;
    }

    void displayCache()
    {
        dll.printList();
    }
};

int main()
{
    LRUCache<string, string> cache(4);
    cache.put("k1", "User1");
    cache.put("k2", "User2");
    cache.put("k3", "User3");

    cache.displayCache();
    auto result = cache.get("k1");
    if (result.has_value())
    {
        cout << result.value() << endl;
    }
    cache.displayCache();

    cache.put("k4", "User4");
    cache.displayCache();

    cache.put("k2", "User2New");
    cache.displayCache();

    cache.put("k5", "user5");
    cache.displayCache();

    auto result2 = cache.get("k3");
    if (result2.has_value())
    {
        cout << result2.value() << endl;
    }
    else
    {
        cout << " k3 [Key not found]" << endl;
    }

    return 0;
}