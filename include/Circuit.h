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

#include <Common.h>

#include <map>

namespace Route20
{

template <auto... components>
class Circuit final
{
public:
    Circuit()
    {
        InitMaps<components...>();
    }

    Circuit( const Circuit& ) = delete;
    Circuit& operator=( const Circuit& ) = delete;

    void Tick()
    {
        Tick<components...>();
        for ( auto& [_, ticked] : tickeds )
        {
            ticked = false;
        }
    }

private:
    template <auto comp, auto comp2, auto... comps>
    void InitMaps()
    {
        InitMaps( comp );
        InitMaps<comp2, comps...>();
    }

    template <auto comp>
    void InitMaps()
    {
        InitMaps( comp );
    }

    void InitMaps( const auto& comp )
    {
        using CompRt = std::remove_reference<decltype( comp )>::type::runtime;
        rts[comp.id].template emplace<CompRt>();
        tickeds[comp.id] = false;
    }

    template <auto comp, auto comp2, auto... comps>
    void Tick()
    {
        Tick( comp );
        Tick<comp2, comps...>();
    }

    template <auto comp>
    void Tick()
    {
        Tick( comp );
    }

    void Tick( const auto& comp )
    {
        if ( tickeds[comp.id] )
        {
            return;
        }
        tickeds[comp.id] = true;

        using CompRt = std::remove_reference<decltype( comp )>::type::runtime;

        comp.InputWires( [&]<auto output, auto input>( const auto& fromComp ) {
            Tick( fromComp );

            using FromCompRt = std::remove_reference<decltype( fromComp )>::type::runtime;

            std::get<input>( std::get<CompRt>( rts[comp.id] ).inputs ) =
                std::get<output>( std::get<FromCompRt>( rts[fromComp.id] ).outputs );
        } );

        comp.Tick( std::get<CompRt>( rts[comp.id] ) );
    }

    using RtTypes = std::variant<typename decltype( components )::runtime...>;

    std::map<unsigned int, without_duplicates<RtTypes>> rts;
    std::map<unsigned int, bool> tickeds;
};

}  // namespace Route20
