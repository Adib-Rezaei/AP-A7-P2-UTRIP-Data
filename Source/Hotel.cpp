#include <bits/stdc++.h>
#include "Utrip.hpp"

using namespace std;

Hotel::Hotel(Line &row){
    uid = row[0];   name = row[1];
    star = stoi(row[2]);    overview = row[3];
    amenities = row[4];     city = row[5];
    latitude = stod(row[6]);    longitude = stod(row[7]);
    image_url = row[8];
    price.standard = stoi(row[13]); price.deluxe = stoi(row[14]);
    price.luxury = stoi(row[15]);   price.premium = stoi(row[16]);
    initialize_rooms(row);
    ratings.initialize = false; 
}

void Hotel::initialize_rooms(Line &row){
    
    for(int i=9; i< 13; i++){
        for(int j=0; j< stoi(row[i]); j++){
            which_room(i, j+1);
        }
    }
}

void Hotel::which_room(int col, int id){
    switch (col){
        case 9:
            rooms.push_back(new Standard(price.standard, id));
            break;
        case 10:
            rooms.push_back(new Deluxe(price.deluxe, id));
            break;
        case 11:
            rooms.push_back(new Luxury(price.luxury, id));
            break;
        case 12:
            rooms.push_back(new Premium(price.premium, id));
            break;
    }
}

void Hotel::print(){
    cout << uid << endl << name << endl << "star: " << star << endl
         << "overview: " << overview << endl << "amenities: " << amenities << endl
         << "city: " << city << endl << "latitude: " << fixed << setprecision(2)
         << latitude << endl << "longitude: " << longitude << endl << "#rooms: ";

    print_extra();
    cout << endl << "price: " << price.standard << ' ' << price.deluxe
         << ' ' << price.luxury << ' ' << price.premium << endl;
}

void Hotel::print_extra(){
    vector<char> names = {'s', 'd', 'l', 'p'};
    for(int i=0; i< 4; i++){
        int cnt=0;
        for(int j=0; j< rooms.size(); j++){
            if(rooms[j]->get_name()[0] == names[i])
                cnt++;
        }
        cout << cnt;
        if(i != 3)
            cout << ' ';
    }
}

void Hotel::filter_print(){
    cout << uid << ' ' << name << ' ' << star << ' ' << city << ' '
         << rooms.size() << ' ' << fixed << setprecision(2) << calc_avg() << ' ' << endl;
}

RoomTable Hotel::find_rooms(string type, int quantity, int in, int out){

    vector<Room*> selected;
    for(auto &room : rooms){
        if(room->get_name()[0] == type[0]){
            vector<int> date = room->get_date();
            bool is_ok=true;
            for(int i=in; i<=out; i++)
                if(date[i])
                    is_ok=false;
            if(is_ok)
                selected.push_back(room);
        }
        if(selected.size() == quantity)
            break;
    }
    
    return selected;
}

void Hotel::print_comments(){
    for(int i=comments.size()-1; i>= 0; i--){
        cout << comments[i] << endl;
    }
}

void Hotel::print_ratings(){
    if(ratings.initialize == false)
        throw ImportException(NO_RATING);
    
    cout << fixed << setprecision(2) << "location: " << ratings.location << endl << "cleanliness: "
    << ratings.cleanlines << endl << "staff: " << ratings.staff << endl 
    << "facilities: " << ratings.facilities << endl << "value_for_money: "
    << ratings.value_for_money << endl << "overall_rating: " << ratings.overall_rating << endl;
}

double Hotel::calc_avg(){
    vector<int> cost = {price.standard, price.deluxe, price.luxury, price.premium};
    int cnt=0;
    double sum=0;
    for(int i=0; i< cost.size(); i++){
        if(cost[i] != 0 ){
            cnt++;
            sum += cost[i];
        }
    }
    if(sum == 0)
        return 0;
    return sum/cnt;
}
