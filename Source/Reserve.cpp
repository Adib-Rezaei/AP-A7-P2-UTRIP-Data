#include <bits/stdc++.h>
#include "Utrip.hpp"
using namespace std;

void Reserve::print_rooms(){
    for(int i=0; i< rooms.size(); i++){
        cout << rooms[i]->get_name();
        if(i != rooms.size()-1)
            cout << ' ';
    }
    cout << ' ' << endl;
}

void Reserve::print_all(){
    cout << "hotel: " << hotel << " room: " << which_room(rooms[0]->get_name()[0])
        << " quantity: " << rooms.size() << " cost: " << rooms[0]->get_price()*rooms.size()
        << " check_in " << check_in << " check_out " << check_out << endl;
}

string Reserve::which_room(char character){
    switch(character){
        case 's':
            return "standard";
        case 'd':
            return "deluxe";
        case 'l':
            return "luxury";
        case 'p':
            return "premium";
        default:
            return "";
    }
}
