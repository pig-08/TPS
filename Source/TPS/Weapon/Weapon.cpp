// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "Character/TPSCharacter.h"
#include "Weapon/Bullet.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshCompnoent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(MeshCompnoent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/_Art/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"));

	if (MeshRef.Succeeded())
	{
		MeshCompnoent->SetSkeletalMesh(MeshRef.Object);
	}

	FireType = EFireType::EF_LineTrace;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	SetAmmoRemainCount(AmmoMaxCount);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::StartFire(TWeakObjectPtr<class ATPSCharacter> OwnerCharacter)
{
	ATPSCharacter* Character = OwnerCharacter.Get();

	if (Character)
	{
		switch (FireType)
		{
		case EFireType::EF_Projectile:
			GetWorldTimerManager().SetTimer(FireTImerHandle,
				 [Character, this]() {FireWithProjectile(Character); },
				FireInterval,
				true);
			break;
		case EFireType::EF_LineTrace:
			GetWorldTimerManager().SetTimer(FireTImerHandle,
				[Character, this]() {FireWithLineTeace(Character); },
				FireInterval,
				true);
			break;
		default:
			break;
		}
	}

}

void AWeapon::StopFire()
{
	if (FireTImerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FireTImerHandle);
	}
}

void AWeapon::Reloaing()
{
}

void AWeapon::FinishReloading()
{
}

void AWeapon::FireWithProjectile(TWeakObjectPtr<class ATPSCharacter> OwnerCharacter)
{
	ATPSCharacter* Character = OwnerCharacter.Get();

	if (Character == nullptr)
		return;

	if (AmmoRemainCount <= 0)
	{
		Character->StopAnimMontage(Character->GetCurrentMontage());

		StopFire();
		return;
	}

	FTransform FireTransform = MeshCompnoent->GetSocketTransform("FireSocket");

	FVector Direction = FireTransform.GetRotation().GetForwardVector() * TracerDistance;

	FActorSpawnParameters SpawnParameter;
	SpawnParameter.Owner = Character;

	ABullet* SpawnBullet = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), SpawnParameter);

	if (SpawnBullet)
	{
		SpawnBullet->SetActorLocation(FireTransform.GetLocation());
		SpawnBullet->SetActorRotation(FireTransform.GetRotation());

		if (Direction.Normalize())
		{
			SpawnBullet->Fire(Direction);
		}

		SetAmmoRemainCount(--AmmoRemainCount);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, FString::Printf(TEXT("Ammmo Remain Cout :: %d"), GetAmmoRemainCount()));
	}
}

void AWeapon::FireWithLineTeace(TWeakObjectPtr<class ATPSCharacter> OwnerCharacter)
{
	ATPSCharacter* Character = OwnerCharacter.Get();

	if (Character == nullptr) return;

	if (AmmoRemainCount <= 0)
	{
		Character->StopAnimMontage(Character->GetCurrentMontage());
		StopFire();
		return;
	}

	const FVector Start = MeshCompnoent->GetSocketLocation("FireSocket");
	const FVector End = Start + Character->GetActorForwardVector() * TracerDistance;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Character);

	bool HitDetected = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (HitDetected)
	{
		if (HitResult.GetActor())
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, TEXT("LIneTraceHit"));
		}
	}

	SetAmmoRemainCount(--AmmoRemainCount);

	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, FString::Printf(TEXT("Ammo Remain Cout : %d"), GetAmmoRemainCount()));

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), Start, End, DrawColor, false, 1.0f);
#endif
}


