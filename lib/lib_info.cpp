/** @file "/vdjml/lib/lib_info.cpp"
part of VDJML project.
Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif

#include "vdjml/lib_info.hpp"
#include <sstream>
#include "boost/preprocessor/stringize.hpp"

#ifndef VDJML_NAME
#define VDJML_NAME VDJML
#endif

#ifndef VDJML_DESCRIPTION
#define VDJML_DESCRIPTION
#endif

#ifndef VDJML_VERSION_1
#define VDJML_VERSION_1 0
#endif

#ifndef VDJML_VERSION_2
#define VDJML_VERSION_2 0
#endif

#ifndef VDJML_VERSION_3
#define VDJML_VERSION_3 0
#endif

#ifndef VDJML_VERSION_EXTRA
#define VDJML_VERSION_EXTRA ???
#endif

#ifndef VDJML_VERSION_DIRTY
#define VDJML_VERSION_DIRTY 0
#endif

#ifndef VDJML_BUILD
#define VDJML_BUILD 0
#endif

namespace vdjml{ namespace{
std::string make_version_str() {
   std::ostringstream str;
   str
   << 'v' << VDJML_VERSION_1 << '.'
   << VDJML_VERSION_2 << '.' << VDJML_VERSION_3
   ;
   const std::string e = std::string(BOOST_PP_STRINGIZE(VDJML_VERSION_EXTRA));
   if( ! e.empty() ) str << '-' << e;
   if( VDJML_VERSION_DIRTY ) str << '~';
   return str.str();
}
}//namespace anonymous


/*
*******************************************************************************/
std::string const& Lib_info::name() {
   static const std::string s = std::string(BOOST_PP_STRINGIZE(VDJML_NAME));
   return s;
}

/*
*******************************************************************************/
std::string const& Lib_info::version() {
   static const std::string s = make_version_str();
   return s;
}

/*
*******************************************************************************/
std::string const& Lib_info::description() {
   static const std::string s = std::string(BOOST_PP_STRINGIZE(VDJML_DESCRIPTION));
   return s;
}

/*
*******************************************************************************/
int Lib_info::version_1() {return VDJML_VERSION_1;}

/*
*******************************************************************************/
int Lib_info::version_2() {return VDJML_VERSION_2;}

/*
*******************************************************************************/
int Lib_info::version_3() {return VDJML_VERSION_3;}

/*
*******************************************************************************/
std::string const& Lib_info::version_e() {
   static const std::string s = std::string(BOOST_PP_STRINGIZE(VDJML_VERSION_EXTRA));
   return s;
}

/*
*******************************************************************************/
int Lib_info::build() {return VDJML_BUILD;}


}//namespace vdjml
