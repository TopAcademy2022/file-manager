#define BOOST_TEST_MODULE testMain


#include <boost/test/unit_test.hpp>
#include "../src/main.cpp"

BOOST_AUTO_TEST_CASE(testMain)
{
    BOOST_CHECK_EQUAL(main(), 0);
}
