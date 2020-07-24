// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "UnrealAudioSoundFile.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

UCLASS()
class CASTLEESCAPE_API AInteractableBase : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AInteractableBase();

    virtual bool IsGrabbable() const { return Grabbable; }

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY()
    UStaticMeshComponent* StaticMeshComponent{nullptr};

    UPROPERTY()
    UAudioComponent* AudioComponent{nullptr};

    bool Grabbable{false};

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    virtual void Interact();

    void SetSimulatePhysics(bool bSimulatePhysics);
    void SetEnableGravity(bool bEnableGravity);

private:
    void FindAudioComponent();
};
