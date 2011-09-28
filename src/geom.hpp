#ifndef GEOM_HPP
#define GEOM_HPP

#include <iostream>

struct Vector;

struct Point {
    double x, y, z;

    Point() :
        x(0.0), y(0.0), z(0.0) {
    }

    Point(double x, double y, double z) :
        x(x), y(y), z(z) {
    }

    Point(const Point& other) :
        x(other.x), y(other.y), z(other.z) {
    }

    bool operator== (const Point& other);
    bool operator!= (const Point& other);

    Point operator+ (const Vector& other);
    Point operator- (const Vector& other);

    Vector operator- (const Point& other);

    friend std::ostream& operator<< (std::ostream& o, const Point& point);
};

struct Vector {
    double dx, dy, dz;

    Vector() :
        dx(0.0), dy(0.0), dz(0.0) {
    }

    Vector(double dx, double dy, double dz) :
        dx(dx), dy(dy), dz(dz) {
    }

    Vector(const Vector& other) :
        dx(other.dx), dy(other.dy), dz(other.dz) {
    }

    double length();
    double dot(const Vector& other);
    Vector cross(const Vector& other);
    Vector unit();

    bool operator== (const Vector& other);
    bool operator!= (const Vector& other);

    Vector operator+ (const Vector& other);
    Vector operator- (const Vector& other);

    Vector operator* (double other);
    Vector operator/ (double other);

    friend std::ostream& operator<< (std::ostream& o, const Vector& vector);
};

inline Vector operator- (const Vector& v) {
    return Vector(-v.dx, -v.dy, -v.dz);
}

inline Vector operator* (double lhs, Vector rhs) {
    return rhs * lhs;
}

inline Vector operator/ (double lhs, Vector rhs) {
    return rhs / lhs;
}

struct Matrix3 {
    double values[9];

    Matrix3();

    // Equivalent to the matlab: m3 = vec1 * vec2'
    Matrix3(const Vector &vec1, const Vector &vec2);

    static Matrix3 identity();

    Matrix3 transpose();
    Vector col(int num);

    Vector operator* (const Vector &other);
    Matrix3 operator+ (const Matrix3 &other);
    Matrix3 operator- (const Matrix3 &other);
    Matrix3 operator* (double other);
    Matrix3 operator* (const Matrix3 &other);
};

inline Matrix3 operator* (double lhs, Matrix3 rhs) {
    return rhs * lhs;
}

inline Matrix3 operator/ (Matrix3 lhs, double rhs) {
    return lhs * (1.0 / rhs);
}

inline Matrix3 operator/ (double lhs, Matrix3 rhs) {
    return rhs / lhs;
}

#endif
