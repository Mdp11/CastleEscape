// Copyrights Mattia De Prisco 2020


#include "PrisonLever.h"


#include "DoorOpenerComponent.h"
#include "Utilities.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

APrisonLever::APrisonLever() : AInteractableBase()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    const auto LeverMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
        TEXT("StaticMesh'/Game/SM_Lever.SM_Lever'"));
    if (LeverMesh.Object)
    {
        StaticMeshComponent->SetStaticMesh(LeverMesh.Object);
    }
    else
    {
        UNDEF_PTR("Lever mesh", *GetName());
    }
}

void APrisonLever::Tick(float DeltaTime)
{
    if (Pulled && !FMath::IsNearlyEqual(CurrentPitch, TargetPitch, 0.1f))
    {
        Pull(DeltaTime);
    }
    else if (!DoorOpened && FMath::IsNearlyEqual(CurrentPitch, TargetPitch, 0.1f))
    {
        OpenDoor();
        DoorOpened = true;
    }
}

void APrisonLever::Interact()
{
    if(!Pulled)
    {
        Pulled = true;
    }
}

void APrisonLever::Pull(const float DeltaTime)
{
    CurrentPitch = FMath::FInterpTo(CurrentPitch, TargetPitch, DeltaTime, 1.7f);
    FRotator Rotator = GetActorRotation();
    Rotator.Pitch = CurrentPitch;
    SetActorRotation(Rotator);
}

void APrisonLever::OpenDoor() const
{
    if(DoorLeftSide && DoorRightSide)
    {
        auto DoorOpenerComponentLeft = DoorLeftSide->FindComponentByClass<UDoorOpenerComponent>();
        auto DoorOpenerComponentRight = DoorRightSide->FindComponentByClass<UDoorOpenerComponent>();
        if(!DoorOpenerComponentLeft || !DoorOpenerComponentRight)
        {
            const FString DoorNames = DoorLeftSide->GetName() + " or " + DoorRightSide->GetName();
            UNDEF_PTR("Door opener component", *DoorNames)
            return;
        }
        DoorOpenerComponentLeft->RequestOpenClose();
        DoorOpenerComponentRight->RequestOpenClose();
        
    }
    else
    {
        UNDEF_PTR("DoorActor", *GetName());
    }
}


