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

        //Stores pointer to the node that had its color set to red last (to ensure only one selected at a time)
        static Node* lastSelectedNode;

        //Stores current "mode" for the visualizer
        //Current modes include:
        //1) Attach - Next node that is pressed is attached to the previous node pressed
        static int mode;
};

class LinkedList{

    public:
        Node* head = nullptr;

        LinkedList(Node* head): head(head) {};
    

    void colorList(Color listcolor);
    void printList();
};


class Node {
    //Defines a class for nodes
    public:

        //Node's value
        int value = 5;

        //Node's coordinates
        int positionX = 400;
        int positionY = 300;

        //Node size
        int radius = 35;

        //Next node
        Node* next = nullptr;
        
        //Node linked list operations
        bool inLinkedList = false; //Keeps track of whether node is in a linked list
        LinkedList* nodeLinkedList = nullptr; //Stores the linked list that the node is a member of 

        //Clickbox for a given node
        Vector2 nodeCenter = { static_cast<float>(positionX), static_cast<float>(positionY) };

        //Node color (for when node is clicked etc)
        Color nodeColor = WHITE;

        Node(int value, int positionX, int positionY): value(value), positionX(positionX), positionY(positionY) {
            AllObjects::Nodes.push_back(this);
        };
    
    void display(){
        //Displays the node on the screen
        DrawCircleLines(positionX, positionY, radius, nodeColor);
        std::string numStr = std::to_string(value);
        DrawText(numStr.c_str(), positionX - 10, positionY - 10, 25, nodeColor);
        if (next){
            DrawLine(positionX + radius, positionY, next->positionX - (radius), next->positionY, WHITE);
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
        DrawLine(positionX + radius, positionY, next->positionX - (radius), next->positionY, BLACK);
        next = nullptr;
    }

};


void LinkedList::colorList(Color listcolor){
    //Colors all nodes in a linked list to a specific color
    Node* curr = head;

    while (curr){
        curr->nodeColor = listcolor;
        curr = curr->next;
    }

}

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

};

class AttachNode : public Button{
    public:
        AttachNode(int positionX, int positionY, int width, int height): Button(positionX, positionY, width, height, "Attach"){
            display();
        };
    
    void buttonAction() override{   

        //Sets the mode to attach mode
        AllObjects::mode = 1;

    }
};

class UnlinkNode : public Button{
    public:
        UnlinkNode(int positionX, int positionY, int width, int height): Button(positionX, positionY, width, height, "Unlink"){
            display();
        };
    
    void buttonAction() override{ //THIS CODE HAS A SEGFAULT SOMEWHERE IN THERE

        if (AllObjects::lastSelectedNode->next){

            //Detaches nodes from last selected node
            AllObjects::lastSelectedNode->detach();
        
        }

        if (AllObjects::lastSelectedNode){
            std::cout << "Unlinking node " << AllObjects::lastSelectedNode->value << " from the tribe!\n\n\n\n\n";

            //Iterates over all nodes and detaches any that are linked to ours
            for (Node* node : AllObjects::Nodes){
                if (node->next == AllObjects::lastSelectedNode){
                    node->detach();
                }
            }
        }

    }
    
};

class ColorLists : public Button{

    public:
        ColorLists(int positionX, int positionY, int width, int height): Button(positionX, positionY, width, height, "Color Lists"){
            display();
        };
    
    void buttonAction() override {
        
        for (LinkedList* linkedlist : AllObjects::LinkedLists){

            //Creates a random number generator
            std::random_device rd;  // obtain a random number from hardware
            std::mt19937 eng(rd()); // seed the generator

            //Generates random numbers for a color
            std::uniform_int_distribution<> distrR(0, 255); 
            int colorR = distrR(eng);
            std::uniform_int_distribution<> distrG(0, 255); 
            int colorG = distrG(eng);
            std::uniform_int_distribution<> distrB(0, 255); 
            int colorB = distrB(eng);

            Color customListColor = {static_cast<unsigned char>(colorR), static_cast<unsigned char>(colorG), static_cast<unsigned char>(colorB), 255};


            linkedlist->colorList(customListColor);

        }
    }
};

//Static member variables of AllObjects
std::vector<LinkedList*> AllObjects::LinkedLists;
std::vector<Node*> AllObjects::Nodes;
std::vector<Button*> AllObjects::Buttons;
Node* AllObjects::lastSelectedNode = nullptr;
int AllObjects::mode = 0;


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
    AttachNode attachnode(650, 570, 100, 30);
    UnlinkNode unlinknode(550, 570, 100, 30);
    ColorLists colorlists(400, 570, 150, 30);

    //DO ANY NODE TESTING HERE

    // Main game loop
    while (!WindowShouldClose())
    {


        // Clear the screen
        BeginDrawing();
        ClearBackground(BLACK);

        //Displays all existing nodes
        for (Node* node : AllObjects::Nodes){
            node->display();

            //Executes if a node is pressed
            if (CheckCollisionPointCircle(GetMousePosition(), node->nodeCenter, static_cast<float>(node->radius)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                std::cout << "Oh my! Node " << node->value << " was touched!!!\n\n\n\n\n";
                
                //Executes action on node based on "mode" (see AllObjects::mode comments at top)
                switch(AllObjects::mode){
                    case 0: //Default case
                        node->nodeColor = RED;
                        if (AllObjects::lastSelectedNode){
                            AllObjects::lastSelectedNode->nodeColor = WHITE;
                        }
                        AllObjects::lastSelectedNode = node;
                        break;
                    case 1: //Attach case
                        if (AllObjects::lastSelectedNode){
                            AllObjects::lastSelectedNode->attach(node);
                            AllObjects::lastSelectedNode->nodeColor = WHITE;
                            std::cout << "Node " << AllObjects::lastSelectedNode->value << " has been attached to node " << node->value << ".\n\n\n\n\n";
                        }
                        AllObjects::mode = 0;
                        break;
                }

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
