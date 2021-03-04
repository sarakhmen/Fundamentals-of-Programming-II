#include <iostream>

class building {
    int floors;
    int rooms;
public:
    building(int fl, int rm): floors(fl), rooms(rm) {}
    int get_floors() {return floors;}
    int get_rooms() {return rooms;}
};

class house : public building {
    int bathrooms;
    int bedrooms;
public:
    house(int fl, int rm, int bthrms, int bdrms): building(fl, rm), bathrooms(bthrms), bedrooms(bdrms) {}
    int get_bathrooms(){return bathrooms;}
    int get_bedrooms(){return bedrooms;}
};

class office : public house {
    int extinguishers;
    int telephones;
public:
    office(int fl, int rm, int bthrms, int bdrms, int extngs, int tlph): house(fl, rm, bthrms, bdrms),
        extinguishers(extngs), telephones(tlph) {}
    int get_extinguishers(){return extinguishers;}
    int get_telephones(){return telephones;}
};

int main(){
    office of(1, 1, 1, 1, 1, 1);
    return 0;
}