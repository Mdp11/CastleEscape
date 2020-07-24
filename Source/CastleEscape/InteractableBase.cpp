// Copyrights Mattia De Prisco 2020

#include "InteractableBase.h"

#include "Utilities.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
    Super::BeginPlay();
    FindAudioComponent();
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInteractableBase::Interact()
{
    UE_LOG(LogTemp, Warning, TEXT("Do not use this class directly, inherit from it instead."))
}

void AInteractableBase::SetSimulatePhysics(bool bSimulatePhysics)
{
    if(StaticMeshComponent)
    {
        StaticMeshComponent->SetSimulatePhysics(bSimulatePhysics);
    }
}

void AInteractableBase::SetEnableGravity(bool bEnableGravity)
{
    if(StaticMeshComponent)
    {
        StaticMeshComponent->SetEnableGravity(bEnableGravity);
    }
}

void AInteractableBase::FindAudioComponent()
{
    AudioComponent = FindComponentByClass<UAudioComponent>();

    if (!AudioComponent)
    {
        UNDEF_PTR("AudioComponent", *GetName())
    }
}
