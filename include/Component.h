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

namespace Route20
{

template <unsigned int uid, class Impl, auto fromComp = nullptr, auto output = -1, auto... input>
class Component final : public Impl
{
public:
    const unsigned int id = uid;

    consteval Component() = default;
    consteval Component( const Component& ) = default;
    Component& operator=( const Component& ) = delete;

    void InputWires( const auto& callback ) const
    {
        InputWires<fromComp, output, input...>( callback );
    }

    template <auto _fromComp, auto _output, auto _input, auto _nextFromComp, auto _nextOutput, auto... _nextInput>
    void InputWires( const auto& callback ) const
    {
        InputWires<_fromComp, _output, _input>( callback );
        InputWires<_nextFromComp, _nextOutput, _nextInput...>( callback );
    }

    template <auto _fromComp, auto _output, auto _input>
    void InputWires( const auto& callback ) const
    {
        callback.template operator()<_fromComp, _output, _input>();
    }

    template <auto, auto>
    void InputWires( const auto& ) const
    {
    }
};

}  // namespace Route20
