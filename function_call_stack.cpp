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
    // TODO (Part D): Write push to add a function name at top.
    // TODO (Part D): Write pop. It returns bool and uses string& removedFunctionName.
    // TODO (Part D): Write peek. It returns bool and uses string& topFunctionName.
    // TODO (Part D): Write a destructor that releases every dynamic node.
};

int main()
{
    cout << boolalpha;

    // ===== Resolve these TODOs later (Part D) =====

    // TODO (Part D): Create a FunctionCallStack object.
    // TODO (Part D): Push main, loadSchedule, and formatSchedule in that order.
    // TODO (Part D): Use peek and pop to demonstrate LIFO with descriptive output.
    // TODO (Part D): Pop remaining calls, then demonstrate an unsuccessful pop on an empty stack.

    return 0;
}

/*
 * Analysis Answers
 *
 * D1 — Adding formatSchedule
 * When push("formatSchedule") executes, what must newNode->next receive before top
 * changes? Explain why reversing those two assignments would lose the previous top.
 * Answer:
 *
 * D2 — Returning from a function
 * After main, loadSchedule, and formatSchedule are pushed in that order, list the
 * order in which three successful pop calls must return their names. Explain LIFO.
 * Answer:
 *
 * D3 — Destructor order
 * Why must the destructor save a next-node address before deleting the current node?
 * Answer:
 *
 */