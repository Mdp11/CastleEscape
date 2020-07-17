// Copyrights Mattia De Prisco 2020

#pragma once

#include "CellLock.h"
#include "CoreMinimal.h"
#include "DoorOpenerComponent.h"
#include "InteractableBase.h"
#include "CellDoor.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEESCAPE_API ACellDoor : public AInteractableBase
{
    GENERATED_BODY()

public:
    ACellDoor();
    
    void Interact() override final;

private:
    UPROPERTY(EditAnywhere)
    UDoorOpenerComponent* DoorOpenerComponent;
    
    UPROPERTY(EditAnywhere)
    ACellLock* CellLock{nullptr};

    UPROPERTY()
    USoundWave* OpenSound{nullptr};

    bool Open{false};
};
