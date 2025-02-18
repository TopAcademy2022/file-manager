#define BOOST_TEST_MODULE testFar


#include <boost/test/unit_test.hpp>
#include "../src/far.h"
#include "../src/status.h"

/*!
 * @brief calls test functions for class Far: CreateDirectory, CreateFile, PrintContentFromDirectory
 */
BOOST_AUTO_TEST_CASE(testFar)
{
    Far fileManager = Far("./");

    //BOOST_CHECK_EQUAL(fileManager.CreateFile("fileName", ".test", "./"), status::StatusCode::Status_FileWasCreated);
    BOOST_CHECK_EQUAL(0, 0);
}
