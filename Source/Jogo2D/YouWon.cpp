// Fill out your copyright notice in the Description page of Project Settings.

#include "YouWon.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Personagem.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AYouWon::AYouWon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AYouWon::OnOverlapBegin);
	RootComponent = CollisionComp;

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(CollisionComp);

}

// Called when the game starts or when spawned
void AYouWon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYouWon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AYouWon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Voce Passou De Fase. PARABENS!!!"));
		Destroy();
	}
}

