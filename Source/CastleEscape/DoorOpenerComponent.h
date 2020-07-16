// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "DoorOpenerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UDoorOpenerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpenerComponent();

	void RequestOpenClose();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	bool OpenDoor{false};
	bool AudioPlayed{false};

	UPROPERTY(EditAnywhere)
	float OpenYaw{90.f};

	float InitialYaw{};
	float CurrentYaw{};

	UPROPERTY()
    UAudioComponent* AudioComponent;

	void OpenClose(float DeltaTime);
	void FindAudioComponent();

		
};
