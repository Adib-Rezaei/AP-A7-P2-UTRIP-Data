#include <bits/stdc++.h>
#include "Utrip.hpp"
#include "Sort.hpp"
#include "IO.hpp"
using namespace std;

#define property first
#define order second
#define MAX_W 5
#define MIN_W 1
#define EPSILON 1e-4
#define score hotelRating.second

void Sort::sort_hotels(HotelTable &hotels, User* current){
    if(type.property == "id"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_uid() < sec.get_uid(); });
    }
    else if(type.property == "name"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_name() < sec.get_name(); });
    }
    else if(type.property == "star_rating"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_star() < sec.get_star(); });
    }
    else if(type.property == "city"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_city() < sec.get_city(); });
    }
    else if(type.property == "standard_room_price"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_price().standard < sec.get_price().standard; });
    }
    else if(type.property == "deluxe_room_price"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_price().deluxe < sec.get_price().deluxe; });
    }
    else if(type.property == "luxury_room_price"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_price().luxury < sec.get_price().luxury; });
    }
    else if(type.property == "premium_room_price"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_price().premium < sec.get_price().premium; });
    }
    else if(type.property == "average_room_price"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.calc_avg() < sec.calc_avg(); });
    }
    else if(type.property == "rating_overall"){
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_ratings().overall_rating < sec.get_ratings().overall_rating; });
    }
    else if(type.property == "rating_personal"){
        rating_personal(hotels, current);
        stable_sort(hotels.begin(), hotels.end(), 
            [](Hotel fi, Hotel sec){ return fi.get_rating_personal() < sec.get_rating_personal(); });
    }

    if(type.order == "descending"){
        reverse(hotels.begin(), hotels.end());
    }
}


Type Sort::check_validity(stringstream &sstream){
    vector<string> properties = {"id", "name", "star_rating", "city", "standard_room_price",
        "deluxe_room_price", "luxury_room_price", "premium_room_price", "average_room_price",
        "rating_overall", "rating_personal"};
    vector<string> orders = {"ascending", "descending"};

    string word, _property, _order;
    sstream >> word;
    for(int i=0; i< 2; i++){
        sstream >> word;
        if(word == "property"){
            sstream >> _property;
            auto it = find(properties.begin(), properties.end(), _property);
            if(it == properties.end()){
                throw ImportException(BAD_REQUEST);
            }
        }
        else if(word == "order"){
            sstream >> _order;
            auto it = find(orders.begin(), orders.end(), _order);
            if(it == orders.end()){
                throw ImportException(BAD_REQUEST);
            }
        }
        else 
            throw ImportException(BAD_REQUEST);
    }
    Type _type = make_pair(_property, _order);
    return _type;
}

void Sort::rating_personal(HotelTable &hotels, User* current){
    for(auto &hotel : hotels){
        if(check_if_rated(hotel, current))
            continue;
        else if(current->get_weight().active){
            manual_on(hotel, current);
        }
        else {
            manual_off(hotel, current);
        }
    }
}

bool Sort::check_if_rated(Hotel &hotel, User* current){
    RatingTable ratings = current->get_ratingTable();
    for(auto & rating : ratings){
        if(hotel.get_uid() == rating.first->get_uid()){
            hotel.set_rating_personal(rating.second.overall_rating);
            return true;
        }
    }
    return false;
}

void Sort::manual_on(Hotel &hotel, User* current){
    Weight w = current->get_weight();
    Ratings r = hotel.get_ratings();
    vector<double> weight = {w.location, w.cleanlines, w.staff, w.facilities, w.value_for_money};
    vector<double> rating = {r.location, r.cleanlines, r.staff, r.facilities, r.value_for_money};

    hotel.set_rating_personal(calc_weight_average(rating, weight));
}

void Sort::manual_off(Hotel &hotel, User* current){
    vector<double> w(5);
    vector<double> d(5);
    RatingTable ratingTable = current->get_ratingTable();

    if(ratingTable.size() < 5)
        throw ImportException(INSUFFICIEND_RATINGS);

    srand(0);
    for(int i=0; i< 5; i++){
        w[i] = (MAX_W - MIN_W) * ( (double)rand() / (double)RAND_MAX ) + MIN_W;
    }
    for(int k=0; k< 1e3; k++){
        for(int i=0; i< 5; i++)
            d[i] = 0;

        for(int j=0; j< ratingTable.size(); j++){
            for(int i=0; i< 5; i++){
                d[i] += (error_func(ratingTable[i], w, i)-error_func(ratingTable[i], w))/EPSILON;
            }
        }

        for(int i=0; i< 5; i++){
            w[i] = w[i] - d[i];
            if(w[i] > 5) w[i] = 5;
            else if(w[i] < 1) w[i] = 1;
        }
    }

    vector<double> ratings = {hotel.get_ratings().location, hotel.get_ratings().cleanlines,
    hotel.get_ratings().staff, hotel.get_ratings().facilities, hotel.get_ratings().value_for_money};
    hotel.set_rating_personal(calc_weight_average(ratings, w));
    
}

double Sort::error_func(HotelRating hotelRating, vector<double> w, int index){
    if(index != -1)
        w[index] += EPSILON;

    vector<double> rating = {score.location, score.cleanlines,
     score.staff, score.facilities, score.value_for_money};
    
    double estimate = calc_weight_average(rating, w);
    double overall = score.overall_rating;
    double error_value = pow(estimate-overall, 2);

    return error_value;
}

double Sort::calc_weight_average(vector<double> rating, vector<double> w){
    double sum = 0;
    for(int i=0; i< 5; i++){
        sum += w[i]*rating[i];
    }
    return sum/accumulate(w.begin(), w.end(), 0.0);
}