// Copyrights Mattia De Prisco 2020

#include "InteractionComponent.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "InteractableBase.h"
#include "Utilities.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
    FindInputComponent();
    // ...
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UInteractionComponent::FindInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        InputComponent->BindAction("CLICK", IE_Pressed, this, &UInteractionComponent::Interact);
    }
    else
    {
        UNDEF_PTR("InputComponent", *GetOwner()->GetName());
    }
}

void UInteractionComponent::Interact()
{
    const auto HitResult = GetFirsDynamictObjectInReach();
    const auto ActorHit = HitResult.GetActor();
    if (ActorHit)
    {
        auto InteractableActor = Cast<AInteractableBase>(ActorHit);
        if (InteractableActor)
        {
            UE_LOG(LogTemp, Display, TEXT("Found interactable object"));
            InteractableActor->Interact();
        }
    }
}

FHitResult UInteractionComponent::GetFirsDynamictObjectInReach() const
{
    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams{FName{TEXT("")}, false, GetOwner()};

    GetWorld()->LineTraceSingleByObjectType(HitResult, GetOwner()->GetActorLocation(), GetPlayerReach(),
                                            ECC_WorldDynamic, CollisionQueryParams);

    return HitResult;
}

FVector UInteractionComponent::GetPlayerReach() const
{
    FVector PlayerViewPointLocation{};
    FRotator PlayerViewPointRotation{};
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
