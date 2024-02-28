// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PT_ChangeForniture.generated.h"

class APT_ActivatorFurniture;
class UPT_WidgetInteraction;
class UWidget;
class UStaticMeshComponent;
class USceneComponent;
class UCameraComponent;

UCLASS()
class POLYGONTEST_API APT_ChangeForniture : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* MeshWrokSpaceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* MeshWallComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* SpectatingCameraComponent;

protected:

	UPROPERTY(BlueprintReadWrite, Category="Furniture")
	bool bIsChangingWall;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Furniture")
	float SpectatingBlendTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Furniture")
	TMap<UStaticMesh*, FName> Furnitures;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Furniture")
	TMap<UStaticMesh*, FName> Walls;
	
	UPROPERTY(BlueprintReadOnly, Category="Furniture|Widgets")
	UPT_WidgetInteraction* WidgetInteractionClass;

	UPROPERTY(BlueprintReadOnly, Category="Furniture")
	APT_ActivatorFurniture* RefActivator;
	
public:	
	// Sets default values for this actor's properties
	APT_ChangeForniture();

	UFUNCTION(BlueprintCallable)
	void SetWidgetInteractionClass(UPT_WidgetInteraction* Widget) { WidgetInteractionClass = Widget; };

	UFUNCTION(BlueprintCallable)
	void SetActivatorReference(APT_ActivatorFurniture* Activator) { RefActivator = Activator; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Furniture")
	void ChangeCustomMesh(int Index);

	UFUNCTION(BlueprintCallable, Category="Furniture|Camera")
	void SetCameraView();

	UFUNCTION(BlueprintCallable, Category="Furniture")
	void EndInteraction();

	UFUNCTION(BlueprintCallable, Category="Furniture")
	void StartInteraction();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartInteraction();

};
