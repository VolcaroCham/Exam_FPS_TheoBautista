#include "AFPSCharacter.h"
#include "AFPSProjectile.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Controles
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	MuzzleOffset = FVector(100.f, 0.f, 0.f);

	// Les parametres pour le gun
	MaxAmmo = 30;
	CurrentAmmo = MaxAmmo;
	ReloadTime = 2.f;
	bIsReloading = false;
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*
	if (AmmoWidgetClass)
	{
		AmmoWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), AmmoWidgetClass);
		if (AmmoWidgetInstance)
		{
			AmmoWidgetInstance->AddToViewport();
			UpdateAmmoWidget();
		}
	}
	*/

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(FPSMappingContext, 0);
		}
	}
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveToForward, ETriggerEvent::Started, this, &AFPSCharacter::MoveForward);
		EIC->BindAction(MoveToRight, ETriggerEvent::Started, this, &AFPSCharacter::MoveRight);
	}
}

void AFPSCharacter::MoveForward(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("MOVE FORWARD APPUYE"));
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		UE_LOG(LogTemp, Warning, TEXT("CONTROLLER EXISTE"));
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFPSCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AFPSCharacter::Turn(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPSCharacter::LookUp(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AFPSCharacter::Fire()
{
	if (bIsReloading)
		return;

	if (CurrentAmmo > 0)
	{
		if (ProjectileClass != nullptr)
		{
			UWorld* World = GetWorld();
			if (World != nullptr)
			{
				FVector MuzzleLocation = GetActorLocation() + FTransform(GetControlRotation()).TransformVector(MuzzleOffset);
				FRotator MuzzleRotation = GetControlRotation();

				AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);
				if (Projectile)
				{
					FVector LaunchDirection = MuzzleRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);

					CurrentAmmo--;

					UpdateAmmoWidget();
				}
			}
		}
	}
	else
		Reload();
}

void AFPSCharacter::Reload()
{
	if (bIsReloading || CurrentAmmo == MaxAmmo)
		return;

	bIsReloading = true;
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AFPSCharacter::FinishReloading, ReloadTime, false);
}

void AFPSCharacter::FinishReloading()
{
	CurrentAmmo = MaxAmmo;
	bIsReloading = false;

	UpdateAmmoWidget();
}

void AFPSCharacter::UpdateAmmoWidget()
{
	/*
	if(AmmoWidgetInstance)
	{
		UTextBlock* AmmoTextBlock = Cast<UTextBlock>(AmmoWidgetInstance->GetWidgetFromName(TEXT("AmmoText")));
		if (AmmoTextBlock)
			AmmoTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Ammo: %d"), CurrentAmmo)));
	}
	*/
}