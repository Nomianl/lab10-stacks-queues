/*
 * Course: COEN 2220 - Programming 2
 * Name: [Your Name]
 * Lab: Lab 10 - Stacks & Queues
 * Description: Guided example - static and dynamic service queues
 * Due date: [Date]
 */

#include <iostream>
#include <string>
using namespace std;

class LoanerDeviceQueue
{
private:
    static const int CAPACITY = 4;
    string deviceIds[CAPACITY]; // Store available device IDs in fixed positions.
    int frontIndex;             // Store the index of the next device to check out.
    int rearIndex;              // Store the index of the most recently returned device.
    int itemCount;              // Distinguish an empty queue from a full queue.

public:
    LoanerDeviceQueue()
    {
        frontIndex = 0;
        rearIndex = CAPACITY - 1; // The first enqueue advances rearIndex to 0.
        itemCount = 0;
    }

    bool isEmpty() const
    {
        return itemCount == 0; // No device is waiting to be checked out.
    }

    // --- STEP B2: Circular-array queue operations ---

    bool enqueue(const string& returnedDeviceId)
    {
        if (itemCount == CAPACITY)
        {
            return false; // No fixed array position is free.
        }

        rearIndex = (rearIndex + 1) % CAPACITY; // Advance and wrap when needed.
        deviceIds[rearIndex] = returnedDeviceId;
        itemCount++;
        return true;
    }

    bool dequeue(string& checkedOutDeviceId)
    {
        if (isEmpty())
        {
            return false; // No device can be checked out from an empty queue.
        }

        checkedOutDeviceId = deviceIds[frontIndex];
        frontIndex = (frontIndex + 1) % CAPACITY; // Advance and wrap when needed.
        itemCount--;
        return true;
    }

    void displayAvailableDevices() const
    {
        for (int offset = 0; offset < itemCount; offset++)
        {
            int currentIndex = (frontIndex + offset) % CAPACITY;
            cout << "Available device: " << deviceIds[currentIndex] << endl;
        }
    }

};

class SupportRequestQueue
{
private:
    struct Node
    {
        string requestId; // Store one support-request ID.
        Node *next;       // Point to the request immediately behind this one.
    };

    Node *front; // Point to the request that must be handled next.
    Node *rear;  // Point to the request most recently received.

public:
    SupportRequestQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~SupportRequestQueue()
    {
        while (front != nullptr)
        {
            Node *nodeToDelete = front;
            front = front->next; // Save the next request through front before delete.
            delete nodeToDelete;
        }

        rear = nullptr; // The destructor leaves no pointer to a released node.
    }

    bool isEmpty() const
    {
        return front == nullptr; // An empty dynamic queue has no first node.
    }

    // --- STEP B3: Dynamic queue operations ---
    
    void enqueue(const string& newRequestId)
    {
        Node *newNode = new Node;
        newNode->requestId = newRequestId;
        newNode->next = nullptr; // The new request begins as the last node.

        if (rear == nullptr)
        {
            front = newNode; // The first node is also the front.
            rear = newNode;  // The first node is also the rear.
            return;
        }

        rear->next = newNode; // Connect the old rear to the new node.
        rear = newNode;       // The new node becomes the rear.
    }

    bool dequeue(string& handledRequestId)
    {
        if (front == nullptr)
        {
            return false; // An empty queue has no request to handle.
        }

        Node *nodeToDelete = front;
        handledRequestId = front->requestId;
        front = front->next; // The next request becomes the front.

        if (front == nullptr)
        {
            rear = nullptr; // Removing the last node leaves both pointers empty.
        }

        delete nodeToDelete;
        return true;
    }
    
};

int main()
{
    LoanerDeviceQueue availableDevices;
    SupportRequestQueue supportRequests;
    string deviceId;
    string requestId;

    cout << boolalpha;
    cout << "Loaner device queue empty: "
         << availableDevices.isEmpty() << endl;
    cout << "Support request queue empty: "
         << supportRequests.isEmpty() << endl;

    // --- STEP B2: Reuse array positions after checkouts ---
    
    availableDevices.enqueue("LT-101");
    availableDevices.enqueue("LT-102");
    availableDevices.enqueue("LT-103");
    availableDevices.enqueue("LT-104");

    availableDevices.dequeue(deviceId);
    cout << "Checked out device: " << deviceId << endl;
    availableDevices.dequeue(deviceId);
    cout << "Checked out device: " << deviceId << endl;

    availableDevices.enqueue("LT-105"); // rearIndex wraps from 3 to 0.
    availableDevices.enqueue("LT-106");

    availableDevices.displayAvailableDevices();
    

    // --- STEP B3: Handle requests in arrival order ---
    
    supportRequests.enqueue("SR-204");
    supportRequests.enqueue("SR-219");
    supportRequests.enqueue("SR-231");

    supportRequests.dequeue(requestId);
    cout << "Handled request: " << requestId << endl;
    supportRequests.dequeue(requestId);
    cout << "Handled request: " << requestId << endl;
    supportRequests.dequeue(requestId);
    cout << "Handled request: " << requestId << endl;

    cout << "Support request queue empty after handling all requests: "
         << supportRequests.isEmpty() << endl;

    supportRequests.enqueue("SR-245");
    supportRequests.dequeue(requestId);
    cout << "Handled new request after empty queue: " << requestId << endl;
    

    return 0;
}

/*
 * Analysis Answers
 *
 * B4 — Circular queue state
 * After LT-101 and LT-102 are checked out, why can LT-105 use an array position
 * near the beginning even though LT-103 and LT-104 are still available? Explain
 * the roles of frontIndex, rearIndex, and itemCount.
 * Answer:
 *
 * B5 — Dynamic queue empty state
 * After SR-231 is handled, why must rear become nullptr as well as front? Explain
 * what would be wrong if rear still pointed to the deleted node before SR-245 arrives.
 * Answer:
 *
 */