/** @file "/vdjml/lib/test/sample_data.hpp"
part of VDJML project.
Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef SAMPLE_DATA_HPP_
#define SAMPLE_DATA_HPP_
#include <string>
#include "boost/preprocessor/stringize.hpp"
#include "boost/filesystem.hpp"

#ifndef SAMPLE_DATA_DIR
#error SAMPLE_DATA_DIR needs to be defined
#endif
#ifndef TEMPORARY_DIR
#error TEMPORARY_DIR needs to be defined
#endif

namespace vdjml{ namespace test{

/**@return full path to file in project's sample data directory
*******************************************************************************/
inline std::string sample_file_path(const std::string& name = "") {
   static const boost::filesystem::path path(BOOST_PP_STRINGIZE(SAMPLE_DATA_DIR));
   return canonical(path / name).string();
}

/**@return full path to file in project's temporary directory
*******************************************************************************/
inline std::string temp_file_path(const std::string& name = "") {
   static const boost::filesystem::path path =
            canonical(
                     boost::filesystem::path(BOOST_PP_STRINGIZE(TEMPORARY_DIR))
            );
   return (path / name).string();
}

}//namespace test
}//namespace vdjml
#endif /* SAMPLE_DATA_HPP_ */
