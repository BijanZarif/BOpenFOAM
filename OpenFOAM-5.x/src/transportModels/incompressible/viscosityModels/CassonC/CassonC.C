/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "CassonC.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(CassonC, 0);

    addToRunTimeSelectionTable
    (
        viscosityModelC,
        CassonC,
        dictionary
    );
}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //
void Foam::viscosityModels::CassonC::correct()
{
    const volScalarField limitedAlpha1(min(max(this->VF(), scalar(0)), scalar(1)));
    const volScalarField kC( mup_ / pow(1.0 - limitedAlpha1 , A_ ));
    const volScalarField tauY((B_ / A_) * ( pow(1 - limitedAlpha1, 0.5*A_) - 1.));

    this->mu_ = min(
    				muMax_,
					sqr(
						sqrt(kC * strainRate()) + sqrt(tauY)
					) / max(
						strainRate(),
						dimensionedScalar("VSMALL", dimless/dimTime, VSMALL)
					)
				);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::CassonC::CassonC
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi,
    const volScalarField& alpha1
)
:

    viscosityModelC(name, viscosityProperties, U, phi, alpha1),
    CassonCCoeffs_(viscosityProperties.subDict(typeName + "Coeffs")),
    mup_(CassonCCoeffs_.lookup("mup")),
    muMax_(CassonCCoeffs_.lookup("muMax")),
    A_(CassonCCoeffs_.lookup("A")),
    B_(CassonCCoeffs_.lookup("B"))
{
	this->correct();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::CassonC::read
(
    const dictionary& viscosityProperties
)
{
    viscosityModelC::read(viscosityProperties);

    CassonCCoeffs_ = viscosityProperties.subDict(typeName + "Coeffs");

    CassonCCoeffs_.lookup("mup") >> mup_;
    CassonCCoeffs_.lookup("muMax") >> muMax_;
    CassonCCoeffs_.lookup("A") >> A_;
    CassonCCoeffs_.lookup("B") >> B_;

    return true;
}


// ************************************************************************* //
