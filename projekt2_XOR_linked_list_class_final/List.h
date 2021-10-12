#pragma once
#include <iostream>

struct Node
{
    int value = 0;
    uintptr_t nodes_xor = NULL; //XOR z adres�w poprzedniego i nast�pnego elementu
};

class List
{
private:
    Node* actual;
    Node* actual_prev; //poprzednik elementu actual
    Node* actual_next; //nast�pnik elementu actual
    Node* first;
    Node* last;

    Node* XOR(uintptr_t node_xor, Node* address) const; //zwraca wska�nik na w�ze� kt�ry jest wynikiem xorowania

public:
    List();
    Node* get_actual() { return actual; }
    void print_actual() const; //drukuje warto�� aktualnego elementu
    void next(); //przestawia wska�nik actual na nastepny element
    void prev(); //przestawia wska�nik actual na poprzedni element
    void add_beg(int n); //dodaje w�ze� o warto�ci n na pocz�tek listy
    void add_end(int n); //dodaje w�ze� o warto�ci n na koniec listy
    void add_act(int n); //dodaje w�ze� o warto�ci n jako poprzednik actual
    void del_beg(); //usuwa z listy pierwszy w�ze�
    void del_end(); //usuwa z listy ostatni w�ze�
    void delete_node(Node* n); //usuwa z listy dany w�ze�
    void del_val(int n); //usuwa z listy wszystkie w�z�y o warto�ci n
    void print_forward() const; //drukuje zawarto�� listy od pierwszego do ostatniego elementu
    void print_backward() const; //drukuje zawarto�� listy od ostatniego do pierwszego elementu
};

