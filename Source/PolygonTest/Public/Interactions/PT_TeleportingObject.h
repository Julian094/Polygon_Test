// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PT_TeleportingObject.generated.h"

class UCameraComponent;
class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class UMaterialInstanceDynamic;

UCLASS()
class POLYGONTEST_API APT_TeleportingObject : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* MeshTeleportComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* SpectatingCameraComponent;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Teleport|Effects")
	FName ParameterNameEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Teleport")
	float SpectatingBlendTime;

	UPROPERTY(BlueprintReadOnly, Category="Teleport")
	FVector InitialLcoation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Teleport")
	TMap<AActor*, FName> TargetsPointsNames;

	UMaterialInstanceDynamic* ObjectMaterial;
	
public:	
	// Sets default values for this actor's properties
	APT_TeleportingObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Teleport")
	void Teleport(AActor* ObjectivePortal);

	UFUNCTION(BlueprintCallable, Category="Teleport")
	void PutObjectOnInitialLocation();

	UFUNCTION()
	void StartInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable, Category="Teleport")
	void EndInteraction();

	UFUNCTION(BlueprintCallable, Category="Telepor|Effects")
	void VisualEffect(float Value);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_StarInteraction();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SetInitialVisualEffect();

	
};
