// Copyrights Mattia De Prisco 2020

#include "DoorOpenerComponent.h"

#include "Utilities.h"

// Sets default values for this component's properties
UDoorOpenerComponent::UDoorOpenerComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UDoorOpenerComponent::BeginPlay()
{
    Super::BeginPlay();
    FindAudioComponent();
    InitialYaw = CurrentYaw = GetOwner()->GetActorRotation().Yaw;
    OpenYaw += InitialYaw;
    // ...
}

// Called every frame
void UDoorOpenerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const float TargetYaw = OpenDoor ? OpenYaw : InitialYaw;
    if (!FMath::IsNearlyEqual(CurrentYaw, TargetYaw, 0.1f))
    {
        if (AudioComponent && !AudioPlayed)
        {
            AudioComponent->Play();
            AudioPlayed = true;
        }
        OpenClose(DeltaTime);
    }
    else
    {
        AudioPlayed = false;
    }

    // ...
}

void UDoorOpenerComponent::RequestOpenClose()
{
    OpenDoor = !OpenDoor;
}

void UDoorOpenerComponent::OpenClose(const float DeltaTime)
{
    const float TargetYaw = OpenDoor ? OpenYaw : InitialYaw;
    CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, OpeningSpeed);
    auto Owner = GetOwner();
    FRotator Rotator = GetOwner()->FindComponentByClass<UStaticMeshComponent>()->GetComponentRotation();
    Rotator.Yaw = CurrentYaw;
    GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetWorldRotation(Rotator);
}

void UDoorOpenerComponent::FindAudioComponent()
{
    AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

    if (!AudioComponent)
    {
        UNDEF_PTR("AudioComponent", *GetOwner()->GetName())
    }
}

void UDoorOpenerComponent::ModifyInitialYaw(float Amount)
{
    InitialYaw += Amount;
}
