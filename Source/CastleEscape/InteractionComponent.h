// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "LeverPullComponent.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"

#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEESCAPE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVector GetPlayerReach() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	UPROPERTY(EditAnywhere)
	float Reach{200.f};
	
	UPROPERTY()
	UInputComponent* InputComponent{nullptr};
	
	void FindInputComponent();
	void Interact();
	FHitResult GetFirsDynamictObjectInReach() const;

		
};
