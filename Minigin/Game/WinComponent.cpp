#include "MiniginPCH.h"
#include "WinComponent.h"

WinComponent::WinComponent(int amountOfEmeralds)
	:m_AmountOfEmeralds{amountOfEmeralds}
{
}

void WinComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void WinComponent::Render()
{
}
