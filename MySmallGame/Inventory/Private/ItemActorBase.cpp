#include "../Public/ItemActorBase.h"

//Local include
#include "../Public/ItemBase.h"
#include "UI/Public/UILogIn.h"

AItemActorBase::AItemActorBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//Replication
	bReplicates = true;
	//bAlwaysRelevant = true;
	//bReplicateMovement = true;
}

void AItemActorBase::Initialize(const UItemBase* ItemBase, UObject* owner)
{

}

void AItemActorBase::Initialize(const FItemBaseInfo* itemInfo, UObject* owner)
{
	ClientDoInitialize(itemInfo->ToString(), owner);
}

void AItemActorBase::ClientDoInitialize_Implementation(const FString& itemInfo, UObject* owner = nullptr)
{
	int a = 0;
	a++;
}

AItemActorBase* AItemActorBase::CreateItemActor(const FItemBaseInfo* itemInfo, UObject* Owner)
{
	UClass* nativeItemActorClass = StaticLoadClass(AItemActorBase::StaticClass(), NULL, *(FString("/Script/KayakGame.") + itemInfo->BindActorItemClassName), NULL, LOAD_Quiet, NULL);

	FActorSpawnParameters params;
	params.Owner = (AActor*)(Owner);
	params.Name = TEXT("LIULIANYOU_ItemActorBase");
	AItemActorBase* result = params.Owner->GetWorld()->SpawnActor<AItemActorBase>(nativeItemActorClass, params);

	result->Initialize(itemInfo, Owner);

	return result;
}


AItemActorBase* AItemActorBase::CreateItemActor( const UItemBase* itemBase, UObject* owner)
{
	UClass* nativeItemActorClass = StaticLoadClass(AItemActorBase::StaticClass(), NULL, *(FString("/Script/KayakGame.") + itemBase->GetBindItemActorClassName()), NULL, LOAD_Quiet, NULL);

	AItemActorBase* result = NewObject<AItemActorBase>(GetTransientPackage(), nativeItemActorClass);

	result->Initialize(itemBase, owner);

	return result;
}