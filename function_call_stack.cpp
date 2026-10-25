/*
 * Course: COEN 2220 - Programming 2
 * Name: [Your Name]
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic stack of active function calls
 * Due date: [Date]
 */

#include <iostream>
#include <string>

using namespace std;

class FunctionCallStack {
private:
    // ===== Resolve these TODOs now (Part C) =====
    // TODO (Part C): Define Node with string functionName and Node *next.
    struct Node {
        string functionName; // Store the name of the active function call
        Node *next;          // Point to the previous call in the stack
    };

    // TODO (Part C): Declare Node *top for the node that must leave next.
    Node *top;               // Point to the most recent function call at the top of the stack

public:
    // TODO (Part C): Write a constructor that creates an empty stack.
    FunctionCallStack() {
        top = nullptr;       // An empty stack starts with no active calls
    }

    // ===== Resolve these TODOs later (Part D) =====
    
    // TODO (Part D): Write isEmpty as a const member function.
    bool isEmpty() const {
        return top == nullptr; // Stack is empty if top points to nothing
    }

    // TODO (Part D): Write push to add a function name at top.
    void push(const string& functionName) {
        Node *newNode = new Node;
        newNode->functionName = functionName;
        newNode->next = top;    // Link the new node to the previous top
        top = newNode;          // Make the new node the new top of the stack
    }

    // TODO (Part D): Write pop. It returns bool and uses string& removedFunctionName.
    bool pop(string& removedFunctionName) {
        if (isEmpty()) {
            return false;       // Cannot pop from an empty stack
        }
        Node *nodeToDelete = top;
        removedFunctionName = top->functionName;
        top = top->next;        // Move top down to the previous node
        delete nodeToDelete;    // Release the memory of the popped node
        return true;
    }

    // TODO (Part D): Write peek. It returns bool and uses string& topFunctionName.
    bool peek(string& topFunctionName) const {
        if (isEmpty()) {
            return false;       // Cannot peek into an empty stack
        }
        topFunctionName = top->functionName;
        return true;
    }

    // TODO (Part D): Write a destructor that releases every dynamic node.
    ~FunctionCallStack() {
        while (!isEmpty()) {
            string tempName;
            pop(tempName);      // Pop nodes until the stack is completely empty and freed
        }
    }
};

int main() {
    cout << boolalpha;

    // ===== Resolve these TODOs later (Part D) =====
    // TODO (Part D): Create a FunctionCallStack object.
    FunctionCallStack callStack;
    string currentFunc;

    // TODO (Part D): Push main, loadSchedule, and formatSchedule in that order.
    callStack.push("main");
    callStack.push("loadSchedule");
    callStack.push("formatSchedule");

    // TODO (Part D): Use peek and pop to demonstrate LIFO with descriptive output.
    if (callStack.peek(currentFunc)) {
        cout << "Current function: " << currentFunc << endl;
    }

    if (callStack.pop(currentFunc)) {
        cout << "Returned from function: " << currentFunc << endl;
    }

    if (callStack.pop(currentFunc)) {
        cout << "Returned from function: " << currentFunc << endl;
    }

    // TODO (Part D): Pop remaining calls, then demonstrate an unsuccessful pop on an empty stack.
    if (callStack.pop(currentFunc)) {
        cout << "Returned from function: " << currentFunc << endl;
    }

    cout << "Stack empty: " << callStack.isEmpty() << endl;

    bool emptyPopResult = callStack.pop(currentFunc);
    cout << "Pop from empty stack succeeded: " << emptyPopResult << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * D1 — Adding formatSchedule
 * When push("formatSchedule") executes, what must newNode->next receive before top
 * changes? Explain why reversing those two assignments would lose the previous top.
 * Answer: newNode->next must receive the current address stored in top (i.e., top). If you reassigned 
 * top = newNode first, you would overwrite the only pointer keeping track of the rest of the stack. 
 * This would sever the connection to all preceding nodes, resulting in a memory leak and permanently 
 * losing access to the rest of the stack.
 *
 * D2 — Returning from a function
 * After main, loadSchedule, and formatSchedule are pushed in that order, list the
 * order in which three successful pop calls must return their names. Explain LIFO.
 * Answer: formatSchedule, then loadSchedule, then main. This follows LIFO (Last-In, First-Out) 
 * because the last function pushed onto the stack is the first one that must finish executing 
 * and pop off before the program can return to the previous calling functions.
 *
 * D3 — Destructor order
 * Why must the destructor save a next-node address before deleting the current node?
 * Answer: Once you call delete on the current node, its memory is deallocated and returned to the 
 * system, meaning you can no longer safely access its members or its ->next pointer. You must 
 * save the next-node address in a temporary pointer before deleting so you can continue traversing 
 * and freeing the rest of the stack.
 *
 */