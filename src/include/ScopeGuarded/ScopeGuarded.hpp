/**
 * @file     ScopeGuarded.hpp
 * @author   William Weston (wjtWeston@protonmail.com)
 * @brief    Define macros SCOPE_EXIT, SCOPE_FAIL and SCOPE_SUCCESS
 * @version  0.1
 * @date     2024-06-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef WJTW_2024_06_06_INCLUDE_SCOPEGUARDED_SCOPEGUARDED_HPP
#define WJTW_2024_06_06_INCLUDE_SCOPEGUARDED_SCOPEGUARDED_HPP


#include "ScopeGuarded/details/ScopeGuard.hpp"
#include "ScopeGuarded/details/ScopeGuardExceptional.hpp"

#include <type_traits>                                         // decay
#include <utility>                                             // forward


// ============================================================================
//                                Helper Macros
// ============================================================================

#define CONCAT_IMPL( lhs, rhs )  lhs##rhs
#define CONCAT( lhs, rhs )       CONCAT_IMPL( lhs, rhs )

#define ANONYMOUS_VARIABLE( str )   \
   CONCAT( str, __LINE__ )




// ============================================================================
//                                     API
// ============================================================================


#define SCOPE_EXIT                                              \
   auto ANONYMOUS_VARIABLE( SCOPE_GUARD_ )                      \
      = ScopeGuarded::details::ScopeGuardOnExit() + [&] ()


#define SCOPE_FAIL                                              \
   auto ANONYMOUS_VARIABLE( SCOPE_GUARD_ )                      \
      = ScopeGuarded::details::ScopeGuardOnFailure() + [&] ()

#define SCOPE_SUCCESS                                           \
   auto ANONYMOUS_VARIABLE( SCOPE_GUARD_ )                      \
      = ScopeGuarded::details::ScopeGuardOnSuccess() + [&] ()



// ============================================================================
//                           Implementation Details
// ============================================================================


namespace ScopeGuarded::details
{

struct ScopeGuardOnExit {};

template <typename Fn> auto 
operator+ ( ScopeGuardOnExit, Fn&& fn ) -> ScopeGuard<typename std::decay_t<Fn>>
{
   return ScopeGuard<typename std::decay_t<Fn>>( std::forward<Fn>( fn ) );
}


struct ScopeGuardOnFailure {};

template <typename Fn> auto 
operator+ ( ScopeGuardOnFailure, Fn&& fn ) -> ScopeGuardExceptional<typename std::decay_t<Fn>, true>
{
   return ScopeGuardExceptional<typename std::decay_t<Fn>, true>( std::forward<Fn>( fn ) );
}



struct ScopeGuardOnSuccess {};

template <typename Fn> auto 
operator+ ( ScopeGuardOnSuccess, Fn&& fn ) -> ScopeGuardExceptional<typename std::decay_t<Fn>, false>
{
   return ScopeGuardExceptional<typename std::decay_t<Fn>, false>( std::forward<Fn>( fn ) );
}

}  // namespace detail






#endif   // WJTW_2024_06_06_INCLUDE_SCOPEGUARDED_SCOPEGUARDED_HPP