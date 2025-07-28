#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <cmath>
#include <string>

// Ném lỗi nếu điều kiện sai
#define EXPECT_TRUE(cond) \
    if (!(cond))          \
        throw std::runtime_error(std::string("EXPECT_TRUE failed: ") + #cond);

// So sánh bằng
#define EXPECT_EQ(actual, expected)                        \
    if ((actual) != (expected))                            \
    {                                                      \
        std::ostringstream oss;                            \
        oss << "EXPECT_EQ failed:\n  actual: " << (actual) \
            << "\nexpected: " << (expected);               \
        throw std::runtime_error(oss.str());               \
    }                                                      \
    else                                                  \
    {                                                      \
        std::cout << "Test passed: " << #actual << " == " << #expected << std::endl; \
    }
/**
 * @class Point
 * @brief Represents a point in 3D coordinate system (Oxyz)
 */
class Point
{
private:
    double x, y, z;

public:
    Point() : x(0), y(0), z(0) {}

    Point(double x, double y) : x(x), y(y), z(0) {}

    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    Point(const Point &other) : x(other.x), y(other.y), z(other.z) {}

    double getX() const { return x; }

    double getY() const { return y; }

    double getZ() const { return z; }

    void setX(double newX) { x = newX; }

    void setY(double newY) { y = newY; }

    void setZ(double newZ) { z = newZ; }

    double distanceTo(const Point &other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }

    void translate(double dx, double dy, double dz)
    {
        x += dx;
        y += dy;
        z += dz;
    }

    Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y, z + other.z);
    }

    Point operator-(const Point &other) const
    {
        return Point(x - other.x, y - other.y, z - other.z);
    }

    Point operator*(double scalar) const
    {
        return Point(x * scalar, y * scalar, z * scalar);
    }

    bool operator==(const Point &other) const
    {
        const double EPSILON = 1e-9;
        return (fabs(x - other.x) < EPSILON) &&
               (fabs(y - other.y) < EPSILON) &&
               (fabs(z - other.z) < EPSILON);
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        os << "(" << point.x << "," << point.y << "," << point.z << ")";
        return os;
    }
};

#endif // __UTILS_H__
