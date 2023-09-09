#include <bits/stdc++.h>
#include "Utrip.hpp"
using namespace std;

bool User::check_signup(std::string _email, std::string _username){
    if(_email == email || _username == username)
        return false;
    return true;
}

bool User::check_login(std::string _email, std::string _password){
    if(email == _email && password == _password)
        return true;
    return false;
}

void User::update_wallet(int amount){
    wallet.push_back(wallet.back()+amount);
}

void User::set_reservation(Reserve* reserve){
    reserves.push_back(reserve);
    reserve->print_rooms();
}

void User::print_reservations(){
    bool is_empty = true;
    for(int i=reserves.size()-1; i>= 0; i--){
        if(reserves[i] == NULL)
            continue;
        cout << "id: " << i+1 << ' ';
        reserves[i]->print_all();
        is_empty = true;
    }
    if(is_empty)
        cout << "Empty" << endl;
}

void User::delete_reserve(int reserve_id){
    if(reserve_id > reserves.size())
        throw ImportException(NOT_FOUND);
    if(reserves[reserve_id-1] == NULL)
        throw ImportException(NOT_FOUND);
    update_wallet(reserves[reserve_id-1]->get_cost()/2);
    reserves[reserve_id-1] = NULL;
    
}

void User::check_def_price_filter(bool no_filter, HotelTable &selected){
    if(!(no_filter && price_filter && reserves.size() >= 10)){
        return;
    }
    selected = Default_price::set_filter(selected, reserves);
    cout << "* Results have been filtered by the default price filter." << endl;
}

void User::manual_weights(std::stringstream &sstream){
    string word, active;
    sstream >> word >> word >> active;
    if(word == "active"){
        if(active == "true")
            weight.active = true;
        else{
            weight.active = false;
            return;
        }
    }
    else 
        throw ImportException(BAD_REQUEST);

    Weight _weight;
    for(int i=0; i< 6; i++){
        sstream >> word;
        if(word == "location")
            sstream >> _weight.location;
        else if(word == "cleanliness")
            sstream >> _weight.cleanlines;
        else if(word == "staff")
            sstream >> _weight.staff;
        else if(word == "facilities")
            sstream >> _weight.facilities;
        else if(word == "value_for_money")
            sstream >> _weight.value_for_money;
        else 
            throw ImportException(BAD_REQUEST);
    }

    if(_weight.location<1 || _weight.cleanlines<1 || _weight.staff<1 || _weight.facilities<1
    || _weight.value_for_money<1  || _weight.location>5 || _weight.cleanlines>5
    || _weight.staff>5 || _weight.facilities>5 || _weight.value_for_money>5)
        throw ImportException(BAD_REQUEST);

    weight = _weight;
}

void User::get_manual_weights(){
    if(weight.active){
        cout << fixed << setprecision(2) << "active " << "true" << " location " << trunc(100*weight.location)/100 << " cleanliness "
        << trunc(100*weight.cleanlines)/100 << " staff " << trunc(100*weight.staff)/100 << " facilities "
        << trunc(100*weight.facilities)/100 << " value_for_money " << trunc(100*weight.value_for_money)/100 
        << ' ' << endl;
    }
    else{
        cout << "active " << "false" << endl;
    }
}