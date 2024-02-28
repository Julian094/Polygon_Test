// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactions/PT_ActivatorFurniture.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Interactions/PT_ChangeForniture.h"

// Sets default values
APT_ActivatorFurniture::APT_ActivatorFurniture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRootComponent"));
	RootComponent = CustomRootComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

	MeshActivatorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponentTeleport"));
	MeshActivatorComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APT_ActivatorFurniture::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APT_ActivatorFurniture::StartInteraction);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APT_ActivatorFurniture::EndOverlap);
	
}

void APT_ActivatorFurniture::StartInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* RefCharacter = Cast<ACharacter>(OtherActor);
	if (IsValid(RefCharacter))
	{
		if (IsValid(RefChangeFurniture))
		{
			BP_ActivatedInteraction(this);
		}
	}
}

void APT_ActivatorFurniture::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* RefCharacter = Cast<ACharacter>(OtherActor);
	if (IsValid(RefCharacter))
	{
		BP_EnOverlap();
	}
}


