#ifndef NET_H
#define NET_H

#include <assert.h>
#include "objects.h"

ClogObject::ClogObject (unsigned characteristic_size, Vector2D center_position,\
                         char x_angle, Vector2D elasticity):
    center_pos (center_position),
    angle (x_angle),
    char_size (characteristic_size * 1. / 1000),
    elast (elasticity) {
        if (elasticity.x_ < 0 || elasticity.y_ < 0 ||
        elasticity.x_ > 1 || elasticity.y_ > 1)
            assert(("Wrong input (ClogObject.Elasticity)", 0));
    }

Net::Net (double x_pos, unsigned floor_height, unsigned height,
                  double transparence, double elasticity):
    ClogObject(height / 2, {x_pos, floor_height - (double)height / 2},\
              90, {elasticity, 0}),
    trans (transparence) {
        if (floor_height < height)
            assert(("Wrong input (Net.Height,Floor_Height)", 0));
        if (transparence < 0 || transparence > 1)
            assert(("Wrong input (Net.Transparence)", 0));
    }

#endif //NET_H
