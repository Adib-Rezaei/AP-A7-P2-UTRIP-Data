#ifndef UTRIP_HPP
#define UTRIP_HPP


typedef std::vector<std::string> Line;
#include "Hotel.hpp"
typedef std::vector<Hotel> HotelTable;
#include "User.hpp"
typedef std::vector<User*> UserTable;
#include "Filter.hpp"
#include "ImportException.hpp"
#include "Sort.hpp"


class Utrip {
public:
    Utrip(HotelTable _hotels){
        hotels = _hotels; current = NULL; Filters.resize(4,NULL); sort=NULL;
    }
    void post_command(std::stringstream &sstream);
    void get_command(std::stringstream &sstream);
    void delete_command(std::stringstream &sstream);

private:
    void signup(std::stringstream &sstream);
    void login(std::stringstream &sstream);
    void logout(std::stringstream &sstream);
    void wallet(std::stringstream &sstream);
    void filters(std::stringstream &sstream);
    void city_filter(std::stringstream &sstream);
    void star_filter(std::stringstream &sstream);
    void cost_filter(std::stringstream &sstream);
    void specific_filter(std::stringstream &sstream);
    void reserve(std::stringstream &sstream);
    void comments(std::stringstream &sstream);
    void ratings(std::stringstream &sstream);

    void get_wallet(std::stringstream &sstream);
    void get_hotels(std::stringstream &sstream);
    void get_comments(std::stringstream &sstream);
    void get_ratings(std::stringstream &sstream);

    void post_sort(std::stringstream &sstream);
    void manual_weights(std::stringstream &sstream);
    void get_manual_weights();
    void def_price_filter(std::stringstream &sstream);
    
    void delete_reserve(std::stringstream &sstream);
    void filter_hotels();
    Hotel* find_hotel(std::string uid);
    void reserve_room(RoomTable &rooms, int in, int out);
    std::string hashing(std::string password);

    HotelTable hotels;
    UserTable users;
    User* current;
    std::vector<Filter*> Filters;
    Sort* sort;
};


#endif