// Copyrights Mattia De Prisco 2020


#include "PrisonDoorOpenerComponent.h"

// Sets default values for this component's properties
UPrisonDoorOpenerComponent::UPrisonDoorOpenerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPrisonDoorOpenerComponent::BeginPlay()
{
	Super::BeginPlay();
	FindAudioComponent();
	InitialYaw = CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += InitialYaw ;
	UE_LOG(LogTemp, Error, TEXT("InitialYaw = %f"), InitialYaw);

	// ...
	
}


// Called every frame
void UPrisonDoorOpenerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (OpenDoorRequested && !FMath::IsNearlyEqual(CurrentYaw, TargetYaw, 0.1f))
	{
		OpenDoor(DeltaTime);
		if (AudioComponent && !AudioPlayed)
		{
			AudioComponent->Play();
			AudioPlayed = true;
		}
	}

	// ...
}

void UPrisonDoorOpenerComponent::RequestOpenDoor()
{
	if (!OpenDoorRequested)
	{
		OpenDoorRequested = true;
	}
}

void UPrisonDoorOpenerComponent::OpenDoor(const float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 0.85f);
	FRotator Rotator = GetOwner()->GetActorRotation();
	Rotator.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(Rotator);
}

void UPrisonDoorOpenerComponent::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Audio component on door not set!"));
	}
}


