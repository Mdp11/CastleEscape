// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "CellKey.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEESCAPE_API ACellKey : public AInteractableBase
{
    GENERATED_BODY()

public:
    ACellKey();

    void Interact() override final;
    bool IsPicked() const;

private:
    bool Picked{false};
};
