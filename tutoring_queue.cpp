/*
 * Course: COEN 2220 - Programming 2
 * Name: [Your Name]
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic queue of tutoring requests
 * Due date: [Date]
 */

#include <iostream>
#include <string>
using namespace std;

class LoanerDeviceQueue {
private:
    static const int CAPACITY = 4;
    string deviceIds[CAPACITY]; // Store available device IDs in fixed positions.
    int frontIndex;             // Store the index of the next device to check out.
    int rearIndex;              // Store the index of the most recently returned device.
    int itemCount;              // Distinguish an empty queue from a full queue.

public:
    LoanerDeviceQueue() {
        frontIndex = 0;
        rearIndex = CAPACITY - 1; // The first enqueue advances rearIndex to 0.
        itemCount = 0;
    }

    bool isEmpty() const {
        return itemCount == 0;    // No device is waiting to be checked out.
    }

    // --- STEP B2: Circular-array queue operations ---
    bool enqueue(const string& returnedDeviceId) {
        if (itemCount == CAPACITY) {
            return false; // No fixed array position is free.
        }
        rearIndex = (rearIndex + 1) % CAPACITY; // Advance and wrap when needed.
        deviceIds[rearIndex] = returnedDeviceId;
        itemCount++;
        return true;
    }

    bool dequeue(string& checkedOutDeviceId) {
        if (isEmpty()) {
            return false; // No device can be checked out from an empty queue.
        }
        checkedOutDeviceId = deviceIds[frontIndex];
        frontIndex = (frontIndex + 1) % CAPACITY; // Advance and wrap when needed.
        itemCount--;
        return true;
    }

    void displayAvailableDevices() const {
        for (int offset = 0; offset < itemCount; offset++) {
            int currentIndex = (frontIndex + offset) % CAPACITY;
            cout << "Available device: " << deviceIds[currentIndex] << endl;
        }
    }
};

class SupportRequestQueue {
private:
    struct Node {
        string requestId; // Store one support-request ID.
        Node *next;       // Point to the request immediately behind this one.
    };

    Node *front;          // Point to the request that must be handled next.
    Node *rear;           // Point to the request most recently received.

public:
    SupportRequestQueue() {
        front = nullptr;
        rear = nullptr;
    }

    ~SupportRequestQueue() {
        while (front != nullptr) {
            Node *nodeToDelete = front;
            front = front->next; // Save the next request through front before delete.
            delete nodeToDelete;
        }
        rear = nullptr; // The destructor leaves no pointer to a released node.
    }

    bool isEmpty() const {
        return front == nullptr; // An empty dynamic queue has no first node.
    }

    // --- STEP B3: Dynamic queue operations ---
    void enqueue(const string& newRequestId) {
        Node *newNode = new Node;
        newNode->requestId = newRequestId;
        newNode->next = nullptr; // The new request begins as the last node.

        if (rear == nullptr) {
            front = newNode; // The first node is also the front.
            rear = newNode;  // The first node is also the rear.
            return;
        }
        rear->next = newNode; // Connect the old rear to the new node.
        rear = newNode;       // The new node becomes the rear.
    }

    bool dequeue(string& handledRequestId) {
        if (front == nullptr) {
            return false; // An empty queue has no request to handle.
        }
        Node *nodeToDelete = front;
        handledRequestId = front->requestId;
        front = front->next; // The next request becomes the front.

        if (front == nullptr) {
            rear = nullptr; // Removing the last node leaves both pointers empty.
        }
        delete nodeToDelete;
        return true;
    }
};

int main() {
    LoanerDeviceQueue availableDevices;
    SupportRequestQueue supportRequests;
    string deviceId;
    string requestId;

    cout << boolalpha;
    cout << "Loaner device queue empty: " << availableDevices.isEmpty() << endl;
    cout << "Support request queue empty: " << supportRequests.isEmpty() << endl;

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
    cout << "Support request queue empty after handling all requests: " << supportRequests.isEmpty() << endl;
    supportRequests.enqueue("SR-245");
    supportRequests.dequeue(requestId);
    cout << "Handled new request after empty queue: " << requestId << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * E1 — First arrival
 * Why must the first call to enqueue assign newNode to both front and rear?
 * Answer: When the queue is empty, there is no existing chain of nodes. The newly added 
 * node serves simultaneously as the very first element (front) and the last element (rear) 
 * of the queue, ensuring both pointers correctly point to the single active node.
 *
 * E2 — Last departure
 * After dequeue removes the only remaining node, what must happen to rear and why?
 * Answer: rear must be set to nullptr (just like front). If rear were left pointing to the 
 * deallocated node, it would become a dangling pointer, corrupting future enqueue operations 
 * that rely on rear being nullptr to correctly identify and re-initialize an empty queue.
 *
 * E3 — FIFO evidence
 * List the expected service order for TU-301, TU-318, and TU-327. Explain why this
 * differs from the return order of the function-call stack in Part D.
 * Answer: TU-301, then TU-318, then TU-327. This follows FIFO (First-In, First-Out) where 
 * the first element added is the first one removed. This differs from a stack's LIFO 
 * (Last-In, First-Out) order in Part D because a stack retrieves the most recently added 
 * element first, whereas a queue maintains the original arrival sequence.
 *
 */