// Copyrights Mattia De Prisco 2020

#include "CellLock.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

ACellLock::ACellLock() : AInteractableBase()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    const auto ClosedMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
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
    const auto OpenMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
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
    if (!StaticMeshComponent || !CellKey)
    {
        UE_LOG(LogTemp, Warning, TEXT("Lock mesh or CellKey pointer are null."))
        return;
    }
    if (!CellKey->IsPicked())
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("You need a key to open it."));
        }
        return;
    }
    if (Locked && OpenLockStaticMesh)
    {
        StaticMeshComponent->SetStaticMesh(OpenLockStaticMesh);
        Locked = false;
    }
    else if (!Locked && ClosedLockStaticMesh)
    {
        StaticMeshComponent->SetStaticMesh(ClosedLockStaticMesh);
        Locked = true;
    }
}

bool ACellLock::IsLocked() const
{
    return Locked;
}
