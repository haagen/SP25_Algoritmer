
#include <algorithm>    // to be able to use min and max
#include <iostream>

using namespace std;

struct AABB
{
    float x, y; // Upper left
    float width, height;

    float left() const { return x; }
    float right() const { return x + width; }
    float top() const { return y; }
    float bottom() const { return y - height; }
};

struct Circle
{
    float x, y; // Center
    float radius;
};

float clamp(float value, float min, float max)
{
    return std::max(min, std::min(value, max));
}

bool isColliding(const AABB& a, const AABB& b)
{
    return (
        a.right() > b.left() &&
        a.left() < b.right() &&
        a.bottom() < b.top() &&
        a.top() > b.bottom()
        );
}

bool isColliding(const Circle& a, const Circle& b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float distSq = dx * dx + dy * dy; // x^2 + y^2
    float radiusSq = (a.radius + b.radius) * (a.radius + b.radius);
    return distSq <= radiusSq;
}

bool isColliding(const Circle& circle, const AABB& box)
{
    float closestX = clamp(circle.x, box.left(), box.right());
    float closestY = clamp(circle.y, box.bottom(), box.top());
    
    float dx = circle.x - closestX;
    float dy = circle.y - closestY;
    float distanceSq = dx * dx + dy * dy;
    float radiusSq = circle.radius * circle.radius;

    return distanceSq <= radiusSq;
}

int main(int argc, char* argv[])
{
    AABB a, b;
    a.x = 1, a.y = 2, a.height = 1, a.width = 1;
    b.x = 3, b.y = 3, b.height = 1, b.width = 1;
    cout << "1. Is a and b colliding? " << isColliding(a, b) << "\n";

    b.x = 1.5, b.y = 2.5;
    cout << "2. Is a and b colliding? " << isColliding(a, b) << "\n";

    Circle c1, c2;
    c1.x = 5, c1.y = 1, c1.radius = 1;
    c2.x = 5, c2.y = 5, c2.radius = 1; 

    cout << "3. Is c1 and c2 colliding? " << isColliding(c1, c2) << "\n";

    c2.x = 6, c2.y = 2;
    cout << "4. Is c1 and c2 colliding? " << isColliding(c1, c2) << "\n";

    cout << "5. Is a and c1 colliding? " << isColliding(c1, a) << "\n";
    a.x = 1, a.y = 2, a.height = 1, a.width = 1;
    c1.x = 2.5, c1.y = 1, c1.radius = 1;
    cout << "6. Is a and c1 colliding? " << isColliding(c1, a) << "\n";
    
    return 0;
}
