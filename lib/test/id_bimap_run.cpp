/** @file "/vdjml/lib/test/id_bimap_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE id_bimap_run
#include "boost/test/unit_test.hpp"
#include <string>
#include "test/exception_fixture.hpp"
#include "vdjml/detail/id_bimap.hpp"
#include "vdjml/object_ids.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**@test 
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   typedef vdjml::detail::Id_bimap<Region_id, std::string> map_t;
   map_t m1(Region_id(1));
   m1.insert(Region_id(1), "name1");
   m1.insert(Region_id(2), "name2");
   BOOST_CHECK_EQUAL(m1.size(), 2);
   BOOST_CHECK_EQUAL(m1[Region_id(1)], "name1");
   BOOST_CHECK_EQUAL(m1[Region_id(2)], "name2");
}

}//namespace test
}//namespace vdjml
