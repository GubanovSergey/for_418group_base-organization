#include <stdio.h>
#define ALL_TEST



#ifdef ALL_TEST
    #define BALL_TEST
    #define NET_TEST

#ifdef BALL_TEST
    #include "ball_test.h"
#endif

#ifdef NET_TEST
    #include "net_test.h"
#endif

#endif

void unit_test() {
    unsigned fine = 1;

#ifdef BALL_TEST
    printf("Ball tests\n\
===================================================\n\n");

    fine &= return_after_place();
    fine &= hit_the_target();

    printf("End of tests\n\
= = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
#endif

#ifdef NET_TEST
    printf("Net tests\n\
===================================================\n\n");

    fine &= into_the_gum();

    printf("End of tests\n\
= = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
#endif

    if (fine)
        printf("\
________´$$$$`______________________________,,_ \n\
_______´$$$$$$$`__________________________´$$$`  \n\
________`$$$$$$$`______,,________,,______´$$$$´\n\
_________`$$$$$$$`____´$$`_____´$$`____´$$$$$´  \n\
__________`$$$$$$$`_´$$$$$`_´$$$$$`__´$$$$$$$´  \n\
___________`$$$$$$$_$$$$$$$_$$$$$$$_´$$$$$$$´_  \n\
____________`$$$$$$_$$$$$$$_$$$$$$$`´$$$$$$´_   \n\
__,,,,______`$$$$$$_$$$$$$$_$$$$$$$_$$$$$$´_    \n\
_´$$$$$`____`$$$$$$_$$$$$$$_$$$$$$$_$$$$$$´_    \n\
´$$$$$$$$$`´$$$$$$$_$$$$$$$_$$$$$$$_$$$$$´_     \n\
´$$$$$$$$$$$$$$$$$$_$$$$$$$_$$$$$$$_$$$$$´_     \n\
___`$$$$$$$$$$$$$$$_$$$$$$$_$$$$$$_$$$$$$´_     \n\
______`$$$$$$$$$$$$$_$$$$$__$$_$$$$$$_$$´_      \n\
_______`$$$$$$$$$$$$,___,$$$$,____,$$$$$´_      \n\
_________`$$$$$$$$$$$$$$$$$$$$$$$$$$$$$´_       \n\
__________`$$$$$$$$$$$$$$$$$$$$$$$$$$$´_        \n\
____________`$$$$$$$$$$$$$$$$$$$$$$$$´_         \n\
_______________`$$$$$$$$$$$$$$$$$$$$´_          \n\
 \n\n");

}


