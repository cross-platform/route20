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

#include <any>
#include <iostream>
#include <vector>

namespace Route20
{

/// RandBool:
/// RandBool has 1 output.
/// This component generates a random boolean value then outputs the result.

class RandBoolRt final
{
public:
    RandBoolRt()
    {
        // seed randomizer
        srand( static_cast<unsigned int>( time( nullptr ) ) );
    }
};

struct RandBool
{
    const int nInputs = 0;
    const int nOutputs = 1;
    using runtime = RandBoolRt;

    void Tick( runtime&, const std::vector<std::any>&, std::vector<std::any>& outputs ) const
    {
        outputs[0] = rand() % 2 == 0;
    }
};

/// And:
/// And has 2 inputs and 1 output.
/// This component performs a logic AND on 2 boolean input values and outputs the result.

struct And
{
    const int nInputs = 2;
    const int nOutputs = 1;
    using runtime = nullptr_t;

    void Tick( runtime&, const std::vector<std::any>& inputs, std::vector<std::any>& outputs ) const
    {
        outputs[0] = std::any_cast<bool>( inputs[0] ) && std::any_cast<bool>( inputs[1] );
    }
};

/// PrintBool:
/// PrintBool has 1 input.
/// This component receives a boolean value and outputs it to the console.

struct PrintBool
{
    const int nInputs = 1;
    const int nOutputs = 0;
    using runtime = nullptr_t;

    void Tick( runtime&, const std::vector<std::any>& inputs, std::vector<std::any>& ) const
    {
        std::cout << ( std::any_cast<bool>( inputs[0] ) ? "true" : "false" ) << std::endl;
    }
};

}  // namespace Route20
