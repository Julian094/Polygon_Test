// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PT_ActivatorFurniture.generated.h"

class APT_ChangeForniture;
class USceneComponent;
class UBoxComponent;

UCLASS()
class POLYGONTEST_API APT_ActivatorFurniture : public AActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* CustomRootComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* MeshActivatorComponent;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Furniture")
	APT_ChangeForniture* RefChangeFurniture;
	
public:	
	// Sets default values for this actor's properties
	APT_ActivatorFurniture();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void StartInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ActivatedInteraction(AActor* RefActor);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_EnOverlap();

};
