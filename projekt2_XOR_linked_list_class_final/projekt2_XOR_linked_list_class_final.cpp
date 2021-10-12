#include <iostream>
#include <string>
#include "List.h"
using namespace std;



int main()
{
    List list;
    string option;
    while (cin >> option) //pêtla g³ówna
    {
        if (option == "ACTUAL")
        {
            list.print_actual();
        }
        else if (option == "NEXT")
        {
            list.next();
            list.print_actual();
        }
        else if (option == "PREV")
        {
            list.prev();
            list.print_actual();
        }
        else if (option == "ADD_BEG")
        {
            int n;
            cin >> n;
            list.add_beg(n);
        }
        else if (option == "ADD_END")
        {
            int n;
            cin >> n;
            list.add_end(n);
        }
        else if (option == "ADD_ACT")
        {
            int n;
            cin >> n;
            list.add_act(n);
        }
        else if (option == "DEL_BEG")
        {
            list.del_beg();
        }
        else if (option == "DEL_END")
        {
            list.del_end();
        }
        else if (option == "DEL_VAL")
        {
            int n;
            cin >> n;
            list.del_val(n);
        }
        else if (option == "DEL_ACT")
        {
            list.delete_node(list.get_actual());
        }
        else if (option == "PRINT_FORWARD")
        {
            list.print_forward();
        }
        else if (option == "PRINT_BACKWARD")
        {
            list.print_backward();
        }
    }

    return 0;
}