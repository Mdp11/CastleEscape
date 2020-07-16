// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Components/AudioComponent.h"

#include "PrisonLever.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEESCAPE_API APrisonLever : public AInteractableBase
{
    GENERATED_BODY()

public:
    APrisonLever();

    void Tick(float DeltaTime) override;
    void Interact() override final;

private:

    bool Pulled{false};
    bool DoorOpened{false};

    UPROPERTY(EditAnywhere)
    AActor* DoorLeftSide;

    UPROPERTY(EditAnywhere)
    AActor* DoorRightSide;

    UPROPERTY(EditAnywhere)
    float TargetPitch{65.f};

    float InitialPitch{};
    float CurrentPitch{};

    void Pull(float DeltaTime);
    void OpenDoor() const;
};
