// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/InGameModeBase.h"
#include "Character/BallPlayer.h"


AInGameModeBase::AInGameModeBase()
{
	//=(�v���C���[�ƂȂ�Class�̒�`)::StaticClass();
	DefaultPawnClass = ABallPlayer::StaticClass();
}
