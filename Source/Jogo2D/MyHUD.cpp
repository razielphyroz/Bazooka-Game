// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Personagem.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"

AMyHUD::AMyHUD() 
{
	ConstructorHelpers::FObjectFinder<UTexture2D> LoadTexture(TEXT("Texture2D'/Game/Sprites/heart.heart'"));
	if (LoadTexture.Succeeded()) {
		LifeTexture = LoadTexture.Object;
	}
}


void AMyHUD::DrawHUD() {
	Super::DrawHUD();
	MostrarLife();
}

void AMyHUD::MostrarLife()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (Pawn) {
		APersonagem* Personagem = Cast<APersonagem>(Pawn);
		if (Personagem) {
			
			float PositionX = 50.0f;
			for (int i = 0; i < Personagem->GetLifes(); i++) {
				DrawTextureSimple(LifeTexture, PositionX, 50.0f, 1.0f);
				PositionX += 50.0f;
			}
		}
	}
}
