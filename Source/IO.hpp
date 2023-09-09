#ifndef IO_HPP
#define IO_HPP

class IO {
public:
    static HotelTable read_hotels(std::string path);
    static void read_ratings(std::string path, HotelTable &hotels);
private:
    static std::vector<std::string> parse_line(std::string line);
    static bool compare_uid(Hotel hotel_1, Hotel hotel_2);
    static Hotel* find_hotel(std::string uid, HotelTable &hotels);
    static Ratings initialize_rating(std::vector<std::string> &row);
};

#endif