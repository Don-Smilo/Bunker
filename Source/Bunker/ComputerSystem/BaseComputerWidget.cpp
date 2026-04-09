// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseComputerWidget.h"
#include "ComputerActor.h"
#include "TerminalCommand.h"

void UBaseComputerWidget::Init(AComputerActor* InTerminal)
{
	Terminal = InTerminal;
}

void UBaseComputerWidget::SendCommand(FName Command, FName Target)
{
	if (!Terminal)
		return;

	FTerminalCommand Cmd;
	Cmd.Command = Command;
	Cmd.Target = Target;

	Terminal->HandleCommand(Cmd);
}
