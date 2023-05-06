// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathNode.generated.h"


UCLASS()
class PATHFINDING_API APathNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathNode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		// Connected Paths
		TArray<APathNode*> nodes;

		// Connected Paths distances
		TArray<float> distances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		// Connected Paths Weight
		TArray<float> weights;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		// Parent Node
		APathNode* parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		// f value
		float f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		// g value
		float g;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		// h value
		float h;

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
		// Create connections
		void LinkPaths();

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
		// Reset Values
		void ResetValues();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		FVector location;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Raise location
	void Raise();

	//reset
	void ResetLocation();

};
