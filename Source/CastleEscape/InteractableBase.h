// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

UCLASS()
class CASTLEESCAPE_API AInteractableBase : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AInteractableBase();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UStaticMeshComponent* StaticMeshComponent{nullptr};

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    virtual void Interact();
};
