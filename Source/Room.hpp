#ifndef ROOM_HPP
#define ROOM_HPP

class Room {
public:
    Room(int _price){ price = _price;   date.resize(31,0); }
    std::string get_name(){ return name; }
    std::vector<int> get_date(){ return date; }
    int get_price(){ return price; }
    void reserve(int in, int out);
protected:
    std::vector<int> date;
    int price;
    std::string name;
};

class Standard : public Room {
public:
    Standard(int _price, int id) : Room(_price){ name = "s"+std::to_string(id); }
};

class Deluxe : public Room {
public:
    Deluxe(int _price, int id) : Room(_price){ name = "d"+std::to_string(id); }
};

class Luxury : public Room {
public:
    Luxury(int _price, int id) : Room(_price){ name = "l"+std::to_string(id); }
};

class Premium : public Room {
public:
    Premium(int _price, int id) : Room(_price){ name = "p"+std::to_string(id); }
};

#endif