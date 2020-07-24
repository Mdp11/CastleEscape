// Copyrights Mattia De Prisco 2020

#include "Gem.h"

#include "Utilities.h"
#include "UObject/ConstructorHelpers.h"

AGem::AGem() : AInteractableBase()
{
    Grabbable = true;
    PrimaryActorTick.bCanEverTick = true;
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    StaticMeshComponent->SetEnableGravity(false);
    const auto GemMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
        TEXT("StaticMesh'/Game/AncientTreasures/Meshes/SM_Gems_01c.SM_Gems_01c'"));
    if (GemMesh.Object)
    {
        StaticMeshComponent->SetStaticMesh(GemMesh.Object);
    }
    else
    {
        UNDEF_PTR("Gem mesh", *GetName());
    }
    //
    const auto PickSound = ConstructorHelpers::FObjectFinder<USoundWave>(
        TEXT("SoundWave'/Game/SoundEffects/ding.ding'"));
    if (PickSound.Object)
    {
        PickSoundWave = PickSound.Object;
    }
    else
    {
        UNDEF_PTR("Pick sound", *GetName());
    }
}

void AGem::BeginPlay()
{
    AInteractableBase::BeginPlay();
    if(AudioComponent)
    {
        AudioComponent->SetSound(PickSoundWave);
    }
}
