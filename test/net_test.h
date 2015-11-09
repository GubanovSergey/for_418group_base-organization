#ifndef NET_TEST_H
#define NET_TEST_H

#include "..\ball.h"
#include "..\net.h"

char into_the_gum () {
    printf("Into the gum\n\
-----------------------------------------\n\n");
    char succ_cnt = 0;

    Ball test_ball(130, {0, 100}, {0, 0});
    ClogObject floor(100, {0, 0}, 0, {0, 0});
    double time = 0;

    do {
        time += 0.5;
        test_ball.move_time(0.5);
        printf("Ball position is %g, time = %g\n", test_ball.get_pos().y_, time);

        if (cmp (test_ball.get_pos().y_, 100 - (Ball::g) * time * time / 2, 0.001) == 0)
            printf("\tPosition %d successful\n\n", (int)(time/0.5)), succ_cnt++;
    } while (time < 4.5);

    time += 0.02215d;
    test_ball.move_time(0.02215);
    printf("Before position is %g, time = %g\n", test_ball.get_pos().y_, time);
    if (cmp (test_ball.get_pos().y_, 100 - (Ball::g) * time * time / 2, 0.001) == 0)
        printf("\tPosition 10 successful\n\n"), succ_cnt++;

    test_ball.collide(&floor);
    time += 0.5d;
    test_ball.move_time(0.5);
    printf("After position is %g, time = %g\n", test_ball.get_pos().y_, time);
    if (cmp (test_ball.get_pos().y_, floor.center_pos.y_, 0.001) == 0)
        printf("\tPosition 11 successful\n\n"), succ_cnt++;

printf("End of test\n\
- - - - - - - - - - - - - - - - - - - - -\n\n");
    if (succ_cnt == 11)
        return 1;
    return 0;
}
#endif //NET_TEST_H
