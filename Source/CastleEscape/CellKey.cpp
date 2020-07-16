// Copyrights Mattia De Prisco 2020


#include "CellKey.h"
#include "Components/StaticMeshComponent.h"
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
        UE_LOG(LogTemp, Warning, TEXT("Key mesh not found."))
    }
}

void ACellKey::Interact()
{
    Picked = true;
    this->Destroy();
}

bool ACellKey::IsPicked() const
{
    return Picked;
}

