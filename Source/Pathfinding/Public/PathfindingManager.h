// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathNode.h"
#include "Kismet/GameplayStatics.h"
#include "PathfindingManager.generated.h"


UCLASS()
class PATHFINDING_API APathfindingManager : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	APathfindingManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		TSubclassOf<APathNode> NodeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		// Nodes
		TArray<APathNode*> nodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
		// Node player is at
		APathNode* currNode;

	TArray<APathNode*> AStar(APathNode* Dest);

	TArray<APathNode*> Trace(APathNode* Dest);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
