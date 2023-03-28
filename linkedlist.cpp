#include <stdio.h>
#include <iostream>
#include <exception>

using namespace std;

class Node{
        public:
            int val; //Stores node value
            Node* next; //Pointer to next node
        
        int get_value(){ //Returns value of node
            return val;
        }
    };

    class LinkedList{
        public:
            Node* first_node = nullptr; //Pointer to first node in LL
            Node* last_node = nullptr; //Pointer to last node in LL
        
            Node* append_node(int val){ //Adds a node to the LL and returns it
                Node* newnode = new Node();
                newnode->val = val;
                if(last_node == nullptr){ //Handles LL being empty
                    first_node = newnode;
                    last_node = newnode;
                } else {
                    last_node->next = newnode; //Adds node to end of list
                    last_node = newnode;
                }
                return newnode;
            }

            Node* remove_node(int index){ //Removes the node at a given index and returns consecutive node
                if (index < 0){ //Catches invalid indices
                    std::cout << "Enter a valid indice.";
                    return nullptr;
                }
                try { //Removes node from list (Attaches previous node pointer to successive node)
                    Node* tempnode = first_node;
                    for (int i = 0; i < index; i++){
                        if (i + 1 == index){
                            tempnode->next = tempnode->next->next;
                        }
                        tempnode = tempnode->next;
                    }
                    return tempnode->next; //Returns successive node
                } catch (const exception& e){    //Catches case that index > len of the LL
                    std::cout << "Index not in list.\n";
                    std::cout << e.what() << '\n';
                    return nullptr;
                }
            }

            Node* view_node(int index){ //Returns a node at a given index
                if (index < 0){ //Catches invalid indices
                    std::cout << "Enter a valid indice.";
                    return nullptr;
                }
                try { //Iterates through list until it reaches node
                    Node* tempnode = first_node;
                    for (int i = 0; i < index; i++){
                        tempnode = tempnode->next;
                    }
                    return tempnode; //Returns node
                } catch (const exception& e){    //Catches case that index > len of the LL
                    std::cout << "Index not in list.\n";
                    std::cout << e.what() << '\n';
                    return nullptr;
                }
            }
    };

int main(){

            LinkedList linkedlist;
            linkedlist.append_node(17);
            linkedlist.append_node(10);
            linkedlist.append_node(5);
            std::cout << linkedlist.view_node(2)->get_value() << '\n';

    return 0;
}

