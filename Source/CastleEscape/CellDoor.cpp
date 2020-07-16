// Copyrights Mattia De Prisco 2020

#include "CellDoor.h"

#include "DoorOpenerComponent.h"
#include "Utilities.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

ACellDoor::ACellDoor()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    const auto CellDoorMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
        TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Architecture/Dungeon/SM_Cell_Door.SM_Cell_Door'"));
    if (CellDoorMesh.Object)
    {
        StaticMeshComponent->SetStaticMesh(CellDoorMesh.Object);
    }
    else
    {
        UNDEF_PTR("CellDoor mesh", GetName());
    }

    DoorOpenerComponent = CreateDefaultSubobject<UDoorOpenerComponent>("RootComponent");
    AddOwnedComponent(DoorOpenerComponent);
}

void ACellDoor::Interact()
{
    DoorOpenerComponent->RequestOpenClose();
}
