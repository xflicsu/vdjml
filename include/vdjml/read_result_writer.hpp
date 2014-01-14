/** @file "/vdjml/include/vdjml/read_result_writer.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef READ_RESULT_WRITER_HPP_
#define READ_RESULT_WRITER_HPP_
#include <string>
#include <fstream>
#include "boost/iostreams/filtering_streambuf.hpp"
#include "boost/noncopyable.hpp"
#include "boost/scoped_ptr.hpp"
#include "vdjml/config.hpp"
#include "vdjml/exception.hpp"
#include "vdjml/xml_writer.hpp"
#include "vdjml/vdjml_current_version.hpp"

namespace vdjml{
class Read_result;
class Results_meta;

enum Compression {
   Uncompressed, Unknown_compression, gzip,
   bzip2, zlib
};

/**@brief Incrementally serialize VDJ alignment results
*******************************************************************************/
class VDJML_DECL Read_result_writer : boost::noncopyable {
   typedef boost::scoped_ptr<std::ostream> os_ptr;
   typedef boost::scoped_ptr<std::ofstream> ofs_ptr;
   typedef boost::iostreams::filtering_ostreambuf fosb_t;
   typedef boost::scoped_ptr<fosb_t> fosb_ptr;

   static Compression guess_compression(std::string const& path);

   static std::ofstream* make_ofstream(
            std::string const& path,
            Compression& compr
   );

   static fosb_t* make_fosb(const Compression compr, std::ostream& os);

public:
   struct Err : public base_exception {};

   /** write to stream */
   Read_result_writer(
            std::ostream& os,
            Results_meta const& rm,
            Compression compr,
            const unsigned version = VDJML_CURRENT_VERSION,
            Xml_writer_options const& opts = Xml_writer_options()
   );

   /** write to file */
   Read_result_writer(
            std::string const& path,
            Results_meta const& rm,
            Compression compr = Unknown_compression,
            const unsigned version = VDJML_CURRENT_VERSION,
            Xml_writer_options const& opts = Xml_writer_options()
   );

   void operator() (Read_result const& rr);

private:
   Results_meta const& rm_;
   ofs_ptr ofs_;
   fosb_ptr fosb_;
   os_ptr os_;
   Xml_writer xw_;
   unsigned version_;

   void init_xml();

};

}//namespace vdjml
#endif /* READ_RESULT_WRITER_HPP_ */
