// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PT_ChangeForniture.generated.h"

UCLASS()
class POLYGONTEST_API APT_ChangeForniture : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APT_ChangeForniture();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
