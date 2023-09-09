#include <bits/stdc++.h>
#include "Utrip.hpp"
using namespace std;

void Room::reserve(int in, int out){
    for(int i=in; i<=out; i++){
        date[i] = 1;
    }
}