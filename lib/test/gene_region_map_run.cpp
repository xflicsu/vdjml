/** @file "/vdjml/lib/test/gene_region_map_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE gene_region_map_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "vdjml/gene_region_type_map.hpp"

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**@test 
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Gene_region_map grm;
   BOOST_CHECK_EQUAL(Gene_region_map::fr1().second, "FR1");
   BOOST_CHECK_EQUAL(grm[Gene_region_map::fr1().first], "FR1");
}

}//namespace test
}//namespace vdjml
