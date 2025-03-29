/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2020 OpenFOAM Foundation
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

#include "etaMean.H"
#include "fvc.H"
//#include "fvcGrad.H"
//#include "fvMesh.H"
//#include "incompressibleMomentumTransportModels.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace functionObjects
{
    defineTypeNameAndDebug(etaMean, 0);

    addToRunTimeSelectionTable
    (
        functionObject,
        etaMean,
        dictionary
    );
}
}



// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool Foam::functionObjects::etaMean::calc()
{
    if (foundObject<volScalarField>("nuTotMean") & foundObject<volScalarField>("epsilonTotMean"))
    {
        const volScalarField& nuTotMean = lookupObject<volScalarField>("nuTotMean");
		const volScalarField& epsilonTotMean = lookupObject<volScalarField>("epsilonTotMean");
		
        return store
		(
			resultName_,
			pow(pow3(nuTotMean) / epsilonTotMean , 1.0/4.0)
		);
    }
    else
    {
        //cannotFindObject<volVectorField>("UMean");

        return false;
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::functionObjects::etaMean::etaMean
(
    const word& name,
    const Time& runTime,
    const dictionary& dict
)
:
    fieldsExpression(name, runTime, dict)
{
	setResultName("etaMean");
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::functionObjects::etaMean::~etaMean()
{}


// ************************************************************************* //
