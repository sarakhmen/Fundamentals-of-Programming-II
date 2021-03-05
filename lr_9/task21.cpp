#include <iostream>
using namespace std;

class ft_to_cms {
    double feet;
    double cms;
public:
    void set(double f) {
        feet = f;
        cms = f * 30.48;
    }
    friend istream &operator >>(istream &stream, ft_to_cms &obj){
        cout << "Enter number of feet: ";
        stream >> obj.feet;
        obj.set(obj.feet);
        return stream;
    }
    friend ostream &operator <<(ostream &stream, ft_to_cms &obj){
        stream << "Feet: " << obj.feet << endl;
        stream << "Cms: " << obj.cms << endl;
        return stream;
    }
};


int main(){
    ft_to_cms ftc;
    cin >> ftc;
    cout << ftc;
    return 0;
}