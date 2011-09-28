#include <cmath>

#include "geom.hpp"


bool Point::operator== (const Point&  other) {
    return ( (x == other.x) && (y == other.y) && (z == other.z) );
}

bool Point::operator!= (const Point& other) {
    return ! (*this == other);
}

Point Point::operator+ (const Vector& other) {
    return Point(x + other.dx, y + other.dy, z + other.dz);
}

Point Point::operator- (const Vector& other) {
    return (*this + (-other));
}

Vector Point::operator- (const Point& other) {
    return Vector(x - other.x, y - other.y, z - other.z);
}

std::ostream& operator<< (std::ostream& o, const Point& point) {
    return o << "(" << point.x << ", " << point.y << ", " << point.z << ")";
}



double Vector::length() {
    return sqrt(this->dot(*this));
}

double Vector::dot(const Vector& other) {
    return (dx * other.dx) + (dy * other.dy) + (dz * other.dz);
}

Vector Vector::cross(const Vector& other) {
    return Vector(
        dy * other.dz - dz * other.dy,
        dz * other.dx - dx * other.dz,
        dx * other.dy - dy * other.dx
    );
}

Vector Vector::unit() {
    return *this / this->length();
}

bool Vector::operator== (const Vector& other) {
    return ( (dx == other.dx) && (dy == other.dy) && (dz == other.dz) );
}

bool Vector::operator!= (const Vector& other) {
    return ! (*this == other);
}

Vector Vector::operator+ (const Vector& other) {
    return Vector(dx + other.dx, dy + other.dy, dz + other.dz);
}

Vector Vector::operator- (const Vector& other) {
    return *this + (-other);
}

Vector Vector::operator* (double other) {
    return Vector(dx * other, dy * other, dz * other);
}

Vector Vector::operator/ (double other) {
    return Vector(dx / other, dy / other, dz / other);
}

std::ostream& operator<< (std::ostream& o, const Vector& vector) {
    return o << "(" << vector.dx << ", " << vector.dy << ", " << vector.dz << ")";
}


Matrix3::Matrix3() {
    values[0] = values[1] = values[2] = 0.0;
    values[3] = values[4] = values[5] = 0.0;
    values[6] = values[7] = values[8] = 0.0;
}

Matrix3::Matrix3(const Vector &vec1, const Vector &vec2) {
    values[0] = vec1.dx * vec2.dx;
    values[1] = vec1.dx * vec2.dy;
    values[2] = vec1.dx * vec2.dz;
    values[3] = vec1.dy * vec2.dx;
    values[4] = vec1.dy * vec2.dy;
    values[5] = vec1.dy * vec2.dz;
    values[6] = vec1.dz * vec2.dx;
    values[7] = vec1.dz * vec2.dy;
    values[8] = vec1.dz * vec2.dz;
}

Matrix3 Matrix3::identity() {
    Matrix3 I = Matrix3();
    I.values[0] = I.values[4] = I.values[8] = 1.0;
    return I;
}

Vector Matrix3::operator*(const Vector &other) {
    double dx = values[0] * other.dx + values[1] * other.dy + values[2] * other.dz;
    double dy = values[3] * other.dx + values[4] * other.dy + values[5] * other.dz;
    double dz = values[6] * other.dx + values[7] * other.dy + values[8] * other.dz;
    return Vector(dx, dy, dz);
}

Matrix3 Matrix3::operator+(const Matrix3 &other) {
    Matrix3 m = Matrix3();
    for (int i = 0; i < 9; i++) {
        m.values[i] = values[i] - other.values[i];
    }
    return m;
}

Matrix3 Matrix3::operator-(const Matrix3 &other) {
    Matrix3 m = Matrix3();
    for (int i = 0; i < 9; i++) {
        m.values[i] = values[i] - other.values[i];
    }
    return m;
}

Matrix3 Matrix3::operator* (double other) {
    Matrix3 m = Matrix3();
    for (int i = 0; i < 9; i++) {
        m.values[i] = values[i] * other;
    }
    return m;
}

Matrix3 Matrix3::operator* (const Matrix3 &other) {
    Matrix3 m = Matrix3();

    m.values[0] = values[0] * other.values[0]
                + values[1] * other.values[3]
                + values[2] * other.values[6];

    m.values[1] = values[0] * other.values[1]
                + values[1] * other.values[4]
                + values[2] * other.values[7];

    m.values[2] = values[0] * other.values[2]
                + values[1] * other.values[5]
                + values[2] * other.values[8];

    m.values[3] = values[3] * other.values[0]
                + values[4] * other.values[3]
                + values[5] * other.values[6];

    m.values[4] = values[3] * other.values[1]
                + values[4] * other.values[4]
                + values[5] * other.values[7];

    m.values[5] = values[3] * other.values[2]
                + values[4] * other.values[5]
                + values[5] * other.values[8];

    m.values[6] = values[6] * other.values[0]
                + values[7] * other.values[3]
                + values[8] * other.values[6];

    m.values[7] = values[6] * other.values[1]
                + values[7] * other.values[4]
                + values[8] * other.values[7];

    m.values[8] = values[6] * other.values[2]
                + values[7] * other.values[5]
                + values[8] * other.values[8];

    return m;
}

Matrix3 Matrix3::transpose() {
    Matrix3 m = Matrix3();

    m.values[0] = values[0];
    m.values[1] = values[3];
    m.values[2] = values[6];
    m.values[3] = values[1];
    m.values[4] = values[4];
    m.values[5] = values[7];
    m.values[6] = values[2];
    m.values[7] = values[5];
    m.values[8] = values[8];

    return m;
}

Vector Matrix3::col(int num) {
    switch (num) {
        case 0:
            return Vector(values[0], values[3], values[6]);
        case 1:
            return Vector(values[1], values[4], values[7]);
        case 2:
            return Vector(values[2], values[5], values[8]);
        default:
            return Vector();
    }
}
