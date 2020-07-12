// Mattia De Prisco

#include "LeverPullComponent.h"

#include "GameFramework/Actor.h"

// Sets default values for this component's properties
ULeverPullComponent::ULeverPullComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void ULeverPullComponent::BeginPlay()
{
    Super::BeginPlay();
    FindAudioComponent();
    InitialPitch = CurrentPitch = GetOwner()->GetActorRotation().Pitch;
    TargetPitch += InitialPitch;
    // ...
}

// Called every frame
void ULeverPullComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (PullRequested && !FMath::IsNearlyEqual(CurrentPitch, TargetPitch, 0.1f))
    {
        PullLever(DeltaTime);
        if (!AudioPlayed)
        {
            AudioComponent->Play();
        }
        AudioPlayed = true;
    }
    else if (FMath::IsNearlyEqual(CurrentPitch, TargetPitch, 0.001f))
    {
        IsPulled = true;
    }
    if (IsPulled)
    {
        //OpenDoor
    }
    // ...
}

void ULeverPullComponent::PerformAction()
{
    if (!PullRequested)
    {
        PullRequested = true;
    }
}

void ULeverPullComponent::PullLever(const float DeltaTime)
{
    CurrentPitch = FMath::FInterpTo(CurrentPitch, TargetPitch, DeltaTime, 1.7f);
    FRotator Rotator = GetOwner()->GetActorRotation();
    Rotator.Pitch = CurrentPitch;
    GetOwner()->SetActorRotation(Rotator);
}

void ULeverPullComponent::FindAudioComponent()
{
    AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

    if (!AudioComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("Audio component on lever not set!"));
    }
}
