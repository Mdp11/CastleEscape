// Copyrights Mattia De Prisco 2020

#include "CellDoor.h"

#include "DoorOpenerComponent.h"
#include "Utilities.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

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
        UNDEF_PTR("CellDoor mesh", *GetName());
    }

    DoorOpenerComponent = CreateDefaultSubobject<UDoorOpenerComponent>("RootComponent");
    AddOwnedComponent(DoorOpenerComponent);

    const auto OpenDoorSound = ConstructorHelpers::FObjectFinder<USoundWave>(
    TEXT("SoundWave'/Game/SoundEffects/cell_door_opening.cell_door_opening'"));
    if (OpenDoorSound.Object)
    {
        OpenSound = OpenDoorSound.Object;
    }
    else
    {
        UNDEF_PTR("Open lock sound", *GetName());
    }
}

void ACellDoor::Interact()
{
    if (!CellLock)
    {
        UNDEF_PTR("CellLock", *GetName());
        return;
    }

    if (Open)
    {
        return;
    }

    if (CellLock->IsLocked())
    {
        if(AudioComponent)
        {
            AudioComponent->Play();
        }
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("It's locked."));
        }
    }
    else
    {
        if(AudioComponent)
        {
            AudioComponent->SetSound(OpenSound);
            AudioComponent->Play();
        }
        DoorOpenerComponent->RequestOpenClose();
        Open = true;
    }
}
