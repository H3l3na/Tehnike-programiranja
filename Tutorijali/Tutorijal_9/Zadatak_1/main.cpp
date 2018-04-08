#include <iostream>
#include <math.h>

using namespace std;


class Vektor3d {
 double x, y, z;
public:
 void Postavi(double x, double y, double z) {
 Vektor3d::x = x; Vektor3d::y = y; Vektor3d::z = z;
 }
 void Ocitaj(double &x, double &y, double &z) const {
 x = Vektor3d::x; y = Vektor3d::y; z = Vektor3d::z;
 }
 void Ispisi() const {
 std::cout << "{" << x << "," << y << "," << z << "}";
 }
 void PostaviX(double x){
     Vektor3d::x=x;
 }
 void PostaviY(double y){
     Vektor3d::y=y;
 }
 void PostaviZ(double z){
     Vektor3d::z=z;
 }
 double DajX() const { return x; }
 double DajY() const { return y; }
 double DajZ() const { return z; }
 double DajDuzinu() const { return std::sqrt(x * x + y * y + z * z); }
 void PomnoziSaSkalarom(double s) { x *= s; y *= s; z *= s; }
 void SaberiSa(const Vektor3d &v) { x += v.x; y += v.y; z += v.z; }
};

int main()
{
    Vektor3d v1, v2;
    v1.Postavi(3, 4, 5);
    v2.Postavi(7, 3, 2);
    std::cout << v1.DajDuzinu() << std::endl; // 7.071068
    v1.PomnoziSaSkalarom(5);
    v1.Ispisi(); // {15,20,25}
    std::cout << std::endl;
    v1.SaberiSa(v2);
    v1.Ispisi();
    return 0;
}
