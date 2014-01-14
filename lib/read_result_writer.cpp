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
boost::iostreams::filtering_ostreambuf* Read_result_writer::setup_fosb(
         std::string const& path,
         Compression compr,
         std::ofstream& ofs,
         boost::iostreams::filtering_ostreambuf& fosb
) {
   if( compr == Unknown_compression ) compr = guess_compression(path);
   static const std::ios_base::openmode bin_mode =
            std::ios_base::out | std::ios_base::trunc | std::ios_base::binary;
   switch (compr) {
      case Uncompressed:
         ofs.open(path.c_str(), std::ios_base::out | std::ios_base::trunc);
         fosb.push(ofs);
         break;
      case bzip2:
         ofs.open(path.c_str(), bin_mode);
         fosb.push(boost::iostreams::bzip2_compressor());
         fosb.push(ofs);
         break;
      case gzip:
         ofs.open(path.c_str(), bin_mode);
         fosb.push(boost::iostreams::gzip_compressor());
         fosb.push(ofs);
         break;
      case zlib:
         ofs.open(path.c_str(), bin_mode);
         fosb.push(boost::iostreams::zlib_compressor());
         fosb.push(ofs);
         break;
      default:
         BOOST_THROW_EXCEPTION(
                  Err()
                  << Err::msg_t("unsupported compression")
                  << Err::str1_t(path)
                  << Err::int1_t(compr)
         );
   }
   return &fosb;
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
: rm_(rm)
{
   switch (compr) {
      case Uncompressed:
         xw_.reset(new Xml_writer(os, opts));
         break;
      case bzip2:
         fosb_.reset(new fosb_t());
         fosb_->push(boost::iostreams::bzip2_compressor());
         os_.reset(new std::ostream(*(*fosb_)));
         xw_.reset(new Xml_writer(*os_, opts));
         break;
      case gzip:
         ofs.open(path.c_str(), bin_mode);
         fosb.push(boost::iostreams::gzip_compressor());
         fosb.push(ofs);
         break;
      case zlib:
         ofs.open(path.c_str(), bin_mode);
         fosb.push(boost::iostreams::zlib_compressor());
         fosb.push(ofs);
         break;
      default:
         BOOST_THROW_EXCEPTION(
                  Err()
                  << Err::msg_t("unsupported compression")
                  << Err::str1_t(path)
                  << Err::int1_t(compr)
         );
   }

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
  ofs_(),
  fosb_(),
  os_(setup_fosb(path, compr, ofs_, fosb_)),
  xw_(os_, opts),
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
