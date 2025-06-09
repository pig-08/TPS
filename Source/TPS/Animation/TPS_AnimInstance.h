// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPS_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UTPS_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UTPS_AnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ATPSCharacter> Character;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;

protected:
	UPROPERTY(BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	float ForwardSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float RightSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;
};
