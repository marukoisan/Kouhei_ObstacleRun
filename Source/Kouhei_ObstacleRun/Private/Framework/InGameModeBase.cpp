// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/InGameModeBase.h"
#include "Character/BallPlayer.h"


AInGameModeBase::AInGameModeBase()
{
	//=(プレイヤーとなるClassの定義)::StaticClass();
	DefaultPawnClass = ABallPlayer::StaticClass();
}
