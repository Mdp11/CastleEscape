// Copyrights Mattia De Prisco 2020

#include "CellKey.h"

#include "Utilities.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

ACellKey::ACellKey() : AInteractableBase()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    const auto KeyMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
        TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Props/SM_Lock_Key.SM_Lock_Key'"));
    if (KeyMesh.Object)
    {
        StaticMeshComponent->SetStaticMesh(KeyMesh.Object);
    }
    else
    {
        UNDEF_PTR("Key mesh", *GetName());
    }
}

void ACellKey::Interact()
{
    if(IsPicked())
    {
        return;
    }
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("You obtained a key."));
    }
    Picked = true;
    StaticMeshComponent->SetVisibility(false);
}

bool ACellKey::IsPicked() const
{
    return Picked;
}
