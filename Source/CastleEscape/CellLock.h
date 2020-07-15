// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "CellLock.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEESCAPE_API ACellLock : public AInteractableBase
{
    GENERATED_BODY()

public:
    ACellLock();

    void Interact() override final;

private:

    UPROPERTY(EditAnywhere)
    UStaticMesh* ClosedLockStaticMesh{nullptr};

    UPROPERTY(EditAnywhere)
    UStaticMesh* OpenLockStaticMesh{nullptr};

    bool IsLocked{true};
};
