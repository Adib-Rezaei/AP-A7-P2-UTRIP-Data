#include <bits/stdc++.h>
#include "Utrip.hpp"
#include "Sort.hpp"
using namespace std;

void Utrip::post_command(stringstream &sstream){
    string word;
    sstream >> word;
    
    if(word == "signup"){
        signup(sstream);
    }
    else if(word == "login"){
        login(sstream);
    }
    else if(word == "logout"){
        logout(sstream);
    }
    else if(word == "wallet"){
        wallet(sstream);
    }
    else if(word == "filters"){
        filters(sstream);
    }
    else if(word == "reserves"){
        reserve(sstream);
    }
    else if(word == "comments"){
        comments(sstream);
    }
    else if(word == "ratings"){
        ratings(sstream);
    }
    else if(word == "default_price_filter"){
        def_price_filter(sstream);
    }
    else if(word == "sort"){
        post_sort(sstream);
    }
    else if(word == "manual_weights"){
        manual_weights(sstream);
    }
    else{
        throw ImportException(BAD_REQUEST);
    }
}

void Utrip::get_command(stringstream &sstream){
    string word;
    sstream >> word;
    
    if(word == "wallet"){
        get_wallet(sstream);
    }
    else if(word == "hotels"){
        get_hotels(sstream);
    }
    else if(word == "reserves"){
        current->print_reservations();
    }
    else if(word == "comments"){
        get_comments(sstream);
    }
    else if(word == "ratings"){
        get_ratings(sstream);
    }
    else if(word == "manual_weights"){
        get_manual_weights();
    }
    else{
        throw ImportException(BAD_REQUEST);
    }

}

void Utrip::delete_command(stringstream &sstream){
    string word;
    sstream >> word;
    
    if(word == "filters"){
        for(auto &filter : Filters)
            filter = NULL;
        cout << "OK" << endl;
    }else if(word == "reserves"){
        delete_reserve(sstream);
    }
    else{
        throw ImportException(BAD_REQUEST);
    }
}

void Utrip::signup(stringstream &sstream){
    string word, word2, email, username, password;
    sstream >> word;

    for(int i=0; i< 3; i++){
        sstream >> word >> word2;
        if(word == "email")
            email = word2;
        else if(word == "username")
            username = word2;
        else if(word == "password")
            password = word2;
        else
            throw ImportException(NOT_FOUND);
    }
    for(auto &user : users)
        if(!user->check_signup(email, username))
            throw ImportException(BAD_REQUEST);


    User* user = new User(email, username, hashing(password));
    users.push_back(user);
    current = user;
    cout << "OK" << endl;
}

string Utrip::hashing(std::string password){
    hash<string> myhash;
    return to_string(myhash(password));
}

void Utrip::login(stringstream &sstream){
    string word, email, password;
    sstream >> word;

    for(int i=0; i< 2; i++){
        sstream >> word;
        if(word == "email")
            sstream >> email;
        else if(word == "password")
            sstream >> password;
        else 
            throw ImportException(BAD_REQUEST);
    }
    for(auto &user : users){
        if(user->check_login(email, hashing(password))){
            current = user;
            cout << "OK" << endl;
            return;
        }
    }
    throw ImportException(BAD_REQUEST);
}

void Utrip::logout(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);
    current = NULL;
    for(auto &_filter : Filters){
        if(_filter != NULL)
            delete _filter;
        _filter = NULL;
        sort = NULL;
    }
    cout << "OK" << endl;
}

void Utrip::wallet(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);
    string word;
    sstream >> word >> word >> word;
    if(stoi(word) <= 0)
        throw ImportException(BAD_REQUEST);
    
    current->update_wallet(stoi(word));
    cout << "OK" << endl;
}

void Utrip::get_wallet(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);
    string count;
    sstream >> count >> count >> count;
    int size = current->get_wallet().size();
    for(int i=1; i<= stoi(count); i++){
        if(size - i < 0)
            break;
        cout << current->get_wallet()[size - i] << endl;
    }
}

void Utrip::get_hotels(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);

    if(sstream.eof()){
        filter_hotels();
        return;
    }

    string word;
    sstream >> word >> word >> word;
    for(auto &hotel : hotels){
        if(word == hotel.get_uid()){
            hotel.print();
            return;
        }
    }
    throw ImportException(NOT_FOUND);
}

void Utrip::filters(stringstream &sstream){
    string word;
    sstream >> word >> word;
    if(word == "city"){
        city_filter(sstream);
    }
    else if(word == "min_star" || word == "max_star"){
        string command = sstream.str();
        stringstream ss(command.substr(command.find('?')+2));
        star_filter(ss);
    }
    else if(word == "min_price" || word == "max_price"){
        string command = sstream.str();
        stringstream ss(command.substr(command.find('?')+2));
        cost_filter(ss);
    }
    else if(word == "type" || word == "quantity" || word == "chech_in" || word == "check_out"){
        string command = sstream.str();
        stringstream ss(command.substr(command.find('?')+2));
        specific_filter(ss);
    }
    else 
        throw ImportException(BAD_REQUEST);
}

void Utrip::filter_hotels(){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);
    
    HotelTable selected = hotels;
    bool is_all_null = true;
    for(int i=0; i< Filters.size(); i++){
        if(Filters[i] == NULL)
            continue;
        is_all_null = false;
        selected = Filters[i]->set_filter(selected);
    }
    current->check_def_price_filter(is_all_null, selected);
    if(sort != NULL)
        sort->sort_hotels(selected, current);

    Filter::print_hotels(selected);
}

void Utrip::city_filter(stringstream &sstream){
    string word;
    getline(sstream, word);
    word.erase(word.begin());
    City* new_filter = new City(word);
    Filters[new_filter->get_id()-1] = new_filter;
    cout << "OK" << endl;
}

void Utrip::star_filter(stringstream &sstream){
    string word;
    int min, max;
    for(int i=0; i< 2; i++){
        sstream >> word; 
        if(word == "min_star"){
            sstream >> min;
        }
        else if(word == "max_star"){
            sstream >> max;
        }
        else
            throw ImportException(BAD_REQUEST);
    }
    if(min > max || min < 1 || max <1 || min > 5 || max > 5)
        throw ImportException(BAD_REQUEST);
    
    Star* new_filter = new Star(min, max);
    Filters[new_filter->get_id()-1] = new_filter;
    cout << "OK" << endl;
}

void Utrip::cost_filter(stringstream &sstream){
    string word;
    double min, max;
    for(int i=0; i< 2; i++){
        sstream >> word; 
        if(word == "min_price"){
            sstream >> min;
        }
        else if(word == "max_price"){
            sstream >> max;
        }
        else
            throw ImportException(BAD_REQUEST);
    }
    if(min < 0 || max < 0 || min > max)
        throw ImportException(BAD_REQUEST);
    
    Cost* new_filter = new Cost(min, max);
    Filters[new_filter->get_id()-1] = new_filter;
    cout << "OK" << endl;
}

void Utrip::specific_filter(stringstream &sstream){
    string word, type;
    int quantity, in, out;
    for(int i=0; i< 4; i++){
        sstream >> word;
        if(word == "type"){
            sstream >> type;
        }
        else if(word == "quantity"){
            sstream >> quantity;
        }
        else if(word == "check_in"){
            sstream >> in;
        }
        else if(word == "check_out"){
            sstream >> out;
        }
        else
            throw ImportException(BAD_REQUEST);
    }
    if(in <1 || out > 30 || in > out)
        throw ImportException(BAD_REQUEST);
    
    Specific* new_filter = new Specific(type, quantity, in, out);
    Filters[new_filter->get_id()-1] = new_filter;
    cout << "OK" << endl;
}

void Utrip::reserve(stringstream &sstream){
    string word, uid, type;
    int quantity, in, out;
    sstream >> word;
    for(int i=0; i<5; i++){
        sstream >> word;
        if(word == "hotel"){
            sstream >> uid;
        }else if(word == "type"){
            sstream >> type;
        }else if(word == "quantity"){
            sstream >> quantity;
        }else if(word == "check_in"){
            sstream >> in;
        }else if(word == "check_out"){
            sstream >> out;
        }else 
            throw ImportException(BAD_REQUEST);
    }
    Hotel* find = find_hotel(uid);

    RoomTable selected = find->find_rooms(type, quantity, in, out);

    if(selected.size() < quantity)
        throw ImportException(NOT_ENOUGH_ROOM);
    if(selected[0]->get_price()*quantity > current->get_wallet().back())
        throw ImportException(NOT_ENOUGH_CREDIT);
    current->update_wallet(-selected[0]->get_price()*quantity);
    reserve_room(selected, in, out);
    current->set_reservation(new Reserve(uid, selected, selected[0]->get_price()*quantity, in, out));
}   

void Utrip::reserve_room(RoomTable &rooms, int in, int out){
    for(auto &room : rooms)
        room->reserve(in, out);
}

void Utrip::delete_reserve(stringstream &sstream){
    string word;
    sstream >> word >> word;
    if(word != "id")
        throw ImportException(BAD_REQUEST);
    int id;
    sstream >> id;
    current->delete_reserve(id);

    cout << "OK" << endl;
}

void Utrip::comments(stringstream &sstream){
    string word, uid, comment;
    sstream >> word;
    for(int i=0; i<2; i++){
        sstream >> word;
        if(word == "hotel"){
            sstream >> uid;
        }
        else if(word == "comment"){
            sstream >> comment;
        }
        else 
            throw ImportException(BAD_REQUEST);
    }
    Hotel* hotel = find_hotel(uid);
    
    hotel->set_comment(current->get_name() + ": " + comment);
    cout << "OK" << endl;
}

void Utrip::get_comments(stringstream &sstream){
    string word, uid;
    sstream >> word >> word;
    if(word != "hotel")
        throw ImportException(BAD_REQUEST);
    sstream >> uid;
    Hotel* hotel = find_hotel(uid);
    
    hotel->print_comments();
}

Hotel* Utrip::find_hotel(string uid){
    for(auto &hotel : hotels)
        if(hotel.get_uid() == uid)
            return &hotel;
    throw ImportException(NOT_FOUND);
}

void Utrip::ratings(stringstream &sstream){
    string word, uid;
    Ratings ratings;
    sstream >> word;
    for(int i=0; i<7; i++){
        sstream >> word;
        if(word == "hotel")
            sstream >> uid;
        else if(word == "location")
            sstream >> ratings.location;
        else if(word == "cleanliness")
            sstream >> ratings.cleanlines;
        else if(word == "staff")
            sstream >> ratings.staff;
        else if(word == "facilities")
            sstream >> ratings.facilities;
        else if(word == "value_for_money")
            sstream >> ratings.value_for_money;
        else if(word == "overall_rating")
            sstream >> ratings.overall_rating;
        else 
            throw ImportException(BAD_REQUEST);
    }

    if(ratings.location<1 || ratings.cleanlines<1 || ratings.staff<1 || ratings.facilities<1
    || ratings.value_for_money<1 || ratings.overall_rating<1 || ratings.location>5 || ratings.cleanlines>5
    || ratings.staff>5 || ratings.facilities>5 || ratings.value_for_money>5 || ratings.overall_rating>5)
        throw ImportException(BAD_REQUEST);

    ratings.initialize = true;
    Hotel* hotel = find_hotel(uid);
    current->set_ratings(make_pair(hotel, ratings));
    cout << "OK" << endl;
}

void Utrip::get_ratings(stringstream &sstream){
    string word, uid;
    sstream >> word >> word;
    if(word == "hotel")
        sstream >> uid;
    else 
        throw ImportException(BAD_REQUEST);
    
    Hotel *hotel= find_hotel(uid);
    hotel->print_ratings();
}

void Utrip::def_price_filter(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);

    string word, status;
    sstream >> word >> word;

    if(word == "active"){
        sstream >> status;
    }
    else 
        throw ImportException(BAD_REQUEST);
    
    if(status == "true")
        current->set_price_filter(true);
    else if(status == "false")
        current->set_price_filter(false);
    else 
        throw ImportException(BAD_REQUEST);
    
    cout << "OK" << endl;
}

void Utrip::post_sort(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);

    Type type = Sort::check_validity(sstream);
    sort = new Sort(type);
    
    cout << "OK" << endl;
}

void Utrip::manual_weights(std::stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);
    
    current->manual_weights(sstream);
    cout << "OK" << endl;
}

void Utrip::get_manual_weights(){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);

    current->get_manual_weights();
}