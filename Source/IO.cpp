#include <bits/stdc++.h>
#include "Utrip.hpp"
#include "IO.hpp"

#define SEPERATOR ','
using namespace std;

HotelTable IO::read_hotels(string path){
    ifstream input(path);
    string line;
    HotelTable hotels;

    getline(input, line);
    while(getline(input, line)){
        vector<string> row = parse_line(line);
        hotels.push_back(Hotel(row));
    }
    sort(hotels.begin(), hotels.end(), compare_uid);
    return hotels;
}

vector<string> IO::parse_line(string line){
    string word;
    stringstream sstream(line);
    vector<string> row;
    
    while (getline(sstream, word, SEPERATOR)){
        row.push_back(word);
    }

    return row;
}

bool IO::compare_uid(Hotel hotel_1, Hotel hotel_2){
    return hotel_1.get_uid() < hotel_2.get_uid();
}

void IO::read_ratings(std::string path, HotelTable &hotels){
    ifstream input(path);
    string line;

    getline(input, line);
    while(getline(input, line)){
        vector<string> row = parse_line(line);
        Ratings ratings = initialize_rating(row);
        find_hotel(row[0], hotels)->set_ratings(ratings);
    }
}

Ratings IO::initialize_rating(vector<string> &row){
    Ratings ratings;
    ratings.initialize = true;
    ratings.location = stod(row[1]);
    ratings.cleanlines = stod(row[2]);
    ratings.staff = stod(row[3]);
    ratings.facilities = stod(row[4]);
    ratings.value_for_money = stod(row[5]);
    ratings.overall_rating = stod(row[6]);
    return ratings;
}

Hotel* IO::find_hotel(string uid, HotelTable &hotels){
    for(auto &hotel : hotels)
        if(hotel.get_uid() == uid)
            return &hotel;
    throw ImportException(NOT_FOUND);
}