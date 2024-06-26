#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AFPSCharacter.generated.h"

UCLASS()
class FPS_THEOBAUTISTA_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

protected:

	virtual void BeginPlay() override;

	// Input Mapping Context et Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* RunnerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveToLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveToRight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveToForward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveToBackwards;

	// Projectile
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AFPSProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FVector MuzzleOffset;

	// Proprietes pour les munitions
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	int32 MaxAmmo;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	int32 CurrentAmmo;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float ReloadTime;

	// Widget
	//UPROPERTY()
	//class UUserWidget* AmmoWidgetInstance;
	//UPROPERTY(EditDefaultsOnly, Category = "UI")
	//TSubclassOf<class UUserWidget> AmmoWidgetClass;




public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Fire();
	void Reload();
	void FinishReloading();

	void UpdateAmmoWidget();

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Rate);
	void LookUp(float Rate);

	FTimerHandle ReloadTimerHandle;
	bool bIsReloading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
};
