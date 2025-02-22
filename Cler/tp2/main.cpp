#include "point.h"
using namespace std;

class Carre : POINT{

    POINT kose1;
    POINT kose2;
    public:

    Carre(POINT kose1, POINT kose2){
        cout << "kare olusturuldu :)" <<endl;
        this -> kose1 = kose1;
        this -> kose2 = kose2;
    }
    //bakılacak
    float Aire(){
        float xkare=(this-> kose1.get_X()-this-> kose2.get_X())*(this-> kose1.get_X()-this-> kose2.get_X());
        float ykare=(this-> kose1.get_Y()-this-> kose2.get_Y())*(this-> kose1.get_Y()-this-> kose2.get_Y());
        float kenar= sqrt((xkare+ykare)/2);
        float aire=kenar*kenar;
        return aire;
    }

    float Perimetre(){
        float xkare=(this-> kose1.get_X()-this-> kose2.get_X())*(this-> kose1.get_X()-this-> kose2.get_X());
        float ykare=(this-> kose1.get_Y()-this-> kose2.get_Y())*(this-> kose1.get_Y()-this-> kose2.get_Y());
        float kenar= sqrt((xkare+ykare)/2);
        float perimetre = 4*kenar;
        return perimetre;
        
    }

};


//rectangle

class Rectangle : POINT{

    POINT kose1;
    POINT kose2;
    public:

    Rectangle(POINT kose1, POINT kose2){
        cout << "kare olusturuldu :)" <<endl;
        this -> kose1 = kose1;
        this -> kose2 = kose2;
    }

    float Aire() {
        float width = abs(kose1.get_X() - kose2.get_X());
        float height = abs(kose1.get_Y() - kose2.get_Y());
        return width * height;
    }

    float Perimetre() {
        float width = abs(kose1.get_X() - kose2.get_X());
        float height = abs(kose1.get_Y() - kose2.get_Y());
        return 2 * (width + height);
    }

};

//cercle

class Cercle : POINT{

    POINT merkez;
    float radius;
    public:

    Cercle(POINT merkez, float radius){
        cout << "cember olusturuldu :)" <<endl;
        this -> merkez = merkez;
        this -> radius = radius;
    }
    //bakılacak
    float Aire(){
        float aire=3.14*radius*radius;
        return aire;
    }

    float Perimetre(){
        float perimetre = 2* 3.14*radius;
        return perimetre;
        
    }

};


//triangle

class Triangle : POINT{

    POINT kose1;
    POINT kose2;
    POINT kose3;
    string color;
    public:

    Triangle(POINT kose1, POINT kose2,POINT kose3 ,string color){
        cout << "kare olusturuldu :)" <<endl;
        this -> kose1 = kose1;
        this -> kose2 = kose2;
        this -> kose3 = kose3;
        this -> color = color;
    }
    string get_color(){
        return this->color;
    }

};




int main(){
    POINT* yenikose1= new POINT(1,1);
    POINT* yenikose2= new POINT(5,5);
    Carre* yenikare= new Carre(*yenikose1,*yenikose2);
    cout << (*yenikare).Aire() <<endl;
    cout << (*yenikare).Perimetre() <<endl;
    Cercle* cember = new Cercle(*yenikose1, 5);
    cout << (*cember).Aire() <<endl;
    cout << (*cember).Perimetre() <<endl;

    return 0;
}