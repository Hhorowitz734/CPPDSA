#include <stdio.h>
#include <iostream>
#include "/opt/homebrew/Cellar/raylib/4.5.0/include/raylib.h"
#include <vector>
#include <random>

//cd "/Users/bhorowitz/Documents/CPLUSPLUS/DSA/" && g++ llvisualizer.cpp -o llvisualizer -I/opt/homebrew/Cellar/raylib/4.5.0/include -L/opt/homebrew/lib -lraylib -std=c++11 && "/Users/bhorowitz/Documents/CPLUSPLUS/DSA/llvisualizer"


class Node;

class LinkedList;

class Button;

class AllObjects{

    public:
        //Storage for all objects in use
        static std::vector<LinkedList*> LinkedLists;
        static std::vector<Node*> Nodes;
        static std::vector<Button*> Buttons;
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

        int radius = 35;

        Node* next = nullptr;

        bool inLinkedList = false; //Keeps track of whether node is in a linked list
        LinkedList* nodeLinkedList = nullptr; //Stores the linked list that the node is a member of 

        //Clickbox for a given node
        Vector2 nodeCenter = { static_cast<float>(positionX), static_cast<float>(positionY) };

        Node(int value, int positionX, int positionY): value(value), positionX(positionX), positionY(positionY) {
            AllObjects::Nodes.push_back(this);
        };
    
    void display(){
        //Displays the node on the screen
        DrawCircleLines(positionX, positionY, radius, WHITE);
        std::string numStr = std::to_string(value);
        DrawText(numStr.c_str(), positionX - 10, positionY - 10, 25, WHITE);
        if (next){
            DrawLine(positionX + radius, positionY, positionX + (radius * 2), positionY, WHITE);
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

class Button{
    public:
        
        //Coordinates
        int positionX;
        int positionY;

        //Width, height, detection box
        int width;
        int height;
        Rectangle buttonArea = {static_cast<float>(positionX), static_cast<float>(positionY), static_cast<float>(width), static_cast<float>(height)};

        std::string text;


        Button(int positionX, int positionY, int width, int height, std::string text): positionX(positionX), positionY(positionY), width(width), height(height), text(text) {
            AllObjects::Buttons.push_back(this);
        };
    
    void display(){
        DrawRectangleLines(positionX, positionY, width, height, WHITE);
        DrawText(text.c_str(), positionX + 5, positionY, 25, WHITE);
    }

    virtual void buttonAction(){
        std::cout << "You've clicked on a useless button.\n\n\n\n\n";
        //If you're getting this, make sure you added "override" to the actual action you're trying to do
    }

};

class NewNode : public Button{
    public:
        NewNode(int positionX, int positionY, int width, int height): Button(positionX, positionY, width, height, "New Node"){
            display();
        };

    void buttonAction() override{
        //Creates a new node at a random point in the screen

        std::random_device rd;  // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator

        //Random range for node position in X
        std::uniform_int_distribution<> distrX(30, 770); 
        int startingX = distrX(eng);

        //Random range for node position in Y
        std::uniform_int_distribution<> distrY(30, 570); 
        int startingY = distrY(eng);

        //Random range for node value
        std::uniform_int_distribution<> distrValue(1, 99); 
        int nodeValue = distrValue(eng);

        //Creates the node
        Node* newNode = new Node(nodeValue, startingX, startingY);
    }


    //Write a method here to create a new node
};

//Static member variables of AllObjects
std::vector<LinkedList*> AllObjects::LinkedLists;
std::vector<Node*> AllObjects::Nodes;
std::vector<Button*> AllObjects::Buttons;

int main()
{
    // Initialize the window and set the frame rate
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Linked List Visualizer");
    SetTargetFPS(60);
    ClearBackground(BLACK);

    //Creates buttons for screen
    NewNode newnode(750, 570, 50, 30);


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

            //Executes if a node is pressed
            if (CheckCollisionPointCircle(GetMousePosition(), node->nodeCenter, static_cast<float>(node->radius)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                std::cout << "Oh my! Node " << node->value << " was touched!!!\n\n\n\n\n";
            }
        }

        //Displays all buttons
        for (Button* button : AllObjects::Buttons){
            button->display();

            //Executes if a button is pressed
            if (CheckCollisionPointRec(GetMousePosition(), button->buttonArea) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                std::cout << button->text << " button has been pressed.\n\n\n\n\n";
                button->buttonAction();
            }
        }


        EndDrawing();
        
    }

    // Clean up and exit
    CloseWindow();
    return 0;
}
