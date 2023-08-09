#include <stdio.h>
#include <iostream>
#include "/opt/homebrew/Cellar/raylib/4.5.0/include/raylib.h"

//cd "/Users/bhorowitz/Documents/CPLUSPLUS/DSA/" && g++ llvisualizer.cpp -o llvisualizer -I/opt/homebrew/Cellar/raylib/4.5.0/include -L/opt/homebrew/lib -lraylib -std=c++11 && "/Users/bhorowitz/Documents/CPLUSPLUS/DSA/llvisualizer"

class Node;

class LinkedList{
    public:
        Node* head = nullptr;

        LinkedList(Node* head): head(head) {};
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

        Node(int value, int positionX, int positionY): value(value), positionX(positionX), positionY(positionY) {};
    
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
        inLinkedList = true;
        next->inLinkedList = true;
        display();
        if (!inLinkedList){
            nodeLinkedList = new LinkedList(this); //Creates a new linked list where this node is the head
        } 
    }

};




int main()
{
    // Initialize the window and set the frame rate
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Linked List Visualizer");
    SetTargetFPS(60);
    ClearBackground(BLACK);

    //Node
    Node test(5, 400, 300);
    Node test2(6, 505, 300);
    test.attach(&test2);


    // Main game loop
    while (!WindowShouldClose())
    {


        // Clear the screen
        BeginDrawing();
        test.display();
        test2.display();

        EndDrawing();
    }

    // Clean up and exit
    CloseWindow();
    return 0;
}