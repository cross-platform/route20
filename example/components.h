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

#include <iostream>

namespace Route20
{

/// RandBool:
/// RandBool has 1 output.
/// This component generates a random boolean value then outputs the result.

class RandBool
{
private:
    class RandBoolRt final
    {
    public:
        RandBoolRt()
        {
            // seed randomizer
            srand( static_cast<unsigned int>( time( nullptr ) ) );
        }

        RandBoolRt( const RandBoolRt& ) = delete;
        RandBoolRt& operator=( const RandBoolRt& ) = delete;

        std::tuple<> inputs;
        std::tuple<bool> outputs;
    };

public:
    using runtime = RandBoolRt;

    void Tick( runtime& rt ) const
    {
        std::get<0>( rt.outputs ) = rand() % 2 == 0;
    }
};

/// And:
/// And has 2 inputs and 1 output.
/// This component performs a logic AND on 2 boolean input values and outputs the result.

class And
{
private:
    class AndRt final
    {
    public:
        AndRt() = default;
        AndRt( const AndRt& ) = delete;
        AndRt& operator=( const AndRt& ) = delete;

        std::tuple<bool, bool> inputs;
        std::tuple<bool> outputs;
    };

public:
    using runtime = AndRt;

    void Tick( runtime& rt ) const
    {
        std::get<0>( rt.outputs ) = std::get<0>( rt.inputs ) && std::get<1>( rt.inputs );
    }
};

/// PrintBool:
/// PrintBool has 1 input.
/// This component receives a boolean value and outputs it to the console.

class PrintBool
{
private:
    class PrintBoolRt final
    {
    public:
        PrintBoolRt() = default;
        PrintBoolRt( const PrintBoolRt& ) = delete;
        PrintBoolRt& operator=( const PrintBoolRt& ) = delete;

        std::tuple<bool> inputs;
        std::tuple<> outputs;
    };

public:
    using runtime = PrintBoolRt;

    void Tick( runtime& rt ) const
    {
        std::cout << ( std::get<0>( rt.inputs ) ? "true" : "false" ) << std::endl;
    }
};

}  // namespace Route20
