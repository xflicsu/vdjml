/** @file "/vdjml/lib/test/exception_fixture.hpp"
part of VDJML project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Author Mikhail K Levin 2013
*******************************************************************************/
#ifndef EXCEPTION_FIXTURE_HPP_
#define EXCEPTION_FIXTURE_HPP_
#include <iostream>
#include "boost/test/unit_test_monitor.hpp"
#include "vdjml/exception.hpp"

namespace vdjml{ namespace test{ namespace detail{

void translate(boost::exception const& e) {
   std::cerr << boost::diagnostic_information(e) << std::endl;
   throw boost::enable_current_exception(e);
}
}//namespace detail

/** Test fixture for printing exception info
*******************************************************************************/
struct Exception_fixture {
   Exception_fixture() {
      ::boost::unit_test::unit_test_monitor.
      register_exception_translator<boost::exception>(&detail::translate);
   }
};

}//namespace test
}//namespace vdjml
#endif /* EXCEPTION_FIXTURE_HPP_ */
