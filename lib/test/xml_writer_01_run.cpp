/** @file "/vdjml/lib/test/xml_writer_01_run.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#define BOOST_TEST_MODULE xml_writer_01_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "vdjml/xml_writer.hpp"
#include <iostream>

namespace vdjml{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**@test 
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   Xml_writer xw(std::cout);
   xw.open("element1", ELEM, "http://some.uri.com", "pref");
   xw.open("element2", ELEM);
   xw.value("val1");
   xw.close();
   xw.open("element3", ELEM);
   xw.open("atr1", ATTR, "", "pref");
   xw.value("val2");
   xw.close();
   xw.value("val3");
   xw.close();
   xw.close();

//   BOOST_ERROR("");
}

}//namespace test
}//namespace vdjml
