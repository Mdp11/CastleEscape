// Copyrights Mattia De Prisco 2020

#pragma once

#include "CellKey.h"
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
    bool IsLocked() const;

private:
    UPROPERTY(EditAnywhere)
    ACellKey* CellKey{nullptr};

    UPROPERTY()
    UStaticMesh* ClosedLockStaticMesh{nullptr};

    UPROPERTY()
    UStaticMesh* OpenLockStaticMesh{nullptr};

    bool Locked{true};
};
