#ifndef SORT_HPP
#define SORT_HPP

typedef std::string Property;
typedef std::string Order;
typedef std::pair<Property, Order> Type;

class Sort {
public:
    Sort(Type _type){ type = _type; }
    static Type check_validity(std::stringstream &sstream);
    void sort_hotels(HotelTable &hotels, User* current);
private:
    void which_sort(std::string property, HotelTable &hotels);
    void rating_personal(HotelTable &hotels, User* current);
    bool check_if_rated(Hotel &hotel, User* current);
    void manual_on(Hotel &hotel, User* current);
    void manual_off(Hotel &hotel, User* current);
    double error_func(HotelRating hotelRating, std::vector<double> w, int index=-1);
    double calc_weight_average(std::vector<double> rating, std::vector<double> w);
    
    Type type;
};

#endif