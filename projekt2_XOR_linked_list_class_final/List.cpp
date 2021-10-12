#include "List.h"
#include <iostream>

using namespace std;


Node*  List::XOR(uintptr_t node_xor, Node* address) const
{
    return (Node*)(node_xor ^ (uintptr_t)address);
}

List::List()
{
    first = nullptr;
    last = nullptr;
    actual = nullptr;
    actual_prev = nullptr;
    actual_next = nullptr;
}

void List::print_actual() const
{
    if (actual != nullptr)
    {
        cout << actual->value << endl;
    }
    else
    {
        cout << "NULL\n";
    }
}

void List::next()
{
    if (first != last && first != nullptr) //funckja coœ robi tylko gdy lista ma wiêcej ni¿ jeden element
    {
        if (actual == last)
        {
            actual = first;
            actual_prev = nullptr;
            actual_next = XOR(actual->nodes_xor, nullptr); //w tym przypadku adres actual_next jest po prostu wartoœci¹ nodes_xor actuala
        }
        else
        {
            Node* temp = actual;
            actual = XOR(actual->nodes_xor, actual_prev);
            actual_prev = temp;
            actual_next = XOR(actual->nodes_xor, actual_prev);
        }
    }
}

void List::prev()
{
    if (first != last && first != nullptr) //funKCja coœ robi tylko gdy lista ma wiêcej ni¿ jeden element
    {
        if (actual == first)
        {
            actual = last;
            actual_next = nullptr;
            actual_prev = XOR(actual->nodes_xor, nullptr);
        }
        else
        {
            Node* temp = actual;
            actual = XOR(actual->nodes_xor, actual_next); //adres poprzedniego elem. uzyskujemy xoruj¹c node_xor actuala z adr.nastêpnika actuala
            actual_next = temp;
            actual_prev = XOR(actual->nodes_xor, actual_next);
        }
    }
}

void List::add_beg(int n)
{
    Node* new_node = new Node;
    new_node->value = n;
    new_node->nodes_xor = (uintptr_t)first;
    if (first != nullptr) //lista nie by³a pusta
    {
        first->nodes_xor = (uintptr_t)XOR(first->nodes_xor, new_node);
    }
    else //lista by³a pusta, wiêc przypisz dodawany element do actual i do last
    {
        actual = new_node;
        last = new_node;
    }

    if (actual == first) //ustawiæ actual_prev na prawid³ow¹ wartoœæ
    {
        actual_prev = new_node;
    }
    first = new_node;
}

void List::add_end(int n)
{
    Node* new_node = new Node;
    new_node->value = n;
    new_node->nodes_xor = (uintptr_t)last;
    if (last != nullptr) //lista nie by³a pusta
    {
        last->nodes_xor = (uintptr_t)XOR(last->nodes_xor, new_node);
    }
    else //lista by³a pusta, wiêc przypisz dodawany element do actual i do first
    {
        actual = new_node;
        first = new_node;
    }

    if (actual == last) //ustawiæ actual_next na prawid³ow¹ wartoœæ
    {
        actual_next = new_node;
    }
    last = new_node;
}

void List::add_act(int n)
{
    if (actual == first) //actual jest pierwszym elementem (lub lista jest pusta)
    {
        add_beg(n);
    }
    else //actual nie jest pierwszym elementem
    {
        Node* new_node = new Node;
        new_node->value = n;
        new_node->nodes_xor = (uintptr_t)XOR((uintptr_t)actual_prev, actual);
        uintptr_t temp = (uintptr_t)XOR(actual_prev->nodes_xor, actual); //adres poprzednika poprzednika actuala
        actual_prev->nodes_xor = (uintptr_t)XOR(temp, new_node);
        actual->nodes_xor = (uintptr_t)XOR((uintptr_t)new_node, actual_next);
        actual_prev = new_node;
    }
}

void List::del_beg()
{
    if (first == last && first != nullptr) //lista ma jeden element
    {
        last = nullptr;
        first = nullptr;
        actual = nullptr;
        delete first;
    }
    else if (first != nullptr) //gdy lista ma wiêcej ni¿ jeden element
    {
        if (actual_prev == first) //jeœli actual_prev by³ pierwszym elementem
        {
            actual_prev = nullptr;
        }
        else if (actual == first) //jeœli actual by³ pierwszym elementem
        {
            prev(); //ustawia actual na ostatni element
        }

        Node* ptr = XOR(first->nodes_xor, nullptr); //wskaŸnik na drugi wêze³
        Node* temp = first;
        first = ptr;
        first->nodes_xor = (uintptr_t)XOR(first->nodes_xor, temp);
        temp = nullptr;
        delete temp;
    }
}

void List::del_end()
{
    if (first == last && first != nullptr) //lista ma jeden element
    {
        last = nullptr;
        first = nullptr;
        actual = nullptr;
        delete last;
    }
    else if (last != nullptr) //gdy lista ma wiêcej ni¿ jeden element
    {
        if (actual_next == last) //jeœli actual_next by³ ostatnim elementem
        {
            actual_next = nullptr;
        }
        else if (actual == last) //jeœli actual by³ ostatnim elementem
        {
            prev(); //przesunie na poprzedni element
            actual_next = nullptr;
        }

        Node* ptr = XOR(last->nodes_xor, nullptr); //wskaŸnik na przedostatni wêze³
        Node* temp = last;
        last = ptr;
        last->nodes_xor = (uintptr_t)XOR(last->nodes_xor, temp);
        temp = nullptr;
        delete temp;
    }
}

void List::delete_node(Node* n)
{
    if (n == first) //n jest pierwszym elementem (lub lista jest pusta i n jest nullptr)
    {
        del_beg();
    }
    else if (n == last) //n jest ostatnim elementem
    {
        del_end();
    }
    else //n jest którymœ ze œrodkowych elementów
    {
        if (actual_next == n)
        {
            actual_next = XOR(actual_next->nodes_xor, actual);
        }
        else if (actual_prev == n)
        {
            actual_prev = XOR(actual_prev->nodes_xor, actual);
        }
        else if (actual == n)
        {
            Node* temp = actual_next;
            prev();
            actual_next = temp;
        }

        Node* left = nullptr; //element poprzedzaj¹cy bie¿acy
        Node* element = first; //element bie¿¹cy
        Node* right = XOR(element->nodes_xor, left); //element po elemencie bie¿¹cym
        Node* temp; //pomocnicza zmienna przy przechodzeniu
        while (element != n) //przechodzi po liœcie a¿ natrafi na element n
        {
            temp = right;
            left = element;
            element = right;
            right = XOR(element->nodes_xor, left);
        }

        if (element == n)
        {
            //ustawiæ odpowiednio xor wêz³a poprzedzaj¹cego usuwany
            uintptr_t left_address = (uintptr_t)XOR(left->nodes_xor, element);
            left->nodes_xor = (uintptr_t)XOR(left_address, right);

            //ustawiæ odpowiednio xor wêz³a który jest po usuwanym
            uintptr_t right_address = (uintptr_t)XOR(right->nodes_xor, element);
            right->nodes_xor = (uintptr_t)XOR(right_address, left);

            //usuñ n
            element = nullptr;
            delete n;
        }
    }
}

void List::del_val(int n)
{
    Node* left = nullptr;
    Node* right = first;
    Node* temp; //pomocnicza zmienna przy zmienianiu left i right
    while (right != nullptr)
    {
        if (right->value == n)
        {
            Node* temp2 = right;
            right = XOR(right->nodes_xor, left);
            delete_node(temp2);
        }
        else
        {
            temp = right;
            right = XOR(right->nodes_xor, left);
            left = temp;
        }
    }
}

void List::print_forward() const
{
    if (first == nullptr)
    {
        cout << "NULL\n";
    }
    else
    {
        Node* left = nullptr;
        Node* right = first;
        Node* temp; //pomocnicza zmienna przy zmienianiu left i right
        while (right != nullptr)
        {
            cout << right->value << " ";
            temp = right;
            right = XOR(right->nodes_xor, left);
            left = temp;
        }
        cout << endl;
    }
}

void List::print_backward() const
{
    if (last == nullptr)
    {
        cout << "NULL\n";
    }
    else
    {
        Node* right = nullptr;
        Node* left = last;
        Node* temp; //pomocnicza zmienna przy zmienianiu left i right
        while (left != nullptr)
        {
            cout << left->value << " ";
            temp = left;
            left = XOR(left->nodes_xor, right);
            right = temp;
        }
        cout << endl;
    }
}