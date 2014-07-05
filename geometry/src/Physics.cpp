void Physics::recalculateVelocityAfterCollision(Vec2& v1, Vec2& v2, const double m1, const double m2, const double cor)
{
    Vec2 u1 = v1;
    Vec2 u2 = v2;
    Vec2 a = u1 * m1 + u2 * m2;
    double d = (m1 + m2);
    v1 = (((u2 - u1) * m2 * cor) + a) / d;
    v2 = (((u1 - u2) * m1 * cor) + a) / d;
}
void Physics::recalculateVelocityAfterCollision(const Vec2& v1, const Vec2& v2, Vec2& rv1, Vec2& rv2, const double m1, const double m2, const double cor)
{
    double d = (m1 + m2);
    Vec2 a = v1 * m1 + v2 * m2;
    rv1 = (((v2 - v1) * m2 * cor) + a) / d;
    rv2 = (((v1 - v2) * m1 * cor) + a) / d;
}

void Physics::recalculateVelocityAfterCollision(Vec2& v1, Vec2& v2, const Vec2& hitVector, const double m1, const double m2, const double cor)
{
    double  m21, dvx2, a, vx21, vy21, vx_cm, vy_cm; //brzydkie ale dziala
    Vec2 newHitVector = hitVector;
    if(newHitVector.x == 0.0f) newHitVector.x = 0.00001f; //== rerquired
    m21 = m2 / m1;
    vx21 = v2.x - v1.x;
    vy21 = v2.y - v1.y;
    vx_cm = (m1 * v1.x + m2 * v2.x) / (m1 + m2) ;
    vy_cm = (m1 * v1.y + m2 * v2.y) / (m1 + m2) ;
    a = newHitVector.y / newHitVector.x;
    dvx2 = -2.0f * (vx21 + a * vy21) / ((1 + a * a) * (1 + m21)) ;
    v2.x = v2.x + dvx2;
    v2.y = v2.y + a * dvx2;
    v1.x = v1.x - m21 * dvx2;
    v1.y = v1.y - a * m21 * dvx2;
    v1.x = (v1.x - vx_cm) * cor + vx_cm;
    v1.y = (v1.y - vy_cm) * cor + vy_cm;
    v2.x = (v2.x - vx_cm) * cor + vx_cm;
    v2.y = (v2.y - vy_cm) * cor + vy_cm;
}
void Physics::recalculateVelocityAfterCollision(const Vec2& v1, const Vec2& v2, const Vec2& hitVector, Vec2& rv1, Vec2& rv2, const double m1, const double m2, const double cor)
{
    double  m21, dvx2, a, vx21, vy21, vx_cm, vy_cm; //brzydkie ale dziala
    m21 = m2 / m1;
    vx21 = v2.x - v1.x;
    vy21 = v2.y - v1.y;
    vx_cm = (m1 * v1.x + m2 * v2.x) / (m1 + m2) ;
    vy_cm = (m1 * v1.y + m2 * v2.y) / (m1 + m2) ;
    a = hitVector.y / hitVector.x;
    dvx2 = -2.0f * (vx21 + a * vy21) / ((1 + a * a) * (1 + m21)) ;
    rv2.x = v2.x + dvx2;
    rv2.y = v2.y + a * dvx2;
    rv1.x = v1.x - m21 * dvx2;
    rv1.y = v1.y - a * m21 * dvx2;
    rv1.x = (rv1.x - vx_cm) * cor + vx_cm;
    rv1.y = (rv1.y - vy_cm) * cor + vy_cm;
    rv2.x = (rv2.x - vx_cm) * cor + vx_cm;
    rv2.y = (rv2.y - vy_cm) * cor + vy_cm;
}
