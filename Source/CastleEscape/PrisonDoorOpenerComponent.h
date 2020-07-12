// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "PrisonDoorOpenerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UPrisonDoorOpenerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPrisonDoorOpenerComponent();

	void RequestOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	bool OpenDoorRequested{false};
	bool AudioPlayed{false};

	UPROPERTY(EditAnywhere)
	float TargetYaw{90.f};

	float InitialYaw{};
	float CurrentYaw{};

	UPROPERTY()
    UAudioComponent* AudioComponent;

	void OpenDoor(float DeltaTime);
	void FindAudioComponent();

		
};
