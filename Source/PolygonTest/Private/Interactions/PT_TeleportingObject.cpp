// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactions/PT_TeleportingObject.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APT_TeleportingObject::APT_TeleportingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpectatingBlendTime = 2.0f;
	ParameterNameEffect = "Appearance";

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRootComponent"));
	RootComponent = CustomRootComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	
	MeshTeleportComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponentTeleport"));
	MeshTeleportComponent->SetupAttachment(RootComponent);

	SpectatingCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SpectatingCameraComponent"));
	SpectatingCameraComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APT_TeleportingObject::BeginPlay()
{
	Super::BeginPlay();

	InitialLcoation = GetActorLocation();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APT_TeleportingObject::StartInteraction);

	ObjectMaterial = MeshTeleportComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshTeleportComponent->GetMaterial(0));	
}

void APT_TeleportingObject::Teleport(AActor* ObjectivePortal)
{
	if (IsValid(ObjectivePortal))
	{
		//SetActorLocation(ObjectivePortal->GetActorLocation());
		MeshTeleportComponent->SetWorldLocation(ObjectivePortal->GetActorLocation());
		BP_SetInitialVisualEffect();
	}
}

void APT_TeleportingObject::PutObjectOnInitialLocation()
{
	MeshTeleportComponent->SetWorldLocation(InitialLcoation);
}

void APT_TeleportingObject::StartInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* RefCharacter = Cast<ACharacter>(OtherActor);
	if (IsValid(RefCharacter))
	{
		AController* RefController = RefCharacter->GetController();
		if (IsValid(RefController))
		{
			APlayerController* PlayerController = Cast<APlayerController>(RefController);
			if (IsValid(PlayerController))
			{
				BP_StarInteraction();
				PlayerController->SetViewTargetWithBlend(SpectatingCameraComponent->GetOwner(), SpectatingBlendTime, VTBlend_Cubic);
				RefCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
			}
		}
	}
}

void APT_TeleportingObject::EndInteraction()
{
	ACharacter* RefCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ACharacter* PlayerCharacter = Cast<ACharacter>(RefCharacter);
	if (IsValid(PlayerCharacter))
	{
		AController* RefController = PlayerCharacter->GetController();
		if (IsValid(RefController))
		{
			APlayerController* PlayerController = Cast<APlayerController>(RefController);
			if (IsValid(PlayerController))
			{
				PlayerController->SetViewTargetWithBlend(PlayerCharacter, SpectatingBlendTime, VTBlend_Cubic);
				PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
				PutObjectOnInitialLocation();
				BP_SetInitialVisualEffect();
				
			}
		}
	}
}

void APT_TeleportingObject::VisualEffect(float Value)
{
	ObjectMaterial->SetScalarParameterValue(ParameterNameEffect, Value);
}






