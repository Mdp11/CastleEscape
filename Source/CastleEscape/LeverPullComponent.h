// Mattia De Prisco

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LeverPullComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API ULeverPullComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    ULeverPullComponent();

    void PerformAction();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

private:
    bool IsPulled{false};

    UPROPERTY(EditAnywhere)
    float TargetPitch{65.f};

    float InitialPitch{};
    float CurrentPitch{};

    void PullLever(float DeltaTime);
};
