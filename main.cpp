#include<iostream>

using namespace std;

struct Node {
    int value;
    Node *next;
};

struct Queue {
    Node *start;
    Node *end;
};

Queue *init() {
    auto *queue = new Queue;

    queue->start = nullptr;

    queue->end = nullptr;

    return queue;
}

bool isEmpty(Queue *queue) {
    return queue->start == nullptr;
}

int count(Queue *queue) {
    int qty = 0;

    Node *node = queue->start;

    while (node != nullptr) {
        qty++;

        node = node->next;
    }

    return qty;
}

void enqueue(Queue *queue, int v) {
    Node *node = new Node;

    node->value = v;

    node->next = nullptr;

    if (isEmpty(queue)) {
        queue->start = node;
    } else {
        queue->end->next = node;
    }

    queue->end = node;
}

int dequeue(Queue *queue) {
    int ret;

    if (isEmpty(queue)) {
        cout << "Can't dequeue an empty queue";
    } else {
        Node *node = queue->start;

        ret = node->value;

        queue->start = node->next;

        if (queue->start == nullptr) {
            queue->end = nullptr;
        }

        free(node);
    }

    return ret;
}

void freeQueue(Queue *queue) {
    Node *node = queue->start;

    while (node != nullptr) {
        Node *temp = node->next;

        free(node);

        node = temp;
    }

    free(queue);
}

void generateTicket(Queue *tickets) {
    int ticketValue = isEmpty(tickets) ? 0 : tickets->end->value + 1;

    enqueue(tickets, ticketValue);
}

void resolveTicket(Queue *tickets, Queue *resolvedTickets) {
    int ticket = dequeue(tickets);

    enqueue(resolvedTickets, ticket);
}

void menu(Queue *tickets, Queue *resolvedTickets, bool *loop) {
    while (*loop) {
        cout << "Senhas aguardando atendimento: " << count(tickets) << endl << endl;

        cout << "0 - Sair" << endl;

        cout << "1 - Gerar senha" << endl;

        cout << "2 - Realizar atendimento" << endl;

        int op;

        cin >> op;

        switch (op) {
            case 0: {
                if (!isEmpty(tickets)) {
                    cout << "Tickets queue is not empty" << endl;
                } else {
                    *loop = false;
                }

                break;
            }
            case 1: {
                generateTicket(tickets);

                break;
            }
            case 2: {
                resolveTicket(tickets, resolvedTickets);

                break;
            }
            default: {
                cout << "Invalid option" << endl;

                break;
            }
        }
    }
}

int main() {
    bool loop = true;

    auto tickets = init();

    auto resolvedTickets = init();

    menu(tickets, resolvedTickets, &loop);

    cout << endl << "Senhas atendidas: " + to_string(count(resolvedTickets));

    return 0;
}