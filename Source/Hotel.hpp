#ifndef HOTEL_HPP
#define HOTEL_HPP

#include "Room.hpp"
typedef std::vector<Room*> RoomTable;

struct Price {
    int standard;
    int deluxe;
    int luxury;
    int premium;
};

struct Ratings {
    bool initialize;
    double location;
    double cleanlines;
    double staff;
    double facilities;
    double value_for_money;
    double overall_rating;
};

class Hotel {
public:
    Hotel(Line &row);
    void print();
    void filter_print();
    std::string get_uid(){ return uid; }
    std::string get_city(){ return city; }
    int get_star(){ return star; }
    RoomTable get_rooms(){ return rooms; }
    std::string get_name(){ return name; }
    Price get_price(){ return price; }
    Ratings get_ratings(){ return ratings; }
    void set_rating_personal(double _rating){ rating_personal = _rating; }
    double get_rating_personal(){ return rating_personal; }

    double calc_avg();
    RoomTable find_rooms(std::string type, int quantity, int in, int out);
    void set_comment(std::string comment){ comments.push_back(comment); }
    void print_comments();
    void set_ratings(Ratings _ratings){ ratings = _ratings; }
    void print_ratings();

private:
    void initialize_rooms(Line &row);
    void which_room(int col, int id);
    void print_extra();

    std::string uid;
    std::string name;
    int star;
    std::string overview;
    std::string amenities;
    std::string city;
    double latitude;
    double longitude;
    std::string image_url;
    RoomTable rooms;
    Price price;
    Ratings ratings;
    double rating_personal;
    std::vector<std::string> comments;
};


#endif