#include <iostream>
#include <stack>
#include <vector>

class Queue {
public:
    std::stack<int> instack;
    std::stack<int> outstack;

public:
    void enqueue(int element) {
        instack.push(element);
    }

    int dequeue() {
        if (outstack.empty()) {
            while (!instack.empty()) {
                outstack.push(instack.top());
                instack.pop();
            }
        }
        int front = outstack.top();
        outstack.pop();
        return front;
    }
};

template<typename T>
void printStack(const std::stack<T>& s) {
    // Create a copy of the original stack
    std::stack<T> tempStack = s;

    // Create a vector to store the elements temporarily
    std::vector<T> elements;

    // Pop elements from the copy of the stack and store them in the vector
    while (!tempStack.empty()) {
        elements.push_back(tempStack.top());
        tempStack.pop();
    }

    // Print the elements in the vector in reverse order
    std::cout << "Stack contents: ";
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int _queue() {
    Queue q;
    for (int i = 0; i < 10; ++i) {
        q.enqueue(i);
    }
    for (int i = 0; i < 9; ++i) {
        std::cout << q.dequeue() << std::endl;
    }
    printStack(q.instack);
    printStack(q.outstack);

    q.enqueue(24);

    for (int i = 0; i < 3; ++i) {
        std::cout << q.dequeue() << std::endl;
    }


    return 0;
}