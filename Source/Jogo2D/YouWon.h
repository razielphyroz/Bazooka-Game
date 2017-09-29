// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YouWon.generated.h"

UCLASS()
class JOGO2D_API AYouWon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYouWon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere)
		class UPaperFlipbookComponent* Sprite;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
