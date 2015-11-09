#ifndef BALL_H
#define BALL_H

#include <cmath>
#include <assert.h>
#include "objects.h"

void Ball::move_time (double dt) {
    using std::abs;
    short temp = 0;
    if (isy_blocked) {
        if ( (temp = abs_cmp(pos_.x_ + speed_.x_ *dt - blocked_by->center_pos.x_,\
                    blocked_by->char_size, 0.001)) == -1)
            pos_.x_ += speed_.x_ * dt;
        else if (temp == 1) {
            assert(0);
            double delta1 = 0;
            delta1 = abs(blocked_by->center_pos.x_ - pos_.x_) / abs(speed_.x_);
            //TODO check unblocking y
            pos_.x_ += speed_.x_ * delta1;
            isy_blocked = 0;
            dt -= delta1;
        }
    }
    else {
        double v0 = speed_.y_;
        speed_.y_ -= g * dt;
        pos_.x_ += speed_.x_ * dt;
        pos_.y_ += (v0 + speed_.y_) / 2 * dt;
    }
}

void Ball::collide (const ClogObject * with) {
    Vector2D its_pos = with->center_pos;
    unsigned its_size = with->char_size;

    if (with->angle != 0 && with->angle != 90)
        assert(("Collision with optional oriented objects \
hasn't been realized yet. Only vertical or horizontal are supported", 0));
    else if (with->angle == 0) {
        if (pos_.y_ - its_pos.y_ > 0.001 ||           //TODO to sync with phys core
            pos_.y_ - its_pos.y_ < -0.001 ||
            (pos_.x_ - its_pos.x_) > its_size ||
            (-pos_.x_ + its_pos.x_) > its_size)
            assert (("Collision between too far objects was called", 0));   //TODO handling error
    }
    else {
        if (pos_.x_ - its_pos.x_ > 0.001 ||           //TODO to sync with phys core
            pos_.x_ - its_pos.x_ < -0.001 ||
            pos_.y_ - its_pos.y_ > its_size ||
            - pos_.y_ + its_pos.y_ > its_size)
            assert (("Collision between too far objects was called", 0));   //TODO handling error
    }

    speed_.x_ *= -with->elast.x_;
    if (with->angle == 0 && with->elast.y_ < 0.001d) {
        speed_.y_ = 0;
        isy_blocked = 1;
        blocked_by = with;
    }
    else
        speed_.y_ *= - with->elast.y_;
}

#endif //BALL_H
