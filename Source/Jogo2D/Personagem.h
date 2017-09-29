// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Personagem.generated.h"

/**
 * 
 */
UCLASS()
class JOGO2D_API APersonagem : public APaperCharacter
{
	GENERATED_BODY()
	
public:

	APersonagem();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent*
		PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	void UpdateFlipbook();

	UFUNCTION(BlueprintCallable, Category="Shoot")
	void StartFire();
	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void StopFire();

	void AddGunToArray(class AGun* Gun);
	int GetSelectedGun();
	TArray<class AGun*> GetGuns();

	void SetLifes(int16 NewLife);

	int16 GetLifes();

	void DarSoco();

	void AddCoin();

private:

	void DelGun();

	void ResetPersonagem();

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		class UPaperFlipbook* Idle;

	UPROPERTY(EditAnywhere)
		class UPaperFlipbook* Walking;

	UPROPERTY(EditAnywhere)
		TArray<class AGun*> Guns;

	UPROPERTY(EditAnywhere)
		int SelectedGun;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDMobile;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class APunch> MyPunch;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AYouWon> MyWonObjectBP;

	void Move(float Value);

	void TouchStarted(const ETouchIndex::Type FinderIndex,
		const FVector Location);

	void TouchStopped(const ETouchIndex::Type FinderIndex,
		const FVector Location);

	void SwitchGun();

	int16 Lifes;
	
	int16 Coins;
	
	FVector InitialLocation;
};
