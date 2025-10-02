/**
 * @file   ScopeGuard.h
 * @author William Weston (wjtWeston@protonmail.com)
 * @brief  RAII template class designed to run a function upon distruction
 * @version 0.1
 * @date    2024-06-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef WJTW_2024_06_06_INCLUDE_SCOPEGUARDED_DETAILS_SCOPEGUARD_HPP
#define WJTW_2024_06_06_INCLUDE_SCOPEGUARDED_DETAILS_SCOPEGUARD_HPP

#include <concepts>        // for invokable
#include <type_traits>     // for is_invokable_v, is_nothrow_default_constructible_v
#include <utility>         // for move


namespace ScopeGuarded::details
{
   
template <std::invocable Fn>
class ScopeGuard
{
public:
   explicit constexpr ScopeGuard()                  noexcept( std::is_nothrow_default_constructible_v<Fn> );
   explicit constexpr ScopeGuard( Fn const& fn );
   explicit constexpr ScopeGuard( Fn&& fn )         noexcept;

   constexpr ~ScopeGuard();

private:
   Fn fn_;
};


template <std::invocable Fn> constexpr
ScopeGuard<Fn>::ScopeGuard() noexcept( std::is_nothrow_default_constructible_v<Fn> )
   : fn_{ Fn{} }
{}

template <std::invocable Fn> constexpr
ScopeGuard<Fn>::ScopeGuard( Fn const& fn )
   : fn_{ fn }
{}

template <std::invocable Fn> constexpr
ScopeGuard<Fn>::ScopeGuard( Fn&& fn ) noexcept
   : fn_{ std::move( fn ) }
{}

template <std::invocable Fn> constexpr
ScopeGuard<Fn>::~ScopeGuard()
{
   fn_();
}

}     // ScopeGuarded::details

#endif   // WJTW_2024_06_06_INCLUDE_SCOPEGUARDED_DETAILS_SCOPEGUARD_HPP
