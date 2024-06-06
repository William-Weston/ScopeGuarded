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
#ifndef WJTW_2024_06_06_INCLUDE_SCOPEGUARD_H
#define WJTW_2024_06_06_INCLUDE_SCOPEGUARD_H

#include <type_traits>     // is_invokable_v, is_nothrow_default_constructible_v
#include <utility>         // move



namespace ScopeGuarded
{
template <typename Fn>
class ScopeGuard
{
public:
   constexpr ScopeGuard() noexcept( std::is_nothrow_default_constructible_v<Fn> );

   explicit constexpr ScopeGuard( Fn const& fn );
   explicit constexpr ScopeGuard( Fn&& fn ) noexcept;

   ~ScopeGuard();

private:
   Fn fn_;
};


template <typename Fn> constexpr
ScopeGuard<Fn>::ScopeGuard() noexcept( std::is_nothrow_default_constructible_v<Fn> )
   : fn_{ Fn{} }
{
   static_assert( std::is_invocable_v<Fn>, "Fn must be invokable");
}

template <typename Fn> constexpr
ScopeGuard<Fn>::ScopeGuard( Fn const& fn )
   : fn_{ fn }
{
   static_assert( std::is_invocable_v<Fn>, "Fn must be invokable");
}

template <typename Fn> constexpr
ScopeGuard<Fn>::ScopeGuard( Fn&& fn ) noexcept
   : fn_{ std::move( fn ) }
{
   static_assert( std::is_invocable_v<Fn>, "Fn must be invokable" );
}

template <typename Fn>
ScopeGuard<Fn>::~ScopeGuard()
{
   fn_();
}

namespace detail
{
   struct ScopeGuardOnExit {};

   template <typename Fn>
   auto operator+ ( ScopeGuardOnExit, Fn&& fn ) -> ScopeGuard<Fn>
   {
      return ScopeGuard<Fn>( std::forward<Fn>( fn ) );
   }
   
}  // namespace detail

}     // namespace ScopeGuard



#define CONCAT_IMPL( lhs, rhs )  lhs##rhs
#define CONCAT( lhs, rhs )       CONCAT_IMPL( lhs, rhs )

#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE( str )   \
   CONCAT( str, __COUNTER__ )

#else
#define ANONYMOUS_VARIABLE( str )   \
   CONCATENATE( str, __LINE__ )

#endif

#define SCOPE_EXIT \
   auto ANONYMOUS_VARIABLE( SCOPE_GUARD_ )    \
      = ScopeGuarded::detail::ScopeGuardOnExit()  + [&] ()


#endif   // WJTW_2024_06_06_INCLUDE_SCOPEGUARD_H
