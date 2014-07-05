#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

class Physics
{
public:
    static void recalculateVelocityAfterCollision(Vec2& v1, Vec2& v2, const double m1 = 1.0f, const double m2 = 1.0f, const double cor = 1.0f);
    static void recalculateVelocityAfterCollision(const Vec2& v1, const Vec2& v2, Vec2& rv1, Vec2& rv2, const double m1 = 1.0f, const double m2 = 1.0f, const double cor = 1.0f);

    static void recalculateVelocityAfterCollision(Vec2& v1, Vec2& v2, const Vec2& hitVector, const double m1 = 1.0f, const double m2 = 1.0f, const double cor = 1.0f);
    static void recalculateVelocityAfterCollision(const Vec2& v1, const Vec2& v2, const Vec2& hitVector, Vec2& rv1, Vec2& rv2, const double m1 = 1.0f, const double m2 = 1.0f, const double cor = 1.0f);
private:
    Physics() {}
};

#endif // PHYSICS_H_INCLUDED
