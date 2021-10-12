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
    if (first != last && first != nullptr) //funckja co� robi tylko gdy lista ma wi�cej ni� jeden element
    {
        if (actual == last)
        {
            actual = first;
            actual_prev = nullptr;
            actual_next = XOR(actual->nodes_xor, nullptr); //w tym przypadku adres actual_next jest po prostu warto�ci� nodes_xor actuala
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
    if (first != last && first != nullptr) //funKCja co� robi tylko gdy lista ma wi�cej ni� jeden element
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
            actual = XOR(actual->nodes_xor, actual_next); //adres poprzedniego elem. uzyskujemy xoruj�c node_xor actuala z adr.nast�pnika actuala
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
    if (first != nullptr) //lista nie by�a pusta
    {
        first->nodes_xor = (uintptr_t)XOR(first->nodes_xor, new_node);
    }
    else //lista by�a pusta, wi�c przypisz dodawany element do actual i do last
    {
        actual = new_node;
        last = new_node;
    }

    if (actual == first) //ustawi� actual_prev na prawid�ow� warto��
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
    if (last != nullptr) //lista nie by�a pusta
    {
        last->nodes_xor = (uintptr_t)XOR(last->nodes_xor, new_node);
    }
    else //lista by�a pusta, wi�c przypisz dodawany element do actual i do first
    {
        actual = new_node;
        first = new_node;
    }

    if (actual == last) //ustawi� actual_next na prawid�ow� warto��
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
    else if (first != nullptr) //gdy lista ma wi�cej ni� jeden element
    {
        if (actual_prev == first) //je�li actual_prev by� pierwszym elementem
        {
            actual_prev = nullptr;
        }
        else if (actual == first) //je�li actual by� pierwszym elementem
        {
            prev(); //ustawia actual na ostatni element
        }

        Node* ptr = XOR(first->nodes_xor, nullptr); //wska�nik na drugi w�ze�
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
    else if (last != nullptr) //gdy lista ma wi�cej ni� jeden element
    {
        if (actual_next == last) //je�li actual_next by� ostatnim elementem
        {
            actual_next = nullptr;
        }
        else if (actual == last) //je�li actual by� ostatnim elementem
        {
            prev(); //przesunie na poprzedni element
            actual_next = nullptr;
        }

        Node* ptr = XOR(last->nodes_xor, nullptr); //wska�nik na przedostatni w�ze�
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
    else //n jest kt�rym� ze �rodkowych element�w
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

        Node* left = nullptr; //element poprzedzaj�cy bie�acy
        Node* element = first; //element bie��cy
        Node* right = XOR(element->nodes_xor, left); //element po elemencie bie��cym
        Node* temp; //pomocnicza zmienna przy przechodzeniu
        while (element != n) //przechodzi po li�cie a� natrafi na element n
        {
            temp = right;
            left = element;
            element = right;
            right = XOR(element->nodes_xor, left);
        }

        if (element == n)
        {
            //ustawi� odpowiednio xor w�z�a poprzedzaj�cego usuwany
            uintptr_t left_address = (uintptr_t)XOR(left->nodes_xor, element);
            left->nodes_xor = (uintptr_t)XOR(left_address, right);

            //ustawi� odpowiednio xor w�z�a kt�ry jest po usuwanym
            uintptr_t right_address = (uintptr_t)XOR(right->nodes_xor, element);
            right->nodes_xor = (uintptr_t)XOR(right_address, left);

            //usu� n
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