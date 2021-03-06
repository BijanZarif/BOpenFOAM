/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2009 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::viscosityModels::Newtonian

Description
    An incompressible Newtonian viscosity model.

SourceFiles
    NewtonianC.C

\*---------------------------------------------------------------------------*/

#ifndef NewtonianC_H
#define NewtonianC_H

#include "viscosityModelC.H"
#include "dimensionedScalar.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{

/*---------------------------------------------------------------------------*\
                           Class NewtonianC Declaration
\*---------------------------------------------------------------------------*/

class NewtonianC
:
    public viscosityModelC
{
    // Private data
		dictionary newtonianCCoeffs_;
        dimensionedScalar mu0_;


public:

    //- Runtime type information
    TypeName("NewtonianC");


    // Constructors

        //- construct from components
        NewtonianC
        (
            const word& name,
            const dictionary& viscosityProperties,
            const volVectorField& U,
            const surfaceScalarField& phi,
            const volScalarField& alpha1
        );


    // Destructor

        ~NewtonianC()
        {}


    // Member Functions

        //- Correct the laminar viscosity (not appropriate, viscosity constant)
        void correct()
        {}

        //- Read transportProperties dictionary
        bool read(const dictionary& viscosityProperties);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace viscosityModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
