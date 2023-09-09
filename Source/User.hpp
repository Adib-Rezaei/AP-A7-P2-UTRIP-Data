#ifndef USER_HPP
#define USER_HPP

#include "Reserve.hpp"

typedef std::pair<Hotel*, Ratings> HotelRating;
typedef std::vector<HotelRating> RatingTable;

struct Weight {
    bool active;
    double location;
    double cleanlines;
    double staff;
    double facilities;
    double value_for_money;
};

class User {
public:
    User(std::string _email, std::string _username, std::string _pass){
        email = _email; username = _username; password = _pass; wallet.push_back(0);
        price_filter = true; weight.active = false;
    }
    bool check_signup(std::string _email, std::string _username);
    bool check_login(std::string _email, std::string _password);
    void update_wallet(int amount);
    void set_reservation(Reserve* reserve);
    std::vector<int> get_wallet(){ return wallet; }
    void print_reservations();
    void delete_reserve(int reserve_id);
    std::string get_name(){ return username; }
    void set_price_filter(bool status){ price_filter = status; }
    void check_def_price_filter(bool no_filter, HotelTable &selected);
    void set_ratings(HotelRating hotelRating){ ratings.push_back(hotelRating); }
    void manual_weights(std::stringstream &sstream);
    void get_manual_weights();
    RatingTable get_ratingTable(){ return ratings; }
    Weight get_weight(){ return weight; }
    
private:
    std::string email;
    std::string username;
    std::string password;
    std::vector<int> wallet;
    std::vector<Reserve*> reserves;
    RatingTable ratings;
    Weight weight;
    bool price_filter;
};

#endif