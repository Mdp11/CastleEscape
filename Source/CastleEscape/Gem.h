// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Gem.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEESCAPE_API AGem : public AInteractableBase
{
    GENERATED_BODY()

public:
    AGem();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    USoundWave* PickSoundWave{nullptr};
};
