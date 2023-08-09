#include <stdio.h>
#include <iostream>
#include "/opt/homebrew/Cellar/raylib/4.5.0/include/raylib.h"
#include <vector>

//cd "/Users/bhorowitz/Documents/CPLUSPLUS/DSA/" && g++ llvisualizer.cpp -o llvisualizer -I/opt/homebrew/Cellar/raylib/4.5.0/include -L/opt/homebrew/lib -lraylib -std=c++11 && "/Users/bhorowitz/Documents/CPLUSPLUS/DSA/llvisualizer"


class Node;

class LinkedList;

class AllObjects{

    public:
        //Storage for all objects in use
        static std::vector<LinkedList*> LinkedLists;
        static std::vector<Node*> Nodes;
};

class LinkedList{

    public:
        Node* head = nullptr;

        LinkedList(Node* head): head(head) {};
    
    void printList();
};


class Node {
    //Defines a class for nodes
    public:
        int value = 5;

        int positionX = 400;
        int positionY = 300;

        Node* next = nullptr;

        bool inLinkedList = false; //Keeps track of whether node is in a linked list
        LinkedList* nodeLinkedList = nullptr; //Stores the linked list that the node is a member of 

        Node(int value, int positionX, int positionY): value(value), positionX(positionX), positionY(positionY) {
            AllObjects::Nodes.push_back(this);
        };
    
    void display(){
        //Displays the node on the screen
        DrawCircleLines(positionX, positionY, 35, WHITE);
        std::string numStr = std::to_string(value);
        DrawText(numStr.c_str(), positionX - 10, positionY - 10, 25, WHITE);
        if (next){
            DrawLine(positionX + 35, positionY, positionX + 70, positionY, WHITE);
        }
    }

    void attach(Node* next_node){
        //Attaches a new node as the next node to the current node
        next = next_node;
        display();
        if (!inLinkedList){
            nodeLinkedList = new LinkedList(this); //Creates a new linked list where this node is the head
            AllObjects::LinkedLists.push_back(nodeLinkedList);
        } 
        inLinkedList = true;
        next->inLinkedList = true;
    }

    void detach(){
        //Detaches all following nodes from the linked list
        next->nodeLinkedList = new LinkedList(next); //Creates a new linked list for the next node 
        next = nullptr;
        DrawLine(positionX + 35, positionY, positionX + 70, positionY, BLACK);
    }

};

void LinkedList::printList(){
    Node* curr = head;
    while (curr){
        std::cout << curr->value << '\n';
        curr = curr->next;  // Progress to the next node
    }
}

//Static member variables of AllObjects
std::vector<LinkedList*> AllObjects::LinkedLists;
std::vector<Node*> AllObjects::Nodes;

int main()
{
    // Initialize the window and set the frame rate
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Linked List Visualizer");
    SetTargetFPS(60);
    ClearBackground(BLACK);


    //Node commands
    Node test(5, 400, 300);
    Node test2(6, 505, 300);
    Node test3(7, 610, 300);
    Node test4(8, 715, 300);
    test.attach(&test2);
    test3.attach(&test4);

    // Main game loop
    while (!WindowShouldClose())
    {


        // Clear the screen
        BeginDrawing();

        //Displays all existing nodes
        for (Node* node : AllObjects::Nodes){
            node->display();
        }

        EndDrawing();
    }

    // Clean up and exit
    CloseWindow();
    return 0;
}
