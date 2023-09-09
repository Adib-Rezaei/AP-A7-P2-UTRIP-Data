#ifndef RESERVE_HPP
#define RESERVE_HPP

class Reserve {
public:
    Reserve(std::string _hotel, RoomTable _rooms, int _cost, int _in, int _out){
        hotel = _hotel; rooms = _rooms; cost = _cost; check_in = _in; check_out = _out;
    }
    void print_rooms();
    void print_all();
    int get_cost(){ return cost; }
    int sizeof_rooms(){ return rooms.size(); }
private:
    std::string which_room(char character);

    int id;
    std::string hotel;
    RoomTable rooms;
    int cost;
    int check_in;
    int check_out;
};

#endif