#define BOOST_TEST_MODULE testMain


#include <boost/test/unit_test.hpp>
#include "../src/main.cpp"

/*!
* @brief Defines a test case named "testMain".
*/
BOOST_AUTO_TEST_CASE(testMain)
{
	/*!
	* @brief A check that is performed within a test case.
	*/
    BOOST_CHECK_EQUAL(main(), 0);
}
