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

#include <Circuit.h>
#include <Component.h>

#include <components.h>

using namespace Route20;

/// In this example we create a simple Route20 circuit that generates random boolean
/// pairs, performs a logic AND on each pair, then prints the result to screen.

int main()
{
    // Instantiate 2x RandBools with IDs 0 and 1 (compile time)
    constexpr auto randBoolGen1 = Component<0, RandBool>();
    constexpr auto randBoolGen2 = Component<1, RandBool>();

    // Instantiate an And component with ID 2, and connect RandBools to inputs 0 and 1 (compile time)
    constexpr auto logicAnd = Component<2, And, randBoolGen1, 0, 0, randBoolGen2, 0, 1>();

    // Instantiate a PrintBool component with ID 3, and connect And output 0 to input 0 (compile time)
    constexpr auto boolPrinter = Component<3, PrintBool, logicAnd, 0, 0>();

    // Instantiate a Circuit (run time)
    auto circuit = Circuit<randBoolGen1, randBoolGen2, logicAnd, boolPrinter>();

    // Run the Circuit (run time)
    for ( int i = 0; i < 100; i++ )
    {
        circuit.Tick();
    }

    return 0;
}
