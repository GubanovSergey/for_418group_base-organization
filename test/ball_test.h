#ifndef BALL_TEST_H
#define BALL_TEST_H

#include "..\ball.h"

char return_after_place () {
    printf("Return_after_place\n\
-----------------------------------------\n\n");
    char succ_cnt = 0;

    Vector2D test_pos(10, -5.3d), test_speed(1, -1);
    Ball test_ball(130, test_pos, test_speed);

    Ball test_ball1 (50, test_pos);

    Vector2D delta_pos(10, 5.5d);
    test_pos += delta_pos;
    Ball test_ball2 (1000, test_pos, test_speed);

//Test 1
    Vector2D result_pos = test_ball.get_pos();
    Vector2D result_speed = test_ball.get_speed();

    printf("Ball_1 position: x = %g, y = %g\n", result_pos.x_, result_pos.y_);
    printf("Ball_1 speed   : x = %g, y = %g\n\n", result_speed.x_, result_speed.y_);

    if (result_pos.x_ == 10 && result_pos.y_ == -5.3d)
        printf ("\tPosition 1 success\n"), ++succ_cnt;

    if (result_speed.x_ == 1 && result_speed.y_ == -1)
        printf ("\tSpeed 1 success\n\n"), ++succ_cnt;

//Test 2
    result_pos = test_ball1.get_pos();
    result_speed = test_ball1.get_speed();

    printf("Ball_2 position: x = %g, y = %g\n", result_pos.x_, result_pos.y_);
    printf("Ball_2 speed   : x = %g, y = %g\n\n", result_speed.x_, result_speed.y_);

    if (result_pos.x_ == 10 && result_pos.y_ == -5.3d)
        printf ("\tPosition 2 success\n"), ++succ_cnt;

    if (result_speed.x_ == 0 && result_speed.y_ == 0)
        printf ("\tSpeed 2 success\n\n"), ++succ_cnt;

//Test 2
    result_pos = test_ball2.get_pos();
    result_speed = test_ball2.get_speed();

    printf("Ball_3 position: x = %g, y = %g\n", result_pos.x_, result_pos.y_);
    printf("Ball_3 speed   : x = %g, y = %g\n\n", result_speed.x_, result_speed.y_);

    if (result_pos.x_ == 20 && result_pos.y_ >= 0.19d && result_pos.y_ <= 0.21d)
        printf ("\tPosition 3 success\n"), ++succ_cnt;

    if (result_speed.x_ == 1 && result_speed.y_ == -1)
        printf ("\tSpeed 3 success\n\n"), ++succ_cnt;

    printf("End of test\n\
- - - - - - - - - - - - - - - - - - - - -\n\n");
    if (succ_cnt == 6)
        return 1;
    return 0;
}

char hit_the_target () {
    printf("Hit the target\n\
-----------------------------------------\n\n");
    char succ_cnt = 0;

    Vector2D pos, speed;
    Ball test_ball(130, {0, 0}, {0, 97.8d});
    test_ball.move_time(10);

//Test 1
    pos = test_ball.get_pos();
    speed = test_ball.get_speed();

    printf("Ball_1 position: x = %g, y = %g\n", pos.x_, pos.y_);
    printf("Ball_1 speed   : x = %g, y = %g\n\n", speed.x_, speed.y_);

    if (pos.x_ == 0 && pos.y_ >= 488.99d && pos.y_ <= 489.01d)
        printf ("Position 1 success\n"), ++succ_cnt;

    if (speed.x_ == 0 && speed.y_ >= -0.01d && speed.y_ <= 0.01d)
        printf ("Speed 1 success\n\n"), ++succ_cnt;

//Test 2
    test_ball.push(780, 0, 0.05);
    speed = test_ball.get_speed();

    printf("Ball_2 speed   : x = %g, y = %g\n\n", speed.x_, speed.y_);
    if (speed.x_ >= 299.99 && speed.x_ <= 300.01 &&
        speed.y_ >= -0.01d && speed.y_ <= 0.01d)
        printf ("Speed 2 success\n\n"), ++succ_cnt;

    test_ball.move_time(5);

    pos = test_ball.get_pos();
    speed = test_ball.get_speed();

    printf("Ball_3 position: x = %g, y = %g\n", pos.x_, pos.y_);
    printf("Ball_3 speed   : x = %g, y = %g\n\n", speed.x_, speed.y_);

    if (pos.x_ >= 1499.99 && pos.x_ <= 1500.01 && pos.y_ >= 366.74d && pos.y_ <= 366.76d)
        printf ("Position 3 success\n"), ++succ_cnt;

    if (speed.x_ >= 299.99 && speed.x_ <= 300.01 && speed.y_ >= -48.91d && speed.y_ <= -48.89d)
        printf ("Speed 3 success\n\n"), ++succ_cnt;

    printf("End of test\n\
- - - - - - - - - - - - - - - - - - - - -\n\n");
    if (succ_cnt == 5)
        return 1;
    return 0;
}
#endif //BALL_TEST_H

