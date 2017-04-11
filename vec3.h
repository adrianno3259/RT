#ifndef VEC3_H
#define VEC3_H

#define printVec(A) std::cout << #A << " = (" << (A).x <<", "<<(A).y<<", "<<(A).z<<")"<<std::endl

class Vec3d
{
public:
    float x, y, z;
    Vec3d(): x(0.0), y(0.0), z(0.0) {} // KAIOSHIN
    Vec3d(const float a) : x(a), y(a), z(a) {} // KAIOSHIN
    Vec3d(const float a, const float b, const float c) : x(a), y(b), z(c) {} // KAIOSHIN
    Vec3d(const Vec3d& v) : x(v.x), y(v.y), z(v.z) {} // KAIOSHIN
    ~Vec3d (void){}; // HAKAISHIN
    Vec3d& operator= (const Vec3d& rhs); //Sobrecarrega os operadores de atribuição
    Vec3d operator- (void) const; // Operador menos unário
    Vec3d operator* (const float a) const; //multiplicação por escalar
    Vec3d operator/ (const float a) const; // divisão por escalar
    Vec3d operator+ (const Vec3d& v) const; // soma de vetores
    Vec3d& operator+= (const Vec3d& v); // soma e atribuição de vetores
    Vec3d operator- (const Vec3d& v) const; // subtração de vetores
    float operator* (const Vec3d& b) const; // produto escalar - dot product de dois vetores
    Vec3d operator^ (const Vec3d& v) const; // produto vetorial - cross product de dois vetores
    float length(void); // retorna a magnitude do vetor
    float len_squared(void); // retorna o quadrado da magnitude do vetor
    void normalize(void); // transforma o vetor em vetor unitário
    Vec3d& hat(void); // retorna o vetor normalizado e transforma o vetor em unitário
};

// ----- multiplicação com o escalar do lado esquerdo -------
Vec3d operator* (const double a, const Vec3d& v);
Vec3d operator* (const int a, const Vec3d& v);


inline Vec3d Vec3d::operator- (void) const { return Vec3d(-x, -y, -z); }
inline Vec3d Vec3d::operator* (const float a) const { return Vec3d(a*x, a*y, a*z); }
inline Vec3d Vec3d::operator/ (const float a) const { return Vec3d(x/a, y/a, z/a); }
inline Vec3d Vec3d::operator+ (const Vec3d& c) const { return Vec3d(x + c.x, y + c.y, z + c.z); }
inline Vec3d& Vec3d::operator+= (const Vec3d& c) { x += c.x; y += c.y; z += c.z; return (*this); }
inline Vec3d Vec3d::operator- (const Vec3d& c) const { return Vec3d(x - c.x, y - c.y, z - c.z); }
inline float Vec3d::operator* (const Vec3d& c) const { return ( (x * c.x)+ (y * c.y) + (z * c.z) ) ; }
inline Vec3d Vec3d::operator^ (const Vec3d& v) const { return Vec3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

inline Vec3d operator* (const double a, const Vec3d& v) { return (Vec3d(a * v.x, a * v.y, a * v.z)); }
inline Vec3d operator* (const int a, const Vec3d& v) { return (Vec3d(a * v.x, a * v.y, a * v.z)); }



#endif // VEC3_H
