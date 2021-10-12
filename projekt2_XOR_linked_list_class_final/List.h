#pragma once
#include <iostream>

struct Node
{
    int value = 0;
    uintptr_t nodes_xor = NULL; //XOR z adresów poprzedniego i nastêpnego elementu
};

class List
{
private:
    Node* actual;
    Node* actual_prev; //poprzednik elementu actual
    Node* actual_next; //nastêpnik elementu actual
    Node* first;
    Node* last;

    Node* XOR(uintptr_t node_xor, Node* address) const; //zwraca wskaŸnik na wêze³ który jest wynikiem xorowania

public:
    List();
    Node* get_actual() { return actual; }
    void print_actual() const; //drukuje wartoœæ aktualnego elementu
    void next(); //przestawia wskaŸnik actual na nastepny element
    void prev(); //przestawia wskaŸnik actual na poprzedni element
    void add_beg(int n); //dodaje wêze³ o wartoœci n na pocz¹tek listy
    void add_end(int n); //dodaje wêze³ o wartoœci n na koniec listy
    void add_act(int n); //dodaje wêze³ o wartoœci n jako poprzednik actual
    void del_beg(); //usuwa z listy pierwszy wêze³
    void del_end(); //usuwa z listy ostatni wêze³
    void delete_node(Node* n); //usuwa z listy dany wêze³
    void del_val(int n); //usuwa z listy wszystkie wêz³y o wartoœci n
    void print_forward() const; //drukuje zawartoœæ listy od pierwszego do ostatniego elementu
    void print_backward() const; //drukuje zawartoœæ listy od ostatniego do pierwszego elementu
};

