// Fill out your copyright notice in the Description page of Project Settings.


#include "PathNode.h"

// Sets default values
APathNode::APathNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	nodes.Init(nullptr,8);
	distances.Init(1000, 8);
	weights.Init(1, 8);
	ResetValues();
}

// Called when the game starts or when spawned
void APathNode::BeginPlay()
{
	Super::BeginPlay();
	LinkPaths();
	location = GetActorLocation();
}

// Called every frame
void APathNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APathNode::LinkPaths() {
	for (int32 i = 0; i < nodes.Num(); i++) {
		if (nodes[i] != nullptr) {
			distances[i] = FVector::Dist(this->GetActorLocation(), nodes[i]->GetActorLocation());
		}
	}
}

void APathNode::ResetValues() {
	parent = nullptr;
	f = 100000.0;
	g = 100000.0;
	h = 100000.0;
}

void APathNode::Raise() {
	FVector temp  = location;
	temp.Z += 50.0;
	TeleportTo(temp, GetActorRotation(), true, true);
}

void APathNode::ResetLocation() {
	TeleportTo(location, GetActorRotation(), true, true);
}

