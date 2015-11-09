#ifndef OBJECTS_H
#define OBJECTS_H

namespace some_operations {
    int cmp(double a, double b, double discret /*TODO= some_var from core*/) {
        if (a - b < discret && b - a < discret)
            return 0;
        else if (a > b)
            return 1;
        else return -1;
    }
    int abs_cmp (double a, double b, double discret /*TODO= some_var from core*/) {
        int temp = cmp (a, b, discret);
        if (temp == 0)
            return 0;
        return (((temp > 0) ? a : b) > 0) ? temp : -temp;
    }
}

using namespace some_operations;

struct Vector2D {
    double x_, y_;

public:
    Vector2D (double x = 0, double y = 0):
        x_ (x), y_ (y) {}
    Vector2D & operator += (const Vector2D & rhs) {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }
};

struct ClogObject {
    Vector2D center_pos;
    const char angle;      //from null to 179 degrees
    const double char_size;    //in meters
    const Vector2D elast;

    explicit ClogObject (unsigned characteristic_size, Vector2D center_position = {0, 0},\
                         char x_angle = 90, Vector2D elasticity = {1, 1});
};

struct Net: public ClogObject {
public:
    const double trans;

    explicit Net (double x_pos, unsigned floor_height, unsigned height /*= floor_height*/,  //NOTE how to do it?
                  double transparence = 0, double elasticity = 0);
};

class Ball {
    Vector2D pos_;          //meters
    Vector2D speed_;        //meters/sec
//specific
    unsigned short isy_blocked;
    const ClogObject * blocked_by;

public:
    const unsigned mass_;   //in grams
    void init (Vector2D pos) {
        pos_ = pos;
        speed_.x_ = 0, speed_.y_ = 0;
        isy_blocked = 0;
    }
    void push (double force, double angle, double dt) {
        speed_.x_ += force * dt * cos(angle) * 1000 / mass_;     //TODO sync with simulation module to correctly perform a push
        speed_.y_ += force * dt * sin(angle) * 1000 / mass_;
    }
    void move_time (double dt);
    const Vector2D & get_pos () const {
        return pos_;
    }
    const Vector2D & get_speed () const {
        return speed_;
    }

    Ball (unsigned mass, Vector2D init_pos, Vector2D init_speed = {0, 0}):
        pos_ (init_pos),
        speed_ (init_speed),
        isy_blocked(0),
        mass_ (mass)    {}

    void collide (const ClogObject * with);
    static constexpr double g = 9.78;
};

#endif //OBJECTS_H
