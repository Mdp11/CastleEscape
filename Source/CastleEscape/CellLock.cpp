// Copyrights Mattia De Prisco 2020

#include "CellLock.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ACellLock::ACellLock() : AInteractableBase()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    auto ClosedMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
        TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Props/SM_Lock_Closed.SM_Lock_Closed'"));
    if (ClosedMesh.Object)
    {
        StaticMeshComponent->SetStaticMesh(ClosedMesh.Object);
        ClosedLockStaticMesh = ClosedMesh.Object;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Closed lock mesh not found."))
    }
    auto OpenMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
    TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Props/SM_Lock_Open.SM_Lock_Open'"));
    if (OpenMesh.Object)
    {
        OpenLockStaticMesh = OpenMesh.Object;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Open lock mesh not found."))
    }
}

void ACellLock::Interact()
{
    if (StaticMeshComponent)
    {
        if (IsLocked && OpenLockStaticMesh)
        {
            StaticMeshComponent->SetStaticMesh(OpenLockStaticMesh);
            IsLocked = false;
        }
        else if (!IsLocked && ClosedLockStaticMesh)
        {
            StaticMeshComponent->SetStaticMesh(ClosedLockStaticMesh);
            IsLocked = true;
        }
    }
}
