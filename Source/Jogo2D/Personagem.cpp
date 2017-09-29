// Fill out your copyright notice in the Description page of Project Settings.

#include "Personagem.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/ChildActorComponent.h"
#include "Gun.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Punch.h"
#include "YouWon.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"

APersonagem::APersonagem() {
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>
		(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>
		(TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 2048.0f;
	Camera->SetupAttachment(CameraBoom);
		
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Lifes = 3;
}

void APersonagem::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

	if (Idle) {
		GetSprite()->SetFlipbook(Idle);
	}

	if (HUDMobile != NULL) {
		UWorld* World = GetWorld();
		if (World != nullptr) {
			APlayerController* Controller =
				UGameplayStatics::
				GetPlayerController(World, 0);
			if (Controller != nullptr) {
				UUserWidget* UserWidget =
					UWidgetBlueprintLibrary::Create
					(World, HUDMobile, Controller);
				if (UserWidget != nullptr) {
					UserWidget->AddToViewport();
				}
			}
		}
	}
}

void APersonagem::SetupPlayerInputComponent(UInputComponent * 
	PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move", this, &APersonagem::Move);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this,
		&APersonagem::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed,
		this, &APersonagem::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released,
		this, &APersonagem::StopFire);
	PlayerInputComponent->BindAction("Switch", IE_Pressed,
		this, &APersonagem::SwitchGun);
	PlayerInputComponent->BindAction("Punch", IE_Pressed,
		this, &APersonagem::DarSoco); 
		PlayerInputComponent->BindAction("DelWeapon", IE_Pressed,
			this, &APersonagem::DelGun);

	PlayerInputComponent->BindTouch(IE_Pressed, this,
		&APersonagem::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this,
		&APersonagem::TouchStopped);

}

void APersonagem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateFlipbook();

}

void APersonagem::UpdateFlipbook()
{

	if (GetVelocity().X != 0) {
		GetSprite()->SetFlipbook(Walking);
		if (GetVelocity().X > 0) {
			GetSprite()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
		} else if (GetVelocity().X < 0) {
			GetSprite()->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
	} else {
		GetSprite()->SetFlipbook(Idle);
	}

}

void APersonagem::AddCoin()
{
	Coins += 1;
	if (Coins == 5) {
		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParameters;	
			World->SpawnActor<AYouWon>(MyWonObjectBP, FVector(2300.0f, 0.0f, 80.0f), FRotator::ZeroRotator, SpawnParameters);
		}
	}
}

void APersonagem::StartFire()
{

	if (Guns.Num() > 0 && SelectedGun >= 0) {
		Guns[SelectedGun]->StartFire();
	}

	/*if (Gun != nullptr) {
		if (Gun->GetChildActor()->IsA(AGun::StaticClass())) {
			AGun* GunCast = Cast<AGun>(Gun->GetChildActor());
			GunCast->StartFire();
		}
	}*/

}

void APersonagem::StopFire()
{

	if (Guns.Num() > 0 && SelectedGun >= 0) {
		Guns[SelectedGun]->StopFire();
	}

	/*if (Gun != nullptr) {
		if (Gun->GetChildActor()->IsA(AGun::StaticClass())) {
			AGun* GunCast = Cast<AGun>(Gun->GetChildActor());
			GunCast->StopFire();
		}
	}*/
}

void APersonagem::AddGunToArray(AGun * Gun)
{
	Gun->SetActorRelativeRotation(GetActorRotation());
	Gun->GetCollisionComp()->SetCollisionProfileName("NoCollision");
	Guns.Add(Gun);
	FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld, true);
	Gun->AttachToComponent(GetSprite(), TransformRules);
	Gun->SetActorRelativeLocation(FVector(45.0f, 0.0f, 10.0f));
	int LastSelected = SelectedGun;
	SelectedGun = Guns.Num()-1;
	if (LastSelected >= 0) {
		Guns[LastSelected]->SetActorHiddenInGame(true);
	}
}

int APersonagem::GetSelectedGun()
{
	return SelectedGun;
}

TArray<class AGun*> APersonagem::GetGuns()
{
	return Guns;
}

void APersonagem::SetLifes(int16 NewLife)
{
	if (NewLife <= 0) {
		ResetPersonagem();
	} else {
		Lifes = NewLife;
	}
}

int16 APersonagem::GetLifes()
{
	return Lifes;
}

void APersonagem::DarSoco()
{
	UWorld* World = GetWorld();
	if (World != nullptr) {
		FActorSpawnParameters SpawnParam;
		APunch* Punch = World->SpawnActor<APunch>(MyPunch, RootComponent->GetComponentLocation(), GetSprite()->GetComponentRotation(), SpawnParam);
	}
}

void APersonagem::ResetPersonagem()
{
	SetActorLocation(InitialLocation);
	Lifes = 3;
}

void APersonagem::Move(float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void APersonagem::TouchStarted(const ETouchIndex::Type FinderIndex, const FVector Location)
{
	Jump();
}

void APersonagem::TouchStopped(const ETouchIndex::Type FinderIndex, const FVector Location)
{
	StopJumping();
}

void APersonagem::SwitchGun()
{
	UE_LOG(LogTemp, Warning, TEXT("VectorSize: %d, SelectedGun: %d."), Guns.Num(), SelectedGun);
	if (SelectedGun == Guns.Num() - 1) {
		SelectedGun = -1;
	} else {
		SelectedGun++;
	}

	if (SelectedGun >= 0) {
		Guns[SelectedGun]->SetActorHiddenInGame(false);
		if (SelectedGun > 0) {
			Guns[SelectedGun - 1]->SetActorHiddenInGame(true);
		}
	} else if (Guns.Num() > 0) {
		Guns[Guns.Num() - 1]->SetActorHiddenInGame(true);
	}

	/*if (Gun != nullptr &&
		Gun->GetNumChildrenComponents() > 0) {

		Gun->DestroyChildActor();

	} else if (Gun != nullptr &&
		Gun->GetNumChildrenComponents() == 0) {*/

		/*Gun->SetChildActorClass(
			StaticLoadClass(AGun::StaticClass(),
				NULL, 
				TEXT("Blueprint'/Game/Blueprints/GunBP.GunBP_C'")));*/
		/*Gun->CreateChildActor();

	}*/

}

void APersonagem::DelGun()
{
	if (Guns.Num() >= 1) {
		if (SelectedGun >= 0 && Guns[SelectedGun] != nullptr) {
			Guns[SelectedGun]->Destroy();
			Guns.Pop(SelectedGun);
			SelectedGun--;
			UE_LOG(LogTemp, Warning, TEXT("Arma Deletada!"));
			SwitchGun();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("VectorSize: %d, SelectedGun: %d."), Guns.Num(), SelectedGun);
}