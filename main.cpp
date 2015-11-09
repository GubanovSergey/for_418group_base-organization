#include <iostream>
#define TEST




#ifdef TEST
    #include "test\test.cpp"
#endif

int main()
{

#ifdef TEST
    unit_test();
#endif
    std::cout << "Hello world!" << std::endl;
    return 0;
}
