/** @file "/vdjml/lib/read_result_writer.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/read_result_writer.hpp"

#include "boost/filesystem.hpp"
namespace bfs = boost::filesystem;
#include "boost/algorithm/string/case_conv.hpp"
#include "boost/iostreams/filter/gzip.hpp"
#include "boost/iostreams/filter/bzip2.hpp"
#include "boost/iostreams/filter/zlib.hpp"

#include "vdjml/results_meta.hpp"
#include "vdjml/read_result.hpp"
#include "vdjml/vdjml_version.hpp"

namespace vdjml {

/*
*******************************************************************************/
Compression Read_result_writer::guess_compression(std::string const& path) {
   boost::filesystem::path p(path);
   std::string ext = p.extension().string();
   boost::algorithm::to_lower(ext);
   if( ext == ".gz") return gzip;
   if( ext == ".z") return zlib;
   if( ext == ".bz2") return bzip2;
   return Uncompressed;
}

/*
*******************************************************************************/
std::ofstream* Read_result_writer::make_ofstream(
            std::string const& path,
            Compression& compr
) {
   static const std::ios_base::openmode bin_mode =
            std::ios_base::out | std::ios_base::trunc | std::ios_base::binary;

   static const std::ios_base::openmode txt_mode =
            std::ios_base::out | std::ios_base::trunc;

   if( compr == Unknown_compression ) compr = guess_compression(path);

   const std::ios_base::openmode mode =
            (compr == Uncompressed) ? txt_mode : bin_mode;

   return new std::ofstream(path.c_str(), mode);
}

/*
*******************************************************************************/
Read_result_writer::fosb_t*
Read_result_writer::make_fosb(const Compression compr, std::ostream& os) {
   if( compr == Uncompressed ) return 0;
   fosb_t* fosb = new fosb_t;
   switch (compr) {
      case Uncompressed:
         break;
      case bzip2:
         fosb->push(boost::iostreams::bzip2_compressor());
         break;
      case gzip:
         fosb->push(boost::iostreams::gzip_compressor());
         break;
      case zlib:
         fosb->push(boost::iostreams::zlib_compressor());
         break;
      default:
         BOOST_THROW_EXCEPTION(
                  Err()
                  << Err::msg_t("unsupported compression")
                  << Err::int1_t(compr)
         );
   }
   fosb->push(os);
   return fosb;
}

/*
*******************************************************************************/
Read_result_writer::Read_result_writer(
         std::ostream& os,
         Results_meta const& rm,
         Compression compr,
         const unsigned version,
         Xml_writer_options const& opts
)
: rm_(rm),
  ofs_(0),
  fosb_(make_fosb(compr, os)),
  os_(fosb_ ? new std::ostream(&(*fosb_)) : 0),
  xw_(os_ ? *os_ : os, opts)
{
   init_xml();
}

/*
*******************************************************************************/
Read_result_writer::Read_result_writer(
         std::string const& path,
         Results_meta const& rm,
         Compression compr,
         const unsigned version,
         Xml_writer_options const& opts
)
: rm_(rm),
  ofs_(make_ofstream(path, compr)),
  fosb_(make_fosb(compr, *ofs_)),
  os_(fosb_ ? new std::ostream(&(*fosb_)) : 0),
  xw_(os_ ? *os_ : *ofs_, opts),
  version_(version)
{
   init_xml();
}

/*
*******************************************************************************/
void Read_result_writer::init_xml() {
   if( ! is_supported(version_) ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("unsupported VDJML version")
            << Err::str1_t(version_string(version_))
   );

   xw_.open("vdjml_results", ELEM, VDJML_NAMESPACE_URI);
   xw_.node("version", ATTR, version_string(version_));
   write(xw_, rm_, version_);
   xw_.open("read_results", ELEM);
}

/*
*******************************************************************************/
void Read_result_writer::operator() (Read_result const& rr) {
   write(xw_, rr, rm_, version_);
}

}//namespace vdjml
