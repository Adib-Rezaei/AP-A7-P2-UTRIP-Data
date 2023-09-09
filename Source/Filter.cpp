#include <bits/stdc++.h>
#include "Utrip.hpp"
using namespace std;

typedef long long ll;

void Filter::print_hotels(HotelTable &_hotels){
    if(_hotels.empty())
        cout << "Empty" << endl;
    for(int i=0; i< _hotels.size(); i++){
        _hotels[i].filter_print();
    }
}

HotelTable City::set_filter(HotelTable selected){
    HotelTable filter;
    for(auto &hotel : selected){
        if(hotel.get_city() == name){
            filter.push_back(hotel);
        }
    }
    return filter;
}

HotelTable Star::set_filter(HotelTable selected){
    HotelTable filter;
    for(auto &hotel : selected){
        if(hotel.get_star() >= min && hotel.get_star() <= max)
            filter.push_back(hotel);
    }
    return filter;
}

HotelTable Cost::set_filter(HotelTable selected){
    HotelTable filter;
    for(auto &hotel : selected){
        if(hotel.calc_avg() >= min && hotel.calc_avg() <= max)
            filter.push_back(hotel);
    }
    return filter;
}

HotelTable Specific::set_filter(HotelTable selected){
    HotelTable filter;
    for(auto &hotel : selected){
        vector<Room*> rooms = hotel.get_rooms();
        int cnt=0;
        for(auto &room : rooms){
            if(is_ok_room(room))
                cnt++;
        }
        if(cnt >= quantity)
            filter.push_back(hotel);
    }
        
    return filter;
}

bool Specific::is_ok_room(Room* room){
    if(room->get_name()[0] == type[0]){
        vector<int> date = room->get_date();
        for(int i=check_in; i<= check_out; i++){
            if(date[i]){
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}

HotelTable Default_price::set_filter(HotelTable hotels, ReserveTable reserves){
    HotelTable filter;
    double TotalCost = (double)accumulate(reserves.begin(), reserves.end(), 0, sum_operation);
    double Ms = TotalCost/accumulate(reserves.begin(), reserves.end(), 0, sum_room_operation);
    double deviation = calc_deviation(Ms, reserves);
    for(auto &hotel : hotels){
        double left_side = fabs(hotel.calc_avg() - Ms);
        if(left_side <= 2*deviation)
            filter.push_back(hotel);
    }
    return filter;
}

double Default_price::calc_deviation(double Ms, ReserveTable reserves){
    double sum=0;
    int count_rooms=0;
    for(auto &reserve : reserves){
        int per_room_price = reserve->get_cost()/reserve->sizeof_rooms();
        count_rooms += reserve->sizeof_rooms();
        for(int i=0; i< reserve->sizeof_rooms(); i++){
            sum += pow(per_room_price-Ms, 2);
        }
    }
    return sqrt(sum/(count_rooms-1));
}

int Default_price::sum_operation(int init, Reserve* reserve){
    return init+reserve->get_cost();
}

int Default_price::sum_room_operation(int init, Reserve* reserve){
    return init + reserve->sizeof_rooms();
}