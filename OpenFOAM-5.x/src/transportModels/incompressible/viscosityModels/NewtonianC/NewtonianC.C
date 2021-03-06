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

\*---------------------------------------------------------------------------*/

#include "NewtonianC.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(NewtonianC, 0);
    addToRunTimeSelectionTable(viscosityModelC, NewtonianC, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::NewtonianC::NewtonianC
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi,
    const volScalarField& alpha1
)
:
    viscosityModelC(name, viscosityProperties, U, phi, alpha1),
    newtonianCCoeffs_(viscosityProperties.subDict(typeName + "Coeffs")),
    mu0_(newtonianCCoeffs_.lookup("mu"))
{
	this->mu_ = mu0_;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::NewtonianC::read
(
    const dictionary& viscosityProperties
)
{
    viscosityModelC::read(viscosityProperties);
    newtonianCCoeffs_ = viscosityProperties.subDict(typeName + "Coeffs");
    newtonianCCoeffs_.lookup("mu") >> mu0_;
    this->mu_ = mu0_;

    return true;
}


// ************************************************************************* //
