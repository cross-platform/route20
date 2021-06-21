/************************************************************************
 Route20 - Cross-Platform C++ Dataflow Metaprogramming Framework
 Copyright (c) 2021 Marcus Tomlinson

 This file is part of Route20.

 Simplified BSD Licence:
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:

 Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ************************************************************************/

#pragma once

#include <variant>

template <class Haystack, class Needle>
struct contains;

template <class Car, class... Cdr, class Needle>
struct contains<std::variant<Car, Cdr...>, Needle> : contains<std::variant<Cdr...>, Needle>
{
};

template <class... Cdr, class Needle>
struct contains<std::variant<Needle, Cdr...>, Needle> : std::true_type
{
};

template <class Needle>
struct contains<std::variant<>, Needle> : std::false_type
{
};

template <class Out, class In>
struct filter;

template <class... Out, class InCar, class... InCdr>
struct filter<std::variant<Out...>, std::variant<InCar, InCdr...>>
{
    using type = typename std::conditional<contains<std::variant<Out...>, InCar>::value,
                                           filter<std::variant<Out...>, std::variant<InCdr...>>,
                                           filter<std::variant<Out..., InCar>, std::variant<InCdr...>>>::type::type;
};

template <class Out>
struct filter<Out, std::variant<>>
{
    using type = Out;
};

template <class T>
using without_duplicates = typename filter<std::variant<>, T>::type;
