// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingManager.h"


// Sets default values
APathfindingManager::APathfindingManager()
{
	nodes.Init(nullptr, 128);
}

// Called when the game starts or when spawned
void APathfindingManager::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), NodeClass, FoundActors);
	for (int i = 0; i < FoundActors.Num(); i++) {
		APathNode* myNode = Cast<APathNode>(FoundActors[i]);
		nodes[i] = myNode;
	}
}

// Called every frame
void APathfindingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<APathNode*> APathfindingManager::AStar(APathNode* Dest) {
	// Reset all values of all nodes
	for (int i = 0; i < nodes.Num(); i++) {
		if (nodes[i] != nullptr)
			nodes[i]->ResetValues();
		else break;
	}

	currNode->f = 0.0;
	currNode->g = 0.0;
	currNode->h = 0.0;
	currNode->parent = currNode;

	// Create closedList
	TArray<APathNode*> closedList;
	closedList.Init(nullptr, 128);

	// Create openList
	TArray<APathNode*> openList;
	openList.Init(nullptr, 128);

	// Add starting node as node
	openList[0] = currNode;
	
	bool foundDest = false;

	float gNew, hNew, fNew;

	bool done = false;

	while (openList[0] != nullptr) {
		int index = 0;
		float fLowest = 100000;
		for (int i = 0; i < openList.Num() - 1; i++) {
			if (openList[i] == nullptr)
				break;
			if (openList[i]->f < fLowest) {
				index = i;
				fLowest = openList[i]->f;
			}
		}
		APathNode* temp = openList[index];

		UE_LOG(LogTemp, Warning, TEXT("Open %s"), *temp->GetName());


		// Shift all elements to the left by one position
		for (int i = index; i < openList.Num() - 1; i++)
		{
			openList[i] = openList[i + 1];
		}

		closedList[closedList.Find(nullptr)] = temp;

		for (int i = 0; i < temp->nodes.Num(); i++) {
			if (temp->nodes[i] == nullptr)
				break;
			APathNode* next = temp->nodes[i];
			UE_LOG(LogTemp, Warning, TEXT("Init %s, in %f"), *next->GetName(), fNew);
			if (Dest == next) {
				next->parent = temp;
				UE_LOG(LogTemp, Warning, TEXT("Arrived %s"), *next->GetName());
				foundDest = true;
				return Trace(Dest);
			}

			else if (!closedList.Contains(next)) {
				gNew = temp-> g + temp->distances[i] * temp->weights[i];
				hNew = FVector::Dist(next->GetActorLocation(), Dest->GetActorLocation());
				fNew = gNew + hNew;
				UE_LOG(LogTemp, Warning, TEXT("Has %s, in %f %f %f"), *next->GetName(), fNew, hNew, gNew);
				if (next->f > fNew || next->f == 100000) {
					UE_LOG(LogTemp, Warning, TEXT("Added %s, in %f %f %f"), *next->GetName(), fNew, hNew, gNew);
					openList[openList.Find(nullptr)] = next;
					next->g = gNew;
					next->h = hNew;
					next->f = fNew;
					next->parent = temp;
				}
			}
		}
	}
	return Trace(Dest);
}

TArray<APathNode*> APathfindingManager::Trace(APathNode* Dest) {
	
	TArray<APathNode*> path;
	path.Init(nullptr, 128);
	APathNode* temp = Dest;

	while (temp != currNode && temp!= nullptr) {
		for (int i = path.Num() - 1; i > 0; i--)
		{
			path[i] = path[i - 1];
		}
		path[0] = temp;
		temp = temp->parent;
	}

	return path;
}



