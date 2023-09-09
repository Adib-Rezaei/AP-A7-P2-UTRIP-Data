#ifndef FILTER_HPP
#define FILTER_HPP

typedef std::vector<Reserve*> ReserveTable; 

class Filter {
public:
    static void print_hotels(HotelTable &_hotels);
    virtual HotelTable set_filter(HotelTable selected) = 0;
    int get_id(){ return id; }
protected:
    int id;
};

class City : public Filter {
public:
    City(std::string _name){ name = _name; id = 1; }
    HotelTable set_filter(HotelTable selected);
private:
    std::string name;
};

class Star : public Filter {
public:
    Star( int _min, int _max){
        min = _min; max = _max; id = 2;
    }
    HotelTable set_filter(HotelTable selected);
private:
    int min;
    int max;
};

class Cost : public Filter {
public:
    Cost(double _min, double _max){ 
        min = _min; max = _max; id = 3;
    }
    HotelTable set_filter(HotelTable selected);
private:
    double min;
    double max;
};

class Specific : public Filter {
public:
    Specific(std::string _type, int _quantity, int _in, int _out){
        type = _type; quantity = _quantity; check_in = _in; check_out = _out; id = 4;
    }
    HotelTable set_filter(HotelTable selected);
private:
    bool is_ok_room(Room* room);
    std::string type;
    int quantity;
    int check_in; 
    int check_out;
};

class Default_price {
public:
    static HotelTable set_filter(HotelTable hotels, ReserveTable reserves);
private:
    static int sum_operation(int init, Reserve* reserve);
    static double calc_deviation(double Ms, ReserveTable reserves);
    static int sum_room_operation(int init, Reserve* reserve);
};

#endif