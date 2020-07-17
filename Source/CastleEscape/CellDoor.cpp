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
        UNDEF_PTR("Door opening sound", *GetName());
    }

    const auto LockedDoorSound = ConstructorHelpers::FObjectFinder<USoundWave>(
        TEXT("SoundWave'/Game/SoundEffects/locked_door.locked_door'"));
    if (LockedDoorSound.Object)
    {
        LockedSound = LockedDoorSound.Object;
    }
    else
    {
        UNDEF_PTR("Door locked sound", *GetName());
    }
}

void ACellDoor::Interact()
{
    if (!CellLock)
    {
        UNDEF_PTR("CellLock", *GetName());
        return;
    }

    if (!Open)
    {
        if (CellLock->IsLocked() && !AlmostClosed)
        {
            if (AudioComponent->Sound != LockedSound)
            {
                AudioComponent->SetSound(LockedSound);
            }
            AudioComponent->Play();
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("It's locked."));
            }
        }
        else
        {
            if (AudioComponent->Sound != OpenSound)
            {
                AudioComponent->SetSound(OpenSound);
            }
            AudioComponent->Play();
            if (AlmostClosed)
            {
                DoorOpenerComponent->ModifyInitialYaw(-6.f);
                AlmostClosed = false;
            }
            DoorOpenerComponent->RequestOpenClose();
            Open = true;
        }
    }
    else
    {
        if (!CellLock->IsLocked())
        {
            if (AudioComponent->Sound != OpenSound)
            {
                AudioComponent->SetSound(OpenSound);
            }
            AudioComponent->Play();
            DoorOpenerComponent->RequestOpenClose();
            Open = false;
        }
        else
        {
            if (AudioComponent->Sound != OpenSound)
            {
                AudioComponent->SetSound(OpenSound);
            }
            AudioComponent->Play();
            DoorOpenerComponent->ModifyInitialYaw(6.f);
            AlmostClosed = true;
            DoorOpenerComponent->RequestOpenClose();
            Open = false;
        }
    }
}
