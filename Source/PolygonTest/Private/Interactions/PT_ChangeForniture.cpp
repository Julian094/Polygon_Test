// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactions/PT_ChangeForniture.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APT_ChangeForniture::APT_ChangeForniture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpectatingBlendTime = 0.5f;
	
	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRootComponent"));
	RootComponent = CustomRootComponent;

	MeshWrokSpaceComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshWorkSpaceComponent"));
	MeshWrokSpaceComponent->SetupAttachment(RootComponent);

	MeshWallComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshWallComponent"));
	MeshWallComponent->SetupAttachment(RootComponent);

	SpectatingCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SpectatingCameraComponent"));
	SpectatingCameraComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APT_ChangeForniture::BeginPlay()
{
	Super::BeginPlay();
	
}

void APT_ChangeForniture::ChangeCustomMesh(int Index)
{
	TArray<UStaticMesh*> Meshes;
	if (bIsChangingWall)
	{
		Walls.GetKeys(Meshes);
		MeshWallComponent->SetStaticMesh(Meshes[Index]);
	}
	else
	{
		Furnitures.GetKeys(Meshes);
		MeshWrokSpaceComponent->SetStaticMesh(Meshes[Index]);	
	}
}

void APT_ChangeForniture::SetCameraView()
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
				PlayerController->SetViewTargetWithBlend(SpectatingCameraComponent->GetOwner(), SpectatingBlendTime, VTBlend_Cubic);
				PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);	
			}
		}
	}
}

void APT_ChangeForniture::EndInteraction()
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
			}
		}
	}
}

void APT_ChangeForniture::StartInteraction()
{
	SetCameraView();
	BP_StartInteraction();
}


