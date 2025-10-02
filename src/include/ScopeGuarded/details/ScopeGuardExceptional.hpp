/**
 * @file     ScopeGuardExceptional.hpp
 * @author   William Weston (wjtWeston@protonmail.com)
 * @brief 
 * @version  0.1
 * @date     2024-06-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef WJTW_2024_06_06_INCLUDE_SCOPEGUARDED_DETAILS_SCOPEGUARDEXCEPTIONAL_HPP
#define WJTW_2024_06_06_INCLUDE_SCOPEGUARDED_DETAILS_SCOPEGUARDEXCEPTIONAL_HPP

#include "ScopeGuarded/details/UncaughtExceptionCounter.hpp"     // for UncaughtExceptionCounter

#include <type_traits>                                           // for is_invocable_v, is_nothrow_default_constructible_v
#include <utility>                                               // for move

namespace ScopeGuarded::details
{

template <typename Fn, bool Execute_On_Exception>
class ScopeGuardExceptional
{
public:

   constexpr explicit ScopeGuardExceptional() noexcept( std::is_nothrow_default_constructible_v<Fn> );
   constexpr explicit ScopeGuardExceptional( Fn const& fn );
   constexpr explicit ScopeGuardExceptional( Fn&& fn ) noexcept;

   constexpr ~ScopeGuardExceptional() noexcept( Execute_On_Exception );

private:
   Fn                       fn_;
   UncaughtExceptionCounter exception_counter_;
};


template <typename Fn, bool Execute_On_Exception> constexpr
ScopeGuardExceptional<Fn, Execute_On_Exception>::ScopeGuardExceptional() noexcept( std::is_nothrow_default_constructible_v<Fn> )
   : fn_{ Fn{} }, exception_counter_{}
{
   static_assert( std::is_invocable_v<Fn>, "Fn must be invokable");
}

template <typename Fn, bool Execute_On_Exception> constexpr
ScopeGuardExceptional<Fn, Execute_On_Exception>::ScopeGuardExceptional( Fn const& fn )
   : fn_{ fn }, exception_counter_{}
{
   static_assert( std::is_invocable_v<Fn>, "Fn must be invokable");
}

template <typename Fn, bool Execute_On_Exception> constexpr
ScopeGuardExceptional<Fn, Execute_On_Exception>::ScopeGuardExceptional( Fn&& fn ) noexcept
   : fn_{ std::move( fn ) }, exception_counter_{}
{
   static_assert( std::is_invocable_v<Fn>, "Fn must be invokable");
}


template <typename Fn, bool Execute_On_Exception> constexpr
ScopeGuardExceptional<Fn, Execute_On_Exception>::~ScopeGuardExceptional() noexcept( Execute_On_Exception )
{
   if ( Execute_On_Exception == exception_counter_.is_new_uncaught_exception() )
   {
      fn_();
   }
}

}     // ScopeGuarded::details

#endif      // WJTW_2024_06_06_INCLUDE_SCOPEGUARDED_DETAILS_SCOPEGUARDEXCEPTIONAL_HPP