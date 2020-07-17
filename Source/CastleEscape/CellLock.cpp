// Copyrights Mattia De Prisco 2020

#include "CellLock.h"

#include "Utilities.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

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
        UNDEF_PTR("Closed lock mesh", *GetName());
    }
    
    const auto OpenMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
        TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Props/SM_Lock_Open.SM_Lock_Open'"));
    if (OpenMesh.Object)
    {
        OpenLockStaticMesh = OpenMesh.Object;
    }
    else
    {
        UNDEF_PTR("Open lock mesh", *GetName());
    }

    const auto OpenLockSound = ConstructorHelpers::FObjectFinder<USoundWave>(
    TEXT("SoundWave'/Game/SoundEffects/lock_opening.lock_opening'"));
    if (OpenLockSound.Object)
    {
        OpenSound = OpenLockSound.Object;
    }
    else
    {
        UNDEF_PTR("Open door sound", *GetName());
    }
}

void ACellLock::Interact()
{
    if (!StaticMeshComponent)
    {
        UNDEF_PTR("StaticMeshComponent", *GetName());
        return;
    }
    if(!CellKey)
    {
        UNDEF_PTR("CellKey actor", *GetName());
        return;
    }
    if (!CellKey->IsPicked())
    {
        if(AudioComponent)
        {
            AudioComponent->Play();
        }
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("You need a key to unlock it."));
        }
        return;
    }
    if(AudioComponent)
    {
        AudioComponent->SetSound(OpenSound);
        AudioComponent->Play();
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
