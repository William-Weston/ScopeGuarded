/**
 * @file   ScopeGuard.t.cpp
 * @author William Weston (wjtWeston@protonmail.com)
 * @brief  Test file for ScopeGuard.hpp
 * @version 0.1
 * @date    2024-06-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ScopeGuarded/ScopeGuarded.hpp"

#include <catch2/catch_all.hpp>

#include <iostream>

#define STRINGIFY_IMPL( str ) #str
#define STRINGIFY( str ) STRINGIFY_IMPL( str )

TEST_CASE( "ScopeGuard.Basic" )
{
   using namespace ScopeGuarded::details;

   auto check = 0;
   auto fn = [&]{ check = 23;  };
   {
      auto sg  = ScopeGuard( fn );
   }

   REQUIRE( check == 23 );

   std::cerr << STRINGIFY( SCOPE_EXIT ) << '\n';
   std::cerr << STRINGIFY( SCOPE_EXIT ) << '\n';

   SCOPE_EXIT
   {
      std::cerr << "\nOn Exit\n";

   };

   try
   {
      SCOPE_FAIL
      {
         std::cerr << "\nOn Failure\n";
      };

      SCOPE_SUCCESS
      {
         std::cerr << "\nOn Success\n";
      };
     throw -1;
   }
   catch( ... )
   {

   }
}