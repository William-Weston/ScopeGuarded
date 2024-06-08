/**
 * @file    UncaughtExceptionCounter.hpp
 * @author  William Weston (wjtWeston@protonmail.com)
 * @brief   Determine number of exceptions in play
 * @version 0.1
 * @date    2024-06-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef WJTW_2024_06_06_INCLUDE__SCOPEGUARDED_DETAILS_UNCAUGHTEXCEPTIONCOUNTER_HPP
#define WJTW_2024_06_06_INCLUDE__SCOPEGUARDED_DETAILS_UNCAUGHTEXCEPTIONCOUNTER_HPP

#include <exception>             // uncaught_exceptions


namespace ScopeGuarded::details
{

class UncaughtExceptionCounter final
{
public: 
   UncaughtExceptionCounter() noexcept
      : exception_count_{ std::uncaught_exceptions() } {}

  auto is_new_uncaught_exception() const noexcept { return std::uncaught_exceptions() > exception_count_; }

private:

   int exception_count_;
};

}  // ScopeGuarded::details


#endif   // WJTW_2024_06_06_INCLUDE__SCOPEGUARDED_DETAILS_UNCAUGHTEXCEPTIONCOUNTER_HPP